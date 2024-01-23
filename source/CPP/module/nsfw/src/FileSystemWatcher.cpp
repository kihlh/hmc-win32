#include "pfw/FileSystemWatcher.h"

using namespace pfw;

FileSystemWatcher::FileSystemWatcher(const fs::path &          path,
                                     std::chrono::milliseconds sleepDuration,
                                     CallBackSignatur          callback)
    : NativeInterface(path, sleepDuration, callback)
{
}

FileSystemWatcher::~FileSystemWatcher() {}
