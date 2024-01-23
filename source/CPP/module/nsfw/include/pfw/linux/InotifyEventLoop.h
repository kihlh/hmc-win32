#ifndef PFW_INOTIFY_EVENT_LOOP_H
#define PFW_INOTIFY_EVENT_LOOP_H

#include <mutex>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/inotify.h>
#include <sys/select.h>
#include <unistd.h>

#include "pfw/SingleshotSemaphore.h"
#include "pfw/linux/InotifyService.h"

namespace pfw {

class InotifyService;
class Lock;

class InotifyEventLoop
{
    struct InotifyRenameEvent {
        InotifyRenameEvent()
            : isGood(false){};
        InotifyRenameEvent(inotify_event *event, bool isDirectoryEvent)
            : cookie(event->cookie)
            , name(event->name)
            , wd(event->wd)
            , isDirectory(isDirectoryEvent)
            , isGood(true){};

        uint32_t              cookie;
        bool                  isDirectory;
        bool                  isGood;
        std::filesystem::path name;
        int                   wd;
    };

  public:
    InotifyEventLoop(int inotifyInstance, InotifyService *inotifyService);

    bool isLooping();

    static void  finish(void *args);
    static void *work(void *args);

    ~InotifyEventLoop();

  private:
    void created(inotify_event *event,
                 bool           isDirectoryEvent,
                 bool           sendInitEvents = true);
    void modified(inotify_event *event);
    void deleted(inotify_event *event, bool isDirectoryRemoval);
    void moveStart(inotify_event *     event,
                   bool                isDirectoryEvent,
                   InotifyRenameEvent &renameEvent);
    void moveEnd(inotify_event *     event,
                 bool                isDirectoryEvent,
                 InotifyRenameEvent &renameEvent);

    InotifyService *  mInotifyService;
    const int         mInotifyInstance;
    std::atomic<bool> mStopped;

    pthread_t           mEventLoop;
    SingleshotSemaphore mThreadStartedSemaphore;
};

}  // namespace pfw

#endif /* PFW_INOTIFY_EVENT_LOOP_H */