//注册表编辑合集   (拥有统一化名称)
export module Registr {

    /**注册表根目录 */
    const Hkey = {
        /**用作默认用户首选设置|也作为单个用户的首选设置 */
        HKEY_CURRENT_CONFIG: "HKEY_CURRENT_CONFIG" as "HKEY_CURRENT_CONFIG",
        /**用作默认用户首选设置|也作为单个用户的首选设置 */
        HKEY_USERS: "HKEY_USERS" as "HKEY_USERS",
        /**是与文档类型和 OLE\COM 相关的信息的支持键。这个键是 */
        HKEY_CLASSES_ROOT: "HKEY_CLASSES_ROOT" as "HKEY_CLASSES_ROOT",
        /**包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息 */
        HKEY_LOCAL_MACHINE: "HKEY_LOCAL_MACHINE" as "HKEY_LOCAL_MACHINE",
        /**管理系统当前的用户信息 */
        HKEY_CURRENT_USER: "HKEY_CURRENT_USER" as "HKEY_CURRENT_USER",
    };

    // 注册表根目录
    export type HKEY = keyof typeof Hkey;

    /**
     * 注册表格式类型
     */
    export enum REG_TYPE {
        /** 没有值 */
        REG_NONE = 0,

        /** 以空字符结尾的字符串 */
        REG_SZ = 1,

        /** 可扩展的字符串（例如环境变量） */
        REG_EXPAND_SZ = 2,

        /** 原始的二进制数据 */
        REG_BINARY = 3,

        /** 32位数字，使用小端字节序 */
        REG_DWORD = 4,

        /** 32位数字，使用小端字节序（与 REG_DWORD 相同） */
        REG_DWORD_LITTLE_ENDIAN = 4,

        /** 32位数字，使用大端字节序 */
        REG_DWORD_BIG_ENDIAN = 5,

        /** 符号链接，使用 Unicode 编码 */
        REG_LINK = 6,

        /** 多个以空字符结尾的 Unicode 字符串 */
        REG_MULTI_SZ = 7,

        /** 资源列表，存储在资源映射中 */
        REG_RESOURCE_LIST = 8,

        /** 硬件描述中的资源列表 */
        REG_FULL_RESOURCE_DESCRIPTOR = 9,

        /** 资源需求列表 */
        REG_RESOURCE_REQUIREMENTS_LIST = 10,

        /** 64位数字，使用小端字节序 */
        REG_QWORD = 11,

        /** 64位数字，使用小端字节序（与 REG_QWORD 相同） */
        REG_QWORD_LITTLE_ENDIAN = 11,
    }


    export type RegistrValueStat = {
        /**此值的类型 */
        type: REG_TYPE;
        /**内容大小 */
        size: number;
        /**此内容是否存在 */
        exists: boolean;
    };

    export type RegistrFolderStat = {
        /**目录键列表 */
        folder?: string[];
        /**值键列表 */
        key?: string[];
        /**此内容是否存在 */
        exists: boolean;
        /**大小 */
        size: number;
        /**目录键数量 */
        folderSize: number;
        /**该目录下有多少个值键 */
        keySize: number;
        /**该目录上次写入的时间戳 毫秒 */
        time: number;
    };

    export interface REG_SZ_VALUE {
        type: 1;
        typeName: "REG_SZ";
        data: string;
        size: number;
    }

    export interface REG_EXPAND_SZ_VALUE {
        type: REG_TYPE.REG_EXPAND_SZ;
        typeName: "REG_EXPAND_SZ";
        data: string;
        dataExpand: string;
        size: number;
    }

    export interface REG_DWORD_VALUE {
        type: REG_TYPE.REG_DWORD | REG_TYPE.REG_DWORD_BIG_ENDIAN | REG_TYPE.REG_DWORD_LITTLE_ENDIAN;
        typeName: "REG_DWORD" | "REG_DWORD_BIG_ENDIAN" | "REG_DWORD_LITTLE_ENDIAN";
        data: number;
        size: number;
    }

    export interface REG_QWORD_VALUE {
        type: REG_TYPE.REG_QWORD | REG_TYPE.REG_QWORD_LITTLE_ENDIAN;
        typeName: "REG_QWORD" | "REG_QWORD_LITTLE_ENDIAN";
        data: bigint;
        size: number;
    }

    export interface REG_BINARY_VALUE {
        type: REG_TYPE.REG_BINARY;
        typeName: "REG_BINARY";
        data: Buffer;
        size: number;
    }

    export interface REG_MULTI_SZ_VALUE {
        type: REG_TYPE.REG_MULTI_SZ;
        typeName: "REG_MULTI_SZ";
        data: string[];
        size: number;
    }


    export interface REG_NONE_VALUE {
        type: REG_TYPE.REG_NONE;
        typeName: "REG_NONE";
        data: null;
        size: number;
    }

    export interface REG_ANY_VALUE {
        type: REG_TYPE.REG_FULL_RESOURCE_DESCRIPTOR | REG_TYPE.REG_LINK | REG_TYPE.REG_NONE | REG_TYPE.REG_RESOURCE_LIST | REG_TYPE.REG_RESOURCE_REQUIREMENTS_LIST;
        typeName: "REG_FULL_RESOURCE_DESCRIPTOR" | "REG_LINK" | "REG_RESOURCE_LIST" | "REG_RESOURCE_REQUIREMENTS_LIST";
        data: Buffer;
        size: number;
    }

    export type REG_VALUE = REG_SZ_VALUE | REG_EXPAND_SZ_VALUE | REG_DWORD_VALUE | REG_QWORD_VALUE | REG_BINARY_VALUE | REG_MULTI_SZ_VALUE | REG_ANY_VALUE;

    export interface chQueryFolderKey {
        key: string[];
        folder: string[];
        size: number;
    };


    /**
     * 获取内容(64位数字)
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
    export function getRegistrQword(HKey: HKEY, SubKey: string, key: string | null): bigint | null;

    /**
     * 设置内容(64位数字)
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
    export function setRegistrQword(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): boolean;

    /**
     * 获取内容(32位数字)
     * @param HKEY 根路径
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey 路径 类似于如同目录路径概念
     * @param key 键名称  `""` `null` 将作为默认key
     */
    export function getRegistrDword(HKey: HKEY, SubKey: string, key: string | null): number | null;

    /**
     * 设置内容(32位数字)
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
    export function setRegistrDword(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): boolean;

    /**
     * 获取注册表字符串值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function getRegistrString(HKey: HKEY, SubKey: string, key: string | null): string | null;

    /**
     * 设置注册表字符串值
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
    export function setRegistrString(HKey: HKEY, SubKey: string, key: string | null, String: string): boolean;

    /**
     * 枚举注册表目录的所有键
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function getRegistrKeys(HKey: HKEY, SubKey: string, key: string | null): chQueryFolderKey;

    /**
     * 获取注册表字符串值列表
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function getRegistrStringList(HKey: HKEY, SubKey: string, key: string | null): string[] | null;

    /**
     * 设置注册表字符串值列表
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
    export function setRegistrStringList(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[]): boolean;

    /**
     * 获取注册表缓冲区值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function getRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null): Buffer | null;

    /**
     * 设置注册表缓冲区值
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
    export function setRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null, String: Buffer): boolean;

    /**
     * 获取注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function getRegistrValue(HKey: HKEY, SubKey: string, key: string | null): REG_VALUE | null;

    /**
     * 复制注册表值
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
    export function copyRegistrValue(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): boolean;

    /**
     * 复制注册表 目录
     * @param HKey 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SourceSubKey 源路径
     * @param NewSubKey 新路径
     */
    export function copyRegistrFolder(HKey: HKEY, SourceSubKey: string, NewSubKey: string): boolean;

    /**
     * 设置注册表值
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
    export function setRegistrValue(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): boolean;

    /**
     * 获取注册表值状态
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function getRegistrValueStat(HKey: HKEY, SubKey: string, key: string | null): RegistrValueStat;

    /**
     * 获取注册表文件夹状态
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function getRegistrFolderStat(HKey: HKEY, SubKey: string, key: string | null): RegistrFolderStat;

    /**
     * 清除注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function clearRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;

    /**
     * 清除注册表文件夹
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function clearRegistrFolder(HKey: HKEY, SubKey: string, key: string | null): boolean;

    /**
     * 删除注册表值
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function removeRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;

    /**
     * 删除注册表文件夹
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    export function removeRegistrFolder(HKey: HKEY, SubKey: string): boolean;

    /**
     * 删除注册表文件夹树
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    export function removeRegistrFolderTree(HKey: HKEY, SubKey: string): boolean;

    /**
     * 创建注册表文件夹
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param folderPath - 要创建的文件夹路径
     */
    export function createRegistrFolder(HKey: HKEY, SubKey: string): boolean;

    /**
     * 创建注册表值键
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param folderPath - 要创建值键的文件夹路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function createRegistrValueKey(HKey: HKEY, SubKey: string, key: string | string[]): boolean;

    /**
     * 判断注册表 键值 存在性
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     * @param key - 键名 允许 `null` or `""` 将作为默认key
     */
    export function hasRegistrKey(HKey: HKEY, SubKey: string, key: string | null): boolean;
    
    /**
     * 判断注册表 目录 存在性
     * @param HKey - 注册表的根键
     * - `HKEY_CLASSES_ROOT`   是与文档类型和 OLE\COM 相关的信息的支持键。
     * - `HKEY_CURRENT_USER`   管理系统当前的用户信息
     * - `HKEY_LOCAL_MACHINE`   包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
     * - `HKEY_USERS`   用作默认用户首选设置，也作为单个用户的首选设置
     * - `HKEY_CURRENT_CONFIG`   用作默认用户首选设置，也作为单个用户的首选设置
     * @param SubKey - 子键路径
     */
    export function hasRegistrFolderKey(HKey: HKEY, SubKey: string): boolean;
};