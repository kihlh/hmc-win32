import PromiseEval = require("./promiseEval");


interface Native {

    /**
     * 执行命令代码 并且按照api内容返回 异步
     * @param pid 进程id
     * @param command 命令
     */
    HMC_PromiseEval?(command: PromiseEval.HMC_PROMISEEVAL_TASK_TYPE, ...arg: any[]): Promise<any>;

    /**
     * 执行命令代码 并且按照api内容返回 同步
     * @param pid 进程id
     * @param command 命令
     */
    HMC_PromiseEvalSync?(command: PromiseEval.HMC_PROMISEEVAL_TASK_TYPE, ...arg: any[]): any;

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

    // 获取剪贴板文件路径列表 以\0切割(高性能同步)
    getClipboardFilePaths?: () => string;

    /**
     * 设置剪贴板本文或者html
     * @param text 文本
     * @param is_html 以html方式写入
     * @returns 
     */
    setClipboardText?: (text: string, is_html?: boolean) => boolean;

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
    getClipboardHTML?: () => HMC2.CLIP_HTML_INFO | null;
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
    createFsLink?: (targetType: HMC2.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string) => boolean;

    /**
     * 弹出右键菜单的接口
     * @param hwnd 调用窗口 / 允许为null
     * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
     * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
     * @param y 坐标
     */
    showContextMenu?: (hwnd: number | null, file: string | string[], x: number, y: number) => boolean;
    HMC_MOUSE_CLASS?: () => HMC2.HMC_MOUSE_CLASS;
    HMC_KEYBOARD_CLASS?: () => HMC2.HMC_KEYBOARD_CLASS;
    HMC_SHELL_STARTUP_CLASS?: () => HMC2.HMC_SHELL_STARTUP_CLASS;
}


export module HMC2 {
    export type CLIP_HTML_INFO = {
        data: string;
        EndFragment: number;
        EndHTML: number;
        is_valid: boolean;
        SourceURL: string;
        StartFragment: number;
        StartHTML: number;
        Version: number;
    }
    export enum FS_MK_LINK_TARGET_TYPE {
        CREATE_DIR_SYMLINK = 166,
        CREATE_SYMLINK = 168,
        CREATE_HARD_LINK = 170,
        CREATE_SYMBOLIC_LINK = 172
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
        isValidHookKeyboard(): boolean;
        getAllKeyboardEventJson(): string;
        stopHookKeyboard(): boolean;
        hasKeysBasic(): BASIC_KEYS;
        hasKeyActivate(KeysEvent: number): boolean;
    }

    export interface HMC_MOUSE_CLASS {
        initMouseEventHook(): boolean;
        isValidHookMouse(): boolean;
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
        // 事件id (每次结束时次记)
        id: number;
        // 事件时间
        time: number;
        // 是否按下
        down: boolean;
        // 扩展键标志
        flags: number;
        // 键码
        keyCode: number;
        // 执行的设备id
        scanCode: number;
        // 映射代码 例如 A 0 1
        KeyName: string;
        // 映射代码 例如 KeyE , KeyA
        KeyNameCode: string;
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

}

class HMC2_Native {

    _BinPath = "";
    _Native: Native = {};
    _Loaded = false;

    constructor(binPath?: string) {

        if (binPath) {
            this._BinPath = binPath;
            return;
        }

        if (process.arch.match(/^(x32|ia32)$/)) {
            this._BinPath = "./bin/HMC@Beta_x86.node";
        }

        if (process.arch.match(/^x64$/)) {
            this._BinPath = "./bin/HMC@Beta_x64.node";
        }

    }

    private LoadNodeBin() {
        try {

            // Debug 环境带入
            if (process.env) {
                if (process.env.USERNAME == "kiic" && process.env.msvc_dir && process.env.mode) {
                    this._BinPath = process.env.mode;
                    return;
                }
            }

            if (this._BinPath) {
                this._Native = require(this._BinPath);
                return;
            } else {

                if (process.arch.match(/^(x32|ia32)$/)) {
                    return require("./bin/HMC@Beta_x86.node");
                }

                if (process.arch.match(/^x64$/)) {
                    return require("./bin/HMC@Beta_x64.node");
                }

            }

        } catch (s_O) { }
    }

    get native(): Native {

        if (!this._Loaded) {
            this.LoadNodeBin();
            this._Loaded = true;
        }

        return this._Native;
    }

}

export const native = new HMC2_Native();

