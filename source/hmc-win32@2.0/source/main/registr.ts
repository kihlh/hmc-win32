import util = require("./util");
import main = require("./index");
import { HMC2_MODE } from "./index";


//注册表编辑合集
export module Registr {

    export type HKEY = HMC2_MODE.HKEY;
    export type chQueryFolderKey = HMC2_MODE.chQueryFolderKey;
    export type REG_VALUE = HMC2_MODE.REG_VALUE;
    export type RegistrValueStat = HMC2_MODE.RegistrValueStat;
    export type RegistrFolderStat = HMC2_MODE.RegistrFolderStat;
    const { ref } = util;

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
    export async function getRegistrQword2(HKey: HKEY, SubKey: string, key: string | null): Promise<bigint | null> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_QWORD,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );

        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {

            return BigInt(data);
        }

        return null;
    }

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
    export async function setRegistrQword2(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_QWORD,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            ref.int(Qword || 0));
        return ref.bool(data);
    }

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
    export async function getRegistrDword2(HKey: HKEY, SubKey: string, key: string | null): Promise<number | null> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_DWORD,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );

        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {

            return ref.long(data);
        }

        return null;
    }

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
    export async function setRegistrDword2(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_DWORD,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            ref.long(Dword)
        );
        return ref.bool(data);
    }

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
    export async function getRegistrString2(HKey: HKEY, SubKey: string, key: string | null): Promise<string | null> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return typeof data == "string" ? data : null;
    }

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
    export async function setRegistrString2(HKey: HKEY, SubKey: string, key: string | null, String: string): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            ref.string(String || "")
        );
        return ref.bool(data);
    }

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
    export async function getRegistrKeys2(HKey: HKEY, SubKey: string, key: string | null): Promise<chQueryFolderKey | null> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_KEYS,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return data ? JSON.parse(String(data)) as chQueryFolderKey : null;
    }

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
    export async function getRegistrStringList2(HKey: HKEY, SubKey: string, key: string | null): Promise<string[] | null> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING_LIST,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );

        if (typeof data == "string") {

            if (data[0] == "[") {
                return JSON.parse(data);
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
    export async function setRegistrStringList2(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[]): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING_LIST,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            Array.isArray(StringList)?StringList:"\0\0"
        );
        return ref.bool(data);
    }

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
    export async function getRegistrBuffer2(HKey: HKEY, SubKey: string, key: string | null): Promise<Buffer | null> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_BUFFER,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return Buffer.isBuffer(data) ? data : null;
    }

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
    export async function setRegistrBuffer2(HKey: HKEY, SubKey: string, key: string | null, Buff: Buffer): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_BUFFER,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            Buff
        );
        return ref.bool(data);
    }

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
    export async function getRegistrValue2(HKey: HKEY, SubKey: string, key: string | null): Promise<REG_VALUE | null> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return data ? data as REG_VALUE : null;
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
    export async function copyRegistrValue2(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SourceSubKey),
            ref.string(Sourcekey || ""),
            ref.string(NewSubKey || ""),
            ref.string(Newkey || "")
        );

        return ref.bool(data);
    }

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
    export async function copyRegistrFolder2(HKey: HKEY, SourceSubKey: string, NewSubKey: string): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_FOLDER,
            ref.string(HKey) as HKEY,
            ref.string(SourceSubKey),
            ref.string(NewSubKey || "")
        );
        return ref.bool(data);
    }

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
    export async function setRegistrValue2(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data_2 = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            data
        );
        return ref.bool(data_2);
    }

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
    export async function getRegistrValueStat2(HKey: HKEY, SubKey: string, key: string | null): Promise<RegistrValueStat | null> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE_STAT,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return data ? JSON.parse(String(data)) : null;
    }

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
    export async function getRegistrFolderStat2(HKey: HKEY, SubKey: string, key: string | null): Promise<RegistrFolderStat | null> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_FOLDER_STAT,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return data ? JSON.parse(String(data)) : null;
    }

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
    export async function clearRegistrValue2(HKey: HKEY, SubKey: string, key: string | null): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

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
    export async function clearRegistrFolder2(HKey: HKEY, SubKey: string): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_FOLDER,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string("")
        );
        return ref.bool(data);
    }

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
    export async function removeRegistrValue2(HKey: HKEY, SubKey: string, key: string | null): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

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
    export async function removeRegistrFolder2(HKey: HKEY, SubKey: string): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER,
            ref.string(HKey) as HKEY,
            ref.string(SubKey)
        );
        return ref.bool(data);
    }

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
    export async function removeRegistrFolderTree2(HKey: HKEY, SubKey: string): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER_TREE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey)
        );
        return ref.bool(data);
    }

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
    export async function createRegistrFolder2(HKey: HKEY, SubKey: string): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_FOLDER,
            ref.string(HKey) as HKEY,
            ref.string(SubKey)
        );
        return ref.bool(data);
    }

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
    export async function createRegistrValueKey2(HKey: HKEY, SubKey: string, key: string | string[]): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_VALUE_KEY,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

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
    export async function hasRegistrKey2(HKey: HKEY, SubKey: string, key: string | null): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_KEY,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

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
    export async function hasRegistrFolderKey2(HKey: HKEY, SubKey: string): Promise<boolean> {
        const GetRegistrEnvInfo = main.Native.native?.GetRegistrEnvInfo;
        if (!GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        const data = await GetRegistrEnvInfo(
            HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_FOLDER_KEY,
            ref.string(HKey) as HKEY,
            ref.string(SubKey));
        return ref.bool(data);
    }

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
    export function getRegistrQword2Sync(HKey: HKEY, SubKey: string, key: string | null): bigint | null {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return null;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_QWORD,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );

        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {

            return BigInt(data);
        }

        return null;
    }

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
    export function setRegistrQword2Sync(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_QWORD,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            ref.int(Qword || 0));
        return ref.bool(data);
    }

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
    export function getRegistrDword2Sync(HKey: HKEY, SubKey: string, key: string | null): number | null {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return null;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_DWORD,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );

        if (typeof data == "number" || typeof data == "string" || typeof data == "boolean" || typeof data == "bigint") {

            return ref.long(data);
        }

        return null;
    }

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
    export function setRegistrDword2Sync(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_DWORD,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            ref.long(Dword)
        );
        return ref.bool(data);
    }

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
    export function getRegistrString2Sync(HKey: HKEY, SubKey: string, key: string | null): string | null {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return null;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return typeof data == "string" ? data : null;
    }

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
    export function setRegistrString2Sync(HKey: HKEY, SubKey: string, key: string | null, String: string): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            ref.string(String || "")
        );
        return ref.bool(data);
    }

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
    export function getRegistrKeys2Sync(HKey: HKEY, SubKey: string, key: string | null): chQueryFolderKey | null {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return null;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_KEYS,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return data ? JSON.parse(String(data)) : null;
    }

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
    export function getRegistrStringList2Sync(HKey: HKEY, SubKey: string, key: string | null): string[] | null {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return null;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_STRING_LIST,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );

        if (typeof data == "string") {

            if (data[0] == "[") {
                return JSON.parse(data);
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
    export function setRegistrStringList2Sync(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[]): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_STRING_LIST,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

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
    export function getRegistrBuffer2Sync(HKey: HKEY, SubKey: string, key: string | null): Buffer | null {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return null;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_BUFFER,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return Buffer.isBuffer(data) ? data : null;
    }

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
    export function setRegistrBuffer2Sync(HKey: HKEY, SubKey: string, key: string | null, Buff: Buffer): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_BUFFER,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            Buff
        );
        return ref.bool(data);
    }

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
    export function getRegistrValue2Sync(HKey: HKEY, SubKey: string, key: string | null): REG_VALUE | null {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return null;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return data ? data as REG_VALUE : null;
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
    export function copyRegistrValue2Sync(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SourceSubKey),
            ref.string(Sourcekey || ""),
            ref.string(NewSubKey || ""),
            ref.string(Newkey || "")
        );

        return ref.bool(data);
    }

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
    export function copyRegistrFolder2Sync(HKey: HKEY, SourceSubKey: string, NewSubKey: string): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.COPY_REGISTR_FOLDER,
            ref.string(HKey) as HKEY,
            ref.string(SourceSubKey),
            ref.string(NewSubKey || "")
        );
        return ref.bool(data);
    }

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
    export function setRegistrValue2Sync(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data_2 = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.SET_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            data
        );
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
    export function getRegistrValueStat2Sync(HKey: HKEY, SubKey: string, key: string | null): RegistrValueStat | null {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return null;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_VALUE_STAT,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return data ? JSON.parse(String(data)) : null;
    }

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
    export function getRegistrFolderStat2Sync(HKey: HKEY, SubKey: string, key: string | null): RegistrFolderStat | null {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return null;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.GET_REGISTR_FOLDER_STAT,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return data ? JSON.parse(String(data)) : null;
    }

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
    export function clearRegistrValue2Sync(HKey: HKEY, SubKey: string, key: string | null): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

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
    export function clearRegistrFolder2Sync(HKey: HKEY, SubKey: string): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.CLEAR_REGISTR_FOLDER,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string("")
        );
        return ref.bool(data);
    }

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
    export function removeRegistrValue2Sync(HKey: HKEY, SubKey: string, key: string | null): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

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
    export function removeRegistrFolder2Sync(HKey: HKEY, SubKey: string): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER,
            ref.string(HKey) as HKEY,
            ref.string(SubKey)
        );
        return ref.bool(data);
    }

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
    export function removeRegistrFolderTree2Sync(HKey: HKEY, SubKey: string): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER_TREE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey)
        );
        return ref.bool(data);
    }

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
    export function createRegistrFolder2Sync(HKey: HKEY, SubKey: string): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_FOLDER,
            ref.string(HKey) as HKEY,
            ref.string(SubKey)
        );
        return ref.bool(data);
    }

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
    export function createRegistrValueKey2Sync(HKey: HKEY, SubKey: string, key: string | string[]): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.CREATE_REGISTR_VALUE_KEY,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

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
    export function hasRegistrKey2Sync(HKey: HKEY, SubKey: string, key: string | null): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_KEY,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

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
    export function hasRegistrFolderKey2Sync(HKey: HKEY, SubKey: string): boolean {
        const GetRegistrEnvInfoSync = main.Native.native?.GetRegistrEnvInfoSync;
        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC2_MODE.ENV_INFO_COMMAND.HAS_REGISTR_FOLDER_KEY,
            ref.string(HKey) as HKEY,
            ref.string(SubKey));
        return ref.bool(data);
    }

};