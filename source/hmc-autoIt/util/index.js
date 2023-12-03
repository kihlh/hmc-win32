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
                return require("./bin/HMN_x86.node");
            if (process.arch.match(/^x64$/))
                return require("./bin/HMN_x64.node");
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
 * 初始化AutoItX，通常在开始使用AutoItX函数之前调用
 * @returns
 */
function Init() {
    return exports.native.Init();
}
exports.Init = Init;
/**
 * 获取上一次AutoItX函数调用返回的错误代码
 * @returns
 */
function error() {
    return exports.native.error();
}
exports.error = error;
/**
 * 设置AutoIt的选项，可以用来配置AutoIt的一些行为
 * @param Option
 * @param nValue
 * @returns
 */
function AutoItSetOption(Option, nValue) {
    return exports.native.AutoItSetOption(exports.ref.string(typeof Option == "undefined" ? "" : Option), exports.ref.int(typeof nValue == "undefined" ? 0 : nValue));
}
exports.AutoItSetOption = AutoItSetOption;
/**
 * @zh-cn 获取剪贴板的内容
 * @en-us Retrieves the content of the Windows clipboard.
 * @returns
 */
function ClipGet() {
    return exports.native.ClipGet();
}
exports.ClipGet = ClipGet;
function ClipPut(intput) {
    return exports.native.ClipPut(exports.ref.string(typeof intput == "undefined" ? "" : intput));
}
exports.ClipPut = ClipPut;
function ControlClick(szTitle, szText, szControl, szButton = "left", nNumClicks = 1, nX = AU3_INTDEFAULT, nY = AU3_INTDEFAULT) {
    return exports.native.ControlClick(exports.ref.string(typeof szTitle == "undefined" ? "" : szTitle), exports.ref.string(typeof szText == "undefined" ? "" : szText), exports.ref.string(typeof szControl == "undefined" ? "" : szControl), exports.ref.string(typeof szButton == "undefined" ? "left" : szButton), exports.ref.int(typeof nNumClicks == "undefined" ? 1 : nNumClicks), exports.ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX), exports.ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY));
}
exports.ControlClick = ControlClick;
function ControlClickByHandle(hWnd, hCtrl, szButton = "left", nNumClicks = 1, nX = AU3_INTDEFAULT, nY = AU3_INTDEFAULT) {
    return exports.native.ControlClickByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof szButton == "undefined" ? "left" : szButton), exports.ref.int(typeof nNumClicks == "undefined" ? 1 : nNumClicks), exports.ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX), exports.ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY));
}
exports.ControlClickByHandle = ControlClickByHandle;
function ControlCommand(Title, Text, Control, Command, Extra = "") {
    return exports.native.ControlCommand(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra == "undefined" ? "" : Extra));
}
exports.ControlCommand = ControlCommand;
function ControlCommandByHandle(hWnd, hCtrl, Command, Extra = "") {
    return exports.native.ControlCommandByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra == "undefined" ? "" : Extra));
}
exports.ControlCommandByHandle = ControlCommandByHandle;
function ControlListView(Title, Text, Control, Command, Extra1, Extra2) {
    return exports.native.ControlListView(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra1 == "undefined" ? "" : Extra1), exports.ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}
exports.ControlListView = ControlListView;
function ControlListViewByHandle(hWnd, hCtrl, Command, Extra1, Extra2) {
    return exports.native.ControlListViewByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra1 == "undefined" ? "" : Extra1), exports.ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}
exports.ControlListViewByHandle = ControlListViewByHandle;
function ControlDisable(Title, Text, Control) {
    return exports.native.ControlDisable(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlDisable = ControlDisable;
function ControlDisableByHandle(hWnd, hCtrl) {
    return exports.native.ControlDisableByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlDisableByHandle = ControlDisableByHandle;
function ControlEnable(Title, Text, Control) {
    return exports.native.ControlEnable(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlEnable = ControlEnable;
function ControlEnableByHandle(hWnd, hCtrl) {
    return exports.native.ControlEnableByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlEnableByHandle = ControlEnableByHandle;
function ControlFocus(Title, Text, Control) {
    return exports.native.ControlFocus(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlFocus = ControlFocus;
function ControlFocusByHandle(hWnd, hCtrl) {
    return exports.native.ControlFocusByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlFocusByHandle = ControlFocusByHandle;
function ControlGetFocus(Title, Text = "") {
    return exports.native.ControlGetFocus(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.ControlGetFocus = ControlGetFocus;
function ControlGetFocusByHandle(hWnd) {
    return exports.native.ControlGetFocusByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.ControlGetFocusByHandle = ControlGetFocusByHandle;
function ControlGetHandle(hWnd, Control) {
    return exports.native.ControlGetHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlGetHandle = ControlGetHandle;
function ControlGetHandleAsText(Title, Text, Control) {
    return exports.native.ControlGetHandleAsText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlGetHandleAsText = ControlGetHandleAsText;
function ControlGetPos(Title, Text, Control) {
    return exports.native.ControlGetPos(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlGetPos = ControlGetPos;
function ControlGetPosByHandle(hWnd, hCtrl) {
    return exports.native.ControlGetPosByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlGetPosByHandle = ControlGetPosByHandle;
function ControlGetText(Title, Text, Control) {
    return exports.native.ControlGetText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlGetText = ControlGetText;
function ControlGetTextByHandle(hWnd, hCtrl) {
    return exports.native.ControlGetTextByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlGetTextByHandle = ControlGetTextByHandle;
function ControlHide(Title, Text, Control) {
    return exports.native.ControlHide(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlHide = ControlHide;
function ControlHideByHandle(hWnd, hCtrl) {
    return exports.native.ControlHideByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlHideByHandle = ControlHideByHandle;
function ControlMove(Title, Text, Control, nX, nY, nWidth = -1, nHeight = -1) {
    return exports.native.ControlMove(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY), exports.ref.int(typeof nWidth == "undefined" ? -1 : nWidth), exports.ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}
exports.ControlMove = ControlMove;
function ControlMoveByHandle(hWnd, hCtrl, nX, nY, nWidth = -1, nHeight = -1) {
    return exports.native.ControlMoveByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY), exports.ref.int(typeof nWidth == "undefined" ? -1 : nWidth), exports.ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}
exports.ControlMoveByHandle = ControlMoveByHandle;
function ControlSend(Title, Text, Control, SendText, nMode = 0) {
    return exports.native.ControlSend(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.string(typeof SendText == "undefined" ? "" : SendText), exports.ref.int(typeof nMode == "undefined" ? 0 : nMode));
}
exports.ControlSend = ControlSend;
function ControlSendByHandle(hWnd, hCtrl, SendText, nMode = 0) {
    return exports.native.ControlSendByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof SendText == "undefined" ? "" : SendText), exports.ref.int(typeof nMode == "undefined" ? 0 : nMode));
}
exports.ControlSendByHandle = ControlSendByHandle;
function ControlSetText(Title, Text, Control, ControlText) {
    return exports.native.ControlSetText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.string(typeof ControlText == "undefined" ? "" : ControlText));
}
exports.ControlSetText = ControlSetText;
function ControlSetTextByHandle(hWnd, hCtrl, SendText) {
    return exports.native.ControlSetTextByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof SendText == "undefined" ? "" : SendText));
}
exports.ControlSetTextByHandle = ControlSetTextByHandle;
function ControlShow(Title, Text, Control) {
    return exports.native.ControlShow(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control));
}
exports.ControlShow = ControlShow;
function ControlShowByHandle(hWnd, hCtrl) {
    return exports.native.ControlShowByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}
exports.ControlShowByHandle = ControlShowByHandle;
function ControlTreeView(Title, Text, Control, Command, Extra1, Extra2) {
    return exports.native.ControlTreeView(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Control == "undefined" ? "" : Control), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra1 == "undefined" ? "" : Extra1), exports.ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}
exports.ControlTreeView = ControlTreeView;
function ControlTreeViewByHandle(hWnd, hCtrl, Command, Extra1, Extra2) {
    return exports.native.ControlTreeViewByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl), exports.ref.string(typeof Command == "undefined" ? "" : Command), exports.ref.string(typeof Extra1 == "undefined" ? "" : Extra1), exports.ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}
exports.ControlTreeViewByHandle = ControlTreeViewByHandle;
function DriveMapAdd(Device, Share, nFlags, User = "", Pwd = "") {
    return exports.native.DriveMapAdd(exports.ref.string(typeof Device == "undefined" ? "" : Device), exports.ref.string(typeof Share == "undefined" ? "" : Share), exports.ref.int(typeof nFlags == "undefined" ? 0 : nFlags), exports.ref.string(typeof User == "undefined" ? "" : User), exports.ref.string(typeof Pwd == "undefined" ? "" : Pwd));
}
exports.DriveMapAdd = DriveMapAdd;
function DriveMapDel(Device) {
    return exports.native.DriveMapDel(exports.ref.string(typeof Device == "undefined" ? "" : Device));
}
exports.DriveMapDel = DriveMapDel;
function DriveMapGet(Device) {
    return exports.native.DriveMapGet(exports.ref.string(typeof Device == "undefined" ? "" : Device));
}
exports.DriveMapGet = DriveMapGet;
function IsAdmin() {
    return exports.native.IsAdmin();
}
exports.IsAdmin = IsAdmin;
function MouseClick(Button = "LEFT", nX = AU3_INTDEFAULT, nY = AU3_INTDEFAULT, nClicks = 1, nSpeed = -1) {
    return exports.native.MouseClick(exports.ref.string(typeof Button == "undefined" ? "LEFT" : Button), exports.ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX), exports.ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY), exports.ref.int(typeof nClicks == "undefined" ? 1 : nClicks), exports.ref.int(typeof nSpeed == "undefined" ? -1 : nSpeed));
}
exports.MouseClick = MouseClick;
function MouseClickDrag(Button, nX1, nY1, nX2, nY2, nSpeed = -1) {
    return exports.native.MouseClickDrag(exports.ref.string(typeof Button == "undefined" ? "" : Button), exports.ref.int(typeof nX1 == "undefined" ? 0 : nX1), exports.ref.int(typeof nY1 == "undefined" ? 0 : nY1), exports.ref.int(typeof nX2 == "undefined" ? 0 : nX2), exports.ref.int(typeof nY2 == "undefined" ? 0 : nY2), exports.ref.int(typeof nSpeed == "undefined" ? -1 : nSpeed));
}
exports.MouseClickDrag = MouseClickDrag;
function MouseDown(Button = "LEFT") {
    return exports.native.MouseDown(exports.ref.string(typeof Button == "undefined" ? "LEFT" : Button));
}
exports.MouseDown = MouseDown;
function MouseGetCursor() {
    return exports.native.MouseGetCursor();
}
exports.MouseGetCursor = MouseGetCursor;
function MouseGetPos() {
    return exports.native.MouseGetPos();
}
exports.MouseGetPos = MouseGetPos;
function MouseMove(nX, nY, nSpeed = -1) {
    return exports.native.MouseMove(exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY), exports.ref.int(typeof nSpeed == "undefined" ? -1 : nSpeed));
}
exports.MouseMove = MouseMove;
function MouseUp(Button = "LEFT") {
    return exports.native.MouseUp(exports.ref.string(typeof Button == "undefined" ? "LEFT" : Button));
}
exports.MouseUp = MouseUp;
function MouseWheel(Direction, nClicks) {
    return exports.native.MouseWheel(exports.ref.string(typeof Direction == "undefined" ? "" : Direction), exports.ref.int(typeof nClicks == "undefined" ? 0 : nClicks));
}
exports.MouseWheel = MouseWheel;
function Opt(Option, nValue) {
    return exports.native.Opt(exports.ref.string(typeof Option == "undefined" ? "" : Option), exports.ref.int(typeof nValue == "undefined" ? 0 : nValue));
}
exports.Opt = Opt;
function PixelChecksum(lpRect, nStep = 1) {
    return exports.native.PixelChecksum({
        left: exports.ref.int(lpRect.left),
        top: exports.ref.int(lpRect.top),
        right: exports.ref.int(lpRect.right),
        bottom: exports.ref.int(lpRect.bottom)
    }, exports.ref.int(typeof nStep == "undefined" ? 1 : nStep));
}
exports.PixelChecksum = PixelChecksum;
function PixelGetColor(nX, nY) {
    return exports.native.PixelGetColor(exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY));
}
exports.PixelGetColor = PixelGetColor;
function PixelSearch(lpRect, nCol, nVar = 0, nStep = 1) {
    return exports.native.PixelSearch({
        left: exports.ref.int(lpRect.left),
        top: exports.ref.int(lpRect.top),
        right: exports.ref.int(lpRect.right),
        bottom: exports.ref.int(lpRect.bottom)
    }, exports.ref.int(typeof nCol == "undefined" ? 0 : nCol), exports.ref.int(typeof nVar == "undefined" ? 0 : nVar), exports.ref.int(typeof nStep == "undefined" ? 1 : nStep));
}
exports.PixelSearch = PixelSearch;
function ProcessClose(Process) {
    return exports.native.ProcessClose(exports.ref.string(typeof Process == "undefined" ? "" : Process));
}
exports.ProcessClose = ProcessClose;
function ProcessExists(Process) {
    return exports.native.ProcessExists(exports.ref.string(typeof Process == "undefined" ? "" : Process));
}
exports.ProcessExists = ProcessExists;
function ProcessSetPriority(Process, nPriority) {
    return exports.native.ProcessSetPriority(exports.ref.string(typeof Process == "undefined" ? "" : Process), exports.ref.int(typeof nPriority == "undefined" ? 0 : nPriority));
}
exports.ProcessSetPriority = ProcessSetPriority;
function ProcessWait(Process, nTimeout = 0) {
    return exports.native.ProcessWait(exports.ref.string(typeof Process == "undefined" ? "" : Process), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.ProcessWait = ProcessWait;
function ProcessWaitClose(Process, nTimeout = 0) {
    return exports.native.ProcessWaitClose(exports.ref.string(typeof Process == "undefined" ? "" : Process), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.ProcessWaitClose = ProcessWaitClose;
function Run(Program, Dir = "", nShowFlag = SW_SHOWNORMAL) {
    return exports.native.Run(exports.ref.string(typeof Program == "undefined" ? "" : Program), exports.ref.string(typeof Dir == "undefined" ? "" : Dir), exports.ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}
exports.Run = Run;
function RunWait(Program, Dir = "", nShowFlag = SW_SHOWNORMAL) {
    return exports.native.RunWait(exports.ref.string(typeof Program == "undefined" ? "" : Program), exports.ref.string(typeof Dir == "undefined" ? "" : Dir), exports.ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}
exports.RunWait = RunWait;
function RunAs(User, Domain, Password, nLogonFlag, Program, Dir = "", nShowFlag = SW_SHOWNORMAL) {
    return exports.native.RunAs(exports.ref.string(typeof User == "undefined" ? "" : User), exports.ref.string(typeof Domain == "undefined" ? "" : Domain), exports.ref.string(typeof Password == "undefined" ? "" : Password), exports.ref.int(typeof nLogonFlag == "undefined" ? 0 : nLogonFlag), exports.ref.string(typeof Program == "undefined" ? "" : Program), exports.ref.string(typeof Dir == "undefined" ? "" : Dir), exports.ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}
exports.RunAs = RunAs;
function RunAsWait(User, Domain, Password, nLogonFlag, Program, Dir = "", nShowFlag = SW_SHOWNORMAL) {
    return exports.native.RunAsWait(exports.ref.string(typeof User == "undefined" ? "" : User), exports.ref.string(typeof Domain == "undefined" ? "" : Domain), exports.ref.string(typeof Password == "undefined" ? "" : Password), exports.ref.int(typeof nLogonFlag == "undefined" ? 0 : nLogonFlag), exports.ref.string(typeof Program == "undefined" ? "" : Program), exports.ref.string(typeof Dir == "undefined" ? "" : Dir), exports.ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}
exports.RunAsWait = RunAsWait;
function Send(SendText, nMode = 0) {
    return exports.native.Send(exports.ref.string(typeof SendText == "undefined" ? "" : SendText), exports.ref.int(typeof nMode == "undefined" ? 0 : nMode));
}
exports.Send = Send;
function Shutdown(nFlags) {
    return exports.native.Shutdown(exports.ref.int(typeof nFlags == "undefined" ? 0 : nFlags));
}
exports.Shutdown = Shutdown;
function Sleep(nMilliseconds) {
    return exports.native.Sleep(exports.ref.int(typeof nMilliseconds == "undefined" ? 0 : nMilliseconds));
}
exports.Sleep = Sleep;
function StatusbarGetText(Title = "", Text = "", nPart = 1) {
    return exports.native.StatusbarGetText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nPart == "undefined" ? 1 : nPart));
}
exports.StatusbarGetText = StatusbarGetText;
function StatusbarGetTextByHandle(hWnd, nPart = 1) {
    return exports.native.StatusbarGetTextByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nPart == "undefined" ? 1 : nPart));
}
exports.StatusbarGetTextByHandle = StatusbarGetTextByHandle;
function ToolTip(Tip, nX = AU3_INTDEFAULT, nY = AU3_INTDEFAULT) {
    return exports.native.ToolTip(exports.ref.string(typeof Tip == "undefined" ? "" : Tip), exports.ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX), exports.ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY));
}
exports.ToolTip = ToolTip;
function WinActivate(Title, Text = "") {
    return exports.native.WinActivate(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinActivate = WinActivate;
function WinActivateByHandle(hWnd) {
    return exports.native.WinActivateByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinActivateByHandle = WinActivateByHandle;
function WinActive(Title, Text = "") {
    return exports.native.WinActive(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinActive = WinActive;
function WinActiveByHandle(hWnd) {
    return exports.native.WinActiveByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinActiveByHandle = WinActiveByHandle;
function WinClose(Title, Text = "") {
    return exports.native.WinClose(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinClose = WinClose;
function WinCloseByHandle(hWnd) {
    return exports.native.WinCloseByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinCloseByHandle = WinCloseByHandle;
function WinExists(Title, Text = "") {
    return exports.native.WinExists(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinExists = WinExists;
function WinExistsByHandle(hWnd) {
    return exports.native.WinExistsByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinExistsByHandle = WinExistsByHandle;
function WinGetCaretPos() {
    return exports.native.WinGetCaretPos();
}
exports.WinGetCaretPos = WinGetCaretPos;
function WinGetClassList(Title, Text = "") {
    return exports.native.WinGetClassList(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetClassList = WinGetClassList;
function WinGetClassListByHandle(hWnd) {
    return exports.native.WinGetClassListByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetClassListByHandle = WinGetClassListByHandle;
function WinGetClientSize(Title, Text = "") {
    return exports.native.WinGetClientSize(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetClientSize = WinGetClientSize;
function WinGetClientSizeByHandle(hWnd) {
    return exports.native.WinGetClientSizeByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetClientSizeByHandle = WinGetClientSizeByHandle;
function WinGetHandle(Title, Text = "") {
    return exports.native.WinGetHandle(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetHandle = WinGetHandle;
function WinGetHandleAsText(Title, Text = "") {
    return exports.native.WinGetHandleAsText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetHandleAsText = WinGetHandleAsText;
function WinGetPos(Title, Text = "") {
    return exports.native.WinGetPos(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetPos = WinGetPos;
function WinGetPosByHandle(hWnd) {
    return exports.native.WinGetPosByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetPosByHandle = WinGetPosByHandle;
function WinGetProcess(Title, Text = "") {
    return exports.native.WinGetProcess(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetProcess = WinGetProcess;
function WinGetProcessByHandle(hWnd) {
    return exports.native.WinGetProcessByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetProcessByHandle = WinGetProcessByHandle;
function WinGetState(Title, Text = "") {
    return exports.native.WinGetState(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetState = WinGetState;
function WinGetStateByHandle(hWnd) {
    return exports.native.WinGetStateByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetStateByHandle = WinGetStateByHandle;
function WinGetText(Title, Text = "") {
    return exports.native.WinGetText(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetText = WinGetText;
function WinGetTextByHandle(hWnd) {
    return exports.native.WinGetTextByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetTextByHandle = WinGetTextByHandle;
function WinGetTitle(Title, Text = "") {
    return exports.native.WinGetTitle(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinGetTitle = WinGetTitle;
function WinGetTitleByHandle(hWnd) {
    return exports.native.WinGetTitleByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinGetTitleByHandle = WinGetTitleByHandle;
function WinKill(Title, Text = "") {
    return exports.native.WinKill(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text));
}
exports.WinKill = WinKill;
function WinKillByHandle(hWnd) {
    return exports.native.WinKillByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}
exports.WinKillByHandle = WinKillByHandle;
function WinMenuSelectItem(Title, Text, Item1, Item2, Item3, Item4, Item5, Item6, Item7, Item8) {
    return exports.native.WinMenuSelectItem(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof Item1 == "undefined" ? "" : Item1), exports.ref.string(typeof Item2 == "undefined" ? "" : Item2), exports.ref.string(typeof Item3 == "undefined" ? "" : Item3), exports.ref.string(typeof Item4 == "undefined" ? "" : Item4), exports.ref.string(typeof Item5 == "undefined" ? "" : Item5), exports.ref.string(typeof Item6 == "undefined" ? "" : Item6), exports.ref.string(typeof Item7 == "undefined" ? "" : Item7), exports.ref.string(typeof Item8 == "undefined" ? "" : Item8));
}
exports.WinMenuSelectItem = WinMenuSelectItem;
function WinMenuSelectItemByHandle(hWnd, Item1, Item2, Item3, Item4, Item5, Item6, Item7, Item8) {
    return exports.native.WinMenuSelectItemByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.string(typeof Item1 == "undefined" ? "" : Item1), exports.ref.string(typeof Item2 == "undefined" ? "" : Item2), exports.ref.string(typeof Item3 == "undefined" ? "" : Item3), exports.ref.string(typeof Item4 == "undefined" ? "" : Item4), exports.ref.string(typeof Item5 == "undefined" ? "" : Item5), exports.ref.string(typeof Item6 == "undefined" ? "" : Item6), exports.ref.string(typeof Item7 == "undefined" ? "" : Item7), exports.ref.string(typeof Item8 == "undefined" ? "" : Item8));
}
exports.WinMenuSelectItemByHandle = WinMenuSelectItemByHandle;
function WinMinimizeAll() {
    return exports.native.WinMinimizeAll();
}
exports.WinMinimizeAll = WinMinimizeAll;
function WinMinimizeAllUndo() {
    return exports.native.WinMinimizeAllUndo();
}
exports.WinMinimizeAllUndo = WinMinimizeAllUndo;
function WinMove(Title, Text, nX, nY, nWidth = -1, nHeight = -1) {
    return exports.native.WinMove(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY), exports.ref.int(typeof nWidth == "undefined" ? -1 : nWidth), exports.ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}
exports.WinMove = WinMove;
function WinMoveByHandle(hWnd, nX, nY, nWidth = -1, nHeight = -1) {
    return exports.native.WinMoveByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nX == "undefined" ? 0 : nX), exports.ref.int(typeof nY == "undefined" ? 0 : nY), exports.ref.int(typeof nWidth == "undefined" ? -1 : nWidth), exports.ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}
exports.WinMoveByHandle = WinMoveByHandle;
function WinSetOnTop(Title, Text, nFlag) {
    return exports.native.WinSetOnTop(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nFlag == "undefined" ? 0 : nFlag));
}
exports.WinSetOnTop = WinSetOnTop;
function WinSetOnTopByHandle(hWnd, nFlag) {
    return exports.native.WinSetOnTopByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nFlag == "undefined" ? 0 : nFlag));
}
exports.WinSetOnTopByHandle = WinSetOnTopByHandle;
function WinSetState(Title, Text, nFlags) {
    return exports.native.WinSetState(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nFlags == "undefined" ? 0 : nFlags));
}
exports.WinSetState = WinSetState;
function WinSetStateByHandle(hWnd, nFlags) {
    return exports.native.WinSetStateByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nFlags == "undefined" ? 0 : nFlags));
}
exports.WinSetStateByHandle = WinSetStateByHandle;
function WinSetTitle(Title, Text, NewTitle) {
    return exports.native.WinSetTitle(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.string(typeof NewTitle == "undefined" ? "" : NewTitle));
}
exports.WinSetTitle = WinSetTitle;
function WinSetTitleByHandle(hWnd, NewTitle) {
    return exports.native.WinSetTitleByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.string(typeof NewTitle == "undefined" ? "" : NewTitle));
}
exports.WinSetTitleByHandle = WinSetTitleByHandle;
function WinSetTrans(Title, Text = "", nTrans = 255) {
    return exports.native.WinSetTrans(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nTrans == "undefined" ? 255 : nTrans));
}
exports.WinSetTrans = WinSetTrans;
function WinSetTransByHandle(hWnd, nTrans) {
    return exports.native.WinSetTransByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nTrans == "undefined" ? 0 : nTrans));
}
exports.WinSetTransByHandle = WinSetTransByHandle;
function WinWait(Title, Text = "", nTimeout = 0) {
    return exports.native.WinWait(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWait = WinWait;
function WinWaitByHandle(hWnd, nTimeout) {
    return exports.native.WinWaitByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitByHandle = WinWaitByHandle;
function WinWaitActive(Title, Text = "", nTimeout = 0) {
    return exports.native.WinWaitActive(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitActive = WinWaitActive;
function WinWaitActiveByHandle(hWnd, nTimeout) {
    return exports.native.WinWaitActiveByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitActiveByHandle = WinWaitActiveByHandle;
function WinWaitClose(Title, Text = "", nTimeout = 0) {
    return exports.native.WinWaitClose(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitClose = WinWaitClose;
function WinWaitCloseByHandle(hWnd, nTimeout) {
    return exports.native.WinWaitCloseByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitCloseByHandle = WinWaitCloseByHandle;
/**
 * @zh-cn d
 * @link http://
 * @param Title
 * @default dd ddd
 * @param Text
 * @param nTimeout
 * @returns
 */
function WinWaitNotActive(Title = "", Text = "", nTimeout = 0) {
    return exports.native.WinWaitNotActive(exports.ref.string(typeof Title == "undefined" ? "" : Title), exports.ref.string(typeof Text == "undefined" ? "" : Text), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitNotActive = WinWaitNotActive;
function WinWaitNotActiveByHandle(hWnd, nTimeout = 0) {
    return exports.native.WinWaitNotActiveByHandle(exports.ref.int(typeof hWnd == "undefined" ? 0 : hWnd), exports.ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}
exports.WinWaitNotActiveByHandle = WinWaitNotActiveByHandle;
