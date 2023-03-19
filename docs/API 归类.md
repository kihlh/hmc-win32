# API 归类

**所有归类的首个字母都为大写 类型为Object 部分API名称被简化**

**截至当前 HMC已经拥有145个API 因此在编程的时候我们需要快速对一些常用的api进行调用，为此我们将他分为了几大类：**

1. [**Process 进程控制**](#CsW0D)
2. [**Shell  实用工具集**](#vkdrS)
3. [**Auto 自动化工具集**](#LcjW2)
4. [**Usb  USB 控制的归档**](#Xwyl9) 
5. [**Clipboard  剪贴板工具集**](#pxpEe)
6. [**Window 所有窗口操作方法的归类合集**](#sFF85)
7. [**Watch 所有变化监听方法合集**](#GghZq)
8. **Registr 所有注册表编辑的方法合集**

------



### hmc.**Process 进程控制**

| **归类名称**       | **用途**                              | 绑定函数                         |
| ------------------ | ------------------------------------- | -------------------------------- |
| **watch**          | 进程监听 当该进程被关闭的时候执行回调 | **processWatchdog**              |
| **kill**           | 结束该进程                            | **killProcess**                  |
| **killMatch**      | 结束该名称的进程                      | **killProcessName**              |
| **getList**        | 获取进程列表                          | **getProcessList**               |
| **getHandle**      | 获取进程的句柄                        | **getProcessHandle**             |
| **getName**        | 获取进程名                            | **getProcessName**               |
| **getPath**        | 获取进程可执行文件位置                | **getProcessidFilePath**         |
| **getFocus**       | 获取活动窗口的进程id                  | **getForegroundWindowProcessID** |
| **has**            | 获取该名称 /正则匹配的进程列表        | **hasProcess**                   |
| **match**          | 获取该名称 /正则匹配的进程列表        | **getProcessNameList**           |
| **matchDetails**   | 获取当前的焦点窗口                    | **getDetailsProcessNameList**    |
| **getDetailsList** | 获取详细进程列表（慢20ms）            | **getDetailsProcessList**        |



### hmc.Shell  实用工具集  (拥有统一化名称)

| **归类名称**         | **用途**                              | 绑定函数             |
| -------------------- | ------------------------------------- | -------------------- |
| **trash**            | 进程监听 当该进程被关闭的时候执行回调 | **trash**            |
| **openApp**          | 结束该进程                            | **openApp**          |
| **getShortcutLink**  | 结束该名称的进程                      | **getShortcutLink**  |
| **setShortcutLink**  | 获取进程列表                          | **setShortcutLink**  |
| **freePort**         | 获取进程的句柄                        | **freePort**         |
| **createSymlink**    | 获取进程名                            | **createSymlink**    |
| **createDirSymlink** | 获取进程可执行文件位置                | **createDirSymlink** |
| **createHardLink**   | 获取活动窗口的进程id                  | **createHardLink**   |

### hmc.Window 所有窗口操作方法的归类合集 (拥有统一化名称) 

| **归类名称**          | **用途**                                                     | **绑定函数**                     |
| --------------------- | ------------------------------------------------------------ | -------------------------------- |
| **getStyle**          | 获取窗口类关联代码                                           | **getWindowStyle**               |
| **getClassName**      | 检索指定窗口所属的类的名称                                   | **getWindowClassName**           |
| **isInMonitor**       | 判断句柄的窗口是否在所有窗口的范围中(无论他是否被其他窗口挡住) | **isInMonitorWindow**            |
| **isMouseMonitor**    | 判断句柄的窗口是否在鼠标所在的窗口                           | **isMouseMonitorWindow**         |
| **HWND**              | 一个可操作的句柄                                             | **HWND**                         |
| **setMode**           | 设置窗口位置大小                                             | **setWindowMode**                |
| **getAllWindows**     | 获取所有窗口的信息                                           | **getAllWindows**                |
| **getAllHandle**      | 获取所有窗口句柄并返回一个快速操作的句柄类 可以快速操作窗口  | **getAllWindowsHandle**          |
| **watchPoint**        | 监听鼠标所在的窗口的句柄的变化                               | **WatchWindowPoint**             |
| **watchtFocus**       | 监听聚焦窗口的变化并返回句柄                                 | **WatchWindowForeground**        |
| **getFocus**          | 获取当前的焦点窗口                                           | **getForegroundWindow**          |
| **getMain**           | 获取句柄的主窗口                                             | **getMainWindow**                |
| **getPoint**          | 获取鼠标所在窗口的句柄                                       | **getPointWindow**               |
| **getProcessHandle**  | 获取进程对应的主进程/线程的窗口句柄                          | **getProcessHandle**             |
| **getPointMain**      | 获取鼠标所在窗口的父窗口                                     | **getPointWindowMain**           |
| **setTaskbarVisible** | 是否在状态栏显示该图标                                       | **SetWindowInTaskbarVisible**    |
| **getProcessID**      | 获取句柄对应的进程id                                         | **getHandleProcessID**           |
| **getRect**           | 获取窗口位置大小                                             | **getWindowRect**                |
| **isEnabled**         | 判断窗口是否支持响应事件(鼠标键盘点击)                       | **isEnabled**                    |
| **isHandle**          | 句柄是否有效                                                 | **isHandle**                     |
| **hasHandle**         | 句柄是否有效                                                 | **isHandle**                     |
| **isVisible**         | 该窗口可见                                                   | **isHandleWindowVisible**        |
| **close**             | 发生关闭消息(让该窗口的关闭功能自行处理关闭)                 | **lookHandleCloseWindow**        |
| **getTitle**          | 获取窗口标题                                                 | **lookHandleGetTitle**           |
| **setTitle**          | 设置标题                                                     | **lookHandleSetTitle**           |
| **setShowWindow**     | 通过句柄设置窗口显示状态                                     | **lookHandleShowWindow**         |
| **setTransparent**    | 设置窗口不透明度                                             | **setHandleTransparent**         |
| **setEnabled**        | 设置窗口是否支持响应事件(鼠标键盘点击)                       | **setWindowEnabled**             |
| **setFocus**          | 设置窗口聚焦                                                 | **setWindowFocus**               |
| **setTop**            | 顶设窗口                                                     | **setWindowTop**                 |
| **update**            | 刷新窗口                                                     | **updateWindow**                 |
| **jitter**            | 窗口抖动                                                     | **windowJitter**                 |
| **hasTop**            | 窗口是否被顶设                                               | **hasWindowTop**                 |
| **closed**            | 强制销毁句柄                                                 | **closedHandle**                 |
| **getFocusProcessID** | 获取活动窗口的进程id                                         | **getForegroundWindowProcessID** |
| **getPointName**      | 获取鼠标所在窗口的进程名                                     | **getPointWindowName**           |
| **getPointProcessId** | 获取鼠标所在窗口的进程id                                     | **getPointWindowProcessId**      |
| **enumChild**         | 枚举句柄的子窗口并返回句柄列表                               | **enumChildWindows**             |

### hmc.Clipboard  剪贴板工具集  (拥有统一化名称)

| **归类名称**       | **用途**                                   | 绑定函数                       |
| ------------------ | ------------------------------------------ | ------------------------------ |
| **clear**          | 清空剪贴板                                 | **clearClipboard**             |
| **readText**       | 读取剪贴板中的文本                         | **getClipboardText**           |
| **readFilePaths**  | 读取剪贴板中的文件列表                     | **getClipboardFilePaths**      |
| **writeText**      | 写入文本到剪贴板                           | **setClipboardText**           |
| **writeFilePaths** | 写入文件列表到剪贴板                       | **setClipboardFilePaths**      |
| **sequence**       | 获取当前监听板内容的id(复制内容变化时变更) | **getClipboardSequenceNumber** |
| **watch**          | 当剪贴板内容变化时候发生回调               | **watchClipboard**             |

### hmc.Usb  USB 控制的归档  (拥有统一化名称)

| **归类名称**    | **用途**                         | 绑定函数           |
| --------------- | -------------------------------- | ------------------ |
| **getHub**      | 获取所有HidUsb设备（仅限HID设备) | **getHidUsbList**  |
| **getDevsInfo** | 获取所有usb驱动器(不包含HUD)     | **getUsbDevsInfo** |
| **watch**       | 当驱动器添加或者移除后发生回调   | **watchUSB**       |

### hmc.Auto 自动化工具集  (拥有统一化名称) 

| **归类名称**           | **用途**                                          | **绑定函数**           |
| ---------------------- | ------------------------------------------------- | ---------------------- |
| **setWindowEnabled**   | 设置窗口是否支持响应事件(鼠标键盘点击)            | **setWindowEnabled**   |
| **setCursorPos**       | 设置鼠标位置                                      | **setCursorPos**       |
| **mouse**              | 自定义鼠标事件                                    | **mouse**              |
| **rightClick**         | 右键点击                                          | **rightClick**         |
| **leftClick**          | 左键点击                                          | **leftClick**          |
| **getBasicKeys**       | 获取四大功能按钮是否按下                          | **getBasicKeys**       |
| **getMouseMovePoints** | 获取鼠标之前64个位置                              | **getMouseMovePoints** |
| **powerControl**       | 电源控制                                          | **powerControl**       |
| **SetBlockInput**      | 禁用鼠标                                          | **SetBlockInput**      |
| **SetSystemHOOK**      | 设置禁用/取消 电脑键盘鼠标挂钩 (儿童防止乱动的锁) | **SetSystemHOOK**      |
| **hasKeyActivate**     | 判断该按键是否被按下                              | **hasKeyActivate**     |

### hmc.Watch  所有监听函数的合集 (拥有统一化名称)  

| **归类名称**    | **用途**                                    | 绑定函数                  |
| --------------- | ------------------------------------------- | ------------------------- |
| **clipboard**   | 当剪贴板内容变化时候发生回调                | **getWindowStyle**        |
| **usb**         | 当驱动器或者HID设备插入或者移除时候发生回调 | **watchUSB**              |
| **windowFocus** | 当正在使用的窗口内容变化时候发生回调        | **WatchWindowForeground** |
| **windowPoint** | 当鼠标所在的窗口变化时候发生回调            | **WatchWindowPoint**      |
| **process**     | 当被监听的进程退出的时候发生回调            | **processWatchdog**       |

### hmc.Registr 所有注册表编辑的方法合集

| **归类名称**               | **用途**                             | **绑定函数**               |
| -------------------------- | ------------------------------------ | -------------------------- |
| **analysisDirectPath**     | 直达路径解析                         | **analysisDirectPath**     |
| **has**                    | 判断注册表中是否有该键值             | **hasRegistrKey**          |
| **get**                    | 获取内容(文本)                       | **getStringRegKey**        |
| **set**                    | 设置键值对                           | **setRegistrKey**          |
| **remove**                 | 删除数据                             | **removeStringRegKey**     |
| **keys**                   | 枚举键值                             | **enumRegistrKey**         |
| **list**                   | 将当前的路径的注册表值转表           | **listRegistrPath**        |
| **create**                 | 创建新的路径                         | **createPathRegistr**      |
| **open**                   | 打开一个注册表路径并返回一些实用方法 | **openRegKey**             |
| **hasRegistrKey**          | 判断注册表中是否有该键值             | **hasRegistrKey**          |
| **listRegistrPath**        | 将当前的路径的注册表值转表           | **listRegistrPath**        |
| **enumRegistrKey**         | 枚举键值                             | **enumRegistrKey**         |
| **removeStringRegKey**     | 删除数据                             | **removeStringRegKey**     |
| **setRegistrKey**          | 设置键值对                           | **setRegistrKey**          |
| **getStringRegKey**        | 获取内容(文本)                       | **getStringRegKey**        |
| **getNumberRegKey**        | 获取内容(数字)                       | **getNumberRegKey**        |
| **createPathRegistr**      | 创建新的路径                         | **createPathRegistr**      |
| **getRegistrBuffValue**    | 获取内容(二进制 Buffer)              | **getRegistrBuffValue**    |
| **openRegKey**             | 打开一个注册表路径并返回一些实用方法 | **openRegKey**             |
| **getRegistrQword**        | 获取一个64位数字                     | **getRegistrQword**        |
| **getRegistrDword**        | 获取一个32位数字                     | **getRegistrDword**        |
| **setRegistrQword**        | 设置一个64位数字                     | **setRegistrQword**        |
| **setRegistrDword**        | 设置一个32位数字                     | **setRegistrDword**        |
| **removeStringRegValue**   | 删除一个值                           | **removeStringRegValue**   |
| **removeStringRegKeyWalk** | 删除一个文件夹键值                   | **removeStringRegKeyWalk** |
| **removeStringTree**       | 删除一个文件夹键值                   | **removeStringTree**       |
| **isRegistrTreeKey**       | 判断该键值是否存在子项               | **isRegistrTreeKey**       |