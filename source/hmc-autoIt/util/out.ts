
import path = require("path");

const AU3_INTDEFAULT = -2147483647;
const SW_SHOWNORMAL = 1;

/**
 * @zh-cn 静态调用 .dll (注意如果您不知道这个是什么作用 请勿随意调用 参数错误有可能会导致进程崩溃)
 * @en-us Static call to .dll (Note that if you don't know what this does, don't call it at random.  Parameter errors may cause the process to crash)
 */
const get_native: () => HMN.Native = (binPath?: string) => {
       function _require_bin(): HMN.Native | null {
              try {
                     if (binPath) return require(binPath);
                     if (process.arch.match(/^x32|ia32$/)) return require("./bin/AutoItX_x86.node");
                     if (process.arch.match(/^x64$/)) return require("./bin/AutoItX_x64.node");
              } catch (X_X) {

              }
              return null;
       }
       let Native: HMN.Native = (process.platform == "win32" ? _require_bin() : null) || (() => {
              let HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
              function fnBool(...args: any[]) { console.error(HMCNotPlatform); return false }
              function fnVoid(...args: any[]) { console.error(HMCNotPlatform); return undefined }
              function fnNull(...args: any[]) { console.error(HMCNotPlatform); return null }
              function fnNum(...args: any[]) { console.error(HMCNotPlatform); return 0 }
              function fnStrList(...args: any[]) { console.error(HMCNotPlatform); return [] as string[] }
              function fnStr(...args: any[]) { console.error(HMCNotPlatform); return '' }
              function fnAnyArr(...args: any[]) { console.error(HMCNotPlatform); return [] as any[] }
              function fnArrayStr(...args: any[]) { console.error(HMCNotPlatform); return '[]' }
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
                     ControlGetPos: (...arg: any[]) => { return { left: 0, top: 0, right: 0, bottom: 0 } as any },
                     ControlGetPosByHandle: (...arg: any[]) => { return { left: 0, top: 0, right: 0, bottom: 0 } as any },
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
                     MouseGetPos: (...arg: any[]) => { return { x: 0, y: 0 } as any },
                     MouseMove: fnNum,
                     MouseUp: fnVoid,
                     MouseWheel: fnVoid,
                     Opt: fnNum,
                     PixelChecksum: fnNum,
                     PixelGetColor: fnNum,
                     PixelSearch: (...arg: any[]) => { return { x: 0, y: 0 } as any },
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
                     WinGetCaretPos: (...arg: any[]) => { return { x: 0, y: 0 } as any },
                     WinGetClassList: fnStr,
                     WinGetClassListByHandle: fnStr,
                     WinGetClientSize: (...arg: any[]) => { return { left: 0, top: 0, right: 0, bottom: 0 } as any },
                     WinGetClientSizeByHandle: (...arg: any[]) => { return { left: 0, top: 0, right: 0, bottom: 0 } as any },
                     WinGetHandle: fnNum,
                     WinGetHandleAsText: fnStr,
                     WinGetPos: (...arg: any[]) => { return { left: 0, top: 0, right: 0, bottom: 0 } as any },
                     WinGetPosByHandle: (...arg: any[]) => { return { left: 0, top: 0, right: 0, bottom: 0 } as any },
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

              }
       })();
       return Native;
};
export const native: HMN.Native = get_native();


// 类型
export module HMN {
       export interface Native {
              Init(): undefined | void;
              error(): number | void;
              AutoItSetOption(Option: string, nValue: number): number | void;
              ClipGet(): string | void;
              ClipPut(intput: string): undefined | void;
              ControlClick(szTitle: string, szText: string, szControl: string, szButton?: string, nNumClicks?: number, nX?: number, nY?: number): boolean | void;
              ControlClickByHandle(hWnd: number, hCtrl: number, szButton?: string, nNumClicks?: number, nX?: number, nY?: number): number | void;
              ControlCommand(Title: string, Text: string, Control: string, Command: string, Extra?: string): string | void;
              ControlCommandByHandle(hWnd: number, hCtrl: number, Command: string, Extra?: string): string | void;
              ControlListView(Title: string, Text: string, Control: string, Command: string, Extra1: string, Extra2: string): string | void;
              ControlListViewByHandle(hWnd: number, hCtrl: number, Command: string, Extra1: string, Extra2: string): string | void;
              ControlDisable(Title: string, Text: string, Control: string): boolean | void;
              ControlDisableByHandle(hWnd: number, hCtrl: number): boolean | void;
              ControlEnable(Title: string, Text: string, Control: string): boolean | void;
              ControlEnableByHandle(hWnd: number, hCtrl: number): boolean | void;
              ControlFocus(Title: string, Text: string, Control: string): boolean | void;
              ControlFocusByHandle(hWnd: number, hCtrl: number): boolean | void;
              ControlGetFocus(Title: string, Text?: string): string | void;
              ControlGetFocusByHandle(hWnd: number): string | void;
              ControlGetHandle(hWnd: number, Control: string): number | void;
              ControlGetHandleAsText(Title: string, Text: string, Control: string): string | void;
              ControlGetPos(Title: string, Text: string, Control: string): { left: number, top: number, right: number, bottom: number } | void;
              ControlGetPosByHandle(hWnd: number, hCtrl: number): { left: number, top: number, right: number, bottom: number } | void;
              ControlGetText(Title: string, Text: string, Control: string): string | void;
              ControlGetTextByHandle(hWnd: number, hCtrl: number): string | void;
              ControlHide(Title: string, Text: string, Control: string): boolean | void;
              ControlHideByHandle(hWnd: number, hCtrl: number): boolean | void;
              ControlMove(Title: string, Text: string, Control: string, nX: number, nY: number, nWidth?: number, nHeight?: number): boolean | void;
              ControlMoveByHandle(hWnd: number, hCtrl: number, nX: number, nY: number, nWidth?: number, nHeight?: number): boolean | void;
              ControlSend(Title: string, Text: string, Control: string, SendText: string, nMode?: number): boolean | void;
              ControlSendByHandle(hWnd: number, hCtrl: number, SendText: string, nMode?: number): boolean | void;
              ControlSetText(Title: string, Text: string, Control: string, ControlText: string): boolean | void;
              ControlSetTextByHandle(hWnd: number, hCtrl: number, SendText: string): boolean | void;
              ControlShow(Title: string, Text: string, Control: string): boolean | void;
              ControlShowByHandle(hWnd: number, hCtrl: number): boolean | void;
              ControlTreeView(Title: string, Text: string, Control: string, Command: string, Extra1: string, Extra2: string): string | void;
              ControlTreeViewByHandle(hWnd: number, hCtrl: number, Command: string, Extra1: string, Extra2: string): string | void;
              DriveMapAdd(Device: string, Share: string, nFlags: number, User?: string, Pwd?: string): string | void;
              DriveMapDel(Device: string): boolean | void;
              DriveMapGet(Device: string): string | void;
              IsAdmin(): boolean | void;
              MouseClick(Button?: string, nX?: number, nY?: number, nClicks?: number, nSpeed?: number): undefined | void;
              MouseClickDrag(Button: string, nX1: number, nY1: number, nX2: number, nY2: number, nSpeed?: number): undefined | void;
              MouseDown(Button?: string): undefined | void;
              MouseGetCursor(): number | void;
              MouseGetPos(): { x: number, y: number } | void;
              MouseMove(nX: number, nY: number, nSpeed?: number): number | void;
              MouseUp(Button?: string): undefined | void;
              MouseWheel(Direction: string, nClicks: number): undefined | void;
              Opt(Option: string, nValue: number): number | void;
              PixelChecksum(lpRect: { left: number, top: number, right: number, bottom: number }, nStep?: number): number | void;
              PixelGetColor(nX: number, nY: number): number | void;
              PixelSearch(lpRect: { left: number, top: number, right: number, bottom: number }, nCol: number, nVar?: number, nStep?: number): { x: number, y: number } | void;
              ProcessClose(Process: string): undefined | void;
              ProcessExists(Process: string): boolean | void;
              ProcessSetPriority(Process: string, nPriority: number): boolean | void;
              ProcessWait(Process: string, nTimeout?: number): boolean | void;
              ProcessWaitClose(Process: string, nTimeout?: number): boolean | void;
              Run(Program: string, Dir?: string, nShowFlag?: number): number | void;
              RunWait(Program: string, Dir?: string, nShowFlag?: number): number | void;
              RunAs(User: string, Domain: string, Password: string, nLogonFlag: number, Program: string, Dir?: string, nShowFlag?: number): number | void;
              RunAsWait(User: string, Domain: string, Password: string, nLogonFlag: number, Program: string, Dir?: string, nShowFlag?: number): number | void;
              Send(SendText: string, nMode?: number): undefined | void;
              Shutdown(nFlags: number): boolean | void;
              Sleep(nMilliseconds: number): undefined | void;
              StatusbarGetText(Title?: string, Text?: string, nPart?: number): string | void;
              StatusbarGetTextByHandle(hWnd: number, nPart?: number): string | void;
              ToolTip(Tip: string, nX?: number, nY?: number): undefined | void;
              WinActivate(Title: string, Text?: string): boolean | void;
              WinActivateByHandle(hWnd: number): boolean | void;
              WinActive(Title: string, Text?: string): boolean | void;
              WinActiveByHandle(hWnd: number): boolean | void;
              WinClose(Title: string, Text?: string): boolean | void;
              WinCloseByHandle(hWnd: number): boolean | void;
              WinExists(Title: string, Text?: string): boolean | void;
              WinExistsByHandle(hWnd: number): boolean | void;
              WinGetCaretPos(): { x: number, y: number } | void;
              WinGetClassList(Title: string, Text?: string): string | void;
              WinGetClassListByHandle(hWnd: number): string | void;
              WinGetClientSize(Title: string, Text?: string): { left: number, top: number, right: number, bottom: number } | void;
              WinGetClientSizeByHandle(hWnd: number): { left: number, top: number, right: number, bottom: number } | void;
              WinGetHandle(Title: string, Text?: string): number | void;
              WinGetHandleAsText(Title: string, Text?: string): string | void;
              WinGetPos(Title: string, Text?: string): { left: number, top: number, right: number, bottom: number } | void;
              WinGetPosByHandle(hWnd: number): { left: number, top: number, right: number, bottom: number } | void;
              WinGetProcess(Title: string, Text?: string): undefined | void;
              WinGetProcessByHandle(hWnd: number): undefined | void;
              WinGetState(Title: string, Text?: string): number | void;
              WinGetStateByHandle(hWnd: number): number | void;
              WinGetText(Title: string, Text?: string): string | void;
              WinGetTextByHandle(hWnd: number): string | void;
              WinGetTitle(Title: string, Text?: string): string | void;
              WinGetTitleByHandle(hWnd: number): string | void;
              WinKill(Title: string, Text?: string): boolean | void;
              WinKillByHandle(hWnd: number): boolean | void;
              WinMenuSelectItem(Title: string, Text: string, Item1: string, Item2: string, Item3: string, Item4: string, Item5: string, Item6: string, Item7: string, Item8: string): boolean | void;
              WinMenuSelectItemByHandle(hWnd: number, Item1: string, Item2: string, Item3: string, Item4: string, Item5: string, Item6: string, Item7: string, Item8: string): boolean | void;
              WinMinimizeAll(): undefined | void;
              WinMinimizeAllUndo(): undefined | void;
              WinMove(Title: string, Text: string, nX: number, nY: number, nWidth?: number, nHeight?: number): undefined | void;
              WinMoveByHandle(hWnd: number, nX: number, nY: number, nWidth?: number, nHeight?: number): undefined | void;
              WinSetOnTop(Title: string, Text: string, nFlag: number): undefined | void;
              WinSetOnTopByHandle(hWnd: number, nFlag: number): undefined | void;
              WinSetState(Title: string, Text: string, nFlags: number): undefined | void;
              WinSetStateByHandle(hWnd: number, nFlags: number): undefined | void;
              WinSetTitle(Title: string, Text: string, NewTitle: string): undefined | void;
              WinSetTitleByHandle(hWnd: number, NewTitle: string): undefined | void;
              WinSetTrans(Title: string, Text?: string, nTrans?: number): boolean | void;
              WinSetTransByHandle(hWnd: number, nTrans: number): boolean | void;
              WinWait(Title: string, Text?: string, nTimeout?: number): boolean | void;
              WinWaitByHandle(hWnd: number, nTimeout: number): boolean | void;
              WinWaitActive(Title: string, Text?: string, nTimeout?: number): boolean | void;
              WinWaitActiveByHandle(hWnd: number, nTimeout: number): boolean | void;
              WinWaitClose(Title: string, Text?: string, nTimeout?: number): boolean | void;
              WinWaitCloseByHandle(hWnd: number, nTimeout: number): boolean | void;
              WinWaitNotActive(Title?: string, Text?: string, nTimeout?: number): boolean | void;
              WinWaitNotActiveByHandle(hWnd: number, nTimeout?: number): boolean | void;

       }
}

export const ref = {
       /**
       * 将内容格式化为文本路径
       * @param Str
       * @returns
       */
       path(Str: any) {
              return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
       },
       /**
        * 格式化为bool
        * @param bool
        * @returns
        */
       bool(bool: any) {
              return bool ? true : false;
       },
       /**
        * 将内容格式化为文本
        * @param Str
        * @returns
        */
       string(Str: any) {
              return String(Str || "");
       },
       /**
        * 格式化数字为int(强制)
        * @param Num
        * @returns
        */
       int(Num: any): number {
              if (!Num) return 0;
              if (typeof Num == "object" && Num instanceof Number) {
                     Num = Num?.valueOf();
              }
              // 取整
              Num = Math.trunc(Num + 0);
              if (typeof Num == "number" && !isNaN(Num)) return Num;
              // true == 1
              if (Num && typeof Num == "boolean") Num = 1;
              // false = 0;
              if (!Num && typeof Num == "boolean") Num = 0;
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
       stringArray(array: Set<any> | Array<any>) {
              let dataList: string[] = [];
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
       intArray(array: Set<any> | Array<any>) {
              let dataList: number[] = [];
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
       concatBuff(buffList: Buffer[]): Buffer {
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

export function Init(): undefined | void {
       return native.Init();
}



/**
* @zh-cn 获取上一次AutoItX函数调用返回的错误代码 
* @en-us Retrieves the error code from the last AutoItX function call.
* @link https://documentation.help/AutoItX/error.htm
*/

export function error(): number | void {
       return native.error();
}



/**
* @zh-cn 设置AutoIt的选项，可以用来配置AutoIt的一些行为 
* @en-us Sets various options for AutoItX, such as timeout and behavior.
* @link https://documentation.help/AutoItX/AutoItSetOption.htm
* @param Option 
* @param nValue 
*/

export function AutoItSetOption(Option: string, nValue: number): number | void {
       return native.AutoItSetOption(ref.string(typeof Option == "undefined" ? "" : Option),
              ref.int(typeof nValue == "undefined" ? 0 : nValue));
}



/**
* @zh-cn 获取剪贴板的内容 
* @en-us Retrieves the content of the Windows clipboard.
* @link https://documentation.help/AutoItX/ClipGet.htm
*/

export function ClipGet(): string | void {
       return native.ClipGet();
}



/**
* @zh-cn 将文本放入剪贴板 
* @en-us Puts text into the Windows clipboard.
* @link https://documentation.help/AutoItX/ClipPut.htm
* @param intput 
*/

export function ClipPut(intput: string): undefined | void {
       return native.ClipPut(ref.string(typeof intput == "undefined" ? "" : intput));
}



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

export function ControlClick(szTitle: string, szText: string, szControl: string, szButton: string = "left", nNumClicks: number = 1, nX: number = AU3_INTDEFAULT, nY: number = AU3_INTDEFAULT): boolean | void {
       return native.ControlClick(ref.string(typeof szTitle == "undefined" ? "" : szTitle),
              ref.string(typeof szText == "undefined" ? "" : szText),
              ref.string(typeof szControl == "undefined" ? "" : szControl),
              ref.string(typeof szButton == "undefined" ? "left" : szButton),
              ref.int(typeof nNumClicks == "undefined" ? 1 : nNumClicks),
              ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX),
              ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY));
}



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

export function ControlClickByHandle(hWnd: number, hCtrl: number, szButton: string = "left", nNumClicks: number = 1, nX: number = AU3_INTDEFAULT, nY: number = AU3_INTDEFAULT): number | void {
       return native.ControlClickByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl),
              ref.string(typeof szButton == "undefined" ? "left" : szButton),
              ref.int(typeof nNumClicks == "undefined" ? 1 : nNumClicks),
              ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX),
              ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY));
}



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

export function ControlCommand(Title: string, Text: string, Control: string, Command: string, Extra: string = ""): string | void {
       return native.ControlCommand(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control),
              ref.string(typeof Command == "undefined" ? "" : Command),
              ref.string(typeof Extra == "undefined" ? "" : Extra));
}



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

export function ControlCommandByHandle(hWnd: number, hCtrl: number, Command: string, Extra: string = ""): string | void {
       return native.ControlCommandByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl),
              ref.string(typeof Command == "undefined" ? "" : Command),
              ref.string(typeof Extra == "undefined" ? "" : Extra));
}



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

export function ControlListView(Title: string, Text: string, Control: string, Command: string, Extra1: string, Extra2: string): string | void {
       return native.ControlListView(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control),
              ref.string(typeof Command == "undefined" ? "" : Command),
              ref.string(typeof Extra1 == "undefined" ? "" : Extra1),
              ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}



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

export function ControlListViewByHandle(hWnd: number, hCtrl: number, Command: string, Extra1: string, Extra2: string): string | void {
       return native.ControlListViewByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl),
              ref.string(typeof Command == "undefined" ? "" : Command),
              ref.string(typeof Extra1 == "undefined" ? "" : Extra1),
              ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}



/**
* @zh-cn 禁用控件 
* @en-us Disables a control in a window.
* @link https://documentation.help/AutoItX/ControlDisable.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/

export function ControlDisable(Title: string, Text: string, Control: string): boolean | void {
       return native.ControlDisable(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control));
}



/**
* @zh-cn 使用控件句柄禁用控件 
* @en-us Same as `AU3_ControlDisable` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlDisable.htm
* @param hWnd 窗口句柄数字
* @param hCtrl 
*/

export function ControlDisableByHandle(hWnd: number, hCtrl: number): boolean | void {
       return native.ControlDisableByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}



/**
* @zh-cn 启用控件 
* @en-us Enables a control in a window.
* @link https://documentation.help/AutoItX/ControlEnable.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/

export function ControlEnable(Title: string, Text: string, Control: string): boolean | void {
       return native.ControlEnable(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control));
}



/**
* @zh-cn 使用控件句柄启用控件 
* @en-us Same as `AU3_ControlEnable` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlEnable.htm
* @param hWnd 窗口句柄数字
* @param hCtrl 
*/

export function ControlEnableByHandle(hWnd: number, hCtrl: number): boolean | void {
       return native.ControlEnableByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}



/**
* @zh-cn 将焦点设置到控件上 
* @en-us Sets focus to a control in a window.
* @link https://documentation.help/AutoItX/ControlFocus.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/

export function ControlFocus(Title: string, Text: string, Control: string): boolean | void {
       return native.ControlFocus(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control));
}



/**
* @zh-cn 使用控件句柄将焦点设置到控件上 
* @en-us Same as `AU3_ControlFocus` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlFocus.htm
* @param hWnd 窗口句柄数字
* @param hCtrl 
*/

export function ControlFocusByHandle(hWnd: number, hCtrl: number): boolean | void {
       return native.ControlFocusByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}



/**
* @zh-cn 获取当前具有焦点的控件句柄 
* @en-us Retrieves the handle of the control with focus.
* @link https://documentation.help/AutoItX/ControlGetFocus.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function ControlGetFocus(Title: string, Text: string = ""): string | void {
       return native.ControlGetFocus(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用控件句柄获取当前具有焦点的控件句柄 
* @en-us Same as `AU3_ControlGetFocus` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlGetFocus.htm
* @param hWnd 窗口句柄数字
*/

export function ControlGetFocusByHandle(hWnd: number): string | void {
       return native.ControlGetFocusByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 获取控件句柄 
* @en-us Retrieves the handle of a control in a window.
* @link https://documentation.help/AutoItX/ControlGetHandle.htm
* @param hWnd 窗口句柄数字
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/

export function ControlGetHandle(hWnd: number, Control: string): number | void {
       return native.ControlGetHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.string(typeof Control == "undefined" ? "" : Control));
}



/**
* @zh-cn 获取控件句柄并返回为文本 
* @en-us Retrieves the handle of a control in a window as text.
* @link https://documentation.help/AutoItX/ControlGetHandleAsText.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/

export function ControlGetHandleAsText(Title: string, Text: string, Control: string): string | void {
       return native.ControlGetHandleAsText(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control));
}



/**
* @zh-cn 获取控件的位置和尺寸 
* @en-us Retrieves the position and size of a control in a window.
* @link https://documentation.help/AutoItX/ControlGetPos.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/

export function ControlGetPos(Title: string, Text: string, Control: string): { left: number, top: number, right: number, bottom: number } | void {
       return native.ControlGetPos(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control));
}



/**
* @zh-cn 使用控件句柄获取控件的位置和尺寸 
* @en-us Same as `AU3_ControlGetPos` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlGetPos.htm
* @param hWnd 窗口句柄数字
* @param hCtrl 
*/

export function ControlGetPosByHandle(hWnd: number, hCtrl: number): { left: number, top: number, right: number, bottom: number } | void {
       return native.ControlGetPosByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}



/**
* @zh-cn 获取控件的文本内容 
* @en-us Retrieves the text from a control in a window.
* @link https://documentation.help/AutoItX/ControlGetText.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/

export function ControlGetText(Title: string, Text: string, Control: string): string | void {
       return native.ControlGetText(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control));
}



/**
* @zh-cn 使用控件句柄获取控件的文本内容 
* @en-us Same as `AU3_ControlGetText` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlGetText.htm
* @param hWnd 窗口句柄数字
* @param hCtrl 
*/

export function ControlGetTextByHandle(hWnd: number, hCtrl: number): string | void {
       return native.ControlGetTextByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}



/**
* @zh-cn 隐藏控件 
* @en-us Hides a control in a window.
* @link https://documentation.help/AutoItX/ControlHide.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/

export function ControlHide(Title: string, Text: string, Control: string): boolean | void {
       return native.ControlHide(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control));
}



/**
* @zh-cn 使用控件句柄隐藏控件 
* @en-us Same as `AU3_ControlHide` but uses a handle instead of window and control IDs.
* @link https://documentation.help/AutoItX/ControlHide.htm
* @param hWnd 窗口句柄数字
* @param hCtrl 
*/

export function ControlHideByHandle(hWnd: number, hCtrl: number): boolean | void {
       return native.ControlHideByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}



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

export function ControlMove(Title: string, Text: string, Control: string, nX: number, nY: number, nWidth: number = -1, nHeight: number = -1): boolean | void {
       return native.ControlMove(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control),
              ref.int(typeof nX == "undefined" ? 0 : nX),
              ref.int(typeof nY == "undefined" ? 0 : nY),
              ref.int(typeof nWidth == "undefined" ? -1 : nWidth),
              ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}



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

export function ControlMoveByHandle(hWnd: number, hCtrl: number, nX: number, nY: number, nWidth: number = -1, nHeight: number = -1): boolean | void {
       return native.ControlMoveByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl),
              ref.int(typeof nX == "undefined" ? 0 : nX),
              ref.int(typeof nY == "undefined" ? 0 : nY),
              ref.int(typeof nWidth == "undefined" ? -1 : nWidth),
              ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}



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

export function ControlSend(Title: string, Text: string, Control: string, SendText: string, nMode: number = 0): boolean | void {
       return native.ControlSend(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control),
              ref.string(typeof SendText == "undefined" ? "" : SendText),
              ref.int(typeof nMode == "undefined" ? 0 : nMode));
}



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

export function ControlSendByHandle(hWnd: number, hCtrl: number, SendText: string, nMode: number = 0): boolean | void {
       return native.ControlSendByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl),
              ref.string(typeof SendText == "undefined" ? "" : SendText),
              ref.int(typeof nMode == "undefined" ? 0 : nMode));
}



/**
* @zh-cn 设置控件的文本内容 
* @en-us Sets the text of a control in a window.
* @link https://documentation.help/AutoItX/ControlSetText.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
* @param ControlText 
*/

export function ControlSetText(Title: string, Text: string, Control: string, ControlText: string): boolean | void {
       return native.ControlSetText(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control),
              ref.string(typeof ControlText == "undefined" ? "" : ControlText));
}



/**
* @zh-cn 使用控件句柄设置控件的文本内容 
* @en-us Sets the text of a control in a window using its handle.
* @link https://documentation.help/AutoItX/ControlSetText.htm
* @param hWnd 窗口句柄数字
* @param hCtrl 
* @param SendText 发送的文本内容
*/

export function ControlSetTextByHandle(hWnd: number, hCtrl: number, SendText: string): boolean | void {
       return native.ControlSetTextByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl),
              ref.string(typeof SendText == "undefined" ? "" : SendText));
}



/**
* @zh-cn 显示控件 
* @en-us Shows a control in a window.
* @link https://documentation.help/AutoItX/ControlShow.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param Control 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
*/

export function ControlShow(Title: string, Text: string, Control: string): boolean | void {
       return native.ControlShow(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control));
}



/**
* @zh-cn 使用控件句柄显示控件 
* @en-us Shows a control in a window using its handle.
* @link https://documentation.help/AutoItX/ControlShow.htm
* @param hWnd 窗口句柄数字
* @param hCtrl 
*/

export function ControlShowByHandle(hWnd: number, hCtrl: number): boolean | void {
       return native.ControlShowByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl));
}



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

export function ControlTreeView(Title: string, Text: string, Control: string, Command: string, Extra1: string, Extra2: string): string | void {
       return native.ControlTreeView(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Control == "undefined" ? "" : Control),
              ref.string(typeof Command == "undefined" ? "" : Command),
              ref.string(typeof Extra1 == "undefined" ? "" : Extra1),
              ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}



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

export function ControlTreeViewByHandle(hWnd: number, hCtrl: number, Command: string, Extra1: string, Extra2: string): string | void {
       return native.ControlTreeViewByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof hCtrl == "undefined" ? 0 : hCtrl),
              ref.string(typeof Command == "undefined" ? "" : Command),
              ref.string(typeof Extra1 == "undefined" ? "" : Extra1),
              ref.string(typeof Extra2 == "undefined" ? "" : Extra2));
}



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

export function DriveMapAdd(Device: string, Share: string, nFlags: number, User: string = "", Pwd: string = ""): string | void {
       return native.DriveMapAdd(ref.string(typeof Device == "undefined" ? "" : Device),
              ref.string(typeof Share == "undefined" ? "" : Share),
              ref.int(typeof nFlags == "undefined" ? 0 : nFlags),
              ref.string(typeof User == "undefined" ? "" : User),
              ref.string(typeof Pwd == "undefined" ? "" : Pwd));
}



/**
* @zh-cn 取消驱动器映射 
* @en-us Unmaps a network drive.
* @link https://documentation.help/AutoItX/DriveMapDel.htm
* @param Device 
*/

export function DriveMapDel(Device: string): boolean | void {
       return native.DriveMapDel(ref.string(typeof Device == "undefined" ? "" : Device));
}



/**
* @zh-cn 获取驱动器映射的信息 
* @en-us Retrieves the mapping of a network drive.
* @link https://documentation.help/AutoItX/DriveMapGet.htm
* @param Device 
*/

export function DriveMapGet(Device: string): string | void {
       return native.DriveMapGet(ref.string(typeof Device == "undefined" ? "" : Device));
}



/**
* @zh-cn 检查当前用户是否有管理员权限 
* @en-us Checks if the current process is running with administrative privileges.
* @link https://documentation.help/AutoItX/IsAdmin.htm
*/

export function IsAdmin(): boolean | void {
       return native.IsAdmin();
}



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

export function MouseClick(Button: string = "LEFT", nX: number = AU3_INTDEFAULT, nY: number = AU3_INTDEFAULT, nClicks: number = 1, nSpeed: number = -1): undefined | void {
       return native.MouseClick(ref.string(typeof Button == "undefined" ? "LEFT" : Button),
              ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX),
              ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY),
              ref.int(typeof nClicks == "undefined" ? 1 : nClicks),
              ref.int(typeof nSpeed == "undefined" ? -1 : nSpeed));
}



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

export function MouseClickDrag(Button: string, nX1: number, nY1: number, nX2: number, nY2: number, nSpeed: number = -1): undefined | void {
       return native.MouseClickDrag(ref.string(typeof Button == "undefined" ? "" : Button),
              ref.int(typeof nX1 == "undefined" ? 0 : nX1),
              ref.int(typeof nY1 == "undefined" ? 0 : nY1),
              ref.int(typeof nX2 == "undefined" ? 0 : nX2),
              ref.int(typeof nY2 == "undefined" ? 0 : nY2),
              ref.int(typeof nSpeed == "undefined" ? -1 : nSpeed));
}



/**
* @zh-cn 模拟鼠标按下 
* @en-us Simulates pressing a mouse button.
* @link https://documentation.help/AutoItX/MouseDown.htm
* @param Button 
* @default "LEFT"
*/

export function MouseDown(Button: string = "LEFT"): undefined | void {
       return native.MouseDown(ref.string(typeof Button == "undefined" ? "LEFT" : Button));
}



/**
* @zh-cn 获取鼠标当前的光标样式 
* @en-us Retrieves the mouse cursor's current shape.
* @link https://documentation.help/AutoItX/MouseGetCursor.htm
*/

export function MouseGetCursor(): number | void {
       return native.MouseGetCursor();
}



/**
* @zh-cn 获取鼠标当前位置 
* @en-us Retrieves the current position of the mouse cursor.
* @link https://documentation.help/AutoItX/MouseGetPos.htm
*/

export function MouseGetPos(): { x: number, y: number } | void {
       return native.MouseGetPos();
}



/**
* @zh-cn 移动鼠标到指定位置 
* @en-us Moves the mouse cursor to a specified position.
* @link https://documentation.help/AutoItX/MouseMove.htm
* @param nX x (left To Right) 
* @param nY y (top To Bottom) 
* @param nSpeed 
* @default -1
*/

export function MouseMove(nX: number, nY: number, nSpeed: number = -1): number | void {
       return native.MouseMove(ref.int(typeof nX == "undefined" ? 0 : nX),
              ref.int(typeof nY == "undefined" ? 0 : nY),
              ref.int(typeof nSpeed == "undefined" ? -1 : nSpeed));
}



/**
* @zh-cn 模拟鼠标释放 
* @en-us Simulates releasing a mouse button.
* @link https://documentation.help/AutoItX/MouseUp.htm
* @param Button 
* @default "LEFT"
*/

export function MouseUp(Button: string = "LEFT"): undefined | void {
       return native.MouseUp(ref.string(typeof Button == "undefined" ? "LEFT" : Button));
}



/**
* @zh-cn 模拟鼠标滚轮滚动 
* @en-us Simulates scrolling the mouse wheel.
* @link https://documentation.help/AutoItX/MouseWheel.htm
* @param Direction 
* @param nClicks 
*/

export function MouseWheel(Direction: string, nClicks: number): undefined | void {
       return native.MouseWheel(ref.string(typeof Direction == "undefined" ? "" : Direction),
              ref.int(typeof nClicks == "undefined" ? 0 : nClicks));
}



/**
* @zh-cn 设置AutoIt选项 
* @en-us Sets options for AutoItX
* @link https://documentation.help/AutoItX/Opt.htm
* @param Option 
* @param nValue 
*/

export function Opt(Option: string, nValue: number): number | void {
       return native.Opt(ref.string(typeof Option == "undefined" ? "" : Option),
              ref.int(typeof nValue == "undefined" ? 0 : nValue));
}



/**
* @zh-cn 获取屏幕区域的像素校验和 
* @en-us Calculates a checksum of a region of pixels on the screen.
* @link https://documentation.help/AutoItX/PixelChecksum.htm
* @param lpRect 位置
* @param nStep 
* @default 1
*/

export function PixelChecksum(lpRect: { left: number, top: number, right: number, bottom: number }, nStep: number = 1): number | void {
       return native.PixelChecksum({
              left: ref.int(lpRect.left),
              top: ref.int(lpRect.top),
              right: ref.int(lpRect.right),
              bottom: ref.int(lpRect.bottom)
       },
              ref.int(typeof nStep == "undefined" ? 1 : nStep));
}



/**
* @zh-cn 获取屏幕上指定位置的像素颜色 
* @en-us Retrieves the color of a pixel at a specified position.
* @link https://documentation.help/AutoItX/PixelGetColor.htm
* @param nX x (left To Right) 
* @param nY y (top To Bottom) 
*/

export function PixelGetColor(nX: number, nY: number): number | void {
       return native.PixelGetColor(ref.int(typeof nX == "undefined" ? 0 : nX),
              ref.int(typeof nY == "undefined" ? 0 : nY));
}



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

export function PixelSearch(lpRect: { left: number, top: number, right: number, bottom: number }, nCol: number, nVar: number = 0, nStep: number = 1): { x: number, y: number } | void {
       return native.PixelSearch({
              left: ref.int(lpRect.left),
              top: ref.int(lpRect.top),
              right: ref.int(lpRect.right),
              bottom: ref.int(lpRect.bottom)
       },
              ref.int(typeof nCol == "undefined" ? 0 : nCol),
              ref.int(typeof nVar == "undefined" ? 0 : nVar),
              ref.int(typeof nStep == "undefined" ? 1 : nStep));
}



/**
* @zh-cn 关闭进程 
* @en-us Closes a specified process.
* @link https://documentation.help/AutoItX/ProcessClose.htm
* @param Process 进程名称
*/

export function ProcessClose(Process: string): undefined | void {
       return native.ProcessClose(ref.string(typeof Process == "undefined" ? "" : Process));
}



/**
* @zh-cn 检查进程是否存在 
* @en-us Checks if a specified process exists.
* @link https://documentation.help/AutoItX/ProcessExists.htm
* @param Process 进程名称
*/

export function ProcessExists(Process: string): boolean | void {
       return native.ProcessExists(ref.string(typeof Process == "undefined" ? "" : Process));
}



/**
* @zh-cn 设置进程的优先级 
* @en-us Sets the priority of a specified process.
* @link https://documentation.help/AutoItX/ProcessSetPriority.htm
* @param Process 进程名称
* @param nPriority 
*/

export function ProcessSetPriority(Process: string, nPriority: number): boolean | void {
       return native.ProcessSetPriority(ref.string(typeof Process == "undefined" ? "" : Process),
              ref.int(typeof nPriority == "undefined" ? 0 : nPriority));
}



/**
* @zh-cn 等待进程的出现 
* @en-us Waits for a specified process to exist.
* @link https://documentation.help/AutoItX/ProcessWait.htm
* @param Process 进程名称
* @param nTimeout 
* @default 0
*/

export function ProcessWait(Process: string, nTimeout: number = 0): boolean | void {
       return native.ProcessWait(ref.string(typeof Process == "undefined" ? "" : Process),
              ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}



/**
* @zh-cn 等待进程的结束 
* @en-us Waits for a specified process to close.
* @link https://documentation.help/AutoItX/ProcessWaitClose.htm
* @param Process 进程名称
* @param nTimeout 
* @default 0
*/

export function ProcessWaitClose(Process: string, nTimeout: number = 0): boolean | void {
       return native.ProcessWaitClose(ref.string(typeof Process == "undefined" ? "" : Process),
              ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}



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

export function Run(Program: string, Dir: string = "", nShowFlag: number = SW_SHOWNORMAL): number | void {
       return native.Run(ref.string(typeof Program == "undefined" ? "" : Program),
              ref.string(typeof Dir == "undefined" ? "" : Dir),
              ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}



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

export function RunWait(Program: string, Dir: string = "", nShowFlag: number = SW_SHOWNORMAL): number | void {
       return native.RunWait(ref.string(typeof Program == "undefined" ? "" : Program),
              ref.string(typeof Dir == "undefined" ? "" : Dir),
              ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}



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

export function RunAs(User: string, Domain: string, Password: string, nLogonFlag: number, Program: string, Dir: string = "", nShowFlag: number = SW_SHOWNORMAL): number | void {
       return native.RunAs(ref.string(typeof User == "undefined" ? "" : User),
              ref.string(typeof Domain == "undefined" ? "" : Domain),
              ref.string(typeof Password == "undefined" ? "" : Password),
              ref.int(typeof nLogonFlag == "undefined" ? 0 : nLogonFlag),
              ref.string(typeof Program == "undefined" ? "" : Program),
              ref.string(typeof Dir == "undefined" ? "" : Dir),
              ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}



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

export function RunAsWait(User: string, Domain: string, Password: string, nLogonFlag: number, Program: string, Dir: string = "", nShowFlag: number = SW_SHOWNORMAL): number | void {
       return native.RunAsWait(ref.string(typeof User == "undefined" ? "" : User),
              ref.string(typeof Domain == "undefined" ? "" : Domain),
              ref.string(typeof Password == "undefined" ? "" : Password),
              ref.int(typeof nLogonFlag == "undefined" ? 0 : nLogonFlag),
              ref.string(typeof Program == "undefined" ? "" : Program),
              ref.string(typeof Dir == "undefined" ? "" : Dir),
              ref.int(typeof nShowFlag == "undefined" ? SW_SHOWNORMAL : nShowFlag));
}



/**
* @zh-cn 向活动窗口发送按键输入 
* @en-us Sends simulated keystrokes.
* @link https://documentation.help/AutoItX/Send.htm
* @param SendText 发送的文本内容
* @param nMode 
* @default 0
*/

export function Send(SendText: string, nMode: number = 0): undefined | void {
       return native.Send(ref.string(typeof SendText == "undefined" ? "" : SendText),
              ref.int(typeof nMode == "undefined" ? 0 : nMode));
}



/**
* @zh-cn 关闭或重启系统 
* @en-us Shuts down, restarts, or logs off the computer.
* @link https://documentation.help/AutoItX/Shutdown.htm
* @param nFlags 
*/

export function Shutdown(nFlags: number): boolean | void {
       return native.Shutdown(ref.int(typeof nFlags == "undefined" ? 0 : nFlags));
}



/**
* @zh-cn 在脚本中加入暂停/延迟 
* @en-us Pauses the script for a specified number of milliseconds.
* @link https://documentation.help/AutoItX/Sleep.htm
* @param nMilliseconds 
*/

export function Sleep(nMilliseconds: number): undefined | void {
       return native.Sleep(ref.int(typeof nMilliseconds == "undefined" ? 0 : nMilliseconds));
}



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

export function StatusbarGetText(Title: string = "", Text: string = "", nPart: number = 1): string | void {
       return native.StatusbarGetText(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.int(typeof nPart == "undefined" ? 1 : nPart));
}



/**
* @zh-cn 使用控件句柄获取状态栏的文本内容 
* @en-us Retrieves the text from the status bar of a window using its handle.
* @link https://documentation.help/AutoItX/StatusbarGetText.htm
* @param hWnd 窗口句柄数字
* @param nPart 
* @default 1
*/

export function StatusbarGetTextByHandle(hWnd: number, nPart: number = 1): string | void {
       return native.StatusbarGetTextByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof nPart == "undefined" ? 1 : nPart));
}



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

export function ToolTip(Tip: string, nX: number = AU3_INTDEFAULT, nY: number = AU3_INTDEFAULT): undefined | void {
       return native.ToolTip(ref.string(typeof Tip == "undefined" ? "" : Tip),
              ref.int(typeof nX == "undefined" ? AU3_INTDEFAULT : nX),
              ref.int(typeof nY == "undefined" ? AU3_INTDEFAULT : nY));
}



/**
* @zh-cn 激活指定的窗口 
* @en-us Activates a window by title or window handle.
* @link https://documentation.help/AutoItX/WinActivate.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinActivate(Title: string, Text: string = ""): boolean | void {
       return native.WinActivate(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄激活指定的窗口 
* @en-us Activates a window using its handle.
* @link https://documentation.help/AutoItX/WinActivate.htm
* @param hWnd 窗口句柄数字
*/

export function WinActivateByHandle(hWnd: number): boolean | void {
       return native.WinActivateByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 检查指定的窗口是否处于活动状态 
* @en-us Checks if a window is currently active by title.
* @link https://documentation.help/AutoItX/WinActive.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinActive(Title: string, Text: string = ""): boolean | void {
       return native.WinActive(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄检查指定的窗口是否处于活动状态 
* @en-us Checks if a window is currently active using its handle.
* @link https://documentation.help/AutoItX/WinActive.htm
* @param hWnd 窗口句柄数字
*/

export function WinActiveByHandle(hWnd: number): boolean | void {
       return native.WinActiveByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 关闭指定的窗口 
* @en-us Closes a window by title.
* @link https://documentation.help/AutoItX/WinClose.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinClose(Title: string, Text: string = ""): boolean | void {
       return native.WinClose(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄关闭指定的窗口 
* @en-us Closes a window using its handle.
* @link https://documentation.help/AutoItX/WinClose.htm
* @param hWnd 窗口句柄数字
*/

export function WinCloseByHandle(hWnd: number): boolean | void {
       return native.WinCloseByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 检查指定的窗口是否存在 
* @en-us Checks if a window exists by title.
* @link https://documentation.help/AutoItX/WinExists.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinExists(Title: string, Text: string = ""): boolean | void {
       return native.WinExists(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄检查指定的窗口是否存在 
* @en-us Checks if a window exists using its handle.
* @link https://documentation.help/AutoItX/WinExists.htm
* @param hWnd 窗口句柄数字
*/

export function WinExistsByHandle(hWnd: number): boolean | void {
       return native.WinExistsByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 获取当前光标的位置 
* @en-us Retrieves the position of the caret in the active window.
* @link https://documentation.help/AutoItX/WinGetCaretPos.htm
*/

export function WinGetCaretPos(): { x: number, y: number } | void {
       return native.WinGetCaretPos();
}



/**
* @zh-cn 获取指定窗口的类名列表 
* @en-us Retrieves a list of classes used by a window by title.
* @link https://documentation.help/AutoItX/WinGetClassList.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinGetClassList(Title: string, Text: string = ""): string | void {
       return native.WinGetClassList(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄获取指定窗口的类名列表 
* @en-us Retrieves a list of classes used by a window using its handle.
* @link https://documentation.help/AutoItX/WinGetClassList.htm
* @param hWnd 窗口句柄数字
*/

export function WinGetClassListByHandle(hWnd: number): string | void {
       return native.WinGetClassListByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 获取指定窗口客户区的尺寸 
* @en-us Retrieves the client area's size of a window by title.
* @link https://documentation.help/AutoItX/WinGetClientSize.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinGetClientSize(Title: string, Text: string = ""): { left: number, top: number, right: number, bottom: number } | void {
       return native.WinGetClientSize(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄获取指定窗口客户区的尺寸 
* @en-us Retrieves the client area's size of a window using its handle.
* @link https://documentation.help/AutoItX/WinGetClientSize.htm
* @param hWnd 窗口句柄数字
*/

export function WinGetClientSizeByHandle(hWnd: number): { left: number, top: number, right: number, bottom: number } | void {
       return native.WinGetClientSizeByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 获取指定窗口的句柄 
* @en-us Retrieves the handle of a window by title.
* @link https://documentation.help/AutoItX/WinGetHandle.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinGetHandle(Title: string, Text: string = ""): number | void {
       return native.WinGetHandle(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 获取指定窗口的句柄并返回为文本 
* @en-us Retrieves the handle of a window by title as text.
* @link https://documentation.help/AutoItX/WinGetHandleAsText.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinGetHandleAsText(Title: string, Text: string = ""): string | void {
       return native.WinGetHandleAsText(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 获取指定窗口的位置和尺寸 
* @en-us Retrieves the position and size of a window by title.
* @link https://documentation.help/AutoItX/WinGetPos.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinGetPos(Title: string, Text: string = ""): { left: number, top: number, right: number, bottom: number } | void {
       return native.WinGetPos(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄获取指定窗口的位置和尺寸 
* @en-us Retrieves the position and size of a window using its handle.
* @link https://documentation.help/AutoItX/WinGetPos.htm
* @param hWnd 窗口句柄数字
*/

export function WinGetPosByHandle(hWnd: number): { left: number, top: number, right: number, bottom: number } | void {
       return native.WinGetPosByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 获取指定窗口的进程ID 
* @en-us Retrieves the process ID of a window by title.
* @link https://documentation.help/AutoItX/WinGetProcess.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinGetProcess(Title: string, Text: string = ""): undefined | void {
       return native.WinGetProcess(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄获取指定窗口的进程ID 
* @en-us Retrieves the process ID of a window using its handle.
* @link https://documentation.help/AutoItX/WinGetProcess.htm
* @param hWnd 窗口句柄数字
*/

export function WinGetProcessByHandle(hWnd: number): undefined | void {
       return native.WinGetProcessByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 获取指定窗口的状态 
* @en-us Retrieves the state of a window by title (minimized, maximized, etc.).
* @link https://documentation.help/AutoItX/WinGetState.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinGetState(Title: string, Text: string = ""): number | void {
       return native.WinGetState(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄获取指定窗口的状态 
* @en-us Retrieves the state of a window using its handle.
* @link https://documentation.help/AutoItX/WinGetState.htm
* @param hWnd 窗口句柄数字
*/

export function WinGetStateByHandle(hWnd: number): number | void {
       return native.WinGetStateByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 获取指定窗口的文本内容 
* @en-us Retrieves the text from a window by title.
* @link https://documentation.help/AutoItX/WinGetText.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinGetText(Title: string, Text: string = ""): string | void {
       return native.WinGetText(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄获取指定窗口的文本内容 
* @en-us Retrieves the text from a window using its handle.
* @link https://documentation.help/AutoItX/WinGetText.htm
* @param hWnd 窗口句柄数字
*/

export function WinGetTextByHandle(hWnd: number): string | void {
       return native.WinGetTextByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 获取指定窗口的标题 
* @en-us Retrieves the title of a window by title.
* @link https://documentation.help/AutoItX/WinGetTitle.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinGetTitle(Title: string, Text: string = ""): string | void {
       return native.WinGetTitle(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄获取指定窗口的标题 
* @en-us Retrieves the title of a window using its handle.
* @link https://documentation.help/AutoItX/WinGetTitle.htm
* @param hWnd 窗口句柄数字
*/

export function WinGetTitleByHandle(hWnd: number): string | void {
       return native.WinGetTitleByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



/**
* @zh-cn 强制关闭指定的窗口 
* @en-us Forces a window to close by title.
* @link https://documentation.help/AutoItX/WinKill.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @default ""
*/

export function WinKill(Title: string, Text: string = ""): boolean | void {
       return native.WinKill(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text));
}



/**
* @zh-cn 使用窗口句柄强制关闭指定的窗口 
* @en-us Forces a window to close using its handle.
* @link https://documentation.help/AutoItX/WinKill.htm
* @param hWnd 窗口句柄数字
*/

export function WinKillByHandle(hWnd: number): boolean | void {
       return native.WinKillByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd));
}



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

export function WinMenuSelectItem(Title: string, Text: string, Item1: string, Item2: string, Item3: string, Item4: string, Item5: string, Item6: string, Item7: string, Item8: string): boolean | void {
       return native.WinMenuSelectItem(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof Item1 == "undefined" ? "" : Item1),
              ref.string(typeof Item2 == "undefined" ? "" : Item2),
              ref.string(typeof Item3 == "undefined" ? "" : Item3),
              ref.string(typeof Item4 == "undefined" ? "" : Item4),
              ref.string(typeof Item5 == "undefined" ? "" : Item5),
              ref.string(typeof Item6 == "undefined" ? "" : Item6),
              ref.string(typeof Item7 == "undefined" ? "" : Item7),
              ref.string(typeof Item8 == "undefined" ? "" : Item8));
}



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

export function WinMenuSelectItemByHandle(hWnd: number, Item1: string, Item2: string, Item3: string, Item4: string, Item5: string, Item6: string, Item7: string, Item8: string): boolean | void {
       return native.WinMenuSelectItemByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.string(typeof Item1 == "undefined" ? "" : Item1),
              ref.string(typeof Item2 == "undefined" ? "" : Item2),
              ref.string(typeof Item3 == "undefined" ? "" : Item3),
              ref.string(typeof Item4 == "undefined" ? "" : Item4),
              ref.string(typeof Item5 == "undefined" ? "" : Item5),
              ref.string(typeof Item6 == "undefined" ? "" : Item6),
              ref.string(typeof Item7 == "undefined" ? "" : Item7),
              ref.string(typeof Item8 == "undefined" ? "" : Item8));
}



/**
* @zh-cn 最小化所有窗口 
* @en-us Minimizes all windows.
* @link https://documentation.help/AutoItX/WinMinimizeAll.htm
*/

export function WinMinimizeAll(): undefined | void {
       return native.WinMinimizeAll();
}



/**
* @zh-cn 恢复最小化的窗口 
* @en-us Undoes the effect of `AU3_WinMinimizeAll`.
* @link https://documentation.help/AutoItX/WinMinimizeAllUndo.htm
*/

export function WinMinimizeAllUndo(): undefined | void {
       return native.WinMinimizeAllUndo();
}



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

export function WinMove(Title: string, Text: string, nX: number, nY: number, nWidth: number = -1, nHeight: number = -1): undefined | void {
       return native.WinMove(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.int(typeof nX == "undefined" ? 0 : nX),
              ref.int(typeof nY == "undefined" ? 0 : nY),
              ref.int(typeof nWidth == "undefined" ? -1 : nWidth),
              ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}



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

export function WinMoveByHandle(hWnd: number, nX: number, nY: number, nWidth: number = -1, nHeight: number = -1): undefined | void {
       return native.WinMoveByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof nX == "undefined" ? 0 : nX),
              ref.int(typeof nY == "undefined" ? 0 : nY),
              ref.int(typeof nWidth == "undefined" ? -1 : nWidth),
              ref.int(typeof nHeight == "undefined" ? -1 : nHeight));
}



/**
* @zh-cn 设置指定窗口在其他窗口之上 
* @en-us Sets a window to be always on top by title.
* @link https://documentation.help/AutoItX/WinSetOnTop.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param nFlag 
*/

export function WinSetOnTop(Title: string, Text: string, nFlag: number): undefined | void {
       return native.WinSetOnTop(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.int(typeof nFlag == "undefined" ? 0 : nFlag));
}



/**
* @zh-cn 使用窗口句柄设置指定窗口在其他窗口之上 
* @en-us Sets a window to be always on top using its handle.
* @link https://documentation.help/AutoItX/WinSetOnTop.htm
* @param hWnd 窗口句柄数字
* @param nFlag 
*/

export function WinSetOnTopByHandle(hWnd: number, nFlag: number): undefined | void {
       return native.WinSetOnTopByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof nFlag == "undefined" ? 0 : nFlag));
}



/**
* @zh-cn 设置指定窗口的状态（最大化、最小化、正常等） 
* @en-us Sets the state of a window by title (minimize, maximize, etc.).
* @link https://documentation.help/AutoItX/WinSetState.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param nFlags 
*/

export function WinSetState(Title: string, Text: string, nFlags: number): undefined | void {
       return native.WinSetState(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.int(typeof nFlags == "undefined" ? 0 : nFlags));
}



/**
* @zh-cn 使用窗口句柄设置指定窗口的状态 
* @en-us Sets the state of a window using its handle.
* @link https://documentation.help/AutoItX/WinSetState.htm
* @param hWnd 窗口句柄数字
* @param nFlags 
*/

export function WinSetStateByHandle(hWnd: number, nFlags: number): undefined | void {
       return native.WinSetStateByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof nFlags == "undefined" ? 0 : nFlags));
}



/**
* @zh-cn 设置指定窗口的标题 
* @en-us Sets the title of a window by title.
* @link https://documentation.help/AutoItX/WinSetTitle.htm
* @param Title 窗口标题
* @param Text 窗口/控件文本
* @param NewTitle 
*/

export function WinSetTitle(Title: string, Text: string, NewTitle: string): undefined | void {
       return native.WinSetTitle(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.string(typeof NewTitle == "undefined" ? "" : NewTitle));
}



/**
* @zh-cn 使用窗口句柄设置指定窗口的标题 
* @en-us Sets the title of a window using its handle.
* @link https://documentation.help/AutoItX/WinSetTitle.htm
* @param hWnd 窗口句柄数字
* @param NewTitle 
*/

export function WinSetTitleByHandle(hWnd: number, NewTitle: string): undefined | void {
       return native.WinSetTitleByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.string(typeof NewTitle == "undefined" ? "" : NewTitle));
}



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

export function WinSetTrans(Title: string, Text: string = "", nTrans: number = 255): boolean | void {
       return native.WinSetTrans(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.int(typeof nTrans == "undefined" ? 255 : nTrans));
}



/**
* @zh-cn 使用窗口句柄设置指定窗口的透明度 
* @en-us Sets the transparency level of a window using its handle.
* @link https://documentation.help/AutoItX/WinSetTrans.htm
* @param hWnd 窗口句柄数字
* @param nTrans 不透明度 阿尔法通道值  0 - 255 
*/

export function WinSetTransByHandle(hWnd: number, nTrans: number): boolean | void {
       return native.WinSetTransByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof nTrans == "undefined" ? 0 : nTrans));
}



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

export function WinWait(Title: string, Text: string = "", nTimeout: number = 0): boolean | void {
       return native.WinWait(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}



/**
* @zh-cn 使用窗口句柄等待指定的窗口出现 
* @en-us Waits for a window to exist using its handle.
* @link https://documentation.help/AutoItX/WinWait.htm
* @param hWnd 窗口句柄数字
* @param nTimeout 
*/

export function WinWaitByHandle(hWnd: number, nTimeout: number): boolean | void {
       return native.WinWaitByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}



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

export function WinWaitActive(Title: string, Text: string = "", nTimeout: number = 0): boolean | void {
       return native.WinWaitActive(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}



/**
* @zh-cn 使用窗口句柄等待指定的窗口处于活动状态 
* @en-us Waits for a window to be active using its handle.
* @link https://documentation.help/AutoItX/WinWaitActive.htm
* @param hWnd 窗口句柄数字
* @param nTimeout 
*/

export function WinWaitActiveByHandle(hWnd: number, nTimeout: number): boolean | void {
       return native.WinWaitActiveByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}



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

export function WinWaitClose(Title: string, Text: string = "", nTimeout: number = 0): boolean | void {
       return native.WinWaitClose(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}



/**
* @zh-cn 使用窗口句柄等待指定的窗口关闭 
* @en-us Waits for a window to close using its handle.
* @link https://documentation.help/AutoItX/WinWaitClose.htm
* @param hWnd 窗口句柄数字
* @param nTimeout 
*/

export function WinWaitCloseByHandle(hWnd: number, nTimeout: number): boolean | void {
       return native.WinWaitCloseByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}



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

export function WinWaitNotActive(Title: string = "", Text: string = "", nTimeout: number = 0): boolean | void {
       return native.WinWaitNotActive(ref.string(typeof Title == "undefined" ? "" : Title),
              ref.string(typeof Text == "undefined" ? "" : Text),
              ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}



/**
* @zh-cn 使用窗口句柄等待指定的窗口不处于活动状态 
* @en-us Waits for a window to be not active using its handle.
* @link https://documentation.help/AutoItX/WinWaitNotActive.htm
* @param hWnd 窗口句柄数字
* @param nTimeout 
* @default 0
*/

export function WinWaitNotActiveByHandle(hWnd: number, nTimeout: number = 0): boolean | void {
       return native.WinWaitNotActiveByHandle(ref.int(typeof hWnd == "undefined" ? 0 : hWnd),
              ref.int(typeof nTimeout == "undefined" ? 0 : nTimeout));
}

