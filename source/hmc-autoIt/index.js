"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.MouseUp = exports.MouseMove = exports.MouseGetPos = exports.MouseGetCursor = exports.MouseDown = exports.MouseClickDrag = exports.MouseClick = exports.IsAdmin = exports.DriveMapGet = exports.DriveMapDel = exports.DriveMapAdd = exports.ControlTreeViewByHandle = exports.ControlTreeView = exports.ControlShowByHandle = exports.ControlShow = exports.ControlSetTextByHandle = exports.ControlSetText = exports.ControlSendByHandle = exports.ControlSend = exports.ControlMoveByHandle = exports.ControlMove = exports.ControlHideByHandle = exports.ControlHide = exports.ControlGetTextByHandle = exports.ControlGetText = exports.ControlGetPosByHandle = exports.ControlGetPos = exports.ControlGetHandleAsText = exports.ControlGetHandle = exports.ControlGetFocusByHandle = exports.ControlGetFocus = exports.ControlFocusByHandle = exports.ControlFocus = exports.ControlEnableByHandle = exports.ControlEnable = exports.ControlDisableByHandle = exports.ControlDisable = exports.ControlListViewByHandle = exports.ControlListView = exports.ControlCommandByHandle = exports.ControlCommand = exports.ControlClickByHandle = exports.ControlClick = exports.ClipPut = exports.ClipGet = exports.AutoItSetOption = exports.error = exports.Init = exports.ref = exports.native = void 0;
exports.WinMinimizeAll = exports.WinMenuSelectItemByHandle = exports.WinMenuSelectItem = exports.WinKillByHandle = exports.WinKill = exports.WinGetTitleByHandle = exports.WinGetTitle = exports.WinGetTextByHandle = exports.WinGetText = exports.WinGetStateByHandle = exports.WinGetState = exports.WinGetProcessByHandle = exports.WinGetProcess = exports.WinGetPosByHandle = exports.WinGetPos = exports.WinGetHandleAsText = exports.WinGetHandle = exports.WinGetClientSizeByHandle = exports.WinGetClientSize = exports.WinGetClassListByHandle = exports.WinGetClassList = exports.WinGetCaretPos = exports.WinExistsByHandle = exports.WinExists = exports.WinCloseByHandle = exports.WinClose = exports.WinActiveByHandle = exports.WinActive = exports.WinActivateByHandle = exports.WinActivate = exports.ToolTip = exports.StatusbarGetTextByHandle = exports.StatusbarGetText = exports.Sleep = exports.Shutdown = exports.Send = exports.RunAsWait = exports.RunAs = exports.RunWait = exports.Run = exports.ProcessWaitClose = exports.ProcessWait = exports.ProcessSetPriority = exports.ProcessExists = exports.ProcessClose = exports.PixelSearch = exports.PixelGetColor = exports.PixelChecksum = exports.Opt = exports.MouseWheel = void 0;
exports.WinWaitNotActiveByHandle = exports.WinWaitNotActive = exports.WinWaitCloseByHandle = exports.WinWaitClose = exports.WinWaitActiveByHandle = exports.WinWaitActive = exports.WinWaitByHandle = exports.WinWait = exports.WinSetTransByHandle = exports.WinSetTrans = exports.WinSetTitleByHandle = exports.WinSetTitle = exports.WinSetStateByHandle = exports.WinSetState = exports.WinSetOnTopByHandle = exports.WinSetOnTop = exports.WinMoveByHandle = exports.WinMove = exports.WinMinimizeAllUndo = void 0;
const path = require("path");
const AU3_INTDEFAULT = -2147483647;
const SW_SHOWNORMAL = 1;
/**
 * @zh-cn 静态调用 .dll (注意如果您不知道这个是什么作用 请勿随意调用 参数错误有可能会导致进程崩溃)
 * @en-us Static call to .dll (Note that if you don't know what this does, don't call it at random.  Parameter errors may cause the process to crash)
 */
const get_native = (binPath) => {
    function _require_bin() {
        try {
            if (binPath)
                return require(binPath);
            if (process.arch.match(/^x32|ia32$/))
                return require("./bin/AutoItX_x86.node");
            if (process.arch.match(/^x64$/))
                return require("./bin/AutoItX_x64.node");
        }
        catch (X_X) {
        }
        return null;
    }
    let Native = (process.platform == "win32" ? _require_bin() : null) || (() => {
        let HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
        function fnBool(...args) { console.error(HMCNotPlatform); return false; }
        function fnVoid(...args) { console.error(HMCNotPlatform); return undefined; }
        function fnNull(...args) { console.error(HMCNotPlatform); return null; }
        function fnNum(...args) { console.error(HMCNotPlatform); return 0; }
        function fnStrList(...args) { console.error(HMCNotPlatform); return []; }
        function fnStr(...args) { console.error(HMCNotPlatform); return ''; }
        function fnAnyArr(...args) { console.error(HMCNotPlatform); return []; }
        function fnArrayStr(...args) { console.error(HMCNotPlatform); return '[]'; }
        return {
            Init: fnVoid,
            error: fnNum,
            AutoItSetOption: fnNum,
            ClipGet: fnStr,
            ClipPut: fnVoid,
            ControlClick: fnBool,
            ControlClickByHandle: fnNum,
            ControlCommand: fnStr,
            ControlCommandByHandle: fnStr,
            ControlListView: fnStr,
            ControlListViewByHandle: fnStr,
            ControlDisable: fnBool,
            ControlDisableByHandle: fnBool,
            ControlEnable: fnBool,
            ControlEnableByHandle: fnBool,
            ControlFocus: fnBool,
            ControlFocusByHandle: fnBool,
            ControlGetFocus: fnStr,
            ControlGetFocusByHandle: fnStr,
            ControlGetHandle: fnNum,
            ControlGetHandleAsText: fnStr,
            ControlGetPos: (...arg) => { return { left: 0, top: 0, right: 0, bottom: 0 }; },
            ControlGetPosByHandle: (...arg) => { return { left: 0, top: 0, right: 0, bottom: 0 }; },
            ControlGetText: fnStr,
            ControlGetTextByHandle: fnStr,
            ControlHide: fnBool,
            ControlHideByHandle: fnBool,
            ControlMove: fnBool,
            ControlMoveByHandle: fnBool,
            ControlSend: fnBool,
            ControlSendByHandle: fnBool,
            ControlSetText: fnBool,
            ControlSetTextByHandle: fnBool,
            ControlShow: fnBool,
            ControlShowByHandle: fnBool,
            ControlTreeView: fnStr,
            ControlTreeViewByHandle: fnStr,
            DriveMapAdd: fnStr,
            DriveMapDel: fnBool,
            DriveMapGet: fnStr,
            IsAdmin: fnBool,
            MouseClick: fnVoid,
            MouseClickDrag: fnVoid,
            MouseDown: fnVoid,
            MouseGetCursor: fnNum,
            MouseGetPos: (...arg) => { return { x: 0, y: 0 }; },
            MouseMove: fnNum,
            MouseUp: fnVoid,
            MouseWheel: fnVoid,
            Opt: fnNum,
            PixelChecksum: fnNum,
            PixelGetColor: fnNum,
            PixelSearch: (...arg) => { return { x: 0, y: 0 }; },
            ProcessClose: fnVoid,
            ProcessExists: fnBool,
            ProcessSetPriority: fnBool,
            ProcessWait: fnBool,
            ProcessWaitClose: fnBool,
            Run: fnNum,
            RunWait: fnNum,
            RunAs: fnNum,
            RunAsWait: fnNum,
            Send: fnVoid,
            Shutdown: fnBool,
            Sleep: fnVoid,
            StatusbarGetText: fnStr,
            StatusbarGetTextByHandle: fnStr,
            ToolTip: fnVoid,
            WinActivate: fnBool,
            WinActivateByHandle: fnBool,
            WinActive: fnBool,
            WinActiveByHandle: fnBool,
            WinClose: fnBool,
            WinCloseByHandle: fnBool,
            WinExists: fnBool,
            WinExistsByHandle: fnBool,
            WinGetCaretPos: (...arg) => { return { x: 0, y: 0 }; },
            WinGetClassList: fnStr,
            WinGetClassListByHandle: fnStr,
            WinGetClientSize: (...arg) => { return { left: 0, top: 0, right: 0, bottom: 0 }; },
            WinGetClientSizeByHandle: (...arg) => { return { left: 0, top: 0, right: 0, bottom: 0 }; },
            WinGetHandle: fnNum,
            WinGetHandleAsText: fnStr,
            WinGetPos: (...arg) => { return { left: 0, top: 0, right: 0, bottom: 0 }; },
            WinGetPosByHandle: (...arg) => { return { left: 0, top: 0, right: 0, bottom: 0 }; },
            WinGetProcess: fnVoid,
            WinGetProcessByHandle: fnVoid,
            WinGetState: fnNum,
            WinGetStateByHandle: fnNum,
            WinGetText: fnStr,
            WinGetTextByHandle: fnStr,
            WinGetTitle: fnStr,
            WinGetTitleByHandle: fnStr,
            WinKill: fnBool,
            WinKillByHandle: fnBool,
            WinMenuSelectItem: fnBool,
            WinMenuSelectItemByHandle: fnBool,
            WinMinimizeAll: fnVoid,
            WinMinimizeAllUndo: fnVoid,
            WinMove: fnVoid,
            WinMoveByHandle: fnVoid,
            WinSetOnTop: fnVoid,
            WinSetOnTopByHandle: fnVoid,
            WinSetState: fnVoid,
            WinSetStateByHandle: fnVoid,
            WinSetTitle: fnVoid,
            WinSetTitleByHandle: fnVoid,
            WinSetTrans: fnBool,
            WinSetTransByHandle: fnBool,
            WinWait: fnBool,
            WinWaitByHandle: fnBool,
            WinWaitActive: fnBool,
            WinWaitActiveByHandle: fnBool,
            WinWaitClose: fnBool,
            WinWaitCloseByHandle: fnBool,
            WinWaitNotActive: fnBool,
            WinWaitNotActiveByHandle: fnBool,
        };
    })();
    return Native;
};
exports.native = get_native();
exports.ref = {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str) {
        return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
    },
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool) {
        return bool ? true : false;
    },
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str) {
        return String(Str || "");
    },
    /**
     * 格式化数字为int(强制)
     * @param Num
     * @returns
     */
    int(Num) {
        if (!Num)
            return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num === null || Num === void 0 ? void 0 : Num.valueOf();
        }
        // 取整
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num))
            return Num;
        // true == 1
        if (Num && typeof Num == "boolean")
            Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean")
            Num = 0;
        if (Num >= Infinity) {
            Num = 999999999999999;
        }
        if (Num <= -Infinity) {
            Num = -999999999999999;
        }
        return Num;
    },
    /**
     * 文本数组
     * @param array
     * @returns
     */
    stringArray(array) {
        let dataList = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(this.string(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(this.string(cout));
            }
        }
        return dataList;
    },
    /**
     * 文本数组
     * @param array
     * @returns
     */
    intArray(array) {
        let dataList = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(this.int(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(this.int(cout));
            }
        }
        return dataList;
    },
    /**
     * 拼合buff片段
     * @param buffList
     * @returns
     */
    concatBuff(buffList) {
        let buffSize = 0;
        for (let index = 0; index < buffList.length; index++) {
            const buff = buffList[index];
            buffSize = buffSize + buff.byteLength;
        }
        let ResponseData = Buffer.concat([...buffList], buffSize);
        return ResponseData;
    },
};
/**
* @zh-cn 初始化AutoItX，通常在开始使用AutoItX函数之前调用
* @en-us Initializes the AutoItX library.
* @link https://documentation.help/AutoItX/Init.htm
*/
function Init() {
    return exports.native.Init();
}
exports.Init = Init;
/**
* @zh-cn 获取上一次AutoItX函数调用返回的错误代码
* @en-us Retrieves the error code from the last AutoItX function call.
* @link https://documentation.help/AutoItX/error.htm
*/
function error() {
    return exports.native.error();
}
exports.error = error;
/**
* @zh-cn 设置AutoIt的选项，可以用来配置AutoIt的一些行为
* @en-us Sets various options for AutoItX, such as timeout and behavior.
* @link https://documentation.help/AutoItX/AutoItSetOption.htm
* @param Option
* @param nValue
*/
function AutoItSetOption(Option, nValue) {
    return exports.native.AutoItSetOption(exports.ref.string(typeof Option == "undefined" ? "" : Option), exports.ref.int(typeof nValue == "undefined" ? 0 : nValue));
}
exports.AutoItSetOption = AutoItSetOption;
/**
* @zh-cn 获取剪贴板的内容
* @en-us Retrieves the content of the Windows clipboard.
* @link https://documentation.help/AutoItX/ClipGet.htm
*/
function ClipGet() {
    return exports.native.ClipGet();
}
exports.ClipGet = ClipGet;
/**
* @zh-cn 将文本放入剪贴板
* @en-us Puts text into the Windows clipboard.
* @link https://documentation.help/AutoItX/ClipPut.htm
* @param intput
*/
function ClipPut(intput) {
    return exports.native.ClipPut(exports.ref.string(typeof intput == "undefined" ? "" : intput));
}
exports.ClipPut = ClipPut;
/**
* @zh-cn 模拟控件的点击操作
* @en-us Simulates a mouse click on a specified control (button, checkbox, etc.) in a window.
* @link https://documentation.help/AutoItX/ControlClick.htm
* @param szTitle
* @param szText
* @param szControl
* @param szButton
* @default "left"
* @param nNumClicks
* @default 1
* @param nX x (left To Right)
* @default AU3_INTDEFAULT
* @param nY y (top To Bottom)
* @default AU3_INTDEFAULT
*/
function ControlClick(szTitle, szText, szControl, szButton = "left", nNumClicks = 1, nX = AU3_INTDEFAULT, nY = AU3_INTDEFAULT) {
    return exports.native.ControlClick(exports.ref.string(typeof szTitle == "undefined" ? "" : szTitle), exports.ref.string(typeof szText == "undefined" ? "" : szText), exports.ref.string(typeof szControl == "undefined" ? "" : szControl), exports.ref.string(typeof szButton == "undefined" ? "left" : szButton), exports.ref.int(typeof nNumClicks == "undefined" ? 1 : nNumClicks), exports.ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX), exports.ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY));
}
exports.ControlClick = ControlClick;
/**
* @zh-cn 使用控件句柄模拟控件的点击操作
* @en-us Same as `AU3_ControlClick` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlClick.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
* @param szButton
* @default "left"
* @param nNumClicks
* @default 1
* @param nX x (left To Right)
* @default AU3_INTDEFAULT
* @param nY y (top To Bottom)
* @default AU3_INTDEFAULT
*/
function ControlClickByHandle(hWnd, hCtrl, szButton = "left", nNumClicks = 1, nX = AU3_INTDEFAULT, nY = AU3_INTDEFAULT) {
    return exports.native.ControlClickByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof szButton == "undefined" ? "left" : szButton), exports.ref.int(typeof nNumClicks == "undefined" ? 1 : nNumClicks), exports.ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX), exports.ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY));
}
exports.ControlClickByHandle = ControlClickByHandle;
/**
* @zh-cn 发送命令给控件，比如选择列表中的项、设置复选框状态等
* @en-us Sends a command to a control (button, checkbox, radio button, etc.) in a window.
* @link https://documentation.help/AutoItX/ControlCommand.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
* @param Command 命令
* @param Extra
* @default ""
*/
function ControlCommand(Title, Text, Control, Command, Extra = "") {
    return exports.native.ControlCommand(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra == "undefined" ? "" : Extra));
}
exports.ControlCommand = ControlCommand;
/**
* @zh-cn 使用控件句柄发送命令给控件
* @en-us Same as `AU3_ControlCommand` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlCommand.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
* @param Command 命令
* @param Extra
* @default ""
*/
function ControlCommandByHandle(hWnd, hCtrl, Command, Extra = "") {
    return exports.native.ControlCommandByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra == "undefined" ? "" : Extra));
}
exports.ControlCommandByHandle = ControlCommandByHandle;
/**
* @zh-cn 操作ListView控件
* @en-us Sends commands to a ListView control (such as list items selection) in a window.
* @link https://documentation.help/AutoItX/ControlListView.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
* @param Command 命令
* @param Extra1
* @param Extra2
*/
function ControlListView(Title, Text, Control, Command, Extra1, Extra2) {
    return exports.native.ControlListView(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra1 == "undefined" ? "" : Extra1), exports.ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}
exports.ControlListView = ControlListView;
/**
* @zh-cn 使用控件句柄操作ListView控件
* @en-us Same as `AU3_ControlListView` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlListView.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
* @param Command 命令
* @param Extra1
* @param Extra2
*/
function ControlListViewByHandle(hWnd, hCtrl, Command, Extra1, Extra2) {
    return exports.native.ControlListViewByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra1 == "undefined" ? "" : Extra1), exports.ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}
exports.ControlListViewByHandle = ControlListViewByHandle;
/**
* @zh-cn 禁用控件
* @en-us Disables a control in a window.
* @link https://documentation.help/AutoItX/ControlDisable.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/
function ControlDisable(Title, Text, Control) {
    return exports.native.ControlDisable(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlDisable = ControlDisable;
/**
* @zh-cn 使用控件句柄禁用控件
* @en-us Same as `AU3_ControlDisable` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlDisable.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
*/
function ControlDisableByHandle(hWnd, hCtrl) {
    return exports.native.ControlDisableByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlDisableByHandle = ControlDisableByHandle;
/**
* @zh-cn 启用控件
* @en-us Enables a control in a window.
* @link https://documentation.help/AutoItX/ControlEnable.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/
function ControlEnable(Title, Text, Control) {
    return exports.native.ControlEnable(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlEnable = ControlEnable;
/**
* @zh-cn 使用控件句柄启用控件
* @en-us Same as `AU3_ControlEnable` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlEnable.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
*/
function ControlEnableByHandle(hWnd, hCtrl) {
    return exports.native.ControlEnableByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlEnableByHandle = ControlEnableByHandle;
/**
* @zh-cn 将焦点设置到控件上
* @en-us Sets focus to a control in a window.
* @link https://documentation.help/AutoItX/ControlFocus.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/
function ControlFocus(Title, Text, Control) {
    return exports.native.ControlFocus(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlFocus = ControlFocus;
/**
* @zh-cn 使用控件句柄将焦点设置到控件上
* @en-us Same as `AU3_ControlFocus` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlFocus.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
*/
function ControlFocusByHandle(hWnd, hCtrl) {
    return exports.native.ControlFocusByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlFocusByHandle = ControlFocusByHandle;
/**
* @zh-cn 获取当前具有焦点的控件句柄
* @en-us Retrieves the handle of the control with focus.
* @link https://documentation.help/AutoItX/ControlGetFocus.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function ControlGetFocus(Title, Text = "") {
    return exports.native.ControlGetFocus(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.ControlGetFocus = ControlGetFocus;
/**
* @zh-cn 使用控件句柄获取当前具有焦点的控件句柄
* @en-us Same as `AU3_ControlGetFocus` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlGetFocus.htm
* @param hWnd 窗口句柄数字
*/
function ControlGetFocusByHandle(hWnd) {
    return exports.native.ControlGetFocusByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.ControlGetFocusByHandle = ControlGetFocusByHandle;
/**
* @zh-cn 获取控件句柄
* @en-us Retrieves the handle of a control in a window.
* @link https://documentation.help/AutoItX/ControlGetHandle.htm
* @param hWnd 窗口句柄数字
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/
function ControlGetHandle(hWnd, Control) {
    return exports.native.ControlGetHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlGetHandle = ControlGetHandle;
/**
* @zh-cn 获取控件句柄并返回为文本
* @en-us Retrieves the handle of a control in a window as text.
* @link https://documentation.help/AutoItX/ControlGetHandleAsText.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/
function ControlGetHandleAsText(Title, Text, Control) {
    return exports.native.ControlGetHandleAsText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlGetHandleAsText = ControlGetHandleAsText;
/**
* @zh-cn 获取控件的位置和尺寸
* @en-us Retrieves the position and size of a control in a window.
* @link https://documentation.help/AutoItX/ControlGetPos.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/
function ControlGetPos(Title, Text, Control) {
    return exports.native.ControlGetPos(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlGetPos = ControlGetPos;
/**
* @zh-cn 使用控件句柄获取控件的位置和尺寸
* @en-us Same as `AU3_ControlGetPos` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlGetPos.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
*/
function ControlGetPosByHandle(hWnd, hCtrl) {
    return exports.native.ControlGetPosByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlGetPosByHandle = ControlGetPosByHandle;
/**
* @zh-cn 获取控件的文本内容
* @en-us Retrieves the text from a control in a window.
* @link https://documentation.help/AutoItX/ControlGetText.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/
function ControlGetText(Title, Text, Control) {
    return exports.native.ControlGetText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlGetText = ControlGetText;
/**
* @zh-cn 使用控件句柄获取控件的文本内容
* @en-us Same as `AU3_ControlGetText` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlGetText.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
*/
function ControlGetTextByHandle(hWnd, hCtrl) {
    return exports.native.ControlGetTextByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlGetTextByHandle = ControlGetTextByHandle;
/**
* @zh-cn 隐藏控件
* @en-us Hides a control in a window.
* @link https://documentation.help/AutoItX/ControlHide.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/
function ControlHide(Title, Text, Control) {
    return exports.native.ControlHide(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlHide = ControlHide;
/**
* @zh-cn 使用控件句柄隐藏控件
* @en-us Same as `AU3_ControlHide` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlHide.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
*/
function ControlHideByHandle(hWnd, hCtrl) {
    return exports.native.ControlHideByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlHideByHandle = ControlHideByHandle;
/**
* @zh-cn 移动控件到指定位置
* @en-us Moves a control within a window.
* @link https://documentation.help/AutoItX/ControlMove.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
* @param nX x (left To Right)
* @param nY y (top To Bottom)
* @param nWidth 宽度
* @default -1
* @param nHeight 高度
* @default -1
*/
function ControlMove(Title, Text, Control, nX, nY, nWidth = -1, nHeight = -1) {
    return exports.native.ControlMove(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY), exports.ref.int(typeof nWidth == "undefined" ? -1 : nWidth), exports.ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}
exports.ControlMove = ControlMove;
/**
* @zh-cn 使用控件句柄移动控件到指定位置
* @en-us Same as `AU3_ControlMove` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlMove.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
* @param nX x (left To Right)
* @param nY y (top To Bottom)
* @param nWidth 宽度
* @default -1
* @param nHeight 高度
* @default -1
*/
function ControlMoveByHandle(hWnd, hCtrl, nX, nY, nWidth = -1, nHeight = -1) {
    return exports.native.ControlMoveByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY), exports.ref.int(typeof nWidth == "undefined" ? -1 : nWidth), exports.ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}
exports.ControlMoveByHandle = ControlMoveByHandle;
/**
* @zh-cn 向控件发送按键输入
* @en-us Sends keystrokes to a control in a window.
* @link https://documentation.help/AutoItX/ControlSend.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
* @param SendText 发送的文本内容
* @param nMode
* @default 0
*/
function ControlSend(Title, Text, Control, SendText, nMode = 0) {
    return exports.native.ControlSend(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.string(typeof SendText == "undefined" ? "" : SendText), exports.ref.int(typeof nMode == "undefined" ? 0 : nMode));
}
exports.ControlSend = ControlSend;
/**
* @zh-cn 使用控件句柄向控件发送按键输入
* @en-us Same as `AU3_ControlSend` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlSend.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
* @param SendText 发送的文本内容
* @param nMode
* @default 0
*/
function ControlSendByHandle(hWnd, hCtrl, SendText, nMode = 0) {
    return exports.native.ControlSendByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof SendText == "undefined" ? "" : SendText), exports.ref.int(typeof nMode == "undefined" ? 0 : nMode));
}
exports.ControlSendByHandle = ControlSendByHandle;
/**
* @zh-cn 设置控件的文本内容
* @en-us Sets the text of a control in a window.
* @link https://documentation.help/AutoItX/ControlSetText.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
* @param ControlText
*/
function ControlSetText(Title, Text, Control, ControlText) {
    return exports.native.ControlSetText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.string(typeof ControlText == "undefined" ? "" : ControlText));
}
exports.ControlSetText = ControlSetText;
/**
* @zh-cn 使用控件句柄设置控件的文本内容
* @en-us Sets the text of a control in a window using its handle.
* @link https://documentation.help/AutoItX/ControlSetText.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
* @param SendText 发送的文本内容
*/
function ControlSetTextByHandle(hWnd, hCtrl, SendText) {
    return exports.native.ControlSetTextByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof SendText == "undefined" ? "" : SendText));
}
exports.ControlSetTextByHandle = ControlSetTextByHandle;
/**
* @zh-cn 显示控件
* @en-us Shows a control in a window.
* @link https://documentation.help/AutoItX/ControlShow.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/
function ControlShow(Title, Text, Control) {
    return exports.native.ControlShow(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlShow = ControlShow;
/**
* @zh-cn 使用控件句柄显示控件
* @en-us Shows a control in a window using its handle.
* @link https://documentation.help/AutoItX/ControlShow.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
*/
function ControlShowByHandle(hWnd, hCtrl) {
    return exports.native.ControlShowByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlShowByHandle = ControlShowByHandle;
/**
* @zh-cn 操作TreeView控件
* @en-us Sends commands to a TreeView control in a window.
* @link https://documentation.help/AutoItX/ControlTreeView.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
* @param Command 命令
* @param Extra1
* @param Extra2
*/
function ControlTreeView(Title, Text, Control, Command, Extra1, Extra2) {
    return exports.native.ControlTreeView(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra1 == "undefined" ? "" : Extra1), exports.ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}
exports.ControlTreeView = ControlTreeView;
/**
* @zh-cn 使用控件句柄操作TreeView控件
* @en-us Same as `AU3_ControlTreeView` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlTreeView.htm
* @param hWnd 窗口句柄数字
* @param hCtrl
* @param Command 命令
* @param Extra1
* @param Extra2
*/
function ControlTreeViewByHandle(hWnd, hCtrl, Command, Extra1, Extra2) {
    return exports.native.ControlTreeViewByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra1 == "undefined" ? "" : Extra1), exports.ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}
exports.ControlTreeViewByHandle = ControlTreeViewByHandle;
/**
* @zh-cn 映射本地驱动器到网络共享路径
* @en-us Maps a network drive.
* @link https://documentation.help/AutoItX/DriveMapAdd.htm
* @param Device
* @param Share
* @param nFlags
* @param User
* @default ""
* @param Pwd
* @default ""
*/
function DriveMapAdd(Device, Share, nFlags, User = "", Pwd = "") {
    return exports.native.DriveMapAdd(exports.ref.string(typeof Device == "undefined" ? "" : Device), exports.ref.string(typeof Share == "undefined" ? "" : Share), exports.ref.int(typeof nFlags == "undefined" ? 0 : nFlags), exports.ref.string(typeof User == "undefined" ? "" : User), exports.ref.string(typeof Pwd == "undefined" ? "" : Pwd));
}
exports.DriveMapAdd = DriveMapAdd;
/**
* @zh-cn 取消驱动器映射
* @en-us Unmaps a network drive.
* @link https://documentation.help/AutoItX/DriveMapDel.htm
* @param Device
*/
function DriveMapDel(Device) {
    return exports.native.DriveMapDel(exports.ref.string(typeof Device == "undefined" ? "" : Device));
}
exports.DriveMapDel = DriveMapDel;
/**
* @zh-cn 获取驱动器映射的信息
* @en-us Retrieves the mapping of a network drive.
* @link https://documentation.help/AutoItX/DriveMapGet.htm
* @param Device
*/
function DriveMapGet(Device) {
    return exports.native.DriveMapGet(exports.ref.string(typeof Device == "undefined" ? "" : Device));
}
exports.DriveMapGet = DriveMapGet;
/**
* @zh-cn 检查当前用户是否有管理员权限
* @en-us Checks if the current process is running with administrative privileges.
* @link https://documentation.help/AutoItX/IsAdmin.htm
*/
function IsAdmin() {
    return exports.native.IsAdmin();
}
exports.IsAdmin = IsAdmin;
/**
* @zh-cn 模拟鼠标点击
* @en-us Simulates a mouse click at the current cursor position.
* @link https://documentation.help/AutoItX/MouseClick.htm
* @param Button
* @default "LEFT"
* @param nX x (left To Right)
* @default AU3_INTDEFAULT
* @param nY y (top To Bottom)
* @default AU3_INTDEFAULT
* @param nClicks
* @default 1
* @param nSpeed
* @default -1
*/
function MouseClick(Button = "LEFT", nX = AU3_INTDEFAULT, nY = AU3_INTDEFAULT, nClicks = 1, nSpeed = -1) {
    return exports.native.MouseClick(exports.ref.string(typeof Button == "undefined" ? "LEFT" : Button), exports.ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX), exports.ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY), exports.ref.int(typeof nClicks == "undefined" ? 1 : nClicks), exports.ref.int(typeof nSpeed == "undefined" ? -1 : nSpeed));
}
exports.MouseClick = MouseClick;
/**
* @zh-cn 模拟鼠标点击并拖动
* @en-us Simulates dragging the mouse between two points.
* @link https://documentation.help/AutoItX/MouseClickDrag.htm
* @param Button
* @param nX1
* @param nY1
* @param nX2
* @param nY2
* @param nSpeed
* @default -1
*/
function MouseClickDrag(Button, nX1, nY1, nX2, nY2, nSpeed = -1) {
    return exports.native.MouseClickDrag(exports.ref.string(typeof Button == "undefined" ? "" : Button), exports.ref.int(typeof nX1 == "undefined" ? 0 : nX1), exports.ref.int(typeof nY1 == "undefined" ? 0 : nY1), exports.ref.int(typeof nX2 == "undefined" ? 0 : nX2), exports.ref.int(typeof nY2 == "undefined" ? 0 : nY2), exports.ref.int(typeof nSpeed == "undefined" ? -1 : nSpeed));
}
exports.MouseClickDrag = MouseClickDrag;
/**
* @zh-cn 模拟鼠标按下
* @en-us Simulates pressing a mouse button.
* @link https://documentation.help/AutoItX/MouseDown.htm
* @param Button
* @default "LEFT"
*/
function MouseDown(Button = "LEFT") {
    return exports.native.MouseDown(exports.ref.string(typeof Button == "undefined" ? "LEFT" : Button));
}
exports.MouseDown = MouseDown;
/**
* @zh-cn 获取鼠标当前的光标样式
* @en-us Retrieves the mouse cursor's current shape.
* @link https://documentation.help/AutoItX/MouseGetCursor.htm
*/
function MouseGetCursor() {
    return exports.native.MouseGetCursor();
}
exports.MouseGetCursor = MouseGetCursor;
/**
* @zh-cn 获取鼠标当前位置
* @en-us Retrieves the current position of the mouse cursor.
* @link https://documentation.help/AutoItX/MouseGetPos.htm
*/
function MouseGetPos() {
    return exports.native.MouseGetPos();
}
exports.MouseGetPos = MouseGetPos;
/**
* @zh-cn 移动鼠标到指定位置
* @en-us Moves the mouse cursor to a specified position.
* @link https://documentation.help/AutoItX/MouseMove.htm
* @param nX x (left To Right)
* @param nY y (top To Bottom)
* @param nSpeed
* @default -1
*/
function MouseMove(nX, nY, nSpeed = -1) {
    return exports.native.MouseMove(exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY), exports.ref.int(typeof nSpeed == "undefined" ? -1 : nSpeed));
}
exports.MouseMove = MouseMove;
/**
* @zh-cn 模拟鼠标释放
* @en-us Simulates releasing a mouse button.
* @link https://documentation.help/AutoItX/MouseUp.htm
* @param Button
* @default "LEFT"
*/
function MouseUp(Button = "LEFT") {
    return exports.native.MouseUp(exports.ref.string(typeof Button == "undefined" ? "LEFT" : Button));
}
exports.MouseUp = MouseUp;
/**
* @zh-cn 模拟鼠标滚轮滚动
* @en-us Simulates scrolling the mouse wheel.
* @link https://documentation.help/AutoItX/MouseWheel.htm
* @param Direction
* @param nClicks
*/
function MouseWheel(Direction, nClicks) {
    return exports.native.MouseWheel(exports.ref.string(typeof Direction == "undefined" ? "" : Direction), exports.ref.int(typeof nClicks == "undefined" ? 0 : nClicks));
}
exports.MouseWheel = MouseWheel;
/**
* @zh-cn 设置AutoIt选项
* @en-us Sets options for AutoItX
* @link https://documentation.help/AutoItX/Opt.htm
* @param Option
* @param nValue
*/
function Opt(Option, nValue) {
    return exports.native.Opt(exports.ref.string(typeof Option == "undefined" ? "" : Option), exports.ref.int(typeof nValue == "undefined" ? 0 : nValue));
}
exports.Opt = Opt;
/**
* @zh-cn 获取屏幕区域的像素校验和
* @en-us Calculates a checksum of a region of pixels on the screen.
* @link https://documentation.help/AutoItX/PixelChecksum.htm
* @param lpRect 位置
* @param nStep
* @default 1
*/
function PixelChecksum(lpRect, nStep = 1) {
    return exports.native.PixelChecksum({
        left: exports.ref.int(lpRect.left),
        top: exports.ref.int(lpRect.top),
        right: exports.ref.int(lpRect.right),
        bottom: exports.ref.int(lpRect.bottom)
    }, exports.ref.int(typeof nStep == "undefined" ? 1 : nStep));
}
exports.PixelChecksum = PixelChecksum;
/**
* @zh-cn 获取屏幕上指定位置的像素颜色
* @en-us Retrieves the color of a pixel at a specified position.
* @link https://documentation.help/AutoItX/PixelGetColor.htm
* @param nX x (left To Right)
* @param nY y (top To Bottom)
*/
function PixelGetColor(nX, nY) {
    return exports.native.PixelGetColor(exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY));
}
exports.PixelGetColor = PixelGetColor;
/**
* @zh-cn 在屏幕上搜索指定颜色的像素
* @en-us Searches for a pixel of a specific color in a region of the screen.
* @link https://documentation.help/AutoItX/PixelSearch.htm
* @param lpRect 位置
* @param nCol
* @param nVar
* @default 0
* @param nStep
* @default 1
*/
function PixelSearch(lpRect, nCol, nVar = 0, nStep = 1) {
    return exports.native.PixelSearch({
        left: exports.ref.int(lpRect.left),
        top: exports.ref.int(lpRect.top),
        right: exports.ref.int(lpRect.right),
        bottom: exports.ref.int(lpRect.bottom)
    }, exports.ref.int(typeof nCol == "undefined" ? 0 : nCol), exports.ref.int(typeof nVar == "undefined" ? 0 : nVar), exports.ref.int(typeof nStep == "undefined" ? 1 : nStep));
}
exports.PixelSearch = PixelSearch;
/**
* @zh-cn 关闭进程
* @en-us Closes a specified process.
* @link https://documentation.help/AutoItX/ProcessClose.htm
* @param Process 进程名称
*/
function ProcessClose(Process) {
    return exports.native.ProcessClose(exports.ref.string(typeof Process == "undefined" ? "" : Process));
}
exports.ProcessClose = ProcessClose;
/**
* @zh-cn 检查进程是否存在
* @en-us Checks if a specified process exists.
* @link https://documentation.help/AutoItX/ProcessExists.htm
* @param Process 进程名称
*/
function ProcessExists(Process) {
    return exports.native.ProcessExists(exports.ref.string(typeof Process == "undefined" ? "" : Process));
}
exports.ProcessExists = ProcessExists;
/**
* @zh-cn 设置进程的优先级
* @en-us Sets the priority of a specified process.
* @link https://documentation.help/AutoItX/ProcessSetPriority.htm
* @param Process 进程名称
* @param nPriority
*/
function ProcessSetPriority(Process, nPriority) {
    return exports.native.ProcessSetPriority(exports.ref.string(typeof Process == "undefined" ? "" : Process), exports.ref.int(typeof nPriority == "undefined" ? 0 : nPriority));
}
exports.ProcessSetPriority = ProcessSetPriority;
/**
* @zh-cn 等待进程的出现
* @en-us Waits for a specified process to exist.
* @link https://documentation.help/AutoItX/ProcessWait.htm
* @param Process 进程名称
* @param nTimeout
* @default 0
*/
function ProcessWait(Process, nTimeout = 0) {
    return exports.native.ProcessWait(exports.ref.string(typeof Process == "undefined" ? "" : Process), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.ProcessWait = ProcessWait;
/**
* @zh-cn 等待进程的结束
* @en-us Waits for a specified process to close.
* @link https://documentation.help/AutoItX/ProcessWaitClose.htm
* @param Process 进程名称
* @param nTimeout
* @default 0
*/
function ProcessWaitClose(Process, nTimeout = 0) {
    return exports.native.ProcessWaitClose(exports.ref.string(typeof Process == "undefined" ? "" : Process), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.ProcessWaitClose = ProcessWaitClose;
/**
* @zh-cn 用于运行外部程序或执行系统命令
* @en-us Runs an external program or opens a document.
* @link https://documentation.help/AutoItX/Run.htm
* @param Program
* @param Dir
* @default ""
* @param nShowFlag
* @default SW_SHOWNORMAL
*/
function Run(Program, Dir = "", nShowFlag = SW_SHOWNORMAL) {
    return exports.native.Run(exports.ref.string(typeof Program == "undefined" ? "" : Program), exports.ref.string(typeof Dir == "undefined" ? "" : Dir), exports.ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}
exports.Run = Run;
/**
* @zh-cn 运行外部程序并等待其完成
* @en-us Runs an external program and waits for it to complete.
* @link https://documentation.help/AutoItX/RunWait.htm
* @param Program
* @param Dir
* @default ""
* @param nShowFlag
* @default SW_SHOWNORMAL
*/
function RunWait(Program, Dir = "", nShowFlag = SW_SHOWNORMAL) {
    return exports.native.RunWait(exports.ref.string(typeof Program == "undefined" ? "" : Program), exports.ref.string(typeof Dir == "undefined" ? "" : Dir), exports.ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}
exports.RunWait = RunWait;
/**
* @zh-cn 以其他用户的身份运行外部程序
* @en-us Runs an external program with different credentials (as a different user).
* @link https://documentation.help/AutoItX/RunAs.htm
* @param User
* @param Domain
* @param Password
* @param nLogonFlag
* @param Program
* @param Dir
* @default ""
* @param nShowFlag
* @default SW_SHOWNORMAL
*/
function RunAs(User, Domain, Password, nLogonFlag, Program, Dir = "", nShowFlag = SW_SHOWNORMAL) {
    return exports.native.RunAs(exports.ref.string(typeof User == "undefined" ? "" : User), exports.ref.string(typeof Domain == "undefined" ? "" : Domain), exports.ref.string(typeof Password == "undefined" ? "" : Password), exports.ref.int(typeof nLogonFlag == "undefined" ? 0 : nLogonFlag), exports.ref.string(typeof Program == "undefined" ? "" : Program), exports.ref.string(typeof Dir == "undefined" ? "" : Dir), exports.ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}
exports.RunAs = RunAs;
/**
* @zh-cn 以其他用户的身份运行外部程序并等待其完成
* @en-us Runs an external program with different credentials and waits for it to complete.
* @link https://documentation.help/AutoItX/RunAsWait.htm
* @param User
* @param Domain
* @param Password
* @param nLogonFlag
* @param Program
* @param Dir
* @default ""
* @param nShowFlag
* @default SW_SHOWNORMAL
*/
function RunAsWait(User, Domain, Password, nLogonFlag, Program, Dir = "", nShowFlag = SW_SHOWNORMAL) {
    return exports.native.RunAsWait(exports.ref.string(typeof User == "undefined" ? "" : User), exports.ref.string(typeof Domain == "undefined" ? "" : Domain), exports.ref.string(typeof Password == "undefined" ? "" : Password), exports.ref.int(typeof nLogonFlag == "undefined" ? 0 : nLogonFlag), exports.ref.string(typeof Program == "undefined" ? "" : Program), exports.ref.string(typeof Dir == "undefined" ? "" : Dir), exports.ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}
exports.RunAsWait = RunAsWait;
/**
* @zh-cn 向活动窗口发送按键输入
* @en-us Sends simulated keystrokes.
* @link https://documentation.help/AutoItX/Send.htm
* @param SendText 发送的文本内容
* @param nMode
* @default 0
*/
function Send(SendText, nMode = 0) {
    return exports.native.Send(exports.ref.string(typeof SendText == "undefined" ? "" : SendText), exports.ref.int(typeof nMode == "undefined" ? 0 : nMode));
}
exports.Send = Send;
/**
* @zh-cn 关闭或重启系统
* @en-us Shuts down, restarts, or logs off the computer.
* @link https://documentation.help/AutoItX/Shutdown.htm
* @param nFlags
*/
function Shutdown(nFlags) {
    return exports.native.Shutdown(exports.ref.int(typeof nFlags == "undefined" ? 0 : nFlags));
}
exports.Shutdown = Shutdown;
/**
* @zh-cn 在脚本中加入暂停/延迟
* @en-us Pauses the script for a specified number of milliseconds.
* @link https://documentation.help/AutoItX/Sleep.htm
* @param nMilliseconds
*/
function Sleep(nMilliseconds) {
    return exports.native.Sleep(exports.ref.int(typeof nMilliseconds == "undefined" ? 0 : nMilliseconds));
}
exports.Sleep = Sleep;
/**
* @zh-cn 获取状态栏的文本内容
* @en-us Retrieves the text from the status bar of a window.
* @link https://documentation.help/AutoItX/StatusbarGetText.htm
* @param Title 窗口标题
* @default ""
* @param Text 窗口/控件文本
* @default ""
* @param nPart
* @default 1
*/
function StatusbarGetText(Title = "", Text = "", nPart = 1) {
    return exports.native.StatusbarGetText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nPart == "undefined" ? 1 : nPart));
}
exports.StatusbarGetText = StatusbarGetText;
/**
* @zh-cn 使用控件句柄获取状态栏的文本内容
* @en-us Retrieves the text from the status bar of a window using its handle.
* @link https://documentation.help/AutoItX/StatusbarGetText.htm
* @param hWnd 窗口句柄数字
* @param nPart
* @default 1
*/
function StatusbarGetTextByHandle(hWnd, nPart = 1) {
    return exports.native.StatusbarGetTextByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nPart == "undefined" ? 1 : nPart));
}
exports.StatusbarGetTextByHandle = StatusbarGetTextByHandle;
/**
* @zh-cn 显示一个提示框，通常用于在屏幕上显示临时的提示信息
* @en-us Creates a tooltip with the specified text at the current mouse position or on a specific control.
* @link https://documentation.help/AutoItX/ToolTip.htm
* @param Tip
* @param nX x (left To Right)
* @default AU3_INTDEFAULT
* @param nY y (top To Bottom)
* @default AU3_INTDEFAULT
*/
function ToolTip(Tip, nX = AU3_INTDEFAULT, nY = AU3_INTDEFAULT) {
    return exports.native.ToolTip(exports.ref.string(typeof Tip == "undefined" ? "" : Tip), exports.ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX), exports.ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY));
}
exports.ToolTip = ToolTip;
/**
* @zh-cn 激活指定的窗口
* @en-us Activates a window by title or window handle.
* @link https://documentation.help/AutoItX/WinActivate.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinActivate(Title, Text = "") {
    return exports.native.WinActivate(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinActivate = WinActivate;
/**
* @zh-cn 使用窗口句柄激活指定的窗口
* @en-us Activates a window using its handle.
* @link https://documentation.help/AutoItX/WinActivate.htm
* @param hWnd 窗口句柄数字
*/
function WinActivateByHandle(hWnd) {
    return exports.native.WinActivateByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinActivateByHandle = WinActivateByHandle;
/**
* @zh-cn 检查指定的窗口是否处于活动状态
* @en-us Checks if a window is currently active by title.
* @link https://documentation.help/AutoItX/WinActive.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinActive(Title, Text = "") {
    return exports.native.WinActive(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinActive = WinActive;
/**
* @zh-cn 使用窗口句柄检查指定的窗口是否处于活动状态
* @en-us Checks if a window is currently active using its handle.
* @link https://documentation.help/AutoItX/WinActive.htm
* @param hWnd 窗口句柄数字
*/
function WinActiveByHandle(hWnd) {
    return exports.native.WinActiveByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinActiveByHandle = WinActiveByHandle;
/**
* @zh-cn 关闭指定的窗口
* @en-us Closes a window by title.
* @link https://documentation.help/AutoItX/WinClose.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinClose(Title, Text = "") {
    return exports.native.WinClose(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinClose = WinClose;
/**
* @zh-cn 使用窗口句柄关闭指定的窗口
* @en-us Closes a window using its handle.
* @link https://documentation.help/AutoItX/WinClose.htm
* @param hWnd 窗口句柄数字
*/
function WinCloseByHandle(hWnd) {
    return exports.native.WinCloseByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinCloseByHandle = WinCloseByHandle;
/**
* @zh-cn 检查指定的窗口是否存在
* @en-us Checks if a window exists by title.
* @link https://documentation.help/AutoItX/WinExists.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinExists(Title, Text = "") {
    return exports.native.WinExists(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinExists = WinExists;
/**
* @zh-cn 使用窗口句柄检查指定的窗口是否存在
* @en-us Checks if a window exists using its handle.
* @link https://documentation.help/AutoItX/WinExists.htm
* @param hWnd 窗口句柄数字
*/
function WinExistsByHandle(hWnd) {
    return exports.native.WinExistsByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinExistsByHandle = WinExistsByHandle;
/**
* @zh-cn 获取当前光标的位置
* @en-us Retrieves the position of the caret in the active window.
* @link https://documentation.help/AutoItX/WinGetCaretPos.htm
*/
function WinGetCaretPos() {
    return exports.native.WinGetCaretPos();
}
exports.WinGetCaretPos = WinGetCaretPos;
/**
* @zh-cn 获取指定窗口的类名列表
* @en-us Retrieves a list of classes used by a window by title.
* @link https://documentation.help/AutoItX/WinGetClassList.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinGetClassList(Title, Text = "") {
    return exports.native.WinGetClassList(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetClassList = WinGetClassList;
/**
* @zh-cn 使用窗口句柄获取指定窗口的类名列表
* @en-us Retrieves a list of classes used by a window using its handle.
* @link https://documentation.help/AutoItX/WinGetClassList.htm
* @param hWnd 窗口句柄数字
*/
function WinGetClassListByHandle(hWnd) {
    return exports.native.WinGetClassListByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetClassListByHandle = WinGetClassListByHandle;
/**
* @zh-cn 获取指定窗口客户区的尺寸
* @en-us Retrieves the client area's size of a window by title.
* @link https://documentation.help/AutoItX/WinGetClientSize.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinGetClientSize(Title, Text = "") {
    return exports.native.WinGetClientSize(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetClientSize = WinGetClientSize;
/**
* @zh-cn 使用窗口句柄获取指定窗口客户区的尺寸
* @en-us Retrieves the client area's size of a window using its handle.
* @link https://documentation.help/AutoItX/WinGetClientSize.htm
* @param hWnd 窗口句柄数字
*/
function WinGetClientSizeByHandle(hWnd) {
    return exports.native.WinGetClientSizeByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetClientSizeByHandle = WinGetClientSizeByHandle;
/**
* @zh-cn 获取指定窗口的句柄
* @en-us Retrieves the handle of a window by title.
* @link https://documentation.help/AutoItX/WinGetHandle.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinGetHandle(Title, Text = "") {
    return exports.native.WinGetHandle(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetHandle = WinGetHandle;
/**
* @zh-cn 获取指定窗口的句柄并返回为文本
* @en-us Retrieves the handle of a window by title as text.
* @link https://documentation.help/AutoItX/WinGetHandleAsText.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinGetHandleAsText(Title, Text = "") {
    return exports.native.WinGetHandleAsText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetHandleAsText = WinGetHandleAsText;
/**
* @zh-cn 获取指定窗口的位置和尺寸
* @en-us Retrieves the position and size of a window by title.
* @link https://documentation.help/AutoItX/WinGetPos.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinGetPos(Title, Text = "") {
    return exports.native.WinGetPos(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetPos = WinGetPos;
/**
* @zh-cn 使用窗口句柄获取指定窗口的位置和尺寸
* @en-us Retrieves the position and size of a window using its handle.
* @link https://documentation.help/AutoItX/WinGetPos.htm
* @param hWnd 窗口句柄数字
*/
function WinGetPosByHandle(hWnd) {
    return exports.native.WinGetPosByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetPosByHandle = WinGetPosByHandle;
/**
* @zh-cn 获取指定窗口的进程ID
* @en-us Retrieves the process ID of a window by title.
* @link https://documentation.help/AutoItX/WinGetProcess.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinGetProcess(Title, Text = "") {
    return exports.native.WinGetProcess(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetProcess = WinGetProcess;
/**
* @zh-cn 使用窗口句柄获取指定窗口的进程ID
* @en-us Retrieves the process ID of a window using its handle.
* @link https://documentation.help/AutoItX/WinGetProcess.htm
* @param hWnd 窗口句柄数字
*/
function WinGetProcessByHandle(hWnd) {
    return exports.native.WinGetProcessByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetProcessByHandle = WinGetProcessByHandle;
/**
* @zh-cn 获取指定窗口的状态
* @en-us Retrieves the state of a window by title (minimized, maximized, etc.).
* @link https://documentation.help/AutoItX/WinGetState.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinGetState(Title, Text = "") {
    return exports.native.WinGetState(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetState = WinGetState;
/**
* @zh-cn 使用窗口句柄获取指定窗口的状态
* @en-us Retrieves the state of a window using its handle.
* @link https://documentation.help/AutoItX/WinGetState.htm
* @param hWnd 窗口句柄数字
*/
function WinGetStateByHandle(hWnd) {
    return exports.native.WinGetStateByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetStateByHandle = WinGetStateByHandle;
/**
* @zh-cn 获取指定窗口的文本内容
* @en-us Retrieves the text from a window by title.
* @link https://documentation.help/AutoItX/WinGetText.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinGetText(Title, Text = "") {
    return exports.native.WinGetText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetText = WinGetText;
/**
* @zh-cn 使用窗口句柄获取指定窗口的文本内容
* @en-us Retrieves the text from a window using its handle.
* @link https://documentation.help/AutoItX/WinGetText.htm
* @param hWnd 窗口句柄数字
*/
function WinGetTextByHandle(hWnd) {
    return exports.native.WinGetTextByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetTextByHandle = WinGetTextByHandle;
/**
* @zh-cn 获取指定窗口的标题
* @en-us Retrieves the title of a window by title.
* @link https://documentation.help/AutoItX/WinGetTitle.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinGetTitle(Title, Text = "") {
    return exports.native.WinGetTitle(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetTitle = WinGetTitle;
/**
* @zh-cn 使用窗口句柄获取指定窗口的标题
* @en-us Retrieves the title of a window using its handle.
* @link https://documentation.help/AutoItX/WinGetTitle.htm
* @param hWnd 窗口句柄数字
*/
function WinGetTitleByHandle(hWnd) {
    return exports.native.WinGetTitleByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetTitleByHandle = WinGetTitleByHandle;
/**
* @zh-cn 强制关闭指定的窗口
* @en-us Forces a window to close by title.
* @link https://documentation.help/AutoItX/WinKill.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/
function WinKill(Title, Text = "") {
    return exports.native.WinKill(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinKill = WinKill;
/**
* @zh-cn 使用窗口句柄强制关闭指定的窗口
* @en-us Forces a window to close using its handle.
* @link https://documentation.help/AutoItX/WinKill.htm
* @param hWnd 窗口句柄数字
*/
function WinKillByHandle(hWnd) {
    return exports.native.WinKillByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinKillByHandle = WinKillByHandle;
/**
* @zh-cn 选择窗口的菜单项
* @en-us Selects an item from a menu in a window by title.
* @link https://documentation.help/AutoItX/WinMenuSelectItem.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Item1
* @param Item2
* @param Item3
* @param Item4
* @param Item5
* @param Item6
* @param Item7
* @param Item8
*/
function WinMenuSelectItem(Title, Text, Item1, Item2, Item3, Item4, Item5, Item6, Item7, Item8) {
    return exports.native.WinMenuSelectItem(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Item1 == "undefined" ? "" : Item1), exports.ref.string(typeof Item2 == "undefined" ? "" : Item2), exports.ref.string(typeof Item3 == "undefined" ? "" : Item3), exports.ref.string(typeof Item4 == "undefined" ? "" : Item4), exports.ref.string(typeof Item5 == "undefined" ? "" : Item5), exports.ref.string(typeof Item6 == "undefined" ? "" : Item6), exports.ref.string(typeof Item7 == "undefined" ? "" : Item7), exports.ref.string(typeof Item8 == "undefined" ? "" : Item8));
}
exports.WinMenuSelectItem = WinMenuSelectItem;
/**
* @zh-cn 使用窗口句柄选择窗口的菜单项
* @en-us Selects an item from a menu in a window using its handle.
* @link https://documentation.help/AutoItX/WinMenuSelectItem.htm
* @param hWnd 窗口句柄数字
* @param Item1
* @param Item2
* @param Item3
* @param Item4
* @param Item5
* @param Item6
* @param Item7
* @param Item8
*/
function WinMenuSelectItemByHandle(hWnd, Item1, Item2, Item3, Item4, Item5, Item6, Item7, Item8) {
    return exports.native.WinMenuSelectItemByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.string(typeof Item1 == "undefined" ? "" : Item1), exports.ref.string(typeof Item2 == "undefined" ? "" : Item2), exports.ref.string(typeof Item3 == "undefined" ? "" : Item3), exports.ref.string(typeof Item4 == "undefined" ? "" : Item4), exports.ref.string(typeof Item5 == "undefined" ? "" : Item5), exports.ref.string(typeof Item6 == "undefined" ? "" : Item6), exports.ref.string(typeof Item7 == "undefined" ? "" : Item7), exports.ref.string(typeof Item8 == "undefined" ? "" : Item8));
}
exports.WinMenuSelectItemByHandle = WinMenuSelectItemByHandle;
/**
* @zh-cn 最小化所有窗口
* @en-us Minimizes all windows.
* @link https://documentation.help/AutoItX/WinMinimizeAll.htm
*/
function WinMinimizeAll() {
    return exports.native.WinMinimizeAll();
}
exports.WinMinimizeAll = WinMinimizeAll;
/**
* @zh-cn 恢复最小化的窗口
* @en-us Undoes the effect of `AU3_WinMinimizeAll`.
* @link https://documentation.help/AutoItX/WinMinimizeAllUndo.htm
*/
function WinMinimizeAllUndo() {
    return exports.native.WinMinimizeAllUndo();
}
exports.WinMinimizeAllUndo = WinMinimizeAllUndo;
/**
* @zh-cn 移动指定窗口到指定位置
* @en-us Moves and/or resizes a window by title.
* @link https://documentation.help/AutoItX/WinMove.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param nX x (left To Right)
* @param nY y (top To Bottom)
* @param nWidth 宽度
* @default -1
* @param nHeight 高度
* @default -1
*/
function WinMove(Title, Text, nX, nY, nWidth = -1, nHeight = -1) {
    return exports.native.WinMove(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY), exports.ref.int(typeof nWidth == "undefined" ? -1 : nWidth), exports.ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}
exports.WinMove = WinMove;
/**
* @zh-cn 使用窗口句柄移动指定窗口到指定位置
* @en-us Moves and/or resizes a window using its handle.
* @link https://documentation.help/AutoItX/WinMove.htm
* @param hWnd 窗口句柄数字
* @param nX x (left To Right)
* @param nY y (top To Bottom)
* @param nWidth 宽度
* @default -1
* @param nHeight 高度
* @default -1
*/
function WinMoveByHandle(hWnd, nX, nY, nWidth = -1, nHeight = -1) {
    return exports.native.WinMoveByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY), exports.ref.int(typeof nWidth == "undefined" ? -1 : nWidth), exports.ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}
exports.WinMoveByHandle = WinMoveByHandle;
/**
* @zh-cn 设置指定窗口在其他窗口之上
* @en-us Sets a window to be always on top by title.
* @link https://documentation.help/AutoItX/WinSetOnTop.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param nFlag
*/
function WinSetOnTop(Title, Text, nFlag) {
    return exports.native.WinSetOnTop(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nFlag == "undefined" ? 0 : nFlag));
}
exports.WinSetOnTop = WinSetOnTop;
/**
* @zh-cn 使用窗口句柄设置指定窗口在其他窗口之上
* @en-us Sets a window to be always on top using its handle.
* @link https://documentation.help/AutoItX/WinSetOnTop.htm
* @param hWnd 窗口句柄数字
* @param nFlag
*/
function WinSetOnTopByHandle(hWnd, nFlag) {
    return exports.native.WinSetOnTopByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nFlag == "undefined" ? 0 : nFlag));
}
exports.WinSetOnTopByHandle = WinSetOnTopByHandle;
/**
* @zh-cn 设置指定窗口的状态（最大化、最小化、正常等）
* @en-us Sets the state of a window by title (minimize, maximize, etc.).
* @link https://documentation.help/AutoItX/WinSetState.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param nFlags
*/
function WinSetState(Title, Text, nFlags) {
    return exports.native.WinSetState(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nFlags == "undefined" ? 0 : nFlags));
}
exports.WinSetState = WinSetState;
/**
* @zh-cn 使用窗口句柄设置指定窗口的状态
* @en-us Sets the state of a window using its handle.
* @link https://documentation.help/AutoItX/WinSetState.htm
* @param hWnd 窗口句柄数字
* @param nFlags
*/
function WinSetStateByHandle(hWnd, nFlags) {
    return exports.native.WinSetStateByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nFlags == "undefined" ? 0 : nFlags));
}
exports.WinSetStateByHandle = WinSetStateByHandle;
/**
* @zh-cn 设置指定窗口的标题
* @en-us Sets the title of a window by title.
* @link https://documentation.help/AutoItX/WinSetTitle.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param NewTitle
*/
function WinSetTitle(Title, Text, NewTitle) {
    return exports.native.WinSetTitle(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof NewTitle == "undefined" ? "" : NewTitle));
}
exports.WinSetTitle = WinSetTitle;
/**
* @zh-cn 使用窗口句柄设置指定窗口的标题
* @en-us Sets the title of a window using its handle.
* @link https://documentation.help/AutoItX/WinSetTitle.htm
* @param hWnd 窗口句柄数字
* @param NewTitle
*/
function WinSetTitleByHandle(hWnd, NewTitle) {
    return exports.native.WinSetTitleByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.string(typeof NewTitle == "undefined" ? "" : NewTitle));
}
exports.WinSetTitleByHandle = WinSetTitleByHandle;
/**
* @zh-cn 设置指定窗口的透明度
* @en-us Sets the transparency level of a window by title.
* @link https://documentation.help/AutoItX/WinSetTrans.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
* @param nTrans 不透明度 阿尔法通道值  0 - 255
* @default 255
*/
function WinSetTrans(Title, Text = "", nTrans = 255) {
    return exports.native.WinSetTrans(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nTrans == "undefined" ? 255 : nTrans));
}
exports.WinSetTrans = WinSetTrans;
/**
* @zh-cn 使用窗口句柄设置指定窗口的透明度
* @en-us Sets the transparency level of a window using its handle.
* @link https://documentation.help/AutoItX/WinSetTrans.htm
* @param hWnd 窗口句柄数字
* @param nTrans 不透明度 阿尔法通道值  0 - 255
*/
function WinSetTransByHandle(hWnd, nTrans) {
    return exports.native.WinSetTransByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nTrans == "undefined" ? 0 : nTrans));
}
exports.WinSetTransByHandle = WinSetTransByHandle;
/**
* @zh-cn 等待指定的窗口出现
* @en-us Waits for a window to exist by title.
* @link https://documentation.help/AutoItX/WinWait.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
* @param nTimeout
* @default 0
*/
function WinWait(Title, Text = "", nTimeout = 0) {
    return exports.native.WinWait(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWait = WinWait;
/**
* @zh-cn 使用窗口句柄等待指定的窗口出现
* @en-us Waits for a window to exist using its handle.
* @link https://documentation.help/AutoItX/WinWait.htm
* @param hWnd 窗口句柄数字
* @param nTimeout
*/
function WinWaitByHandle(hWnd, nTimeout) {
    return exports.native.WinWaitByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitByHandle = WinWaitByHandle;
/**
* @zh-cn 等待指定的窗口处于活动状态
* @en-us Waits for a window to be active by title.
* @link https://documentation.help/AutoItX/WinWaitActive.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
* @param nTimeout
* @default 0
*/
function WinWaitActive(Title, Text = "", nTimeout = 0) {
    return exports.native.WinWaitActive(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitActive = WinWaitActive;
/**
* @zh-cn 使用窗口句柄等待指定的窗口处于活动状态
* @en-us Waits for a window to be active using its handle.
* @link https://documentation.help/AutoItX/WinWaitActive.htm
* @param hWnd 窗口句柄数字
* @param nTimeout
*/
function WinWaitActiveByHandle(hWnd, nTimeout) {
    return exports.native.WinWaitActiveByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitActiveByHandle = WinWaitActiveByHandle;
/**
* @zh-cn 等待指定的窗口关闭
* @en-us Waits for a window to close by title.
* @link https://documentation.help/AutoItX/WinWaitClose.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
* @param nTimeout
* @default 0
*/
function WinWaitClose(Title, Text = "", nTimeout = 0) {
    return exports.native.WinWaitClose(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitClose = WinWaitClose;
/**
* @zh-cn 使用窗口句柄等待指定的窗口关闭
* @en-us Waits for a window to close using its handle.
* @link https://documentation.help/AutoItX/WinWaitClose.htm
* @param hWnd 窗口句柄数字
* @param nTimeout
*/
function WinWaitCloseByHandle(hWnd, nTimeout) {
    return exports.native.WinWaitCloseByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitCloseByHandle = WinWaitCloseByHandle;
/**
* @zh-cn 等待指定的窗口不处于活动状态
* @en-us Waits for a window to be not active by title.
* @link https://documentation.help/AutoItX/WinWaitNotActive.htm
* @param Title 窗口标题
* @default ""
* @param Text 窗口/控件文本
* @default ""
* @param nTimeout
* @default 0
*/
function WinWaitNotActive(Title = "", Text = "", nTimeout = 0) {
    return exports.native.WinWaitNotActive(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitNotActive = WinWaitNotActive;
/**
* @zh-cn 使用窗口句柄等待指定的窗口不处于活动状态
* @en-us Waits for a window to be not active using its handle.
* @link https://documentation.help/AutoItX/WinWaitNotActive.htm
* @param hWnd 窗口句柄数字
* @param nTimeout
* @default 0
*/
function WinWaitNotActiveByHandle(hWnd, nTimeout = 0) {
    return exports.native.WinWaitNotActiveByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitNotActiveByHandle = WinWaitNotActiveByHandle;
