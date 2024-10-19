process.env.HMC___CREATE__REQUIRE___URL__ESM_MODE_PATH=import.meta.url;
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __require = /* @__PURE__ */ ((x) => typeof require !== "undefined" ? require : typeof Proxy !== "undefined" ? new Proxy(x, {
  get: (a, b) => (typeof require !== "undefined" ? require : a)[b]
}) : x)(function(x) {
  if (typeof require !== "undefined")
    return require.apply(this, arguments);
  throw new Error('Dynamic require of "' + x + '" is not supported');
});
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

// source/hmc-win32@2.0/source/main/util.ts
var util_exports = {};
__export(util_exports, {
  ref: () => ref
});
import _path from "path";
var ref;
var init_util = __esm({
  "source/hmc-win32@2.0/source/main/util.ts"() {
    "use strict";
    ((ref6) => {
      function path(Str) {
        return _path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, "\0");
      }
      ref6.path = path;
      function bool(bool2) {
        if (bool2 && typeof bool2 == "string") {
          const TEMP = bool2.toUpperCase();
          if (TEMP == "0" || TEMP == "FALSE" || TEMP == "NULL" || TEMP == "NONE") {
            return false;
          }
          return true;
        }
        return bool2 ? true : false;
      }
      ref6.bool = bool;
      function string(Str) {
        if (!Str && typeof Str == "object") {
          return "null";
        }
        if (typeof Str == "object" && Str instanceof String) {
          Str = (Str == null ? void 0 : Str.toString()) || String(Str);
          return Str;
        }
        if (typeof Str == "object" || Array.isArray(Str)) {
          try {
            return JSON.stringify(Str);
          } catch (error) {
            return String(Str);
          }
        }
        if (typeof Str == "number") {
          Str = String(Str);
          return Str;
        }
        if (typeof Str == "boolean") {
          Str = Str ? "true" : "false";
          return Str;
        }
        return String(Str || "");
      }
      ref6.string = string;
      function float(Num) {
        if (!Num)
          return 0;
        if (typeof Num == "object" && Num instanceof Number) {
          Num = Num == null ? void 0 : Num.valueOf();
        }
        const MAX_VALUE = Math.pow(2, 31);
        const MIN_VALUE = -Math.pow(2, 31);
        if (typeof Num == "string") {
          Num = parseFloat(Num);
          if (isNaN(Num))
            return 0;
          if (Num >= MAX_VALUE) {
            Num = parseFloat(string(MAX_VALUE - 1) + ".999");
          }
          if (Num <= MIN_VALUE) {
            Num = parseFloat(string(MIN_VALUE) + ".999");
          }
          return Num;
        }
        if (typeof Num == "number" && !isNaN(Num))
          return Num;
        if (Num && typeof Num == "boolean")
          Num = 1;
        if (!Num && typeof Num == "boolean")
          Num = 0;
        if (Num >= MAX_VALUE) {
          Num = parseFloat(string(MAX_VALUE - 1) + ".999");
        }
        if (Num <= MIN_VALUE) {
          Num = parseFloat(string(MIN_VALUE) + ".999");
        }
        return Num;
      }
      ref6.float = float;
      function int(Num) {
        if (!Num)
          return 0;
        if (typeof Num == "object" && Num instanceof Number) {
          Num = Num == null ? void 0 : Num.valueOf();
        }
        if (typeof Num == "bigint") {
          Num = Number(Num);
        }
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num))
          return Num;
        if (Num && typeof Num == "boolean")
          Num = 1;
        if (!Num && typeof Num == "boolean")
          Num = 0;
        const MAX_VALUE = Math.pow(2, 31);
        const MIN_VALUE = -Math.pow(2, 31);
        if (Num >= MAX_VALUE) {
          Num = MAX_VALUE - 1;
        }
        if (Num <= MIN_VALUE) {
          Num = MIN_VALUE;
        }
        return Num;
      }
      ref6.int = int;
      function long(Num) {
        if (!Num)
          return 0;
        if (typeof Num == "object" && Num instanceof Number) {
          Num = Num == null ? void 0 : Num.valueOf();
        }
        if (typeof Num == "bigint") {
          Num = Number(Num);
        }
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num))
          return Num;
        if (Num && typeof Num == "boolean")
          Num = 1;
        if (!Num && typeof Num == "boolean")
          Num = 0;
        const MAX_VALUE = Math.pow(2, 63);
        const MIN_VALUE = -Math.pow(2, 63);
        if (Num >= MAX_VALUE) {
          Num = MAX_VALUE - 1;
        }
        if (Num <= MIN_VALUE) {
          Num = MIN_VALUE;
        }
        return Num;
      }
      ref6.long = long;
      function stringArray(array) {
        let dataList = [];
        if (Array.isArray(array)) {
          for (let index = 0; index < array.length; index++) {
            const cout = array[index];
            dataList.push(string(cout));
          }
        }
        if (array instanceof Set) {
          for (const cout of array) {
            dataList.push(string(cout));
          }
        }
        return dataList;
      }
      ref6.stringArray = stringArray;
      function is_stringArray(array) {
        if (Array.isArray(array)) {
          for (let index = 0; index < array.length; index++) {
            const cout = array[index];
            if (typeof cout != "string") {
              return false;
            }
          }
        } else {
          return false;
        }
        return true;
      }
      ref6.is_stringArray = is_stringArray;
      function convertMultiStringArray(input) {
        if (typeof input == "string") {
          const temp = input.replace(/[\0]+$/, "").split("\0");
          for (let index = 0; index < 2; index++) {
            if (temp.at(-1)) {
              return temp;
            }
            temp && temp.pop();
          }
        }
        if (Array.isArray(input)) {
          let temp = "";
          for (let index = 0; index < input.length; index++) {
            const element = input[index];
            temp += string(element) + "\0";
          }
          return temp.replace(/[\0]+$/, "\0\0");
        }
        if (input && input instanceof Set) {
          let temp = "";
          for (const element of input) {
            temp += string(element) + "\0";
          }
          return temp.replace(/[\0]+$/, "\0\0");
        }
        return [];
      }
      ref6.convertMultiStringArray = convertMultiStringArray;
      function intArray(array) {
        let dataList = [];
        if (Array.isArray(array)) {
          for (let index = 0; index < array.length; index++) {
            const cout = array[index];
            dataList.push(int(cout));
          }
        }
        if (array instanceof Set) {
          for (const cout of array) {
            dataList.push(int(cout));
          }
        }
        return dataList;
      }
      ref6.intArray = intArray;
      function formatArgv(...argv) {
        let argvs = [];
        let argvsResult = [];
        for (let index = 0; index < argv.length; index++) {
          const cout = argv[index];
          if (Array.isArray(cout)) {
            for (let cout_index = 0; cout_index < cout.length; cout_index++) {
              const cout2 = cout[cout_index];
              argvs.push(string(cout2));
            }
            continue;
          }
          argvs.push(string(cout));
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
      }
      ref6.formatArgv = formatArgv;
      function concatBuff(buffList) {
        let buffSize = 0;
        for (let index = 0; index < buffList.length; index++) {
          const buff = buffList[index];
          buffSize = buffSize + buff.byteLength;
        }
        let ResponseData = Buffer.concat([...buffList], buffSize);
        return ResponseData;
      }
      ref6.concatBuff = concatBuff;
      function JSONP(..._input) {
        const result = {
          input: _input[0],
          is_or: _input.length >= 2,
          orData: _input.length >= 2 ? _input[1] : null
        };
        const { input } = result;
        if (input && (typeof input == "object" || Array.isArray(input))) {
          return input;
        }
        try {
          return JSON.parse(input);
        } catch (error) {
        }
        if (result.is_or) {
          return result.orData;
        }
        return null;
      }
      ref6.JSONP = JSONP;
    })(ref || (ref = {}));
  }
});

// source/hmc-win32@2.0/source/main/registr.ts
var registr_exports = {};
__export(registr_exports, {
  Registr: () => Registr
});
var util, main, _Native, Native, Registr;
var init_registr = __esm({
  "source/hmc-win32@2.0/source/main/registr.ts"() {
    "use strict";
    init_main();
    util = (init_util(), __toCommonJS(util_exports));
    main = (init_main(), __toCommonJS(main_exports));
    _Native = (init_Native(), __toCommonJS(Native_exports));
    ({ Native } = _Native);
    ((Registr3) => {
      const { ref: ref6 } = util;
      async function GetRegistrEnvInfo(ENV_INFO_COMMAND, HKey, ...aegs) {
        var _a;
        const _GetRegistrEnvInfo = (_a = Native.native) == null ? void 0 : _a.GetRegistrEnvInfo;
        if (!_GetRegistrEnvInfo)
          return Promise.reject("not func -> GetRegistrEnvInfo");
        return _GetRegistrEnvInfo(ENV_INFO_COMMAND, HKey, ...aegs);
      }
      function GetRegistrEnvInfoSync(ENV_INFO_COMMAND, HKey, ...aegs) {
        var _a;
        const _GetRegistrEnvInfoSync = (_a = Native.native) == null ? void 0 : _a.GetRegistrEnvInfoSync;
        if (!_GetRegistrEnvInfoSync)
          return null;
        return _GetRegistrEnvInfoSync(ENV_INFO_COMMAND, HKey, ...aegs);
      }
      async function getRegistrQword2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_QWORD,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {
          return BigInt(data);
        }
        return null;
      }
      Registr3.getRegistrQword2 = getRegistrQword2;
      async function setRegistrQword2(HKey, SubKey, key, Qword) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_QWORD,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          ref6.int(Qword || 0)
        );
        return ref6.bool(data);
      }
      Registr3.setRegistrQword2 = setRegistrQword2;
      async function getRegistrDword2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_DWORD,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {
          return ref6.long(data);
        }
        return null;
      }
      Registr3.getRegistrDword2 = getRegistrDword2;
      async function setRegistrDword2(HKey, SubKey, key, Dword) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_DWORD,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          ref6.long(Dword)
        );
        return ref6.bool(data);
      }
      Registr3.setRegistrDword2 = setRegistrDword2;
      async function getRegistrString2(HKey, SubKey, key, expand) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          expand ? true : false
        );
        return typeof data == "string" ? data : null;
      }
      Registr3.getRegistrString2 = getRegistrString2;
      async function setRegistrString2(HKey, SubKey, key, String2, expand) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          ref6.string(String2 || ""),
          expand ? true : false
        );
        return ref6.bool(data);
      }
      Registr3.setRegistrString2 = setRegistrString2;
      async function getRegistrKeys2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_KEYS,
          ref6.string(HKey),
          ref6.string(SubKey),
          ""
        );
        return data ? JSON.parse(String(data)) : null;
      }
      Registr3.getRegistrKeys2 = getRegistrKeys2;
      async function getRegistrStringList2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING_LIST,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        if (typeof data == "string") {
          if (data[0] == "[") {
            return ref6.JSONP(data);
          }
          if (data.includes("\0")) {
            const temp = data.split(/\0+/);
            if (temp.at(-1) == "") {
              temp.pop();
            }
            return temp;
          }
        }
        return Array.isArray(data) ? data : null;
      }
      Registr3.getRegistrStringList2 = getRegistrStringList2;
      async function setRegistrStringList2(HKey, SubKey, key, StringList) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING_LIST,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          Array.isArray(StringList) ? ref6.stringArray(StringList) : ref6.convertMultiStringArray(ref6.string(StringList || "")) || []
        );
        return ref6.bool(data);
      }
      Registr3.setRegistrStringList2 = setRegistrStringList2;
      async function getRegistrBuffer2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_BUFFER,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return Buffer.isBuffer(data) ? data : null;
      }
      Registr3.getRegistrBuffer2 = getRegistrBuffer2;
      async function setRegistrBuffer2(HKey, SubKey, key, Buff) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_BUFFER,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          Buff
        );
        return ref6.bool(data);
      }
      Registr3.setRegistrBuffer2 = setRegistrBuffer2;
      async function getRegistrValue2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return data ? data : null;
      }
      Registr3.getRegistrValue2 = getRegistrValue2;
      async function copyRegistrValue2(HKey, SourceSubKey, Sourcekey, NewSubKey, Newkey) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_VALUE,
          ref6.string(HKey),
          ref6.string(SourceSubKey),
          ref6.string(Sourcekey || ""),
          ref6.string(NewSubKey || ""),
          ref6.string(Newkey || "")
        );
        return ref6.bool(data);
      }
      Registr3.copyRegistrValue2 = copyRegistrValue2;
      async function copyRegistrFolder2(HKey, SourceSubKey, NewSubKey) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_FOLDER,
          ref6.string(HKey),
          ref6.string(SourceSubKey),
          ref6.string(NewSubKey || "")
        );
        return ref6.bool(data);
      }
      Registr3.copyRegistrFolder2 = copyRegistrFolder2;
      async function setRegistrValue2(HKey, SubKey, key, data, type) {
        const send_data = convertRegistrData(data, type);
        const data_2 = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_VALUE,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          send_data.data,
          send_data.type
        );
        return ref6.bool(data_2);
      }
      Registr3.setRegistrValue2 = setRegistrValue2;
      async function getRegistrValueStat2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE_STAT,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return data ? data : null;
      }
      Registr3.getRegistrValueStat2 = getRegistrValueStat2;
      async function getRegistrFolderStat2(HKey, SubKey, isQuerykey) {
        if (isQuerykey) {
          return getRegistrKeys2(HKey, SubKey);
        }
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_FOLDER_STAT,
          ref6.string(HKey),
          ref6.string(SubKey),
          ""
        );
        return data ? JSON.parse(String(data)) : null;
      }
      Registr3.getRegistrFolderStat2 = getRegistrFolderStat2;
      async function clearRegistrValue2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_VALUE,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return ref6.bool(data);
      }
      Registr3.clearRegistrValue2 = clearRegistrValue2;
      async function clearRegistrFolder2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_FOLDER,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string("")
        );
        return ref6.bool(data);
      }
      Registr3.clearRegistrFolder2 = clearRegistrFolder2;
      async function removeRegistrValue2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_VALUE,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return ref6.bool(data);
      }
      Registr3.removeRegistrValue2 = removeRegistrValue2;
      async function removeRegistrFolder2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER,
          ref6.string(HKey),
          ref6.string(SubKey)
        );
        return ref6.bool(data);
      }
      Registr3.removeRegistrFolder2 = removeRegistrFolder2;
      async function removeRegistrFolderTree2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER_TREE,
          ref6.string(HKey),
          ref6.string(SubKey)
        );
        return ref6.bool(data);
      }
      Registr3.removeRegistrFolderTree2 = removeRegistrFolderTree2;
      async function createRegistrFolder2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_FOLDER,
          ref6.string(HKey),
          ref6.string(SubKey)
        );
        return ref6.bool(data);
      }
      Registr3.createRegistrFolder2 = createRegistrFolder2;
      async function createRegistrValueKey2(HKey, SubKey, key, type) {
        const regVlaue = {};
        if (typeof key == "string") {
          if (typeof type == "number") {
            regVlaue[key] = type;
          } else {
            regVlaue[key] = HMC2_MODE.REG_TYPE.REG_NONE;
          }
        } else if (Array.isArray(key)) {
          for (const Ckey of key) {
            regVlaue[Ckey] = typeof type == "number" ? type : HMC2_MODE.REG_TYPE.REG_NONE;
          }
        } else if (key && typeof key == "object") {
          for (const Ckey in key) {
            regVlaue[Ckey] = key[Ckey];
          }
        }
        const bool_list = [];
        for (const key2 in regVlaue) {
          const type2 = regVlaue[key2] || HMC2_MODE.REG_TYPE.REG_NONE;
          const keyname = key2;
          const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_VALUE_KEY,
            ref6.string(HKey),
            ref6.string(SubKey),
            ref6.string(keyname),
            ref6.int(type2)
          );
          bool_list.push(data ? true : false);
        }
        return ref6.bool(bool_list.length == 1 ? bool_list.pop() : bool_list.at(-1) || false);
      }
      Registr3.createRegistrValueKey2 = createRegistrValueKey2;
      async function hasRegistrKey2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_KEY,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return ref6.bool(data);
      }
      Registr3.hasRegistrKey2 = hasRegistrKey2;
      async function hasRegistrFolderKey2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(
          HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_FOLDER_KEY,
          ref6.string(HKey),
          ref6.string(SubKey)
        );
        return ref6.bool(data);
      }
      Registr3.hasRegistrFolderKey2 = hasRegistrFolderKey2;
      function getRegistrQword2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_QWORD,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {
          return BigInt(data);
        }
        return null;
      }
      Registr3.getRegistrQword2Sync = getRegistrQword2Sync;
      function setRegistrQword2Sync(HKey, SubKey, key, Qword) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_QWORD,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          ref6.int(Qword || 0)
        );
        return ref6.bool(data);
      }
      Registr3.setRegistrQword2Sync = setRegistrQword2Sync;
      function getRegistrDword2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_DWORD,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {
          return ref6.long(data);
        }
        return null;
      }
      Registr3.getRegistrDword2Sync = getRegistrDword2Sync;
      function setRegistrDword2Sync(HKey, SubKey, key, Dword) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_DWORD,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          ref6.long(Dword)
        );
        return ref6.bool(data);
      }
      Registr3.setRegistrDword2Sync = setRegistrDword2Sync;
      function getRegistrString2Sync(HKey, SubKey, key, expand) {
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          expand ? true : false
        );
        return typeof data == "string" ? data : null;
      }
      Registr3.getRegistrString2Sync = getRegistrString2Sync;
      function setRegistrString2Sync(HKey, SubKey, key, String2, expand) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          ref6.string(String2 || ""),
          expand ? true : false
        );
        return ref6.bool(data);
      }
      Registr3.setRegistrString2Sync = setRegistrString2Sync;
      function getRegistrKeys2Sync(HKey, SubKey) {
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_KEYS,
          ref6.string(HKey),
          ref6.string(SubKey),
          ""
        );
        return data ? JSON.parse(String(data)) : null;
      }
      Registr3.getRegistrKeys2Sync = getRegistrKeys2Sync;
      function getRegistrStringList2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING_LIST,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        if (typeof data == "string") {
          if (data[0] == "[") {
            return ref6.JSONP(data);
          }
          if (data.includes("\0")) {
            const temp = data.split(/\0+/);
            if (temp.at(-1) == "") {
              temp.pop();
            }
            return temp;
          }
        }
        return Array.isArray(data) ? data : null;
      }
      Registr3.getRegistrStringList2Sync = getRegistrStringList2Sync;
      function setRegistrStringList2Sync(HKey, SubKey, key, StringList) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING_LIST,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          Array.isArray(StringList) ? ref6.stringArray(StringList) : ref6.convertMultiStringArray(ref6.string(StringList || "")) || []
        );
        return ref6.bool(data);
      }
      Registr3.setRegistrStringList2Sync = setRegistrStringList2Sync;
      function getRegistrBuffer2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_BUFFER,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return Buffer.isBuffer(data) ? data : null;
      }
      Registr3.getRegistrBuffer2Sync = getRegistrBuffer2Sync;
      function setRegistrBuffer2Sync(HKey, SubKey, key, Buff) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_BUFFER,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          Buff
        );
        return ref6.bool(data);
      }
      Registr3.setRegistrBuffer2Sync = setRegistrBuffer2Sync;
      function getRegistrValue2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return data ? data : null;
      }
      Registr3.getRegistrValue2Sync = getRegistrValue2Sync;
      function copyRegistrValue2Sync(HKey, SourceSubKey, Sourcekey, NewSubKey, Newkey) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_VALUE,
          ref6.string(HKey),
          ref6.string(SourceSubKey),
          ref6.string(Sourcekey || ""),
          ref6.string(NewSubKey || ""),
          ref6.string(Newkey || "")
        );
        return ref6.bool(data);
      }
      Registr3.copyRegistrValue2Sync = copyRegistrValue2Sync;
      function copyRegistrFolder2Sync(HKey, SourceSubKey, NewSubKey) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_FOLDER,
          ref6.string(HKey),
          ref6.string(SourceSubKey),
          ref6.string(NewSubKey || "")
        );
        return ref6.bool(data);
      }
      Registr3.copyRegistrFolder2Sync = copyRegistrFolder2Sync;
      function typename(type) {
        for (let i in main.HMC2_MODE.REG_TYPE) {
          const at = main.HMC2_MODE.REG_TYPE[i];
          if (at == type) {
            return i;
          }
        }
        return null;
      }
      Registr3.typename = typename;
      function is_REG_VALUE(data) {
        const result = data && typeof data == "object" && REG_TYPE(data.type) != null && (typeof data.data == "string" || typeof data.data == "object" && !data.data || Array.isArray(data.data), typeof data.data == "bigint" || typeof data.data == "number" || Buffer.isBuffer(data.data));
        if (result && typeof result.type_name != "string") {
          result.type_name = typename(result.type_name) || "REG_NONE";
        }
        return result;
      }
      Registr3.is_REG_VALUE = is_REG_VALUE;
      function REG_VALUE(REG_VALUE2) {
        if (is_REG_VALUE(REG_VALUE2))
          return REG_VALUE2;
        if (Buffer.isBuffer(REG_VALUE2)) {
          return {
            "data": REG_VALUE2,
            "type": main.HMC2_MODE.REG_TYPE.REG_BINARY,
            "size": REG_VALUE2.length,
            "typeName": "REG_BINARY"
          };
        }
        if (typeof REG_VALUE2 == "string") {
          return {
            "data": REG_VALUE2,
            "type": main.HMC2_MODE.REG_TYPE.REG_SZ,
            "size": REG_VALUE2.length,
            "typeName": "REG_SZ"
          };
        }
        if (typeof REG_VALUE2 == "bigint") {
          return {
            "data": REG_VALUE2,
            "type": main.HMC2_MODE.REG_TYPE.REG_QWORD,
            "size": 8,
            "typeName": "REG_QWORD"
          };
        }
        if (typeof REG_VALUE2 == "number") {
          return REG_VALUE2 <= 4294967295 ? {
            "data": REG_VALUE2,
            "type": main.HMC2_MODE.REG_TYPE.REG_DWORD,
            "size": 4,
            "typeName": "REG_DWORD"
          } : {
            "data": BigInt(REG_VALUE2),
            "type": main.HMC2_MODE.REG_TYPE.REG_QWORD,
            "size": 8,
            "typeName": "REG_QWORD"
          };
        }
        if (Array.isArray(REG_VALUE2)) {
          return {
            "data": ref6.is_stringArray(REG_VALUE2) ? REG_VALUE2 : ref6.stringArray(REG_VALUE2),
            "type": main.HMC2_MODE.REG_TYPE.REG_MULTI_SZ,
            "size": 0,
            "typeName": "REG_MULTI_SZ"
          };
        }
        return null;
      }
      Registr3.REG_VALUE = REG_VALUE;
      function REG_TYPE(type) {
        if (typeof type == "string") {
          for (let i in main.HMC2_MODE.REG_TYPE) {
            if ((i == null ? void 0 : i.toUpperCase()) == (type == null ? void 0 : type.toUpperCase())) {
              return main.HMC2_MODE.REG_TYPE[i];
            }
          }
        }
        if (typeof type == "number") {
          for (let i in main.HMC2_MODE.REG_TYPE) {
            const at = main.HMC2_MODE.REG_TYPE[i];
            if (at == type) {
              return at;
            }
          }
        }
        return main.HMC2_MODE.REG_TYPE.REG_NONE;
      }
      Registr3.REG_TYPE = REG_TYPE;
      function convertRegistrData(data, type) {
        const data_copy = REG_VALUE(data);
        const type_copy = REG_TYPE(type);
        const send_data = {
          type: type_copy || (data_copy == null ? void 0 : data_copy.type) || HMC2_MODE.REG_TYPE.REG_NONE,
          data: typeof (data_copy == null ? void 0 : data_copy.data) != "undefined" ? data_copy.data : Buffer.alloc(0)
        };
        return send_data;
      }
      Registr3.convertRegistrData = convertRegistrData;
      function setRegistrValue2Sync(HKey, SubKey, key, data, type) {
        const send_data = convertRegistrData(data, type);
        if (!GetRegistrEnvInfoSync)
          return false;
        const data_2 = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_VALUE,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || ""),
          send_data.data,
          send_data.type
        );
        return ref6.bool(data_2);
      }
      Registr3.setRegistrValue2Sync = setRegistrValue2Sync;
      function getRegistrValueStat2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE_STAT,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return data || null;
      }
      Registr3.getRegistrValueStat2Sync = getRegistrValueStat2Sync;
      function getRegistrFolderStat2Sync(HKey, SubKey, isQuerykey) {
        if (isQuerykey) {
          return getRegistrKeys2Sync(HKey, SubKey);
        }
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_FOLDER_STAT,
          ref6.string(HKey),
          ref6.string(SubKey),
          ""
        );
        return data ? JSON.parse(String(data)) : null;
      }
      Registr3.getRegistrFolderStat2Sync = getRegistrFolderStat2Sync;
      function clearRegistrValue2Sync(HKey, SubKey, key) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_VALUE,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return ref6.bool(data);
      }
      Registr3.clearRegistrValue2Sync = clearRegistrValue2Sync;
      function clearRegistrFolder2Sync(HKey, SubKey) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_FOLDER,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string("")
        );
        return ref6.bool(data);
      }
      Registr3.clearRegistrFolder2Sync = clearRegistrFolder2Sync;
      function removeRegistrValue2Sync(HKey, SubKey, key) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_VALUE,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return ref6.bool(data);
      }
      Registr3.removeRegistrValue2Sync = removeRegistrValue2Sync;
      function removeRegistrFolder2Sync(HKey, SubKey) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER,
          ref6.string(HKey),
          ref6.string(SubKey)
        );
        return ref6.bool(data);
      }
      Registr3.removeRegistrFolder2Sync = removeRegistrFolder2Sync;
      function removeRegistrFolderTree2Sync(HKey, SubKey) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER_TREE,
          ref6.string(HKey),
          ref6.string(SubKey)
        );
        return ref6.bool(data);
      }
      Registr3.removeRegistrFolderTree2Sync = removeRegistrFolderTree2Sync;
      function createRegistrFolder2Sync(HKey, SubKey) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_FOLDER,
          ref6.string(HKey),
          ref6.string(SubKey)
        );
        return ref6.bool(data);
      }
      Registr3.createRegistrFolder2Sync = createRegistrFolder2Sync;
      function createRegistrValueKey2Sync(HKey, SubKey, key, type) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const regVlaue = {};
        if (typeof key == "string") {
          if (typeof type == "number") {
            regVlaue[key] = type;
          } else {
            regVlaue[key] = HMC2_MODE.REG_TYPE.REG_NONE;
          }
        } else if (Array.isArray(key)) {
          for (const Ckey of key) {
            regVlaue[Ckey] = typeof type == "number" ? type : HMC2_MODE.REG_TYPE.REG_NONE;
          }
        } else if (key && typeof key == "object") {
          for (const Ckey in key) {
            regVlaue[Ckey] = key[Ckey];
          }
        }
        const bool_list = [];
        for (const key2 in regVlaue) {
          const type2 = regVlaue[key2] || HMC2_MODE.REG_TYPE.REG_NONE;
          const keyname = key2;
          const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_VALUE_KEY,
            ref6.string(HKey),
            ref6.string(SubKey),
            ref6.string(keyname),
            ref6.int(type2)
          );
          bool_list.push(data ? true : false);
        }
        return ref6.bool(bool_list.length == 1 ? bool_list.pop() : bool_list.at(-1) || false);
      }
      Registr3.createRegistrValueKey2Sync = createRegistrValueKey2Sync;
      function hasRegistrKey2Sync(HKey, SubKey, key) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_KEY,
          ref6.string(HKey),
          ref6.string(SubKey),
          ref6.string(key || "")
        );
        return ref6.bool(data);
      }
      Registr3.hasRegistrKey2Sync = hasRegistrKey2Sync;
      function hasRegistrFolderKey2Sync(HKey, SubKey) {
        if (!GetRegistrEnvInfoSync)
          return false;
        const data = GetRegistrEnvInfoSync(
          HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_FOLDER_KEY,
          ref6.string(HKey),
          ref6.string(SubKey)
        );
        return ref6.bool(data);
      }
      Registr3.hasRegistrFolderKey2Sync = hasRegistrFolderKey2Sync;
    })(Registr || (Registr = {}));
  }
});

// source/hmc-win32@2.0/source/main/ShellPromiseEval.ts
var ShellPromiseEval_exports = {};
__export(ShellPromiseEval_exports, {
  HMC_PROMISEEVAL_TASK_TYPE: () => HMC_PROMISEEVAL_TASK_TYPE,
  promiseEvalTask: () => promiseEvalTask
});
var main2, _Native2, Native2, HMC_PROMISEEVAL_TASK_TYPE, HMC_PromiseeEvalTask, promiseEvalTask;
var init_ShellPromiseEval = __esm({
  "source/hmc-win32@2.0/source/main/ShellPromiseEval.ts"() {
    "use strict";
    init_util();
    main2 = (init_main(), __toCommonJS(main_exports));
    _Native2 = (init_Native(), __toCommonJS(Native_exports));
    ({ Native: Native2 } = _Native2);
    HMC_PROMISEEVAL_TASK_TYPE = /* @__PURE__ */ ((HMC_PROMISEEVAL_TASK_TYPE3) => {
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["getLinkTarget2"] = 1] = "getLinkTarget2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["getFileAttributes2"] = 2] = "getFileAttributes2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["getVolumeList2"] = 3] = "getVolumeList2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["formatVolumePath2"] = 5] = "formatVolumePath2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["formatVolumeName2"] = 6] = "formatVolumeName2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["formatVolumeNtName2"] = 7] = "formatVolumeNtName2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["getLinkPath2"] = 8] = "getLinkPath2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["hasFileSymbolicLink2"] = 9] = "hasFileSymbolicLink2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["hasFileHardLink2"] = 10] = "hasFileHardLink2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["hasDirSymbolicLink2"] = 12] = "hasDirSymbolicLink2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["hasDirJunctionPoint2"] = 13] = "hasDirJunctionPoint2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["getLinkType2"] = 15] = "getLinkType2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["createLink"] = 16] = "createLink";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["createDirJunctionPoint2"] = 17] = "createDirJunctionPoint2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["createHardLink2"] = 18] = "createHardLink2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["createSymlink2"] = 19] = "createSymlink2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["createDirSymlink2"] = 20] = "createDirSymlink2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["setFolderIcon2"] = 21] = "setFolderIcon2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["setExtensionIcon2"] = 22] = "setExtensionIcon2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["setAppURLProtocol2"] = 23] = "setAppURLProtocol2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["getShortcutLink2"] = 25] = "getShortcutLink2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["trashFile2"] = 26] = "trashFile2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["clearTrash2"] = 27] = "clearTrash2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["copyFile2"] = 28] = "copyFile2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["moveFile2"] = 29] = "moveFile2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["setShortcutLink2"] = 30] = "setShortcutLink2";
      return HMC_PROMISEEVAL_TASK_TYPE3;
    })(HMC_PROMISEEVAL_TASK_TYPE || {});
    HMC_PromiseeEvalTask = class {
      constructor() {
        this.async = {};
        this.sync = {};
        const TASK_TYPE_LIST = Object.keys(HMC_PROMISEEVAL_TASK_TYPE);
        const _this = this;
        for (let index = 0; index < TASK_TYPE_LIST.length; index++) {
          const TASK_TYPE = TASK_TYPE_LIST[index];
          if (!TASK_TYPE || (TASK_TYPE == null ? void 0 : TASK_TYPE.match(/^\d+/)))
            continue;
          const TASK_ID = HMC_PROMISEEVAL_TASK_TYPE[TASK_TYPE];
          _this.async[TASK_TYPE] = (...arg) => {
            var _a;
            try {
              if (!((_a = Native2.native) == null ? void 0 : _a.HMC_GetShellEnvInfo)) {
                return Promise.reject(main2.HMC2_MODE.HMCNotPlatform);
              }
              if (arg.length >= 1) {
                return Native2.native.HMC_GetShellEnvInfo(TASK_ID, ...arg);
              }
              return Native2.native.HMC_GetShellEnvInfo(TASK_ID);
            } catch (error) {
              return Promise.reject(error);
            }
          };
          _this.sync[TASK_TYPE] = (...arg) => {
            var _a;
            if (!((_a = Native2.native) == null ? void 0 : _a.HMC_GetShellEnvInfoSync)) {
              return null;
            }
            if (arg.length >= 1) {
              return Native2.native.HMC_GetShellEnvInfoSync(TASK_ID, ...arg) || null;
            }
            return Native2.native.HMC_GetShellEnvInfoSync(TASK_ID);
          };
          if (!_this[TASK_TYPE]) {
            _this[TASK_TYPE] = _this.async[TASK_TYPE];
          }
          const KEY = `${TASK_TYPE}Sync`;
          if (!_this[KEY]) {
            _this[KEY] = _this.sync[TASK_TYPE];
          }
        }
      }
      async getLinkTarget2(targetPath) {
        if (!promiseEvalTask.async.getLinkTarget2) {
          return Promise.resolve(null);
        }
        return await promiseEvalTask.async.getLinkTarget2(targetPath).then((data) => {
          if (typeof data == "string") {
            data = ref.JSONP(data);
            if ((data == null ? void 0 : data.type) == "HARD_LINK_FILE" && (data == null ? void 0 : data.volume)) {
              data.volume = ref.JSONP(data.volume);
            }
          }
          return data || null;
        });
      }
      getLinkTarget2Sync(targetPath) {
        if (!promiseEvalTask.sync.getLinkTarget2) {
          return null;
        }
        let data = promiseEvalTask.sync.getLinkTarget2(targetPath);
        if (typeof data == "string") {
          data = ref.JSONP(data);
          if ((data == null ? void 0 : data.type) == "HARD_LINK_FILE" && (data == null ? void 0 : data.volume)) {
            data.volume = ref.JSONP(data.volume);
          }
        }
        return data || null;
      }
      async getFileAttributes2(targetPath) {
        if (!promiseEvalTask.async.getFileAttributes2) {
          return null;
        }
        let data = await promiseEvalTask.async.getFileAttributes2(targetPath);
        const attributes_list = typeof data == "string" ? ref.JSONP(data) : data;
        if (attributes_list == null ? void 0 : attributes_list.length) {
          return {
            "attributes": attributes_list[0],
            "list": attributes_list.length == 1 ? attributes_list : attributes_list.slice(1)
          };
        }
        return null;
      }
      getFileAttributes2Sync(targetPath) {
        if (!promiseEvalTask.sync.getFileAttributes2) {
          return null;
        }
        let data = promiseEvalTask.sync.getFileAttributes2(targetPath);
        const attributes_list = typeof data == "string" ? ref.JSONP(data) : data;
        if (attributes_list == null ? void 0 : attributes_list.length) {
          return {
            "attributes": attributes_list[0],
            "list": attributes_list.length == 1 ? attributes_list : attributes_list.slice(1)
          };
        }
        return null;
      }
      async getVolumeList2() {
        if (!promiseEvalTask.async.getVolumeList2) {
          return Promise.resolve(null);
        }
        return await promiseEvalTask.async.getVolumeList2().then((data) => {
          if (typeof data == "string") {
            data = ref.JSONP(data);
          }
          return data || null;
        });
      }
      getVolumeList2Sync() {
        if (!promiseEvalTask.sync.getVolumeList2) {
          return null;
        }
        let data = promiseEvalTask.sync.getVolumeList2();
        if (typeof data == "string") {
          data = ref.JSONP(data);
        }
        return data || null;
      }
    };
    promiseEvalTask = new HMC_PromiseeEvalTask();
  }
});

// source/hmc-win32@2.0/source/main/shell.ts
var shell_exports = {};
__export(shell_exports, {
  Shell: () => Shell
});
var main3, util2, PromiseEval, ShellPromiseEvalMain, _Native3, Native3, ref2, REG_KEY_EM, StartupConstructor, Shell;
var init_shell = __esm({
  "source/hmc-win32@2.0/source/main/shell.ts"() {
    "use strict";
    init_registr();
    init_promiseEval();
    main3 = (init_main(), __toCommonJS(main_exports));
    util2 = (init_util(), __toCommonJS(util_exports));
    PromiseEval = (init_promiseEval(), __toCommonJS(promiseEval_exports));
    ShellPromiseEvalMain = (init_ShellPromiseEval(), __toCommonJS(ShellPromiseEval_exports));
    _Native3 = (init_Native(), __toCommonJS(Native_exports));
    ({ Native: Native3 } = _Native3);
    ({ ref: ref2 } = util2);
    REG_KEY_EM = {
      HKEY_LOCAL_MACHINE: "HKEY_LOCAL_MACHINE",
      pathRun: "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
      pathRunOnce: "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"
    };
    StartupConstructor = class {
      constructor() {
      }
      has(keyName) {
        var _a;
        return ((_a = Native3.HMC_SHELL_STARTUP_CLASS) == null ? void 0 : _a.has(ref2.string(keyName))) || false;
      }
      hasOnce(keyName) {
        var _a;
        return ((_a = Native3.HMC_SHELL_STARTUP_CLASS) == null ? void 0 : _a.hasOnce(ref2.string(keyName))) || false;
      }
      remove(keyName) {
        var _a;
        return ((_a = Native3.HMC_SHELL_STARTUP_CLASS) == null ? void 0 : _a.remove(ref2.string(keyName))) || false;
      }
      removeOnce(keyName) {
        var _a;
        return ((_a = Native3.HMC_SHELL_STARTUP_CLASS) == null ? void 0 : _a.removeOnce(ref2.string(keyName))) || false;
      }
      set(keyName, path, cmd) {
        var _a;
        return ((_a = Native3.HMC_SHELL_STARTUP_CLASS) == null ? void 0 : _a.set(ref2.string(keyName), ref2.string(path), ref2.string(cmd || ""))) || false;
      }
      setOnce(keyName, path, cmd) {
        var _a;
        return ((_a = Native3.HMC_SHELL_STARTUP_CLASS) == null ? void 0 : _a.setOnce(ref2.string(keyName), ref2.string(path), ref2.string(cmd || ""))) || false;
      }
      async enum2() {
        const obj = {};
        const keys = await this.keys2();
        const { HKEY_LOCAL_MACHINE } = main3.HMC2_MODE.Hkey;
        for (let index = 0; index < keys.length; index++) {
          let at = keys[index];
          obj[at] = await Registr.getRegistrString2(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRun, at);
        }
        return obj;
      }
      enum2Sync() {
        const obj = {};
        const keys = this.keys2Sync();
        const { HKEY_LOCAL_MACHINE } = main3.HMC2_MODE.Hkey;
        for (let index = 0; index < keys.length; index++) {
          let at = keys[index];
          obj[at] = Registr.getRegistrString2Sync(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRun, at);
        }
        return obj;
      }
      async enumOnce2() {
        const obj = {};
        const keys = await this.keysOnce2();
        const { HKEY_LOCAL_MACHINE } = main3.HMC2_MODE.Hkey;
        for (let index = 0; index < keys.length; index++) {
          let at = keys[index];
          obj[at] = await Registr.getRegistrString2(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRunOnce, at);
        }
        return obj;
      }
      enumOnce2Sync() {
        const obj = {};
        const keys = this.keysOnce2Sync();
        const { HKEY_LOCAL_MACHINE } = main3.HMC2_MODE.Hkey;
        for (let index = 0; index < keys.length; index++) {
          let at = keys[index];
          obj[at] = Registr.getRegistrString2Sync(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRunOnce, at);
        }
        return obj;
      }
      async keys2() {
        var _a;
        const { HKEY_LOCAL_MACHINE } = main3.HMC2_MODE.Hkey;
        const key = Registr.getRegistrKeys2(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRun);
        return ((_a = await key) == null ? void 0 : _a.valueKeyList.map((_) => _.name)) || [];
      }
      keys2Sync() {
        const { HKEY_LOCAL_MACHINE } = main3.HMC2_MODE.Hkey;
        const key = Registr.getRegistrKeys2Sync(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRun);
        return (key == null ? void 0 : key.valueKeyList.map((_) => _.name)) || [];
      }
      async keysOnce2() {
        var _a;
        const { HKEY_LOCAL_MACHINE } = main3.HMC2_MODE.Hkey;
        const key = Registr.getRegistrKeys2(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRunOnce);
        return ((_a = await key) == null ? void 0 : _a.valueKeyList.map((_) => _.name)) || [];
      }
      keysOnce2Sync() {
        const { HKEY_LOCAL_MACHINE } = main3.HMC2_MODE.Hkey;
        const key = Registr.getRegistrKeys2Sync(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRunOnce);
        return (key == null ? void 0 : key.valueKeyList.map((_) => _.name)) || [];
      }
    };
    ((Shell3) => {
      Shell3.ShellPromise = ShellPromiseEvalMain.promiseEvalTask;
      Shell3.Startup = new StartupConstructor();
      function showContextMenu(hwnd, file, x, y) {
        var _a, _b;
        return ((_a = Native3.HMC_SHELL_CLASS) == null ? void 0 : _a.showContextMenu) ? (_b = Native3.HMC_SHELL_CLASS) == null ? void 0 : _b.showContextMenu(
          ref2.int(hwnd || 0),
          Array.isArray(file) ? file : ref2.string(file),
          ref2.int(x || 0),
          ref2.int(y || 0)
        ) : false;
      }
      Shell3.showContextMenu = showContextMenu;
      function getTrayList2() {
        return promiseEvalTask2.getTrayList2();
      }
      Shell3.getTrayList2 = getTrayList2;
      function getTrayList2Sync() {
        return promiseEvalTask2.getTrayList2Sync();
      }
      Shell3.getTrayList2Sync = getTrayList2Sync;
      function trashFile(trash_path, is_Recycle, isShow) {
        var _a;
        if (!((_a = Native3.HMC_SHELL_CLASS) == null ? void 0 : _a.trashFile))
          return false;
        return Native3.HMC_SHELL_CLASS.trashFile(ref2.string(trash_path), ref2.bool(is_Recycle), ref2.bool(isShow));
      }
      Shell3.trashFile = trashFile;
      function clearTrash(root_path, isShow) {
        var _a;
        if (!((_a = Native3.HMC_SHELL_CLASS) == null ? void 0 : _a.clearTrash))
          return false;
        return Native3.HMC_SHELL_CLASS.clearTrash(ref2.string(root_path), ref2.bool(isShow));
      }
      Shell3.clearTrash = clearTrash;
      function copyFile(filePath, newFilePath, isShowConfirm, isShow, isShowProgress) {
        var _a;
        if (!((_a = Native3.HMC_SHELL_CLASS) == null ? void 0 : _a.copyFile))
          return false;
        return Native3.HMC_SHELL_CLASS.copyFile(ref2.string(filePath), ref2.string(newFilePath), ref2.bool(isShowConfirm), ref2.bool(isShow), ref2.bool(isShowProgress));
      }
      Shell3.copyFile = copyFile;
      function moveFile(filePath, newFilePath, isShowConfirm, isShow, isShowProgress) {
        var _a;
        if (!((_a = Native3.HMC_SHELL_CLASS) == null ? void 0 : _a.moveFile))
          return false;
        return Native3.HMC_SHELL_CLASS.moveFile(ref2.string(filePath), ref2.string(newFilePath), ref2.bool(isShowConfirm), ref2.bool(isShow), ref2.bool(isShowProgress));
      }
      Shell3.moveFile = moveFile;
      Shell3.captureBmp2 = PromiseEval.promiseEvalTask.captureBmp2;
      Shell3.captureBmp2Sync = PromiseEval.promiseEvalTask.captureBmp2Sync;
      Shell3.getThumbnailPng2 = PromiseEval.promiseEvalTask.getThumbnailPng2;
      Shell3.getThumbnailPng2Sync = PromiseEval.promiseEvalTask.getThumbnailPng2Sync;
      Shell3.getFileIcon2 = PromiseEval.promiseEvalTask.getThumbnailPng2;
      Shell3.getFileIcon2Sync = PromiseEval.promiseEvalTask.getThumbnailPng2Sync;
      let Symlink2;
      ((Symlink3) => {
        async function hasLink2(targetPath) {
          return await getLinkPath2(targetPath) ? true : false;
        }
        Symlink3.hasLink2 = hasLink2;
        function hasLink2Sync(targetPath) {
          return getLinkPath2Sync(targetPath) ? true : false;
        }
        Symlink3.hasLink2Sync = hasLink2Sync;
        async function getLinkType2(targetPath) {
          const data = await ShellPromiseEvalMain.promiseEvalTask.getLinkType2(ref2.string(targetPath));
          return ref2.JSONP(data, null);
        }
        Symlink3.getLinkType2 = getLinkType2;
        function getLinkType2Sync(targetPath) {
          const data = ShellPromiseEvalMain.promiseEvalTask.getLinkType2Sync(ref2.string(targetPath));
          return ref2.JSONP(data, null);
        }
        Symlink3.getLinkType2Sync = getLinkType2Sync;
        function getLinkPath2(targetPath) {
          return ShellPromiseEvalMain.promiseEvalTask.getLinkPath2(ref2.string(targetPath));
        }
        Symlink3.getLinkPath2 = getLinkPath2;
        function getLinkPath2Sync(targetPath) {
          return Shell3.ShellPromise.getLinkPath2Sync(ref2.string(targetPath));
        }
        Symlink3.getLinkPath2Sync = getLinkPath2Sync;
        function hasFileSymbolicLink2(targetPath) {
          return Shell3.ShellPromise.hasFileSymbolicLink2(ref2.string(targetPath));
        }
        Symlink3.hasFileSymbolicLink2 = hasFileSymbolicLink2;
        function hasFileSymbolicLink2Sync(targetPath) {
          return Shell3.ShellPromise.hasFileSymbolicLink2Sync(ref2.string(targetPath));
        }
        Symlink3.hasFileSymbolicLink2Sync = hasFileSymbolicLink2Sync;
        function hasFileHardLink2(targetPath) {
          return Shell3.ShellPromise.hasFileHardLink2(ref2.string(targetPath));
        }
        Symlink3.hasFileHardLink2 = hasFileHardLink2;
        function hasFileHardLink2Sync(targetPath) {
          return Shell3.ShellPromise.hasFileHardLink2Sync(ref2.string(targetPath));
        }
        Symlink3.hasFileHardLink2Sync = hasFileHardLink2Sync;
        function hasDirSymbolicLink2(targetPath) {
          return Shell3.ShellPromise.hasDirSymbolicLink2(ref2.string(targetPath));
        }
        Symlink3.hasDirSymbolicLink2 = hasDirSymbolicLink2;
        function hasDirSymbolicLink2Sync(targetPath) {
          return Shell3.ShellPromise.hasDirSymbolicLink2Sync(ref2.string(targetPath));
        }
        Symlink3.hasDirSymbolicLink2Sync = hasDirSymbolicLink2Sync;
        function hasDirJunctionPoint2(targetPath) {
          return Shell3.ShellPromise.hasDirJunctionPoint2(ref2.string(targetPath));
        }
        Symlink3.hasDirJunctionPoint2 = hasDirJunctionPoint2;
        function hasDirJunctionPoint2Sync(targetPath) {
          return Shell3.ShellPromise.hasDirJunctionPoint2Sync(ref2.string(targetPath));
        }
        Symlink3.hasDirJunctionPoint2Sync = hasDirJunctionPoint2Sync;
        function createLink(targetType, targetPath, sourcePath) {
          return Shell3.ShellPromise.createLink(ref2.int(targetType), ref2.string(targetPath), ref2.string(sourcePath));
        }
        Symlink3.createLink = createLink;
        function createLinkSync(targetType, targetPath, sourcePath) {
          return Shell3.ShellPromise.createLinkSync(ref2.int(targetType), ref2.string(targetPath), ref2.string(sourcePath));
        }
        Symlink3.createLinkSync = createLinkSync;
        function createDirJunctionPoint2(targetPath, sourcePath) {
          return Shell3.ShellPromise.createDirJunctionPoint2(ref2.string(targetPath), ref2.string(sourcePath));
        }
        Symlink3.createDirJunctionPoint2 = createDirJunctionPoint2;
        function createDirJunctionPoint2Sync(targetPath, sourcePath) {
          return Shell3.ShellPromise.createDirJunctionPoint2Sync(ref2.string(targetPath), ref2.string(sourcePath));
        }
        Symlink3.createDirJunctionPoint2Sync = createDirJunctionPoint2Sync;
        function createHardLink2(targetPath, sourcePath) {
          return Shell3.ShellPromise.createHardLink2(ref2.string(targetPath), ref2.string(sourcePath));
        }
        Symlink3.createHardLink2 = createHardLink2;
        function createHardLink2Sync(targetPath, sourcePath) {
          return Shell3.ShellPromise.createHardLink2Sync(ref2.string(targetPath), ref2.string(sourcePath));
        }
        Symlink3.createHardLink2Sync = createHardLink2Sync;
        function createSymlink2(targetPath, sourcePath) {
          return Shell3.ShellPromise.createSymlink2(ref2.string(targetPath), ref2.string(sourcePath));
        }
        Symlink3.createSymlink2 = createSymlink2;
        function createSymlink2Sync(targetPath, sourcePath) {
          return Shell3.ShellPromise.createSymlink2Sync(ref2.string(targetPath), ref2.string(sourcePath));
        }
        Symlink3.createSymlink2Sync = createSymlink2Sync;
        function createDirSymlink2(targetPath, sourcePath) {
          return Shell3.ShellPromise.createDirSymlink2(ref2.string(targetPath), ref2.string(sourcePath));
        }
        Symlink3.createDirSymlink2 = createDirSymlink2;
        function createDirSymlink2Sync(targetPath, sourcePath) {
          return Shell3.ShellPromise.createDirSymlink2Sync(ref2.string(targetPath), ref2.string(sourcePath));
        }
        Symlink3.createDirSymlink2Sync = createDirSymlink2Sync;
      })(Symlink2 = Shell3.Symlink || (Shell3.Symlink = {}));
      function getFileAttributes2(targetPath) {
        return Shell3.ShellPromise.getFileAttributes2(ref2.string(targetPath));
      }
      Shell3.getFileAttributes2 = getFileAttributes2;
      function getFileAttributes2Sync(targetPath) {
        return Shell3.ShellPromise.getFileAttributes2Sync(ref2.string(targetPath));
      }
      Shell3.getFileAttributes2Sync = getFileAttributes2Sync;
      function setFolderIcon2(targetPath, iconPath, iconIndex) {
        return Shell3.ShellPromise.setFolderIcon2(ref2.string(targetPath), ref2.string(iconPath), ref2.int(iconIndex || 0));
      }
      Shell3.setFolderIcon2 = setFolderIcon2;
      function setFolderIcon2Sync(targetPath, iconPath, iconIndex) {
        return Shell3.ShellPromise.setFolderIcon2Sync(ref2.string(targetPath), ref2.string(iconPath), ref2.int(iconIndex || 0));
      }
      Shell3.setFolderIcon2Sync = setFolderIcon2Sync;
      async function setExtensionIcon2(extensionName, typeName, iconPath, iconIndex) {
        return await Shell3.ShellPromise.setExtensionIcon2(ref2.string(extensionName), ref2.string(typeName), ref2.string(iconPath), ref2.int(iconIndex || 0)) || false;
      }
      Shell3.setExtensionIcon2 = setExtensionIcon2;
      function setExtensionIcon2Sync(extensionName, typeName, iconPath, iconIndex) {
        return Shell3.ShellPromise.setExtensionIcon2Sync(ref2.string(extensionName), ref2.string(typeName), ref2.string(iconPath), ref2.int(iconIndex || 0)) || false;
      }
      Shell3.setExtensionIcon2Sync = setExtensionIcon2Sync;
      function setAppURLProtocol2Sync(protocolName, appPath, command) {
        if (Array.isArray(command)) {
          let command_list = "";
          for (let index = 0; index < command.length; index++) {
            const command_ = command[index];
            command_list = command_list + ` "${command_}"`;
          }
          command = command_list;
        }
        return Shell3.ShellPromise.setAppURLProtocol2Sync(ref2.string(protocolName), ref2.string(appPath), ref2.string(command));
      }
      Shell3.setAppURLProtocol2Sync = setAppURLProtocol2Sync;
      function setAppURLProtocol2(protocolName, appPath, command) {
        if (Array.isArray(command)) {
          let command_list = "";
          for (let index = 0; index < command.length; index++) {
            const command_ = command[index];
            command_list = command_list + ` "${command_}"`;
          }
          command = command_list;
        }
        if (!command) {
          command = "%1";
        }
        return Shell3.ShellPromise.setAppURLProtocol2(ref2.string(protocolName), ref2.string(appPath), ref2.string(command));
      }
      Shell3.setAppURLProtocol2 = setAppURLProtocol2;
      async function getShortcutLink2(targetPath, QueryDetaile) {
        const _QueryDetaile = typeof QueryDetaile == "boolean" ? QueryDetaile : ref2.bool(QueryDetaile || true);
        const data = await Shell3.ShellPromise.getShortcutLink2(ref2.string(targetPath), _QueryDetaile);
        if (typeof data == "string") {
          if (_QueryDetaile) {
            return ref2.JSONP(data, null);
          }
          return data;
        }
        return data;
      }
      Shell3.getShortcutLink2 = getShortcutLink2;
      function getShortcutLink2Sync(targetPath, QueryDetaile) {
        const _QueryDetaile = typeof QueryDetaile == "boolean" ? QueryDetaile : ref2.bool(QueryDetaile || true);
        const data = Shell3.ShellPromise.getShortcutLink2Sync(ref2.string(targetPath), _QueryDetaile);
        if (typeof data == "string") {
          if (_QueryDetaile) {
            return ref2.JSONP(data, null);
          }
          return data;
        }
        return data;
      }
      Shell3.getShortcutLink2Sync = getShortcutLink2Sync;
      async function setShortcutLink2(targetPath, FilePath, work_dir, desc, args, iShowCmd, icon, iconIndex) {
        if (!work_dir)
          work_dir = "";
        if (!desc)
          desc = "";
        if (!args)
          args = "";
        if (!icon)
          icon = "";
        if (!iconIndex)
          iconIndex = 0;
        if (!iShowCmd)
          iShowCmd = 1;
        return Shell3.ShellPromise.setShortcutLink2(ref2.string(targetPath), ref2.string(FilePath), ref2.string(work_dir), ref2.string(desc), ref2.string(args), ref2.int(iShowCmd), ref2.string(icon), ref2.int(iconIndex));
      }
      Shell3.setShortcutLink2 = setShortcutLink2;
      async function trashFile2(trash_path, is_Recycle, isShow) {
        if (typeof is_Recycle != "boolean")
          is_Recycle = true;
        if (typeof isShow != "boolean")
          isShow = true;
        return Shell3.ShellPromise.trashFile2(ref2.string(trash_path), ref2.bool(is_Recycle), ref2.bool(isShow));
      }
      Shell3.trashFile2 = trashFile2;
      async function clearTrash2(root_path, isShow) {
        if (typeof isShow != "boolean")
          isShow = true;
        return Shell3.ShellPromise.clearTrash2(ref2.string(root_path || ""), ref2.bool(isShow));
      }
      Shell3.clearTrash2 = clearTrash2;
      async function copyFile2(filePath, newFilePath, isShowConfirm, isShow, isShowProgress) {
        if (typeof isShowConfirm != "boolean")
          isShowConfirm = true;
        if (typeof isShow != "boolean")
          isShow = true;
        if (typeof isShowProgress != "boolean")
          isShowProgress = true;
        return Shell3.ShellPromise.copyFile2(ref2.string(filePath), ref2.string(newFilePath), ref2.bool(isShowConfirm), ref2.bool(isShow), ref2.bool(isShowProgress));
      }
      Shell3.copyFile2 = copyFile2;
      async function moveFile2(filePath, newFilePath, isShowConfirm, isShow, isShowProgress) {
        if (typeof isShowConfirm != "boolean")
          isShowConfirm = true;
        if (typeof isShow != "boolean")
          isShow = true;
        if (typeof isShowProgress != "boolean")
          isShowProgress = true;
        return Shell3.ShellPromise.moveFile2(ref2.string(filePath), ref2.string(newFilePath), ref2.bool(isShowConfirm), ref2.bool(isShow), ref2.bool(isShowProgress));
      }
      Shell3.moveFile2 = moveFile2;
      function setShortcutLink2Sync(targetPath, FilePath, work_dir, desc, args, iShowCmd, icon, iconIndex) {
        if (!work_dir)
          work_dir = "";
        if (!desc)
          desc = "";
        if (!args)
          args = "";
        if (!icon)
          icon = "";
        if (!iconIndex)
          iconIndex = 0;
        if (!iShowCmd)
          iShowCmd = 1;
        return Shell3.ShellPromise.setShortcutLink2Sync(ref2.string(targetPath), ref2.string(FilePath), ref2.string(work_dir), ref2.string(desc), ref2.string(args), ref2.int(iShowCmd), ref2.string(icon), ref2.int(iconIndex));
      }
      Shell3.setShortcutLink2Sync = setShortcutLink2Sync;
      function trashFile2Sync(trash_path, is_Recycle, isShow) {
        if (typeof is_Recycle != "boolean")
          is_Recycle = true;
        if (typeof isShow != "boolean")
          isShow = true;
        return Shell3.ShellPromise.trashFile2Sync(ref2.string(trash_path), ref2.bool(is_Recycle), ref2.bool(isShow));
      }
      Shell3.trashFile2Sync = trashFile2Sync;
      function clearTrash2Sync(root_path, isShow) {
        if (typeof isShow != "boolean")
          isShow = true;
        return Shell3.ShellPromise.clearTrash2Sync(ref2.string(root_path || ""), ref2.bool(isShow));
      }
      Shell3.clearTrash2Sync = clearTrash2Sync;
      function copyFile2Sync(filePath, newFilePath, isShowConfirm, isShow, isShowProgress) {
        if (typeof isShowConfirm != "boolean")
          isShowConfirm = true;
        if (typeof isShow != "boolean")
          isShow = true;
        if (typeof isShowProgress != "boolean")
          isShowProgress = true;
        return Shell3.ShellPromise.copyFile2Sync(ref2.string(filePath), ref2.string(newFilePath), ref2.bool(isShowConfirm), ref2.bool(isShow), ref2.bool(isShowProgress));
      }
      Shell3.copyFile2Sync = copyFile2Sync;
      function moveFile2Sync(filePath, newFilePath, isShowConfirm, isShow, isShowProgress) {
        if (typeof isShowConfirm != "boolean")
          isShowConfirm = true;
        if (typeof isShow != "boolean")
          isShow = true;
        if (typeof isShowProgress != "boolean")
          isShowProgress = true;
        return Shell3.ShellPromise.moveFile2Sync(ref2.string(filePath), ref2.string(newFilePath), ref2.bool(isShowConfirm), ref2.bool(isShow), ref2.bool(isShowProgress));
      }
      Shell3.moveFile2Sync = moveFile2Sync;
      Shell3.HMC_GetShellEnvInfo = ShellPromiseEvalMain.promiseEvalTask;
    })(Shell || (Shell = {}));
  }
});

// source/mian/vkKey.ts
var vkKey_exports = {};
__export(vkKey_exports, {
  KeyboardVKcodeComparisonEmenList: () => KeyboardVKcodeComparisonEmenList,
  KeyboardVKcodeEmenList: () => KeyboardVKcodeEmenList,
  KeyboardcodeComparisonTable: () => KeyboardcodeComparisonTable,
  KeyboardcodeEmenList: () => KeyboardcodeEmenList,
  vkKey: () => vkKey
});
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
var KeyboardcodeComparisonTable, KeyboardVKcodeComparisonEmenList, KeyboardVKcodeEmenList, KeyboardcodeEmenList;
var init_vkKey = __esm({
  "source/mian/vkKey.ts"() {
    "use strict";
    KeyboardcodeComparisonTable = /* @__PURE__ */ new Map();
    KeyboardVKcodeComparisonEmenList = [
      ["Escape", null, 27, 27, ["esc"]],
      ["F1", null, 112, 112]
    ];
    KeyboardVKcodeEmenList = [
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
      ["Separator", null, 108, 108, [" "]],
      [";", "Semicolon", 186, 186],
      ["+", "Equal", 187, 187],
      [",", "Comma", 188, 188],
      ["-", "Minus", 189, 189],
      [".", "Period", 190, 190],
      ["/", "Slash", 191, 191],
      ["`", "Backquote", 192, 192],
      ["[", "BracketLeft", 219, 219],
      ["\\", "Backslash", 220, 220],
      ["]", "BracketRight", 221, 221],
      ["'", "Quote", 222, 222],
      ["Enter", "NumpadEnter", 224, 224]
    ];
    KeyboardcodeEmenList = (() => {
      let data = /* @__PURE__ */ new Map();
      for (let index = 0; index < KeyboardVKcodeEmenList.length; index++) {
        const [VK_key, VK_code, VK_keyCode, VK_VirtualKey, VK_Nickname] = KeyboardVKcodeEmenList[index];
        data.set(VK_VirtualKey, KeyboardVKcodeEmenList[index]);
      }
      return data;
    })();
  }
});

// source/hmc-win32@2.0/source/main/auto.ts
var auto_exports = {};
__export(auto_exports, {
  keyboardHook: () => keyboardHook,
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
var VK_KEY, KeyboardcodeEmenList2, main4, util3, ref3, _Native4, Native4, HMC_MOUSE_CLASS, HmcMouseClass, HMC_KEYBOARD_CLASS, HmcKeyboardClass, Keyboard, Iohook_Keyboard, keyboardHook;
var init_auto = __esm({
  "source/hmc-win32@2.0/source/main/auto.ts"() {
    "use strict";
    VK_KEY = (init_vkKey(), __toCommonJS(vkKey_exports));
    ({ KeyboardcodeEmenList: KeyboardcodeEmenList2 } = VK_KEY);
    main4 = (init_main(), __toCommonJS(main_exports));
    util3 = (init_util(), __toCommonJS(util_exports));
    ({ ref: ref3 } = util3);
    _Native4 = (init_Native(), __toCommonJS(Native_exports));
    ({ Native: Native4 } = _Native4);
    HMC_MOUSE_CLASS = class {
      constructor() {
      }
      initMouseEventHook() {
        var _a;
        return ((_a = Native4.HMC_MOUSE_CLASS) == null ? void 0 : _a.initMouseEventHook()) || false;
      }
      isValidHookMouse() {
        var _a;
        return ((_a = Native4.HMC_MOUSE_CLASS) == null ? void 0 : _a.isValidHookMouse()) || false;
      }
      getMouseEventListJson() {
        var _a;
        return ((_a = Native4.HMC_MOUSE_CLASS) == null ? void 0 : _a.getMouseEventListJson()) || false;
      }
      stopHookMouse() {
        var _a;
        return ((_a = Native4.HMC_MOUSE_CLASS) == null ? void 0 : _a.stopHookMouse()) || false;
      }
      setLimitMouseRange(ms, x, y, right, bottom) {
        var _a;
        return ((_a = Native4.HMC_MOUSE_CLASS) == null ? void 0 : _a.setLimitMouseRange(ref3.int(ms), ref3.int(x), ref3.int(y), ref3.int(right), ref3.int(bottom))) || false;
      }
      setShakeEventTime(ms) {
        var _a;
        return ((_a = Native4.HMC_MOUSE_CLASS) == null ? void 0 : _a.setShakeEventTime(ref3.int(ms))) || false;
      }
      hasLimitMouseRangeWorker() {
        var _a;
        return ((_a = Native4.HMC_MOUSE_CLASS) == null ? void 0 : _a.hasLimitMouseRangeWorker()) || false;
      }
      stopLimitMouseRangeWorker() {
        var _a;
        return ((_a = Native4.HMC_MOUSE_CLASS) == null ? void 0 : _a.stopLimitMouseRangeWorker()) || false;
      }
    };
    HmcMouseClass = new HMC_MOUSE_CLASS();
    HMC_KEYBOARD_CLASS = class {
      constructor() {
      }
      initKeyboardEventHook() {
        var _a;
        return ((_a = Native4.HMC_KEYBOARD_CLASS) == null ? void 0 : _a.initKeyboardEventHook()) || false;
      }
      isValidHookKeyboard() {
        var _a;
        return ((_a = Native4.HMC_KEYBOARD_CLASS) == null ? void 0 : _a.isValidHookKeyboard()) || false;
      }
      getAllKeyboardEventJson() {
        var _a;
        return JSON.parse(((_a = Native4.HMC_KEYBOARD_CLASS) == null ? void 0 : _a.getAllKeyboardEventJson()) || "[]");
      }
      stopHookKeyboard() {
        var _a;
        return ((_a = Native4.HMC_KEYBOARD_CLASS) == null ? void 0 : _a.stopHookKeyboard()) || false;
      }
      hasKeysBasic() {
        var _a;
        return ((_a = Native4.HMC_KEYBOARD_CLASS) == null ? void 0 : _a.hasKeysBasic()) || {
          "alt": false,
          "ctrl": false,
          "shift": false,
          "win": false
        };
      }
      hasKeyActivate(KeysEvent) {
        var _a;
        return ((_a = Native4.HMC_KEYBOARD_CLASS) == null ? void 0 : _a.hasKeyActivate(ref3.int(KeysEvent))) || false;
      }
    };
    HmcKeyboardClass = new HMC_KEYBOARD_CLASS();
    Keyboard = class {
      /**
       * 是否按下了shift
       */
      get shiftKey() {
        return HmcKeyboardClass.hasKeyActivate(16) || HmcKeyboardClass.hasKeyActivate(161) || HmcKeyboardClass.hasKeyActivate(160);
      }
      /***
       * 是否按下了alt
       */
      get altKey() {
        return HmcKeyboardClass.hasKeyActivate(18) || HmcKeyboardClass.hasKeyActivate(164) || HmcKeyboardClass.hasKeyActivate(165);
      }
      /***
       * 是否按下了ctrl
       */
      get ctrlKey() {
        return HmcKeyboardClass.hasKeyActivate(17);
      }
      /***
       * 是否按下了win
       */
      get winKey() {
        return HmcKeyboardClass.hasKeyActivate(91) || HmcKeyboardClass.hasKeyActivate(92);
      }
      constructor(env) {
        this.id = Number(env.id);
        this.time = Number(env.time);
        this.down = Boolean(env.down);
        this.flags = Number(env.flags);
        this.keyCode = Number(env.keyCode);
        this.scanCode = Number(env.scanCode);
        this.KeyName = String(env.key);
        this.KeyNameCode = String(env.code);
        this.vKey = Number(env.keyCode);
        this.isDown = env.down ? true : false;
        let KeyboardcodeEmen = KeyboardcodeEmenList2.get(this.vKey);
        if (!KeyboardcodeEmen) {
          KeyboardcodeEmen = ["unknown", null, this.vKey, 0];
        }
        const [VK_key, VK_code, VK_keyCode, VK_VirtualKey, VK_Nickname] = KeyboardcodeEmen;
        this.keyCode = this.keyCode || VK_keyCode;
        this.key = VK_key || this.KeyName;
        this.code = VK_code || VK_key || this.KeyNameCode;
      }
    };
    Iohook_Keyboard = class {
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
        this._next_Sleep = 50;
        this._hook_Task_id = 0;
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
       * 设置于hmc 对接的刷新延迟毫秒数 数字越小读取越快但是性能消耗将会增加
       * @param Sleep 要求 10ms - 10,000
       * @default 50ms
       * @returns 
       */
      setRefreshRate(Sleep2 = 50) {
        Sleep2 = Number(Sleep2);
        if (isNaN(Sleep2))
          return false;
        if (Sleep2 < 10) {
          return false;
        }
        if (Sleep2 > 1e4) {
          return false;
        }
        this._next_Sleep = Sleep2;
        return true;
      }
      /**
       * 开始
       * @returns 
       */
      start() {
        let start = HmcKeyboardClass.isValidHookKeyboard();
        if (start != false)
          throw new Error("the Task Has Started.");
        const _hook_Task_id = this._hook_Task_id + 1;
        start = HmcKeyboardClass.initKeyboardEventHook();
        if (!start) {
          return false;
        }
        this._Close = false;
        keyboardHook.emit("start");
        let emit_getKeyboardNextSession = () => {
          let getKeyboardNextSession = HmcKeyboardClass.getAllKeyboardEventJson();
          if (getKeyboardNextSession == null ? void 0 : getKeyboardNextSession.length)
            keyboardHook.emit("data", getKeyboardNextSession);
          if (getKeyboardNextSession)
            for (let index = 0; index < getKeyboardNextSession.length; index++) {
              const KeyboardNextSession = getKeyboardNextSession[index];
              const KeyboardPoint = new Keyboard(KeyboardNextSession);
              keyboardHook.emit("change", KeyboardPoint);
            }
        };
        this._hook_Task_id = _hook_Task_id;
        (async () => {
          while (true) {
            if (this._hook_Task_id != _hook_Task_id || keyboardHook._Close)
              return;
            await main4.Sleep(this._next_Sleep);
            emit_getKeyboardNextSession();
          }
        })();
        return start;
      }
      /**
       * 挂起 并且不销毁已经绑定的函数 以及当前配置
       */
      suspend() {
        return HmcKeyboardClass.stopHookKeyboard();
      }
      /**
       * 解除suspend的挂起状态
       */
      next() {
        const isValidHookKeyboard = HmcKeyboardClass.isValidHookKeyboard();
        if (isValidHookKeyboard) {
          HmcKeyboardClass.stopHookKeyboard();
        }
        return HmcKeyboardClass.initKeyboardEventHook();
      }
      /**
       * 判断当前的hook是否有效 有效返回线程id
       * @returns 
       */
      isValidHook() {
        let isValidHookKeyboard = HmcKeyboardClass.isValidHookKeyboard();
        if (this._Close && isValidHookKeyboard) {
          HmcKeyboardClass.stopHookKeyboard();
          isValidHookKeyboard = HmcKeyboardClass.isValidHookKeyboard();
        }
        return isValidHookKeyboard;
      }
      /**
       * 结束
       */
      close() {
        HmcKeyboardClass.stopHookKeyboard();
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
    keyboardHook = new Iohook_Keyboard();
  }
});

// source/hmc-win32@2.0/source/main/Process.ts
var Process_exports = {};
__export(Process_exports, {
  Process: () => Process
});
function GetProcessEnvInfo2Clone(pid, command) {
  var _a;
  if (!((_a = Native5.native) == null ? void 0 : _a["getProcessEnvInfo2"])) {
    return Promise.resolve(null);
  }
  return Native5.native["getProcessEnvInfo2"](pid, command);
}
function GetProcessEnvInfo2SyncClone(pid, command) {
  var _a;
  if (!((_a = Native5.native) == null ? void 0 : _a["getProcessEnvInfo2Sync"])) {
    return null;
  }
  return Native5.native["getProcessEnvInfo2Sync"](pid, command);
}
var main5, util4, _Native5, Native5, ref4, Process;
var init_Process = __esm({
  "source/hmc-win32@2.0/source/main/Process.ts"() {
    "use strict";
    init_main();
    main5 = (init_main(), __toCommonJS(main_exports));
    util4 = (init_util(), __toCommonJS(util_exports));
    _Native5 = (init_Native(), __toCommonJS(Native_exports));
    ({ Native: Native5 } = _Native5);
    ({ ref: ref4 } = util4);
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
        if (!Native5.native.getProcessName2) {
          if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
            return Promise.resolve([]);
          }
          return Promise.resolve(null);
        }
        const data = await Native5.native.getProcessName2(ref4.int(pid), type ? ref4.int(type) : void 0);
        if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
          const data_list = data ? Array.isArray(data) ? data : data == null ? void 0 : data.split("\0") : [];
          return data_list.filter((item) => item);
        }
        return data ? String(data) : null;
      }
      Process3.getProcessName2 = getProcessName2;
      function getProcessName2Sync(pid, type) {
        if (!Native5.native.getProcessName2Sync) {
          if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
            return [];
          }
          return null;
        }
        const data = Native5.native.getProcessName2Sync(ref4.int(pid), type ? ref4.int(type) : void 0);
        if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
          const data_list = data ? Array.isArray(data) ? data : data == null ? void 0 : data.split("\0") : [];
          return data_list.filter((item) => item);
        }
        return data ? String(data) : null;
      }
      Process3.getProcessName2Sync = getProcessName2Sync;
      function getProcessFilePath2(pid, isEnumListExists, isSnapshotName) {
        return Native5.native.getProcessFilePath2 ? Native5.native.getProcessFilePath2(ref4.int(pid), ...[...isEnumListExists ? [true] : [], ...isSnapshotName ? [true] : []]) : Promise.resolve(null);
      }
      Process3.getProcessFilePath2 = getProcessFilePath2;
      function getProcessFilePath2Sync(pid, isEnumListExists, isSnapshotName) {
        return Native5.native.getProcessFilePath2Sync ? Native5.native.getProcessFilePath2Sync(ref4.int(pid), ...[...isEnumListExists ? [true] : [], ...isSnapshotName ? [true] : []]) : null;
      }
      Process3.getProcessFilePath2Sync = getProcessFilePath2Sync;
      function getProcessParentProcessMatch2(Process4) {
        return new Promise((resolve, reject) => {
          const data_list = [];
          getAllProcessListSnp2().then((process_list) => {
            for (let index = 0; index < process_list.length; index++) {
              const for_process_item = process_list[index];
              if (typeof Process4 == "number" && for_process_item.th32ProcessID == Process4) {
                return resolve(for_process_item);
              }
              if (typeof Process4 == "string" && for_process_item.szExeFile == "string") {
                data_list.push(for_process_item);
              }
              if (Process4 instanceof RegExp && for_process_item.szExeFile.match(Process4)) {
                data_list.push(for_process_item);
              }
            }
            return resolve(data_list);
          }).catch(reject);
        });
      }
      Process3.getProcessParentProcessMatch2 = getProcessParentProcessMatch2;
      function getProcessParentProcessMatch2Sync(Process4) {
        const data_list = [];
        const process_list = getAllProcessListSnp2Sync();
        for (let index = 0; index < process_list.length; index++) {
          const for_process_item = process_list[index];
          if (typeof Process4 == "number" && for_process_item.th32ProcessID == Process4) {
            return for_process_item;
          }
          if (typeof Process4 == "string" && for_process_item.szExeFile == "string") {
            data_list.push(for_process_item);
          }
          if (Process4 instanceof RegExp && for_process_item.szExeFile.match(Process4)) {
            data_list.push(for_process_item);
          }
        }
        return data_list;
      }
      Process3.getProcessParentProcessMatch2Sync = getProcessParentProcessMatch2Sync;
      async function findProcess2(ProcessName) {
        return new Promise(async (resolve, reject) => {
          var _a, _b, _c, _d;
          let result = [];
          const isMacthFile = ProcessName && typeof ProcessName != "number";
          let ProcessList = await (isMacthFile ? getAllProcessList2(true) : getAllProcessList2()).catch(reject) || [];
          for (let index = 0; index < ProcessList.length; index++) {
            const Process4 = ProcessList[index];
            if (typeof ProcessName == "string") {
              if (((_a = Process4 == null ? void 0 : Process4.name) == null ? void 0 : _a.includes(ProcessName)) || ((_b = Process4 == null ? void 0 : Process4.path) == null ? void 0 : _b.includes(ProcessName))) {
                result.push(Process4);
              }
            } else if (typeof ProcessName == "number") {
              if (Process4.pid == ProcessName) {
                let path = await getProcessFilePath2(ProcessName).catch(reject);
                Process4.path = path || null;
                Process4.name = (path == null ? void 0 : path.split(/[\\\/]+/).at(-1)) || null;
                result.push(Process4);
              }
            } else {
              if (((_c = Process4 == null ? void 0 : Process4.name) == null ? void 0 : _c.match(ProcessName)) || typeof (Process4 == null ? void 0 : Process4.path) == "string" ? (_d = Process4 == null ? void 0 : Process4.path) == null ? void 0 : _d.match(ProcessName) : false) {
                result.push(Process4);
              }
            }
          }
          resolve(result);
        });
      }
      Process3.findProcess2 = findProcess2;
      function findProcess2Sync(ProcessName) {
        var _a, _b, _c, _d;
        let result = [];
        const isMacthFile = ProcessName && typeof ProcessName != "number";
        let ProcessList = (isMacthFile ? getAllProcessList2Sync(true) : getAllProcessList2Sync()) || [];
        for (let index = 0; index < ProcessList.length; index++) {
          const Process4 = ProcessList[index];
          if (typeof ProcessName == "string") {
            if (((_a = Process4 == null ? void 0 : Process4.name) == null ? void 0 : _a.includes(ProcessName)) || ((_b = Process4 == null ? void 0 : Process4.path) == null ? void 0 : _b.includes(ProcessName))) {
              result.push(Process4);
            }
          } else if (typeof ProcessName == "number") {
            if (Process4.pid == ProcessName) {
              let path = getProcessFilePath2Sync(ProcessName);
              Process4.path = path || null;
              Process4.name = (path == null ? void 0 : path.split(/[\\\/]+/).at(-1)) || null;
              result.push(Process4);
            }
          } else {
            if (((_c = Process4 == null ? void 0 : Process4.name) == null ? void 0 : _c.match(ProcessName)) || typeof (Process4 == null ? void 0 : Process4.path) == "string" ? (_d = Process4 == null ? void 0 : Process4.path) == null ? void 0 : _d.match(ProcessName) : false) {
              result.push(Process4);
            }
          }
        }
        return result;
      }
      Process3.findProcess2Sync = findProcess2Sync;
      function sleep2(awaitTime) {
        return GetProcessEnvInfo2SyncClone(ref4.int(awaitTime), HMC2_MODE.ENV_INFO_COMMAND.SEND_SLEEP);
      }
      Process3.sleep = sleep2;
      async function Sleep2(awaitTime, Sync) {
        if (Sync) {
          return sleep2(ref4.int(awaitTime));
        }
        return new Promise(
          (resolve) => setTimeout(resolve, ref4.int(awaitTime))
        );
      }
      Process3.Sleep = Sleep2;
    })(Process || (Process = {}));
  }
});

// source/hmc-win32@2.0/source/main/Sock.ts
var Sock_exports = {};
__export(Sock_exports, {
  HMC_SOKE_PROMISEEVAL_TASK_TYPE: () => HMC_SOKE_PROMISEEVAL_TASK_TYPE,
  Network: () => Network
});
import https from "https";
import http from "http";
import dgram from "dgram";
import net from "net";
var main6, _Native6, Native6, HMC_SOKE_PROMISEEVAL_TASK_TYPE, HMC_PromiseeEvalTask2, Network;
var init_Sock = __esm({
  "source/hmc-win32@2.0/source/main/Sock.ts"() {
    "use strict";
    init_util();
    main6 = (init_main(), __toCommonJS(main_exports));
    _Native6 = (init_Native(), __toCommonJS(Native_exports));
    ({ Native: Native6 } = _Native6);
    HMC_SOKE_PROMISEEVAL_TASK_TYPE = /* @__PURE__ */ ((HMC_SOKE_PROMISEEVAL_TASK_TYPE2) => {
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["ipv4"] = 1] = "ipv4";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getIpaddressList"] = 1] = "getIpaddressList";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["ip"] = 2] = "ip";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getAdapterIP2"] = 3] = "getAdapterIP2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getNetParams2"] = 8] = "getNetParams2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getSystemProxyServer2"] = 14] = "getSystemProxyServer2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getSystemProxyPac2"] = 15] = "getSystemProxyPac2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getDomainIPaddress2"] = 17] = "getDomainIPaddress2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getHostsPath2"] = 18] = "getHostsPath2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getTCPv6PortProcessID2"] = 19] = "getTCPv6PortProcessID2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getUDPv6PortProcessID2"] = 25] = "getUDPv6PortProcessID2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getUDPv4PortProcessID2"] = 26] = "getUDPv4PortProcessID2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getTCPv4PortProcessID2"] = 27] = "getTCPv4PortProcessID2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getConnectNetList2"] = 29] = "getConnectNetList2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["isAdmin2"] = 32] = "isAdmin2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["getMacAddresses2"] = 33] = "getMacAddresses2";
      HMC_SOKE_PROMISEEVAL_TASK_TYPE2[HMC_SOKE_PROMISEEVAL_TASK_TYPE2["isSystemFor64bit2"] = 35] = "isSystemFor64bit2";
      return HMC_SOKE_PROMISEEVAL_TASK_TYPE2;
    })(HMC_SOKE_PROMISEEVAL_TASK_TYPE || {});
    HMC_PromiseeEvalTask2 = class {
      constructor() {
        this.async = {};
        this.sync = {};
        const TASK_TYPE_LIST = Object.keys(HMC_SOKE_PROMISEEVAL_TASK_TYPE);
        const _this = this;
        for (let index = 0; index < TASK_TYPE_LIST.length; index++) {
          const TASK_TYPE = TASK_TYPE_LIST[index];
          if (!TASK_TYPE || (TASK_TYPE == null ? void 0 : TASK_TYPE.match(/^\d+/)))
            continue;
          const TASK_ID = HMC_SOKE_PROMISEEVAL_TASK_TYPE[TASK_TYPE];
          _this.async[TASK_TYPE] = (...arg) => {
            var _a;
            try {
              if (!((_a = Native6.native) == null ? void 0 : _a.HMC_GetSockEnvInfo)) {
                return Promise.reject(main6.HMC2_MODE.HMCNotPlatform);
              }
              if (arg.length >= 1) {
                return Native6.native.HMC_GetSockEnvInfo(TASK_ID, ...arg);
              }
              return Native6.native.HMC_GetSockEnvInfo(TASK_ID);
            } catch (error) {
              return Promise.reject(error);
            }
          };
          _this.sync[TASK_TYPE] = (...arg) => {
            var _a;
            if (!((_a = Native6.native) == null ? void 0 : _a.HMC_GetSockEnvInfoSync)) {
              return null;
            }
            if (arg.length >= 1) {
              return Native6.native.HMC_GetSockEnvInfoSync(TASK_ID, ...arg) || null;
            }
            return Native6.native.HMC_GetSockEnvInfoSync(TASK_ID);
          };
          if (!_this[TASK_TYPE]) {
            _this[TASK_TYPE] = _this.async[TASK_TYPE];
          }
          const KEY = `${TASK_TYPE}Sync`;
          if (!_this[KEY]) {
            _this[KEY] = _this.sync[TASK_TYPE];
          }
        }
      }
    };
    ((Network3) => {
      Network3.HMC_GetSokeEnvInfo = new HMC_PromiseeEvalTask2();
      function https_get_data(url) {
        return new Promise((resolve, reject) => {
          const buffList = [];
          (() => {
            if (url.match("https://")) {
              return https;
            } else {
              return http;
            }
          })().get(url, (res) => {
            if (res.statusCode !== 200) {
              reject(new Error(`get failure statusCode: ${res.statusCode || 404}`));
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
              resolve(buff);
              buffList.length = 0;
            });
          });
        });
      }
      Network3.https_get_data = https_get_data;
      function public_ip() {
        return new Promise(async (resolve, reject) => {
          let result_ok = false;
          let ip_server_list = [
            ["http://ipwho.is/", "ip"],
            ["http://httpbin.org/ip", "origin"],
            ["https://ipapi.co/json/", "ip"],
            ["https://api.ipify.org/?format=json", "ip"],
            ["https://freeipapi.com/api/json/", "ipAddress"],
            ["https://api.ip.sb/geoip", "ip"],
            ["https://api.myip.com/", "ip"],
            ["http://ip-api.com/json/?lang=zh-CN", "ip"]
          ];
          for (const iterator of ip_server_list) {
            try {
              await https_get_data(iterator[0]).catch(() => Buffer.alloc(0)).then((response) => {
                try {
                  let data = JSON.parse(response.toString("utf-8"));
                  if (data[iterator[1]]) {
                    result_ok = true;
                    resolve(data[iterator[1]]);
                  }
                } catch (e) {
                }
              });
              if (result_ok) {
                return;
              }
            } catch (e) {
            }
          }
          reject();
        });
      }
      Network3.public_ip = public_ip;
      function freePort() {
        return new Promise((resolve, reject) => {
          let sock = net.createServer(function() {
          });
          sock.listen(0, () => {
            var _a;
            resolve(Number((_a = sock == null ? void 0 : sock.address()) == null ? void 0 : _a.port));
            sock.close();
          });
          sock.once("error", reject);
        });
      }
      Network3.freePort = freePort;
      function freePortTCP() {
        return freePort();
      }
      Network3.freePortTCP = freePortTCP;
      function freePortUDP() {
        return new Promise((resolve, reject) => {
          let udp4 = dgram.createSocket("udp4");
          udp4.bind(0);
          udp4.on("listening", function() {
            resolve && resolve(udp4.address().port);
            udp4.close();
          });
          udp4.once("error", reject);
        });
      }
      Network3.freePortUDP = freePortUDP;
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
      Network3.hasPortTCP = hasPortTCP;
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
      Network3.hasPortUDP = hasPortUDP;
      ({
        isAdmin2: (
          /**判断当前软件是否拥有管理员权限 */
          Network3.isAdmin2
        ),
        isAdmin2Sync: (
          /**判断当前软件是否拥有管理员权限 */
          Network3.isAdmin2Sync
        ),
        getMacAddresses2: (
          /**获取mac地址列表 */
          Network3.getMacAddresses2
        ),
        getMacAddresses2Sync: (
          /**获取mac地址列表 */
          Network3.getMacAddresses2Sync
        ),
        getHostsPath2Sync: (
          /**获取hosts文件的路径 */
          Network3.getHostsPath2Sync
        ),
        getHostsPath2: (
          /**获取hosts文件的路径 */
          Network3.getHostsPath2
        ),
        getSystemProxyPac2: (
          /**获取hosts文件的路径 */
          Network3.getSystemProxyPac2
        ),
        getSystemProxyPac2Sync: (
          /**获取hosts文件的路径 */
          Network3.getSystemProxyPac2Sync
        ),
        getSystemProxyServer2: (
          /**获取系统代理链接（仅在启用系统代理时） */
          Network3.getSystemProxyServer2
        ),
        getSystemProxyServer2Sync: (
          /**获取系统代理链接（仅在启用系统代理时） */
          Network3.getSystemProxyServer2Sync
        ),
        isSystemFor64bit2: (
          /**判断系统是否是64位系统 */
          Network3.isSystemFor64bit2
        ),
        isSystemFor64bit2Sync: (
          /**判断系统是否是64位系统 */
          Network3.isSystemFor64bit2Sync
        )
      } = Network3.HMC_GetSokeEnvInfo);
      async function ipv4() {
        return ref.JSONP(await Network3.HMC_GetSokeEnvInfo.ipv4(), []);
      }
      Network3.ipv4 = ipv4;
      async function getIpaddressList() {
        return ref.JSONP(await Network3.HMC_GetSokeEnvInfo.getIpaddressList(), []);
      }
      Network3.getIpaddressList = getIpaddressList;
      async function ip() {
        return ref.JSONP(await Network3.HMC_GetSokeEnvInfo.ip(), []);
      }
      Network3.ip = ip;
      async function getAdapterIP2() {
        return ref.JSONP(await Network3.HMC_GetSokeEnvInfo.getAdapterIP2(), []);
      }
      Network3.getAdapterIP2 = getAdapterIP2;
      async function getNetParams2() {
        return ref.JSONP(await Network3.HMC_GetSokeEnvInfo.getNetParams2(), null);
      }
      Network3.getNetParams2 = getNetParams2;
      async function getDomainIPaddress2(url) {
        return Network3.HMC_GetSokeEnvInfo.getDomainIPaddress2(ref.string(url || ""));
      }
      Network3.getDomainIPaddress2 = getDomainIPaddress2;
      async function getTCPv6PortProcessID2(port) {
        return Network3.HMC_GetSokeEnvInfo.getTCPv6PortProcessID2(ref.int(port));
      }
      Network3.getTCPv6PortProcessID2 = getTCPv6PortProcessID2;
      async function getUDPv6PortProcessID2(port) {
        return Network3.HMC_GetSokeEnvInfo.getUDPv6PortProcessID2(ref.int(port));
      }
      Network3.getUDPv6PortProcessID2 = getUDPv6PortProcessID2;
      async function getUDPv4PortProcessID2(port) {
        return Network3.HMC_GetSokeEnvInfo.getUDPv4PortProcessID2(ref.int(port));
      }
      Network3.getUDPv4PortProcessID2 = getUDPv4PortProcessID2;
      async function getTCPv4PortProcessID2(port) {
        return Network3.HMC_GetSokeEnvInfo.getTCPv4PortProcessID2(ref.int(port));
      }
      Network3.getTCPv4PortProcessID2 = getTCPv4PortProcessID2;
      async function getConnectNetList2(tcp, udp, tcp6, udp6) {
        return ref.JSONP(await Network3.HMC_GetSokeEnvInfo.getConnectNetList2(
          typeof tcp == "boolean" ? tcp : true,
          typeof udp == "boolean" ? udp : true,
          typeof tcp6 == "boolean" ? tcp6 : true,
          typeof udp6 == "boolean" ? udp6 : true
        ), []);
      }
      Network3.getConnectNetList2 = getConnectNetList2;
      function ipv4Sync() {
        return ref.JSONP(Network3.HMC_GetSokeEnvInfo.ipv4Sync(), []);
      }
      Network3.ipv4Sync = ipv4Sync;
      function getIpaddressListSync() {
        return ref.JSONP(Network3.HMC_GetSokeEnvInfo.getIpaddressListSync(), []);
      }
      Network3.getIpaddressListSync = getIpaddressListSync;
      function ipSync() {
        return ref.JSONP(Network3.HMC_GetSokeEnvInfo.ipSync(), []);
      }
      Network3.ipSync = ipSync;
      function getAdapterIP2Sync() {
        return ref.JSONP(Network3.HMC_GetSokeEnvInfo.getAdapterIP2Sync(), []);
      }
      Network3.getAdapterIP2Sync = getAdapterIP2Sync;
      function getNetParams2Sync() {
        return ref.JSONP(Network3.HMC_GetSokeEnvInfo.getNetParams2Sync(), null);
      }
      Network3.getNetParams2Sync = getNetParams2Sync;
      function getDomainIPaddress2Sync(url) {
        return Network3.HMC_GetSokeEnvInfo.getDomainIPaddress2Sync(ref.string(url || ""));
      }
      Network3.getDomainIPaddress2Sync = getDomainIPaddress2Sync;
      function getTCPv6PortProcessID2Sync(port) {
        return Network3.HMC_GetSokeEnvInfo.getTCPv6PortProcessID2Sync(ref.int(port));
      }
      Network3.getTCPv6PortProcessID2Sync = getTCPv6PortProcessID2Sync;
      function getUDPv6PortProcessID2Sync(port) {
        return Network3.HMC_GetSokeEnvInfo.getUDPv6PortProcessID2Sync(ref.int(port));
      }
      Network3.getUDPv6PortProcessID2Sync = getUDPv6PortProcessID2Sync;
      function getUDPv4PortProcessID2Sync(port) {
        return Network3.HMC_GetSokeEnvInfo.getUDPv4PortProcessID2Sync(ref.int(port));
      }
      Network3.getUDPv4PortProcessID2Sync = getUDPv4PortProcessID2Sync;
      function getTCPv4PortProcessID2Sync(port) {
        return Network3.HMC_GetSokeEnvInfo.getTCPv4PortProcessID2Sync(ref.int(port));
      }
      Network3.getTCPv4PortProcessID2Sync = getTCPv4PortProcessID2Sync;
      function getConnectNetList2Sync(tcp, udp, tcp6, udp6) {
        return ref.JSONP(Network3.HMC_GetSokeEnvInfo.getConnectNetList2Sync(
          typeof tcp == "boolean" ? tcp : true,
          typeof udp == "boolean" ? udp : true,
          typeof tcp6 == "boolean" ? tcp6 : true,
          typeof udp6 == "boolean" ? udp6 : true
        ), []);
      }
      Network3.getConnectNetList2Sync = getConnectNetList2Sync;
    })(Network || (Network = {}));
  }
});

// source/hmc-win32@2.0/source/main/Native.ts
var Native_exports = {};
__export(Native_exports, {
  HMC: () => HMC,
  HMC_STORE: () => HMC_STORE,
  Native: () => Native7,
  Native_v2: () => Native_v2,
  default: () => Native_default,
  get_native_v1: () => get_native_v1
});
import { createRequire } from "module";
var PromiseEval2, ShellMain, AutoMain, UtilMain, ProcessMain, RegistrMain, ShellPromiseEvalMain2, SokePromiseEvalMain, HMC_LAZY_CLASS, HMC_STORE, Native_v2, get_native_v1, HMC, Native_default, Native7;
var init_Native = __esm({
  "source/hmc-win32@2.0/source/main/Native.ts"() {
    "use strict";
    init_util();
    init_main();
    PromiseEval2 = (init_promiseEval(), __toCommonJS(promiseEval_exports));
    ShellMain = (init_shell(), __toCommonJS(shell_exports));
    AutoMain = (init_auto(), __toCommonJS(auto_exports));
    UtilMain = (init_util(), __toCommonJS(util_exports));
    ProcessMain = (init_Process(), __toCommonJS(Process_exports));
    RegistrMain = (init_registr(), __toCommonJS(registr_exports));
    ShellPromiseEvalMain2 = (init_ShellPromiseEval(), __toCommonJS(ShellPromiseEval_exports));
    SokePromiseEvalMain = (init_Sock(), __toCommonJS(Sock_exports));
    HMC_LAZY_CLASS = {
      ALL_LAZY_FUN_KEY: [
        "HMC_KEYBOARD_CLASS",
        "HMC_MOUSE_CLASS",
        "HMC_SHELL_STARTUP_CLASS",
        "HMC_SHELL_CLASS"
      ]
    };
    HMC_STORE = {
      ____native____: null,
      get native_v1() {
        if (!HMC_STORE.____native____)
          HMC_STORE.____native____ = get_native_v1();
        return HMC_STORE.____native____;
      },
      HMC_LAZY_CLASS,
      ____native__v2____: null,
      get native() {
        if (!HMC_STORE.____native__v2____)
          HMC_STORE.____native__v2____ = Native_v2().native;
        return HMC_STORE.____native__v2____;
      },
      get HMC_KEYBOARD_CLASS() {
        var _a;
        if (!HMC_STORE.____native__v2____)
          HMC_STORE.____native__v2____ = Native_v2().native;
        return (_a = HMC_STORE.____native__v2____) == null ? void 0 : _a.HMC_KEYBOARD_CLASS_LAZY;
      },
      get HMC_SHELL_CLASS() {
        if (!HMC_STORE.____native__v2____)
          HMC_STORE.____native__v2____ = Native_v2().native;
        return HMC_STORE.____native__v2____.HMC_SHELL_CLASS_LAZY;
      },
      get HMC_SHELL_STARTUP_CLASS() {
        var _a;
        if (!HMC_STORE.____native__v2____)
          HMC_STORE.____native__v2____ = Native_v2().native;
        return (_a = HMC_STORE.____native__v2____) == null ? void 0 : _a.HMC_SHELL_STARTUP_CLASS_LAZY;
      },
      get HMC_MOUSE_CLASS() {
        var _a;
        if (!HMC_STORE.____native__v2____)
          HMC_STORE.____native__v2____ = Native_v2().native;
        return (_a = HMC_STORE.____native__v2____) == null ? void 0 : _a.HMC_MOUSE_CLASS_LAZY;
      }
    };
    Native_v2 = () => {
      var _a;
      const run = {};
      let _BinPath = "";
      let _Native8 = {};
      let _Loaded = false;
      const ESM_PATH = process.env.HMC___CREATE__REQUIRE___URL__ESM_MODE_PATH;
      const version = ref.int((_a = process.version.match(/^(?:.+?)?v([0-9]+)/)) == null ? void 0 : _a[1]);
      let _require = typeof __require == "undefined" ? null : __require;
      if (ESM_PATH && version >= 11) {
        _require = createRequire(ESM_PATH || process.cwd());
      }
      function LoadNodeBin() {
        try {
          if (process.env) {
            if (process.env.USERNAME == "kiic" && process.env.msvc_dir && process.env.mode) {
              _BinPath = process.env.mode;
              _Native8 = _require && _require(_BinPath);
              return _Native8;
            }
          }
          if (_BinPath) {
            _Native8 = _require && _require(_BinPath);
            return _Native8;
          } else {
            if (process.arch.match(/^(x32|ia32)$/)) {
              return _require && _require("./bin/HMC@Beta_x86.node");
            }
            if (process.arch.match(/^x64$/)) {
              return _require && _require("./bin/HMC@Beta_x64.node");
            }
          }
          if (!process.env && process) {
            __require("./bin/HMC@Beta_x86.node");
            __require("./bin/HMC@Beta_x64.node");
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
            _Native8 = LoadNodeBin();
            _Native8.HMC_LAZY_CLASS = HMC_LAZY_CLASS;
          }
          return _Native8;
        },
        set: HMC2_MODE.ALL_NONE_FUN_CALLBECK
      });
      const result = run;
      function MAKE_HMC_LAZY_CLASS(Key) {
        const FUN_LAZY_KEY = `${Key}_LAZY`;
        const FUN_KEY = Key;
        if (!_Native8) {
          return null;
        }
        if (!HMC_LAZY_CLASS[FUN_LAZY_KEY] && _Native8[FUN_KEY]) {
          if (typeof _Native8.HMC_KEYBOARD_CLASS == "function") {
            HMC_LAZY_CLASS[FUN_LAZY_KEY] = _Native8[FUN_KEY]();
          } else {
            HMC_LAZY_CLASS[FUN_LAZY_KEY] = _Native8[FUN_KEY];
          }
        }
        return HMC_LAZY_CLASS[FUN_LAZY_KEY];
      }
      for (let index = 0; index < HMC_LAZY_CLASS.ALL_LAZY_FUN_KEY.length; index++) {
        const key = HMC_LAZY_CLASS.ALL_LAZY_FUN_KEY[index];
        Object.defineProperty(run, key, {
          enumerable: false,
          get: () => MAKE_HMC_LAZY_CLASS(key),
          set: (v) => {
            result[key] = v;
          }
        });
      }
      return result;
    };
    get_native_v1 = (binPath) => {
      var _a;
      let _BinPath = "";
      let _Native8 = null;
      let _Loaded = false;
      const ESM_PATH = process.env.HMC___CREATE__REQUIRE___URL__ESM_MODE_PATH;
      delete process.env["HMC___CREATE__REQUIRE___URL__ESM_MODE_PATH"];
      const version = ref.int((_a = process.version.match(/^(?:.+?)?v([0-9]+)/)) == null ? void 0 : _a[1]);
      let _require = typeof __require == "undefined" ? null : __require;
      if (ESM_PATH && version >= 11) {
        _require = createRequire(ESM_PATH || process.cwd());
      }
      function LoadNodeBin() {
        try {
          if (_BinPath) {
            _Native8 = _require && _require(_BinPath);
            return _Native8;
          } else {
            if (process.arch.match(/^(x32|ia32)$/)) {
              return _require && _require("./bin/HMC@v1.0_x86.node");
            }
            if (process.arch.match(/^x64$/)) {
              return _require && _require("./bin/HMC@v1.0_x64.node");
            }
          }
          if (!process.env && process) {
            __require("./bin/HMC@v1.0_x86.node");
            __require("./bin/HMC@v1.0_x64.node");
          }
        } catch (s_O) {
        }
        return {};
      }
      return function() {
        if (!_Loaded && !_BinPath) {
          if (process.arch.match(/^(x32|ia32)$/)) {
            _BinPath = "./bin/HMC@v1.0_x86.node";
          }
          if (process.arch.match(/^x64$/)) {
            _BinPath = "./bin/HMC@v1.0_x64.node";
          }
        }
        if (!_Loaded) {
          _Native8 = LoadNodeBin();
          _Native8.HMC_LAZY_CLASS = HMC_LAZY_CLASS;
        }
        return _Native8;
      }();
    };
    ((HMC3) => {
      let REG_TYPE;
      ((REG_TYPE2) => {
        REG_TYPE2[REG_TYPE2["REG_NONE"] = 0] = "REG_NONE";
        REG_TYPE2[REG_TYPE2["REG_SZ"] = 1] = "REG_SZ";
        REG_TYPE2[REG_TYPE2["REG_EXPAND_SZ"] = 2] = "REG_EXPAND_SZ";
        REG_TYPE2[REG_TYPE2["REG_BINARY"] = 3] = "REG_BINARY";
        REG_TYPE2[REG_TYPE2["REG_DWORD"] = 4] = "REG_DWORD";
        REG_TYPE2[REG_TYPE2["REG_DWORD_LITTLE_ENDIAN"] = 4] = "REG_DWORD_LITTLE_ENDIAN";
        REG_TYPE2[REG_TYPE2["REG_DWORD_BIG_ENDIAN"] = 5] = "REG_DWORD_BIG_ENDIAN";
        REG_TYPE2[REG_TYPE2["REG_LINK"] = 6] = "REG_LINK";
        REG_TYPE2[REG_TYPE2["REG_MULTI_SZ"] = 7] = "REG_MULTI_SZ";
        REG_TYPE2[REG_TYPE2["REG_RESOURCE_LIST"] = 8] = "REG_RESOURCE_LIST";
        REG_TYPE2[REG_TYPE2["REG_FULL_RESOURCE_DESCRIPTOR"] = 9] = "REG_FULL_RESOURCE_DESCRIPTOR";
        REG_TYPE2[REG_TYPE2["REG_RESOURCE_REQUIREMENTS_LIST"] = 10] = "REG_RESOURCE_REQUIREMENTS_LIST";
        REG_TYPE2[REG_TYPE2["REG_QWORD"] = 11] = "REG_QWORD";
        REG_TYPE2[REG_TYPE2["REG_QWORD_LITTLE_ENDIAN"] = 11] = "REG_QWORD_LITTLE_ENDIAN";
      })(REG_TYPE = HMC3.REG_TYPE || (HMC3.REG_TYPE = {}));
      ;
      HMC3.Hkey = {
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
      })(MouseKey = HMC3.MouseKey || (HMC3.MouseKey = {}));
      let SYSTEM_METRICS_NINDEX;
      ((SYSTEM_METRICS_NINDEX2) => {
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_ARRANGE"] = 56] = "SM_ARRANGE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CLEANBOOT"] = 67] = "SM_CLEANBOOT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CMONITORS"] = 80] = "SM_CMONITORS";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CMOUSEBUTTONS"] = 43] = "SM_CMOUSEBUTTONS";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CONVERTIBLESLATEMODE"] = 8195] = "SM_CONVERTIBLESLATEMODE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXBORDER"] = 5] = "SM_CXBORDER";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXCURSOR"] = 13] = "SM_CXCURSOR";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXDLGFRAME"] = 7] = "SM_CXDLGFRAME";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXDOUBLECLK"] = 36] = "SM_CXDOUBLECLK";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXDRAG"] = 68] = "SM_CXDRAG";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXEDGE"] = 45] = "SM_CXEDGE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXFIXEDFRAME"] = 7] = "SM_CXFIXEDFRAME";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXFOCUSBORDER"] = 83] = "SM_CXFOCUSBORDER";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXFRAME"] = 32] = "SM_CXFRAME";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXFULLSCREEN"] = 16] = "SM_CXFULLSCREEN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXHSCROLL"] = 21] = "SM_CXHSCROLL";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXHTHUMB"] = 10] = "SM_CXHTHUMB";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXICON"] = 11] = "SM_CXICON";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXICONSPACING"] = 38] = "SM_CXICONSPACING";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXMAXIMIZED"] = 61] = "SM_CXMAXIMIZED";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXMAXTRACK"] = 59] = "SM_CXMAXTRACK";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXMENUCHECK"] = 71] = "SM_CXMENUCHECK";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXMENUSIZE"] = 54] = "SM_CXMENUSIZE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXMIN"] = 28] = "SM_CXMIN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXMINIMIZED"] = 57] = "SM_CXMINIMIZED";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXMINSPACING"] = 47] = "SM_CXMINSPACING";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXMINTRACK"] = 34] = "SM_CXMINTRACK";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXPADDEDBORDER"] = 92] = "SM_CXPADDEDBORDER";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXSCREEN"] = 0] = "SM_CXSCREEN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXSIZE"] = 30] = "SM_CXSIZE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXSIZEFRAME"] = 32] = "SM_CXSIZEFRAME";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXSMICON"] = 49] = "SM_CXSMICON";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXSMSIZE"] = 52] = "SM_CXSMSIZE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXVIRTUALSCREEN"] = 78] = "SM_CXVIRTUALSCREEN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CXVSCROLL"] = 2] = "SM_CXVSCROLL";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYBORDER"] = 6] = "SM_CYBORDER";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYCAPTION"] = 4] = "SM_CYCAPTION";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYCURSOR"] = 14] = "SM_CYCURSOR";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYDLGFRAME"] = 8] = "SM_CYDLGFRAME";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYDOUBLECLK"] = 37] = "SM_CYDOUBLECLK";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYDRAG"] = 69] = "SM_CYDRAG";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYEDGE"] = 46] = "SM_CYEDGE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYFIXEDFRAME"] = 8] = "SM_CYFIXEDFRAME";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYFOCUSBORDER"] = 84] = "SM_CYFOCUSBORDER";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYFRAME"] = 33] = "SM_CYFRAME";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYFULLSCREEN"] = 17] = "SM_CYFULLSCREEN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYHSCROLL"] = 3] = "SM_CYHSCROLL";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYICON"] = 12] = "SM_CYICON";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYICONSPACING"] = 39] = "SM_CYICONSPACING";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYKANJIWINDOW"] = 18] = "SM_CYKANJIWINDOW";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYMAXIMIZED"] = 62] = "SM_CYMAXIMIZED";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYMAXTRACK"] = 60] = "SM_CYMAXTRACK";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYMENU"] = 15] = "SM_CYMENU";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYMENUCHECK"] = 72] = "SM_CYMENUCHECK";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYMENUSIZE"] = 55] = "SM_CYMENUSIZE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYMIN"] = 29] = "SM_CYMIN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYMINIMIZED"] = 58] = "SM_CYMINIMIZED";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYMINSPACING"] = 48] = "SM_CYMINSPACING";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYMINTRACK"] = 35] = "SM_CYMINTRACK";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYSCREEN"] = 1] = "SM_CYSCREEN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYSIZE"] = 31] = "SM_CYSIZE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYSIZEFRAME"] = 33] = "SM_CYSIZEFRAME";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYSMCAPTION"] = 51] = "SM_CYSMCAPTION";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYSMICON"] = 50] = "SM_CYSMICON";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYSMSIZE"] = 53] = "SM_CYSMSIZE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYVIRTUALSCREEN"] = 79] = "SM_CYVIRTUALSCREEN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYVSCROLL"] = 20] = "SM_CYVSCROLL";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_CYVTHUMB"] = 9] = "SM_CYVTHUMB";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_DBCSENABLED"] = 42] = "SM_DBCSENABLED";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_DEBUG"] = 22] = "SM_DEBUG";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_DIGITIZER"] = 94] = "SM_DIGITIZER";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_IMMENABLED"] = 82] = "SM_IMMENABLED";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_MAXIMUMTOUCHES"] = 95] = "SM_MAXIMUMTOUCHES";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_MEDIACENTER"] = 87] = "SM_MEDIACENTER";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_MENUDROPALIGNMENT"] = 40] = "SM_MENUDROPALIGNMENT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_MIDEASTENABLED"] = 74] = "SM_MIDEASTENABLED";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_MOUSEPRESENT"] = 19] = "SM_MOUSEPRESENT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_MOUSEHORIZONTALWHEELPRESENT"] = 91] = "SM_MOUSEHORIZONTALWHEELPRESENT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_MOUSEWHEELPRESENT"] = 75] = "SM_MOUSEWHEELPRESENT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_NETWORK"] = 63] = "SM_NETWORK";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_PENWINDOWS"] = 41] = "SM_PENWINDOWS";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_REMOTECONTROL"] = 8193] = "SM_REMOTECONTROL";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_REMOTESESSION"] = 4096] = "SM_REMOTESESSION";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_SAMEDISPLAYFORMAT"] = 81] = "SM_SAMEDISPLAYFORMAT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_SECURE"] = 44] = "SM_SECURE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_SERVERR2"] = 89] = "SM_SERVERR2";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_SHOWSOUNDS"] = 70] = "SM_SHOWSOUNDS";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_SHUTTINGDOWN"] = 8192] = "SM_SHUTTINGDOWN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_SLOWMACHINE"] = 73] = "SM_SLOWMACHINE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_STARTER"] = 88] = "SM_STARTER";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_SWAPBUTTON"] = 23] = "SM_SWAPBUTTON";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_SYSTEMDOCKED"] = 8196] = "SM_SYSTEMDOCKED";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_TABLETPC"] = 86] = "SM_TABLETPC";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_XVIRTUALSCREEN"] = 76] = "SM_XVIRTUALSCREEN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["SM_YVIRTUALSCREEN"] = 77] = "SM_YVIRTUALSCREEN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["ARW_BOTTOMLEFT"] = 0] = "ARW_BOTTOMLEFT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["ARW_BOTTOMRIGHT"] = 1] = "ARW_BOTTOMRIGHT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["ARW_TOPLEFT"] = 2] = "ARW_TOPLEFT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["ARW_TOPRIGHT"] = 3] = "ARW_TOPRIGHT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["ARW_DOWN"] = 4] = "ARW_DOWN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["ARW_HIDE"] = 8] = "ARW_HIDE";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["ARW_LEFT"] = 0] = "ARW_LEFT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["ARW_RIGHT"] = 0] = "ARW_RIGHT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["ARW_UP"] = 4] = "ARW_UP";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["NID_INTEGRATED_TOUCH"] = 1] = "NID_INTEGRATED_TOUCH";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["NID_EXTERNAL_TOUCH"] = 2] = "NID_EXTERNAL_TOUCH";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["NID_INTEGRATED_PEN"] = 4] = "NID_INTEGRATED_PEN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["NID_EXTERNAL_PEN"] = 8] = "NID_EXTERNAL_PEN";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["NID_MULTI_INPUT"] = 64] = "NID_MULTI_INPUT";
        SYSTEM_METRICS_NINDEX2[SYSTEM_METRICS_NINDEX2["NID_READY"] = 128] = "NID_READY";
      })(SYSTEM_METRICS_NINDEX = HMC3.SYSTEM_METRICS_NINDEX || (HMC3.SYSTEM_METRICS_NINDEX = {}));
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
      })(MouseKeyName = HMC3.MouseKeyName || (HMC3.MouseKeyName = {}));
      ;
      ;
      ;
    })(HMC || (HMC = {}));
    Native_default = HMC_STORE;
    Native7 = HMC_STORE;
  }
});

// source/hmc-win32@2.0/source/main/promiseEval.ts
var promiseEval_exports = {};
__export(promiseEval_exports, {
  HMC_PROMISEEVAL_TASK_TYPE: () => HMC_PROMISEEVAL_TASK_TYPE2,
  HMC_PromiseeEvalTask: () => HMC_PromiseeEvalTask3,
  promiseEvalTask: () => promiseEvalTask2
});
var main7, _Native7, Native8, HMC_PROMISEEVAL_TASK_TYPE2, HMC_PromiseeEvalTask3, promiseEvalTask2;
var init_promiseEval = __esm({
  "source/hmc-win32@2.0/source/main/promiseEval.ts"() {
    "use strict";
    init_util();
    main7 = (init_main(), __toCommonJS(main_exports));
    _Native7 = (init_Native(), __toCommonJS(Native_exports));
    ({ Native: Native8 } = _Native7);
    HMC_PROMISEEVAL_TASK_TYPE2 = /* @__PURE__ */ ((HMC_PROMISEEVAL_TASK_TYPE3) => {
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["getClipboardFilePaths2"] = 1] = "getClipboardFilePaths2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["captureBmp2"] = 2] = "captureBmp2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["closeWindow2"] = 3] = "closeWindow2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["getClipboardText2"] = 5] = "getClipboardText2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["getThumbnailPng2"] = 6] = "getThumbnailPng2";
      HMC_PROMISEEVAL_TASK_TYPE3[HMC_PROMISEEVAL_TASK_TYPE3["getTrayList2"] = 7] = "getTrayList2";
      return HMC_PROMISEEVAL_TASK_TYPE3;
    })(HMC_PROMISEEVAL_TASK_TYPE2 || {});
    HMC_PromiseeEvalTask3 = class {
      constructor() {
        this.async = {};
        this.sync = {};
        const TASK_TYPE_LIST = Object.keys(HMC_PROMISEEVAL_TASK_TYPE2);
        for (let index = 0; index < TASK_TYPE_LIST.length; index++) {
          const TASK_TYPE = TASK_TYPE_LIST[index];
          if (!TASK_TYPE || (TASK_TYPE == null ? void 0 : TASK_TYPE.match(/^\d+/)))
            continue;
          const TASK_ID = HMC_PROMISEEVAL_TASK_TYPE2[TASK_TYPE];
          this.async[TASK_TYPE] = (...arg) => {
            var _a;
            try {
              if (!((_a = Native8.native) == null ? void 0 : _a.HMC_PromiseEval)) {
                return Promise.reject(main7.HMC2_MODE.HMCNotPlatform);
              }
              if (arg.length >= 1) {
                return Native8.native.HMC_PromiseEval(TASK_ID, ...arg);
              }
              return Native8.native.HMC_PromiseEval(TASK_ID);
            } catch (error) {
              return Promise.reject(error);
            }
          };
          this.sync[TASK_TYPE] = (...arg) => {
            var _a;
            if (!((_a = Native8.native) == null ? void 0 : _a.HMC_PromiseEvalSync)) {
              return null;
            }
            if (arg.length >= 1) {
              return Native8.native.HMC_PromiseEvalSync(TASK_ID, ...arg) || null;
            }
            return Native8.native.HMC_PromiseEvalSync(TASK_ID);
          };
          if (!this[TASK_TYPE]) {
            this[TASK_TYPE] = this.async[TASK_TYPE];
          }
          const KEY = `${TASK_TYPE}Sync`;
          if (!this[KEY]) {
            this[KEY] = this.sync[TASK_TYPE];
          }
        }
      }
      async getClipboardFilePaths2() {
        var _a, _b;
        if (!((_a = promiseEvalTask2 == null ? void 0 : promiseEvalTask2.async) == null ? void 0 : _a.getClipboardFilePaths2)) {
          return Promise.resolve([]);
        }
        const data = await (((_b = promiseEvalTask2 == null ? void 0 : promiseEvalTask2.async) == null ? void 0 : _b.getClipboardFilePaths2()) || null);
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
        if (!((_a = promiseEvalTask2 == null ? void 0 : promiseEvalTask2.sync) == null ? void 0 : _a.getClipboardFilePaths2)) {
          return [];
        }
        const data = ((_b = promiseEvalTask2 == null ? void 0 : promiseEvalTask2.sync) == null ? void 0 : _b.getClipboardFilePaths2()) || null;
        if (typeof data == "string") {
          const temp = data ? data == null ? void 0 : data.split("\0") : [];
          if (temp.length && temp.at(-1) == "")
            temp.pop();
          return temp;
        }
        return data || [];
      }
      async getTrayList2() {
        var _a, _b;
        if (!((_a = promiseEvalTask2 == null ? void 0 : promiseEvalTask2.async) == null ? void 0 : _a.getTrayList2)) {
          return Promise.resolve([]);
        }
        let data = await (((_b = promiseEvalTask2 == null ? void 0 : promiseEvalTask2.async) == null ? void 0 : _b.getTrayList2()) || null);
        if (typeof data == "string") {
          return ref.JSONP(data) || [];
        }
        return [];
      }
      getTrayList2Sync() {
        var _a, _b;
        if (!((_a = promiseEvalTask2 == null ? void 0 : promiseEvalTask2.sync) == null ? void 0 : _a.getTrayList2)) {
          return [];
        }
        let data = ((_b = promiseEvalTask2 == null ? void 0 : promiseEvalTask2.sync) == null ? void 0 : _b.getTrayList2()) || null;
        if (typeof data == "string") {
          return ref.JSONP(data) || [];
        }
        return data || [];
      }
    };
    promiseEvalTask2 = new HMC_PromiseeEvalTask3();
  }
});

// source/hmc-win32@2.0/source/main/index.ts
var main_exports = {};
__export(main_exports, {
  Auto: () => Auto,
  HMC2_MODE: () => HMC2_MODE,
  Network: () => Network2,
  Process: () => Process2,
  Registr: () => Registr2,
  Shell: () => Shell2,
  Sleep: () => Sleep,
  Startup: () => Startup,
  Symlink: () => Symlink,
  Window: () => Window,
  default: () => main_default,
  isAdmin2: () => isAdmin2,
  isAdmin2Sync: () => isAdmin2Sync,
  isSystemFor64bit2: () => isSystemFor64bit2,
  isSystemFor64bit2Sync: () => isSystemFor64bit2Sync,
  ref: () => ref5,
  sleep: () => sleep
});
var PromiseEval3, ShellMain2, AutoMain2, UtilMain2, ProcessMain2, RegistrMain2, ShellPromiseEvalMain3, SokePromiseEvalMain2, Native9, ref5, HMC2_MODE, Auto, Startup, Shell2, Process2, Sleep, sleep, Registr2, Window, Symlink, Network2, isAdmin2, isAdmin2Sync, isSystemFor64bit2, isSystemFor64bit2Sync, HMC2, main_default;
var init_main = __esm({
  "source/hmc-win32@2.0/source/main/index.ts"() {
    PromiseEval3 = (init_promiseEval(), __toCommonJS(promiseEval_exports));
    ShellMain2 = (init_shell(), __toCommonJS(shell_exports));
    AutoMain2 = (init_auto(), __toCommonJS(auto_exports));
    UtilMain2 = (init_util(), __toCommonJS(util_exports));
    ProcessMain2 = (init_Process(), __toCommonJS(Process_exports));
    RegistrMain2 = (init_registr(), __toCommonJS(registr_exports));
    ShellPromiseEvalMain3 = (init_ShellPromiseEval(), __toCommonJS(ShellPromiseEval_exports));
    SokePromiseEvalMain2 = (init_Sock(), __toCommonJS(Sock_exports));
    Native9 = (init_Native(), __toCommonJS(Native_exports));
    ({ ref: ref5 } = UtilMain2);
    ((HMC2_MODE2) => {
      function ALL_NONE_FUN_CALLBECK(...arg) {
      }
      HMC2_MODE2.ALL_NONE_FUN_CALLBECK = ALL_NONE_FUN_CALLBECK;
      HMC2_MODE2.Hkey = {
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
      let REG_TYPE;
      ((REG_TYPE2) => {
        REG_TYPE2[REG_TYPE2["REG_NONE"] = 0] = "REG_NONE";
        REG_TYPE2[REG_TYPE2["REG_SZ"] = 1] = "REG_SZ";
        REG_TYPE2[REG_TYPE2["REG_EXPAND_SZ"] = 2] = "REG_EXPAND_SZ";
        REG_TYPE2[REG_TYPE2["REG_BINARY"] = 3] = "REG_BINARY";
        REG_TYPE2[REG_TYPE2["REG_DWORD"] = 4] = "REG_DWORD";
        REG_TYPE2[REG_TYPE2["REG_DWORD_LITTLE_ENDIAN"] = 4] = "REG_DWORD_LITTLE_ENDIAN";
        REG_TYPE2[REG_TYPE2["REG_DWORD_BIG_ENDIAN"] = 5] = "REG_DWORD_BIG_ENDIAN";
        REG_TYPE2[REG_TYPE2["REG_LINK"] = 6] = "REG_LINK";
        REG_TYPE2[REG_TYPE2["REG_MULTI_SZ"] = 7] = "REG_MULTI_SZ";
        REG_TYPE2[REG_TYPE2["REG_RESOURCE_LIST"] = 8] = "REG_RESOURCE_LIST";
        REG_TYPE2[REG_TYPE2["REG_FULL_RESOURCE_DESCRIPTOR"] = 9] = "REG_FULL_RESOURCE_DESCRIPTOR";
        REG_TYPE2[REG_TYPE2["REG_RESOURCE_REQUIREMENTS_LIST"] = 10] = "REG_RESOURCE_REQUIREMENTS_LIST";
        REG_TYPE2[REG_TYPE2["REG_QWORD"] = 11] = "REG_QWORD";
        REG_TYPE2[REG_TYPE2["REG_QWORD_LITTLE_ENDIAN"] = 11] = "REG_QWORD_LITTLE_ENDIAN";
      })(REG_TYPE = HMC2_MODE2.REG_TYPE || (HMC2_MODE2.REG_TYPE = {}));
      let LINK_TYPE_INFO;
      ((LINK_TYPE_INFO2) => {
        LINK_TYPE_INFO2[LINK_TYPE_INFO2["HARD_LINK_FILE"] = 170] = "HARD_LINK_FILE";
        LINK_TYPE_INFO2[LINK_TYPE_INFO2["SOFT_LINK_FILE"] = 168] = "SOFT_LINK_FILE";
        LINK_TYPE_INFO2[LINK_TYPE_INFO2["SOFT_LINK_DIR"] = 166] = "SOFT_LINK_DIR";
        LINK_TYPE_INFO2[LINK_TYPE_INFO2["SYMBOLIC_LINK_DIR"] = 172] = "SYMBOLIC_LINK_DIR";
        LINK_TYPE_INFO2[LINK_TYPE_INFO2["UNKNOWN"] = 0] = "UNKNOWN";
      })(LINK_TYPE_INFO || (LINK_TYPE_INFO = {}));
      ;
      ;
      let FS_MK_LINK_TARGET_TYPE;
      ((FS_MK_LINK_TARGET_TYPE2) => {
        FS_MK_LINK_TARGET_TYPE2[FS_MK_LINK_TARGET_TYPE2["CREATE_DIR_SYMLINK"] = 166] = "CREATE_DIR_SYMLINK";
        FS_MK_LINK_TARGET_TYPE2[FS_MK_LINK_TARGET_TYPE2["CREATE_SYMLINK"] = 168] = "CREATE_SYMLINK";
        FS_MK_LINK_TARGET_TYPE2[FS_MK_LINK_TARGET_TYPE2["CREATE_HARD_LINK"] = 170] = "CREATE_HARD_LINK";
        FS_MK_LINK_TARGET_TYPE2[FS_MK_LINK_TARGET_TYPE2["CREATE_JUNCTION_POINT_LINK"] = 172] = "CREATE_JUNCTION_POINT_LINK";
      })(FS_MK_LINK_TARGET_TYPE = HMC2_MODE2.FS_MK_LINK_TARGET_TYPE || (HMC2_MODE2.FS_MK_LINK_TARGET_TYPE = {}));
      let LINK_TYPE;
      ((LINK_TYPE2) => {
        LINK_TYPE2[LINK_TYPE2["HARD_LINK_FILE"] = 170] = "HARD_LINK_FILE";
        LINK_TYPE2[LINK_TYPE2["SOFT_LINK_FILE"] = 168] = "SOFT_LINK_FILE";
        LINK_TYPE2[LINK_TYPE2["SOFT_LINK_DIR"] = 166] = "SOFT_LINK_DIR";
        LINK_TYPE2[LINK_TYPE2["JUNCTION_POINT_DIR"] = 172] = "JUNCTION_POINT_DIR";
        LINK_TYPE2[LINK_TYPE2["UNKNOWN"] = 0] = "UNKNOWN";
      })(LINK_TYPE = HMC2_MODE2.LINK_TYPE || (HMC2_MODE2.LINK_TYPE = {}));
      ;
      let FILE_ATTRIBUTE_INFO_LIST;
      ((FILE_ATTRIBUTE_INFO_LIST2) => {
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_READONLY"] = 1] = "FILE_ATTRIBUTE_READONLY";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_HIDDEN"] = 2] = "FILE_ATTRIBUTE_HIDDEN";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_SYSTEM"] = 4] = "FILE_ATTRIBUTE_SYSTEM";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_DIRECTORY"] = 16] = "FILE_ATTRIBUTE_DIRECTORY";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_ARCHIVE"] = 32] = "FILE_ATTRIBUTE_ARCHIVE";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_DEVICE"] = 64] = "FILE_ATTRIBUTE_DEVICE";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_NORMAL"] = 128] = "FILE_ATTRIBUTE_NORMAL";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_TEMPORARY"] = 256] = "FILE_ATTRIBUTE_TEMPORARY";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_SPARSE_FILE"] = 512] = "FILE_ATTRIBUTE_SPARSE_FILE";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_REPARSE_POINT"] = 1024] = "FILE_ATTRIBUTE_REPARSE_POINT";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_COMPRESSED"] = 2048] = "FILE_ATTRIBUTE_COMPRESSED";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_OFFLINE"] = 4096] = "FILE_ATTRIBUTE_OFFLINE";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_NOT_CONTENT_INDEXED"] = 8192] = "FILE_ATTRIBUTE_NOT_CONTENT_INDEXED";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_ENCRYPTED"] = 16384] = "FILE_ATTRIBUTE_ENCRYPTED";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_VIRTUAL"] = 65536] = "FILE_ATTRIBUTE_VIRTUAL";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_INTEGRITY_STREAM"] = 32768] = "FILE_ATTRIBUTE_INTEGRITY_STREAM";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_NO_SCRUB_DATA"] = 131072] = "FILE_ATTRIBUTE_NO_SCRUB_DATA";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_EA"] = 262144] = "FILE_ATTRIBUTE_EA";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_PINNED"] = 524288] = "FILE_ATTRIBUTE_PINNED";
        FILE_ATTRIBUTE_INFO_LIST2[FILE_ATTRIBUTE_INFO_LIST2["FILE_ATTRIBUTE_UNPINNED"] = 1048576] = "FILE_ATTRIBUTE_UNPINNED";
      })(FILE_ATTRIBUTE_INFO_LIST = HMC2_MODE2.FILE_ATTRIBUTE_INFO_LIST || (HMC2_MODE2.FILE_ATTRIBUTE_INFO_LIST = {}));
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
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["SEND_SLEEP"] = 22] = "SEND_SLEEP";
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
      ((ENV_INFO_COMMAND2) => {
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["NONE"] = 0] = "NONE";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_REGISTR_QWORD"] = 70] = "GET_REGISTR_QWORD";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["SET_REGISTR_QWORD"] = 71] = "SET_REGISTR_QWORD";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_REGISTR_DWORD"] = 72] = "GET_REGISTR_DWORD";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["SET_REGISTR_DWORD"] = 73] = "SET_REGISTR_DWORD";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_REGISTR_STRING"] = 74] = "GET_REGISTR_STRING";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["SET_REGISTR_STRING"] = 75] = "SET_REGISTR_STRING";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_REGISTR_KEYS"] = 76] = "GET_REGISTR_KEYS";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_REGISTR_STRING_LIST"] = 77] = "GET_REGISTR_STRING_LIST";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["SET_REGISTR_STRING_LIST"] = 78] = "SET_REGISTR_STRING_LIST";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_REGISTR_BUFFER"] = 79] = "GET_REGISTR_BUFFER";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["SET_REGISTR_BUFFER"] = 710] = "SET_REGISTR_BUFFER";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_REGISTR_VALUE"] = 711] = "GET_REGISTR_VALUE";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["COPY_REGISTR_VALUE"] = 712] = "COPY_REGISTR_VALUE";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["COPY_REGISTR_FOLDER"] = 713] = "COPY_REGISTR_FOLDER";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["SET_REGISTR_VALUE"] = 714] = "SET_REGISTR_VALUE";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_REGISTR_VALUE_STAT"] = 715] = "GET_REGISTR_VALUE_STAT";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["GET_REGISTR_FOLDER_STAT"] = 716] = "GET_REGISTR_FOLDER_STAT";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["CLEAR_REGISTR_VALUE"] = 717] = "CLEAR_REGISTR_VALUE";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["CLEAR_REGISTR_FOLDER"] = 718] = "CLEAR_REGISTR_FOLDER";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["REMOVE_REGISTR_VALUE"] = 719] = "REMOVE_REGISTR_VALUE";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["REMOVE_REGISTR_FOLDER"] = 720] = "REMOVE_REGISTR_FOLDER";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["REMOVE_REGISTR_FOLDER_TREE"] = 721] = "REMOVE_REGISTR_FOLDER_TREE";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["CREATE_REGISTR_FOLDER"] = 722] = "CREATE_REGISTR_FOLDER";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["CREATE_REGISTR_VALUE_KEY"] = 723] = "CREATE_REGISTR_VALUE_KEY";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["HAS_REGISTR_KEY"] = 724] = "HAS_REGISTR_KEY";
        ENV_INFO_COMMAND2[ENV_INFO_COMMAND2["HAS_REGISTR_FOLDER_KEY"] = 725] = "HAS_REGISTR_FOLDER_KEY";
      })(ENV_INFO_COMMAND = HMC2_MODE2.ENV_INFO_COMMAND || (HMC2_MODE2.ENV_INFO_COMMAND = {}));
      ;
      let Net;
      ((Net2) => {
        let network_type;
        ((network_type2) => {
          network_type2[network_type2["AF_UNSPEC"] = 0] = "AF_UNSPEC";
          network_type2[network_type2["AF_UNIX"] = 1] = "AF_UNIX";
          network_type2[network_type2["AF_INET"] = 2] = "AF_INET";
          network_type2[network_type2["AF_IMPLINK"] = 3] = "AF_IMPLINK";
          network_type2[network_type2["AF_PUP"] = 4] = "AF_PUP";
          network_type2[network_type2["AF_CHAOS"] = 5] = "AF_CHAOS";
          network_type2[network_type2["AF_NS"] = 6] = "AF_NS";
          network_type2[network_type2["AF_IPX"] = 6] = "AF_IPX";
          network_type2[network_type2["AF_ISO"] = 7] = "AF_ISO";
          network_type2[network_type2["AF_OSI"] = 7] = "AF_OSI";
          network_type2[network_type2["AF_ECMA"] = 8] = "AF_ECMA";
          network_type2[network_type2["AF_DATAKIT"] = 9] = "AF_DATAKIT";
          network_type2[network_type2["AF_CCITT"] = 10] = "AF_CCITT";
          network_type2[network_type2["AF_SNA"] = 11] = "AF_SNA";
          network_type2[network_type2["AF_DECnet"] = 12] = "AF_DECnet";
          network_type2[network_type2["AF_DLI"] = 13] = "AF_DLI";
          network_type2[network_type2["AF_LAT"] = 14] = "AF_LAT";
          network_type2[network_type2["AF_HYLINK"] = 15] = "AF_HYLINK";
          network_type2[network_type2["AF_APPLETALK"] = 16] = "AF_APPLETALK";
          network_type2[network_type2["AF_NETBIOS"] = 17] = "AF_NETBIOS";
          network_type2[network_type2["AF_VOICEVIEW"] = 18] = "AF_VOICEVIEW";
          network_type2[network_type2["AF_FIREFOX"] = 19] = "AF_FIREFOX";
          network_type2[network_type2["AF_UNKNOWN1"] = 20] = "AF_UNKNOWN1";
          network_type2[network_type2["AF_BAN"] = 21] = "AF_BAN";
          network_type2[network_type2["AF_ATM"] = 22] = "AF_ATM";
          network_type2[network_type2["AF_INET6"] = 23] = "AF_INET6";
          network_type2[network_type2["AF_CLUSTER"] = 24] = "AF_CLUSTER";
          network_type2[network_type2["AF_12844"] = 25] = "AF_12844";
          network_type2[network_type2["AF_IRDA"] = 26] = "AF_IRDA";
          network_type2[network_type2["AF_NETDES"] = 28] = "AF_NETDES";
        })(network_type = Net2.network_type || (Net2.network_type = {}));
      })(Net = HMC2_MODE2.Net || (HMC2_MODE2.Net = {}));
    })(HMC2_MODE || (HMC2_MODE = {}));
    Auto = AutoMain2;
    Startup = ShellMain2.Shell.Startup;
    Shell2 = ShellMain2.Shell;
    Process2 = ProcessMain2.Process;
    ({ Sleep, sleep } = Process2);
    Registr2 = RegistrMain2.Registr;
    ((Window2) => {
      function readElectronHandle(handleBuffer) {
        let num = 0;
        if (typeof BigInt != "undefined") {
          let handleBigInt = handleBuffer.readBigUInt64LE();
          return Number(handleBigInt);
        } else {
          if (process.platform == "win32") {
            num = handleBuffer.readUInt32LE();
          } else if (process.platform == "darwin") {
            num = handleBuffer.readUInt32LE(0) + 2 * 32 * handleBuffer.readUInt32LE(4);
          } else {
            num = handleBuffer.readUInt32LE(0) + 2 * 32 * handleBuffer.readUInt32LE(4);
          }
          return num;
        }
        return num;
      }
      Window2.readElectronHandle = readElectronHandle;
    })(Window || (Window = {}));
    Symlink = ShellMain2.Shell.Symlink;
    Network2 = SokePromiseEvalMain2.Network;
    ({ isAdmin2, isAdmin2Sync, isSystemFor64bit2, isSystemFor64bit2Sync } = Network2);
    HMC2 = {
      Native: Native9,
      Auto,
      Startup,
      Shell: Shell2,
      Process: Process2,
      Registr: Registr2,
      Window,
      Symlink,
      Network: Network2,
      Sleep,
      sleep,
      isAdmin2,
      isAdmin2Sync,
      isSystemFor64bit2,
      isSystemFor64bit2Sync
    };
    main_default = HMC2;
    process.on("exit", function() {
    });
  }
});
init_main();
export {
  Auto,
  HMC2_MODE,
  Network2 as Network,
  Process2 as Process,
  Registr2 as Registr,
  Shell2 as Shell,
  Sleep,
  Startup,
  Symlink,
  Window,
  main_default as default,
  isAdmin2,
  isAdmin2Sync,
  isSystemFor64bit2,
  isSystemFor64bit2Sync,
  ref5 as ref,
  sleep
};
