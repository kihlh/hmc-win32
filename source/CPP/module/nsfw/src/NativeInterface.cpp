#include "pfw/NativeInterface.h"

using namespace pfw;

NativeInterface::NativeInterface(const fs::path &   path,
                                 const std::chrono::milliseconds latency,
                                 CallBackSignatur                callback)
    : _filter(std::make_shared<Filter>(callback))
{
    _nativeInterface.reset(new NativeImplementation(_filter, path, latency));
}

NativeInterface::~NativeInterface() { _nativeInterface.reset(); }

bool NativeInterface::isWatching() { return _nativeInterface->isWatching(); }
