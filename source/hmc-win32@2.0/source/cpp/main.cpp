#include "./main.h"
#include "export.h"
#include <stdlib.h>

#include "hmc_automation_util.h"

static void hmc_gc_func()
{
    // 防止鼠标被锁定
    if (hmc_mouse::LimitMouseRange::hasLimitMouseRange_worker())
    {
        hmc_mouse::LimitMouseRange::stopLimitMouseRange_worker();
    }

    // 释放鼠标监听的线程
    if (!hmc_mouse::MouseHook::isValidHookMouse())
    {
        hmc_mouse::MouseHook::stopHookMouse();
    }

    // 释放键盘监听的线程
    if (!hmc_Keyboard::keyboardHook::isValidHookKeyboard())
    {
        hmc_Keyboard::keyboardHook::stopHookKeyboard();
    }
}

static napi_value Init(napi_env env, napi_value exports)
{

    napi_property_descriptor BIND_NAPI_METHOD[] = {

        // screen.cpp
        DECLARE_NAPI_METHODRM("captureBmpToBuff", captureBmpToBuff),
        DECLARE_NAPI_METHODRM("captureBmpToFile", captureBmpToFile),

        // clip.cpp
        DECLARE_NAPI_METHODRM("getClipboardFilePaths", getClipboardFilePaths),
        DECLARE_NAPI_METHODRM("setClipboardText", setClipboardText),
        DECLARE_NAPI_METHODRM("getClipboardText", getClipboardText),
        DECLARE_NAPI_METHODRM("clearClipboard", clearClipboard),
        DECLARE_NAPI_METHODRM("setClipboardFilePaths", setClipboardFilePaths),
        DECLARE_NAPI_METHODRM("getClipboardInfo", getClipboardInfo),
        DECLARE_NAPI_METHODRM("enumClipboardFormats", enumClipboardFormats),
        DECLARE_NAPI_METHODRM("getClipboardHTML", getClipboardHTML),

        // shell.cpp
        DECLARE_NAPI_METHODRM("getTrayList", getTrayList),
        DECLARE_NAPI_METHODRM("trashFile", trashFile),
        DECLARE_NAPI_METHODRM("clearTrash", clearTrash),
        DECLARE_NAPI_METHODRM("copyFile", copyFile),
        DECLARE_NAPI_METHODRM("moveFile", moveFile),
        DECLARE_NAPI_METHODRM("getThumbnailPng", getThumbnailPng),
        DECLARE_NAPI_METHODRM("getLinkTarget", getLinkTarget),
        DECLARE_NAPI_METHODRM("setFolderIcon", setFolderIcon),
        DECLARE_NAPI_METHODRM("isLinkLink", isLinkLink),
        DECLARE_NAPI_METHODRM("setShortcutLink", setShortcutLink),
        DECLARE_NAPI_METHODRM("createFsLink", createFsLink),
        DECLARE_NAPI_METHODRM("getSystemMetrics", getSystemMetrics),
        DECLARE_NAPI_METHODRM("getShortcutLink", getShortcutLink),
        DECLARE_NAPI_METHODRM("showContextMenu", showContextMenu),
        DECLARE_NAPI_METHODRM("setConversionStatus", setConversionStatus),

    };

    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);

    exports_window_async_fun(env, exports /* closeWindow2 */);
    exports_screen_async_fun(env, exports /* captureBmp2 */);

    atexit(hmc_gc_func);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
