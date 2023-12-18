# HMC-win32: Easier Access to System APIs

![System Environment](https://cos.kiic.top/assets/used/202204112301972.svg)      ![System Environment](https://cos.kiic.top/assets/used/202204112301969.svg)      ![System Environment](https://img.shields.io/badge/Node6.14.2+-Node-97c40f.svg?longCache=true)       ![System Environment](https://img.shields.io/badge/Node8.0+-electron-97c40f.svg?longCache=true)    

## Help

#### 你正在查看 English 版本的介绍，您可以点击此 [中文](README-zh.md) 查看此 readme 的语言的中文版本

The document you are currently viewing has been translated from Chinese to English by GPT3.5(AI). If there are any errors, please provide feedback in the issues section.

We provide programming language documentation for understanding API usage, but please note that it may not be up-to-date due to the large number of APIs, and writing comprehensive documentation is a significant task. HMC is written in TypeScript and comes with type declarations, allowing you to see types and usage in mainstream IDE editors.

#### Relevant Links:

##### Help:   [Programming Help](https://kihlh.gitbook.io/hmc_en/)          NPM:    [hmc-win32](https://www.npmjs.com/package/hmc-win32)    [hmc-autoit](https://www.npmjs.com/package/hmc-autoit)      Source:  [C++ Source Code](https://github.com/kihlh/hmc-win32/tree/master/source)    [AutoitX](https://github.com/kihlh/hmc-win32/tree/master/source/hmc-autoIt)      [Refactoring Version](https://github.com/kihlh/hmc-win32/tree/master/source/h2c-win32)   



### Subset

#### autoit: hmc-autoit     [npm](https://www.npmjs.com/package/hmc-autoit)       [source code](https://github.com/kihlh/hmc-win32/tree/master/source/hmc-autoIt) 

**hmc-autoit is a subset of HMC that includes a series of functions for invoking AutoItX API. It shares the advantages of HMC and does not require recompilation or the use of ffi magic.**

------------------



## Why Should I Use This Module?


- **Zero Dependencies: HMC does not rely on third-party modules and does not require knowledge of C++ programming.**
- **Requirement for Execution Speed: Previously, when using Node.js for complex functionalities, I could only call programs through the command line, which made data retrieval and invocation very challenging and resulted in an additional minimum latency of 100ms.**
- **HMC predominantly uses system APIs, which are usually very fast. HMC performs extensive transformations on its APIs, making input parameters and return values easier to handle. You do not need a clear understanding of the system, and HMC itself is very lightweight. It can even run with just two files and does not rely on additional DLL files or similar dependencies.**
- **In most cases, HMC has negligible memory consumption.**


## We have categorized several functionalities for you:

- ##### Window Operations: Adjustment / Enumeration / Disable / Query / Change

- **Process Control: Kill / Information / Handle / Window / Change**

- **Network: Port / Network Card / LAN / IP**

- **File System: Symbolic Link / Hard Link / USB**

- ##### Environment Variables: User Variables / System Variables / Synchronization / Escape

- **Clipboard: File List / Read and Write / Text / Change**

- **Automation: Keyboard / Mouse / Execution / Reading / AutoIt3**

- **Registry: Read / Write** 

- ##### Power Control: Shutdown / Restart / Logoff / Monitor / Startup Time

- **Shell: Recycle Bin / Message / Shortcut / Run Software / Select File / Save File**

- **Mutex: Create / Destroy (to prevent process duplicates)**

- **Tray: Create / Enumerate / Destroy**




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

- Overview of Functions

  ### Window Operation

  ----------------------------------

- **closedHandle** Close handle

- **setWindowMode** Set window position and size

- **getWindowRect** Get window position and size

- **getDeviceCaps** Get screen size

- **getPointWindow** Get handle of the window where the mouse is located

- **getPointWindowName** Get the process name of the window where the mouse is located

- **getPointWindowProcessId** Get the process ID of the window where the mouse is located

- **getPointWindowMain** Get the parent window of the window where the mouse is located

- **getHandleProcessID** Get the process ID corresponding to the handle

- **getProcessHandle** Get the handle of the main process/thread corresponding to the process

- **lookHandleGetTitle** Get the title of the handle

- **lookHandleSetTitle** Set the title of the handle

- **lookHandleShowWindow** Set the window display state through the handle

- **isHandleWindowVisible** Determine if the handle is an active window

- **lookHandleCloseWindow** Close the window corresponding to the handle

- **getForegroundWindow** Get the handle of the active window

- **getAllWindows** Get information for all windows

- **getMainWindow** Get the parent window under this handle

- **setWindowTop** Set the window to the top

- **hasWindowTop** Check if the window is set to the top

- **windowJitter** Shake the window

- **updateWindow** Refresh the window

- **setWindowFocus** Set the window focus

- **setWindowEnabled** Set whether the window supports response events (mouse and keyboard clicks)

- **isEnabled** Check if the window supports response events (mouse and keyboard clicks)

- **SetWindowInTaskbarVisible** Whether to display the icon in the taskbar

- **setHandleTransparent** Set window opacity

- **SetBlockInput** Prevent keyboard and mouse input events from reaching the application.

- **WatchWindowPoint** Callback when the window where the mouse is located changes

- **WatchWindowForeground** Callback when the focused window changes

- **getAllWindowsHandle** Get all handles and return a pseudo-number method set of HWND (replacement of getAllWindows, no impact on getting 200,000 processes)

- **HWND** (class) Number (mapping)

  - **HWND** number
  - **closed** Close handle forcefully
  - **close** Send a close message to the window
  - **rect** Window position (automatically retrieved when accessed)
  - **title** Title (automatically retrieved when accessed)
  - **setTitle** Set the title
  - **exists** Check if the handle is valid (automatically retrieved when accessed)
  - **isHandle** Check if the handle is valid (automatically retrieved when accessed)
  - **pid** Attached process ID of the handle (automatically retrieved when accessed)
  - **MianPid** Main thread/main process ID of the handle (automatically retrieved when accessed)
  - **MainHandle** Main handle
  - **isVisible** Visibility
  - **kill** Terminate the main process/main thread
  - **hide** Hide
  - **show** Show
  - **setMin** Minimize
  - **setMax** Maximize
  - **setRestore** Restore to the most recent state
  - **setFocus** Set focus
  - **setEnabled** Disable
  - **isEnabled** Check if it is disabled
  - **setJitter** Window jitter
  - **isTop** Check if it is set to top
  - **setTopOrCancel** Cancel/set as top window
  - **setOpacity** Set opacity 0-100 / 0.0-1.0
  - **setTransparent** Set transparency
  - **enumChildWindows** Enumerate the child windows of the handle
  - **setWindowTitleIcon** Set the window title icon
  - **getWindowClassName** Get the window class name
  - **getAllWindowsHandle** Get the handles of all windows (Add an additional parameter to specify if only windows are required)
  - **setForegroundWindow** Set the window focus
  - **getAllWindows** Default isWindows=true
  - **getWindowStyle** Get the window class style code
  - **setWindowIconForExtract** Set the window icon using an executable file or a file with an icon

### Process Control

  - **killProcess** Terminate the process with the given PID
  - **sleep** Synchronous blocking (for processes)
  - **openApp** Open an application
  - **getProcessList** Get the list of processes
  - **getDetailsProcessList** Get the detailed process list (slow, 20ms delay)
  - **getProcessHandle** Get the window handle for the main process/thread corresponding to the process
  - **getProcessName** Get the process name
  - **getProcessidFilePath** Get the file path of the executable for the process
  - **getForegroundWindowProcessID** Get the process ID of the active window
  - **getHandleProcessID** Get the process ID corresponding to the handle
  - **isProcess** Check if the process ID exists
  - **hasProcess** Check if the process ID exists
  - **killProcessName** Terminate the process with the given name or (regular expression) matching process name
  - **processWatchdog** Callback when the monitored process ends
  - **getProcessNameList** Get the list of processes matching the given name or (regular expression)
  - **getDetailsProcessNameList** Get the list of processes matching the given name or (regular expression) with executable file paths (slow, 20ms delay)
  - **getModulePathList** Query the modules loaded by the process
  - **getProcessThreadList** Enumerate the thread IDs of the process
  - **getProcessParentProcessID** Get the parent process of the process
  - **getSubProcessID** Get the list of sub-process IDs
  - **enumProcessHandle** Enumerate the handles of the process ID
  - **enumAllProcessHandle** Enumerate the handles of all process IDs
  - **findProcess** Search for a process
  - **getProcessStartTime** Get the process start time (in ms)
  - **With "2.0api" at the end, they all support:**
    - Asynchronous `Promise`
    - Asynchronous `callback`
    - Synchronous `Promise`
    - Concurrent execution
- **findProcess2**: Search for processes (Asynchronous)

- **findProcess2Sync**: Search for processes (Synchronous)

- **getAllProcessList2**: Get a list of processes (Asynchronous - Enumeration). Enumeration is the fastest method but may not enumerate processes on a 64-bit system where the application is 32-bit. However, the information provided may not be detailed.

  - pid: Process ID
  - name: Resolved from the image path
  - path: Image path

- **getAllProcessList2Sync**: Get a list of processes (Synchronous - Enumeration)

- **getAllProcessList2Snp**: Get a list of processes (Asynchronous - Snapshot). Please note that if the executable is 32-bit and the system is 64-bit, information about 64-bit processes will not be retrieved.

  - pid: Process ID
  - name: Resolved from the image path
  - ppid: Parent process ID
  - ... (additional information)

- **getAllProcessListSnp2Sync**: Get a list of processes (Synchronous - Snapshot)

- **getAllProcessListNt2**: Get a list of processes (Asynchronous - Kernel)

  - pid: Process ID
  - name: Software name
  - ... (additional information)

- **getAllProcessListNt2Sync**: Get a list of processes (Synchronous - Kernel)

- **getProcessCpuUsage2**: Get CPU usage of a process (Asynchronous)

- **getProcessCpuUsage2Sync**: Get CPU usage of a process (Synchronous)

- **getProcessParentProcessMatch2**: Match parent process information (Asynchronous)

- **getProcessParentProcessMatch2Sync**: Match parent process information (Synchronous)

- **getProcessFilePath2**: Get executable file path of a process (Asynchronous)

- **getProcessFilePath2Sync**: Get executable file path of a process (Synchronous)

- **existProcess2**: Check if a process exists (Asynchronous)

- **existProcess2Sync**: Check if a process exists (Synchronous)

- **getDetailsProcessList2**: For compatibility with old API, export a process list with executable file paths (Asynchronous)

- **getDetailsProcessList2Sync**: For compatibility with old API, export a process list with executable file paths (Synchronous)

- **getProcessName2**: Get the executable file name of a process (Asynchronous)

- **getProcessName2Sync**: Get the executable file name of a process (Synchronous)

### Status Bar

  - **getTrayList** Get the tray icons
  - **closedHandle** Close the tray icon (submit handle)

  ### System Operations

  - **SetSystemHOOK** Disable/enable system keyboard and mouse hook (advanced API)
  - **getHidUsbList** Get all HID USB devices (for HID devices only)
  - **getShortcutLink** Get the content of a shortcut link
  - **setShortcutLink** Set the content of a shortcut link
  - **isSystemX64** Check if the current system is x64
  - **messageBox** Message box (call win-api)
  - **getSystemMenu** Customize the system right-click menu (to disable the default ugly system menu provided by Windows)
  - **clearClipboard** Clear the clipboard
  - **setClipboardText** Set the clipboard text
  - **getClipboardText** Get the clipboard text
  - **setClipboardFilePaths** Write a list of file paths to the clipboard
  - **getClipboardFilePaths** Read a list of file paths from the clipboard
  - **openApp** Open an application
  - **isAdmin** Check if the current software has administrator privileges
  - **getSystemIdleTime** Get system idle time
  - **systemStartTime** System uptime
  - **system** Equivalent to the system function in C/C++
  - **alert** Display a message box with a specified message and an OK button
  - **confirm** Display a message box with a specified message and OK/Cancel buttons
  - **MessageStop** Display a message box with a specified message, OK button, and ❌ (X) icon
  - **MessageError** Display an error box with a specified message, OK button, and ❗ exclamation mark icon.
  - **systemChcp** Current system shell's chcp information
  - **deleteFile** Move a file to the recycle bin
  - **trash** Move a file to the recycle bin
  - **getClipboardSequenceNumber** Get the ID of the current clipboard content (if it is overwritten, the ID will change)
  - **watchClipboard** Callback when the clipboard content changes
  - **watchUSB** Callback when a drive is added or removed
  - **keyboardHook** Low-level keyboard input change detection
  - **mouseHook** Low-level mouse position change detection
  - **freePort** Get an available free port number
  - **hasPortTCP** Check if a TCP port is in use or occupied by the system (if true, the port cannot be bound)
  - **hasPortUDP** Check if a UDP port is in use or occupied by the system (if true, the port cannot be bound)
  - **_popen** Create a pipe and execute a command
  - **popen** Create a pipe and execute a command
  - **formatVolumePath** Format a drive path ('\\Device\\HarddiskVolume2' => "D:\")
  - **getVolumeList** Get the names and paths of the current file system drives
  - **getTCPPortProcessID** Get the PID of the process using the specified TCP port
  - **getUDPPortProcessID** Get the PID of the process using the specified UDP port
  - **createMutex** Create a process mutex (global)
  - **hasMutex** Check if the process mutex (global) exists

  ### Power Control

  - **systemStartTime** System uptime
  - **shutMonitors** Turn off the monitors
  - **showMonitors** Restore the monitors
  - **powerControl** Power control
    - **1001** Shut down
    - **1002** Restart
    - **1003** Log off
    - **1005** Lock
    - **shutDown** Shut down
    - **restart** Restart
    - **cancellation** Log off
    - **lock** Lock

### Registry Editing

- **hasRegistrKey** Check if a registry key exists
- **getStringRegKey** Get the content (text) of a registry key
- **removeStringRegKey** Delete data from a registry key
- **setRegistrKey** Set a key-value pair in the registry
- **createPathRegistr** Create a new registry path
- **enumRegistrKey** Enumerate the keys in a registry path
- **getRegistrBuffValue** Get the content (binary buffer) of a registry key
- **openRegKey** Open a registry path and return a wrapped method
- **listRegistrPath** Display the content of a registry path as an object
- **removeStringRegKeyWalk** Delete a registry key folder

- **removeStringRegKey** Delete a registry key folder

- **removeStringRegValue** Delete a registry value

- **setRegistrDword** Set a 32-bit number in the registry

- **setRegistrQword** Set a 64-bit number in the registry

- **getRegistrDword** Get a 32-bit number from the registry

- **getRegistrQword** Get a 64-bit number from the registry

- **registr** Collection of registry handling methods
  - **analysisDirectPath** Split a complete registry path into an array [ *HKEY*: HKEY, *Path*: string, *key*?: string]

  - **has**
  - **get**
  - **remove**
  - **keys**
  - **list**
  - **create**
  - **open**

### Keyboard Mouse USB

- **getHidUsbList** Get all HidUsb devices (only HID devices)
- **setCursorPos** Set the mouse position
- **mouse** Custom mouse events
- **hasKeyActivate** Check if a key is pressed
- **leftClick** Perform a left mouse click
- **rightClick** Perform a right mouse click
- **getBasicKeys** Get the status of the four major buttons (Ctrl, Shift, Alt, Win)
- **getMouseMovePoints** Get the previous 64 positions of the mouse
- **getUsbDevsInfo** Get information of all USB drives (excluding HUD)
- **keyboardHook** Low-level keyboard event listener constructor
- **mouseHook** Low-level mouse event listener constructor
- **sendBasicKeys** Send standard shortcut keys to the system (e.g., Ctrl+Win+C)
- **getColor** Get the color at a specified position
- **captureBmpToFile** Capture a screenshot of a specific position and save it to a file (BMP format)
- **sendKeyboard** Send a keyboard event
- **sendKeyboardSequence** Send a sequence of keyboard events
- **sendKeyT2CSync** Execute t2c script synchronously (a convenient and human-friendly text-based scripting language for simulating keyboard and mouse operations)
- **sendKeyT2C** Execute t2c script asynchronously

### File Links/Shortcuts

- **createSymlink** Create a symbolic link
- **createDirSymlink** Create a directory symbolic link
- **createHardLink** Create a hard link

### WebView2

- **getWebView2Info** Get information about the installed WebView2
- **hasWebView2** Check if WebView2 is installed on the current computer

- **WebView2OnlineInstall** WebView2 Online Installation



### Environment Variables

- **Environment** Collection of environment variables
- **hasKeyExists** Check if a specific value exists in the variables (User/System)
- **hasUseKeyExists** Check if a specific value exists in the variables (User)
- **hasSysKeyExists** Check if a specific value exists in the variables (System)
- **escapeEnvVariable** Resolve the variable contents using the current environment (not affected by process variables) in real-time
  - HMC_x64.escapeEnvVariable("%AppData%\\hmc-win32") => 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
- **removeUserVariable** Remove a user variable (User)
- **removeVariable** Remove a user variable (User/System)
- **removeSystemVariable** Remove a user variable (System)
- **getSystemVariable** Get the value of a variable from the system variables (System)
  - transMean<true>  %AppData%\\hmc-win32  => 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
  - transMean<false> %AppData%\\hmc-win32 => '%AppData%\\hmc-win32'
- **getUserVariable** Get the value of a variable from the user variables (User)
  - transMean<true>  %AppData%\\hmc-win32  => 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'
  - transMean<false> %AppData%\\hmc-win32 => '%AppData%\\hmc-win32'
- **getVariableAnalysis** Get the value of a variable from the user/system variables (User/System)
- **putSystemVariable** Add a system variable (Note that the priority of variable lookup in the Windows process is: Process variables -> User variables -> *System variables). Path variables are not affected by this (Windows-defined).
  - append: Add to the end instead of replacing. "ddd" => "oid...;ddd"
  - transMean: Translate "%AppData%\\hmc-win32" => 'C:\\Users\\...\\AppData\\Roaming\\hmc-win32'

- **putUserVariable** Add a user variable (Note that the priority of variable lookup in the Windows process is: Process variables -> User variables -> *System variables). Path variables are not affected by this (Windows-defined).
  - append: Add to the end instead of replacing. "ddd" => "oid...;ddd"
  - transMean: Translate "%AppData%\\hmc-win32" => 'C:\Users\\...\\AppData\\Roaming\\hmc-win32'

- **getVariableAll** Retrieve all values from the environment variables (Process Environment)
- **getRealGlobalVariableList** Retrieve all values from the registry (System Configuration)
- **getUserKeyList** Get the key list of user variables (User)
- **getSystemKeyList** Get the key list of system variables (System)
- **updateThis** Synchronize system (global) variables to the current process

### Network (net)

- **ipv4** Get the local IP address (v4) of the machine
- **ip** Get the local IP address (adapter, v4, v6) of the machine
- **adapterIP** Get the local IP address (adapter, v4, v6) of the machine
- **public_ip** Get the public IP address of the machine
- **getNetParams** Get the network information of the host
- **freePort** Get a free TCP port (service)
- **freePortTCP** Get a free TCP port
- **freePortUDP** Get a free UDP port
- **hasPortUDP** Check if the UDP port is free
- **hasPortTCP** Check if the TCP port is free
- **getSystemProxyServer** Get the system proxy server link (only when the system proxy is enabled)
- **getSystemProxyPac** Get the system proxy PAC script link
- **getDomainIPaddress** Resolve the IP address of a domain host using the default DNS (Internet connection)
- **getHostsPath** Get the path of the hosts file
- **getTCPv6PortProcessID** Get the process ID that is using this TCPv6 port
- **getUDPv6PortProcessID** Get the process ID that is using this UDPv6 port
- **getUDPv4PortProcessID** Get the process ID that is using this UDPv4 port
- **getTCPv4PortProcessID** Get the process ID that is using this TCPv4 port
- **getConnectNetList** Enumerate TCP and UDP port information of IPv4 and IPv6 in this computer
- **killProcess** Terminate the process with the specified PID (with low privileges, for high privilege killing, please use hmc-win32)
- **sleep** Synchronous blocking (process)
- **Sleep** Asynchronous blocking (process)
- **PortWatchdog** Detect changes in ports and trigger callbacks when closed or enabled
- **getProcessidFilePath** Get the executable file path of a process
- **isAdmin** Check if the current software has administrator privileges

### API Middle Layer

- **ref** Conversion
  - **bool** Convert boolean content to a safe boolean type
  - **string** Convert text/pseudo-text content to safe text
  - **int** Convert numeric/pseudo-numeric content to a safe integer
  - **HKEY** HKEY object for all registry keys
- **Sleep** Asynchronous blocking
- **default** Map the entire function group (compatible with EJS)
- **hmc** Map the entire function group (compatible with partial exports)
- **native** Directly connect to native methods of HMC.node (not recommended)



### Miscellaneous

### Rebuilding

All HMC APIs are implemented using winapi+nodeapi, so there is no need to recompile (it can run in Node.js 8 or higher environment, Node.js 6.14.2 needs to be compiled using esbuild). If you need to modify the source code, please use `node-gyp rebuild` for compilation. This requires some knowledge of C/C++ and the use of the node-gyp compilation tool. The following tools are needed:

- node-gyp
- Visual Studio 2019 (or other versions)

### Common Issues

- Incomplete information when retrieving subprocesses/threads

  - **The node process executable is 32-bit, but the system is 64-bit, so the enumerated subprocesses/threads include 64-bit ones**
    - This cannot be resolved because retrieving subprocesses/threads using process snapshots has the best performance and security

### Risk Disclosure

- Each functional module has been tested thousands of times without process crashes.
- The APIs have been strictly encoded in JavaScript. Only calling native functions requires it. ~~However, due to the strict typing of C++ and C, typeScript must be used strictly for type passing.~~
- Although fatigue testing has been performed, unexpected process crashes may still occur. It is recommended to run in a subprocess.
- C++ issues such as dangling pointers, null pointers, memory overflows, reference errors, and type errors are fatal to the process. Therefore, continuous simulated fatigue testing is required when developing new features.



