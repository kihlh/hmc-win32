#include "./main.h"
#include "./export/export.h"
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
        
    };
    
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);

    atexit(hmc_gc_func);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
