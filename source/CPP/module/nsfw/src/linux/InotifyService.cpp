#include "pfw/linux/InotifyService.h"

using namespace pfw;

InotifyService::InotifyService(std::shared_ptr<Filter>         filter,
                               const std::filesystem::path &   path,
                               const std::chrono::milliseconds latency)
    : mCollector(std::make_shared<Collector>(filter, latency))
    , mEventLoop(NULL)
    , mTree(NULL)
{
    mInotifyInstance = inotify_init();

    if (mInotifyInstance == -1) {
        mCollector->sendError("could not init inotify");
        return;
    }

    mTree = new InotifyTree(mInotifyInstance, path, mCollector);
    if (!mTree->isRootAlive()) {
        delete mTree;
        mTree      = NULL;
        mEventLoop = NULL;
    } else {
        mEventLoop = new InotifyEventLoop(mInotifyInstance, this);
    }
}

InotifyService::~InotifyService()
{
    if (mEventLoop != NULL) {
        delete mEventLoop;
    }

    if (mTree != NULL) {
        delete mTree;
    }

    close(mInotifyInstance);
}

void InotifyService::create(int wd, std::filesystem::path name)
{
    dispatch(CREATED, wd, name);
}

void InotifyService::sendError(std::string errorMsg)
{
    mCollector->sendError(errorMsg);
}

void InotifyService::dispatch(EventType             actionOld,
                              int                   wdOld,
                              std::filesystem::path nameOld,
                              EventType             actionNew,
                              int                   wdNew,
                              std::filesystem::path nameNew)
{
    std::vector<EventPtr> result;
    std::filesystem::path pathOld;
    if (!mTree->getRelPath(pathOld, wdOld)) {
        return;
    }
    result.emplace_back(std::make_unique<Event>(actionOld, pathOld / nameOld));

    std::filesystem::path pathNew;
    if (!mTree->getRelPath(pathNew, wdNew)) {
        return;
    }
    result.emplace_back(std::make_unique<Event>(actionNew, pathNew / nameNew));

    mCollector->insert(std::move(result));
}

void InotifyService::dispatch(EventType             action,
                              int                   wd,
                              std::filesystem::path name)
{
    std::filesystem::path path;
    if (!mTree->getRelPath(path, wd)) {
        return;
    }

    std::filesystem::path newPath = path / name;

    mCollector->push_back(action, newPath);
}

bool InotifyService::isWatching()
{
    if (mTree == NULL || mEventLoop == NULL) {
        return false;
    }

    return mTree->isRootAlive() && mEventLoop->isLooping();
}

void InotifyService::modify(int wd, std::filesystem::path name)
{
    dispatch(MODIFIED, wd, name);
}

void InotifyService::remove(int wd, std::filesystem::path name)
{
    dispatch(DELETED, wd, name);
}

void InotifyService::createDirectory(int                   wd,
                                     std::filesystem::path name,
                                     bool                  sendInitEvents)
{
    if (!mTree->nodeExists(wd)) {
        return;
    }

    mTree->addDirectory(wd, name, sendInitEvents);
    dispatch(CREATED, wd, name);
}

void InotifyService::removeDirectory(int wd) { mTree->removeDirectory(wd); }

void InotifyService::removeDirectory(int wd, const std::filesystem::path &name)
{
    mTree->removeDirectory(wd, name);
}

void InotifyService::move(int                   wdOld,
                          std::filesystem::path oldName,
                          int                   wdNew,
                          std::filesystem::path newName)
{
    dispatch(DELETED | RENAMED, wdOld, oldName, CREATED | RENAMED, wdNew,
             newName);
}

void InotifyService::moveDirectory(int                   wdOld,
                                   std::filesystem::path oldName,
                                   int                   wdNew,
                                   std::filesystem::path newName)
{
    move(wdOld, oldName, wdNew, newName);
    mTree->moveDirectory(wdOld, oldName, wdNew, newName);
}
