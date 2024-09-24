import PromiseEval = require("./promiseEval");
import ShellMain = require("./shell");
import AutoMain = require("./auto");
import ProcessMain = require("./Process");
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
}
export declare module HMC2_MODE {
    type CLIP_HTML_INFO = {
        data: string;
        EndFragment: number;
        EndHTML: number;
        is_valid: boolean;
        SourceURL: string;
        StartFragment: number;
        StartHTML: number;
        Version: number;
    };
    enum FS_MK_LINK_TARGET_TYPE {
        CREATE_DIR_SYMLINK = 166,
        CREATE_SYMLINK = 168,
        CREATE_HARD_LINK = 170,
        CREATE_SYMBOLIC_LINK = 172
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
        isValidHookKeyboard(): boolean;
        getAllKeyboardEventJson(): string;
        stopHookKeyboard(): boolean;
        hasKeysBasic(): BASIC_KEYS;
        hasKeyActivate(KeysEvent: number): boolean;
    }
    interface HMC_MOUSE_CLASS {
        initMouseEventHook(): boolean;
        isValidHookMouse(): boolean;
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
        id: number;
        time: number;
        down: boolean;
        flags: number;
        keyCode: number;
        scanCode: number;
        KeyName: string;
        KeyNameCode: string;
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
        GET_EXECUTABLE_CWD_LIST = 21
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
}
export declare const Native: {
    native: Native;
};
export declare const ref: {
    path(Str: any): string; /**
     * 执行命令代码 并且按照api内容返回 异步
     * @docs PromiseEval 是通过(hmc -> PromiseEval)生成的Promise / Sync 函数 他性能并不是特别出众 但是比编写一个标准化Promise 节省近百行C++代码
     * @param pid 进程id
     * @param command 命令
     */
    bool(bool: any): boolean;
    string(Str: any): string;
    float(Num: any): number;
    int(Num: any): number;
    stringArray(array: any[] | Set<any>): string[];
    intArray(array: any[] | Set<any>): number[];
    formatArgv(...argv: any[] | any[][]): string;
    concatBuff(buffList: Buffer[]): Buffer;
};
export declare module Auto {
    const setLimitMouseRange: typeof AutoMain.setLimitMouseRange;
}
export declare const Startup: {
    "__#42927@#Startup": HMC2_MODE.HMC_SHELL_STARTUP_CLASS | null;
    "__#42927@#initialize"(): void;
    "__#42927@#root": "HKEY_LOCAL_MACHINE";
    "__#42927@#pathRun": string;
    "__#42927@#pathRunOnce": string;
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
export {};
