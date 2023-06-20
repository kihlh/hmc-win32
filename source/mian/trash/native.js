"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.native = void 0;
let HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
function fnBool(...args) { console.error(HMCNotPlatform); return false; }
function fnVoid(...args) { console.error(HMCNotPlatform); return undefined; }
function fnNull(...args) { console.error(HMCNotPlatform); return null; }
function fnNum(...args) { console.error(HMCNotPlatform); return 0; }
function fnStrList(...args) { console.error(HMCNotPlatform); return []; }
function fnStr(...args) { console.error(HMCNotPlatform); return ''; }
let NotHMC = {
    MessageError: fnVoid,
    MessageStop: fnBool,
    SetBlockInput: fnBool,
    SetSystemHOOK: fnBool,
    SetWindowInTaskbarVisible: fnBool,
    alert: fnBool,
    clearClipboard: fnBool,
    closedHandle: fnVoid,
    confirm: fnBool,
    createDirSymlink: fnBool,
    createHardLink: fnBool,
    createPathRegistr: fnBool,
    createSymlink: fnBool,
    desc: "HMC Connection System api",
    enumRegistrKey: () => { console.error(HMCNotPlatform); return []; },
    getAllWindows: () => { console.error(HMCNotPlatform); return []; },
    getAllWindowsHandle: () => { console.error(HMCNotPlatform); return []; },
    getBasicKeys: () => {
        console.error(HMCNotPlatform);
        return {
            "alt": false,
            "ctrl": false,
            "shift": false,
            "win": false,
        };
    },
    getClipboardFilePaths: fnStrList,
    getClipboardText: fnStr,
    getDetailsProcessList: () => { console.error(HMCNotPlatform); return []; },
    getDeviceCaps: () => {
        console.error(HMCNotPlatform);
        return {
            "height": 0,
            "width": 0,
        };
    },
    getForegroundWindow: fnNum,
    getForegroundWindowProcessID: fnNull,
    getHandleProcessID: fnNull,
    getHidUsbList: () => { console.error(HMCNotPlatform); return []; },
    getMainWindow: fnNull,
    getMetrics: () => { console.error(HMCNotPlatform); return { "left": 0, "top": 0, "x": 0, "y": 0 }; },
    getMouseMovePoints: () => { console.error(HMCNotPlatform); return []; },
    getPointWindow: fnNull,
    getPointWindowMain: fnNum,
    getPointWindowName: fnStr,
    getPointWindowProcessId: fnNum,
    getProcessHandle: fnNull,
    getProcessList: () => { console.error(HMCNotPlatform); return []; },
    getProcessName: fnNull,
    getProcessidFilePath: fnNull,
    getRegistrBuffValue: fnVoid,
    getRegistrDword: fnNum,
    getRegistrQword: () => {
        console.error(HMCNotPlatform);
        return BigInt(0);
    },
    getShortcutLink: () => {
        console.error(HMCNotPlatform);
        return { "args": "", "cwd": '', "desc": "", "hotkey": 0, "icon": "", "iconIndex": 0, "showCmd": 0, "path": "" };
    },
    getStringRegKey: fnStr,
    getSystemIdleTime: fnNum,
    getSystemMenu: fnBool,
    getTrayList: () => { console.error(HMCNotPlatform); return []; },
    getUsbDevsInfo: fnStrList,
    getWindowRect: () => {
        console.error(HMCNotPlatform);
        return { "bottom": 0, "height": 0, "width": 0, "left": 0, "top": 0, "right": 0, "x": 0, "y": 0 };
    },
    hasKeyActivate: fnBool,
    hasProcess: fnBool,
    hasRegistrKey: fnBool,
    hasWindowTop: fnBool,
    isAdmin: fnBool,
    isEnabled: fnBool,
    isHandle: fnBool,
    isHandleWindowVisible: fnBool,
    isProcess: fnBool,
    isSystemX64: fnBool,
    killProcess: fnBool,
    leftClick: fnBool,
    lookHandleCloseWindow: fnBool,
    lookHandleGetTitle: fnNull,
    lookHandleSetTitle: fnBool,
    lookHandleShowWindow: fnBool,
    messageBox: fnNum,
    mouse: fnBool,
    openApp: fnBool,
    openExternal: fnBool,
    openPath: fnBool,
    openURL: fnBool,
    platform: "win32",
    powerControl: fnVoid,
    removeStringRegKey: fnBool,
    removeStringRegKeyWalk: fnBool,
    removeStringRegValue: fnBool,
    rightClick: fnBool,
    setClipboardFilePaths: fnBool,
    setClipboardText: fnBool,
    setCursorPos: fnBool,
    setHandleTransparent: fnBool,
    setRegistrDword: fnBool,
    setRegistrKey: fnBool,
    setRegistrQword: fnBool,
    setShortcutLink: fnBool,
    setWindowEnabled: fnBool,
    setWindowFocus: fnBool,
    setWindowMode: fnBool,
    setWindowTop: fnBool,
    showMonitors: fnBool,
    shutMonitors: fnBool,
    sleep: fnBool,
    system: fnNum,
    systemStartTime: fnNum,
    updateWindow: fnBool,
    version: "1.0.5",
    windowJitter: fnVoid,
    enumChildWindows: () => { console.error(HMCNotPlatform); return []; },
    deleteFile: fnNum,
    getClipboardSequenceNumber: fnNum,
    enumClipboardFormats: () => { console.error(HMCNotPlatform); return []; },
    getHidUsbIdList: () => { console.error(HMCNotPlatform); return []; },
    getDeviceCapsAll: () => { console.error(HMCNotPlatform); return []; },
    isInMonitorWindow: fnBool,
    isMouseMonitorWindow: fnBool,
    getCurrentMonitorRect: () => { console.error(HMCNotPlatform); return { "bottom": 0, "left": 0, "top": 0, "right": 0, }; },
    getSystemMetricsLen: fnNum
};
exports.native = (() => {
    return process.platform == "win32" ? require("./HMC.node") : NotHMC;
})();
