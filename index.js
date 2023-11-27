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
      // object is more readable than multi-dim array.
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
  _KeyboardcodeComparisonTable: () => _KeyboardcodeComparisonTable,
  _KeyboardcodeEmenList: () => _KeyboardcodeEmenList,
  _popen: () => _popen,
  alert: () => alert,
  analysisDirectPath: () => analysisDirectPath,
  captureBmpToFile: () => captureBmpToFile,
  clearClipboard: () => clearClipboard,
  closedHandle: () => closedHandle,
  confirm: () => confirm,
  createDirSymlink: () => createDirSymlink,
  createHardLink: () => createHardLink,
  createMutex: () => createMutex,
  createPathRegistr: () => createPathRegistr,
  createSymlink: () => createSymlink,
  default: () => hmc_default,
  deleteFile: () => deleteFile,
  desc: () => desc,
  enumAllProcessHandle: () => enumAllProcessHandle,
  enumChildWindows: () => enumChildWindows,
  enumProcessHandle: () => enumProcessHandle,
  enumRegistrKey: () => enumRegistrKey,
  findWindow: () => findWindow,
  findWindowEx: () => findWindowEx,
  formatVolumePath: () => formatVolumePath,
  freePort: () => freePort,
  getAllEnv: () => getAllEnv,
  getAllWindows: () => getAllWindows,
  getAllWindowsHandle: () => getAllWindowsHandle,
  getBasicKeys: () => getBasicKeys,
  getClipboardFilePaths: () => getClipboardFilePaths,
  getClipboardSequenceNumber: () => getClipboardSequenceNumber,
  getClipboardText: () => getClipboardText,
  getColor: () => getColor,
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
  getModulePathList: () => getModulePathList,
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
  getProcessParentProcessID: () => getProcessParentProcessID,
  getProcessThreadList: () => getProcessThreadList,
  getProcessidFilePath: () => getProcessidFilePath,
  getRegistrBuffValue: () => getRegistrBuffValue,
  getRegistrDword: () => getRegistrDword,
  getRegistrQword: () => getRegistrQword,
  getShortcutLink: () => getShortcutLink,
  getStringRegKey: () => getStringRegKey,
  getSubProcessID: () => getSubProcessID,
  getSystemIdleTime: () => getSystemIdleTime,
  getSystemMenu: () => getSystemMenu,
  getSystemMetricsLen: () => getSystemMetricsLen,
  getTCPPortProcessID: () => getTCPPortProcessID,
  getTrayList: () => getTrayList,
  getUDPPortProcessID: () => getUDPPortProcessID,
  getUsbDevsInfo: () => getUsbDevsInfo,
  getVolumeList: () => getVolumeList,
  getWebView2Info: () => getWebView2Info,
  getWindowClassName: () => getWindowClassName,
  getWindowRect: () => getWindowRect,
  getWindowStyle: () => getWindowStyle,
  getWindowTitle: () => getWindowTitle,
  getenv: () => getenv,
  hasKeyActivate: () => hasKeyActivate,
  hasMutex: () => hasMutex,
  hasPortTCP: () => hasPortTCP,
  hasPortUDP: () => hasPortUDP,
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
  popen: () => popen,
  powerControl: () => powerControl,
  processWatchdog: () => processWatchdog,
  putenv: () => putenv,
  ref: () => ref,
  registr: () => registr,
  removeStringRegKey: () => removeStringRegKey,
  removeStringRegKeyWalk: () => removeStringRegKeyWalk,
  removeStringRegValue: () => removeStringRegValue,
  removeStringTree: () => removeStringTree,
  rightClick: () => rightClick,
  sendBasicKeys: () => sendBasicKeys,
  sendKeyboard: () => sendKeyboard,
  sendKeyboardSequence: () => sendKeyboardSequence,
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
  setWindowIconForExtract: () => setWindowIconForExtract,
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

// source/mian/vkKey.ts
var KeyboardcodeComparisonTable = /* @__PURE__ */ new Map();
function installKeyboardcodeComparisonTable() {
  KeyboardcodeEmenList.forEach(function(value, key) {
    if (value.length == 5) {
      if (value[4])
        for (let index = 0; index < value[4].length; index++) {
          const of_value = value[4][index];
          KeyboardcodeComparisonTable.set(of_value.toUpperCase(), key);
        }
    }
    if (typeof value[0] == "string") {
      KeyboardcodeComparisonTable.set(value[0].toUpperCase(), key);
    }
    if (typeof value[1] == "string") {
      KeyboardcodeComparisonTable.set(value[1].toUpperCase(), key);
    }
  });
}
function vkKey(key) {
  if (typeof key == "number")
    return key;
  if (typeof key == "string") {
    key = key.toUpperCase();
    if (!KeyboardcodeComparisonTable.size)
      installKeyboardcodeComparisonTable();
    if (KeyboardcodeComparisonTable == null ? void 0 : KeyboardcodeComparisonTable.has(key)) {
      return KeyboardcodeComparisonTable.get(key) || null;
    }
  }
  return null;
}
var KeyboardVKcodeEmenList = [
  // key ,code , keyCode , VirtualKey
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
  ["'", "Quote", 222, 222],
  ["Win", "MetaLeft", 91, 91],
  ["Win", "MetaRight", 92, 92]
];
var KeyboardcodeEmenList = (() => {
  let data = /* @__PURE__ */ new Map();
  for (let index = 0; index < KeyboardVKcodeEmenList.length; index++) {
    const [VK_key2, VK_code2, VK_keyCode2, VK_VirtualKey2, VK_Nickname] = KeyboardVKcodeEmenList[index];
    data.set(VK_VirtualKey2, KeyboardVKcodeEmenList[index]);
  }
  return data;
})();

// source/mian/hmc.ts
var path = require("path");
var os = require("os");
var fs = require("fs");
var https = require("https");
var dgram = require("dgram");
var child_process = require("child_process");
var net = require("net");
var argvSplit = require_split();
var $_thenConsole = null;
var Hkey = {
  /**用作默认用户首选设置|也作为单个用户的首选设置 */
  HKEY_CURRENT_CONFIG: "HKEY_CURRENT_CONFIG",
  /**用作默认用户首选设置|也作为单个用户的首选设置 */
  HKEY_USERS: "HKEY_USERS",
  /**是与文档类型和 OLE\COM 相关的信息的支持键。这个键是 */
  HKEY_CLASSES_ROOT: "HKEY_CLASSES_ROOT",
  /**包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息 */
  HKEY_LOCAL_MACHINE: "HKEY_LOCAL_MACHINE",
  /**管理系统当前的用户信息 */
  HKEY_CURRENT_USER: "HKEY_CURRENT_USER"
};
var get_native = (binPath) => {
  function _require_bin() {
    try {
      if (binPath)
        return require(binPath);
      if (process.arch.match(/^x32|ia32$/))
        return require("./bin/HMC_x86.node");
      if (process.arch.match(/^x64$/))
        return require("./bin/HMC_x64.node");
    } catch (X_X) {
    }
    return null;
  }
  let Native = (process.platform == "win32" ? _require_bin() : null) || (() => {
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
    function fnAnyArr(...args) {
      console.error(HMCNotPlatform);
      return [];
    }
    return {
      findAllWindow: fnAnyArr,
      _popen: fnStr,
      popen: fnStr,
      createMutex: fnBool,
      getSubProcessID: fnAnyArr,
      enumAllProcessPolling: fnVoid,
      clearEnumAllProcessList: fnVoid,
      getProcessParentProcessID: fnVoid,
      enumAllProcess: fnNum,
      _SET_HMC_DEBUG: fnBool,
      isStartKeyboardHook: fnBool,
      isStartHookMouse: fnBool,
      clearEnumProcessHandle: fnVoid,
      getProcessThreadList: fnAnyArr,
      getMouseNextSession: fnAnyArr,
      getKeyboardNextSession: fnAnyArr,
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
      enumRegistrKey: fnStrList,
      getAllWindows: fnAnyArr,
      getAllWindowsHandle: fnAnyArr,
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
      getDetailsProcessList: fnAnyArr,
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
      getHidUsbList: fnAnyArr,
      getMainWindow: fnNull,
      getMetrics: () => {
        console.error(HMCNotPlatform);
        return { "left": 0, "top": 0, "x": 0, "y": 0 };
      },
      getMouseMovePoints: fnAnyArr,
      getPointWindow: fnNull,
      getPointWindowMain: fnNum,
      getPointWindowName: fnStr,
      getPointWindowProcessId: fnNum,
      getProcessHandle: fnNull,
      getProcessList: fnAnyArr,
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
      getTrayList: fnAnyArr,
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
      setWindowIconForExtract: fnVoid,
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
      enumChildWindows: fnAnyArr,
      deleteFile: fnNum,
      getClipboardSequenceNumber: fnNum,
      enumClipboardFormats: fnAnyArr,
      getHidUsbIdList: fnAnyArr,
      getDeviceCapsAll: fnAnyArr,
      isInMonitorWindow: fnBool,
      isMouseMonitorWindow: fnBool,
      getCurrentMonitorRect: () => {
        console.error(HMCNotPlatform);
        return { "bottom": 0, "left": 0, "top": 0, "right": 0 };
      },
      getSystemMetricsLen: fnNum,
      getWindowStyle: fnNum,
      getWindowClassName: fnStr,
      formatVolumePath: fnStr,
      getVolumeList: fnAnyArr,
      enumProcessHandlePolling: fnVoid,
      enumProcessHandle: fnNum,
      getModulePathList: fnStrList,
      getColor() {
        return { r: 0, g: 0, b: 0, hex: "#000000" };
      },
      captureBmpToFile: fnVoid,
      sendKeyboard: fnBool,
      sendBasicKeys: fnBool,
      sendKeyT2C: fnVoid,
      sendKeyT2CSync: fnVoid,
      hasMutex: fnBool,
      getAllEnv() {
        return process.env;
      },
      getTCPPortProcessID: fnNull,
      getenv: fnStr,
      getUDPPortProcessID: fnNull,
      putenv: fnVoid,
      findWindowEx: fnNull,
      findWindow: fnNull
    };
  })();
  return Native;
};
var native = get_native();
var HWND = class extends Number {
  constructor(hWnd) {
    super(hWnd);
    this.HWND = hWnd;
  }
  /**句柄 */
  get handle() {
    return this.HWND;
  }
  /**
   * 强制关闭窗口不发送被关闭的消息给窗口
   */
  closed() {
    if (!this.exists)
      return false;
    return native.closedHandle(this.HWND);
  }
  /**
   * 向窗口发送关闭的消息
   */
  close() {
    if (!this.exists)
      return false;
    return native.lookHandleCloseWindow(this.HWND);
  }
  /**
   * 窗口位置
   */
  get rect() {
    if (!this.exists)
      return null;
    return native.getWindowRect(this.HWND);
  }
  /**
   * 窗口名称
   */
  get title() {
    return native.lookHandleGetTitle(this.HWND) || "";
  }
  /**
   * 设置窗口的标题
   * @param Title 标题
   * @returns
   */
  setTitle(Title) {
    if (typeof Title !== "string" || !this.exists) {
      return false;
    }
    return native.lookHandleSetTitle(this.HWND, Title);
  }
  /**句柄是否有效 */
  get exists() {
    if (!this.HWND)
      return false;
    return native.isHandle(this.HWND);
  }
  /**句柄是否有效 */
  get isHandle() {
    return this.exists;
  }
  /**
   * 当前句柄的pid
   */
  get pid() {
    if (!this.exists)
      return 0;
    return native.getHandleProcessID(this.HWND);
  }
  /**
   * 获取主窗口的pid
   */
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
  /**
   * 判断窗口是否可见
   * @returns
   */
  isVisible() {
    if (!this.HWND)
      return false;
    return native.isHandleWindowVisible(this.HWND);
  }
  /**
   * 结束该进程
   * @returns
   */
  kill() {
    let processid = this.MianPid;
    if (!processid)
      return false;
    return native.killProcess(processid);
  }
  /**
   * 隐藏窗口
   * @returns
   */
  hide() {
    if (!this.HWND)
      return false;
    return native.lookHandleShowWindow(this.HWND, 0);
  }
  /**
   * 显示窗口
   * @returns
   */
  show() {
    if (!this.HWND)
      return false;
    return native.lookHandleShowWindow(this.HWND, 5);
  }
  /**
   * 窗口最小化
   * @returns
   */
  setMin() {
    if (!this.HWND)
      return false;
    return native.lookHandleShowWindow(this.HWND, 7);
  }
  /**
   * 窗口最大化
   * @returns
   */
  setMax() {
    if (!this.HWND)
      return false;
    return native.lookHandleShowWindow(this.HWND, 3);
  }
  /**
   * 恢复最近的状态
   * @returns
   */
  setRestore() {
    if (!this.HWND)
      return false;
    return native.lookHandleShowWindow(this.HWND, 9);
  }
  /**
   * 聚焦该窗口
   * @returns
   */
  setFocus() {
    if (!this.HWND)
      return false;
    return native.setWindowFocus(this.HWND);
  }
  /**
   * 禁用窗口
   * @param enabled
   * @returns
   */
  setEnabled(enabled) {
    if (!this.HWND)
      return false;
    return native.setWindowEnabled(this.HWND, enabled);
  }
  /**
   * 是否被禁用
   * @returns
   */
  isEnabled() {
    if (!this.HWND)
      return false;
    return native.isEnabled(this.HWND);
  }
  /**
   * 窗口抖动
   * @returns
   */
  setJitter() {
    if (!this.HWND)
      return false;
    return native.windowJitter(this.HWND);
  }
  /**
   * 判断窗口是否被顶设
   * @returns
   */
  isTop() {
    if (!this.HWND)
      return false;
    return native.hasWindowTop(this.HWND);
  }
  /**
   * 设置窗口顶设或者取消
   * @returns
   */
  setTopOrCancel() {
    if (!this.HWND)
      return false;
    return native.setWindowTop(this.HWND);
  }
  /**
   * 设置窗口不透明度
   * @param opacity 0-100 or 0.0 - 1.0
   */
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
  /**
   * 设置窗口不透明度
   * @param opacity -1 - 255
   */
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
  let MouseKey;
  ((MouseKey2) => {
    MouseKey2[MouseKey2["WM_MOUSEMOVE"] = 512] = "WM_MOUSEMOVE";
    MouseKey2[MouseKey2["WM_LBUTTONDOWN"] = 513] = "WM_LBUTTONDOWN";
    MouseKey2[MouseKey2["WM_RBUTTONDOWN"] = 516] = "WM_RBUTTONDOWN";
    MouseKey2[MouseKey2["WM_LBUTTONUP"] = 514] = "WM_LBUTTONUP";
    MouseKey2[MouseKey2["WM_RBUTTONUP"] = 517] = "WM_RBUTTONUP";
    MouseKey2[MouseKey2["WM_MBUTTONDOWN"] = 519] = "WM_MBUTTONDOWN";
    MouseKey2[MouseKey2["WM_MBUTTONUP"] = 520] = "WM_MBUTTONUP";
    MouseKey2[MouseKey2["WM_MOUSEWHEEL"] = 522] = "WM_MOUSEWHEEL";
  })(MouseKey = HMC2.MouseKey || (HMC2.MouseKey = {}));
  let MouseKeyName;
  ((MouseKeyName2) => {
    MouseKeyName2["UNKNOWN"] = "unknown";
    MouseKeyName2["WM_LBUTTONDOWN"] = "left-button-down";
    MouseKeyName2["WM_RBUTTONDOWN"] = "right-button-down";
    MouseKeyName2["WM_LBUTTONUP"] = "left-button-up";
    MouseKeyName2["WM_RBUTTONUP"] = "right-button-up";
    MouseKeyName2["WM_MBUTTONDOWN"] = "mouse-button-down";
    MouseKeyName2["WM_MBUTTONUP"] = "mouse-button-up";
    MouseKeyName2["WM_MOUSEWHEEL"] = "mouse-wheel";
    MouseKeyName2["WM_MOUSEMOVE"] = "move";
  })(MouseKeyName = HMC2.MouseKeyName || (HMC2.MouseKeyName = {}));
})(HMC || (HMC = {}));
var ref = {
  /**
  * 将内容格式化为文本路径
  * @param Str
  * @returns
  */
  path(Str) {
    return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, "\0");
  },
  /**
   * 格式化为bool
   * @param bool
   * @returns
   */
  bool(bool) {
    return bool ? true : false;
  },
  /**
   * 将内容格式化为文本
   * @param Str
   * @returns
   */
  string(Str) {
    return String(Str || "");
  },
  /**
   * 格式化数字为int(强制)
   * @param Num
   * @returns
   */
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
  /**
   * 文本数组
   * @param array 
   * @returns 
   */
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
  /**
   * 文本数组
   * @param array 
   * @returns 
   */
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
  /**
   * 格式化命令行内容
   */
  formatCmd(cmd) {
    return argvSplit(this.string(cmd));
  },
  /**
   * 将命令行内容组转为cmd文本
   * @param argv 
   */
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
        cout = '"'.concat(cout, '"');
      }
      if (cout.match(/[\n\r]/)) {
        cout = cout.replace(/(\n|\r|\r\n)/g, "$0^");
      }
      argvsResult.push(cout);
    }
    return argvsResult.join(" ");
  },
  /**注册表根目录 */
  HKEY: Hkey,
  /**
   * 拼合buff片段
   * @param buffList 
   * @returns 
   */
  concatBuff(buffList) {
    let buffSize = 0;
    for (let index = 0; index < buffList.length; index++) {
      const buff = buffList[index];
      buffSize = buffSize + buff.byteLength;
    }
    let ResponseData = Buffer.concat([...buffList], buffSize);
    return ResponseData;
  },
  /**
   * 键盘值格式化为键值
   * @param key 键值/键
   * @returns 
   */
  vkKey
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
  if (!width)
    width = 0;
  if (!height)
    height = 0;
  return native.setWindowMode(
    ref.int(HWND2),
    x == null ? null : ref.int(x),
    y == null ? null : ref.int(y),
    ref.int(width),
    ref.int(height)
  );
}
function has_reg_args(HKEY, Path, funName) {
  let hasHKEY = new RegExp("^".concat(Object.keys(Hkey).join("|"), "$")).exec(HKEY);
  if (!hasHKEY || !Path) {
    throw new Error("\n        <fun> ".concat(funName, "  \n        argument size 2 or 3\n        HKEY : ").concat(Object.keys(Hkey), '\n        Path : string\n        key ?: string  or "" or undefined\n        '));
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
    /**
     * 获取全路径
     */
    get path() {
      return HKEY.concat("\\", Path, "\\", key || "");
    },
    /**
     * 设置一个值
     * @param data 数据
     */
    set(data) {
      return native.setRegistrKey(HKEY, Path, key || "", data);
    },
    /**
     * 获取内容
     * @returns
     */
    get() {
      return native.getStringRegKey(HKEY, Path, key || "");
    },
    /**
     * 获取该内容并将其视为二进制缓冲区
     * @returns 二进制缓冲区
     */
    getBuff() {
      return native.getRegistrBuffValue(HKEY, Path, key || "") || Buffer.alloc(0);
    },
    /**
     * 获取该内容并将其视为数字
     * @returns 数字
     */
    getNumber() {
      return Number(native.getStringRegKey(HKEY, Path, key || ""));
    },
    /**
     * 枚举当前路径下的键
     * @returns 键 数组
     */
    keys() {
      return enumRegistrKey(HKEY, Path);
    },
    /**
     * 将当前目录转为对象
     */
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
    /**
     * 取消继续监听
     */
    unwatcher() {
      Next = false;
    },
    /**
     * 每次判断内容变化用时 默认 `150` ms
     * @param nextAwaitMs 
     */
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
    /**
     * 取消继续监听
     */
    unwatcher() {
      Next = false;
    },
    /**
     * 每次判断内容变化用时 默认 `800` ms
     * @param nextAwaitMs 
     */
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
function getAllWindowsHandle(isWindows) {
  let data = [];
  let AllWindowsHandle = native.getAllWindowsHandle(isWindows || false);
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
    /**结束监听 */
    quit: function() {
      quit = true;
    },
    /**设置每次延迟事件 */
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
    /**结束监听 */
    quit: function() {
      quit = true;
    },
    /**设置每次延迟事件 */
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
function hasProcess(...ProcessMatch) {
  if (ProcessMatch.length == 1) {
    return native.isProcess(ref.int(ProcessMatch[0]));
  }
  let _ProcessMatch = [];
  let isString = false;
  for (let index = 0; index < ProcessMatch.length; index++) {
    const ProcessID = ProcessMatch[index];
    if (Array.isArray(ProcessID)) {
      for (let index2 = 0; index2 < ProcessID.length; index2++) {
        if (typeof ProcessID[index2] == "string")
          isString = true;
        _ProcessMatch.push(ProcessID[index2]);
      }
    }
    if (typeof ProcessID == "string") {
      isString = true;
      _ProcessMatch.push(ProcessID);
    }
    if (typeof ProcessID == "number")
      _ProcessMatch.push(ProcessID);
  }
  let ProcessList = isString ? getProcessList() : [];
  for (let index = 0; index < _ProcessMatch.length; index++) {
    if (!isString) {
      if (native.isProcess(ref.int(_ProcessMatch[index])))
        return true;
    }
    for (let index2 = 0; index2 < ProcessList.length; index2++) {
      const elp = ProcessList[index2];
      if (elp.name === _ProcessMatch[index2] || elp.pid === _ProcessMatch[index2])
        return true;
    }
  }
  return false;
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
  if (typeof args[1] == "object") {
    const shortcutData = args[1] || {};
    args[1] = shortcutData.path || "";
    args[2] = shortcutData.cwd || "";
    args[3] = shortcutData.desc || "";
    args[4] = shortcutData.args || "";
    args[5] = shortcutData.showCmd || 1;
    args[6] = shortcutData.icon || "";
    args[7] = shortcutData.iconIndex || 0;
  }
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
function getAllWindows(isWindows, initialize) {
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
  let AllWindowsHandle = native.getAllWindowsHandle(isWindows === false ? false : true);
  let AllWindows = [];
  for (let index = 0; index < AllWindowsHandle.length; index++) {
    const handle = AllWindowsHandle[index];
    const WINDOWS_INFO_ITEM = new WINDOWS_INFO(handle);
    if (initialize) {
      AllWindows.push({
        handle: WINDOWS_INFO_ITEM.handle,
        className: WINDOWS_INFO_ITEM.className,
        rect: WINDOWS_INFO_ITEM.rect,
        style: WINDOWS_INFO_ITEM.style,
        title: WINDOWS_INFO_ITEM.title
      });
    } else {
      AllWindows.push(WINDOWS_INFO_ITEM);
    }
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
        reject(new Error("Install  WebView2 failure statusCode: ".concat(res.statusCode || 404)));
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
            reject(new Error("Install  WebView2 failure Installation process creation failed"));
            spawn.kill();
          });
          spawn.once("exit", function() {
            resolve(void 0);
          });
        }).catch((err) => {
          reject(new Error("Install  WebView2 failure Update file cannot be written"));
        });
      });
    });
  });
}
function hasWebView2() {
  return GetWebView2Info(true);
}
function hasPortTCP(port, callBack) {
  let resolve = null;
  let prom;
  let sock = net.createServer(function() {
  });
  sock.listen(port);
  if (typeof callBack == "function") {
    resolve = callBack;
  } else {
    prom = new Promise((Prom_resolve) => {
      resolve = Prom_resolve;
    });
  }
  sock.on("error", function(err) {
    resolve && resolve(true);
    sock.close();
  });
  sock.on("listening", function() {
    resolve && resolve(false);
    sock.close();
  });
  if (typeof callBack !== "function") {
    return prom;
  }
}
var _KeyboardcodeEmenList = KeyboardcodeEmenList;
var _KeyboardcodeComparisonTable = KeyboardcodeComparisonTable;
function hasPortUDP(port, callBack) {
  let resolve = null;
  let prom;
  let udp4 = dgram.createSocket("udp4");
  udp4.bind(port);
  if (typeof callBack == "function") {
    resolve = callBack;
  } else {
    prom = new Promise((Prom_resolve) => {
      resolve = Prom_resolve;
    });
  }
  udp4.on("error", function(err) {
    resolve && resolve(true);
    udp4.close();
  });
  udp4.on("listening", function() {
    resolve && resolve(false);
    udp4.close();
  });
  if (typeof callBack !== "function") {
    return prom;
  }
}
function formatVolumePath(VolumePath) {
  return native.formatVolumePath(ref.string(VolumePath));
}
function getVolumeList() {
  return native.getVolumeList();
}
function getModulePathList(ProcessID) {
  return native.getModulePathList(ref.int(ProcessID));
}
function enumProcessHandle(ProcessID, CallBack) {
  let enumID = native.enumProcessHandle(ref.int(ProcessID));
  let next = true;
  let enumProcessHandleList = [];
  if (typeof enumID != "number")
    throw new Error("No enumerated id to query unknown error");
  if (typeof CallBack == "function") {
    ;
    (async () => {
      while (next) {
        await Sleep(50);
        let data = native.enumProcessHandlePolling(enumID);
        if (data) {
          for (let index = 0; index < data.length; index++) {
            const enumProcessHandle2 = data[index];
            if (!enumProcessHandle2)
              continue;
            if (enumProcessHandle2.type == "hmc::endl::") {
              return;
            }
            CallBack(enumProcessHandle2);
          }
        }
      }
    })();
    return;
  }
  return new Promise(async (resolve, reject) => {
    while (next) {
      await Sleep(50);
      let data = native.enumProcessHandlePolling(enumID);
      if (data) {
        for (let index = 0; index < data.length; index++) {
          const enumProcessHandle2 = data[index];
          if (!enumProcessHandle2)
            continue;
          if (enumProcessHandle2.type == "hmc::endl::") {
            return resolve(enumProcessHandleList);
          }
          enumProcessHandleList.push(enumProcessHandle2);
        }
      }
    }
    resolve(enumProcessHandleList);
  });
}
function getProcessThreadList(ProcessID, returnDetail) {
  const _returnDetail = returnDetail ? true : false;
  if (_returnDetail)
    return native.getProcessThreadList(ref.int(ProcessID), true) || [];
  return native.getProcessThreadList(ref.int(ProcessID)) || [];
}
function getSubProcessID(ProcessID) {
  return native.getSubProcessID(ref.int(ProcessID)) || [];
}
function getProcessParentProcessID(ProcessID) {
  return native.getProcessParentProcessID(ref.int(ProcessID)) || null;
}
function enumAllProcessHandle(CallBack) {
  let enumID = native.enumAllProcess();
  let next = true;
  let PROCESSENTRYLIST = [];
  if (typeof enumID != "number")
    throw new Error("No enumerated id to query unknown error");
  if (typeof CallBack == "function") {
    ;
    (async () => {
      while (next) {
        await Sleep(15);
        let data = native.enumAllProcessPolling(enumID);
        if (data) {
          for (let index = 0; index < data.length; index++) {
            const PROCESSENTRY = data[index];
            if (!PROCESSENTRY)
              continue;
            if (PROCESSENTRY.szExeFile == "HMC::endl::") {
              return;
            }
            CallBack(PROCESSENTRY);
          }
        }
      }
    })();
    return;
  }
  return new Promise(async (resolve, reject) => {
    while (next) {
      await Sleep(50);
      let data = native.enumAllProcessPolling(enumID);
      if (data) {
        for (let index = 0; index < data.length; index++) {
          const PROCESSENTRY = data[index];
          if (!PROCESSENTRY)
            continue;
          if (PROCESSENTRY.szExeFile == "HMC::endl::") {
            return resolve(PROCESSENTRYLIST);
          }
          PROCESSENTRYLIST.push(PROCESSENTRY);
        }
      }
    }
    resolve(PROCESSENTRYLIST);
  });
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
    this.mouseKeyCode = Number(data[2]);
    this.event = "unknown" /* UNKNOWN */;
    this.isDown = ((key = this.mouseKeyCode) => {
      switch (key) {
        case 513 /* WM_LBUTTONDOWN */:
          this.event = "left-button-down" /* WM_LBUTTONDOWN */;
          break;
        case 516 /* WM_RBUTTONDOWN */:
          this.event = "right-button-down" /* WM_RBUTTONDOWN */;
          break;
        case 519 /* WM_MBUTTONDOWN */:
          this.event = "mouse-button-down" /* WM_MBUTTONDOWN */;
          break;
        case 514 /* WM_LBUTTONUP */:
          this.event = "left-button-up" /* WM_LBUTTONUP */;
          break;
        case 517 /* WM_RBUTTONUP */:
          this.event = "right-button-up" /* WM_RBUTTONUP */;
          break;
        case 520 /* WM_MBUTTONUP */:
          this.event = "mouse-button-up" /* WM_MBUTTONUP */;
          break;
        case 522 /* WM_MOUSEWHEEL */:
          this.event = "mouse-wheel" /* WM_MOUSEWHEEL */;
          break;
        case 512 /* WM_MOUSEMOVE */:
          this.event = "move" /* WM_MOUSEMOVE */;
          break;
      }
      switch (key) {
        case 513 /* WM_LBUTTONDOWN */:
        case 516 /* WM_RBUTTONDOWN */:
        case 519 /* WM_MBUTTONDOWN */:
          return true;
      }
      return false;
    })();
  }
  /**
   * 鼠标左键按下
   */
  get isLeft() {
    return Auto.hasKeyActivate(1);
  }
  /**
   * 鼠标右键被按下
   */
  get isRight() {
    return Auto.hasKeyActivate(2);
  }
  /**
   * 鼠标中键被按下
   */
  get isMiddle() {
    return Auto.hasKeyActivate(4);
  }
  /**
   * 在此坐标模拟进行单击
   * @param awitMs 
   */
  async click(awitMs) {
    awitMs = awitMs || 150;
    Auto.setCursorPos(this.x, this.y);
    Auto.mouse("MOUSEEVENTF_LEFTDOWN");
    await Sleep(awitMs);
    return Auto.mouse("MOUSEEVENTF_LEFTUP");
  }
  /**
   * 模拟右键在此坐标按下和释放鼠标中键
   * @param awitMs 
   */
  async middle(awitMs) {
    awitMs = awitMs || 150;
    Auto.setCursorPos(this.x, this.y);
    Auto.mouse(32);
    await Sleep(awitMs);
    return Auto.mouse("MOUSEEVENTF_MIDDLEUP");
  }
  /**
   * 在此坐标按下模拟右键点击
   * @param awitMs 
   */
  async rClick(awitMs) {
    awitMs = awitMs || 150;
    Auto.setCursorPos(this.x, this.y);
    Auto.mouse("MOUSEEVENTF_RIGHTDOWN");
    await Sleep(awitMs);
    return Auto.mouse("MOUSEEVENTF_RIGHTUP");
  }
  /**
   * 双击
   * @param doubleAwitMs 双击间隔 
   * @param clickAwitMs 模拟点击时间间隔
   */
  doubleClick(doubleAwitMs, clickAwitMs) {
    doubleAwitMs = doubleAwitMs || 150;
    clickAwitMs = clickAwitMs || 150;
    this.click(clickAwitMs).then(() => {
      Sleep(doubleAwitMs || 150).then(() => {
        this.click(clickAwitMs);
      });
    });
  }
  /**
   * 移动鼠标位置
   * @param x 
   * @param y 
   */
  moveMouse(x, y) {
    Auto.setCursorPos(x, y);
  }
};
var Keyboard = class {
  /**
   * 是否按下了shift
   */
  get shiftKey() {
    return Auto.hasKeyActivate(16) || Auto.hasKeyActivate(161) || Auto.hasKeyActivate(160);
  }
  /***
   * 是否按下了alt
   */
  get altKey() {
    return Auto.hasKeyActivate(18) || Auto.hasKeyActivate(164) || Auto.hasKeyActivate(165);
  }
  /***
   * 是否按下了ctrl
   */
  get ctrlKey() {
    return Auto.hasKeyActivate(17);
  }
  /***
   * 是否按下了win
   */
  get winKey() {
    return Auto.hasKeyActivate(91) || Auto.hasKeyActivate(92);
  }
  constructor(str) {
    const data = str.split("|");
    this.vKey = Number(data[0]);
    this.__isDown = Number(data[1]) ? true : false;
    let KeyboardcodeEmen = KeyboardcodeEmenList.get(this.vKey);
    if (!KeyboardcodeEmen) {
      KeyboardcodeEmen = ["unknown", null, this.vKey, 0];
    }
    const [VK_key2, VK_code2, VK_keyCode2, VK_VirtualKey2, VK_Nickname] = KeyboardcodeEmen;
    this.keyCode = VK_keyCode2;
    this.key = VK_key2;
    this.code = VK_code2 || VK_key2;
  }
  /**是否被按下 */
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
      move: [],
      button: [],
      wheel: []
    };
    this._oncelistenerCountList = {
      close: [],
      data: [],
      mouse: [],
      start: [],
      move: [],
      button: [],
      wheel: []
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
  /**
   * 开始
   * @returns 
   */
  start() {
    SetIohook = true;
    let start = native.isStartHookMouse();
    if (start)
      throw new Error("the Task Has Started.");
    native.installHookMouse();
    const oid_Mouse_info = {
      x: 0,
      y: 0,
      isDown: false
    };
    if (native.isStartHookMouse()) {
      mouseHook._Close = false;
    }
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
          if ([
            513 /* WM_LBUTTONDOWN */,
            514 /* WM_LBUTTONUP */,
            519 /* WM_MBUTTONDOWN */,
            520 /* WM_MBUTTONUP */,
            516 /* WM_RBUTTONDOWN */,
            517 /* WM_RBUTTONUP */
          ].includes(mousePoint.mouseKeyCode)) {
            mouseHook.emit("button", mousePoint.event, mousePoint);
          }
          if ([522 /* WM_MOUSEWHEEL */].includes(mousePoint.mouseKeyCode)) {
            mouseHook.emit("wheel", mousePoint);
          }
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
        if (mouseHook._Close)
          return;
        await Sleep(50);
        emit_getMouseNextSession();
      }
    })();
  }
  /**
   * 结束
   */
  close() {
    native.unHookMouse();
    mouseHook.emit("close");
    mouseHook._Close = true;
    mouseHook._oncelistenerCountList.close.length = 0;
    mouseHook._oncelistenerCountList.data.length = 0;
    mouseHook._oncelistenerCountList.mouse.length = 0;
    mouseHook._oncelistenerCountList.move.length = 0;
    mouseHook._oncelistenerCountList.start.length = 0;
    mouseHook._oncelistenerCountList.button.length = 0;
    mouseHook._oncelistenerCountList.wheel.length = 0;
    mouseHook._onlistenerCountList.close.length = 0;
    mouseHook._onlistenerCountList.data.length = 0;
    mouseHook._onlistenerCountList.mouse.length = 0;
    mouseHook._onlistenerCountList.move.length = 0;
    mouseHook._onlistenerCountList.start.length = 0;
    mouseHook._onlistenerCountList.button.length = 0;
    mouseHook._onlistenerCountList.wheel.length = 0;
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
  /**
   * 关闭监听
   * @param eventName 
   * @param data 
   * @returns 
   */
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
function setWindowIconForExtract(handle, Extract, index) {
  if (!Extract)
    throw new Error("Extract Path not defined");
  return native.setWindowIconForExtract(ref.int(handle), ref.string(Extract), index ? ref.int(index) : 0);
}
function captureBmpToFile(FilePath, x, y, width, height) {
  native.captureBmpToFile(ref.string(FilePath), ref.int(x || 0), ref.int(y || 0), ref.int(width || 0), ref.int(height || 0));
}
function sendKeyboard(keyCode, keyDown) {
  let vk = vkKey(keyCode);
  if (!vk)
    throw new Error("The currently entered keyboard key name/key value does not exist");
  if (keyDown === null) {
    native.sendKeyboard(vk);
  } else
    native.sendKeyboard(vk, ref.bool(keyDown));
}
function sendKeyboardSequence(...keys) {
  (async () => {
    for (let index = 0; index < keys.length; index++) {
      const of_key = keys[index];
      if (Array.isArray(of_key)) {
        if (of_key == null ? void 0 : of_key[2]) {
          let ms = ref.int(of_key == null ? void 0 : of_key[2]);
          await Sleep(ms);
        }
        if (of_key.length < 2)
          continue;
        sendKeyboard(of_key[0], typeof (of_key == null ? void 0 : of_key[1]) == "boolean" ? of_key == null ? void 0 : of_key[1] : null);
      } else if (typeof of_key == "object") {
        let keys2 = Object.keys(of_key);
        if (!keys2.includes("key"))
          continue;
        if (keys2.includes("ms")) {
          let ms = ref.int(of_key.ms);
          await Sleep(ms);
        }
        sendKeyboard(of_key.key, typeof of_key.down == "undefined" ? null : of_key.down);
      }
    }
  })();
}
function getColor(x, y) {
  return native.getColor(ref.int(x), ref.int(y));
}
function sendBasicKeys(ctrlKey, shiftKey, altKey, winKey, KeyCode) {
  let _ctrlKey = false, _shiftKey = false, _altKey = false, _winKey = false;
  let _KeyCode = null;
  if (ctrlKey && typeof ctrlKey == "object") {
    let keys = Object.keys(ctrlKey);
    if (!keys.includes("key") && !keys.includes("code") && !vkKey(shiftKey)) {
      throw new Error("The current function requires other keys, not only (ctrl, shift, ait, win)");
    }
    _ctrlKey = keys.includes("ctrl") ? true : false;
    _shiftKey = keys.includes("shift") ? true : false;
    _altKey = keys.includes("alt") ? true : false;
    _winKey = keys.includes("win") ? true : false;
    _KeyCode = vkKey((ctrlKey == null ? void 0 : ctrlKey.key) || (ctrlKey == null ? void 0 : ctrlKey.code) || shiftKey || 0);
  } else if (typeof ctrlKey == "string") {
    _ctrlKey = ctrlKey.includes("ctrl") ? true : false;
    _shiftKey = ctrlKey.includes("shift") ? true : false;
    _altKey = ctrlKey.includes("alt") ? true : false;
    _winKey = ctrlKey.includes("win") ? true : false;
    _KeyCode = vkKey(ctrlKey.replace(/[+]|ctrl|shift|alt|win/g, ""));
  } else {
    _ctrlKey = ctrlKey ? true : false;
    _shiftKey = shiftKey ? true : false;
    _altKey = altKey ? true : false;
    _winKey = winKey ? true : false;
    _KeyCode = vkKey(KeyCode);
  }
  if ((_ctrlKey || _shiftKey || _altKey || _winKey) && _KeyCode !== null) {
    native.sendBasicKeys(ref.bool(_ctrlKey), ref.bool(_shiftKey), ref.bool(_altKey), ref.bool(_winKey), ref.int(_KeyCode));
  } else {
    throw new Error("The current function can only execute standard shortcuts and cannot enter a key value alone or without a regular keystroke");
  }
}
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
  /**
   * 开始
   * @returns 
   */
  start() {
    SetIohook = true;
    let start = native.isStartKeyboardHook();
    if (start)
      throw new Error("the Task Has Started.");
    native.installKeyboardHook();
    if (native.isStartKeyboardHook()) {
      keyboardHook._Close = false;
    }
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
  /**
   * 结束
   */
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
  /**
   * 关闭监听
   * @param eventName 
   * @param data 
   * @returns 
   */
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
  sendKeyboard,
  sendKeyboardSequence,
  getColor,
  sendBasicKeys,
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
  getDetailsList: getDetailsProcessList,
  parentID: getProcessParentProcessID,
  mianPID: getProcessParentProcessID,
  subPID: getSubProcessID,
  threadList: getProcessThreadList
};
var registr = {
  /**
   * 直达路径解析
   * @param Path 全路径(直达路径)
   * @param atkey 是否将最后一个值解释为键
   * @returns
   */
  analysisDirectPath,
  /**
   * 判断注册表中是否有该键值
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.06591796875 ms
   * @returns
   */
  has: (HKEY, Path, key) => {
    return hasRegistrKey(HKEY, Path, key);
  },
  /**
   * 获取内容(文本)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.108ms
   * @returns
   */
  get: (HKEY, Path, key) => {
    return getStringRegKey(HKEY, Path, key);
  },
  /**
   * 设置键值对
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @param Value 数据
   * @time 2.02392578125 ms
   * @returns
   */
  set: (HKEY, Path, key, value) => {
    return setRegistrKey(HKEY, Path, key, value);
  },
  /**
   * 删除数据
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.076904296875 ms
   * @returns
   */
  remove: (HKEY, Path, key) => {
    return removeStringRegKey(HKEY, Path, key);
  },
  /**
   * 枚举键值
   * @param HKEY 根路径
   * @param Path 路径
   * @time 0.06689453125 ms
   * @returns
   */
  keys: (HKEY, Path) => {
    return enumRegistrKey(HKEY, Path);
  },
  /**
   * 将当前的路径的注册表值转表
   * @param HKEY
   * @param Path
   */
  list: (HKEY, Path) => {
    return listRegistrPath(HKEY, Path);
  },
  /**
   * 创建新的路径
   * @param HKEY 根路径
   * @param Path 路径
   * @time 2.02392578125 ms
   * @returns
   */
  create: (HKEY, Path, key) => {
    return createPathRegistr(HKEY, Path);
  },
  /**
   * 打开一个注册表路径并返回一些实用方法
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @returns
   */
  open: (HKEY, Path, key) => {
    return openRegKey(HKEY, Path, key);
  },
  /**
   * 判断注册表中是否有该键值
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.06591796875 ms
   * @returns
   */
  get hasRegistrKey() {
    return this.has;
  },
  /**
   * 将当前的路径的注册表值转表
   * @param HKEY
   * @param Path
   */
  get listRegistrPath() {
    return this.list;
  },
  /**
   * 枚举键值
   * @param HKEY 根路径
   * @param Path 路径
   * @time 0.06689453125 ms
   * @returns
   */
  get enumRegistrKey() {
    return this.keys;
  },
  /**
   * 删除数据
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.076904296875 ms
   * @returns
   */
  get removeStringRegKey() {
    return this.remove;
  },
  /**
   * 设置键值对
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @param Value 数据
   * @time 2.02392578125 ms
   * @returns
   */
  get setRegistrKey() {
    return this.set;
  },
  /**
   * 获取内容(文本)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.108ms
   * @returns
   */
  get getStringRegKey() {
    return this.get;
  },
  /**
   * 获取内容(数字)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.10888671875 ms
   * @returns
   */
  getNumberRegKey: (HKEY, Path, key) => {
    return getNumberRegKey(HKEY, Path, key);
  },
  /**
   * 创建新的路径
   * @param HKEY 根路径
   * @param Path 路径
   * @time 2.02392578125 ms
   * @returns
   */
  get createPathRegistr() {
    return this.create;
  },
  /**
   * 获取内容(二进制 Buffer)
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @time 0.06787109375 ms
   * @returns
   */
  getRegistrBuffValue: (HKEY, Path, key) => {
    return getRegistrBuffValue(HKEY, Path, key);
  },
  /**
   * 打开一个注册表路径并返回一些实用方法
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @returns
   */
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
function _popen(cmd) {
  return native.popen(ref.string(cmd));
}
function hasMutex(MutexName) {
  return native.hasMutex(ref.string(MutexName));
}
function createMutex(MutexName) {
  return native.createMutex(ref.string(MutexName));
}
function popen(cmd) {
  return native.popen(ref.string(cmd));
}
function getAllEnv() {
  return native.getAllEnv();
}
function getenv(key) {
  return native.getenv(ref.string(key));
}
function getUDPPortProcessID(Port) {
  let pid = native.getUDPPortProcessID(ref.int(Port));
  return pid ? pid : null;
}
function putenv(key, data) {
  return native.putenv(ref.string(key), ref.string(Array.isArray(data) ? data.join(";") : data));
}
function getTCPPortProcessID(Port) {
  let pid = native.getTCPPortProcessID(ref.int(Port));
  return pid ? pid : null;
}
function findWindow(className, titleName) {
  return native.findWindow(
    typeof className == "string" ? ref.string(className) : null,
    typeof titleName == "string" ? ref.string(titleName) : null
  );
}
function findWindowEx(hWndParent, hWndChildAfter, className, titleName) {
  return native.findWindowEx(
    !!hWndParent ? ref.int(className) : null,
    !!hWndChildAfter ? ref.int(titleName) : null,
    typeof className == "string" ? ref.string(className) : null,
    typeof titleName == "string" ? ref.string(titleName) : null
  );
}
var Registr = registr;
var hmc = {
  findWindowEx,
  findWindow,
  getAllEnv,
  getenv,
  getUDPPortProcessID,
  getTCPPortProcessID,
  putenv,
  createMutex,
  hasMutex,
  Auto,
  Clipboard,
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
  _popen,
  alert,
  analysisDirectPath,
  captureBmpToFile,
  clearClipboard,
  closedHandle,
  confirm,
  createDirSymlink,
  createHardLink,
  createPathRegistr,
  createSymlink,
  deleteFile,
  desc,
  enumAllProcessHandle,
  enumChildWindows,
  enumProcessHandle,
  enumRegistrKey,
  formatVolumePath,
  freePort,
  getAllWindows,
  getAllWindowsHandle,
  getBasicKeys,
  getClipboardFilePaths,
  getClipboardSequenceNumber,
  getClipboardText,
  getColor,
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
  getModulePathList,
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
  getProcessParentProcessID,
  getProcessThreadList,
  getProcessidFilePath,
  getRegistrBuffValue,
  getRegistrDword,
  getRegistrQword,
  getShortcutLink,
  getStringRegKey,
  getSubProcessID,
  getSystemIdleTime,
  getSystemMenu,
  getSystemMetricsLen,
  getTrayList,
  getUsbDevsInfo,
  getVolumeList,
  getWebView2Info,
  getWindowClassName,
  getWindowRect,
  getWindowStyle,
  getWindowTitle,
  hasKeyActivate,
  hasPortTCP,
  hasPortUDP,
  hasProcess,
  hasRegistrKey,
  hasWebView2,
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
  popen,
  powerControl,
  processWatchdog,
  ref,
  registr,
  removeStringRegKey,
  removeStringRegKeyWalk,
  removeStringRegValue,
  removeStringTree,
  rightClick,
  sendBasicKeys,
  sendKeyboard,
  sendKeyboardSequence,
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
  setWindowIconForExtract,
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
};
var hmc_default = hmc;
process.on("exit", function() {
  if (SetIohook) {
    native.unHookMouse();
    native.unKeyboardHook();
    native.clearEnumAllProcessList();
    native.clearEnumProcessHandle();
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
  _KeyboardcodeComparisonTable,
  _KeyboardcodeEmenList,
  _popen,
  alert,
  analysisDirectPath,
  captureBmpToFile,
  clearClipboard,
  closedHandle,
  confirm,
  createDirSymlink,
  createHardLink,
  createMutex,
  createPathRegistr,
  createSymlink,
  deleteFile,
  desc,
  enumAllProcessHandle,
  enumChildWindows,
  enumProcessHandle,
  enumRegistrKey,
  findWindow,
  findWindowEx,
  formatVolumePath,
  freePort,
  getAllEnv,
  getAllWindows,
  getAllWindowsHandle,
  getBasicKeys,
  getClipboardFilePaths,
  getClipboardSequenceNumber,
  getClipboardText,
  getColor,
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
  getModulePathList,
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
  getProcessParentProcessID,
  getProcessThreadList,
  getProcessidFilePath,
  getRegistrBuffValue,
  getRegistrDword,
  getRegistrQword,
  getShortcutLink,
  getStringRegKey,
  getSubProcessID,
  getSystemIdleTime,
  getSystemMenu,
  getSystemMetricsLen,
  getTCPPortProcessID,
  getTrayList,
  getUDPPortProcessID,
  getUsbDevsInfo,
  getVolumeList,
  getWebView2Info,
  getWindowClassName,
  getWindowRect,
  getWindowStyle,
  getWindowTitle,
  getenv,
  hasKeyActivate,
  hasMutex,
  hasPortTCP,
  hasPortUDP,
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
  popen,
  powerControl,
  processWatchdog,
  putenv,
  ref,
  registr,
  removeStringRegKey,
  removeStringRegKeyWalk,
  removeStringRegValue,
  removeStringTree,
  rightClick,
  sendBasicKeys,
  sendKeyboard,
  sendKeyboardSequence,
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
  setWindowIconForExtract,
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
