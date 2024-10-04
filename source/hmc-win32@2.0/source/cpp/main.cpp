#include "./main.h"
#include "./export/export.h"
#include <stdlib.h>
#include "hmc_util.h"

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
        // DECLARE_NAPI_METHODRM("captureBmpToBuff", captureBmpToBuff),
        // DECLARE_NAPI_METHODRM("captureBmpToFile", captureBmpToFile),

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
        // DECLARE_NAPI_METHODRM("getTrayList", getTrayList),
        // DECLARE_NAPI_METHODRM("trashFile", trashFile),
        // DECLARE_NAPI_METHODRM("clearTrash", clearTrash),
        // DECLARE_NAPI_METHODRM("copyFile", copyFile),
        // DECLARE_NAPI_METHODRM("moveFile", moveFile),
        // DECLARE_NAPI_METHODRM("getThumbnailPng", getThumbnailPng),
        // DECLARE_NAPI_METHODRM("getLinkTarget", getLinkTarget),
        // DECLARE_NAPI_METHODRM("setFolderIcon", setFolderIcon),
        // DECLARE_NAPI_METHODRM("isLinkLink", isLinkLink),
        // DECLARE_NAPI_METHODRM("setShortcutLink", setShortcutLink),
        // DECLARE_NAPI_METHODRM("createFsLink", createFsLink),
        // DECLARE_NAPI_METHODRM("getSystemMetrics", getSystemMetrics),
        // DECLARE_NAPI_METHODRM("getShortcutLink", getShortcutLink),
        // DECLARE_NAPI_METHODRM("showContextMenu", showContextMenu),
        // DECLARE_NAPI_METHODRM("setConversionStatus", setConversionStatus),
        DECLARE_NAPI_METHODRM("HMC_SHELL_CLASS", HMC_shell::StartupClassConstructor),
        DECLARE_NAPI_METHODRM("HMC_SHELL_STARTUP_CLASS", HMC_shell_startup::StartupClassConstructor),

        // auto.cpp
        DECLARE_NAPI_METHODRM("HMC_KEYBOARD_CLASS", HMC_Keyboard::StartupClassConstructor),
        DECLARE_NAPI_METHODRM("HMC_MOUSE_CLASS", HMC_mouse::StartupClassConstructor),
    };

    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);

    // Promise 高性能要求的

    InitAsyncFunction(env, exports, "getProcessName2", HMC_GetProcessName::StartAsyncTask, HMC_GetProcessName::ExecuteSync);
    InitAsyncFunction(env, exports, "getProcessFilePath2", HMC_GetProcessFilePath::StartAsyncTask, HMC_GetProcessFilePath::ExecuteSync);
    InitAsyncFunction(env, exports, "getProcessEnvInfo2", HMC_GetProcessEnvInfo::StartAsyncTask, HMC_GetProcessEnvInfo::ExecuteSync);
    InitAsyncFunction(env, exports, "GetRegistrEnvInfo", HMC_GetRegistrEnvInfo::StartAsyncTask, HMC_GetRegistrEnvInfo::ExecuteSync);
    InitAsyncFunction(env, exports, "HMC_PromiseEval", HMC_PromiseEval::StartAsyncTask, HMC_PromiseEval::ExecuteSync);

    // Promise 低调用量 低性能要求的
    HMC_PromiseEval::append(HMC_PromiseStore::getClipboardFilePaths2, std::nullopt, GetClipboardFilePaths2, std::nullopt);
    HMC_PromiseEval::append(HMC_PromiseStore::getClipboardText2, std::nullopt, GetClipboardText2, std::nullopt);
    // HMC_PromiseEval::append(HMC_PromiseStore::getThumbnailPng2, std::nullopt, GetThumbnailPng2, std::nullopt);

    CaptureBmp2::initialize(HMC_PromiseStore::captureBmp2);
    CloseWindow2::initialize(HMC_PromiseStore::closeWindow2);
    GetThumbnailPng2::initialize(HMC_PromiseStore::getThumbnailPng2);

    atexit(hmc_gc_func);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
