#include "pfw/osx/RunLoop.h"

#include "pfw/osx/FSEventsService.h"

using namespace pfw;

RunLoop::RunLoop(FSEventsService *                eventsService,
                 const std::filesystem::path &    path,
                 const std::chrono::milliseconds &latency)
    : mEventsService(eventsService)
    , mExited(false)
    , mShutdown(false)
    , mPath(path)
    , mLatency(latency)
    , mRunLoop(NULL)
    , mStarted(false)
{
    mRunLoopThread = std::thread([](RunLoop *rl) { rl->work(); }, this);
    mStarted       = mRunLoopThread.joinable();

    if (!mStarted) {
        mEventsService->sendError("Service shutdown unexpectedly.");
    }
}

bool RunLoop::isLooping() { return mStarted && !mExited; }

RunLoop::~RunLoop()
{
    mShutdown = true;
    if (!mStarted) {
        return;
    }

    mReadyForCleanup.wait();
    CFRunLoopStop(mRunLoop);

    mRunLoopThread.join();
}

void RunLoop::work()
{
    CFTimeInterval latency = mLatency.count() / (double)1000;
    CFStringRef    fileWatchPath =
        CFStringCreateWithCString(NULL, mPath.c_str(), kCFStringEncodingUTF8);
    CFArrayRef pathsToWatch =
        CFArrayCreate(NULL, (const void **)&fileWatchPath, 1, NULL);
    FSEventStreamContext callbackInfo{0, (void *)mEventsService, nullptr,
                                      nullptr, nullptr};

    mRunLoop = CFRunLoopGetCurrent();

    CFRunLoopPerformBlock(mRunLoop, kCFRunLoopDefaultMode,
                          ^{ mReadyForCleanup.signal(); });

    CFRunLoopWakeUp(mRunLoop);

    mEventStream = FSEventStreamCreate(
        NULL, &FSEventsService::FSEventsServiceCallback, &callbackInfo,
        pathsToWatch, kFSEventStreamEventIdSinceNow, latency,
        kFSEventStreamCreateFlagFileEvents);

    CFRelease(pathsToWatch);
    CFRelease(fileWatchPath);

    FSEventStreamScheduleWithRunLoop(mEventStream, mRunLoop,
                                     kCFRunLoopDefaultMode);

    if (FSEventStreamStart(mEventStream)) {
        CFRunLoopRun();
    } else {
        mEventsService->sendError("Could not start event stream.");
    }

    FSEventStreamStop(mEventStream);
    FSEventStreamUnscheduleFromRunLoop(mEventStream, mRunLoop,
                                       kCFRunLoopDefaultMode);
    FSEventStreamInvalidate(mEventStream);
    FSEventStreamRelease(mEventStream);

    if (!mShutdown) {
        mEventsService->sendError("Service shutdown unexpectedly.");
    }

    mExited = true;
}
