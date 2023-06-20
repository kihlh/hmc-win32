# **HMC-win32: Package for Windows platform API**

![系统环境](https://cos.kiic.top/assets/used/202204112301972.svg)      ![系统环境](https://cos.kiic.top/assets/used/202204112301969.svg)      ![系统环境](https://img.shields.io/badge/Node6.14.2+-Node-97c40f.svg?longCache=true)       ![系统环境](https://img.shields.io/badge/Node8.0+-electron-97c40f.svg?longCache=true)    

## help
`ddffsd Parts of this document were translated by machine (Deepl)`

`Backwards compatible to node6.14.2 but the precompiled version is only supported to node8 and above (because node6 has no asynchronous syntactic sugar), for node6 please compile to node6.14.2 with esbuld yourself`

####  [编程帮助(中文)](https://kihlh.gitbook.io/hmc/)     [编程帮助(中国服务器)](https://www.yuque.com/kiic/hmc/)           [help (English) ](https://kihlh.gitbook.io/hmc_en/)

##   Why do I need to use this module ?


- **Zero Dependency**

- **There are requirements for execution speed (e.g. cmd runs require an extra 100ms for calls, and compatibility is poor, requiring extra processes to handle)**

- **Low consumption e.g.  [ffi](https://github.com/node-ffi/node-ffi)  requires a lot of conversion and coding callbacks and is complex to write compared to hmc which is smaller and can implement hundreds of functions in just a few hundred K without third party support**

- **Need for assistance with window automation**

- **Need something very simple but difficult to implement via node**

- **A stable, don't-compile-every-time module**

- **High memory requirements**

- **Development of desktop gadgets**

- **HMC encapsulates dozens of common or uncommon APIs for desktop applications**


## What functions can be achieved

- **C++ easily implements functions like closing processes, getting the clipboard, but node doesn't support them.**

- **Window Processing**

- **Process Handling**

- **System api calls**

- **Disable user actions**

  




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

```

###  In TypeScript using the

```typescript
import  HMC = require("hmc-win32");
```

# 功能概览

### API中间层

- **ref**  转换
  - **bool**  将布尔内容转为安全的 bool 类型布尔
  - **string** 将文本/伪文本内容转为安全的文本
  - **int** 将数字/伪数字内容转为安全的int数字
  - **HKEY** 所有注册表的 HKEY 对象
- **Sleep** 异步的阻塞
- **default**  映射整个功能组(兼容ejs)
- **hmc**   映射整个功能组(兼容局部导出)
- **native** 直接连接HMC.node的原生方法 (不建议使用)

### 窗口操作

- **closedHandle** 关闭句柄
- **setWindowMode** 设置窗口位置大小
- **getWindowRect** 获取窗口位置大小
- **getDeviceCaps** 获取屏幕大小
- **getPointWindow** 获取鼠标所在窗口的句柄
- **getPointWindowName** 获取鼠标所在窗口的进程名
- **getPointWindowProcessId** 获取鼠标所在窗口的进程id
- **getPointWindowMain**  获取鼠标所在窗口的父窗口
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
  - **setTransparent** 设置 不透明度
- **enumChildWindows** 枚举句柄的子窗口
- **setWindowTitleIcon**  设置标题窗口图标icon
- **getWindowClassName** 获取窗口类名
- **getAllWindowsHandle**  获取所有窗口的句柄 **增加一个参数** 是否要求必须为窗口
- **setForegroundWindow**  设置窗口聚焦
- **getAllWindows** 默认使用 *isWindows* 为true
- **getWindowStyle**  获取窗口类关联代码
- **setWindowIconForExtract**  通过可执行文件或者带有图标的文件设置窗口图标


### 进程控制
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
- 


### 状态栏
- **getTrayList** 获取托盘图标
- **closedHandle** 关闭托盘图标(提交句柄)

### 系统操作
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
### 电源控制
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

### 文件链接/快捷方式

- **createSymlink** 创建一个软链接

- **createDirSymlink** 创建一个文件夹软链接

- **createHardLink** 创建一个硬链接

### WebView2

- **getWebView2Info**  当前安装的WebView2 信息
- **hasWebView2** 当前电脑是否安装了 WebView2
- **WebView2OnlineInstall** 在线安装WebView2

### 其他

- **_SET_HMC_DEBUG**  HMC调试模式  打开以后会正常执行代码 但是会打印报错内容到控制台 console.error(new Error( HMC 内部错误定义 )) 例如 设置标题 设置错误 只返false 打开以后会打印详细的错误内容

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





