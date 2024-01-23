#include "pfw/osx/FSEventsService.h"

#include "pfw/osx/RunLoop.h"

#include <chrono>
#include <iostream>

using namespace pfw;

FSEventsService::FSEventsService(std::shared_ptr<Filter>          filter,
                                 std::filesystem::path            path,
                                 const std::chrono::milliseconds &latency)
    : mFilter(filter)
{
    std::error_code ec;
    mPath = std::filesystem::canonical(path, ec);
    if (ec) {
        mFilter->sendError("Failed to open directory.");
        mRunLoop = NULL;
        return;
    }

    mRunLoop = new RunLoop(this, mPath, latency);

    if (!mRunLoop->isLooping()) {
        delete mRunLoop;
        mRunLoop = NULL;
        return;
    }
}

FSEventsService::~FSEventsService()
{
    if (mRunLoop != NULL) {
        delete mRunLoop;
    }
}

void FSEventsService::FSEventsServiceCallback(
    ConstFSEventStreamRef         streamRef,
    void *                        clientCallBackInfo,
    size_t                        numEvents,
    void *                        eventPaths,
    const FSEventStreamEventFlags eventFlags[],
    const FSEventStreamEventId    eventIds[])
{
    static std::mutex           mutex;
    std::lock_guard<std::mutex> locked(mutex);

    FSEventsService *eventsService = (FSEventsService *)clientCallBackInfo;
    char **          paths         = (char **)eventPaths;
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch())
                    .count();

    std::vector<EventPtr> events;
    for (size_t i = 0; i < numEvents; ++i) {
        if ((eventFlags[i] & kFSEventStreamEventFlagUserDropped) ==
            kFSEventStreamEventFlagUserDropped) {
            events.emplace_back(new Event(BUFFER_OVERFLOW, ""));
            continue;
        }

        if ((eventFlags[i] & kFSEventStreamEventFlagKernelDropped) ==
            kFSEventStreamEventFlagKernelDropped) {
            events.emplace_back(new Event(BUFFER_OVERFLOW, ""));
            continue;
        }

        const auto absPath = std::filesystem::path(paths[i]);

        bool isCreated = (eventFlags[i] & kFSEventStreamEventFlagItemCreated) ==
                         kFSEventStreamEventFlagItemCreated;
        bool isRemoved = (eventFlags[i] & kFSEventStreamEventFlagItemRemoved) ==
                         kFSEventStreamEventFlagItemRemoved;
        bool isModified =
            (eventFlags[i] & kFSEventStreamEventFlagItemModified) ==
                kFSEventStreamEventFlagItemModified ||
            (eventFlags[i] & kFSEventStreamEventFlagItemInodeMetaMod) ==
                kFSEventStreamEventFlagItemInodeMetaMod ||
            (eventFlags[i] & kFSEventStreamEventFlagItemFinderInfoMod) ==
                kFSEventStreamEventFlagItemFinderInfoMod ||
            (eventFlags[i] & kFSEventStreamEventFlagItemChangeOwner) ==
                kFSEventStreamEventFlagItemChangeOwner ||
            (eventFlags[i] & kFSEventStreamEventFlagItemXattrMod) ==
                kFSEventStreamEventFlagItemXattrMod;
        bool isRenamed = (eventFlags[i] & kFSEventStreamEventFlagItemRenamed) ==
                         kFSEventStreamEventFlagItemRenamed;

        EventType type = NOOP;
        if (isCreated) {
            type = type | CREATED;
        }
        if (isModified) {
            type = type | MODIFIED;
        }
        if (isRemoved) {
            type = type | DELETED;
        }
        if (isRenamed) {
            if (!std::filesystem::exists(absPath)) {
                type = type | DELETED;
            } else {
                type = type | CREATED;
            }
            type = type | RENAMED;
        }

        const auto relPath =
            absPath.lexically_relative(eventsService->rootPath());

        auto relPathItr = relPath.begin();
        if (*relPathItr == "." || *relPathItr == "..") {
            continue;
        }

        events.emplace_back(new Event(type, relPath));
    }
    eventsService->dispatch(std::move(events));
}

void FSEventsService::dispatch(std::vector<EventPtr> &&events)
{
    mFilter->filterAndNotify(std::move(events));
}

const std::filesystem::path &FSEventsService::rootPath() { return mPath; }

void FSEventsService::sendError(const std::string &errorMsg)
{
    mFilter->sendError(errorMsg);
}

bool FSEventsService::isWatching()
{
    return mRunLoop != NULL && mRunLoop->isLooping();
}
