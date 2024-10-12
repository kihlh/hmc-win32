import PromiseEval = require("./promiseEval");
import ShellMain = require("./shell");
import AutoMain = require("./auto");
import UtilMain = require("./util");
import ProcessMain = require("./Process");
import RegistrMain = require("./registr");
import ShellPromiseEvalMain = require("./ShellPromiseEval");

interface Native {
    /**
     * 执行命令代码 并且按照api内容返回 异步
     * @docs PromiseEval 是通过(hmc -> PromiseEval)生成的Promise / Sync 函数 他性能并不是特别出众 但是比编写一个标准化Promise 节省近百行C++代码
     * @param pid 进程id
     * @param command 命令
     */
    HMC_PromiseEval?(command: PromiseEval.HMC_PROMISEEVAL_TASK_TYPE, ...arg: unknown[]): Promise<unknown>;

    /**
     * 执行命令代码 并且按照api内容返回 同步
     * @docs PromiseEval 是通过(hmc -> PromiseEval)生成的Promise / Sync 函数 他性能并不是特别出众 但是比编写一个标准化Promise 节省近百行C++代码
     * @param pid 进程id
     * @param command 命令
     */
    HMC_PromiseEvalSync?(command: PromiseEval.HMC_PROMISEEVAL_TASK_TYPE, ...arg: unknown[]): unknown;

    /**
     * 执行Shell命令代码 并且按照api内容返回 异步
     * @docs GetShellEnvInfo 是通过(hmc -> GetShellEnvInfo)生成的Promise / Sync 函数 他性能比PromiseEval更好 因为他并未使用any泛型 仅使用了精简的 数据类型
     * @param pid 进程id
     * @param command 命令
     */
    HMC_GetShellEnvInfo?(command: ShellPromiseEvalMain.HMC_PROMISEEVAL_TASK_TYPE, ...arg: unknown[]): Promise<unknown>;

    /**
     * 执行Shell命令代码 并且按照api内容返回 同步
     * @docs GetShellEnvInfo 是通过(hmc -> GetShellEnvInfo)生成的Promise / Sync 函数 他性能比PromiseEval更好 因为他并未使用any泛型 仅使用了精简的 数据类型
     * @param pid 进程id
     * @param command 命令
     */
    HMC_GetShellEnvInfoSync?(command: ShellPromiseEvalMain.HMC_PROMISEEVAL_TASK_TYPE, ...arg: unknown[]): unknown;

    /**
     * 执行进程环境获取 需要配合命令代码
     * @docs  是类似于HMC_PromiseEval的函数 但是性能更好但是局限性是只能发送 long,long 数据 返回的只能是文本 
     * @param pid 进程id
     * @param command 命令
     */
    getProcessEnvInfo2?(pid: number, command: HMC2_MODE.ENV_INFO_COMMAND): Promise<string | null>;

    /**
     * 执行进程环境获取 需要配合命令代码
     * @docs  是类似于HMC_PromiseEval的函数 但是性能更好但是局限性是只能发送 long,long 数据 返回的只能是文本 
     * @param pid 进程id
     * @param command 命令
     */
    getProcessEnvInfo2Sync?(pid: number, command: HMC2_MODE.ENV_INFO_COMMAND): string | null;

    /**
     * 关闭窗口 同步
     * @param handle 句柄 
     * @param grade 等级
     * - 1 关闭 / 非强制
     * - 2 关闭 / 系统级(半强制)
     * - 3 关闭线程 (强制)
     * - 5 尝试所有办法直到关闭 (默认)
     */
    closeWindow2?: (handle: number, grade?: 1 | 2 | 3) => Promise<boolean>;

    /**
     * 关闭窗口 同步
     * @param handle 句柄 
     * @param grade 等级
     * - 1 关闭 / 非强制
     * - 2 关闭 / 系统级(半强制)
     * - 3 关闭线程 (强制)
     */
    closeWindow2Sync?: (handle: number, grade: 1 | 2 | 3) => boolean;

    /**
     * 获取剪贴板文件路径列表 以\0切割(高性能,同步)
     * @returns 
     */
    getClipboardFilePaths?: () => string;

    /**
     * 设置剪贴板本文或者html
     * @param text 文本
     * @param is_html 以html方式写入
     * @returns 
     */
    setClipboardText?: (text: string, is_html?: boolean) => boolean;

    /**
     * 获取剪贴板文本 (高性能,同步)
     * @returns 
     */
    getClipboardText?: () => string | null;

    /**
     * 清空剪贴板
     * @returns 
     */
    clearClipboard?: () => boolean;

    /**
     * 设置文件路径列表 
     * @param paths 路径列表
     * @returns 
     */
    setClipboardFilePaths?: (paths: string | string[]) => boolean;

    /**
     * 获取剪贴板内容响应
     * @returns 
     */
    getClipboardInfo?: () => {
        // json数组(文本)
        format: string;
        // 设置剪贴板的窗口句柄
        hwnd: number;
        // 剪贴板唯一id
        id: number;
        // 当前格式包含数量
        formatCount: number;
    };

    /**
     * 枚举剪贴板包含的格式
     * @returns 
     */
    enumClipboardFormats?: () => `{"type":${string},"type_name":${string}}...[]`;

    /**
     * 获取剪贴板中的html
     */
    getClipboardHTML?: () => HMC2_MODE.CLIP_HTML_INFO | null;


    // 鼠标函数 懒构建体 请勿多次构建 因为此函数返回的函数集内容不会被v8回收
    HMC_MOUSE_CLASS?: HMC2_MODE.HMC_MOUSE_CLASS | (() => HMC2_MODE.HMC_MOUSE_CLASS);
    HMC_MOUSE_CLASS_LAZY?: null | HMC2_MODE.HMC_MOUSE_CLASS;

    // 键盘函数 懒构建体 请勿多次构建 因为此函数返回的函数集内容不会被v8回收
    HMC_KEYBOARD_CLASS?: HMC2_MODE.HMC_KEYBOARD_CLASS | (() => HMC2_MODE.HMC_KEYBOARD_CLASS);
    HMC_KEYBOARD_CLASS_LAZY?: null | HMC2_MODE.HMC_KEYBOARD_CLASS;

    // shell函数 懒构建体 请勿多次构建 因为此函数返回的函数集内容不会被v8回收
    HMC_SHELL_STARTUP_CLASS?: HMC2_MODE.HMC_SHELL_STARTUP_CLASS | (() => HMC2_MODE.HMC_SHELL_STARTUP_CLASS);
    HMC_SHELL_STARTUP_CLASS_LAZY?: null | HMC2_MODE.HMC_SHELL_STARTUP_CLASS;

    HMC_SHELL_CLASS?: HMC2_MODE.HMC_SHELL_CLASS | (() => HMC2_MODE.HMC_SHELL_CLASS);
    HMC_SHELL_CLASS_LAZY?: HMC2_MODE.HMC_SHELL_CLASS | null;

    /**
     * 获取指定进程的可执行文件路径
     * @param pid 进程id
     * @param isEnumListExists 是否必须出现在进程列表中的 
     * @default false
     * @param isSnapshotName 获取失败时获取进程名称
     * @default false
     */
    getProcessFilePath2?(pid: number, isEnumListExists?: boolean, isSnapshotName?: boolean): Promise<string | null>;

    /**
     * 获取指定进程的可执行文件路径
     * @param pid 进程id
     * @param isEnumListExists 是否必须出现在进程列表中的 
     * @default false
     * @param isSnapshotName 获取失败时获取进程名称
     * @default false
     */
    getProcessFilePath2Sync?(pid: number, isEnumListExists?: boolean, isSnapshotName?: boolean): string | null;

    /**
     * 获取进程名称
     * @param pid 进程id
     * @param type 深度类型
     * @default GET_FIND 
     * - GET_AII 查找所有名字并以\0分隔形式返回
     * - GET_NT 查找进程在内核中的名字
     * - GET_SNP 获取进程快照的名字(如果当前node载体是32位将找不到系统中64位应用)
     * - GET_FIND 找到时就停下 [默认]
     * - GET_MODE 找模块名(最快)
     * @returns 
     */
    getProcessName2?(pid: number): Promise<string | null>;
    getProcessName2?(pid: number, type: HMC2_MODE.GET_PROCESS_NAME_TYPE): Promise<string | null>;
    getProcessName2?(pid: number, type?: unknown): Promise<unknown>;

    /**
     * 获取进程名称
     * @param pid 进程id
     * @param type 深度类型
     * @default GET_FIND 
     * - GET_AII 查找所有名字并以\0分隔形式返回
     * - GET_NT 查找进程在内核中的名字
     * - GET_SNP 获取进程快照的名字(如果当前node载体是32位将找不到系统中64位应用)
     * - GET_FIND 找到时就停下 [默认]
     * - GET_MODE 找模块名(最快)
     * @returns 
     */
    getProcessName2Sync?(pid: number): string | null;
    getProcessName2Sync?(pid: number, type: HMC2_MODE.GET_PROCESS_NAME_TYPE): string | null;
    getProcessName2Sync?(pid: number, type?: unknown): unknown;

    GetRegistrEnvInfo?(ENV_INFO_COMMAND: HMC2_MODE.ENV_INFO_COMMAND, HKey: HMC2_MODE.HKEY, ...aegs: any[]): Promise<unknown>;
    GetRegistrEnvInfoSync?(ENV_INFO_COMMAND: HMC2_MODE.ENV_INFO_COMMAND, HKey: HMC2_MODE.HKEY, ...aegs: any[]): unknown;
}

export module HMC2_MODE {

    export function ALL_NONE_FUN_CALLBECK(...arg: any[]) { }
    
    // 快捷方式的信息
    export interface SHORTCUT_LINK {
        /** 工作环境文件夹**/
        cwd: string;
        /** 进程图标(例如来自1.dll)**/
        icon: string;
        /**图标索引位置 */
        iconIndex: number;
        /** 描述**/
        desc: string;
        /** 启动命令**/
        args: string;
        /** 启动属性**/
        showCmd: number;
        /** hotkey**/
        hotkey: number;
        /** 目标路径**/
        path: string;
    }
    
    /**注册表根目录 */
    export const Hkey = {
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
        /**类型 格式文本化*/
        type_name: REG_VALUE_TYPE_NAME;
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

    export type REG_VALUE_DATA_TYPE = REG_SZ_VALUE["data"] | REG_EXPAND_SZ_VALUE["data"] | REG_DWORD_VALUE["data"] | REG_QWORD_VALUE["data"] | REG_BINARY_VALUE["data"] | REG_MULTI_SZ_VALUE["data"] | REG_ANY_VALUE["data"];

    export type REG_VALUE_TYPE_NAME = `${keyof typeof REG_TYPE}`;//"REG_RESOURCE_REQUIREMENTS_LIST"|"REG_FULL_RESOURCE_DESCRIPTOR"|"REG_RESOURCE_LIST"|"REG_MULTI_SZ"|"REG_LINK"|"REG_QWORD"|"REG_DWORD"|"REG_BINARY"|"REG_EXPAND_SZ"|"REG_SZ"|"REG_NONE";

    export type chQueryValueKeyItem = {
        /**名称 */
        name: string;
        /**类型 */
        type: number;
        /**类型 格式文本化*/
        type_name: REG_VALUE_TYPE_NAME;
        /**大小 */
        size: number;
    };

    export type chQueryFolderKeyItem = {
        /**名称 */
        name: string;
        /**上次修订时间 */
        time: number;
    };

    export type chQueryFolderInfo = {
        /**目录键列表 */
        folderKeyList: chQueryFolderKeyItem[];
        /**值键列表 */
        valueKeyList: chQueryValueKeyItem[];
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
        /**该目录下最大的值键的内容大小 */
        maxValueDataSize: number;
    };

    export type CLIP_HTML_INFO = {
        /**剪贴板中的 HTML 数据 */
        data: string;
        /**片段结束位置（HTML 内容的结束偏移量） */
        EndFragment: number;
        /**HTML 内容的结束偏移量 */
        EndHTML: number;
        /**数据是否有效（是否为有效的 HTML 剪贴板数据） */
        is_valid: boolean;
        /**源 URL（HTML 内容来源的 URL） */
        SourceURL: string;
        /**片段起始位置（HTML 内容的开始偏移量） */
        StartFragment: number;
        /** HTML 内容的开始偏移量 */
        StartHTML: number;
        /**剪贴板数据的版本号 */
        Version: number;
    }

    export type Volume = {
        // 卷的路径 如 F:\\
        path: string;
        // Volume名称 如 "\\\\?\\Volume{00000000-000000-000000-0000-000000}\\"
        name: string;
        // 内核驱动器名称 如 "\\Device\\HarddiskVolume6"
        device: string;
        // HarddiskVolume6
        device_id:string;
        // 00000000-000000-000000-0000-000000
        volume_id:string;
    };

    enum LINK_TYPE_INFO {
        /**硬链接*/
        HARD_LINK_FILE = 170,
        /**软链接*/
        SOFT_LINK_FILE = 168,
        /**目录软链接*/
        SOFT_LINK_DIR = 166,
        /**目录链接点*/
        SYMBOLIC_LINK_DIR = 172,
        /**是个未知的类型 */
        UNKNOWN = 0
    };

    export type Link_TYPE_NAME = keyof typeof LINK_TYPE_INFO;

    export type LINK_FOR_FILE = {
        "isdir": boolean,
        "path": null,
        "size": 0,
        "type": "UNKNOWN",
        "valid": false
    };

    export type LINK_FOR_DIR = {
        "isdir": boolean,
        "path": null,
        "size": 0,
        "type": "UNKNOWN",
        "valid": false
    };

    export type LINK_FOR_SYMBOLIC_LINK_DIR = {
        "isdir": true,
        "path": string | null,
        "size": 1,
        "type": "SYMBOLIC_LINK_DIR",
        "valid": true
    };

    export type LINK_FOR_LINK_DIR = {
        "isdir": true,
        "path": string | null,
        "size": 1,
        "type": "SOFT_LINK_DIR",
        "valid": true
    };

    export type LINK_FOR_SOFT_LINK_FILER = {
        "isdir": false,
        "path": string | null,
        "size": 1,
        "type": "SOFT_LINK_FILE",
        "valid": true
    };

    export type LINK_FOR_HARD_LINK_FILER = {
        "isdir": false,
        "path": string | null,
        "size": number,
        "type": "HARD_LINK_FILE",
        "valid": true,
        "volume": null | Volume
    };

    export type LINK_TARGET = LINK_FOR_FILE | LINK_FOR_DIR | LINK_FOR_SYMBOLIC_LINK_DIR | LINK_FOR_LINK_DIR | LINK_FOR_SOFT_LINK_FILER | LINK_FOR_HARD_LINK_FILER;

    export interface FileAttributesStat {
        // 文件属性 的源位运算值
        attributes: number;
        // 其中包含的值 运算值 列表
        list: FILE_ATTRIBUTE_INFO_LIST[];
    };

    export enum FS_MK_LINK_TARGET_TYPE {
        /**
         * 文件夹链接
         */
        CREATE_DIR_SYMLINK = 166,
        /**
         * 软链接
         */
        CREATE_SYMLINK = 168,
        /**
         * 硬链接
         */
        CREATE_HARD_LINK = 170,
        /**
         * 目录连接点
         */
        CREATE_JUNCTION_POINT_LINK = 172
    }

    export enum LINK_TYPE {
        /**硬链接*/
        HARD_LINK_FILE = 170,
        /**软链接*/
        SOFT_LINK_FILE = 168,
        /**目录软链接*/
        SOFT_LINK_DIR = 166,
        /**目录链接点*/
        JUNCTION_POINT_DIR = 172,
        /**是个未知的类型 */
        UNKNOWN = 0
    };

    export interface LINK_TYPE_EQ {
        // 类型id
        type: LINK_TYPE;
        // 类型名称
        type_name: keyof typeof LINK_TYPE;
        // 是否是基于文件夹
        isDir:boolean;
    }

    export enum FILE_ATTRIBUTE_INFO_LIST {
        /** 文件是只读的 */
        FILE_ATTRIBUTE_READONLY = 0x00000001,

        /** 文件是隐藏的 */
        FILE_ATTRIBUTE_HIDDEN = 0x00000002,

        /** 文件是系统文件 */
        FILE_ATTRIBUTE_SYSTEM = 0x00000004,

        /** 文件是一个目录 */
        FILE_ATTRIBUTE_DIRECTORY = 0x00000010,

        /** 文件将被备份或归档 */
        FILE_ATTRIBUTE_ARCHIVE = 0x00000020,

        /** 保留，不用于文件 */
        FILE_ATTRIBUTE_DEVICE = 0x00000040,

        /** 文件没有其他属性集 */
        FILE_ATTRIBUTE_NORMAL = 0x00000080,

        /** 文件用于临时存储，尽快删除 */
        FILE_ATTRIBUTE_TEMPORARY = 0x00000100,

        /** 文件是稀疏文件，节省磁盘空间 */
        FILE_ATTRIBUTE_SPARSE_FILE = 0x00000200,

        /** 文件或目录具有重解析点 */
        FILE_ATTRIBUTE_REPARSE_POINT = 0x00000400,

        /** 文件或目录是压缩的 */
        FILE_ATTRIBUTE_COMPRESSED = 0x00000800,

        /** 文件的数据没有立即可用 */
        FILE_ATTRIBUTE_OFFLINE = 0x00001000,

        /** 文件或目录不被内容索引 */
        FILE_ATTRIBUTE_NOT_CONTENT_INDEXED = 0x00002000,

        /** 文件或目录是加密的 */
        FILE_ATTRIBUTE_ENCRYPTED = 0x00004000,

        /** 保留，供未来使用 */
        FILE_ATTRIBUTE_VIRTUAL = 0x00010000,

        /** 文件包含完整性流 */
        FILE_ATTRIBUTE_INTEGRITY_STREAM = 0x00008000,

        /** 文件禁止自动数据擦除功能 */
        FILE_ATTRIBUTE_NO_SCRUB_DATA = 0x00020000,

        /** 文件包含扩展属性 (EA) */
        FILE_ATTRIBUTE_EA = 0x00040000,

        /** 文件为固定文件 */
        FILE_ATTRIBUTE_PINNED = 0x00080000,

        /** 文件为未固定文件 */
        FILE_ATTRIBUTE_UNPINNED = 0x00100000
    }

    // 托盘图标信息
    export interface TRAY_ICON {
        // 可执行文件路径
        path: string;
        // 停留时显示的文本
        info: string;
        // 句柄
        handle: number;
    }

    export const HMCNotPlatform = "HMC::HMC current method only supports win32 platform";

    // 键盘四大功能键的状态
    export type BASIC_KEYS = {
        // shift 被按下
        shift: boolean;
        // alt 被按下
        alt: boolean;
        // ctrl 被按下
        ctrl: boolean;
        // win 被按下
        win: boolean;
    }

    export interface HMC_KEYBOARD_CLASS {
        initKeyboardEventHook(): boolean;
        isValidHookKeyboard(): false | number;
        getAllKeyboardEventJson(): `KeyboardEvent[]`;
        stopHookKeyboard(): boolean;
        hasKeysBasic(): BASIC_KEYS;
        hasKeyActivate(KeysEvent: number): boolean;
    }

    export interface HMC_MOUSE_CLASS {
        initMouseEventHook(): boolean;
        isValidHookMouse(): false | number;
        getMouseEventListJson(): string;
        stopHookMouse(): boolean;
        setShakeEventTime(ms: number): boolean;
        setLimitMouseRange(ms: number, x: number, y: number, right: number, bottom: number): boolean;
        hasLimitMouseRangeWorker(): boolean;
        stopLimitMouseRangeWorker(): boolean;
    }

    export interface HMC_SHELL_STARTUP_CLASS {
        has: (keyName: string) => boolean;
        hasOnce: (keyName: string) => boolean;
        remove: (keyName: string) => boolean;
        removeOnce: (keyName: string) => boolean;
        set: (keyName: string, path: string, cmd: string) => boolean;
        setOnce: (keyName: string, path: string, cmd: string) => boolean;
    }

    export interface HMC_SHELL_CLASS {

        /**
         * 删除文件到垃圾桶
         * @param trash_path 处理的路径
         * @param is_Recycle 可以回收 
         * @param isShow 显示窗口
         */
        trashFile?: (trash_path: string, is_Recycle: boolean, isShow: boolean) => boolean;

        /**
         * 清空回收站
         * @param root_path 文件或者根目录 
         * @param isShow 是否显示窗口
         */
        clearTrash?: (root_path: string, isShow: boolean) => boolean;
        /**
         * 
         * @param filePath 
         * @param newFilePath 
         * @param isShowConfirm 
         * @param isShow 
         * @param isShowProgress 
         * @param trash_ok 
         * @returns 
         */
        copyFile?: (filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean, trash_ok: boolean) => boolean;

        /**
         * 
         * @param filePath 
         * @param newFilePath 
         * @param isShowConfirm 
         * @param isShow 
         * @param isShowProgress 
         * @param trash_ok 
         * @returns 
         */
        moveFile?: (filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean, trash_ok: boolean) => boolean;

        /**
         * 弹出右键菜单的接口
         * @param hwnd 调用窗口 / 允许为null
         * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
         * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
         * @param y 坐标
         */
        showContextMenu?: (hwnd: number | null, file: string | string[], x: number, y: number) => boolean;

    }

    // 鼠标按钮变化
    export enum MouseKeyName {
        UNKNOWN = "unknown",
        // 左键按下
        WM_LBUTTONDOWN = "left-button-down",
        // 右键按下
        WM_RBUTTONDOWN = "right-button-down",
        // 左键释放
        WM_LBUTTONUP = "left-button-up",
        // 右键释放
        WM_RBUTTONUP = "right-button-up",
        // 中键按下
        WM_MBUTTONDOWN = "mouse-button-down",
        // 中键释放
        WM_MBUTTONUP = "mouse-button-up",
        // 滚轮向上
        WM_MOUSEWHEEL = "mouse-wheel",
        // 鼠标移动
        WM_MOUSEMOVE = "move"
    }

    export interface KeyboardEvent {
        /**事件id (每次结束时次记) */
        id: number;
        /**事件时间 */
        time: number;
        /**是否按下 */
        down: boolean;
        /**扩展键标志 */
        flags: number;
        /**键码 */
        keyCode: number;
        /**执行的设备id */
        scanCode: number;
        /**映射代码 例如 A 0 1 */
        key: string;
        /**映射代码 例如 KeyE , KeyA */
        code: string;
    }

    export type MouseEventButtonName = "left-mouse-button" | "right-mouse-button" | "middle-mouse-button" | null;

    // 鼠标按钮变化
    export enum MouseKey {
        WM_MOUSEMOVE = 512,
        // 左键按下
        WM_LBUTTONDOWN = 0x0201,
        // 右键按下
        WM_RBUTTONDOWN = 0x0204,
        // 左键释放
        WM_LBUTTONUP = 0x0202,
        // 右键释放
        WM_RBUTTONUP = 0x0205,
        // 中键按下
        WM_MBUTTONDOWN = 0x0207,
        // 中键释放
        WM_MBUTTONUP = 0x0208,
        // 滚轮
        WM_MOUSEWHEEL = 522,
    }

    export interface MouseNulEventItme {
        // 事件id (每次结束时次记)
        id: 0,
        // 事件时间
        time: 0
    }

    export interface MouseMoveEventItme {
        // 事件id (每次结束时次记)
        id: number;
        // 事件时间
        time: number;
        // 按键名称
        button: MouseKey.WM_MOUSEMOVE;
        // 坐标 左到右边
        x: number;
        // 坐标 顶部到底部
        y: number;
    }

    export interface MouseEventItme {
        // 事件id (每次结束时次记)
        id: number;
        // 事件时间
        time: number;
        // 按键名称
        name: MouseEventButtonName;
        // 当前按下的按钮
        button: MouseKey;
        // true 向上 false 向下
        buttonDown: boolean;
        // 滚轮步进数量 负数为向下
        wheelDelta: number;
    }

    export enum ENV_INFO_COMMAND {

        // getProcessCommandLine2   `string`
        GET_COMMAND = 1,
        // getProcessCwdPath2 `string`
        GET_CWD = 2,
        // getProcessCpuUsage2 `float`
        GET_PROCESS_CPU_USAGE = 3,
        // getProcessStartTime2 `number`
        GET_PROCESS_START_TIME = 5,
        // EnumProcesses `json`
        GET_ENUM_PROCESSES_LIST = 6,
        // getAllProcessList2(true) `json`
        GET_ALL_PROCESS_LIST_PID_NAME = 7,
        // getAllProcessList2 `json`
        GET_ALL_PROCESS_LIST_NONE_NAME = 8,
        // getDetailsProcessList2 `json`
        GET_ALL_PROCESS_LIST_DETAILS = 7,
        // getAllProcessListSnp2 `json`
        GET_ALL_PROCESS_LIST_SNP = 10,
        // getAllProcessListNt2 `json`
        GET_ALL_PROCESS_LIST_NT = 11,
        //  getProcessThreadList `json`
        GET_ALL_THREAD_LIST = 12,
        //  getParentProcessID2 `long`
        GET_PARENT_PROCESS_ID = 13,
        // existProcess `bool`
        GET_EXIST_PROCESS = 15,
        // getSubProcess `Array<int>`
        GET_SUB_PROCESS = 19,
        // isProcessWow64 `bool`
        GET_IS_PROCESS_WOW64 = 20,
        // getExecutableCwdList `Array<string>`
        GET_EXECUTABLE_CWD_LIST = 21,
        // sleep(ms);
        SEND_SLEEP = 22,
    };

    export type GET_PROCESS_LIST_COMMAND =
        ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST |
        ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS |
        ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP |
        ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT |
        ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_PID_NAME |
        ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NONE_NAME;

    /**
     * （进程快照）PROCESSENTRY 结构体  它包含了进程的各种信息，如进程 ID、线程计数器、优先级等等
     */
    export type PROCESSENTRY = {
        /**结构体的大小，以字节为单位。 */
        dwSize: number;
        /**引用计数。 */
        cntUsage: number;
        /**进程 ID。 */
        th32ProcessID: number;
        /**默认堆 ID */
        th32DefaultHeapID: number;
        /**模块 ID */
        th32ModuleID: number;
        /**线程计数器。 */
        cntThreads: number;
        /** 父进程 ID。 */
        th32ParentProcessID: number;
        /**基本优先级。 */
        pcPriClassBase: number;
        /**标志位。 */
        dwFlags: number;
        /**进程名。 */
        szExeFile: string;

        // 以下是通过js扩展的

        /**进程名称 */
        name: string,
        /**进程id */
        pid: number;
    };

    export type PROCESSENTRY_DEFAULT = {
        /**进程名称 */
        name: string,
        /**进程id */
        pid: number;
        /**进程路径 */
        path: string;
    };

    export type PROCESSENTRY_NONE_NAME = {
        /**进程名称 */
        name: string | null,
        /**进程id */
        pid: number;
        /**进程路径 */
        path: null;
    };

    export interface PSYSTEM_PROCESS_INFORMATION {
        /**
         * 结构体实例的偏移量
         * - 这是无用的数据
         * - 下一个结构体实例的偏移量，用于遍历多个结构体。
         */
        NextEntryOffset: number;
        /**
         * 进程线程数量。
         */
        NumberOfThreads: number;
        /**进程的镜像名称 */
        ImageName: string;
        /**进程的基本优先级。 */
        BasePriority: number;
        /**进程的唯一标识符。(pid) */
        UniqueProcessId: number;
        /**进程的句柄数。 */
        HandleCount: number;
        /**进程所在的会话 ID。 */
        SessionId: number;
        /**进程的峰值虚拟内存大小。 */
        PeakVirtualSize: number;
        /**进程的虚拟内存大小。 */
        VirtualSize: number;
        /**进程的峰值工作集大小。 */
        PeakWorkingSetSize: number;
        /**进程的实际工作集大小。 */
        WorkingSetSize: number;
        /**
         * `分页池配额使用量`
         * - 分配给进程的分页池配额使用量。
         */
        QuotaPagedPoolUsage: number;
        /**
         * `非分页池内存大小`
         * - 分配给进程的非分页池配额使用量。非分页池是内核提供的内存池，用于驻留在物理内存中，并且不会被换出到磁盘页面文件。该字段表示进程当前使用的非分页池内存大小。
         */
        QuotaNonPagedPoolUsage: number;
        /**
         * `进程的页面文件使用量`
         * - 页面文件是用于交换进程数据的虚拟内存扩展，当物理内存不足时，部分数据会被交换到页面文件中以释放内存。 
         **/
        PagefileUsage: number;
        /**
         * `进程的峰值页面文件使用量`
         * - 进程的峰值页面文件使用量。这是进程在其生命周期内达到的最高页面文件使用量。
         */
        PeakPagefileUsage: number;
        /**
         *`进程的私有页计数`
         * - 私有页是进程专用的虚拟内存页面，不被其他进程共享。
         */
        PrivatePageCount: number;

        // 以下是通过js扩展的

        /**进程名称 */
        name: string,
        /**进程id */
        pid: number;
    }

    /**是一个结构体，它定义在 `tlhelp32.h` 头文件中。它描述了在系统执行快照时正在执行的线程列表中的条目*/
    export type THREADENTRY32 = {
        /**线程使用计数 */
        cntUsage: number,
        /**保留，不再使用 */
        dwFlags: 0,
        /**结构体的大小，以字节为单位 */
        dwSize: number,
        /**创建线程的进程标识符 */
        th32OwnerProcessID: number,
        /**线程标识符，与 `CreateProcess` 函数返回的线程标识符兼容 */
        th32ThreadID: number,
        /**分配给线程的内核基优先级 */
        tpBasePri: number,
        /**线程优先级相对于基本优先级的增量 */
        tpDeltaPri: number
    }

    export enum GET_PROCESS_NAME_TYPE {
        // 查找所有名字
        GET_AII = 1,
        // 使用内核法查找
        GET_NT = 2,
        // 获取进程快照的名字
        GET_SNP = 3,
        // 找到时就停下 [默认]
        GET_FIND = 5,
        // 找模块名
        GET_MODE = 7,
        // 默认 找到时就停下 
        GET_DEFAULT = 0,
        // 即便是从可执行文件中路径获取文件名也行
        GET_FILE_NAME = 8
    };

    export enum ENV_INFO_COMMAND {
        NONE = 0,
        // export function getRegistrQword(HKey: HKEY, SubKey: string, key: string | null): bigint | null;
        GET_REGISTR_QWORD = 70,
        // export function setRegistrQword(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): boolean;
        SET_REGISTR_QWORD = 71,
        // export function getRegistrDword(HKey: HKEY, SubKey: string, key: string | null): number | null;
        GET_REGISTR_DWORD = 72,
        // export function setRegistrDword(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): boolean;
        SET_REGISTR_DWORD = 73,
        // export function getRegistrString(HKey: HKEY, SubKey: string, key: string | null): string | null;
        GET_REGISTR_STRING = 74,
        // export function setRegistrString(HKey: HKEY, SubKey: string, key: string | null, String: string): boolean;
        SET_REGISTR_STRING = 75,
        // export function getRegistrKeys(HKey: HKEY, SubKey: string, key: string | null): chQueryFolderKey;
        GET_REGISTR_KEYS = 76,
        // export function getRegistrStringList(HKey: HKEY, SubKey: string, key: string | null): string[] | null;
        GET_REGISTR_STRING_LIST = 77,
        // export function setRegistrStringList(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[]): boolean;
        SET_REGISTR_STRING_LIST = 78,
        // export function getRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null): Buffer | null;
        GET_REGISTR_BUFFER = 79,
        // export function setRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null, String: Buffer): boolean;
        SET_REGISTR_BUFFER = 710,
        // export function getRegistrValue(HKey: HKEY, SubKey: string, key: string | null): REG_VALUE | null;
        GET_REGISTR_VALUE = 711,
        // export function copyRegistrValue(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): boolean;
        COPY_REGISTR_VALUE = 712,
        // export function copyRegistrFolder(HKey: HKEY, SourceSubKey: string, NewSubKey: string): boolean;
        COPY_REGISTR_FOLDER = 713,
        // export function setRegistrValue(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): boolean;
        SET_REGISTR_VALUE = 714,
        // export function getRegistrValueStat(HKey: HKEY, SubKey: string, key: string | null): RegistrValueStat;
        GET_REGISTR_VALUE_STAT = 715,
        // export function getRegistrFolderStat(HKey: HKEY, SubKey: string, key: string | null): RegistrFolderStat;
        GET_REGISTR_FOLDER_STAT = 716,
        // export function clearRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;
        CLEAR_REGISTR_VALUE = 717,
        // export function clearRegistrFolder(HKey: HKEY, SubKey: string, key: string | null): boolean;
        CLEAR_REGISTR_FOLDER = 718,
        // export function removeRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;
        REMOVE_REGISTR_VALUE = 719,
        // export function removeRegistrFolder(HKey: HKEY, SubKey: string): boolean;
        REMOVE_REGISTR_FOLDER = 720,
        // export function removeRegistrFolderTree(HKey: HKEY, SubKey: string): boolean;
        REMOVE_REGISTR_FOLDER_TREE = 721,
        // export function createRegistrFolder(HKey: HKEY, SubKey: string): boolean;
        CREATE_REGISTR_FOLDER = 722,
        // export function createRegistrValueKey(HKey: HKEY, SubKey: string, key: string | string[]): boolean;
        CREATE_REGISTR_VALUE_KEY = 723,
        // export function hasRegistrKey(HKey: HKEY, SubKey: string, key: string | null): boolean;
        HAS_REGISTR_KEY = 724,
        // export function hasRegistrFolderKey(HKey: HKEY, SubKey: string): boolean;
        HAS_REGISTR_FOLDER_KEY = 725,
    };


}

const HMC_LAZY_CLASS: { [key: string]: any } = {
    ALL_LAZY_FUN_KEY: [
        "HMC_KEYBOARD_CLASS",
        "HMC_MOUSE_CLASS",
        "HMC_SHELL_STARTUP_CLASS",
        "HMC_SHELL_CLASS"
    ]
};

export const Native = (() => {
    const run = {};

    let _BinPath = "";
    let _Native: Native = {};
    let _Loaded = false;

    function LoadNodeBin() {
        try {

            // Debug 环境带入
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

        } catch (s_O) { }
        return {};
    }

    Object.defineProperty(run, "native", {
        // configurable:false,
        enumerable: false,
        // writable:false,
        get: function () {

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
                // @ts-ignore
                _Native.HMC_LAZY_CLASS = HMC_LAZY_CLASS;
            }

            return _Native;
        },
        set: HMC2_MODE.ALL_NONE_FUN_CALLBECK
    });

    const result = run as {
        native: Native;
        HMC_KEYBOARD_CLASS: Native["HMC_KEYBOARD_CLASS_LAZY"];
        HMC_MOUSE_CLASS: Native["HMC_MOUSE_CLASS_LAZY"];
        HMC_SHELL_STARTUP_CLASS: Native["HMC_SHELL_STARTUP_CLASS_LAZY"];
        HMC_SHELL_CLASS: Native["HMC_SHELL_CLASS_LAZY"];
    };

    function MAKE_HMC_LAZY_CLASS(Key: string) {

        const FUN_LAZY_KEY = `${Key}_LAZY` as "HMC_SHELL_CLASS_LAZY";
        const FUN_KEY = Key as "HMC_SHELL_CLASS_LAZY";

        if (!_Native) {
            return null;
        }

        if (!HMC_LAZY_CLASS[FUN_LAZY_KEY] && _Native[FUN_KEY]) {
            if (typeof _Native.HMC_KEYBOARD_CLASS == "function") {
                HMC_LAZY_CLASS[FUN_LAZY_KEY] = (_Native[FUN_KEY] as any)();
            } else {
                HMC_LAZY_CLASS[FUN_LAZY_KEY] = _Native[FUN_KEY];
            }
        }

        return HMC_LAZY_CLASS[FUN_LAZY_KEY];
    }

    for (let index = 0; index < HMC_LAZY_CLASS.ALL_LAZY_FUN_KEY.length; index++) {
        const key = HMC_LAZY_CLASS.ALL_LAZY_FUN_KEY[index] as "HMC_KEYBOARD_CLASS";
        Object.defineProperty(run, key, {
            enumerable: false,
            get: () => MAKE_HMC_LAZY_CLASS(key),
            set: HMC2_MODE.ALL_NONE_FUN_CALLBECK
        });
    }

    return result;
})();

export const { ref } = UtilMain;

// 键鼠/自动化相关
export const Auto = AutoMain;

// 启动项管理
export const Startup = ShellMain.Shell.Startup;

// win32 shell(壳) api 功能集
export const Shell = ShellMain.Shell;

// 进程操作功能集
export const Process = ProcessMain.Process;
export const { Sleep, sleep } = Process;

//注册表编辑合集
export const Registr = RegistrMain.Registr;

export module Window {

    /**
     * 将 electron 句柄内存缓冲区转换为标准 窗口数字句柄
     * @param handleBuffer 例如 Electron.BrowserWindow.getFocusedWindow().getNativeWindowHandle()
     * @returns 
     */
    export function readElectronHandle(handleBuffer: any) {
        let num = 0;

        // Node.js 10.5.0 以上版本
        if (typeof BigInt != 'undefined') {
            let handleBigInt = handleBuffer.readBigUInt64LE();
            return (Number(handleBigInt));
        }
        else {
            if (process.platform == 'win32') {
                num = handleBuffer.readUInt32LE();
            }
            else if (process.platform == 'darwin') {
                num = handleBuffer.readUInt32LE(0) + 2 * 32 * handleBuffer.readUInt32LE(4);
            }
            else {
                num = handleBuffer.readUInt32LE(0) + 2 * 32 * handleBuffer.readUInt32LE(4);
            }

            return num;
        }
        return num;
    }


}

// 软硬链接相关
export const Symlink =  ShellMain.Shell.Symlink;

