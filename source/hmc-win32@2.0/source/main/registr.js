"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Registr = void 0;
const util = require("./util");
const main = require("./index");
const index_1 = require("./index");
//注册表编辑合集
var Registr;
(function (Registr) {
    const { ref } = util;
    async function GetRegistrEnvInfo(ENV_INFO_COMMAND, HKey, ...aegs) {
        var _a;
        const _GetRegistrEnvInfo = (_a = main.Native.native) === null || _a === void 0 ? void 0 : _a.GetRegistrEnvInfo;
        if (!_GetRegistrEnvInfo)
            return Promise.reject("not func -> GetRegistrEnvInfo");
        return _GetRegistrEnvInfo(ENV_INFO_COMMAND, HKey, ...aegs);
    }
    function GetRegistrEnvInfoSync(ENV_INFO_COMMAND, HKey, ...aegs) {
        var _a;
        const _GetRegistrEnvInfoSync = (_a = main.Native.native) === null || _a === void 0 ? void 0 : _a.GetRegistrEnvInfoSync;
        if (!_GetRegistrEnvInfoSync)
            return null;
        return _GetRegistrEnvInfoSync(ENV_INFO_COMMAND, HKey, ...aegs);
    }
    /**
     * `异步` 获取内容(64位数字)
     * @param HKEY 根路径
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey 路径 类似于如同目录路径概念
     * @param key 键名称  `""` `null` 将作为默认key
     * @time 0.06787109375 ms
     * @returns
     */
    async function getRegistrQword2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_QWORD, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {
            return BigInt(data);
        }
        return null;
    }
    Registr.getRegistrQword2 = getRegistrQword2;
    /**
     * `异步` 设置内容(64位数字)
     * @param HKEY 根路径
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey 路径 类似于如同目录路径概念
     * @param key 键名称  `""` `null` 将作为默认key
     * @param Qword 64位数字，接受 `bigint` 或 `number` 类型
     */
    async function setRegistrQword2(HKey, SubKey, key, Qword) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_QWORD, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), ref.int(Qword || 0));
        return ref.bool(data);
    }
    Registr.setRegistrQword2 = setRegistrQword2;
    /**
     * `异步` 获取内容(32位数字)
     * @param HKEY 根路径
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey 路径 类似于如同目录路径概念
     * @param key 键名称  `""` `null` 将作为默认key
     */
    async function getRegistrDword2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_DWORD, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {
            return ref.long(data);
        }
        return null;
    }
    Registr.getRegistrDword2 = getRegistrDword2;
    /**
     * `异步` 设置内容(32位数字)
     * @param HKEY 根路径
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey 路径 类似于如同目录路径概念
     * @param key 键名称  `""` `null` 将作为默认key
     * @param Dword 32位数字，接受 `bigint` 或 `number` 类型
     */
    async function setRegistrDword2(HKey, SubKey, key, Dword) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_DWORD, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), ref.long(Dword));
        return ref.bool(data);
    }
    Registr.setRegistrDword2 = setRegistrDword2;
    /**
     * `异步` 获取注册表字符串值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function getRegistrString2(HKey, SubKey, key, expand) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), expand ? true : false);
        return typeof data == "string" ? data : null;
    }
    Registr.getRegistrString2 = getRegistrString2;
    /**
     * `异步` 设置注册表字符串值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     * @param String - 要设置的字符串值
     */
    async function setRegistrString2(HKey, SubKey, key, String, expand) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), ref.string(String || ""), expand ? true : false);
        return ref.bool(data);
    }
    Registr.setRegistrString2 = setRegistrString2;
    /**
     * `异步` 枚举注册表目录的所有键
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function getRegistrKeys2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_KEYS, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return data ? JSON.parse(String(data)) : null;
    }
    Registr.getRegistrKeys2 = getRegistrKeys2;
    /**
     * `异步` 获取注册表字符串值列表
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function getRegistrStringList2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING_LIST, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        if (typeof data == "string") {
            if (data[0] == "[") {
                return ref.JSONP(data);
            }
            if (data.includes('\0')) {
                const temp = data.split(/\0+/);
                if (temp.at(-1) == "") {
                    temp.pop();
                }
                return temp;
            }
        }
        return Array.isArray(data) ? data : null;
    }
    Registr.getRegistrStringList2 = getRegistrStringList2;
    /**
     * `异步` 设置注册表字符串值列表
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     * @param StringList - 要设置的字符串值列表
     */
    async function setRegistrStringList2(HKey, SubKey, key, StringList) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING_LIST, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), Array.isArray(StringList) ? ref.stringArray(StringList) : ref.convertMultiStringArray(ref.string(StringList || "")) || []);
        return ref.bool(data);
    }
    Registr.setRegistrStringList2 = setRegistrStringList2;
    /**
     * `异步` 获取注册表缓冲区值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function getRegistrBuffer2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_BUFFER, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return Buffer.isBuffer(data) ? data : null;
    }
    Registr.getRegistrBuffer2 = getRegistrBuffer2;
    /**
     * `异步` 设置注册表缓冲区值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     * @param String - 要设置的缓冲区值
     */
    async function setRegistrBuffer2(HKey, SubKey, key, Buff) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_BUFFER, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), Buff);
        return ref.bool(data);
    }
    Registr.setRegistrBuffer2 = setRegistrBuffer2;
    /**
     * `异步` 获取注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function getRegistrValue2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return data ? data : null;
    }
    /**
     * `异步` 复制注册表值
     * @param HKey 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SourceSubKey 源子键路径
     * @param Sourcekey 源取值的键名
     * @param NewSubKey 新子键路径
     * @param Newkey 新取值的键名
     */
    async function copyRegistrValue2(HKey, SourceSubKey, Sourcekey, NewSubKey, Newkey) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_VALUE, ref.string(HKey), ref.string(SourceSubKey), ref.string(Sourcekey || ""), ref.string(NewSubKey || ""), ref.string(Newkey || ""));
        return ref.bool(data);
    }
    Registr.copyRegistrValue2 = copyRegistrValue2;
    /**
     * `异步` 复制注册表 目录
     * @param HKey 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SourceSubKey 源路径
     * @param NewSubKey 新路径
     */
    async function copyRegistrFolder2(HKey, SourceSubKey, NewSubKey) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_FOLDER, ref.string(HKey), ref.string(SourceSubKey), ref.string(NewSubKey || ""));
        return ref.bool(data);
    }
    Registr.copyRegistrFolder2 = copyRegistrFolder2;
    /**
     * `异步` 设置注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     * @param data - 要设置的注册表值
     */
    async function setRegistrValue2(HKey, SubKey, key, data) {
        const data_2 = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_VALUE, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), data);
        return ref.bool(data_2);
    }
    Registr.setRegistrValue2 = setRegistrValue2;
    /**
     * `异步` 获取注册表值状态
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function getRegistrValueStat2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE_STAT, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return data ? data : null;
    }
    Registr.getRegistrValueStat2 = getRegistrValueStat2;
    /**
     * `异步` 获取注册表文件夹状态
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function getRegistrFolderStat2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_FOLDER_STAT, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return data ? JSON.parse(String(data)) : null;
    }
    Registr.getRegistrFolderStat2 = getRegistrFolderStat2;
    /**
     * `异步` 清除注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function clearRegistrValue2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_VALUE, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return ref.bool(data);
    }
    Registr.clearRegistrValue2 = clearRegistrValue2;
    /**
     * `异步` 清除注册表文件夹
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function clearRegistrFolder2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_FOLDER, ref.string(HKey), ref.string(SubKey), ref.string(""));
        return ref.bool(data);
    }
    Registr.clearRegistrFolder2 = clearRegistrFolder2;
    /**
     * `异步` 删除注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function removeRegistrValue2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_VALUE, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return ref.bool(data);
    }
    Registr.removeRegistrValue2 = removeRegistrValue2;
    /**
     * `异步` 删除注册表文件夹
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    async function removeRegistrFolder2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER, ref.string(HKey), ref.string(SubKey));
        return ref.bool(data);
    }
    Registr.removeRegistrFolder2 = removeRegistrFolder2;
    /**
     * `异步` 删除注册表文件夹树
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    async function removeRegistrFolderTree2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER_TREE, ref.string(HKey), ref.string(SubKey));
        return ref.bool(data);
    }
    Registr.removeRegistrFolderTree2 = removeRegistrFolderTree2;
    /**
     * `异步` 创建注册表文件夹
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param folderPath - 要创建的文件夹路径
     */
    async function createRegistrFolder2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_FOLDER, ref.string(HKey), ref.string(SubKey));
        return ref.bool(data);
    }
    Registr.createRegistrFolder2 = createRegistrFolder2;
    /**
     * `异步` 创建注册表值键
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param folderPath - 要创建值键的文件夹路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function createRegistrValueKey2(HKey, SubKey, key, type) {
        const regVlaue = {};
        if (typeof key == "string") {
            if (typeof type == "number") {
                regVlaue[key] = type;
            }
            else {
                regVlaue[key] = index_1.HMC2_MODE.REG_TYPE.REG_NONE;
            }
        }
        else if (Array.isArray(key)) {
            for (const Ckey of key) {
                regVlaue[Ckey] = typeof type == "number" ? type : index_1.HMC2_MODE.REG_TYPE.REG_NONE;
            }
        }
        else if (key && typeof key == "object") {
            for (const Ckey in key) {
                regVlaue[Ckey] = key[Ckey];
            }
        }
        const bool_list = [];
        for (const key in regVlaue) {
            const type = regVlaue[key] || index_1.HMC2_MODE.REG_TYPE.REG_NONE;
            const keyname = key;
            const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_VALUE_KEY, ref.string(HKey), ref.string(SubKey), ref.string(keyname), ref.int(type));
            bool_list.push(data ? true : false);
        }
        return ref.bool(bool_list.length == 1 ? bool_list.pop() : bool_list.at(-1) || false);
    }
    Registr.createRegistrValueKey2 = createRegistrValueKey2;
    /**
     * `异步` 判断注册表 键值 存在性
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    async function hasRegistrKey2(HKey, SubKey, key) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_KEY, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return ref.bool(data);
    }
    Registr.hasRegistrKey2 = hasRegistrKey2;
    /**
     * `异步` 判断注册表 目录 存在性
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    async function hasRegistrFolderKey2(HKey, SubKey) {
        const data = await GetRegistrEnvInfo(index_1.HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_FOLDER_KEY, ref.string(HKey), ref.string(SubKey));
        return ref.bool(data);
    }
    Registr.hasRegistrFolderKey2 = hasRegistrFolderKey2;
    /**
 * `同步` 获取内容(64位数字)
 * @param HKEY 根路径
 * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
 * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
 * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
 * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
 * @param SubKey 路径 类似于如同目录路径概念
 * @param key 键名称  `""` `null` 将作为默认key
 * @time 0.06787109375 ms
 * @returns
 */
    function getRegistrQword2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_QWORD, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {
            return BigInt(data);
        }
        return null;
    }
    Registr.getRegistrQword2Sync = getRegistrQword2Sync;
    /**
     * `同步` 设置内容(64位数字)
     * @param HKEY 根路径
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey 路径 类似于如同目录路径概念
     * @param key 键名称  `""` `null` 将作为默认key
     * @param Qword 64位数字，接受 `bigint` 或 `number` 类型
     */
    function setRegistrQword2Sync(HKey, SubKey, key, Qword) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_QWORD, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), ref.int(Qword || 0));
        return ref.bool(data);
    }
    Registr.setRegistrQword2Sync = setRegistrQword2Sync;
    /**
     * `同步` 获取内容(32位数字)
     * @param HKEY 根路径
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey 路径 类似于如同目录路径概念
     * @param key 键名称  `""` `null` 将作为默认key
     */
    function getRegistrDword2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_DWORD, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {
            return ref.long(data);
        }
        return null;
    }
    Registr.getRegistrDword2Sync = getRegistrDword2Sync;
    /**
     * `同步` 设置内容(32位数字)
     * @param HKEY 根路径
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey 路径 类似于如同目录路径概念
     * @param key 键名称  `""` `null` 将作为默认key
     * @param Dword 32位数字，接受 `bigint` 或 `number` 类型
     */
    function setRegistrDword2Sync(HKey, SubKey, key, Dword) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_DWORD, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), ref.long(Dword));
        return ref.bool(data);
    }
    Registr.setRegistrDword2Sync = setRegistrDword2Sync;
    /**
     * `同步` 获取注册表字符串值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function getRegistrString2Sync(HKey, SubKey, key, expand) {
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), expand ? true : false);
        return typeof data == "string" ? data : null;
    }
    Registr.getRegistrString2Sync = getRegistrString2Sync;
    /**
     * `同步` 设置注册表字符串值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     * @param String - 要设置的字符串值
     */
    function setRegistrString2Sync(HKey, SubKey, key, String, expand) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), ref.string(String || ""), expand ? true : false);
        return ref.bool(data);
    }
    Registr.setRegistrString2Sync = setRegistrString2Sync;
    /**
     * `同步` 枚举注册表目录的所有键
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function getRegistrKeys2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_KEYS, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return data ? JSON.parse(String(data)) : null;
    }
    Registr.getRegistrKeys2Sync = getRegistrKeys2Sync;
    /**
     * `同步` 获取注册表字符串值列表
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function getRegistrStringList2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING_LIST, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        if (typeof data == "string") {
            if (data[0] == "[") {
                return ref.JSONP(data);
            }
            if (data.includes('\0')) {
                const temp = data.split(/\0+/);
                if (temp.at(-1) == "") {
                    temp.pop();
                }
                return temp;
            }
        }
        return Array.isArray(data) ? data : null;
    }
    Registr.getRegistrStringList2Sync = getRegistrStringList2Sync;
    /**
     * `同步` 设置注册表字符串值列表
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     * @param StringList - 要设置的字符串值列表
     */
    function setRegistrStringList2Sync(HKey, SubKey, key, StringList) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING_LIST, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), Array.isArray(StringList) ? ref.stringArray(StringList) : ref.convertMultiStringArray(ref.string(StringList || "")) || []);
        return ref.bool(data);
    }
    Registr.setRegistrStringList2Sync = setRegistrStringList2Sync;
    /**
     * `同步` 获取注册表缓冲区值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function getRegistrBuffer2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_BUFFER, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return Buffer.isBuffer(data) ? data : null;
    }
    Registr.getRegistrBuffer2Sync = getRegistrBuffer2Sync;
    /**
     * `同步` 设置注册表缓冲区值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     * @param String - 要设置的缓冲区值
     */
    function setRegistrBuffer2Sync(HKey, SubKey, key, Buff) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_BUFFER, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), Buff);
        return ref.bool(data);
    }
    Registr.setRegistrBuffer2Sync = setRegistrBuffer2Sync;
    /**
     * `同步` 获取注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function getRegistrValue2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return data ? data : null;
    }
    /**
     * `同步` 复制注册表值
     * @param HKey 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SourceSubKey 源子键路径
     * @param Sourcekey 源取值的键名
     * @param NewSubKey 新子键路径
     * @param Newkey 新取值的键名
     */
    function copyRegistrValue2Sync(HKey, SourceSubKey, Sourcekey, NewSubKey, Newkey) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_VALUE, ref.string(HKey), ref.string(SourceSubKey), ref.string(Sourcekey || ""), ref.string(NewSubKey || ""), ref.string(Newkey || ""));
        return ref.bool(data);
    }
    Registr.copyRegistrValue2Sync = copyRegistrValue2Sync;
    /**
     * `同步` 复制注册表 目录
     * @param HKey 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SourceSubKey 源路径
     * @param NewSubKey 新路径
     */
    function copyRegistrFolder2Sync(HKey, SourceSubKey, NewSubKey) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_FOLDER, ref.string(HKey), ref.string(SourceSubKey), ref.string(NewSubKey || ""));
        return ref.bool(data);
    }
    Registr.copyRegistrFolder2Sync = copyRegistrFolder2Sync;
    /**
     * `同步` 设置注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     * @param data - 要设置的注册表值
     */
    function setRegistrValue2Sync(HKey, SubKey, key, data) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data_2 = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_VALUE, ref.string(HKey), ref.string(SubKey), ref.string(key || ""), data);
        return ref.bool(data_2);
    }
    /**
     * `同步` 获取注册表值状态
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function getRegistrValueStat2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE_STAT, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return data || null;
    }
    Registr.getRegistrValueStat2Sync = getRegistrValueStat2Sync;
    /**
     * `同步` 获取注册表文件夹状态
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function getRegistrFolderStat2Sync(HKey, SubKey, key) {
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_FOLDER_STAT, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return data ? JSON.parse(String(data)) : null;
    }
    Registr.getRegistrFolderStat2Sync = getRegistrFolderStat2Sync;
    /**
     * `同步` 清除注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function clearRegistrValue2Sync(HKey, SubKey, key) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_VALUE, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return ref.bool(data);
    }
    Registr.clearRegistrValue2Sync = clearRegistrValue2Sync;
    /**
     * `同步` 清除注册表文件夹
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function clearRegistrFolder2Sync(HKey, SubKey) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_FOLDER, ref.string(HKey), ref.string(SubKey), ref.string(""));
        return ref.bool(data);
    }
    Registr.clearRegistrFolder2Sync = clearRegistrFolder2Sync;
    /**
     * `同步` 删除注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function removeRegistrValue2Sync(HKey, SubKey, key) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_VALUE, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return ref.bool(data);
    }
    Registr.removeRegistrValue2Sync = removeRegistrValue2Sync;
    /**
     * `同步` 删除注册表文件夹
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    function removeRegistrFolder2Sync(HKey, SubKey) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER, ref.string(HKey), ref.string(SubKey));
        return ref.bool(data);
    }
    Registr.removeRegistrFolder2Sync = removeRegistrFolder2Sync;
    /**
     * `同步` 删除注册表文件夹树
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    function removeRegistrFolderTree2Sync(HKey, SubKey) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER_TREE, ref.string(HKey), ref.string(SubKey));
        return ref.bool(data);
    }
    Registr.removeRegistrFolderTree2Sync = removeRegistrFolderTree2Sync;
    /**
     * `同步` 创建注册表文件夹
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param folderPath - 要创建的文件夹路径
     */
    function createRegistrFolder2Sync(HKey, SubKey) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_FOLDER, ref.string(HKey), ref.string(SubKey));
        return ref.bool(data);
    }
    Registr.createRegistrFolder2Sync = createRegistrFolder2Sync;
    /**
     * `同步` 创建注册表值键
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param folderPath - 要创建值键的文件夹路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function createRegistrValueKey2Sync(HKey, SubKey, key, type) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const regVlaue = {};
        if (typeof key == "string") {
            if (typeof type == "number") {
                regVlaue[key] = type;
            }
            else {
                regVlaue[key] = index_1.HMC2_MODE.REG_TYPE.REG_NONE;
            }
        }
        else if (Array.isArray(key)) {
            for (const Ckey of key) {
                regVlaue[Ckey] = typeof type == "number" ? type : index_1.HMC2_MODE.REG_TYPE.REG_NONE;
            }
        }
        else if (key && typeof key == "object") {
            for (const Ckey in key) {
                regVlaue[Ckey] = key[Ckey];
            }
        }
        const bool_list = [];
        for (const key in regVlaue) {
            const type = regVlaue[key] || index_1.HMC2_MODE.REG_TYPE.REG_NONE;
            const keyname = key;
            const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_VALUE_KEY, ref.string(HKey), ref.string(SubKey), ref.string(keyname), ref.int(type));
            bool_list.push(data ? true : false);
        }
        return ref.bool(bool_list.length == 1 ? bool_list.pop() : bool_list.at(-1) || false);
    }
    Registr.createRegistrValueKey2Sync = createRegistrValueKey2Sync;
    /**
     * `同步` 判断注册表 键值 存在性
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    function hasRegistrKey2Sync(HKey, SubKey, key) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_KEY, ref.string(HKey), ref.string(SubKey), ref.string(key || ""));
        return ref.bool(data);
    }
    Registr.hasRegistrKey2Sync = hasRegistrKey2Sync;
    /**
     * `同步` 判断注册表 目录 存在性
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    function hasRegistrFolderKey2Sync(HKey, SubKey) {
        if (!GetRegistrEnvInfoSync)
            return false;
        const data = GetRegistrEnvInfoSync(index_1.HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_FOLDER_KEY, ref.string(HKey), ref.string(SubKey));
        return ref.bool(data);
    }
    Registr.hasRegistrFolderKey2Sync = hasRegistrFolderKey2Sync;
})(Registr = exports.Registr || (exports.Registr = {}));
;
