var __getOwnPropNames = Object.getOwnPropertyNames;
var __require = /* @__PURE__ */ ((x) => typeof require !== "undefined" ? require : typeof Proxy !== "undefined" ? new Proxy(x, {
  get: (a, b) => (typeof require !== "undefined" ? require : a)[b]
}) : x)(function(x) {
  if (typeof require !== "undefined")
    return require.apply(this, arguments);
  throw new Error('Dynamic require of "' + x + '" is not supported');
});
var __commonJS = (cb, mod) => function __require2() {
  return mod || (0, cb[__getOwnPropNames(cb)[0]])((mod = { exports: {} }).exports, mod), mod.exports;
};
var __async = (__this, __arguments, generator) => {
  return new Promise((resolve, reject) => {
    var fulfilled = (value) => {
      try {
        step(generator.next(value));
      } catch (e) {
        reject(e);
      }
    };
    var rejected = (value) => {
      try {
        step(generator.throw(value));
      } catch (e) {
        reject(e);
      }
    };
    var step = (x) => x.done ? resolve(x.value) : Promise.resolve(x.value).then(fulfilled, rejected);
    step((generator = generator.apply(__this, __arguments)).next());
  });
};

// node_modules/argv-split/split.js
var require_split = __commonJS({
  "node_modules/argv-split/split.js"(exports, module) {
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
    module.exports = split;
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
var path = __require("path");
var child_process = __require("child_process");
var net = __require("net");
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
  let Native = process.platform == "win32" ? __require("./HMC.node") : (() => {
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
  (function() {
    return __async(this, null, function* () {
      while (Next) {
        yield Sleep(NextAwaitMs);
        let clipboardSequenceNumber = getClipboardSequenceNumber();
        if (oidClipboardSequenceNumber !== clipboardSequenceNumber) {
          if (CallBack)
            CallBack();
        }
        oidClipboardSequenceNumber = clipboardSequenceNumber;
      }
    });
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
  (function() {
    return __async(this, null, function* () {
      while (Next) {
        yield Sleep(NextAwaitMs);
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
    });
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
      (resolve, reject) => __async(this, null, function* () {
        while (true) {
          if (quit)
            break;
          yield Sleep(awaitMs || 500);
          if (!hasProcess(ref.int(ProcessID))) {
            resolve(void 0);
            break;
          }
        }
      })
    );
    Prom.quit = function() {
      quit = true;
    };
    return Prom;
  }
  (() => __async(this, null, function* () {
    while (true) {
      yield Sleep(awaitMs || 500);
      if (!hasProcess(ref.int(ProcessID))) {
        typeof callback == "function" && callback();
        break;
      }
    }
  }))();
  return {
    quit: function() {
      quit = true;
    }
  };
}
function WatchWindowPoint(callback, awaitMs) {
  let quit = false;
  let oidPoint = native.getPointWindow() || 0;
  (() => __async(this, null, function* () {
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
      yield Sleep(awaitMs || 350);
    }
  }))();
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
  (() => __async(this, null, function* () {
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
      yield Sleep(awaitMs || 350);
    }
  }))();
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
function Sleep(awaitTime, Sync) {
  return __async(this, null, function* () {
    if (Sync) {
      return sleep(ref.int(awaitTime));
    }
    return new Promise(
      (resolve) => setTimeout(resolve, ref.int(awaitTime))
    );
  });
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
  }
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
  hasKeyActivate
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
  }
};
var hmc = {
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
  windowJitter
};
export {
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
  windowJitter
};
