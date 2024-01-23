#ifndef PFW_RUN_LOOP_H
#define PFW_RUN_LOOP_H

#include <filesystem>
#include <thread>
#include <atomic>

#include "pfw/SingleshotSemaphore.h"
#include "pfw/osx/OSXHeader.h"

namespace pfw {

class FSEventsService;

class RunLoop
{
  public:
    RunLoop(FSEventsService *                eventsService,
            const std::filesystem::path &    path,
            const std::chrono::milliseconds &latency);

    bool isLooping();

    ~RunLoop();

  private:
    void work();

    FSEventsService *               mEventsService;
    FSEventStreamRef                mEventStream;
    std::atomic<bool>               mExited;
    std::filesystem::path           mPath;
    const std::chrono::milliseconds mLatency;
    CFRunLoopRef                    mRunLoop;
    std::thread                     mRunLoopThread;
    SingleshotSemaphore             mReadyForCleanup;
    std::atomic<bool>               mStarted;
    std::atomic<bool>               mShutdown;
};

}  // namespace pfw

#endif /* PFW_RUN_LOOP_H */
