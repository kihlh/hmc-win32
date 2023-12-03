export declare const native: HMN.Native;
export declare module HMN {
    interface Native {
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
        ControlGetPos(Title: string, Text: string, Control: string): {
            left: number;
            top: number;
            right: number;
            bottom: number;
        } | void;
        ControlGetPosByHandle(hWnd: number, hCtrl: number): {
            left: number;
            top: number;
            right: number;
            bottom: number;
        } | void;
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
        MouseGetPos(): {
            x: number;
            y: number;
        } | void;
        MouseMove(nX: number, nY: number, nSpeed?: number): number | void;
        MouseUp(Button?: string): undefined | void;
        MouseWheel(Direction: string, nClicks: number): undefined | void;
        Opt(Option: string, nValue: number): number | void;
        PixelChecksum(lpRect: {
            left: number;
            top: number;
            right: number;
            bottom: number;
        }, nStep?: number): number | void;
        PixelGetColor(nX: number, nY: number): number | void;
        PixelSearch(lpRect: {
            left: number;
            top: number;
            right: number;
            bottom: number;
        }, nCol: number, nVar?: number, nStep?: number): {
            x: number;
            y: number;
        } | void;
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
        WinGetCaretPos(): {
            x: number;
            y: number;
        } | void;
        WinGetClassList(Title: string, Text?: string): string | void;
        WinGetClassListByHandle(hWnd: number): string | void;
        WinGetClientSize(Title: string, Text?: string): {
            left: number;
            top: number;
            right: number;
            bottom: number;
        } | void;
        WinGetClientSizeByHandle(hWnd: number): {
            left: number;
            top: number;
            right: number;
            bottom: number;
        } | void;
        WinGetHandle(Title: string, Text?: string): number | void;
        WinGetHandleAsText(Title: string, Text?: string): string | void;
        WinGetPos(Title: string, Text?: string): {
            left: number;
            top: number;
            right: number;
            bottom: number;
        } | void;
        WinGetPosByHandle(hWnd: number): {
            left: number;
            top: number;
            right: number;
            bottom: number;
        } | void;
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
export declare const ref: {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str: any): string;
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool: any): boolean;
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str: any): string;
    /**
     * 格式化数字为int(强制)
     * @param Num
     * @returns
     */
    int(Num: any): number;
    /**
     * 文本数组
     * @param array
     * @returns
     */
    stringArray(array: Set<any> | Array<any>): string[];
    /**
     * 文本数组
     * @param array
     * @returns
     */
    intArray(array: Set<any> | Array<any>): number[];
    /**
     * 拼合buff片段
     * @param buffList
     * @returns
     */
    concatBuff(buffList: Buffer[]): Buffer;
};
/**
 * 初始化AutoItX，通常在开始使用AutoItX函数之前调用
 * @returns
 */
export declare function Init(): undefined | void;
/**
 * 获取上一次AutoItX函数调用返回的错误代码
 * @returns
 */
export declare function error(): number | void;
/**
 * 设置AutoIt的选项，可以用来配置AutoIt的一些行为
 * @param Option
 * @param nValue
 * @returns
 */
export declare function AutoItSetOption(Option: string, nValue: number): number | void;
/**
 * @zh-cn 获取剪贴板的内容
 * @en-us Retrieves the content of the Windows clipboard.
 * @returns
 */
export declare function ClipGet(): string | void;
export declare function ClipPut(intput: string): undefined | void;
export declare function ControlClick(szTitle: string, szText: string, szControl: string, szButton?: string, nNumClicks?: number, nX?: number, nY?: number): boolean | void;
export declare function ControlClickByHandle(hWnd: number, hCtrl: number, szButton?: string, nNumClicks?: number, nX?: number, nY?: number): number | void;
export declare function ControlCommand(Title: string, Text: string, Control: string, Command: string, Extra?: string): string | void;
export declare function ControlCommandByHandle(hWnd: number, hCtrl: number, Command: string, Extra?: string): string | void;
export declare function ControlListView(Title: string, Text: string, Control: string, Command: string, Extra1: string, Extra2: string): string | void;
export declare function ControlListViewByHandle(hWnd: number, hCtrl: number, Command: string, Extra1: string, Extra2: string): string | void;
export declare function ControlDisable(Title: string, Text: string, Control: string): boolean | void;
export declare function ControlDisableByHandle(hWnd: number, hCtrl: number): boolean | void;
export declare function ControlEnable(Title: string, Text: string, Control: string): boolean | void;
export declare function ControlEnableByHandle(hWnd: number, hCtrl: number): boolean | void;
export declare function ControlFocus(Title: string, Text: string, Control: string): boolean | void;
export declare function ControlFocusByHandle(hWnd: number, hCtrl: number): boolean | void;
export declare function ControlGetFocus(Title: string, Text?: string): string | void;
export declare function ControlGetFocusByHandle(hWnd: number): string | void;
export declare function ControlGetHandle(hWnd: number, Control: string): number | void;
export declare function ControlGetHandleAsText(Title: string, Text: string, Control: string): string | void;
export declare function ControlGetPos(Title: string, Text: string, Control: string): {
    left: number;
    top: number;
    right: number;
    bottom: number;
} | void;
export declare function ControlGetPosByHandle(hWnd: number, hCtrl: number): {
    left: number;
    top: number;
    right: number;
    bottom: number;
} | void;
export declare function ControlGetText(Title: string, Text: string, Control: string): string | void;
export declare function ControlGetTextByHandle(hWnd: number, hCtrl: number): string | void;
export declare function ControlHide(Title: string, Text: string, Control: string): boolean | void;
export declare function ControlHideByHandle(hWnd: number, hCtrl: number): boolean | void;
export declare function ControlMove(Title: string, Text: string, Control: string, nX: number, nY: number, nWidth?: number, nHeight?: number): boolean | void;
export declare function ControlMoveByHandle(hWnd: number, hCtrl: number, nX: number, nY: number, nWidth?: number, nHeight?: number): boolean | void;
export declare function ControlSend(Title: string, Text: string, Control: string, SendText: string, nMode?: number): boolean | void;
export declare function ControlSendByHandle(hWnd: number, hCtrl: number, SendText: string, nMode?: number): boolean | void;
export declare function ControlSetText(Title: string, Text: string, Control: string, ControlText: string): boolean | void;
export declare function ControlSetTextByHandle(hWnd: number, hCtrl: number, SendText: string): boolean | void;
export declare function ControlShow(Title: string, Text: string, Control: string): boolean | void;
export declare function ControlShowByHandle(hWnd: number, hCtrl: number): boolean | void;
export declare function ControlTreeView(Title: string, Text: string, Control: string, Command: string, Extra1: string, Extra2: string): string | void;
export declare function ControlTreeViewByHandle(hWnd: number, hCtrl: number, Command: string, Extra1: string, Extra2: string): string | void;
export declare function DriveMapAdd(Device: string, Share: string, nFlags: number, User?: string, Pwd?: string): string | void;
export declare function DriveMapDel(Device: string): boolean | void;
export declare function DriveMapGet(Device: string): string | void;
export declare function IsAdmin(): boolean | void;
export declare function MouseClick(Button?: string, nX?: number, nY?: number, nClicks?: number, nSpeed?: number): undefined | void;
export declare function MouseClickDrag(Button: string, nX1: number, nY1: number, nX2: number, nY2: number, nSpeed?: number): undefined | void;
export declare function MouseDown(Button?: string): undefined | void;
export declare function MouseGetCursor(): number | void;
export declare function MouseGetPos(): {
    x: number;
    y: number;
} | void;
export declare function MouseMove(nX: number, nY: number, nSpeed?: number): number | void;
export declare function MouseUp(Button?: string): undefined | void;
export declare function MouseWheel(Direction: string, nClicks: number): undefined | void;
export declare function Opt(Option: string, nValue: number): number | void;
export declare function PixelChecksum(lpRect: {
    left: number;
    top: number;
    right: number;
    bottom: number;
}, nStep?: number): number | void;
export declare function PixelGetColor(nX: number, nY: number): number | void;
export declare function PixelSearch(lpRect: {
    left: number;
    top: number;
    right: number;
    bottom: number;
}, nCol: number, nVar?: number, nStep?: number): {
    x: number;
    y: number;
} | void;
export declare function ProcessClose(Process: string): undefined | void;
export declare function ProcessExists(Process: string): boolean | void;
export declare function ProcessSetPriority(Process: string, nPriority: number): boolean | void;
export declare function ProcessWait(Process: string, nTimeout?: number): boolean | void;
export declare function ProcessWaitClose(Process: string, nTimeout?: number): boolean | void;
export declare function Run(Program: string, Dir?: string, nShowFlag?: number): number | void;
export declare function RunWait(Program: string, Dir?: string, nShowFlag?: number): number | void;
export declare function RunAs(User: string, Domain: string, Password: string, nLogonFlag: number, Program: string, Dir?: string, nShowFlag?: number): number | void;
export declare function RunAsWait(User: string, Domain: string, Password: string, nLogonFlag: number, Program: string, Dir?: string, nShowFlag?: number): number | void;
export declare function Send(SendText: string, nMode?: number): undefined | void;
export declare function Shutdown(nFlags: number): boolean | void;
export declare function Sleep(nMilliseconds: number): undefined | void;
export declare function StatusbarGetText(Title?: string, Text?: string, nPart?: number): string | void;
export declare function StatusbarGetTextByHandle(hWnd: number, nPart?: number): string | void;
export declare function ToolTip(Tip: string, nX?: number, nY?: number): undefined | void;
export declare function WinActivate(Title: string, Text?: string): boolean | void;
export declare function WinActivateByHandle(hWnd: number): boolean | void;
export declare function WinActive(Title: string, Text?: string): boolean | void;
export declare function WinActiveByHandle(hWnd: number): boolean | void;
export declare function WinClose(Title: string, Text?: string): boolean | void;
export declare function WinCloseByHandle(hWnd: number): boolean | void;
export declare function WinExists(Title: string, Text?: string): boolean | void;
export declare function WinExistsByHandle(hWnd: number): boolean | void;
export declare function WinGetCaretPos(): {
    x: number;
    y: number;
} | void;
export declare function WinGetClassList(Title: string, Text?: string): string | void;
export declare function WinGetClassListByHandle(hWnd: number): string | void;
export declare function WinGetClientSize(Title: string, Text?: string): {
    left: number;
    top: number;
    right: number;
    bottom: number;
} | void;
export declare function WinGetClientSizeByHandle(hWnd: number): {
    left: number;
    top: number;
    right: number;
    bottom: number;
} | void;
export declare function WinGetHandle(Title: string, Text?: string): number | void;
export declare function WinGetHandleAsText(Title: string, Text?: string): string | void;
export declare function WinGetPos(Title: string, Text?: string): {
    left: number;
    top: number;
    right: number;
    bottom: number;
} | void;
export declare function WinGetPosByHandle(hWnd: number): {
    left: number;
    top: number;
    right: number;
    bottom: number;
} | void;
export declare function WinGetProcess(Title: string, Text?: string): undefined | void;
export declare function WinGetProcessByHandle(hWnd: number): undefined | void;
export declare function WinGetState(Title: string, Text?: string): number | void;
export declare function WinGetStateByHandle(hWnd: number): number | void;
export declare function WinGetText(Title: string, Text?: string): string | void;
export declare function WinGetTextByHandle(hWnd: number): string | void;
export declare function WinGetTitle(Title: string, Text?: string): string | void;
export declare function WinGetTitleByHandle(hWnd: number): string | void;
export declare function WinKill(Title: string, Text?: string): boolean | void;
export declare function WinKillByHandle(hWnd: number): boolean | void;
export declare function WinMenuSelectItem(Title: string, Text: string, Item1: string, Item2: string, Item3: string, Item4: string, Item5: string, Item6: string, Item7: string, Item8: string): boolean | void;
export declare function WinMenuSelectItemByHandle(hWnd: number, Item1: string, Item2: string, Item3: string, Item4: string, Item5: string, Item6: string, Item7: string, Item8: string): boolean | void;
export declare function WinMinimizeAll(): undefined | void;
export declare function WinMinimizeAllUndo(): undefined | void;
export declare function WinMove(Title: string, Text: string, nX: number, nY: number, nWidth?: number, nHeight?: number): undefined | void;
export declare function WinMoveByHandle(hWnd: number, nX: number, nY: number, nWidth?: number, nHeight?: number): undefined | void;
export declare function WinSetOnTop(Title: string, Text: string, nFlag: number): undefined | void;
export declare function WinSetOnTopByHandle(hWnd: number, nFlag: number): undefined | void;
export declare function WinSetState(Title: string, Text: string, nFlags: number): undefined | void;
export declare function WinSetStateByHandle(hWnd: number, nFlags: number): undefined | void;
export declare function WinSetTitle(Title: string, Text: string, NewTitle: string): undefined | void;
export declare function WinSetTitleByHandle(hWnd: number, NewTitle: string): undefined | void;
export declare function WinSetTrans(Title: string, Text?: string, nTrans?: number): boolean | void;
export declare function WinSetTransByHandle(hWnd: number, nTrans: number): boolean | void;
export declare function WinWait(Title: string, Text?: string, nTimeout?: number): boolean | void;
export declare function WinWaitByHandle(hWnd: number, nTimeout: number): boolean | void;
export declare function WinWaitActive(Title: string, Text?: string, nTimeout?: number): boolean | void;
export declare function WinWaitActiveByHandle(hWnd: number, nTimeout: number): boolean | void;
export declare function WinWaitClose(Title: string, Text?: string, nTimeout?: number): boolean | void;
export declare function WinWaitCloseByHandle(hWnd: number, nTimeout: number): boolean | void;
/**
 * @zh-cn d
 * @link http://
 * @param Title
 * @default dd ddd
 * @param Text
 * @param nTimeout
 * @returns
 */
export declare function WinWaitNotActive(Title?: string, Text?: string, nTimeout?: number): boolean | void;
export declare function WinWaitNotActiveByHandle(hWnd: number, nTimeout?: number): boolean | void;
