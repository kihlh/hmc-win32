/// <reference types="node" />
import PromiseEval = require("./promiseEval");
import ShellMain = require("./shell");
import AutoMain = require("./auto");
import UtilMain = require("./util");
import ProcessMain = require("./Process");
import RegistrMain = require("./registr");
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
        format: string;
        hwnd: number;
        id: number;
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
    /**
     * 获取托盘图标列表
     * ? win11 在22621.1000版本之后失效 具体原因查看https://github.com/kihlh/hmc-win32/issues/36
     */
    getTrayList?: () => string;
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
    getThumbnailPng?: (...args: unknown[]) => unknown;
    /**
     * 获取 软/硬 链接的指向内容
     * @param Linkath
     */
    getLinkTarget?: (Linkath: string) => string | string[] | null;
    /**
     * 设置文件夹的缩略图
     * @param folderPath 路径
     * @param iconPath 图标路径
     * @param iconIndex 图标索引 比如exe中的0
     * @returns
     */
    setFolderIcon?: (folderPath: string, iconPath: string, iconIndex?: number) => boolean;
    /**
     * 判断指定文件是否是 软链接/硬链接
     * @param path
     * @returns
     */
    isLinkLink?: (path: string) => boolean;
    /**
     * 创建 软链接/硬链接/目录连接点/文件夹链接
     * @param targetType 创建类型
     * - 文件夹链接 CREATE_DIR_SYMLINK = 166
     * - 软链接 CREATE_SYMLINK = 168
     * - 硬链接 CREATE_HARD_LINK = 170
     * - 目录连接点 CREATE_SYMBOLIC_LINK = 172
     * @param targetPath 目标位置
     * @param sourcePath 源文件路径
     * @returns
     */
    createFsLink?: (targetType: HMC2_MODE.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string) => boolean;
    /**
     * 弹出右键菜单的接口
     * @param hwnd 调用窗口 / 允许为null
     * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
     * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
     * @param y 坐标
     */
    showContextMenu?: (hwnd: number | null, file: string | string[], x: number, y: number) => boolean;
    HMC_MOUSE_CLASS?: () => HMC2_MODE.HMC_MOUSE_CLASS;
    HMC_KEYBOARD_CLASS?: () => HMC2_MODE.HMC_KEYBOARD_CLASS;
    HMC_SHELL_STARTUP_CLASS?: () => HMC2_MODE.HMC_SHELL_STARTUP_CLASS;
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
export declare module HMC2_MODE {
    /**注册表根目录 */
    const Hkey: {
        /**用作默认用户首选设置|也作为单个用户的首选设置 */
        HKEY_CURRENT_CONFIG: "HKEY_CURRENT_CONFIG";
        /**用作默认用户首选设置|也作为单个用户的首选设置 */
        HKEY_USERS: "HKEY_USERS";
        /**是与文档类型和 OLE\COM 相关的信息的支持键。这个键是 */
        HKEY_CLASSES_ROOT: "HKEY_CLASSES_ROOT";
        /**包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息 */
        HKEY_LOCAL_MACHINE: "HKEY_LOCAL_MACHINE";
        /**管理系统当前的用户信息 */
        HKEY_CURRENT_USER: "HKEY_CURRENT_USER";
    };
    type HKEY = keyof typeof Hkey;
    /**
     * 注册表格式类型
     */
    enum REG_TYPE {
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
        REG_QWORD_LITTLE_ENDIAN = 11
    }
    type RegistrValueStat = {
        /**此值的类型 */
        type: REG_TYPE;
        /**内容大小 */
        size: number;
        /**此内容是否存在 */
        exists: boolean;
        /**类型 格式文本化*/
        type_name: REG_VALUE_TYPE_NAME;
    };
    interface REG_SZ_VALUE {
        type: 1;
        typeName: "REG_SZ";
        data: string;
        size: number;
    }
    interface REG_EXPAND_SZ_VALUE {
        type: REG_TYPE.REG_EXPAND_SZ;
        typeName: "REG_EXPAND_SZ";
        data: string;
        dataExpand: string;
        size: number;
    }
    interface REG_DWORD_VALUE {
        type: REG_TYPE.REG_DWORD | REG_TYPE.REG_DWORD_BIG_ENDIAN | REG_TYPE.REG_DWORD_LITTLE_ENDIAN;
        typeName: "REG_DWORD" | "REG_DWORD_BIG_ENDIAN" | "REG_DWORD_LITTLE_ENDIAN";
        data: number;
        size: number;
    }
    interface REG_QWORD_VALUE {
        type: REG_TYPE.REG_QWORD | REG_TYPE.REG_QWORD_LITTLE_ENDIAN;
        typeName: "REG_QWORD" | "REG_QWORD_LITTLE_ENDIAN";
        data: bigint;
        size: number;
    }
    interface REG_BINARY_VALUE {
        type: REG_TYPE.REG_BINARY;
        typeName: "REG_BINARY";
        data: Buffer;
        size: number;
    }
    interface REG_MULTI_SZ_VALUE {
        type: REG_TYPE.REG_MULTI_SZ;
        typeName: "REG_MULTI_SZ";
        data: string[];
        size: number;
    }
    interface REG_NONE_VALUE {
        type: REG_TYPE.REG_NONE;
        typeName: "REG_NONE";
        data: null;
        size: number;
    }
    interface REG_ANY_VALUE {
        type: REG_TYPE.REG_FULL_RESOURCE_DESCRIPTOR | REG_TYPE.REG_LINK | REG_TYPE.REG_NONE | REG_TYPE.REG_RESOURCE_LIST | REG_TYPE.REG_RESOURCE_REQUIREMENTS_LIST;
        typeName: "REG_FULL_RESOURCE_DESCRIPTOR" | "REG_LINK" | "REG_RESOURCE_LIST" | "REG_RESOURCE_REQUIREMENTS_LIST";
        data: Buffer;
        size: number;
    }
    type REG_VALUE = REG_SZ_VALUE | REG_EXPAND_SZ_VALUE | REG_DWORD_VALUE | REG_QWORD_VALUE | REG_BINARY_VALUE | REG_MULTI_SZ_VALUE | REG_ANY_VALUE;
    type REG_VALUE_TYPE_NAME = `${keyof typeof REG_TYPE}`;
    type chQueryValueKeyItem = {
        /**名称 */
        name: string;
        /**类型 */
        type: number;
        /**类型 格式文本化*/
        type_name: REG_VALUE_TYPE_NAME;
        /**大小 */
        size: number;
    };
    type chQueryFolderKeyItem = {
        /**名称 */
        name: string;
        /**上次修订时间 */
        time: number;
    };
    type chQueryFolderInfo = {
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
    type CLIP_HTML_INFO = {
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
    };
    enum FS_MK_LINK_TARGET_TYPE {
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
        CREATE_SYMBOLIC_LINK = 172
    }
    interface TRAY_ICON {
        path: string;
        info: string;
        handle: number;
    }
    const HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
    type BASIC_KEYS = {
        shift: boolean;
        alt: boolean;
        ctrl: boolean;
        win: boolean;
    };
    interface HMC_KEYBOARD_CLASS {
        initKeyboardEventHook(): boolean;
        isValidHookKeyboard(): false | number;
        getAllKeyboardEventJson(): `KeyboardEvent[]`;
        stopHookKeyboard(): boolean;
        hasKeysBasic(): BASIC_KEYS;
        hasKeyActivate(KeysEvent: number): boolean;
    }
    interface HMC_MOUSE_CLASS {
        initMouseEventHook(): boolean;
        isValidHookMouse(): false | number;
        getMouseEventListJson(): string;
        stopHookMouse(): boolean;
        setShakeEventTime(ms: number): boolean;
        setLimitMouseRange(ms: number, x: number, y: number, right: number, bottom: number): boolean;
        hasLimitMouseRangeWorker(): boolean;
        stopLimitMouseRangeWorker(): boolean;
    }
    interface HMC_SHELL_STARTUP_CLASS {
        has: (keyName: string) => boolean;
        hasOnce: (keyName: string) => boolean;
        remove: (keyName: string) => boolean;
        removeOnce: (keyName: string) => boolean;
        set: (keyName: string, path: string, cmd: string) => boolean;
        setOnce: (keyName: string, path: string, cmd: string) => boolean;
    }
    enum MouseKeyName {
        UNKNOWN = "unknown",
        WM_LBUTTONDOWN = "left-button-down",
        WM_RBUTTONDOWN = "right-button-down",
        WM_LBUTTONUP = "left-button-up",
        WM_RBUTTONUP = "right-button-up",
        WM_MBUTTONDOWN = "mouse-button-down",
        WM_MBUTTONUP = "mouse-button-up",
        WM_MOUSEWHEEL = "mouse-wheel",
        WM_MOUSEMOVE = "move"
    }
    interface KeyboardEvent {
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
    type MouseEventButtonName = "left-mouse-button" | "right-mouse-button" | "middle-mouse-button" | null;
    enum MouseKey {
        WM_MOUSEMOVE = 512,
        WM_LBUTTONDOWN = 513,
        WM_RBUTTONDOWN = 516,
        WM_LBUTTONUP = 514,
        WM_RBUTTONUP = 517,
        WM_MBUTTONDOWN = 519,
        WM_MBUTTONUP = 520,
        WM_MOUSEWHEEL = 522
    }
    interface MouseNulEventItme {
        id: 0;
        time: 0;
    }
    interface MouseMoveEventItme {
        id: number;
        time: number;
        button: MouseKey.WM_MOUSEMOVE;
        x: number;
        y: number;
    }
    interface MouseEventItme {
        id: number;
        time: number;
        name: MouseEventButtonName;
        button: MouseKey;
        buttonDown: boolean;
        wheelDelta: number;
    }
    enum ENV_INFO_COMMAND {
        GET_COMMAND = 1,
        GET_CWD = 2,
        GET_PROCESS_CPU_USAGE = 3,
        GET_PROCESS_START_TIME = 5,
        GET_ENUM_PROCESSES_LIST = 6,
        GET_ALL_PROCESS_LIST_PID_NAME = 7,
        GET_ALL_PROCESS_LIST_NONE_NAME = 8,
        GET_ALL_PROCESS_LIST_DETAILS = 7,
        GET_ALL_PROCESS_LIST_SNP = 10,
        GET_ALL_PROCESS_LIST_NT = 11,
        GET_ALL_THREAD_LIST = 12,
        GET_PARENT_PROCESS_ID = 13,
        GET_EXIST_PROCESS = 15,
        GET_SUB_PROCESS = 19,
        GET_IS_PROCESS_WOW64 = 20,
        GET_EXECUTABLE_CWD_LIST = 21,
        SEND_SLEEP = 22
    }
    type GET_PROCESS_LIST_COMMAND = ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST | ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS | ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP | ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT | ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_PID_NAME | ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NONE_NAME;
    /**
     * （进程快照）PROCESSENTRY 结构体  它包含了进程的各种信息，如进程 ID、线程计数器、优先级等等
     */
    type PROCESSENTRY = {
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
        /**进程名称 */
        name: string;
        /**进程id */
        pid: number;
    };
    type PROCESSENTRY_DEFAULT = {
        /**进程名称 */
        name: string;
        /**进程id */
        pid: number;
        /**进程路径 */
        path: string;
    };
    type PROCESSENTRY_NONE_NAME = {
        /**进程名称 */
        name: string | null;
        /**进程id */
        pid: number;
        /**进程路径 */
        path: null;
    };
    interface PSYSTEM_PROCESS_INFORMATION {
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
        /**进程名称 */
        name: string;
        /**进程id */
        pid: number;
    }
    /**是一个结构体，它定义在 `tlhelp32.h` 头文件中。它描述了在系统执行快照时正在执行的线程列表中的条目*/
    type THREADENTRY32 = {
        /**线程使用计数 */
        cntUsage: number;
        /**保留，不再使用 */
        dwFlags: 0;
        /**结构体的大小，以字节为单位 */
        dwSize: number;
        /**创建线程的进程标识符 */
        th32OwnerProcessID: number;
        /**线程标识符，与 `CreateProcess` 函数返回的线程标识符兼容 */
        th32ThreadID: number;
        /**分配给线程的内核基优先级 */
        tpBasePri: number;
        /**线程优先级相对于基本优先级的增量 */
        tpDeltaPri: number;
    };
    enum GET_PROCESS_NAME_TYPE {
        GET_AII = 1,
        GET_NT = 2,
        GET_SNP = 3,
        GET_FIND = 5,
        GET_MODE = 7,
        GET_DEFAULT = 0,
        GET_FILE_NAME = 8
    }
    enum ENV_INFO_COMMAND {
        NONE = 0,
        GET_REGISTR_QWORD = 70,
        SET_REGISTR_QWORD = 71,
        GET_REGISTR_DWORD = 72,
        SET_REGISTR_DWORD = 73,
        GET_REGISTR_STRING = 74,
        SET_REGISTR_STRING = 75,
        GET_REGISTR_KEYS = 76,
        GET_REGISTR_STRING_LIST = 77,
        SET_REGISTR_STRING_LIST = 78,
        GET_REGISTR_BUFFER = 79,
        SET_REGISTR_BUFFER = 710,
        GET_REGISTR_VALUE = 711,
        COPY_REGISTR_VALUE = 712,
        COPY_REGISTR_FOLDER = 713,
        SET_REGISTR_VALUE = 714,
        GET_REGISTR_VALUE_STAT = 715,
        GET_REGISTR_FOLDER_STAT = 716,
        CLEAR_REGISTR_VALUE = 717,
        CLEAR_REGISTR_FOLDER = 718,
        REMOVE_REGISTR_VALUE = 719,
        REMOVE_REGISTR_FOLDER = 720,
        REMOVE_REGISTR_FOLDER_TREE = 721,
        CREATE_REGISTR_FOLDER = 722,
        CREATE_REGISTR_VALUE_KEY = 723,
        HAS_REGISTR_KEY = 724,
        HAS_REGISTR_FOLDER_KEY = 725
    }
}
export declare const Native: {
    native: Native;
};
export declare const ref: typeof UtilMain.ref;
export declare const Auto: typeof AutoMain;
export declare const Startup: {
    "__#13951@#Startup": HMC2_MODE.HMC_SHELL_STARTUP_CLASS | null;
    "__#13951@#initialize"(): void;
    "__#13951@#root": "HKEY_LOCAL_MACHINE";
    "__#13951@#pathRun": string;
    "__#13951@#pathRunOnce": string;
    has(keyName: string): boolean;
    hasOnce(keyName: string): boolean;
    remove(keyName: string): boolean;
    removeOnce(keyName: string): boolean;
    set(keyName: string, path: string, cmd?: string | undefined): boolean;
    setOnce(keyName: string, path: string, cmd?: string | undefined): boolean;
    enum(): {
        [key: string]: string;
    };
    enumOnce(): {
        [key: string]: string;
    };
    keys(): never[];
    keysOnce(): never[];
};
export declare const Shell: typeof ShellMain.Shell;
export declare const Process: typeof ProcessMain.Process;
export declare const Sleep: typeof ProcessMain.Process.Sleep, sleep: typeof ProcessMain.Process.sleep;
export declare const Registr: typeof RegistrMain.Registr;
export declare module Window {
    /**
     * 将 electron 句柄内存缓冲区转换为标准 窗口数字句柄
     * @param handleBuffer 例如 Electron.BrowserWindow.getFocusedWindow().getNativeWindowHandle()
     * @returns
     */
    function readElectronHandle(handleBuffer: any): number;
}
export {};
