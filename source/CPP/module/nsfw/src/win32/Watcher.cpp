#include "pfw/win32/Watcher.h"

#include <sstream>

#include "pfw/Event.h"

using namespace pfw;

Watcher::Watcher(std::shared_ptr<Collector> collector, HANDLE dirHandle)
    : mRunning(false)
    , mDirectoryHandle(dirHandle)
    , mCollector(collector)
{
    ::ZeroMemory(&mOverlapped, sizeof(OVERLAPPED));
    mOverlapped.hEvent = this;
    start();
}

Watcher::~Watcher() { stop(); }

void Watcher::run()
{
    while (mRunning) {
        ::SleepEx(INFINITE, true);
    }
}

bool Watcher::pollDirectoryChanges()
{
    if (!isRunning()) {
        return false;
    }

    // maximum buffer size
    mBuffer = std::vector<BYTE>(64 * 1024);
    
    const DWORD dwNotifyFilterFlag =  FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
                FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE |
                FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_ATTRIBUTES |
                FILE_NOTIFY_CHANGE_LAST_ACCESS;

    if (!::ReadDirectoryChangesW(
            mDirectoryHandle, mBuffer.data(),
            static_cast<DWORD>(mBuffer.size()),
            TRUE,  // recursive watching
            dwNotifyFilterFlag,
            NULL, &mOverlapped,
            [](DWORD errorCode, DWORD numBytes, LPOVERLAPPED overlapped) {
                auto watcher = reinterpret_cast<Watcher *>(overlapped->hEvent);
                watcher->eventCallback(errorCode);
            })) {
        mCollector->sendError("Service shutdown unexpectedly");
        stop();
        return false;
    }

    return true;
}

void Watcher::eventCallback(DWORD errorCode)
{
    if (errorCode != ERROR_SUCCESS) {
        if (errorCode == ERROR_NOTIFY_ENUM_DIR) {
            mCollector->push_back(BUFFER_OVERFLOW, "");
            pollDirectoryChanges();
            return;
        } else if (errorCode == ERROR_INVALID_PARAMETER) {
            mCollector->sendError(
                "invalid ReadDirectoryChangesW params -> shutdown");
        } else {
            mCollector->sendError("Service shutdown unexpectedly");
        }

        stop();
        return;
    }

    handleEvents();
    pollDirectoryChanges();
}

void Watcher::handleEvents()
{
    BYTE *                base = mBuffer.data();
    std::vector<EventPtr> events;
    while (true) {
        PFILE_NOTIFY_INFORMATION info = (PFILE_NOTIFY_INFORMATION)base;
        fs::path fileName = std::wstring(info->FileName, info->FileNameLength /
                                                             sizeof(wchar_t));
        
        EventPtr event;
        switch (info->Action) {
        case FILE_ACTION_RENAMED_OLD_NAME:
            event = std::make_unique<Event>(DELETED | RENAMED, fileName);
            break;
        case FILE_ACTION_RENAMED_NEW_NAME:
            event = std::make_unique<Event>(CREATED | RENAMED, fileName);
            break;
        case FILE_ACTION_ADDED:
            event = std::make_unique<Event>(CREATED, fileName);
            break;
        case FILE_ACTION_REMOVED:
            event = std::make_unique<Event>(DELETED, fileName);
            break;
        case FILE_ACTION_MODIFIED:
        default:
            event = std::make_unique<Event>(MODIFIED, fileName);
        };

        events.emplace_back(std::move(event));

        if (info->NextEntryOffset == 0) {
            break;
        }
        base += info->NextEntryOffset;
    }

    mCollector->insert(std::move(events));
}

void Watcher::start()
{
    mRunning = true;

    mRunner = std::thread([this] { run(); });

    if (!mRunner.joinable()) {
        mRunning = false;
        return;
    }

    ::QueueUserAPC(
        [](__in ULONG_PTR self) {
            auto watcher = reinterpret_cast<Watcher *>(self);
            watcher->pollDirectoryChanges();
            watcher->mHasStartedSemaphore.signal();
        },
        mRunner.native_handle(), (ULONG_PTR)this);

    if (!mHasStartedSemaphore.waitFor(std::chrono::seconds(10))) {
        mCollector->sendError("Watcher is not started");
        stop();
    }
}

void Watcher::stop()
{
    mRunning = false;
    // 在 `Watcher::run()` 中安排一个NOOP APC，强制运行循环唤醒
    // 注意到已更改的 `mRunning` 并正确终止运行循环
    ::QueueUserAPC([](__in ULONG_PTR) {}, mRunner.native_handle(),
                 (ULONG_PTR)this);
    mRunner.join();
}
