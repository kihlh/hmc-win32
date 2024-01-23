#include "pfw/win32/Controller.h"

namespace fs = std::filesystem;
using namespace pfw;

HANDLE Controller::openDirectory(const fs::path &path)
{
    return CreateFileW(path.c_str(), FILE_LIST_DIRECTORY,
                       FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                       NULL, OPEN_EXISTING,
                       FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
}

Controller::Controller(FilterPtr                       filter,
                       const fs::path &                path,
                       const std::chrono::milliseconds latency)
    : mDirectoryHandle(INVALID_HANDLE_VALUE)
    , mWatcher(nullptr)
    , mCollector(std::make_shared<Collector>(filter, latency))
{
    mDirectoryHandle = openDirectory(path);

    if (mDirectoryHandle == INVALID_HANDLE_VALUE) {
        mCollector->sendError("Failed to open directory.");
        return;
    }

    mWatcher.reset(new Watcher(mCollector, mDirectoryHandle));
}

Controller::~Controller()
{
    mWatcher.reset();
    CancelIo(mDirectoryHandle);
    CloseHandle(mDirectoryHandle);
    mDirectoryHandle = INVALID_HANDLE_VALUE;
}

bool Controller::isWatching()
{
    return (bool)mWatcher && mWatcher->isRunning();
}
