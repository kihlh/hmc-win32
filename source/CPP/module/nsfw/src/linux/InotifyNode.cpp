#include "pfw/linux/InotifyNode.h"

#include "pfw/linux/InotifyTree.h"

using namespace pfw;

InotifyNode::InotifyNode(InotifyTree *                tree,
                         int                          inotifyInstance,
                         InotifyNode *                parent,
                         const std::filesystem::path &fileWatcherRoot,
                         const std::filesystem::path &relPath,
                         bool                         bSendInitEvent)
    : mInotifyInstance(inotifyInstance)
    , mFileWatcherRoot(fileWatcherRoot)
    , mRelPath(relPath)
    , mParent(parent)
    , mTree(tree)
    , mWatchDescriptorInitialized(false)
    , mChildren(new std::map<std::filesystem::path, InotifyNode *>)
{

    int attr = mParent != NULL ? ATTRIBUTES : ATTRIBUTES | IN_MOVE_SELF;

    mWatchDescriptor = inotify_add_watch(
        mInotifyInstance, (mFileWatcherRoot / mRelPath).c_str(), attr);

    mAlive = (mWatchDescriptor != -1);

    if (!mAlive) {
        if (errno == EACCES) {
            mTree->sendError("Read access to the given file (" +
                             mRelPath.string() + ") is not permitted.");
        } else if (errno == EFAULT) {
            mTree->sendError("pathname points outside of the process's "
                             "accessible address space.");
        } else if (errno == ENOSPC) {
            mTree->sendError("Inotify limit reached");
        } else if (errno == ENOMEM) {
            mTree->sendError("Not enough space/cannot allocate memory");
        } else if (errno == EBADF || errno == EINVAL) {
            mTree->sendError("Invalid file descriptor");
        }

        return;
    }

    std::error_code ec;
    auto status = std::filesystem::status(mFileWatcherRoot / mRelPath, ec);
    if (ec || !std::filesystem::is_directory(status) ||
        std::filesystem::is_symlink(status)) {
        inotify_rm_watch(mInotifyInstance, mWatchDescriptor);
        mAlive = false;
        return;
    }

    mWatchDescriptorInitialized = true;
    mTree->addNodeReferenceByWD(mWatchDescriptor, this);

    initRecursively(bSendInitEvent);
}

void InotifyNode::initRecursively(bool bSendInitEvent)
{
    std::error_code ec;
    auto            dirItr =
        std::filesystem::directory_iterator(
            mFileWatcherRoot / mRelPath,
            std::filesystem::directory_options::skip_permission_denied,
            ec);
    if (ec) {
        return;
    }
    for (auto &child : dirItr) {
        std::error_code statusEc;
        auto            status = std::filesystem::status(child);
        if (statusEc || std::filesystem::is_symlink(status)) {
            continue;
        }

        const auto filename = child.path().filename();

        if (std::filesystem::is_directory(status)) {

            InotifyNode *childInotifyNode =
                new InotifyNode(mTree, mInotifyInstance, this, mFileWatcherRoot,
                                mRelPath / filename, bSendInitEvent);

            if (childInotifyNode->isAlive()) {
                (*mChildren)[filename] = childInotifyNode;
            } else {
                delete childInotifyNode;
            }
        }

        if (bSendInitEvent) {
            mTree->sendInitEvent(mRelPath / filename);
        }
    }
}

InotifyNode::~InotifyNode()
{
    if (mWatchDescriptorInitialized) {
        inotify_rm_watch(mInotifyInstance, mWatchDescriptor);
        mTree->removeNodeReferenceByWD(mWatchDescriptor);
    }

    for (auto i = mChildren->begin(); i != mChildren->end(); ++i) {
        delete i->second;
        i->second = NULL;
    }
    delete mChildren;
}

void InotifyNode::addChild(const std::filesystem::path &name,
                           bool                         sendInitEvents)
{
    InotifyNode *child =
        new InotifyNode(mTree, mInotifyInstance, this, mFileWatcherRoot,
                        mRelPath / name, sendInitEvents);

    if (child->isAlive()) {
        (*mChildren)[name] = child;
    } else {
        delete child;
    }
}

void InotifyNode::fixPaths()
{
    const auto relPath = mParent->getRelPath() / mRelPath.filename();

    if (relPath == mRelPath) {
        return;
    }

    mRelPath = relPath;

    for (auto i = mChildren->begin(); i != mChildren->end(); ++i) {
        i->second->fixPaths();
    }
}

std::filesystem::path InotifyNode::getRelPath() { return mRelPath; }

std::filesystem::path InotifyNode::getName() { return mRelPath.filename(); }

bool InotifyNode::isAlive() { return mAlive; }

InotifyNode *InotifyNode::getParent() { return mParent; }

void InotifyNode::removeChild(const std::filesystem::path &name)
{
    auto child = mChildren->find(name);
    if (child != mChildren->end()) {
        delete child->second;
        child->second = NULL;
        mChildren->erase(child);
    }
}

InotifyNode *InotifyNode::removeAndGetChild(const std::filesystem::path &name)
{
    InotifyNode *result = NULL;
    auto         child  = mChildren->find(name);
    if (child != mChildren->end()) {
        result = child->second;
        mChildren->erase(child);
    }

    return result;
}

void InotifyNode::insertChild(InotifyNode *childNode)
{
    (*mChildren)[childNode->getName()] = childNode;
}

void InotifyNode::setNewParent(const std::filesystem::path &filename,
                               InotifyNode *                parentNode)
{
    if (mRelPath == std::filesystem::path() || parentNode == NULL) {
        return;
    }
    mRelPath = mRelPath.parent_path() / filename;
    mParent  = parentNode;
    fixPaths();
}

std::filesystem::path
InotifyNode::createFullPath(const std::filesystem::path &root,
                            const std::filesystem::path &relPath)
{
    return root / relPath;
}
