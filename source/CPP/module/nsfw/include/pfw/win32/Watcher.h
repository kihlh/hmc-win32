#ifndef PFW_WATCHER_H
#define PFW_WATCHER_H

#include <atomic>

#include "pfw/SingleshotSemaphore.h"
#include "pfw/win32/Collector.h"
#include "pfw/win32/WindowsHeader.h"

namespace pfw {

class Watcher
{
  public:
    Watcher(std::shared_ptr<Collector> collector, HANDLE dirHandle);
    ~Watcher();

    bool isRunning() const { return mRunning; }

  private:
    void run();
    bool pollDirectoryChanges();
    void start();
    void stop();

    void eventCallback(DWORD errorCode);
    void handleEvents();

    std::atomic<bool>   mRunning;
    SingleshotSemaphore mHasStartedSemaphore;

    std::shared_ptr<Collector> mCollector;
    HANDLE                     mDirectoryHandle;

    std::vector<BYTE> mBuffer;
    OVERLAPPED        mOverlapped;

    std::thread mRunner;
};

}  // namespace pfw

#endif /* PFW_WATCHER_H */
