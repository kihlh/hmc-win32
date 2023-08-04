

# 进度api列表



**此文档是hmc重构版本的 CPP代码接口的实例，本api列表的内容并不完全会在hmc和dll中导出，因为有些解构是需要经过二次转义的，hmc对于新版的重构理念是本着可以被cpp代码调用 可以兼容其他接口，所以api实现均为cpp的接口**

This document is an example of the CPP code interface for the refactored version of HMC. The content of this API list may not be fully exported in HMC and DLL because some structures need to undergo secondary escaping. For the new version, HMC follows the principle of being callable by CPP code and compatible with other interfaces, so all API implementations are in CPP interface.

------------------------------------------------------------------------------------------

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

| API 名称                  | 用途               | 完成度 | 类型重定向 | 测试     |
| ------------------------- | ------------------ | ------ | ---------- | -------- |
| showProgress              | 在窗口图标显示进度 | 计划   | **plan**   | **plan** |
| isWindowVisible           |                    |        |            |          |
| getClassName              |                    | true   | 2          | 未压测   |
| getStyle                  |                    | true   | 1          | 未压测   |
| getWindowID               |                    |        |            |          |
| getSubWindow              |                    |        |            |          |
| getParentWindow           |                    |        |            |          |
| getWindowText             |                    |        | 2          |          |
| isChildWindow             |                    |        |            |          |
| getTopWindow              |                    |        |            |          |
| setWindowText             |                    |        | 2          |          |
| updateWindow              |                    |        |            |          |
| getPointWindow            |                    |        | 2          |          |
| setWindowEnabled          |                    |        |            |          |
| setWindowFocus            |                    |        |            |          |
| setWindowTop              |                    |        |            |          |
| isWindowTop               |                    |        |            |          |
| setWindowShake            |                    |        | 2          |          |
| isWindowEnabled           |                    |        |            |          |
| setWindowInTaskbarVisible |                    |        |            |          |
| setWindowTransparent      |                    |        | 2          |          |
| getAllWindowsHwnd         |                    |        |            |          |
| closedHandle              |                    |        |            |          |
| closeWindow               |                    |        |            |          |
| setWindowFileIcon         |                    |        |            |          |
| setWindowIcon             |                    |        |            |          |
| getProcessIDWindow        |                    |        |            |          |
| setWindowIcon             |                    |        |            |          |
|                           |                    |        |            |          |
| 计划中.....               |                    |        |            |          |
| HMC_IMPORT_WINDOW_H       | 避免重复导入       | true   | null       | null     |


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

#### （网络）sock.hpp  代码被同步软件删除  近期修复

[查看代码( code)](https://github.com/kihlh/hmc-win32/blob/master/source/CPP_Reconfig/util/sock.hpp)

| API 名称            | 用途                             | 完成度 | 类型重定向 | 测试 |
| ------------------- | -------------------------------- | ------ | ---------- | ---- |
| getNetParams        | 适配器信息                       | true   | 0          | true |
| enumConnectNet      | 枚举本机所有的已经打开的端口信息 | true   | 3          | true |
| dwLocalAddrToIP     | ip数字转ip                       | true   | 0          | true |
| GetUDPPortProcessID | 获取指定TCP端口的进程id          | true   | 0          | true |
| GetTCPPortProcessID | 获取指定TCP端口的进程id          | true   | 0          | true |
| TCP4                | 支持                             | true   | 0          | true |
| TCP6                | 支持                             | true   | 0          | true |
| UDP4                | 支持                             | true   | 0          | true |
| UDP6                | 支持                             | true   | 0          | true |
|                     |                                  |        |            |      |

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

| API 名称                   | 用途     | 完成度 | 类型重定向 | 测试 |
| -------------------------- | -------- | ------ | ---------- | ---- |
| **hmc_EnableShutDownPriv** | 临时提权 | true   | false      | true |
|                            |          |        |            |      |