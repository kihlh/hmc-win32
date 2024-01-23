#ifndef PFW_CONTROLLER_H
#define PFW_CONTROLLER_H

#include <filesystem>
#include <memory>
#include <string>

#include "pfw/win32/Collector.h"
#include "pfw/win32/Watcher.h"
#include "pfw/win32/WindowsHeader.h"

namespace pfw {

class Controller
{
  public:
    Controller(FilterPtr                       filter,
               const std::filesystem::path &   path,
               const std::chrono::milliseconds latency);
    ~Controller();

    bool isWatching();

  private:
    std::unique_ptr<Watcher>   mWatcher;
    std::shared_ptr<Collector> mCollector;

    HANDLE openDirectory(const std::filesystem::path &path);
    HANDLE mDirectoryHandle;
};

}  // namespace pfw

#endif /* PFW_CONTROLLER_H */
