#ifndef PFW_INOTIFY_NODE_H
#define PFW_INOTIFY_NODE_H

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <filesystem>
#include <map>

namespace pfw {

class InotifyTree;

class InotifyNode
{
  public:
    InotifyNode(InotifyTree *                tree,
                int                          inotifyInstance,
                InotifyNode *                parent,
                const std::filesystem::path &rootFileWatcherPath,
                const std::filesystem::path &relativePath,
                bool                         bSendInitEvent);

    void initRecursively(bool bSendInitEvent);
    void addChild(const std::filesystem::path &name, bool sendInitEvents);
    void fixPaths();
    std::filesystem::path getRelPath();
    std::filesystem::path getName();
    InotifyNode *         getParent();
    bool                  isAlive();
    void                  removeChild(const std::filesystem::path &name);
    InotifyNode *         removeAndGetChild(const std::filesystem::path &name);
    void                  insertChild(InotifyNode *childNode);
    void                  setNewParent(const std::filesystem::path &filename,
                                       InotifyNode *                parentNode);

    ~InotifyNode();

  private:
    static std::filesystem::path
                     createFullPath(const std::filesystem::path &root,
                                    const std::filesystem::path &relPath);
    static const int ATTRIBUTES = IN_ATTRIB | IN_CREATE | IN_DELETE |
                                  IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO |
                                  IN_DELETE_SELF;

    bool                                            mAlive;
    std::map<std::filesystem::path, InotifyNode *> *mChildren;
    const std::filesystem::path                     mFileWatcherRoot;
    std::filesystem::path                           mRelPath;
    const int                                       mInotifyInstance;
    InotifyNode *                                   mParent;
    InotifyTree *                                   mTree;
    int                                             mWatchDescriptor;
    bool                                            mWatchDescriptorInitialized;
};

}  // namespace pfw

#endif /* PFW_INOTIFY_NODE_H */