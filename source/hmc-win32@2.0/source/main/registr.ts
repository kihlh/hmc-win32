import { ref } from "./util";
import { HMC } from "./HMC";
import { Native } from "./Native";


//注册表编辑合集
export namespace Registr {

    export type HKEY = HMC.HKEY;
    export type REG_VALUE = HMC.REG_VALUE;
    export type RegistrValueStat = HMC.RegistrValueStat;
    export type chQueryFolderInfo = HMC.chQueryFolderInfo;
    export type REG_TYPE = HMC.Registr.REG_TYPE;
    export type REG_VALUE_TYPE_NAME = HMC.REG_VALUE_TYPE_NAME;
    export type REG_VALUE_DATA_TYPE = HMC.REG_VALUE_DATA_TYPE;

    async function GetRegistrEnvInfo(ENV_INFO_COMMAND: HMC.ENV_INFO_COMMAND, HKey: HMC.HKEY, ...aegs: any[]) {
        const _GetRegistrEnvInfo = Native.native?.GetRegistrEnvInfo;
        if (!_GetRegistrEnvInfo) return Promise.reject("not func -> GetRegistrEnvInfo");
        return _GetRegistrEnvInfo(ENV_INFO_COMMAND, HKey, ...aegs);
    }

    function GetRegistrEnvInfoSync(ENV_INFO_COMMAND: HMC.ENV_INFO_COMMAND, HKey: HMC.HKEY, ...aegs: any[]) {
        const _GetRegistrEnvInfoSync = Native.native?.GetRegistrEnvInfoSync;
        if (!_GetRegistrEnvInfoSync) return null;
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
    export async function getRegistrQword2(HKey: HKEY, SubKey: string, key: string | null): Promise<bigint | null> {


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_QWORD,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_QWORD,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_DWORD,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_DWORD,
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
    export async function getRegistrString2(HKey: HKEY, SubKey: string, key: string | null, expand?: boolean): Promise<string | null> {


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_STRING,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
            ,
            expand ? true : false
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
    export async function setRegistrString2(HKey: HKEY, SubKey: string, key: string | null, String: string, expand?: boolean): Promise<boolean> {


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_STRING,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            ref.string(String || ""),
            expand ? true : false
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
    export async function getRegistrKeys2(HKey: HKEY, SubKey: string): Promise<chQueryFolderInfo | null> {


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_KEYS,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ""
        );
        return data ? JSON.parse(String(data)) as chQueryFolderInfo : null;
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_STRING_LIST,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );

        if (typeof data == "string") {

            if (data[0] == "[") {
                return ref.JSONP(data) as string[] | null;
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
    export async function setRegistrStringList2(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[] | string): Promise<boolean> {


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_STRING_LIST,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            Array.isArray(StringList) ? ref.stringArray(StringList) : ref.convertMultiStringArray(ref.string(StringList || "")) || []
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_BUFFER,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_BUFFER,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_VALUE,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.COPY_REGISTR_VALUE,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.COPY_REGISTR_FOLDER,
            ref.string(HKey) as HKEY,
            ref.string(SourceSubKey),
            ref.string(NewSubKey || "")
        );
        return ref.bool(data);
    }

    export async function setRegistrValue2(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE_DATA_TYPE, type?: REG_TYPE | REG_VALUE_TYPE_NAME): Promise<boolean>;
    export async function setRegistrValue2(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): Promise<boolean>;

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
    export async function setRegistrValue2(HKey: HKEY, SubKey: string, key: string | null, data: unknown, type?: unknown): Promise<boolean> {

        const send_data = convertRegistrData(data as any, type as any);

        const data_2 = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            send_data.data,
            send_data.type
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
        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_VALUE_STAT,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return data ? (data as RegistrValueStat) : null;
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
    export async function getRegistrFolderStat2(HKey: HKEY, SubKey: string, isQuerykey?: boolean): Promise<chQueryFolderInfo | null> {

        if (isQuerykey) {
            return getRegistrKeys2(HKey, SubKey);
        }

        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_FOLDER_STAT,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ""
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
        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.CLEAR_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

    /**
     * `异步` 清除注册表文件夹内的所有值(不涉及子目录 并保留目录)
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.CLEAR_REGISTR_FOLDER,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.REMOVE_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

    /**
     * `异步` 删除注册表文件夹(无子目录)
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    export async function removeRegistrFolder2(HKey: HKEY, SubKey: string): Promise<boolean> {


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER_TREE,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.CREATE_REGISTR_FOLDER,
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
    export async function createRegistrValueKey2(HKey: HKEY, SubKey: string, key: string | string[] | { [key: string]: HMC.Registr.REG_TYPE }, type?: HMC.Registr.REG_TYPE): Promise<boolean> {

        const regVlaue: { [key: string]: HMC.Registr.REG_TYPE } = {};

        if (typeof key == "string") {

            if (typeof type == "number") {
                regVlaue[key] = type;
            } else {
                regVlaue[key] = HMC.Registr.REG_TYPE.REG_NONE;
            }

        }
        else if (Array.isArray(key)) {

            for (const Ckey of key) {
                regVlaue[Ckey] = typeof type == "number" ? type : HMC.Registr.REG_TYPE.REG_NONE;
            }
        }
        else if (key && typeof key == "object") {

            for (const Ckey in key) {
                regVlaue[Ckey] = key[Ckey];
            }
        }

        const bool_list: boolean[] = [];

        for (const key in regVlaue) {
            const type = regVlaue[key] || HMC.Registr.REG_TYPE.REG_NONE;
            const keyname = key;
            const data = await GetRegistrEnvInfo(
                HMC.ENV_INFO_COMMAND.CREATE_REGISTR_VALUE_KEY,
                ref.string(HKey) as HKEY,
                ref.string(SubKey),
                ref.string(keyname), ref.int(type)
            );

            bool_list.push(data ? true : false);
        }

        return ref.bool(bool_list.length == 1 ? bool_list.pop() : bool_list.at(-1) || false);
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.HAS_REGISTR_KEY,
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


        const data = await GetRegistrEnvInfo(
            HMC.ENV_INFO_COMMAND.HAS_REGISTR_FOLDER_KEY,
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


        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_QWORD,
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_QWORD,
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


        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_DWORD,
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_DWORD,
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
    export function getRegistrString2Sync(HKey: HKEY, SubKey: string, key: string | null, expand?: boolean): string | null {


        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_STRING,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
            , expand ? true : false

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
    export function setRegistrString2Sync(HKey: HKEY, SubKey: string, key: string | null, String: string, expand?: boolean): boolean {

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_STRING,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            ref.string(String || ""),
            expand ? true : false
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
    export function getRegistrKeys2Sync(HKey: HKEY, SubKey: string): chQueryFolderInfo | null {


        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_KEYS,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ""
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


        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_STRING_LIST,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );

        if (typeof data == "string") {

            if (data[0] == "[") {
                return ref.JSONP(data) as string[] | null;
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
    export function setRegistrStringList2Sync(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[] | string): boolean {

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_STRING_LIST,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            Array.isArray(StringList) ? ref.stringArray(StringList) : ref.convertMultiStringArray(ref.string(StringList || "")) || []
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


        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_BUFFER,
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_BUFFER,
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


        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_VALUE,
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.COPY_REGISTR_VALUE,
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.COPY_REGISTR_FOLDER,
            ref.string(HKey) as HKEY,
            ref.string(SourceSubKey),
            ref.string(NewSubKey || "")
        );
        return ref.bool(data);
    }

    export function typename(type: REG_TYPE): REG_VALUE_TYPE_NAME | null {
        // if(typeof type =="number"){
        for (let i in HMC.Registr.REG_TYPE) {
            const at = HMC.Registr.REG_TYPE[i as keyof typeof HMC.Registr.REG_TYPE];
            if (at == type) {
                return i as REG_VALUE_TYPE_NAME;
            }
        }
        // }

        return null;
    }

    type REG_DATA_SEND = { type: REG_TYPE, data: REG_VALUE_DATA_TYPE };

    export function is_REG_VALUE(data: any): data is REG_VALUE {
        const result = (
            data && typeof data == "object"

            // data.type
            && REG_TYPE(data.type) != null
            // data.data
            && (
                typeof data.data == "string" ||
                (typeof data.data == "object" && !data.data) ||
                Array.isArray(data.data),
                typeof data.data == "bigint" ||
                typeof data.data == "number" ||
                Buffer.isBuffer(data.data)
            )
        );

        if (result && typeof result.type_name != "string") {
            result.type_name = typename(result.type_name) || "REG_NONE";
        }

        return result;
    }

    export function REG_VALUE(REG_VALUE: string): HMC.REG_SZ_VALUE;
    export function REG_VALUE(REG_VALUE: REG_VALUE): REG_VALUE;
    export function REG_VALUE(REG_VALUE: number): HMC.REG_DWORD_VALUE | HMC.REG_QWORD_VALUE;
    export function REG_VALUE(REG_VALUE: bigint): HMC.REG_QWORD_VALUE;
    export function REG_VALUE(REG_VALUE: string[]): HMC.REG_MULTI_SZ_VALUE;

    export function REG_VALUE(REG_VALUE: unknown): REG_VALUE | null {
        if (is_REG_VALUE(REG_VALUE)) return REG_VALUE;

        if (Buffer.isBuffer(REG_VALUE)) {
            return {
                "data": REG_VALUE,
                "type": HMC.Registr.REG_TYPE.REG_BINARY,
                "size": REG_VALUE.length,
                "typeName": "REG_BINARY"
            };
        }

        if (typeof REG_VALUE == "string") {
            return {
                "data": REG_VALUE,
                "type": HMC.Registr.REG_TYPE.REG_SZ,
                "size": REG_VALUE.length,
                "typeName": "REG_SZ"
            };
        }

        if (typeof REG_VALUE == "bigint") {
            return {
                "data": REG_VALUE,
                "type": HMC.Registr.REG_TYPE.REG_QWORD,
                "size": 8,
                "typeName": "REG_QWORD"
            };
        }

        if (typeof REG_VALUE == "number") {
            return (REG_VALUE <= 0xffffffff ?
                ({
                    "data": REG_VALUE,
                    "type": HMC.Registr.REG_TYPE.REG_DWORD,
                    "size": 4,
                    "typeName": "REG_DWORD"
                } as HMC.REG_DWORD_VALUE) : ({
                    "data": BigInt(REG_VALUE),
                    "type": HMC.Registr.REG_TYPE.REG_QWORD,
                    "size": 8,
                    "typeName": "REG_QWORD"
                } as HMC.REG_QWORD_VALUE));
        }

        if (Array.isArray(REG_VALUE)) {
            return {
                "data": ref.is_stringArray(REG_VALUE) ? REG_VALUE : ref.stringArray(REG_VALUE),
                "type": HMC.Registr.REG_TYPE.REG_MULTI_SZ,
                "size": 0,
                "typeName": "REG_MULTI_SZ"
            }
        }

        return null;
    }

    export function REG_TYPE(type: any): REG_TYPE | null {

        if (typeof type == "string") {
            for (let i in HMC.Registr.REG_TYPE) {
                if (i?.toUpperCase() == type?.toUpperCase()) {
                    return HMC.Registr.REG_TYPE[i as keyof typeof HMC.Registr.REG_TYPE];
                }
            }
        }

        if (typeof type == "number") {
            for (let i in HMC.Registr.REG_TYPE) {
                const at = HMC.Registr.REG_TYPE[i as keyof typeof HMC.Registr.REG_TYPE];
                if (at == type) {
                    return at;
                }
            }
        }

        return HMC.Registr.REG_TYPE.REG_NONE;
    }

    export function convertRegistrData(data: REG_VALUE_DATA_TYPE, type?: REG_TYPE | REG_VALUE_TYPE_NAME): REG_DATA_SEND;
    export function convertRegistrData(data: REG_VALUE): REG_DATA_SEND;
    export function convertRegistrData(data: unknown, type?: unknown): REG_DATA_SEND {
        const data_copy = REG_VALUE(data as any);
        const type_copy = REG_TYPE(type);

        const send_data: REG_DATA_SEND = {
            type: type_copy || data_copy?.type || HMC.Registr.REG_TYPE.REG_NONE,
            data: typeof data_copy?.data != "undefined" ? data_copy.data : Buffer.alloc(0)
        };

        return send_data;
    }

    export function setRegistrValue2Sync(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE_DATA_TYPE, type?: REG_TYPE | REG_VALUE_TYPE_NAME): boolean;
    export function setRegistrValue2Sync(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): boolean;

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
    export function setRegistrValue2Sync(HKey: HKEY, SubKey: string, key: string | null, data: unknown, type?: unknown): boolean {

        const send_data = convertRegistrData(data as any, type as any);

        if (!GetRegistrEnvInfoSync) return false;
        const data_2 = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.SET_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || ""),
            send_data.data,
            send_data.type
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

        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_VALUE_STAT,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return (data as RegistrValueStat) || null;
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
    export function getRegistrFolderStat2Sync(HKey: HKEY, SubKey: string, isQuerykey?: boolean): chQueryFolderInfo | null {
        if (isQuerykey) {
            return getRegistrKeys2Sync(HKey, SubKey);
        }

        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.GET_REGISTR_FOLDER_STAT,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ""
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.CLEAR_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

    /**
     * `同步` 清除注册表文件夹的所有值(不涉及子目录 并保留目录)
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.CLEAR_REGISTR_FOLDER,
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.REMOVE_REGISTR_VALUE,
            ref.string(HKey) as HKEY,
            ref.string(SubKey),
            ref.string(key || "")
        );
        return ref.bool(data);
    }

    /**
     * `同步` 删除注册表文件夹(无子目录)
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    export function removeRegistrFolder2Sync(HKey: HKEY, SubKey: string): boolean {

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER,
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.REMOVE_REGISTR_FOLDER_TREE,
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.CREATE_REGISTR_FOLDER,
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
    export function createRegistrValueKey2Sync(HKey: HKEY, SubKey: string, key: string | string[] | { [key: string]: HMC.Registr.REG_TYPE }, type?: HMC.Registr.REG_TYPE): boolean {

        if (!GetRegistrEnvInfoSync) return false;
        const regVlaue: { [key: string]: HMC.Registr.REG_TYPE } = {};

        if (typeof key == "string") {

            if (typeof type == "number") {
                regVlaue[key] = type;
            } else {
                regVlaue[key] = HMC.Registr.REG_TYPE.REG_NONE;
            }

        }
        else if (Array.isArray(key)) {

            for (const Ckey of key) {
                regVlaue[Ckey] = typeof type == "number" ? type : HMC.Registr.REG_TYPE.REG_NONE;
            }
        }
        else
            if (key && typeof key == "object") {

                for (const Ckey in key) {
                    regVlaue[Ckey] = key[Ckey];
                }
            }

        const bool_list: boolean[] = [];

        for (const key in regVlaue) {
            const type = regVlaue[key] || HMC.Registr.REG_TYPE.REG_NONE;
            const keyname = key;
            const data = GetRegistrEnvInfoSync(
                HMC.ENV_INFO_COMMAND.CREATE_REGISTR_VALUE_KEY,
                ref.string(HKey) as HKEY,
                ref.string(SubKey),
                ref.string(keyname), ref.int(type)
            );

            bool_list.push(data ? true : false);
        }

        return ref.bool(bool_list.length == 1 ? bool_list.pop() : bool_list.at(-1) || false);
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.HAS_REGISTR_KEY,
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

        if (!GetRegistrEnvInfoSync) return false;
        const data = GetRegistrEnvInfoSync(
            HMC.ENV_INFO_COMMAND.HAS_REGISTR_FOLDER_KEY,
            ref.string(HKey) as HKEY,
            ref.string(SubKey));
        return ref.bool(data);
    }

};