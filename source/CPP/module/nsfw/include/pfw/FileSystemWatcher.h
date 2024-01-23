#ifndef PFW_FILESYSTEM_WATCHER_H
#define PFW_FILESYSTEM_WATCHER_H

#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "pfw/Filter.h"
#include "pfw/NativeInterface.h"

namespace pfw {

class FileSystemWatcher : public NativeInterface
{
  public:
    FileSystemWatcher(const fs::path &path,
                      std::chrono::milliseconds    sleepDuration,
                      CallBackSignatur             callback);
    ~FileSystemWatcher();
};

}  // namespace pfw

#endif /* PFW_FILESYSTEM_WATCHER_H */
