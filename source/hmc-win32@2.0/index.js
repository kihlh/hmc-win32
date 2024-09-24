"use strict";
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __esm = (fn, res) => function __init() {
  return fn && (res = (0, fn[__getOwnPropNames(fn)[0]])(fn = 0)), res;
};
var __export = (target, all) => {
  for (var name in all)
    __defProp(target, name, { get: all[name], enumerable: true });
};
var __copyProps = (to, from, except, desc) => {
  if (from && typeof from === "object" || typeof from === "function") {
    for (let key of __getOwnPropNames(from))
      if (!__hasOwnProp.call(to, key) && key !== except)
        __defProp(to, key, { get: () => from[key], enumerable: !(desc = __getOwnPropDesc(from, key)) || desc.enumerable });
  }
  return to;
};
var __toCommonJS = (mod) => __copyProps(__defProp({}, "__esModule", { value: true }), mod);
var __accessCheck = (obj, member, msg) => {
  if (!member.has(obj))
    throw TypeError("Cannot " + msg);
};
var __privateGet = (obj, member, getter) => {
  __accessCheck(obj, member, "read from private field");
  return getter ? getter.call(obj) : member.get(obj);
};
var __privateAdd = (obj, member, value) => {
  if (member.has(obj))
    throw TypeError("Cannot add the same private member more than once");
  member instanceof WeakSet ? member.add(obj) : member.set(obj, value);
};
var __privateSet = (obj, member, value, setter) => {
  __accessCheck(obj, member, "write to private field");
  setter ? setter.call(obj, value) : member.set(obj, value);
  return value;
};
var __privateMethod = (obj, member, method) => {
  __accessCheck(obj, member, "access private method");
  return method;
};

// source/hmc-win32@2.0/source/main/promiseEval.ts
var promiseEval_exports = {};
__export(promiseEval_exports, {
  HMC_PROMISEEVAL_TASK_TYPE: () => HMC_PROMISEEVAL_TASK_TYPE,
  promiseEvalTask: () => promiseEvalTask
});
var main, HMC_PROMISEEVAL_TASK_TYPE, HMC_PromiseeEvalTask, promiseEvalTask;
var init_promiseEval = __esm({
  "source/hmc-win32@2.0/source/main/promiseEval.ts"() {
    "use strict";
    main = (init_main(), __toCommonJS(main_exports));
    HMC_PROMISEEVAL_TASK_TYPE = /* @__PURE__ */ ((HMC_PROMISEEVAL_TASK_TYPE2) => {
      HMC_PROMISEEVAL_TASK_TYPE2[HMC_PROMISEEVAL_TASK_TYPE2["getClipboardFilePaths2"] = 1] = "getClipboardFilePaths2";
      HMC_PROMISEEVAL_TASK_TYPE2[HMC_PROMISEEVAL_TASK_TYPE2["captureBmp2"] = 2] = "captureBmp2";
      HMC_PROMISEEVAL_TASK_TYPE2[HMC_PROMISEEVAL_TASK_TYPE2["closeWindow2"] = 3] = "closeWindow2";
      HMC_PROMISEEVAL_TASK_TYPE2[HMC_PROMISEEVAL_TASK_TYPE2["getClipboardText2"] = 5] = "getClipboardText2";
      return HMC_PROMISEEVAL_TASK_TYPE2;
    })(HMC_PROMISEEVAL_TASK_TYPE || {});
    HMC_PromiseeEvalTask = class {
      constructor() {
        this.async = {};
        this.sync = {};
        const TASK_TYPE_LIST = Object.keys(HMC_PROMISEEVAL_TASK_TYPE);
        for (let index = 0; index < TASK_TYPE_LIST.length; index++) {
          const TASK_TYPE = TASK_TYPE_LIST[index];
          const TASK_ID = HMC_PROMISEEVAL_TASK_TYPE[TASK_TYPE];
          this.async[TASK_TYPE] = (...arg) => {
            var _a;
            try {
              if (!((_a = main.Native.native) == null ? void 0 : _a.HMC_PromiseEval)) {
                return Promise.reject(main.HMC2_MODE.HMCNotPlatform);
              }
              if (arg.length >= 1) {
                return main.Native.native.HMC_PromiseEval(TASK_ID, ...arg);
              }
              return main.Native.native.HMC_PromiseEval(TASK_ID);
            } catch (error) {
              return Promise.reject(error);
            }
          };
          this.sync[TASK_TYPE] = (...arg) => {
            var _a;
            if (!((_a = main.Native.native) == null ? void 0 : _a.HMC_PromiseEvalSync)) {
              return null;
            }
            if (arg.length >= 1) {
              return main.Native.native.HMC_PromiseEvalSync(TASK_ID, ...arg) || null;
            }
            return main.Native.native.HMC_PromiseEvalSync(TASK_ID);
          };
          if (!this[TASK_TYPE]) {
            this[TASK_TYPE] = this.async[TASK_TYPE];
          }
          const KEY = "".concat(TASK_TYPE, "Sync");
          if (!this[KEY]) {
            this[KEY] = this.sync[TASK_TYPE];
          }
        }
      }
      async getClipboardFilePaths2() {
        var _a, _b;
        if (!((_a = promiseEvalTask == null ? void 0 : promiseEvalTask.async) == null ? void 0 : _a.getClipboardFilePaths2)) {
          return Promise.resolve([]);
        }
        const data = await (((_b = promiseEvalTask == null ? void 0 : promiseEvalTask.async) == null ? void 0 : _b.getClipboardFilePaths2()) || null);
        if (typeof data == "string") {
          const temp = data ? data == null ? void 0 : data.split("\0") : [];
          if (temp.length && temp.at(-1) == "")
            temp.pop();
          return temp;
        }
        return data || [];
      }
      getClipboardFilePaths2Sync() {
        var _a, _b;
        if (!((_a = promiseEvalTask == null ? void 0 : promiseEvalTask.sync) == null ? void 0 : _a.getClipboardFilePaths2)) {
          return [];
        }
        const data = ((_b = promiseEvalTask == null ? void 0 : promiseEvalTask.sync) == null ? void 0 : _b.getClipboardFilePaths2()) || null;
        if (typeof data == "string") {
          const temp = data ? data == null ? void 0 : data.split("\0") : [];
          if (temp.length && temp.at(-1) == "")
            temp.pop();
          return temp;
        }
        return data || [];
      }
    };
    promiseEvalTask = new HMC_PromiseeEvalTask();
  }
});

// source/hmc-win32@2.0/source/main/util.ts
var util_exports = {};
__export(util_exports, {
  ref: () => ref
});
var path, ref;
var init_util = __esm({
  "source/hmc-win32@2.0/source/main/util.ts"() {
    "use strict";
    path = require("path");
    ref = {
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
        if (typeof bool == "string") {
          const TEMP = bool.toUpperCase();
          if (TEMP == "0" || TEMP == "FALSE" || TEMP == "NULL" || TEMP == "NONE") {
            return false;
          }
          return true;
        }
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
       * 格式化数字为float(强制) 浮点
       * @param Num
       * @returns
       */
      float(Num) {
        if (!Num)
          return 0;
        if (typeof Num == "object" && Num instanceof Number) {
          Num = Num == null ? void 0 : Num.valueOf();
        }
        if (typeof Num == "string") {
          Num = parseFloat(Num);
          if (isNaN(Num))
            return 0;
          if (Num >= Infinity) {
            Num = 1e15;
          }
          if (Num <= -Infinity) {
            Num = -1e15;
          }
          return Num;
        }
        if (typeof Num == "number" && !isNaN(Num))
          return Num;
        if (Num && typeof Num == "boolean")
          Num = 1;
        if (!Num && typeof Num == "boolean")
          Num = 0;
        if (Num >= Infinity) {
          Num = 1e15;
        }
        if (Num <= -Infinity) {
          Num = -1e15;
        }
        return Num;
      },
      /**
       * 格式化数字为int(强制) 取整
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
      }
    };
  }
});

// source/hmc-win32@2.0/source/main/shell.ts
var shell_exports = {};
__export(shell_exports, {
  Shell: () => Shell
});
var main2, util, PromiseEval, ref2, _Startup, _initialize, initialize_fn, _root, _pathRun, _pathRunOnce, StartupConstructor, Shell;
var init_shell = __esm({
  "source/hmc-win32@2.0/source/main/shell.ts"() {
    "use strict";
    main2 = (init_main(), __toCommonJS(main_exports));
    util = (init_util(), __toCommonJS(util_exports));
    PromiseEval = (init_promiseEval(), __toCommonJS(promiseEval_exports));
    ({ ref: ref2 } = util);
    StartupConstructor = class {
      constructor() {
        __privateAdd(this, _initialize);
        __privateAdd(this, _Startup, null);
        __privateAdd(this, _root, "HKEY_LOCAL_MACHINE");
        __privateAdd(this, _pathRun, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
        __privateAdd(this, _pathRunOnce, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce");
      }
      has(keyName) {
        var _a;
        __privateMethod(this, _initialize, initialize_fn).call(this);
        return ((_a = __privateGet(this, _Startup)) == null ? void 0 : _a.has(ref2.string(keyName))) || false;
      }
      hasOnce(keyName) {
        var _a;
        __privateMethod(this, _initialize, initialize_fn).call(this);
        return ((_a = __privateGet(this, _Startup)) == null ? void 0 : _a.hasOnce(ref2.string(keyName))) || false;
      }
      remove(keyName) {
        var _a;
        __privateMethod(this, _initialize, initialize_fn).call(this);
        return ((_a = __privateGet(this, _Startup)) == null ? void 0 : _a.remove(ref2.string(keyName))) || false;
      }
      removeOnce(keyName) {
        var _a;
        __privateMethod(this, _initialize, initialize_fn).call(this);
        return ((_a = __privateGet(this, _Startup)) == null ? void 0 : _a.removeOnce(ref2.string(keyName))) || false;
      }
      set(keyName, path2, cmd) {
        var _a;
        __privateMethod(this, _initialize, initialize_fn).call(this);
        return ((_a = __privateGet(this, _Startup)) == null ? void 0 : _a.set(ref2.string(keyName), ref2.string(path2), ref2.string(cmd || ""))) || false;
      }
      setOnce(keyName, path2, cmd) {
        var _a;
        __privateMethod(this, _initialize, initialize_fn).call(this);
        return ((_a = __privateGet(this, _Startup)) == null ? void 0 : _a.setOnce(ref2.string(keyName), ref2.string(path2), ref2.string(cmd || ""))) || false;
      }
      enum() {
        const obj = {};
        return obj;
      }
      enumOnce() {
        const obj = {};
        return obj;
      }
      keys() {
        return [];
      }
      keysOnce() {
        return [];
      }
    };
    _Startup = new WeakMap();
    _initialize = new WeakSet();
    initialize_fn = function() {
      if (!__privateGet(this, _Startup) && main2.Native.native.HMC_SHELL_STARTUP_CLASS) {
        __privateSet(this, _Startup, main2.Native.native.HMC_SHELL_STARTUP_CLASS());
      }
    };
    _root = new WeakMap();
    _pathRun = new WeakMap();
    _pathRunOnce = new WeakMap();
    ((Shell3) => {
      Shell3.Startup = new StartupConstructor();
      Shell3.captureBmp2 = PromiseEval.promiseEvalTask.captureBmp2;
      Shell3.captureBmp2Sync = PromiseEval.promiseEvalTask.captureBmp2Sync;
    })(Shell || (Shell = {}));
  }
});

// source/hmc-win32@2.0/source/main/auto.ts
var auto_exports = {};
__export(auto_exports, {
  HmcKeyboardClass: () => HmcKeyboardClass,
  HmcMouseClass: () => HmcMouseClass,
  setLimitMouseRange: () => setLimitMouseRange
});
function setLimitMouseRange(ms, x, y, right = 1, bottom = 1) {
  ms = Math.abs(ref3.int(ms));
  x = Math.abs(ref3.int(x));
  y = Math.abs(ref3.int(y));
  right = Math.abs(ref3.int(right)) || 1;
  bottom = Math.abs(ref3.int(bottom)) || 1;
  if (ms > 30 * 1e3 || ms < 30) {
    throw new Error("The range is only allowed from 31 milliseconds to 30 seconds (31ms-30000).");
  }
  HmcMouseClass.setLimitMouseRange(ms, x, y, right, bottom);
  const res = {
    ms,
    x,
    y,
    right,
    bottom,
    closed: (() => {
      setTimeout(() => {
        res.closed = HmcMouseClass.hasLimitMouseRangeWorker();
      }, ms + 80);
      return false;
    })(),
    /**
     * 停止本次
     * @returns 
     */
    close() {
      return HmcMouseClass.stopLimitMouseRangeWorker();
    },
    // 停止本次
    stop() {
      return this.close();
    },
    /**
     * 是否正在执行中
     * @returns 
     */
    has() {
      return !HmcMouseClass.hasLimitMouseRangeWorker();
    }
  };
  return res;
}
var main3, util2, ref3, _fun, _initialize2, initialize_fn2, HMC_MOUSE_CLASS, HmcMouseClass, _fun2, _initialize3, initialize_fn3, HMC_KEYBOARD_CLASS, HmcKeyboardClass;
var init_auto = __esm({
  "source/hmc-win32@2.0/source/main/auto.ts"() {
    "use strict";
    main3 = (init_main(), __toCommonJS(main_exports));
    util2 = (init_util(), __toCommonJS(util_exports));
    ({ ref: ref3 } = util2);
    HMC_MOUSE_CLASS = class {
      constructor() {
        __privateAdd(this, _initialize2);
        __privateAdd(this, _fun, null);
      }
      initMouseEventHook() {
        var _a;
        __privateMethod(this, _initialize2, initialize_fn2).call(this);
        return ((_a = __privateGet(this, _fun)) == null ? void 0 : _a.initMouseEventHook()) || false;
      }
      isValidHookMouse() {
        var _a;
        __privateMethod(this, _initialize2, initialize_fn2).call(this);
        return ((_a = __privateGet(this, _fun)) == null ? void 0 : _a.isValidHookMouse()) || false;
      }
      getMouseEventListJson() {
        var _a;
        __privateMethod(this, _initialize2, initialize_fn2).call(this);
        return ((_a = __privateGet(this, _fun)) == null ? void 0 : _a.getMouseEventListJson()) || false;
      }
      stopHookMouse() {
        var _a;
        __privateMethod(this, _initialize2, initialize_fn2).call(this);
        return ((_a = __privateGet(this, _fun)) == null ? void 0 : _a.stopHookMouse()) || false;
      }
      setLimitMouseRange(ms, x, y, right, bottom) {
        var _a;
        __privateMethod(this, _initialize2, initialize_fn2).call(this);
        return ((_a = __privateGet(this, _fun)) == null ? void 0 : _a.setLimitMouseRange(ref3.int(ms), ref3.int(x), ref3.int(y), ref3.int(right), ref3.int(bottom))) || false;
      }
      setShakeEventTime(ms) {
        var _a;
        __privateMethod(this, _initialize2, initialize_fn2).call(this);
        return ((_a = __privateGet(this, _fun)) == null ? void 0 : _a.setShakeEventTime(ref3.int(ms))) || false;
      }
      hasLimitMouseRangeWorker() {
        var _a;
        __privateMethod(this, _initialize2, initialize_fn2).call(this);
        return ((_a = __privateGet(this, _fun)) == null ? void 0 : _a.hasLimitMouseRangeWorker()) || false;
      }
      stopLimitMouseRangeWorker() {
        var _a;
        __privateMethod(this, _initialize2, initialize_fn2).call(this);
        return ((_a = __privateGet(this, _fun)) == null ? void 0 : _a.stopLimitMouseRangeWorker()) || false;
      }
    };
    _fun = new WeakMap();
    _initialize2 = new WeakSet();
    initialize_fn2 = function() {
      if (!__privateGet(this, _fun) && main3.Native.native.HMC_MOUSE_CLASS) {
        __privateSet(this, _fun, main3.Native.native.HMC_MOUSE_CLASS());
      }
    };
    HmcMouseClass = new HMC_MOUSE_CLASS();
    HMC_KEYBOARD_CLASS = class {
      constructor() {
        __privateAdd(this, _initialize3);
        __privateAdd(this, _fun2, null);
      }
      initKeyboardEventHook() {
        var _a;
        __privateMethod(this, _initialize3, initialize_fn3).call(this);
        return ((_a = __privateGet(this, _fun2)) == null ? void 0 : _a.initKeyboardEventHook()) || false;
      }
      isValidHookKeyboard() {
        var _a;
        __privateMethod(this, _initialize3, initialize_fn3).call(this);
        return ((_a = __privateGet(this, _fun2)) == null ? void 0 : _a.isValidHookKeyboard()) || false;
      }
      getAllKeyboardEventJson() {
        var _a;
        __privateMethod(this, _initialize3, initialize_fn3).call(this);
        return JSON.parse(((_a = __privateGet(this, _fun2)) == null ? void 0 : _a.getAllKeyboardEventJson()) || "[]");
      }
      stopHookKeyboard() {
        var _a;
        __privateMethod(this, _initialize3, initialize_fn3).call(this);
        return ((_a = __privateGet(this, _fun2)) == null ? void 0 : _a.stopHookKeyboard()) || false;
      }
      hasKeysBasic() {
        var _a;
        __privateMethod(this, _initialize3, initialize_fn3).call(this);
        return ((_a = __privateGet(this, _fun2)) == null ? void 0 : _a.hasKeysBasic()) || {
          "alt": false,
          "ctrl": false,
          "shift": false,
          "win": false
        };
      }
      hasKeyActivate(KeysEvent) {
        var _a;
        __privateMethod(this, _initialize3, initialize_fn3).call(this);
        return ((_a = __privateGet(this, _fun2)) == null ? void 0 : _a.hasKeyActivate(ref3.int(KeysEvent))) || false;
      }
    };
    _fun2 = new WeakMap();
    _initialize3 = new WeakSet();
    initialize_fn3 = function() {
      if (!__privateGet(this, _fun2) && main3.Native.native.HMC_KEYBOARD_CLASS) {
        __privateSet(this, _fun2, main3.Native.native.HMC_KEYBOARD_CLASS());
      }
    };
    HmcKeyboardClass = new HMC_KEYBOARD_CLASS();
  }
});

// source/hmc-win32@2.0/source/main/Process.ts
var Process_exports = {};
__export(Process_exports, {
  Process: () => Process
});
function GetProcessEnvInfo2Clone(pid, command) {
  var _a;
  if (!((_a = main4.Native.native) == null ? void 0 : _a["getProcessEnvInfo2"])) {
    return Promise.resolve(null);
  }
  return main4.Native.native["getProcessEnvInfo2"](pid, command);
}
function GetProcessEnvInfo2SyncClone(pid, command) {
  var _a;
  if (!((_a = main4.Native.native) == null ? void 0 : _a["getProcessEnvInfo2Sync"])) {
    return null;
  }
  return main4.Native.native["getProcessEnvInfo2Sync"](pid, command);
}
var main4, util3, ref4, Process;
var init_Process = __esm({
  "source/hmc-win32@2.0/source/main/Process.ts"() {
    "use strict";
    init_main();
    main4 = (init_main(), __toCommonJS(main_exports));
    util3 = (init_util(), __toCommonJS(util_exports));
    ({ ref: ref4 } = util3);
    ((Process3) => {
      async function getProcessCwdPath2(ProcessID) {
        return GetProcessEnvInfo2Clone(ref4.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_CWD).then((data) => {
          return data || ref4.string(data);
        }).catch((err) => {
          return null;
        });
      }
      Process3.getProcessCwdPath2 = getProcessCwdPath2;
      function getProcessCwdPath2Sync(ProcessID) {
        return GetProcessEnvInfo2SyncClone(ref4.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_CWD);
      }
      Process3.getProcessCwdPath2Sync = getProcessCwdPath2Sync;
      async function getProcessCommandLine2(ProcessID) {
        return GetProcessEnvInfo2Clone(ref4.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_COMMAND).then((data) => {
          return data || ref4.string(data);
        }).catch((err) => {
          return null;
        });
      }
      Process3.getProcessCommandLine2 = getProcessCommandLine2;
      function getProcessCommandLine2Sync(ProcessID) {
        return GetProcessEnvInfo2SyncClone(ref4.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_COMMAND);
      }
      Process3.getProcessCommandLine2Sync = getProcessCommandLine2Sync;
      async function getProcessCpuUsage2(ProcessID) {
        return GetProcessEnvInfo2Clone(ref4.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_CPU_USAGE).then((data) => {
          return ref4.float(data);
        }).catch((err) => {
          return 0;
        });
      }
      Process3.getProcessCpuUsage2 = getProcessCpuUsage2;
      function getProcessCpuUsage2Sync(ProcessID) {
        return ref4.float(GetProcessEnvInfo2SyncClone(ref4.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_CPU_USAGE));
      }
      Process3.getProcessCpuUsage2Sync = getProcessCpuUsage2Sync;
      async function getProcessStartTime2(ProcessID) {
        return GetProcessEnvInfo2Clone(ref4.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_START_TIME).then((data) => {
          return ref4.int(data);
        }).catch((err) => {
          return 0;
        });
      }
      Process3.getProcessStartTime2 = getProcessStartTime2;
      function getProcessStartTime2Sync(ProcessID) {
        return ref4.int(GetProcessEnvInfo2SyncClone(ref4.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_START_TIME));
      }
      Process3.getProcessStartTime2Sync = getProcessStartTime2Sync;
      async function getAllProcessList2(is_execPath) {
        const {
          GET_ALL_PROCESS_LIST_NT,
          GET_ALL_PROCESS_LIST_DETAILS,
          // 
          GET_ALL_PROCESS_LIST_NONE_NAME,
          // 带路径
          GET_ALL_PROCESS_LIST_PID_NAME,
          // sup 列表
          GET_ALL_PROCESS_LIST_SNP,
          GET_ENUM_PROCESSES_LIST
        } = HMC2_MODE.ENV_INFO_COMMAND;
        let SEND_TYPE = typeof is_execPath == "boolean" ? is_execPath ? GET_ALL_PROCESS_LIST_DETAILS : GET_ALL_PROCESS_LIST_NONE_NAME : GET_ALL_PROCESS_LIST_NONE_NAME;
        const INCLUDES_TYPES = [
          GET_ALL_PROCESS_LIST_NT,
          GET_ALL_PROCESS_LIST_DETAILS,
          GET_ALL_PROCESS_LIST_NONE_NAME,
          GET_ALL_PROCESS_LIST_PID_NAME,
          GET_ALL_PROCESS_LIST_SNP,
          GET_ENUM_PROCESSES_LIST
        ];
        if (typeof is_execPath == "number") {
          if (!INCLUDES_TYPES.includes(is_execPath)) {
            return Promise.reject("An illegal call to the function <getAllProcessList2> has been made.");
          }
          SEND_TYPE = is_execPath;
        }
        try {
          const data = await GetProcessEnvInfo2Clone(0, SEND_TYPE);
          const result = JSON.parse(data || "[]");
          if (GET_ALL_PROCESS_LIST_NT == SEND_TYPE || GET_ALL_PROCESS_LIST_SNP == SEND_TYPE) {
            for (let index = 0; index < result.length; index++) {
              const element = result[index];
              element.name = (element == null ? void 0 : element.szExeFile) || (element == null ? void 0 : element.ImageName) || "";
              element.pid = (element == null ? void 0 : element.th32ProcessID) || (element == null ? void 0 : element.UniqueProcessId) || 0;
            }
          }
          return result;
        } catch (err) {
          return [];
        }
      }
      Process3.getAllProcessList2 = getAllProcessList2;
      function getAllProcessList2Sync(is_execPath) {
        const {
          GET_ALL_PROCESS_LIST_NT,
          GET_ALL_PROCESS_LIST_DETAILS,
          // 
          GET_ALL_PROCESS_LIST_NONE_NAME,
          // 带路径
          GET_ALL_PROCESS_LIST_PID_NAME,
          // sup 列表
          GET_ALL_PROCESS_LIST_SNP,
          GET_ENUM_PROCESSES_LIST
        } = HMC2_MODE.ENV_INFO_COMMAND;
        let SEND_TYPE = typeof is_execPath == "boolean" ? is_execPath ? GET_ALL_PROCESS_LIST_DETAILS : GET_ALL_PROCESS_LIST_NONE_NAME : GET_ALL_PROCESS_LIST_NONE_NAME;
        const INCLUDES_TYPES = [
          GET_ALL_PROCESS_LIST_NT,
          GET_ALL_PROCESS_LIST_DETAILS,
          GET_ALL_PROCESS_LIST_NONE_NAME,
          GET_ALL_PROCESS_LIST_PID_NAME,
          GET_ALL_PROCESS_LIST_SNP,
          GET_ENUM_PROCESSES_LIST
        ];
        if (typeof is_execPath == "number") {
          if (!INCLUDES_TYPES.includes(is_execPath)) {
            throw new Error("An illegal call to the function <getAllProcessList2> has been made.");
          }
          SEND_TYPE = is_execPath;
        }
        const result = JSON.parse(GetProcessEnvInfo2SyncClone(0, SEND_TYPE) || "[]");
        if (GET_ALL_PROCESS_LIST_NT == SEND_TYPE || GET_ALL_PROCESS_LIST_SNP == SEND_TYPE) {
          for (let index = 0; index < result.length; index++) {
            const element = result[index];
            element.name = (element == null ? void 0 : element.szExeFile) || (element == null ? void 0 : element.ImageName) || "";
            element.pid = (element == null ? void 0 : element.th32ProcessID) || (element == null ? void 0 : element.UniqueProcessId) || 0;
          }
        }
        return result;
      }
      Process3.getAllProcessList2Sync = getAllProcessList2Sync;
      function getAllProcessListNt2() {
        return getAllProcessList2(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT);
      }
      Process3.getAllProcessListNt2 = getAllProcessListNt2;
      function getAllProcessListNt2Sync() {
        return getAllProcessList2Sync(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT);
      }
      Process3.getAllProcessListNt2Sync = getAllProcessListNt2Sync;
      function getAllProcessListSnp2() {
        return getAllProcessList2(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP);
      }
      Process3.getAllProcessListSnp2 = getAllProcessListSnp2;
      function getAllProcessListSnp2Sync() {
        return getAllProcessList2Sync(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP);
      }
      Process3.getAllProcessListSnp2Sync = getAllProcessListSnp2Sync;
      function getDetailsProcessList2() {
        return getAllProcessList2(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS);
      }
      Process3.getDetailsProcessList2 = getDetailsProcessList2;
      function getDetailsProcessList2Sync() {
        return getAllProcessList2Sync(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS);
      }
      Process3.getDetailsProcessList2Sync = getDetailsProcessList2Sync;
      function enumAllProcess2() {
        return getAllProcessList2(HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST);
      }
      Process3.enumAllProcess2 = enumAllProcess2;
      function enumAllProcess2Sync() {
        return getAllProcessList2Sync(HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST);
      }
      Process3.enumAllProcess2Sync = enumAllProcess2Sync;
      async function isProcessWow64(ProcessID) {
        const bool = await GetProcessEnvInfo2Clone(
          ref4.int(ProcessID || -1),
          HMC2_MODE.ENV_INFO_COMMAND.GET_IS_PROCESS_WOW64
        );
        return !!ref4.int(bool);
      }
      Process3.isProcessWow64 = isProcessWow64;
      function isProcessWow64Sync(ProcessID) {
        const bool = GetProcessEnvInfo2SyncClone(
          ref4.int(ProcessID || -1),
          HMC2_MODE.ENV_INFO_COMMAND.GET_IS_PROCESS_WOW64
        );
        return !!ref4.int(bool);
      }
      Process3.isProcessWow64Sync = isProcessWow64Sync;
      async function existProcess2(ProcessID) {
        const bool = await GetProcessEnvInfo2Clone(
          ref4.int(ProcessID || -1),
          HMC2_MODE.ENV_INFO_COMMAND.GET_EXIST_PROCESS
        );
        return !!ref4.int(bool);
      }
      Process3.existProcess2 = existProcess2;
      function existProcess2Sync(ProcessID) {
        const bool = GetProcessEnvInfo2SyncClone(
          ref4.int(ProcessID || -1),
          HMC2_MODE.ENV_INFO_COMMAND.GET_EXIST_PROCESS
        );
        return !!ref4.int(bool);
      }
      Process3.existProcess2Sync = existProcess2Sync;
      async function getParentProcess2(ProcessID) {
        const long = await GetProcessEnvInfo2Clone(
          ref4.int(ProcessID || -1),
          HMC2_MODE.ENV_INFO_COMMAND.GET_PARENT_PROCESS_ID
        );
        return ref4.int(long || 0) || null;
        ;
      }
      Process3.getParentProcess2 = getParentProcess2;
      function getParentProcess2Sync(ProcessID) {
        return ref4.int(GetProcessEnvInfo2SyncClone(
          ref4.int(ProcessID || -1),
          HMC2_MODE.ENV_INFO_COMMAND.GET_PARENT_PROCESS_ID
        ) || 0) || null;
      }
      Process3.getParentProcess2Sync = getParentProcess2Sync;
      async function getSubProcess2(ProcessID) {
        const anyJSON = await GetProcessEnvInfo2Clone(
          ref4.int(ProcessID || -1),
          HMC2_MODE.ENV_INFO_COMMAND.GET_SUB_PROCESS
        );
        return JSON.parse(anyJSON || "[]");
        ;
      }
      Process3.getSubProcess2 = getSubProcess2;
      function getSubProcess2Sync(ProcessID) {
        return JSON.parse(GetProcessEnvInfo2SyncClone(
          ref4.int(ProcessID || -1),
          HMC2_MODE.ENV_INFO_COMMAND.GET_SUB_PROCESS
        ) || "[]");
      }
      Process3.getSubProcess2Sync = getSubProcess2Sync;
      async function getProcessThreadList2(FindProcessID) {
        const anyJSON = await GetProcessEnvInfo2Clone(
          ref4.int(FindProcessID || -1),
          HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_THREAD_LIST
        );
        return JSON.parse(anyJSON || "[]");
      }
      Process3.getProcessThreadList2 = getProcessThreadList2;
      function getProcessThreadList2Sync(FindProcessID) {
        return JSON.parse(GetProcessEnvInfo2SyncClone(
          ref4.int(FindProcessID || -1),
          HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_THREAD_LIST
        ) || "[]");
      }
      Process3.getProcessThreadList2Sync = getProcessThreadList2Sync;
      async function getExecutableCwdList2(FindProcessID) {
        const anyJSON = await GetProcessEnvInfo2Clone(
          ref4.int(FindProcessID || process.pid),
          HMC2_MODE.ENV_INFO_COMMAND.GET_EXECUTABLE_CWD_LIST
        );
        return JSON.parse(anyJSON || "[]");
      }
      Process3.getExecutableCwdList2 = getExecutableCwdList2;
      function getExecutableCwdList2Sync(FindProcessID) {
        return JSON.parse(GetProcessEnvInfo2SyncClone(
          ref4.int(FindProcessID || process.pid),
          HMC2_MODE.ENV_INFO_COMMAND.GET_EXECUTABLE_CWD_LIST
        ) || "[]");
      }
      Process3.getExecutableCwdList2Sync = getExecutableCwdList2Sync;
      async function getProcessName2(pid, type) {
        if (!main4.Native.native.getProcessName2) {
          if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
            return Promise.resolve([]);
          }
          return Promise.resolve(null);
        }
        const data = await main4.Native.native.getProcessName2(ref4.int(pid), type ? ref4.int(type) : void 0);
        if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
          const data_list = data ? Array.isArray(data) ? data : data == null ? void 0 : data.split("\0") : [];
          return data_list.filter((item) => item);
        }
        return data ? String(data) : null;
      }
      Process3.getProcessName2 = getProcessName2;
      function getProcessName2Sync(pid, type) {
        if (!main4.Native.native.getProcessName2Sync) {
          if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
            return [];
          }
          return null;
        }
        const data = main4.Native.native.getProcessName2Sync(ref4.int(pid), type ? ref4.int(type) : void 0);
        if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
          const data_list = data ? Array.isArray(data) ? data : data == null ? void 0 : data.split("\0") : [];
          return data_list.filter((item) => item);
        }
        return data ? String(data) : null;
      }
      Process3.getProcessName2Sync = getProcessName2Sync;
    })(Process || (Process = {}));
  }
});

// source/hmc-win32@2.0/source/main/index.ts
var main_exports = {};
__export(main_exports, {
  Auto: () => Auto,
  HMC2_MODE: () => HMC2_MODE,
  Native: () => Native,
  Process: () => Process2,
  Shell: () => Shell2,
  Startup: () => Startup,
  ref: () => ref5
});
module.exports = __toCommonJS(main_exports);
var PromiseEval2, ShellMain, AutoMain, UtilMain, ProcessMain, HMC2_MODE, Native, ref5, Auto, Startup, Shell2, Process2;
var init_main = __esm({
  "source/hmc-win32@2.0/source/main/index.ts"() {
    PromiseEval2 = (init_promiseEval(), __toCommonJS(promiseEval_exports));
    ShellMain = (init_shell(), __toCommonJS(shell_exports));
    AutoMain = (init_auto(), __toCommonJS(auto_exports));
    UtilMain = (init_util(), __toCommonJS(util_exports));
    ProcessMain = (init_Process(), __toCommonJS(Process_exports));
    ((HMC2_MODE2) => {
      let FS_MK_LINK_TARGET_TYPE;
      ((FS_MK_LINK_TARGET_TYPE2) => {
        FS_MK_LINK_TARGET_TYPE2[FS_MK_LINK_TARGET_TYPE2["CREATE_DIR_SYMLINK"] = 166] = "CREATE_DIR_SYMLINK";
        FS_MK_LINK_TARGET_TYPE2[FS_MK_LINK_TARGET_TYPE2["CREATE_SYMLINK"] = 168] = "CREATE_SYMLINK";
        FS_MK_LINK_TARGET_TYPE2[FS_MK_LINK_TARGET_TYPE2["CREATE_HARD_LINK"] = 170] = "CREATE_HARD_LINK";
        FS_MK_LINK_TARGET_TYPE2[FS_MK_LINK_TARGET_TYPE2["CREATE_SYMBOLIC_LINK"] = 172] = "CREATE_SYMBOLIC_LINK";
      })(FS_MK_LINK_TARGET_TYPE = HMC2_MODE2.FS_MK_LINK_TARGET_TYPE || (HMC2_MODE2.FS_MK_LINK_TARGET_TYPE = {}));
      HMC2_MODE2.HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
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
      })(MouseKeyName = HMC2_MODE2.MouseKeyName || (HMC2_MODE2.MouseKeyName = {}));
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
      })(MouseKey = HMC2_MODE2.MouseKey || (HMC2_MODE2.MouseKey = {}));
      let ENV_INFO_COMMAND;
      ((ENV_INFO_COMMAND2) => {
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_COMMAND"] = 1] = "GET_COMMAND";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_CWD"] = 2] = "GET_CWD";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_PROCESS_CPU_USAGE"] = 3] = "GET_PROCESS_CPU_USAGE";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_PROCESS_START_TIME"] = 5] = "GET_PROCESS_START_TIME";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_ENUM_PROCESSES_LIST"] = 6] = "GET_ENUM_PROCESSES_LIST";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_ALL_PROCESS_LIST_PID_NAME"] = 7] = "GET_ALL_PROCESS_LIST_PID_NAME";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_ALL_PROCESS_LIST_NONE_NAME"] = 8] = "GET_ALL_PROCESS_LIST_NONE_NAME";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_ALL_PROCESS_LIST_DETAILS"] = 7] = "GET_ALL_PROCESS_LIST_DETAILS";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_ALL_PROCESS_LIST_SNP"] = 10] = "GET_ALL_PROCESS_LIST_SNP";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_ALL_PROCESS_LIST_NT"] = 11] = "GET_ALL_PROCESS_LIST_NT";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_ALL_THREAD_LIST"] = 12] = "GET_ALL_THREAD_LIST";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_PARENT_PROCESS_ID"] = 13] = "GET_PARENT_PROCESS_ID";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_EXIST_PROCESS"] = 15] = "GET_EXIST_PROCESS";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_SUB_PROCESS"] = 19] = "GET_SUB_PROCESS";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_IS_PROCESS_WOW64"] = 20] = "GET_IS_PROCESS_WOW64";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_EXECUTABLE_CWD_LIST"] = 21] = "GET_EXECUTABLE_CWD_LIST";
      })(ENV_INFO_COMMAND = HMC2_MODE2.ENV_INFO_COMMAND || (HMC2_MODE2.ENV_INFO_COMMAND = {}));
      ;
      let GET_PROCESS_NAME_TYPE;
      ((GET_PROCESS_NAME_TYPE2) => {
        GET_PROCESS_NAME_TYPE2[GET_PROCESS_NAME_TYPE2["GET_AII"] = 1] = "GET_AII";
        GET_PROCESS_NAME_TYPE2[GET_PROCESS_NAME_TYPE2["GET_NT"] = 2] = "GET_NT";
        GET_PROCESS_NAME_TYPE2[GET_PROCESS_NAME_TYPE2["GET_SNP"] = 3] = "GET_SNP";
        GET_PROCESS_NAME_TYPE2[GET_PROCESS_NAME_TYPE2["GET_FIND"] = 5] = "GET_FIND";
        GET_PROCESS_NAME_TYPE2[GET_PROCESS_NAME_TYPE2["GET_MODE"] = 7] = "GET_MODE";
        GET_PROCESS_NAME_TYPE2[GET_PROCESS_NAME_TYPE2["GET_DEFAULT"] = 0] = "GET_DEFAULT";
        GET_PROCESS_NAME_TYPE2[GET_PROCESS_NAME_TYPE2["GET_FILE_NAME"] = 8] = "GET_FILE_NAME";
      })(GET_PROCESS_NAME_TYPE = HMC2_MODE2.GET_PROCESS_NAME_TYPE || (HMC2_MODE2.GET_PROCESS_NAME_TYPE = {}));
      ;
    })(HMC2_MODE || (HMC2_MODE = {}));
    Native = (() => {
      const run = {};
      let _BinPath = "";
      let _Native = {};
      let _Loaded = false;
      function LoadNodeBin() {
        try {
          if (process.env) {
            if (process.env.USERNAME == "kiic" && process.env.msvc_dir && process.env.mode) {
              _BinPath = process.env.mode;
              _Native = require(_BinPath);
              return _Native;
            }
          }
          if (_BinPath) {
            _Native = require(_BinPath);
            return _Native;
          } else {
            if (process.arch.match(/^(x32|ia32)$/)) {
              return require("./bin/HMC@Beta_x86.node");
            }
            if (process.arch.match(/^x64$/)) {
              return require("./bin/HMC@Beta_x64.node");
            }
          }
        } catch (s_O) {
        }
        return {};
      }
      Object.defineProperty(run, "native", {
        // configurable:false,
        enumerable: false,
        // writable:false,
        get: function() {
          if (!_Loaded && !_BinPath) {
            if (process.arch.match(/^(x32|ia32)$/)) {
              _BinPath = "./bin/HMC@Beta_x86.node";
            }
            if (process.arch.match(/^x64$/)) {
              _BinPath = "./bin/HMC@Beta_x64.node";
            }
          }
          if (!_Loaded) {
            _Native = LoadNodeBin();
          }
          return _Native;
        },
        set(v) {
        }
      });
      return run;
    })();
    ({ ref: ref5 } = UtilMain);
    ((Auto2) => {
      ({ setLimitMouseRange: Auto2.setLimitMouseRange } = AutoMain);
    })(Auto || (Auto = {}));
    Startup = ShellMain.Shell.Startup;
    Shell2 = ShellMain.Shell;
    Process2 = ProcessMain.Process;
  }
});
init_main();
// Annotate the CommonJS export names for ESM import in node:
0 && (module.exports = {
  Auto,
  HMC2_MODE,
  Native,
  Process,
  Shell,
  Startup,
  ref
});
