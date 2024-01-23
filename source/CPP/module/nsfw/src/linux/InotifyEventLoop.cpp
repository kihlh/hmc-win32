#include "pfw/linux/InotifyEventLoop.h"

#include <sys/ioctl.h>

#include <csignal>
#include <iostream>

using namespace pfw;

InotifyEventLoop::InotifyEventLoop(int             inotifyInstance,
                                   InotifyService *inotifyService)
    : mInotifyService(inotifyService)
    , mInotifyInstance(inotifyInstance)
    , mStopped(true)
{
    int result = pthread_create(&mEventLoop, nullptr, work, this);

    if (result != 0) {
        mInotifyService->sendError(
            "Could not start InotifyEventLoop thread. ErrorCode: " +
            std::string(strerror(errno)));
        return;
    }

    mThreadStartedSemaphore.wait();
}

bool InotifyEventLoop::isLooping() { return !mStopped; }

void InotifyEventLoop::created(inotify_event *event,
                               bool           isDirectoryEvent,
                               bool           sendInitEvents)
{
    if (event == NULL || mStopped) {
        return;
    }

    if (isDirectoryEvent) {
        mInotifyService->createDirectory(event->wd, event->name,
                                         sendInitEvents);
    } else {
        mInotifyService->create(event->wd, event->name);
    }
}
void InotifyEventLoop::modified(inotify_event *event)
{
    if (event == NULL || mStopped) {
        return;
    }

    mInotifyService->modify(event->wd, event->name);
}
void InotifyEventLoop::deleted(inotify_event *event, bool isDirectoryRemoval)
{
    if (event == NULL || mStopped) {
        return;
    }

    if (isDirectoryRemoval) {
        mInotifyService->removeDirectory(event->wd);
    } else {
        mInotifyService->remove(event->wd, event->name);
    }
}
void InotifyEventLoop::moveStart(inotify_event *     event,
                                 bool                isDirectoryEvent,
                                 InotifyRenameEvent &renameEvent)
{
    if (mStopped) {
        return;
    }

    renameEvent = InotifyRenameEvent(event, isDirectoryEvent);
}
void InotifyEventLoop::moveEnd(inotify_event *     event,
                               bool                isDirectoryEvent,
                               InotifyRenameEvent &renameEvent)
{
    if (mStopped) {
        return;
    }

    if (!renameEvent.isGood) {
        return created(event, isDirectoryEvent, false);
    }

    renameEvent.isGood = false;

    if (renameEvent.cookie != event->cookie) {
        if (renameEvent.isDirectory) {
            mInotifyService->removeDirectory(renameEvent.wd, renameEvent.name);
        }
        mInotifyService->remove(renameEvent.wd, renameEvent.name);

        return created(event, isDirectoryEvent, false);
    }

    if (renameEvent.isDirectory) {
        mInotifyService->moveDirectory(renameEvent.wd, renameEvent.name,
                                       event->wd, event->name);
    } else {
        mInotifyService->move(renameEvent.wd, renameEvent.name, event->wd,
                              event->name);
    }
}

void InotifyEventLoop::finish(void *args)
{
    InotifyEventLoop *eventLoop = reinterpret_cast<InotifyEventLoop *>(args);
    eventLoop->mStopped         = true;
}

void *InotifyEventLoop::work(void *args)
{
    pthread_cleanup_push(InotifyEventLoop::finish, args);

    static const int  BUFFER_SIZE = 16384;
    InotifyEventLoop *eventLoop   = reinterpret_cast<InotifyEventLoop *>(args);

    eventLoop->mStopped = false;
    eventLoop->mThreadStartedSemaphore.signal();

    InotifyRenameEvent renameEvent;

    while (!eventLoop->mStopped) {
        char buffer[BUFFER_SIZE];

        auto bytesRead =
            read(eventLoop->mInotifyInstance, &buffer, BUFFER_SIZE);

        if (eventLoop->mStopped) {
            break;
        } else if (bytesRead == 0) {
            eventLoop->mInotifyService->sendError(
                "InotifyEventLoop thread mStopped because read returned 0.");
            break;
        } else if (bytesRead == -1) {
            // read was interrupted
            if (errno == EINTR) {
                break;
            }
            eventLoop->mInotifyService->sendError(
                "Read on inotify fails because of error: " +
                std::string(strerror(errno)));
            break;
        }

        ssize_t        position = 0;
        inotify_event *event    = nullptr;
        do {
            if (eventLoop->mStopped) {
                break;
            }
            event = (struct inotify_event *)(buffer + position);

            bool isDirectoryRemoval =
                event->mask & (uint32_t)(IN_IGNORED | IN_DELETE_SELF);
            bool isDirectoryEvent = event->mask & (uint32_t)(IN_ISDIR);

            if (renameEvent.isGood && event->cookie != renameEvent.cookie) {
                eventLoop->moveEnd(event, isDirectoryEvent, renameEvent);
            } else if (event->mask & (uint32_t)(IN_ATTRIB | IN_MODIFY)) {
                eventLoop->modified(event);
            } else if (event->mask & (uint32_t)IN_CREATE) {
                eventLoop->created(event, isDirectoryEvent);
            } else if (event->mask & (uint32_t)(IN_DELETE | IN_DELETE_SELF)) {
                eventLoop->deleted(event, isDirectoryRemoval);
            } else if (event->mask & (uint32_t)IN_MOVED_TO) {
                if (event->cookie == 0) {
                    eventLoop->created(event, isDirectoryEvent);
                    continue;
                }

                eventLoop->moveEnd(event, isDirectoryEvent, renameEvent);
            } else if (event->mask & (uint32_t)IN_MOVED_FROM) {
                if (event->cookie == 0) {
                    eventLoop->deleted(event, isDirectoryRemoval);
                    continue;
                }

                eventLoop->moveStart(event, isDirectoryEvent, renameEvent);
            } else if (event->mask & (uint32_t)IN_MOVE_SELF) {
                eventLoop->mInotifyService->remove(event->wd, event->name);
                eventLoop->mInotifyService->removeDirectory(event->wd);
            }
        } while ((position += sizeof(struct inotify_event) + event->len) <
                 bytesRead);

        if (eventLoop->mStopped) {
            break;
        }

        size_t bytesAvailable = 0;
        if (ioctl(eventLoop->mInotifyInstance, FIONREAD, &bytesAvailable) < 0) {
            continue;
        }
        if (bytesAvailable == 0) {
            // If we have a trailing renameEvent and not another event is in the
            // pipeline, then we need to finish this renameEvent. Otherwise we
            // will loose the information of pending rename event.
            if (renameEvent.isGood) {
                if (renameEvent.isDirectory) {
                    eventLoop->mInotifyService->removeDirectory(
                        renameEvent.wd, renameEvent.name);
                }
                eventLoop->mInotifyService->remove(renameEvent.wd,
                                                   renameEvent.name);
            }
        }
    }

    pthread_cleanup_pop(1);
    return nullptr;
}

InotifyEventLoop::~InotifyEventLoop()
{
    if (mStopped) {
        return;
    }
    mStopped = true;

    // \note(mathias): To be sure, that canceling the thread does not causes
    // abortion of the whole programm, because another lib reacts on signal 32,
    // we ignore the signal extra. Additionally we are saving the previous
    // handler to register this handler to signal 32 again at the end. (This is
    // only a assumption, because we was seeing this behaviour (abort of the
    // whole programm when calling dtor of NotifyEventLoop) in combination with
    // other libs without finding the root causes.
    auto previousHandler = std::signal(32, SIG_IGN);

    auto errorCode = pthread_cancel(mEventLoop);
    if (errorCode != 0) {
        mInotifyService->sendError(
            "Could not cancel InotifyEventLoop thread. ErrorCode: " +
            std::to_string(errorCode));
        return;
    }

    errorCode = pthread_join(mEventLoop, NULL);
    if (errorCode != 0) {
        mInotifyService->sendError(
            "Could not join InotifyEventLoop thread. ErrorCode: " +
            std::to_string(errorCode));
    }

    if (previousHandler != SIG_ERR) {
        std::signal(32, previousHandler);
    }
}
