import { createRequire } from "node:module";
import { ref } from "./util";
import *as PromiseEval from "./promiseEval";
import { HMC_PROMISEEVAL_TASK_TYPE } from "./ShellPromiseEval";
import { HMC } from "./HMC";
import { HMC_SOKE_PROMISEEVAL_TASK_TYPE } from "./Sock";

const HMC_LAZY_CLASS: { [key: string]: any } = {
    ALL_LAZY_FUN_KEY: [
        "HMC_KEYBOARD_CLASS",
        "HMC_MOUSE_CLASS",
        "HMC_SHELL_STARTUP_CLASS",
        "HMC_SHELL_CLASS"
    ]
};

export const HMC_STORE = {
    // 鼠标hook被启用过
    IS_HOOK_MOUSE: false,
    // 键盘hook被启用过
    IS_HOOK_KEYBOARD: false,
    // 鼠标区域限制启用过
    IS_MOUSE_DISABLE: false,
    // 键鼠锁定启用
    IS_MOUSE_LOCK: false,

    ____native____: null as HMC_V1.Native | null,
    get native_v1() {
        if (!HMC_STORE.____native____) HMC_STORE.____native____ = get_native_v1();
        return HMC_STORE.____native____;
    },
    HMC_LAZY_CLASS,
    ____native__v2____: null as Native_v2 | null,
    get native() {
        if (!HMC_STORE.____native__v2____) HMC_STORE.____native__v2____ = Native_v2().native;
        return HMC_STORE.____native__v2____;
    },

    get HMC_KEYBOARD_CLASS() {
        if (!HMC_STORE.____native__v2____) HMC_STORE.____native__v2____ = Native_v2().native;
        return HMC_STORE.____native__v2____?.HMC_KEYBOARD_CLASS_LAZY;
    },

    get HMC_SHELL_CLASS() {
        if (!HMC_STORE.____native__v2____) HMC_STORE.____native__v2____ = Native_v2().native;
        return HMC_STORE.____native__v2____.HMC_SHELL_CLASS_LAZY;
    },

    get HMC_SHELL_STARTUP_CLASS() {
        if (!HMC_STORE.____native__v2____) HMC_STORE.____native__v2____ = Native_v2().native;
        return HMC_STORE.____native__v2____?.HMC_SHELL_STARTUP_CLASS_LAZY;
    },

    get HMC_MOUSE_CLASS() {
        if (!HMC_STORE.____native__v2____) HMC_STORE.____native__v2____ = Native_v2().native;
        return HMC_STORE.____native__v2____?.HMC_MOUSE_CLASS_LAZY;
    },

};


interface Native_v2 {
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
    HMC_GetShellEnvInfo?(command: HMC_PROMISEEVAL_TASK_TYPE, ...arg: unknown[]): Promise<unknown>;

    /**
     * 执行Shell命令代码 并且按照api内容返回 同步
     * @docs GetShellEnvInfo 是通过(hmc -> GetShellEnvInfo)生成的Promise / Sync 函数 他性能比PromiseEval更好 因为他并未使用any泛型 仅使用了精简的 数据类型
     * @param pid 进程id
     * @param command 命令
     */
    HMC_GetShellEnvInfoSync?(command: HMC_PROMISEEVAL_TASK_TYPE, ...arg: unknown[]): unknown;

    /**
     * 执行Shell命令代码 并且按照api内容返回 异步
     * @docs GetShellEnvInfo 是通过(hmc -> GetShellEnvInfo)生成的Promise / Sync 函数 他性能比PromiseEval更好 因为他并未使用any泛型 仅使用了精简的 数据类型
     * @param pid 进程id
     * @param command 命令
     */
    HMC_GetSockEnvInfo?(command: HMC_SOKE_PROMISEEVAL_TASK_TYPE, ...arg: unknown[]): Promise<unknown>;

    /**
     * 执行Shell命令代码 并且按照api内容返回 同步
     * @docs GetShellEnvInfo 是通过(hmc -> GetShellEnvInfo)生成的Promise / Sync 函数 他性能比PromiseEval更好 因为他并未使用any泛型 仅使用了精简的 数据类型
     * @param pid 进程id
     * @param command 命令
     */
    HMC_GetSockEnvInfoSync?(command: HMC_SOKE_PROMISEEVAL_TASK_TYPE, ...arg: unknown[]): unknown;

    /**
     * 执行进程环境获取 需要配合命令代码
     * @docs  是类似于HMC_PromiseEval的函数 但是性能更好但是局限性是只能发送 long,long 数据 返回的只能是文本 
     * @param pid 进程id
     * @param command 命令
     */
    getProcessEnvInfo2?(pid: number, command: HMC.ENV_INFO_COMMAND): Promise<string | null>;

    /**
     * 执行进程环境获取 需要配合命令代码
     * @docs  是类似于HMC_PromiseEval的函数 但是性能更好但是局限性是只能发送 long,long 数据 返回的只能是文本 
     * @param pid 进程id
     * @param command 命令
     */
    getProcessEnvInfo2Sync?(pid: number, command: HMC.ENV_INFO_COMMAND): string | null;

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
    getClipboardHTML?: () => HMC.CLIP_HTML_INFO | null;


    // 鼠标函数 懒构建体 请勿多次构建 因为此函数返回的函数集内容不会被v8回收
    HMC_MOUSE_CLASS?: HMC.HMC_MOUSE_CLASS | (() => HMC.HMC_MOUSE_CLASS);
    HMC_MOUSE_CLASS_LAZY?: null | HMC.HMC_MOUSE_CLASS;

    // 键盘函数 懒构建体 请勿多次构建 因为此函数返回的函数集内容不会被v8回收
    HMC_KEYBOARD_CLASS?: HMC.HMC_KEYBOARD_CLASS | (() => HMC.HMC_KEYBOARD_CLASS);
    HMC_KEYBOARD_CLASS_LAZY?: null | HMC.HMC_KEYBOARD_CLASS;

    // shell函数 懒构建体 请勿多次构建 因为此函数返回的函数集内容不会被v8回收
    HMC_SHELL_STARTUP_CLASS?: HMC.HMC_SHELL_STARTUP_CLASS | (() => HMC.HMC_SHELL_STARTUP_CLASS);
    HMC_SHELL_STARTUP_CLASS_LAZY?: null | HMC.HMC_SHELL_STARTUP_CLASS;

    HMC_SHELL_CLASS?: HMC.HMC_SHELL_CLASS | (() => HMC.HMC_SHELL_CLASS);
    HMC_SHELL_CLASS_LAZY?: HMC.HMC_SHELL_CLASS | null;

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
    getProcessName2?(pid: number, type: HMC.Process.GET_PROCESS_NAME_TYPE): Promise<string | null>;
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
    getProcessName2Sync?(pid: number, type: HMC.Process.GET_PROCESS_NAME_TYPE): string | null;
    getProcessName2Sync?(pid: number, type?: unknown): unknown;

    GetRegistrEnvInfo?(ENV_INFO_COMMAND: HMC.ENV_INFO_COMMAND, HKey: HMC.HKEY, ...aegs: any[]): Promise<unknown>;
    GetRegistrEnvInfoSync?(ENV_INFO_COMMAND: HMC.ENV_INFO_COMMAND, HKey: HMC.HKEY, ...aegs: any[]): unknown;
}

export const Native_v2 = (() => {
    const run = {};

    let _BinPath = "";
    let _Native: Native_v2 = {};
    let _Loaded = false;

    const ESM_PATH = process.env.HMC___CREATE__REQUIRE___URL__ESM_MODE_PATH;

    const version = ref.int(process.version.match(/^(?:.+?)?v([0-9]+)/)?.[1]);

    let _require = typeof require == "undefined" ? null : require;

    if (ESM_PATH && version >= 11) {
        _require = createRequire(ESM_PATH || process.cwd());
    }

    function LoadNodeBin() {
        try {

            // Debug 环境带入
            if (process.env) {
                if (process.env.USERNAME == "kiic" && process.env.msvc_dir && process.env.mode) {
                    _BinPath = process.env.mode;
                    _Native = _require && _require(_BinPath);
                    return _Native;
                }
            }

            if (_BinPath) {
                _Native = _require && _require(_BinPath);
                return _Native;
            } else {

                if (process.arch.match(/^(x32|ia32)$/)) {
                    return _require && _require("./bin/HMC@Beta_x86.node");
                }

                if (process.arch.match(/^x64$/)) {
                    return _require && _require("./bin/HMC@Beta_x64.node");
                }

            }

            // 不会被执行 这里是给某些打包工具识别 不然会导致 打包出错
            if (!process.env && process) {
                require("./bin/HMC@Beta_x86.node");
                require("./bin/HMC@Beta_x64.node");
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
        set: HMC.ALL_NONE_FUN_CALLBECK
    });

    const result = run as {
        native: Native_v2;
        HMC_KEYBOARD_CLASS: Native_v2["HMC_KEYBOARD_CLASS_LAZY"];
        HMC_MOUSE_CLASS: Native_v2["HMC_MOUSE_CLASS_LAZY"];
        HMC_SHELL_STARTUP_CLASS: Native_v2["HMC_SHELL_STARTUP_CLASS_LAZY"];
        HMC_SHELL_CLASS: Native_v2["HMC_SHELL_CLASS_LAZY"];
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
            set: (v) => {
                result[key] = v;
            }
        });
    }

    return result;
});


/**
 * @zh-cn 静态调用 hmc.dll (注意如果您不知道这个是什么作用 请勿随意调用 参数错误有可能会导致进程崩溃)
 * @en-us Static call to hmc.dll (Note that if you don't know what this does, don't call it at random.  Parameter errors may cause the process to crash)
 */
export const get_native_v1: () => HMC_V1.Native | null = (binPath?: string) => {
    let _BinPath = "";
    let _Native: HMC_V1.Native | null = null;
    let _Loaded = false;

    const ESM_PATH = process.env.HMC___CREATE__REQUIRE___URL__ESM_MODE_PATH;

    delete process.env["HMC___CREATE__REQUIRE___URL__ESM_MODE_PATH"];

    const version = ref.int(process.version.match(/^(?:.+?)?v([0-9]+)/)?.[1]);

    let _require = typeof require == "undefined" ? null : require;

    if (ESM_PATH && version >= 11) {
        _require = createRequire(ESM_PATH || process.cwd());
    }

    function LoadNodeBin() {
        try {

            if (_BinPath) {
                _Native = _require && _require(_BinPath);
                return _Native;
            } else {

                if (process.arch.match(/^(x32|ia32)$/)) {
                    return _require && _require("./bin/HMC@v1.0_x86.node");
                }

                if (process.arch.match(/^x64$/)) {
                    return _require && _require("./bin/HMC@v1.0_x64.node");
                }

            }

            // 不会被执行 这里是给某些打包工具识别 不然会导致 打包出错
            if (!process.env && process) {
                require("./bin/HMC@v1.0_x86.node");
                require("./bin/HMC@v1.0_x64.node");
            }

        } catch (s_O) { }
        return {};
    }


    return (function () {

        if (!_Loaded && !_BinPath) {

            if (process.arch.match(/^(x32|ia32)$/)) {
                _BinPath = "./bin/HMC@v1.0_x86.node";
            }

            if (process.arch.match(/^x64$/)) {
                _BinPath = "./bin/HMC@v1.0_x64.node";
            }
        }

        if (!_Loaded) {
            _Native = LoadNodeBin();
            // @ts-ignore
            _Native.HMC_LAZY_CLASS = HMC_LAZY_CLASS;
        }

        return _Native;
    })();

};

// 类型
export namespace HMC_V1 {

    export type MouseMovePoints = {
        // 坐标 x 左边到右边的距离(px)
        "x": number | null,
        // 坐标 y 顶边到底部的距离(px)
        "y": number | null,
        // 此任务的发生时间
        "time": number | null,
        // 预留数据
        "dwExtraInfo": number | null
    }

    export enum REG_TYPE {
        REG_NONE = 0,      // 没有类型
        REG_SZ = 1,        // 结尾的文本
        REG_EXPAND_SZ = 2, // 可扩展文本
        REG_BINARY = 3,                   // 二进制
        REG_DWORD = 4,                    // 32-bit number
        REG_DWORD_LITTLE_ENDIAN = 4,      // 32-bit number (same as REG_DWORD)
        REG_DWORD_BIG_ENDIAN = 5,         // 32-bit number
        REG_LINK = 6,                     // Symbolic Link (unicode)
        REG_MULTI_SZ = 7,                 // Multiple Unicode strings
        REG_RESOURCE_LIST = 8,            // Resource list in the resource map
        REG_FULL_RESOURCE_DESCRIPTOR = 9, // Resource list in the hardware description
        REG_RESOURCE_REQUIREMENTS_LIST = 10,
        REG_QWORD = 11,               // 64-bit number
        REG_QWORD_LITTLE_ENDIAN = 11, // 64-bit number (same as REG_QWORD)
    }

    export type EnumRegistrFolderItem = RegistrFolderInfo & {
        key: string[]; // 值键
        Folder: string[]; // 目录键
    };

    export type RegistrFolderInfo = {
        size: number;   // 值键 / 目录键 数量
        exists: boolean;      // 此键是否存在
        folderSize: number; // 此目录键总数量
        keySize: number;    // 此目录键总数量
        time: number | null;   // 时间戳(最后写入时间)
    };

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
    };

    /**
     * 是一个结构体，它定义在 `tlhelp32.h` 头文件中。它描述了在系统执行快照时正在执行的线程列表中的条目
     */
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
    /**
     * 设置窗口坐标
     */
    export type RECT_CONFIG = {
        /**
         * (right) 从屏幕右边到所在位置得像素数
         */
        x?: number;
        /**
         * (top)从屏幕顶部边到所在位置得像素数
         */
        y?: number;
        /**
         * 宽度
         */
        width?: number;
        /**
         * 高度
         */
        height?: number;
        /**
         * (x)从屏幕左边到所在位置得像素数
         */
        right?: number;
        /**
         * (y)从屏幕顶部边到所在位置得像素数
         */
        top?: number;
    };

    /**
     * C++中的坐标
     */
    export type cPOINT = {
        // (left) 从屏幕左边到所在位置得像素数
        x: number;
        //  (top) 从屏幕顶部边到所在位置得像素数
        y: number;
    }

    // WebView2 信息
    export type WebView2Info = {
        // 版本号
        version: string,
        // 名称
        name: string,
        // 安装路径
        location: string,
    } | null;


    /**
     * C++ 中的 位置定义
     */
    export type cRECT = {
        // (x) 从屏幕左边到所在位置得像素数
        left: number;
        // (y) 从屏幕顶部边到所在位置得像素数
        top: number;
        // 距离右边的距离
        right: number;
        // 距离底部的距离
        bottom: number;
    }

    /**
     * C++中的位置定义
     */
    export interface cRect {
        // (left) 从屏幕左边到所在位置得像素数
        x: number;
        //  (top) 从屏幕顶部边到所在位置得像素数
        y: number;
        // 高度
        height: number;
        // 宽度
        width: number;
    }

    // 枚举进程id的内容 带执行文件路径
    export interface enumProcessContP {
        // 软件名称
        name: string;
        // 进程id
        pid: ProcessID;
        // 可执行文件路径
        path: string;
    }

    // 枚举进程id的内容
    export interface enumProcessCont {
        // 软件名称
        name: string;
        // 进程id
        pid: ProcessID;
    }

    // 鼠标所在位置
    export interface MousePosn {
        // (x) 从屏幕左边到所在位置得像素数
        left: number;
        // (y) 从屏幕顶部边到所在位置得像素数
        top: number;
        // (left) 从屏幕左边到所在位置得像素数
        x: number;
        //  (top) 从屏幕顶部边到所在位置得像素数
        y: number;
    };

    // 返回的进程id
    export type ProcessID = number;

    // win窗口允许的不透明度
    export type HandleTransparent = number;

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

    export type direction = "right" | "left" | "right-top" | "left-bottom" | "left-top" | "right-bottom" | "bottom" | "top" | "middle";

    // getsystemmetrics的可获取值 详见 https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getsystemmetrics
    export enum SYSTEM_METRICS_NINDEX {
        // 指定系统如何排列最小化窗口的标志。 有关详细信息，请参阅本主题中的“备注”部分。  
        SM_ARRANGE = 56,
        // 指定系统启动方式的 值：0 正常启动1 故障安全启动2 通过网络启动实现故障安全故障安全启动 (也称为 SafeBoot、安全模式或干净启动) 会绕过用户启动文件。  
        SM_CLEANBOOT = 67,
        // 桌面上的显示监视器数。 有关详细信息，请参阅本主题中的“备注”部分。  
        SM_CMONITORS = 80,
        // 鼠标上的按钮数;如果未安装鼠标，则为零。                       
        SM_CMOUSEBUTTONS = 43,
        // 反映笔记本电脑或平板模式的状态，0 表示板模式，否则为非零。 当此系统指标发生更改时，系统会通过 LPARAM 中带有“ConvertibleSlateMode” [的WM_SETTINGCHANGE](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-settingchange) 发送广播消息。 请注意，此系统指标不适用于台式电脑。 在这种情况下，请使用 [GetAutoRotationState](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-getautorotationstate)。  
        SM_CONVERTIBLESLATEMODE = 0x2003,
        // 窗口边框的宽度（以像素为单位）。 这等效于具有 3D 外观的窗口的 SM_CXEDGE 值。  
        SM_CXBORDER = 5,
        // 光标的标称宽度（以像素为单位）。                              
        SM_CXCURSOR = 13,
        // 此值与 SM_CXFIXEDFRAME 相同。                                 
        SM_CXDLGFRAME = 7,
        // 矩形围绕双击序列中第一次单击的位置的宽度（以像素为单位）。 第二次单击必须在由 SM_CXDOUBLECLK 和 SM_CYDOUBLECLK 定义的矩形内发生，系统才能将两次单击视为双击。 两次单击也必须在指定时间内发生。若要设置双击矩形的宽度，请使用SPI_SETDOUBLECLKWIDTH调用 [SystemParametersInfo](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-systemparametersinfoa) 。  
        SM_CXDOUBLECLK = 36,
        // 鼠标指针在拖动操作开始之前可以移动的鼠标向下点任一侧的像素数。 这允许用户轻松单击并释放鼠标按钮，而不会无意中启动拖动操作。 如果此值为负值，则从鼠标向下点的左侧减去该值，并将其添加到其右侧。  
        SM_CXDRAG = 68,
        // 三维边框的宽度（以像素为单位）。 此指标是SM_CXBORDER的三维对应指标。  
        SM_CXEDGE = 45,
        // 窗口周围具有描述文字但不是相当大的（以像素为单位）的框架的粗细。 SM_CXFIXEDFRAME是水平边框的高度，SM_CYFIXEDFRAME是垂直边框的宽度。此值与 SM_CXDLGFRAME 相同。  
        SM_CXFIXEDFRAME = 7,
        // [DrawFocusRect](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-drawfocusrect) 绘制的焦点矩形的左边缘和右边缘的宽度。 此值以像素为单位。**Windows 2000：** 不支持此值。  
        SM_CXFOCUSBORDER = 83,
        // 此值与 SM_CXSIZEFRAME 相同。                                  
        SM_CXFRAME = 32,
        // 主显示器上全屏窗口的工作区宽度（以像素为单位）。 若要获取系统任务栏或应用程序桌面工具栏未遮挡的屏幕部分的坐标，请使用SPI_GETWORKAREA值调用 [SystemParametersInfo](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-systemparametersinfoa) 函数。  
        SM_CXFULLSCREEN = 16,
        // 水平滚动条上箭头位图的宽度（以像素为单位）。                  
        SM_CXHSCROLL = 21,
        // 水平滚动条中拇指框的宽度（以像素为单位）。                    
        SM_CXHTHUMB = 10,
        // 图标的系统大宽度（以像素为单位）。 [LoadIcon](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-loadicona) 函数只能加载具有SM_CXICON和SM_CYICON指定尺寸的图标。 有关详细信息 [，请参阅图标大小](https://learn.microsoft.com/zh-cn/windows/win32/menurc/about-icons#icon-sizes) 。  
        SM_CXICON = 11,
        // 大图标视图中项的网格单元格的宽度（以像素为单位）。 每个项都适合在排列时按SM_CYICONSPACING SM_CXICONSPACING大小的矩形。 此值始终大于或等于 SM_CXICON。  
        SM_CXICONSPACING = 38,
        // 主显示监视器上最大化的顶级窗口的默认宽度（以像素为单位）。    
        SM_CXMAXIMIZED = 61,
        // 具有描述文字和大小调整边框（以像素为单位）的窗口的默认最大宽度。 此指标是指整个桌面。 用户无法将窗口框架拖动到大于这些尺寸的大小。 窗口可以通过处理 [WM_GETMINMAXINFO](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-getminmaxinfo) 消息来替代此值。  
        SM_CXMAXTRACK = 59,
        // 默认菜单的宽度检查标记位图（以像素为单位）。                  
        SM_CXMENUCHECK = 71,
        // 菜单栏按钮的宽度，例如在多个文档界面中使用的子窗口关闭按钮（以像素为单位）。  
        SM_CXMENUSIZE = 54,
        // 窗口的最小宽度（以像素为单位）。                              
        SM_CXMIN = 28,
        // 最小化窗口的宽度（以像素为单位）。                            
        SM_CXMINIMIZED = 57,
        // 最小化窗口的网格单元格的宽度（以像素为单位）。 每个最小化窗口在排列时适合此大小的矩形。 此值始终大于或等于 SM_CXMINIMIZED。  
        SM_CXMINSPACING = 47,
        // 窗口的最小跟踪宽度（以像素为单位）。 用户无法将窗口框架拖动到小于这些尺寸的大小。 窗口可以通过处理 [WM_GETMINMAXINFO](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-getminmaxinfo) 消息来替代此值。  
        SM_CXMINTRACK = 34,
        // 带字幕窗口的边框填充量（以像素为单位）。**Windows XP/2000：** 不支持此值。  
        SM_CXPADDEDBORDER = 92,
        // 主显示器的屏幕宽度（以像素为单位）。 这是通过调用 [GetDeviceCaps](https://learn.microsoft.com/zh-cn/windows/desktop/api/wingdi/nf-wingdi-getdevicecaps) 获取的相同值，如下所示： `GetDeviceCaps( hdcPrimaryMonitor, HORZRES)`。  
        SM_CXSCREEN = 0,
        // 窗口中按钮的宽度描述文字或标题栏（以像素为单位）。            
        SM_CXSIZE = 30,
        // 可调整大小的窗口周边的大小边框的粗细（以像素为单位）。 SM_CXSIZEFRAME是水平边框的宽度，SM_CYSIZEFRAME是垂直边框的高度。此值与 SM_CXFRAME 相同。  
        SM_CXSIZEFRAME = 32,
        // 图标的系统小宽度（以像素为单位）。 小图标通常显示在窗口标题和小图标视图中。 有关详细信息 [，请参阅图标大小](https://learn.microsoft.com/zh-cn/windows/win32/menurc/about-icons#icon-sizes) 。  
        SM_CXSMICON = 49,
        // 小描述文字按钮的宽度（以像素为单位）。                        
        SM_CXSMSIZE = 52,
        // 虚拟屏幕的宽度（以像素为单位）。 虚拟屏幕是所有显示监视器的边框。 SM_XVIRTUALSCREEN指标是虚拟屏幕左侧的坐标。  
        SM_CXVIRTUALSCREEN = 78,
        // 垂直滚动条的宽度（以像素为单位）。                            
        SM_CXVSCROLL = 2,
        // 窗口边框的高度（以像素为单位）。 这等效于具有 3D 外观的窗口的 SM_CYEDGE 值。  
        SM_CYBORDER = 6,
        // 描述文字区域的高度（以像素为单位）。                          
        SM_CYCAPTION = 4,
        // 光标的标称高度（以像素为单位）。                              
        SM_CYCURSOR = 14,
        // 此值与 SM_CYFIXEDFRAME 相同。                                 
        SM_CYDLGFRAME = 8,
        // 矩形围绕双击序列中第一次单击的位置的高度（以像素为单位）。 第二次单击必须在由 SM_CXDOUBLECLK 定义的矩形内发生，SM_CYDOUBLECLK系统会将两次单击视为双击。 两次单击也必须在指定时间内发生。若要设置双击矩形的高度，请使用SPI_SETDOUBLECLKHEIGHT调用 [SystemParametersInfo](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-systemparametersinfoa) 。  
        SM_CYDOUBLECLK = 37,
        // 鼠标指针在拖动操作开始之前可以移动的鼠标向下点上方和下方的像素数。 这允许用户轻松单击并释放鼠标按钮，而不会无意中启动拖动操作。 如果此值为负值，则从鼠标向下点上方减去该值，并将其添加到其下方。  
        SM_CYDRAG = 69,
        // 三维边框的高度（以像素为单位）。 这是SM_CYBORDER的三维对应项。  
        SM_CYEDGE = 46,
        // 窗口周围具有描述文字但不是相当大的（以像素为单位）的框架的粗细。 SM_CXFIXEDFRAME是水平边框的高度，SM_CYFIXEDFRAME是垂直边框的宽度。此值与 SM_CYDLGFRAME 相同。  
        SM_CYFIXEDFRAME = 8,
        // [DrawFocusRect](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-drawfocusrect) 绘制的焦点矩形的上边缘和下边缘的高度。 此值以像素为单位。**Windows 2000：** 不支持此值。  
        SM_CYFOCUSBORDER = 84,
        // 此值与 SM_CYSIZEFRAME 相同。                                  
        SM_CYFRAME = 33,
        // 主显示器上全屏窗口的工作区高度（以像素为单位）。 若要获取系统任务栏或应用程序桌面工具栏未遮挡的屏幕部分的坐标，请使用 SPI_GETWORKAREA 值调用 [SystemParametersInfo](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-systemparametersinfoa) 函数。  
        SM_CYFULLSCREEN = 17,
        // 水平滚动条的高度（以像素为单位）。                            
        SM_CYHSCROLL = 3,
        // 图标的系统高度（以像素为单位）。 [LoadIcon](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-loadicona) 函数只能加载具有SM_CXICON和SM_CYICON指定尺寸的图标。 有关详细信息 [，请参阅图标大小](https://learn.microsoft.com/zh-cn/windows/win32/menurc/about-icons#icon-sizes) 。  
        SM_CYICON = 12,
        // 大图标视图中项的网格单元格的高度（以像素为单位）。 每个项都适合在排列时按SM_CYICONSPACING SM_CXICONSPACING大小的矩形。 此值始终大于或等于 SM_CYICON。  
        SM_CYICONSPACING = 39,
        // 对于系统的双字节字符集版本，这是屏幕底部的汉字窗口的高度（以像素为单位）。  
        SM_CYKANJIWINDOW = 18,
        // 主显示监视器上最大化的顶级窗口的默认高度（以像素为单位）。    
        SM_CYMAXIMIZED = 62,
        // 具有描述文字和大小调整边框的窗口的默认最大高度（以像素为单位）。 此指标是指整个桌面。 用户无法将窗口框架拖动到大于这些尺寸的大小。 窗口可以通过处理 [WM_GETMINMAXINFO](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-getminmaxinfo) 消息来替代此值。  
        SM_CYMAXTRACK = 60,
        // 单行菜单栏的高度（以像素为单位）。                            
        SM_CYMENU = 15,
        // 默认菜单的高度检查标记位图（以像素为单位）。                  
        SM_CYMENUCHECK = 72,
        // 菜单栏按钮（例如在多个文档界面中使用的子窗口关闭按钮）的高度（以像素为单位）。  
        SM_CYMENUSIZE = 55,
        // 窗口的最小高度（以像素为单位）。                              
        SM_CYMIN = 29,
        // 最小化窗口的高度（以像素为单位）。                            
        SM_CYMINIMIZED = 58,
        // 最小化窗口的网格单元格的高度（以像素为单位）。 每个最小化窗口在排列时适合此大小的矩形。 此值始终大于或等于 SM_CYMINIMIZED。  
        SM_CYMINSPACING = 48,
        // 窗口的最小跟踪高度（以像素为单位）。 用户无法将窗口框架拖动到小于这些尺寸的大小。 窗口可以通过处理 [WM_GETMINMAXINFO](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-getminmaxinfo) 消息来替代此值。  
        SM_CYMINTRACK = 35,
        // 主显示器的屏幕高度（以像素为单位）。 这是通过调用 [GetDeviceCaps](https://learn.microsoft.com/zh-cn/windows/desktop/api/wingdi/nf-wingdi-getdevicecaps) 获取的相同值，如下所示： `GetDeviceCaps( hdcPrimaryMonitor, VERTRES)`。  
        SM_CYSCREEN = 1,
        // 窗口中按钮的高度描述文字或标题栏（以像素为单位）。            
        SM_CYSIZE = 31,
        // 可调整大小的窗口周边的大小边框的粗细（以像素为单位）。 SM_CXSIZEFRAME是水平边框的宽度，SM_CYSIZEFRAME是垂直边框的高度。此值与 SM_CYFRAME 相同。  
        SM_CYSIZEFRAME = 33,
        // 小描述文字的高度（以像素为单位）。                            
        SM_CYSMCAPTION = 51,
        // 图标的系统小高度（以像素为单位）。 小图标通常显示在窗口标题和小图标视图中。 有关详细信息 [，请参阅图标大小](https://learn.microsoft.com/zh-cn/windows/win32/menurc/about-icons#icon-sizes) 。  
        SM_CYSMICON = 50,
        // 小描述文字按钮的高度（以像素为单位）。                        
        SM_CYSMSIZE = 53,
        // 虚拟屏幕的高度（以像素为单位）。 虚拟屏幕是所有显示监视器的边框。 SM_YVIRTUALSCREEN指标是虚拟屏幕顶部的坐标。  
        SM_CYVIRTUALSCREEN = 79,
        // 垂直滚动条上箭头位图的高度（以像素为单位）。                  
        SM_CYVSCROLL = 20,
        // 垂直滚动条中拇指框的高度（以像素为单位）。                    
        SM_CYVTHUMB = 9,
        // 如果User32.dll支持 DBCS，则为非零值;否则为 0。                
        SM_DBCSENABLED = 42,
        // 如果安装了User.exe的调试版本，则为非零;否则为 0。             
        SM_DEBUG = 22,
        // 如果当前操作系统是 Windows 7 或 Windows Server 2008 R2 并且平板电脑输入服务已启动，则为非零;否则为 0。 返回值是一个位掩码，用于指定设备支持的数字化器输入的类型。 有关详细信息，请参阅“备注”。**Windows Server 2008、Windows Vista 和 Windows XP/2000：** 不支持此值。  
        SM_DIGITIZER = 94,
        // 如果启用了输入法管理器/输入法编辑器功能，则为非零值;否则为 0。SM_IMMENABLED指示系统是否已准备好在 Unicode 应用程序上使用基于 Unicode 的 IME。 若要确保依赖于语言的 IME 正常工作，检查 SM_DBCSENABLED和系统 ANSI 代码页。 否则，ANSI 到 Unicode 的转换可能无法正确执行，或者某些组件（如字体或注册表设置）可能不存在。  
        SM_IMMENABLED = 82,
        // 如果系统中存在数字化器，则为非零值;否则为 0。SM_MAXIMUMTOUCHES返回系统中每个数字化器支持的最大接触数的聚合最大值。 如果系统只有单点触控数字化器，则返回值为 1。 如果系统具有多点触控数字化器，则返回值是硬件可以提供的同时触点数。**Windows Server 2008、Windows Vista 和 Windows XP/2000：** 不支持此值。  
        SM_MAXIMUMTOUCHES = 95,
        // 如果当前操作系统是 Windows XP，则为非零，Media Center Edition 为 0（如果不是）。  
        SM_MEDIACENTER = 87,
        // 如果下拉菜单与相应的菜单栏项右对齐，则为非零值;如果菜单左对齐，则为 0。  
        SM_MENUDROPALIGNMENT = 40,
        // 如果为希伯来语和阿拉伯语启用系统，则为非零值;否则为 0。       
        SM_MIDEASTENABLED = 74,
        // 如果安装了鼠标，则为非零值;否则为 0。 此值很少为零，因为支持虚拟鼠标，并且某些系统检测到端口的存在，而不是鼠标的存在。  
        SM_MOUSEPRESENT = 19,
        // 如果安装了水平滚轮的鼠标，则为非零值;否则为 0。              | 
        SM_MOUSEHORIZONTALWHEELPRESENT = 91,
        // 如果安装了具有垂直滚轮的鼠标，则为非零值;否则为 0。           
        SM_MOUSEWHEELPRESENT = 75,
        // 如果存在网络，则设置最小有效位;否则，将清除它。 其他位保留供将来使用。  
        SM_NETWORK = 63,
        // 如果安装了 Microsoft Windows for Pen 计算扩展，则为非零值;否则为零。  
        SM_PENWINDOWS = 41,
        // 此系统指标在终端服务环境中用于确定是否远程控制当前终端服务器会话。 如果远程控制当前会话，则其值为非零值;否则为 0。可以使用终端服务管理工具（如终端服务管理器 (tsadmin.msc) 和shadow.exe）来控制远程会话。 远程控制会话时，另一个用户可以查看该会话的内容，并可能与之交互。  
        SM_REMOTECONTROL = 0x2001,
        // 此系统指标用于终端服务环境。 如果调用进程与终端服务客户端会话相关联，则返回值为非零值。 如果调用进程与终端服务控制台会话相关联，则返回值为 0。 **Windows Server 2003 和 Windows XP：** 控制台会话不一定是物理控制台。 有关详细信息，请参阅 [WTSGetActiveConsoleSessionId](https://learn.microsoft.com/zh-cn/windows/desktop/api/winbase/nf-winbase-wtsgetactiveconsolesessionid)。  
        SM_REMOTESESSION = 0x1000,
        // 如果所有显示监视器具有相同的颜色格式，则为非零值，否则为 0。 两个显示器可以具有相同的位深度，但颜色格式不同。 例如，红色、绿色和蓝色像素可以使用不同位数进行编码，或者这些位可以位于像素颜色值的不同位置。  
        SM_SAMEDISPLAYFORMAT = 81,
        // 应忽略此系统指标;它始终返回 0。                               
        SM_SECURE = 44,
        // 系统为 Windows Server 2003 R2 时的内部版本号;否则为 0。       
        SM_SERVERR2 = 89,
        // 如果用户要求应用程序在仅以声音形式显示信息的情况下直观显示信息，则为非零值;否则为 0。  
        SM_SHOWSOUNDS = 70,
        // 如果当前会话正在关闭，则为非零;否则为 0。**Windows 2000：** 不支持此值。  
        SM_SHUTTINGDOWN = 0x2000,
        // 如果计算机具有低端 (慢) 处理器，则为非零值;否则为 0。         
        SM_SLOWMACHINE = 73,
        // 如果当前操作系统为 Windows 7 简易版 Edition、Windows Vista 入门版 或 Windows XP Starter Edition，则为非零;否则为 0。  
        SM_STARTER = 88,
        // 如果交换了鼠标左键和右键的含义，则为非零值;否则为 0。         
        SM_SWAPBUTTON = 23,
        // 反映停靠模式的状态，0 表示未停靠模式，否则为非零。 当此系统指标发生更改时，系统会通过 LPARAM 中带有“SystemDockMode” [的WM_SETTINGCHANGE](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-settingchange) 发送广播消息。  
        SM_SYSTEMDOCKED = 0x2004,
        // 如果当前操作系统是 Windows XP 平板电脑版本，或者当前操作系统是 Windows Vista 或 Windows 7 并且平板电脑输入服务已启动，则为非零值;否则为 0。 SM_DIGITIZER设置指示运行 Windows 7 或 Windows Server 2008 R2 的设备支持的数字化器输入类型。 有关详细信息，请参阅“备注”。  
        SM_TABLETPC = 86,
        // 虚拟屏幕左侧的坐标。 虚拟屏幕是所有显示监视器的边框。 SM_CXVIRTUALSCREEN指标是虚拟屏幕的宽度。  
        SM_XVIRTUALSCREEN = 76,
        // 虚拟屏幕顶部的坐标。 虚拟屏幕是所有显示监视器的边框。 SM_CYVIRTUALSCREEN指标是虚拟屏幕的高度。  
        SM_YVIRTUALSCREEN = 77,
        // 从屏幕左下角开始。 默认位置。

        // --------------------------------

        // 从屏幕左下角开始。 默认位置。 [扩展值]
        ARW_BOTTOMLEFT = 0x000,
        // 从屏幕右下角开始。 等效于 ARW_STARTRIGHT。 [扩展值]
        ARW_BOTTOMRIGHT = 0x0001,
        // 从屏幕左上角开始。 等效于 ARW_STARTTOP。 [扩展值]
        ARW_TOPLEFT = 0x0002,
        // 从屏幕右上角开始。 等效于 ARW_STARTTOP |SRW_STARTRIGHT。 [扩展值]
        ARW_TOPRIGHT = 0x0003,

        // --------------------------------

        // 垂直排列，从上到下 [扩展值]
        ARW_DOWN = 0x0004,
        // 通过将最小化的窗口移出屏幕的可见区域来隐藏这些窗口 [扩展值]
        ARW_HIDE = 0x0008,
        // 从左到右水平排列。 [扩展值]
        ARW_LEFT = 0x0000,
        // 	从右到左水平排列 [扩展值]
        ARW_RIGHT = 0x0000,
        // 垂直排列，从下到上。 [扩展值]
        ARW_UP = 0x0004,

        // --------------------------------
        // 该设备具有集成的触摸数字化器 [扩展值]
        NID_INTEGRATED_TOUCH = 0x01,
        // 设备具有外部触摸数字化器 [扩展值]
        NID_EXTERNAL_TOUCH = 0x02,
        // 该设备具有集成的笔数字化器 [扩展值]
        NID_INTEGRATED_PEN = 0x04,
        // 设备具有外部笔数字化器 [扩展值]
        NID_EXTERNAL_PEN = 0x08,
        // 设备支持多个数字化器输入源 [扩展值]
        NID_MULTI_INPUT = 0x40,
        // 设备已准备好接收数字化器输入。 [扩展值]
        NID_READY = 0x80
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

    // 返回的数据无效
    export interface MouseNotEventData {
        // 无效id
        "id": null,
        // 无效时间
        "time": null
    };

    export interface MouseMoveEventData {
        // 鼠标 hook 的唯一id
        "id": number,
        // 事件发生的时间
        "time": number,
        // 按钮类型
        "button": MouseKey.WM_MOUSEMOVE,
        // (left) 从屏幕左边到所在位置得像素数
        "x": number,
        //  (top) 从屏幕顶部边到所在位置得像素数
        "y": number
    };

    export interface MouseMouseEventData {
        // 鼠标 hook 的唯一id
        "id": number,
        // 事件发生的时间
        "time": number,
        // 按钮类型
        "button": MouseKey.WM_LBUTTONDOWN | MouseKey.WM_LBUTTONUP | MouseKey.WM_MBUTTONDOWN | MouseKey.WM_MBUTTONUP | MouseKey.WM_MOUSEWHEEL | MouseKey.WM_RBUTTONDOWN | MouseKey.WM_RBUTTONUP,
        // 按钮是否是按下状态/ 滚轮是否向上
        "buttonDown": boolean,
        // 滚轮向量 如果是正值为向上 负值为向下
        "wheelDelta": number | null,
        // 按钮名称
        "name": "left-mouse-button" | "right-mouse-button" | "middle-mouse-button" | null
    };

    export type MouseEventDataAll = MouseMouseEventData | MouseMoveEventData | MouseNotEventData;
    export type MouseEventDataOK = MouseMouseEventData | MouseMoveEventData;

    // 传回的位置信息
    export interface Rect {
        /**
         * (x)从屏幕左边到所在位置得像素数
         */
        right?: number;
        /**
         * 底部到当前位置
         */
        bottom: number;
        /**
         * 左边到当前位置
         */
        left: number;
        /**
         * 宽度
         */
        width: number;
        /**
         * 高度
         */
        height: number;
        /**
         * (left) 从屏幕左边到所在位置得像素数
         */
        x: number;
        /**
         * (top) 从屏幕顶部边到所在位置得像素数
         */
        y: number;

        /**
         * (y) 从屏幕顶部边到所在位置得像素数
         */
        top: number;
    }
    export type VariableList = { [key: string]: string };

    // 托盘图标信息
    export interface TRAY_ICON {
        // 可执行文件路径
        path: string;
        // 停留时显示的文本
        info: string;
        // 句柄
        handle: number;
    }

    // 屏幕宽度高度信息
    export interface DeviceCaps { width: number; height: number; }

    // 鼠标历史坐标位置信息
    export interface MovePoint {
        // (left) 从屏幕左边到所在位置得像素数
        x: number;
        //  (top) 从屏幕顶部边到所在位置得像素数
        y: number;
        /**点击时候的时间 */
        time: number;
        /**附加信息 */
        dwExtraInfo: number;
    }

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

    //枚举所有窗口返回的信息 
    export type GET_ALL_WINDOWS_INFO = {
        /**窗口类名**/
        className: string;
        /**句柄**/
        handle: number;
        /**窗口位置信息**/
        rect: {
            bottom: number;
            height: number;
            left: number;
            right: number;
            top: number;
            width: number;
            x: number;
            y: number;
        };
        /**窗口外观类**/
        style: number;
        /**窗口标题**/
        title: string;
    }

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

    // 自定义鼠标事件
    export type mouse_event =
    /**不支持的属性 请使用 setCursorPos 方法设置位置*/ 32768 |
    /**左键按下 */ 2 |
    /**左边的按钮是向上的 */ 4 |
    /**中间的按钮是向下的 */ 32 |
    /**中间的按钮是向上的 */ 64 |
    /**鼠标移动和按钮点击 */ 1 |
     /**鼠标右键按下 */ 8 |
      /**鼠标右键弹起 */ 16 |
       /**滚轮按钮被旋转 */ 2048 |
        /**按下了 X 按钮 */ 128 |
         /**X 按钮被释放 */ 256 |
          /**滚轮按钮倾斜*/ 4096 |
           /**不支持的属性 请使用 setCursorPos 方法设置位置*/ "MOUSEEVENTF_ABSOLUTE" |
            /**左键按下 */ "MOUSEEVENTF_LEFTDOWN" |
             /**左边的按钮是向上的 */ "MOUSEEVENTF_LEFTUP" |
              /**中间的按钮是向下的 */ "MOUSEEVENTF_MIDDLEDOWN" |
               /**中间的按钮是向上的 */ "MOUSEEVENTF_MIDDLEUP" |
                /**鼠标移动和按钮点击 */ "MOUSEEVENTF_MOVE" |
                 /**鼠标右键按下 */ "MOUSEEVENTF_RIGHTDOWN" |
                  /**鼠标右键弹起 */ "MOUSEEVENTF_RIGHTUP" |
                   /**滚轮按钮被旋转 */ "MOUSEEVENTF_WHEEL" |
                    /**按下了 X 按钮 */ "MOUSEEVENTF_XDOWN" |
                     /**X 按钮被释放 */ "MOUSEEVENTF_XUP" |
                      /**滚轮按钮倾斜*/ "MOUSEEVENTF_HWHEEL";

    // 消息框显示方式
    export type MB_UINT =  /**消息框包含三个按钮：终止、重试和忽略。 */ "MB_ABORTRETRYIGNORE" | /**消息框包含三个按钮：取消、重试、继续。使用此消息框类型而不是 MB_ABORTRETRYIGNORE。 */ "MB_CANCELTRYCONTINUE" | /**向消息框 添加帮助按钮。当用户单击帮助按钮或按 F1 时|系统会向所有者 发送WM_HELP消息。 */ "MB_HELP" | /**消息框包含一个按钮：确定。这是默认设置。 */ "MB_OK" | /**消息框包含两个按钮：确定和取消。 */ "MB_YESNOCANCEL" | /**消息框包含两个按钮：是和否。 */ "MB_YESNO" | /**消息框包含两个按钮：OK和Cancel。 */ "MB_OKCANCEL" | /**消息框包含两个按钮：OK和Cancel。 */ "MB_RETRYCANCEL" | /**消息框包含三个按钮：Yes、No和Cancel。 一个停止标志图标出现在消息框中。*/ "MB_ICONERROR" | /**一个停止标志图标出现在消息框中。 */ "MB_ICONSTOP" | /**问号图标出现在消息框中。不再推荐使用问号消息图标|因为它不能清楚地表示特定类型的消息|并且作为问题的消息措辞可能适用于任何消息类型。此外|用户可能会将消息符号问号与帮助信息混淆。因此|请勿在消息框中使用此问号消息符号。系统继续支持它的包含只是为了向后兼容。 */ "MB_ICONQUESTION" | /**一个由圆圈中的小写字母i组成的图标出现在消息框中。 */ "MB_ICONASTERISK" | "MB_ICONINFORMATION" | /**消息框中会出现一个感叹号图标。 */ "MB_ICONEXCLAMATION" | /** 消息框中会出现一个感叹号图标。 */ "MB_ICONWARNING" | /* 消息框成为前台窗口 **/ "MB_TOPMOST" | "MB_SETFOREGROUND" | "MB_RTLREADING" | "MB_RIGHT" | "MB_DEFAULT_DESKTOP_ONLY" | "MB_TASKMODAL" | "MB_SYSTEMMODAL" | "MB_APPLMODAL" | "MB_DEFBUTTON4" | "MB_DEFBUTTON3" | "MB_DEFBUTTON2" | "MB_ICONHAND" | "MB_DEFBUTTON1";

    // HID设备信息
    export type HID_USB_INFO = {
        /**类型**/
        type: "hid" | "keyboard" | "mouse";
        /**设备名称**/
        name: string;
        /**供应商 ID */
        dwVendorId: number;
        /**产品 ID */
        dwProductId: number;
        /**版本号 */
        dwVersionNumber: number;
        /**开发人员提供有关控制测量内容的信息 */
        usUsage: number;
        /**设备供应商对其设备的控制或者设备控制组的特定用途建议 */
        usUsagePage: number;
    };

    export type PROCESSENTRY_V2 = HMC_V1.PROCESSENTRY & { name: string, pid: number, ppid: number };

    export interface PSYSTEM_PROCESS_INFORMATION {
        // 下一个结构体实例的偏移量，用于遍历多个结构体。
        NextEntryOffset: number;
        // 进程线程数量。
        NumberOfThreads: number;
        // 进程的镜像名称
        ImageName: string;
        // 进程的基本优先级。
        BasePriority: number;
        // 进程的唯一标识符。(pid)
        UniqueProcessId: number;
        // 进程的句柄数。
        HandleCount: number;
        // 进程所在的会话 ID。
        SessionId: number;
        // 进程的峰值虚拟内存大小。
        PeakVirtualSize: number;
        // 进程的虚拟内存大小。
        VirtualSize: number;
        // 进程的峰值工作集大小。
        PeakWorkingSetSize: number;
        // 进程的实际工作集大小。
        WorkingSetSize: number;
        // 分配给进程的分页池配额使用量。
        QuotaPagedPoolUsage: number;
        // 分配给进程的非分页池配额使用量。非分页池是内核提供的内存池，用于驻留在物理内存中，并且不会被换出到磁盘页面文件。该字段表示进程当前使用的非分页池内存大小。
        QuotaNonPagedPoolUsage: number;
        // 进程的页面文件使用量。页面文件是用于交换进程数据的虚拟内存扩展，当物理内存不足时，部分数据会被交换到页面文件中以释放内存。
        PagefileUsage: number;
        // 进程的峰值页面文件使用量。这是进程在其生命周期内达到的最高页面文件使用量。
        PeakPagefileUsage: number;
        // 进程的私有页计数。私有页是进程专用的虚拟内存页面，不被其他进程共享。
        PrivatePageCount: number;
    }

    export type Native = {
        /**版本号 */
        version: string;
        /**功能介绍 */
        desc: string;
        /**当前二进制适用系统平台 */
        platform: string;
        /**
         * 方法用于显示带有一条指定消息和一个 确认 按钮的警告框。
         * @param lpText 消息内容
         * @param lpCaption 标题
         */
        alert(lpText: string, lpCaption: string): boolean;
        /**
         * 方法用于显示带有一条指定消息和一个 确认 按钮的错误框 附带有❗ 感叹号。
         * @param lpText 消息内容
         * @param lpCaption 标题
         */
        MessageError(lpText: string, lpCaption: string): void;
        /**
         * 用默认浏览器打开这条url
         * @param URL
         */
        openURL(URL: string): boolean;
        /**
         * 方法用于显示带有一条指定消息和一个 确认 按钮的和❌（X）的消息框。
         * @param lpText 消息内容
         * @param lpCaption 标题
         */
        MessageStop(lpText: string, lpCaption: string): void;
        /**
         * 方法用于显示带有一条指定消息和一个 确认 取消 按钮的消息框。
         * @param lpText 消息内容
         * @param lpCaption 标题
         */
        confirm(lpText: string, lpCaption: string): boolean;
        /**
         * 用默认应用打开该 （文件/文件夹）
         * @param Path 文件路径
         */
        openPath(Path: string): boolean;
        /**
         * 在资源管理器中显示并选中该文件
         * @param Path 文件路径
         */
        openExternal(Path: string): boolean;
        /** 关闭该句柄窗口(可关闭托盘)(发送关闭消息)**/
        closedHandle: (Handle: number) => undefined;
        /** 设置窗口位置大小**/
        setWindowMode: (Handle: number, x: number | null | 0, y: number | null | 0, width: number | null | 0, height: number | null | 0) => boolean;
        /** 获取窗口位置大小
         *  - 高|宽|坐标大于一万以上都是不可见的
         * **/
        getWindowRect: (Handle: number) => Rect;
        /** 获取屏幕大小**/
        getDeviceCaps: () => DeviceCaps;
        /**
         * 判断句柄是否有效
         * @param Handle
         * @returns
         */
        isHandle: (Handle: number) => boolean;
        /** 获取鼠标所在窗口的句柄**/
        getPointWindow: () => number | null;
        /** 获取鼠标所在窗口的进程名**/
        getPointWindowName: () => string;
        /** 获取鼠标所在窗口的进程id**/
        getPointWindowProcessId: () => number;
        /**阻止键盘和鼠标输入事件到达应用程序。 */
        SetBlockInput: (Block: boolean) => boolean;
        /** 获取鼠标所在窗口的父窗口**/
        getPointWindowMain: () => number;
        /** 获取鼠标所在位置**/
        getMetrics: () => MousePosn
        /** 获取活动窗口的进程id**/
        getForegroundWindowProcessID: () => ProcessID | null;
        /** 获取句柄对应的进程id**/
        getHandleProcessID: (Handle: number) => ProcessID | null;
        /** 获取快捷方式的信息**/
        getShortcutLink: (LnkPath: string) => SHORTCUT_LINK;
        setShortcutLink(LnkPath: string, FilePath: string, work_dir: string, desc: string, args: string, iShowCmd: number, icon: string, iconIndex: number): boolean;
        setShortcutLink(LnkPath: string, FilePath: string, work_dir?: string, desc?: string, args?: string, iShowCmd?: number): boolean;
        setShortcutLink(LnkPath: string, FilePath: string): boolean;
        setShortcutLink(LnkPath: string, Shortcut: SHORTCUT_LINK): boolean;
        /**
         * 创建快捷方式
         * @param LnkPath 快捷方式位置
         * @param FilePath 关联的文件
         * @param work_dir 工作目录
         * @param desc 简介
         * @param args 启动命令
         * @param iShowCmd 显示方式
         * @param icon 使用的图标如dll,exe,icon
         * @param iconIndex 图标索引
         */
        setShortcutLink(LnkPath: unknown, FilePath: unknown, work_dir?: unknown, desc?: unknown, args?: unknown, iShowCmd?: unknown, icon?: unknown, iconIndex?: unknown): boolean;
        /**
         * 创建文件软链接
         * @param LinkPath 创建的位置
         * @param sourcePath 原文件链接
         */
        createSymlink(LinkPath: string, sourcePath: string): boolean;
        /**
         * 创建文件夹软链接
         * @param LinkPath 创建的位置
         * @param sourcePath 原文件链接
         */
        createDirSymlink(LinkPath: string, sourcePath: string): boolean;
        /**
         * 创建硬链接
         * @param LinkPath 创建的位置
         * @param sourcePath 原文件链接
         */
        createHardLink(LinkPath: string, sourcePath: string): boolean;
        /** 设置窗口不透明度 0-255**/
        setHandleTransparent(Handle: number, opacity: HandleTransparent): void;
        /**
         * 获取托盘图标列表
         * 1.4.6 起返回json文本
         */
        getTrayList(): TRAY_ICON[] | string;
        /** 判断当前是否为64位系统**/
        isSystemX64(): boolean;
        /** 同 C++/C 的system */
        system(str: string): number;
        /**系统启动到现在的时间(毫秒) */
        systemStartTime(): number;
        /** 获取进程对应的主进程/线程的窗口句柄**/
        getProcessHandle(ProcessID: ProcessID): number | null;
        /** 获取此句柄的标题**/
        lookHandleGetTitle(Handle: number): string | null;

        /** 设置此句柄的标题**/
        lookHandleSetTitle(Handle: number, title: string): boolean;
        /**
         * 通过句柄设置窗口显示状态  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
         * @param Handle 窗口句柄
         * @param nCmdShow 操作内容
         *  - "SW_HIDE" ： 0 隐藏窗口并激活另一个窗口。
         *  - "SW_SHOWNORMAL" ： 1 激活并显示一个窗口。如果窗口被最小化或最大化|系统会将其恢复到原来的大小和位置。应用程序应在第一次显示窗口时指定此标志
         *  - "SW_SHOWMINIMIZED" ：2 激活窗口并将其显示为最小化窗口
         *  - "SW_SHOWMAXIMIZED" | "SW_MAXIMIZE" ： 3 激活窗口并将其显示为最大化窗口
         *  - "SW_SHOWNOACTIVATE" ： 4 以最近的大小和位置显示窗口。这个值类似于SW_SHOWNORMAL|除了窗口没有被激活
         *  - "SW_SHOW" ：5  激活窗口并以其当前大小和位置显示它
         *  - "SW_MINIMIZE" ：6 最小化指定窗口并激活 Z 顺序中的下一个顶级窗口
         *  - "SW_SHOWMINNOACTIVE" ： 7 将窗口显示为最小化窗口。这个值类似于SW_SHOWMINIMIZED|除了窗口没有被激活
         *  - "SW_SHOWNA" ： 8 以当前大小和位置显示窗口。这个值类似于SW_SHOW|除了窗口没有被激活
         *  - "SW_RESTORE" ： 9 激活并显示窗口。如果窗口被最小化或最大化|系统会将其恢复到原来的大小和位置。应用程序在恢复最小化窗口时应指定此标志
         *  - "SW_SHOWDEFAULT" ： 10 据启动应用程序的程序传递给CreateProcess函数的STARTUPINFO结构中指定的SW_值设置显示状态。
         *  - "SW_FORCEMINIMIZE" ： 11 最小化一个窗口|即使拥有该窗口的线程没有响应。只有在最小化来自不同线程的窗口时才应使用此标志
         * @returns
         */
        lookHandleShowWindow: (Handle: number, SetShowType: 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11) => boolean;
        /** 判断此句柄是否是正在活动中的窗口**/
        isHandleWindowVisible: (Handle: number) => boolean;
        /** 关闭此句柄对应的窗口**/
        lookHandleCloseWindow: (Handle: number) => boolean;
        /**
         * 消息窗口(调用 win-api)
         * @param lpText 消息内容
         * @param lpCaption 标题
         * @param UINT_String 显示窗口类型 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
         * @returns int
         * - 3 中止按钮被选中
         * - 2 取消
         * - 11 继续
         * - 5 识别
         * - 7 否
         * - 1 确定
         * - 6 是
         * - 10 重试
         * - 4 重试
         */
        messageBox(lpText: string, lpCaption: string, UINT_String?: MB_UINT): 3 | 2 | 11 | 5 | 7 | 1 | 4 | 10 | 6;
        /** 设置系统右键菜单 **/
        getSystemMenu: (Handle: number, boolean: boolean) => void;
        /** 关闭显示器**/
        shutMonitors: () => void;
        /** 恢复显示器**/
        showMonitors: () => void;
        /** 获取活动窗口句柄**/
        getForegroundWindow: () => number;
        /**
        * 电源控制
        * - 1001 关机
        * - 1002 重启
        * - 1003 注销
        * - 1005 锁定
        */
        powerControl: (Set: 1001 | 1002 | 1003 | 1005) => void;
        /**
         * 打开程序
         * @param AppPath 程序路径
         * @param Command 启动命令
         * @param cwd 工作文件夹
         * @param hide 是否隐藏
         * @param UAC 是否以管理员方式启动
         */
        openApp(AppPath: string, Command: string, cwd: string, hide: boolean, UAC: boolean): boolean;
        /** 是否拥有管理员权限**/
        isAdmin: () => boolean;
        /** 同步阻塞(进程)**/
        sleep: (awaitTime: number) => void;
        /** 系统空闲时间**/
        getSystemIdleTime: () => number;
        /** 结束该pid进程**/
        killProcess: (ProcessID: ProcessID) => boolean;
        /** 清空剪贴版**/
        clearClipboard(): boolean;
        /**
         * 设置剪贴板文本 或html
         * @param EditText 文本或者html
         * @param is_html 当此参数为true 文本将被写入为html
         * @param html_url 如果是html可以传入一个来源的链接
         * @returns 
         */
        setClipboardText: (EditText: string, is_html?: boolean, html_url?: string) => void;
        /** 获取剪贴板文本**/
        getClipboardText: () => string;

        /** 获取鼠标之前64个位置**/
        getMouseMovePoints: () => string;
        /**
         * 获取所有窗口的句柄
         */
        getAllWindowsHandle(isWindows?: boolean): number[];
        /**
         * 获取所有窗口的信息
         * @deprecated 已被移除 已使用js获取所有句柄模拟
         **/
        getAllWindows: () => GET_ALL_WINDOWS_INFO[];
        /**获取四大按钮是否按下**/
        getBasicKeys: () => BASIC_KEYS;
        /**获取该句柄下的父窗口**/
        getMainWindow: (Handle: number) => number | null;
        /**设置窗口顶设 */
        setWindowTop(HWND: number): boolean;
        /**判断窗口是否被顶设 */
        hasWindowTop(HWND: number): boolean;
        /**窗口抖动 */
        windowJitter(Handle: number): void;
        /** 刷新该窗口**/
        updateWindow(HWND: number): boolean;
        /**设置窗口焦点**/
        setWindowFocus(HWND: number): boolean;
        /** 设置窗口是否支持响应事件(鼠标键盘点击)**/
        setWindowEnabled(HWND: number, Enabled: boolean): boolean;
        /** 判断窗口是否禁用响应事件(鼠标键盘点击)**/
        isEnabled(HWND: number): boolean;
        /** 右键点击**/
        rightClick(ms?: number): void;
        /** 左键点击**/
        leftClick(ms?: number): void;
        /**设置鼠标位置**/
        setCursorPos(x: number, y: number): boolean;
        /**自定义鼠标事件 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mouse_event **/
        mouse(mouse_event: mouse_event, ms?: number): void;
        /**判断该按键是否被按下  https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getkeystate **/
        hasKeyActivate(KeysEvent: number): boolean;
        /**设置该窗口图标在状态栏可见性 (注意：XP 下激活窗口了会失效(但是有没有一种可能 xp运行不了node和electron))*/
        SetWindowInTaskbarVisible(Handle: number, Visible: boolean): boolean;
        /**禁用/启用系统键盘鼠标钩子
          * @param HOOK 是否启用系统键盘鼠标钩子
          !注意该功能很危险 主要用于自动化防止误操作 用户锁屏  禁止用于非法用途
          *手动解锁方式 Ctrl+Alt+Del   => esc
          !请注意 你需要确保你的解锁代码  运行没有任何错误或者有定时解锁
          否则有可能导致用户无法正常使用
          **/
        SetSystemHOOK(HOOK: boolean): boolean;
        /**获取所有HidUsb设备（仅限HID设备）**/
        getHidUsbList(): HID_USB_INFO[];
        /**
        * 向剪贴板写入文件路径
        * @param FilePaths 路径列表
        */
        setClipboardFilePaths(FilePaths: string | string[]): void
        /**
         * 获取剪贴板中的文件路径
         */
        getClipboardFilePaths(): string
        /**
         * 获取所有usb驱动器(不包含HUD)
         */
        getUsbDevsInfo(): string[]
        /**枚举子窗口 */
        enumChildWindows(Handle: number): number[]
        /**
         * 将文件/文件夹  移除到系统回收站中
         * @param Path 处理的路径(\n结尾)
         * @param Recycle 是否保留撤销权(回收站)
         * @param isShow 是否显示确认窗口
         * @returns 返回操作状态 请参考：
         * @link https://learn.microsoft.com/zh-CN/windows/win32/api/shellapi/nf-shellapi-shfileoperationa
         * @default 默认配置
         * * Recycle true
         * * isShow false
         */
        deleteFile(Path: string, Recycle?: boolean, isShow?: boolean): number
        /**
         * 获取当前剪贴板内容的id(如果被重新写入了该id会变动)
         */
        getClipboardInfo(): ClipboardInfo;
        /**
         * 枚举剪贴板中的内容格式
         */
        enumClipboardFormats(): { type_name: string, type: number }[];
        // 获取剪贴板中的html
        getClipboardHTML(): ClipboardHTMLInfo | null;
        /**
         * 获取所有HID设备的id
         */
        getHidUsbIdList(): string[];
        /**
         * 获取所有屏幕
         */
        getDeviceCapsAll(): cRECT[];
        /**
         * 判断句柄的窗口是否在所有窗口的范围中(无论他是否被其他窗口挡住)
         * @param Handle 
         */
        isInMonitorWindow(Handle: number): boolean;
        /**
         * 判断句柄的窗口是否在鼠标所在的窗口
         * @param Handle 
         */
        isMouseMonitorWindow(Handle: number): boolean;
        /**
         * 获取鼠标所在的屏幕信息
         */
        getCurrentMonitorRect(): cRECT;
        /**
         * 当前电脑存在几个屏幕
         */
        getSystemMetricsLen(): number;
        /**
         * 获取窗口类关联代码
         */
        getWindowStyle(Handle: number): number;
        /**
         * 检索指定窗口所属的类的名称
         * @param Handle 
         */
        getWindowClassName(Handle: number): string;
        /**
         * 移除鼠标挂钩
         */
        // unHookMouse(): void;
        /**
         * 移除键盘挂钩
         */
        unKeyboardHook(): void;
        /**
         * 启动键盘动作挂钩
         */
        installKeyboardHook(): void;
        /**
         * 获取已经记录了的低级鼠标动作数据 出于性能优化使用了(文本数组)
         */
        getKeyboardNextSession(): `${number}|${0 | 1}`[] | undefined
        /**
         * 键盘挂钩是否已经启用
         */
        isStartKeyboardHook(): boolean;
        /**
         * 格式化 驱动器路径  ('\\Device\\HarddiskVolume2' => "D:\\")
         * @param VolumePath 
         */
        formatVolumePath(VolumePath: string): string;
        /**
         * 获取当前文件系统的驱动器名称及路径
         */
        getVolumeList(): Volume[];
        /**
         * 内联 轮询枚举的进程句柄
         * @param enumID 枚举id 由enumProcessHandle 提供
         */
        enumProcessHandlePolling(enumID: number): void | ProcessHandle[];
        /**
         * 内联 枚举进程的所有句柄 并返回一个枚举id
         * @param ProcessID 
         */
        enumProcessHandle(ProcessID: number): number;
        /**
         * 查询进程加载的模块
         * @param ProcessID 
         */
        getModulePathList(ProcessID: number): string[];
        /**
         * 内联 清空句柄存储  不需要暴露
         */
        clearEnumProcessHandle(): void;
        /**
         * 枚举进程的线程id
         * @param ProcessID 进程id
         * @param returnDetail 是否返回 THREADENTRY32 为`false`或者为空则返回线程id
         */
        getProcessThreadList(ProcessID: number, returnDetail?: false): number[];
        /**
         * 
         * @param ProcessID 进程id
         * @param returnDetail 为`true` 则返回THREADENTRY32 
         */
        getProcessThreadList(ProcessID: number, returnDetail: true): HMC_V1.THREADENTRY32[];
        /**
         * 枚举进程的线程id
         * @param ProcessID 进程id
         */
        getProcessThreadList(ProcessID: number): number[];
        /**
         * 内联 清空句柄存储  不需要暴露
         */
        clearEnumAllProcessList(): void;
        /**
       * 内联 启动枚举进程快照 与句柄
       */
        enumAllProcess(): number;
        /**
         * 内联 枚举进程快照结果查询
         * @param enumID 枚举id
         */
        enumAllProcessPolling(enumID: number): Array<HMC_V1.PROCESSENTRY | void> | void;
        /**
         * 获取子进程id
         * @param ProcessID 
         */
        getSubProcessID(ProcessID: number): number[];
        /**
         * 通过可执行文件或者带有图标的文件设置窗口图标
         * @param handle 句柄
         * @param Extract 可执行文件/Dll/文件
         * @param index 图标位置索引 例如文件显示的图标默认是0
         */
        setWindowIconForExtract(handle: number, Extract: string, index: number): void;
        /**
         * 创建管道并执行命令
         * @param cmd 命令
         */
        popen(cmd: string): string;
        /**
        * 创建管道并执行命令
        * @param cmd 命令
        */
        _popen(cmd: string): string;
        /**
         * 获取屏幕上指定坐标的颜色
         * @param x 左边开始的坐标
         * @param y 从上面开始的坐标
         */
        getColor(x: number, y: number): Color;
        // /**
        //  * 截屏指定的宽高坐标 并将其存储写入为文件 
        //  * @param FilePath 文件路径
        //  * @param x 从左边的哪里开始 为空为0
        //  * @param y 从顶部的哪里开始 为空为0
        //  * @param width 宽度
        //  * @param height 高度
        //  */
        // captureBmpToFile(FilePath: string, x: number | null | 0, y: number | null | 0, width: number | null | 0, height: number | null | 0): void;
        /**
         * 响应标准快捷键
         */
        sendBasicKeys(ctrlKey: boolean, shiftKey: boolean, altKey: boolean, winKey: boolean, KeyCode: number): boolean;
        /**
         * 发送键盘事件
         * @param keyCode 键值码 
         * @param keyDown 是否按下
         */
        sendKeyboard(keyCode: number, keyDown?: boolean): boolean;
        /**
         * 响应T2C脚本 仅支持键盘事件 异步
         * @param T2C 脚本
         */
        sendKeyT2C(T2C: string): void;
        /**
        * 响应T2C脚本 仅支持键盘事件 同步
        * @param T2C 脚本
        */
        sendKeyT2CSync(T2C: string): void;
        /**
         * 创建一个互斥体 (如果当前进程还在 互斥体就不会消失) 返回的是互斥体是否成功创建
         */
        createMutex(MutexName: string): boolean;
        /**
        * 检查一个互斥体 如果互斥体存在
        */
        hasMutex(MutexName: string): boolean;
        /**
         * 添加环境变量
         * @param key 
         * @param data 
         */
        putenv(key: string, data: string): void;
        /**
         * 获取指定的变量环境
         * @param key 
         */
        getenv(key: string): string;
        /**
         * 获取变量环境
         */
        getAllEnv(): { [key: string]: string };
        /**
         * 通过标题或类名搜索所有窗口句柄
         * @param className 类名
         * @param titleName 标题
         * @param isWindow 是否要求为窗口(忽略子组件) 默认 true
         * @param isCaseSensitive 忽略区分大小写 默认 true
         */
        findAllWindow(className: string | null, titleName: string | null, isWindow: boolean | null, isCaseSensitive: boolean | null): number[];
        /**
         * 通过标题或类名搜索窗口句柄
         * @param className 类名
         * @param titleName 标题
         */
        findWindow(className?: string | null, titleName?: string | null): number | null;
        /**
         * 搜索窗口或子窗口
         * @param hWndParent 父窗口
         * @param hWndChildAfter 下級窗口 
         * @param className 类名
         * @param titleName 标题
         */
        findWindowEx(hWndParent: number | null, hWndChildAfter: number | null, className: string | null, titleName: string | null): number | null;
        /**
         * 获取指定进程的从启动到现在的时间 单位ms
         * @param ProcessID 
         */
        getProcessStartTime(ProcessID: number): number | null;
        /**
         * 内部debug开关
         */
        __debug_AllocConsole(): void;
        /**
         * 判断变量中是否存在指定值
         * - 用户
         * - 系统
         * @param key 
         */
        hasKeyExists(key: string): boolean;
        /**
         * 判断用户变量中是否存在指定值
         * - 用户
         * @param key 
         */
        hasUseKeyExists(key: string): boolean;
        /**
         * 判断系统变量中是否存在指定值
         * - 系统
         * @param key 
         */
        hasSysKeyExists(key: string): boolean;
        /**
         * 通过当前的变量对变量内容进行解析
         * - 实时的
         * - HMC_x64.escapeEnvVariable("%AppData%\\hmc-win32")   log  ->  'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
         * @param input 
         */
        escapeEnvVariable(input: string): string;

        /**
         * 删除一个用户变量
         * - 仅用户
         * @param key 
         */
        removeUserVariable(key: string): boolean;

        /**
        * 删除一个变量
        *  - 用户
        *  - 系统用户
        * @param key 
        */
        removeUserVariable(key: string): boolean;

        /**
         * 删除一个用户变量
         * - 仅用户
         * @param key 
         */
        removeSystemVariable(key: string): boolean;

        /**
         * 获取一个在系统变量中的值
         * @param key 
         * @param transMean 是否自动转义
         * - true %AppData%\\hmc-win32  -> 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
         * - false %AppData%\\hmc-win32 -> '%AppData%\\hmc-win32'
         * @default true
         */
        getSystemVariable(key: string, transMean?: boolean): string;

        /**
        * 获取一个在用户变量中的值
        * @param key 
        * @param transMean 是否自动转义
        * - true %AppData%\\hmc-win32  -> 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
        * - false %AppData%\\hmc-win32 -> '%AppData%\\hmc-win32'
        * @default true
        */
        getUserVariable(key: string, transMean?: boolean): string;

        /**
         *获取指定键值 按照默认优先级
         * ?- 用户变量和系统变量同时有非数组键  -> 用户变量
         * ?- 用户变量和系统变量同时为数组键    -> 用户变量数组
         * ?- 用户变量为数组键 系统变量为文本键  -> 用户文本键 排除系统
         * ?- 系统变量为文本键 用户变量为数组    -> 用户变量数组 排除系统
         * ?- 系统变量存在 用户变量为空文本      -> 排除此变量
         * ?- PATH                          -> 合并数组
         * @param key 键
         * @param key 
         */
        getVariableAnalysis(key: string): string;

        /**
         * 添加一个系统变量 （请注意 win进程获取的优先级: 进程变量 -> 用户变量 -> *系统变量）
         * @param key 键
         * @param value 值
         * @param append 是否添加到尾部 而不是替换
         * - false  "ddd" -> "ddd"
         * - true "ddd" -> "oid...;ddd"
         * @default false
         * @param transMean 是个自动转义的值
         * - false "%AppData%\\hmc-win32" -> "%AppData%\\hmc-win32"
         * - true "%AppData%\\hmc-win32" -> 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
         * @default false
         */
        putSystemVariable(key: string, value?: string, append?: boolean, transMean?: boolean): boolean;

        /**
         * 添加一个用户变量 （请注意 win进程获取的优先级: 进程变量 -> *用户变量 -> 系统变量）
         * @param key 键
         * @param value 值
         * @param append 是否添加到尾部 而不是替换
         * - false  "ddd" -> "ddd"
         * - true "ddd" -> "oid...;ddd"
         * @default false
         * @param transMean 是个自动转义的值
         * - false "%AppData%\\hmc-win32" -> "%AppData%\\hmc-win32"
         * - true "%AppData%\\hmc-win32" -> 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
         * @default false
         */
        putUserVariable(key: string, value?: string, append?: boolean, transMean?: boolean): boolean;

        /**
         * 获取所有的值 从环境读取 (进程环境)
         */
        getVariableAll(): HMC_V1.VariableList;

        /**
         * 从注册表读取现在的真实环境变量 但不更新到进程环境
         * - 请注意这里 不会添加 进程的变量
         * @param key 
         */
        getRealGlobalVariable(): HMC_V1.VariableList;
        /**
         * 获取用户变量的键列表
         */
        getUserKeyList(): string[];
        /**
         * 获取系统变量的键列表
         */
        getSystemKeyList(): string[];
        /**
         * 获取进程列表（枚举法）
         * - 枚举是最快的 最安全的 不会出现遗漏
         * @module 异步  
         * @time  fn() 9.691ms     fn(true)61.681ms
         * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
         * @returns 
         */
        getAllProcessList: (is_execPath?: boolean) => Promise<string> | number;
        /**
         * 获取进程列表（枚举法）
         * - 枚举是最快的 最安全的 不会出现遗漏
         * @module 同步 
         * @time  fn() 11.147ms     fn(true)44.633ms
         * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
         * @returns 
         */
        getAllProcessListSync: (is_execPath?: boolean) => string;
        /**
         * 获取进程列表 (快照法)  
         * - (一般用来枚举进程树)
         * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
         * @module 异步 
         * @time 66.428ms
         * @returns 
         */
        getAllProcessListSnp: () => Promise<string> | number;
        /**
         * 获取进程列表 (快照法)  
         * - (一般用来枚举进程树)
         * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
         * @module 同步 
         * @time 66.428ms
         * @returns 
         */
        getAllProcessListSnpSync: () => string;
        /**
         * 获取进程列表 (内核法)
         * - (可以获取内核软件和系统服务的名称)
         * - 请注意 内核法有可能被杀毒软件拦截
         * - 有概率第一次获取时失败
         * @module 异步  
         * @time 30.542ms
         * @returns 
         */
        getAllProcessListNt: () => Promise<string> | number;
        /**
         * 获取进程列表 (内核法)
         * - (可以获取内核软件和系统服务的名称)
         * - 请注意 内核法有可能被杀毒软件拦截
         * - 有概率第一次获取时失败
         * @module 同步 
         * @time 30.542ms
         * @returns 
         */
        getAllProcessListNtSync: () => string;
        /**
         * 获取指定进程的cpu百分比 (10% -> 10.02515102152)
         * @module 异步  
         * @time 1000ms+
         * @param pid 
         */
        getProcessCpuUsage(pid: number): Promise<number>;
        /**
         * 获取指定进程的cpu百分比 (10% -> 10.02515102152)
         * @module 同步 
         * ! 请注意此函数会阻塞进程最少1000ms 因为运算cpu占比需要一秒内进行两次对比
         * @param pid 进程id
         */
        getProcessCpuUsageSync(pid: number): number;
        /**
         * 获取指定进程的文件路径
         * @module 异步 
         * @param pid 进程id
         */
        getProcessFilePath(pid: number): Promise<string | null>;
        /**
         * @module 同步 
         * @param pid 进程id
         */
        getProcessFilePathSync(pid: number): string | null;
        /**
         * 判断当前进程是否存在
         * @module 异步 
         * @param pid 
         */
        existProcess(pid: number): null | number | Promise<boolean | null>;
        /**
        * 判断当前进程是否存在
        * @module 同步 
        * @param pid 
        */
        existProcessSync(pid: number): boolean | null;
        getCursorPos(): string;
        isStartHookMouse2(): boolean;
        unHookMouse2(): void;
        installHookMouse2(): void;
        getMouseNextSession2(): string;
        getLastInputTime(): number;
        /**
         * 是否 正在调用着 限制鼠标可移动范围的线程
         */
        hasLimitMouseRangeWorker(): boolean;
        /**
         * 限制鼠标光标可移动范围 (异步)
         * @description 可以调用stopLimitMouseRangeWorker提前结束 
         * ?最高不允许超过30000ms (30秒) 最低不允许低于31ms 
         * ?范围为正方形 如果没有设置right与bottom的值则将限制为1x1的正方形 (不可动)
         * @param ms 本次限制的时间
         * @param x 限制左边初始化点的位置
         * @param y 限制顶部初始化点的位置
         * @param right 允许的范围(左边到右边部)
         * @param bottom 允许光标移动的范围(顶到底部)
         */
        setLimitMouseRange(ms: number, x: number, y: number, right: number, bottom: number): boolean;
        /**
         * 提前结束限制鼠标可移动范围 一旦调用则立即解锁 返回的布尔是解锁线程是否成功 
         */
        stopLimitMouseRangeWorker(): boolean;
        /**
         * 获取指定进程得出命令行 
         * @description 由于跨进程权限问题 不保证获取得到
         * ?此功能在win8及以下系统 需要读取进程内存
         * @module 异步async
         * @param pid 进程id
         */
        getProcessCommand(pid: number): Promise<string | null>;
        /**
         * 获取指定进程得出命令行
         * @description 由于跨进程权限问题 不保证获取得到
         * ?此功能在win8及以下系统 需要读取进程内存
         * @module 同步Sync
         * @param pid 
         */
        getProcessCommandSync(pid: number): string | null;
        /**
         * 获取指定进程的工作目录
         * @description 由于跨进程权限问题 不保证获取得到
         * !此功能需要读取进程内存
         * @module 异步async
         * @param pid 
         */
        getProcessCwd(pid: number): Promise<string>;
        /**
         * 获取指定进程的工作目录
         * @description 由于跨进程权限问题 不保证获取得到
         * !此功能需要读取进程内存
         * @module 同步Sync
         * @param pid 
         */
        getProcessCwdSync(pid: number): string;
        /**
         * 获取注册表值
         */
        getRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null): REG_VALUE | null;
        /**
         * 设置注册表值 （提供了初级和低级操作）
         * @param Hive 根目录
         * @param folderPath 目录路径
         * @param keyName 值键
         * @param data 数据体
         * - null 设置空值
         * - string 约 2^31 - 1 个字符 (2GB) 但是不建议存储过大数据 会出问题
         * - number DWORD 标准范围约为 0(0x0) 到 4294967295(0xffffffff) (即 2^32 - 1)
         * - bigint QWORD 标准范围约为  0n(0x0) 到 18446744073709551615n (0xffffffffffffffff)（即 2^64 - 1）
         * - boolean 布尔 以DWORD状态存储 范围 0-1
         * - Buffer 二进制  1024KB 以内
         * - Date 时间戳 以浮点二进制存储
         * - string[] 文本数组 REG_MULTI_SZ格式 允许存储空文本但是不建议 (因为非标准) 但是数组末尾的元素是空文本会被清空
         * @param type 类型
         * - true 文本时将转义到转义类型
         * - HMC.REG_TYPE 强制转义 仅限二进制类型
         */
        setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null, data: null | number | bigint | boolean | Buffer | Date | string | string[], type: undefined | boolean | HMC.REG_TYPE): boolean;
        /**
         * 创建目录
         * @param Hive 
         * @param folderPath 
         */
        createRegistrFolder(Hive: HMC.HKEY, folderPath: string): boolean;
        /**
         * 获取目录信息
         * @param Hive 
         * @param folderPath 
         */
        getRegistrFolderStat(Hive: HMC.HKEY, folderPath: string, is_enum?: boolean): string | null;
        /**
         * 删除目录
         * @param Hive 
         * @param folderPath 
         * @param keyName 
         * @param tree 
         */
        removeRegistrFolder(Hive: HMC.HKEY, folderPath: string, keyName: string | null, tree: boolean): boolean;
        /**
         * 删除值
         * @param Hive 
         * @param folderPath 
         * @param keyName 
         */
        removeRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null): boolean;
        /**
         * 获取值信息
         * @param Hive 
         * @param folderPath 
         * @param keyName 
         */
        getRegistrValueStat(Hive: HMC.HKEY, folderPath: string, keyName: string | null): string | null;
        /**
         * 获取二进制值
         * @param Hive 
         * @param folderPath 
         * @param keyName 
         */
        getRegistrBuffValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null): Buffer | null;

    }

    export type ProcessHandle = {
        // 句柄 
        handle: number;
        // 名称(数据)
        name: string;
        // 类型
        type: "ALPC Port" | "Event" | "Timer" | "Mutant" | "Key" | "Section" | "File" | "Thread" | string;
    };

    export type Volume = {
        // 真实的文件路径  例如： 'D:\\' 
        path: string;
        // 名称：驱动路径 例如： \\\\?\\Volume{f0b00a00-0000-0000-0000-000000000000}\\ 
        name: string;
        // 驱动器  例如：'\\Device\\HarddiskVolume2'
        device: string;
    };

    /**取色 颜色返回值 */
    export type Color = {
        r: number;
        g: number;
        b: number;
        // #000000 16进制色码
        hex: string;
    };

    export type RegistrFolderStat = {
        // 目录键列表
        folder?: string[];
        // 值键列表
        key?: string[];
        // 此内容是否存在
        exists: boolean;
        // 大小
        size: number;
        // 目录键数量
        folderSize: number;
        // 该目录下有多少个值键
        keySize: number;
        // 该目录上次写入的时间戳 毫秒
        time: number;
    };

    export type RegistrValueStat = {
        // 此值的类型
        type: REG_TYPE;
        // 内容大小
        size: number;
        // 此内容是否存在
        exists: boolean;
    };

    /**
     * 标准快捷键的输入表
     */
    export type BasicCout = {
        /**组合中含有ctrl */
        ctrl?: any,
        /**组合中含有shift */
        shift?: any,
        /**组合中含有alt */
        alt?: any,
        /**组合中含有win */
        win?: any,
        /**键码/按键名 */
        key?: number | string,
        /**键码/按键名 */
        code?: number | string
    };

    type chcpList = {
        37: "IBM037",
        437: "IBM437",
        500: "IBM500",
        708: "ASMO-708",
        720: "DOS-720",
        737: "ibm737",
        775: "ibm775",
        850: "ibm850",
        852: "ibm852",
        855: "IBM855",
        857: "ibm857",
        858: "IBM00858",
        860: "IBM860",
        861: "ibm861",
        862: "DOS-862",
        863: "IBM863",
        864: "IBM864",
        865: "IBM865",
        866: "cp866",
        869: "ibm869",
        870: "IBM870",
        874: "windows-874",
        875: "cp875",
        932: "shift_jis",
        936: "gb2312",
        949: "ks_c_5601-1987",
        950: "big5",
        1026: "IBM1026",
        1047: "IBM01047",
        1140: "IBM01140",
        1141: "IBM01141",
        1142: "IBM01142",
        1143: "IBM01143",
        1144: "IBM01144",
        1145: "IBM01145",
        1146: "IBM01146",
        1147: "IBM01147",
        1148: "IBM01148",
        1149: "IBM01149",
        1200: "utf-16",
        1201: "unicodeFFFE",
        1250: "windows-1250",
        1251: "windows-1251",
        1252: "windows-1252",
        1253: "windows-1253",
        1254: "windows-1254",
        1255: "windows-1255",
        1256: "windows-1256",
        1257: "windows-1257",
        1258: "windows-1258",
        1361: "Johab",
        10000: "macintosh",
        10001: "x-mac-japanese",
        10002: "x-mac-chinesetrad",
        10003: "x-mac-korean",
        10004: "x-mac-arabic",
        10005: "x-mac-hebrew",
        10006: "x-mac-greek",
        10007: "x-mac-cyrillic",
        10008: "x-mac-chinesesimp",
        10010: "x-mac-romanian",
        10017: "x-mac-ukrainian",
        10021: "x-mac-thai",
        10029: "x-mac-ce",
        10079: "x-mac-icelandic",
        10081: "x-mac-turkish",
        10082: "x-mac-croatian",
        12000: "utf-32",
        12001: "utf-32BE",
        20000: "x-Chinese_CNS",
        20001: "x-cp20001",
        20002: "x_Chinese-Eten",
        20003: "x-cp20003",
        20004: "x-cp20004",
        20005: "x-cp20005",
        20105: "x-IA5",
        20106: "x-IA5-German",
        20107: "x-IA5-Swedish",
        20108: "x-IA5-Norwegian",
        20127: "us-ascii",
        20261: "x-cp20261",
        20269: "x-cp20269",
        20273: "IBM273",
        20277: "IBM277",
        20278: "IBM278",
        20280: "IBM280",
        20284: "IBM284",
        20285: "IBM285",
        20290: "IBM290",
        20297: "IBM297",
        20420: "IBM420",
        20423: "IBM423",
        20424: "IBM424",
        20833: "x-EBCDIC-KoreanExtended",
        20838: "IBM-Thai",
        20866: "koi8-r",
        20871: "IBM871",
        20880: "IBM880",
        20905: "IBM905",
        20924: "IBM00924",
        20932: "EUC-JP",
        20936: "x-cp20936",
        20949: "x-cp20949",
        21025: "cp1025",
        21866: "koi8-u",
        28591: "iso-8859-1",
        28592: "iso-8859-2",
        28593: "iso-8859-3",
        28594: "iso-8859-4",
        28595: "iso-8859-5",
        28596: "iso-8859-6",
        28597: "iso-8859-7",
        28598: "iso-8859-8",
        28599: "iso-8859-9",
        28603: "iso-8859-13",
        28605: "iso-8859-15",
        29001: "x-Europa",
        38598: "iso-8859-8-i",
        50220: "iso-2022-jp",
        50221: "csISO2022JP",
        50222: "iso-2022-jp",
        50225: "iso-2022-kr",
        50227: "x-cp50227",
        51932: "euc-jp",
        51936: "EUC-CN",
        51949: "euc-kr",
        52936: "hz-gb-2312",
        54936: "GB18030",
        57002: "x-iscii-de",
        57003: "x-iscii-be",
        57004: "x-iscii-ta",
        57005: "x-iscii-te",
        57006: "x-iscii-as",
        57007: "x-iscii-or",
        57008: "x-iscii-ka",
        57009: "x-iscii-ma",
        57010: "x-iscii-gu",
        57011: "x-iscii-pa",
        65000: "utf-7",
        65001: "utf-8"
    };

    export type SystemDecoderKey = keyof chcpList;

    export type VarValueReBackData = {
        // 被更新的键名称
        key: string,
        // 之前的变量
        oid_value: string | undefined | null,
        // 新的变量内容
        new_vaule: string | undefined | null,
        /**
         * 更新类型
         * - update 直接替换新的变量内容
         * - remove 直接删除变量
         * - append 添加了新的变量(变量组)
         * - reduce 删除了新的变量(变量组)
         */
        update_type: "update" | "remove" | "append" | "reduce"
        // 更新类型为 reduce/ append  时候会有此属性
        value?: string | undefined | null,
    };

    export interface REG_SZ_VALUE {
        type: 1;
        typeName: "REG_SZ";
        data: string;
    }

    export interface REG_EXPAND_SZ_VALUE {
        type: REG_TYPE.REG_EXPAND_SZ;
        typeName: "REG_EXPAND_SZ";
        data: string;
        dataExpand: string;
    }

    export interface REG_DWORD_VALUE {
        type: REG_TYPE.REG_DWORD | REG_TYPE.REG_DWORD_BIG_ENDIAN | REG_TYPE.REG_DWORD_LITTLE_ENDIAN;
        typeName: "REG_DWORD" | "REG_DWORD_BIG_ENDIAN" | "REG_DWORD_LITTLE_ENDIAN";
        data: number;
    }

    export interface REG_QWORD_VALUE {
        type: REG_TYPE.REG_QWORD | REG_TYPE.REG_QWORD_LITTLE_ENDIAN;
        typeName: "REG_QWORD" | "REG_QWORD_LITTLE_ENDIAN";
        data: bigint;
    }

    export interface REG_BINARY_VALUE {
        type: REG_TYPE.REG_BINARY;
        typeName: "REG_BINARY";
        data: Buffer;
    }

    export interface REG_MULTI_SZ_VALUE {
        type: REG_TYPE.REG_MULTI_SZ;
        typeName: "REG_MULTI_SZ";
        data: string[];
    }

    export interface REG_ANY_VALUE {
        type: REG_TYPE.REG_FULL_RESOURCE_DESCRIPTOR | REG_TYPE.REG_LINK | REG_TYPE.REG_NONE | REG_TYPE.REG_RESOURCE_LIST | REG_TYPE.REG_RESOURCE_REQUIREMENTS_LIST;
        typeName: "REG_FULL_RESOURCE_DESCRIPTOR" | "REG_LINK" | "REG_NONE" | "REG_RESOURCE_LIST" | "REG_RESOURCE_REQUIREMENTS_LIST";
        data: Buffer;
    }

    export type REG_VALUE = REG_SZ_VALUE | REG_EXPAND_SZ_VALUE | REG_DWORD_VALUE | REG_QWORD_VALUE | REG_BINARY_VALUE | REG_MULTI_SZ_VALUE | REG_ANY_VALUE;



    export type ClipboardInfo = {
        // 枚举剪贴板中的格式
        format: number[],
        // 剪贴板中的格式数量
        formatCount: number,
        // 写入剪贴板软件的句柄
        hwnd: number,
        // 本次剪贴板内容的唯一id
        id: number
    };

    export type ClipboardHTMLInfo = {
        // html文本 原始文本(win 的存储格式)
        data: string;
        // body体(核心数据) 结束位置
        EndFragment: number;
        // html body(document) 结束位置
        EndHTML: number;
        // 本次数据格式是否有效
        is_valid: boolean;
        // 链接
        SourceURL: string;
        // body体(核心数据) 开始位置
        StartFragment: number;
        // html body(document) 开始位置
        StartHTML: number;
        // 此格式是winapi的什么格式
        Version: number;
        // 获取html(document)
        get document(): string | null;
        // 获取html(body 内容体)
        get body(): string | null;
    }
    export type PromiseSessionDataType = undefined | null | any;

    export type SystemDecoder = chcpList[SystemDecoderKey];
}

export default HMC_STORE;

export const Native = HMC_STORE;
