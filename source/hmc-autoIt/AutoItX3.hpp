#include <iostream>
#include <windows.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <any>
#include "./util/hmc_string_util.h"
#include "./AutoItX3/AutoItX3_DLL.h"

#define HMC_IS_DEUG_COUT 1

// 最大文本分配内存为1M
#define STR_TEXT_SIZE 1048576

// 导入库
#ifdef _MSC_VER

#ifdef _M_IX86
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_DLL.lib")

#elif defined(_M_X64) || defined(_M_AMD64)
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_x64_DLL.lib")

#endif
#endif
using namespace std;

// HMC_CHECK_CATCH2

#define HMC_CHECK_CATCH2            \
    catch (char *err)              \
    {                              \
        if (HMC_IS_DEUG_COUT == 1) \
        {                          \
            cout << err << "\n";   \
        }                          \
    }



#define AU3_DEBUG_CATCH(code, name) \
    if (AU3_error() == code)        \
    {                               \
        throw name;                 \
    }

#define str2lp(str) hmc_string_util::string_to_lpstr(str)

/**
 * @brief 初始化au3
 *
 */
void fn_AU3_Init()
{
    try
    {
        AU3_Init();
    }
    HMC_CHECK_CATCH2;
}

/**
 * @brief 获取au3的错误代码
 *
 * @return int
 */
int fn_AU3_error()
{
    try
    {
        return AU3_error();
    }
    HMC_CHECK_CATCH2;
    return 0;
}

/**
 * @brief 更改各种 AutoIt 功能/参数的操作
 *
 * @link https://documentation.help/AutoItX/AutoItSetOption.htm
 * @param szOption 选项
 * @param nValue 值
 * @return int
 */
int fn_AU3_AutoItSetOption(wstring Option, int nValue)
{
    try
    {
        LPCWSTR szOption = str2lp(Option);
        return AU3_AutoItSetOption(szOption, nValue);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

/**
 * @brief 读取剪贴板文本
 *
 * @return wstring
 */
wstring fn_AU3_ClipGet()
{
    wstring result = L"";
    try
    {
        DWORD dwLength = 0;

        // AU3_ClipGet 不会自动计算大小 需要手动计算出剪贴板大小
        if (OpenClipboard(NULL))
        {
            HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
            if (hClipboardData != NULL) {

                dwLength = static_cast<int>(GlobalSize(hClipboardData));
                CloseClipboard();
            }
        }
        else
        {
            return result;
        }

        
        if (dwLength != 0)
        {
           LPWSTR sz_clip = new wchar_t[dwLength];
           
           AU3_ClipGet(sz_clip, (int)dwLength);

           AU3_DEBUG_CATCH(1, "fn_AU3_ClipGet Failure");
           result.append(hmc_string_util::lpstr_to_string(sz_clip, (int)dwLength));
           return result;
        }
    }
    HMC_CHECK_CATCH2;
    return result;
}

/**
 * @brief 读取剪贴板文本
 *
 * @return wstring
 */
void fn_AU3_ClipPut(wstring intput)
{
    try
    {
        LPCWSTR szintput = str2lp(intput);
        AU3_ClipPut(szintput);
    }
    HMC_CHECK_CATCH2;
}

/**
 * @brief 向给定控件发送鼠标单击命令
 * @link https://documentation.help/AutoItX/ControlClick.htm
 * @param szTitle 要访问的窗口的标题。
 * @param szText 要访问的窗口的文本。
 * @param szControl 与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)
 * @param szButton 要单击的按钮，"left", "right" or "middle" 默认为"left"。
 * - "left" 左边
 * - "right" 右边
 * - "middle" 中间
 * @param nNumClicks 单击鼠标的次数。默认值为 1。
 * @param nX X
 * @param nY Y
 * @return int
 */
bool fn_AU3_ControlClick(wstring szTitle, wstring szText, wstring szControl, wstring szButton = L"left", int nNumClicks = 1, int nX = AU3_INTDEFAULT, int nY = AU3_INTDEFAULT)
{
    try
    {
        LPCWSTR to_szTitle = str2lp(szTitle);
        LPCWSTR to_szText = str2lp(szText);
        LPCWSTR to_szControl = str2lp(szControl);
        LPCWSTR to_szButton = str2lp(szButton);

        return 1 == AU3_ControlClick(to_szTitle, to_szText, to_szControl, to_szButton, nNumClicks, nX, nY);
    }
    HMC_CHECK_CATCH2;
    return false;
}

/**
 * @brief 向给定控件发送鼠标单击命令
 *
 * @param hWnd 窗口句柄
 * @param hCtrl 控件句柄
 * @param szButton 要单击的按钮，"left", "right" or "middle" 默认为"left"。
 * - "left" 左边
 * - "right" 右边
 * - "middle" 中间
 * @param nNumClicks 单击鼠标的次数。默认值为 1。
 * @param nX X
 * @param nY Y
 * @return int
 */
int fn_AU3_ControlClickByHandle(HWND hWnd, HWND hCtrl, wstring szButton = L"left", int nNumClicks = 1, int nX = AU3_INTDEFAULT, int nY = AU3_INTDEFAULT)
{
    try
    {
        LPCWSTR to_szButton = str2lp(szButton);

        return 1 == AU3_ControlClickByHandle(hWnd, hCtrl, to_szButton, nNumClicks, nX, nY);
    }
    HMC_CHECK_CATCH2;
    return false;
}

/**
 * @brief 向控件发送命令
 * @link https://documentation.help/AutoItX/ControlCommand.htm
 *
 * @param szTitle 标题	要访问的窗口的标题。
 * @param szText 文本	要访问的窗口的文本。
 * @param szControl 控制ID 与之交互的控件。请参阅控件。
 * @param szCommand 命令 发送到控制器的命令。
 * @param szExtra 可选	某些命令需要附加参数
 */
wstring fn_AU3_ControlCommand(wstring Title, wstring Text, wstring Control, wstring Command, wstring Extra = L"")
{
    try
    {
        LPWSTR szResult = new wchar_t[MAX_PATH];
        int nBufSize = MAX_PATH;

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        LPCWSTR szCommand = str2lp(Command);
        LPCWSTR szExtra = str2lp(Extra);
        AU3_ControlCommand(szTitle, szText, szControl, szCommand, szExtra, szResult, nBufSize);
        return hmc_string_util::lpstr_to_string(szResult, nBufSize, true);
    }
    HMC_CHECK_CATCH2;

    return L"";
}

/**
 * @brief 向控件发送命令
 * @link https://documentation.help/AutoItX/ControlCommand.htm
 *
 * @param hWnd 窗口句柄
 * @param hCtrl 控件句柄
 * @param szCommand 命令 发送到控制器的命令。
 * @param szExtra 可选	某些命令需要附加参数
 * @return wstring
 */
wstring fn_AU3_ControlCommandByHandle(HWND hWnd, HWND hCtrl, wstring Command, wstring Extra = L"")
{
    try
    {
        LPWSTR szResult = new wchar_t[MAX_PATH];
        int nBufSize = MAX_PATH;

        LPCWSTR szCommand = str2lp(Command);
        LPCWSTR szExtra = str2lp(Extra);
        AU3_ControlCommandByHandle(hWnd, hCtrl, szCommand, szExtra, szResult, nBufSize);
        return hmc_string_util::lpstr_to_string(szResult, nBufSize, true);
    }
    HMC_CHECK_CATCH2;

    return L"";
}

/**
 * @brief 控制列表视图
 * 向 ListView32 控件发送命令
 * @link https://documentation.help/AutoItX/ControlListView.htm
 *
 * @param szTitle 标题	要访问的窗口的标题。
 * @param szText 文本	要访问的窗口的文本。
 * @param szControl 控制ID	与之交互的控件。请参阅请参阅[控件](https://documentation.help/AutoItX/controls.htm)
 * @param szCommand 命令	发送到控制器的命令（见下文）。
 * @param szExtra1 选项1	某些命令需要附加参数；如果不需要参数，请使用“”。
 * @param szExtra2 选项2	某些命令需要附加参数；如果不需要参数，请使用“”。
 * @return wstring
 */
wstring fn_AU3_ControlListView(wstring Title, wstring Text, wstring Control, wstring Command, wstring Extra1, wstring Extra2)
{
    try
    {
        LPWSTR szResult = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        LPCWSTR szCommand = str2lp(Command);
        LPCWSTR szExtra1 = str2lp(Extra1);
        LPCWSTR szExtra2 = str2lp(Extra2);
        AU3_ControlListView(szTitle, szText, szControl, szCommand, szExtra1, szExtra2, szResult, nBufSize);
        return hmc_string_util::lpstr_to_string(szResult, nBufSize, true);
    }
    HMC_CHECK_CATCH2;

    return L"";
}

/**
 * @brief 控制列表视图
 * 向 ListView32 控件发送命令
 * @link https://documentation.help/AutoItX/ControlListView.htm
 *
 * @param hWnd 窗口句柄
 * @param hCtrl 控件句柄
 * @param szCommand 命令	发送到控制器的命令（见下文）。
 * @param szExtra1 选项1	某些命令需要附加参数；如果不需要参数，请使用“”。
 * @param szExtra2 选项2	某些命令需要附加参数；如果不需要参数，请使用“”。
 * @return wstring
 */
wstring fn_AU3_ControlListViewByHandle(HWND hWnd, HWND hCtrl, wstring Command, wstring Extra1, wstring Extra2)
{
    try
    {
        LPWSTR szResult = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;

        LPCWSTR szCommand = str2lp(Command);
        LPCWSTR szExtra1 = str2lp(Extra1);
        LPCWSTR szExtra2 = str2lp(Extra2);
        AU3_ControlListViewByHandle(hWnd, hCtrl, szCommand, szExtra1, szExtra2, szResult, nBufSize);
        return hmc_string_util::lpstr_to_string(szResult, nBufSize, true);
    }
    HMC_CHECK_CATCH2;

    return L"";
}

/**
 * @brief ControlDisable
 *  Disables or "grays-out" a control
 *  ControlDisable "title", "text", "controlID"
 * @param szTitle  title The title of the window to access.
 * @param szText The text of the window to access.
 * @param szControl The control to interact with. See [Controls](https://documentation.help/AutoItX/controls.htm).
 * @return true
 * @return false
 */
bool fn_AU3_ControlDisable(wstring Title, wstring Text, wstring Control)
{
    try
    {
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        return (AU3_ControlDisable(szTitle, szText, szControl) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

/**
 * @brief ControlDisable
 *  Disables or "grays-out" a control
 *  ControlDisable "title", "text", "controlID"
 * @param hWnd 窗口句柄
 * @param hCtrl 控件句柄
 * @return true
 * @return false
 */
bool fn_AU3_ControlDisableByHandle(HWND hWnd, HWND hCtrl)
{
    try
    {
        return (AU3_ControlDisableByHandle(hWnd, hCtrl) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ControlEnable(wstring Title, wstring Text, wstring Control)
{
    try
    {
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        return (AU3_ControlEnable(szTitle, szText, szControl) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ControlEnableByHandle(HWND hWnd, HWND hCtrl)
{
    try
    {
        return (AU3_ControlEnableByHandle(hWnd, hCtrl) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

/**
 * @brief ControlFocus
 * Sets input focus to a given control on a window
 * @param Title The title of the window to access.
 * @param Text The text of the window to access.
 * @param szControl The control to interact with. See [Controls](https://documentation.help/AutoItX/controls.htm).
 * @return true
 * @return false
 */
bool fn_AU3_ControlFocus(wstring Title, wstring Text, wstring Control)
{
    try
    {
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        return (AU3_ControlFocus(szTitle, szText, szControl) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

/**
 * @brief ControlFocus
 * Sets input focus to a given control on a window
 * @param hWnd 窗口句柄
 * @param hCtrl 控件句柄
 * @return true
 * @return false
 */
bool fn_AU3_ControlFocusByHandle(HWND hWnd, HWND hCtrl)
{
    try
    {
        return (AU3_ControlFocusByHandle(hWnd, hCtrl) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

/**
 * @brief ControlGetFocus
 * Returns the ControlRef # of the control that has keyboard focus within a specified window
 * ControlGetFocus "title" [, "text"]
 * @param szTitle Title of window to check.
 * @param szText Optional: Text from window to check.
 */
wstring fn_AU3_ControlGetFocus(wstring Title, wstring Text = L"")
{
    try
    {
        int nBufSize = STR_TEXT_SIZE;
        LPWSTR szControlWithFocus = new wchar_t[nBufSize];
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        AU3_ControlGetFocus(szTitle, szText, szControlWithFocus, nBufSize);
        return hmc_string_util::lpstr_to_string(szControlWithFocus, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

/**
 * @brief ControlGetFocus
 * Returns the ControlRef # of the control that has keyboard focus within a specified window
 * ControlGetFocus "title" [, "text"]
 * @param hWnd Title of window to check.
 */
wstring fn_AU3_ControlGetFocusByHandle(HWND hWnd)
{
    try
    {
        int nBufSize = STR_TEXT_SIZE;
        LPWSTR szControlWithFocus = new wchar_t[nBufSize];
        AU3_ControlGetFocusByHandle(hWnd, szControlWithFocus, nBufSize);
        return hmc_string_util::lpstr_to_string(szControlWithFocus, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

HWND fn_AU3_ControlGetHandle(HWND hWnd, wstring Control)
{
    try
    {
        LPCWSTR szControl = str2lp(Control);
        return AU3_ControlGetHandle(hWnd, (LPCWSTR)szControl);
    }
    HMC_CHECK_CATCH2;
    return NULL;
}

wstring fn_AU3_ControlGetHandleAsText(wstring Title, wstring Text, wstring Control)
{
    try
    {
        int nBufSize = STR_TEXT_SIZE;
        LPWSTR szRetText = new wchar_t[nBufSize];
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        AU3_ControlGetHandleAsText(szTitle, szText, szControl, szRetText, nBufSize);
        return hmc_string_util::lpstr_to_string(szRetText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

RECT fn_AU3_ControlGetPos(wstring Title, wstring Text, wstring Control)
{
    RECT Pos = RECT{};
    Pos.bottom = 0;
    Pos.left = 0;
    Pos.right = 0;
    Pos.top = 0;

    try
    {
        
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        RECT lpRect;
        if (AU3_ControlGetPos(szTitle, szText, szControl,&lpRect) == 1)
        {
            Pos.bottom =lpRect.bottom;
            Pos.left =lpRect.left;
            Pos.right =lpRect.right;
            Pos.top =lpRect.top;
        }
    }
    HMC_CHECK_CATCH2;
    return Pos;
}

RECT fn_AU3_ControlGetPosByHandle(HWND hWnd, HWND hCtrl)
{
    RECT Pos = RECT{};
    Pos.bottom = 0;
    Pos.left = 0;
    Pos.right = 0;
    Pos.top = 0;

    try
    {

        if (AU3_ControlGetPosByHandle(hWnd, hCtrl, &Pos) == 1)
        {
        }
    }
    HMC_CHECK_CATCH2;
    return Pos;
}

wstring fn_AU3_ControlGetText(wstring Title, wstring Text, wstring Control)
{
    try
    {
        int nBufSize = STR_TEXT_SIZE;
        LPWSTR szRetText = new wchar_t[nBufSize];
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        AU3_ControlGetText(szTitle, szText, szControl, szRetText, nBufSize);
        return hmc_string_util::lpstr_to_string(szRetText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

wstring fn_AU3_ControlGetTextByHandle(HWND hWnd, HWND hCtrl)
{
    try
    {
        LPWSTR szResult = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;

        AU3_ControlGetTextByHandle(hWnd, hCtrl, szResult, nBufSize);
        return hmc_string_util::lpstr_to_string(szResult, nBufSize, true);
    }
    HMC_CHECK_CATCH2;

    return L"";
}

bool fn_AU3_ControlHide(wstring Title, wstring Text, wstring Control)
{
    try
    {
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);

        return (AU3_ControlHide(szTitle, szText, szControl) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ControlHideByHandle(HWND hWnd, HWND hCtrl)
{
    try
    {
        return (AU3_ControlHideByHandle(hWnd, hCtrl) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

/**
 * @brief ControlMove
 * Moves a control within a window
 * ControlMove "title", "text", "controlID", x, y [, width [, height]]
 * @param Title The title of the window to move.
 * @param Text The text of the window to move.
 * @param Control The control to interact with. See [控件](https://documentation.help/AutoItX/controls.htm)
 * @param nX X coordinate to move to.
 * @param nY Y coordinate to move to.
 * @param nWidth Optional: New width of the window.
 * @param nHeight 	Optional: New height of the window.
 * @return int
 */
bool fn_AU3_ControlMove(wstring Title, wstring Text, wstring Control, int nX, int nY, int nWidth = -1, int nHeight = -1)
{

    try
    {
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        return (fn_AU3_ControlMove(szTitle, szText, szControl, nX, nY, nWidth, nHeight) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ControlMoveByHandle(HWND hWnd, HWND hCtrl, int nX, int nY, int nWidth = -1, int nHeight = -1)
{

    try
    {
        return (AU3_ControlMoveByHandle(hWnd, hCtrl, nX, nY, nWidth, nHeight) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ControlSend(wstring Title, wstring Text, wstring Control, wstring SendText, int nMode = 0)
{
    try
    {
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        LPCWSTR szSendText = str2lp(SendText);

        return (AU3_ControlSend(szTitle, szText, szControl, szSendText, nMode) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ControlSendByHandle(HWND hWnd, HWND hCtrl, wstring SendText, int nMode = 0)
{
    try
    {
        LPCWSTR szSendText = str2lp(SendText);
        return (AU3_ControlSendByHandle(hWnd, hCtrl, szSendText, nMode) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ControlSetText(wstring Title, wstring Text, wstring Control, wstring ControlText)
{
    try
    {
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        LPCWSTR szSendText = str2lp(ControlText);
        return (AU3_ControlSetText(szTitle, szText, szControl, szSendText) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ControlSetTextByHandle(HWND hWnd, HWND hCtrl, wstring SendText)
{
    try
    {
        LPCWSTR szSendText = str2lp(SendText);
        return (AU3_ControlSetTextByHandle(hWnd, hCtrl, szSendText) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ControlShow(wstring Title, wstring Text, wstring Control)
{
    try
    {
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        return (AU3_ControlShow(szTitle, szText, szControl) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ControlShowByHandle(HWND hWnd, HWND hCtrl)
{
    try
    {
        return (AU3_ControlShowByHandle(hWnd, hCtrl) == 1) ? true : false;
    }
    HMC_CHECK_CATCH2;
    return false;
}

wstring fn_AU3_ControlTreeView(wstring Title, wstring Text, wstring Control, wstring Command, wstring Extra1, wstring Extra2)
{
    try
    {
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szControl = str2lp(Control);
        LPCWSTR szCommand = str2lp(Command);

        LPCWSTR szExtra1 = str2lp(Extra1);
        LPCWSTR szExtra2 = str2lp(Extra2);

        LPWSTR szResult = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;

        AU3_ControlTreeView(szTitle, szText, szControl, szCommand, szExtra1, szExtra2, szResult, nBufSize);

        return hmc_string_util::lpstr_to_string(szResult, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

wstring fn_AU3_ControlTreeViewByHandle(HWND hWnd, HWND hCtrl, wstring Command, wstring Extra1, wstring Extra2)
{
    try
    {

        LPCWSTR szCommand = str2lp(Command);

        LPCWSTR szExtra1 = str2lp(Extra1);
        LPCWSTR szExtra2 = str2lp(Extra2);

        LPWSTR szResult = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;

        AU3_ControlTreeViewByHandle(hWnd, hCtrl, szCommand, szExtra1, szExtra2, szResult, nBufSize);

        return hmc_string_util::lpstr_to_string(szResult, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

wstring fn_AU3_DriveMapAdd(wstring Device, wstring Share, int nFlags, wstring User = L"", wstring Pwd = L"")
{
    try
    {

        LPCWSTR szDevice = str2lp(Device);
        LPCWSTR szShare = str2lp(Share);
        LPCWSTR szUser = str2lp(User);
        LPCWSTR szPwd = str2lp(Pwd);

        LPWSTR szResult = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;

        AU3_DriveMapAdd(szDevice, szShare, nFlags, szUser, szPwd, szResult, nBufSize);

        return hmc_string_util::lpstr_to_string(szResult, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

bool fn_AU3_DriveMapDel(wstring Device)
{
    try
    {

        LPCWSTR szDevice = str2lp(Device);
        return (AU3_DriveMapDel(szDevice) == 1 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

wstring fn_AU3_DriveMapGet(wstring Device)
{
    try
    {

        LPWSTR szMapping = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;

        LPCWSTR szDevice = str2lp(Device);
        AU3_DriveMapGet(szDevice, szMapping, nBufSize);
        return hmc_string_util::lpstr_to_string(szMapping, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

bool fn_AU3_IsAdmin()
{
    try
    {

        return (AU3_IsAdmin() ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

void fn_AU3_MouseClick(wstring Button = L"LEFT", int nX = AU3_INTDEFAULT, int nY = AU3_INTDEFAULT, int nClicks = 1, int nSpeed = -1)
{
    try
    {

        LPCWSTR szButton = str2lp(Button);
        AU3_MouseClick(szButton, nX, nY, nClicks, nSpeed);
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_MouseClickDrag(wstring Button, int nX1, int nY1, int nX2, int nY2, int nSpeed = -1)
{
    try
    {

        LPCWSTR szButton = str2lp(Button);
        AU3_MouseClickDrag(szButton, nX1, nY1, nX2, nY2, nSpeed);
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_MouseDown(wstring Button = L"LEFT")
{
    try
    {

        LPCWSTR szButton = str2lp(Button);
        AU3_MouseDown(szButton);
    }
    HMC_CHECK_CATCH2;
}

int fn_AU3_MouseGetCursor()
{
    try
    {

        return AU3_MouseGetCursor();
    }
    HMC_CHECK_CATCH2;
    return 0;
}

POINT fn_AU3_MouseGetPos()
{
    POINT result = POINT{};
    result.x = 0;
    result.y = 0;
    try
    {

        AU3_MouseGetPos(&result);
    }
    HMC_CHECK_CATCH2;
    return result;
}

int fn_AU3_MouseMove(int nX, int nY, int nSpeed = -1)
{
    try
    {

        return AU3_MouseMove(nX, nY, nSpeed);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

void fn_AU3_MouseUp(wstring Button = L"LEFT")
{
    try
    {

        LPCWSTR szButton = str2lp(Button);
        AU3_MouseUp(szButton);
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_MouseWheel(wstring Direction, int nClicks)
{
    try
    {

        LPCWSTR szDirection = str2lp(Direction);
        AU3_MouseWheel(szDirection, nClicks);
    }
    HMC_CHECK_CATCH2;
}

int fn_AU3_Opt(wstring Option, int nValue)
{
    try
    {

        LPCWSTR szOption = str2lp(Option);
        return AU3_Opt(szOption, nValue);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

unsigned int fn_AU3_PixelChecksum(RECT lpRect, int nStep = 1)
{
    try
    {

        return AU3_PixelChecksum(&lpRect, nStep);
    }
    HMC_CHECK_CATCH2;
    return -1;
}

int fn_AU3_PixelGetColor(int nX, int nY)
{
    try
    {

        return AU3_PixelGetColor(nX, nY);
    }
    HMC_CHECK_CATCH2;
    return -1;
}

POINT fn_AU3_PixelSearch(RECT lpRect, int nCol, int nVar = 0, int nStep = 1)
{
    POINT result = POINT{};
    result.x = 0;
    result.y = 0;

    try
    {
        AU3_PixelSearch(&lpRect, nCol, nVar, nStep, &result);
    }
    HMC_CHECK_CATCH2;
    return result;
}

void fn_AU3_ProcessClose(wstring Process)
{
    try
    {

        LPCWSTR szProcess = str2lp(Process);
        AU3_ProcessClose(szProcess);
    }
    HMC_CHECK_CATCH2;
}

bool fn_AU3_ProcessExists(wstring Process)
{
    try
    {

        LPCWSTR szProcess = str2lp(Process);
        return (AU3_ProcessExists(szProcess) == 1 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ProcessSetPriority(wstring Process, int nPriority)
{
    try
    {

        LPCWSTR szProcess = str2lp(Process);
        return (AU3_ProcessSetPriority(szProcess, nPriority) == 1 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ProcessWait(wstring Process, int nTimeout = 0)
{
    try
    {

        LPCWSTR szProcess = str2lp(Process);
        return (AU3_ProcessWait(szProcess, nTimeout) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_ProcessWaitClose(wstring Process, int nTimeout = 0)
{
    try
    {

        LPCWSTR szProcess = str2lp(Process);
        return (AU3_ProcessWaitClose(szProcess, nTimeout) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

int fn_AU3_Run(wstring Program, wstring Dir = L"", int nShowFlag = SW_SHOWNORMAL)
{
    try
    {

        LPCWSTR szProgram = str2lp(Program);
        LPCWSTR szDir = str2lp(Dir);
        return AU3_Run(szProgram, szDir, nShowFlag);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

int fn_AU3_RunWait(wstring Program, wstring Dir = L"", int nShowFlag = SW_SHOWNORMAL)
{
    try
    {

        LPCWSTR szProgram = str2lp(Program);
        LPCWSTR szDir = str2lp(Dir);
        return AU3_RunWait(szProgram, szDir, nShowFlag);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

int fn_AU3_RunAs(wstring User, wstring Domain, wstring Password, int nLogonFlag, wstring Program, wstring Dir = L"", int nShowFlag = SW_SHOWNORMAL)
{
    try
    {

        LPCWSTR szUser = str2lp(User);
        LPCWSTR szDomain = str2lp(Domain);
        LPCWSTR szPassword = str2lp(Password);
        LPCWSTR szProgram = str2lp(Program);
        LPCWSTR szDir = str2lp(Dir);
        return AU3_RunAs(szUser, szDomain, szPassword, nLogonFlag, szProgram, szDir, nShowFlag);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

int fn_AU3_RunAsWait(wstring User, wstring Domain, wstring Password, int nLogonFlag, wstring Program, wstring Dir = L"", int nShowFlag = SW_SHOWNORMAL)
{
    try
    {

        LPCWSTR szUser = str2lp(User);
        LPCWSTR szDomain = str2lp(Domain);
        LPCWSTR szPassword = str2lp(Password);
        LPCWSTR szProgram = str2lp(Program);
        LPCWSTR szDir = str2lp(Dir);

        return AU3_RunAsWait(szUser, szDomain, szPassword, nLogonFlag, szProgram, szDir, nShowFlag);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

void fn_AU3_Send(wstring SendText, int nMode = 0)
{
    try
    {

        LPCWSTR szSendText = str2lp(SendText);
        AU3_Send(szSendText, nMode = 0);
    }
    HMC_CHECK_CATCH2;
}

bool fn_AU3_Shutdown(int nFlags)
{
    try
    {

        return (AU3_Shutdown(nFlags) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

void fn_AU3_Sleep(int nMilliseconds)
{
    try
    {

        AU3_Sleep(nMilliseconds);
    }
    HMC_CHECK_CATCH2;
}

wstring fn_AU3_StatusbarGetText(wstring Title = L"", wstring Text = L"", int nPart = 1)
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);

        LPWSTR szStatusText = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;
        AU3_StatusbarGetText(szTitle, szText, nPart, szStatusText, nBufSize);

        return hmc_string_util::lpstr_to_string(szStatusText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

wstring fn_AU3_StatusbarGetTextByHandle(HWND hWnd, int nPart = 1)
{
    try
    {
        LPWSTR szStatusText = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;
        AU3_StatusbarGetTextByHandle(hWnd, nPart, szStatusText, nBufSize);
        return hmc_string_util::lpstr_to_string(szStatusText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

void fn_AU3_ToolTip(wstring Tip, int nX = AU3_INTDEFAULT, int nY = AU3_INTDEFAULT)
{
    try
    {

        LPCWSTR szTip = str2lp(Tip);
        AU3_ToolTip(szTip, nX, nY);
    }
    HMC_CHECK_CATCH2;
}

bool fn_AU3_WinActivate(wstring Title, wstring Text = L"")
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return (AU3_WinActivate(szTitle, szText) == 1 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinActivateByHandle(HWND hWnd)
{
    try
    {

        return (AU3_WinActivateByHandle(hWnd) == 1 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinActive(wstring Title, wstring Text = L"")
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return (AU3_WinActive(szTitle, szText) == 1 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinActiveByHandle(HWND hWnd)
{
    try
    {

        return (AU3_WinActiveByHandle(hWnd) == 1 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinClose(wstring Title, wstring Text = L"")
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return (AU3_WinClose(szTitle, szText) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinCloseByHandle(HWND hWnd)
{
    try
    {

        return (AU3_WinCloseByHandle(hWnd) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinExists(wstring Title, wstring Text = L"")
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return (AU3_WinExists(szTitle, szText) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinExistsByHandle(HWND hWnd)
{
    try
    {

        return (AU3_WinExistsByHandle(hWnd) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

POINT fn_AU3_WinGetCaretPos()
{
    POINT point = POINT{};
    point.x = 0;
    point.y = 0;
    try
    {
        if (AU3_WinGetCaretPos(&point) == 1)
        {

        }
    }
    HMC_CHECK_CATCH2;
    return point;
}

wstring fn_AU3_WinGetClassList(wstring Title, wstring Text = L"")
{
    try
    {
        LPWSTR szRetText = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        AU3_WinGetClassList(szTitle, szText, szRetText, nBufSize);
        return hmc_string_util::lpstr_to_string(szRetText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

wstring fn_AU3_WinGetClassListByHandle(HWND hWnd)
{
    try
    {
        LPWSTR szRetText = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;
        AU3_WinGetClassListByHandle(hWnd, szRetText, nBufSize);
        return hmc_string_util::lpstr_to_string(szRetText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

RECT fn_AU3_WinGetClientSize(wstring Title, wstring Text = L"")
{
    RECT Pos = RECT{};
    Pos.bottom = 0;
    Pos.left = 0;
    Pos.right = 0;
    Pos.top = 0;
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        if (AU3_WinGetClientSize(szTitle, szText, &Pos) != 0)
        {
        }
    }
    HMC_CHECK_CATCH2;
    return Pos;
}

RECT fn_AU3_WinGetClientSizeByHandle(HWND hWnd)
{
    RECT Pos = RECT{};
    Pos.bottom = 0;
    Pos.left = 0;
    Pos.right = 0;
    Pos.top = 0;
    try
    {

        if (AU3_WinGetClientSizeByHandle(hWnd, &Pos) != 0)
        {
        }
    }
    HMC_CHECK_CATCH2;
    return Pos;
}

HWND fn_AU3_WinGetHandle(wstring Title, wstring Text = L"")
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return AU3_WinGetHandle(szTitle, szText);
    }
    HMC_CHECK_CATCH2;
    return NULL;
}

wstring fn_AU3_WinGetHandleAsText(wstring Title, wstring Text = L"")
{
    try
    {
        LPWSTR szRetText = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        AU3_WinGetHandleAsText(szTitle, szText, szRetText, nBufSize);
        return hmc_string_util::lpstr_to_string(szRetText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

RECT fn_AU3_WinGetPos(wstring Title, wstring Text = L"")
{
    RECT Pos = RECT{};
    Pos.bottom = 0;
    Pos.left = 0;
    Pos.right = 0;
    Pos.top = 0;
    try
    {
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szTitle = str2lp(Title);

        if (AU3_WinGetPos(szTitle, szText, &Pos) != 0)
        {
        }
    }
    HMC_CHECK_CATCH2;
    return Pos;
}

RECT fn_AU3_WinGetPosByHandle(HWND hWnd)
{
    RECT Pos = RECT{};
    Pos.bottom = 0;
    Pos.left = 0;
    Pos.right = 0;
    Pos.top = 0;

    try
    {
        if (AU3_WinGetPosByHandle(hWnd, &Pos) == 1)
        {
        }
    }
    HMC_CHECK_CATCH2;
    return Pos;
}

DWORD fn_AU3_WinGetProcess(wstring Title, wstring Text = L"")
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return AU3_WinGetProcess(szTitle, szText);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

DWORD fn_AU3_WinGetProcessByHandle(HWND hWnd)
{
    try
    {

        return AU3_WinGetProcessByHandle(hWnd);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

int fn_AU3_WinGetState(wstring Title, wstring Text = L"")
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return AU3_WinGetState(szTitle, szText);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

int fn_AU3_WinGetStateByHandle(HWND hWnd)
{
    try
    {

        return AU3_WinGetStateByHandle(hWnd);
    }
    HMC_CHECK_CATCH2;
    return 0;
}

wstring fn_AU3_WinGetText(wstring Title, wstring Text = L"")
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPWSTR szRetText = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;
        AU3_WinGetText(szTitle, szText, szRetText, nBufSize);

        return hmc_string_util::lpstr_to_string(szRetText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

wstring fn_AU3_WinGetTextByHandle(HWND hWnd)
{
    try
    {
        LPWSTR szRetText = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;

        AU3_WinGetTextByHandle(hWnd, szRetText, nBufSize);
        return hmc_string_util::lpstr_to_string(szRetText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

wstring fn_AU3_WinGetTitle(wstring Title, wstring Text = L"")
{
    try
    {

        LPWSTR szRetText = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;
        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        AU3_WinGetTitle(szTitle, szText, szRetText, nBufSize);
        return hmc_string_util::lpstr_to_string(szRetText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

wstring fn_AU3_WinGetTitleByHandle(HWND hWnd)
{
    try
    {
        LPWSTR szRetText = new wchar_t[STR_TEXT_SIZE];
        int nBufSize = STR_TEXT_SIZE;
        AU3_WinGetTitleByHandle(hWnd, szRetText, nBufSize);
        return hmc_string_util::lpstr_to_string(szRetText, nBufSize, true);
    }
    HMC_CHECK_CATCH2;
    return L"";
}

bool fn_AU3_WinKill(wstring Title, wstring Text = L"")
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return (AU3_WinKill(szTitle, szText) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinKillByHandle(HWND hWnd)
{
    try
    {

        return (AU3_WinKillByHandle(hWnd) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinMenuSelectItem(wstring Title, wstring Text, wstring Item1, wstring Item2, wstring Item3, wstring Item4, wstring Item5, wstring Item6, wstring Item7, wstring Item8)
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szItem1 = str2lp(Item1);
        LPCWSTR szItem2 = str2lp(Item2);
        LPCWSTR szItem3 = str2lp(Item3);
        LPCWSTR szItem4 = str2lp(Item4);
        LPCWSTR szItem5 = str2lp(Item5);
        LPCWSTR szItem6 = str2lp(Item6);
        LPCWSTR szItem7 = str2lp(Item7);
        LPCWSTR szItem8 = str2lp(Item8);
        return (AU3_WinMenuSelectItem(szTitle, szText, szItem1, szItem2, szItem3, szItem4, szItem5, szItem6, szItem7, szItem8) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinMenuSelectItemByHandle(HWND hWnd, wstring Item1, wstring Item2, wstring Item3, wstring Item4, wstring Item5, wstring Item6, wstring Item7, wstring Item8)
{
    try
    {

        LPCWSTR szItem1 = str2lp(Item1);
        LPCWSTR szItem2 = str2lp(Item2);
        LPCWSTR szItem3 = str2lp(Item3);
        LPCWSTR szItem4 = str2lp(Item4);
        LPCWSTR szItem5 = str2lp(Item5);
        LPCWSTR szItem6 = str2lp(Item6);
        LPCWSTR szItem7 = str2lp(Item7);
        LPCWSTR szItem8 = str2lp(Item8);
        return (AU3_WinMenuSelectItemByHandle(hWnd, szItem1, szItem2, szItem3, szItem4, szItem5, szItem6, szItem7, szItem8) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

void fn_AU3_WinMinimizeAll()
{
    try
    {

        AU3_WinMinimizeAll();
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_WinMinimizeAllUndo()
{
    try
    {

        AU3_WinMinimizeAllUndo();
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_WinMove(wstring Title, wstring Text, int nX, int nY, int nWidth = -1, int nHeight = -1)
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        AU3_WinMove(szTitle, szText, nX, nY, nWidth, nHeight);
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_WinMoveByHandle(HWND hWnd, int nX, int nY, int nWidth = -1, int nHeight = -1)
{
    try
    {

        AU3_WinMoveByHandle(hWnd, nX, nY, nWidth, nHeight);
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_WinSetOnTop(wstring Title, wstring Text, int nFlag)
{
    try
    {
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szTitle = str2lp(Title);
        AU3_WinSetOnTop(szTitle, szText, nFlag);
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_WinSetOnTopByHandle(HWND hWnd, int nFlag)
{
    try
    {

        AU3_WinSetOnTopByHandle(hWnd, nFlag);
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_WinSetState(wstring Title, wstring Text, int nFlags)
{
    try
    {
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szTitle = str2lp(Title);
        AU3_WinSetState(szTitle, szText, nFlags);
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_WinSetStateByHandle(HWND hWnd, int nFlags)
{
    try
    {

        AU3_WinSetStateByHandle(hWnd, nFlags);
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_WinSetTitle(wstring Title, wstring Text, wstring NewTitle)
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        LPCWSTR szNewTitle = str2lp(NewTitle);
        AU3_WinSetTitle(szTitle, szText, szNewTitle);
    }
    HMC_CHECK_CATCH2;
}

void fn_AU3_WinSetTitleByHandle(HWND hWnd, wstring NewTitle)
{
    try
    {

        LPCWSTR szNewTitle = str2lp(NewTitle);
        AU3_WinSetTitleByHandle(hWnd, szNewTitle);
    }
    HMC_CHECK_CATCH2;
}

bool fn_AU3_WinSetTrans(wstring Title, wstring Text = L"", int nTrans = 255)
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return (AU3_WinSetTrans(szTitle, szText, nTrans) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinSetTransByHandle(HWND hWnd, int nTrans)
{
    try
    {

        return (AU3_WinSetTransByHandle(hWnd, nTrans) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinWait(wstring Title, wstring Text = L"", int nTimeout = 0)
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return (AU3_WinWait(szTitle, szText, nTimeout) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinWaitByHandle(HWND hWnd, int nTimeout)
{
    try
    {

        return (AU3_WinWaitByHandle(hWnd, nTimeout) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinWaitActive(wstring Title, wstring Text = L"", int nTimeout = 0)
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return (AU3_WinWaitActive(szTitle, szText, nTimeout) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinWaitActiveByHandle(HWND hWnd, int nTimeout)
{
    try
    {

        return (AU3_WinWaitActiveByHandle(hWnd, nTimeout) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinWaitClose(wstring Title, wstring Text = L"", int nTimeout = 0)
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);
        return (AU3_WinWaitClose(szTitle, szText, nTimeout) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinWaitCloseByHandle(HWND hWnd, int nTimeout)
{
    try
    {

        return (AU3_WinWaitCloseByHandle(hWnd, nTimeout) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinWaitNotActive(wstring Title = L"", wstring Text = L"", int nTimeout = 0)
{
    try
    {

        LPCWSTR szTitle = str2lp(Title);
        LPCWSTR szText = str2lp(Text);

        return (AU3_WinWaitNotActive(szTitle, szText, nTimeout) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}

bool fn_AU3_WinWaitNotActiveByHandle(HWND hWnd, int nTimeout = 0)
{
    try
    {

        return (AU3_WinWaitNotActiveByHandle(hWnd, nTimeout) != 0 ? true : false);
    }
    HMC_CHECK_CATCH2;
    return false;
}
