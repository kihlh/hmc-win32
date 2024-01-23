#include "pfw/linux/InotifyTree.h"

using namespace pfw;

InotifyTree::InotifyTree(int                          inotifyInstance,
                         const std::filesystem::path &path,
                         std::shared_ptr<Collector>   collector)
    : mRoot(NULL)
    , mInotifyInstance(inotifyInstance)
    , mCollector(collector)
{
    if (!std::filesystem::exists(path)) {
        mCollector->sendError("Failed to open directory.");
        return;
    }

    mRoot = new InotifyNode(this, mInotifyInstance, NULL, path,
                            std::filesystem::path(""), false);

    if (!mRoot->isAlive()) {
        mCollector->sendError("Service shutdown unexpectedly.");
        delete mRoot;
        mRoot = NULL;
        return;
    }
}

void InotifyTree::sendInitEvent(const std::filesystem::path relPath)
{
    mCollector->push_back(CREATED, relPath);
}

InotifyNode *InotifyTree::getInotifyTreeByWatchDescriptor(int watchDescriptor)
{
    std::lock_guard<std::mutex> locked(mapBlock);
    auto nodeIterator = mInotifyNodeByWatchDescriptor.find(watchDescriptor);
    if (nodeIterator == mInotifyNodeByWatchDescriptor.end()) {
        return NULL;
    }

    return nodeIterator->second;
}

void InotifyTree::addDirectory(int                          wd,
                               const std::filesystem::path &name,
                               bool                         sendInitEvents)
{
    InotifyNode *node = getInotifyTreeByWatchDescriptor(wd);

    if (node != NULL) {
        node->addChild(name, sendInitEvents);
    }
}

void InotifyTree::addNodeReferenceByWD(int wd, InotifyNode *node)
{
    std::lock_guard<std::mutex> locked(mapBlock);
    mInotifyNodeByWatchDescriptor[wd] = node;
}

bool InotifyTree::getRelPath(std::filesystem::path &out, int wd)
{
    InotifyNode *node = getInotifyTreeByWatchDescriptor(wd);

    if (node == NULL) {
        return false;
    }

    out = node->getRelPath();
    return true;
}

bool InotifyTree::isRootAlive() { return mRoot != NULL; }

bool InotifyTree::nodeExists(int wd)
{
    std::lock_guard<std::mutex> locked(mapBlock);
    auto nodeIterator = mInotifyNodeByWatchDescriptor.find(wd);
    return nodeIterator != mInotifyNodeByWatchDescriptor.end();
}

void InotifyTree::removeDirectory(int wd, const std::filesystem::path &name)
{
    InotifyNode *node = getInotifyTreeByWatchDescriptor(wd);

    if (node != NULL) {
        node->removeChild(name);
    }
}

void InotifyTree::removeDirectory(int wd)
{
    InotifyNode *node = getInotifyTreeByWatchDescriptor(wd);

    if (node == NULL) {
        return;
    }

    InotifyNode *parent = node->getParent();
    if (parent == NULL) {
        mCollector->sendError("Service shutdown unexpectedly.");
        delete mRoot;
        mRoot = NULL;
        return;
    }

    parent->removeChild(node->getName());
}

void InotifyTree::removeNodeReferenceByWD(int wd)
{
    std::lock_guard<std::mutex> locked(mapBlock);
    auto nodeIterator = mInotifyNodeByWatchDescriptor.find(wd);
    if (nodeIterator != mInotifyNodeByWatchDescriptor.end()) {
        mInotifyNodeByWatchDescriptor.erase(nodeIterator);
    }
}

void InotifyTree::moveDirectory(int                          wdOld,
                                const std::filesystem::path &oldName,
                                int                          wdNew,
                                const std::filesystem::path &newName)
{
    InotifyNode *node = getInotifyTreeByWatchDescriptor(wdOld);
    if (node == NULL) {
        return addDirectory(wdNew, newName, true);
    }

    InotifyNode *movingNode = node->removeAndGetChild(oldName);

    if (movingNode == NULL) {
        return addDirectory(wdNew, newName, true);
    }

    InotifyNode *nodeNew = getInotifyTreeByWatchDescriptor(wdNew);
    if (nodeNew == NULL) {
        delete movingNode;
        movingNode = NULL;
        return;
    }

    movingNode->setNewParent(newName, nodeNew);
    nodeNew->insertChild(movingNode);
}

void InotifyTree::sendError(const std::string &error)
{
    mCollector->sendError(error);
}

InotifyTree::~InotifyTree()
{
    if (isRootAlive()) {
        delete mRoot;
    }
}
