# **hmc-autoit**

![系统环境](https://cos.kiic.top/assets/used/202204112301972.svg)      ![系统环境](https://cos.kiic.top/assets/used/202204112301969.svg)      ![系统环境](https://img.shields.io/badge/Node6.14.2+-Node-97c40f.svg?longCache=true)       ![系统环境](https://img.shields.io/badge/Node8.0+-electron-97c40f.svg?longCache=true)    

基于autoItX 与napi( node-api(C) )结合的api转发模块，无需再次编译,也无需使用ffi魔法，安全高效

An API forwarding module based on the combination of autoItX and NAPI (Node-API, C) provides a seamless solution without the need for recompilation or the use of \"ffi\" magic. It ensures high security and efficiency.

# api列表

| API 名称                      | 用途                                                 | **description**                                              | 完成度 | 类型重定向 | 测试 |
| ----------------------------- | ---------------------------------------------------- | ------------------------------------------------------------ | ------ | ---------- | ---- |
| **Init**                      | 初始化AutoItX，通常在开始使用AutoItX函数之前调用     | Initializes the AutoItX library.                             | **OK** | 1          |      |
| **error**                     | 获取上一次AutoItX函数调用返回的错误代码              | Retrieves the error code from the last AutoItX function call. | **OK** | 1          |      |
| **AutoItSetOption**           | 设置AutoIt的选项，可以用来配置AutoIt的一些行为       | Sets various options for AutoItX, such as timeout and behavior. | **OK** | 1          |      |
| **ClipGet**                   | 获取剪贴板的内容                                     | Retrieves the content of the Windows clipboard.              | **OK** | 1          |      |
| **ClipPut**                   | 将文本放入剪贴板                                     | Puts text into the Windows clipboard.                        | **OK** | 1          |      |
| **ControlClick**              | 模拟控件的点击操作                                   | Simulates a mouse click on a specified control (button, checkbox, etc.) in a window. | **OK** | 1          |      |
| **ControlClickByHandle**      | 使用控件句柄模拟控件的点击操作                       | Same as `AU3_ControlClick` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlCommand**            | 发送命令给控件，比如选择列表中的项、设置复选框状态等 | Sends a command to a control (button, checkbox, radio button, etc.) in a window. | **OK** | 1          |      |
| **ControlCommandByHandle**    | 使用控件句柄发送命令给控件                           | Same as `AU3_ControlCommand` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlListView**           | 操作ListView控件                                     | Sends commands to a ListView control (such as list items selection) in a window. | **OK** | 1          |      |
| **ControlListViewByHandle**   | 使用控件句柄操作ListView控件                         | Same as `AU3_ControlListView` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlDisable**            | 禁用控件                                             | Disables a control in a window.                              | **OK** | 1          |      |
| **ControlDisableByHandle**    | 使用控件句柄禁用控件                                 | Same as `AU3_ControlDisable` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlEnable**             | 启用控件                                             | Enables a control in a window.                               | **OK** | 1          |      |
| **ControlEnableByHandle**     | 使用控件句柄启用控件                                 | Same as `AU3_ControlEnable` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlFocus**              | 将焦点设置到控件上                                   | Sets focus to a control in a window.                         | **OK** | 1          |      |
| **ControlFocusByHandle**      | 使用控件句柄将焦点设置到控件上                       | Same as `AU3_ControlFocus` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlGetFocus**           | 获取当前具有焦点的控件句柄                           | Retrieves the handle of the control with focus.              | **OK** | 1          |      |
| **ControlGetFocusByHandle**   | 使用控件句柄获取当前具有焦点的控件句柄               | Same as `AU3_ControlGetFocus` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlGetHandle**          | 获取控件句柄                                         | Retrieves the handle of a control in a window.               | **OK** | 1          |      |
| **ControlGetHandleAsText**    | 获取控件句柄并返回为文本                             | Retrieves the handle of a control in a window as text.       | **OK** | 1          |      |
| **ControlGetPos**             | 获取控件的位置和尺寸                                 | Retrieves the position and size of a control in a window.    | **OK** | 1          |      |
| **ControlGetPosByHandle**     | 使用控件句柄获取控件的位置和尺寸                     | Same as `AU3_ControlGetPos` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlGetText**            | 获取控件的文本内容                                   | Retrieves the text from a control in a window.               | **OK** | 1          |      |
| **ControlGetTextByHandle**    | 使用控件句柄获取控件的文本内容                       | Same as `AU3_ControlGetText` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlHide**               | 隐藏控件                                             | Hides a control in a window.                                 | **OK** | 1          |      |
| **ControlHideByHandle**       | 使用控件句柄隐藏控件                                 | Same as `AU3_ControlHide` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlMove**               | 移动控件到指定位置                                   | Moves a control within a window.                             | **OK** | 1          |      |
| **ControlMoveByHandle**       | 使用控件句柄移动控件到指定位置                       | Same as `AU3_ControlMove` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlSend**               | 向控件发送按键输入                                   | Sends keystrokes to a control in a window.                   | **OK** | 1          |      |
| **ControlSendByHandle**       | 使用控件句柄向控件发送按键输入                       | Same as `AU3_ControlSend` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **ControlSetText**            | 设置控件的文本内容                                   | Sets the text of a control in a window.                      | **OK** | 1          |      |
| **ControlSetTextByHandle**    | 使用控件句柄设置控件的文本内容                       | Sets the text of a control in a window using its handle.     | **OK** | 1          |      |
| **ControlShow**               | 显示控件                                             | Shows a control in a window.                                 | **OK** | 1          |      |
| **ControlShowByHandle**       | 使用控件句柄显示控件                                 | Shows a control in a window using its handle.                | **OK** | 1          |      |
| **ControlTreeView**           | 操作TreeView控件                                     | Sends commands to a TreeView control in a window.            | **OK** | 1          |      |
| **ControlTreeViewByHandle**   | 使用控件句柄操作TreeView控件                         | Same as `AU3_ControlTreeView` but uses a handle instead of window and control IDs. | **OK** | 1          |      |
| **DriveMapAdd**               | 映射本地驱动器到网络共享路径                         | Maps a network drive.                                        | **OK** | 1          |      |
| **DriveMapDel**               | 取消驱动器映射                                       | Unmaps a network drive.                                      | **OK** | 1          |      |
| **DriveMapGet**               | 获取驱动器映射的信息                                 | Retrieves the mapping of a network drive.                    | **OK** | 1          |      |
| **IsAdmin**                   | 检查当前用户是否有管理员权限                         | Checks if the current process is running with administrative privileges. | **OK** | 1          |      |
| **MouseClick**                | 模拟鼠标点击                                         | Simulates a mouse click at the current cursor position.      | **OK** | 1          |      |
| **MouseClickDrag**            | 模拟鼠标点击并拖动                                   | Simulates dragging the mouse between two points.             | **OK** | 1          |      |
| **MouseDown**                 | 模拟鼠标按下                                         | Simulates pressing a mouse button.                           | **OK** | 1          |      |
| **MouseGetCursor**            | 获取鼠标当前的光标样式                               | Retrieves the mouse cursor's current shape.                  | **OK** | 1          |      |
| **MouseGetPos**               | 获取鼠标当前位置                                     | Retrieves the current position of the mouse cursor.          | **OK** | 1          |      |
| **MouseMove**                 | 移动鼠标到指定位置                                   | Moves the mouse cursor to a specified position.              | **OK** | 1          |      |
| **MouseUp**                   | 模拟鼠标释放                                         | Simulates releasing a mouse button.                          | **OK** | 1          |      |
| **MouseWheel**                | 模拟鼠标滚轮滚动                                     | Simulates scrolling the mouse wheel.                         | **OK** | 1          |      |
| **Opt**                       | 设置AutoIt选项                                       | Sets options for AutoItX                                     | **OK** | 1          |      |
| **PixelChecksum**             | 获取屏幕区域的像素校验和                             | Calculates a checksum of a region of pixels on the screen.   | **OK** | 1          |      |
| **PixelGetColor**             | 获取屏幕上指定位置的像素颜色                         | Retrieves the color of a pixel at a specified position.      | **OK** | 1          |      |
| **PixelSearch**               | 在屏幕上搜索指定颜色的像素                           | Searches for a pixel of a specific color in a region of the screen. | **OK** | 1          |      |
| **ProcessClose**              | 关闭进程                                             | Closes a specified process.                                  | **OK** | 1          |      |
| **ProcessExists**             | 检查进程是否存在                                     | Checks if a specified process exists.                        | **OK** | 1          |      |
| **ProcessSetPriority**        | 设置进程的优先级                                     | Sets the priority of a specified process.                    | **OK** | 1          |      |
| **ProcessWait**               | 等待进程的出现                                       | Waits for a specified process to exist.                      | **OK** | 1          |      |
| **ProcessWaitClose**          | 等待进程的结束                                       | Waits for a specified process to close.                      | **OK** | 1          |      |
| **Run**                       | 用于运行外部程序或执行系统命令                       | Runs an external program or opens a document.                | **OK** | 1          |      |
| **RunWait**                   | 运行外部程序并等待其完成                             | Runs an external program and waits for it to complete.       | **OK** | 1          |      |
| **RunAs**                     | 以其他用户的身份运行外部程序                         | Runs an external program with different credentials (as a different user). | **OK** | 1          |      |
| **RunAsWait**                 | 以其他用户的身份运行外部程序并等待其完成             | Runs an external program with different credentials and waits for it to complete. | **OK** | 1          |      |
| **Send**                      | 向活动窗口发送按键输入                               | Sends simulated keystrokes.                                  | **OK** | 1          |      |
| **Shutdown**                  | 关闭或重启系统                                       | Shuts down, restarts, or logs off the computer.              | **OK** | 1          |      |
| **Sleep**                     | 在脚本中加入暂停/延迟                                | Pauses the script for a specified number of milliseconds.    | **OK** | 1          |      |
| **StatusbarGetText**          | 获取状态栏的文本内容                                 | Retrieves the text from the status bar of a window.          | **OK** | 1          |      |
| **StatusbarGetTextByHandle**  | 使用控件句柄获取状态栏的文本内容                     | Retrieves the text from the status bar of a window using its handle. | **OK** | 1          |      |
| **ToolTip**                   | 显示一个提示框，通常用于在屏幕上显示临时的提示信息   | Creates a tooltip with the specified text at the current mouse position or on a specific control. | **OK** | 1          |      |
| **WinActivate**               | 激活指定的窗口                                       | Activates a window by title or window handle.                | **OK** | 1          |      |
| **WinActivateByHandle**       | 使用窗口句柄激活指定的窗口                           | Activates a window using its handle.                         | **OK** | 1          |      |
| **WinActive**                 | 检查指定的窗口是否处于活动状态                       | Checks if a window is currently active by title.             | **OK** | 1          |      |
| **WinActiveByHandle**         | 使用窗口句柄检查指定的窗口是否处于活动状态           | Checks if a window is currently active using its handle.     | **OK** | 1          |      |
| **WinClose**                  | 关闭指定的窗口                                       | Closes a window by title.                                    | **OK** | 1          |      |
| **WinCloseByHandle**          | 使用窗口句柄关闭指定的窗口                           | Closes a window using its handle.                            | **OK** | 1          |      |
| **WinExists**                 | 检查指定的窗口是否存在                               | Checks if a window exists by title.                          | **OK** | 1          |      |
| **WinExistsByHandle**         | 使用窗口句柄检查指定的窗口是否存在                   | Checks if a window exists using its handle.                  | **OK** | 1          |      |
| **WinGetCaretPos**            | 获取当前光标的位置                                   | Retrieves the position of the caret in the active window.    | **OK** | 1          |      |
| **WinGetClassList**           | 获取指定窗口的类名列表                               | Retrieves a list of classes used by a window by title.       | **OK** | 1          |      |
| **WinGetClassListByHandle**   | 使用窗口句柄获取指定窗口的类名列表                   | Retrieves a list of classes used by a window using its handle. | **OK** | 1          |      |
| **WinGetClientSize**          | 获取指定窗口客户区的尺寸                             | Retrieves the client area's size of a window by title.       | **OK** | 1          |      |
| **WinGetClientSizeByHandle**  | 使用窗口句柄获取指定窗口客户区的尺寸                 | Retrieves the client area's size of a window using its handle. | **OK** | 1          |      |
| **WinGetHandle**              | 获取指定窗口的句柄                                   | Retrieves the handle of a window by title.                   | **OK** | 1          |      |
| **WinGetHandleAsText**        | 获取指定窗口的句柄并返回为文本                       | Retrieves the handle of a window by title as text.           | **OK** | 1          |      |
| **WinGetPos**                 | 获取指定窗口的位置和尺寸                             | Retrieves the position and size of a window by title.        | **OK** | 1          |      |
| **WinGetPosByHandle**         | 使用窗口句柄获取指定窗口的位置和尺寸                 | Retrieves the position and size of a window using its handle. | **OK** | 1          |      |
| **WinGetProcess**             | 获取指定窗口的进程ID                                 | Retrieves the process ID of a window by title.               | **OK** | 1          |      |
| **WinGetProcessByHandle**     | 使用窗口句柄获取指定窗口的进程ID                     | Retrieves the process ID of a window using its handle.       | **OK** | 1          |      |
| **WinGetState**               | 获取指定窗口的状态                                   | Retrieves the state of a window by title (minimized, maximized, etc.). | **OK** | 1          |      |
| **WinGetStateByHandle**       | 使用窗口句柄获取指定窗口的状态                       | Retrieves the state of a window using its handle.            | **OK** | 1          |      |
| **WinGetText**                | 获取指定窗口的文本内容                               | Retrieves the text from a window by title.                   | **OK** | 1          |      |
| **WinGetTextByHandle**        | 使用窗口句柄获取指定窗口的文本内容                   | Retrieves the text from a window using its handle.           | **OK** | 1          |      |
| **WinGetTitle**               | 获取指定窗口的标题                                   | Retrieves the title of a window by title.                    | **OK** | 1          |      |
| **WinGetTitleByHandle**       | 使用窗口句柄获取指定窗口的标题                       | Retrieves the title of a window using its handle.            | **OK** | 1          |      |
| **WinKill**                   | 强制关闭指定的窗口                                   | Forces a window to close by title.                           | **OK** | 1          |      |
| **WinKillByHandle**           | 使用窗口句柄强制关闭指定的窗口                       | Forces a window to close using its handle.                   | **OK** | 1          |      |
| **WinMenuSelectItem**         | 选择窗口的菜单项                                     | Selects an item from a menu in a window by title.            | **OK** | 1          |      |
| **WinMenuSelectItemByHandle** | 使用窗口句柄选择窗口的菜单项                         | Selects an item from a menu in a window using its handle.    | **OK** | 1          |      |
| **WinMinimizeAll**            | 最小化所有窗口                                       | Minimizes all windows.                                       | **OK** | 1          |      |
| **WinMinimizeAllUndo**        | 恢复最小化的窗口                                     | Undoes the effect of `AU3_WinMinimizeAll`.                   | **OK** | 1          |      |
| **WinMove**                   | 移动指定窗口到指定位置                               | Moves and/or resizes a window by title.                      | **OK** | 1          |      |
| **WinMoveByHandle**           | 使用窗口句柄移动指定窗口到指定位置                   | Moves and/or resizes a window using its handle.              | **OK** | 1          |      |
| **WinSetOnTop**               | 设置指定窗口在其他窗口之上                           | Sets a window to be always on top by title.                  | **OK** | 1          |      |
| **WinSetOnTopByHandle**       | 使用窗口句柄设置指定窗口在其他窗口之上               | Sets a window to be always on top using its handle.          | **OK** | 1          |      |
| **WinSetState**               | 设置指定窗口的状态（最大化、最小化、正常等）         | Sets the state of a window by title (minimize, maximize, etc.). | **OK** | 1          |      |
| **WinSetStateByHandle**       | 使用窗口句柄设置指定窗口的状态                       | Sets the state of a window using its handle.                 | **OK** | 1          |      |
| **WinSetTitle**               | 设置指定窗口的标题                                   | Sets the title of a window by title.                         | **OK** | 1          |      |
| **WinSetTitleByHandle**       | 使用窗口句柄设置指定窗口的标题                       | Sets the title of a window using its handle.                 | **OK** | 1          |      |
| **WinSetTrans**               | 设置指定窗口的透明度                                 | Sets the transparency level of a window by title.            | **OK** | 1          |      |
| **WinSetTransByHandle**       | 使用窗口句柄设置指定窗口的透明度                     | Sets the transparency level of a window using its handle.    | **OK** | 1          |      |
| **WinWait**                   | 等待指定的窗口出现                                   | Waits for a window to exist by title.                        | **OK** | 1          |      |
| **WinWaitByHandle**           | 使用窗口句柄等待指定的窗口出现                       | Waits for a window to exist using its handle.                | **OK** | 1          |      |
| **WinWaitActive**             | 等待指定的窗口处于活动状态                           | Waits for a window to be active by title.                    | **OK** | 1          |      |
| **WinWaitActiveByHandle**     | 使用窗口句柄等待指定的窗口处于活动状态               | Waits for a window to be active using its handle.            | **OK** | 1          |      |
| **WinWaitClose**              | 等待指定的窗口关闭                                   | Waits for a window to close by title.                        | **OK** | 1          |      |
| **WinWaitCloseByHandle**      | 使用窗口句柄等待指定的窗口关闭                       | Waits for a window to close using its handle.                | **OK** | 1          |      |
| **WinWaitNotActive**          | 等待指定的窗口不处于活动状态                         | Waits for a window to be not active by title.                | **OK** | 1          |      |
| **WinWaitNotActiveByHandle**  | 使用窗口句柄等待指定的窗口不处于活动状态             | Waits for a window to be not active using its handle.        | **OK** | 1          |      |
