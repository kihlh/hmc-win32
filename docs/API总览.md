# API总览

### HMC所有的api名称用法概述

## [窗口操作](https://kihlh.gitbook.io/hmc/chuang-kou-cao-zuo)

- **closedHandle**关闭句柄
- **setWindowMode** 设置窗口位置大小
- **getWindowRect** 获取窗口位置大小
- **getDeviceCaps** 获取屏幕大小
- **getPointWindow** 获取鼠标所在窗口的句柄
- **getPointWindowName** 获取鼠标所在窗口的进程名
- **getPointWindowProcessId** 获取鼠标所在窗口的进程id
- **getPointWindowMain** 获取鼠标所在窗口的父窗口
- **getHandleProcessID** 获取句柄对应的进程id
- **getProcessHandle** 获取进程对应的主进程/线程的窗口句柄
- **lookHandleGetTitle** 获取此句柄的标题
- **lookHandleSetTitle** 设置此句柄的标题
- **lookHandleShowWindow** 通过句柄设置窗口显示状态
- **isHandleWindowVisible** 判断此句柄是否是正在活动中的窗口
- **lookHandleCloseWindow** 关闭此句柄对应的窗口
- **getForegroundWindow** 获取活动窗口句柄
- **getAllWindows** 获取所有窗口的信息
- **getMainWindow** 获取该句柄下的父窗口
- **setWindowTop** 顶设窗口
- **hasWindowTop** 窗口是否被顶设
- **windowJitter** 窗口抖动
- **updateWindow** 刷新窗口
- **setWindowFocus** 设置窗口聚焦
- **setWindowEnabled** 设置窗口是否支持响应事件(鼠标键盘点击)
- **isEnabled** 判断窗口是否支持响应事件(鼠标键盘点击)
- **SetWindowInTaskbarVisible** 是否在状态栏显示该图标
- **setHandleTransparent** 设置窗口不透明度
- **SetBlockInput** 阻止键盘和鼠标输入事件到达应用程序。
- **HWND (类) Number(伪)**

- - **HWND** number
  - **closed** 强制结束句柄
  - **close** 向窗口发送关闭的消息
  - **rect** 窗口位置 (访问时自动获取)
  - **title** 标题 (访问时自动获取)
  - **setTitle** 设置标题
  - **exists** 句柄是否有效 (访问时自动获取)
  - **isHandle** 句柄是否有效 (访问时自动获取)
  - **pid** 句柄的附属进程id (访问时自动获取)
  - **MianPid** 句柄的 主线程/主进程 id (访问时自动获取)
  - **MainHandle** 主句柄
  - **isVisible** 可见性
  - **kill** 结束 主进程/主线程
  - **hide** 隐藏
  - **show** 显示
  - **setMin** 最小化
  - **setMax** 最大化
  - **setRestore** 恢复最近的状态
  - **setFocus** 聚集
  - **setEnabled** 禁用
  - **isEnabled** 是否禁用
  - **setJitter** 窗口抖动
  - **isTop** 是否顶设
  - **setTopOrCancel** 取消顶设 / 设置顶设
  - **setOpacity** 设置 不透明度 0-100 / 0.0-1.0
  - **setTransparent** 设置 不透明度

- **getAllWindowsHandle** 获取所有句柄 并返回一个HWND 的伪数字方法集 （getAllWindows 的替代 获取 200000次进程无影响）
- **WatchWindowForeground** 当聚集的窗口变更的时候发生回调
- **WatchWindowPoint** 当鼠标所在的窗口变更的时候发生回调
- **enumChildWindows** 枚举句柄的子窗口并返回句柄列表
- **getConsoleHandle** 获取node控制台的句柄
- **hideConsole** 隐藏node控制台
- **showConsole** 显示node控制台

## [进程控制](https://kihlh.gitbook.io/hmc/jin-cheng-kong-zhi)

- **killProcess** 结束该pid进程
- **sleep** 同步阻塞(进程)
- **openApp** 打开程序
- **getProcessList** 获取进程列表
- **getDetailsProcessList** 获取详细进程列表（慢20ms）
- **getProcessHandle** 获取进程对应的主进程/线程的窗口句柄
- **getProcessName** 获取进程名
- **getProcessidFilePath** 获取进程可执行文件位置
- **getForegroundWindowProcessID** 获取活动窗口的进程id
- **getHandleProcessID** 获取句柄对应的进程id
- **isProcess** 判断进程id 是否存在
- **hasProcess** 判断进程id 是否存在
- **getDetailsProcessNameList** 获取该名称 /正则匹配的进程列表 带执行文件路径 慢20ms
- **getProcessNameList** 获取该名称 /正则匹配的进程列表
- **processWatchdog** 当监察的进程结束时候执行回调
- **killProcessName** 结束该名称 /(正则)匹配的 进程

## [状态栏](https://kihlh.gitbook.io/hmc/zhuang-tai-lan)

- **getTrayList** 获取托盘图标
- **closedHandle** 关闭托盘图标(提交句柄)

## [系统相关](https://kihlh.gitbook.io/hmc/xi-tong-xiang-guan)

- **SetSystemHOOK** (禁用/启用系统键盘鼠标钩子 (高级api) )
- **getHidUsbList** 获取所有HidUsb设备（仅限HID设备）
- **getShortcutLink** 获取快捷方式内容
- **setShortcutLink** 设置快捷方式内容
- **isSystemX64** 判断当前系统是否是x64
- **messageBox** 消息窗口(调用 win-api)
- **getSystemMenu** 设置系统右键菜单 
- **clearClipboard** 清空剪贴版
- **setClipboardText** 设置剪贴板文本
- **getClipboardText** 获取剪贴板文本
- **openApp** 打开程序
- **isAdmin** 判断当前软件是否拥有管理员权限
- **getSystemIdleTime** 系统空闲时间
- **systemStartTime** 系统启动到现在的时间
- **system** 同 C++/C 的system
- **MessageError** 方法用于显示带有一条指定消息和一个 确认 按钮的错误框 附带有❗ 感叹号。
- **MessageStop** 方法用于显示带有一条指定消息和一个 确认 按钮的和❌（X）的消息框
- **confirm** 方法用于显示带有一条指定消息和 确认 和取消 的按钮的消息框
- **alert** 方法用于显示带有一条指定消息和一个 确认 按钮的警告框
- **openPath** 在系统默认的关联软件中打开此文件
- **openURL** 在默认浏览器中打开该链接
- **openExternal** 在资源管理器中打开该文件并
- **getUsbDevsInfo** 获取所有usb驱动器(不包含HUD)
- **setClipboardFilePaths** 向剪贴板写入文件列表
- **getClipboardFilePaths** 向剪贴板读取文件列表
- **freePort** 获取一个空闲可用的端口号
- **systemChcp** 当前系统shell的chcp信息
- **showConsole** 显示node控制台
- **hideConsole** 隐藏node控制台
- **getConsoleHandle** 获取node控制台的句柄
- **trash** 将文件放进回收站
- **deleteFile** 将文件放进回收站

## [电源控制](https://kihlh.gitbook.io/hmc/dian-yuan-kong-zhi)

- **systemStartTime** 系统启动到现在的时间
- **shutMonitors** 关闭显示器
- **showMonitors** 恢复显示器
- **powerControl** 电源控制

- - **1001** 关机
  - **1002** 重启
  - **1003** 注销
  - **1005** 锁定
  - **lock** 锁定
  - **cancellation** 注销
  - **restart** 重启
  - **shutDown** 关机

## [注册表编辑](https://kihlh.gitbook.io/hmc/zhu-ce-biao-bian-ji)

- **hasRegistrKey** 判断键值是否存在
- **getStringRegKey** 获取内容(文本)
- **removeStringRegKey** 删除数据
- **setRegistrKey** 设置键值对
- **createPathRegistr** 创建新的路径
- **enumRegistrKey** 枚举键值
- **getRegistrBuffValue** 获取内容(二进制 Buffer)
- **registr** 注册表处理的集合

- - **analysisDirectPath** 将一条完整的注册表路径 转为 数组 拆分为 [ *HKEY*: HKEY, *Path*: string, *key*?: string]
  - **has**
  - **get**
  - **remove**
  - **keys**
  - **list**
  - **create**
  - **open**

- **listRegistrPath** 将该路径下的内容以objcet 的方式显示
- **openRegKey** 打开该路径并返回方法的封装
- **setRegistrDword** 设置一个32位数字
- **setRegistrQword** 设置一个64位数字
- **getRegistrDword** 获取一个32位数字
- **getRegistrQword** 获取一个64位数字
- **isRegistrTreeKey** 判断该键值是否存在子项
- **removeStringTree** 删除一个文件夹键值

## [键盘鼠标](https://kihlh.gitbook.io/hmc/jian-pan-shu-biao)

- **getHidUsbList** 获取所有HidUsb设备（仅限HID设备）
- **setCursorPos** 设置鼠标位置
- **mouse** 自定义鼠标事件
- **hasKeyActivate** 判断该按键是否被按下
- **leftClick** 左键点击
- **rightClick** 右键点击
- **getBasicKeys** 获取四大按钮是否按下
- **getMouseMovePoints** 获取鼠标之前64个位置

## 文件链接/快捷方式

- **createSymlink** 创建一个软链接
- **createDirSymlink** 创建一个文件夹软链接
- **createHardLink** 创建一个硬链接

## HMC的内部工具

- **ref** 转换

- - **bool** 将布尔内容转为安全的 bool 类型布尔
  - **string** 将文本/伪文本内容转为安全的文本
  - **int** 将数字/伪数字内容转为安全的int数字
  - **HKEY** 所有注册表的 HKEY 对象

- **Sleep** 异步的阻塞
- **default** 映射整个功能组(兼容ejs)
- **hmc** 映射整个功能组(兼容局部导出)
- **native** 直接连接HMC.node的原生方法 (不建议使用)