#include <node_api.h>
#include "hmc_napi_value_util.h"

#ifdef _DEBUG
#ifdef _WIN64
#pragma comment(lib, "hmc-module-static_DEBUG_X64.lib")
#else
#pragma comment(lib, "hmc-module-static_DEBUG_X86.lib")
#endif
#else
#ifdef _WIN64
#pragma comment(lib, "hmc-module-static_RELEASE_X64.lib")
#else
#pragma comment(lib, "hmc-module-static_RELEASE_X86.lib")
#endif
#endif

// clip.cpp
extern napi_value getClipboardFilePaths(napi_env env, napi_callback_info info);
extern napi_value setClipboardText(napi_env env, napi_callback_info info);
extern napi_value getClipboardText(napi_env env, napi_callback_info info);
extern napi_value clearClipboard(napi_env env, napi_callback_info info);
extern napi_value setClipboardFilePaths(napi_env env, napi_callback_info info);
extern napi_value getClipboardInfo(napi_env env, napi_callback_info info);
extern napi_value enumClipboardFormats(napi_env env, napi_callback_info info);
extern napi_value getClipboardHTML(napi_env env, napi_callback_info info);

// shell.cpp
extern napi_value getTrayList(napi_env env, napi_callback_info info);
extern napi_value trashFile(napi_env env, napi_callback_info info);
extern napi_value copyFile(napi_env env, napi_callback_info info);
extern napi_value moveFile(napi_env env, napi_callback_info info);
extern napi_value clearTrash(napi_env env, napi_callback_info info);
extern napi_value getThumbnailPng(napi_env env, napi_callback_info info);
extern napi_value getLinkTarget(napi_env env, napi_callback_info info);
extern napi_value setFolderIcon(napi_env env, napi_callback_info info);
extern napi_value isLinkLink(napi_env env, napi_callback_info info);
extern napi_value setShortcutLink(napi_env env, napi_callback_info info);
extern napi_value createFsLink(napi_env env, napi_callback_info info);
extern napi_value getSystemMetrics(napi_env env, napi_callback_info info);
extern napi_value getShortcutLink(napi_env env, napi_callback_info info);
extern napi_value showContextMenu(napi_env env, napi_callback_info info);
extern napi_value setConversionStatus(napi_env env, napi_callback_info info);

// screen.cpp
extern napi_value captureBmpToBuff(napi_env env, napi_callback_info info);
extern napi_value captureBmpToFile(napi_env env, napi_callback_info info);

// window.cpp

void exports_window_async_fun(napi_env env, napi_value exports);
void exports_screen_async_fun(napi_env env, napi_value exports);

namespace shell_startup
{
    extern napi_value set(napi_env env, napi_callback_info info);
    extern napi_value setOnce(napi_env env, napi_callback_info info);
    extern napi_value remove(napi_env env, napi_callback_info info);
    extern napi_value has(napi_env env, napi_callback_info info);
    extern napi_value removeOnce(napi_env env, napi_callback_info info);
    extern napi_value hasOnce(napi_env env, napi_callback_info info);
    extern napi_value StartupClassConstructor(napi_env env, napi_callback_info info);
}