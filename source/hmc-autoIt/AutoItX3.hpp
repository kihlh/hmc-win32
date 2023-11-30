#include <iostream>
#include <windows.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <any>
#include "./AutoItX3/AutoItX3_DLL.h"
#include "./util/hmc_string_util.hpp"

#define HMC_IS_DEUG_COUT 1;

// 导入库
#ifdef _MSC_VER

#ifdef _M_IX86
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_DLL.lib")

#elif defined(_M_X64) || defined(_M_AMD64)
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_x64_DLL.lib")

#endif
#endif
using namespace std;

// HMC_CHECK_CATCH
#ifdef SRC_NODE_API_H_

#elif HMC_IS_DEUG_COUT == 1
#define HMC_CHECK_CATCH                        \
    catch (char *err)                          \
    {                                          \
        napi_throw_type_error(env, NULL, err); \
        return NULL;                           \
    }
#define HMC_CHECK_CATCH      \
    catch (char *err)        \
    {                        \
        cout << err << "\n"; \
    }

#else
#define HMC_CHECK_CATCH \
    catch (char *err) {}
#endif // SRC_NODE_API_H_

#define AU3_DEBUG_CATCH(code, name) \
    if (AU3_error() == code)        \
    {                               \
        throw name;                 \
    }
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
    HMC_CHECK_CATCH;
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
    HMC_CHECK_CATCH;
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
int fn_AU3_AutoItSetOption(wstring szOption, int nValue)
{
    try
    {
        return AU3_AutoItSetOption(hmc_string_util::string_to_lpstr(szOption), nValue);
    }
    HMC_CHECK_CATCH;
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
            dwLength = static_cast<int>(GlobalSize(hClipboardData));
            CloseClipboard();
        }
        else
        {
            return result;
        }

        LPWSTR sz_clip = new wchar_t[dwLength];

        AU3_ClipGet(sz_clip, (int)dwLength);
        if (dwLength != 0)
        {
            result.append(hmc_string_util::lpstr_to_string(sz_clip, (int)dwLength));
            return result;
        }
    }
    HMC_CHECK_CATCH;
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
        AU3_ClipPut(hmc_string_util::string_to_lpstr(intput));
    }
    HMC_CHECK_CATCH;
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
        LPCWSTR to_szTitle = hmc_string_util::string_to_lpstr(szTitle);
        LPCWSTR to_szText = hmc_string_util::string_to_lpstr(szText);
        LPCWSTR to_szControl = hmc_string_util::string_to_lpstr(szControl);
        LPCWSTR to_szButton = hmc_string_util::string_to_lpstr(szButton);

        return 1 == AU3_ControlClick(to_szTitle, to_szText, to_szControl, to_szButton, nNumClicks, nX, nY);
    }
    HMC_CHECK_CATCH;
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
int fn_AU3_ControlClickByHandle(HWND hWnd, HWND hCtrl, LPCWSTR szButton = L"left", int nNumClicks = 1, int nX = AU3_INTDEFAULT, int nY = AU3_INTDEFAULT)
{
    try
    {
        LPCWSTR to_szButton = hmc_string_util::string_to_lpstr(szButton);

        return 1 == AU3_ControlClickByHandle(hWnd, hCtrl, to_szButton, nNumClicks, nX, nY);
    }
    HMC_CHECK_CATCH;
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

        LPCWSTR szTitle = hmc_string_util::string_to_lpstr(Title);
        LPCWSTR szText = hmc_string_util::string_to_lpstr(Text);
        LPCWSTR szControl = hmc_string_util::string_to_lpstr(Control);
        LPCWSTR szCommand = hmc_string_util::string_to_lpstr(Command);
        LPCWSTR szExtra = hmc_string_util::string_to_lpstr(Extra);
        AU3_ControlCommand(szTitle, szText, szControl, szCommand, szExtra, szResult, nBufSize);
    }
    HMC_CHECK_CATCH;

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

        LPCWSTR szCommand = hmc_string_util::string_to_lpstr(Command);
        LPCWSTR szExtra = hmc_string_util::string_to_lpstr(Extra);
        AU3_ControlCommandByHandle(hWnd, hCtrl, szCommand, szExtra, szResult, nBufSize);
    }
    HMC_CHECK_CATCH;

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
wstring fn_AU3_ControlListView(LPCWSTR Title, LPCWSTR Text, LPCWSTR Control, LPCWSTR Command, LPCWSTR Extra1, LPCWSTR Extra2)
{
    try
    {
        LPWSTR szResult = new wchar_t[50000];
        int nBufSize = 50000;

        LPCWSTR szTitle = hmc_string_util::string_to_lpstr(Title);
        LPCWSTR szText = hmc_string_util::string_to_lpstr(Text);
        LPCWSTR szControl = hmc_string_util::string_to_lpstr(Control);
        LPCWSTR szCommand = hmc_string_util::string_to_lpstr(Command);
        LPCWSTR szExtra1 = hmc_string_util::string_to_lpstr(Extra1);
        LPCWSTR szExtra2 = hmc_string_util::string_to_lpstr(Extra2);
        AU3_ControlListView(szTitle, szText, szControl, szCommand, szExtra1, szExtra2, szResult, nBufSize);
    }
    HMC_CHECK_CATCH;

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
wstring fn_AU3_ControlListView(HWND hWnd, HWND hCtrl, LPCWSTR Command, LPCWSTR Extra1, LPCWSTR Extra2)
{
    try
    {
        LPWSTR szResult = new wchar_t[50000];
        int nBufSize = 50000;

        LPCWSTR szCommand = hmc_string_util::string_to_lpstr(Command);
        LPCWSTR szExtra1 = hmc_string_util::string_to_lpstr(Extra1);
        LPCWSTR szExtra2 = hmc_string_util::string_to_lpstr(Extra2);
        AU3_ControlListViewByHandle(hWnd, hCtrl, szCommand, szExtra1, szExtra2, szResult, nBufSize);
    }
    HMC_CHECK_CATCH;

    return L"";
}