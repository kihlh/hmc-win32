/// <reference types="node" />
export declare const native: Native;
import { cRECT, HKEY, HidUsb, mouse_event, UINT, ProcessID, Rect, HandleTransparent } from './index';
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
     *  - 高，宽，坐标大于一万以上都是不可见的
     * **/
    getWindowRect: (Handle: number) => Rect;
    /** 获取屏幕大小**/
    getDeviceCaps: () => {
        width: number;
        height: number;
    };
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
    getMetrics: () => {
        left: number;
        top: number;
        x: number;
        y: number;
    };
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
    getShortcutLink: (LnkPath: string) => {
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
    };
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
    getTrayList(): {
        path: string;
        info: string;
        handle: number;
    }[];
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
    messageBox(lpText: string, lpCaption: string, UINT_String?: UINT): 3 | 2 | 11 | 5 | 7 | 1 | 4 | 10 | 6;
    /** 设置系统右键菜单 例如win自带的系统菜单就很丑还不能禁用  使用这个禁用**/
    getSystemMenu: (Handle: number, boolean: boolean) => void;
    /** 关闭显示器**/
    shutMonitors: () => void;
    /** 恢复显示器**/
    showMonitors: () => void;
    /** 获取活动窗口句柄**/
    getForegroundWindow: () => number;
    /** 获取进程列表**/
    getProcessList: (ForSleepTime?: number) => {
        name: string;
        pid: ProcessID;
    }[];
    /** 获取详细进程列表（慢20ms）**/
    getDetailsProcessList: (ForSleepTime?: number) => {
        name: string;
        pid: ProcessID;
        path: string;
    }[];
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
    getMouseMovePoints: () => {
        x: number;
        y: number;
        time: number;
        dwExtraInfo: number;
    }[];
    /**
     * 获取所有窗口的句柄
     */
    getAllWindowsHandle(): number[];
    /**
     * 获取所有窗口的信息
     * @deprecated 该功能有概率使进程奔溃 请使用 getAllWindowsHandle 代替该功能
     **/
    getAllWindows: () => {
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
    }[];
    /**获取四大按钮是否按下**/
    getBasicKeys: () => {
        shift: boolean;
        alt: boolean;
        ctrl: boolean;
        win: boolean;
    };
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
    getHidUsbList(): HidUsb[];
    /**
     * 判断键值是否存在
     * @param HKEY 根目录
     * @param Path 路径
     * @param Key 键值 (默认值 直接用： "" )
     */
    hasRegistrKey(HKEY: HKEY, Path: string, Key: string): boolean;
    /**
     * 获取内容(文本)
     * @param HKEY 根目录
     * @param Path 路径
     * @param Key 键值 (默认值 直接用： "" )
     */
    getStringRegKey(HKEY: HKEY, Path: string, Key: string): string;
    /**
    * 获取内容(64位数字)
    * @param HKEY 根目录
    * @param Path 路径
    * @param Key 键值 (默认值 直接用： "" )
    */
    getRegistrQword(HKEY: HKEY, Path: string, Key: string): bigint;
    /**
    * 获取内容(32位数字)
    * @param HKEY 根目录
    * @param Path 路径
    * @param Key 键值 (默认值 直接用： "" )
    */
    getRegistrDword(HKEY: HKEY, Path: string, Key: string): number;
    /**
     * 设置键值对(32位数字)
     * @param HKEY 根目录
     * @param Path 路径
     * @param Key 键值
     * @param Data 数据 (默认值 直接用： "" )
     */
    setRegistrDword(HKEY: HKEY, Path: string, Key: string, Dword: number): boolean;
    /**
     * 设置键值对(64位数字)
     * @param HKEY 根目录
     * @param Path 路径
     * @param Key 键值
     * @param Data 数据 (默认值 直接用： "" )
     */
    setRegistrQword(HKEY: HKEY, Path: string, Key: string, Qword: bigint): boolean;
    /**
     * 删除空目录键值
     * @param HKEY 根目录
     * @param Path 路径
     * @param Key 键值 (默认值 直接用： "" )
     */
    removeStringRegKey(HKEY: HKEY, Path: string, Key: string): boolean;
    /**
     * 设置键值对
     * @param HKEY 根目录
     * @param Path 路径
     * @param Key 键值
     * @param Data 数据 (默认值 直接用： "" )
     */
    setRegistrKey(HKEY: HKEY, Path: string, Key: string, Data: string): boolean;
    /**
     * 创建新的路径
     * @param HKEY 根目录
     * @param Path 路径
     */
    createPathRegistr(HKEY: HKEY, Path: string): boolean;
    /**
     * 枚举键值
     * @param HKEY 根目录
     * @param Path 路径
     */
    enumRegistrKey(HKEY: HKEY, Path: string): string[];
    /**
     * 获取内容(二进制 Buffer)
     * @param HKEY 根目录
     * @param Path 路径
     * @param Key 键值
     */
    getRegistrBuffValue(HKEY: HKEY, Path: string, Key: string): Buffer | void;
    /**
     * 删除值
     * @param HKEY 根目录
     * @param Path 路径
     * @param Key 键值 (不允许空值)
     */
    removeStringRegValue(HKEY: HKEY, Path: string, Key: string): boolean;
    /**
     * 删除该目录下的所有内容（树遍历）
     * @param HKEY 根目录
     * @param Path 路径
     * @param Key 键值(不允许空值)
     */
    removeStringRegKeyWalk(HKEY: HKEY, Path: string, Key: string): boolean;
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
};
export type chcpList = {
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
