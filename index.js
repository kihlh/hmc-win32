"use strict";
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __commonJS = (cb, mod) => function __require() {
  return mod || (0, cb[__getOwnPropNames(cb)[0]])((mod = { exports: {} }).exports, mod), mod.exports;
};
var __export = (target, all) => {
  for (var name in all)
    __defProp(target, name, { get: all[name], enumerable: true });
};
var __copyProps = (to, from, except, desc2) => {
  if (from && typeof from === "object" || typeof from === "function") {
    for (let key of __getOwnPropNames(from))
      if (!__hasOwnProp.call(to, key) && key !== except)
        __defProp(to, key, { get: () => from[key], enumerable: !(desc2 = __getOwnPropDesc(from, key)) || desc2.enumerable });
  }
  return to;
};
var __toCommonJS = (mod) => __copyProps(__defProp({}, "__esModule", { value: true }), mod);

// ../node_modules/argv-split/split.js
var require_split = __commonJS({
  "../node_modules/argv-split/split.js"(exports, module2) {
    "use strict";
    var _CHARS;
    function _defineProperty(obj, key, value) {
      if (key in obj) {
        Object.defineProperty(obj, key, { value, enumerable: true, configurable: true, writable: true });
      } else {
        obj[key] = value;
      }
      return obj;
    }
    module2.exports = split;
    var MATRIX = {
      0: [a, suq, a, a, a, EOF],
      1: [eaue, aue, eaue, aue, aue, ue],
      2: [e, a, duq, a, a, EOF],
      3: [eaue, aue, aue, aue, eaue, ue],
      4: [e, sq, dq, a, tp, EOF]
    };
    var escaped = false;
    var single_quoted = false;
    var double_quoted = false;
    var ended = false;
    var FLAGS = {
      2: 0,
      5: 1,
      4: 2,
      1: 3,
      0: 4
    };
    function y() {
      var sum = 0;
      if (escaped) {
        sum++;
      }
      if (single_quoted) {
        sum += 2;
      }
      if (double_quoted) {
        sum += 4;
      }
      return FLAGS[sum];
    }
    var BACK_SLASH = "\\";
    var SINGLE_QUOTE = "'";
    var DOUBLE_QUOTE = '"';
    var WHITE_SPACE = " ";
    var CARRIAGE_RETURN = "\n";
    function x() {
      return c in CHARS ? CHARS[c] : CHARS.NORMAL;
    }
    var CHARS = (_CHARS = {}, _defineProperty(_CHARS, BACK_SLASH, 0), _defineProperty(_CHARS, SINGLE_QUOTE, 1), _defineProperty(_CHARS, DOUBLE_QUOTE, 2), _defineProperty(_CHARS, "NORMAL", 3), _defineProperty(_CHARS, WHITE_SPACE, 4), _defineProperty(_CHARS, CARRIAGE_RETURN, 5), _CHARS);
    var c = "";
    var stash = "";
    var ret = [];
    function reset() {
      escaped = false;
      single_quoted = false;
      double_quoted = false;
      ended = false;
      c = "";
      stash = "";
      ret.length = 0;
    }
    function a() {
      stash += c;
    }
    function sq() {
      single_quoted = true;
    }
    function suq() {
      single_quoted = false;
    }
    function dq() {
      double_quoted = true;
    }
    function duq() {
      double_quoted = false;
    }
    function e() {
      escaped = true;
    }
    function ue() {
      escaped = false;
    }
    function aue() {
      stash += BACK_SLASH + c;
      escaped = false;
    }
    function eaue() {
      stash += c;
      escaped = false;
    }
    function tp() {
      if (stash) {
        ret.push(stash);
        stash = "";
      }
    }
    function EOF() {
      ended = true;
    }
    function split(str) {
      if (typeof str !== "string") {
        type_error("Str must be a string. Received " + str, "NON_STRING");
      }
      reset();
      var length = str.length;
      var i = -1;
      while (++i < length) {
        c = str[i];
        MATRIX[y()][x()]();
        if (ended) {
          break;
        }
      }
      if (single_quoted) {
        error("unmatched single quote", "UNMATCHED_SINGLE");
      }
      if (double_quoted) {
        error("unmatched double quote", "UNMATCHED_DOUBLE");
      }
      if (escaped) {
        error("unexpected end with \\", "ESCAPED_EOF");
      }
      tp();
      return ret;
    }
    function error(message, code) {
      var err = new Error(message);
      err.code = code;
      throw err;
    }
    function type_error(message, code) {
      var err = new TypeError(message);
      err.code = code;
      throw err;
    }
  }
});

// source/mian/hmc.ts
var hmc_exports = {};
__export(hmc_exports, {
  Auto: () => Auto,
  Clipboard: () => Clipboard,
  HMC: () => HMC,
  HWND: () => HWND,
  MessageError: () => MessageError,
  MessageStop: () => MessageStop,
  Process: () => Process,
  Registr: () => Registr,
  SetBlockInput: () => SetBlockInput,
  SetSystemHOOK: () => SetSystemHOOK,
  SetWindowInTaskbarVisible: () => SetWindowInTaskbarVisible,
  Shell: () => Shell,
  Sleep: () => Sleep,
  Usb: () => Usb,
  Watch: () => Watch,
  WatchWindowForeground: () => WatchWindowForeground,
  WatchWindowPoint: () => WatchWindowPoint,
  WebView2OnlineInstall: () => WebView2OnlineInstall,
  Window: () => Window,
  alert: () => alert,
  analysisDirectPath: () => analysisDirectPath,
  clearClipboard: () => clearClipboard,
  closedHandle: () => closedHandle,
  confirm: () => confirm,
  createDirSymlink: () => createDirSymlink,
  createHardLink: () => createHardLink,
  createPathRegistr: () => createPathRegistr,
  createSymlink: () => createSymlink,
  default: () => hmc_default,
  deleteFile: () => deleteFile,
  desc: () => desc,
  enumChildWindows: () => enumChildWindows,
  enumRegistrKey: () => enumRegistrKey,
  freePort: () => freePort,
  getAllWindows: () => getAllWindows,
  getAllWindowsHandle: () => getAllWindowsHandle,
  getBasicKeys: () => getBasicKeys,
  getClipboardFilePaths: () => getClipboardFilePaths,
  getClipboardSequenceNumber: () => getClipboardSequenceNumber,
  getClipboardText: () => getClipboardText,
  getConsoleHandle: () => getConsoleHandle,
  getCurrentMonitorRect: () => getCurrentMonitorRect,
  getDetailsProcessList: () => getDetailsProcessList,
  getDetailsProcessNameList: () => getDetailsProcessNameList,
  getDeviceCaps: () => getDeviceCaps,
  getDeviceCapsAll: () => getDeviceCapsAll,
  getForegroundWindow: () => getForegroundWindow,
  getForegroundWindowProcessID: () => getForegroundWindowProcessID,
  getHandleProcessID: () => getHandleProcessID,
  getHidUsbList: () => getHidUsbList,
  getMainWindow: () => getMainWindow,
  getMetrics: () => getMetrics,
  getMouseMovePoints: () => getMouseMovePoints,
  getNumberRegKey: () => getNumberRegKey,
  getPointWindow: () => getPointWindow,
  getPointWindowMain: () => getPointWindowMain,
  getPointWindowName: () => getPointWindowName,
  getPointWindowProcessId: () => getPointWindowProcessId,
  getProcessHandle: () => getProcessHandle,
  getProcessList: () => getProcessList,
  getProcessName: () => getProcessName,
  getProcessNameList: () => getProcessNameList,
  getProcessidFilePath: () => getProcessidFilePath,
  getRegistrBuffValue: () => getRegistrBuffValue,
  getRegistrDword: () => getRegistrDword,
  getRegistrQword: () => getRegistrQword,
  getShortcutLink: () => getShortcutLink,
  getStringRegKey: () => getStringRegKey,
  getSystemIdleTime: () => getSystemIdleTime,
  getSystemMenu: () => getSystemMenu,
  getSystemMetricsLen: () => getSystemMetricsLen,
  getTrayList: () => getTrayList,
  getUsbDevsInfo: () => getUsbDevsInfo,
  getWebView2Info: () => getWebView2Info,
  getWindowClassName: () => getWindowClassName,
  getWindowRect: () => getWindowRect,
  getWindowStyle: () => getWindowStyle,
  getWindowTitle: () => getWindowTitle,
  hasKeyActivate: () => hasKeyActivate,
  hasProcess: () => hasProcess,
  hasRegistrKey: () => hasRegistrKey,
  hasWebView2: () => hasWebView2,
  hasWindowTop: () => hasWindowTop,
  hideConsole: () => hideConsole,
  hmc: () => hmc,
  isAdmin: () => isAdmin,
  isEnabled: () => isEnabled,
  isHandle: () => isHandle,
  isHandleWindowVisible: () => isHandleWindowVisible,
  isInMonitorWindow: () => isInMonitorWindow,
  isMouseMonitorWindow: () => isMouseMonitorWindow,
  isProcess: () => isProcess,
  isRegistrTreeKey: () => isRegistrTreeKey,
  isSystemX64: () => isSystemX64,
  keyboardHook: () => keyboardHook,
  killProcess: () => killProcess,
  killProcessName: () => killProcessName,
  leftClick: () => leftClick,
  listRegistrPath: () => listRegistrPath,
  lookHandleCloseWindow: () => lookHandleCloseWindow,
  lookHandleGetTitle: () => lookHandleGetTitle,
  lookHandleSetTitle: () => lookHandleSetTitle,
  lookHandleShowWindow: () => lookHandleShowWindow,
  messageBox: () => messageBox,
  mouse: () => mouse,
  mouseHook: () => mouseHook,
  native: () => native,
  openApp: () => openApp,
  openExternal: () => openExternal,
  openPath: () => openPath,
  openRegKey: () => openRegKey,
  openURL: () => openURL,
  platform: () => platform,
  powerControl: () => powerControl,
  processWatchdog: () => processWatchdog,
  ref: () => ref,
  registr: () => registr,
  removeStringRegKey: () => removeStringRegKey,
  removeStringRegKeyWalk: () => removeStringRegKeyWalk,
  removeStringRegValue: () => removeStringRegValue,
  removeStringTree: () => removeStringTree,
  rightClick: () => rightClick,
  setClipboardFilePaths: () => setClipboardFilePaths,
  setClipboardText: () => setClipboardText,
  setCloseWindow: () => setCloseWindow,
  setCursorPos: () => setCursorPos,
  setHandleTransparent: () => setHandleTransparent,
  setRegistrDword: () => setRegistrDword,
  setRegistrKey: () => setRegistrKey,
  setRegistrQword: () => setRegistrQword,
  setShortcutLink: () => setShortcutLink,
  setShowWindow: () => setShowWindow,
  setWindowEnabled: () => setWindowEnabled,
  setWindowFocus: () => setWindowFocus,
  setWindowMode: () => setWindowMode,
  setWindowTitle: () => setWindowTitle,
  setWindowTop: () => setWindowTop,
  showConsole: () => showConsole,
  showMonitors: () => showMonitors,
  shutMonitors: () => shutMonitors,
  sleep: () => sleep,
  system: () => system,
  systemChcp: () => systemChcp,
  systemStartTime: () => systemStartTime,
  trash: () => trash,
  updateWindow: () => updateWindow,
  version: () => version,
  watchClipboard: () => watchClipboard,
  watchUSB: () => watchUSB,
  windowJitter: () => windowJitter
});
module.exports = __toCommonJS(hmc_exports);

// source/mian/chcpList.ts
var chcpList = {
  37: "IBM037",
  437: "IBM437",
  500: "IBM500",
  708: "ASMO-708",
  720: "DOS-720",
  737: "ibm737",
  775: "ibm775",
  850: "ibm850",
  852: "ibm852",
  855: "IBM855",
  857: "ibm857",
  858: "IBM00858",
  860: "IBM860",
  861: "ibm861",
  862: "DOS-862",
  863: "IBM863",
  864: "IBM864",
  865: "IBM865",
  866: "cp866",
  869: "ibm869",
  870: "IBM870",
  874: "windows-874",
  875: "cp875",
  932: "shift_jis",
  936: "gb2312",
  949: "ks_c_5601-1987",
  950: "big5",
  1026: "IBM1026",
  1047: "IBM01047",
  1140: "IBM01140",
  1141: "IBM01141",
  1142: "IBM01142",
  1143: "IBM01143",
  1144: "IBM01144",
  1145: "IBM01145",
  1146: "IBM01146",
  1147: "IBM01147",
  1148: "IBM01148",
  1149: "IBM01149",
  1200: "utf-16",
  1201: "unicodeFFFE",
  1250: "windows-1250",
  1251: "windows-1251",
  1252: "windows-1252",
  1253: "windows-1253",
  1254: "windows-1254",
  1255: "windows-1255",
  1256: "windows-1256",
  1257: "windows-1257",
  1258: "windows-1258",
  1361: "Johab",
  1e4: "macintosh",
  10001: "x-mac-japanese",
  10002: "x-mac-chinesetrad",
  10003: "x-mac-korean",
  10004: "x-mac-arabic",
  10005: "x-mac-hebrew",
  10006: "x-mac-greek",
  10007: "x-mac-cyrillic",
  10008: "x-mac-chinesesimp",
  10010: "x-mac-romanian",
  10017: "x-mac-ukrainian",
  10021: "x-mac-thai",
  10029: "x-mac-ce",
  10079: "x-mac-icelandic",
  10081: "x-mac-turkish",
  10082: "x-mac-croatian",
  12e3: "utf-32",
  12001: "utf-32BE",
  2e4: "x-Chinese_CNS",
  20001: "x-cp20001",
  20002: "x_Chinese-Eten",
  20003: "x-cp20003",
  20004: "x-cp20004",
  20005: "x-cp20005",
  20105: "x-IA5",
  20106: "x-IA5-German",
  20107: "x-IA5-Swedish",
  20108: "x-IA5-Norwegian",
  20127: "us-ascii",
  20261: "x-cp20261",
  20269: "x-cp20269",
  20273: "IBM273",
  20277: "IBM277",
  20278: "IBM278",
  20280: "IBM280",
  20284: "IBM284",
  20285: "IBM285",
  20290: "IBM290",
  20297: "IBM297",
  20420: "IBM420",
  20423: "IBM423",
  20424: "IBM424",
  20833: "x-EBCDIC-KoreanExtended",
  20838: "IBM-Thai",
  20866: "koi8-r",
  20871: "IBM871",
  20880: "IBM880",
  20905: "IBM905",
  20924: "IBM00924",
  20932: "EUC-JP",
  20936: "x-cp20936",
  20949: "x-cp20949",
  21025: "cp1025",
  21866: "koi8-u",
  28591: "iso-8859-1",
  28592: "iso-8859-2",
  28593: "iso-8859-3",
  28594: "iso-8859-4",
  28595: "iso-8859-5",
  28596: "iso-8859-6",
  28597: "iso-8859-7",
  28598: "iso-8859-8",
  28599: "iso-8859-9",
  28603: "iso-8859-13",
  28605: "iso-8859-15",
  29001: "x-Europa",
  38598: "iso-8859-8-i",
  50220: "iso-2022-jp",
  50221: "csISO2022JP",
  50222: "iso-2022-jp",
  50225: "iso-2022-kr",
  50227: "x-cp50227",
  51932: "euc-jp",
  51936: "EUC-CN",
  51949: "euc-kr",
  52936: "hz-gb-2312",
  54936: "GB18030",
  57002: "x-iscii-de",
  57003: "x-iscii-be",
  57004: "x-iscii-ta",
  57005: "x-iscii-te",
  57006: "x-iscii-as",
  57007: "x-iscii-or",
  57008: "x-iscii-ka",
  57009: "x-iscii-ma",
  57010: "x-iscii-gu",
  57011: "x-iscii-pa",
  65e3: "utf-7",
  65001: "utf-8"
};

// source/mian/hmc.ts
var path = require("path");
var os = require("os");
var fs = require("fs");
var https = require("https");
var child_process = require("child_process");
var net = require("net");
var argvSplit = require_split();
var $_thenConsole = null;
var Hkey = {
  HKEY_CURRENT_CONFIG: "HKEY_CURRENT_CONFIG",
  HKEY_USERS: "HKEY_USERS",
  HKEY_CLASSES_ROOT: "HKEY_CLASSES_ROOT",
  HKEY_LOCAL_MACHINE: "HKEY_LOCAL_MACHINE",
  HKEY_CURRENT_USER: "HKEY_CURRENT_USER"
};
var native = (() => {
  function _require_bin() {
    try {
      if (process.arch == "x32")
        return require("./bin/HMC_x86.node");
      else
        return require("./bin/HMC_x64.node");
    } catch (error) {
      return require("../HMC.node");
    }
  }
  let Native = process.platform == "win32" ? _require_bin() : (() => {
    let HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
    function fnBool(...args) {
      console.error(HMCNotPlatform);
      return false;
    }
    function fnVoid(...args) {
      console.error(HMCNotPlatform);
      return void 0;
    }
    function fnNull(...args) {
      console.error(HMCNotPlatform);
      return null;
    }
    function fnNum(...args) {
      console.error(HMCNotPlatform);
      return 0;
    }
    function fnStrList(...args) {
      console.error(HMCNotPlatform);
      return [];
    }
    function fnStr(...args) {
      console.error(HMCNotPlatform);
      return "";
    }
    return {
      isStartKeyboardHook: fnBool,
      isStartHookMouse: fnBool,
      getMouseNextSession: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      getKeyboardNextSession: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      unKeyboardHook: fnVoid,
      unHookMouse: fnVoid,
      installKeyboardHook: fnVoid,
      installHookMouse: fnVoid,
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
      enumRegistrKey: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      getAllWindows: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      getAllWindowsHandle: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      getBasicKeys: () => {
        console.error(HMCNotPlatform);
        return {
          "alt": false,
          "ctrl": false,
          "shift": false,
          "win": false
        };
      },
      getClipboardFilePaths: fnStrList,
      getClipboardText: fnStr,
      getDetailsProcessList: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      getDeviceCaps: () => {
        console.error(HMCNotPlatform);
        return {
          "height": 0,
          "width": 0
        };
      },
      getForegroundWindow: fnNum,
      getForegroundWindowProcessID: fnNull,
      getHandleProcessID: fnNull,
      getHidUsbList: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      getMainWindow: fnNull,
      getMetrics: () => {
        console.error(HMCNotPlatform);
        return { "left": 0, "top": 0, "x": 0, "y": 0 };
      },
      getMouseMovePoints: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      getPointWindow: fnNull,
      getPointWindowMain: fnNum,
      getPointWindowName: fnStr,
      getPointWindowProcessId: fnNum,
      getProcessHandle: fnNull,
      getProcessList: () => {
        console.error(HMCNotPlatform);
        return [];
      },
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
        return { "args": "", "cwd": "", "desc": "", "hotkey": 0, "icon": "", "iconIndex": 0, "showCmd": 0, "path": "" };
      },
      getStringRegKey: fnStr,
      getSystemIdleTime: fnNum,
      getSystemMenu: fnBool,
      getTrayList: () => {
        console.error(HMCNotPlatform);
        return [];
      },
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
      version: "0.0.0",
      windowJitter: fnVoid,
      enumChildWindows: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      deleteFile: fnNum,
      getClipboardSequenceNumber: fnNum,
      enumClipboardFormats: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      getHidUsbIdList: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      getDeviceCapsAll: () => {
        console.error(HMCNotPlatform);
        return [];
      },
      isInMonitorWindow: fnBool,
      isMouseMonitorWindow: fnBool,
      getCurrentMonitorRect: () => {
        console.error(HMCNotPlatform);
        return { "bottom": 0, "left": 0, "top": 0, "right": 0 };
      },
      getSystemMetricsLen: fnNum,
      getWindowStyle: fnNum,
      getWindowClassName: fnStr
    };
  })();
  return Native;
})();
var HWND = class extends Number {
  constructor(hWnd) {
    super(hWnd);
    this.HWND = hWnd;
  }
  get handle() {
    return this.HWND;
  }
  closed() {
    if (!this.exists)
      return false;
    return native.closedHandle(this.HWND);
  }
  close() {
    if (!this.exists)
      return false;
    return native.lookHandleCloseWindow(this.HWND);
  }
  get rect() {
    if (!this.exists)
      return null;
    return native.getWindowRect(this.HWND);
  }
  get title() {
    return native.lookHandleGetTitle(this.HWND) || "";
  }
  setTitle(Title) {
    if (typeof Title !== "string" || !this.exists) {
      return false;
    }
    return native.lookHandleSetTitle(this.HWND, Title);
  }
  get exists() {
    if (!this.HWND)
      return false;
    return native.isHandle(this.HWND);
  }
  get isHandle() {
    return this.exists;
  }
  get pid() {
    if (!this.exists)
      return 0;
    return native.getHandleProcessID(this.HWND);
  }
  get MianPid() {
    if (!this.exists)
      return 0;
    return native.getHandleProcessID(this.MainHandle);
  }
  get MainHandle() {
    return native.getMainWindow(this.HWND) || 0;
  }
  get className() {
    return native.getWindowClassName(this.HWND);
  }
  get style() {
    return native.getWindowStyle(this.HWND);
  }
  isVisible() {
    if (!this.HWND)
      return false;
    return native.isHandleWindowVisible(this.HWND);
  }
  kill() {
    let processid = this.MianPid;
    if (!processid)
      return false;
    return native.killProcess(processid);
  }
  hide() {
    if (!this.HWND)
      return false;
    return native.lookHandleShowWindow(this.HWND, 0);
  }
  show() {
    if (!this.HWND)
      return false;
    return native.lookHandleShowWindow(this.HWND, 5);
  }
  setMin() {
    if (!this.HWND)
      return false;
    return native.lookHandleShowWindow(this.HWND, 7);
  }
  setMax() {
    if (!this.HWND)
      return false;
    return native.lookHandleShowWindow(this.HWND, 3);
  }
  setRestore() {
    if (!this.HWND)
      return false;
    return native.lookHandleShowWindow(this.HWND, 9);
  }
  setFocus() {
    if (!this.HWND)
      return false;
    return native.setWindowFocus(this.HWND);
  }
  setEnabled(enabled) {
    if (!this.HWND)
      return false;
    return native.setWindowEnabled(this.HWND, enabled);
  }
  isEnabled() {
    if (!this.HWND)
      return false;
    return native.isEnabled(this.HWND);
  }
  setJitter() {
    if (!this.HWND)
      return false;
    return native.windowJitter(this.HWND);
  }
  isTop() {
    if (!this.HWND)
      return false;
    return native.hasWindowTop(this.HWND);
  }
  setTopOrCancel() {
    if (!this.HWND)
      return false;
    return native.setWindowTop(this.HWND);
  }
  setOpacity(opacity) {
    if (typeof opacity !== "number" || opacity > 100 || isNaN(opacity))
      throw new Error(
        "fun <setOpacity> arg:<Opacity> is only allowed from 0.0 to 1.0 or  0 to 255"
      );
    if (opacity < 1) {
      return this.setTransparent(Math.trunc(255 * opacity));
    }
    opacity = 255 / 100 * opacity;
    if (!isNaN(opacity)) {
      return this.setTransparent(Math.trunc(255 * opacity));
    }
    return false;
  }
  setTransparent(opacity) {
    if (opacity > -1 || opacity < 255) {
      throw new Error(
        "fun <setTransparent> arg:<Opacity> is only allowed from -1 to 255"
      );
    }
    if (!this.HWND)
      return false;
    return native.setHandleTransparent(this.HWND, opacity);
  }
};
var HMC;
((HMC2) => {
  ;
})(HMC || (HMC = {}));
var ref = {
  path(Str) {
    return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, "\0");
  },
  bool(bool) {
    return bool ? true : false;
  },
  string(Str) {
    return String(Str || "");
  },
  int(Num) {
    if (!Num)
      return 0;
    if (typeof Num == "object" && Num instanceof Number) {
      Num = Num == null ? void 0 : Num.valueOf();
    }
    Num = Math.trunc(Num + 0);
    if (typeof Num == "number" && !isNaN(Num))
      return Num;
    if (Num && typeof Num == "boolean")
      Num = 1;
    if (!Num && typeof Num == "boolean")
      Num = 0;
    if (Num >= Infinity) {
      Num = 999999999999999;
    }
    if (Num <= -Infinity) {
      Num = -999999999999999;
    }
    return Num;
  },
  stringArray(array) {
    let dataList = [];
    if (Array.isArray(array)) {
      for (let index = 0; index < array.length; index++) {
        const cout = array[index];
        dataList.push(this.string(cout));
      }
    }
    if (array instanceof Set) {
      for (const cout of array) {
        dataList.push(this.string(cout));
      }
    }
    return dataList;
  },
  intArray(array) {
    let dataList = [];
    if (Array.isArray(array)) {
      for (let index = 0; index < array.length; index++) {
        const cout = array[index];
        dataList.push(this.int(cout));
      }
    }
    if (array instanceof Set) {
      for (const cout of array) {
        dataList.push(this.int(cout));
      }
    }
    return dataList;
  },
  formatCmd(cmd) {
    return argvSplit(this.string(cmd));
  },
  formatArgv(...argv) {
    let argvs = [];
    let argvsResult = [];
    for (let index = 0; index < argv.length; index++) {
      const cout = argv[index];
      if (Array.isArray(cout)) {
        for (let cout_index = 0; cout_index < cout.length; cout_index++) {
          const cout2 = cout[cout_index];
          argvs.push(this.string(cout2));
        }
        continue;
      }
      argvs.push(this.string(cout));
    }
    for (let index = 0; index < argvs.length; index++) {
      let cout = argvs[index];
      if (!cout)
        continue;
      if (cout.match(/['"]/)) {
        cout = cout.replace(/(\\)?["']/g, "\\$0");
      }
      if (cout.match(" ")) {
        cout = `"${cout}"`;
      }
      if (cout.match(/[\n\r]/)) {
        cout = cout.replace(/(\n|\r|\r\n)/g, "$0^");
      }
      argvsResult.push(cout);
    }
    return argvsResult.join(" ");
  },
  HKEY: Hkey,
  concatBuff(buffList) {
    let buffSize = 0;
    for (let index = 0; index < buffList.length; index++) {
      const buff = buffList[index];
      buffSize = buffSize + buff.byteLength;
    }
    let ResponseData = Buffer.concat([...buffList], buffSize);
    return ResponseData;
  }
};
function getDefaultTitele() {
  try {
    return globalThis.document.title;
  } catch (error) {
    return native.lookHandleGetTitle(native.getProcessHandle(process.pid) || 0) || native.getProcessName(process.pid) || process.title;
  }
}
function analysisDirectPath(Path, atkey) {
  let directPath = [];
  directPath.push(...Path.split(new RegExp(Object.keys(Hkey).join("|"))));
  if (directPath.length < 2) {
    return [];
  }
  directPath[1] = directPath[1].replace(/[\\\/]+/g, "\\");
  if (atkey) {
    let paths = directPath[1].split(/[\\]/g);
    if (paths.length) {
      let popData = paths.pop();
      popData && directPath.push(popData);
      directPath.unshift(...paths);
    }
  }
  return directPath;
}
function systemChcp() {
  let result = { code: 437, chcp: chcpList[437] };
  return new Promise((resolve) => {
    child_process.execFile("chcp", function(err, data) {
      if (!data || err)
        return resolve(result);
      let sy_Chcp = data.match(/^.+?(\d+)[\r\n]+$/);
      if (sy_Chcp && chcpList[Number(sy_Chcp[1])]) {
        result.chcp = chcpList[Number(sy_Chcp[1])];
        result.code = Number(sy_Chcp[1]);
        resolve(result);
      }
      resolve(result);
    });
  });
}
function setWindowMode(HWND2, x, y, width, height) {
  if (!ref.int(HWND2))
    return false;
  if (x && typeof x == "object") {
    let SetWindowRect = x;
    SetWindowRect.y = SetWindowRect.top ? SetWindowRect.top : SetWindowRect.y || 0;
    SetWindowRect.x = SetWindowRect.right ? SetWindowRect.right : SetWindowRect.x || 0;
    if (SetWindowRect.x)
      x = SetWindowRect.x;
    if (SetWindowRect.y)
      y = SetWindowRect.y;
    if (SetWindowRect.width)
      width = SetWindowRect.width;
    if (SetWindowRect.height)
      height = SetWindowRect.height;
  }
  if (!x)
    x = 0;
  if (!y)
    x = 0;
  if (!width)
    width = 0;
  if (!height)
    height = 0;
  return native.setWindowMode(
    ref.int(HWND2),
    ref.int(x),
    ref.int(y),
    ref.int(width),
    ref.int(height)
  );
}
function has_reg_args(HKEY, Path, funName) {
  let hasHKEY = new RegExp(`^${Object.keys(Hkey).join("|")}$`).exec(HKEY);
  if (hasHKEY || !Path) {
    throw new Error(`
        <fun> ${funName}  
        argument size 2 or 3
        HKEY : ${Object.keys(Hkey)}
        Path : string
        key ?: string  or "" or undefined
        `);
  }
}
function hasRegistrKey(HKEY, Path, key) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "hasRegistrKey");
  return native.hasRegistrKey(
    HKEY,
    ref.string(Path).split(/[\\\/]+/g).join("\\"),
    ref.string(key)
  );
}
function setRegistrQword(HKEY, Path, key, Qword) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "hasRegistrKey");
  if (!Qword)
    Qword = BigInt(0);
  return native.setRegistrQword(HKEY, ref.string(Path), ref.string(key), BigInt(Qword));
}
function setRegistrDword(HKEY, Path, key, Dword) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "hasRegistrKey");
  return native.setRegistrDword(HKEY, ref.string(Path), ref.string(key), ref.int(Dword));
}
function getRegistrQword(HKEY, Path, key) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "getRegistrQword");
  return native.getRegistrQword(
    HKEY,
    ref.string(Path).split(/[\\\/]+/g).join("\\"),
    ref.string(key)
  );
}
function getRegistrDword(HKEY, Path, key) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "getRegistrDword");
  return native.getRegistrDword(
    HKEY,
    ref.string(Path).split(/[\\\/]+/g).join("\\"),
    ref.string(key)
  );
}
function getRegistrBuffValue(HKEY, Path, key) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "getRegistrBuffValue");
  return native.getRegistrBuffValue(
    HKEY,
    ref.string(Path).split(/[\\\/]+/g).join("\\"),
    ref.string(key)
  );
}
function enumRegistrKey(HKEY, Path) {
  has_reg_args(HKEY, Path, "createPathRegistr");
  let enumKeyList = /* @__PURE__ */ new Set();
  let NatenumKey = native.enumRegistrKey(
    HKEY,
    ref.string(Path).split(/[\\\/]+/g).join("\\")
  );
  for (let index = 0; index < NatenumKey.length; index++) {
    const key = NatenumKey[index];
    enumKeyList.add(key);
  }
  return [...enumKeyList];
}
function listRegistrPath(HKEY, Path) {
  let enumRegistrKeys = enumRegistrKey(HKEY, Path);
  enumRegistrKeys.unshift("");
  let data = {
    "": ""
  };
  for (let i = 0; i < enumRegistrKeys.length; i++) {
    data[enumRegistrKeys[i]] = getStringRegKey(
      HKEY,
      Path,
      enumRegistrKeys[i]
    );
  }
  return data;
}
function isRegistrTreeKey(HKEY, Path, key) {
  return !!enumRegistrKey(HKEY, Path + (!key ? "" : "\\" + key)).length;
}
function getStringRegKey(HKEY, Path, key) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "getStringRegKey");
  return native.getStringRegKey(
    HKEY,
    ref.string(Path).split(/[\\\/]+/g).join("\\"),
    ref.string(key)
  );
}
function openRegKey(HKEY, Path, key) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "openRegKey");
  return {
    get path() {
      return HKEY.concat("\\", Path, "\\", key || "");
    },
    set(data) {
      return native.setRegistrKey(HKEY, Path, key || "", data);
    },
    get() {
      return native.getStringRegKey(HKEY, Path, key || "");
    },
    getBuff() {
      return native.getRegistrBuffValue(HKEY, Path, key || "") || Buffer.alloc(0);
    },
    getNumber() {
      return Number(native.getStringRegKey(HKEY, Path, key || ""));
    },
    keys() {
      return enumRegistrKey(HKEY, Path);
    },
    list() {
      return listRegistrPath(HKEY, Path);
    }
  };
}
function getNumberRegKey(HKEY, Path, key) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "getNumberRegKey");
  return ref.int(
    native.getStringRegKey(
      HKEY,
      ref.string(Path).split(/[\\\/]+/g).join("\\"),
      ref.string(key)
    )
  );
}
function removeStringRegKey(HKEY, Path, key) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "removeStringRegKey");
  return native.removeStringRegKey(
    HKEY,
    ref.string(Path).split(/[\\\/]+/g).join("\\"),
    ref.string(key)
  );
}
function removeStringRegKeyWalk(HKEY, Path, key) {
  if (!key) {
    let paths = ref.string(Path).split(/[\\\/]/g);
    key = paths.pop();
    if (!key)
      throw new Error("Invalid key because it is empty");
    Path = paths.join("\\");
  }
  has_reg_args(HKEY, Path, "removeStringRegKeyWalk");
  return native.removeStringRegKeyWalk(
    HKEY,
    ref.string(Path).split(/[\\\/]+/g).join("\\"),
    ref.string(key)
  );
}
function removeStringTree(HKEY, Path, key) {
  return removeStringRegKeyWalk(HKEY, Path, key);
}
function removeStringRegValue(HKEY, Path, key) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "removeStringRegValue");
  return native.removeStringRegValue(
    HKEY,
    ref.string(Path).split(/[\\\/]/g).join("\\"),
    ref.string(key)
  );
}
function setRegistrKey(HKEY, Path, key, Value) {
  if (!key)
    key = "";
  has_reg_args(HKEY, Path, "setRegistrKey");
  return native.setRegistrKey(
    HKEY,
    ref.string(Path).split(/[\\\/]/g).join("\\"),
    ref.string(key),
    ref.string(Value)
  );
}
function createPathRegistr(HKEY, Path) {
  has_reg_args(HKEY, Path, "createPathRegistr");
  return native.createPathRegistr(
    HKEY,
    ref.string(Path).split(/[\\\/]/g).join("\\")
  );
}
function system(str) {
  return native.system(ref.string(str));
}
function freePort() {
  return new Promise((resolve, reject) => {
    let sock = net.createServer(function() {
    });
    sock.listen(0, () => {
      var _a;
      resolve(Number((_a = sock == null ? void 0 : sock.address()) == null ? void 0 : _a.port));
      sock.close();
    });
  });
}
function getClipboardFilePaths(at) {
  let paths = native.getClipboardFilePaths();
  if (typeof at === "number") {
    if (at < 0) {
      return paths[paths.length + at];
    }
    return paths[at];
  }
  return paths;
}
function setClipboardFilePaths(...FilePaths) {
  let filePaths = [];
  for (let index = 0; index < FilePaths.length; index++) {
    const FilePath = FilePaths[index];
    if (typeof FilePath !== "string") {
      for (let indexc = 0; indexc < FilePaths.length; indexc++) {
        filePaths.push(ref.string(FilePaths[indexc]));
      }
    } else {
      filePaths.push(ref.string(FilePath));
    }
  }
  return native.setClipboardFilePaths(filePaths);
}
function getUsbDevsInfo() {
  return native.getUsbDevsInfo();
}
function enumChildWindows(Handle) {
  return native.enumChildWindows(ref.int(Handle));
}
function hideConsole() {
  if (!$_thenConsole) {
    $_thenConsole = getProcessHandle(process.pid);
  }
  if (!$_thenConsole)
    return false;
  return ($_thenConsole == null ? void 0 : $_thenConsole.hide()) || false;
}
function showConsole() {
  if (!$_thenConsole) {
    $_thenConsole = getProcessHandle(process.pid);
  }
  if (!$_thenConsole)
    return false;
  return ($_thenConsole == null ? void 0 : $_thenConsole.show()) || false;
}
function getConsoleHandle() {
  if (!$_thenConsole) {
    $_thenConsole = getProcessHandle(process.pid);
  }
  return $_thenConsole;
}
function deleteFile(Path, Recycle, isShow) {
  return native.deleteFile(
    ref.path(Path),
    typeof Recycle == "boolean" ? ref.bool(Recycle) : true,
    typeof isShow == "boolean" ? ref.bool(isShow) : false
  );
}
var trash = deleteFile;
function getClipboardSequenceNumber() {
  return native.getClipboardSequenceNumber();
}
function watchClipboard(CallBack, nextAwaitMs) {
  let NextAwaitMs = nextAwaitMs || 150;
  let Next = true;
  let oidClipboardSequenceNumber = getClipboardSequenceNumber();
  (async function() {
    while (Next) {
      await Sleep(NextAwaitMs);
      let clipboardSequenceNumber = getClipboardSequenceNumber();
      if (oidClipboardSequenceNumber !== clipboardSequenceNumber) {
        if (CallBack)
          CallBack();
      }
      oidClipboardSequenceNumber = clipboardSequenceNumber;
    }
  })();
  return {
    unwatcher() {
      Next = false;
    },
    setNextAwaitMs(nextAwaitMs2) {
      NextAwaitMs = ref.int(nextAwaitMs2) || 150;
    }
  };
}
function watchUSB(CallBack, nextAwaitMs, watchType) {
  let NextAwaitMs = nextAwaitMs || 800;
  let Next = true;
  let OID_ID_LIST = /* @__PURE__ */ new Set();
  let start = true;
  if (typeof watchType == "string")
    watchType = [watchType];
  (async function() {
    while (Next) {
      await Sleep(NextAwaitMs);
      let GET_ID_List = new Set(watchType ? [
        ...watchType.includes("hub") ? native.getHidUsbIdList() : [],
        ...watchType.includes("drive") ? native.getUsbDevsInfo() : []
      ] : [...native.getHidUsbIdList(), ...native.getUsbDevsInfo()]);
      if (start) {
        for (const NEW_ID of GET_ID_List) {
          OID_ID_LIST.add(NEW_ID);
          CallBack && CallBack("start", NEW_ID);
        }
        start = false;
      }
      let GET_ID_List_NEW = [...GET_ID_List];
      for (const OID_ID of OID_ID_LIST) {
        if (!GET_ID_List.has(OID_ID)) {
          CallBack && CallBack("remove", OID_ID);
        }
      }
      for (const NEW_ID of GET_ID_List) {
        if (!OID_ID_LIST.has(NEW_ID)) {
          CallBack && CallBack("add", NEW_ID);
        }
      }
      OID_ID_LIST.clear();
      for (let index = 0; index < GET_ID_List_NEW.length; index++) {
        const GET_ID = GET_ID_List_NEW[index];
        OID_ID_LIST.add(GET_ID);
      }
    }
  })();
  return {
    get idList() {
      return OID_ID_LIST;
    },
    unwatcher() {
      Next = false;
    },
    setNextAwaitMs(nextAwaitMs2) {
      NextAwaitMs = ref.int(nextAwaitMs2) || 800;
    }
  };
}
function getDeviceCapsAll() {
  return native.getDeviceCapsAll();
}
function isInMonitorWindow(Handle) {
  return native.isInMonitorWindow(ref.int(Handle));
}
function isMouseMonitorWindow(Handle) {
  return native.isMouseMonitorWindow(ref.int(Handle));
}
function getCurrentMonitorRect() {
  return native.getCurrentMonitorRect();
}
function getSystemMetricsLen() {
  return native.getSystemMetricsLen();
}
function alert(Message, Title) {
  return native.alert(
    Message,
    typeof Title != "string" ? getDefaultTitele() : Title
  );
}
function confirm(Message, Title) {
  return native.confirm(
    Message,
    typeof Title != "string" ? getDefaultTitele() : Title
  );
}
function MessageStop(Message, Title) {
  return native.MessageStop(
    Message,
    typeof Title != "string" ? getDefaultTitele() : Title
  );
}
function MessageError(Message, Title) {
  return native.MessageError(
    Message,
    typeof Title != "string" ? getDefaultTitele() : Title
  );
}
function getAllWindowsHandle() {
  let data = [];
  let AllWindowsHandle = native.getAllWindowsHandle();
  for (let index = 0; index < AllWindowsHandle.length; index++) {
    const element = AllWindowsHandle[index];
    data.push(new HWND(element));
  }
  return data;
}
function processWatchdog(ProcessID, callback, awaitMs) {
  let quit = false;
  if (!callback) {
    let Prom = new Promise(
      async (resolve, reject) => {
        while (true) {
          if (quit)
            break;
          await Sleep(awaitMs || 500);
          if (!hasProcess(ref.int(ProcessID))) {
            resolve(void 0);
            break;
          }
        }
      }
    );
    Prom.quit = function() {
      quit = true;
    };
    return Prom;
  }
  (async () => {
    while (true) {
      await Sleep(awaitMs || 500);
      if (!hasProcess(ref.int(ProcessID))) {
        typeof callback == "function" && callback();
        break;
      }
    }
  })();
  return {
    quit: function() {
      quit = true;
    }
  };
}
function WatchWindowPoint(callback, awaitMs) {
  let quit = false;
  let oidPoint = native.getPointWindow() || 0;
  (async () => {
    if (typeof callback !== "function")
      return;
    while (true) {
      if (quit)
        return;
      let newPoint = native.getPointWindow() || 0;
      if (newPoint) {
        if (newPoint != oidPoint) {
          if (callback) {
            callback(
              ref.int(newPoint),
              ref.int(oidPoint) || 0,
              new HWND(ref.int(newPoint))
            );
            oidPoint = newPoint;
          }
        }
      }
      await Sleep(awaitMs || 350);
    }
  })();
  return {
    quit: function() {
      quit = true;
    },
    setAwaitMs(ms) {
      awaitMs = ms;
    }
  };
}
function WatchWindowForeground(callback, awaitMs) {
  let quit = false;
  let oidForeg = getForegroundWindow();
  (async () => {
    if (typeof callback !== "function")
      return;
    while (true) {
      if (quit)
        return;
      let newForeg = getForegroundWindow();
      if (newForeg) {
        if (ref.int(newForeg) != ref.int(oidForeg)) {
          if (callback) {
            callback(
              ref.int(newForeg),
              ref.int(oidForeg) || 0,
              new HWND(ref.int(newForeg))
            );
            oidForeg = newForeg;
          }
        }
      }
      await Sleep(awaitMs || 350);
    }
  })();
  return {
    quit: function() {
      quit = true;
    },
    setAwaitMs(ms) {
      awaitMs = ms;
    }
  };
}
function openApp(AppPath, Command, cwd, hide, UAC) {
  return native.openApp(
    ref.string(AppPath),
    ref.string(
      Array.isArray(Command) ? ref.formatArgv(Command) : Command
    ) || "",
    ref.string(cwd || path.parse(AppPath || "").dir || process.cwd()),
    ref.bool(hide || false),
    ref.bool(UAC || false)
  );
}
function getProcessNameList(...Name) {
  let resultList = [];
  let ProcessList = native.getProcessList();
  for (let index = 0; index < ProcessList.length; index++) {
    const Process2 = ProcessList[index];
    const { pid, name } = Process2;
    for (let NextNameIndex = 0; NextNameIndex < Name.length; NextNameIndex++) {
      const NextName = Name[NextNameIndex];
      if (typeof NextName === "string") {
        if (Process2.name == NextName) {
          resultList.push({ pid, name });
        }
      }
      if (NextName instanceof RegExp && NextName.test(name)) {
        resultList.push({ pid, name });
      }
    }
  }
  return resultList;
}
function getDetailsProcessNameList(...Name) {
  let resultList = [];
  let ProcessList = native.getDetailsProcessList();
  for (let index = 0; index < ProcessList.length; index++) {
    const Process2 = ProcessList[index];
    const { pid, name, path: path2 } = Process2;
    for (let NextNameIndex = 0; NextNameIndex < Name.length; NextNameIndex++) {
      const NextName = Name[NextNameIndex];
      if (typeof NextName === "string") {
        if (Process2.name == NextName) {
          resultList.push({ pid, name, path: path2 });
        }
      }
      if (NextName instanceof RegExp && NextName.test(name)) {
        resultList.push({ pid, name, path: path2 });
      }
    }
  }
  return resultList;
}
function killProcessName(...Name) {
  let resultList = [];
  let ProcessList = getProcessList();
  for (let index = 0; index < ProcessList.length; index++) {
    const Process2 = ProcessList[index];
    const { pid, name } = Process2;
    for (let NextNameIndex = 0; NextNameIndex < Name.length; NextNameIndex++) {
      const NextName = Name[NextNameIndex];
      if (typeof NextName === "string") {
        if (Process2.name == NextName) {
          killProcess(Process2.pid);
          resultList.push({
            pid,
            name,
            get kill() {
              return hasProcess(pid);
            }
          });
        }
      }
      if (NextName instanceof RegExp && NextName.test(name)) {
        killProcess(Process2.pid);
        resultList.push({
          pid,
          name,
          get kill() {
            return hasProcess(pid);
          }
        });
      }
    }
  }
  return resultList;
}
function getForegroundWindow() {
  let Handle = native.getForegroundWindow();
  return Handle ? new HWND(Handle) : null;
}
function getMainWindow(Handle) {
  let Handles = native.getMainWindow(ref.int(Handle));
  return Handles ? new HWND(Handles) : null;
}
function getPointWindow() {
  let Handle = native.getPointWindow();
  return Handle ? new HWND(Handle) : null;
}
function getPointWindowMain() {
  let Handle = native.getPointWindowMain();
  return Handle ? new HWND(Handle) : null;
}
function getProcessHandle(ProcessID) {
  let Handles = native.getProcessHandle(ref.int(ProcessID));
  return Handles ? new HWND(Handles) : null;
}
function SetBlockInput(Block) {
  return native.SetBlockInput(ref.bool(Block));
}
function SetWindowInTaskbarVisible(Handle, Visible) {
  return native.SetWindowInTaskbarVisible(
    ref.int(Handle),
    ref.bool(Visible)
  );
}
function getHandleProcessID(Handle) {
  return native.getHandleProcessID(ref.int(Handle));
}
function getWindowRect(Handle) {
  return native.getWindowRect(ref.int(Handle));
}
function isEnabled(Handle) {
  return native.isEnabled(ref.int(Handle));
}
function isHandle(Handle) {
  return native.isHandle(ref.int(Handle));
}
function isHandleWindowVisible(Handle) {
  return native.isHandleWindowVisible(ref.int(Handle));
}
function lookHandleCloseWindow(Handle) {
  return native.lookHandleCloseWindow(ref.int(Handle));
}
function lookHandleGetTitle(Handle) {
  return native.lookHandleGetTitle(ref.int(Handle));
}
function lookHandleSetTitle(Handle, title) {
  return native.lookHandleSetTitle(
    ref.int(Handle),
    ref.string(title)
  );
}
var setShowWindow = lookHandleShowWindow;
var setCloseWindow = lookHandleCloseWindow;
var getWindowTitle = lookHandleGetTitle;
var setWindowTitle = lookHandleSetTitle;
function lookHandleShowWindow(Handle, SetShowType) {
  return native.lookHandleShowWindow(
    ref.int(Handle),
    ref.int(
      typeof SetShowType == "number" ? ref.int(SetShowType) : 5
    )
  );
}
function setHandleTransparent(Handle, Transparent) {
  return native.setHandleTransparent(
    ref.int(Handle),
    ref.int(Transparent || 255)
  );
}
function setWindowEnabled(Handle, Enabled) {
  return native.setWindowEnabled(
    ref.int(Handle),
    ref.bool(Enabled)
  );
}
function setWindowFocus(Handle) {
  return native.setWindowFocus(ref.int(Handle));
}
function setWindowTop(Handle) {
  return native.setWindowTop(ref.int(Handle));
}
function updateWindow(Handle) {
  return native.updateWindow(ref.int(Handle));
}
function windowJitter(Handle) {
  return native.windowJitter(ref.int(Handle));
}
function hasWindowTop(Handle) {
  return native.hasWindowTop(ref.int(Handle));
}
function closedHandle(Handle) {
  return native.closedHandle(ref.int(Handle));
}
function getHidUsbList() {
  return native.getHidUsbList();
}
function getMetrics() {
  return native.getMetrics();
}
function getMouseMovePoints() {
  return native.getMouseMovePoints();
}
function getDeviceCaps() {
  return native.getDeviceCaps();
}
function SetSystemHOOK(HOOK) {
  return native.SetSystemHOOK(ref.bool(HOOK));
}
function getBasicKeys() {
  return native.getBasicKeys();
}
function getClipboardText() {
  return native.getClipboardText();
}
function setClipboardText(text) {
  return native.setClipboardText(ref.string(text));
}
function clearClipboard() {
  return native.clearClipboard();
}
function getDetailsProcessList() {
  return native.getDetailsProcessList();
}
function getProcessList() {
  return native.getProcessList();
}
function getForegroundWindowProcessID() {
  return native.getForegroundWindowProcessID();
}
function getPointWindowName() {
  return native.getPointWindowName();
}
function getPointWindowProcessId() {
  return native.getPointWindowProcessId();
}
function getProcessName(ProcessID) {
  return native.getProcessName(ref.int(ProcessID));
}
function getProcessidFilePath(ProcessID) {
  return native.getProcessidFilePath(ref.int(ProcessID));
}
function getShortcutLink(LnkPath) {
  return native.getShortcutLink(ref.string(LnkPath));
}
function getSystemIdleTime() {
  return native.getSystemIdleTime();
}
function getSystemMenu(Handle, boolean) {
  return native.getSystemMenu(ref.int(Handle), ref.bool(boolean));
}
function getTrayList() {
  return native.getTrayList();
}
function hasKeyActivate(KeysEvent) {
  return native.hasKeyActivate(ref.int(KeysEvent));
}
function hasProcess(ProcessID) {
  return native.isProcess(ref.int(ProcessID));
}
function isAdmin() {
  return native.isAdmin();
}
function isProcess(ProcessID) {
  return native.isProcess(ref.int(ProcessID));
}
function isSystemX64() {
  return native.isSystemX64();
}
function killProcess(ProcessID) {
  if (typeof ProcessID == "string" || typeof ProcessID == "object") {
    return killProcessName(ProcessID);
  }
  return native.killProcess(ref.int(ProcessID));
}
function leftClick(ms) {
  return native.leftClick(ms);
}
function messageBox(message, title, MB_UINT) {
  return native.messageBox(ref.string(message), ref.string(title), ref.string(MB_UINT));
}
function mouse(mouse_event, ms) {
  if (typeof mouse_event == "number") {
    mouse_event = ref.int(mouse_event);
  } else {
    mouse_event = ref.string(mouse_event);
  }
  return native.mouse.apply(void 0, ms ? [mouse_event] : [mouse_event, ms]);
}
function openExternal(Path) {
  return native.openExternal(Path);
}
function openPath(Path) {
  return native.openPath(Path);
}
function openURL(URL) {
  return native.openURL(ref.string(URL));
}
var powerControl = (() => {
  function _PowerControl(Set2) {
    native.powerControl(Set2);
  }
  _PowerControl[1001] = () => {
    native.powerControl(1001);
  };
  _PowerControl[1002] = () => {
    native.powerControl(1002);
  };
  _PowerControl[1003] = () => {
    native.powerControl(1003);
  };
  _PowerControl[1005] = () => {
    native.powerControl(1005);
  };
  _PowerControl.shutDown = () => {
    native.powerControl(1001);
  };
  _PowerControl.restart = () => {
    native.powerControl(1002);
  };
  _PowerControl.cancellation = () => {
    native.powerControl(1003);
  };
  _PowerControl.lock = () => {
    native.powerControl(1005);
  };
  return _PowerControl;
})();
function rightClick(ms) {
  return native.rightClick(ms);
}
function setCursorPos(x, y) {
  return native.setCursorPos(ref.int(x), ref.int(y));
}
function setShortcutLink(...args) {
  if (args.length < 2)
    throw new Error("not LnkPath and FilePath arguments");
  args[0] = ref.string(args[0] || "");
  args[1] = ref.string(args[1] || "");
  args[2] = ref.string(args[2] || "");
  args[3] = ref.string(args[3] || "");
  if (Array.isArray(args[4])) {
    args[4] = ref.formatArgv(args[4]);
  }
  args[4] = ref.string(args[4] || "");
  if (args.length > 5) {
    args[5] = ref.int(args[5] || 0);
  }
  if (args.length > 6) {
    args[6] = ref.string(args[6] || "");
  }
  if (args.length > 7) {
    args[7] = ref.int(args[7] || 0);
  }
  return native.setShortcutLink(...args);
}
function createSymlink(LinkPath, sourcePath) {
  return native.createSymlink(ref.string(LinkPath), ref.string(sourcePath));
}
function createDirSymlink(LinkPath, sourcePath) {
  return native.createSymlink(ref.string(LinkPath), ref.string(sourcePath));
}
function createHardLink(LinkPath, sourcePath) {
  return native.createSymlink(ref.string(LinkPath), ref.string(sourcePath));
}
function showMonitors(show) {
  if (typeof show == "boolean") {
    return show ? native.showMonitors() : native.shutMonitors();
  }
  return native.showMonitors();
}
function shutMonitors(show) {
  if (typeof show == "boolean") {
    return show ? native.showMonitors() : native.shutMonitors();
  }
  return native.shutMonitors();
}
function sleep(awaitTime) {
  return native.sleep(ref.int(awaitTime));
}
async function Sleep(awaitTime, Sync) {
  if (Sync) {
    return sleep(ref.int(awaitTime));
  }
  return new Promise(
    (resolve) => setTimeout(resolve, ref.int(awaitTime))
  );
}
function systemStartTime() {
  return native.systemStartTime();
}
function getAllWindows() {
  class WINDOWS_INFO {
    constructor(handle) {
      this.handle = handle;
    }
    get rect() {
      if (!this._rect)
        this._rect = native.getWindowRect(this.handle);
      return this._rect;
    }
    get className() {
      if (typeof this._className == "undefined")
        this._className = native.getWindowClassName(this.handle);
      return this._className;
    }
    get style() {
      if (typeof this._style == "undefined")
        this._style = native.getWindowStyle(this.handle);
      return this._style;
    }
    get title() {
      if (typeof this._title == "undefined")
        this._title = native.lookHandleGetTitle(this.handle);
      return this._title;
    }
  }
  let AllWindowsHandle = native.getAllWindowsHandle();
  let AllWindows = [];
  for (let index = 0; index < AllWindowsHandle.length; index++) {
    const handle = AllWindowsHandle[index];
    AllWindows.push(new WINDOWS_INFO(handle));
  }
  return AllWindows;
}
function getWindowClassName(Handle) {
  return native.getWindowClassName(ref.int(Handle));
}
function getWindowStyle(Handle) {
  return native.getWindowStyle(ref.int(Handle));
}
function GetWebView2Info(Has) {
  const INFO = {
    version: "",
    name: "",
    location: ""
  };
  const { HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER } = Hkey;
  let WebView2IDKEY = "{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5}";
  let Path_64bit_LOCAL = [HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\EdgeUpdate\\Clients"];
  let Path_64bit_USER = [HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\EdgeUpdate\\Clients"];
  let Path_32bit_LOCAL = [HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\EdgeUpdate\\Clients"];
  let Path_32bit_USER = [HKEY_CURRENT_USER, "Software\\Microsoft\\EdgeUpdate\\Clients"];
  let ForEachKey = [Path_64bit_LOCAL, Path_64bit_USER, Path_32bit_LOCAL, Path_32bit_USER];
  for (let index = 0; index < ForEachKey.length; index++) {
    const KEY_PATH = ForEachKey[index];
    if (registr.hasRegistrKey(...KEY_PATH, WebView2IDKEY)) {
      if (Has)
        return true;
    }
    const [Hkey2, Path] = KEY_PATH;
    INFO.location = registr.getStringRegKey(Hkey2, Path.concat("\\", WebView2IDKEY), "location");
    INFO.name = registr.getStringRegKey(Hkey2, Path.concat("\\", WebView2IDKEY), "name");
    INFO.version = registr.getStringRegKey(Hkey2, Path.concat("\\", WebView2IDKEY), "pv");
    break;
  }
  return INFO;
}
function getWebView2Info() {
  return GetWebView2Info();
}
async function WebView2OnlineInstall() {
  const webView2URL = "https://go.microsoft.com/fwlink/p/?LinkId=2124703";
  const webView2Path = path.join("MicrosoftEdgeWebview2Setup.exe");
  const webView2InstallCommand = ["/silent", "/install"];
  return new Promise((resolve, reject) => {
    const buffList = [];
    https.get(webView2URL, (res) => {
      if (res.statusCode !== 200) {
        reject(new Error(`Install  WebView2 failure statusCode: ${res.statusCode || 404}`));
        return;
      }
      res.on("data", (data) => {
        buffList.push(data);
      });
      res.once("error", (err) => {
        reject(err);
      });
      res.on("end", () => {
        const buff = ref.concatBuff(buffList);
        buffList.length = 0;
        fs.promises.writeFile(webView2Path, buff).then(() => {
          const spawn = child_process.spawn(webView2Path, webView2InstallCommand, { "windowsHide": true });
          spawn.on("error", function() {
            reject(new Error(`Install  WebView2 failure Installation process creation failed`));
            spawn.kill();
          });
          spawn.once("exit", function() {
            resolve(void 0);
          });
        }).catch((err) => {
          reject(new Error(`Install  WebView2 failure Update file cannot be written`));
        });
      });
    });
  });
}
function hasWebView2() {
  return GetWebView2Info(true);
}
var version = native.version;
var desc = native.desc;
var platform = native.platform;
var Window = {
  isInMonitor: isInMonitorWindow,
  isMouseMonitor: isMouseMonitorWindow,
  HWND,
  setMode: setWindowMode,
  getAllWindows,
  getAllHandle: getAllWindowsHandle,
  watchPoint: WatchWindowPoint,
  watchtFocus: WatchWindowForeground,
  getFocus: getForegroundWindow,
  getMain: getMainWindow,
  getPoint: getPointWindow,
  getProcessHandle,
  getPointMain: getPointWindowMain,
  setTaskbarVisible: SetWindowInTaskbarVisible,
  getProcessID: getHandleProcessID,
  getRect: getWindowRect,
  isEnabled,
  isHandle,
  hasHandle: isHandle,
  isVisible: isHandleWindowVisible,
  close: lookHandleCloseWindow,
  getTitle: lookHandleGetTitle,
  setTitle: lookHandleSetTitle,
  setShowWindow: lookHandleShowWindow,
  setTransparent: setHandleTransparent,
  setEnabled: setWindowEnabled,
  setFocus: setWindowFocus,
  setTop: setWindowTop,
  update: updateWindow,
  jitter: windowJitter,
  hasTop: hasWindowTop,
  closed: closedHandle,
  getFocusProcessID: getForegroundWindowProcessID,
  getPointName: getPointWindowName,
  getPointProcessId: getPointWindowProcessId,
  enumChild: enumChildWindows,
  console: {
    hide: hideConsole,
    show: showConsole,
    get: getConsoleHandle,
    blockInput: SetBlockInput
  },
  getStyle: getWindowStyle,
  getClassName: getWindowClassName
};
var Watch = {
  clipboard: watchClipboard,
  usb: watchUSB,
  windowFocus: WatchWindowForeground,
  windowPoint: WatchWindowPoint,
  process: processWatchdog
};
var Clipboard = {
  clear: clearClipboard,
  readText: getClipboardText,
  readFilePaths: getClipboardFilePaths,
  writeText: setClipboardText,
  writeFilePaths: setClipboardFilePaths,
  sequence: getClipboardSequenceNumber,
  watch: watchClipboard
};
var MousePoint = class {
  constructor(str) {
    const data = str.split("|");
    this.x = Number(data[0]);
    this.y = Number(data[1]);
    this.isDown = Number(data[2]) ? true : false;
  }
  get isLeft() {
    return Auto.hasKeyActivate(1);
  }
  get isRight() {
    return Auto.hasKeyActivate(2);
  }
  get isMiddle() {
    return Auto.hasKeyActivate(4);
  }
  async click(awitMs) {
    awitMs = awitMs || 150;
    Auto.setCursorPos(this.x, this.y);
    Auto.mouse("MOUSEEVENTF_LEFTDOWN");
    await Sleep(awitMs);
    return Auto.mouse("MOUSEEVENTF_LEFTUP");
  }
  async middle(awitMs) {
    awitMs = awitMs || 150;
    Auto.setCursorPos(this.x, this.y);
    Auto.mouse(32);
    await Sleep(awitMs);
    return Auto.mouse("MOUSEEVENTF_MIDDLEUP");
  }
  async rClick(awitMs) {
    awitMs = awitMs || 150;
    Auto.setCursorPos(this.x, this.y);
    Auto.mouse("MOUSEEVENTF_RIGHTDOWN");
    await Sleep(awitMs);
    return Auto.mouse("MOUSEEVENTF_RIGHTUP");
  }
  doubleClick(doubleAwitMs, clickAwitMs) {
    doubleAwitMs = doubleAwitMs || 150;
    clickAwitMs = clickAwitMs || 150;
    this.click(clickAwitMs).then(() => {
      Sleep(doubleAwitMs || 150).then(() => {
        this.click(clickAwitMs);
      });
    });
  }
  moveMouse(x, y) {
    Auto.setCursorPos(x, y);
  }
};
var KeyboardVKcodeEmenList = [
  ["0", "Digit0", 48, 48],
  ["1", "Digit1", 49, 49],
  ["2", "Digit2", 50, 50],
  ["3", "Digit3", 51, 51],
  ["4", "Digit4", 52, 52],
  ["5", "Digit5", 53, 53],
  ["6", "Digit6", 54, 54],
  ["7", "Digit7", 55, 55],
  ["8", "Digit8", 56, 56],
  ["9", "Digit9", 57, 57],
  ["A", "KeyA", 65, 65],
  ["B", "KeyB", 66, 66],
  ["C", "KeyC", 67, 67],
  ["D", "KeyD", 68, 68],
  ["E", "KeyE", 69, 69],
  ["F", "KeyF", 70, 70],
  ["G", "KeyG", 71, 71],
  ["H", "KeyH", 72, 72],
  ["I", "KeyI", 73, 73],
  ["J", "KeyJ", 74, 74],
  ["K", "KeyK", 75, 75],
  ["L", "KeyL", 76, 76],
  ["M", "KeyM", 77, 77],
  ["N", "KeyN", 78, 78],
  ["O", "KeyO", 79, 79],
  ["P", "KeyP", 80, 80],
  ["Q", "KeyQ", 81, 81],
  ["R", "KeyR", 82, 82],
  ["S", "KeyS", 83, 83],
  ["T", "KeyT", 84, 84],
  ["U", "KeyU", 85, 85],
  ["V", "KeyV", 86, 86],
  ["W", "KeyW", 87, 87],
  ["X", "KeyX", 88, 88],
  ["Y", "KeyY", 89, 89],
  ["Z", "KeyZ", 90, 90],
  ["0", "Numpad0", 96, 96],
  ["1", "Numpad1", 97, 97],
  ["2", "Numpad2", 98, 98],
  ["3", "Numpad3", 99, 99],
  ["4", "Numpad4", 100, 100],
  ["5", "Numpad5", 101, 101],
  ["6", "Numpad6", 102, 102],
  ["7", "Numpad7", 103, 103],
  ["8", "Numpad8", 104, 104],
  ["9", "Numpad9", 105, 105],
  ["Alt", "Alt", 18, 18],
  ["Alt", "AltLeft", 164, 164],
  ["Alt", "AltRight", 165, 165],
  ["CapsLock", "CapsLock", 20, 20],
  ["Control", "Control", 17, 17, ["ctrl"]],
  ["Control", "ControlLeft", 162, 162, ["ctrl"]],
  ["Control", "ControlRight", 163, 163, ["ctrl"]],
  ["Win", "MetaLeft", 91, 91],
  ["Win", "MetaRight", 92, 92],
  ["NumLock", "NumLock", 144, 144],
  ["ScrollLock", null, 145, 145],
  ["Shift", "Shift", 16, 16],
  ["Shift", "ShiftLeft", 160, 160],
  ["Shift", "ShiftRight", 161, 161],
  ["Enter", "Enter", 13, 13, ["\r\n", "\r", "\n"]],
  ["Tab", "Tab", 9, 9],
  ["Space", "Space", 32, 32],
  ["ArrowDown", null, 40, 40],
  ["ArrowLeft", null, 37, 37],
  ["ArrowRight", null, 39, 39],
  ["ArrowUp", null, 38, 38],
  ["End", "End", 35, 35],
  ["Home", "Home", 36, 36],
  ["PageDown", null, 34, 34],
  ["PageUp", null, 33, 33],
  ["Backspace", null, 8, 8],
  ["Clear", null, 12, 12],
  ["Clear", null, 254, 254],
  ["CrSel", null, 247, 247],
  ["Delete", null, 46, 46],
  ["EraseEof", null, 249, 249],
  ["ExSel", null, 248, 248],
  ["Insert", null, 45, 45],
  ["Accept", null, 30, 30],
  ["ContextMenu", null, 93, 93],
  ["Escape", null, 27, 27, ["esc"]],
  ["Execute", null, 43, 43],
  ["Finish", null, 241, 241],
  ["Help", null, 47, 47],
  ["Pause", null, 19, 19],
  ["Play", null, 250, 250],
  ["Select", null, 41, 41],
  ["PrintScreen", null, 44, 44],
  ["Standby", null, 95, 95],
  ["Alphanumeric", null, 240, 240],
  ["Convert", null, 28, 28],
  ["FinalMode", null, 24, 24],
  ["ModeChange", null, 31, 31],
  ["NonConvert", null, 29, 29],
  ["Process", null, 229, 229],
  ["HangulMode", null, 21, 21],
  ["HanjaMode", null, 25, 25],
  ["JunjaMode", null, 23, 23],
  ["Hankaku", null, 243, 243],
  ["Hiragana", null, 242, 242],
  ["KanaMode", null, 246, 246],
  ["Romaji", null, 245, 245],
  ["Zenkaku", null, 244, 244],
  ["F1", null, 112, 112],
  ["F2", null, 113, 113],
  ["F3", null, 114, 114],
  ["F4", null, 115, 115],
  ["F5", null, 116, 116],
  ["F6", null, 117, 117],
  ["F7", null, 118, 118],
  ["F8", null, 119, 119],
  ["F9", null, 120, 120],
  ["F10", null, 121, 121],
  ["F11", null, 122, 122],
  ["F12", null, 123, 123],
  ["F13", null, 124, 124],
  ["F14", null, 125, 125],
  ["F15", null, 126, 126],
  ["F16", null, 127, 127],
  ["F17", null, 128, 128],
  ["F18", null, 129, 129],
  ["F19", null, 130, 130],
  ["F20", null, 131, 131],
  ["MediaPlayPause", null, 179, 179],
  ["MediaStop", null, 178, 178],
  ["MediaTrackNext", null, 176, 176],
  ["MediaTrackPrevious", null, 177, 177],
  ["AudioVolumeDown", null, 174, 174],
  ["AudioVolumeMute", null, 173, 173],
  ["AudioVolumeUp", null, 175, 175],
  ["ZoomToggle", null, 251, 251],
  ["LaunchMail", null, 180, 180],
  ["LaunchMediaPlayer", null, 181, 181],
  ["LaunchApplication1", null, 182, 182],
  ["LaunchApplication2", null, 183, 183],
  ["BrowserBack", null, 166, 166],
  ["BrowserFavorites", null, 171, 171],
  ["BrowserForward", null, 167, 167],
  ["BrowserHome", null, 172, 172],
  ["BrowserRefresh", null, 168, 168],
  ["BrowserSearch", null, 170, 170],
  ["BrowserStop", null, 169, 169],
  [".", "NumpadDecimal", 110, 110],
  ["*", "NumpadMultiply", 106, 106],
  ["+", "NumpadAdd", 107, 107],
  ["/", "NumpadDivide", 111, 111],
  ["-", "NumpadSubtract", 109, 109],
  ["Separator", null, 108, 108],
  [";", "Semicolon", 186, 186],
  ["+", "Equal", 187, 187],
  [",", "Comma", 188, 188],
  ["-", "Minus", 189, 189],
  [".", "Period", 190, 190],
  ["/", "Slash", 191, 191],
  ["`", "Backquote", 192, 192],
  ["[", "BracketLeft", 219, 219],
  ["\\", "Backslash", 220, 220],
  ["]", "BracketLeft", 221, 221],
  ["'", "Quote", 222, 222]
];
var KeyboardcodeEmenList = (() => {
  let data = /* @__PURE__ */ new Map();
  for (let index = 0; index < KeyboardVKcodeEmenList.length; index++) {
    const [VK_key, VK_code, VK_keyCode, VK_VirtualKey, VK_Nickname] = KeyboardVKcodeEmenList[index];
    data.set(VK_VirtualKey, KeyboardVKcodeEmenList[index]);
  }
  return data;
})();
var Keyboard = class {
  get shiftKey() {
    return Auto.hasKeyActivate(16) || Auto.hasKeyActivate(161) || Auto.hasKeyActivate(160);
  }
  get altKey() {
    return Auto.hasKeyActivate(18) || Auto.hasKeyActivate(164) || Auto.hasKeyActivate(165);
  }
  get ctrlKey() {
    return Auto.hasKeyActivate(17);
  }
  get winKey() {
    return Auto.hasKeyActivate(91) || Auto.hasKeyActivate(92);
  }
  constructor(str) {
    const data = str.split("|");
    this.vKey = Number(data[0]);
    this.__isDown = Number(data[1]) ? true : false;
    const KeyboardcodeEmen = KeyboardcodeEmenList.get(this.vKey);
    if (!KeyboardcodeEmen)
      throw new Error("key Value Data That Does Not Exist !");
    const [VK_key, VK_code, VK_keyCode, VK_VirtualKey, VK_Nickname] = KeyboardcodeEmen;
    this.keyCode = VK_keyCode;
    this.key = VK_key;
    this.code = VK_code || VK_key;
  }
  get isDown() {
    return this.__isDown || hasKeyActivate(this.vKey);
  }
};
var SetIohook = false;
var Iohook_Mouse = class {
  constructor() {
    this._onlistenerCountList = {
      close: [],
      data: [],
      mouse: [],
      start: [],
      move: []
    };
    this._oncelistenerCountList = {
      close: [],
      data: [],
      mouse: [],
      start: [],
      move: []
    };
    this._Close = false;
  }
  once(eventName, listener) {
    if (typeof eventName === "function") {
      listener = eventName;
      eventName = "mouse";
    }
    if (typeof listener !== "function")
      return mouseHook;
    mouseHook._oncelistenerCountList[eventName].push(listener);
    return mouseHook;
  }
  on(eventName, listener) {
    if (typeof eventName === "function") {
      listener = eventName;
      eventName = "mouse";
    }
    if (typeof listener !== "function")
      return mouseHook;
    mouseHook._onlistenerCountList[eventName].push(listener);
    return mouseHook;
  }
  start() {
    let start = native.isStartHookMouse();
    if (start)
      throw new Error("the Task Has Started.");
    native.installHookMouse();
    const oid_Mouse_info = {
      x: 0,
      y: 0,
      isDown: false
    };
    mouseHook.emit("start");
    let emit_getMouseNextSession = () => {
      if (mouseHook._Close) {
        return;
      }
      ;
      let getMouseNextSession = native.getMouseNextSession();
      if (getMouseNextSession == null ? void 0 : getMouseNextSession.length)
        mouseHook.emit("data", getMouseNextSession);
      if (getMouseNextSession)
        for (let index = 0; index < getMouseNextSession.length; index++) {
          const MouseNextSession = getMouseNextSession[index];
          const mousePoint = new MousePoint(MouseNextSession);
          mouseHook.emit("mouse", mousePoint);
          if (oid_Mouse_info.x != mousePoint.x || oid_Mouse_info.y != mousePoint.y) {
            mouseHook.emit("move", mousePoint.x, mousePoint.y, mousePoint);
          }
          oid_Mouse_info.isDown = mousePoint.isDown;
          oid_Mouse_info.x = mousePoint.x;
          oid_Mouse_info.y = mousePoint.y;
        }
    };
    (async () => {
      while (true) {
        if (this._Close)
          return;
        await Sleep(50);
        emit_getMouseNextSession();
      }
    })();
  }
  close() {
    native.unHookMouse();
    mouseHook.emit("close");
    mouseHook._Close = true;
    mouseHook._oncelistenerCountList.close.length = 0;
    mouseHook._oncelistenerCountList.data.length = 0;
    mouseHook._oncelistenerCountList.mouse.length = 0;
    mouseHook._oncelistenerCountList.move.length = 0;
    mouseHook._oncelistenerCountList.start.length = 0;
    mouseHook._onlistenerCountList.close.length = 0;
    mouseHook._onlistenerCountList.data.length = 0;
    mouseHook._onlistenerCountList.mouse.length = 0;
    mouseHook._onlistenerCountList.move.length = 0;
    mouseHook._onlistenerCountList.start.length = 0;
  }
  emit(eventName, ...data) {
    const emitFunList = mouseHook._onlistenerCountList[eventName];
    const onceEmitFunList = mouseHook._oncelistenerCountList[eventName];
    for (let index = 0; index < emitFunList.length; index++) {
      const emitFun = emitFunList[index];
      emitFun.apply(mouseHook, data);
    }
    ;
    for (let index = 0; index < onceEmitFunList.length; index++) {
      const emitFun = onceEmitFunList[index];
      emitFun.apply(mouseHook, data);
    }
    ;
    onceEmitFunList.length = 0;
    return emitFunList.length ? true : false;
  }
  off(eventName, treatmentMode, data) {
    switch (treatmentMode) {
      case "on": {
        if (data) {
          const listenerCountList = mouseHook._onlistenerCountList[eventName];
          if (listenerCountList.indexOf(data)) {
            return mouseHook._onlistenerCountList[eventName].splice(listenerCountList.indexOf(data), 1) ? true : false;
          }
        } else {
          mouseHook._onlistenerCountList[eventName].length = 0;
          return !mouseHook._onlistenerCountList[eventName].length;
        }
        break;
      }
      case "once": {
        if (data) {
          const listenerCountList = mouseHook._oncelistenerCountList[eventName];
          if (listenerCountList.indexOf(data)) {
            return mouseHook._oncelistenerCountList[eventName].splice(listenerCountList.indexOf(data), 1) ? true : false;
          }
        } else {
          mouseHook._oncelistenerCountList[eventName].length = 0;
          return !mouseHook._oncelistenerCountList[eventName].length;
        }
        break;
      }
    }
    return false;
  }
};
var mouseHook = new Iohook_Mouse();
var Iohook_Keyboard = class {
  constructor() {
    this._onlistenerCountList = {
      close: [],
      data: [],
      start: [],
      change: []
    };
    this._oncelistenerCountList = {
      close: [],
      data: [],
      start: [],
      change: []
    };
    this._Close = false;
  }
  once(eventName, listener) {
    if (typeof eventName === "function") {
      listener = eventName;
      eventName = "change";
    }
    if (typeof listener !== "function")
      return keyboardHook;
    keyboardHook._oncelistenerCountList[eventName].push(listener);
    return keyboardHook;
  }
  on(eventName, listener) {
    if (typeof eventName === "function") {
      listener = eventName;
      eventName = "change";
    }
    if (typeof listener !== "function")
      return keyboardHook;
    keyboardHook._onlistenerCountList[eventName].push(listener);
    return keyboardHook;
  }
  start() {
    let start = native.isStartKeyboardHook();
    if (start)
      throw new Error("the Task Has Started.");
    native.installKeyboardHook();
    keyboardHook.emit("start");
    let emit_getKeyboardNextSession = () => {
      let getKeyboardNextSession = native.getKeyboardNextSession();
      if (getKeyboardNextSession == null ? void 0 : getKeyboardNextSession.length)
        keyboardHook.emit("data", getKeyboardNextSession);
      if (getKeyboardNextSession)
        for (let index = 0; index < getKeyboardNextSession.length; index++) {
          const KeyboardNextSession = getKeyboardNextSession[index];
          const KeyboardPoint = new Keyboard(KeyboardNextSession);
          keyboardHook.emit("change", KeyboardPoint);
        }
    };
    (async () => {
      while (true) {
        if (keyboardHook._Close)
          return;
        await Sleep(15);
        emit_getKeyboardNextSession();
      }
    })();
    return start;
  }
  close() {
    native.unKeyboardHook();
    keyboardHook.emit("close");
    keyboardHook._Close = true;
    keyboardHook._oncelistenerCountList.close.length = 0;
    keyboardHook._oncelistenerCountList.data.length = 0;
    keyboardHook._oncelistenerCountList.change.length = 0;
    keyboardHook._oncelistenerCountList.start.length = 0;
    keyboardHook._onlistenerCountList.close.length = 0;
    keyboardHook._onlistenerCountList.data.length = 0;
    keyboardHook._onlistenerCountList.change.length = 0;
    keyboardHook._onlistenerCountList.start.length = 0;
  }
  emit(eventName, ...data) {
    const emitFunList = keyboardHook._onlistenerCountList[eventName];
    const onceEmitFunList = keyboardHook._oncelistenerCountList[eventName];
    for (let index = 0; index < emitFunList.length; index++) {
      const emitFun = emitFunList[index];
      emitFun.apply(keyboardHook, data);
    }
    ;
    for (let index = 0; index < onceEmitFunList.length; index++) {
      const emitFun = onceEmitFunList[index];
      emitFun.apply(keyboardHook, data);
    }
    ;
    onceEmitFunList.length = 0;
    return emitFunList.length ? true : false;
  }
  off(eventName, treatmentMode, data) {
    switch (treatmentMode) {
      case "on": {
        if (data) {
          const listenerCountList = keyboardHook._onlistenerCountList[eventName];
          if (listenerCountList.indexOf(data)) {
            return keyboardHook._onlistenerCountList[eventName].splice(listenerCountList.indexOf(data), 1) ? true : false;
          }
        } else {
          keyboardHook._onlistenerCountList[eventName].length = 0;
          return !keyboardHook._onlistenerCountList[eventName].length;
        }
        break;
      }
      case "once": {
        if (data) {
          const listenerCountList = keyboardHook._oncelistenerCountList[eventName];
          if (listenerCountList.indexOf(data)) {
            return keyboardHook._oncelistenerCountList[eventName].splice(listenerCountList.indexOf(data), 1) ? true : false;
          }
        } else {
          keyboardHook._oncelistenerCountList[eventName].length = 0;
          return !keyboardHook._oncelistenerCountList[eventName].length;
        }
        break;
      }
    }
    return false;
  }
};
var keyboardHook = new Iohook_Keyboard();
var Auto = {
  setWindowEnabled,
  setCursorPos,
  mouse,
  rightClick,
  leftClick,
  getBasicKeys,
  getMouseMovePoints,
  powerControl,
  SetBlockInput,
  SetSystemHOOK,
  hasKeyActivate,
  mouseHook,
  keyboardHook
};
var Usb = {
  getHub: getHidUsbList,
  getDevsInfo: getUsbDevsInfo,
  watch: watchUSB
};
var Shell = {
  trash: deleteFile,
  openApp,
  getShortcutLink,
  setShortcutLink,
  freePort,
  createSymlink,
  createDirSymlink,
  createHardLink
};
var Process = {
  watch: processWatchdog,
  kill: killProcess,
  killMatch: killProcessName,
  getList: getProcessList,
  getHandle: getProcessHandle,
  getName: getProcessName,
  getPath: getProcessidFilePath,
  getFocus: getForegroundWindowProcessID,
  has: hasProcess,
  match: getProcessNameList,
  matchDetails: getDetailsProcessNameList,
  getDetailsList: getDetailsProcessList
};
var registr = {
  analysisDirectPath,
  has: (HKEY, Path, key) => {
    return hasRegistrKey(HKEY, Path, key);
  },
  get: (HKEY, Path, key) => {
    return getStringRegKey(HKEY, Path, key);
  },
  set: (HKEY, Path, key, value) => {
    return setRegistrKey(HKEY, Path, key, value);
  },
  remove: (HKEY, Path, key) => {
    return removeStringRegKey(HKEY, Path, key);
  },
  keys: (HKEY, Path) => {
    return enumRegistrKey(HKEY, Path);
  },
  list: (HKEY, Path) => {
    return listRegistrPath(HKEY, Path);
  },
  create: (HKEY, Path, key) => {
    return createPathRegistr(HKEY, Path);
  },
  open: (HKEY, Path, key) => {
    return openRegKey(HKEY, Path, key);
  },
  get hasRegistrKey() {
    return this.has;
  },
  get listRegistrPath() {
    return this.list;
  },
  get enumRegistrKey() {
    return this.keys;
  },
  get removeStringRegKey() {
    return this.remove;
  },
  get setRegistrKey() {
    return this.set;
  },
  get getStringRegKey() {
    return this.get;
  },
  getNumberRegKey: (HKEY, Path, key) => {
    return getNumberRegKey(HKEY, Path, key);
  },
  get createPathRegistr() {
    return this.create;
  },
  getRegistrBuffValue: (HKEY, Path, key) => {
    return getRegistrBuffValue(HKEY, Path, key);
  },
  get openRegKey() {
    return open;
  },
  getRegistrQword,
  getRegistrDword,
  setRegistrQword,
  setRegistrDword,
  removeStringRegValue,
  removeStringRegKeyWalk,
  removeStringTree,
  isRegistrTreeKey
};
var Registr = registr;
var hmc = {
  getWebView2Info,
  hasWebView2,
  Auto,
  Clipboard,
  HMC,
  HWND,
  MessageError,
  MessageStop,
  Process,
  SetBlockInput,
  SetSystemHOOK,
  SetWindowInTaskbarVisible,
  Shell,
  Sleep,
  Usb,
  Watch,
  WatchWindowForeground,
  WatchWindowPoint,
  Window,
  alert,
  analysisDirectPath,
  clearClipboard,
  closedHandle,
  confirm,
  createDirSymlink,
  createHardLink,
  createPathRegistr,
  createSymlink,
  deleteFile,
  desc,
  enumChildWindows,
  enumRegistrKey,
  freePort,
  getAllWindows,
  getAllWindowsHandle,
  getBasicKeys,
  getClipboardFilePaths,
  getClipboardSequenceNumber,
  getClipboardText,
  getConsoleHandle,
  getCurrentMonitorRect,
  getDetailsProcessList,
  getDetailsProcessNameList,
  getDeviceCaps,
  getDeviceCapsAll,
  getForegroundWindow,
  getForegroundWindowProcessID,
  getHandleProcessID,
  getHidUsbList,
  getMainWindow,
  getMetrics,
  getMouseMovePoints,
  getNumberRegKey,
  getPointWindow,
  getPointWindowMain,
  getPointWindowName,
  getPointWindowProcessId,
  getProcessHandle,
  getProcessList,
  getProcessName,
  getProcessNameList,
  getProcessidFilePath,
  getRegistrBuffValue,
  getRegistrDword,
  getRegistrQword,
  getShortcutLink,
  getStringRegKey,
  getSystemIdleTime,
  getSystemMenu,
  getSystemMetricsLen,
  getTrayList,
  getUsbDevsInfo,
  getWindowClassName,
  getWindowRect,
  getWindowStyle,
  getWindowTitle,
  hasKeyActivate,
  hasProcess,
  hasRegistrKey,
  hasWindowTop,
  hideConsole,
  isAdmin,
  isEnabled,
  isHandle,
  isHandleWindowVisible,
  isInMonitorWindow,
  isMouseMonitorWindow,
  isProcess,
  isRegistrTreeKey,
  isSystemX64,
  killProcess,
  killProcessName,
  leftClick,
  listRegistrPath,
  lookHandleCloseWindow,
  lookHandleGetTitle,
  lookHandleSetTitle,
  lookHandleShowWindow,
  messageBox,
  mouse,
  native,
  openApp,
  openExternal,
  openPath,
  openRegKey,
  openURL,
  platform,
  powerControl,
  processWatchdog,
  ref,
  registr,
  removeStringRegKey,
  removeStringRegKeyWalk,
  removeStringRegValue,
  removeStringTree,
  rightClick,
  setClipboardFilePaths,
  setClipboardText,
  setCloseWindow,
  setCursorPos,
  setHandleTransparent,
  setRegistrDword,
  setRegistrKey,
  setRegistrQword,
  setShortcutLink,
  setShowWindow,
  setWindowEnabled,
  setWindowFocus,
  setWindowMode,
  setWindowTitle,
  setWindowTop,
  showConsole,
  showMonitors,
  shutMonitors,
  sleep,
  system,
  systemChcp,
  systemStartTime,
  trash,
  updateWindow,
  version,
  watchClipboard,
  watchUSB,
  windowJitter,
  keyboardHook,
  mouseHook
};
var hmc_default = hmc;
process.on("exit", function() {
  if (SetIohook) {
    native.unHookMouse();
    native.unKeyboardHook();
  }
});
// Annotate the CommonJS export names for ESM import in node:
0 && (module.exports = {
  Auto,
  Clipboard,
  HMC,
  HWND,
  MessageError,
  MessageStop,
  Process,
  Registr,
  SetBlockInput,
  SetSystemHOOK,
  SetWindowInTaskbarVisible,
  Shell,
  Sleep,
  Usb,
  Watch,
  WatchWindowForeground,
  WatchWindowPoint,
  WebView2OnlineInstall,
  Window,
  alert,
  analysisDirectPath,
  clearClipboard,
  closedHandle,
  confirm,
  createDirSymlink,
  createHardLink,
  createPathRegistr,
  createSymlink,
  deleteFile,
  desc,
  enumChildWindows,
  enumRegistrKey,
  freePort,
  getAllWindows,
  getAllWindowsHandle,
  getBasicKeys,
  getClipboardFilePaths,
  getClipboardSequenceNumber,
  getClipboardText,
  getConsoleHandle,
  getCurrentMonitorRect,
  getDetailsProcessList,
  getDetailsProcessNameList,
  getDeviceCaps,
  getDeviceCapsAll,
  getForegroundWindow,
  getForegroundWindowProcessID,
  getHandleProcessID,
  getHidUsbList,
  getMainWindow,
  getMetrics,
  getMouseMovePoints,
  getNumberRegKey,
  getPointWindow,
  getPointWindowMain,
  getPointWindowName,
  getPointWindowProcessId,
  getProcessHandle,
  getProcessList,
  getProcessName,
  getProcessNameList,
  getProcessidFilePath,
  getRegistrBuffValue,
  getRegistrDword,
  getRegistrQword,
  getShortcutLink,
  getStringRegKey,
  getSystemIdleTime,
  getSystemMenu,
  getSystemMetricsLen,
  getTrayList,
  getUsbDevsInfo,
  getWebView2Info,
  getWindowClassName,
  getWindowRect,
  getWindowStyle,
  getWindowTitle,
  hasKeyActivate,
  hasProcess,
  hasRegistrKey,
  hasWebView2,
  hasWindowTop,
  hideConsole,
  hmc,
  isAdmin,
  isEnabled,
  isHandle,
  isHandleWindowVisible,
  isInMonitorWindow,
  isMouseMonitorWindow,
  isProcess,
  isRegistrTreeKey,
  isSystemX64,
  keyboardHook,
  killProcess,
  killProcessName,
  leftClick,
  listRegistrPath,
  lookHandleCloseWindow,
  lookHandleGetTitle,
  lookHandleSetTitle,
  lookHandleShowWindow,
  messageBox,
  mouse,
  mouseHook,
  native,
  openApp,
  openExternal,
  openPath,
  openRegKey,
  openURL,
  platform,
  powerControl,
  processWatchdog,
  ref,
  registr,
  removeStringRegKey,
  removeStringRegKeyWalk,
  removeStringRegValue,
  removeStringTree,
  rightClick,
  setClipboardFilePaths,
  setClipboardText,
  setCloseWindow,
  setCursorPos,
  setHandleTransparent,
  setRegistrDword,
  setRegistrKey,
  setRegistrQword,
  setShortcutLink,
  setShowWindow,
  setWindowEnabled,
  setWindowFocus,
  setWindowMode,
  setWindowTitle,
  setWindowTop,
  showConsole,
  showMonitors,
  shutMonitors,
  sleep,
  system,
  systemChcp,
  systemStartTime,
  trash,
  updateWindow,
  version,
  watchClipboard,
  watchUSB,
  windowJitter
});
