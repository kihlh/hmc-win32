#ifndef PFW_NATIVE_INTERFACE_H
#define PFW_NATIVE_INTERFACE_H

#include "pfw/internal/definitions.h"

#ifdef PFW_WINDOWS
#include "pfw/win32/Controller.h"
using NativeImplementation = pfw::Controller;
#elif PFW_APPLE
#include "pfw/osx/FSEventsService.h"
using NativeImplementation = pfw::FSEventsService;
#elif PFW_LINUX
#include "pfw/linux/InotifyService.h"
using NativeImplementation = pfw::InotifyService;
#endif

#include "pfw/Filter.h"
#include <vector>

namespace pfw {
namespace fs = std::filesystem;

class NativeInterface
{
  public:
    NativeInterface(const fs::path &                path,
                    const std::chrono::milliseconds latency,
                    CallBackSignatur                callback);
    ~NativeInterface();

    bool isWatching();

  private:
    std::shared_ptr<Filter>               _filter;
    std::unique_ptr<NativeImplementation> _nativeInterface;
};
}  // namespace pfw

#endif /* PFW_NATIVE_INTERFACE_H */
