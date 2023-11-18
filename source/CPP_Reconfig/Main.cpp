#include "Main.h"
#include "./util/util_node.h";
#include "./util/include/global.hpp";

static napi_value getProcessList(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "getProcessList");

    // 参数最少要求1个
    if (!hmc_napi_util::assert::argsSize(env, argsLen, 0, 1))
    {
        return NULL;
    }
    return NULL;
}

static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor BIND_NAPI_METHOD[] = {
        DECLARE_NAPI_VALUE("version", "0.0.0"),                                 // add 2023-07-23
        DECLARE_NAPI_VALUE("desc", "hmc 2.0 : ' HMC Connection System api ' "), // add 2023-07-23
        DECLARE_NAPI_VALUE("platform", "win32"),                                // add 2023-07-23
        DECLARE_NAPI_VALUE("arch", isSystemFor64bit() ? "64bit" : "32bit"),     // add 2023-07-23
        
        // 兼容屎山函数
        // ------------------------------------------------------------------------------------------------
        // DECLARE_NAPI_METHOD("getSystemIdleTime", getSystemIdleTime),
        // DECLARE_NAPI_METHOD("sleep", sleep),
        // DECLARE_NAPI_METHOD("isAdmin", isAdmin),
        // DECLARE_NAPI_METHOD("openApp", openApp),
        // DECLARE_NAPI_METHOD("openExternal", openExternal),
        // DECLARE_NAPI_METHOD("openURL", openURL),
        // DECLARE_NAPI_METHOD("openPath", openPath),
        // DECLARE_NAPI_METHOD("powerControl", powerControl),
        // DECLARE_NAPI_METHOD("getForegroundWindow", getForegroundWindow),
        // DECLARE_NAPI_METHOD("showMonitors", showMonitors),
        // DECLARE_NAPI_METHOD("shutMonitors", shutMonitors),
        // DECLARE_NAPI_METHOD("getSystemMenu", getSystemMenu),
        // DECLARE_NAPI_METHOD("messageBox", messageBox),
        // DECLARE_NAPI_METHOD("alert", alert),
        // DECLARE_NAPI_METHOD("confirm", confirm),
        // DECLARE_NAPI_METHOD("MessageError", MessageError),
        // DECLARE_NAPI_METHOD("MessageStop", MessageStop),
        // DECLARE_NAPI_METHOD("lookHandleSetTitle", lookHandleSetTitle),
        // DECLARE_NAPI_METHOD("lookHandleCloseWindow", lookHandleCloseWindow),
        // DECLARE_NAPI_METHOD("isHandleWindowVisible", isHandleWindowVisible),
        // DECLARE_NAPI_METHOD("lookHandleShowWindow", lookHandleShowWindow),
        // DECLARE_NAPI_METHOD("lookHandleGetTitle", lookHandleGetTitle),
        // DECLARE_NAPI_METHOD("getProcessHandle", getProcessHandle),
        // DECLARE_NAPI_METHOD("isSystemX64", isSystemX64),
        // DECLARE_NAPI_METHOD("getTrayList", getTrayList),
        // DECLARE_NAPI_METHOD("setHandleTransparent", setHandleTransparent),
        // DECLARE_NAPI_METHOD("getHandleProcessID", getHandleProcessID),
        // DECLARE_NAPI_METHOD("getForegroundWindowProcessID", getForegroundWindowProcessID),
        // DECLARE_NAPI_METHOD("getMetrics", getMetrics),
        // DECLARE_NAPI_METHOD("getPointWindowProcessId", getPointWindowProcessId),
        // DECLARE_NAPI_METHOD("getPointWindowName", getPointWindowName),
        // DECLARE_NAPI_METHOD("getPointWindow", getPointWindow),
        // DECLARE_NAPI_METHOD("getDeviceCaps", getDeviceCaps),
        // DECLARE_NAPI_METHOD("getWindowRect", getWindowRect),
        // DECLARE_NAPI_METHOD("setWindowMode", setWindowMode),
        // DECLARE_NAPI_METHOD("closedHandle", closedHandle),
        // DECLARE_NAPI_METHOD("setWindowTop", setWindowTop),
        // DECLARE_NAPI_METHOD("hasWindowTop", hasWindowTop),
        // DECLARE_NAPI_METHOD("windowJitter", windowJitter),
        // DECLARE_NAPI_METHOD("isHandle", isHandle),
        // DECLARE_NAPI_METHOD("getPointWindowMain", getPointWindowMain),
        // DECLARE_NAPI_METHOD("getMainWindow", getMainWindow),
        // DECLARE_NAPI_METHOD("isEnabled", isEnabled),
        // DECLARE_NAPI_METHOD("setWindowEnabled", setWindowEnabled),
        // DECLARE_NAPI_METHODRM("setWindowFocus", setForegroundWindow),
        // DECLARE_NAPI_METHODRM("setForegroundWindow", setForegroundWindow),
        // DECLARE_NAPI_METHOD("updateWindow", updateWindow),
        // DECLARE_NAPI_METHOD("SetWindowInTaskbarVisible", SetWindowInTaskbarVisible),
        // DECLARE_NAPI_METHOD("SetBlockInput", SetBlockInput),
        // DECLARE_NAPI_METHOD("system", CallSystem),
        // DECLARE_NAPI_METHOD("SetSystemHOOK", SetSystemHOOK),
        // DECLARE_NAPI_METHOD("systemStartTime", systemStartTime),
        // DECLARE_NAPI_METHODRM("getStringRegKey", getStringRegKey),
        // DECLARE_NAPI_METHODRM("hasRegistrKey", hasRegistrKey),
        // DECLARE_NAPI_METHODRM("setRegistrKey", setRegistrKey),
        // DECLARE_NAPI_METHODRM("createPathRegistr", createPathRegistr),
        // DECLARE_NAPI_METHODRM("enumRegistrKey", enumRegistrKey),
        // DECLARE_NAPI_METHODRM("getRegistrBuffValue", getRegistrBuffValue),
        // DECLARE_NAPI_METHODRM("removeStringRegKeyWalk", removeStringRegKeyWalk),
        // DECLARE_NAPI_METHODRM("removeStringRegKey", removeStringRegKey),
        // DECLARE_NAPI_METHODRM("removeStringRegValue", removeStringRegValue),
        // DECLARE_NAPI_METHODRM("setRegistrDword", setRegistrDword),
        // DECLARE_NAPI_METHODRM("setRegistrQword", setRegistrQword),
        // DECLARE_NAPI_METHODRM("getRegistrDword", getRegistrDword),
        // DECLARE_NAPI_METHODRM("getRegistrQword", getRegistrQword),
        // DECLARE_NAPI_METHODRM("getShortcutLink", getShortcutLink),
        // DECLARE_NAPI_METHODRM("setShortcutLink", setShortcutLink),
        // DECLARE_NAPI_METHODRM("createSymlink", createSymlink),
        // DECLARE_NAPI_METHODRM("createHardLink", createHardLink),
        // DECLARE_NAPI_METHODRM("createDirSymlink", createDirSymlink),
        // DECLARE_NAPI_METHODRM("getClipboardText", getClipboardText),
        // DECLARE_NAPI_METHODRM("setClipboardText", setClipboardText),
        // DECLARE_NAPI_METHODRM("clearClipboard", clearClipboard),
        // DECLARE_NAPI_METHODRM("getClipboardFilePaths", getClipboardFilePaths),
        // DECLARE_NAPI_METHODRM("setClipboardFilePaths", setClipboardFilePaths),
        // DECLARE_NAPI_METHOD("getHidUsbList", getHidUsbList),
        // DECLARE_NAPI_METHOD("getUsbDevsInfo", getUsbDevsInfo),
        // DECLARE_NAPI_METHOD("enumChildWindows", enumChildWindows),
        // DECLARE_NAPI_METHOD("deleteFile", deleteFile),
        // DECLARE_NAPI_METHOD("_SET_HMC_DEBUG", _SET_HMC_DEBUG),
        // DECLARE_NAPI_METHODRM("getClipboardSequenceNumber", getClipboardSequenceNumber),
        // DECLARE_NAPI_METHODRM("enumClipboardFormats", enumClipboardFormats),
        // DECLARE_NAPI_METHODRM("getHidUsbIdList", getHidUsbIdList),
        // DECLARE_NAPI_METHODRM("getSystemMetricsLen", getSystemMetricsLen),
        // DECLARE_NAPI_METHODRM("getCurrentMonitorRect", getCurrentMonitorRect),
        // DECLARE_NAPI_METHODRM("getDeviceCapsAll", getDeviceCapsAll),
        // DECLARE_NAPI_METHODRM("isMouseMonitorWindow", isMouseMonitorWindow),
        // DECLARE_NAPI_METHODRM("isInMonitorWindow", isInMonitorWindow),
        // DECLARE_NAPI_METHOD("getWindowStyle", getWindowStyle),
        // DECLARE_NAPI_METHOD("getWindowClassName", getWindowClassName),
        // DECLARE_NAPI_METHOD("setWindowTitleIcon", setWindowTitleIcon),
        // DECLARE_NAPI_METHODRM("setCursorPos", setCursorPos),
        // DECLARE_NAPI_METHODRM("rightClick", rightClick),
        // DECLARE_NAPI_METHODRM("leftClick", leftClick),
        // DECLARE_NAPI_METHODRM("getMouseMovePoints", getMouseMovePoints),
        // DECLARE_NAPI_METHODRM("hasKeyActivate", hasKeyActivate),
        // DECLARE_NAPI_METHODRM("getBasicKeys", getBasicKeys),
        // DECLARE_NAPI_METHODRM("mouse", mouse),
        // DECLARE_NAPI_METHODRM("installKeyboardHook", installKeyboardHook),
        // DECLARE_NAPI_METHODRM("installHookMouse", installHookMouse),
        // DECLARE_NAPI_METHODRM("unHookMouse", unHookMouse),
        // DECLARE_NAPI_METHODRM("unKeyboardHook", unKeyboardHook),
        // DECLARE_NAPI_METHODRM("getKeyboardNextSession", getKeyboardNextSession),
        // DECLARE_NAPI_METHODRM("getMouseNextSession", getMouseNextSession),
        // DECLARE_NAPI_METHODRM("isStartHookMouse", isStartHookMouse),
        // DECLARE_NAPI_METHODRM("isStartKeyboardHook", isStartKeyboardHook),
        // DECLARE_NAPI_METHODRM("getAllWindowsHandle", getAllWindowsHandle),
        // DECLARE_NAPI_METHODRM("getProcessIdHandleStore", getProcessIdHandleStore),
        // DECLARE_NAPI_METHODRM("killProcess", killProcess),
        // DECLARE_NAPI_METHODRM("getDetailsProcessList", getDetailsProcessList),
        // DECLARE_NAPI_METHODRM("getProcessList", getProcessList),
        // DECLARE_NAPI_METHODRM("hasProcess", hasProcess),
        // DECLARE_NAPI_METHODRM("isProcess", isProcess),
        // DECLARE_NAPI_METHODRM("getProcessidFilePath", getProcessidFilePath),
        // DECLARE_NAPI_METHODRM("getProcessName", getProcessName),
        // DECLARE_NAPI_METHODRM("getModulePathList", getModulePathList),
        // DECLARE_NAPI_METHODRM("enumProcessHandle", enumProcessHandle),
        // DECLARE_NAPI_METHODRM("enumProcessHandlePolling", enumProcessHandlePolling),
        // DECLARE_NAPI_METHODRM("getVolumeList", getVolumeList),
        // DECLARE_NAPI_METHODRM("formatVolumePath", formatVolumePath),
        // DECLARE_NAPI_METHODRM("getProcessThreadList", getProcessThreadList),
        // DECLARE_NAPI_METHODRM("clearEnumProcessHandle", clearEnumProcessHandle),
        // DECLARE_NAPI_METHODRM("getSubProcessID", getSubProcessID),
        // DECLARE_NAPI_METHODRM("enumAllProcessPolling", enumAllProcessPolling),
        // DECLARE_NAPI_METHODRM("enumAllProcess", enumAllProcess),
        // DECLARE_NAPI_METHODRM("getProcessParentProcessID", getProcessParentProcessID),
        // DECLARE_NAPI_METHODRM("clearEnumAllProcessList", clearEnumAllProcessList),
        // DECLARE_NAPI_METHOD("setWindowIconForExtract", setWindowIconForExtract),
        // DECLARE_NAPI_METHOD("popen", Popen),
        // DECLARE_NAPI_METHOD("_popen", __Popen),
        // DECLARE_NAPI_METHODRM("sendKeyT2C", sendKeyT2C),
        // DECLARE_NAPI_METHODRM("sendKeyboard", sendKeyboard),
        // DECLARE_NAPI_METHODRM("sendKeyT2CSync", sendKeyT2CSync),
        // DECLARE_NAPI_METHODRM("sendBasicKeys", sendBasicKeys),
        // DECLARE_NAPI_METHODRM("captureBmpToFile", captureBmpToFile),
        // DECLARE_NAPI_METHODRM("getColor", getColor),
        // DECLARE_NAPI_METHOD("createMutex", createMutex),
        // DECLARE_NAPI_METHOD("hasMutex", hasMutex),
        // DECLARE_NAPI_METHOD("putenv", putenv),
        // DECLARE_NAPI_METHOD("getenv", napi_getenv),
        // DECLARE_NAPI_METHOD("getAllEnv", getAllEnv),
        // DECLARE_NAPI_METHOD("getUDPPortProcessID", getUDPPortProcessID),
        // DECLARE_NAPI_METHOD("getTCPPortProcessID", getTCPPortProcessID),
        // ------------------------------------------------------------------------------------------------
        // 兼容屎山函数结束

    };
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
