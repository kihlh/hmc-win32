#ifndef PFW_INOTIFY_SERVICE_H
#define PFW_INOTIFY_SERVICE_H

#include <map>
#include <queue>

#include "pfw/Filter.h"
#include "pfw/linux/Collector.h"
#include "pfw/linux/InotifyEventLoop.h"
#include "pfw/linux/InotifyTree.h"

namespace pfw {

class InotifyEventLoop;
class InotifyTree;

class InotifyService
{
  public:
    InotifyService(std::shared_ptr<Filter>         filter,
                   const std::filesystem::path &   path,
                   const std::chrono::milliseconds latency);

    bool isWatching();

    ~InotifyService();

  private:
    void create(int wd, std::filesystem::path name);
    void
         createDirectory(int wd, std::filesystem::path name, bool sendInitEvents);
    void dispatch(EventType action, int wd, std::filesystem::path name);
    void dispatch(EventType             actionOld,
                  int                   wdOld,
                  std::filesystem::path nameOld,
                  EventType             actionNew,
                  int                   wdNew,
                  std::filesystem::path nameNew);
    void modify(int wd, std::filesystem::path name);
    void remove(int wd, std::filesystem::path name);
    void removeDirectory(int wd);
    void removeDirectory(int wd, const std::filesystem::path &name);
    void sendError(std::string errorMsg);
    void move(int                   wdOld,
              std::filesystem::path oldName,
              int                   wdNew,
              std::filesystem::path newName);
    void moveDirectory(int                   wdOld,
                       std::filesystem::path oldName,
                       int                   wdNew,
                       std::filesystem::path newName);

    InotifyEventLoop *         mEventLoop;
    std::shared_ptr<Collector> mCollector;
    InotifyTree *              mTree;
    int                        mInotifyInstance;

    friend class InotifyEventLoop;
};

}  // namespace pfw

#endif /* PFW_INOTIFY_SERVICE_H */