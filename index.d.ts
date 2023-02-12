/// <reference types="node" />
import { Native, chcpList } from "./native";
declare const native: Native;
declare let chcpList: {
    [key: string | number]: SystemDecoder;
};
declare function systemChcp(): Promise<{
    chcp: SystemDecoder;
    code: SystemDecoderKey;
}>;
/**
 * 句柄 可以视为是一个数字也可以视为是一个功能 {0}
 * 继承了 Number 的构建类
 */
export declare class HWND extends Number {
    constructor(hWnd: number);
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
    get rect(): Rect | null;
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
    get MianPid(): ProcessID | null;
    get MainHandle(): number;
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
/**注册表根目录 */
declare const Hkey: {
    /**用作默认用户首选设置，也作为单个用户的首选设置 */
    HKEY_CURRENT_CONFIG: string;
    /**用作默认用户首选设置，也作为单个用户的首选设置 */
    HKEY_USERS: string;
    /**是与文档类型和 OLE\COM 相关的信息的支持键。这个键是 */
    HKEY_CLASSES_ROOT: string;
    /**包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息 */
    HKEY_LOCAL_MACHINE: string;
    /**管理系统当前的用户信息 */
    HKEY_CURRENT_USER: string;
};
/**
 * 直达路径解析
 * @param Path 全路径(直达路径)
 * @param atkey 是否将最后一个值解释为键
 * @returns
 */
declare function analysisDirectPath(Path: string, atkey?: boolean): string[];
declare class hmc_win32 {
    #private;
    get hmc(): this;
    get default(): this;
    /**原生HMC */
    native: Native;
    /**一个可以快速操作的句柄类对象 */
    HWND: typeof HWND;
    /**版本号 */
    version: string;
    /**功能介绍 */
    desc: string;
    /**当前二进制适用系统平台 */
    platform: string;
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
        HKEY: {
            /**用作默认用户首选设置，也作为单个用户的首选设置 */
            HKEY_CURRENT_CONFIG: string;
            /**用作默认用户首选设置，也作为单个用户的首选设置 */
            HKEY_USERS: string;
            /**是与文档类型和 OLE\COM 相关的信息的支持键。这个键是 */
            HKEY_CLASSES_ROOT: string;
            /**包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息 */
            HKEY_LOCAL_MACHINE: string;
            /**管理系统当前的用户信息 */
            HKEY_CURRENT_USER: string;
        };
        /**
         * 拼合buff片段
         * @param buffList
         * @returns
         */
        concatBuff(buffList: Buffer[]): Buffer;
    };
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
    setWindowMode(HWND: HWND | number, x: number | null | 0 | SetWindowRect, y?: number | null | 0, width?: number | null | 0, height?: number | null | 0): boolean;
    /**
     * 判断注册表中是否有该键值
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06591796875 ms
     * @returns
     */
    hasRegistrKey(HKEY: HKEY, Path: string, key: string): boolean;
    /**
     * 设置键值对内容(64位数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Qword (64位数字)
     * @returns
     */
    setRegistrQword(HKEY: HKEY, Path: string, key: string, Qword: bigint | number): boolean;
    /**
     * 设置键值对内容(32位数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Qword (32位数字)
     * @returns
     */
    setRegistrDword(HKEY: HKEY, Path: string, key: string, Dword: number): boolean;
    /**
     * 获取内容(64位数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06787109375 ms
     * @returns
     */
    getRegistrQword(HKEY: HKEY, Path: string, key: string): bigint;
    /**
     * 获取内容(64位数字)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06787109375 ms
     * @returns
     */
    getRegistrDword(HKEY: HKEY, Path: string, key: string): number;
    /**
     * 获取内容(二进制 Buffer)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.06787109375 ms
     * @returns
     */
    getRegistrBuffValue(HKEY: HKEY, Path: string, key: string): void | Buffer;
    /**
     * 枚举键值
     * @param HKEY 根路径
     * @param Path 路径
     * @time 0.06689453125 ms
     * @returns
     */
    enumRegistrKey(HKEY: HKEY, Path: string): string[];
    /**
     * 将当前的路径的注册表值转表
     * @param HKEY
     * @param Path
     */
    listRegistrPath(HKEY: HKEY, Path: string): {
        [key: string]: string | Buffer;
        "": string | Buffer;
    };
    /**
     * 判断该键值是否存在子项
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     */
    isRegistrTreeKey(HKEY: HKEY, Path: string, key?: string): boolean;
    /**
     * 获取内容(文本)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.108ms
     * @returns
     */
    getStringRegKey(HKEY: HKEY, Path: string, key?: string): string;
    /**
     * 打开一个注册表路径并返回一些实用方法
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    openRegKey(HKEY: HKEY, Path: string, key?: string): {
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
    getNumberRegKey(HKEY: HKEY, Path: string, key?: string): number;
    /**
     * 删除键 (文件夹)
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @time 0.076904296875 ms
     * @returns
     */
    removeStringRegKey(HKEY: HKEY, Path: string, key?: string): boolean;
    /**
     * 删除该目录下的所有内容（树遍历）
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    removeStringRegKeyWalk(HKEY: HKEY, Path: string, key?: string): boolean;
    /**
   * 删除该目录下的所有内容（树遍历）
   * @param HKEY 根路径
   * @param Path 路径
   * @param key 键
   * @returns
   */
    removeStringTree(HKEY: HKEY, Path: string, key: string): boolean;
    /**
     * 删除该键值
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @returns
     */
    removeStringRegValue(HKEY: HKEY, Path: string, key?: string): boolean;
    /**
     * 设置键值对
     * @param HKEY 根路径
     * @param Path 路径
     * @param key 键
     * @param Value 数据
     * @time 2.02392578125 ms
     * @returns
     */
    setRegistrKey(HKEY: HKEY, Path: string, key: string, Value: string): boolean;
    /**
     * 创建新的路径
     * @param HKEY 根路径
     * @param Path 路径
     * @time 2.02392578125 ms
     * @returns
     */
    createPathRegistr(HKEY: HKEY, Path: string): boolean;
    /**
     * 方法用于显示带有一条指定消息和一个 确认 按钮的警告框
     * @param Message 消息
     * @param Title 标题
     * @time any ms
     * @returns
     */
    alert(Message: string, Title?: string): boolean;
    /**
     * 方法用于显示带有一条指定消息和 确认 和取消  的按钮的消息框
     * @param Message 消息
     * @param Title 标题
     * @time any ms
     * @returns
     */
    confirm(Message: string, Title?: string): boolean;
    /**
     * 方法用于显示带有一条指定消息和一个 确认 按钮的和❌（X）的消息框。
     * @param Message 消息
     * @param Title 标题
     * @time any ms
     * @returns
     */
    MessageStop(Message: string, Title?: string): void;
    /**
     * 方法用于显示带有一条指定消息和一个 确认 按钮的错误框 附带有❗ 感叹号。
     * @param Message 消息
     * @param Title 标题
     * @time any ms
     * @returns
     */
    MessageError(Message: string, Title?: string): void;
    /**
     * 获取所有窗口的信息
     * ! @time 28.283203125 ms
     * @deprecated 该功能有概率使进程奔溃 请使用 getAllWindowsHandle 代替该功能
     **/
    getAllWindows: () => {
        className: string;
        handle: number;
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
        style: number;
        title: string;
    }[];
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
    getAllWindowsHandle(): HWND[];
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
    processWatchdog(ProcessID: number, callback?: (() => void) | number, awaitMs?: number): (Promise<void> & {
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
    WatchWindowPoint(callback: (newPoint: number, oidPoint: number, HWND: HWND) => void, awaitMs?: number): {
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
    WatchWindowForeground(callback: (newForeg: number, oidForeg: number, HWND: HWND) => void, awaitMs?: number): {
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
    openApp(AppPath: string, Command?: string | string[], cwd?: string, hide?: boolean, UAC?: boolean): boolean;
    /**
     * 获取该名称 /正则匹配的进程列表
     * @param Name
     * @returns
     */
    getProcessNameList(...Name: Array<string | RegExp>): {
        pid: number;
        name: string;
    }[];
    /**
    * 获取该名称 /正则匹配的进程列表 带执行文件路径 慢20ms
    * @param Name
    * @returns
    */
    getDetailsProcessNameList(...Name: Array<string | RegExp>): {
        pid: number;
        name: string;
        path: string;
    }[];
    /**
     * 结束该名称的进程
     * @param Name
     */
    killProcessName(...Name: Array<string | RegExp>): {
        pid: number;
        kill: boolean;
        name: string;
    }[];
    /**
     * 获取当前的焦点窗口
     * @returns 一个可以操作的伪数字类
     */
    getForegroundWindow(): HWND | null;
    /**
     * 获取句柄的主窗口
     * @returns 一个可以操作的伪数字类
     */
    getMainWindow(Handle: number | HWND): HWND | null;
    /**
     * 获取鼠标所在的窗口
     * @returns 一个可以操作的伪数字类
     */
    getPointWindow(): HWND | null;
    /**
     * 获取鼠标所在的窗口的主窗口
     * @returns 一个可以操作的伪数字类
     */
    getPointWindowMain(): HWND | null;
    /**
     * 获取进程的句柄
     * @param ProcessID
     * @returns
     */
    getProcessHandle(ProcessID: number): HWND | null;
    /**
     * 阻止键盘和鼠标输入事件到达应用程序。
     */
    SetBlockInput(Block: boolean): boolean;
    /**
     * 设置该窗口图标在状态栏可见性 (注意：XP 下激活窗口了会失效(但是有没有一种可能 xp运行不了node和electron))
     * @param Handle 句柄
     * @param Visible 可见性
     * @returns
     */
    SetWindowInTaskbarVisible(Handle: number | HWND, Visible: boolean): boolean;
    /**
     * 获取句柄对应的进程id
     * @param Handle 句柄
     * @returns
     */
    getHandleProcessID(Handle: number | HWND): number | null;
    /** 获取窗口位置大小
     *  - 高，宽，坐标大于一万以上都是不可见的
     * **/
    getWindowRect(Handle: number | HWND): Rect;
    /**
     * 判断窗口是否禁用响应事件(鼠标键盘点击)
     * @param Handle
     * @returns
     */
    isEnabled(Handle: number | HWND): boolean;
    /**
     * 判断句柄是否有效
     * @param Handle
     * @returns
     */
    isHandle(Handle: number | HWND): boolean;
    /**
     * 判断此句柄是否是正在活动中的窗口
     * @param Handle
     * @returns
     */
    isHandleWindowVisible(Handle: number | HWND): boolean;
    /**
     * 关闭此句柄对应的窗口
     * @param Handle
     * @returns
     */
    lookHandleCloseWindow(Handle: number | HWND): boolean;
    /**
     * 获取此句柄的标题
     * @param Handle
     * @returns
     */
    lookHandleGetTitle(Handle: number | HWND): string | null;
    /**
     * 设置此句柄的标题
     * @param Handle
     * @param title
     * @returns
     */
    lookHandleSetTitle(Handle: number | HWND, title: string): boolean;
    /**
     * 通过句柄设置窗口显示状态  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
     * @param Handle 窗口句柄
     * @param nCmdShow 操作内容
     *  - "SW_HIDE" ： 0 隐藏窗口并激活另一个窗口。
     *  - "SW_SHOWNORMAL" ： 1 激活并显示一个窗口。如果窗口被最小化或最大化，系统会将其恢复到原来的大小和位置。应用程序应在第一次显示窗口时指定此标志
     *  - "SW_SHOWMINIMIZED" ：2 激活窗口并将其显示为最小化窗口
     *  - "SW_SHOWMAXIMIZED" | "SW_MAXIMIZE" ： 3 激活窗口并将其显示为最大化窗口
     *  - "SW_SHOWNOACTIVATE" ： 4 以最近的大小和位置显示窗口。这个值类似于SW_SHOWNORMAL，除了窗口没有被激活
     *  - "SW_SHOW" ：5  激活窗口并以其当前大小和位置显示它
     *  - "SW_MINIMIZE" ：6 最小化指定窗口并激活 Z 顺序中的下一个顶级窗口
     *  - "SW_SHOWMINNOACTIVE" ： 7 将窗口显示为最小化窗口。这个值类似于SW_SHOWMINIMIZED，除了窗口没有被激活
     *  - "SW_SHOWNA" ： 8 以当前大小和位置显示窗口。这个值类似于SW_SHOW，除了窗口没有被激活
     *  - "SW_RESTORE" ： 9 激活并显示窗口。如果窗口被最小化或最大化，系统会将其恢复到原来的大小和位置。应用程序在恢复最小化窗口时应指定此标志
     *  - "SW_SHOWDEFAULT" ： 10 据启动应用程序的程序传递给CreateProcess函数的STARTUPINFO结构中指定的SW_值设置显示状态。
     *  - "SW_FORCEMINIMIZE" ： 11 最小化一个窗口，即使拥有该窗口的线程没有响应。只有在最小化来自不同线程的窗口时才应使用此标志
     * @returns
     */
    lookHandleShowWindow(Handle: number | HWND, SetShowType: 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11): boolean;
    /**
     * 设置窗口不透明度 0-255
     * @param Handle
     * @param Transparent 0-255
     * @returns
     */
    setHandleTransparent(Handle: number | HWND, Transparent: number): void;
    /**
     * 设置窗口是否支持响应事件(鼠标键盘点击)
     * @param Handle
     * @param Enabled
     * @returns
     */
    setWindowEnabled(Handle: number | HWND, Enabled: boolean): boolean;
    /**
     * 设置窗口焦点
     * @param Handle
     * @returns
     */
    setWindowFocus(Handle: number | HWND): boolean;
    /**
     * 设置窗口顶设
     * @param Handle
     * @returns
     */
    setWindowTop(Handle: number | HWND): boolean;
    /**
     * 刷新该窗口
     * @param Handle
     * @returns
     */
    updateWindow(Handle: number | HWND): boolean;
    /**
     * 窗口抖动
     * @param Handle
     * @returns
     */
    windowJitter(Handle: number | HWND): void;
    /**
     * 判断窗口是否被顶设
     * @param Handle
     * @returns
     */
    hasWindowTop(Handle: number | HWND): boolean;
    /**
     * 关闭该句柄窗口(可关闭托盘)(发送关闭消息)
     */
    closedHandle(Handle: number | HWND): undefined;
    /**
     * 获取所有HidUsb设备（仅限HID设备)
     * @returns HidUsb设备数组
     */
    getHidUsbList(): HidUsb[];
    /**
     * 获取鼠标所在位置
     * @returns 鼠标所在位置
     */
    getMetrics(): {
        left: number;
        top: number;
        x: number;
        y: number;
    };
    /**
     * 获取鼠标之前64个位置
     * @returns 之前64个位置
     */
    getMouseMovePoints(): {
        x: number;
        /**管理系统当前的用户信息 */
        y: number;
        time: number;
        dwExtraInfo: number;
    }[];
    /**
     * 获取屏幕大小
     */
    getDeviceCaps(): {
        width: number;
        height: number;
    };
    /**禁用/启用系统键盘鼠标钩子
      * @param HOOK 是否启用系统键盘鼠标钩子
      !注意该功能很危险 主要用于自动化防止误操作 用户锁屏  禁止用于非法用途
      *手动解锁方式 Ctrl+Alt+Del   => esc
      !请注意 你需要确保你的解锁代码  运行没有任何错误或者有定时解锁
      否则有可能导致用户无法正常使用
      **/
    SetSystemHOOK(HOOK: boolean): boolean;
    /**
     * 获取四大按钮(`alt`  `ctrl`  `win`  `shift` )是否按下
     * @returns
     */
    getBasicKeys(): {
        shift: boolean;
        alt: boolean;
        ctrl: boolean;
        win: boolean;
    };
    /**
     * 获取剪贴板文本
     * @returns 剪贴板文本
     */
    getClipboardText(): string;
    /**
     * 设置剪贴板文本
     * @param text 文本
     * @returns
     */
    setClipboardText(text: string): void;
    /**
     * 清空剪贴版
     * @returns 处理结果
     */
    clearClipboard(): boolean;
    /** 获取详细进程列表（慢20ms）**/
    getDetailsProcessList(): {
        name: string;
        pid: number;
        path: string;
    }[];
    /** 获取进程列表**/
    getProcessList(): {
        name: string;
        pid: number;
    }[];
    /**获取活动窗口的进程id */
    getForegroundWindowProcessID(): number | null;
    /**获取鼠标所在窗口的进程名 */
    getPointWindowName(): string;
    /**获取鼠标所在窗口的进程id */
    getPointWindowProcessId(): number;
    /**
     * 获取进程名
     * @param ProcessID 进程id
     * @returns
     */
    getProcessName(ProcessID: number): string | null;
    /**
     * 获取进程可执行文件位置
     * @param ProcessName 进程名
     * @returns 进程id
     */
    getProcessidFilePath(ProcessID: number): string | null;
    /**
     * 获取快捷方式的信息
     * @param LnkPath 快捷方式路径
     * @returns
     */
    getShortcutLink(LnkPath: string): {
        cwd: string;
        icon: string;
        iconIndex: number;
        desc: string;
        args: string;
        showCmd: number;
        hotkey: number;
        path: string;
    };
    /**系统空闲时间 */
    getSystemIdleTime(): number;
    /**
     * 设置系统右键菜单 例如win自带的系统菜单就很丑还不能禁用  使用这个禁用
     * @param Handle 句柄
     * @param boolean 是否禁用
     * @returns
     */
    getSystemMenu(Handle: number | HWND, boolean: boolean): void;
    /**获取托盘图标列表 */
    getTrayList(): {
        path: string;
        info: string;
        handle: number;
    }[];
    /**判断该按键是否被按下  https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getkeystate **/
    hasKeyActivate(KeysEvent: number): (KeysEvent: number) => boolean;
    /**
     * 判断进程id 是否存在
     * @param ProcessID 进程id
     * @returns
     */
    hasProcess(ProcessID: number): boolean;
    /**
     * 当前程序是否拥有管理员权限
     * @returns
     */
    isAdmin(): boolean;
    /**
     * 判断进程id 是否存在
     * @param ProcessID 进程id
     * @returns
     */
    isProcess(ProcessID: number): boolean;
    /**判断当前系统是否是64位 */
    isSystemX64(): boolean;
    killProcess(ProcessID: number): boolean;
    killProcess(ProcessID: string): {
        pid: number;
        kill: boolean;
        name: string;
    }[];
    /**
     * 左键点击
     * @param ms 延迟
     * @returns
     */
    leftClick(ms?: number): void;
    /**
     * 消息窗口(调用 win-api)
     * @param message 消息内容
     * @param title 标题
     * @param UINT_String 显示窗口类型 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
     * @description 衍生api(已预设): `confirm`  `alert` `MessageError` `MessageStop`
     * @returns
     */
    messageBox(message: string, title: string, UINT_String: UINT): 1 | 2 | 3 | 4 | 5 | 6 | 7 | 10 | 11;
    /**自定义鼠标事件 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mouse_event **/
    mouse(mouse_event: mouse_event, ms?: number): void;
    /**
     * 在资源管理器中显示并选中该文件
     * @param Path 路径
     * @returns
     */
    openExternal(Path: string): boolean;
    /**
     * 用默认应用打开该 （文件/文件夹）
     * @param Path 文件路径
     * @returns
     */
    openPath(Path: string): boolean;
    /**
     * 用默认浏览器打开这条url
     * @param URL url
     * @returns
     */
    openURL(URL: string): boolean;
    /**
     * 电源控制
     */
    get powerControl(): {
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
    rightClick(ms?: number): void;
    /**
     * 设置鼠标位置
     * @param x 左边开始的像素数坐标
     * @param y 上方到下方的像素数坐标
     * @returns
     */
    setCursorPos(x: number, y: number): boolean;
    setShortcutLink(LnkPath: string, FilePath: string, work_dir: string, desc: string, args: string | string[], iShowCmd: number, icon: string, iconIndex: number): boolean;
    setShortcutLink(LnkPath: string, FilePath: string, work_dir?: string, desc?: string, args?: string | string[], iShowCmd?: number): boolean;
    setShortcutLink(LnkPath: string, FilePath: string): boolean;
    /**
     * 创建文件软链接
     * @param LinkPath 创建的位置
     * @param sourcePath 原文件链接
     * @returns
     */
    createSymlink(LinkPath: string, sourcePath: string): boolean;
    /**
     * 创建文件夹软链接
     * @param LinkPath 创建的位置
     * @param sourcePath 原文件链接
     * @returns
     */
    createDirSymlink(LinkPath: string, sourcePath: string): boolean;
    /**
     * 创建文件硬链接
     * @param LinkPath 创建的位置
     * @param sourcePath 原文件链接
     * @returns
     */
    createHardLink(LinkPath: string, sourcePath: string): boolean;
    /**打开显示器 */
    showMonitors(show?: boolean): void;
    /**关闭显示器 */
    shutMonitors(show?: boolean): void;
    /**
     * `Sync` 同步阻塞(进程)
     * @param awaitTime
     * @returns
     */
    sleep(awaitTime: number): void;
    /**
     * `async` 异步阻塞(进程)
     * @param awaitTime
     * @returns
     */
    Sleep(awaitTime: number, Sync?: boolean): Promise<unknown>;
    /**
     * 系统启动到现在的时间(毫秒)
     * @returns
     */
    systemStartTime(): number;
    /**
     * 注册表编辑
     */
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
         */ open: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => {
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
        readonly openRegKey: (HKEY: "HKEY_CURRENT_CONFIG" | "HKEY_USERS" | "HKEY_CLASSES_ROOT" | "HKEY_LOCAL_MACHINE" | "HKEY_CURRENT_USER", Path: string, key: string) => {
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
    };
    /**
     * 同 C++/C 的system
     * @returns 程序退出代码
     */
    system(str: string): number;
    /**
     * 空闲的随机端口号
     * @returns
     */
    freePort(): Promise<number>;
    /**
     * 获取系统shell默认编码
     * @returns
     */
    systemChcp: typeof systemChcp;
    getClipboardFilePaths(): string[];
    getClipboardFilePaths(at: number): string | undefined;
    /**
     * 向剪贴板写入文件列表
     * @param FilePaths
     */
    setClipboardFilePaths(...FilePaths: string[] | [string[]]): void;
    /**
     * 获取所有usb驱动器(不包含HUD)
     * @returns
     */
    getUsbDevsInfo(): string[];
    /**
     * 枚举句柄的子窗口
     * @param Handle 句柄
     * @returns
     */
    enumChildWindows(Handle: number | HWND): number[];
    /**
     * 隐藏当前控制台窗口(node)
     */
    hideConsole(): boolean;
    /**
     * 显示当前控制台窗口(node)
     */
    showConsole(): boolean;
    /**
     * 获取当前控制台窗口的句柄(node)
     * @returns
     */
    getConsoleHandle(): HWND | null;
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
    get trash(): (Path: string, Recycle?: boolean | undefined, isShow?: boolean | undefined) => number;
    /**
     * 获取当前剪贴板内容的id(如果被重新写入了该id会变动)
     * @returns
     */
    getClipboardSequenceNumber(): number;
    /**
     * 当剪贴板内容变更后发生回调
     * @param CallBack 回调函数
     * @param nextAwaitMs 每次判断内容变化用时 默认 `150` ms
     * @returns
     */
    watchClipboard(CallBack: () => void, nextAwaitMs?: number): {
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
    watchUSB(CallBack: (env: "add" | "remove" | "start", id: string) => void, nextAwaitMs?: number, watchType?: "hub" | "drive" | Array<"hub" | "drive">): {
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
}
export declare const hmc: hmc_win32;
export declare interface Rect {
    /**
     * (x)从屏幕左边到所在位置得像素数
     */
    right?: number;
    /**
     * 底部到当前位置
     */
    bottom: number;
    /**
     * 右边到当前位置
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
     * (right) 从屏幕右边到所在位置得像素数
     */
    x: number;
    /**
     * (top)从屏幕顶部边到所在位置得像素数
     */
    y: number;
    /**
     * (y)从屏幕顶部边到所在位置得像素数
     */
    top: number;
}
export declare let UINT: {
    /**消息框包含三个按钮：终止、重试和忽略。 */
    MB_ABORTRETRYIGNORE: string;
    /**消息框包含三个按钮：取消、重试、继续。使用此消息框类型而不是 MB_ABORTRETRYIGNORE。 */
    MB_CANCELTRYCONTINUE: string;
    /**向消息框 添加帮助按钮。当用户单击帮助按钮或按 F1 时，系统会向所有者 发送WM_HELP消息。 */
    MB_HELP: string;
    /**消息框包含一个按钮：确定。这是默认设置。 */
    MB_OK: string;
    /**消息框包含两个按钮：确定和取消。 */
    MB_YESNOCANCEL: string;
    /**消息框包含两个按钮：是和否。 */
    MB_YESNO: string;
    /**消息框包含两个按钮：OK和Cancel。 */
    MB_OKCANCEL: string;
    /**消息框包含两个按钮：OK和Cancel。 */
    MB_RETRYCANCEL: string;
    /**
     * 消息框包含三个按钮：Yes、No和Cancel。
     * *一个停止标志图标出现在消息框中。
     */
    MB_ICONERROR: string;
    /**一个停止标志图标出现在消息框中。 */
    MB_ICONSTOP: string;
    /**问号图标出现在消息框中。不再推荐使用问号消息图标，因为它不能清楚地表示特定类型的消息，并且作为问题的消息措辞可能适用于任何消息类型。此外，用户可能会将消息符号问号与帮助信息混淆。因此，请勿在消息框中使用此问号消息符号。系统继续支持它的包含只是为了向后兼容。 */
    MB_ICONQUESTION: string;
    /**一个由圆圈中的小写字母i组成的图标出现在消息框中。 */
    MB_ICONASTERISK: string;
    MB_ICONINFORMATION: string;
    /**消息框中会出现一个感叹号图标。 */
    MB_ICONEXCLAMATION: string;
    /** 消息框中会出现一个感叹号图标。 */
    MB_ICONWARNING: string;
    /**以下也是被支持的具体请查看 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
     *消息框成为前台窗口 **/
    MB_TOPMOST: string;
    MB_SETFOREGROUND: string;
    MB_RTLREADING: string;
    MB_RIGHT: string;
    MB_DEFAULT_DESKTOP_ONLY: string;
    MB_TASKMODAL: string;
    MB_SYSTEMMODAL: string;
    MB_APPLMODAL: string;
    MB_DEFBUTTON4: string;
    MB_DEFBUTTON3: string;
    MB_DEFBUTTON2: string;
    MB_ICONHAND: string;
    MB_DEFBUTTON1: string;
};
export declare type UINT = keyof typeof UINT;
/**进程名称**/
export declare type ProcessID = number;
/**win窗口允许的不透明度 */
export declare type HandleTransparent = number;
export declare type HidUsb = {
    /**类型**/
    type: "hid" | "keyboard" | "mouse";
    /**本次枚举中的索引/
    "index": number,
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
export declare type HKEY = keyof typeof Hkey;
export declare type mouse_event = keyof typeof mouse_event_list;
export declare let mouse_event_list: {
    /**不支持的属性 请使用 setCursorPos 方法设置位置*/
    32768: string;
    /**左键按下 */
    2: string;
    /**左边的按钮是向上的 */
    4: string;
    /**中间的按钮是向下的 */
    32: string;
    /**中间的按钮是向上的 */
    64: string;
    /**鼠标移动和按钮点击 */
    1: string;
    /**鼠标右键按下 */
    8: string;
    /**鼠标右键弹起 */
    16: string;
    /**滚轮按钮被旋转 */
    2048: string;
    /**按下了 X 按钮 */
    128: string;
    /**X 按钮被释放 */
    256: string;
    /**滚轮按钮倾斜*/
    4096: string;
    /**不支持的属性 请使用 setCursorPos 方法设置位置*/
    MOUSEEVENTF_ABSOLUTE: number;
    /**左键按下 */
    MOUSEEVENTF_LEFTDOWN: number;
    /**左边的按钮是向上的 */
    MOUSEEVENTF_LEFTUP: number;
    /**中间的按钮是向下的 */
    MOUSEEVENTF_MIDDLEDOWN: number;
    /**中间的按钮是向上的 */
    MOUSEEVENTF_MIDDLEUP: number;
    /**鼠标移动和按钮点击 */
    MOUSEEVENTF_MOVE: number;
    /**鼠标右键按下 */
    MOUSEEVENTF_RIGHTDOWN: number;
    /**鼠标右键弹起 */
    MOUSEEVENTF_RIGHTUP: number;
    /**滚轮按钮被旋转 */
    MOUSEEVENTF_WHEEL: number;
    /**按下了 X 按钮 */
    MOUSEEVENTF_XDOWN: number;
    /**X 按钮被释放 */
    MOUSEEVENTF_XUP: number;
    /**滚轮按钮倾斜*/
    MOUSEEVENTF_HWHEEL: number;
};
/**
 * 设置窗口坐标
 */
export declare type SetWindowRect = {
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
/**功能介绍 */
export declare const desc: hmc_win32['desc'];
/**
 * 获取所有窗口的信息
 * ! @time 28.283203125 ms
 * @deprecated 该功能有概率使进程奔溃 请使用 getAllWindowsHandle 代替该功能
 **/
export declare const getAllWindows: hmc_win32['getAllWindows'];
/**当前二进制适用系统平台 */
export declare const platform: hmc_win32['platform'];
export declare const ref: hmc_win32['ref'];
/**注册表编辑 */
export declare const registr: hmc_win32['registr'];
/**版本号 */
export declare const version: hmc_win32['version'];
/**版本号 */
export declare const powerControl: hmc_win32['powerControl'];
/**
  * 方法用于显示带有一条指定消息和一个 确认 按钮的错误框 附带有❗ 感叹号。
  * @param Message 消息
  * @param Title 标题
  * @time any ms
  * @returns
  */
export declare const MessageError: hmc_win32['MessageError'];
/**
   * 方法用于显示带有一条指定消息和一个 确认 按钮的和❌（X）的消息框。
   * @param Message 消息
   * @param Title 标题
   * @time any ms
   * @returns
   */
export declare const MessageStop: hmc_win32['MessageStop'];
/**阻止键盘和鼠标输入事件到达应用程序。 */
export declare const SetBlockInput: hmc_win32['SetBlockInput'];
/**禁用/启用系统键盘鼠标钩子
    * @param HOOK 是否启用系统键盘鼠标钩子
    !注意该功能很危险 主要用于自动化防止误操作 用户锁屏  禁止用于非法用途
    *手动解锁方式 Ctrl+Alt+Del   => esc
    !请注意 你需要确保你的解锁代码  运行没有任何错误或者有定时解锁
    否则有可能导致用户无法正常使用
    **/
export declare const SetSystemHOOK: hmc_win32['SetSystemHOOK'];
/**
   * 设置该窗口图标在状态栏可见性 (注意：XP 下激活窗口了会失效(但是有没有一种可能 xp运行不了node和electron))
   * @param Handle 句柄
   * @param Visible 可见性
   * @returns
   */
export declare const SetWindowInTaskbarVisible: hmc_win32['SetWindowInTaskbarVisible'];
/**
   * `async` 异步阻塞(进程)
   * @param awaitTime
   * @returns
   */
export declare const Sleep: hmc_win32['Sleep'];
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
export declare const WatchWindowForeground: hmc_win32['WatchWindowForeground'];
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
export declare const WatchWindowPoint: hmc_win32['WatchWindowPoint'];
/**
  * 方法用于显示带有一条指定消息和一个 确认 按钮的警告框
  * @param Message 消息
  * @param Title 标题
  * @time any ms
  * @returns
  */
export declare const alert: hmc_win32['alert'];
/**
 * 清空剪贴版
 * @returns 处理结果
 */
export declare const clearClipboard: hmc_win32['clearClipboard'];
/**
 * 关闭该句柄窗口(可关闭托盘)(发送关闭消息)
 */
export declare const closedHandle: hmc_win32['closedHandle'];
/**
 * 方法用于显示带有一条指定消息和 确认 和取消  的按钮的消息框
 * @param Message 消息
 * @param Title 标题
 * @time any ms
 * @returns
 */
export declare const confirm: hmc_win32['confirm'];
/**
 * 创建新的路径
 * @param HKEY 根路径
 * @param Path 路径
 * @time 2.02392578125 ms
 * @returns
 */
export declare const createPathRegistr: hmc_win32['createPathRegistr'];
/**
 * 枚举键值
 * @param HKEY 根路径
 * @param Path 路径
 * @time 0.06689453125 ms
 * @returns
 */
export declare const enumRegistrKey: hmc_win32['enumRegistrKey'];
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
export declare const getAllWindowsHandle: hmc_win32['getAllWindowsHandle'];
/**
 * 获取四大按钮(`alt`  `ctrl`  `win`  `shift` )是否按下
 * @returns
 */
export declare const getBasicKeys: hmc_win32['getBasicKeys'];
/**
 * 获取剪贴板文本
 * @returns 剪贴板文本
 */
export declare const getClipboardText: hmc_win32['getClipboardText'];
/** 获取详细进程列表（慢20ms）**/
export declare const getDetailsProcessList: hmc_win32['getDetailsProcessList'];
/**
 * 获取屏幕大小
 */
export declare const getDeviceCaps: hmc_win32['getDeviceCaps'];
/**
 * 获取当前的焦点窗口
 * @returns 一个可以操作的伪数字类
 */
export declare const getForegroundWindow: hmc_win32['getForegroundWindow'];
/**获取活动窗口的进程id */
export declare const getForegroundWindowProcessID: hmc_win32['getForegroundWindowProcessID'];
/**
 * 获取句柄对应的进程id
 * @param Handle 句柄
 * @returns
 */
export declare const getHandleProcessID: hmc_win32['getHandleProcessID'];
/**
 * 获取所有HidUsb设备（仅限HID设备)
 * @returns HidUsb设备数组
 */
export declare const getHidUsbList: hmc_win32['getHidUsbList'];
/**
 * 获取句柄的主窗口
 * @returns 一个可以操作的伪数字类
 */
export declare const getMainWindow: hmc_win32['getMainWindow'];
/**
 * 获取鼠标所在位置
 * @returns 鼠标所在位置
 */
export declare const getMetrics: hmc_win32['getMetrics'];
/**
 * 获取鼠标之前64个位置
 * @returns 之前64个位置
 */
export declare const getMouseMovePoints: hmc_win32['getMouseMovePoints'];
/**
 * 获取内容(数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.10888671875 ms
 * @returns
 */
export declare const getNumberRegKey: hmc_win32['getNumberRegKey'];
/**
 * 获取鼠标所在的窗口
 * @returns 一个可以操作的伪数字类
 */
export declare const getPointWindow: hmc_win32['getPointWindow'];
/**
 * 获取鼠标所在的窗口的主窗口
 * @returns 一个可以操作的伪数字类
 */
export declare const getPointWindowMain: hmc_win32['getPointWindowMain'];
/**获取鼠标所在窗口的进程名 */
export declare const getPointWindowName: hmc_win32['getPointWindowName'];
/**获取鼠标所在窗口的进程id */
export declare const getPointWindowProcessId: hmc_win32['getPointWindowProcessId'];
/**
 * 获取进程的句柄
 * @param ProcessID
 * @returns
 */
export declare const getProcessHandle: hmc_win32['getProcessHandle'];
/** 获取进程列表**/
export declare const getProcessList: hmc_win32['getProcessList'];
/**
 * 获取进程名
 * @param ProcessID 进程id
 * @returns
 */
export declare const getProcessName: hmc_win32['getProcessName'];
/**
 * 获取进程可执行文件位置
 * @param ProcessName 进程名
 * @returns 进程id
 */
export declare const getProcessidFilePath: hmc_win32['getProcessidFilePath'];
/**
 * 获取内容(二进制 Buffer)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06787109375 ms
 * @returns
 */
export declare const getRegistrBuffValue: hmc_win32['getRegistrBuffValue'];
/**
  * 获取快捷方式的信息
  * @param LnkPath 快捷方式路径
  * @returns
  */
export declare const getShortcutLink: hmc_win32['getShortcutLink'];
/**
 * 获取内容(文本)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.108ms
 * @returns
 */
export declare const getStringRegKey: hmc_win32['getStringRegKey'];
/**系统空闲时间 */
export declare const getSystemIdleTime: hmc_win32['getSystemIdleTime'];
/**
 * 设置系统右键菜单 例如win自带的系统菜单就很丑还不能禁用  使用这个禁用
 * @param Handle 句柄
 * @param boolean 是否禁用
 * @returns
 */
export declare const getSystemMenu: hmc_win32['getSystemMenu'];
/**获取托盘图标列表 */
export declare const getTrayList: hmc_win32['getTrayList'];
/** 获取窗口位置大小
 *  - 高，宽，坐标大于一万以上都是不可见的
 * **/
export declare const getWindowRect: hmc_win32['getWindowRect'];
/**判断该按键是否被按下  https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getkeystate **/
export declare const hasKeyActivate: hmc_win32['hasKeyActivate'];
/**
 * 判断进程id 是否存在
 * @param ProcessID 进程id
 * @returns
 */
export declare const hasProcess: hmc_win32['hasProcess'];
/**
 * 判断注册表中是否有该键值
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.06591796875 ms
 * @returns
 */
export declare const hasRegistrKey: hmc_win32['hasRegistrKey'];
/**
 * 判断窗口是否被顶设
 * @param Handle
 * @returns
 */
export declare const hasWindowTop: hmc_win32['hasWindowTop'];
/**
 * 当前程序是否拥有管理员权限
 * @returns
 */
export declare const isAdmin: hmc_win32['isAdmin'];
/**
 * 判断窗口是否禁用响应事件(鼠标键盘点击)
 * @param Handle
 * @returns
 */
export declare const isEnabled: hmc_win32['isEnabled'];
/**
 * 判断句柄是否有效
 * @param Handle
 * @returns
 */
export declare const isHandle: hmc_win32['isHandle'];
/**
 * 判断此句柄是否是正在活动中的窗口
 * @param Handle
 * @returns
 */
export declare const isHandleWindowVisible: hmc_win32['isHandleWindowVisible'];
/**
 * 判断进程id 是否存在
 * @param ProcessID 进程id
 * @returns
 */
export declare const isProcess: hmc_win32['isProcess'];
/**判断当前系统是否是64位 */
export declare const isSystemX64: hmc_win32['isSystemX64'];
/**
 * 结束该进程
 * @param ProcessID
 * @returns
 */
export declare const killProcess: hmc_win32['killProcess'];
/**
 * 结束该名称的进程
 * @param Name
 */
export declare const killProcessName: hmc_win32['killProcessName'];
/**
 * 左键点击
 * @param ms 延迟
 * @returns
 */
export declare const leftClick: hmc_win32['leftClick'];
/**
 * 将当前的路径的注册表值转表
 * @param HKEY
 * @param Path
 */
export declare const listRegistrPath: hmc_win32['listRegistrPath'];
/**
 * 关闭此句柄对应的窗口
 * @param Handle
 * @returns
 */
export declare const lookHandleCloseWindow: hmc_win32['lookHandleCloseWindow'];
/**
 * 获取此句柄的标题
 * @param Handle
 * @returns
 */
export declare const lookHandleGetTitle: hmc_win32['lookHandleGetTitle'];
/**
 * 设置此句柄的标题
 * @param Handle
 * @param title
 * @returns
 */
export declare const lookHandleSetTitle: hmc_win32['lookHandleSetTitle'];
/**
 * 通过句柄设置窗口显示状态  https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
 * @param Handle 窗口句柄
 * @param nCmdShow 操作内容
 *  - "SW_HIDE" ： 0 隐藏窗口并激活另一个窗口。
 *  - "SW_SHOWNORMAL" ： 1 激活并显示一个窗口。如果窗口被最小化或最大化，系统会将其恢复到原来的大小和位置。应用程序应在第一次显示窗口时指定此标志
 *  - "SW_SHOWMINIMIZED" ：2 激活窗口并将其显示为最小化窗口
 *  - "SW_SHOWMAXIMIZED" | "SW_MAXIMIZE" ： 3 激活窗口并将其显示为最大化窗口
 *  - "SW_SHOWNOACTIVATE" ： 4 以最近的大小和位置显示窗口。这个值类似于SW_SHOWNORMAL，除了窗口没有被激活
 *  - "SW_SHOW" ：5  激活窗口并以其当前大小和位置显示它
 *  - "SW_MINIMIZE" ：6 最小化指定窗口并激活 Z 顺序中的下一个顶级窗口
 *  - "SW_SHOWMINNOACTIVE" ： 7 将窗口显示为最小化窗口。这个值类似于SW_SHOWMINIMIZED，除了窗口没有被激活
 *  - "SW_SHOWNA" ： 8 以当前大小和位置显示窗口。这个值类似于SW_SHOW，除了窗口没有被激活
 *  - "SW_RESTORE" ： 9 激活并显示窗口。如果窗口被最小化或最大化，系统会将其恢复到原来的大小和位置。应用程序在恢复最小化窗口时应指定此标志
 *  - "SW_SHOWDEFAULT" ： 10 据启动应用程序的程序传递给CreateProcess函数的STARTUPINFO结构中指定的SW_值设置显示状态。
 *  - "SW_FORCEMINIMIZE" ： 11 最小化一个窗口，即使拥有该窗口的线程没有响应。只有在最小化来自不同线程的窗口时才应使用此标志
 * @returns
 */
export declare const lookHandleShowWindow: hmc_win32['lookHandleShowWindow'];
/**
 * 消息窗口(调用 win-api)
 * @param message 消息内容
 * @param title 标题
 * @param UINT_String 显示窗口类型 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
 * @description 衍生api(已预设): `confirm`  `alert` `MessageError` `MessageStop`
 * @returns
 */
export declare const messageBox: hmc_win32['messageBox'];
/**自定义鼠标事件 https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mouse_event **/
export declare const mouse: hmc_win32['mouse'];
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
export declare const openApp: hmc_win32['openApp'];
/**
 * 在资源管理器中显示并选中该文件
 * @param Path 路径
 * @returns
 */
export declare const openExternal: hmc_win32['openExternal'];
/**
 * 用默认应用打开该 （文件/文件夹）
 * @param Path 文件路径
 * @returns
 */
export declare const openPath: hmc_win32['openPath'];
/**
 * 打开一个注册表路径并返回一些实用方法
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare const openRegKey: hmc_win32['openRegKey'];
/**
 * 用默认浏览器打开这条url
 * @param URL url
 * @returns
 */
export declare const openURL: hmc_win32['openURL'];
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
export declare const processWatchdog: hmc_win32['processWatchdog'];
/**
 * 删除数据
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @time 0.076904296875 ms
 * @returns
 */
export declare const removeStringRegKey: hmc_win32['removeStringRegKey'];
/**
 * 右键点击
 * @param ms 延迟
 * @returns
 */
export declare const rightClick: hmc_win32['rightClick'];
/**
 * 设置剪贴板文本
 * @param text 文本
 * @returns
 */
export declare const setClipboardText: hmc_win32['setClipboardText'];
/**
* 设置鼠标位置
* @param x 左边开始的像素数坐标
* @param y 上方到下方的像素数坐标
* @returns
*/
export declare const setCursorPos: hmc_win32['setCursorPos'];
/**
 * 设置窗口不透明度 0-255
 * @param Handle
 * @param Transparent 0-255
 * @returns
 */
export declare const setHandleTransparent: hmc_win32['setHandleTransparent'];
/**
 * 设置键值对
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @param Value 数据
 * @time 2.02392578125 ms
 * @returns
 */
export declare const setRegistrKey: hmc_win32['setRegistrKey'];
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
export declare const setShortcutLink: hmc_win32['setShortcutLink'];
/**
 * 设置窗口是否支持响应事件(鼠标键盘点击)
 * @param Handle
 * @param Enabled
 * @returns
 */
export declare const setWindowEnabled: hmc_win32['setWindowEnabled'];
/**
 * 设置窗口焦点
 * @param Handle
 * @returns
 */
export declare const setWindowFocus: hmc_win32['setWindowFocus'];
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
export declare const setWindowMode: hmc_win32['setWindowMode'];
/**
 * 设置窗口顶设
 * @param Handle
 * @returns
 */
export declare const setWindowTop: hmc_win32['setWindowTop'];
/**打开显示器 */
export declare const showMonitors: hmc_win32['showMonitors'];
/**关闭显示器 */
export declare const shutMonitors: hmc_win32['shutMonitors'];
/**
   * `Sync` 同步阻塞(进程)
   * @param awaitTime
   * @returns
   */
export declare const sleep: hmc_win32['sleep'];
/**
   * 同 C++/C 的system
   * @returns 程序退出代码
   */
export declare const system: hmc_win32['system'];
/**
  * 系统启动到现在的时间(毫秒)
  * @returns
  */
export declare const systemStartTime: hmc_win32['systemStartTime'];
/**
   * 刷新该窗口
   * @param Handle
   * @returns
   */
export declare const updateWindow: hmc_win32['updateWindow'];
/**
   * 窗口抖动
   * @param Handle
   * @returns
   */
export declare const windowJitter: hmc_win32['windowJitter'];
/**
   * 获取该名称 /正则匹配的进程列表
   * @param Name
   * @returns
   */
export declare const getProcessNameList: hmc_win32['getProcessNameList'];
/**
* 获取该名称 /正则匹配的进程列表 带执行文件路径 慢20ms
* @param Name
* @returns
*/
export declare const getDetailsProcessNameList: hmc_win32['getDetailsProcessNameList'];
/**
 * 删除该目录下的所有内容（树遍历）
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare const removeStringRegKeyWalk: hmc_win32['removeStringRegKeyWalk'];
/**
 * 删除该键值
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare const removeStringRegValue: hmc_win32["removeStringRegValue"];
/**
 * 设置键值对内容(32位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @param Qword (32位数字)
 * @returns
 */
export declare const setRegistrDword: hmc_win32["setRegistrDword"];
/**
 * 设置键值对内容(64位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @param Qword (64位数字)
 * @returns
 */
export declare const setRegistrQword: hmc_win32["setRegistrQword"];
/**
 * 获取内容(64位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare const getRegistrQword: hmc_win32["getRegistrQword"];
/**
 * 获取内容(64位数字)
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 * @returns
 */
export declare const getRegistrDword: hmc_win32["getRegistrDword"];
/**
 * 枚举句柄的子窗口
 * @param Handle 句柄
 * @returns
 */
export declare const enumChildWindows: hmc_win32["enumChildWindows"];
/**
 * 获取所有usb驱动器(不包含HUD)
 * @returns
 */
export declare const getUsbDevsInfo: hmc_win32["getUsbDevsInfo"];
/**
  * 获取剪贴板中的文件列表
  * @returns
  */
export declare const getClipboardFilePaths: hmc_win32["getClipboardFilePaths"];
/**
 * 创建文件夹软链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns
 */
export declare const createDirSymlink: hmc_win32["createDirSymlink"];
/**
 * 创建文件软链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns
 */
export declare const createSymlink: hmc_win32["createSymlink"];
/**
 * 创建文件硬链接
 * @param LinkPath 创建的位置
 * @param sourcePath 原文件链接
 * @returns
 */
export declare const createHardLink: hmc_win32["createHardLink"];
/**
 * 空闲的随机端口号
 * @returns
 */
export declare const freePort: hmc_win32["freePort"];
/**
 * 获取当前控制台窗口的句柄(node)
 * @returns
 */
export declare const getConsoleHandle: hmc_win32["getConsoleHandle"];
/**
* 隐藏当前控制台窗口(node)
* @returns
*/
export declare const hideConsole: hmc_win32["hideConsole"];
/**
* 显示当前控制台窗口(node)
* @returns
*/
export declare const showConsole: hmc_win32["showConsole"];
/**
 * 判断该键值是否存在子项
 * @param HKEY 根路径
 * @param Path 路径
 * @param key 键
 */
export declare const isRegistrTreeKey: hmc_win32["isRegistrTreeKey"];
/**
* 删除该目录下的所有内容（树遍历）
* @param HKEY 根路径
* @param Path 路径
* @param key 键
* @returns
*/
export declare const removeStringTree: hmc_win32["removeStringTree"];
/**
 * 向剪贴板写入文件列表
 * @param FilePaths
 */
export declare const setClipboardFilePaths: hmc_win32["setClipboardFilePaths"];
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
export declare const deleteFile: hmc_win32["deleteFile"];
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
export declare const trash: hmc_win32["deleteFile"];
/**
 * 获取当前剪贴板内容的id(如果被重新写入了该id会变动)
 * @returns
 */
export declare const getClipboardSequenceNumber: hmc_win32["getClipboardSequenceNumber"];
/**
 * 当剪贴板内容变更后发生回调
 * @param CallBack 回调函数
 * @param nextAwaitMs 每次判断内容变化用时 默认 `150` ms
 * @returns
 */
export declare const watchClipboard: hmc_win32["watchClipboard"];
/**
    * 当驱动器添加或者移除后发生回调
    * @param CallBack 回调函数
    * @param nextAwaitMs 每次判断内容变化用时 默认 `800` ms
    * @returns
    */
export declare const watchUSB: hmc_win32["watchUSB"];
export { native };
export default hmc;
declare type SystemDecoderKey = keyof chcpList;
declare type SystemDecoder = chcpList[SystemDecoderKey];
