import path = require("path");
import os = require("os");
import fs = require("fs");
import https = require('https');
import dgram = require('dgram');
import { chcpList } from "./chcpList";
import { KeyboardcodeComparisonTable, KeyboardcodeEmenList, VK_VirtualKey, VK_code, VK_key, VK_keyCode, vkKey } from "./vkKey";
import child_process = require("child_process");
import net = require("net");
const argvSplit: (str: string) => string[] = require("argv-split");
let $_thenConsole: HWND | null = null;
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
/**
 * @zh-cn 静态调用 hmc.dll (注意如果您不知道这个是什么作用 请勿随意调用 参数错误有可能会导致进程崩溃)
 * @en-us Static call to hmc.dll (Note that if you don't know what this does, don't call it at random.  Parameter errors may cause the process to crash)
 */
const get_native: () => HMC.Native = (binPath?: string) => {
    function _require_bin(): HMC.Native | null {
        try {
            if (binPath) return require(binPath);
            if (process.arch.match(/^x32|ia32$/)) return require("./bin/HMC_x86.node");
            if (process.arch.match(/^x64$/)) return require("./bin/HMC_x64.node");
        } catch (X_X) {

        }
        return null;
    }
    let Native: HMC.Native = (process.platform == "win32" ? _require_bin() : null) || (() => {
        let HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
        function fnBool(...args: any[]) { console.error(HMCNotPlatform); return false }
        function fnVoid(...args: any[]) { console.error(HMCNotPlatform); return undefined }
        function fnNull(...args: any[]) { console.error(HMCNotPlatform); return null }
        function fnNum(...args: any[]) { console.error(HMCNotPlatform); return 0 }
        function fnStrList(...args: any[]) { console.error(HMCNotPlatform); return [] as string[] }
        function fnStr(...args: any[]) { console.error(HMCNotPlatform); return '' }
        function fnAnyArr(...args: any[]) { console.error(HMCNotPlatform); return [] as any[] }
        return {
            _popen: fnStr,
            popen: fnStr,
            createMutex: fnBool,
            getSubProcessID: fnAnyArr,
            enumAllProcessPolling: fnVoid,
            clearEnumAllProcessList: fnVoid,
            getProcessParentProcessID: fnVoid,
            enumAllProcess: fnNum,
            _SET_HMC_DEBUG: fnBool,
            isStartKeyboardHook: fnBool,
            isStartHookMouse: fnBool,
            clearEnumProcessHandle: fnVoid,
            getProcessThreadList: fnAnyArr,
            getMouseNextSession: fnAnyArr,
            getKeyboardNextSession: fnAnyArr,
            unKeyboardHook: fnVoid,
            unHookMouse: fnVoid,
            installKeyboardHook: fnVoid,
            installHookMouse: fnVoid,
            MessageError: fnVoid,
            MessageStop: fnBool,
            SetBlockInput: fnBool,
            SetSystemHOOK: fnBool,
            SetWindowInTaskbarVisible: fnBool,
            alert: fnBool,
            clearClipboard: fnBool,
            closedHandle: fnVoid,
            confirm: fnBool,
            createDirSymlink: fnBool,
            createHardLink: fnBool,
            createPathRegistr: fnBool,
            createSymlink: fnBool,
            desc: "HMC Connection System api",
            enumRegistrKey: fnStrList,
            getAllWindows: fnAnyArr,
            getAllWindowsHandle: fnAnyArr,
            getBasicKeys: () => {
                console.error(HMCNotPlatform);
                return {
                    "alt": false,
                    "ctrl": false,
                    "shift": false,
                    "win": false,
                }
            },
            getClipboardFilePaths: fnStrList,
            getClipboardText: fnStr,
            getDetailsProcessList: fnAnyArr,
            getDeviceCaps: () => {
                console.error(HMCNotPlatform);
                return {
                    "height": 0,
                    "width": 0,
                }
            },
            getForegroundWindow: fnNum,
            getForegroundWindowProcessID: fnNull,
            getHandleProcessID: fnNull,
            getHidUsbList: fnAnyArr,
            getMainWindow: fnNull,
            getMetrics: () => { console.error(HMCNotPlatform); return { "left": 0, "top": 0, "x": 0, "y": 0 } },
            getMouseMovePoints: fnAnyArr,
            getPointWindow: fnNull,
            getPointWindowMain: fnNum,
            getPointWindowName: fnStr,
            getPointWindowProcessId: fnNum,
            getProcessHandle: fnNull,
            getProcessList: fnAnyArr,
            getProcessName: fnNull,
            getProcessidFilePath: fnNull,
            getRegistrBuffValue: fnVoid,
            getRegistrDword: fnNum,
            getRegistrQword: () => {
                console.error(HMCNotPlatform);
                return BigInt(0)
            },
            getShortcutLink: () => {
                console.error(HMCNotPlatform);
                return { "args": "", "cwd": '', "desc": "", "hotkey": 0, "icon": "", "iconIndex": 0, "showCmd": 0, "path": "" }
            },
            getStringRegKey: fnStr,
            getSystemIdleTime: fnNum,
            getSystemMenu: fnBool,
            getTrayList: fnAnyArr,
            getUsbDevsInfo: fnStrList,
            getWindowRect: () => {
                console.error(HMCNotPlatform);
                return { "bottom": 0, "height": 0, "width": 0, "left": 0, "top": 0, "right": 0, "x": 0, "y": 0 }
            },
            hasKeyActivate: fnBool,
            hasProcess: fnBool,
            hasRegistrKey: fnBool,
            hasWindowTop: fnBool,
            isAdmin: fnBool,
            isEnabled: fnBool,
            isHandle: fnBool,
            isHandleWindowVisible: fnBool,
            isProcess: fnBool,
            isSystemX64: fnBool,
            killProcess: fnBool,
            leftClick: fnBool,
            lookHandleCloseWindow: fnBool,
            lookHandleGetTitle: fnNull,
            lookHandleSetTitle: fnBool,
            setWindowIconForExtract: fnVoid,
            lookHandleShowWindow: fnBool,
            messageBox: fnNum as () => 1,
            mouse: fnBool,
            openApp: fnBool,
            openExternal: fnBool,
            openPath: fnBool,
            openURL: fnBool,
            platform: "win32",
            powerControl: fnVoid,
            removeStringRegKey: fnBool,
            removeStringRegKeyWalk: fnBool,
            removeStringRegValue: fnBool,
            rightClick: fnBool,
            setClipboardFilePaths: fnBool,
            setClipboardText: fnBool,
            setCursorPos: fnBool,
            setHandleTransparent: fnBool,
            setRegistrDword: fnBool,
            setRegistrKey: fnBool,
            setRegistrQword: fnBool,
            setShortcutLink: fnBool,
            setWindowEnabled: fnBool,
            setWindowFocus: fnBool,
            setWindowMode: fnBool,
            setWindowTop: fnBool,
            showMonitors: fnBool,
            shutMonitors: fnBool,
            sleep: fnBool,
            system: fnNum,
            systemStartTime: fnNum,
            updateWindow: fnBool,
            version: "0.0.0",
            windowJitter: fnVoid,
            enumChildWindows: fnAnyArr,
            deleteFile: fnNum,
            getClipboardSequenceNumber: fnNum,
            enumClipboardFormats: fnAnyArr,
            getHidUsbIdList: fnAnyArr,
            getDeviceCapsAll: fnAnyArr,
            isInMonitorWindow: fnBool,
            isMouseMonitorWindow: fnBool,
            getCurrentMonitorRect: () => { console.error(HMCNotPlatform); return { "bottom": 0, "left": 0, "top": 0, "right": 0, } },
            getSystemMetricsLen: fnNum,
            getWindowStyle: fnNum,
            getWindowClassName: fnStr,
            formatVolumePath: fnStr,
            getVolumeList: fnAnyArr,
            enumProcessHandlePolling: fnVoid,
            enumProcessHandle: fnNum,
            getModulePathList: fnStrList,
            getColor() { return { r: 0, g: 0, b: 0, hex: "#000000" } as HMC.Color },
            captureBmpToFile: fnVoid,
            sendKeyboard: fnBool,
            sendBasicKeys: fnBool,
            sendKeyT2C: fnVoid,
            sendKeyT2CSync: fnVoid,
            hasMutex: fnBool,
            getAllEnv() { return process.env as any },
            getTCPPortProcessID: fnNull,
            getenv: fnStr,
            getUDPPortProcessID: fnNull,
            putenv: fnVoid,
        }
    })();
    return Native;
};
export const native: HMC.Native = get_native();

/**
 * 句柄 可以视为是一个数字也可以视为是一个功能 {0}
 * 继承了 Number 的构建类
 */
export class HWND extends Number {
    constructor(hWnd: number) {
        super(hWnd);
        this.HWND = hWnd;
    }
    /**句柄 */
    get handle() { return this.HWND };
    /**真实的句柄 */
    HWND: number;
    /**
     * 强制关闭窗口不发送被关闭的消息给窗口
     */
    closed() {
        if (!this.exists) return false;
        return native.closedHandle(this.HWND);
    }
    /**
     * 向窗口发送关闭的消息
     */
    close() {
        if (!this.exists) return false;
        return native.lookHandleCloseWindow(this.HWND);
    }
    /**
     * 窗口位置
     */
    get rect(): HMC.Rect | null {
        if (!this.exists) return null;
        return native.getWindowRect(this.HWND);
    }
    /**
     * 窗口名称
     */
    get title(): string {
        return native.lookHandleGetTitle(this.HWND) || "";
    }
    /**
     * 设置窗口的标题
     * @param Title 标题
     * @returns
     */
    setTitle(Title: string) {
        if (typeof Title !== "string" || !this.exists) {
            return false;
        }
        return native.lookHandleSetTitle(this.HWND, Title);
    }
    /**句柄是否有效 */
    get exists() {
        if (!this.HWND) return false;
        return native.isHandle(this.HWND);
    }
    /**句柄是否有效 */
    get isHandle() {
        return this.exists;
    }
    /**
     * 当前句柄的pid
     */
    get pid() {
        if (!this.exists) return 0;
        return native.getHandleProcessID(this.HWND);
    }
    /**
     * 获取主窗口的pid
     */
    get MianPid(): HMC.ProcessID | null {
        if (!this.exists) return 0;
        return native.getHandleProcessID(this.MainHandle);
    }
    get MainHandle(): number {
        return native.getMainWindow(this.HWND) || 0;
    }
    get className() {
        return native.getWindowClassName(this.HWND);
    }
    get style() {
        return native.getWindowStyle(this.HWND);
    }
    /**
     * 判断窗口是否可见
     * @returns
     */
    isVisible() {
        if (!this.HWND) return false;
        return native.isHandleWindowVisible(this.HWND);
    }
    /**
     * 结束该进程
     * @returns
     */
    kill() {
        let processid = this.MianPid;
        if (!processid) return false;
        return native.killProcess(processid);
    }
    /**
     * 隐藏窗口
     * @returns
     */
    hide() {
        if (!this.HWND) return false;
        return native.lookHandleShowWindow(this.HWND, 0);
    }
    /**
     * 显示窗口
     * @returns
     */
    show() {
        if (!this.HWND) return false;

        return native.lookHandleShowWindow(this.HWND, 5);
    }
    /**
     * 窗口最小化
     * @returns
     */
    setMin() {
        if (!this.HWND) return false;

        return native.lookHandleShowWindow(this.HWND, 7);
    }
    /**
     * 窗口最大化
     * @returns
     */
    setMax() {
        if (!this.HWND) return false;

        return native.lookHandleShowWindow(this.HWND, 3);
    }
    /**
     * 恢复最近的状态
     * @returns
     */
    setRestore() {
        if (!this.HWND) return false;

        return native.lookHandleShowWindow(this.HWND, 9);
    }
    /**
     * 聚焦该窗口
     * @returns
     */
    setFocus() {
        if (!this.HWND) return false;

        return native.setWindowFocus(this.HWND);
    }
    /**
     * 禁用窗口
     * @param enabled
     * @returns
     */
    setEnabled(enabled: boolean) {
        if (!this.HWND) return false;

        return native.setWindowEnabled(this.HWND, enabled);
    }
    /**
     * 是否被禁用
     * @returns
     */
    isEnabled() {
        if (!this.HWND) return false;

        return native.isEnabled(this.HWND);
    }
    /**
     * 窗口抖动
     * @returns
     */
    setJitter() {
        if (!this.HWND) return false;
        return native.windowJitter(this.HWND);
    }
    /**
     * 判断窗口是否被顶设
     * @returns
     */
    isTop() {
        if (!this.HWND) return false;

        return native.hasWindowTop(this.HWND);
    }
    /**
     * 设置窗口顶设或者取消
     * @returns
     */
    setTopOrCancel() {
        if (!this.HWND) return false;

        return native.setWindowTop(this.HWND);
    }
    /**
     * 设置窗口不透明度
     * @param opacity 0-100 or 0.0 - 1.0
     */
    setOpacity(opacity: number) {
        if (typeof opacity !== "number" || opacity > 100 || isNaN(opacity))
            throw new Error(
                "fun <setOpacity> arg:<Opacity> is only allowed from 0.0 to 1.0 or  0 to 255"
            );
        if (opacity < 1) {
            return this.setTransparent(Math.trunc(255 * opacity));
        }
        opacity = (255 / 100) * opacity;
        if (!isNaN(opacity)) {
            return this.setTransparent(Math.trunc(255 * opacity));
        }
        return false;
    }
    /**
     * 设置窗口不透明度
     * @param opacity -1 - 255
     */
    setTransparent(opacity: number) {
        if (opacity > -1 || opacity < 255) {
            throw new Error(
                "fun <setTransparent> arg:<Opacity> is only allowed from -1 to 255"
            );
        }
        if (!this.HWND) return false;
        return native.setHandleTransparent(this.HWND, opacity as HMC.HandleTransparent);
    }
}
// 类型
export module HMC {
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

    // 注册表根目录
    export type HKEY = keyof typeof Hkey;

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
    export type mouse_event = /**不支持的属性 请使用 setCursorPos 方法设置位置*/ 32768 | /**左键按下 */ 2 | /**左边的按钮是向上的 */ 4 | /**中间的按钮是向下的 */ 32 | /**中间的按钮是向上的 */ 64 | /**鼠标移动和按钮点击 */ 1 | /**鼠标右键按下 */ 8 | /**鼠标右键弹起 */ 16 | /**滚轮按钮被旋转 */ 2048 | /**按下了 X 按钮 */ 128 | /**X 按钮被释放 */ 256 | /**滚轮按钮倾斜*/ 4096 | /**不支持的属性 请使用 setCursorPos 方法设置位置*/ "MOUSEEVENTF_ABSOLUTE" | /**左键按下 */ "MOUSEEVENTF_LEFTDOWN" | /**左边的按钮是向上的 */ "MOUSEEVENTF_LEFTUP" | /**中间的按钮是向下的 */ "MOUSEEVENTF_MIDDLEDOWN" | /**中间的按钮是向上的 */ "MOUSEEVENTF_MIDDLEUP" | /**鼠标移动和按钮点击 */ "MOUSEEVENTF_MOVE" | /**鼠标右键按下 */ "MOUSEEVENTF_RIGHTDOWN" | /**鼠标右键弹起 */ "MOUSEEVENTF_RIGHTUP" | /**滚轮按钮被旋转 */ "MOUSEEVENTF_WHEEL" | /**按下了 X 按钮 */ "MOUSEEVENTF_XDOWN" | /**X 按钮被释放 */ "MOUSEEVENTF_XUP" | /**滚轮按钮倾斜*/ "MOUSEEVENTF_HWHEEL";

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

    export type Native = {
        _SET_HMC_DEBUG(): boolean;
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
        /**
         * 判断进程id 是否存在
         */
        isProcess(ProcessID: ProcessID): boolean;
        /**
         * 判断进程id 是否存在
         */
        hasProcess(ProcessID: ProcessID): boolean;
        /** 获取进程名**/
        getProcessName: (ProcessID: ProcessID) => string | null;
        /** 获取进程可执行文件位置**/
        getProcessidFilePath: (ProcessID: ProcessID) => string | null;
        /** 获取活动窗口的进程id**/
        getForegroundWindowProcessID: () => ProcessID | null;
        /** 获取句柄对应的进程id**/
        getHandleProcessID: (Handle: number) => ProcessID | null;
        /** 获取快捷方式的信息**/
        getShortcutLink: (LnkPath: string) => SHORTCUT_LINK;
        setShortcutLink(LnkPath: string, FilePath: string, work_dir: string, desc: string, args: string, iShowCmd: number, icon: string, iconIndex: number): boolean;
        setShortcutLink(LnkPath: string, FilePath: string, work_dir?: string, desc?: string, args?: string, iShowCmd?: number): boolean;
        setShortcutLink(LnkPath: string, FilePath: string): boolean;
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
        /** 获取托盘图标列表**/
        getTrayList(): TRAY_ICON[];
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
        /** 获取进程列表**/
        getProcessList: (ForSleepTime?: number) => enumProcessCont[];
        /** 获取详细进程列表（慢20ms）**/
        getDetailsProcessList: (ForSleepTime?: number) => enumProcessContP[];
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
        /** 设置剪贴板文本**/
        setClipboardText: (EditText: string) => void;
        /** 获取剪贴板文本**/
        getClipboardText: () => string;
        /** 获取鼠标之前64个位置**/
        getMouseMovePoints: () => MovePoint[];
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
         * 判断键值是否存在
         * @param HKEY 根目录
         * @param Path 路径
         * @param Key 键值 (默认值 直接用： "" )
         */
        hasRegistrKey(HKEY: HMC.HKEY, Path: string, Key: string): boolean;
        /**
         * 获取内容(文本)
         * @param HKEY 根目录
         * @param Path 路径
         * @param Key 键值 (默认值 直接用： "" )
         */
        getStringRegKey(HKEY: HMC.HKEY, Path: string, Key: string): string;
        /**
        * 获取内容(64位数字)
        * @param HKEY 根目录
        * @param Path 路径
        * @param Key 键值 (默认值 直接用： "" )
        */
        getRegistrQword(HKEY: HMC.HKEY, Path: string, Key: string): bigint;
        /**
        * 获取内容(32位数字)
        * @param HKEY 根目录
        * @param Path 路径
        * @param Key 键值 (默认值 直接用： "" )
        */
        getRegistrDword(HKEY: HMC.HKEY, Path: string, Key: string): number;
        /**
         * 设置键值对(32位数字)
         * @param HKEY 根目录
         * @param Path 路径
         * @param Key 键值
         * @param Data 数据 (默认值 直接用： "" )
         */
        setRegistrDword(HKEY: HMC.HKEY, Path: string, Key: string, Dword: number): boolean;
        /**
         * 设置键值对(64位数字)
         * @param HKEY 根目录
         * @param Path 路径
         * @param Key 键值
         * @param Data 数据 (默认值 直接用： "" )
         */
        setRegistrQword(HKEY: HMC.HKEY, Path: string, Key: string, Qword: bigint): boolean;
        /**
         * 删除空目录键值
         * @param HKEY 根目录
         * @param Path 路径
         * @param Key 键值 (默认值 直接用： "" )
         */
        removeStringRegKey(HKEY: HMC.HKEY, Path: string, Key: string): boolean;
        /**
         * 设置键值对
         * @param HKEY 根目录
         * @param Path 路径
         * @param Key 键值
         * @param Data 数据 (默认值 直接用： "" )
         */
        setRegistrKey(HKEY: HMC.HKEY, Path: string, Key: string, Data: string): boolean;
        /**
         * 创建新的路径
         * @param HKEY 根目录
         * @param Path 路径
         */
        createPathRegistr(HKEY: HMC.HKEY, Path: string): boolean;
        /**
         * 枚举键值
         * @param HKEY 根目录
         * @param Path 路径
         */
        enumRegistrKey(HKEY: HMC.HKEY, Path: string): string[];
        /**
         * 获取内容(二进制 Buffer)
         * @param HKEY 根目录
         * @param Path 路径
         * @param Key 键值
         */
        getRegistrBuffValue(HKEY: HMC.HKEY, Path: string, Key: string): Buffer | void;
        /**
         * 删除值
         * @param HKEY 根目录
         * @param Path 路径
         * @param Key 键值 (不允许空值)
         */
        removeStringRegValue(HKEY: HMC.HKEY, Path: string, Key: string): boolean;
        /**
         * 删除该目录下的所有内容（树遍历）
         * @param HKEY 根目录
         * @param Path 路径
         * @param Key 键值(不允许空值)
         */
        removeStringRegKeyWalk(HKEY: HMC.HKEY, Path: string, Key: string): boolean;
        /**
         * 向剪贴板写入文件路径
         * @param FilePaths 路径列表
         */
        setClipboardFilePaths(FilePaths: string[]): void
        /**
         * 获取剪贴板中的文件路径
         */
        getClipboardFilePaths(): string[]
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
        getClipboardSequenceNumber(): number;
        /**
         * 枚举剪贴板中的内容格式
         */
        enumClipboardFormats(): number[];
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
        unHookMouse(): void;
        /**
         * 移除键盘挂钩
         */
        unKeyboardHook(): void;
        /**
         * 启动鼠标动作挂钩
         */
        installHookMouse(): void;
        /**
         * 启动键盘动作挂钩
         */
        installKeyboardHook(): void;
        /**
         * 获取已经记录了的低级鼠标动作数据 出于性能优化使用了(文本数组)
         */
        getKeyboardNextSession(): `${number}|${0 | 1}`[] | undefined
        /**
         * 获取已经记录了的低级键盘动作数据 出于性能优化使用了(文本数组)
         */
        getMouseNextSession(): `${number}|${number}|${0 | 1}`[] | undefined
        /**
         * 鼠标挂钩是否已经启用
         */
        isStartHookMouse(): boolean;
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
        getProcessThreadList(ProcessID: number, returnDetail: true): HMC.THREADENTRY32[];
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
         * 获取进程的主进程
         * @param ProcessID 
         */
        getProcessParentProcessID(ProcessID: number): number | null | void;
        /**
         * 内联 启动枚举进程快照
         */
        enumAllProcess(): number;
        /**
         * 内联 枚举进程快照结果查询
         * @param enumID 枚举id
         */
        enumAllProcessPolling(enumID: number): Array<HMC.PROCESSENTRY | void> | void;
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
        /**
         * 截屏指定的宽高坐标 并将其存储写入为文件 
         * @param FilePath 文件路径
         * @param x 从左边的哪里开始 为空为0
         * @param y 从顶部的哪里开始 为空为0
         * @param width 宽度
         * @param height 高度
         */
        captureBmpToFile(FilePath: string, x: number | null | 0, y: number | null | 0, width: number | null | 0, height: number | null | 0): void;
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
         * 获取占用指定TCP的进程id
         * @param Port 
         */
        getTCPPortProcessID(Port: number): ProcessID | null;
        /**
         * 添加环境变量
         * @param key 
         * @param data 
         */
        putenv(key: string, data: string): void;
        /**
         * 获取占用指定UDP的进程id
         * @param Port 
         */
        getUDPPortProcessID(Port: number): ProcessID | null;
        /**
         * 获取指定的变量环境
         * @param key 
         */
        getenv(key: string): string;
        /**
         * 获取变量环境
         */
        getAllEnv(): { [key: string]: string };

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

    export type SystemDecoder = chcpList[SystemDecoderKey]
}

export const ref = {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str: any) {
        return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
    },
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool: any) {
        return bool ? true : false;
    },
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str: any) {
        return String(Str || "");
    },
    /**
     * 格式化数字为int(强制)
     * @param Num
     * @returns
     */
    int(Num: any): number {
        if (!Num) return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num?.valueOf();
        }
        // 取整
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num)) return Num;
        // true == 1
        if (Num && typeof Num == "boolean") Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean") Num = 0;
        if (Num >= Infinity) {
            Num = 999999999999999;
        }
        if (Num <= -Infinity) {
            Num = -999999999999999;
        }
        return Num;
    },
    /**
     * 文本数组
     * @param array 
     * @returns 
     */
    stringArray(array: Set<any> | Array<any>) {
        let dataList: string[] = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(this.string(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(this.string(cout));
            }
        }
        return dataList;
    },
    /**
     * 文本数组
     * @param array 
     * @returns 
     */
    intArray(array: Set<any> | Array<any>) {
        let dataList: number[] = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(this.int(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(this.int(cout));
            }
        }
        return dataList;
    },
    /**
     * 格式化命令行内容
     */
    formatCmd(cmd: string): string[] {
        return argvSplit(this.string(cmd));
    },
    /**
     * 将命令行内容组转为cmd文本
     * @param argv 
     */
    formatArgv(...argv: Array<any>[] | any[]): string {
        let argvs: string[] = [];
        let argvsResult: string[] = [];

        // 获取
        for (let index = 0; index < argv.length; index++) {
            const cout = argv[index];
            if (Array.isArray(cout)) {
                for (let cout_index = 0; cout_index < cout.length; cout_index++) {
                    const cout2 = cout[cout_index];
                    argvs.push(this.string(cout2));
                }
                continue;
            }
            argvs.push(this.string(cout));
        }

        // 处理
        for (let index = 0; index < argvs.length; index++) {
            let cout = argvs[index];
            if (!cout) continue;
            if (cout.match(/['"]/)) {
                cout = cout.replace(/(\\)?["']/g, "\\$0");
            }
            if (cout.match(" ")) {
                cout = `"${cout}"`;
            }
            if (cout.match(/[\n\r]/)) {
                cout = cout.replace(/(\n|\r|\r\n)/g, "$0^");
            }
            argvsResult.push(cout);
        }
        return argvsResult.join(" ");
    },
    /**注册表根目录 */

    HKEY: Hkey,
    /**
     * 拼合buff片段
     * @param buffList 
     * @returns 
     */
    concatBuff(buffList: Buffer[]): Buffer {
        let buffSize = 0;
        for (let index = 0; index < buffList.length; index++) {
            const buff = buffList[index];
            buffSize = buffSize + buff.byteLength;
        }
        let ResponseData = Buffer.concat([...buffList], buffSize);
        return ResponseData;
    },
    /**
     * 键盘值格式化为键值
     * @param key 键值/键
     * @returns 
     */
    vkKey: vkKey
};

/**
 * 获取窗口的标题
 * @returns
 */
function getDefaultTitele(): string {
    try {
        return globalThis.document.title;
    } catch (error) {
        return (
            native.lookHandleGetTitle(native.getProcessHandle(process.pid) || 0) ||
            native.getProcessName(process.pid) ||
            process.title
        );
    }

}

/**
 * 直达路径解析
 * @param Path 全路径(直达路径)
 * @param atkey 是否将最后一个值解释为键
 * @returns
 */
export function analysisDirectPath(Path: string, atkey?: boolean): string[] {
    let directPath = [];
    directPath.push(...Path.split(new RegExp(Object.keys(Hkey).join("|"))));
    if (directPath.length < 2) {
        return [];
    }
    directPath[1] = directPath[1].replace(/[\\\/]+/g, "\\");
    if (atkey) {
        let paths = directPath[1].split(/[\\]/g);
        if (paths.length) {
            let popData = paths.pop();
            popData && directPath.push(popData);
            directPath.unshift(...paths);
        }
    }
    return directPath;
}

/**
 * 获取系统shell默认编码
 * @returns 
 */
export function systemChcp() {
    let result = { code: 437 as HMC.SystemDecoderKey, chcp: chcpList[437] as HMC.SystemDecoder };
    return new Promise<{
        chcp: HMC.SystemDecoder,
        code: HMC.SystemDecoderKey
    }>(resolve => {
        child_process.execFile("chcp", function (err, data) {
            if (!data || err) return resolve(result);
            let sy_Chcp = data.match(/^.+?(\d+)[\r\n]+$/)
            if (sy_Chcp && chcpList[Number(sy_Chcp[1])]) {
                result.chcp = chcpList[Number(sy_Chcp[1])];
                result.code = Number(sy_Chcp[1]) as HMC.SystemDecoderKey;
                resolve(result);
            }
            resolve(result);
        });
    });
}

/**
 * 设置窗口位置大小
 * @param Handle 句柄
 * @param x (right) 从屏幕右边到所在位置得像素数
 * @param y (top) 从屏幕顶部边到所在位置得像素数
 * @param width 窗口宽度
 * @param height 窗口高度
 * @time 0.0068359375 ms
 * @returns 布尔
 */
export function setWindowMode(HWND: HWND | number, x: number | null | 0 | HMC.RECT_CONFIG, y?: number | null | 0, width?: number | null | 0, height?: number | null | 0): boolean {
    if (!ref.int(HWND)) return false;
    if (x && typeof x == "object") {
        let SetWindowRect = x;
        SetWindowRect.y = SetWindowRect.top
            ? SetWindowRect.top
            : SetWindowRect.y || 0;
        SetWindowRect.x = SetWindowRect.right
            ? SetWindowRect.right
            : SetWindowRect.x || 0;
        if (SetWindowRect.x) x = SetWindowRect.x;
        if (SetWindowRect.y) y = SetWindowRect.y;
        if (SetWindowRect.width) width = SetWindowRect.width;
        if (SetWindowRect.height) height = SetWindowRect.height;
    }
    if (!x) x = 0;
    if (!y) x = 0;
    if (!width) width = 0;
    if (!height) height = 0;
    return native.setWindowMode(
        ref.int(HWND),
        ref.int(x),
        ref.int(y),
        ref.int(width),
        ref.int(height)
    );
}

/**
 * 判断输入的注册表路径是否合法
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 */
function has_reg_args(HKEY: HMC.HKEY, Path: string, funName: string) {
    let hasHKEY = new RegExp(`^${Object.keys(Hkey).join("|")}$`).exec(HKEY);
    if (!hasHKEY || !Path) {
        throw new Error(`
        <fun> ${funName}  
        argument size 2 or 3
        HKEY : ${Object.keys(Hkey)}
        Path : string
        key ?: string  or "" or undefined
        `);
    }
}

/**
 * 判断注册表中是否有该键值
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06591796875 ms
 * @returns
 */
export function hasRegistrKey(HKEY: HMC.HKEY, Path: string, key: string): boolean {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "hasRegistrKey");
    return native.hasRegistrKey(
        HKEY,
        ref.string(Path)
            .split(/[\\\/]+/g)
            .join("\\"),
        ref.string(key)
    );
}

/**
  * 设置键值对内容(64位数字)
  * @param HKEY 根路径
  * @param Path 路径
  * @param key 键
  * @param Qword (64位数字)
  * @returns 
  */
export function setRegistrQword(HKEY: HMC.HKEY, Path: string, key: string, Qword: bigint | number): boolean {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "hasRegistrKey");
    if (!Qword) Qword = BigInt(0);
    return native.setRegistrQword(HKEY, ref.string(Path), ref.string(key), BigInt(Qword));
}

/**
 * 设置键值对内容(32位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @param Qword (32位数字)
 * @returns 
 */
export function setRegistrDword(HKEY: HMC.HKEY, Path: string, key: string, Dword: number): boolean {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "hasRegistrKey");
    return native.setRegistrDword(HKEY, ref.string(Path), ref.string(key), ref.int(Dword));
}

/**
 * 获取内容(64位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06787109375 ms
 * @returns
 */
export function getRegistrQword(HKEY: HMC.HKEY, Path: string, key: string) {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "getRegistrQword");
    return native.getRegistrQword(
        HKEY,
        ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"),
        ref.string(key)
    );
}

/**
 * 获取内容(64位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06787109375 ms
 * @returns
 */
export function getRegistrDword(HKEY: HMC.HKEY, Path: string, key: string) {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "getRegistrDword");
    return native.getRegistrDword(
        HKEY,
        ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"),
        ref.string(key)
    );
}

/**
 * 获取内容(二进制 Buffer)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06787109375 ms
 * @returns
 */
export function getRegistrBuffValue(HKEY: HMC.HKEY, Path: string, key: string) {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "getRegistrBuffValue");
    return native.getRegistrBuffValue(
        HKEY,
        ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"),
        ref.string(key)
    );
}

/**
 * 枚举键值
 * @param HKEY 根路径
 * @param Path 路径
 * @time 0.06689453125 ms
 * @returns
 */
export function enumRegistrKey(HKEY: HMC.HKEY, Path: string) {
    has_reg_args(HKEY, Path, "createPathRegistr");
    let enumKeyList: Set<string> = new Set();
    let NatenumKey = native.enumRegistrKey(
        HKEY,
        ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\")
    );
    for (let index = 0; index < NatenumKey.length; index++) {
        const key = NatenumKey[index];
        enumKeyList.add(key)
    }
    return [...enumKeyList];
}

/**
 * 将当前的路径的注册表值转表
 * @param HKEY
 * @param Path
 */
export function listRegistrPath(HKEY: HMC.HKEY, Path: string) {
    let enumRegistrKeys = enumRegistrKey(HKEY, Path);
    enumRegistrKeys.unshift("");
    let data: { "": string | Buffer;[key: string]: string | Buffer } = {
        "": "",
    };
    for (let i = 0; i < enumRegistrKeys.length; i++) {
        data[enumRegistrKeys[i]] = getStringRegKey(
            HKEY,
            Path,
            enumRegistrKeys[i]
        );
    }
    return data;
}

/**
 * 判断该键值是否存在子项
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 */
export function isRegistrTreeKey(HKEY: HMC.HKEY, Path: string, key?: string) {
    return !!enumRegistrKey(HKEY, Path + (!key ? "" : "\\" + key)).length
}

/**
 * 获取内容(文本)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.108ms
 * @returns
 */
export function getStringRegKey(HKEY: HMC.HKEY, Path: string, key?: string) {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "getStringRegKey");
    return native.getStringRegKey(
        HKEY,
        ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"),
        ref.string(key)
    );
}

/**
 * 打开一个注册表路径并返回一些实用方法
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export function openRegKey(HKEY: HMC.HKEY, Path: string, key?: string) {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "openRegKey");
    return {
        /**
         * 获取全路径
         */
        get path() {
            return HKEY.concat("\\", Path, "\\", key || "");
        },
        /**
         * 设置一个值
         * @param data 数据
         */
        set(data: string) {
            return native.setRegistrKey(HKEY, Path, key || "", data);
        },
        /**
         * 获取内容
         * @returns
         */
        get() {
            return native.getStringRegKey(HKEY, Path, key || "");
        },
        /**
         * 获取该内容并将其视为二进制缓冲区
         * @returns 二进制缓冲区
         */
        getBuff(): Buffer {
            return (
                native.getRegistrBuffValue(HKEY, Path, key || "") || Buffer.alloc(0)
            );
        },
        /**
         * 获取该内容并将其视为数字
         * @returns 数字
         */
        getNumber(): number {
            return Number(native.getStringRegKey(HKEY, Path, key || ""));
        },
        /**
         * 枚举当前路径下的键
         * @returns 键 数组
         */
        keys() {
            return enumRegistrKey(HKEY, Path);
        },
        /**
         * 将当前目录转为对象
         */
        list() {
            return listRegistrPath(HKEY, Path);
        },
    };
}

/**
 * 获取内容(数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.10888671875 ms
 * @returns
 */
export function getNumberRegKey(HKEY: HMC.HKEY, Path: string, key?: string): number {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "getNumberRegKey");
    return ref.int(
        native.getStringRegKey(
            HKEY,
            ref
                .string(Path)
                .split(/[\\\/]+/g)
                .join("\\"),
            ref.string(key)
        )
    );
}

/**
 * 删除键 (文件夹)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.076904296875 ms
 * @returns
 */
export function removeStringRegKey(HKEY: HMC.HKEY, Path: string, key?: string) {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "removeStringRegKey");
    return native.removeStringRegKey(
        HKEY,
        ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"),
        ref.string(key)
    );
}

/**
 * 删除该目录下的所有内容（树遍历）
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns 
 */
export function removeStringRegKeyWalk(HKEY: HMC.HKEY, Path: string, key?: string) {
    if (!key) {
        let paths = ref
            .string(Path)
            .split(/[\\\/]/g);
        key = paths.pop();
        if (!key) throw new Error("Invalid key because it is empty");
        Path = paths.join("\\");
    }
    has_reg_args(HKEY, Path, "removeStringRegKeyWalk");
    return native.removeStringRegKeyWalk(
        HKEY,
        ref
            .string(Path)
            .split(/[\\\/]+/g)
            .join("\\"),
        ref.string(key)
    );
}

/**
* 删除该目录下的所有内容（树遍历）
* @param HKEY 根路径
* @param Path 路径
* @param key 键
* @returns 
*/
export function removeStringTree(HKEY: HMC.HKEY, Path: string, key: string) {
    return removeStringRegKeyWalk(HKEY, Path, key);
}

/**
 * 删除该键值
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns 
 */
export function removeStringRegValue(HKEY: HMC.HKEY, Path: string, key?: string) {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "removeStringRegValue");
    return native.removeStringRegValue(
        HKEY,
        ref
            .string(Path)
            .split(/[\\\/]/g)
            .join("\\"),
        ref.string(key)
    );
}

/**
 * 设置键值对
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @param Value 数据
 * @time 2.02392578125 ms
 * @returns
 */
export function setRegistrKey(HKEY: HMC.HKEY, Path: string, key: string, Value: string) {
    if (!key) key = "";
    has_reg_args(HKEY, Path, "setRegistrKey");
    return native.setRegistrKey(
        HKEY,
        ref
            .string(Path)
            .split(/[\\\/]/g)
            .join("\\"),
        ref.string(key),
        ref.string(Value)
    );
}

/**
 * 创建新的路径
 * @param HKEY 根路径
 * @param Path 路径
 * @time 2.02392578125 ms
 * @returns
 */
export function createPathRegistr(HKEY: HMC.HKEY, Path: string) {
    has_reg_args(HKEY, Path, "createPathRegistr");
    return native.createPathRegistr(
        HKEY,
        ref
            .string(Path)
            .split(/[\\\/]/g)
            .join("\\")
    );
}

/**
  * 同 C++/C 的system
  * @returns 程序退出代码
  */
export function system(str: string) {
    return native.system(ref.string(str));
}

/**
 * 空闲的随机端口号
 * @returns 
 */
export function freePort(): Promise<number> {
    return new Promise((resolve, reject) => {
        let sock = net.createServer(function () { });
        sock.listen(0, () => {
            // @ts-expect-error
            resolve(Number(sock?.address()?.port as string));
            sock.close();
        });
    });
}
/**
 * 获取剪贴板中的文件列表
 * @returns 
 */
export function getClipboardFilePaths(): string[];
export function getClipboardFilePaths(at: number): string | undefined;
/**
 * 获取剪贴板中的文件列表
 * @returns 
 */
export function getClipboardFilePaths(at?: number): unknown {
    let paths = native.getClipboardFilePaths();
    if (typeof at === 'number') {
        if (at < 0) {
            return paths[paths.length + at];
        }
        return paths[at];
    }
    return paths
}

/**
 * 向剪贴板写入文件列表
 * @param FilePaths 
 */
export function setClipboardFilePaths(...FilePaths: string[] | [string[]]) {
    let filePaths: string[] = [];
    for (let index = 0; index < FilePaths.length; index++) {
        const FilePath = FilePaths[index];
        if (typeof FilePath !== "string") {
            for (let indexc = 0; indexc < FilePaths.length; indexc++) {
                filePaths.push(ref.string(FilePaths[indexc]));
            }
        } else {
            filePaths.push(ref.string(FilePath));
        }
    }
    return native.setClipboardFilePaths(filePaths);
}

/**
 * 获取所有usb驱动器(不包含HUD)
 * @returns 
 */
export function getUsbDevsInfo() {
    return native.getUsbDevsInfo();
}

/**
 * 枚举句柄的子窗口
 * @param Handle 句柄
 * @returns 
 */
export function enumChildWindows(Handle: number | HWND) {
    return native.enumChildWindows(ref.int(Handle));
}

/**
 * 隐藏当前控制台窗口(node)
 */
export function hideConsole() {
    if (!$_thenConsole) {
        $_thenConsole = getProcessHandle(process.pid);
    }
    if (!$_thenConsole) return false;
    return $_thenConsole?.hide() || false;
}

/**
 * 显示当前控制台窗口(node)
 */
export function showConsole() {
    if (!$_thenConsole) {
        $_thenConsole = getProcessHandle(process.pid);
    }
    if (!$_thenConsole) return false;
    return $_thenConsole?.show() || false;
}

/**
 * 获取当前控制台窗口的句柄(node)
 * @returns 
 */
export function getConsoleHandle() {
    if (!$_thenConsole) {
        $_thenConsole = getProcessHandle(process.pid);
    }
    return $_thenConsole;
}

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
export function deleteFile(Path: string, Recycle?: boolean, isShow?: boolean) {
    return native.deleteFile(ref.path(Path),
        typeof Recycle == "boolean" ? ref.bool(Recycle) : true,
        typeof isShow == "boolean" ? ref.bool(isShow) : false,
    )
}

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
export const trash = deleteFile;

/**
 * 获取当前剪贴板内容的id(如果被重新写入了该id会变动)
 * @returns 
 */
export function getClipboardSequenceNumber(): number {
    return native.getClipboardSequenceNumber()
}

/**
 * 当剪贴板内容变更后发生回调
 * @param CallBack 回调函数
 * @param nextAwaitMs 每次判断内容变化用时 默认 `150` ms
 * @returns 
 */
export function watchClipboard(CallBack: () => void, nextAwaitMs?: number) {
    let NextAwaitMs = nextAwaitMs || 150;
    let Next = true;
    let oidClipboardSequenceNumber = getClipboardSequenceNumber();
    (async function () {
        while (Next) {
            await Sleep(NextAwaitMs);
            let clipboardSequenceNumber = getClipboardSequenceNumber();
            if (oidClipboardSequenceNumber !== clipboardSequenceNumber) {
                if (CallBack) CallBack();
            }
            oidClipboardSequenceNumber = clipboardSequenceNumber;
        }
    })();
    return {
        /**
         * 取消继续监听
         */
        unwatcher() {
            Next = false;
        },
        /**
         * 每次判断内容变化用时 默认 `150` ms
         * @param nextAwaitMs 
         */
        setNextAwaitMs(nextAwaitMs: number) {
            NextAwaitMs = ref.int(nextAwaitMs) || 150;
        }
    }
}

/**
  * 当驱动器添加或者移除后发生回调
  * @param CallBack 回调函数
  * @param nextAwaitMs 每次判断内容变化用时 默认 `800` ms
  * @param watchType 监听的设备类型 默认 `["HUB","drive"]`
  * @returns 
  */
export function watchUSB(CallBack: (env: "add" | "remove" | "start", id: string) => void, nextAwaitMs?: number, watchType?: "hub" | "drive" | Array<"hub" | "drive">) {
    let NextAwaitMs = nextAwaitMs || 800;
    let Next = true;
    let OID_ID_LIST: Set<string> = new Set();
    let start = true;
    if (typeof watchType == "string") watchType = [watchType];
    (async function () {
        while (Next) {
            await Sleep(NextAwaitMs);
            let GET_ID_List = new Set(watchType ? [
                ...(watchType.includes("hub") ? native.getHidUsbIdList() : []),
                ...(watchType.includes("drive") ? native.getUsbDevsInfo() : []),
            ] : [...native.getHidUsbIdList(), ...native.getUsbDevsInfo()]);
            if (start) {
                for (const NEW_ID of GET_ID_List) {
                    OID_ID_LIST.add(NEW_ID);
                    CallBack && CallBack("start", NEW_ID);
                }
                start = false;
            }
            let GET_ID_List_NEW = [...GET_ID_List];

            for (const OID_ID of OID_ID_LIST) {
                if (!GET_ID_List.has(OID_ID)) {
                    CallBack && CallBack("remove", OID_ID);
                }
            }

            for (const NEW_ID of GET_ID_List) {
                if (!OID_ID_LIST.has(NEW_ID)) {
                    CallBack && CallBack("add", NEW_ID);
                }
            }

            OID_ID_LIST.clear();
            for (let index = 0; index < GET_ID_List_NEW.length; index++) {
                const GET_ID = GET_ID_List_NEW[index];
                OID_ID_LIST.add(GET_ID);
            }
        }
    })();
    return {
        get idList() {
            return OID_ID_LIST
        },
        /**
         * 取消继续监听
         */
        unwatcher() {
            Next = false;
        },
        /**
         * 每次判断内容变化用时 默认 `800` ms
         * @param nextAwaitMs 
         */
        setNextAwaitMs(nextAwaitMs: number) {
            NextAwaitMs = ref.int(nextAwaitMs) || 800;
        }
    }
}

/**
 * 获取所有屏幕
 * @returns 
 */
export function getDeviceCapsAll(): HMC.cRECT[] {
    return native.getDeviceCapsAll();
}

/**
 * 判断句柄的窗口是否在所有窗口的范围中(无论他是否被其他窗口挡住)
 * @param Handle 
 */
export function isInMonitorWindow(Handle: number | HWND): boolean {
    return native.isInMonitorWindow(ref.int(Handle));
}

/**
 * 判断句柄的窗口是否在鼠标所在的窗口
 * @param Handle 
 */
export function isMouseMonitorWindow(Handle: number): boolean {
    return native.isMouseMonitorWindow(ref.int(Handle));
}

/**
 * 获取鼠标所在的屏幕信息
 */
export function getCurrentMonitorRect(): HMC.cRECT {
    return native.getCurrentMonitorRect();
}

/**
 * 当前电脑存在几个屏幕
 */
export function getSystemMetricsLen(): number {
    return native.getSystemMetricsLen();
}

/**
 * 方法用于显示带有一条指定消息和一个 确认 按钮的警告框
 * @param Message 消息
 * @param Title 标题
 * @time any ms
 * @returns
 */
export function alert(Message: string, Title?: string) {
    return native.alert(
        Message,
        typeof Title != "string" ? getDefaultTitele() : Title
    );
}

/**
 * 方法用于显示带有一条指定消息和 确认 和取消  的按钮的消息框
 * @param Message 消息
 * @param Title 标题
 * @time any ms
 * @returns
 */
export function confirm(Message: string, Title?: string) {
    return native.confirm(
        Message,
        typeof Title != "string" ? getDefaultTitele() : Title
    );
}

/**
 * 方法用于显示带有一条指定消息和一个 确认 按钮的和❌（X）的消息框。
 * @param Message 消息
 * @param Title 标题
 * @time any ms
 * @returns
 */
export function MessageStop(Message: string, Title?: string) {
    return native.MessageStop(
        Message,
        typeof Title != "string" ? getDefaultTitele() : Title
    );
}

/**
 * 方法用于显示带有一条指定消息和一个 确认 按钮的错误框 附带有❗ 感叹号。
 * @param Message 消息
 * @param Title 标题
 * @time any ms
 * @returns
 */
export function MessageError(Message: string, Title?: string) {
    return native.MessageError(
        Message,
        typeof Title != "string" ? getDefaultTitele() : Title
    );
}

/**
 * 获取所有窗口句柄并返回一个快速操作的句柄类 可以快速操作窗口
 * @time 0.657958984375 ms 
 * @example ```javascript
 * const getAllWindows = hmc.getAllWindowsHandle();
 * console.log({
 * title:getAllWindows[0].title,
 * handle : getAllWindows[0]+0,
 * rect:getAllWindows[0].rect,
 * })
//  log=>
//  {
//   "title": "Program Manager",
//   "handle": 65826,
//   "rect": {
//       "top": 0,
//       "bottom": 1080,
//       "left": 0,
//       "right": 1920,
//       "y": 0,
//       "x": 0,
//       "width": 1920,
//       "height": 1080
//   }
//  }
 *  ```
 * @returns 
 */
export function getAllWindowsHandle(isWindows: boolean) {
    let data = [];
    let AllWindowsHandle = native.getAllWindowsHandle(isWindows || false);
    for (let index = 0; index < AllWindowsHandle.length; index++) {
        const element = AllWindowsHandle[index];
        // const mydata = {
        //   _Handle:null as null | HWND ,
        //   Handle:element,
        //   get handle(){
        //     if(!mydata._Handle) mydata._Handle=new HWND(mydata.Handle);
        //     return mydata._Handle
        //   }
        // }
        // data.push(mydata);
        data.push(new HWND(element));
    }
    return data;
}

/**
 * 进程监听 当该进程被关闭的时候执行回调
 * @param ProcessID 进程id
 * @param callback 回调函数
 * @param awaitMs 每次执行的延迟事件
 * @default awaitMs 500
 * @example ```javascript
 * hmc_win32.processWatchdog(4836,()=>console.log("进程已经退出。。。"));
 * hmc_win32.sleep(2836);
 * hmc_win32.killProcess(4836);
 * ```
 * @returns 包含一个quit函数(结束监听)的异步或对象
 */
export function processWatchdog(ProcessID: number, callback?: (() => void) | number, awaitMs?: number) {
    let quit = false;
    if (!callback) {
        let Prom: Promise<void> & { quit: () => void } = new Promise(
            async (resolve, reject) => {
                while (true) {
                    if (quit) break;
                    await Sleep(awaitMs || 500);
                    if (!hasProcess(ref.int(ProcessID))) {
                        resolve(void 0);
                        break;
                    }
                }
            }
        ) as Promise<void> & { quit: () => void };
        Prom.quit = function () {
            quit = true;
        };
        return Prom;
    }
    (async () => {
        while (true) {
            await Sleep(awaitMs || 500);
            if (!hasProcess(ref.int(ProcessID))) {
                typeof callback == "function" && callback();
                break;
            }
        }
    })();
    return {
        quit: function () {
            quit = true;
        },
    };
}

/**
 * 监听鼠标所在的窗口的句柄
 * @param callback 回调函数
 * @param awaitMs 每次延迟的事件 
 * @default awaitMs 350
 * @example ```javascript
 * let WatchPoint = hmc_win32.WatchWindowPoint(function(newPoint,oidPoint,HWND){
  console.log(newPoint,oidPoint,HWND,HWND.title)
  // quit 结束
  WatchPoint.quit();
  });
 * ```
 * @returns 一个可以控制结束和延迟事件的对象
 */
export function WatchWindowPoint(callback: (newPoint: number, oidPoint: number, HWND: HWND) => void, awaitMs?: number) {
    let quit = false;
    let oidPoint = native.getPointWindow() || 0;
    (async () => {
        if (typeof callback !== "function") return;
        while (true) {
            if (quit) return;
            let newPoint = native.getPointWindow() || 0;
            if (newPoint)
                if (newPoint != oidPoint) {
                    if (callback) {
                        callback(
                            ref.int(newPoint),
                            ref.int(oidPoint) || 0,
                            new HWND(ref.int(newPoint))
                        );
                        oidPoint = newPoint;
                    }
                }
            await Sleep(awaitMs || 350);
        }
    })();
    return {
        /**结束监听 */
        quit: function () {
            quit = true;
        },
        /**设置每次延迟事件 */
        setAwaitMs(ms: number) {
            awaitMs = ms;
        },
    };
}

/**
* 监听焦点窗口变化并返回句柄
* @param callback 回调函数
* @param awaitMs 每次延迟的事件 
* @default awaitMs 350
* @example ```javascript
* let WatchForeg = hmc_win32.WatchWindowForeground(function(newForeg,oidForeg,HWND){
  console.log(newForeg,oidForeg,HWND,HWND.title)
  // quit 结束
  WatchForeg.quit();
  });
 * ```
* @returns 一个可以控制结束和延迟事件的对象
*/
export function WatchWindowForeground(callback: (newForeg: number, oidForeg: number, HWND: HWND) => void, awaitMs?: number) {
    let quit = false;
    let oidForeg = getForegroundWindow();
    (async () => {
        if (typeof callback !== "function") return;
        while (true) {
            if (quit) return;
            let newForeg = getForegroundWindow();
            if (newForeg)
                if (ref.int(newForeg) != ref.int(oidForeg)) {
                    if (callback) {
                        callback(
                            ref.int(newForeg),
                            ref.int(oidForeg) || 0,
                            new HWND(ref.int(newForeg))
                        );
                        oidForeg = newForeg;
                    }
                }
            await Sleep(awaitMs || 350);
        }
    })();
    return {
        /**结束监听 */
        quit: function () {
            quit = true;
        },
        /**设置每次延迟事件 */
        setAwaitMs(ms: number) {
            awaitMs = ms;
        },
    };
}

/**
 * 打开一个程序
 * @param AppPath 程序路径
 * @param Command 命令行
 * @param cwd 工作路径
 * @param hide 隐藏窗口
 * @param UAC 提升到管理员权限
 * @default
 * - Command ""
 * - cwd AppPath DirPath
 * - hide false
 * - UAC false
 * @returns
 */
export function openApp(AppPath: string, Command?: string | string[], cwd?: string, hide?: boolean, UAC?: boolean) {
    return native.openApp(
        ref.string(AppPath),
        ref.string(
            Array.isArray(Command) ? ref.formatArgv(Command) : Command
        ) || "",
        ref.string(cwd || path.parse(AppPath || "").dir || process.cwd()),
        ref.bool(hide || false),
        ref.bool(UAC || false)
    );
}

/**
 * 获取该名称 /正则匹配的进程列表
 * @param Name 
 * @returns 
 */
export function getProcessNameList(...Name: Array<string | RegExp>) {
    let resultList: { pid: number; name: string }[] = [];
    let ProcessList = native.getProcessList();
    for (let index = 0; index < ProcessList.length; index++) {
        const Process = ProcessList[index];
        const { pid, name } = Process;
        for (let NextNameIndex = 0; NextNameIndex < Name.length; NextNameIndex++) {
            const NextName = Name[NextNameIndex];
            if (typeof NextName === "string") {
                if (Process.name == NextName) {
                    resultList.push({ pid, name });
                }
            }
            if (NextName instanceof RegExp && NextName.test(name)) {
                resultList.push({ pid, name });
            }
        }
    }
    return resultList;
}

/**
* 获取该名称 /正则匹配的进程列表 带执行文件路径 慢20ms
* @param Name 
* @returns 
*/
export function getDetailsProcessNameList(...Name: Array<string | RegExp>) {
    let resultList: { pid: number; name: string, path: string }[] = [];
    let ProcessList = native.getDetailsProcessList();
    for (let index = 0; index < ProcessList.length; index++) {
        const Process = ProcessList[index];
        const { pid, name, path } = Process;
        for (let NextNameIndex = 0; NextNameIndex < Name.length; NextNameIndex++) {
            const NextName = Name[NextNameIndex];
            if (typeof NextName === "string") {
                if (Process.name == NextName) {
                    resultList.push({ pid, name, path });
                }
            }
            if (NextName instanceof RegExp && NextName.test(name)) {
                resultList.push({ pid, name, path });
            }
        }
    }
    return resultList;
}

/**
 * 结束该名称的进程
 * @param Name
 */
export function killProcessName(...Name: Array<string | RegExp>) {
    let resultList: { pid: number; kill: boolean; name: string }[] = [];
    let ProcessList = getProcessList();
    for (let index = 0; index < ProcessList.length; index++) {
        const Process = ProcessList[index];
        const { pid, name } = Process;
        for (
            let NextNameIndex = 0;
            NextNameIndex < Name.length;
            NextNameIndex++
        ) {
            const NextName = Name[NextNameIndex];
            if (typeof NextName === "string") {
                if (Process.name == NextName) {
                    killProcess(Process.pid);
                    resultList.push({
                        pid,
                        name,
                        get kill() {
                            return hasProcess(pid);
                        },
                    });
                }
            }
            if (NextName instanceof RegExp && NextName.test(name)) {
                killProcess(Process.pid);
                resultList.push({
                    pid,
                    name,
                    get kill() {
                        return hasProcess(pid);
                    },
                });
            }
        }
    }
    return resultList;
}

/**
 * 获取当前的焦点窗口
 * @returns 一个可以操作的伪数字类
 */
export function getForegroundWindow() {
    let Handle = native.getForegroundWindow();
    return Handle ? new HWND(Handle) : null;
}

/**
 * 获取句柄的主窗口
 * @returns 一个可以操作的伪数字类
 */
export function getMainWindow(Handle: number | HWND) {
    let Handles = native.getMainWindow(ref.int(Handle));
    return Handles ? new HWND(Handles) : null;
}

/**
 * 获取鼠标所在的窗口
 * @returns 一个可以操作的伪数字类
 */
export function getPointWindow() {
    let Handle = native.getPointWindow();
    return Handle ? new HWND(Handle) : null;
}

/**
 * 获取鼠标所在的窗口的主窗口
 * @returns 一个可以操作的伪数字类
 */
export function getPointWindowMain() {
    let Handle = native.getPointWindowMain();
    return Handle ? new HWND(Handle) : null;
}

/**
 * 获取进程的句柄
 * @param ProcessID
 * @returns
 */
export function getProcessHandle(ProcessID: number) {
    let Handles = native.getProcessHandle(ref.int(ProcessID));
    return Handles ? new HWND(Handles) : null;
}

/**
 * 阻止键盘和鼠标输入事件到达应用程序。
 */
export function SetBlockInput(Block: boolean) {
    return native.SetBlockInput(ref.bool(Block));
}

/**
 * 设置该窗口图标在状态栏可见性 (注意：XP 下激活窗口了会失效(但是有没有一种可能 xp运行不了node和electron))
 * @param Handle 句柄
 * @param Visible 可见性
 * @returns
 */
export function SetWindowInTaskbarVisible(Handle: number | HWND, Visible: boolean) {
    return native.SetWindowInTaskbarVisible(
        ref.int(Handle),
        ref.bool(Visible)
    );
}

/**
 * 获取句柄对应的进程id
 * @param Handle 句柄
 * @returns
 */
export function getHandleProcessID(Handle: number | HWND) {
    return native.getHandleProcessID(ref.int(Handle));
}

/** 获取窗口位置大小
 *  - 高|宽|坐标大于一万以上都是不可见的
 * **/
export function getWindowRect(Handle: number | HWND) {
    return native.getWindowRect(ref.int(Handle));
}

/**
 * 判断窗口是否禁用响应事件(鼠标键盘点击)
 * @param Handle
 * @returns
 */
export function isEnabled(Handle: number | HWND) {
    return native.isEnabled(ref.int(Handle));
}

/**
 * 判断句柄是否有效
 * @param Handle
 * @returns
 */
export function isHandle(Handle: number | HWND) {
    return native.isHandle(ref.int(Handle));
}

/**
 * 判断此句柄是否是正在活动中的窗口
 * @param Handle
 * @returns
 */
export function isHandleWindowVisible(Handle: number | HWND) {
    return native.isHandleWindowVisible(ref.int(Handle));
}

/**
 * 关闭此句柄对应的窗口
 * @param Handle
 * @returns
 */
export function lookHandleCloseWindow(Handle: number | HWND) {
    return native.lookHandleCloseWindow(ref.int(Handle));
}

/**
 * 获取此句柄的标题
 * @param Handle
 * @returns
 */
export function lookHandleGetTitle(Handle: number | HWND) {
    return native.lookHandleGetTitle(ref.int(Handle));
}

/**
 * 设置此句柄的标题
 * @param Handle
 * @param title
 * @returns
 */
export function lookHandleSetTitle(Handle: number | HWND, title: string) {
    return native.lookHandleSetTitle(
        ref.int(Handle),
        ref.string(title)
    );
}

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
export const setShowWindow = lookHandleShowWindow;

/**
 * 关闭此句柄对应的窗口
 * @param Handle
 * @returns
 */
export const setCloseWindow = lookHandleCloseWindow;

/**
 * 获取此句柄的标题
 * @param Handle
 * @returns
 */
export const getWindowTitle = lookHandleGetTitle;

/**
 * 设置此句柄的标题
 * @param Handle
 * @param title
 * @returns
 */
export const setWindowTitle = lookHandleSetTitle;

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
export function lookHandleShowWindow(Handle: number | HWND, SetShowType: 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11) {
    return native.lookHandleShowWindow(
        ref.int(Handle),
        ref.int(
            typeof SetShowType == "number" ? ref.int(SetShowType) : 5
        ) as 0
    );
}

/**
 * 设置窗口不透明度 0-255
 * @param Handle
 * @param Transparent 0-255
 * @returns
 */
export function setHandleTransparent(Handle: number | HWND, Transparent: number) {
    return native.setHandleTransparent(
        ref.int(Handle),
        ref.int(Transparent || 255)
    );
}

/**
 * 设置窗口是否支持响应事件(鼠标键盘点击)
 * @param Handle
 * @param Enabled
 * @returns
 */
export function setWindowEnabled(Handle: number | HWND, Enabled: boolean) {
    return native.setWindowEnabled(
        ref.int(Handle),
        ref.bool(Enabled)
    );
}

/**
 * 设置窗口焦点
 * @param Handle
 * @returns
 */
export function setWindowFocus(Handle: number | HWND) {
    return native.setWindowFocus(ref.int(Handle));
}

/**
 * 设置窗口顶设
 * @param Handle
 * @returns
 */
export function setWindowTop(Handle: number | HWND) {
    return native.setWindowTop(ref.int(Handle));
}

/**
 * 刷新该窗口
 * @param Handle
 * @returns
 */
export function updateWindow(Handle: number | HWND) {
    return native.updateWindow(ref.int(Handle));
}

/**
 * 窗口抖动
 * @param Handle
 * @returns
 */
export function windowJitter(Handle: number | HWND) {
    return native.windowJitter(ref.int(Handle));
}

/**
 * 判断窗口是否被顶设
 * @param Handle
 * @returns
 */
export function hasWindowTop(Handle: number | HWND) {
    return native.hasWindowTop(ref.int(Handle));
}

/**
 * 关闭该句柄窗口(可关闭托盘)(发送关闭消息)
 */
export function closedHandle(Handle: number | HWND) {
    return native.closedHandle(ref.int(Handle));
}

/**
 * 获取所有HidUsb设备（仅限HID设备)
 * @returns HidUsb设备数组
 */
export function getHidUsbList() {
    return native.getHidUsbList();
}

/**
 * 获取鼠标所在位置
 * @returns 鼠标所在位置
 */
export function getMetrics() {
    return native.getMetrics();
}

/**
 * 获取鼠标之前64个位置
 * @returns 之前64个位置
 */
export function getMouseMovePoints() {
    return native.getMouseMovePoints();
}

/**
 * 获取屏幕大小
 */
export function getDeviceCaps() {
    return native.getDeviceCaps();
}

/**禁用/启用系统键盘鼠标钩子
  * @param HOOK 是否启用系统键盘鼠标钩子
  !注意该功能很危险 主要用于自动化防止误操作 用户锁屏  禁止用于非法用途
  *手动解锁方式 Ctrl+Alt+Del   => esc
  !请注意 你需要确保你的解锁代码  运行没有任何错误或者有定时解锁
  否则有可能导致用户无法正常使用
  **/
export function SetSystemHOOK(HOOK: boolean) {
    return native.SetSystemHOOK(ref.bool(HOOK));
}

/**
 * 获取四大按钮(`alt`  `ctrl`  `win`  `shift` )是否按下
 * @returns
 */
export function getBasicKeys() {
    return native.getBasicKeys();
}

/**
 * 获取剪贴板文本
 * @returns 剪贴板文本
 */
export function getClipboardText() {
    return native.getClipboardText();
}

/**
 * 设置剪贴板文本
 * @param text 文本
 * @returns
 */
export function setClipboardText(text: string) {
    return native.setClipboardText(ref.string(text));
}

/**
 * 清空剪贴版
 * @returns 处理结果
 */
export function clearClipboard() {
    return native.clearClipboard();
}

/** 获取详细进程列表（慢20ms）**/
export function getDetailsProcessList() {
    return native.getDetailsProcessList();
}

/** 获取进程列表**/
export function getProcessList() {
    return native.getProcessList();
}

/**获取活动窗口的进程id */
export function getForegroundWindowProcessID() {
    return native.getForegroundWindowProcessID();
}

/**获取鼠标所在窗口的进程名 */
export function getPointWindowName() {
    return native.getPointWindowName();
}

/**获取鼠标所在窗口的进程id */
export function getPointWindowProcessId() {
    return native.getPointWindowProcessId();
}

/**
 * 获取进程名
 * @param ProcessID 进程id
 * @returns
 */
export function getProcessName(ProcessID: number) {
    return native.getProcessName(ref.int(ProcessID));
}

/**
 * 获取进程可执行文件位置
 * @param ProcessName 进程名
 * @returns 进程id
 */
export function getProcessidFilePath(ProcessID: number) {
    return native.getProcessidFilePath(ref.int(ProcessID));
}

/**
 * 获取快捷方式的信息
 * @param LnkPath 快捷方式路径
 * @returns
 */
export function getShortcutLink(LnkPath: string) {
    return native.getShortcutLink(ref.string(LnkPath));
}

/**系统空闲时间 */
export function getSystemIdleTime() {
    return native.getSystemIdleTime();
}

/**
 * 设置系统右键菜单 例如win自带的系统菜单就很丑还不能禁用  使用这个禁用
 * @param Handle 句柄
 * @param boolean 是否禁用
 * @returns
 */
export function getSystemMenu(Handle: number | HWND, boolean: boolean) {
    return native.getSystemMenu(ref.int(Handle), ref.bool(boolean));
}

/**获取托盘图标列表 */
export function getTrayList() {
    return native.getTrayList();
}

/**判断该按键是否被按下  https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getkeystate **/
export function hasKeyActivate(KeysEvent: number) {
    return native.hasKeyActivate(ref.int(KeysEvent));
}

/**
 * 判断进程id 是否存在
 * @param ProcessID 进程id
 * @returns
 */
export function hasProcess(...ProcessMatch: Array<number | string | Array<number | string>>): boolean {
    // 只有一个参数 而且是数字 直接打开句柄 不枚举
    if (ProcessMatch.length == 1) {
        return native.isProcess(ref.int(ProcessMatch[0]));
    }
    let _ProcessMatch: Array<number | string> = [];
    let isString = false;
    // 多个参数 压入缓冲数组
    for (let index = 0; index < ProcessMatch.length; index++) {
        const ProcessID = ProcessMatch[index];
        if (Array.isArray(ProcessID)) {
            for (let index = 0; index < ProcessID.length; index++) {
                if (typeof ProcessID[index] == "string") isString = true;
                _ProcessMatch.push(ProcessID[index]);
            }
        }
        if (typeof ProcessID == "string") {
            isString = true;
            _ProcessMatch.push(ProcessID);
        }
        if (typeof ProcessID == "number") _ProcessMatch.push(ProcessID);
    }
    // 开始处理  如果全是数字 就不枚举进程列表 因为直接打开句柄更快
    let ProcessList = isString ? getProcessList() : [];
    for (let index = 0; index < _ProcessMatch.length; index++) {
        if (!isString) {
            if (native.isProcess(ref.int(_ProcessMatch[index]))) return true;
        }
        for (let index = 0; index < ProcessList.length; index++) {
            const elp = ProcessList[index];
            if (elp.name === _ProcessMatch[index] || elp.pid === _ProcessMatch[index]) return true;
        }
    }
    return false;
}

/**
 * 当前程序是否拥有管理员权限
 * @returns
 */
export function isAdmin() {
    return native.isAdmin();
}

/**
 * 判断进程id 是否存在
 * @param ProcessID 进程id
 * @returns
 */
export function isProcess(ProcessID: number) {
    return native.isProcess(ref.int(ProcessID));
}

/**判断当前系统是否是64位 */
export function isSystemX64() {
    return native.isSystemX64();
}

/**
 * 结束该进程
 * @param ProcessID 
 * @returns 
 */
export function killProcess(ProcessID: number): boolean;
export function killProcess(ProcessID: string | RegExp): {
    pid: number;
    kill: boolean;
    name: string;
}[];
export function killProcess(ProcessID: number | string | RegExp) {
    if (typeof ProcessID == "string" || typeof ProcessID == "object") {
        return killProcessName(ProcessID)
    }
    return native.killProcess(ref.int(ProcessID));
}

/**
 * 左键点击
 * @param ms 延迟
 * @returns 
 */
export function leftClick(ms?: number) {
    return native.leftClick(ms);
}

/**
 * 消息窗口(调用 win-api)
 * @param message 消息内容
 * @param title 标题
 * @param UINT_String 显示窗口类型 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
 * @description 衍生api(已预设): `confirm`  `alert` `MessageError` `MessageStop`
 * @returns 
 */
export function messageBox(message: string, title: string, MB_UINT: HMC.MB_UINT) {
    return native.messageBox(ref.string(message), ref.string(title), ref.string(MB_UINT) as HMC.MB_UINT);
}

/**自定义鼠标事件 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mouse_event **/
export function mouse(mouse_event: HMC.mouse_event, ms?: number) {
    if (typeof mouse_event == "number") {
        mouse_event = ref.int(mouse_event) as 1;
    } else {
        mouse_event = ref.string(mouse_event) as 'MOUSEEVENTF_RIGHTDOWN';
    }
    return native.mouse.apply(undefined, ms ? [mouse_event] : [mouse_event, ms]);
}

/**
 * 在资源管理器中显示并选中该文件
 * @param Path 路径
 * @returns 
 */
export function openExternal(Path: string) {
    return native.openExternal(Path);
}

/**
 * 用默认应用打开该 （文件/文件夹）
 * @param Path 文件路径
 * @returns 
 */
export function openPath(Path: string) {
    return native.openPath(Path);
}

/**
 * 用默认浏览器打开这条url
 * @param URL url
 * @returns 
 */
export function openURL(URL: string) {
    return native.openURL(ref.string(URL));
}

/**
 * 电源控制
 */
export const powerControl = (() => {
    function _PowerControl(Set:
        /**关机 */
        1001 |
        /**重启 */
        1002 |
        /**注销 */
        1003 |
        /**锁定 */
        1005) {
        native.powerControl(Set)
    }
    /**关机 */
    _PowerControl[1001] = () => { native.powerControl(1001) }
    /**重启 */
    _PowerControl[1002] = () => { native.powerControl(1002) }
    /**注销 */
    _PowerControl[1003] = () => { native.powerControl(1003) }
    /**锁定 */
    _PowerControl[1005] = () => { native.powerControl(1005) }
    /**关机 */
    _PowerControl.shutDown = () => { native.powerControl(1001) }
    /**重启 */
    _PowerControl.restart = () => { native.powerControl(1002) }
    /**注销 */
    _PowerControl.cancellation = () => { native.powerControl(1003) }
    /**锁定 */
    _PowerControl.lock = () => { native.powerControl(1005) }

    return _PowerControl;
})();

/**
 * 右键点击
 * @param ms 延迟
 * @returns 
 */
export function rightClick(ms?: number) {
    return native.rightClick(ms);
}

/**
 * 设置鼠标位置
 * @param x 左边开始的像素数坐标
 * @param y 上方到下方的像素数坐标
 * @returns 
 */
export function setCursorPos(x: number, y: number) {
    return native.setCursorPos(ref.int(x), ref.int(y));
}

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
export function setShortcutLink(LnkPath: string, FilePath: string, work_dir: string, desc: string, args: string | string[], iShowCmd: number, icon: string, iconIndex: number): boolean;
export function setShortcutLink(LnkPath: string, FilePath: string, work_dir?: string, desc?: string, args?: string | string[], iShowCmd?: number): boolean;
export function setShortcutLink(LnkPath: string, FilePath: string): boolean;
export function setShortcutLink(...args: unknown[]): boolean {
    if (args.length < 2) throw new Error("not LnkPath and FilePath arguments");
    // LnkPath
    args[0] = ref.string(args[0] || "");
    // FilePath
    args[1] = ref.string(args[1] || "");
    // work_dir
    args[2] = ref.string(args[2] || "");
    // desc
    args[3] = ref.string(args[3] || "");
    // args
    if (Array.isArray(args[4])) {
        args[4] = ref.formatArgv(args[4]);
    }
    args[4] = ref.string(args[4] || "");
    // iShowCmd
    if (args.length > 5) {
        args[5] = ref.int(args[5] || 0);
    }
    // icon
    if (args.length > 6) {
        args[6] = ref.string(args[6] || "");
    }
    // iconIndex
    if (args.length > 7) {
        args[7] = ref.int(args[7] || 0);
    }
    return native.setShortcutLink(...args as [string, string, string]);
}

/**
 * 创建文件软链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns 
 */
export function createSymlink(LinkPath: string, sourcePath: string) {
    return native.createSymlink(ref.string(LinkPath), ref.string(sourcePath))
}

/**
 * 创建文件夹软链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns 
 */
export function createDirSymlink(LinkPath: string, sourcePath: string) {
    return native.createSymlink(ref.string(LinkPath), ref.string(sourcePath))
}

/**
 * 创建文件硬链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns 
 */
export function createHardLink(LinkPath: string, sourcePath: string) {
    return native.createSymlink(ref.string(LinkPath), ref.string(sourcePath))
}

/**打开显示器 */
export function showMonitors(show?: boolean) {
    if (typeof show == "boolean") {
        return show ? native.showMonitors() : native.shutMonitors()
    }
    return native.showMonitors();
}

/**关闭显示器 */
export function shutMonitors(show?: boolean) {
    if (typeof show == "boolean") {
        return show ? native.showMonitors() : native.shutMonitors()
    }
    return native.shutMonitors();
}

/**
 * `Sync` 同步阻塞(进程)
 * @param awaitTime
 * @returns
 */
export function sleep(awaitTime: number) {
    return native.sleep(ref.int(awaitTime));
}

/**
 * `async` 异步阻塞(进程)
 * @param awaitTime
 * @returns
 */
export async function Sleep(awaitTime: number, Sync?: boolean) {
    if (Sync) {
        return sleep(ref.int(awaitTime));
    }
    return new Promise((resolve) =>
        setTimeout(resolve, ref.int(awaitTime))
    );
}

/**
 * 系统启动到现在的时间(毫秒)
 * @returns
 */
export function systemStartTime() {
    return native.systemStartTime();
}

/**
* 获取所有窗口的信息
**/
export function getAllWindows(isWindows: boolean) {
    class WINDOWS_INFO {
        handle: number;
        constructor(handle: number) {
            this.handle = handle;
        }
        _rect?: HMC.Rect
        get rect() {
            if (!this._rect) this._rect = native.getWindowRect(this.handle);
            return this._rect;
        }
        _className?: string
        get className() {
            if (typeof this._className == "undefined") this._className = native.getWindowClassName(this.handle);
            return this._className;
        }
        _style?: number
        get style() {
            if (typeof this._style == "undefined") this._style = native.getWindowStyle(this.handle);
            return this._style;
        }
        _title?: string | null;
        get title() {
            if (typeof this._title == "undefined") this._title = native.lookHandleGetTitle(this.handle);
            return this._title;
        }
    }

    let AllWindowsHandle = native.getAllWindowsHandle(isWindows === false ? false : true);
    let AllWindows: HMC.GET_ALL_WINDOWS_INFO[] = [];
    for (let index = 0; index < AllWindowsHandle.length; index++) {
        const handle = AllWindowsHandle[index];
        AllWindows.push((new WINDOWS_INFO(handle)) as HMC.GET_ALL_WINDOWS_INFO);
    }
    return AllWindows;
}

/**
 * 检索指定窗口所属的类的名称
 * @param Handle 句柄
 * @returns 
 */
export function getWindowClassName(Handle: number | HWND) {
    return native.getWindowClassName(ref.int(Handle));
}

/**
 * 获取窗口类关联代码
 * @param Handle 句柄
 * @returns 
 */
export function getWindowStyle(Handle: number | HWND) {
    return native.getWindowStyle(ref.int(Handle));
}

/**
 * 获取WebView2Info 的信息
 * @param Has 
 */
function GetWebView2Info(Has: true): boolean;
function GetWebView2Info(Has?: false): HMC.WebView2Info
function GetWebView2Info(Has?: boolean): boolean | HMC.WebView2Info {
    const INFO: HMC.WebView2Info = {
        version: "",
        name: "",
        location: "",
    };
    const { HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER } = Hkey;
    let WebView2IDKEY = "{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5}";

    //  https://learn.microsoft.com/zh-cn/microsoft-edge/webview2/concepts/distribution#detect-if-a-suitable-webview2-runtime-is-already-installed

    // 64bit Windows
    let Path_64bit_LOCAL: ForEachKey = [HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\EdgeUpdate\\Clients"];
    let Path_64bit_USER: ForEachKey = [HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\EdgeUpdate\\Clients"];

    // 32bit Windows
    let Path_32bit_LOCAL: ForEachKey = [HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\EdgeUpdate\\Clients"];
    let Path_32bit_USER: ForEachKey = [HKEY_CURRENT_USER, "Software\\Microsoft\\EdgeUpdate\\Clients"];

    type ForEachKey = [HMC.HKEY, string];
    let ForEachKey: Array<ForEachKey> = [Path_64bit_LOCAL, Path_64bit_USER, Path_32bit_LOCAL, Path_32bit_USER];

    for (let index = 0; index < ForEachKey.length; index++) {
        const KEY_PATH = ForEachKey[index];
        if (registr.hasRegistrKey(...KEY_PATH, WebView2IDKEY)) {
            if (Has) return true;
        }
        const [Hkey, Path] = KEY_PATH;
        INFO.location = registr.getStringRegKey(Hkey, Path.concat("\\", WebView2IDKEY), "location");
        INFO.name = registr.getStringRegKey(Hkey, Path.concat("\\", WebView2IDKEY), "name");
        INFO.version = registr.getStringRegKey(Hkey, Path.concat("\\", WebView2IDKEY), "pv");

        break;
    }

    return INFO;
}

/**
 * 获取WebView2的信息
 * @returns 
 */
export function getWebView2Info() {
    return GetWebView2Info();
}

/**
 * 下载并安装WebView2 
 */
export async function WebView2OnlineInstall() {
    const webView2URL = "https://go.microsoft.com/fwlink/p/?LinkId=2124703";
    const webView2Path = path.join("MicrosoftEdgeWebview2Setup.exe");
    const webView2InstallCommand = ["/silent", "/install"];
    return new Promise<void>((resolve, reject) => {
        const buffList: Buffer[] = [];
        https.get(webView2URL, (res) => {
            if (res.statusCode !== 200) {
                reject(new Error(`Install  WebView2 failure statusCode: ${res.statusCode || 404}`));
                return;
            }

            res.on("data", (data) => {
                buffList.push(data);
            });

            res.once("error", (err) => {
                reject(err);
            });

            res.on('end', () => {
                const buff = ref.concatBuff(buffList);
                buffList.length = 0;
                fs.promises.writeFile(webView2Path, buff).then(() => {
                    const spawn = child_process.spawn(webView2Path, webView2InstallCommand, { "windowsHide": true, });
                    spawn.on("error", function () {
                        reject(new Error(`Install  WebView2 failure Installation process creation failed`));
                        spawn.kill();
                    });
                    spawn.once("exit", function () {
                        resolve(undefined);
                    });
                }).catch(err => {
                    reject(new Error(`Install  WebView2 failure Update file cannot be written`));
                });
            });

        });
    });
}

/**
 * 当前系统是否安装了 WebView2
 * @returns 
 */
export function hasWebView2() {
    return GetWebView2Info(true);
}
/**
 * 判断TCP(服务)端口号正在使用/系统占用
 * @param port TCP端口
 * @returns 
 */
export function hasPortTCP(port: number): Promise<boolean>;
export function hasPortTCP(port: number, callBack: (hasPort: boolean) => unknown): void;
/**
 * 判断TCP(服务)端口号正在使用/系统占用
 * @param port TCP端口
 * @returns 
 */
export function hasPortTCP(port: number, callBack?: (hasPort: boolean) => unknown): unknown {
    let resolve: ((hasPort: boolean) => unknown) | null = null;
    let prom;
    let sock = net.createServer(function () { });
    sock.listen(port);
    if (typeof callBack == 'function') {
        resolve = callBack;
    } else {
        prom = new Promise((Prom_resolve) => {
            resolve = Prom_resolve;
        });
    }
    sock.on("error", function (err) {
        resolve && resolve(true);
        sock.close();
    });
    sock.on("listening", function () {
        resolve && resolve(false);
        sock.close();
    });
    if (typeof callBack !== 'function') {
        return prom;
    }
}
export const _KeyboardcodeEmenList = KeyboardcodeEmenList;
export const _KeyboardcodeComparisonTable = KeyboardcodeComparisonTable;

/**
 * 判断UDP端口号正在使用/系统占用
 * @param port TCP端口
 * @returns 
 */
export function hasPortUDP(port: number): Promise<boolean>;
export function hasPortUDP(port: number, callBack: (hasPort: boolean) => unknown): void;
/**
 * 判断UDP端口号正在使用/系统占用
 * @param port TCP端口
 * @returns 
 */
export function hasPortUDP(port: number, callBack?: (hasPort: boolean) => unknown): unknown {
    let resolve: ((hasPort: boolean) => unknown) | null = null;
    let prom;
    let udp4 = dgram.createSocket('udp4');
    udp4.bind(port);
    if (typeof callBack == 'function') {
        resolve = callBack;
    } else {
        prom = new Promise((Prom_resolve) => {
            resolve = Prom_resolve;
        });
    }
    udp4.on("error", function (err) {
        resolve && resolve(true);
        udp4.close();
    });
    udp4.on("listening", function () {
        resolve && resolve(false);
        udp4.close();
    });
    if (typeof callBack !== 'function') {
        return prom;
    }
}
/**
 * 格式化 驱动器路径 ('\Device\HarddiskVolume2' => "D:\")
 */
export function formatVolumePath(VolumePath: string) {
    return native.formatVolumePath(ref.string(VolumePath))
}
/**
 * 获取当前文件系统的驱动器名称及路径
 * @returns 
 */
export function getVolumeList() {
    return native.getVolumeList()
}

/**
 * 枚举进程id 的加载的模块路径
 * @param ProcessID 
 * @returns 
 */
export function getModulePathList(ProcessID: number) {
    return native.getModulePathList(ref.int(ProcessID));
}

/**
 * 枚举进程id的句柄
 * @param ProcessID 被枚举的进程id
 * @returns 
 */
export function enumProcessHandle(ProcessID: number): Promise<HMC.ProcessHandle[]>;

/**
 * 枚举进程id的句柄
 * @param ProcessID 被枚举的进程id
 * @param CallBack 枚举时候的回调
 * @returns 
 */
export function enumProcessHandle(ProcessID: number, CallBack: (PHandle: HMC.ProcessHandle) => void): void

/**
 * 枚举进程id的句柄
 * @param ProcessID 被枚举的进程id
 * @param CallBack 枚举时候的回调
 * @returns 
 */
export function enumProcessHandle(ProcessID: number, CallBack?: (PHandle: HMC.ProcessHandle) => void) {
    let enumID = native.enumProcessHandle(ref.int(ProcessID));
    let next = true;
    let enumProcessHandleList: HMC.ProcessHandle[] = [];
    if (typeof enumID != "number") throw new Error("No enumerated id to query unknown error");
    if (typeof CallBack == "function") {
        ; (async () => {
            while (next) {
                await Sleep(50);
                let data = native.enumProcessHandlePolling(enumID);
                if (data) {
                    for (let index = 0; index < data.length; index++) {
                        const enumProcessHandle = data[index];
                        if (!enumProcessHandle) continue;
                        if (enumProcessHandle.type == 'hmc::endl::') {
                            return;
                        }
                        CallBack(enumProcessHandle);
                    }
                }
            }
        })();
        return;
    }
    return new Promise(async (resolve, reject) => {
        while (next) {
            await Sleep(50);
            let data = native.enumProcessHandlePolling(enumID);
            if (data) {
                for (let index = 0; index < data.length; index++) {
                    const enumProcessHandle = data[index];
                    if (!enumProcessHandle) continue;
                    if (enumProcessHandle.type == 'hmc::endl::') {
                        return resolve(enumProcessHandleList);
                    }
                    enumProcessHandleList.push(enumProcessHandle);
                }
            }
        }
        resolve(enumProcessHandleList);
    });

}
/**
* 枚举进程的线程id
* @param ProcessID 进程id
* @param returnDetail 是否返回 THREADENTRY32 为`false`或者为空则返回线程id
*/
export function getProcessThreadList(ProcessID: number, returnDetail?: false): number[];
/**
 * 
 * @param ProcessID 进程id
 * @param returnDetail 为`true` 则返回THREADENTRY32 
 */
export function getProcessThreadList(ProcessID: number, returnDetail: true): HMC.THREADENTRY32[];
/**
 * 枚举进程的线程id
 * @param ProcessID 进程id
 */
export function getProcessThreadList(ProcessID: number): number[];

/**
 * 枚举子线程id
 * @param ProcessID 进程id
 * @returns 
 */
export function getProcessThreadList(ProcessID: unknown, returnDetail?: unknown): unknown {
    const _returnDetail = returnDetail ? true : false;
    if (_returnDetail) return native.getProcessThreadList(ref.int(ProcessID), true) || [];
    return native.getProcessThreadList(ref.int(ProcessID),) || [];
}

/**
 * 获取所有该进程下的 子进程id
 * @param ProcessID 进程id
 * @returns 
 */
export function getSubProcessID(ProcessID: number) {
    return native.getSubProcessID(ref.int(ProcessID)) || [];
}
/**
 * 获取进程id的主进程
 * @param ProcessID 进程id
 * @returns 
 */
export function getProcessParentProcessID(ProcessID: number) {
    return native.getProcessParentProcessID(ref.int(ProcessID)) || null;
}

/**
 * 枚举所有进程id的句柄
 * @param ProcessID 被枚举的进程id
 * @param CallBack 枚举时候的回调
 * @returns 
 */
export function enumAllProcessHandle(CallBack?: (PHandle: HMC.PROCESSENTRY) => void) {
    let enumID = native.enumAllProcess();
    let next = true;
    let PROCESSENTRYLIST: HMC.PROCESSENTRY[] = [];
    if (typeof enumID != "number") throw new Error("No enumerated id to query unknown error");
    if (typeof CallBack == "function") {
        ; (async () => {
            while (next) {
                await Sleep(15);
                let data = native.enumAllProcessPolling(enumID);
                if (data) {
                    for (let index = 0; index < data.length; index++) {
                        const PROCESSENTRY = data[index];
                        if (!PROCESSENTRY) continue;
                        if (PROCESSENTRY.szExeFile == 'HMC::endl::') {
                            return;
                        }
                        CallBack(PROCESSENTRY);
                    }
                }
            }
        })();
        return;
    }
    return new Promise(async (resolve, reject) => {
        while (next) {
            await Sleep(50);
            let data = native.enumAllProcessPolling(enumID);
            if (data) {
                for (let index = 0; index < data.length; index++) {
                    const PROCESSENTRY = data[index];
                    if (!PROCESSENTRY) continue;
                    if (PROCESSENTRY.szExeFile == 'HMC::endl::') {
                        return resolve(PROCESSENTRYLIST);
                    }
                    PROCESSENTRYLIST.push(PROCESSENTRY);
                }
            }
        }
        resolve(PROCESSENTRYLIST);
    });

}

// hmc.node 的版本号
export const version = native.version;

// hmc的用途
export const desc = native.desc;

// 当前hmc.node 的适用平台
export const platform = native.platform;


//  所有窗口操作方法的归类合集 (拥有统一化名称) 
export const Window = {
    isInMonitor: isInMonitorWindow,
    isMouseMonitor: isMouseMonitorWindow,
    HWND: HWND,
    setMode: setWindowMode,
    getAllWindows: getAllWindows,
    getAllHandle: getAllWindowsHandle,
    watchPoint: WatchWindowPoint,
    watchtFocus: WatchWindowForeground,
    getFocus: getForegroundWindow,
    getMain: getMainWindow,
    getPoint: getPointWindow,
    getProcessHandle: getProcessHandle,
    getPointMain: getPointWindowMain,
    setTaskbarVisible: SetWindowInTaskbarVisible,
    getProcessID: getHandleProcessID,
    getRect: getWindowRect,
    isEnabled: isEnabled,
    isHandle: isHandle,
    hasHandle: isHandle,
    isVisible: isHandleWindowVisible,
    close: lookHandleCloseWindow,
    getTitle: lookHandleGetTitle,
    setTitle: lookHandleSetTitle,
    setShowWindow: lookHandleShowWindow,
    setTransparent: setHandleTransparent,
    setEnabled: setWindowEnabled,
    setFocus: setWindowFocus,
    setTop: setWindowTop,
    update: updateWindow,
    jitter: windowJitter,
    hasTop: hasWindowTop,
    closed: closedHandle,
    getFocusProcessID: getForegroundWindowProcessID,
    getPointName: getPointWindowName,
    getPointProcessId: getPointWindowProcessId,
    enumChild: enumChildWindows,
    console: {
        hide: hideConsole,
        show: showConsole,
        get: getConsoleHandle,
        blockInput: SetBlockInput,
    },
    getStyle: getWindowStyle,
    getClassName: getWindowClassName
}

//所有监听函数的合集 (拥有统一化名称)  
export const Watch = {
    clipboard: watchClipboard,
    usb: watchUSB,
    windowFocus: WatchWindowForeground,
    windowPoint: WatchWindowPoint,
    process: processWatchdog
}

// 剪贴板工具集  (拥有统一化名称)
export const Clipboard = {
    clear: clearClipboard,
    readText: getClipboardText,
    readFilePaths: getClipboardFilePaths,
    writeText: setClipboardText,
    writeFilePaths: setClipboardFilePaths,
    sequence: getClipboardSequenceNumber,
    watch: watchClipboard,
}


class MousePoint {
    /**从右到左的像素数 */
    x: number;
    /**从上到下的像素数 */
    y: number;
    /**是否被按下 */
    isDown: boolean;
    constructor(str: `${number}|${number}|${0 | 1}`) {
        const data = str.split("|");
        this.x = Number(data[0]);
        this.y = Number(data[1]);
        this.isDown = Number(data[2]) ? true : false;
    }
    /**
     * 鼠标左键按下
     */
    get isLeft() {
        return Auto.hasKeyActivate(0x01);
    }
    /**
     * 鼠标右键被按下
     */
    get isRight() {
        return Auto.hasKeyActivate(0x02);
    }
    /**
     * 鼠标中键被按下
     */
    get isMiddle() {
        return Auto.hasKeyActivate(0x04);
    }
    /**
     * 在此坐标模拟进行单击
     * @param awitMs 
     */
    async click(awitMs?: number) {
        awitMs = awitMs || 150;
        Auto.setCursorPos(this.x, this.y);
        Auto.mouse("MOUSEEVENTF_LEFTDOWN");
        await Sleep(awitMs);
        return Auto.mouse("MOUSEEVENTF_LEFTUP");
    }
    /**
     * 模拟右键在此坐标按下和释放鼠标中键
     * @param awitMs 
     */
    async middle(awitMs?: number) {
        awitMs = awitMs || 150;
        Auto.setCursorPos(this.x, this.y);
        Auto.mouse(0x0020);
        await Sleep(awitMs);
        return Auto.mouse("MOUSEEVENTF_MIDDLEUP");
    }
    /**
     * 在此坐标按下模拟右键点击
     * @param awitMs 
     */
    async rClick(awitMs?: number) {
        awitMs = awitMs || 150;
        Auto.setCursorPos(this.x, this.y);
        Auto.mouse("MOUSEEVENTF_RIGHTDOWN");
        await Sleep(awitMs);
        return Auto.mouse("MOUSEEVENTF_RIGHTUP");
    }
    /**
     * 双击
     * @param doubleAwitMs 双击间隔 
     * @param clickAwitMs 模拟点击时间间隔
     */
    doubleClick(doubleAwitMs?: number, clickAwitMs?: number) {
        doubleAwitMs = doubleAwitMs || 150;
        clickAwitMs = clickAwitMs || 150;
        this.click(clickAwitMs).then(() => {
            Sleep(doubleAwitMs || 150)
                .then(() => {
                    this.click(clickAwitMs);
                });
        });
    }
    /**
     * 移动鼠标位置
     * @param x 
     * @param y 
     */
    moveMouse(x: number, y: number) {
        Auto.setCursorPos(x, y);
    }
}


class Keyboard {
    /**
     * 是否按下了shift
     */
    get shiftKey() {
        return Auto.hasKeyActivate(0x10) || Auto.hasKeyActivate(0xA1) || Auto.hasKeyActivate(0xA0);
    }
    /***
     * 是否按下了alt
     */
    get altKey() {
        return Auto.hasKeyActivate(0x12) || Auto.hasKeyActivate(0xA4) || Auto.hasKeyActivate(0xA5);
    }
    /***
     * 是否按下了ctrl
     */
    get ctrlKey() {
        return Auto.hasKeyActivate(0x11);
    }
    /***
     * 是否按下了win
     */
    get winKey() {
        return Auto.hasKeyActivate(0x5B) || Auto.hasKeyActivate(0x5C);
    }
    vKey: VK_VirtualKey;
    key: VK_key;
    code: VK_code;
    /**
     * 键值代码
     */
    keyCode: VK_keyCode;
    constructor(str: `${number}|${0 | 1}`) {
        const data = str.split("|");
        this.vKey = Number(data[0]);
        this.__isDown = Number(data[1]) ? true : false;
        let KeyboardcodeEmen = KeyboardcodeEmenList.get(this.vKey);
        if (!KeyboardcodeEmen) {
            KeyboardcodeEmen = ["unknown", null, this.vKey, 0];
            // throw new Error("key Value Data That Does Not Exist !");
        }
        const [VK_key, VK_code, VK_keyCode, VK_VirtualKey, VK_Nickname] = KeyboardcodeEmen;
        this.keyCode = VK_keyCode;
        this.key = VK_key;
        this.code = VK_code || VK_key;
    }
    /**
     * 是否被按下
     */
    private __isDown: boolean;
    /**是否被按下 */
    get isDown() {
        return this.__isDown || hasKeyActivate(this.vKey);
    }
}

let SetIohook = false;

class Iohook_Mouse {
    private _onlistenerCountList = {
        close: [] as Function[],
        data: [] as Function[],
        mouse: [] as Function[],
        start: [] as Function[],
        move: [] as Function[],
    };
    private _oncelistenerCountList = {
        close: [] as Function[],
        data: [] as Function[],
        mouse: [] as Function[],
        start: [] as Function[],
        move: [] as Function[],
    };
    private _Close = false;
    constructor() {

    }
    once(eventName: "start" | "close", listener: () => void): this;
    once(eventName: "mouse", listener: (MousePoint: MousePoint) => void): this;
    once(listener: (MousePoint: MousePoint) => void): this;
    once(eventName: "move", listener: (x: number, y: number, MousePoint: MousePoint) => void): this;
    once(eventName: "data", listener: (data: `${number}|${number}|${0 | 1}`[]) => void): this;
    once(eventName: unknown, listener?: unknown) {
        if (typeof eventName === "function") {
            listener = eventName;
            eventName = "mouse"
        }
        if (typeof listener !== "function") return mouseHook;
        mouseHook._oncelistenerCountList[eventName as "data"].push(listener);
        return mouseHook;
    };
    on(listener: (MousePoint: MousePoint) => void): this;
    on(eventName: "start" | "close", listener: () => void): this;
    on(eventName: "mouse", listener: (MousePoint: MousePoint) => void): this;
    on(eventName: "move", listener: (x: number, y: number, MousePoint: MousePoint) => void): this;
    on(eventName: "data", listener: (data: `${number}|${number}|${0 | 1}`[]) => void): this;
    on(eventName: unknown, listener?: unknown) {
        if (typeof eventName === "function") {
            listener = eventName;
            eventName = "mouse"
        }
        if (typeof listener !== "function") return mouseHook;
        mouseHook._onlistenerCountList[eventName as "data"].push(listener);
        return mouseHook;
    };
    /**
     * 开始
     * @returns 
     */
    start() {
        SetIohook = true;
        let start = native.isStartHookMouse();
        if (start) throw new Error("the Task Has Started.");
        native.installHookMouse();
        const oid_Mouse_info = {
            x: 0,
            y: 0,
            isDown: false,
        };
        if (native.isStartHookMouse()) {
            mouseHook._Close = false;
        }
        mouseHook.emit("start");
        let emit_getMouseNextSession = () => {
            if (mouseHook._Close) { return };
            let getMouseNextSession = native.getMouseNextSession();
            if (getMouseNextSession?.length) mouseHook.emit("data", getMouseNextSession);
            if (getMouseNextSession)
                for (let index = 0; index < getMouseNextSession.length; index++) {
                    const MouseNextSession = getMouseNextSession[index];
                    const mousePoint = new MousePoint(MouseNextSession);
                    mouseHook.emit("mouse", mousePoint);
                    if (oid_Mouse_info.x != mousePoint.x || oid_Mouse_info.y != mousePoint.y) {
                        mouseHook.emit("move", mousePoint.x, mousePoint.y, mousePoint);
                    }
                    oid_Mouse_info.isDown = mousePoint.isDown;
                    oid_Mouse_info.x = mousePoint.x;
                    oid_Mouse_info.y = mousePoint.y;
                }

        }
        (async () => {
            while (true) {
                if (mouseHook._Close) return;
                await Sleep(50);
                emit_getMouseNextSession();
            }
        })();
    }
    /**
     * 结束
     */
    close() {
        native.unHookMouse();

        mouseHook.emit("close");
        mouseHook._Close = true;
        mouseHook._oncelistenerCountList.close.length = 0;
        mouseHook._oncelistenerCountList.data.length = 0;
        mouseHook._oncelistenerCountList.mouse.length = 0;
        mouseHook._oncelistenerCountList.move.length = 0;
        mouseHook._oncelistenerCountList.start.length = 0;

        mouseHook._onlistenerCountList.close.length = 0;
        mouseHook._onlistenerCountList.data.length = 0;
        mouseHook._onlistenerCountList.mouse.length = 0;
        mouseHook._onlistenerCountList.move.length = 0;
        mouseHook._onlistenerCountList.start.length = 0;
    }
    emit(eventName: "data", data: `${number}|${number}|${0 | 1}`[]): boolean;
    emit(eventName: "start" | "close"): boolean;
    emit(eventName: "move", x: number, y: number, MousePoint: MousePoint): boolean;
    emit(eventName: "mouse", MousePoint: MousePoint): boolean;
    emit(eventName: unknown, ...data: unknown[]) {
        const emitFunList = mouseHook._onlistenerCountList[eventName as "data"];
        const onceEmitFunList = mouseHook._oncelistenerCountList[eventName as "data"];
        for (let index = 0; index < emitFunList.length; index++) {
            const emitFun = emitFunList[index];
            emitFun.apply(mouseHook, data);
        };
        for (let index = 0; index < onceEmitFunList.length; index++) {
            const emitFun = onceEmitFunList[index];
            emitFun.apply(mouseHook, data);
        };
        onceEmitFunList.length = 0;
        return emitFunList.length ? true : false;
    }
    /**
     * 关闭监听
     * @param eventName 
     * @param data 
     * @returns 
     */
    off(eventName: "start" | "close" | "mouse" | "move" | "data", treatmentMode: "on" | "once" | Function, data?: Function) {
        switch (treatmentMode) {
            case "on": {
                if (data) {
                    const listenerCountList = mouseHook._onlistenerCountList[eventName];
                    if (listenerCountList.indexOf(data)) {
                        return mouseHook._onlistenerCountList[eventName].splice(listenerCountList.indexOf(data), 1) ? true : false;
                    }
                } else {
                    mouseHook._onlistenerCountList[eventName].length = 0;
                    return !mouseHook._onlistenerCountList[eventName].length
                }
                break;
            }
            case "once": {
                if (data) {
                    const listenerCountList = mouseHook._oncelistenerCountList[eventName];
                    if (listenerCountList.indexOf(data)) {
                        return mouseHook._oncelistenerCountList[eventName].splice(listenerCountList.indexOf(data), 1) ? true : false;
                    }
                } else {
                    mouseHook._oncelistenerCountList[eventName].length = 0;
                    return !mouseHook._oncelistenerCountList[eventName].length
                }
                break;
            }
        }
        return false;
    }
}

/**
 * 设置一个低级鼠标变化监听
 * @example ```javascript
 * // 添加处理函数
   hmc.Auto.mouseHook.on("move",function(x,y,env){
    console.log(x,y,env);
    });
   // log => 50 ,  350  , {...env}

   // 添加处理函数
   hmc.Auto.mouseHook.on("mouse",function(env){
    console.log(env);
   });
   // log => {...env}

   // 启动
   hmc.Auto.mouseHook.start();

   // off
   hmc.Sleep(5000).then(hmc.Auto.mouseHook.close);

```
 */
export const mouseHook = new Iohook_Mouse();

/**
 * 通过可执行文件或者带有图标的文件设置窗口图标
 * @param handle 句柄
 * @param Extract 可执行文件/Dll/文件
 * @param index 图标位置索引 例如文件显示的图标默认是0
 */
export function setWindowIconForExtract(handle: number, Extract: string, index: number): void {
    if (!Extract) throw new Error("Extract Path not defined");
    return native.setWindowIconForExtract(ref.int(handle), ref.string(Extract), index ? ref.int(index) : 0)
};
// /**
//  * 执行t2c 脚本 (异步)
//  * - 第一位是事件名称 例如 点击：click 按键A：A 按键Ctrl：ctrl 鼠标移动：60,50 
//  * - 第二位是按下或者松开 NULL为按下立刻松开
//  * - 第三位是延迟时间ms 为0立刻执行
//  * -----------------------
//  * - 单击键盘事件T2C语法： click|NULL|500  事件名称|NULL=单击|延迟时间
//  * 
//  * @example ```javascript
//  * hmc.sendKeyT2C(
//  * `
//  * 50,72|NULL|500
//  * ctrl|true|50
//  * A|NULL|0
//  * ctrl|false|50
//  * `
//  * )
//  * ```
//  * @param t2cStr 
//  */
// export function sendKeyT2C(...t2cStr: string[]) {

// }
// /**
//  * 执行t2c 脚本 (同步)
//  * - 第一位是事件名称 例如 点击：click 按键A：A 按键Ctrl：ctrl 鼠标移动：60,50 
//  * - 第二位是按下或者松开 NULL为按下立刻松开
//  * - 第三位是延迟时间ms 为0立刻执行
//  * -----------------------
//  * - 单击键盘事件T2C语法： click|NULL|500  事件名称|NULL=单击|延迟时间
//  * 
//  * @example ```javascript
//  * hmc.sendKeyT2C(
//  * `
//  * 50,72|NULL|500
//  * ctrl|true|50
//  * A|NULL|0
//  * ctrl|false|50
//  * `
//  * )
//  * ```
//  * @param t2cStr 
//  */
// export function sendKeyT2CSync(...t2cStr: string[]) {

// }
/**
    * 截屏指定的宽高坐标 并将其存储写入为文件 
    * @param FilePath 文件路径
    * @param x 从左边的哪里开始 为空为0
    * @param y 从顶部的哪里开始 为空为0
    * @param width 宽度
    * @param height 高度
    */
export function captureBmpToFile(FilePath: string, x: number | null, y: number | null, width: number | null, height: number | null) {
    native.captureBmpToFile(ref.string(FilePath), ref.int(x || 0), ref.int(y || 0), ref.int(width || 0), ref.int(height || 0))
}
/**
 * 发送键盘事件
 * @param keyCode 键值
 * @param keyDown 是否按下
 * 
 */
export function sendKeyboard(keyCode: number | string, keyDown: boolean | null) {
    let vk = vkKey(keyCode);
    if (!vk) throw new Error("The currently entered keyboard key name/key value does not exist");
    if (keyDown === null) {
        native.sendKeyboard(vk);

    } else
        native.sendKeyboard(vk, ref.bool(keyDown));
};

/**
 * 发送键盘事件序列
 * @example ```javascript
 * hmc.sendKey(
 * // 数组序列 
 * ['ctrl',50] , // 50毫秒以后执行ctrl 点击事件(按下立刻放开)
 * ['ctrl',null] , // 执行ctrl 点击事件(按下立刻放开)
 * ['ctrl',true,50] , // 50毫秒以后按下ctrl不放开
 * ['ctrl',fasle,50] , // 50毫秒以后将ctrl放开
 * 
 *  // 对象序列
 * {key:"ctrl",} // ctrl键 点击事件(按下立刻放开)
 * {key:"ctrl",ms:50} // 50毫秒以后执行ctrl 点击事件(按下立刻放开)
 * {key:"ctrl",down:false,ms:50} // 50毫秒以后将ctrl放开
 * )
 * ```
 */
export function sendKeyboardSequence(...keys: Array<{ key: number | string, down?: boolean, ms?: number } | [number | string, boolean | number | null, number]>) {
    (async () => {
        for (let index = 0; index < keys.length; index++) {
            const of_key = keys[index];
            if (Array.isArray(of_key)) {
                if (of_key?.[2]) {
                    let ms = ref.int(of_key?.[2]);
                    await Sleep(ms);
                }
                if (of_key.length < 2) continue;
                sendKeyboard(of_key[0], typeof of_key?.[1] == "boolean" ? of_key?.[1] : null);
            }
            else if (typeof of_key == "object") {
                let keys = Object.keys(of_key);
                if (!keys.includes("key")) continue;
                if (keys.includes("ms")) {
                    let ms = ref.int(of_key.ms);
                    await Sleep(ms);
                }
                sendKeyboard(of_key.key, typeof of_key.down == "undefined" ? null : of_key.down);
            }
        }

    })();

};
/**
 * 获取屏幕指定区域的颜色
 * @param x 左边开始的坐标
 * @param y 从上面开始的坐标
 * @returns 
 */
export function getColor(x: number, y: number) {
    return native.getColor(ref.int(x), ref.int(y));
}
/**
 * 执行标准快捷键
 * @param basicCout 四大按键的包含表
 * @param KeyCode 执行的键码(如果表中有可以忽略) 
 * @example ```javascript
 * // ctrl + shift +A 
 * hmc.sendBasicKeys({"ctrl","shift",key:"A"});
 * hmc.sendBasicKeys({"ctrl","shift"},"A");
 * 
 * ```
 */
export function sendBasicKeys(basicCout: HMC.BasicCout, KeyCode?: number | string): void;
/**
 * 执行标准快捷键
 * @param basicKeysStr 快捷键内容
 * @example ```javascript
 * // ctrl + shift +A 
 * hmc.sendBasicKeys("ctrl+shift+A");
 * 
 */
export function sendBasicKeys(basicKeysStr: string): void;
/**
 * 执行标准快捷键(标准化输入)
 * @param ctrlKey 组合中含有ctrl
 * @param shiftKey 组合中含有shift
 * @param altKey 组合中含有alt
 * @param winKey 组合中含有win
 * @param KeyCode 键盘隐射值
 */
export function sendBasicKeys(ctrlKey: boolean, shiftKey: boolean, altKey: boolean, winKey: boolean, KeyCode: number | string): void;

/**
 * 执行标准快捷键
 * @param ctrlKey 组合中含有ctrl
 * @param shiftKey 组合中含有shift
 * @param altKey 组合中含有alt
 * @param winKey 组合中含有win
 * @param KeyCode 键盘隐射值
 * @returns 
 */
export function sendBasicKeys(ctrlKey: unknown, shiftKey?: unknown, altKey?: unknown, winKey?: unknown, KeyCode?: unknown): void {
    let _ctrlKey = false, _shiftKey = false, _altKey = false, _winKey = false;
    let _KeyCode: number | null = null;

    // hmc.sendBasicKeys({"ctrl","shift",key:"A"});   or   hmc.sendBasicKeys({"ctrl","shift"},"A");
    if (ctrlKey && typeof ctrlKey == "object") {
        let keys = Object.keys(ctrlKey);
        if (!keys.includes("key") && !keys.includes("code") && !vkKey(shiftKey)) {
            throw new Error("The current function requires other keys, not only (ctrl, shift, ait, win)");
        }
        _ctrlKey = keys.includes("ctrl") ? true : false;
        _shiftKey = keys.includes("shift") ? true : false;
        _altKey = keys.includes("alt") ? true : false;
        _winKey = keys.includes("win") ? true : false;
        // @ts-expect-error
        _KeyCode = vkKey(ctrlKey?.key || ctrlKey?.code || shiftKey || 0);
    }
    // hmc.sendBasicKeys("ctrl+shift+A");
    else
        if (typeof ctrlKey == "string") {
            _ctrlKey = ctrlKey.includes("ctrl") ? true : false;
            _shiftKey = ctrlKey.includes("shift") ? true : false;
            _altKey = ctrlKey.includes("alt") ? true : false;
            _winKey = ctrlKey.includes("win") ? true : false;
            _KeyCode = vkKey(ctrlKey.replace(/[+]|ctrl|shift|alt|win/g, ''));
        }
        else {
            _ctrlKey = ctrlKey ? true : false;
            _shiftKey = shiftKey ? true : false;
            _altKey = altKey ? true : false;
            _winKey = winKey ? true : false;
            _KeyCode = vkKey(KeyCode);
        }
    if ((_ctrlKey || _shiftKey || _altKey || _winKey) && _KeyCode !== null) {
        native.sendBasicKeys(ref.bool(_ctrlKey), ref.bool(_shiftKey), ref.bool(_altKey), ref.bool(_winKey), ref.int(_KeyCode));
    } else {
        throw new Error("The current function can only execute standard shortcuts and cannot enter a key value alone or without a regular keystroke")
    }
}

class Iohook_Keyboard {
    private _onlistenerCountList = {
        close: [] as Function[],
        data: [] as Function[],
        start: [] as Function[],
        change: [] as Function[],
    };
    private _oncelistenerCountList = {
        close: [] as Function[],
        data: [] as Function[],
        start: [] as Function[],
        change: [] as Function[],
    };
    private _Close = false;
    constructor() {

    }
    once(eventName: "start" | "close", listener: () => void): this;
    once(eventName: "data", listener: (data: (`${number}|0` | `${number}|1`)[]) => void): this;
    once(eventName: "change", listener: (KeyboardPoint: Keyboard) => void): this;
    once(listener: (KeyboardPoint: Keyboard) => void): this;
    once(eventName: unknown, listener?: unknown) {
        if (typeof eventName === "function") {
            listener = eventName;
            eventName = "change"
        }
        if (typeof listener !== "function") return keyboardHook;
        keyboardHook._oncelistenerCountList[eventName as "data"].push(listener);
        return keyboardHook;
    };
    on(eventName: "start" | "close", listener: () => void): this;
    on(eventName: "data", listener: (data: (`${number}|0` | `${number}|1`)[]) => void): this;
    on(eventName: "change", listener: (KeyboardPoint: Keyboard) => void): this;
    on(listener: (KeyboardPoint: Keyboard) => void): this;
    on(eventName: unknown, listener?: unknown) {
        if (typeof eventName === "function") {
            listener = eventName;
            eventName = "change"
        }
        if (typeof listener !== "function") return keyboardHook;
        keyboardHook._onlistenerCountList[eventName as "data"].push(listener);
        return keyboardHook;
    };
    /**
     * 开始
     * @returns 
     */
    start() {
        SetIohook = true;
        let start = native.isStartKeyboardHook();
        if (start) throw new Error("the Task Has Started.");
        native.installKeyboardHook();
        if (native.isStartKeyboardHook()) {
            keyboardHook._Close = false;
        }
        keyboardHook.emit("start");
        let emit_getKeyboardNextSession = () => {
            let getKeyboardNextSession = native.getKeyboardNextSession();
            if (getKeyboardNextSession?.length) keyboardHook.emit("data", getKeyboardNextSession);
            if (getKeyboardNextSession)
                for (let index = 0; index < getKeyboardNextSession.length; index++) {
                    const KeyboardNextSession = getKeyboardNextSession[index];
                    const KeyboardPoint = new Keyboard(KeyboardNextSession);
                    keyboardHook.emit("change", KeyboardPoint);
                }

        }
        (async () => {
            while (true) {
                if (keyboardHook._Close) return;
                await Sleep(15);
                emit_getKeyboardNextSession();
            }
        })();
        return start;
    }
    /**
     * 结束
     */
    close() {
        native.unKeyboardHook();

        keyboardHook.emit("close");
        keyboardHook._Close = true;

        keyboardHook._oncelistenerCountList.close.length = 0;
        keyboardHook._oncelistenerCountList.data.length = 0;
        keyboardHook._oncelistenerCountList.change.length = 0;
        keyboardHook._oncelistenerCountList.start.length = 0;

        keyboardHook._onlistenerCountList.close.length = 0;
        keyboardHook._onlistenerCountList.data.length = 0;
        keyboardHook._onlistenerCountList.change.length = 0;
        keyboardHook._onlistenerCountList.start.length = 0;
    }
    emit(eventName: "data", data: (`${number}|0` | `${number}|1`)[]): boolean;
    emit(eventName: "start" | "close"): boolean;
    emit(eventName: "change", KeyboardPoint: Keyboard): boolean;
    emit(eventName: unknown, ...data: unknown[]) {
        const emitFunList = keyboardHook._onlistenerCountList[eventName as "data"];
        const onceEmitFunList = keyboardHook._oncelistenerCountList[eventName as "data"];
        for (let index = 0; index < emitFunList.length; index++) {
            const emitFun = emitFunList[index];
            emitFun.apply(keyboardHook, data);
        };
        for (let index = 0; index < onceEmitFunList.length; index++) {
            const emitFun = onceEmitFunList[index];
            emitFun.apply(keyboardHook, data);
        };
        onceEmitFunList.length = 0;
        return emitFunList.length ? true : false;
    }
    /**
     * 关闭监听
     * @param eventName 
     * @param data 
     * @returns 
     */
    off(eventName: "start" | "close" | "change" | "data", treatmentMode: "on" | "once" | Function, data?: Function) {
        switch (treatmentMode) {
            case "on": {
                if (data) {
                    const listenerCountList = keyboardHook._onlistenerCountList[eventName];
                    if (listenerCountList.indexOf(data)) {
                        return keyboardHook._onlistenerCountList[eventName].splice(listenerCountList.indexOf(data), 1) ? true : false;
                    }
                } else {
                    keyboardHook._onlistenerCountList[eventName].length = 0;
                    return !keyboardHook._onlistenerCountList[eventName].length
                }
                break;
            }
            case "once": {
                if (data) {
                    const listenerCountList = keyboardHook._oncelistenerCountList[eventName];
                    if (listenerCountList.indexOf(data)) {
                        return keyboardHook._oncelistenerCountList[eventName].splice(listenerCountList.indexOf(data), 1) ? true : false;
                    }
                } else {
                    keyboardHook._oncelistenerCountList[eventName].length = 0;
                    return !keyboardHook._oncelistenerCountList[eventName].length
                }
                break;
            }
        }
        return false;
    }
}
/**
 * 设置一个键盘低级变化监听
 * @example ```javascript 
  // 添加处理函数
  hmc.Auto.keyboardHook.on("change",function(env){
     console.log(env.key,env.isDown,env);
  });
  // log => ctrl , true {...env}

  // 启动
  hmc.Auto.keyboardHook.start();

  // off
  hmc.Sleep(5000).then(hmc.Auto.keyboardHook.close);

 *  ```
 * 
 */
export const keyboardHook = new Iohook_Keyboard();


// 自动化工具集   (拥有统一化名称) 
export const Auto = {
    sendKeyboard,
    sendKeyboardSequence,
    getColor,
    sendBasicKeys,
    setWindowEnabled,
    setCursorPos,
    mouse,
    rightClick,
    leftClick,
    getBasicKeys,
    getMouseMovePoints,
    powerControl,
    SetBlockInput,
    SetSystemHOOK,
    hasKeyActivate,
    mouseHook,
    keyboardHook
}

// USB 控制的归档   (拥有统一化名称)
export const Usb = {
    getHub: getHidUsbList,
    getDevsInfo: getUsbDevsInfo,
    watch: watchUSB,
}

// 实用工具集   (拥有统一化名称)
export const Shell = {
    trash: deleteFile,
    openApp: openApp,
    getShortcutLink: getShortcutLink,
    setShortcutLink: setShortcutLink,
    freePort: freePort,
    createSymlink: createSymlink,
    createDirSymlink: createDirSymlink,
    createHardLink: createHardLink,
}

//进程操作合集   (拥有统一化名称)
export const Process = {
    watch: processWatchdog,
    kill: killProcess,
    killMatch: killProcessName,
    getList: getProcessList,
    getHandle: getProcessHandle,
    getName: getProcessName,
    getPath: getProcessidFilePath,
    getFocus: getForegroundWindowProcessID,
    has: hasProcess,
    match: getProcessNameList,
    matchDetails: getDetailsProcessNameList,
    getDetailsList: getDetailsProcessList,
    parentID: getProcessParentProcessID,
    mianPID: getProcessParentProcessID,
    subPID: getSubProcessID,
    threadList: getProcessThreadList
}

//注册表编辑合集   (拥有统一化名称)
export const registr = {
    /**
     * 直达路径解析
     * @param Path 全路径(直达路径)
     * @param atkey 是否将最后一个值解释为键
     * @returns
     */
    analysisDirectPath,
    /**
     * 判断注册表中是否有该键值
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06591796875 ms
     * @returns
     */
    has: (HKEY: HMC.HKEY, Path: string, key: string) => {
        return hasRegistrKey(HKEY, Path, key);
    },
    /**
     * 获取内容(文本)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.108ms
     * @returns
     */
    get: (HKEY: HMC.HKEY, Path: string, key: string) => {
        return getStringRegKey(HKEY, Path, key);
    },
    /**
     * 设置键值对
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Value 数据
     * @time 2.02392578125 ms
     * @returns
     */

    set: (HKEY: HMC.HKEY, Path: string, key: string, value: string) => {
        return setRegistrKey(HKEY, Path, key, value);
    },
    /**
     * 删除数据
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.076904296875 ms
     * @returns
     */

    remove: (HKEY: HMC.HKEY, Path: string, key: string) => {
        return removeStringRegKey(HKEY, Path, key);
    },
    /**
     * 枚举键值
     * @param HKEY 根路径
     * @param Path 路径
     * @time 0.06689453125 ms
     * @returns
     */

    keys: (HKEY: HMC.HKEY, Path: string) => {
        return enumRegistrKey(HKEY, Path);
    },
    /**
     * 将当前的路径的注册表值转表
     * @param HKEY
     * @param Path
     */

    list: (HKEY: HMC.HKEY, Path: string) => {
        return listRegistrPath(HKEY, Path);
    },
    /**
     * 创建新的路径
     * @param HKEY 根路径
     * @param Path 路径
     * @time 2.02392578125 ms
     * @returns
     */

    create: (HKEY: HMC.HKEY, Path: string, key: string) => {
        return createPathRegistr(HKEY, Path);
    },
    /**
     * 打开一个注册表路径并返回一些实用方法
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    open: (HKEY: HMC.HKEY, Path: string, key: string) => {
        return openRegKey(HKEY, Path, key);
    },
    /**
     * 判断注册表中是否有该键值
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06591796875 ms
     * @returns
     */
    get hasRegistrKey() {
        return this.has;
    },
    /**
     * 将当前的路径的注册表值转表
     * @param HKEY
     * @param Path
     */

    get listRegistrPath() {
        return this.list;
    },
    /**
     * 枚举键值
     * @param HKEY 根路径
     * @param Path 路径
     * @time 0.06689453125 ms
     * @returns
     */
    get enumRegistrKey() {
        return this.keys;
    },
    /**
     * 删除数据
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.076904296875 ms
     * @returns
     */

    get removeStringRegKey() {
        return this.remove;
    },
    /**
     * 设置键值对
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Value 数据
     * @time 2.02392578125 ms
     * @returns
     */

    get setRegistrKey() {
        return this.set;
    },
    /**
     * 获取内容(文本)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.108ms
     * @returns
     */
    get getStringRegKey() {
        return this.get;
    },
    /**
     * 获取内容(数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.10888671875 ms
     * @returns
     */

    getNumberRegKey: (HKEY: HMC.HKEY, Path: string, key: string) => {
        return getNumberRegKey(HKEY, Path, key);
    },
    /**
     * 创建新的路径
     * @param HKEY 根路径
     * @param Path 路径
     * @time 2.02392578125 ms
     * @returns
     */

    get createPathRegistr() {
        return this.create;
    },
    /**
     * 获取内容(二进制 Buffer)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06787109375 ms
     * @returns
     */

    getRegistrBuffValue: (HKEY: HMC.HKEY, Path: string, key: string) => {
        return getRegistrBuffValue(HKEY, Path, key);
    },
    /**
     * 打开一个注册表路径并返回一些实用方法
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */

    get openRegKey() {
        return open;
    },
    getRegistrQword,
    getRegistrDword,
    setRegistrQword,
    setRegistrDword,
    removeStringRegValue,
    removeStringRegKeyWalk,
    removeStringTree,
    isRegistrTreeKey,
};
/**
* 创建管道并执行命令
* @param cmd 命令
*/
export function _popen(cmd: string) {
    return native.popen(ref.string(cmd));
}
/**
 * 判断互斥体文本是否存在
 * @param MutexName 互斥体文本
 * @returns 
 */
export function hasMutex(MutexName: string) {
    return native.hasMutex(ref.string(MutexName));
}
/**
 * 创建互斥体文本并返回结果 
 * ?(无法移除 除非当前进程退出 互斥体具有唯一性) 
 * ? 可以用于判断进程是否重复启动
 * @param MutexName 互斥体文本
 * @returns 
 */
export function createMutex(MutexName: string) {
    return native.createMutex(ref.string(MutexName));
}

/**
* 创建管道并执行命令
* @param cmd 命令
*/
export function popen(cmd: string) {
    return native.popen(ref.string(cmd));
}

/**
 * 获取当前进程的环境变量
 * @returns 
 */
export function getAllEnv() {
    return native.getAllEnv();
}

/**
 * 获取指定key的环境变量
 * @param key 
 * @returns 
 */
export function getenv(key: string) {
    return native.getenv(ref.string(key));
}

/**
 * 获取指定UDP端口的pid
 * @param Port 
 * @returns 
 */
export function getUDPPortProcessID(Port: number) {
    return native.getUDPPortProcessID(ref.int(Port));
}

/**
 * 添加环境变量(不写入系统)
 * @param key 
 * @param data 
 * @returns 
 */
export function putenv(key: string, data: string | string[]) {
    return native.putenv(ref.string(key), ref.string(Array.isArray(data) ? data.join(";") : data));
}

/**
 * 获取指定TCP端口的pid
 * @param Port 
 * @returns 
 */
export function getTCPPortProcessID(Port: number) {
    return native.getTCPPortProcessID(ref.int(Port));

}

export const Registr = registr;
export const hmc = {
    getAllEnv,
    getenv,
    getUDPPortProcessID,
    getTCPPortProcessID,
    putenv,
    createMutex,
    hasMutex,
    Auto,
    Clipboard,
    HWND,
    MessageError,
    MessageStop,
    Process,
    Registr,
    SetBlockInput,
    SetSystemHOOK,
    SetWindowInTaskbarVisible,
    Shell,
    Sleep,
    Usb,
    Watch,
    WatchWindowForeground,
    WatchWindowPoint,
    WebView2OnlineInstall,
    Window,
    _popen,
    alert,
    analysisDirectPath,
    captureBmpToFile,
    clearClipboard,
    closedHandle,
    confirm,
    createDirSymlink,
    createHardLink,
    createPathRegistr,
    createSymlink,
    deleteFile,
    desc,
    enumAllProcessHandle,
    enumChildWindows,
    enumProcessHandle,
    enumRegistrKey,
    formatVolumePath,
    freePort,
    getAllWindows,
    getAllWindowsHandle,
    getBasicKeys,
    getClipboardFilePaths,
    getClipboardSequenceNumber,
    getClipboardText,
    getColor,
    getConsoleHandle,
    getCurrentMonitorRect,
    getDetailsProcessList,
    getDetailsProcessNameList,
    getDeviceCaps,
    getDeviceCapsAll,
    getForegroundWindow,
    getForegroundWindowProcessID,
    getHandleProcessID,
    getHidUsbList,
    getMainWindow,
    getMetrics,
    getModulePathList,
    getMouseMovePoints,
    getNumberRegKey,
    getPointWindow,
    getPointWindowMain,
    getPointWindowName,
    getPointWindowProcessId,
    getProcessHandle,
    getProcessList,
    getProcessName,
    getProcessNameList,
    getProcessParentProcessID,
    getProcessThreadList,
    getProcessidFilePath,
    getRegistrBuffValue,
    getRegistrDword,
    getRegistrQword,
    getShortcutLink,
    getStringRegKey,
    getSubProcessID,
    getSystemIdleTime,
    getSystemMenu,
    getSystemMetricsLen,
    getTrayList,
    getUsbDevsInfo,
    getVolumeList,
    getWebView2Info,
    getWindowClassName,
    getWindowRect,
    getWindowStyle,
    getWindowTitle,
    hasKeyActivate,
    hasPortTCP,
    hasPortUDP,
    hasProcess,
    hasRegistrKey,
    hasWebView2,
    hasWindowTop,
    hideConsole,
    isAdmin,
    isEnabled,
    isHandle,
    isHandleWindowVisible,
    isInMonitorWindow,
    isMouseMonitorWindow,
    isProcess,
    isRegistrTreeKey,
    isSystemX64,
    keyboardHook,
    killProcess,
    killProcessName,
    leftClick,
    listRegistrPath,
    lookHandleCloseWindow,
    lookHandleGetTitle,
    lookHandleSetTitle,
    lookHandleShowWindow,
    messageBox,
    mouse,
    mouseHook,
    native,
    openApp,
    openExternal,
    openPath,
    openRegKey,
    openURL,
    platform,
    popen,
    powerControl,
    processWatchdog,
    ref,
    registr,
    removeStringRegKey,
    removeStringRegKeyWalk,
    removeStringRegValue,
    removeStringTree,
    rightClick,
    sendBasicKeys,
    sendKeyboard,
    sendKeyboardSequence,
    setClipboardFilePaths,
    setClipboardText,
    setCloseWindow,
    setCursorPos,
    setHandleTransparent,
    setRegistrDword,
    setRegistrKey,
    setRegistrQword,
    setShortcutLink,
    setShowWindow,
    setWindowEnabled,
    setWindowFocus,
    setWindowIconForExtract,
    setWindowMode,
    setWindowTitle,
    setWindowTop,
    showConsole,
    showMonitors,
    shutMonitors,
    sleep,
    system,
    systemChcp,
    systemStartTime,
    trash,
    updateWindow,
    version,
    watchClipboard,
    watchUSB,
    windowJitter
}
export default hmc;

process.on('exit', function () {
    if (SetIohook) {
        native.unHookMouse();
        native.unKeyboardHook();
        native.clearEnumAllProcessList();
        native.clearEnumProcessHandle();
    }
});

