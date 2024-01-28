"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const native = require(process.argv.at(-1) || "");
const log4js = require("D:/source/\u9B54\u6CD5\u81EA\u52A8\u66F4\u65B0/node_modules/log4js");
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");
var MAKE_LINK_PATH;
(function (MAKE_LINK_PATH) {
    // 文件夹软链接
    MAKE_LINK_PATH[MAKE_LINK_PATH["CREATE_DIR_SYMLINK"] = 166] = "CREATE_DIR_SYMLINK";
    // 软链接
    MAKE_LINK_PATH[MAKE_LINK_PATH["CREATE_SYMLINK"] = 168] = "CREATE_SYMLINK";
    // 硬链接
    MAKE_LINK_PATH[MAKE_LINK_PATH["CREATE_HARD_LINK"] = 170] = "CREATE_HARD_LINK";
    // 目录连接点
    MAKE_LINK_PATH[MAKE_LINK_PATH["CREATE_SYMBOLIC_LINK"] = 172] = "CREATE_SYMBOLIC_LINK";
})(MAKE_LINK_PATH || (MAKE_LINK_PATH = {}));
;
var POWER_CONTROL_COMMAND;
(function (POWER_CONTROL_COMMAND) {
    // 关机
    POWER_CONTROL_COMMAND[POWER_CONTROL_COMMAND["EWX_SHUTDOWN"] = 1001] = "EWX_SHUTDOWN";
    // 重启
    POWER_CONTROL_COMMAND[POWER_CONTROL_COMMAND["EWX_REBOOT"] = 1002] = "EWX_REBOOT";
    // 注销
    POWER_CONTROL_COMMAND[POWER_CONTROL_COMMAND["EWX_LOGOFF"] = 1003] = "EWX_LOGOFF";
    // 锁定
    POWER_CONTROL_COMMAND[POWER_CONTROL_COMMAND["HMC_LOCK_WORK_STATION"] = 1005] = "HMC_LOCK_WORK_STATION";
    // 关闭显示器
    POWER_CONTROL_COMMAND[POWER_CONTROL_COMMAND["SC_MONITORPOWER_OFF"] = 1006] = "SC_MONITORPOWER_OFF";
    // 打开显示器
    POWER_CONTROL_COMMAND[POWER_CONTROL_COMMAND["SC_MONITORPOWER_ON"] = 1007] = "SC_MONITORPOWER_ON";
    // 播放beep 声音
    POWER_CONTROL_COMMAND[POWER_CONTROL_COMMAND["HMC_BEEP"] = 6660] = "HMC_BEEP";
})(POWER_CONTROL_COMMAND || (POWER_CONTROL_COMMAND = {}));
;
var SYSTEM_METRICS;
(function (SYSTEM_METRICS) {
    // 指定系统如何排列最小化窗口的标志。 有关详细信息，请参阅本主题中的“备注”部分。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_ARRANGE"] = 56] = "SM_ARRANGE";
    // 指定系统启动方式的 值：0 正常启动1 故障安全启动2 通过网络启动实现故障安全故障安全启动 (也称为 SafeBoot、安全模式或干净启动) 会绕过用户启动文件。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CLEANBOOT"] = 67] = "SM_CLEANBOOT";
    // 桌面上的显示监视器数。 有关详细信息，请参阅本主题中的“备注”部分。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CMONITORS"] = 80] = "SM_CMONITORS";
    // 鼠标上的按钮数;如果未安装鼠标，则为零。                       
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CMOUSEBUTTONS"] = 43] = "SM_CMOUSEBUTTONS";
    // 反映笔记本电脑或平板模式的状态，0 表示板模式，否则为非零。 当此系统指标发生更改时，系统会通过 LPARAM 中带有“ConvertibleSlateMode” [的WM_SETTINGCHANGE](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-settingchange) 发送广播消息。 请注意，此系统指标不适用于台式电脑。 在这种情况下，请使用 [GetAutoRotationState](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-getautorotationstate)。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CONVERTIBLESLATEMODE"] = 8195] = "SM_CONVERTIBLESLATEMODE";
    // 窗口边框的宽度（以像素为单位）。 这等效于具有 3D 外观的窗口的 SM_CXEDGE 值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXBORDER"] = 5] = "SM_CXBORDER";
    // 光标的标称宽度（以像素为单位）。                              
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXCURSOR"] = 13] = "SM_CXCURSOR";
    // 此值与 SM_CXFIXEDFRAME 相同。                                 
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXDLGFRAME"] = 7] = "SM_CXDLGFRAME";
    // 矩形围绕双击序列中第一次单击的位置的宽度（以像素为单位）。 第二次单击必须在由 SM_CXDOUBLECLK 和 SM_CYDOUBLECLK 定义的矩形内发生，系统才能将两次单击视为双击。 两次单击也必须在指定时间内发生。若要设置双击矩形的宽度，请使用SPI_SETDOUBLECLKWIDTH调用 [SystemParametersInfo](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-systemparametersinfoa) 。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXDOUBLECLK"] = 36] = "SM_CXDOUBLECLK";
    // 鼠标指针在拖动操作开始之前可以移动的鼠标向下点任一侧的像素数。 这允许用户轻松单击并释放鼠标按钮，而不会无意中启动拖动操作。 如果此值为负值，则从鼠标向下点的左侧减去该值，并将其添加到其右侧。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXDRAG"] = 68] = "SM_CXDRAG";
    // 三维边框的宽度（以像素为单位）。 此指标是SM_CXBORDER的三维对应指标。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXEDGE"] = 45] = "SM_CXEDGE";
    // 窗口周围具有描述文字但不是相当大的（以像素为单位）的框架的粗细。 SM_CXFIXEDFRAME是水平边框的高度，SM_CYFIXEDFRAME是垂直边框的宽度。此值与 SM_CXDLGFRAME 相同。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXFIXEDFRAME"] = 7] = "SM_CXFIXEDFRAME";
    // [DrawFocusRect](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-drawfocusrect) 绘制的焦点矩形的左边缘和右边缘的宽度。 此值以像素为单位。**Windows 2000：** 不支持此值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXFOCUSBORDER"] = 83] = "SM_CXFOCUSBORDER";
    // 此值与 SM_CXSIZEFRAME 相同。                                  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXFRAME"] = 32] = "SM_CXFRAME";
    // 主显示器上全屏窗口的工作区宽度（以像素为单位）。 若要获取系统任务栏或应用程序桌面工具栏未遮挡的屏幕部分的坐标，请使用SPI_GETWORKAREA值调用 [SystemParametersInfo](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-systemparametersinfoa) 函数。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXFULLSCREEN"] = 16] = "SM_CXFULLSCREEN";
    // 水平滚动条上箭头位图的宽度（以像素为单位）。                  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXHSCROLL"] = 21] = "SM_CXHSCROLL";
    // 水平滚动条中拇指框的宽度（以像素为单位）。                    
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXHTHUMB"] = 10] = "SM_CXHTHUMB";
    // 图标的系统大宽度（以像素为单位）。 [LoadIcon](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-loadicona) 函数只能加载具有SM_CXICON和SM_CYICON指定尺寸的图标。 有关详细信息 [，请参阅图标大小](https://learn.microsoft.com/zh-cn/windows/win32/menurc/about-icons#icon-sizes) 。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXICON"] = 11] = "SM_CXICON";
    // 大图标视图中项的网格单元格的宽度（以像素为单位）。 每个项都适合在排列时按SM_CYICONSPACING SM_CXICONSPACING大小的矩形。 此值始终大于或等于 SM_CXICON。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXICONSPACING"] = 38] = "SM_CXICONSPACING";
    // 主显示监视器上最大化的顶级窗口的默认宽度（以像素为单位）。    
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXMAXIMIZED"] = 61] = "SM_CXMAXIMIZED";
    // 具有描述文字和大小调整边框（以像素为单位）的窗口的默认最大宽度。 此指标是指整个桌面。 用户无法将窗口框架拖动到大于这些尺寸的大小。 窗口可以通过处理 [WM_GETMINMAXINFO](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-getminmaxinfo) 消息来替代此值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXMAXTRACK"] = 59] = "SM_CXMAXTRACK";
    // 默认菜单的宽度检查标记位图（以像素为单位）。                  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXMENUCHECK"] = 71] = "SM_CXMENUCHECK";
    // 菜单栏按钮的宽度，例如在多个文档界面中使用的子窗口关闭按钮（以像素为单位）。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXMENUSIZE"] = 54] = "SM_CXMENUSIZE";
    // 窗口的最小宽度（以像素为单位）。                              
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXMIN"] = 28] = "SM_CXMIN";
    // 最小化窗口的宽度（以像素为单位）。                            
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXMINIMIZED"] = 57] = "SM_CXMINIMIZED";
    // 最小化窗口的网格单元格的宽度（以像素为单位）。 每个最小化窗口在排列时适合此大小的矩形。 此值始终大于或等于 SM_CXMINIMIZED。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXMINSPACING"] = 47] = "SM_CXMINSPACING";
    // 窗口的最小跟踪宽度（以像素为单位）。 用户无法将窗口框架拖动到小于这些尺寸的大小。 窗口可以通过处理 [WM_GETMINMAXINFO](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-getminmaxinfo) 消息来替代此值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXMINTRACK"] = 34] = "SM_CXMINTRACK";
    // 带字幕窗口的边框填充量（以像素为单位）。**Windows XP/2000：** 不支持此值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXPADDEDBORDER"] = 92] = "SM_CXPADDEDBORDER";
    // 主显示器的屏幕宽度（以像素为单位）。 这是通过调用 [GetDeviceCaps](https://learn.microsoft.com/zh-cn/windows/desktop/api/wingdi/nf-wingdi-getdevicecaps) 获取的相同值，如下所示： `GetDeviceCaps( hdcPrimaryMonitor, HORZRES)`。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXSCREEN"] = 0] = "SM_CXSCREEN";
    // 窗口中按钮的宽度描述文字或标题栏（以像素为单位）。            
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXSIZE"] = 30] = "SM_CXSIZE";
    // 可调整大小的窗口周边的大小边框的粗细（以像素为单位）。 SM_CXSIZEFRAME是水平边框的宽度，SM_CYSIZEFRAME是垂直边框的高度。此值与 SM_CXFRAME 相同。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXSIZEFRAME"] = 32] = "SM_CXSIZEFRAME";
    // 图标的系统小宽度（以像素为单位）。 小图标通常显示在窗口标题和小图标视图中。 有关详细信息 [，请参阅图标大小](https://learn.microsoft.com/zh-cn/windows/win32/menurc/about-icons#icon-sizes) 。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXSMICON"] = 49] = "SM_CXSMICON";
    // 小描述文字按钮的宽度（以像素为单位）。                        
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXSMSIZE"] = 52] = "SM_CXSMSIZE";
    // 虚拟屏幕的宽度（以像素为单位）。 虚拟屏幕是所有显示监视器的边框。 SM_XVIRTUALSCREEN指标是虚拟屏幕左侧的坐标。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXVIRTUALSCREEN"] = 78] = "SM_CXVIRTUALSCREEN";
    // 垂直滚动条的宽度（以像素为单位）。                            
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CXVSCROLL"] = 2] = "SM_CXVSCROLL";
    // 窗口边框的高度（以像素为单位）。 这等效于具有 3D 外观的窗口的 SM_CYEDGE 值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYBORDER"] = 6] = "SM_CYBORDER";
    // 描述文字区域的高度（以像素为单位）。                          
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYCAPTION"] = 4] = "SM_CYCAPTION";
    // 光标的标称高度（以像素为单位）。                              
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYCURSOR"] = 14] = "SM_CYCURSOR";
    // 此值与 SM_CYFIXEDFRAME 相同。                                 
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYDLGFRAME"] = 8] = "SM_CYDLGFRAME";
    // 矩形围绕双击序列中第一次单击的位置的高度（以像素为单位）。 第二次单击必须在由 SM_CXDOUBLECLK 定义的矩形内发生，SM_CYDOUBLECLK系统会将两次单击视为双击。 两次单击也必须在指定时间内发生。若要设置双击矩形的高度，请使用SPI_SETDOUBLECLKHEIGHT调用 [SystemParametersInfo](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-systemparametersinfoa) 。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYDOUBLECLK"] = 37] = "SM_CYDOUBLECLK";
    // 鼠标指针在拖动操作开始之前可以移动的鼠标向下点上方和下方的像素数。 这允许用户轻松单击并释放鼠标按钮，而不会无意中启动拖动操作。 如果此值为负值，则从鼠标向下点上方减去该值，并将其添加到其下方。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYDRAG"] = 69] = "SM_CYDRAG";
    // 三维边框的高度（以像素为单位）。 这是SM_CYBORDER的三维对应项。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYEDGE"] = 46] = "SM_CYEDGE";
    // 窗口周围具有描述文字但不是相当大的（以像素为单位）的框架的粗细。 SM_CXFIXEDFRAME是水平边框的高度，SM_CYFIXEDFRAME是垂直边框的宽度。此值与 SM_CYDLGFRAME 相同。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYFIXEDFRAME"] = 8] = "SM_CYFIXEDFRAME";
    // [DrawFocusRect](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-drawfocusrect) 绘制的焦点矩形的上边缘和下边缘的高度。 此值以像素为单位。**Windows 2000：** 不支持此值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYFOCUSBORDER"] = 84] = "SM_CYFOCUSBORDER";
    // 此值与 SM_CYSIZEFRAME 相同。                                  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYFRAME"] = 33] = "SM_CYFRAME";
    // 主显示器上全屏窗口的工作区高度（以像素为单位）。 若要获取系统任务栏或应用程序桌面工具栏未遮挡的屏幕部分的坐标，请使用 SPI_GETWORKAREA 值调用 [SystemParametersInfo](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-systemparametersinfoa) 函数。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYFULLSCREEN"] = 17] = "SM_CYFULLSCREEN";
    // 水平滚动条的高度（以像素为单位）。                            
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYHSCROLL"] = 3] = "SM_CYHSCROLL";
    // 图标的系统高度（以像素为单位）。 [LoadIcon](https://learn.microsoft.com/zh-cn/windows/desktop/api/winuser/nf-winuser-loadicona) 函数只能加载具有SM_CXICON和SM_CYICON指定尺寸的图标。 有关详细信息 [，请参阅图标大小](https://learn.microsoft.com/zh-cn/windows/win32/menurc/about-icons#icon-sizes) 。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYICON"] = 12] = "SM_CYICON";
    // 大图标视图中项的网格单元格的高度（以像素为单位）。 每个项都适合在排列时按SM_CYICONSPACING SM_CXICONSPACING大小的矩形。 此值始终大于或等于 SM_CYICON。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYICONSPACING"] = 39] = "SM_CYICONSPACING";
    // 对于系统的双字节字符集版本，这是屏幕底部的汉字窗口的高度（以像素为单位）。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYKANJIWINDOW"] = 18] = "SM_CYKANJIWINDOW";
    // 主显示监视器上最大化的顶级窗口的默认高度（以像素为单位）。    
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYMAXIMIZED"] = 62] = "SM_CYMAXIMIZED";
    // 具有描述文字和大小调整边框的窗口的默认最大高度（以像素为单位）。 此指标是指整个桌面。 用户无法将窗口框架拖动到大于这些尺寸的大小。 窗口可以通过处理 [WM_GETMINMAXINFO](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-getminmaxinfo) 消息来替代此值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYMAXTRACK"] = 60] = "SM_CYMAXTRACK";
    // 单行菜单栏的高度（以像素为单位）。                            
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYMENU"] = 15] = "SM_CYMENU";
    // 默认菜单的高度检查标记位图（以像素为单位）。                  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYMENUCHECK"] = 72] = "SM_CYMENUCHECK";
    // 菜单栏按钮（例如在多个文档界面中使用的子窗口关闭按钮）的高度（以像素为单位）。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYMENUSIZE"] = 55] = "SM_CYMENUSIZE";
    // 窗口的最小高度（以像素为单位）。                              
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYMIN"] = 29] = "SM_CYMIN";
    // 最小化窗口的高度（以像素为单位）。                            
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYMINIMIZED"] = 58] = "SM_CYMINIMIZED";
    // 最小化窗口的网格单元格的高度（以像素为单位）。 每个最小化窗口在排列时适合此大小的矩形。 此值始终大于或等于 SM_CYMINIMIZED。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYMINSPACING"] = 48] = "SM_CYMINSPACING";
    // 窗口的最小跟踪高度（以像素为单位）。 用户无法将窗口框架拖动到小于这些尺寸的大小。 窗口可以通过处理 [WM_GETMINMAXINFO](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-getminmaxinfo) 消息来替代此值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYMINTRACK"] = 35] = "SM_CYMINTRACK";
    // 主显示器的屏幕高度（以像素为单位）。 这是通过调用 [GetDeviceCaps](https://learn.microsoft.com/zh-cn/windows/desktop/api/wingdi/nf-wingdi-getdevicecaps) 获取的相同值，如下所示： `GetDeviceCaps( hdcPrimaryMonitor, VERTRES)`。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYSCREEN"] = 1] = "SM_CYSCREEN";
    // 窗口中按钮的高度描述文字或标题栏（以像素为单位）。            
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYSIZE"] = 31] = "SM_CYSIZE";
    // 可调整大小的窗口周边的大小边框的粗细（以像素为单位）。 SM_CXSIZEFRAME是水平边框的宽度，SM_CYSIZEFRAME是垂直边框的高度。此值与 SM_CYFRAME 相同。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYSIZEFRAME"] = 33] = "SM_CYSIZEFRAME";
    // 小描述文字的高度（以像素为单位）。                            
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYSMCAPTION"] = 51] = "SM_CYSMCAPTION";
    // 图标的系统小高度（以像素为单位）。 小图标通常显示在窗口标题和小图标视图中。 有关详细信息 [，请参阅图标大小](https://learn.microsoft.com/zh-cn/windows/win32/menurc/about-icons#icon-sizes) 。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYSMICON"] = 50] = "SM_CYSMICON";
    // 小描述文字按钮的高度（以像素为单位）。                        
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYSMSIZE"] = 53] = "SM_CYSMSIZE";
    // 虚拟屏幕的高度（以像素为单位）。 虚拟屏幕是所有显示监视器的边框。 SM_YVIRTUALSCREEN指标是虚拟屏幕顶部的坐标。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYVIRTUALSCREEN"] = 79] = "SM_CYVIRTUALSCREEN";
    // 垂直滚动条上箭头位图的高度（以像素为单位）。                  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYVSCROLL"] = 20] = "SM_CYVSCROLL";
    // 垂直滚动条中拇指框的高度（以像素为单位）。                    
    SYSTEM_METRICS[SYSTEM_METRICS["SM_CYVTHUMB"] = 9] = "SM_CYVTHUMB";
    // 如果User32.dll支持 DBCS，则为非零值;否则为 0。                
    SYSTEM_METRICS[SYSTEM_METRICS["SM_DBCSENABLED"] = 42] = "SM_DBCSENABLED";
    // 如果安装了User.exe的调试版本，则为非零;否则为 0。             
    SYSTEM_METRICS[SYSTEM_METRICS["SM_DEBUG"] = 22] = "SM_DEBUG";
    // 如果当前操作系统是 Windows 7 或 Windows Server 2008 R2 并且平板电脑输入服务已启动，则为非零;否则为 0。 返回值是一个位掩码，用于指定设备支持的数字化器输入的类型。 有关详细信息，请参阅“备注”。**Windows Server 2008、Windows Vista 和 Windows XP/2000：** 不支持此值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_DIGITIZER"] = 94] = "SM_DIGITIZER";
    // 如果启用了输入法管理器/输入法编辑器功能，则为非零值;否则为 0。SM_IMMENABLED指示系统是否已准备好在 Unicode 应用程序上使用基于 Unicode 的 IME。 若要确保依赖于语言的 IME 正常工作，检查 SM_DBCSENABLED和系统 ANSI 代码页。 否则，ANSI 到 Unicode 的转换可能无法正确执行，或者某些组件（如字体或注册表设置）可能不存在。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_IMMENABLED"] = 82] = "SM_IMMENABLED";
    // 如果系统中存在数字化器，则为非零值;否则为 0。SM_MAXIMUMTOUCHES返回系统中每个数字化器支持的最大接触数的聚合最大值。 如果系统只有单点触控数字化器，则返回值为 1。 如果系统具有多点触控数字化器，则返回值是硬件可以提供的同时触点数。**Windows Server 2008、Windows Vista 和 Windows XP/2000：** 不支持此值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_MAXIMUMTOUCHES"] = 95] = "SM_MAXIMUMTOUCHES";
    // 如果当前操作系统是 Windows XP，则为非零，Media Center Edition 为 0（如果不是）。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_MEDIACENTER"] = 87] = "SM_MEDIACENTER";
    // 如果下拉菜单与相应的菜单栏项右对齐，则为非零值;如果菜单左对齐，则为 0。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_MENUDROPALIGNMENT"] = 40] = "SM_MENUDROPALIGNMENT";
    // 如果为希伯来语和阿拉伯语启用系统，则为非零值;否则为 0。       
    SYSTEM_METRICS[SYSTEM_METRICS["SM_MIDEASTENABLED"] = 74] = "SM_MIDEASTENABLED";
    // 如果安装了鼠标，则为非零值;否则为 0。 此值很少为零，因为支持虚拟鼠标，并且某些系统检测到端口的存在，而不是鼠标的存在。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_MOUSEPRESENT"] = 19] = "SM_MOUSEPRESENT";
    // 如果安装了水平滚轮的鼠标，则为非零值;否则为 0。              | 
    SYSTEM_METRICS[SYSTEM_METRICS["SM_MOUSEHORIZONTALWHEELPRESENT"] = 91] = "SM_MOUSEHORIZONTALWHEELPRESENT";
    // 如果安装了具有垂直滚轮的鼠标，则为非零值;否则为 0。           
    SYSTEM_METRICS[SYSTEM_METRICS["SM_MOUSEWHEELPRESENT"] = 75] = "SM_MOUSEWHEELPRESENT";
    // 如果存在网络，则设置最小有效位;否则，将清除它。 其他位保留供将来使用。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_NETWORK"] = 63] = "SM_NETWORK";
    // 如果安装了 Microsoft Windows for Pen 计算扩展，则为非零值;否则为零。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_PENWINDOWS"] = 41] = "SM_PENWINDOWS";
    // 此系统指标在终端服务环境中用于确定是否远程控制当前终端服务器会话。 如果远程控制当前会话，则其值为非零值;否则为 0。可以使用终端服务管理工具（如终端服务管理器 (tsadmin.msc) 和shadow.exe）来控制远程会话。 远程控制会话时，另一个用户可以查看该会话的内容，并可能与之交互。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_REMOTECONTROL"] = 8193] = "SM_REMOTECONTROL";
    // 此系统指标用于终端服务环境。 如果调用进程与终端服务客户端会话相关联，则返回值为非零值。 如果调用进程与终端服务控制台会话相关联，则返回值为 0。 **Windows Server 2003 和 Windows XP：** 控制台会话不一定是物理控制台。 有关详细信息，请参阅 [WTSGetActiveConsoleSessionId](https://learn.microsoft.com/zh-cn/windows/desktop/api/winbase/nf-winbase-wtsgetactiveconsolesessionid)。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_REMOTESESSION"] = 4096] = "SM_REMOTESESSION";
    // 如果所有显示监视器具有相同的颜色格式，则为非零值，否则为 0。 两个显示器可以具有相同的位深度，但颜色格式不同。 例如，红色、绿色和蓝色像素可以使用不同位数进行编码，或者这些位可以位于像素颜色值的不同位置。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_SAMEDISPLAYFORMAT"] = 81] = "SM_SAMEDISPLAYFORMAT";
    // 应忽略此系统指标;它始终返回 0。                               
    SYSTEM_METRICS[SYSTEM_METRICS["SM_SECURE"] = 44] = "SM_SECURE";
    // 系统为 Windows Server 2003 R2 时的内部版本号;否则为 0。       
    SYSTEM_METRICS[SYSTEM_METRICS["SM_SERVERR2"] = 89] = "SM_SERVERR2";
    // 如果用户要求应用程序在仅以声音形式显示信息的情况下直观显示信息，则为非零值;否则为 0。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_SHOWSOUNDS"] = 70] = "SM_SHOWSOUNDS";
    // 如果当前会话正在关闭，则为非零;否则为 0。**Windows 2000：** 不支持此值。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_SHUTTINGDOWN"] = 8192] = "SM_SHUTTINGDOWN";
    // 如果计算机具有低端 (慢) 处理器，则为非零值;否则为 0。         
    SYSTEM_METRICS[SYSTEM_METRICS["SM_SLOWMACHINE"] = 73] = "SM_SLOWMACHINE";
    // 如果当前操作系统为 Windows 7 简易版 Edition、Windows Vista 入门版 或 Windows XP Starter Edition，则为非零;否则为 0。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_STARTER"] = 88] = "SM_STARTER";
    // 如果交换了鼠标左键和右键的含义，则为非零值;否则为 0。         
    SYSTEM_METRICS[SYSTEM_METRICS["SM_SWAPBUTTON"] = 23] = "SM_SWAPBUTTON";
    // 反映停靠模式的状态，0 表示未停靠模式，否则为非零。 当此系统指标发生更改时，系统会通过 LPARAM 中带有“SystemDockMode” [的WM_SETTINGCHANGE](https://learn.microsoft.com/zh-cn/windows/desktop/winmsg/wm-settingchange) 发送广播消息。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_SYSTEMDOCKED"] = 8196] = "SM_SYSTEMDOCKED";
    // 如果当前操作系统是 Windows XP 平板电脑版本，或者当前操作系统是 Windows Vista 或 Windows 7 并且平板电脑输入服务已启动，则为非零值;否则为 0。 SM_DIGITIZER设置指示运行 Windows 7 或 Windows Server 2008 R2 的设备支持的数字化器输入类型。 有关详细信息，请参阅“备注”。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_TABLETPC"] = 86] = "SM_TABLETPC";
    // 虚拟屏幕左侧的坐标。 虚拟屏幕是所有显示监视器的边框。 SM_CXVIRTUALSCREEN指标是虚拟屏幕的宽度。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_XVIRTUALSCREEN"] = 76] = "SM_XVIRTUALSCREEN";
    // 虚拟屏幕顶部的坐标。 虚拟屏幕是所有显示监视器的边框。 SM_CYVIRTUALSCREEN指标是虚拟屏幕的高度。  
    SYSTEM_METRICS[SYSTEM_METRICS["SM_YVIRTUALSCREEN"] = 77] = "SM_YVIRTUALSCREEN";
    // 从屏幕左下角开始。 默认位置。
    // --------------------------------
    // 从屏幕左下角开始。 默认位置。 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["ARW_BOTTOMLEFT"] = 0] = "ARW_BOTTOMLEFT";
    // 从屏幕右下角开始。 等效于 ARW_STARTRIGHT。 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["ARW_BOTTOMRIGHT"] = 1] = "ARW_BOTTOMRIGHT";
    // 从屏幕左上角开始。 等效于 ARW_STARTTOP。 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["ARW_TOPLEFT"] = 2] = "ARW_TOPLEFT";
    // 从屏幕右上角开始。 等效于 ARW_STARTTOP |SRW_STARTRIGHT。 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["ARW_TOPRIGHT"] = 3] = "ARW_TOPRIGHT";
    // --------------------------------
    // 垂直排列，从上到下 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["ARW_DOWN"] = 4] = "ARW_DOWN";
    // 通过将最小化的窗口移出屏幕的可见区域来隐藏这些窗口 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["ARW_HIDE"] = 8] = "ARW_HIDE";
    // 从左到右水平排列。 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["ARW_LEFT"] = 0] = "ARW_LEFT";
    // 	从右到左水平排列 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["ARW_RIGHT"] = 0] = "ARW_RIGHT";
    // 垂直排列，从下到上。 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["ARW_UP"] = 4] = "ARW_UP";
    // --------------------------------
    // 该设备具有集成的触摸数字化器 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["NID_INTEGRATED_TOUCH"] = 1] = "NID_INTEGRATED_TOUCH";
    // 设备具有外部触摸数字化器 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["NID_EXTERNAL_TOUCH"] = 2] = "NID_EXTERNAL_TOUCH";
    // 该设备具有集成的笔数字化器 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["NID_INTEGRATED_PEN"] = 4] = "NID_INTEGRATED_PEN";
    // 设备具有外部笔数字化器 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["NID_EXTERNAL_PEN"] = 8] = "NID_EXTERNAL_PEN";
    // 设备支持多个数字化器输入源 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["NID_MULTI_INPUT"] = 64] = "NID_MULTI_INPUT";
    // 设备已准备好接收数字化器输入。 [扩展值]
    SYSTEM_METRICS[SYSTEM_METRICS["NID_READY"] = 128] = "NID_READY";
    // 扩展值
    // 系统是否是64位
    SYSTEM_METRICS[SYSTEM_METRICS["HMC_IS_SYSTEM_64BIT"] = 1000000] = "HMC_IS_SYSTEM_64BIT";
    // 判断聚焦中的窗口是否是全屏
    SYSTEM_METRICS[SYSTEM_METRICS["HMC_IS_FOCUS_WINDOW_FULL_SCREEN"] = 1100001] = "HMC_IS_FOCUS_WINDOW_FULL_SCREEN";
    // 当前处于全屏模式（与 HMC_IS_FOCUS_WINDOW_FULL_SCREEN 不同的是此值是经过类型判断的排除了很多无意义可能 比如桌面）
    SYSTEM_METRICS[SYSTEM_METRICS["HMC_IS_FULL_SCREEN"] = 1200002] = "HMC_IS_FULL_SCREEN";
    // 系统时间转为时间戳 [纳秒]
    SYSTEM_METRICS[SYSTEM_METRICS["HMC_GET_TIMESTAMP"] = 1300003] = "HMC_GET_TIMESTAMP";
    // 系统启动到现在已经多久了
    SYSTEM_METRICS[SYSTEM_METRICS["HMC_GET_SYSTEM_IDLE_TIME"] = 1400004] = "HMC_GET_SYSTEM_IDLE_TIME";
    // GetTickCount64
    SYSTEM_METRICS[SYSTEM_METRICS["HMC_GET_TICK_COUNT64"] = 1500005] = "HMC_GET_TICK_COUNT64";
    // 当前进程正在以wow64方式运行 (wow是32位二进制在x64系统运行的虚拟容器)
    SYSTEM_METRICS[SYSTEM_METRICS["HMC_IS_PROCESS_WOW64"] = 1600006] = "HMC_IS_PROCESS_WOW64";
    // 获取当前进程的从启动到现在的时间 单位纳秒(ns)
    SYSTEM_METRICS[SYSTEM_METRICS["HMC_GET_PROCESS_START_TIME"] = 1700007] = "HMC_GET_PROCESS_START_TIME";
    // 当前进程是否拥有管理员权限
    SYSTEM_METRICS[SYSTEM_METRICS["HMC_IS_USER_AN_ADMIN"] = 1800008] = "HMC_IS_USER_AN_ADMIN";
})(SYSTEM_METRICS || (SYSTEM_METRICS = {}));
;
(async function () {
    var temp = native.getLinkTarget("F:\\source\\module\\hmc-win32\\source\\h2c-win32\\source\\cpp\\debug.js");
    console.log(temp);
    native.getLinkTarget("C:\\Windows\\explorer.exe");
    native.getLinkTarget("C:\\Windows\\regedit.exe");
    native.copyFile("F:\\1111.json", "F:\\111221.json", false, false, false);
    native.moveFile("F:\\1111.json", "F:\\111221.json", false, false, false);
})();
process.exitCode = 666;
