/// <reference types="node" />
import { HMC2_MODE } from "./index";
export declare module Registr {
    type HKEY = HMC2_MODE.HKEY;
    type REG_VALUE = HMC2_MODE.REG_VALUE;
    type RegistrValueStat = HMC2_MODE.RegistrValueStat;
    type chQueryFolderInfo = HMC2_MODE.chQueryFolderInfo;
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
    function getRegistrQword2(HKey: HKEY, SubKey: string, key: string | null): Promise<bigint | null>;
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
    function setRegistrQword2(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): Promise<boolean>;
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
    function getRegistrDword2(HKey: HKEY, SubKey: string, key: string | null): Promise<number | null>;
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
    function setRegistrDword2(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): Promise<boolean>;
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
    function getRegistrString2(HKey: HKEY, SubKey: string, key: string | null, expand?: boolean): Promise<string | null>;
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
    function setRegistrString2(HKey: HKEY, SubKey: string, key: string | null, String: string, expand?: boolean): Promise<boolean>;
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
    function getRegistrKeys2(HKey: HKEY, SubKey: string, key: string | null): Promise<chQueryFolderInfo | null>;
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
    function getRegistrStringList2(HKey: HKEY, SubKey: string, key: string | null): Promise<string[] | null>;
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
    function setRegistrStringList2(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[] | string): Promise<boolean>;
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
    function getRegistrBuffer2(HKey: HKEY, SubKey: string, key: string | null): Promise<Buffer | null>;
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
    function setRegistrBuffer2(HKey: HKEY, SubKey: string, key: string | null, Buff: Buffer): Promise<boolean>;
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
    function copyRegistrValue2(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): Promise<boolean>;
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
    function copyRegistrFolder2(HKey: HKEY, SourceSubKey: string, NewSubKey: string): Promise<boolean>;
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
    function setRegistrValue2(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): Promise<boolean>;
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
    function getRegistrValueStat2(HKey: HKEY, SubKey: string, key: string | null): Promise<RegistrValueStat | null>;
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
    function getRegistrFolderStat2(HKey: HKEY, SubKey: string, key: string | null): Promise<chQueryFolderInfo | null>;
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
    function clearRegistrValue2(HKey: HKEY, SubKey: string, key: string | null): Promise<boolean>;
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
    function clearRegistrFolder2(HKey: HKEY, SubKey: string): Promise<boolean>;
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
    function removeRegistrValue2(HKey: HKEY, SubKey: string, key: string | null): Promise<boolean>;
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
    function removeRegistrFolder2(HKey: HKEY, SubKey: string): Promise<boolean>;
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
    function removeRegistrFolderTree2(HKey: HKEY, SubKey: string): Promise<boolean>;
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
    function createRegistrFolder2(HKey: HKEY, SubKey: string): Promise<boolean>;
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
    function createRegistrValueKey2(HKey: HKEY, SubKey: string, key: string | string[] | {
        [key: string]: HMC2_MODE.REG_TYPE;
    }, type?: HMC2_MODE.REG_TYPE): Promise<boolean>;
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
    function hasRegistrKey2(HKey: HKEY, SubKey: string, key: string | null): Promise<boolean>;
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
    function hasRegistrFolderKey2(HKey: HKEY, SubKey: string): Promise<boolean>;
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
    function getRegistrQword2Sync(HKey: HKEY, SubKey: string, key: string | null): bigint | null;
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
    function setRegistrQword2Sync(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): boolean;
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
    function getRegistrDword2Sync(HKey: HKEY, SubKey: string, key: string | null): number | null;
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
    function setRegistrDword2Sync(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): boolean;
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
    function getRegistrString2Sync(HKey: HKEY, SubKey: string, key: string | null, expand?: boolean): string | null;
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
    function setRegistrString2Sync(HKey: HKEY, SubKey: string, key: string | null, String: string, expand?: boolean): boolean;
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
    function getRegistrKeys2Sync(HKey: HKEY, SubKey: string, key: string | null): chQueryFolderInfo | null;
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
    function getRegistrStringList2Sync(HKey: HKEY, SubKey: string, key: string | null): string[] | null;
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
    function setRegistrStringList2Sync(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[] | string): boolean;
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
    function getRegistrBuffer2Sync(HKey: HKEY, SubKey: string, key: string | null): Buffer | null;
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
    function setRegistrBuffer2Sync(HKey: HKEY, SubKey: string, key: string | null, Buff: Buffer): boolean;
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
    function copyRegistrValue2Sync(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): boolean;
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
    function copyRegistrFolder2Sync(HKey: HKEY, SourceSubKey: string, NewSubKey: string): boolean;
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
    function getRegistrValueStat2Sync(HKey: HKEY, SubKey: string, key: string | null): RegistrValueStat | null;
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
    function getRegistrFolderStat2Sync(HKey: HKEY, SubKey: string, key: string | null): chQueryFolderInfo | null;
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
    function clearRegistrValue2Sync(HKey: HKEY, SubKey: string, key: string | null): boolean;
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
    function clearRegistrFolder2Sync(HKey: HKEY, SubKey: string): boolean;
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
    function removeRegistrValue2Sync(HKey: HKEY, SubKey: string, key: string | null): boolean;
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
    function removeRegistrFolder2Sync(HKey: HKEY, SubKey: string): boolean;
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
    function removeRegistrFolderTree2Sync(HKey: HKEY, SubKey: string): boolean;
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
    function createRegistrFolder2Sync(HKey: HKEY, SubKey: string): boolean;
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
    function createRegistrValueKey2Sync(HKey: HKEY, SubKey: string, key: string | string[] | {
        [key: string]: HMC2_MODE.REG_TYPE;
    }, type?: HMC2_MODE.REG_TYPE): boolean;
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
    function hasRegistrKey2Sync(HKey: HKEY, SubKey: string, key: string | null): boolean;
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
    function hasRegistrFolderKey2Sync(HKey: HKEY, SubKey: string): boolean;
}
