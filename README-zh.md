# **HMC-win32: 更加轻松的连接系统API**

![系统环境](https://cos.kiic.top/assets/used/202204112301972.svg)      ![系统环境](https://cos.kiic.top/assets/used/202204112301969.svg)      ![系统环境](https://img.shields.io/badge/Node6.14.2+-Node-97c40f.svg?longCache=true)       ![系统环境](https://img.shields.io/badge/Node8.0+-electron-97c40f.svg?longCache=true)    

![img](source\src\zh_cn.png)

## 帮助

#### **You are currently viewing the Chinese version of the introduction. You can click [here](about:blank) to view the English version of this README.**

我们提供了多份编程语言帮助文档 可供了解api的调用，但是他可能更新时间不及时，因为api非常多，需要编写文档是个不小的工程，hmc使用的是 TypeScript 编写的 并且他预带了一份类型声明 可以让您在主流的 ide编辑器 中显示类型 以及用法

#### 相关的链接 ：

##### Help：   [【编程帮助】](https://kihlh.gitbook.io/hmc/)          NPM：    [【hmc-win32】](https://www.npmjs.com/package/hmc-win32)    [【hmc-autoit】](https://www.npmjs.com/package/hmc-autoit)      Source： [【c++源代码】](https://github.com/kihlh/hmc-win32/tree/master/source)    [【AutoitX】](https://github.com/kihlh/hmc-win32/tree/master/source/hmc-autoIt)      [【重构版】](https://github.com/kihlh/hmc-win32/tree/master/source/h2c-win32)   



### 子集 (Subset)

#### autoit：hmc-autoit     [【npm】](https://www.npmjs.com/package/hmc-autoit)       [【源代码】](https://github.com/kihlh/hmc-win32/tree/master/source/hmc-autoIt) 

**hmc-autoit 是hmc的子集 他包含了一些列调用 autoitX api的函数，并且和hmc的优点一样，不需要再次编译和ffi魔法**

------------------



##   我为什么要使用这个模块？


- **零依赖   hmc不依赖于第三方模块  也不需要您需要懂得C++ 编程知识**
- **对执行速度有要求  在此之前我在使用node执行一些复杂功能 只能通过命令行去调用程序执行 他的取值和调用 非常困难 而且最少多出100ms 的消耗**
- **hmc调用的基本都是系统API，他在大多数情况下非常迅速，hmc对自己的api进行了大量的转换，让参数输入和返回更加轻松 ，不需要您对系统有很清晰的了解，hmc非常轻便 你甚至可以在只有两个文件的时候正常运行，并且不依赖于多出的dll等文件**
- **hmc在大多数情况下对内存的消耗几乎可以忽略不计**


## 为您总结了几种功能的分类

- ##### [窗口操作](#Window Operation) ：调整  /  枚举  /  禁用   /  查询  /  变化

- **[进程控制](#Process Control) ：kill  /  信息  /  句柄  /  窗口 / 变化**

- **[网    络](#Network (net))    ：端口  /  网卡  /  局域网  /  IP**

- **[文件系统](#File Links/Shortcuts) ：软链接  /  硬链接  /  USB**

- ##### [环境变量](#Environment Variables) ：用户变量  /  系统变量  /  同步  /  转义

- **[剪 贴 板](#System Operations)   ：文件列表  /  读写  /  文本  /  变化** 

- **[自 动 化](#Keyboard Mouse USB):   ：键盘  /  鼠标  /   执行  /  读取  /  autoit3**

- **[注 册 表](#Registry Editing)   ：读 / 写** 

- ##### [电源控制](#Power Control) : 关机  /  重启   /  注销  /   显示器  /  启动时间 

- **[Shell](#System Operations)       ：回收站  / Message  / 快捷方式 / 执行软件 / 选取文件 / 保存文件**

- **[互斥体](#System Operations)    ： 创建 / 销毁  （防止进程重复启动）**

- **[托 盘](#Status Bar)**       ：创建 / 枚举 / 销毁



## installation

```
npm i hmc-win32
```

### How to call

```javascript
let HMC = require("hmc-win32");
console.log("App:Admin=>",HMC.isAdmin())
//App:Admin=> true

console.log("SystemIdleTime=>",HMC.getSystemIdleTime())
//SystemIdleTime=> 25

console.log("escapeEnvVariable=>",HMC.escapeEnvVariable("%AppData%\hmc-win32"))
//escapeEnvVariable=> C:\Users\...\AppData\Roaming\hmc-win32

console.log("Clipboard=>",setClipboardFilePaths(["D:/1.jpg"]),HMC.getClipboardFilePaths())
//Clipboard=> true , ["D:/1.jpg"]

```

###  In TypeScript using the

```typescript
import  HMC = require("hmc-win32");
```

# 功能概览

### 窗口操作

----------------------------------

- **closedHandle** 关闭句柄
- **setWindowMode** 设置窗口位置大小
- **getWindowRect** 获取窗口位置大小
- **getDeviceCaps** 获取屏幕大小
- **getPointWindow** 获取鼠标所在窗口的句柄
- **getPointWindowName** 获取鼠标所在窗口的进程名
- **getPointWindowProcessId** 获取鼠标所在窗口的进程id
- **getPointWindowMain**  获取鼠标所在窗口的父窗口
- **getPointWindowMain** 获取鼠标所在窗口的父窗口
- **getWindowProcess** 获取句柄对应的进程id
- **getProcessWindow** 获取进程对应的主进程/线程的窗口句柄
- **getWindowTitle** 获取此句柄的标题
- **setWindowTitle** 设置此句柄的标题
- **setShowWindow** 通过句柄设置窗口显示状态
- **isWindowVisible** 判断此句柄是否是正在活动中的窗口
- **closeWindow** 关闭此句柄对应的窗口
- **getForegroundWindow** 获取活动窗口句柄
- **getAllWindows** 获取所有窗口的信息  
- **getMainWindow** 获取该句柄下的父窗口
- **setWindowTop** 顶设窗口
- **isWindowTop** 窗口是否被顶设
- **setWindowShake** 窗口抖动
- **updateWindow** 刷新窗口
- **setWindowFocus** 设置窗口聚焦
- **setWindowEnabled** 设置窗口是否支持响应事件(鼠标键盘点击)
- **isEnabled** 判断窗口是否支持响应事件(鼠标键盘点击)
- **SetWindowInTaskbarVisible** 是否在状态栏显示该图标
- **setHandleTransparent** 设置窗口不透明度
- **SetBlockInput** 阻止键盘和鼠标输入事件到达应用程序。
- **WatchWindowPoint**   当鼠标所在的窗口变更的时候发生回调
- **WatchWindowForeground**  当聚集的窗口变更的时候发生回调
- **getAllWindowsHandle**  获取所有句柄 并返回一个HWND 的伪数字方法集  （getAllWindows  的替代  获取 200000次进程无影响）
- **HWND**  (类)         Number(伪)
  - **HWND** number
  - **closed** 强制结束句柄
  - **close** 向窗口发送关闭的消息
  - **rect** 窗口位置  (访问时自动获取)
  - **title** 标题 (访问时自动获取)
  - **setTitle** 设置标题
  - **exists** 句柄是否有效  (访问时自动获取)
  - **isHandle** 句柄是否有效  (访问时自动获取)
  - **pid** 句柄的附属进程id   (访问时自动获取)
  - **MianPid** 句柄的 主线程/主进程   id  (访问时自动获取)
  - **MainHandle** 主句柄
  - **isVisible** 可见性
  - **kill**  结束  主进程/主线程
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
- **setTopOrCancel**  取消顶设 / 设置顶设
- **setOpacity**  设置 不透明度 0-100  / 0.0-1.0
- **setTransparent** 设置 不透明度  0-255 (alpha)
- **enumChildWindows** 枚举句柄的子窗口
- **setWindowTitleIcon**  设置标题窗口图标icon
- **getWindowClassName** 获取窗口类名
- **getAllWindowsHandle**  获取所有窗口的句柄 **增加一个参数** 是否要求必须为窗口
- **setForegroundWindow**  设置窗口聚焦
- **getAllWindows** 默认使用 *isWindows* 为true
- **getWindowStyle**  获取窗口类关联代码
- **setWindowIconForExtract**  通过可执行文件或者带有图标的文件设置窗口图标

### 进程控制

----------------------------------

- **killProcess** 结束该pid进程

- **sleep** 同步阻塞(进程)

- **openApp** 打开程序

- **getProcessList** 获取进程列表

- **getDetailsProcessList** 获取详细进程列表（慢20ms）

- **getProcessWindow** 获取进程对应的主进程/线程的窗口句柄

- **getProcessName** 获取进程名

- **getProcessFilePath** 获取进程可执行文件位置

- **getForegroundWindowProcessID** 获取活动窗口的进程id

- **getWindowProcess** 获取句柄对应的进程id

- **isProcess** 判断进程id 是否存在

- **hasProcess** 判断进程id 是否存在

- **killProcessName** 结束该名称 /(正则)匹配的   进程

- **processWatchdog** 当监察的进程结束时候执行回调

- **getProcessNameList**  获取该名称 /正则匹配的进程列表

- **getDetailsProcessNameList**  获取该名称 /正则匹配的进程列表 带执行文件路径 慢20ms

- **getModulePathList** 查询进程加载的模块

- **getProcessThreadList** 枚举进程的线程id

- **getProcessParentProcessID** 获取进程的主进程

- **getSubProcessID** 获取子进程id列表

- **enumProcessHandle**  枚举进程id的句柄

- **enumAllProcessHandle** 枚举所有进程id的句柄

- **findProcess** 搜索进程

- **getProcessStartTime** 获取进程启动时间 (ms)

- **尾部带有2的为2.0api** 均支持异步（2   / 2Sync ）:**

  - 异步 `Promise`
  - 异步  `callback`
  - 异步  `Promise`
  - 均支持并发

- **findProcess2** 搜索进程 `异步` 

- **findProcess2Sync** 搜索进程 `同步` 

- **getAllProcessList2** `异步` 获取进程列表（枚举） 枚举是最快的也不受应用是32位系统64位导致无法枚举到 但是信息不够细

  - pid 进程id
  - name 由镜像路径解析
  - path 镜像路径

- **getAllProcessList2Sync** `同步` 获取进程列表（枚举）

- **getAllProcessList2Snp** `异步` 获取进程列表 (快照)     请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息

  - pid 进程id
  - name 由镜像路径解析
  - ppid 父进程id
  - ... :  cntThreads cntUsage dwFlags dwSize pcPriClassBase th32DefaultHeapID th32ModuleID

  **getAllProcessListSnp2Sync** `同步` 获取进程列表 (快照)

- **getAllProcessListNt2** `异步` 获取进程列表 (内核)

  - pid 进程id
  - name 软件名称
  - BasePriority NextEntryOffset NumberOfThreads PagefileUsage pcPriClassBase PeakPagefileUsage PeakWorkingSetSize QuotaNonPagedPoolUsage Reserved [1-6]

- **getAllProcessListNt2Sync** `同步` 获取进程列表 (内核)

- **getProcessCpuUsage2** `异步` 获取进程占用的cpu

- **getProcessCpuUsage2Sync** `同步` 获取进程占用的cpu

-  **getProcessNameSnp2Sync** `同步` 获取进程的名称(快照)

-  **getProcessNameSnp2** `异步` 获取进程的命令行(快照)

-  **getProcessNameNt2Sync** `同步` 获取进程的名称(内核)

-  **getProcessNameNt2** `异步` 获取进程的命令行(内核)

-  **getProcessName2Sync** `同步` 获取进程的名称(正常)

- **getProcessName2** `异步` 获取进程的命令行(正常)

- **getProcessCommand2**  `异步` 获取指定进程的启动命令行

- **getProcessCommand2Sync** `同步`  获取指定进程的工作目录

- **getProcessCwd2**  `异步` 获取指定进程的工作目录

- **getProcessCwd2Sync** `同步`  获取指定进程的启动命令行

### 状态栏

----------------------------------

- **getTrayList** 获取托盘图标
- **closedHandle** 关闭托盘图标(提交句柄)

### 系统操作

----------------------------------

- **SetSystemHOOK** (禁用/启用系统键盘鼠标钩子  (高级api) )
- **getHidUsbList** 获取所有HidUsb设备（仅限HID设备）
- **getShortcutLink**  获取快捷方式内容
- **setShortcutLink** 设置快捷方式内容
- **isSystemX64** 判断当前系统是否是x64
- **messageBox** 消息窗口(调用 win-api)
- **getSystemMenu** 设置系统右键菜单  例如win自带的系统菜单就很丑还不能禁用  使用这个禁用
- **clearClipboard** 清空剪贴版
- **setClipboardText** 设置剪贴板文本
- **getClipboardText** 获取剪贴板文本
- **setClipboardFilePaths** 向剪贴板写入文件列表
- **getClipboardFilePaths** 向剪贴板读取文件列表
- **openApp** 打开程序
- **isAdmin** 判断当前软件是否拥有管理员权限
- **getSystemIdleTime** 系统空闲时间
- **systemStartTime** 系统启动到现在的时间
- **system** 同 C++/C 的system
- **alert**  方法用于显示带有一条指定消息和一个 确认 按钮的警告框
- **confirm** 方法用于显示带有一条指定消息和 确认 和取消 的按钮的消息框
- **MessageStop** 方法用于显示带有一条指定消息和一个 确认 按钮的和❌（X）的消息框
- **MessageError** 方法用于显示带有一条指定消息和一个 确认 按钮的错误框 附带有❗ 感叹号。
- **systemChcp** 当前系统shell的chcp信息
- **deleteFile** 将文件放入回收站
- **trash**  将文件放入回收站
- **getClipboardSequenceNumber** 获取当前剪贴板内容的id(如果被重新写入了该id会变动)
- **watchClipboard**  当剪贴板内容变更后发生回调
- **watchUSB** 当驱动器添加或者移除后发生回调
- **keyboardHook** 低级键盘输入变化获取
- **mouseHook** 低级鼠标位置变化获取
- **freePort** 获取一个空闲可用的端口号
- **hasPortTCP** 判断TCP(服务)端口号正在使用/系统占用  （反向理解：为true的话不能创建端口绑定）
- **hasPortUDP** 判断UDP端口号正在使用/系统占用（反向理解：为true的话不能创建端口绑定）
- **_popen** 创建管道并执行命令
- **popen** 创建管道并执行命令
- **formatVolumePath** 格式化 驱动器路径  ('\\Device\\HarddiskVolume2' => "D:\\")
- **getVolumeList**  获取当前文件系统的驱动器名称及路径
- **getTCPPortProcessID** 获取指定TCP端口的pid
- **getTCPPortProcessID** 获取指定UDP端口的pid
- **createMutex** 创建进程互斥体(全局)
- **hasMutex** 判断进程互斥体(全局)

### 电源控制

----------------------------------

- **systemStartTime** 系统启动到现在的时间
- **shutMonitors** 关闭显示器
- **showMonitors** 恢复显示器
- **powerControl** 电源控制
  * **1001** 关机
  * **1002** 重启
  * **1003** 注销
  * **1005** 锁定
  * **shutDown** 关机
  * **restart** 重启
  * **cancellation** 注销
  * **lock** 锁定

### 注册表编辑

----------------------------------

- **hasRegistrKey** 判断键值是否存在
- **getStringRegKey** 获取内容(文本)
- **removeStringRegKey** 删除数据
- **setRegistrKey** 设置键值对
- **createPathRegistr** 创建新的路径
- **enumRegistrKey** 枚举键值
- **getRegistrBuffValue** 获取内容(二进制 Buffer)
- **openRegKey**  打开该路径并返回方法的封装
- **listRegistrPath**  将该路径下的内容以objcet 的方式显示
- **removeStringRegKeyWalk** 删除一个文件夹键值

- **removeStringRegKey** 删除一个文件夹key

- **removeStringRegValue** 删除一个值

- **setRegistrDword** 设置一个32位数字

- **setRegistrQword** 设置一个64位数字

- **getRegistrDword** 获取一个32位数字

- **getRegistrQword** 获取一个64位数字

- **registr**  注册表处理的集合
  - **analysisDirectPath**  将一条完整的注册表路径 转为  数组 拆分为 [  *HKEY*: HKEY, *Path*: string, *key*?: string]
  - **has**
  - **get**
  - **remove**
  - **keys**
  - **list**
  - **create**
  - **open**

### 键盘鼠标USB

----------------------------------

- **getHidUsbList** 获取所有HidUsb设备（仅限HID设备）
- **setCursorPos** 设置鼠标位置
- **mouse** 自定义鼠标事件
- **hasKeyActivate** 判断该按键是否被按下
- **leftClick** 左键点击
- **rightClick** 右键点击
- **getBasicKeys** 获取四大按钮是否按下
- **getMouseMovePoints** 获取鼠标之前64个位置
- **getUsbDevsInfo** 获取所有usb驱动器(不包含HUD)
- **keyboardHook** 低级的键盘变化监听构造函数
- **mouseHook** 低级的鼠标变化监听构造函数
- **sendBasicKeys**  向系统发送标准的快捷键  例如 ： ctrl+win+C
- **getColor**  获取指定位置的颜色
- **captureBmpToFile**  截图指定位置并且写入文件 （BMP）
- **sendKeyboard** 发送键盘事件 
- **sendKeyboardSequence**  发送键盘事件序列
- **sendKeyT2CSync**  同步执行t2c 脚本  （一种快捷的 更加符合人类编写键鼠操作的文本微脚本）
- **sendKeyT2C**  异步执行t2c 脚本  （一种快捷的 更加符合人类编写键鼠操作的文本微脚本）
- **getCursorPos** 获取鼠标光标所在位置的坐标
- **hasMouseLeftActivate**  判断鼠标左键是否被按下
- **hasMouseRightActivate**  判断鼠标右键是否被按下
- **hasMouseMiddleActivate** 判断鼠标中键是否被按下
- **hasMouseBtnActivate** 判断鼠标的按钮按下状态
- **setLimitMouseRange** 设置鼠标坐标到指定位置 并且限制在一定范围内(时间ms)

### 文件链接/快捷方式

----------------------------------

- **createSymlink** 创建一个软链接

- **createDirSymlink** 创建一个文件夹软链接

- **createHardLink** 创建一个硬链接

### WebView2

----------------------------------

- **getWebView2Info**  当前安装的WebView2 信息
- **hasWebView2** 当前电脑是否安装了 WebView2
- **WebView2OnlineInstall** 在线安装WebView2



### 变量环境（Environment）

----------------------------------

- **Environment** 合集
- **hasKeyExists** 判断变量中是否存在指定值 `用户` `系统`
- **hasUseKeyExists** 判断变量中是否存在指定值 `用户` 
- **hasSysKeyExists** 判断变量中是否存在指定值 `系统`
- **escapeEnvVariable** 通过当前的变量对变量内容进行解析（不受进程变量影响）实时
  -  HMC_x64.escapeEnvVariable("%AppData%\\hmc-win32")  log  ->  'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
- **removeUserVariable** 删除一个用户变量 `用户` 
- **removeVariable** 删除一个用户变量 `用户` `系统`
- **removeSystemVariable** 删除一个用户变量  `系统`
- **getSystemVariable** 获取一个在系统变量中的值 `系统`
  - transMean<true>  %AppData%\\hmc-win32  -> 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
  - transMean<false> %AppData%\\hmc-win32 -> '%AppData%\\hmc-win32'
- **getUserVariable** 获取一个在用户变量中的值 `用户` 
  - transMean<true>  %AppData%\\hmc-win32  -> 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
  - transMean<false> %AppData%\\hmc-win32 -> '%AppData%\\hmc-win32'
- **getVariableAnalysis** 获取一个在用户变量中的值 `用户`  `系统`
- **putSystemVariable** 添加一个系统变量 （请注意 win进程获取的优先级: 进程变量 -> 用户变量 -> *系统变量） path变量不受此影响（win定义）
  - append 添加到尾部 而不是替换   "ddd" -> "oid...;ddd"
  - transMean 转义 "%AppData%\\hmc-win32" -> 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'

- **putUserVariable**  添加一个系统变量 （请注意 win进程获取的优先级: 进程变量 -> 用户变量 -> *系统变量） path变量不受此影响（win定义）
  - append 添加到尾部 而不是替换   "ddd" -> "oid...;ddd"
  - transMean 转义 "%AppData%\\hmc-win32" -> 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
- **getVariableAll** 获取所有的值 从环境读取 (进程环境)
- **getRealGlobalVariableList**  获取所有的值 从注册表读取 (配置环境)
- **getUserKeyList** 获取用户变量的键列表`用户` 
- **getSystemKeyList** 获取系统变量的键列表 `系统`
- **updateThis** 同步系统(全局)变量到当前进程

### 网络 (net)

------------------------------

- **ipv4** 获取本机局域网的ip(v4)
- **ip** 获取本机局域网的ip(适配器,v4,v6)
- **adapterIP** 获取本机局域网的ip(适配器,v4,v6)
- **public_ip** 获取本机公网ip
- **getNetParams** 获取主机网络信息
- **freePort** 获取一个tcp空闲端口 (服务)
- **freePortTCP** 获取一个空闲的tcp端口
- **freePortUDP** 获取一个空闲的udp端口
- **hasPortUDP** 判断此udp端口是否空闲
- **hasPortTCP**判断此TCP端口是否空闲
- **getSystemProxyServer** 获取系统代理链接（仅在启用系统代理时）
- **getSystemProxyPac** 获取系统代理pac脚本链接
- **getDomainIPaddress** 从默认dns(联网)解析域名主机ip
- **getHostsPath** 获取hosts文件的路径
- **getTCPv6PortProcessID** 获取此端口被哪个进程占用了
- **getUDPv6PortProcessID** 获取此端口被哪个进程占用了
- **getUDPv4PortProcessID** 获取此端口被哪个进程占用了
- **getTCPv4PortProcessID** 获取此端口被哪个进程占用了
- **getConnectNetList** 枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息
- **killProcess** 结束该pid进程（低权利 如果需要高权限的kill请使用hmc-win32）
- **sleep** 同步阻塞(进程)
- **Sleep** 异步阻塞(进程)
- **PortWatchdog** 检测端口变化如果关闭或者启用时发起回调
- **getProcessidFilePath** 获取进程可执行文件位置
- **isAdmin** 判断当前软件是否拥有管理员权限



### API中间层

----------------------------------

- **ref**  转换
  - **bool**  将布尔内容转为安全的 bool 类型布尔
  - **string** 将文本/伪文本内容转为安全的文本
  - **int** 将数字/伪数字内容转为安全的int数字
  - **HKEY** 所有注册表的 HKEY 对象
- **Sleep** 异步的阻塞
- **default**  映射整个功能组(兼容ejs)
- **hmc**   映射整个功能组(兼容局部导出)
- **native** 直接连接HMC.node的原生方法 (不建议使用)



### 其他

### 重新构建

HMC所有API采用winapi+nodeapi实现，因此无需重新编译（允许运行在node8以上环境 node6.14.2 需要自行使用esbuld编译），如果您需要对源代码进行修改请使用``node-gyp rebuild`` 进行编译，这需要有一定的C/C++基础，编译工具使用node-gyp即可，需要使用到的工具如下：

- node-gyp
- Visual Studio 2019（or other versions)

### 一些常见问题

- 子进程/线程  信息获取不全 

  - **node 进程可执行文件是 32位的 但是系统是64位的 被枚举的  进程/线程/子进程/二次子进程  包含64位的** 
    - 无法解决 因为 子进程/线程 使用进程快照消耗和安全性都最佳  

  

### 风险告知

- 每个功能模块都会经过千次以上循环调用 无出现进程崩溃

- API已经通过js严格转码 只有调用native才需要 ~~但是由于C++和C语言都是严格类型，必须严格使用typeScript严格传递类型~~
- 虽然经过疲劳测试，但是还是有可能会有无法预期的进程奔溃，所以建议在子进程下运行
- C++ 的野指针和空指针和内存溢出 引用错误 类型错误 等 对于进程都是致命的，所以在编写新功能时候需要不断地进行模拟疲劳测试



