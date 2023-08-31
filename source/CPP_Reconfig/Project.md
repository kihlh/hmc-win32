

# 进度api列表



**此文档是hmc重构版本的 CPP代码接口的实例，本api列表的内容并不完全会在hmc和dll中导出，因为有些解构是需要经过二次转义的，hmc对于新版的重构理念是本着可以被cpp代码调用 可以兼容其他接口，所以api实现均为cpp的接口**

This document is an example of the CPP code interface for the refactored version of HMC. The content of this API list may not be fully exported in HMC and DLL because some structures need to undergo secondary escaping. For the new version, HMC follows the principle of being callable by CPP code and compatible with other interfaces, so all API implementations are in CPP interface.

------------------------------------------------------------------------------------------

#### （向下兼容hmc史山api）reback-hmc.hpp

  (愿天堂没有屎山)

 [查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/reback-hmc.hpp)

| API 名称 | 用途 | 完成度 | 类型重定向 | 测试 |
| -------- | ---- | ------ | ---------- | ---- |
| version |  | 固定为: 保留但移除信息 | string | null |
| desc |  | 固定为: hmc 2.0 : ' HMC Connection System api ' | string | null |
| platform |  | 固定为: win32                                   | string | null |
| arch |  | 保留为：64bit/32bit | string | null |
| getSystemIdleTime     |  ||    |      |
| sleep     |      ||    |      |
| isAdmin     |      ||    |      |
| openApp     |      ||    |      |
| openExternal     |      ||    |      |
| openURL     |      ||    |      |
| openPath     |      ||    |      |
| powerControl     |      ||    |      |
| getForegroundWindow     |      ||    |      |
| showMonitors     |      ||    |      |
| shutMonitors     |      ||    |      |
| getSystemMenu     |      ||    |      |
| messageBox     |      ||    |      |
| alert     |      ||    |      |
| confirm     |      ||    |      |
| MessageError     |      ||    |      |
| MessageStop     |      ||    |      |
| lookHandleSetTitle     |      ||    |      |
| lookHandleCloseWindow     |      ||    |      |
| isHandleWindowVisible     |      ||    |      |
| lookHandleShowWindow     |      ||    |      |
| lookHandleGetTitle     |      ||    |      |
| getProcessHandle     |      ||    |      |
| isSystemX64     |      ||    |      |
| getTrayList     |      ||    |      |
| setHandleTransparent     |      ||    |      |
| getHandleProcessID     |      ||    |      |
| getForegroundWindowProcessID     |      ||    |      |
| getMetrics     |      ||    |      |
| getPointWindowProcessId     |      ||    |      |
| getPointWindowName     |      ||    |      |
| getPointWindow     |      ||    |      |
| getDeviceCaps     |      ||    |      |
| getWindowRect     |      ||    |      |
| setWindowMode     |      ||    |      |
| closedHandle     |      ||    |      |
| setWindowTop     |      ||    |      |
| hasWindowTop     |      ||    |      |
| windowJitter     |      ||    |      |
| isHandle     |      ||    |      |
| getPointWindowMain     |      ||    |      |
| getMainWindow     |      ||    |      |
| isEnabled     |      ||    |      |
| setWindowEnabled     |      ||    |      |
| setWindowFocus     |      ||    |      |
| setForegroundWindow     |      ||    |      |
| updateWindow     |      ||    |      |
| SetWindowInTaskbarVisible     |      ||    |      |
| SetBlockInput     |      ||    |      |
| system     |      ||    |      |
| SetSystemHOOK     |      ||    |      |
| systemStartTime     |      ||    |      |
| getStringRegKey     |      ||    |      |
| hasRegistrKey     |      ||    |      |
| setRegistrKey     |      ||    |      |
| createPathRegistr     |      ||    |      |
| enumRegistrKey     |      ||    |      |
| getRegistrBuffValue     |      ||    |      |
| removeStringRegKeyWalk     |      ||    |      |
| removeStringRegKey     |      ||    |      |
| removeStringRegValue     |      ||    |      |
| setRegistrDword     |      ||    |      |
| setRegistrQword     |      ||    |      |
| getRegistrDword     |      ||    |      |
| getRegistrQword     |      ||    |      |
| getShortcutLink     |      ||    |      |
| setShortcutLink     |      ||    |      |
| createSymlink     |      ||    |      |
| createHardLink     |      ||    |      |
| createDirSymlink     |      ||    |      |
| getClipboardText     |      ||    |      |
| setClipboardText     |      ||    |      |
| clearClipboard     |      ||    |      |
| getClipboardFilePaths     |      ||    |      |
| setClipboardFilePaths     |      ||    |      |
| getHidUsbList     |      ||    |      |
| getUsbDevsInfo     |      ||    |      |
| enumChildWindows     |      ||    |      |
| deleteFile     |      ||    |      |
| _SET_HMC_DEBUG     |      |移除|    |      |
| getClipboardSequenceNumber     |      ||    |      |
| enumClipboardFormats     |      ||    |      |
| getHidUsbIdList     |      ||    |      |
| getSystemMetricsLen     |      ||    |      |
| getCurrentMonitorRect     |      ||    |      |
| getDeviceCapsAll     |      ||    |      |
| isMouseMonitorWindow     |      ||    |      |
| isInMonitorWindow     |      ||    |      |
| getWindowStyle     |      ||    |      |
| getWindowClassName     |      ||    |      |
| setWindowTitleIcon     |      ||    |      |
| setCursorPos     |      ||    |      |
| rightClick     |      ||    |      |
| leftClick     |      ||    |      |
| getMouseMovePoints     |      ||    |      |
| hasKeyActivate     |      ||    |      |
| getBasicKeys     |      ||    |      |
| mouse     |      ||    |      |
| installKeyboardHook     |      ||    |      |
| installHookMouse     |      ||    |      |
| unHookMouse     |      ||    |      |
| unKeyboardHook     |      ||    |      |
| getKeyboardNextSession     |      ||    |      |
| getMouseNextSession     |      ||    |      |
| isStartHookMouse     |      ||    |      |
| isStartKeyboardHook     |      ||    |      |
| getAllWindowsHandle     |      ||    |      |
| getProcessIdHandleStore     |      ||    |      |
| killProcess     |      ||    |      |
| getDetailsProcessList     |      ||    |      |
| getProcessList     |      ||    |      |
| hasProcess     |      ||    |      |
| isProcess     |      ||    |      |
| getProcessidFilePath     |      ||    |      |
| getProcessName     |      ||    |      |
| getModulePathList     |      ||    |      |
| enumProcessHandle     |      ||    |      |
| enumProcessHandlePolling     |      ||    |      |
| getVolumeList     |      ||    |      |
| formatVolumePath     |      ||    |      |
| getProcessThreadList     |      ||    |      |
| clearEnumProcessHandle     |      ||    |      |
| getSubProcessID     |      ||    |      |
| enumAllProcessPolling     |      ||    |      |
| enumAllProcess     |      ||    |      |
| getProcessParentProcessID     |      ||    |      |
| clearEnumAllProcessList     |      ||    |      |
| setWindowIconForExtract     |      ||    |      |
| popen     |      ||    |      |
| _popen     |      ||    |      |
| sendKeyT2C     |      ||    |      |
| sendKeyboard     |      ||    |      |
| sendKeyT2CSync     |      ||    |      |
| sendBasicKeys     |      ||    |      |
| captureBmpToFile     |      ||    |      |
| getColor     |      ||    |      |
| createMutex     |      ||    |      |
| hasMutex     |      ||    |      |
| putenv     |      ||    |      |
| getenv     |      ||    |      |
| getAllEnv     |      ||    |      |
| getUDPPortProcessID     |      ||    |      |
| getTCPPortProcessID     |      ||    |      |

#### （进程）process.hpp 

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/process.hpp)

| API 名称                      | 用途         | 完成度 | 类型重定向 | 测试   |
| ----------------------------- | ------------ | ------ | ---------- | ------ |
| getParentProcessID            |              | true   | 1          | 未压测 |
| getSubProcessList             |              | true   | 1          | 未压测 |
| getFilePath                   |              | true   | 1          | 未压测 |
| killProcessID                 |              | true   | 1          | 未压测 |
| existsProcessID               |              | true   | 1          | 未压测 |
| getHwnd                       |              | true   | 1          | 未压测 |
| getBaseName                   |              | true   | 1          | 未压测 |
| getThreadList                 |              | true   | 1          | 未压测 |
| getThreadList                 |              | true   | 1          | 未压测 |
| getModulePathList             |              | true   | 1          | 未压测 |
| getPointWindowProcessId       |              | true   | 1          | 未压测 |
| getPointWindowProcessBaseName |              | true   | 1          | 未压测 |
| getFocusWindowProcessID       |              | true   | 1          | 未压测 |
| getFocusWindowProcessBaseName |              | true   | 1          | 未压测 |
| ProcessEnumDetailsCont        |              | true   | struct     | null   |
| ProcessEnumCont               |              | true   | struct     | null   |
| hmc_ProcessHandleContext      |              | true   | struct     | null   |
| getProcessList                |              | true   | 2          | null   |
| getHwndProcessID              |              | true   | 1          | 未压测 |
| enumProcessHandle             |              | true   | 1          | 未压测 |
| getProcessMemoryInfo          |              | true   | 1          | 未压测 |
| getProcessCpuUsage            |              | true   | 1          | 未压测 |
| enumProcessSnapshot           |              | true   | 1          | 未压测 |
| treeAllProcessJson            |              | true   | 1          | 未压测 |
| getProcessCommand             |              | true   | 1          | 未压测 |
| getProcessIDTimes             |              | true   | 1          | 未压测 |
| treeAllProcess                |              | 计划   | 1          | 未压测 |
| HMC_IMPORT_PROCESS_H          | 避免重复导入 | true   | null       | null   |

#### （窗口）window.hpp 

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/window.hpp)

| API 名称                  | 用途                                                         | 完成度 | 类型重定向 | 测试     |
| ------------------------- | ------------------------------------------------------------ | ------ | ---------- | -------- |
| showProgress              | 在窗口图标显示进度                                           | 计划   | **plan**   | **plan** |
| isWindowVisible           | 判断句柄是否是可见的 (也可以判断是否是合法的窗口句柄)        | true   |            |          |
| getClassName              | 获取窗口类名                                                 | true   | 2          | 未压测   |
| getStyle                  | 获取样式id                                                   | true   | 1          | 未压测   |
| getWindowID               | 获取 窗口/控件 的id                                          | true   |            |          |
| getSubWindow              | 枚举子窗口                                                   | true   |            |          |
| getParentWindow           | 获取父级窗口                                                 | true   |            |          |
| getWindowText             | 获取窗口文本/title                                           | true   | 2          |          |
| isChildWindow             | 判断是否是XX的 子窗口                                        | true   |            |          |
| getTopWindow              | 获取附属的根级窗口                                           | true   |            |          |
| setWindowText             |                                                              |        | 2          |          |
| updateWindow              | 刷新指定句柄的窗口                                           | true   |            |          |
| getPointWindow            | 获取指定坐标位置的窗口/获取当前鼠标坐标位置的窗口            | true   | 2          |          |
| setWindowEnabled          | 设置窗口禁用                                                 | true   |            |          |
| setWindowFocus            | 非常复杂                                                     |        |            |          |
| setWindowTop              | 设置窗口的顶设状态                                           | true   |            |          |
| isWindowTop               | 判断窗口是否顶设                                             | true   |            |          |
| setWindowShake            | 窗口抖动                                                     | true   | 2          |          |
| isWindowEnabled           |                                                              | true   |            |          |
| setWindowInTaskbarVisible | 设置窗口在托盘的可见性                                       | true   |            |          |
| setWindowTransparent      | 设置窗口可见性 百分比 如：0.92 / 0-255                       | true   | 2          |          |
| getAllWindowsHwnd         | 枚举所有句柄                                                 | true   |            |          |
| closedHandle              | 关闭指定句柄(强制关闭窗口)                                   | true   |            |          |
| closeWindow               | 关闭指定窗口                                                 | true   |            |          |
| setWindowFileIcon         | 设置窗口图标为文件 例如dll/exe                               | true   |            |          |
| setWindowIcon             | 设置窗口图标为指定的icon文件/设置图标为当前二进制的图标      | true   | 3          |          |
| getProcessIDWindow        | 获取指定进程id所属的窗口                                     |        |            |          |
| setMoveWindow             | 设置窗口位置                                                 |        |            |          |
| getFocusWindow            | 获取当前激活的窗口                                           |        |            |          |
| setWindowCenter           | 设置窗口到屏幕中间                                           |        |            |          |
| isFullScreen              | 窗口是否处于正常状态（未最大化、未最小化、未处于全屏模式）   |        |            |          |
| isFocused                 | 窗口是否获得焦点                                             |        |            |          |
| isFullScreen              | 判断窗口是否全屏中                                           |        |            |          |
| isMinimized               | 判断窗口是否最小化                                           |        |            |          |
| isMaximize                | 判断窗口是否最大化                                           |        |            |          |
| setNotVisibleWindow       | 让这个窗口不可见(不可触) 但是他是活动状态的 （本人用来挂机小游戏） |        |            |          |
| isDesktopWindow           | 判断此窗口是否是桌面                                         |        |            |          |
| sendMessage               | 发送窗口消息                                                 |        |            |          |
| getWindowStatus           | 获取窗口基础信息并且深挖他所属的进程的所有句柄               |        |            |          |
| 计划中.....               |                                                              |        |            |          |
| HMC_IMPORT_WINDOW_H       | 避免重复导入                                                 | true   | null       | null     |


#### （调试）console.hpp 

 [查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/console.hpp)

| API 名称                 | 用途                              | 完成度 | 类型重定向 | 测试  |
| ------------------------ | --------------------------------- | ------ | ---------- | ----- |
| **level**                | 日志等级                          | true   | 无         | false |
| **escapeJson**           | 转义json字符                      | true   | 1          | true  |
| **get_time**             | 日期头 [2023-01-02 08:08:25 .666] | true   | 1          | true  |
| **separator**            | 分割线                            | true   | 1          | true  |
| **setLogToCout**         | 启用控制台打印                    | true   | 1          | true  |
| **setLogToFile**         | 启用打印到日志文件                | true   | 1          | true  |
| **setLevel**             | 设置控制台和日志的记录等级        | true   | 1          | true  |
| **setFileLevel**         | 仅设置日志文件的记录等级          | true   | 1          | true  |
| **setCoutLevel**         | 仅设置控制台记录等级              | true   | 1          | true  |
| **info**                 | 打印常规文本                      | true   | 1          | true  |
| **error**                | 打印错误文本(红色)                | true   | 1          | true  |
| **warn**                 | 打印警告文本                      | true   | 1          | true  |
| **debug**                | 打印开发时候的内容                | true   | **31**     | true  |
| **time**                 | 开始计算运行时间(相对)            | true   | 2          | true  |
| **timeEnd**              | 结束计算运行时间(相对)            | true   | 2          | true  |
| **HMC_IMPORT_CONSOLE_H** | 避免重复导入                      | true   | null       | null  |
| showConsoleWin           | 显示hmc内部调试器的黑框框         | 计划   |            |       |

#### （托盘）tray.hpp

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/tray.hpp)

| API 名称                 | 用途                                    | 完成度     | 类型重定向 | 测试  |
| ------------------------ | --------------------------------------- | ---------- | ---------- | ----- |
| **Menu**                 | 归类                                    | true       | 1          | true  |
| **Menu::menu**           | 创建一个常规按钮                        | true       | 1          | true  |
| **Menu::check**          | 创建一个选项按钮                        | true       | 1          | true  |
| **Menu::separator**      | 创建一个分割线                          | true       | 1          | true  |
| **setMenuItmetoSubMenu** | 将B按钮设置到A按钮的子按钮(折叠项)      | true       | 6          | true  |
| **getMenuItme**          | 使用文本id获取按钮                      | true       | 1          | true  |
| **setMenuItmeVisible**   | 设置按钮可见性                          | true       | 1          | true  |
| **setMenuItmeEnable**    | 设置按钮是否禁用                        | true       | 1          | true  |
| **setMenuItmeName**      | 设置按钮名称                            | true       | 1          | true  |
| **setMenuItmeSelect**    | 设置按钮是否选中(check)                 | true       | 1          | true  |
| **setTrayInfo**          | 显示文本                                | true       | 1          | true  |
| **addMenuItem**          | 添加按钮                                | true       | 1          | true  |
| **close**                | 销毁                                    | true       | 1          | true  |
| **start**                | 启动                                    | true       | 1          | true  |
| **setTrayIcon**          | 设置托盘图标                            | true       | 3          | true  |
| **once**                 | 监听事件或者按钮的id被点击的回调 (单次) | true       | 1(2)       | true  |
| **on**                   | 监听事件或者按钮的id被点击的回调        | true       | 1(2)       | true  |
| **chMenuItem**           | 按钮存储体                              | true       | struct     | null  |
| **chMenuType**           | 按钮类型                                | true       | struct     | null  |
| **HMC_IMPORT_TRAY_H**    | 避免重复导入                            | true       | null       | null  |
| **multiple instances**   | 多个实例支持 不考虑支持 会破坏node安全  | **ignore** | false      | false |

#### （屏幕）screen.hpp   

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/screen.hpp)

| API 名称                | 用途                | 完成度   | 类型重定向 | 测试 |
| ----------------------- | ------------------- | -------- | ---------- | ---- |
| **GetDeviceCapsAll**    | 获取所有屏幕位置    | true     | 1          | true |
| **GetColor**            | 获取指定坐标的颜色  | true     | 1          | true |
| **CaptureBmpToBuff**    | 截图bmp并获取缓冲   | true     | 1          | true |
| **CaptureBmpToFile**    | 截图bmp并获取为文件 | true     | 1          | true |
| **isInside**            | 判断是否过界        | true     | 1          | true |
| **CaptureJpegToFile**   | 截图jpg并获取为文件 | **plan** | 1          | null |
| **CaptureJpegToBuff**   | 截图jpg并获取缓冲   | **plan** | 1          | null |
| **CapturePngToFile**    | 截图png并获取为文件 | **plan** | 1          | null |
| **CapturePngToBuff**    | 截图png并获取缓冲   | **plan** | 1          | null |
| **HMC_IMPORT_SCREEN_H** | 避免重复导入        | true     | null       | null |

#### （注册表）registr.hpp 

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/registr.hpp)

| API 名称                 | 用途                              | 完成度 | 类型重定向 | 测试 |
| ------------------------ | --------------------------------- | ------ | ---------- | ---- |
| **chQueryDirStat**       | 目录的信息                        | true   | struct     | null |
| **chQueryDirKey**        | 枚举键                            | true   | struct     | null |
| **chWalkItme**           | 遍历树结构的信息 但是不返回内容   | true   | struct     | null |
| **chValueStat**          | 获取值的信息                      | true   | struct     | null |
| **getHive**              | 根目录隐私为文本 / 文本隐射为根   | true   | 2          | true |
| **getRegistrDirStat**    | 获取目录的信息多少个 key 更新时间 | true   | 2          | true |
| **listKey**              | 枚举key                           | true   | 2          | true |
| **path2hKey**            | 完整路径分析出HKEY和路径          | true   | 1          | true |
| **getValueStat**         | 获取值类型与值路径                | true   | 1          | true |
| **getValueStat**         | 获取值类型与值路径                | true   | 1          | true |
| **setRegistrValue**      | 设置内容 自识别或者自定义         | true   | any type   | true |
| **getRegistrValue**      | 获取指定的值                      | true   | any type   | true |
| **getRegistrAnyValue**   | 获取单条数据并返回类型与数据      | true   | 1          | true |
| **hasRegistrKey**        | 判断是否存在此key                 | true   | 1          | true |
| **hasRegistrDir**        | 判断是否存在此key                 | true   | 1          | true |
| **removeRegistrValue**   | 删除指定的值                      | true   | 1          | true |
| **removeRegistrTree**    | 删除注册表值树                    | true   | 1          | true |
| **removeRegistrDir**     | 删除指定文件夹                    | true   | 1          | true |
| **createRegistrDir**     | 创建文件夹                        | true   | 1          | true |
| **copyRegistrDir**       | 复制指定的目录到指定目录          | true   | 1          | true |
| **walkRegistrDir**       | 获取目录表中的键                  | true   | 1          | true |
| **HMC_IMPORT_REGISTR_H** | 避免重复导入                      | true   | null       | null |


#### （hmc视图）gui.hpp 

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/gui.hpp)

| API 名称                           | 用途                       | 完成度   | 类型重定向 | 测试 |
| ---------------------------------- | -------------------------- | -------- | ---------- | ---- |
| **onSearchBoxCallbackFunc**        | 搜索框的回调函数           | **plan** | typedef    | null |
| **prompt**                         | 输入框                     | **plan** |            |      |
| **password**                       | 密码库                     | **plan** |            |      |
| **passLogin**                      | 登录框                     | **plan** |            |      |
| **SearchBox**                      | 搜索框 的类 浏览的ctrl+f   | **plan** | Class(4)   | null |
| **SearchBox** -> **close**         | 销毁                       | **plan** |            |      |
| **SearchBox** -> **on**            | 监听上一个/下一个          | **plan** |            |      |
| **SearchBox** -> **setInput**      | 设置输入框                 | **plan** |            |      |
| **SearchBox** -> **getInput**      | 获取输入框内容             | **plan** |            |      |
| **SearchBox** -> **getLen**        | 获取当前上限               | **plan** |            |      |
| **SearchBox** -> **setLen**        | 设置当前上限               | **plan** |            |      |
| **SearchBox** -> **setIndex**      | 设置当前索引位置           | **plan** |            |      |
| **SearchBox** -> **getIndex**      | 获取当前索引位置           | **plan** |            |      |
| **progressBar**                    | 进度条 的类 一个进度条窗口 | **plan** |            |      |
| **progressBar** -> **close**       | 销毁                       | **plan** |            |      |
| **progressBar** -> **getProgress** | 获取当前进度 0.0 - 1.0     | **plan** | 2/1        |      |
| **progressBar** -> **setProgress** | 设置当前进度 0.0 - 1.0     | **plan** | 2/1        |      |
| **progressBar** -> **getProgress** | 获取当前进度 0 - 100       | **plan** | 2/2        |      |
| **progressBar** -> **setProgress** | 设置当前进度 0 - 100       | **plan** | 2/2        |      |

#### （文本处理）text.hpp 

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/text.hpp)

| API 名称           | 用途                                        | 完成度 | 类型重定向 | 测试 |
| ------------------ | ------------------------------------------- | ------ | ---------- | ---- |
| **base64_encode**  | 将A转为bs64                                 | true   | 1          | true |
| **W2A**            | WIDE to ANSI                                | true   | 1          | true |
| **A2B64A**         | A字符转为base64字符A                        | true   | 1          | true |
| **W2B64A**         | W字符转为base64字符A                        | true   | 1          | true |
| **A2B64W**         | A字符转为base64字符W                        | true   | 1          | true |
| **W2B64W**         | W字符转为base64字符W                        | true   | 1          | true |
| **A2W**            | ANSI to WIDE                                | true   | 1          | true |
| **W2U8**           | 宽字符字符串转UTF-8字符串                   | true   | 1          | true |
| **U82W**           | UTF-8字符串转宽字符                         | true   | 1          | true |
| **A2U8**           | 多字节字符串转UTF-8字符串                   | true   | 1          | true |
| **U82A**           | UTF-8字符串转多字节字符串                   | true   | 1          | true |
| **U82B64A**        | TF-8 to Base64 encoding ANSI                | true   | 1          | true |
| **U82B64W**        | UTF-8 to Base64 encoding WIDE               | true   | 1          | true |
| **UTF8ToGBK**      | UFT8 字符转为GBK(中文)                      | true   | 1          | true |
| **hasIntStr**      | 文本中是否有数字 并且是否是安全的 int32     | true   | 1          | true |
| **haslongStr**     | 文本中是否有数字 并且是否是安全的 long      | true   | 1          | true |
| **haslonglongStr** | 文本中是否有数字 并且是否是安全的 long long | true   | 1          | true |
| **CStringToUTF8**  | CString  To UTF8                            | true   | 1          | true |
| **UTF8ToCString**  | UTF8  To  CString                           | true   | 1          | true |

#### （napi类型转换）napi_util.hpp

 [查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/napi_util.hpp)

| API 名称 | 用途 | 完成度 | 类型重定向 | 测试 |
| -------- | ---- | ------ | ---------- | ---- |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |

#### （USB）usb.hpp

 [查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/usb.hpp)

| API 名称 | 用途 | 完成度 | 类型重定向 | 测试 |
| -------- | ---- | ------ | ---------- | ---- |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |

#### （变量环境）environment.hpp 

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/environment.hpp)

| API 名称                        | 用途         | 完成度 | 类型重定向 | 测试 |
| ------------------------------- | ------------ | ------ | ---------- | ---- |
| GetVariable                     |              | true   | 1          | true |
| isSystemFor64bit                |              | true   | 1          | true |
| getVariableAll                  |              | true   | 1          | true |
| getenv                          |              | true   | 1          | true |
| setCwd                          |              | true   | 1          | true |
| getenv                          |              | true   | 1          | true |
| getcmdLine                      |              | true   | 1          | true |
| getcmd                          |              | true   | 1          | true |
| getpid                          |              | true   | 1          | true |
| getppid                         |              | true   | 1          | true |
| getcwd                          |              | true   | 1          | true |
| getexecPath                     |              | true   | 1          | true |
| getexecDirPath                  |              | true   | 1          | true |
| getarch                         |              | true   | 1          | true |
| hasEnvKey                       |              | true   | 1          | true |
| putenv                          |              |        | 3          |      |
| getEnvList                      |              | true   | 1          | true |
| removeEnv                       |              | true   | 1          | true |
| Mutex                           |              | true   | 1          | true |
| Mutex::create                   |              | true   | 1          | true |
| Mutex::has                      |              | true   | 1          | true |
| Mutex::remove                   |              | true   | 1          | true |
| Mutex::list                     |              | true   | 1          | true |
| systemEnv                       |              | true   | 1          | true |
| systemEnv::keyUpper             |              | true   | 1          | true |
| systemEnv::keyDiff              |              | true   | 1          | true |
| systemEnv::freezeEnvKeys        |              | true   | 1          | true |
| systemEnv::get                  |              | true   | 1          | true |
| systemEnv::getSys               |              | true   | 1          | true |
| systemEnv::putUse               |              | true   | 1          | true |
| systemEnv::getUse               |              | true   | 1          | true |
| systemEnv::putSys               |              | true   | 1          | true |
| systemEnv::removeUse            |              | true   | 1          | true |
| systemEnv::removeSys            |              | true   | 1          | true |
| systemEnv::removeAll            |              | true   | 1          | true |
| systemEnv::updateThis           |              | true   | 1          | true |
| systemEnv::hasSysKeyExists      |              | true   | 1          | true |
| systemEnv::hasUseKeyExists      |              | true   | 1          | true |
| systemEnv::hasKeyExists         |              | true   | 1          | true |
| systemEnv::hasExpval            |              | true   | 1          | true |
| systemEnv::keySysList           |              | true   | 1          | true |
| systemEnv::keyUseList           |              | true   | 1          | true |
| systemEnv::getEnvVariable       |              | true   | 1          | true |
| systemEnv::getEnvVariable       |              | true   | 1          | true |
| systemEnv::escapeEnvVariable    |              | true   | 1          | true |
| systemEnv::getGlobalVariableAll |              | true   | 1          | true |
| systemEnv::getGlobalVariable    |              | true   | 1          | true |
| HMC_IMPORT_ENVIRONMENT_H        | 避免重复导入 | true   | null       | null |

#### （网络）sock.hpp  

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/sock.hpp)

| API 名称             | 用途                             | 完成度 | 类型重定向 | 测试 |
| -------------------- | -------------------------------- | ------ | ---------- | ---- |
| getNetParams         | 适配器信息                       | true   | 0          | true |
| enumConnectNet       | 枚举本机所有的已经打开的端口信息 | true   | 3          | true |
| GetUDPPortProcessID  | 获取指定TCP端口的进程id          | true   | 0          | true |
| GetTCPPortProcessID  | 获取指定TCP端口的进程id          | true   | 0          | true |
| TCP4                 | 支持                             | true   | 0          | true |
| TCP6                 | 支持                             | true   | 0          | true |
| UDP4                 | 支持                             | true   | 0          | true |
| UDP6                 | 支持                             | true   | 0          | true |
| GetUDP6PortProcessID | 获取指定UDP6端口的进程id列表     | true   | 0          | true |
| GetTCP6PortProcessID | 获取指定TCP6端口的进程id列表     | true   | 0          | true |
| formatIP             | 格式化ip                         |        |            |      |
| GetStateName         | U6,T6,U4,T4                      |        |            |      |

#### （初始化hmc）newhmc.hpp

 [查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/newhmc.hpp)

| API 名称 | 用途 | 完成度 | 类型重定向 | 测试 |
| -------- | ---- | ------ | ---------- | ---- |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |
|          |      |        |            |      |

#### （提权工具）attribute.hpp 

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/include/attribute.hpp)

| API 名称                   | 用途     | **description**                | 完成度 | 类型重定向 | 测试 |
| -------------------------- | -------- | ------------------------------ | ------ | ---------- | ---- |
| **hmc_EnableShutDownPriv** | 临时提权 | Temporary privilege escalation | true   | false      | true |
|                            |          |                                |        |            |      |

##### (AutoItX扩展) AutoItX.hpp   新模块: hmc-AutoItX

 AutoItX.hpp是hmc的一个扩展 是个独立模块

| API 名称 | 用途 | **description** | 完成度 | 类型重定向 | 测试 |
| -------- | ---- | ------ | ---------- | ---- | ---- |
|     **Init**     | 初始化AutoItX，通常在开始使用AutoItX函数之前调用 | Initializes the AutoItX library. |  **plan**      |      1      |      |
|     **error**     | 获取上一次AutoItX函数调用返回的错误代码 | Retrieves the error code from the last AutoItX function call. |  **plan**      |      1      |      |
|     **AutoItSetOption**     | 设置AutoIt的选项，可以用来配置AutoIt的一些行为 | Sets various options for AutoItX, such as timeout and behavior. |  **plan**      |      1      |      |
|     **ClipGet**     | 获取剪贴板的内容 | Retrieves the content of the Windows clipboard. |  **plan**      |      1      |      |
|     **ClipPut**     | 将文本放入剪贴板 | Puts text into the Windows clipboard. |  **plan**      |      1      |      |
|     **ControlClick**     | 模拟控件的点击操作 | Simulates a mouse click on a specified control (button, checkbox, etc.) in a window. |  **plan**      |      1      |      |
|     **ControlClickByHandle**     | 使用控件句柄模拟控件的点击操作 | Same as `AU3_ControlClick` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlCommand**     | 发送命令给控件，比如选择列表中的项、设置复选框状态等 | Sends a command to a control (button, checkbox, radio button, etc.) in a window. |  **plan**      |      1      |      |
|     **ControlCommandByHandle**     | 使用控件句柄发送命令给控件 | Same as `AU3_ControlCommand` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlListView**     | 操作ListView控件 | Sends commands to a ListView control (such as list items selection) in a window. |  **plan**      |      1      |      |
|     **ControlListViewByHandle**     | 使用控件句柄操作ListView控件 | Same as `AU3_ControlListView` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlDisable**     | 禁用控件 | Disables a control in a window. |  **plan**      |      1      |      |
|     **ControlDisableByHandle**     | 使用控件句柄禁用控件 | Same as `AU3_ControlDisable` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlEnable**     | 启用控件 | Enables a control in a window. |  **plan**      |      1      |      |
|     **ControlEnableByHandle**     | 使用控件句柄启用控件 | Same as `AU3_ControlEnable` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlFocus**     | 将焦点设置到控件上 | Sets focus to a control in a window. |  **plan**      |      1      |      |
|     **ControlFocusByHandle**     | 使用控件句柄将焦点设置到控件上 | Same as `AU3_ControlFocus` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlGetFocus**     | 获取当前具有焦点的控件句柄 | Retrieves the handle of the control with focus. |  **plan**      |      1      |      |
|     **ControlGetFocusByHandle**     | 使用控件句柄获取当前具有焦点的控件句柄 | Same as `AU3_ControlGetFocus` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlGetHandle**     | 获取控件句柄 | Retrieves the handle of a control in a window. |  **plan**      |      1      |      |
|     **ControlGetHandleAsText**     | 获取控件句柄并返回为文本 | Retrieves the handle of a control in a window as text. |  **plan**      |      1      |      |
|     **ControlGetPos**     | 获取控件的位置和尺寸 | Retrieves the position and size of a control in a window. |  **plan**      |      1      |      |
|     **ControlGetPosByHandle**     | 使用控件句柄获取控件的位置和尺寸 | Same as `AU3_ControlGetPos` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlGetText**     | 获取控件的文本内容 | Retrieves the text from a control in a window. |  **plan**      |      1      |      |
|     **ControlGetTextByHandle**     | 使用控件句柄获取控件的文本内容 | Same as `AU3_ControlGetText` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlHide**     | 隐藏控件 | Hides a control in a window. |  **plan**      |      1      |      |
|     **ControlHideByHandle**     | 使用控件句柄隐藏控件 | Same as `AU3_ControlHide` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlMove**     | 移动控件到指定位置 | Moves a control within a window. |  **plan**      |      1      |      |
|     **ControlMoveByHandle**     | 使用控件句柄移动控件到指定位置 | Same as `AU3_ControlMove` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlSend**     | 向控件发送按键输入 | Sends keystrokes to a control in a window. |  **plan**      |      1      |      |
|     **ControlSendByHandle**     | 使用控件句柄向控件发送按键输入 | Same as `AU3_ControlSend` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **ControlSetText**     | 设置控件的文本内容 | Sets the text of a control in a window. |  **plan**      |      1      |      |
|     **ControlSetTextByHandle**     | 使用控件句柄设置控件的文本内容 | Sets the text of a control in a window using its handle. |  **plan**      |      1      |      |
|     **ControlShow**     | 显示控件 | Shows a control in a window. |  **plan**      |      1      |      |
|     **ControlShowByHandle**     | 使用控件句柄显示控件 | Shows a control in a window using its handle. |  **plan**      |      1      |      |
|     **ControlTreeView**     | 操作TreeView控件 | Sends commands to a TreeView control in a window. |  **plan**      |      1      |      |
|     **ControlTreeViewByHandle**     | 使用控件句柄操作TreeView控件 | Same as `AU3_ControlTreeView` but uses a handle instead of window and control IDs. |  **plan**      |      1      |      |
|     **DriveMapAdd**     | 映射本地驱动器到网络共享路径 | Maps a network drive. |  **plan**      |      1      |      |
|     **DriveMapDel**     | 取消驱动器映射 | Unmaps a network drive. |  **plan**      |      1      |      |
|     **DriveMapGet**     | 获取驱动器映射的信息 | Retrieves the mapping of a network drive. |  **plan**      |      1      |      |
|     **IsAdmin**     | 检查当前用户是否有管理员权限 | Checks if the current process is running with administrative privileges. |  **plan**      |      1      |      |
|     **MouseClick**     | 模拟鼠标点击 | Simulates a mouse click at the current cursor position. |  **plan**      |      1      |      |
|     **MouseClickDrag**     | 模拟鼠标点击并拖动 | Simulates dragging the mouse between two points. |  **plan**      |      1      |      |
|     **MouseDown**     | 模拟鼠标按下 | Simulates pressing a mouse button. |  **plan**      |      1      |      |
|     **MouseGetCursor**     | 获取鼠标当前的光标样式 | Retrieves the mouse cursor's current shape. |  **plan**      |      1      |      |
|     **MouseGetPos**     | 获取鼠标当前位置 | Retrieves the current position of the mouse cursor. |  **plan**      |      1      |      |
|     **MouseMove**     | 移动鼠标到指定位置 | Moves the mouse cursor to a specified position. |  **plan**      |      1      |      |
|     **MouseUp**     | 模拟鼠标释放 | Simulates releasing a mouse button. |  **plan**      |      1      |      |
|     **MouseWheel**     | 模拟鼠标滚轮滚动 | Simulates scrolling the mouse wheel. |  **plan**      |      1      |      |
|     **Opt**     | 设置AutoIt选项 | Sets options for AutoItX |  **plan**      |      1      |      |
|     **PixelChecksum**     | 获取屏幕区域的像素校验和 | Calculates a checksum of a region of pixels on the screen. |  **plan**      |      1      |      |
|     **PixelGetColor**     | 获取屏幕上指定位置的像素颜色 | Retrieves the color of a pixel at a specified position. |  **plan**      |      1      |      |
|     **PixelSearch**     | 在屏幕上搜索指定颜色的像素 | Searches for a pixel of a specific color in a region of the screen. |  **plan**      |      1      |      |
|     **ProcessClose**     | 关闭进程 | Closes a specified process. |  **plan**      |      1      |      |
|     **ProcessExists**     | 检查进程是否存在 | Checks if a specified process exists. |  **plan**      |      1      |      |
|     **ProcessSetPriority**     | 设置进程的优先级 | Sets the priority of a specified process. |  **plan**      |      1      |      |
|     **ProcessWait**     | 等待进程的出现 | Waits for a specified process to exist. |  **plan**      |      1      |      |
|     **ProcessWaitClose**     | 等待进程的结束 | Waits for a specified process to close. |  **plan**      |      1      |      |
|     **Run**     | 用于运行外部程序或执行系统命令 | Runs an external program or opens a document. |  **plan**      |      1      |      |
|     **RunWait**     | 运行外部程序并等待其完成 | Runs an external program and waits for it to complete. |  **plan**      |      1      |      |
|     **RunAs**     | 以其他用户的身份运行外部程序 | Runs an external program with different credentials (as a different user). |  **plan**      |      1      |      |
|     **RunAsWait**     | 以其他用户的身份运行外部程序并等待其完成 | Runs an external program with different credentials and waits for it to complete. |  **plan**      |      1      |      |
|     **Send**     | 向活动窗口发送按键输入 | Sends simulated keystrokes. |  **plan**      |      1      |      |
|     **Shutdown**     | 关闭或重启系统 | Shuts down, restarts, or logs off the computer. |  **plan**      |      1      |      |
|     **Sleep**     | 在脚本中加入暂停/延迟 | Pauses the script for a specified number of milliseconds. |  **plan**      |      1      |      |
|     **StatusbarGetText**     | 获取状态栏的文本内容 | Retrieves the text from the status bar of a window. |  **plan**      |      1      |      |
|     **StatusbarGetTextByHandle**     | 使用控件句柄获取状态栏的文本内容 | Retrieves the text from the status bar of a window using its handle. |  **plan**      |      1      |      |
|     **ToolTip**     | 显示一个提示框，通常用于在屏幕上显示临时的提示信息 | Creates a tooltip with the specified text at the current mouse position or on a specific control. |  **plan**      |      1      |      |
|     **WinActivate**     | 激活指定的窗口 | Activates a window by title or window handle. |  **plan**      |      1      |      |
|     **WinActivateByHandle**     | 使用窗口句柄激活指定的窗口 | Activates a window using its handle. |  **plan**      |      1      |      |
|     **WinActive**     | 检查指定的窗口是否处于活动状态 | Checks if a window is currently active by title. |  **plan**      |      1      |      |
|     **WinActiveByHandle**     | 使用窗口句柄检查指定的窗口是否处于活动状态 | Checks if a window is currently active using its handle. |  **plan**      |      1      |      |
|     **WinClose**     | 关闭指定的窗口 | Closes a window by title. |  **plan**      |      1      |      |
|     **WinCloseByHandle**     | 使用窗口句柄关闭指定的窗口 | Closes a window using its handle. |  **plan**      |      1      |      |
|     **WinExists**     | 检查指定的窗口是否存在 | Checks if a window exists by title. |  **plan**      |      1      |      |
|     **WinExistsByHandle**     | 使用窗口句柄检查指定的窗口是否存在 | Checks if a window exists using its handle. |  **plan**      |      1      |      |
|     **WinGetCaretPos**     | 获取当前光标的位置 | Retrieves the position of the caret in the active window. |  **plan**      |      1      |      |
|     **WinGetClassList**     | 获取指定窗口的类名列表 | Retrieves a list of classes used by a window by title. |  **plan**      |      1      |      |
|     **WinGetClassListByHandle**     | 使用窗口句柄获取指定窗口的类名列表 | Retrieves a list of classes used by a window using its handle. |  **plan**      |      1      |      |
|     **WinGetClientSize**     | 获取指定窗口客户区的尺寸 | Retrieves the client area's size of a window by title. |  **plan**      |      1      |      |
|     **WinGetClientSizeByHandle**     | 使用窗口句柄获取指定窗口客户区的尺寸 | Retrieves the client area's size of a window using its handle. |  **plan**      |      1      |      |
|     **WinGetHandle**     | 获取指定窗口的句柄 | Retrieves the handle of a window by title. |  **plan**      |      1      |      |
|     **WinGetHandleAsText**     | 获取指定窗口的句柄并返回为文本 | Retrieves the handle of a window by title as text. |  **plan**      |      1      |      |
|     **WinGetPos**     | 获取指定窗口的位置和尺寸 | Retrieves the position and size of a window by title. |  **plan**      |      1      |      |
|     **WinGetPosByHandle**     | 使用窗口句柄获取指定窗口的位置和尺寸 | Retrieves the position and size of a window using its handle. |  **plan**      |      1      |      |
|     **WinGetProcess**     | 获取指定窗口的进程ID | Retrieves the process ID of a window by title. |  **plan**      |      1      |      |
|     **WinGetProcessByHandle**     | 使用窗口句柄获取指定窗口的进程ID | Retrieves the process ID of a window using its handle. |  **plan**      |      1      |      |
|     **WinGetState**     | 获取指定窗口的状态 | Retrieves the state of a window by title (minimized, maximized, etc.). |  **plan**      |      1      |      |
|     **WinGetStateByHandle**     | 使用窗口句柄获取指定窗口的状态 | Retrieves the state of a window using its handle. |  **plan**      |      1      |      |
|     **WinGetText**     | 获取指定窗口的文本内容 | Retrieves the text from a window by title. |  **plan**      |      1      |      |
|     **WinGetTextByHandle**     | 使用窗口句柄获取指定窗口的文本内容 | Retrieves the text from a window using its handle. |  **plan**      |      1      |      |
|     **WinGetTitle**     | 获取指定窗口的标题 | Retrieves the title of a window by title. |  **plan**      |      1      |      |
|     **WinGetTitleByHandle**     | 使用窗口句柄获取指定窗口的标题 | Retrieves the title of a window using its handle. |  **plan**      |      1      |      |
|     **WinKill**     | 强制关闭指定的窗口 | Forces a window to close by title. |  **plan**      |      1      |      |
|     **WinKillByHandle**     | 使用窗口句柄强制关闭指定的窗口 | Forces a window to close using its handle. |  **plan**      |      1      |      |
|     **WinMenuSelectItem**     | 选择窗口的菜单项 | Selects an item from a menu in a window by title. |  **plan**      |      1      |      |
|     **WinMenuSelectItemByHandle**     | 使用窗口句柄选择窗口的菜单项 | Selects an item from a menu in a window using its handle. |  **plan**      |      1      |      |
|     **WinMinimizeAll**     | 最小化所有窗口 | Minimizes all windows. |  **plan**      |      1      |      |
|     **WinMinimizeAllUndo**     | 恢复最小化的窗口 | Undoes the effect of `AU3_WinMinimizeAll`. |  **plan**      |      1      |      |
|     **WinMove**     | 移动指定窗口到指定位置 | Moves and/or resizes a window by title. |  **plan**      |      1      |      |
|     **WinMoveByHandle**     | 使用窗口句柄移动指定窗口到指定位置 | Moves and/or resizes a window using its handle. |  **plan**      |      1      |      |
|     **WinSetOnTop**     | 设置指定窗口在其他窗口之上 | Sets a window to be always on top by title. |  **plan**      |      1      |      |
|     **WinSetOnTopByHandle**     | 使用窗口句柄设置指定窗口在其他窗口之上 | Sets a window to be always on top using its handle. |  **plan**      |      1      |      |
|     **WinSetState**     | 设置指定窗口的状态（最大化、最小化、正常等） | Sets the state of a window by title (minimize, maximize, etc.). |  **plan**      |      1      |      |
|     **WinSetStateByHandle**     | 使用窗口句柄设置指定窗口的状态 | Sets the state of a window using its handle. |  **plan**      |      1      |      |
|     **WinSetTitle**     | 设置指定窗口的标题 | Sets the title of a window by title. |  **plan**      |      1      |      |
|     **WinSetTitleByHandle**     | 使用窗口句柄设置指定窗口的标题 | Sets the title of a window using its handle. |  **plan**      |      1      |      |
|     **WinSetTrans**     | 设置指定窗口的透明度 | Sets the transparency level of a window by title. |  **plan**      |      1      |      |
|     **WinSetTransByHandle**     | 使用窗口句柄设置指定窗口的透明度 | Sets the transparency level of a window using its handle. |  **plan**      |      1      |      |
|     **WinWait**     | 等待指定的窗口出现 | Waits for a window to exist by title. |  **plan**      |      1      |      |
|     **WinWaitByHandle**     | 使用窗口句柄等待指定的窗口出现 | Waits for a window to exist using its handle. |  **plan**      |      1      |      |
|     **WinWaitActive**     | 等待指定的窗口处于活动状态 | Waits for a window to be active by title. |  **plan**      |      1      |      |
|     **WinWaitActiveByHandle**     | 使用窗口句柄等待指定的窗口处于活动状态 | Waits for a window to be active using its handle. |  **plan**      |      1      |      |
|     **WinWaitClose**     | 等待指定的窗口关闭 | Waits for a window to close by title. |  **plan**      |      1      |      |
|     **WinWaitCloseByHandle**     | 使用窗口句柄等待指定的窗口关闭 | Waits for a window to close using its handle. |  **plan**      |      1      |      |
|     **WinWaitNotActive**     | 等待指定的窗口不处于活动状态 | Waits for a window to be not active by title. |  **plan**      |      1      |      |
|     **WinWaitNotActiveByHandle**     | 使用窗口句柄等待指定的窗口不处于活动状态 | Waits for a window to be not active using its handle. |  **plan**      |      1      |      |
