#ifndef PFW_INOTIFY_TREE_H
#define PFW_INOTIFY_TREE_H

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <map>
#include <mutex>
#include <sstream>
#include <stdlib.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <vector>

#include "pfw/linux/Collector.h"
#include "pfw/linux/InotifyNode.h"

namespace pfw {

class InotifyTree
{
  public:
    InotifyTree(int                          inotifyInstance,
                const std::filesystem::path &path,
                std::shared_ptr<Collector>   collector);

    void addDirectory(int                          wd,
                      const std::filesystem::path &name,
                      bool                         sendInitEvents);
    bool getRelPath(std::filesystem::path &out, int wd);
    bool isRootAlive();
    bool nodeExists(int wd);
    void removeDirectory(int wd);
    void removeDirectory(int wd, const std::filesystem::path &name);
    void moveDirectory(int                          wdOld,
                       const std::filesystem::path &oldName,
                       int                          wdNew,
                       const std::filesystem::path &newName);
    void sendInitEvent(const std::filesystem::path relPath);

    ~InotifyTree();

  private:
    void         sendError(const std::string &error);
    void         addNodeReferenceByWD(int watchDescriptor, InotifyNode *node);
    void         removeNodeReferenceByWD(int watchDescriptor);
    InotifyNode *getInotifyTreeByWatchDescriptor(int watchDescriptor);

    std::mutex                   mapBlock;
    std::shared_ptr<Collector>   mCollector;
    const int                    mInotifyInstance;
    std::map<int, InotifyNode *> mInotifyNodeByWatchDescriptor;
    InotifyNode *                mRoot;

    friend class InotifyNode;
};

}  // namespace pfw

#endif /* PFW_INOTIFY_TREE_H */