/// <reference types="node" />
import { VK_VirtualKey, VK_code, VK_key, VK_keyCode, vkKey } from "./vkKey";
/**注册表根目录 */
declare const Hkey: {
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
export declare const native: HMC.Native;
/**
 * 句柄 可以视为是一个数字也可以视为是一个功能 {0}
 * 继承了 Number 的构建类
 */
export declare class HWND extends Number {
    constructor(hWnd: number);
    /**句柄 */
    get handle(): number;
    /**真实的句柄 */
    HWND: number;
    /**
     * 强制关闭窗口不发送被关闭的消息给窗口
     */
    closed(): false | undefined;
    /**
     * 向窗口发送关闭的消息
     */
    close(): boolean;
    /**
     * 窗口位置
     */
    get rect(): HMC.Rect | null;
    /**
     * 窗口名称
     */
    get title(): string;
    /**
     * 设置窗口的标题
     * @param Title 标题
     * @returns
     */
    setTitle(Title: string): boolean;
    /**句柄是否有效 */
    get exists(): boolean;
    /**句柄是否有效 */
    get isHandle(): boolean;
    /**
     * 当前句柄的pid
     */
    get pid(): number | null;
    /**
     * 获取主窗口的pid
     */
    get MianPid(): HMC.ProcessID | null;
    get MainHandle(): number;
    get className(): string;
    get style(): number;
    /**
     * 判断窗口是否可见
     * @returns
     */
    isVisible(): boolean;
    /**
     * 结束该进程
     * @returns
     */
    kill(): boolean;
    /**
     * 隐藏窗口
     * @returns
     */
    hide(): boolean;
    /**
     * 显示窗口
     * @returns
     */
    show(): boolean;
    /**
     * 窗口最小化
     * @returns
     */
    setMin(): boolean;
    /**
     * 窗口最大化
     * @returns
     */
    setMax(): boolean;
    /**
     * 恢复最近的状态
     * @returns
     */
    setRestore(): boolean;
    /**
     * 聚焦该窗口
     * @returns
     */
    setFocus(): boolean;
    /**
     * 禁用窗口
     * @param enabled
     * @returns
     */
    setEnabled(enabled: boolean): boolean;
    /**
     * 是否被禁用
     * @returns
     */
    isEnabled(): boolean;
    /**
     * 窗口抖动
     * @returns
     */
    setJitter(): false | void;
    /**
     * 判断窗口是否被顶设
     * @returns
     */
    isTop(): boolean;
    /**
     * 设置窗口顶设或者取消
     * @returns
     */
    setTopOrCancel(): boolean;
    /**
     * 设置窗口不透明度
     * @param opacity 0-100 or 0.0 - 1.0
     */
    setOpacity(opacity: number): false | void;
    /**
     * 设置窗口不透明度
     * @param opacity -1 - 255
     */
    setTransparent(opacity: number): false | void;
}
export declare module HMC {
    export type G_HMC_NATIVE = {
        _PromiseSession_get: HMC.Native["_PromiseSession_get"];
        _PromiseSession_isClosed: HMC.Native["_PromiseSession_isClosed"];
        _PromiseSession_stop: HMC.Native["_PromiseSession_stop"];
        _PromiseSession_max_id: HMC.Native["_PromiseSession_max_id"];
        _PromiseSession_data_size: HMC.Native["_PromiseSession_data_size"];
        _PromiseSession_set_sleep_time: HMC.Native["_PromiseSession_set_sleep_time"];
        _PromiseSession_await: HMC.Native["_PromiseSession_await"];
        _PromiseSession_ongoingTasks: HMC.Native["_PromiseSession_ongoingTasks"];
        _PromiseSession_completeTasks: HMC.Native["_PromiseSession_completeTasks"];
        _PromiseSession_get_sleep_time: HMC.Native["_PromiseSession_get_sleep_time"];
        _PromiseSession_allTasks: HMC.Native["_PromiseSession_allTasks"];
    };
    export type MouseMovePoints = {
        "x": number | null;
        "y": number | null;
        "time": number | null;
        "dwExtraInfo": number | null;
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
        x: number;
        y: number;
    };
    export type WebView2Info = {
        version: string;
        name: string;
        location: string;
    } | null;
    /**
     * C++ 中的 位置定义
     */
    export type cRECT = {
        left: number;
        top: number;
        right: number;
        bottom: number;
    };
    /**
     * C++中的位置定义
     */
    export interface cRect {
        x: number;
        y: number;
        height: number;
        width: number;
    }
    export interface enumProcessContP {
        name: string;
        pid: ProcessID;
        path: string;
    }
    export interface enumProcessCont {
        name: string;
        pid: ProcessID;
    }
    export interface MousePosn {
        left: number;
        top: number;
        x: number;
        y: number;
    }
    export type ProcessID = number;
    export type HandleTransparent = number;
    export type HKEY = keyof typeof Hkey;
    export enum MouseKey {
        WM_MOUSEMOVE = 512,
        WM_LBUTTONDOWN = 513,
        WM_RBUTTONDOWN = 516,
        WM_LBUTTONUP = 514,
        WM_RBUTTONUP = 517,
        WM_MBUTTONDOWN = 519,
        WM_MBUTTONUP = 520,
        WM_MOUSEWHEEL = 522
    }
    export type direction = "right" | "left" | "right-top" | "left-bottom" | "left-top" | "right-bottom" | "bottom" | "top" | "middle";
    export enum MouseKeyName {
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
    export interface MouseNotEventData {
        "id": null;
        "time": null;
    }
    export interface MouseMoveEventData {
        "id": number;
        "time": number;
        "button": MouseKey.WM_MOUSEMOVE;
        "x": number;
        "y": number;
    }
    export interface MouseMouseEventData {
        "id": number;
        "time": number;
        "button": MouseKey.WM_LBUTTONDOWN | MouseKey.WM_LBUTTONUP | MouseKey.WM_MBUTTONDOWN | MouseKey.WM_MBUTTONUP | MouseKey.WM_MOUSEWHEEL | MouseKey.WM_RBUTTONDOWN | MouseKey.WM_RBUTTONUP;
        "buttonDown": boolean;
        "wheelDelta": number | null;
        "name": "left-mouse-button" | "right-mouse-button" | "middle-mouse-button" | null;
    }
    export type MouseEventDataAll = MouseMouseEventData | MouseMoveEventData | MouseNotEventData;
    export type MouseEventDataOK = MouseMouseEventData | MouseMoveEventData;
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
    export type VariableList = {
        [key: string]: string;
    };
    export interface TRAY_ICON {
        path: string;
        info: string;
        handle: number;
    }
    export interface DeviceCaps {
        width: number;
        height: number;
    }
    export interface MovePoint {
        x: number;
        y: number;
        /**点击时候的时间 */
        time: number;
        /**附加信息 */
        dwExtraInfo: number;
    }
    export type BASIC_KEYS = {
        shift: boolean;
        alt: boolean;
        ctrl: boolean;
        win: boolean;
    };
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
    };
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
    export type mouse_event = /**不支持的属性 请使用 setCursorPos 方法设置位置*/ 32768 | /**左键按下 */ 2 | /**左边的按钮是向上的 */ 4 | /**中间的按钮是向下的 */ 32 | /**中间的按钮是向上的 */ 64 | /**鼠标移动和按钮点击 */ 1 | /**鼠标右键按下 */ 8 | /**鼠标右键弹起 */ 16 | /**滚轮按钮被旋转 */ 2048 | /**按下了 X 按钮 */ 128 | /**X 按钮被释放 */ 256 | /**滚轮按钮倾斜*/ 4096 | /**不支持的属性 请使用 setCursorPos 方法设置位置*/ "MOUSEEVENTF_ABSOLUTE" | /**左键按下 */ "MOUSEEVENTF_LEFTDOWN" | /**左边的按钮是向上的 */ "MOUSEEVENTF_LEFTUP" | /**中间的按钮是向下的 */ "MOUSEEVENTF_MIDDLEDOWN" | /**中间的按钮是向上的 */ "MOUSEEVENTF_MIDDLEUP" | /**鼠标移动和按钮点击 */ "MOUSEEVENTF_MOVE" | /**鼠标右键按下 */ "MOUSEEVENTF_RIGHTDOWN" | /**鼠标右键弹起 */ "MOUSEEVENTF_RIGHTUP" | /**滚轮按钮被旋转 */ "MOUSEEVENTF_WHEEL" | /**按下了 X 按钮 */ "MOUSEEVENTF_XDOWN" | /**X 按钮被释放 */ "MOUSEEVENTF_XUP" | /**滚轮按钮倾斜*/ "MOUSEEVENTF_HWHEEL";
    export type MB_UINT = /**消息框包含三个按钮：终止、重试和忽略。 */ "MB_ABORTRETRYIGNORE" | /**消息框包含三个按钮：取消、重试、继续。使用此消息框类型而不是 MB_ABORTRETRYIGNORE。 */ "MB_CANCELTRYCONTINUE" | /**向消息框 添加帮助按钮。当用户单击帮助按钮或按 F1 时|系统会向所有者 发送WM_HELP消息。 */ "MB_HELP" | /**消息框包含一个按钮：确定。这是默认设置。 */ "MB_OK" | /**消息框包含两个按钮：确定和取消。 */ "MB_YESNOCANCEL" | /**消息框包含两个按钮：是和否。 */ "MB_YESNO" | /**消息框包含两个按钮：OK和Cancel。 */ "MB_OKCANCEL" | /**消息框包含两个按钮：OK和Cancel。 */ "MB_RETRYCANCEL" | /**消息框包含三个按钮：Yes、No和Cancel。 一个停止标志图标出现在消息框中。*/ "MB_ICONERROR" | /**一个停止标志图标出现在消息框中。 */ "MB_ICONSTOP" | /**问号图标出现在消息框中。不再推荐使用问号消息图标|因为它不能清楚地表示特定类型的消息|并且作为问题的消息措辞可能适用于任何消息类型。此外|用户可能会将消息符号问号与帮助信息混淆。因此|请勿在消息框中使用此问号消息符号。系统继续支持它的包含只是为了向后兼容。 */ "MB_ICONQUESTION" | /**一个由圆圈中的小写字母i组成的图标出现在消息框中。 */ "MB_ICONASTERISK" | "MB_ICONINFORMATION" | /**消息框中会出现一个感叹号图标。 */ "MB_ICONEXCLAMATION" | /** 消息框中会出现一个感叹号图标。 */ "MB_ICONWARNING" | /* 消息框成为前台窗口 **/ "MB_TOPMOST" | "MB_SETFOREGROUND" | "MB_RTLREADING" | "MB_RIGHT" | "MB_DEFAULT_DESKTOP_ONLY" | "MB_TASKMODAL" | "MB_SYSTEMMODAL" | "MB_APPLMODAL" | "MB_DEFBUTTON4" | "MB_DEFBUTTON3" | "MB_DEFBUTTON2" | "MB_ICONHAND" | "MB_DEFBUTTON1";
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
    export type PROCESSENTRY_V2 = HMC.PROCESSENTRY & {
        name: string;
        pid: number;
        ppid: number;
    };
    export interface PSYSTEM_PROCESS_INFORMATION {
        NextEntryOffset: number;
        NumberOfThreads: number;
        ImageName: string;
        BasePriority: number;
        UniqueProcessId: number;
        HandleCount: number;
        SessionId: number;
        PeakVirtualSize: number;
        VirtualSize: number;
        PeakWorkingSetSize: number;
        WorkingSetSize: number;
        QuotaPagedPoolUsage: number;
        QuotaNonPagedPoolUsage: number;
        PagefileUsage: number;
        PeakPagefileUsage: number;
        PrivatePageCount: number;
    }
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
        getMetrics: () => MousePosn;
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
        setClipboardFilePaths(FilePaths: string[]): void;
        /**
         * 获取剪贴板中的文件路径
         */
        getClipboardFilePaths(): string[];
        /**
         * 获取所有usb驱动器(不包含HUD)
         */
        getUsbDevsInfo(): string[];
        /**枚举子窗口 */
        enumChildWindows(Handle: number): number[];
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
        deleteFile(Path: string, Recycle?: boolean, isShow?: boolean): number;
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
        /**
         * 移除键盘挂钩
         */
        unKeyboardHook(): void;
        /**
         * 启动鼠标动作挂钩
         */
        /**
         * 启动键盘动作挂钩
         */
        installKeyboardHook(): void;
        /**
         * 获取已经记录了的低级鼠标动作数据 出于性能优化使用了(文本数组)
         */
        getKeyboardNextSession(): `${number}|${0 | 1}`[] | undefined;
        /**
         * 获取已经记录了的低级键盘动作数据 出于性能优化使用了(文本数组)
         */
        /**
         * 鼠标挂钩是否已经启用
         */
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
       * 内联 启动枚举进程快照 与句柄
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
        /**
         * 获取指定的变量环境
         * @param key
         */
        getenv(key: string): string;
        /**
         * 获取变量环境
         */
        getAllEnv(): {
            [key: string]: string;
        };
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
        getVariableAll(): HMC.VariableList;
        /**
         * 从注册表读取现在的真实环境变量 但不更新到进程环境
         * - 请注意这里 不会添加 进程的变量
         * @param key
         */
        getRealGlobalVariable(): HMC.VariableList;
        /**
         * 获取用户变量的键列表
         */
        getUserKeyList(): string[];
        /**
         * 获取系统变量的键列表
         */
        getSystemKeyList(): string[];
        _PromiseSession_get(SessionID: number, size?: number): undefined | null | any[];
        /**
         * 判断指定的  [Session Promise] 是否已经结束
         * @param SessionID id
         */
        _PromiseSession_isClosed(SessionID: number): boolean;
        /**
         * 停止一个  [Session Promise] 事件
         * @param SessionID id
         */
        _PromiseSession_stop(SessionID: number): void;
        /**
         * 获取当前  Session ID 已经到哪里了
         */
        _PromiseSession_max_id(): number;
        /**
         * 获取指定的id存在了多少个数据
         * @param SessionID id
         */
        _PromiseSession_data_size(SessionID: number): number;
        /**
         * 设置每次获取 Session Promise 的毫秒数
         * @param sleep_time 毫秒
         * @default 5 ms
         */
        _PromiseSession_set_sleep_time(sleep_time: number): number;
        /**
         * 将  [Session Promise] 转为同步
         * @param SessionID id
         */
        _PromiseSession_await(SessionID: number): void;
        /**
         * 所有任务
         */
        _PromiseSession_allTasks(): number[];
        /**
         * 已经完成的任务
         */
        _PromiseSession_completeTasks(): number[];
        /**
         * 进行中的任务
         */
        _PromiseSession_ongoingTasks(): number[];
        /**
         * 当前的sleep ms
         */
        _PromiseSession_get_sleep_time(): number;
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
    };
    export type ProcessHandle = {
        handle: number;
        name: string;
        type: "ALPC Port" | "Event" | "Timer" | "Mutant" | "Key" | "Section" | "File" | "Thread" | string;
    };
    export type Volume = {
        path: string;
        name: string;
        device: string;
    };
    /**取色 颜色返回值 */
    export type Color = {
        r: number;
        g: number;
        b: number;
        hex: string;
    };
    /**
     * 标准快捷键的输入表
     */
    export type BasicCout = {
        /**组合中含有ctrl */
        ctrl?: any;
        /**组合中含有shift */
        shift?: any;
        /**组合中含有alt */
        alt?: any;
        /**组合中含有win */
        win?: any;
        /**键码/按键名 */
        key?: number | string;
        /**键码/按键名 */
        code?: number | string;
    };
    type chcpList = {
        37: "IBM037";
        437: "IBM437";
        500: "IBM500";
        708: "ASMO-708";
        720: "DOS-720";
        737: "ibm737";
        775: "ibm775";
        850: "ibm850";
        852: "ibm852";
        855: "IBM855";
        857: "ibm857";
        858: "IBM00858";
        860: "IBM860";
        861: "ibm861";
        862: "DOS-862";
        863: "IBM863";
        864: "IBM864";
        865: "IBM865";
        866: "cp866";
        869: "ibm869";
        870: "IBM870";
        874: "windows-874";
        875: "cp875";
        932: "shift_jis";
        936: "gb2312";
        949: "ks_c_5601-1987";
        950: "big5";
        1026: "IBM1026";
        1047: "IBM01047";
        1140: "IBM01140";
        1141: "IBM01141";
        1142: "IBM01142";
        1143: "IBM01143";
        1144: "IBM01144";
        1145: "IBM01145";
        1146: "IBM01146";
        1147: "IBM01147";
        1148: "IBM01148";
        1149: "IBM01149";
        1200: "utf-16";
        1201: "unicodeFFFE";
        1250: "windows-1250";
        1251: "windows-1251";
        1252: "windows-1252";
        1253: "windows-1253";
        1254: "windows-1254";
        1255: "windows-1255";
        1256: "windows-1256";
        1257: "windows-1257";
        1258: "windows-1258";
        1361: "Johab";
        10000: "macintosh";
        10001: "x-mac-japanese";
        10002: "x-mac-chinesetrad";
        10003: "x-mac-korean";
        10004: "x-mac-arabic";
        10005: "x-mac-hebrew";
        10006: "x-mac-greek";
        10007: "x-mac-cyrillic";
        10008: "x-mac-chinesesimp";
        10010: "x-mac-romanian";
        10017: "x-mac-ukrainian";
        10021: "x-mac-thai";
        10029: "x-mac-ce";
        10079: "x-mac-icelandic";
        10081: "x-mac-turkish";
        10082: "x-mac-croatian";
        12000: "utf-32";
        12001: "utf-32BE";
        20000: "x-Chinese_CNS";
        20001: "x-cp20001";
        20002: "x_Chinese-Eten";
        20003: "x-cp20003";
        20004: "x-cp20004";
        20005: "x-cp20005";
        20105: "x-IA5";
        20106: "x-IA5-German";
        20107: "x-IA5-Swedish";
        20108: "x-IA5-Norwegian";
        20127: "us-ascii";
        20261: "x-cp20261";
        20269: "x-cp20269";
        20273: "IBM273";
        20277: "IBM277";
        20278: "IBM278";
        20280: "IBM280";
        20284: "IBM284";
        20285: "IBM285";
        20290: "IBM290";
        20297: "IBM297";
        20420: "IBM420";
        20423: "IBM423";
        20424: "IBM424";
        20833: "x-EBCDIC-KoreanExtended";
        20838: "IBM-Thai";
        20866: "koi8-r";
        20871: "IBM871";
        20880: "IBM880";
        20905: "IBM905";
        20924: "IBM00924";
        20932: "EUC-JP";
        20936: "x-cp20936";
        20949: "x-cp20949";
        21025: "cp1025";
        21866: "koi8-u";
        28591: "iso-8859-1";
        28592: "iso-8859-2";
        28593: "iso-8859-3";
        28594: "iso-8859-4";
        28595: "iso-8859-5";
        28596: "iso-8859-6";
        28597: "iso-8859-7";
        28598: "iso-8859-8";
        28599: "iso-8859-9";
        28603: "iso-8859-13";
        28605: "iso-8859-15";
        29001: "x-Europa";
        38598: "iso-8859-8-i";
        50220: "iso-2022-jp";
        50221: "csISO2022JP";
        50222: "iso-2022-jp";
        50225: "iso-2022-kr";
        50227: "x-cp50227";
        51932: "euc-jp";
        51936: "EUC-CN";
        51949: "euc-kr";
        52936: "hz-gb-2312";
        54936: "GB18030";
        57002: "x-iscii-de";
        57003: "x-iscii-be";
        57004: "x-iscii-ta";
        57005: "x-iscii-te";
        57006: "x-iscii-as";
        57007: "x-iscii-or";
        57008: "x-iscii-ka";
        57009: "x-iscii-ma";
        57010: "x-iscii-gu";
        57011: "x-iscii-pa";
        65000: "utf-7";
        65001: "utf-8";
    };
    export type SystemDecoderKey = keyof chcpList;
    export type VarValueReBackData = {
        key: string;
        oid_value: string | undefined | null;
        new_vaule: string | undefined | null;
        /**
         * 更新类型
         * - update 直接替换新的变量内容
         * - remove 直接删除变量
         * - append 添加了新的变量(变量组)
         * - reduce 删除了新的变量(变量组)
         */
        update_type: "update" | "remove" | "append" | "reduce";
        value?: string | undefined | null;
    };
    export type PromiseSessionDataType = undefined | null | any;
    export type SystemDecoder = chcpList[SystemDecoderKey];
    export {};
}
export declare const ref: {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str: any): string;
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool: any): boolean;
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str: any): string;
    /**
     * 格式化数字为int(强制)
     * @param Num
     * @returns
     */
    int(Num: any): number;
    /**
     * 文本数组
     * @param array
     * @returns
     */
    stringArray(array: Set<any> | Array<any>): string[];
    /**
     * 文本数组
     * @param array
     * @returns
     */
    intArray(array: Set<any> | Array<any>): number[];
    /**
     * 格式化命令行内容
     */
    formatCmd(cmd: string): string[];
    /**
     * 将命令行内容组转为cmd文本
     * @param argv
     */
    formatArgv(...argv: Array<any>[] | any[]): string;
    /**注册表根目录 */
    HKEY: {
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
    /**
     * 拼合buff片段
     * @param buffList
     * @returns
     */
    concatBuff(buffList: Buffer[]): Buffer;
    /**
     * 键盘值格式化为键值
     * @param key 键值/键
     * @returns
     */
    vkKey: typeof vkKey;
};
export declare class PromiseSession {
    private data_list;
    private SessionID;
    /**
     * 将 PromiseSession 转为 Promise
     * @param format 数据格式化的函数
     * @returns
     */
    to_Promise<T>(format: (value: Array<undefined | null | any>) => T): Promise<T>;
    /**
     * PromiseSession 转为 callBack
     * @param format 格式化的函数 如果没有callback 此函数将被作为callBack使用
     * @param callback 回调函数 接收的第一个参数将会是 format格式化过得内容
     * @param everyCallback 是否每次回调 当此选项为false 将只会在PromiseSession接收完成时候回调
     */
    to_callback<T>(format: (value: Array<undefined | null | any>) => T, callback?: (value: T) => any, everyCallback?: boolean): void;
    /**
     * 异步改同步
     */
    await(): any[] | null | undefined;
    /**
     * 提前结束
     */
    stop(): void;
    /**
     * 初始化一个将 hmc_PromiseSession 转为js 异步的方法
     * hmc_PromiseSession 是一个支持并发异步的调用封装库
     * 用于解决napi无法连续创建同事件的异步空间 以及napi的异步及其难写的问题
     * @param SessionID
     */
    constructor(SessionID: number);
}
export declare function PromiseSP<T>(SessionID: number | Promise<any>, format: ((value: Array<undefined | null | any>) => T), Callback: undefined | ((error: null | Error, ...args: any[]) => any)): void;
export declare function PromiseSP<T>(SessionID: number | Promise<any>, format: ((value: Array<undefined | null | any>) => T)): Promise<T>;
/**
 * 直达路径解析
 * @param Path 全路径(直达路径)
 * @param atkey 是否将最后一个值解释为键
 * @returns
 */
export declare function analysisDirectPath(Path: string, atkey?: boolean): string[];
/**
 * 获取系统shell默认编码
 * @returns
 */
export declare function systemChcp(): Promise<{
    chcp: HMC.SystemDecoder;
    code: HMC.SystemDecoderKey;
}>;
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
export declare function setWindowMode(HWND: HWND | number, x: number | null | 0 | HMC.RECT_CONFIG, y?: number | null | 0, width?: number | null | 0, height?: number | null | 0): boolean;
/**
 * 判断注册表中是否有该键值
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06591796875 ms
 * @returns
 */
export declare function hasRegistrKey(HKEY: HMC.HKEY, Path: string, key: string): boolean;
/**
  * 设置键值对内容(64位数字)
  * @param HKEY 根路径
  * @param Path 路径
  * @param key 键
  * @param Qword (64位数字)
  * @returns
  */
export declare function setRegistrQword(HKEY: HMC.HKEY, Path: string, key: string, Qword: bigint | number): boolean;
/**
 * 设置键值对内容(32位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @param Qword (32位数字)
 * @returns
 */
export declare function setRegistrDword(HKEY: HMC.HKEY, Path: string, key: string, Dword: number): boolean;
/**
 * 获取内容(64位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06787109375 ms
 * @returns
 */
export declare function getRegistrQword(HKEY: HMC.HKEY, Path: string, key: string): bigint;
/**
 * 获取内容(64位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06787109375 ms
 * @returns
 */
export declare function getRegistrDword(HKEY: HMC.HKEY, Path: string, key: string): number;
/**
 * 获取内容(二进制 Buffer)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06787109375 ms
 * @returns
 */
export declare function getRegistrBuffValue(HKEY: HMC.HKEY, Path: string, key: string): void | Buffer;
/**
 * 枚举键值
 * @param HKEY 根路径
 * @param Path 路径
 * @time 0.06689453125 ms
 * @returns
 */
export declare function enumRegistrKey(HKEY: HMC.HKEY, Path: string): string[];
/**
 * 将当前的路径的注册表值转表
 * @param HKEY
 * @param Path
 */
export declare function listRegistrPath(HKEY: HMC.HKEY, Path: string): {
    [key: string]: string | Buffer;
    "": string | Buffer;
};
/**
 * 判断该键值是否存在子项
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 */
export declare function isRegistrTreeKey(HKEY: HMC.HKEY, Path: string, key?: string): boolean;
/**
 * 获取内容(文本)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.108ms
 * @returns
 */
export declare function getStringRegKey(HKEY: HMC.HKEY, Path: string, key?: string): string;
/**
 * 打开一个注册表路径并返回一些实用方法
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare function openRegKey(HKEY: HMC.HKEY, Path: string, key?: string): {
    /**
     * 获取全路径
     */
    readonly path: string;
    /**
     * 设置一个值
     * @param data 数据
     */
    set(data: string): boolean;
    /**
     * 获取内容
     * @returns
     */
    get(): string;
    /**
     * 获取该内容并将其视为二进制缓冲区
     * @returns 二进制缓冲区
     */
    getBuff(): Buffer;
    /**
     * 获取该内容并将其视为数字
     * @returns 数字
     */
    getNumber(): number;
    /**
     * 枚举当前路径下的键
     * @returns 键 数组
     */
    keys(): string[];
    /**
     * 将当前目录转为对象
     */
    list(): {
        [key: string]: string | Buffer;
        "": string | Buffer;
    };
};
/**
 * 获取内容(数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.10888671875 ms
 * @returns
 */
export declare function getNumberRegKey(HKEY: HMC.HKEY, Path: string, key?: string): number;
/**
 * 删除键 (文件夹)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.076904296875 ms
 * @returns
 */
export declare function removeStringRegKey(HKEY: HMC.HKEY, Path: string, key?: string): boolean;
/**
 * 删除该目录下的所有内容（树遍历）
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare function removeStringRegKeyWalk(HKEY: HMC.HKEY, Path: string, key?: string): boolean;
/**
* 删除该目录下的所有内容（树遍历）
* @param HKEY 根路径
* @param Path 路径
* @param key 键
* @returns
*/
export declare function removeStringTree(HKEY: HMC.HKEY, Path: string, key: string): boolean;
/**
 * 删除该键值
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare function removeStringRegValue(HKEY: HMC.HKEY, Path: string, key?: string): boolean;
/**
 * 设置键值对
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @param Value 数据
 * @time 2.02392578125 ms
 * @returns
 */
export declare function setRegistrKey(HKEY: HMC.HKEY, Path: string, key: string, Value: string): boolean;
/**
 * 创建新的路径
 * @param HKEY 根路径
 * @param Path 路径
 * @time 2.02392578125 ms
 * @returns
 */
export declare function createPathRegistr(HKEY: HMC.HKEY, Path: string): boolean;
/**
  * 同 C++/C 的system
  * @returns 程序退出代码
  */
export declare function system(str: string): number;
/**
 * 空闲的随机端口号
 * @returns
 */
export declare function freePort(): Promise<number>;
/**
 * 获取剪贴板中的文件列表
 * @returns
 */
export declare function getClipboardFilePaths(): string[];
export declare function getClipboardFilePaths(at: number): string | undefined;
/**
 * 向剪贴板写入文件列表
 * @param FilePaths
 */
export declare function setClipboardFilePaths(...FilePaths: string[] | [string[]]): void;
/**
 * 获取所有usb驱动器(不包含HUD)
 * @returns
 */
export declare function getUsbDevsInfo(): string[];
/**
 * 枚举句柄的子窗口
 * @param Handle 句柄
 * @returns
 */
export declare function enumChildWindows(Handle: number | HWND): number[];
/**
 * 隐藏当前控制台窗口(node)
 */
export declare function hideConsole(): boolean;
/**
 * 显示当前控制台窗口(node)
 */
export declare function showConsole(): boolean;
/**
 * 获取当前控制台窗口的句柄(node)
 * @returns
 */
export declare function getConsoleHandle(): HWND | null;
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
export declare function deleteFile(Path: string, Recycle?: boolean, isShow?: boolean): number;
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
export declare const trash: typeof deleteFile;
/**
 * 获取当前剪贴板内容的id(如果被重新写入了该id会变动)
 * @returns
 */
export declare function getClipboardSequenceNumber(): number;
/**
 * 当剪贴板内容变更后发生回调
 * @param CallBack 回调函数
 * @param nextAwaitMs 每次判断内容变化用时 默认 `150` ms
 * @returns
 */
export declare function watchClipboard(CallBack: () => void, nextAwaitMs?: number): {
    /**
     * 取消继续监听
     */
    unwatcher(): void;
    /**
     * 每次判断内容变化用时 默认 `150` ms
     * @param nextAwaitMs
     */
    setNextAwaitMs(nextAwaitMs: number): void;
};
/**
  * 当驱动器添加或者移除后发生回调
  * @param CallBack 回调函数
  * @param nextAwaitMs 每次判断内容变化用时 默认 `800` ms
  * @param watchType 监听的设备类型 默认 `["HUB","drive"]`
  * @returns
  */
export declare function watchUSB(CallBack: (env: "add" | "remove" | "start", id: string) => void, nextAwaitMs?: number, watchType?: "hub" | "drive" | Array<"hub" | "drive">): {
    readonly idList: Set<string>;
    /**
     * 取消继续监听
     */
    unwatcher(): void;
    /**
     * 每次判断内容变化用时 默认 `800` ms
     * @param nextAwaitMs
     */
    setNextAwaitMs(nextAwaitMs: number): void;
};
/**
 * 获取所有屏幕
 * @returns
 */
export declare function getDeviceCapsAll(): HMC.cRECT[];
/**
 * 判断句柄的窗口是否在所有窗口的范围中(无论他是否被其他窗口挡住)
 * @param Handle
 */
export declare function isInMonitorWindow(Handle: number | HWND): boolean;
/**
 * 判断句柄的窗口是否在鼠标所在的窗口
 * @param Handle
 */
export declare function isMouseMonitorWindow(Handle: number): boolean;
/**
 * 获取鼠标所在的屏幕信息
 */
export declare function getCurrentMonitorRect(): HMC.cRECT;
/**
 * 当前电脑存在几个屏幕
 */
export declare function getSystemMetricsLen(): number;
/**
 * 方法用于显示带有一条指定消息和一个 确认 按钮的警告框
 * @param Message 消息
 * @param Title 标题
 * @time any ms
 * @returns
 */
export declare function alert(Message: string, Title?: string): boolean;
/**
 * 方法用于显示带有一条指定消息和 确认 和取消  的按钮的消息框
 * @param Message 消息
 * @param Title 标题
 * @time any ms
 * @returns
 */
export declare function confirm(Message: string, Title?: string): boolean;
/**
 * 方法用于显示带有一条指定消息和一个 确认 按钮的和❌（X）的消息框。
 * @param Message 消息
 * @param Title 标题
 * @time any ms
 * @returns
 */
export declare function MessageStop(Message: string, Title?: string): void;
/**
 * 方法用于显示带有一条指定消息和一个 确认 按钮的错误框 附带有❗ 感叹号。
 * @param Message 消息
 * @param Title 标题
 * @time any ms
 * @returns
 */
export declare function MessageError(Message: string, Title?: string): void;
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
export declare function getAllWindowsHandle(isWindows: boolean): HWND[];
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
export declare function processWatchdog(ProcessID: number, callback?: (() => void) | number, awaitMs?: number): (Promise<void> & {
    quit: () => void;
}) | {
    quit: () => void;
};
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
export declare function WatchWindowPoint(callback: (newPoint: number, oidPoint: number, HWND: HWND) => void, awaitMs?: number): {
    /**结束监听 */
    quit: () => void;
    /**设置每次延迟事件 */
    setAwaitMs(ms: number): void;
};
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
export declare function WatchWindowForeground(callback: (newForeg: number, oidForeg: number, HWND: HWND) => void, awaitMs?: number): {
    /**结束监听 */
    quit: () => void;
    /**设置每次延迟事件 */
    setAwaitMs(ms: number): void;
};
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
export declare function openApp(AppPath: string, Command?: string | string[], cwd?: string, hide?: boolean, UAC?: boolean): boolean;
/**
 * 获取该名称 /正则匹配的进程列表
 * @param Name
 * @returns
 */
export declare function getProcessNameList(...Name: Array<string | RegExp>): {
    pid: number;
    name: string;
}[];
/**
* 获取该名称 /正则匹配的进程列表 带执行文件路径 慢20ms
* @param Name
* @returns
*/
export declare function getDetailsProcessNameList(...Name: Array<string | RegExp>): {
    pid: number;
    name: string;
    path: string;
}[];
/**
 * 结束该名称的进程
 * @param Name
 */
export declare function killProcessName(...Name: Array<string | RegExp>): {
    pid: number;
    kill: boolean;
    name: string;
}[];
/**
 * 获取当前的焦点窗口
 * @returns 一个可以操作的伪数字类
 */
export declare function getForegroundWindow(): HWND | null;
/**
 * 获取句柄的主窗口
 * @returns 一个可以操作的伪数字类
 */
export declare function getMainWindow(Handle: number | HWND): HWND | null;
/**
 * 获取鼠标所在的窗口
 * @returns 一个可以操作的伪数字类
 */
export declare function getPointWindow(): HWND | null;
/**
 * 获取鼠标所在的窗口的主窗口
 * @returns 一个可以操作的伪数字类
 */
export declare function getPointWindowMain(): HWND | null;
/**
 * 获取进程的句柄
 * @param ProcessID
 * @returns
 */
export declare function getProcessHandle(ProcessID: number): HWND | null;
/**
 * 阻止键盘和鼠标输入事件到达应用程序。
 */
export declare function SetBlockInput(Block: boolean): boolean;
/**
 * 设置该窗口图标在状态栏可见性 (注意：XP 下激活窗口了会失效(但是有没有一种可能 xp运行不了node和electron))
 * @param Handle 句柄
 * @param Visible 可见性
 * @returns
 */
export declare function SetWindowInTaskbarVisible(Handle: number | HWND, Visible: boolean): boolean;
/**
 * 获取句柄对应的进程id
 * @param Handle 句柄
 * @returns
 */
export declare function getHandleProcessID(Handle: number | HWND): number | null;
/** 获取窗口位置大小
 *  - 高|宽|坐标大于一万以上都是不可见的
 * **/
export declare function getWindowRect(Handle: number | HWND): HMC.Rect;
/**
 * 判断窗口是否禁用响应事件(鼠标键盘点击)
 * @param Handle
 * @returns
 */
export declare function isEnabled(Handle: number | HWND): boolean;
/**
 * 判断句柄是否有效
 * @param Handle
 * @returns
 */
export declare function isHandle(Handle: number | HWND): boolean;
/**
 * 判断此句柄是否是正在活动中的窗口
 * @param Handle
 * @returns
 */
export declare function isHandleWindowVisible(Handle: number | HWND): boolean;
/**
 * 关闭此句柄对应的窗口
 * @param Handle
 * @returns
 */
export declare function lookHandleCloseWindow(Handle: number | HWND): boolean;
/**
 * 获取此句柄的标题
 * @param Handle
 * @returns
 */
export declare function lookHandleGetTitle(Handle: number | HWND): string | null;
/**
 * 设置此句柄的标题
 * @param Handle
 * @param title
 * @returns
 */
export declare function lookHandleSetTitle(Handle: number | HWND, title: string): boolean;
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
export declare const setShowWindow: typeof lookHandleShowWindow;
/**
 * 关闭此句柄对应的窗口
 * @param Handle
 * @returns
 */
export declare const setCloseWindow: typeof lookHandleCloseWindow;
/**
 * 获取此句柄的标题
 * @param Handle
 * @returns
 */
export declare const getWindowTitle: typeof lookHandleGetTitle;
/**
 * 设置此句柄的标题
 * @param Handle
 * @param title
 * @returns
 */
export declare const setWindowTitle: typeof lookHandleSetTitle;
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
export declare function lookHandleShowWindow(Handle: number | HWND, SetShowType: 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11): boolean;
/**
 * 设置窗口不透明度 0-255
 * @param Handle
 * @param Transparent 0-255
 * @returns
 */
export declare function setHandleTransparent(Handle: number | HWND, Transparent: number): void;
/**
 * 设置窗口是否支持响应事件(鼠标键盘点击)
 * @param Handle
 * @param Enabled
 * @returns
 */
export declare function setWindowEnabled(Handle: number | HWND, Enabled: boolean): boolean;
/**
 * 设置窗口焦点
 * @param Handle
 * @returns
 */
export declare function setWindowFocus(Handle: number | HWND): boolean;
/**
 * 设置窗口顶设
 * @param Handle
 * @returns
 */
export declare function setWindowTop(Handle: number | HWND): boolean;
/**
 * 刷新该窗口
 * @param Handle
 * @returns
 */
export declare function updateWindow(Handle: number | HWND): boolean;
/**
 * 窗口抖动
 * @param Handle
 * @returns
 */
export declare function windowJitter(Handle: number | HWND): void;
/**
 * 判断窗口是否被顶设
 * @param Handle
 * @returns
 */
export declare function hasWindowTop(Handle: number | HWND): boolean;
/**
 * 关闭该句柄窗口(可关闭托盘)(发送关闭消息)
 */
export declare function closedHandle(Handle: number | HWND): undefined;
/**
 * 获取所有HidUsb设备（仅限HID设备)
 * @returns HidUsb设备数组
 */
export declare function getHidUsbList(): HMC.HID_USB_INFO[];
/**
 * 获取鼠标所在位置
 * @returns 鼠标所在位置
 */
export declare function getMetrics(): HMC.MousePosn;
/**
 * 获取鼠标之前64个位置
 * @returns 之前64个位置
 */
export declare function getMouseMovePoints(): Array<HMC.MouseMovePoints>;
/**
 * 获取屏幕大小
 */
export declare function getDeviceCaps(): HMC.DeviceCaps;
/**禁用/启用系统键盘鼠标钩子
  * @param HOOK 是否启用系统键盘鼠标钩子
  !注意该功能很危险 主要用于自动化防止误操作 用户锁屏  禁止用于非法用途
  *手动解锁方式 Ctrl+Alt+Del   => esc
  !请注意 你需要确保你的解锁代码  运行没有任何错误或者有定时解锁
  否则有可能导致用户无法正常使用
  **/
export declare function SetSystemHOOK(HOOK: boolean): boolean;
/**
 * 获取四大按钮(`alt`  `ctrl`  `win`  `shift` )是否按下
 * @returns
 */
export declare function getBasicKeys(): HMC.BASIC_KEYS;
/**
 * 获取剪贴板文本
 * @returns 剪贴板文本
 */
export declare function getClipboardText(): string;
/**
 * 设置剪贴板文本
 * @param text 文本
 * @returns
 */
export declare function setClipboardText(text: string): void;
/**
 * 清空剪贴版
 * @returns 处理结果
 */
export declare function clearClipboard(): boolean;
/** 获取详细进程列表（慢20ms）**/
export declare function getDetailsProcessList(): {
    pid: number;
    name: string;
    path: string;
}[];
/** 获取进程列表**/
export declare function getProcessList(): {
    pid: number;
    name: string;
    path: string;
}[];
/**获取活动窗口的进程id */
export declare function getForegroundWindowProcessID(): number | null;
/**获取鼠标所在窗口的进程名 */
export declare function getPointWindowName(): string;
/**获取鼠标所在窗口的进程id */
export declare function getPointWindowProcessId(): number;
/**
 * 获取进程名
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessName(ProcessID: number): string | null;
/**
 * 获取进程可执行文件位置
 * @param ProcessName 进程名
 * @returns 进程id
 */
export declare function getProcessidFilePath(ProcessID: number): string | null;
/**
 * 获取快捷方式的信息
 * @param LnkPath 快捷方式路径
 * @returns
 */
export declare function getShortcutLink(LnkPath: string): HMC.SHORTCUT_LINK;
/**系统空闲时间 */
export declare function getSystemIdleTime(): number;
/**
 * 设置系统右键菜单 例如win自带的系统菜单就很丑还不能禁用  使用这个禁用
 * @param Handle 句柄
 * @param boolean 是否禁用
 * @returns
 */
export declare function getSystemMenu(Handle: number | HWND, boolean: boolean): void;
/**获取托盘图标列表 */
export declare function getTrayList(): HMC.TRAY_ICON[];
/**判断该按键是否被按下  https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getkeystate **/
export declare function hasKeyActivate(KeysEvent: number): boolean;
/**
 * 判断进程id 是否存在
 * @param ProcessID 进程id
 * @returns
 */
export declare function hasProcess(...ProcessMatch: Array<number | string | Array<number | string>>): boolean;
/**
 * 当前程序是否拥有管理员权限
 * @returns
 */
export declare function isAdmin(): boolean;
/**
 * 判断进程id 是否存在
 * @param ProcessID 进程id
 * @returns
 */
export declare function isProcess(ProcessID: number): boolean;
/**判断当前系统是否是64位 */
export declare function isSystemX64(): boolean;
/**
 * 结束该进程
 * @param ProcessID
 * @returns
 */
export declare function killProcess(ProcessID: number): boolean;
export declare function killProcess(ProcessID: string | RegExp): {
    pid: number;
    kill: boolean;
    name: string;
}[];
/**
 * 左键点击
 * @param ms 延迟
 * @returns
 */
export declare function leftClick(ms?: number): void;
/**
 * 消息窗口(调用 win-api)
 * @param message 消息内容
 * @param title 标题
 * @param UINT_String 显示窗口类型 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
 * @description 衍生api(已预设): `confirm`  `alert` `MessageError` `MessageStop`
 * @returns
 */
export declare function messageBox(message: string, title: string, MB_UINT: HMC.MB_UINT): 1 | 2 | 3 | 4 | 5 | 6 | 7 | 10 | 11;
/**自定义鼠标事件 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mouse_event **/
export declare function mouse(mouse_event: HMC.mouse_event, ms?: number): void;
/**
 * 在资源管理器中显示并选中该文件
 * @param Path 路径
 * @returns
 */
export declare function openExternal(Path: string): boolean;
/**
 * 用默认应用打开该 （文件/文件夹）
 * @param Path 文件路径
 * @returns
 */
export declare function openPath(Path: string): boolean;
/**
 * 用默认浏览器打开这条url
 * @param URL url
 * @returns
 */
export declare function openURL(URL: string): boolean;
/**
 * 电源控制
 */
export declare const powerControl: {
    (Set: 
    /**关机 */
    1001 | 
    /**重启 */
    1002 | 
    /**注销 */
    1003 | 
    /**锁定 */
    1005): void;
    /**关机 */
    1001(): void;
    /**重启 */
    1002(): void;
    /**注销 */
    1003(): void;
    /**锁定 */
    1005(): void;
    /**关机 */
    shutDown(): void;
    /**重启 */
    restart(): void;
    /**注销 */
    cancellation(): void;
    /**锁定 */
    lock(): void;
};
/**
 * 右键点击
 * @param ms 延迟
 * @returns
 */
export declare function rightClick(ms?: number): void;
/**
 * 设置鼠标位置
 * @param x 左边开始的像素数坐标
 * @param y 上方到下方的像素数坐标
 * @param Must 尝试必须到达此坐标 (每 MustTime /5 ms 检测一次坐标是否到达 如果未到达则重试)
 * @param MustTime 锁定键盘到达此坐标的有效时间 ms
 * @returns
 */
export declare function setCursorPos(x: number, y: number): boolean;
export declare function setCursorPos(x: number, y: number, Must: true, MustTime?: number): Promise<boolean>;
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
export declare function setShortcutLink(LnkPath: string, FilePath: string, work_dir: string, desc: string, args: string | string[], iShowCmd: number, icon: string, iconIndex: number): boolean;
export declare function setShortcutLink(LnkPath: string, FilePath: string, work_dir?: string, desc?: string, args?: string | string[], iShowCmd?: number): boolean;
export declare function setShortcutLink(LnkPath: string, FilePath: string): boolean;
export declare function setShortcutLink(LnkPath: string, Shortcut: HMC.SHORTCUT_LINK): boolean;
/**
 * 创建文件软链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns
 */
export declare function createSymlink(LinkPath: string, sourcePath: string): boolean;
/**
 * 创建文件夹软链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns
 */
export declare function createDirSymlink(LinkPath: string, sourcePath: string): boolean;
/**
 * 创建文件硬链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns
 */
export declare function createHardLink(LinkPath: string, sourcePath: string): boolean;
/**打开显示器 */
export declare function showMonitors(show?: boolean): void;
/**关闭显示器 */
export declare function shutMonitors(show?: boolean): void;
/**
 * `Sync` 同步阻塞(进程)
 * @param awaitTime
 * @returns
 */
export declare function sleep(awaitTime: number): void;
/**
 * `async` 异步阻塞(进程)
 * @param awaitTime
 * @returns
 */
export declare function Sleep(awaitTime: number, Sync?: boolean): Promise<unknown>;
/**
 * 系统启动到现在的时间(毫秒)
 * @returns
 */
export declare function systemStartTime(): number;
/**
* 获取所有窗口的信息
**/
export declare function getAllWindows(isWindows: boolean, initialize: boolean): HMC.GET_ALL_WINDOWS_INFO[];
/**
 * 检索指定窗口所属的类的名称
 * @param Handle 句柄
 * @returns
 */
export declare function getWindowClassName(Handle: number | HWND): string;
/**
 * 获取窗口类关联代码
 * @param Handle 句柄
 * @returns
 */
export declare function getWindowStyle(Handle: number | HWND): number;
/**
 * 获取WebView2的信息
 * @returns
 */
export declare function getWebView2Info(): HMC.WebView2Info;
/**
 * 下载并安装WebView2
 */
export declare function WebView2OnlineInstall(): Promise<void>;
/**
 * 当前系统是否安装了 WebView2
 * @returns
 */
export declare function hasWebView2(): boolean;
/**
 * 判断TCP(服务)端口号正在使用/系统占用
 * @param port TCP端口
 * @returns
 */
export declare function hasPortTCP(port: number): Promise<boolean>;
export declare function hasPortTCP(port: number, callBack: (hasPort: boolean) => unknown): void;
export declare const _KeyboardcodeEmenList: Map<number, [string, string | null, number, number] | [string, string | null, number, number, import("./vkKey").VK_Nickname]>;
export declare const _KeyboardcodeComparisonTable: Map<string, number>;
/**
 * 判断UDP端口号正在使用/系统占用
 * @param port TCP端口
 * @returns
 */
export declare function hasPortUDP(port: number): Promise<boolean>;
export declare function hasPortUDP(port: number, callBack: (hasPort: boolean) => unknown): void;
/**
 * 格式化 驱动器路径 ('\Device\HarddiskVolume2' => "D:\")
 */
export declare function formatVolumePath(VolumePath: string): string;
/**
 * 获取当前文件系统的驱动器名称及路径
 * @returns
 */
export declare function getVolumeList(): HMC.Volume[];
/**
 * 枚举进程id 的加载的模块路径
 * @param ProcessID
 * @returns
 */
export declare function getModulePathList(ProcessID: number): string[];
/**
 * 枚举进程id的句柄
 * @param ProcessID 被枚举的进程id
 * @returns
 */
export declare function enumProcessHandle(ProcessID: number): Promise<HMC.ProcessHandle[]>;
/**
 * 枚举进程id的句柄
 * @param ProcessID 被枚举的进程id
 * @param CallBack 枚举时候的回调
 * @returns
 */
export declare function enumProcessHandle(ProcessID: number, CallBack: (PHandle: HMC.ProcessHandle) => void): void;
/**
* 枚举进程的线程id
* @param ProcessID 进程id
* @param returnDetail 是否返回 THREADENTRY32 为`false`或者为空则返回线程id
*/
export declare function getProcessThreadList(ProcessID: number, returnDetail?: false): number[];
/**
 *
 * @param ProcessID 进程id
 * @param returnDetail 为`true` 则返回THREADENTRY32
 */
export declare function getProcessThreadList(ProcessID: number, returnDetail: true): HMC.THREADENTRY32[];
/**
 * 枚举进程的线程id
 * @param ProcessID 进程id
 */
export declare function getProcessThreadList(ProcessID: number): number[];
/**
 * 获取所有该进程下的 子进程id
 * @param ProcessID 进程id
 * @returns
 */
export declare function getSubProcessID(ProcessID: number): number[];
/**
 * 获取进程id的主进程
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessParentProcessID(ProcessID: number, is_SessionCache?: boolean): HMC.PROCESSENTRY_V2 | null;
/**
 * 枚举所有进程id的句柄
 * @param ProcessID 被枚举的进程id
 * @param CallBack 枚举时候的回调
 * @returns
 */
export declare function enumAllProcessHandle(CallBack?: (PHandle: HMC.PROCESSENTRY) => void): Promise<unknown> | undefined;
/**
 * 获取鼠标所在坐标
 * @returns
 */
export declare function getCursorPos(): null | {
    x: number;
    y: number;
};
export declare const version: string;
export declare const desc: string;
export declare const platform: string;
export declare const Window: {
    isInMonitor: typeof isInMonitorWindow;
    isMouseMonitor: typeof isMouseMonitorWindow;
    HWND: typeof HWND;
    setMode: typeof setWindowMode;
    getAllWindows: typeof getAllWindows;
    getAllHandle: typeof getAllWindowsHandle;
    watchPoint: typeof WatchWindowPoint;
    watchtFocus: typeof WatchWindowForeground;
    getFocus: typeof getForegroundWindow;
    getMain: typeof getMainWindow;
    getPoint: typeof getPointWindow;
    getProcessHandle: typeof getProcessHandle;
    getPointMain: typeof getPointWindowMain;
    setTaskbarVisible: typeof SetWindowInTaskbarVisible;
    getProcessID: typeof getHandleProcessID;
    getRect: typeof getWindowRect;
    isEnabled: typeof isEnabled;
    isHandle: typeof isHandle;
    hasHandle: typeof isHandle;
    isVisible: typeof isHandleWindowVisible;
    close: typeof lookHandleCloseWindow;
    getTitle: typeof lookHandleGetTitle;
    setTitle: typeof lookHandleSetTitle;
    setShowWindow: typeof lookHandleShowWindow;
    setTransparent: typeof setHandleTransparent;
    setEnabled: typeof setWindowEnabled;
    setFocus: typeof setWindowFocus;
    setTop: typeof setWindowTop;
    update: typeof updateWindow;
    jitter: typeof windowJitter;
    hasTop: typeof hasWindowTop;
    closed: typeof closedHandle;
    getFocusProcessID: typeof getForegroundWindowProcessID;
    getPointName: typeof getPointWindowName;
    getPointProcessId: typeof getPointWindowProcessId;
    enumChild: typeof enumChildWindows;
    console: {
        hide: typeof hideConsole;
        show: typeof showConsole;
        get: typeof getConsoleHandle;
        blockInput: typeof SetBlockInput;
    };
    getStyle: typeof getWindowStyle;
    getClassName: typeof getWindowClassName;
};
export declare const Watch: {
    clipboard: typeof watchClipboard;
    usb: typeof watchUSB;
    windowFocus: typeof WatchWindowForeground;
    windowPoint: typeof WatchWindowPoint;
    process: typeof processWatchdog;
};
export declare const Clipboard: {
    clear: typeof clearClipboard;
    readText: typeof getClipboardText;
    readFilePaths: typeof getClipboardFilePaths;
    writeText: typeof setClipboardText;
    writeFilePaths: typeof setClipboardFilePaths;
    sequence: typeof getClipboardSequenceNumber;
    watch: typeof watchClipboard;
};
declare class MousePoint {
    /**从右到左的像素数 */
    x: number;
    /**从上到下的像素数 */
    y: number;
    /**是否被按下 */
    isDown: boolean;
    mouseKeyCode: HMC.MouseKey;
    event: HMC.MouseKeyName;
    private _MouseNextSession;
    constructor(str: `${number}|${number}|${HMC.MouseKey}` | HMC.MouseEventDataAll);
    /**
     * 鼠标左键按下
     */
    get isLeft(): boolean;
    /**
     * 鼠标右键被按下
     */
    get isRight(): boolean;
    /**
     * 鼠标中键被按下
     */
    get isMiddle(): boolean;
    /**
     * 在此坐标模拟进行单击
     * @param awitMs
     */
    click(awitMs?: number): Promise<void>;
    /**
     * 模拟右键在此坐标按下和释放鼠标中键
     * @param awitMs
     */
    middle(awitMs?: number): Promise<void>;
    /**
     * 在此坐标按下模拟右键点击
     * @param awitMs
     */
    rClick(awitMs?: number): Promise<void>;
    /**
     * 双击
     * @param doubleAwitMs 双击间隔
     * @param clickAwitMs 模拟点击时间间隔
     */
    doubleClick(doubleAwitMs?: number, clickAwitMs?: number): void;
    /**
     * 移动鼠标位置
     * @param x
     * @param y
     */
    moveMouse(x: number, y: number): void;
}
declare class Keyboard {
    /**
     * 是否按下了shift
     */
    get shiftKey(): boolean;
    /***
     * 是否按下了alt
     */
    get altKey(): boolean;
    /***
     * 是否按下了ctrl
     */
    get ctrlKey(): boolean;
    /***
     * 是否按下了win
     */
    get winKey(): boolean;
    vKey: VK_VirtualKey;
    key: VK_key;
    code: VK_code;
    /**
     * 键值代码
     */
    keyCode: VK_keyCode;
    constructor(str: `${number}|${0 | 1}`);
    /**
     * 是否被按下
     */
    private __isDown;
    /**是否被按下 */
    get isDown(): boolean;
}
declare class Iohook_Mouse {
    private _onlistenerCountList;
    private _oncelistenerCountList;
    _history_list: Array<HMC.MouseEventDataOK>;
    _screen_Information: null | HMC.DeviceCaps;
    private _Close;
    _direction_percentage: number;
    constructor();
    /**
     * 获取之前的0-64个记录
     */
    get history(): Array<HMC.MouseEventDataOK>;
    once(eventName: "start" | "close", listener: () => void): this;
    once(eventName: "mouse", listener: (MousePoint: MousePoint, MouseNextSession: HMC.MouseEventDataAll) => void): this;
    once(listener: (MousePoint: MousePoint) => void): this;
    once(eventName: "button", listener: (event: HMC.MouseKeyName, MousePoint: MousePoint) => void): this;
    once(eventName: "wheel", listener: (MousePoint: MousePoint) => void): this;
    once(eventName: "move", listener: (x: number, y: number, MousePoint: MousePoint, data: HMC.MouseMoveEventData) => void): this;
    on(listener: (MousePoint: MousePoint) => void): this;
    on(eventName: "start" | "close", listener: () => void): this;
    on(eventName: "mouse", listener: (MousePoint: MousePoint, MouseNextSession: HMC.MouseEventDataAll) => void): this;
    on(eventName: "button", listener: (event: HMC.MouseKeyName, MousePoint: MousePoint) => void): this;
    on(eventName: "wheel", listener: (MousePoint: MousePoint) => void): this;
    on(eventName: "move", listener: (x: number, y: number, MousePoint: MousePoint, data: HMC.MouseMoveEventData) => void): this;
    /**
     * 开始
     * @returns
     */
    start(): void;
    /**
     * 结束
     */
    close(): void;
    emit(eventName: "start" | "close"): boolean;
    emit(eventName: "move", x: number, y: number, MousePoint: MousePoint, data: HMC.MouseMoveEventData): boolean;
    emit(eventName: "button", event: HMC.MouseKeyName, MousePoint: MousePoint): boolean;
    emit(eventName: "wheel", MousePoint: MousePoint): boolean;
    emit(eventName: "mouse", MousePoint: MousePoint, MouseNextSession: HMC.MouseEventDataOK): boolean;
    emit(eventName: "drag", x: number, y: number, direction: HMC.direction, MousePoint: MousePoint, data: HMC.MouseMoveEventData): boolean;
    /**
     * 关闭监听
     * @param eventName
     * @param data
     * @returns
     */
    off(eventName: "start" | "drag" | "close" | "mouse" | "move" | "data" | "button" | "wheel", treatmentMode: "on" | "once" | Function, data?: Function): boolean;
}
/**
 * 鼠标左键被按下
 * @returns
 */
export declare function hasMouseLeftActivate(): boolean;
/**
 * 鼠标右键被按下
 */
export declare function hasMouseRightActivate(): boolean;
/**
 * 鼠标中键被按下
 */
export declare function hasMouseMiddleActivate(): boolean;
/**
 * 判断鼠标三按钮是否被按下
 * @returns
 */
export declare function hasMouseBtnActivate(): {
    left: boolean;
    right: boolean;
    middle: boolean;
};
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
export declare const mouseHook: Iohook_Mouse;
/**
 * 通过可执行文件或者带有图标的文件设置窗口图标
 * @param handle 句柄
 * @param Extract 可执行文件/Dll/文件
 * @param index 图标位置索引 例如文件显示的图标默认是0
 */
export declare function setWindowIconForExtract(handle: number, Extract: string, index: number): void;
/**
    * 截屏指定的宽高坐标 并将其存储写入为文件
    * @param FilePath 文件路径
    * @param x 从左边的哪里开始 为空为0
    * @param y 从顶部的哪里开始 为空为0
    * @param width 宽度
    * @param height 高度
    */
export declare function captureBmpToFile(FilePath: string, x: number | null, y: number | null, width: number | null, height: number | null): void;
/**
 * 发送键盘事件
 * @param keyCode 键值
 * @param keyDown 是否按下
 *
 */
export declare function sendKeyboard(keyCode: number | string, keyDown: boolean | null): void;
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
export declare function sendKeyboardSequence(...keys: Array<{
    key: number | string;
    down?: boolean;
    ms?: number;
} | [number | string, boolean | number | null, number]>): void;
/**
 * 获取屏幕指定区域的颜色
 * @param x 左边开始的坐标
 * @param y 从上面开始的坐标
 * @returns
 */
export declare function getColor(x: number, y: number): HMC.Color;
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
export declare function sendBasicKeys(basicCout: HMC.BasicCout, KeyCode?: number | string): void;
/**
 * 执行标准快捷键
 * @param basicKeysStr 快捷键内容
 * @example ```javascript
 * // ctrl + shift +A
 * hmc.sendBasicKeys("ctrl+shift+A");
 *
 */
export declare function sendBasicKeys(basicKeysStr: string): void;
/**
 * 执行标准快捷键(标准化输入)
 * @param ctrlKey 组合中含有ctrl
 * @param shiftKey 组合中含有shift
 * @param altKey 组合中含有alt
 * @param winKey 组合中含有win
 * @param KeyCode 键盘隐射值
 */
export declare function sendBasicKeys(ctrlKey: boolean, shiftKey: boolean, altKey: boolean, winKey: boolean, KeyCode: number | string): void;
/**
 * 获取指定进程的工作目录
 * @time 5.449ms
 * @description 由于跨进程权限问题 不保证获取得到
 * !此功能需要读取进程内存
 * @module 异步async
 * @param pid
 */
export declare function getProcessCwd2(pid: number): Promise<string | null>;
/**
 * 获取指定进程的工作目录
 * @time 0.435ms
 * @description 由于跨进程权限问题 不保证获取得到
 * !此功能需要读取进程内存
 * @module 同步Sync
 * @param pid
 */
export declare function getProcessCwd2Sync(pid: number): string | null;
/**
 * 获取指定进程得出命令行
 * @time 1.095ms
 * @description 由于跨进程权限问题 不保证获取得到
 * ?此功能在win8及以下系统 需要读取进程内存
 * @module 异步async
 * @param pid 进程id
 */
export declare function getProcessCommand2(pid: number): Promise<string>;
/**
 * 获取指定进程得出命令行
 * @time 0.386ms
 * @description 由于跨进程权限问题 不保证获取得到
 * ?此功能在win8及以下系统 需要读取进程内存
 * @module 同步Sync
 * @param pid
 */
export declare function getProcessCommand2Sync(pid: number): string | null;
/**
 * 限制鼠标光标可移动范围 (异步)
 * @description 可以调用 stop 提前结束
 * ?最高不允许超过30000ms (30秒) 最低不允许低于31ms
 * ?范围为正方形 如果没有设置right与bottom的值则将限制为1x1的正方形 (不可动)
 * @param ms 本次限制的时间
 * @param x 限制左边初始化点的位置
 * @param y 限制顶部初始化点的位置
 * @param right 允许的范围(左边到右边部)
 * @param bottom 允许光标移动的范围(顶到底部)
 */
export declare function setLimitMouseRange(ms: number, x: number, y: number, right?: number, bottom?: number): {
    ms: number;
    x: number;
    y: number;
    right: number;
    bottom: number;
    closed: boolean;
    /**
     * 停止本次
     * @returns
     */
    close(): boolean;
    /**
     * 是否正在执行中
     * @returns
     */
    has(): boolean;
};
declare class Iohook_Keyboard {
    private _onlistenerCountList;
    private _oncelistenerCountList;
    private _Close;
    constructor();
    once(eventName: "start" | "close", listener: () => void): this;
    once(eventName: "data", listener: (data: (`${number}|0` | `${number}|1`)[]) => void): this;
    once(eventName: "change", listener: (KeyboardPoint: Keyboard) => void): this;
    once(listener: (KeyboardPoint: Keyboard) => void): this;
    on(eventName: "start" | "close", listener: () => void): this;
    on(eventName: "data", listener: (data: (`${number}|0` | `${number}|1`)[]) => void): this;
    on(eventName: "change", listener: (KeyboardPoint: Keyboard) => void): this;
    on(listener: (KeyboardPoint: Keyboard) => void): this;
    /**
     * 开始
     * @returns
     */
    start(): false;
    /**
     * 结束
     */
    close(): void;
    emit(eventName: "data", data: (`${number}|0` | `${number}|1`)[]): boolean;
    emit(eventName: "start" | "close"): boolean;
    emit(eventName: "change", KeyboardPoint: Keyboard): boolean;
    /**
     * 关闭监听
     * @param eventName
     * @param data
     * @returns
     */
    off(eventName: "start" | "close" | "change" | "data", treatmentMode: "on" | "once" | Function, data?: Function): boolean;
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
export declare const keyboardHook: Iohook_Keyboard;
export declare function getLastInputTime(): number;
export declare const Auto: {
    setLimitMouseRange: typeof setLimitMouseRange;
    hasMouseLeftActivate: typeof hasMouseLeftActivate;
    hasMouseRightActivate: typeof hasMouseRightActivate;
    hasMouseMiddleActivate: typeof hasMouseMiddleActivate;
    hasMouseBtnActivate: typeof hasMouseBtnActivate;
    sendKeyboard: typeof sendKeyboard;
    sendKeyboardSequence: typeof sendKeyboardSequence;
    getColor: typeof getColor;
    sendBasicKeys: typeof sendBasicKeys;
    setWindowEnabled: typeof setWindowEnabled;
    setCursorPos: typeof setCursorPos;
    mouse: typeof mouse;
    rightClick: typeof rightClick;
    leftClick: typeof leftClick;
    getBasicKeys: typeof getBasicKeys;
    getMouseMovePoints: typeof getMouseMovePoints;
    powerControl: {
        (Set: 
        /**关机 */
        1001 | 
        /**重启 */
        1002 | 
        /**注销 */
        1003 | 
        /**锁定 */
        1005): void;
        /**关机 */
        1001(): void;
        /**重启 */
        1002(): void;
        /**注销 */
        1003(): void;
        /**锁定 */
        1005(): void;
        /**关机 */
        shutDown(): void;
        /**重启 */
        restart(): void;
        /**注销 */
        cancellation(): void;
        /**锁定 */
        lock(): void;
    };
    SetBlockInput: typeof SetBlockInput;
    SetSystemHOOK: typeof SetSystemHOOK;
    hasKeyActivate: typeof hasKeyActivate;
    mouseHook: Iohook_Mouse;
    keyboardHook: Iohook_Keyboard;
    getCursorPos: typeof getCursorPos;
    getLastInputTime: typeof getLastInputTime;
};
export declare const Usb: {
    getHub: typeof getHidUsbList;
    getDevsInfo: typeof getUsbDevsInfo;
    watch: typeof watchUSB;
};
export declare const Shell: {
    trash: typeof deleteFile;
    openApp: typeof openApp;
    getShortcutLink: typeof getShortcutLink;
    setShortcutLink: typeof setShortcutLink;
    freePort: typeof freePort;
    createSymlink: typeof createSymlink;
    createDirSymlink: typeof createDirSymlink;
    createHardLink: typeof createHardLink;
};
export declare const Process: {
    watch: typeof processWatchdog;
    kill: typeof killProcess;
    killMatch: typeof killProcessName;
    getList: typeof getProcessList;
    getHandle: typeof getProcessHandle;
    getName: typeof getProcessName;
    getPath: typeof getProcessidFilePath;
    getFocus: typeof getForegroundWindowProcessID;
    has: typeof hasProcess;
    match: typeof getProcessNameList;
    matchDetails: typeof getDetailsProcessNameList;
    getDetailsList: typeof getDetailsProcessList;
    parentID: typeof getProcessParentProcessID;
    mianPID: typeof getProcessParentProcessID;
    subPID: typeof getSubProcessID;
    threadList: typeof getProcessThreadList;
};
export declare const registr: {
    /**
     * 直达路径解析
     * @param Path 全路径(直达路径)
     * @param atkey 是否将最后一个值解释为键
     * @returns
     */
    analysisDirectPath: typeof analysisDirectPath;
    /**
     * 判断注册表中是否有该键值
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06591796875 ms
     * @returns
     */
    has: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 获取内容(文本)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.108ms
     * @returns
     */
    get: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => string;
    /**
     * 设置键值对
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Value 数据
     * @time 2.02392578125 ms
     * @returns
     */
    set: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string, value: string) => boolean;
    /**
     * 删除数据
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.076904296875 ms
     * @returns
     */
    remove: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 枚举键值
     * @param HKEY 根路径
     * @param Path 路径
     * @time 0.06689453125 ms
     * @returns
     */
    keys: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => string[];
    /**
     * 将当前的路径的注册表值转表
     * @param HKEY
     * @param Path
     */
    list: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => {
        [key: string]: string | Buffer;
        "": string | Buffer;
    };
    /**
     * 创建新的路径
     * @param HKEY 根路径
     * @param Path 路径
     * @time 2.02392578125 ms
     * @returns
     */
    create: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 打开一个注册表路径并返回一些实用方法
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    open: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => {
        /**
         * 获取全路径
         */
        readonly path: string;
        /**
         * 设置一个值
         * @param data 数据
         */
        set(data: string): boolean;
        /**
         * 获取内容
         * @returns
         */
        get(): string;
        /**
         * 获取该内容并将其视为二进制缓冲区
         * @returns 二进制缓冲区
         */
        getBuff(): Buffer;
        /**
         * 获取该内容并将其视为数字
         * @returns 数字
         */
        getNumber(): number;
        /**
         * 枚举当前路径下的键
         * @returns 键 数组
         */
        keys(): string[];
        /**
         * 将当前目录转为对象
         */
        list(): {
            [key: string]: string | Buffer;
            "": string | Buffer;
        };
    };
    /**
     * 判断注册表中是否有该键值
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06591796875 ms
     * @returns
     */
    readonly hasRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 将当前的路径的注册表值转表
     * @param HKEY
     * @param Path
     */
    readonly listRegistrPath: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => {
        [key: string]: string | Buffer;
        "": string | Buffer;
    };
    /**
     * 枚举键值
     * @param HKEY 根路径
     * @param Path 路径
     * @time 0.06689453125 ms
     * @returns
     */
    readonly enumRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => string[];
    /**
     * 删除数据
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.076904296875 ms
     * @returns
     */
    readonly removeStringRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 设置键值对
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Value 数据
     * @time 2.02392578125 ms
     * @returns
     */
    readonly setRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string, value: string) => boolean;
    /**
     * 获取内容(文本)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.108ms
     * @returns
     */
    readonly getStringRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => string;
    /**
     * 获取内容(数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.10888671875 ms
     * @returns
     */
    getNumberRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => number;
    /**
     * 创建新的路径
     * @param HKEY 根路径
     * @param Path 路径
     * @time 2.02392578125 ms
     * @returns
     */
    readonly createPathRegistr: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 获取内容(二进制 Buffer)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06787109375 ms
     * @returns
     */
    getRegistrBuffValue: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => void | Buffer;
    /**
     * 打开一个注册表路径并返回一些实用方法
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    readonly openRegKey: typeof open;
    getRegistrQword: typeof getRegistrQword;
    getRegistrDword: typeof getRegistrDword;
    setRegistrQword: typeof setRegistrQword;
    setRegistrDword: typeof setRegistrDword;
    removeStringRegValue: typeof removeStringRegValue;
    removeStringRegKeyWalk: typeof removeStringRegKeyWalk;
    removeStringTree: typeof removeStringTree;
    isRegistrTreeKey: typeof isRegistrTreeKey;
};
/**
* 创建管道并执行命令
* @param cmd 命令
*/
export declare function _popen(cmd: string): string;
/**
 * 判断互斥体文本是否存在
 * @param MutexName 互斥体文本
 * @returns
 */
export declare function hasMutex(MutexName: string): boolean;
/**
 * 创建互斥体文本并返回结果
 * ?(无法移除 除非当前进程退出 互斥体具有唯一性)
 * ? 可以用于判断进程是否重复启动
 * @param MutexName 互斥体文本
 * @returns
 */
export declare function createMutex(MutexName: string): boolean;
/**
* 创建管道并执行命令
* @param cmd 命令
*/
export declare function popen(cmd: string): string;
/**
 * 获取当前进程的环境变量
 * @returns
 */
export declare function getAllEnv(): {
    [key: string]: string;
};
/**
 * 获取指定key的环境变量
 * @param key
 * @returns
 */
export declare function getenv(key: string): string;
/**
 * 获取指定UDP端口的pid
 * @deprecated 此api已经废弃 请使用 net-win32 模块代替
 * @param Port
 * @returns
 */
export declare function getUDPPortProcessID(Port: number): null;
/**
 * 添加环境变量(不写入系统)
 * @param key
 * @param data
 * @returns
 */
export declare function putenv(key: string, data: string | string[]): void;
/**
 * 获取指定TCP端口的pid
 * @deprecated 此api已经废弃 请使用 net-win32 模块代替
 * @param Port
 * @returns
 */
export declare function getTCPPortProcessID(Port: number): null;
/**
 * 通过标题或类名搜索窗口句柄
 * @param className 类名
 * @param titleName 标题
 */
export declare function findWindow(className?: string | null, titleName?: string | null): number | null;
/**
 * 搜索窗口或子窗口
 * @param hWndParent 父窗口
 * @param hWndChildAfter 下級窗口
 * @param className 类名
 * @param titleName 标题
 */
export declare function findWindowEx(hWndParent: number | null | HWND, hWndChildAfter: number | null | HWND, className: string | null, titleName: string | null): number | null;
/**
 * 按照名称搜索进程
 * @param ProcessName
 * @returns
 */
export declare function findProcess(ProcessName: string | RegExp | number, isMacthFile?: boolean): HMC.enumProcessCont[];
/**
 * 获取指定进程的从启动到现在的时间 单位ms
 * @param ProcessID
 */
export declare function getProcessStartTime(ProcessID: number): number | null;
/**
 * 判断变量中是否存在指定值
 * - 用户
 * - 系统
 * @param key
 */
export declare function hasKeyExists(key: string): boolean;
/**
 * 判断用户变量中是否存在指定值
 * - 用户
 * @param key
 */
export declare function hasUseKeyExists(key: string): boolean;
/**
 * 判断系统变量中是否存在指定值
 * - 系统
 * @param key
 */
export declare function hasSysKeyExists(key: string): boolean;
/**
 * 通过当前的变量对变量内容进行解析
 * - 实时的
 * - HMC_x64.escapeEnvVariable("%AppData%\\hmc-win32")   log  ->  'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
 * @param input
 */
export declare function escapeEnvVariable(input: string): string;
/**
 * 删除一个用户变量
 * - 仅用户
 * @param key
 */
export declare function removeUserVariable(key: string): boolean;
/**
* 删除一个变量
*  - 用户
*  - 系统用户
* @param key
*/
export declare function removeVariable(key: string): boolean;
/**
 * 删除一个用户变量
 * - 仅用户
 * @param key
 */
export declare function removeSystemVariable(key: string): boolean;
/**
 * 获取一个在系统变量中的值
 * @param key
 * @param transMean 是否自动转义
 * - true %AppData%\\hmc-win32  -> 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
 * - false %AppData%\\hmc-win32 -> '%AppData%\\hmc-win32'
 * @default true
 */
export declare function getSystemVariable(key: string, transMean?: boolean): string;
/**
* 获取一个在用户变量中的值
* @param key
* @param transMean 是否自动转义
* - true %AppData%\\hmc-win32  -> 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
* - false %AppData%\\hmc-win32 -> '%AppData%\\hmc-win32'
* @default true
*/
export declare function getUserVariable(key: string, transMean?: boolean): string;
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
export declare function getVariableAnalysis(key: string): string;
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
export declare function putSystemVariable(key: string, value?: string, append?: boolean, transMean?: boolean): boolean;
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
export declare function setUserVariable(key: string, value?: string, append?: boolean, transMean?: boolean): boolean;
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
export declare function setSystemVariable(key: string, value?: string, append?: boolean, transMean?: boolean): boolean;
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
export declare function putUserVariable(key: string, value?: string, append?: boolean, transMean?: boolean): boolean;
/**
 * 获取所有的值 从环境读取 (进程环境)
 */
export declare function getVariableAll(): HMC.VariableList;
/**
 * 从注册表读取现在的真实环境变量 但不更新到进程环境
 * - 请注意这里 不会添加 进程的变量
 * @param key
 */
export declare function getRealGlobalVariableList(): HMC.VariableList;
/**
 * 获取用户变量的键列表
 */
export declare function getUserKeyList(): string[];
/**
 * 获取系统变量的键列表
 */
export declare function getSystemKeyList(): string[];
/**
 *
 * 从注册表中读取 变量并且写入到当前进程变量
 * @param remove 删除 已经消失的环境 到当前进程
 * @param update_add update 新的变量到当前进程
 * @param append 新的变量先尝试追加或者移除变量单值 而不是直接全部替换
 *  - 如果 update_add and remove  为false 此选项将被忽略
 *  - 如果 update_add and remove 同时为true 此选项将解析为全部替换
 * @param filter 过滤条件 (匹配则忽略)
 * - key name (不区分大小写)
 * - filter 一个返回布尔值的函数  (key: 键(大写), new_value: string | null | undefined, oid_value: string | null | undefined) => boolean
 * - key[] 数组 (不区分大小写)
 * - RegExp 正则 (key区分大小写(原始值))
* @returns
 */
export declare function updateThis(remove?: boolean, update_add?: boolean, append?: boolean, filter?: ((key: string, new_value: string | null | undefined, oid_value: string | null | undefined) => boolean) | string | string[] | RegExp): HMC.VarValueReBackData[];
export declare const getWindowProcess: typeof getHandleProcessID;
export declare const getProcessWindow: typeof getProcessHandle;
export declare const isWindowVisible: typeof isHandleWindowVisible;
export declare const closeWindow: typeof lookHandleCloseWindow;
export declare const setWindowShake: typeof windowJitter;
export declare const isWindowTop: typeof hasWindowTop;
export declare const getProcessFilePath: typeof getProcessidFilePath;
/**
   * 获取进程列表 (快照法)
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步
   * @time 66.428ms
   * @returns
   */
export declare function getAllProcessListSnp2(callback: (data_list: Array<HMC.PROCESSENTRY_V2>, err: null | Error) => void): void;
export declare function getAllProcessListSnp2(): Promise<Array<HMC.PROCESSENTRY_V2>>;
/**
   * 获取进程列表 (快照法)   带有一个临时缓冲 在1.2秒内提供高速读取
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步
   * @time 66.428ms
   * @returns
   */
export declare function getAllProcessListSnpSession2(callback: (data_list: Array<HMC.PROCESSENTRY_V2>, err: null | Error) => void): void;
export declare function getAllProcessListSnpSession2(): Promise<Array<HMC.PROCESSENTRY_V2>>;
/**
   * 获取进程列表 (快照法)   带有一个临时缓冲 在1.2秒内提供高速读取
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步
   * @time 66.428ms
   * @returns
   */
export declare function getAllProcessListSnpSession2Sync(): Array<HMC.PROCESSENTRY_V2>;
/**
 * 获取进程列表 (内核法)
 * - (可以获取内核软件和系统服务的名称)
 * - 请注意 内核法有可能被杀毒软件拦截
 * - 有概率第一次获取时失败
 * @module 异步
 * @time 30.542ms
 * @returns
 */
export declare function getAllProcessListNt2(callback: (data_list: Array<HMC.PSYSTEM_PROCESS_INFORMATION & {
    name: string;
    pid: number;
}> | null, err: null | Error) => void): void;
export declare function getAllProcessListNt2(): Promise<Array<HMC.PSYSTEM_PROCESS_INFORMATION & {
    name: string;
    pid: number;
}>>;
/**
 * 获取进程列表（枚举法）
 * - 枚举是最快的 最安全的 不会出现遗漏
 * @module 异步
 * @time  fn() 9.691ms     fn(true)61.681ms
 * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
 * @returns
 */
export declare function getAllProcessList2(callback: ((data_list: Array<{
    pid: number;
}> | null, err: null | Error) => void)): void;
export declare function getAllProcessList2(callback: ((data_list: Array<{
    pid: number;
    name: string;
    path: string;
}> | null, err: null | Error) => void), is_execPath: true): void;
export declare function getAllProcessList2(is_execPath: true): Promise<Array<{
    pid: number;
    name: string;
    path: string;
}>>;
export declare function getAllProcessList2(): Promise<Array<{
    pid: number;
}>>;
/**
 * 获取进程列表（枚举法）
 * - 枚举是最快的 最安全的 不会出现遗漏
 * @module 同步
 * @time  fn() 11.147ms     fn(true)44.633ms
 * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
 * @returns
 */
export declare function getAllProcessList2Sync(is_execPath?: true): Array<{
    pid: number;
    name: string;
    path: string;
}>;
export declare function getAllProcessList2Sync(): Array<{
    pid: number;
}>;
/**
 * 获取进程列表 (内核法)
 * - (可以获取内核软件和系统服务的名称)
 * - 请注意 内核法有可能被杀毒软件拦截
 * - 有概率第一次获取时失败
 * @module 同步
 * @time 30.542ms
 * @returns
 */
export declare function getAllProcessListNt2Sync(): Array<HMC.PSYSTEM_PROCESS_INFORMATION & {
    name: string;
    pid: number;
}>;
/**
 * 获取进程列表 (快照法)
 * - (一般用来枚举进程树)
 * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
 * @module 同步
 * @time 66.428ms
 * @returns
 */
export declare function getAllProcessListSnp2Sync(): Array<HMC.PROCESSENTRY_V2>;
/**
 * 获取匹配进程的 父进程信息
 * @param Process 需要被搜索的子进程 名称/pid/正则名称
 * @param is_SessionCache 是否启用缓冲区以提高检索速度 （缓冲区有效时间1.2秒）
 * @returns
 */
export declare function getProcessParentProcessMatch2(Process: string | RegExp, is_SessionCache?: boolean): Promise<Array<HMC.PROCESSENTRY_V2>>;
export declare function getProcessParentProcessMatch2(Process: number, is_SessionCache?: boolean): Promise<HMC.PROCESSENTRY_V2>;
/**
 * 获取匹配进程的 父进程信息
 * @param Process 需要被搜索的子进程 名称/pid/正则名称
 * @param is_SessionCache 是否启用缓冲区以提高检索速度 （缓冲区有效时间1.2秒）
 * @returns
 */
export declare function getProcessParentProcessMatch2Sync(Process: string | RegExp, is_SessionCache?: boolean): Array<HMC.PROCESSENTRY_V2>;
export declare function getProcessParentProcessMatch2Sync(Process: number, is_SessionCache?: boolean): HMC.PROCESSENTRY_V2 | null;
/**
 * 获取指定进程的可执行文件路径
 * @param ProcessID 进程id
 * @param callback 回调函数 如果没有则返回一个 Promise
 * @returns
 */
export declare function getProcessFilePath2(ProcessID: number, callback: (path: string | null, err: null | Error) => void): void;
export declare function getProcessFilePath2(ProcessID: number): Promise<string | null>;
/**
 * 获取指定进程的可执行文件路径
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessFilePath2Sync(ProcessID: number): string | null;
/**
 * 获取指定进程的可执行文件路径
 * @param ProcessID 进程id
 * @param callback 回调函数 如果没有则返回一个 Promise
 * @returns
 */
export declare function existProcess2(ProcessID: number, callback: (exist: boolean, err: null | Error) => void): void;
export declare function existProcess2(ProcessID: number): Promise<boolean>;
/**
 * 获取指定进程的可执行文件路径
 * @param ProcessID 进程id
 * @returns
 */
export declare function existProcess2Sync(ProcessID: number): boolean;
/**
 * 获取一个带有exe path 的进程列表
 * @returns
 */
export declare function getDetailsProcessList2(): {
    pid: number;
    name: string;
    path: string;
}[];
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @param is_SessionCache  是否使用缓存提高速度
 * @returns
 */
export declare function getProcessNameSnp2Sync(ProcessID: number, is_SessionCache?: boolean): string | null;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @param is_SessionCache  是否使用缓存提高速度
 * @returns
 */
export declare function getProcessNameSnp2(ProcessID: number, is_SessionCache?: boolean): Promise<null | string>;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessNameNt2Sync(ProcessID: number): string | null;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessNameNt2(ProcessID: number): Promise<null | string>;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessName2(ProcessID: number): Promise<null | string>;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessName2Sync(ProcessID: number): string | null;
/**
 * 按照名称搜索进程
 * @param ProcessName
 * @returns
 */
export declare function findProcess2(ProcessName: string | RegExp | number): Promise<{
    pid: number;
    name: string | null;
    path: string | null;
}[]>;
/**
 * 按照名称搜索进程
 * @param ProcessName
 * @returns
 */
export declare function findProcess2Sync(ProcessName: string | RegExp | number): Array<{
    pid: number;
    name: string;
    path: string;
}>;
export declare const Environment: {
    hasKeyExists: typeof hasKeyExists;
    hasUseKeyExists: typeof hasUseKeyExists;
    hasSysKeyExists: typeof hasSysKeyExists;
    escapeEnvVariable: typeof escapeEnvVariable;
    removeUserVariable: typeof removeUserVariable;
    removeVariable: typeof removeVariable;
    removeSystemVariable: typeof removeSystemVariable;
    getSystemVariable: typeof getSystemVariable;
    getUserVariable: typeof getUserVariable;
    getVariableAnalysis: typeof getVariableAnalysis;
    putSystemVariable: typeof putSystemVariable;
    putUserVariable: typeof putUserVariable;
    getVariableAll: typeof getVariableAll;
    getRealGlobalVariableList: typeof getRealGlobalVariableList;
    getUserKeyList: typeof getUserKeyList;
    getSystemKeyList: typeof getSystemKeyList;
    updateThis: typeof updateThis;
    setUserVariable: typeof setUserVariable;
    setSystemVariable: typeof setSystemVariable;
};
export declare const Registr: {
    /**
     * 直达路径解析
     * @param Path 全路径(直达路径)
     * @param atkey 是否将最后一个值解释为键
     * @returns
     */
    analysisDirectPath: typeof analysisDirectPath;
    /**
     * 判断注册表中是否有该键值
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06591796875 ms
     * @returns
     */
    has: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 获取内容(文本)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.108ms
     * @returns
     */
    get: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => string;
    /**
     * 设置键值对
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Value 数据
     * @time 2.02392578125 ms
     * @returns
     */
    set: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string, value: string) => boolean;
    /**
     * 删除数据
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.076904296875 ms
     * @returns
     */
    remove: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 枚举键值
     * @param HKEY 根路径
     * @param Path 路径
     * @time 0.06689453125 ms
     * @returns
     */
    keys: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => string[];
    /**
     * 将当前的路径的注册表值转表
     * @param HKEY
     * @param Path
     */
    list: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => {
        [key: string]: string | Buffer;
        "": string | Buffer;
    };
    /**
     * 创建新的路径
     * @param HKEY 根路径
     * @param Path 路径
     * @time 2.02392578125 ms
     * @returns
     */
    create: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 打开一个注册表路径并返回一些实用方法
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    open: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => {
        /**
         * 获取全路径
         */
        readonly path: string;
        /**
         * 设置一个值
         * @param data 数据
         */
        set(data: string): boolean;
        /**
         * 获取内容
         * @returns
         */
        get(): string;
        /**
         * 获取该内容并将其视为二进制缓冲区
         * @returns 二进制缓冲区
         */
        getBuff(): Buffer;
        /**
         * 获取该内容并将其视为数字
         * @returns 数字
         */
        getNumber(): number;
        /**
         * 枚举当前路径下的键
         * @returns 键 数组
         */
        keys(): string[];
        /**
         * 将当前目录转为对象
         */
        list(): {
            [key: string]: string | Buffer;
            "": string | Buffer;
        };
    };
    /**
     * 判断注册表中是否有该键值
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06591796875 ms
     * @returns
     */
    readonly hasRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 将当前的路径的注册表值转表
     * @param HKEY
     * @param Path
     */
    readonly listRegistrPath: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => {
        [key: string]: string | Buffer;
        "": string | Buffer;
    };
    /**
     * 枚举键值
     * @param HKEY 根路径
     * @param Path 路径
     * @time 0.06689453125 ms
     * @returns
     */
    readonly enumRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => string[];
    /**
     * 删除数据
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.076904296875 ms
     * @returns
     */
    readonly removeStringRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 设置键值对
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Value 数据
     * @time 2.02392578125 ms
     * @returns
     */
    readonly setRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string, value: string) => boolean;
    /**
     * 获取内容(文本)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.108ms
     * @returns
     */
    readonly getStringRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => string;
    /**
     * 获取内容(数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.10888671875 ms
     * @returns
     */
    getNumberRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => number;
    /**
     * 创建新的路径
     * @param HKEY 根路径
     * @param Path 路径
     * @time 2.02392578125 ms
     * @returns
     */
    readonly createPathRegistr: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
    /**
     * 获取内容(二进制 Buffer)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06787109375 ms
     * @returns
     */
    getRegistrBuffValue: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => void | Buffer;
    /**
     * 打开一个注册表路径并返回一些实用方法
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    readonly openRegKey: typeof open;
    getRegistrQword: typeof getRegistrQword;
    getRegistrDword: typeof getRegistrDword;
    setRegistrQword: typeof setRegistrQword;
    setRegistrDword: typeof setRegistrDword;
    removeStringRegValue: typeof removeStringRegValue;
    removeStringRegKeyWalk: typeof removeStringRegKeyWalk;
    removeStringTree: typeof removeStringTree;
    isRegistrTreeKey: typeof isRegistrTreeKey;
};
export declare const hmc: {
    getLastInputTime: typeof getLastInputTime;
    getCursorPos: typeof getCursorPos;
    Auto: {
        setLimitMouseRange: typeof setLimitMouseRange;
        hasMouseLeftActivate: typeof hasMouseLeftActivate;
        hasMouseRightActivate: typeof hasMouseRightActivate;
        hasMouseMiddleActivate: typeof hasMouseMiddleActivate;
        hasMouseBtnActivate: typeof hasMouseBtnActivate;
        sendKeyboard: typeof sendKeyboard;
        sendKeyboardSequence: typeof sendKeyboardSequence;
        getColor: typeof getColor;
        sendBasicKeys: typeof sendBasicKeys;
        setWindowEnabled: typeof setWindowEnabled;
        setCursorPos: typeof setCursorPos;
        mouse: typeof mouse;
        rightClick: typeof rightClick;
        leftClick: typeof leftClick;
        getBasicKeys: typeof getBasicKeys;
        getMouseMovePoints: typeof getMouseMovePoints;
        powerControl: {
            (Set: 
            /**关机 */
            1001 | 
            /**重启 */
            1002 | 
            /**注销 */
            1003 | 
            /**锁定 */
            1005): void;
            /**关机 */
            1001(): void;
            /**重启 */
            1002(): void;
            /**注销 */
            1003(): void;
            /**锁定 */
            1005(): void;
            /**关机 */
            shutDown(): void;
            /**重启 */
            restart(): void;
            /**注销 */
            cancellation(): void;
            /**锁定 */
            lock(): void;
        };
        SetBlockInput: typeof SetBlockInput;
        SetSystemHOOK: typeof SetSystemHOOK;
        hasKeyActivate: typeof hasKeyActivate;
        mouseHook: Iohook_Mouse;
        keyboardHook: Iohook_Keyboard;
        getCursorPos: typeof getCursorPos;
        getLastInputTime: typeof getLastInputTime;
    };
    Clipboard: {
        clear: typeof clearClipboard;
        readText: typeof getClipboardText;
        readFilePaths: typeof getClipboardFilePaths;
        writeText: typeof setClipboardText;
        writeFilePaths: typeof setClipboardFilePaths;
        sequence: typeof getClipboardSequenceNumber;
        watch: typeof watchClipboard;
    };
    Environment: {
        hasKeyExists: typeof hasKeyExists;
        hasUseKeyExists: typeof hasUseKeyExists;
        hasSysKeyExists: typeof hasSysKeyExists;
        escapeEnvVariable: typeof escapeEnvVariable;
        removeUserVariable: typeof removeUserVariable;
        removeVariable: typeof removeVariable;
        removeSystemVariable: typeof removeSystemVariable;
        getSystemVariable: typeof getSystemVariable;
        getUserVariable: typeof getUserVariable;
        getVariableAnalysis: typeof getVariableAnalysis;
        putSystemVariable: typeof putSystemVariable;
        putUserVariable: typeof putUserVariable;
        getVariableAll: typeof getVariableAll;
        getRealGlobalVariableList: typeof getRealGlobalVariableList;
        getUserKeyList: typeof getUserKeyList;
        getSystemKeyList: typeof getSystemKeyList;
        updateThis: typeof updateThis;
        setUserVariable: typeof setUserVariable;
        setSystemVariable: typeof setSystemVariable;
    };
    HWND: typeof HWND;
    MessageError: typeof MessageError;
    MessageStop: typeof MessageStop;
    Process: {
        watch: typeof processWatchdog;
        kill: typeof killProcess;
        killMatch: typeof killProcessName;
        getList: typeof getProcessList;
        getHandle: typeof getProcessHandle;
        getName: typeof getProcessName;
        getPath: typeof getProcessidFilePath;
        getFocus: typeof getForegroundWindowProcessID;
        has: typeof hasProcess;
        match: typeof getProcessNameList;
        matchDetails: typeof getDetailsProcessNameList;
        getDetailsList: typeof getDetailsProcessList;
        parentID: typeof getProcessParentProcessID;
        mianPID: typeof getProcessParentProcessID;
        subPID: typeof getSubProcessID;
        threadList: typeof getProcessThreadList;
    };
    PromiseSession: typeof PromiseSession;
    Registr: {
        /**
         * 直达路径解析
         * @param Path 全路径(直达路径)
         * @param atkey 是否将最后一个值解释为键
         * @returns
         */
        analysisDirectPath: typeof analysisDirectPath;
        /**
         * 判断注册表中是否有该键值
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.06591796875 ms
         * @returns
         */
        has: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 获取内容(文本)
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.108ms
         * @returns
         */
        get: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => string;
        /**
         * 设置键值对
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @param Value 数据
         * @time 2.02392578125 ms
         * @returns
         */
        set: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string, value: string) => boolean;
        /**
         * 删除数据
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.076904296875 ms
         * @returns
         */
        remove: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 枚举键值
         * @param HKEY 根路径
         * @param Path 路径
         * @time 0.06689453125 ms
         * @returns
         */
        keys: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => string[];
        /**
         * 将当前的路径的注册表值转表
         * @param HKEY
         * @param Path
         */
        list: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => {
            [key: string]: string | Buffer;
            "": string | Buffer;
        };
        /**
         * 创建新的路径
         * @param HKEY 根路径
         * @param Path 路径
         * @time 2.02392578125 ms
         * @returns
         */
        create: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 打开一个注册表路径并返回一些实用方法
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @returns
         */
        open: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => {
            /**
             * 获取全路径
             */
            readonly path: string;
            /**
             * 设置一个值
             * @param data 数据
             */
            set(data: string): boolean;
            /**
             * 获取内容
             * @returns
             */
            get(): string;
            /**
             * 获取该内容并将其视为二进制缓冲区
             * @returns 二进制缓冲区
             */
            getBuff(): Buffer;
            /**
             * 获取该内容并将其视为数字
             * @returns 数字
             */
            getNumber(): number;
            /**
             * 枚举当前路径下的键
             * @returns 键 数组
             */
            keys(): string[];
            /**
             * 将当前目录转为对象
             */
            list(): {
                [key: string]: string | Buffer;
                "": string | Buffer;
            };
        };
        /**
         * 判断注册表中是否有该键值
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.06591796875 ms
         * @returns
         */
        readonly hasRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 将当前的路径的注册表值转表
         * @param HKEY
         * @param Path
         */
        readonly listRegistrPath: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => {
            [key: string]: string | Buffer;
            "": string | Buffer;
        };
        /**
         * 枚举键值
         * @param HKEY 根路径
         * @param Path 路径
         * @time 0.06689453125 ms
         * @returns
         */
        readonly enumRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => string[];
        /**
         * 删除数据
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.076904296875 ms
         * @returns
         */
        readonly removeStringRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 设置键值对
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @param Value 数据
         * @time 2.02392578125 ms
         * @returns
         */
        readonly setRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string, value: string) => boolean;
        /**
         * 获取内容(文本)
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.108ms
         * @returns
         */
        readonly getStringRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => string;
        /**
         * 获取内容(数字)
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.10888671875 ms
         * @returns
         */
        getNumberRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => number;
        /**
         * 创建新的路径
         * @param HKEY 根路径
         * @param Path 路径
         * @time 2.02392578125 ms
         * @returns
         */
        readonly createPathRegistr: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 获取内容(二进制 Buffer)
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.06787109375 ms
         * @returns
         */
        getRegistrBuffValue: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => void | Buffer;
        /**
         * 打开一个注册表路径并返回一些实用方法
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @returns
         */
        readonly openRegKey: typeof open;
        getRegistrQword: typeof getRegistrQword;
        getRegistrDword: typeof getRegistrDword;
        setRegistrQword: typeof setRegistrQword;
        setRegistrDword: typeof setRegistrDword;
        removeStringRegValue: typeof removeStringRegValue;
        removeStringRegKeyWalk: typeof removeStringRegKeyWalk;
        removeStringTree: typeof removeStringTree;
        isRegistrTreeKey: typeof isRegistrTreeKey;
    };
    SetBlockInput: typeof SetBlockInput;
    SetSystemHOOK: typeof SetSystemHOOK;
    SetWindowInTaskbarVisible: typeof SetWindowInTaskbarVisible;
    Shell: {
        trash: typeof deleteFile;
        openApp: typeof openApp;
        getShortcutLink: typeof getShortcutLink;
        setShortcutLink: typeof setShortcutLink;
        freePort: typeof freePort;
        createSymlink: typeof createSymlink;
        createDirSymlink: typeof createDirSymlink;
        createHardLink: typeof createHardLink;
    };
    Sleep: typeof Sleep;
    Usb: {
        getHub: typeof getHidUsbList;
        getDevsInfo: typeof getUsbDevsInfo;
        watch: typeof watchUSB;
    };
    Watch: {
        clipboard: typeof watchClipboard;
        usb: typeof watchUSB;
        windowFocus: typeof WatchWindowForeground;
        windowPoint: typeof WatchWindowPoint;
        process: typeof processWatchdog;
    };
    WatchWindowForeground: typeof WatchWindowForeground;
    WatchWindowPoint: typeof WatchWindowPoint;
    WebView2OnlineInstall: typeof WebView2OnlineInstall;
    Window: {
        isInMonitor: typeof isInMonitorWindow;
        isMouseMonitor: typeof isMouseMonitorWindow;
        HWND: typeof HWND;
        setMode: typeof setWindowMode;
        getAllWindows: typeof getAllWindows;
        getAllHandle: typeof getAllWindowsHandle;
        watchPoint: typeof WatchWindowPoint;
        watchtFocus: typeof WatchWindowForeground;
        getFocus: typeof getForegroundWindow;
        getMain: typeof getMainWindow;
        getPoint: typeof getPointWindow;
        getProcessHandle: typeof getProcessHandle;
        getPointMain: typeof getPointWindowMain;
        setTaskbarVisible: typeof SetWindowInTaskbarVisible;
        getProcessID: typeof getHandleProcessID;
        getRect: typeof getWindowRect;
        isEnabled: typeof isEnabled;
        isHandle: typeof isHandle;
        hasHandle: typeof isHandle;
        isVisible: typeof isHandleWindowVisible;
        close: typeof lookHandleCloseWindow;
        getTitle: typeof lookHandleGetTitle;
        setTitle: typeof lookHandleSetTitle;
        setShowWindow: typeof lookHandleShowWindow;
        setTransparent: typeof setHandleTransparent;
        setEnabled: typeof setWindowEnabled;
        setFocus: typeof setWindowFocus;
        setTop: typeof setWindowTop;
        update: typeof updateWindow;
        jitter: typeof windowJitter;
        hasTop: typeof hasWindowTop;
        closed: typeof closedHandle;
        getFocusProcessID: typeof getForegroundWindowProcessID;
        getPointName: typeof getPointWindowName;
        getPointProcessId: typeof getPointWindowProcessId;
        enumChild: typeof enumChildWindows;
        console: {
            hide: typeof hideConsole;
            show: typeof showConsole;
            get: typeof getConsoleHandle;
            blockInput: typeof SetBlockInput;
        };
        getStyle: typeof getWindowStyle;
        getClassName: typeof getWindowClassName;
    };
    _KeyboardcodeComparisonTable: Map<string, number>;
    _KeyboardcodeEmenList: Map<number, [string, string | null, number, number] | [string, string | null, number, number, import("./vkKey").VK_Nickname]>;
    _popen: typeof _popen;
    alert: typeof alert;
    analysisDirectPath: typeof analysisDirectPath;
    captureBmpToFile: typeof captureBmpToFile;
    clearClipboard: typeof clearClipboard;
    closeWindow: typeof lookHandleCloseWindow;
    closedHandle: typeof closedHandle;
    confirm: typeof confirm;
    createDirSymlink: typeof createDirSymlink;
    createHardLink: typeof createHardLink;
    createMutex: typeof createMutex;
    createPathRegistr: typeof createPathRegistr;
    createSymlink: typeof createSymlink;
    deleteFile: typeof deleteFile;
    desc: string;
    enumAllProcessHandle: typeof enumAllProcessHandle;
    enumChildWindows: typeof enumChildWindows;
    enumProcessHandle: typeof enumProcessHandle;
    enumRegistrKey: typeof enumRegistrKey;
    escapeEnvVariable: typeof escapeEnvVariable;
    findProcess: typeof findProcess;
    findProcess2: typeof findProcess2;
    findProcess2Sync: typeof findProcess2Sync;
    findWindow: typeof findWindow;
    findWindowEx: typeof findWindowEx;
    formatVolumePath: typeof formatVolumePath;
    freePort: typeof freePort;
    getAllEnv: typeof getAllEnv;
    getAllProcessList2: typeof getAllProcessList2;
    getAllProcessList2Sync: typeof getAllProcessList2Sync;
    getAllProcessListNt2: typeof getAllProcessListNt2;
    getAllProcessListNt2Sync: typeof getAllProcessListNt2Sync;
    getAllProcessListSnp2: typeof getAllProcessListSnp2;
    getAllProcessListSnp2Sync: typeof getAllProcessListSnp2Sync;
    getAllProcessListSnpSession2: typeof getAllProcessListSnpSession2;
    getAllProcessListSnpSession2Sync: typeof getAllProcessListSnpSession2Sync;
    getAllWindows: typeof getAllWindows;
    getAllWindowsHandle: typeof getAllWindowsHandle;
    getBasicKeys: typeof getBasicKeys;
    getClipboardFilePaths: typeof getClipboardFilePaths;
    getClipboardSequenceNumber: typeof getClipboardSequenceNumber;
    getClipboardText: typeof getClipboardText;
    getColor: typeof getColor;
    getConsoleHandle: typeof getConsoleHandle;
    getCurrentMonitorRect: typeof getCurrentMonitorRect;
    getDetailsProcessList: typeof getDetailsProcessList;
    getDetailsProcessList2: typeof getDetailsProcessList2;
    getDetailsProcessNameList: typeof getDetailsProcessNameList;
    getDeviceCaps: typeof getDeviceCaps;
    getDeviceCapsAll: typeof getDeviceCapsAll;
    getForegroundWindow: typeof getForegroundWindow;
    getForegroundWindowProcessID: typeof getForegroundWindowProcessID;
    getHandleProcessID: typeof getHandleProcessID;
    getHidUsbList: typeof getHidUsbList;
    getMainWindow: typeof getMainWindow;
    getMetrics: typeof getMetrics;
    getModulePathList: typeof getModulePathList;
    getMouseMovePoints: typeof getMouseMovePoints;
    getNumberRegKey: typeof getNumberRegKey;
    getPointWindow: typeof getPointWindow;
    getPointWindowMain: typeof getPointWindowMain;
    getPointWindowName: typeof getPointWindowName;
    getPointWindowProcessId: typeof getPointWindowProcessId;
    getProcessFilePath: typeof getProcessidFilePath;
    getProcessFilePath2: typeof getProcessFilePath2;
    getProcessFilePath2Sync: typeof getProcessFilePath2Sync;
    getProcessHandle: typeof getProcessHandle;
    getProcessList: typeof getProcessList;
    getProcessName: typeof getProcessName;
    getProcessName2: typeof getProcessName2;
    getProcessName2Sync: typeof getProcessName2Sync;
    getProcessNameList: typeof getProcessNameList;
    getProcessNameNt2: typeof getProcessNameNt2;
    getProcessNameNt2Sync: typeof getProcessNameNt2Sync;
    getProcessNameSnp2: typeof getProcessNameSnp2;
    getProcessNameSnp2Sync: typeof getProcessNameSnp2Sync;
    getProcessParentProcessID: typeof getProcessParentProcessID;
    getProcessParentProcessMatch2: typeof getProcessParentProcessMatch2;
    getProcessParentProcessMatch2Sync: typeof getProcessParentProcessMatch2Sync;
    getProcessStartTime: typeof getProcessStartTime;
    getProcessThreadList: typeof getProcessThreadList;
    getProcessWindow: typeof getProcessHandle;
    getProcessidFilePath: typeof getProcessidFilePath;
    getRealGlobalVariableList: typeof getRealGlobalVariableList;
    getRegistrBuffValue: typeof getRegistrBuffValue;
    getRegistrDword: typeof getRegistrDword;
    getRegistrQword: typeof getRegistrQword;
    getShortcutLink: typeof getShortcutLink;
    getStringRegKey: typeof getStringRegKey;
    getSubProcessID: typeof getSubProcessID;
    getSystemIdleTime: typeof getSystemIdleTime;
    getSystemKeyList: typeof getSystemKeyList;
    getSystemMenu: typeof getSystemMenu;
    getSystemMetricsLen: typeof getSystemMetricsLen;
    getSystemVariable: typeof getSystemVariable;
    getTCPPortProcessID: typeof getTCPPortProcessID;
    getTrayList: typeof getTrayList;
    getUDPPortProcessID: typeof getUDPPortProcessID;
    getUsbDevsInfo: typeof getUsbDevsInfo;
    getUserKeyList: typeof getUserKeyList;
    getUserVariable: typeof getUserVariable;
    getVariableAll: typeof getVariableAll;
    getVariableAnalysis: typeof getVariableAnalysis;
    getVolumeList: typeof getVolumeList;
    getWebView2Info: typeof getWebView2Info;
    getWindowClassName: typeof getWindowClassName;
    getWindowProcess: typeof getHandleProcessID;
    getWindowRect: typeof getWindowRect;
    getWindowStyle: typeof getWindowStyle;
    getWindowTitle: typeof lookHandleGetTitle;
    getenv: typeof getenv;
    hasKeyActivate: typeof hasKeyActivate;
    hasKeyExists: typeof hasKeyExists;
    hasMutex: typeof hasMutex;
    hasPortTCP: typeof hasPortTCP;
    hasPortUDP: typeof hasPortUDP;
    hasProcess: typeof hasProcess;
    hasRegistrKey: typeof hasRegistrKey;
    hasSysKeyExists: typeof hasSysKeyExists;
    hasUseKeyExists: typeof hasUseKeyExists;
    hasWebView2: typeof hasWebView2;
    hasWindowTop: typeof hasWindowTop;
    hideConsole: typeof hideConsole;
    isAdmin: typeof isAdmin;
    isEnabled: typeof isEnabled;
    isHandle: typeof isHandle;
    isHandleWindowVisible: typeof isHandleWindowVisible;
    isInMonitorWindow: typeof isInMonitorWindow;
    isMouseMonitorWindow: typeof isMouseMonitorWindow;
    isProcess: typeof isProcess;
    isRegistrTreeKey: typeof isRegistrTreeKey;
    isSystemX64: typeof isSystemX64;
    isWindowTop: typeof hasWindowTop;
    isWindowVisible: typeof isHandleWindowVisible;
    keyboardHook: Iohook_Keyboard;
    killProcess: typeof killProcess;
    killProcessName: typeof killProcessName;
    leftClick: typeof leftClick;
    listRegistrPath: typeof listRegistrPath;
    lookHandleCloseWindow: typeof lookHandleCloseWindow;
    lookHandleGetTitle: typeof lookHandleGetTitle;
    lookHandleSetTitle: typeof lookHandleSetTitle;
    lookHandleShowWindow: typeof lookHandleShowWindow;
    messageBox: typeof messageBox;
    mouse: typeof mouse;
    mouseHook: Iohook_Mouse;
    native: HMC.Native;
    openApp: typeof openApp;
    openExternal: typeof openExternal;
    openPath: typeof openPath;
    openRegKey: typeof openRegKey;
    openURL: typeof openURL;
    platform: string;
    popen: typeof popen;
    powerControl: {
        (Set: 
        /**关机 */
        1001 | 
        /**重启 */
        1002 | 
        /**注销 */
        1003 | 
        /**锁定 */
        1005): void;
        /**关机 */
        1001(): void;
        /**重启 */
        1002(): void;
        /**注销 */
        1003(): void;
        /**锁定 */
        1005(): void;
        /**关机 */
        shutDown(): void;
        /**重启 */
        restart(): void;
        /**注销 */
        cancellation(): void;
        /**锁定 */
        lock(): void;
    };
    processWatchdog: typeof processWatchdog;
    putSystemVariable: typeof putSystemVariable;
    putUserVariable: typeof putUserVariable;
    putenv: typeof putenv;
    ref: {
        /**
        * 将内容格式化为文本路径
        * @param Str
        * @returns
        */
        path(Str: any): string;
        /**
         * 格式化为bool
         * @param bool
         * @returns
         */
        bool(bool: any): boolean;
        /**
         * 将内容格式化为文本
         * @param Str
         * @returns
         */
        string(Str: any): string;
        /**
         * 格式化数字为int(强制)
         * @param Num
         * @returns
         */
        int(Num: any): number;
        /**
         * 文本数组
         * @param array
         * @returns
         */
        stringArray(array: Set<any> | Array<any>): string[];
        /**
         * 文本数组
         * @param array
         * @returns
         */
        intArray(array: Set<any> | Array<any>): number[];
        /**
         * 格式化命令行内容
         */
        formatCmd(cmd: string): string[];
        /**
         * 将命令行内容组转为cmd文本
         * @param argv
         */
        formatArgv(...argv: Array<any>[] | any[]): string;
        /**注册表根目录 */
        HKEY: {
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
        /**
         * 拼合buff片段
         * @param buffList
         * @returns
         */
        concatBuff(buffList: Buffer[]): Buffer;
        /**
         * 键盘值格式化为键值
         * @param key 键值/键
         * @returns
         */
        vkKey: typeof vkKey;
    };
    registr: {
        /**
         * 直达路径解析
         * @param Path 全路径(直达路径)
         * @param atkey 是否将最后一个值解释为键
         * @returns
         */
        analysisDirectPath: typeof analysisDirectPath;
        /**
         * 判断注册表中是否有该键值
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.06591796875 ms
         * @returns
         */
        has: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 获取内容(文本)
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.108ms
         * @returns
         */
        get: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => string;
        /**
         * 设置键值对
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @param Value 数据
         * @time 2.02392578125 ms
         * @returns
         */
        set: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string, value: string) => boolean;
        /**
         * 删除数据
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.076904296875 ms
         * @returns
         */
        remove: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 枚举键值
         * @param HKEY 根路径
         * @param Path 路径
         * @time 0.06689453125 ms
         * @returns
         */
        keys: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => string[];
        /**
         * 将当前的路径的注册表值转表
         * @param HKEY
         * @param Path
         */
        list: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => {
            [key: string]: string | Buffer;
            "": string | Buffer;
        };
        /**
         * 创建新的路径
         * @param HKEY 根路径
         * @param Path 路径
         * @time 2.02392578125 ms
         * @returns
         */
        create: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 打开一个注册表路径并返回一些实用方法
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @returns
         */
        open: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => {
            /**
             * 获取全路径
             */
            readonly path: string;
            /**
             * 设置一个值
             * @param data 数据
             */
            set(data: string): boolean;
            /**
             * 获取内容
             * @returns
             */
            get(): string;
            /**
             * 获取该内容并将其视为二进制缓冲区
             * @returns 二进制缓冲区
             */
            getBuff(): Buffer;
            /**
             * 获取该内容并将其视为数字
             * @returns 数字
             */
            getNumber(): number;
            /**
             * 枚举当前路径下的键
             * @returns 键 数组
             */
            keys(): string[];
            /**
             * 将当前目录转为对象
             */
            list(): {
                [key: string]: string | Buffer;
                "": string | Buffer;
            };
        };
        /**
         * 判断注册表中是否有该键值
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.06591796875 ms
         * @returns
         */
        readonly hasRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 将当前的路径的注册表值转表
         * @param HKEY
         * @param Path
         */
        readonly listRegistrPath: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => {
            [key: string]: string | Buffer;
            "": string | Buffer;
        };
        /**
         * 枚举键值
         * @param HKEY 根路径
         * @param Path 路径
         * @time 0.06689453125 ms
         * @returns
         */
        readonly enumRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string) => string[];
        /**
         * 删除数据
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.076904296875 ms
         * @returns
         */
        readonly removeStringRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 设置键值对
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @param Value 数据
         * @time 2.02392578125 ms
         * @returns
         */
        readonly setRegistrKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string, value: string) => boolean;
        /**
         * 获取内容(文本)
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.108ms
         * @returns
         */
        readonly getStringRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => string;
        /**
         * 获取内容(数字)
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.10888671875 ms
         * @returns
         */
        getNumberRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => number;
        /**
         * 创建新的路径
         * @param HKEY 根路径
         * @param Path 路径
         * @time 2.02392578125 ms
         * @returns
         */
        readonly createPathRegistr: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => boolean;
        /**
         * 获取内容(二进制 Buffer)
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @time 0.06787109375 ms
         * @returns
         */
        getRegistrBuffValue: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => void | Buffer;
        /**
         * 打开一个注册表路径并返回一些实用方法
         * @param HKEY 根路径
         * @param Path 路径
         * @param key 键
         * @returns
         */
        readonly openRegKey: typeof open;
        getRegistrQword: typeof getRegistrQword;
        getRegistrDword: typeof getRegistrDword;
        setRegistrQword: typeof setRegistrQword;
        setRegistrDword: typeof setRegistrDword;
        removeStringRegValue: typeof removeStringRegValue;
        removeStringRegKeyWalk: typeof removeStringRegKeyWalk;
        removeStringTree: typeof removeStringTree;
        isRegistrTreeKey: typeof isRegistrTreeKey;
    };
    removeStringRegKey: typeof removeStringRegKey;
    removeStringRegKeyWalk: typeof removeStringRegKeyWalk;
    removeStringRegValue: typeof removeStringRegValue;
    removeStringTree: typeof removeStringTree;
    removeSystemVariable: typeof removeSystemVariable;
    removeUserVariable: typeof removeUserVariable;
    removeVariable: typeof removeVariable;
    rightClick: typeof rightClick;
    sendBasicKeys: typeof sendBasicKeys;
    sendKeyboard: typeof sendKeyboard;
    sendKeyboardSequence: typeof sendKeyboardSequence;
    setClipboardFilePaths: typeof setClipboardFilePaths;
    setClipboardText: typeof setClipboardText;
    setCloseWindow: typeof lookHandleCloseWindow;
    setCursorPos: typeof setCursorPos;
    setHandleTransparent: typeof setHandleTransparent;
    setRegistrDword: typeof setRegistrDword;
    setRegistrKey: typeof setRegistrKey;
    setRegistrQword: typeof setRegistrQword;
    setShortcutLink: typeof setShortcutLink;
    setShowWindow: typeof lookHandleShowWindow;
    setSystemVariable: typeof setSystemVariable;
    setUserVariable: typeof setUserVariable;
    setWindowEnabled: typeof setWindowEnabled;
    setWindowFocus: typeof setWindowFocus;
    setWindowIconForExtract: typeof setWindowIconForExtract;
    setWindowMode: typeof setWindowMode;
    setWindowShake: typeof windowJitter;
    setWindowTitle: typeof lookHandleSetTitle;
    setWindowTop: typeof setWindowTop;
    showConsole: typeof showConsole;
    showMonitors: typeof showMonitors;
    shutMonitors: typeof shutMonitors;
    sleep: typeof sleep;
    system: typeof system;
    systemChcp: typeof systemChcp;
    systemStartTime: typeof systemStartTime;
    trash: typeof deleteFile;
    updateThis: typeof updateThis;
    updateWindow: typeof updateWindow;
    version: string;
    watchClipboard: typeof watchClipboard;
    watchUSB: typeof watchUSB;
    windowJitter: typeof windowJitter;
    hasMouseLeftActivate: typeof hasMouseLeftActivate;
    hasMouseRightActivate: typeof hasMouseRightActivate;
    hasMouseMiddleActivate: typeof hasMouseMiddleActivate;
    hasMouseBtnActivate: typeof hasMouseBtnActivate;
    setLimitMouseRange: typeof setLimitMouseRange;
    getProcessCwd2Sync: typeof getProcessCwd2Sync;
    getProcessCwd2: typeof getProcessCwd2;
    getProcessCommand2: typeof getProcessCommand2;
    getProcessCommand2Sync: typeof getProcessCommand2Sync;
};
export default hmc;
