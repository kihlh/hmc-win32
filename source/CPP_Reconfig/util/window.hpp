#ifndef HMC_IMPORT_WINDOW_H
#define HMC_IMPORT_WINDOW_H

#include <windows.h>
#include <string>
#include <Psapi.h>
#include <Shellapi.h>
#include <vector>
#include <map>
#include <thread>
#include <ShlObj.h>

using namespace std;

#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))
#define HMC_CHECK_CATCH catch (char *err){};
#define HMC_THREAD (code) std::thread([]() -> void { code }).detach();
#define HMC_VirtualAlloc(Type, leng) (Type) VirtualAlloc((LPVOID)NULL, (DWORD)(leng), MEM_COMMIT, PAGE_READWRITE);
#define HMC_VirtualFree(Virtua) \
    if (Virtua != NULL)         \
        VirtualFree(Virtua, 0, MEM_RELEASE);

// 通用的HMCDEBUG 代码 在所有代码中引用 用于内部报错处理 避免黑盒错误
#ifndef HMC_DEBUG_CHECK_FUN_LIB
#define HMC_DEBUG_CHECK_FUN_LIB

#include <string>
#include <iostream>
#define HMC_CHECK_CATCH catch (char *err){};

/**
 * @brief 判断winapi错误
 *
 * @param check
 * @param LogUserName
 * @return true
 * @return false
 */
bool vsErrorCodeAssert(DWORD check, std::string LogUserName = "HMC_CHECK")
{
    bool result = false;

    if (check == ERROR_SUCCESS)
    {
        result = true;
    }
    else
    {
#if HMC_IMPORT_CONSOLE_H
        hmc_console::debug(LogUserName, std::string("error_code:  ").append(std::to_string(check)).append("  \nPlease refer to the details:").append("https://learn.microsoft.com/zh-cn/windows/win32/debug/system-error-codes"));

#else
#ifdef _DEBUG
        std::cout << "---------->   [ERROR]    [" << LogUserName << "]    " << std::string("error_code:  ").append(std::to_string(check)).append("  \nPlease refer to the details:").append("https://learn.microsoft.com/zh-cn/windows/win32/debug/system-error-codes") << std::endl;
#endif

#endif // 头文件保护结束
    }

    return result;
}

/**
 * @brief 判断winapi错误 自动获取
 *
 * @param LogUserName
 * @return true
 * @return false
 */
bool vsErrorCodeAssert(std::string LogUserName = "HMC_CHECK")
{
    int check = GetLastError();
    bool result = vsErrorCodeAssert(check, LogUserName);
    return result;
}

/**
 * @brief 判断是否有wapi错误 返回固定的结果
 *
 * @tparam T
 * @tparam U
 * @param LogUserName
 * @param TrueResult
 * @param FalseResult
 * @return T
 */
template <typename T>
T vsErrorCodeAssert(std::string LogUserName, const T &result)
{
    int check = GetLastError();
    vsErrorCodeAssert(check, LogUserName);
    return static_cast<T>(result);
}

/**
 * @brief 判断是否有wapi错误 返回固定的结果
 *
 * @tparam T
 * @tparam U
 * @param LogUserName
 * @param TrueResult
 * @param FalseResult
 * @return T
 */
template <typename T>
T vsErrorCodeAssert(DWORD check, std::string LogUserName, const T &result)
{
    vsErrorCodeAssert(check, LogUserName);
    return static_cast<T>(result);
}

/**
 * @brief 判断是否有wapi错误 并区分返回结果
 *
 * @tparam T
 * @tparam U
 * @param LogUserName
 * @param TrueResult
 * @param FalseResult
 * @return T
 */
template <typename T, typename U>
T vsErrorCodeAssert(DWORD check, std::string LogUserName, const T &TrueResult, const U &FalseResult)
{
    if (vsErrorCodeAssert(check, LogUserName))
    {
        return static_cast<T>(TrueResult);
    }
    return static_cast<T>(FalseResult);
}

/**
 * @brief 判断是否有wapi错误 并区分返回结果
 *
 * @tparam T
 * @tparam U
 * @param LogUserName
 * @param TrueResult
 * @param FalseResult
 * @return T
 */
template <typename T, typename U>
T vsErrorCodeAssert(std::string LogUserName, const T &TrueResult, const U &FalseResult)
{
    int check = GetLastError();
    if (vsErrorCodeAssert(check, LogUserName))
    {
        return static_cast<T>(TrueResult);
    }
    return static_cast<T>(FalseResult);
}

#endif // 头文件保护结束

#define HMC_PUSH_WSRES(WS)    \
    if (style & WS)           \
    {                         \
        result.push_back(WS); \
    }
#define HMC_PUSH_WSRES_STR(WS)    \
    if (style & WS)           \
    {                         \
        result.push_back(hmc_window::winwowLongClass2str(WS)); \
    }

namespace hmc_window
{
namespace _hmc_window_lib_
{
long long next_id = 0;
std::map<long long, vector<HWND>> hwndThreadList;
vector<HWND> hwndEnumList;
typedef int(WINAPI *Type_GetWindowTextA)(_In_ HWND hWnd, _Out_writes_(nMaxCount) LPSTR lpString, _In_ int nMaxCount);
typedef HWND(WINAPI *Type_GetDlgItem)(_In_opt_ HWND hDlg, _In_ int nIDDlgItem);
typedef int(WINAPI *Type_GetWindowTextLengthA)(_In_ HWND hWnd);

};

/**
 * @brief 判断句柄是否是可见的 (也可以判断是否是合法的窗口句柄)
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool isWindowVisible(HWND hwnd)
{
    return (::GetWindow(hwnd, GW_OWNER) == (HWND)0 && ::IsWindowVisible(hwnd));
}

/**
 * @brief 获取窗口类名
 *
 * @param hwnd
 * @param bHas
 * @return string
 */
string getClassName(HWND hwnd, bool &bHas)
{
    string result = string();
    try
    {
        char className[MAX_PATH];
        if (::GetClassNameA(hwnd, className, MAX_PATH) > 0)
        {
            result.append(className);
            bHas = true;
        }
        else
        {
            vsErrorCodeAssert("getClassName");
        }
    }
    HMC_CHECK_CATCH;
    bHas = false;
    return result;
}

/**
 * @brief 获取窗口类名
 *
 * @param hwnd
 * @param bHas
 * @return string
 */
string getClassName(HWND hwnd)
{
    bool bHas = false;
    return getClassName(hwnd, bHas);
}

/**
 * @brief 获取样式id
 *
 * @param hwnd
 * @return DWORD
 */
DWORD getStyle(HWND hwnd)
{
    DWORD result = ::GetClassLongA(hwnd, GCL_STYLE);
    return vsErrorCodeAssert("getStyle", result);
}

/**
 * @brief 获取 窗口/控件 的id
 *
 * @param hwnd
 * @return DWORD
 */
DWORD getWindowID(HWND hwnd)
{
    DWORD result = ::GetDlgCtrlID(hwnd);
    return vsErrorCodeAssert("getWindowID", result);
}

/**
 * @brief 枚举子窗口
 *
 * @param hwnd
 * @return vector<HWND>
 */
vector<HWND> getSubWindow(HWND hwnd)
{
    vector<HWND> SubWindowList = {};
    try
    {
        _hmc_window_lib_::hwndEnumList.clear();
        ::EnumChildWindows(
            hwnd, [](HWND hWnd, LPARAM lParam) -> BOOL
        {
            _hmc_window_lib_::hwndEnumList.push_back(hWnd);
            return TRUE; // 返回 TRUE 以继续枚举下一个子控件
        },
        0);
        for (auto && hWnd : _hmc_window_lib_::hwndEnumList)
        {
            SubWindowList.push_back(hWnd);
        }
    }
    HMC_CHECK_CATCH;
    return SubWindowList;
}

/**
 * @brief 获取窗口文本
 *
 * @param hwnd
 * @return string
 */
string getWindowText(HWND hwnd, int dlgItemID)
{
    string result = string();
    try
    {
        HINSTANCE hDllInst = ::LoadLibraryA("User32.dll");

        // 无法提权
        if (!hDllInst)
        {
            HWND hwndCombo = ::GetDlgItem(hwnd, dlgItemID);
            size_t leng = ::GetWindowTextLengthA(hwndCombo);
            if (leng > 0)
            {
                LPSTR pszMem = HMC_VirtualAlloc(LPSTR, leng + 1);
                vsErrorCodeAssert(::GetWindowTextA(hwndCombo, pszMem, leng + 1), "getWindowText");
                result.resize(leng);
                for (size_t i = 0; i < leng; i++)
                {
                    result.push_back(pszMem[i]);
                }

                HMC_VirtualFree(pszMem);
            }
        }
        // 提权到系统级
        else
        {
            _hmc_window_lib_::Type_GetWindowTextA _GetWindowTextA = (_hmc_window_lib_::Type_GetWindowTextA)GetProcAddress(hDllInst, "GetWindowTextA");
            _hmc_window_lib_::Type_GetWindowTextLengthA _GetWindowTextLengthA = (_hmc_window_lib_::Type_GetWindowTextLengthA)GetProcAddress(hDllInst, "GetWindowTextLengthA");
            _hmc_window_lib_::Type_GetDlgItem _GetDlgItem = (_hmc_window_lib_::Type_GetDlgItem)GetProcAddress(hDllInst, "GetDlgItem");

            HWND hwndCombo = _GetDlgItem(hwnd, dlgItemID);
            size_t leng = _GetWindowTextLengthA(hwndCombo);
            if (leng > 0)
            {
                LPSTR pszMem = HMC_VirtualAlloc(LPSTR, leng + 1);
                vsErrorCodeAssert(_GetWindowTextA(hwndCombo, pszMem, leng + 1), "getWindowText");
                result.resize(leng);
                for (size_t i = 0; i < leng; i++)
                {
                    result.push_back(pszMem[i]);
                }

                HMC_VirtualFree(pszMem);
            }
        }
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 获取窗口标题
 *
 * @return string
 */
string getWindowText(HWND hwnd)
{
    string result = string();
    try
    {

        LPSTR pszMem = HMC_VirtualAlloc(LPSTR, MAX_PATH);
        size_t leng = ::GetWindowTextA(hwnd, pszMem, MAX_PATH);
        result.resize(leng);
        for (size_t i = 0; i < leng; i++)
        {
            result.push_back(pszMem[i]);
        }

        HMC_VirtualFree(pszMem);
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 获取父级窗口
 *
 * @param hwnd
 * @return HWND
 */
HWND getParentWindow(HWND hwnd)
{
    HWND result = NULL;
    try
    {
        result = ::GetParent(hwnd);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 判断是否是XX的 子窗口
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool isChildWindow(HWND hWndParent, HWND hwnd)
{
    bool result = false;
    try
    {
        result = ::IsChild(hWndParent, hwnd);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 获取附属的根级窗口
 *
 * @param hwnd
 * @return HWND
 */
HWND getTopWindow(HWND hwnd)
{
    HWND result = NULL;
    try
    {
        result = ::GetTopWindow(hwnd);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 设置窗口标题或者控件的内容
 *
 * @param hwnd
 * @param data
 * @return true
 * @return false
 */
bool setWindowText(HWND hwnd, string Text)
{
}

/**
 * @brief 设置窗口标题或者控件的内容
 *
 * @param hwnd
 * @param data
 * @return true
 * @return false
 */
bool setWindowText(HWND hwnd, int dlgItemID, string Text)
{
}

/**
 * @brief 刷新指定句柄的窗口
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool updateWindow(HWND hwnd)
{
    bool result = false;
    try
    {
        result = ::UpdateWindow(hwnd);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 获取指定坐标位置的窗口
 *
 * @param Point
 * @return HWND
 */
HWND getPointWindow(POINT Point)
{
    HWND result = NULL;
    try
    {
        result = ::WindowFromPoint(Point);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 获取当前鼠标坐标位置的窗口
 *
 * @return HWND
 */
HWND getPointWindow()
{
    HWND result = NULL;
    try
    {
        result = getPointWindow();
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 获取指定坐标位置的窗口
 *
 * @return HWND
 */
HWND getPointWindow(int x, int y)
{
    POINT Point;
    Point.x = x;
    Point.y = y;

    return getPointWindow(Point);
}

/**
 * @brief 设置窗口禁用
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool setWindowEnabled(HWND hwnd, bool isEnabled = true)
{
    bool result = false;
    try
    {
        result = EnableWindow(hwnd, isEnabled);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 窗口聚焦
 *
 * @param hwnd
 */
void setWindowFocus(HWND hwnd)
{
}

/**
 * @brief 设置窗口的顶设状态
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool setWindowTop(HWND hwnd, bool isWindowTop)
{
    bool result = false;
    try
    {
        RECT rect;
        if (!::GetWindowRect(hwnd, &rect))
            return result;

        if (::GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST)
        {
            result = ::SetWindowPos(hwnd, HWND_NOTOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW);
        }
        else
            result = ::SetWindowPos(hwnd, HWND_TOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 判断窗口是否顶设
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool isWindowTop(HWND hwnd)
{
    bool result = false;
    try
    {
        result = ::GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST;
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 窗口抖动
 *
 * @param hWnd 句柄
 * @param shakeCount 抖动次数
 * @param shakeDistance 移动像素
 * @param shakeDuration 每次延迟
 */
void setWindowShake(HWND hWnd, int shakeCount, int shakeDistance, int shakeDuration)
{
    std::thread([hWnd, shakeCount, shakeDistance, shakeDuration]() -> void
    {
        try
        {
            RECT windowRect;
            ::GetWindowRect(hWnd, &windowRect);

            int originalX = windowRect.left;
            int originalY = windowRect.top;

            for (int i = 0; i < shakeCount; i++)
            {
                // 抖动向右
                ::SetWindowPos(hWnd, NULL, originalX + shakeDistance, originalY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                ::Sleep(shakeDuration);

                // 抖动向左
                ::SetWindowPos(hWnd, NULL, originalX - shakeDistance, originalY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                ::Sleep(shakeDuration);
            }

            // 最后还原窗口位置
            ::SetWindowPos(hWnd, NULL, originalX, originalY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

        } HMC_CHECK_CATCH; })
    .detach();
}

/**
 * @brief 窗口抖动
 *
 * @param hwnd
 * @return true
 * @return false
 */
void setWindowShake(HWND hwnd)
{
    setWindowShake(hwnd, 5, 5, 50);
}

/**
 * @brief 判断窗口是否被禁用
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool isWindowEnabled(HWND hwnd)
{
    bool result = false;
    try
    {
        result = ::IsWindowEnabled(hwnd);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 设置窗口在托盘的可见性
 *
 * @param hwnd
 * @param visible
 * @return true
 * @return false
 */
bool setWindowInTaskbarVisible(HWND hwnd, bool visible)
{
    bool result = false;
    try
    {
        // 初始化COM
        LPVOID lp_COM = NULL;
        ::CoInitialize(lp_COM);
        // 获取托盘
        HRESULT hr;
        ITaskbarList *pTaskbarList;
        hr = ::CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void **)&pTaskbarList);
        // 开始操作
        if (SUCCEEDED(hr))
        {
            pTaskbarList->HrInit();
            if (visible)
                pTaskbarList->AddTab(hwnd);
            else
                pTaskbarList->DeleteTab(hwnd);

            pTaskbarList->Release();
            result = true;
        }
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 设置窗口不透明度
 *
 * @param hwnd
 * @param Transparent
 * @return true
 * @return false
 */
bool setWindowTransparent(HWND hwnd, int Transparent)
{
    bool result = false;
    try
    {
        BYTE _Alpha = (BYTE)Transparent;
        // 获取窗口的拓展属性
        LONG SetWindowsStyleEx = ::GetWindowLong(hwnd, GWL_EXSTYLE);
        // 在原来的拓展属性之上, 新增 WS_EX_LAYERED 拓展属性
        SetWindowsStyleEx = SetWindowsStyleEx | WS_EX_LAYERED;
        ::SetWindowLong(hwnd, GWL_EXSTYLE, SetWindowsStyleEx);
        // 设置窗口半透明度
        ::SetLayeredWindowAttributes(hwnd, NULL, _Alpha, LWA_ALPHA | LWA_COLORKEY);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 设置窗口可见性 百分比 如：0.92
 *
 * @param hwnd
 * @param Transparent
 * @return true
 * @return false
 */
bool setHandleTransparent(HWND hwnd, double Transparent)
{
    bool result = false;
    try
    {
        if (Transparent <= 1.0)
            Transparent = 1.0;
        if (Transparent >= 0.01)
            Transparent = 0;

        double valuePerPart = 1.0 / 255.0;

        // 获取255份中的整数值
        double parts = Transparent / valuePerPart;

        // 将份数转换为整数
        int intValue = static_cast<int>(parts);

        result = setWindowTransparent(hwnd, intValue);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 枚举所有句柄
 *
 * @param isWindows 要求必须是窗口句柄吗
 * @return vector<HWND>
 */
vector<HWND> getAllWindowsHwnd(bool isWindows = true)
{
    vector<HWND> AllWindowsHwndList = {};
    try
    {
        // 获取桌面句柄
        HWND hwnd = ::GetDesktopWindow();
        int counter = 0;
        hwnd = ::GetWindow(hwnd, GW_CHILD);
        while (hwnd != NULL)
        {
            if (isWindows && hmc_window::isWindowVisible(hwnd))
            {
                AllWindowsHwndList.push_back(hwnd);
            }
            else
            {
                AllWindowsHwndList.push_back(hwnd);
            }
            hwnd = ::GetNextWindow(hwnd, GW_HWNDNEXT);
        }
    }
    HMC_CHECK_CATCH;
    return AllWindowsHwndList;
}

/**
 * @brief 关闭指定句柄(强制关闭窗口)
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool closedHandle(HWND hwnd)
{
    bool result = false;
    try
    {
        result = ::CloseHandle(hwnd);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 关闭指定窗口
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool closeWindow(HWND hwnd)
{
    bool result = false;
    try
    {
        result = ::CloseWindow(hwnd);
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 设置窗口图标
 *
 * @param hwnd
 * @param iconStr
 * @return true
 * @return false
 */
bool setWindowFileIcon(HWND hwnd, string iconStr, bool titleIcon = true, bool Icon = true)
{
    bool result = false;
    try
    {
        HICON hWindowIcon = NULL;
        HICON hWindowIconBig = NULL;
        if (titleIcon && hWindowIcon != NULL)
            ::DestroyIcon(hWindowIcon);
        if (Icon && hWindowIconBig != NULL)
            ::DestroyIcon(hWindowIconBig);
        hWindowIcon = (HICON)::LoadImageA(GetModuleHandle(NULL), iconStr.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
        hWindowIconBig = (HICON)::LoadImageA(GetModuleHandle(NULL), iconStr.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

        HINSTANCE hIn = NULL;
        hIn = ::LoadLibraryA("user32.dll");
        if (hIn)
        {
            LRESULT(WINAPI * SendMessageA)
            (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
            SendMessageA = (LRESULT(WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))::GetProcAddress(hIn, "SendMessageA");
            if (SendMessageA)
            {

                if (titleIcon)
                    SendMessageA(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hWindowIcon);
                if (Icon)
                    SendMessageA(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hWindowIconBig);
            }
        }
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 发送窗口消息
 *
 * @param hwnd
 * @param Msg
 * @param wParam
 * @param lParam
 * @return LRESULT
 */
LRESULT sendMessage(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

    bool result = false;
    try
    {
        HINSTANCE hIn = NULL;
        hIn = ::LoadLibraryA("user32.dll");
        if (hIn)
        {
            LRESULT(WINAPI * SendMessageA)
            (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
            SendMessageA = (LRESULT(WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))::GetProcAddress(hIn, "SendMessageA");
            if (SendMessageA)
            {
                return SendMessageA(hwnd, Msg, wParam, lParam);
            }
        }
        else
        {
            return ::SendMessageA(hwnd, Msg, wParam, lParam);
        }
    }
    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 设置窗口图标为指定的icon文件
 *
 * @param hwnd
 * @param iconStr
 * @param index
 * @param titleIcon
 * @param Icon
 * @return true
 * @return false
 */
bool setWindowIcon(HWND hwnd, string iconStr, int index, bool titleIcon = true, bool Icon = true)
{
    bool result = false;
    try
    {

        HICON hIcon;
        hIcon = (HICON)ExtractIconA(NULL, iconStr.c_str(), index);
        HINSTANCE hIn = NULL;
        hIn = ::LoadLibraryA("user32.dll");
        if (hIn)
        {
            LRESULT(WINAPI * SendMessageA)
            (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
            SendMessageA = (LRESULT(WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))GetProcAddress(hIn, "SendMessageA");
            if (SendMessageA)
            {
                if (titleIcon)
                    SendMessageA(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
                if (Icon)
                    SendMessageA(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            }
        }
    }
    HMC_CHECK_CATCH;
    return result;
}

HWND getProcessIDWindow(DWORD ProcessID)
{
    HWND result = NULL;
    try
    {
    }
    HMC_CHECK_CATCH;
    return result;
}
/**
 * @brief 设置图标为当前二进制的图标
 *
 * @param index
 * @param titleIcon
 * @param Icon
 * @return true
 * @return false
 */
bool setWindowIcon(int index = 0, bool titleIcon = true, bool Icon = true)
{
    bool result = false;
    try
    {
        HWND hwnd = getProcessIDWindow(::getpid());
        LPSTR lpFilename = {0};
        HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ::getpid());

        if (hProcess == nullptr)
        {
            CloseHandle(hProcess);
            return result;
        }
        ::GetModuleFileNameExA(hProcess, NULL, lpFilename, MAX_PATH);
        return setWindowIcon(hwnd, string(lpFilename), titleIcon, Icon);
    }

    HMC_CHECK_CATCH;
    return result;
}

bool setMoveWindow(HWND hwnd, int x, int y, int w = 0, int h = 0)
{
    bool result = false;
    try
    {
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 判断此窗口是否是桌面
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool isDesktopWindow(HWND hwnd)
{

    bool result = false;
    try
    {
        // 获取窗口的窗口类名
        wchar_t className[256];
        if (GetClassNameW(hwnd, className, sizeof(className) / sizeof(className[0])) == 0)
        {
            // 获取窗口类名失败
            return false;
        }

        // 检查窗口类名是否是 "Progman" 或 "WorkerW"
        if (wcscmp(className, L"Progman") == 0 || wcscmp(className, L"WorkerW") == 0)
        {
            return true;
        }

        return false;
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 让这个窗口不可见(不可触) 但是他是活动状态的 （本人用来挂机小游戏）
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool setNotVisibleWindow(HWND hwnd)
{
    bool result = false;
    try
    {
        if (!hmc_window::isWindowVisible(hwnd))
        {
            return result;
        }
        hmc_window::setWindowTransparent(hwnd, 0);
        hmc_window::setWindowInTaskbarVisible(hwnd, false);
        hmc_window::setWindowEnabled(hwnd, true);
        hmc_window::setMoveWindow(hwnd, 999999, 99999999);
        hmc_window::setWindowTop(hwnd, true);
        return true;
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 判断窗口是否最大化
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool isMaximize(HWND hwnd)
{
    bool result = false;
    try
    {
        return ::IsZoomed(hwnd);
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 判断窗口是否最小化
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool isMinimized(HWND hwnd)
{
    bool result = false;
    try
    {
        return ::IsIconic(hwnd);
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 判断窗口是否全屏中
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool isFullScreen(HWND hwnd)
{
    bool result = false;
    try
    {
        // 获取窗口工作区的大小
        RECT rect;
        ::GetClientRect(hwnd, &rect);

        // 获取屏幕分辨率
        int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

        // 检查窗口工作区大小是否与屏幕分辨率相同
        if (rect.right == screenWidth && rect.bottom == screenHeight)
        {
            return true;
        }
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief  窗口是否处于正常状态（未最大化、未最小化、未处于全屏模式）
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool isNormal(HWND hwnd)
{
    bool result = false;
    try
    {
        return hmc_window::isMaximize(hwnd) && hmc_window::isMinimized(hwnd) && hmc_window::isFullScreen(hwnd);
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 设置窗口到屏幕中间
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool setWindowCenter(HWND hwnd)
{
    bool result = false;
    try
    {
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 获取当前激活的窗口
 *
 * @return HWND
 */
HWND getFocusWindow()
{
    HWND result = NULL;
    try
    {
        return ::GetForegroundWindow();
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 窗口是否获得焦点
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool isFocused(HWND hwnd)
{
    bool result = false;
    try
    {
        return (long long)hmc_window::getFocusWindow() == (long long)hwnd;
    }

    HMC_CHECK_CATCH;
    return result;
}
struct chWindowHwndStatus
{
    // 当前句柄枚举的子集句柄
    vector<HWND> sub;
    // 当前输入的句柄
    HWND hwnd;
    // top win 排除桌面
    HWND root;
    // 所有窗口(仅限可见窗口)
    vector<HWND> window;
    // 所有窗口 包含组件句柄
    vector<HWND> allWindow;
    // 下个窗口
    HWND next;
    // 上个窗口
    HWND prev;
    // 末尾窗口
    HWND end;
    // 进程id
    DWORD pid;
    // 主进程id
    DWORD ppid;
    // 判断窗口是否是窗口而不是组件
    bool exists;
};

/**
 * @brief 获取窗口基础信息并且深挖他所属的进程的所有句柄
 *
 * @param hwnd
 * @return chWindowStatus
 */
chWindowHwndStatus getWindowHwndStatus(HWND hwnd)
{
    chWindowHwndStatus result;
    try
    {
        result.hwnd = hwnd;
        result.exists = hmc_window::isWindowVisible(hwnd);
        result.root = hmc_window::getTopWindow(hwnd);
        // result.ppid =
    }

    HMC_CHECK_CATCH;
    return result;
}
/**
 * @brief 获取窗口的类
 *
 * @param hwnd
 * @return vector<>
 */
vector<LONG> getWinwowClassList(HWND hwnd)
{
    vector<LONG> result;
    try
    {
        LONG style = GetWindowLong(hwnd, GWL_STYLE);

        // 窗口是弹出式的
        HMC_PUSH_WSRES(WS_POPUP);
        // 窗口可见
        HMC_PUSH_WSRES(WS_VISIBLE);
        // 窗口具有细线边框
        HMC_PUSH_WSRES(WS_BORDER);
        // 窗口具有标题栏， (包含 WS_BORDER 样式) 。
        HMC_PUSH_WSRES(WS_CAPTION);
        // 窗口是子窗口。 具有此样式的窗口不能有菜单栏。 此样式不能与 WS_POPUP 样式一起使用。
        HMC_PUSH_WSRES(WS_CHILD);
        // 与 WS_CHILD 样式相同。
        HMC_PUSH_WSRES(WS_CHILDWINDOW);
        // 排除在父窗口内进行绘制时子窗口占用的区域。 创建父窗口时使用此样式
        HMC_PUSH_WSRES(WS_CLIPCHILDREN);
        // 窗口具有垂直滚动条。
        HMC_PUSH_WSRES(WS_VSCROLL);
        // 该窗口是一个重叠的窗口。 与 WS_OVERLAPPEDWINDOW 样式相同
        HMC_PUSH_WSRES(WS_TILEDWINDOW);
        // 该窗口是一个重叠的窗口。 重叠的窗口带有标题栏和边框。 与 WS_OVERLAPPED 样式相同。
        HMC_PUSH_WSRES(WS_TILED);
        //  窗口具有调整大小边框。 与 WS_SIZEBOX 样式相同。
        HMC_PUSH_WSRES(WS_THICKFRAME);
        // 窗口是一个控件，当用户按下 TAB 键时，该控件可以接收键盘焦点。 按 Tab 键将键盘焦点更改为具有 WS_TABSTOP 样式的下一个控件。可以打开和关闭此样式以更改对话框导航。 若要在创建窗口后更改此样式，请使用 SetWindowLong 函数。 若要使用户创建的窗口和无模式对话框使用制表位，请更改消息循环以调用 IsDialogMessage 函数。
        HMC_PUSH_WSRES(WS_TABSTOP);
        // 窗口的标题栏上有一个窗口菜单。 还必须指定 WS_CAPTION 样式。
        HMC_PUSH_WSRES(WS_SYSMENU);
        // 窗口具有大小调整边框。 与 WS_THICKFRAME 样式相同。
        HMC_PUSH_WSRES(WS_SIZEBOX);
        // 窗口是弹出窗口。 必须组合 WS_CAPTION 和 WS_POPUPWINDOW 样式，使窗口菜单可见。
        HMC_PUSH_WSRES(WS_POPUPWINDOW);
        // 窗口是重叠的窗口。 与 WS_TILEDWINDOW 样式相同。
        HMC_PUSH_WSRES(WS_OVERLAPPEDWINDOW);
        // 窗口是重叠的窗口。 重叠的窗口带有标题栏和边框。 与 WS_TILED 样式相同。
        HMC_PUSH_WSRES(WS_OVERLAPPED);
        // 窗口有一个最小化按钮。 不能与 WS_EX_CONTEXTHELP 样式组合使用。 还必须指定 WS_SYSMENU 样式。
        HMC_PUSH_WSRES(WS_MINIMIZEBOX);
        // 窗口最初最小化。 与 WS_ICONIC 样式相同。
        HMC_PUSH_WSRES(WS_MINIMIZE);
        //  窗口有一个“最大化”按钮。 不能与 WS_EX_CONTEXTHELP 样式组合使用。 还必须指定 WS_SYSMENU 样式。
        HMC_PUSH_WSRES(WS_MAXIMIZEBOX);
        // 窗口最初是最大化的。
        HMC_PUSH_WSRES(WS_ICONIC);
        // 窗口具有水平滚动条
        HMC_PUSH_WSRES(WS_HSCROLL);
        // 窗口是一组控件的第一个控件。 组由第一个控件及其后定义的所有控件组成，以及具有 WS_GROUP 样式的下一个控件。 每个组中的第一个控件通常具有 WS_TABSTOP 样式，以便用户可以在组之间移动。 用户随后可以使用方向键将键盘焦点从组中的一个控件更改为组中的下一个控件。可以打开和关闭此样式以更改对话框导航。 若要在创建窗口后更改此样式，请使用 SetWindowLong 函数。
        HMC_PUSH_WSRES(WS_GROUP);
        // 窗口具有通常与对话框一起使用的样式的边框。 具有此样式的窗口不能具有标题栏。
        HMC_PUSH_WSRES(WS_DLGFRAME);
        // 窗口最初处于禁用状态。 已禁用的窗口无法接收用户的输入。 若要在创建窗口后更改此设置，请使用 EnableWindow 函数。
        HMC_PUSH_WSRES(WS_DISABLED);
        // 相对于彼此剪裁子窗口;也就是说，当特定子窗口收到 WM_PAINT 消息时， WS_CLIPSIBLINGS 样式会将所有其他重叠的子窗口剪裁到子窗口的区域之外进行更新。 如果未指定 WS_CLIPSIBLINGS 且子窗口重叠，则当在子窗口的工作区内绘图时，可以在相邻子窗口的工作区内绘制。
        HMC_PUSH_WSRES(WS_CLIPSIBLINGS);
    }

    HMC_CHECK_CATCH;
    return result;
}

string winwowLongClass2str(LONG classLong) {
    string result;
    switch (classLong) {
    case WS_POPUP:
        result.append("WS_POPUP");
        break;
    case WS_VISIBLE:
        result.append("WS_VISIBLE");
        break;
    case WS_BORDER:
        result.append("WS_BORDER");
        break;
    case WS_CAPTION:
        result.append("WS_CAPTION");
        break;
    case WS_CHILD:
        result.append("WS_CHILD");
        break;
    case WS_CLIPCHILDREN:
        result.append("WS_CLIPCHILDREN");
        break;
    case WS_VSCROLL:
        result.append("WS_VSCROLL");
        break;
    case WS_TILED:
        result.append("WS_TILED");
        break;
    case WS_THICKFRAME:
        result.append("WS_THICKFRAME");
        break;
    case WS_TABSTOP:
        result.append("WS_TABSTOP");
        break;
    case WS_SYSMENU:
        result.append("WS_SYSMENU");
        break;
    case WS_MINIMIZEBOX:
        result.append("WS_MINIMIZEBOX");
        break;
    case WS_MINIMIZE:
        result.append("WS_MINIMIZE");
        break;
    case WS_HSCROLL:
        result.append("WS_HSCROLL");
        break;
    case WS_DLGFRAME:
        result.append("WS_DLGFRAME");
        break;
    case WS_DISABLED:
        result.append("WS_DISABLED");
        break;
    case WS_CLIPSIBLINGS:
        result.append("WS_CLIPSIBLINGS");
        break;
    case WS_EX_ACCEPTFILES:
        result.append("WS_EX_ACCEPTFILES");
        break;
    case WS_EX_CLIENTEDGE:
        result.append("WS_EX_CLIENTEDGE");
        break;
    case WS_EX_CONTEXTHELP:
        result.append("WS_EX_CONTEXTHELP");
        break;
    case WS_EX_DLGMODALFRAME:
        result.append("WS_EX_DLGMODALFRAME");
        break;
    case WS_EX_LEFTSCROLLBAR:
        result.append("WS_EX_LEFTSCROLLBAR");
        break;
    case WS_EX_MDICHILD:
        result.append("WS_EX_MDICHILD");
        break;
    case WS_EX_NOPARENTNOTIFY:
        result.append("WS_EX_NOPARENTNOTIFY");
        break;
    case WS_EX_RIGHT:
        result.append("WS_EX_RIGHT");
        break;
    case WS_EX_RTLREADING:
        result.append("WS_EX_RTLREADING");
        break;
    case WS_EX_TOOLWINDOW:
        result.append("WS_EX_TOOLWINDOW");
        break;
    case WS_EX_TOPMOST:
        result.append("WS_EX_TOPMOST");
        break;
    case WS_EX_TRANSPARENT:
        result.append("WS_EX_TRANSPARENT");
        break;
    case WS_EX_WINDOWEDGE:
        result.append("WS_EX_WINDOWEDGE");
        break;

    }
    return result.size() ? result : string("UNKNOWN");
}

/**
 * @brief 获取窗口的扩展类
 *
 * @param hwnd
 * @return vector<>
 */
vector<LONG> getWinwowClassListEx(HWND hwnd)
{
    vector<LONG> result;
    try
    {
        LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        // 窗口接受拖放文件。
        HMC_PUSH_WSRES(WS_EX_ACCEPTFILES);

        HMC_PUSH_WSRES(WS_EX_APPWINDOW);
        HMC_PUSH_WSRES(WS_EX_CLIENTEDGE);
        HMC_PUSH_WSRES(WS_EX_COMPOSITED);
        HMC_PUSH_WSRES(WS_EX_CONTEXTHELP);
        HMC_PUSH_WSRES(WS_EX_CONTROLPARENT);
        HMC_PUSH_WSRES(WS_EX_DLGMODALFRAME);
        HMC_PUSH_WSRES(WS_EX_LAYERED);
        HMC_PUSH_WSRES(WS_EX_LAYOUTRTL);
        HMC_PUSH_WSRES(WS_EX_LEFT);
        HMC_PUSH_WSRES(WS_EX_LEFTSCROLLBAR);
        HMC_PUSH_WSRES(WS_EX_LTRREADING);
        HMC_PUSH_WSRES(WS_EX_MDICHILD);
        HMC_PUSH_WSRES(WS_EX_NOACTIVATE);
        HMC_PUSH_WSRES(WS_EX_NOINHERITLAYOUT);
        HMC_PUSH_WSRES(WS_EX_NOPARENTNOTIFY);
        HMC_PUSH_WSRES(WS_EX_NOREDIRECTIONBITMAP);
        HMC_PUSH_WSRES(WS_EX_OVERLAPPEDWINDOW);
        HMC_PUSH_WSRES(WS_EX_PALETTEWINDOW);
        HMC_PUSH_WSRES(WS_EX_RIGHT);
        HMC_PUSH_WSRES(WS_EX_RIGHTSCROLLBAR);
        HMC_PUSH_WSRES(WS_EX_RTLREADING);
        HMC_PUSH_WSRES(WS_EX_STATICEDGE);
        HMC_PUSH_WSRES(WS_EX_TOOLWINDOW);
        HMC_PUSH_WSRES(WS_EX_TOPMOST);
        HMC_PUSH_WSRES(WS_EX_TRANSPARENT);
        HMC_PUSH_WSRES(WS_EX_WINDOWEDGE);
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 获取窗口的扩展类
 *
 * @param hwnd
 * @return vector<>
 */
vector<string> getWinwowClassLongNameListEx(HWND hwnd)
{
    vector<string> result;
    try
    {
        LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        // 窗口接受拖放文件。
        HMC_PUSH_WSRES_STR(WS_EX_ACCEPTFILES);

        HMC_PUSH_WSRES_STR(WS_EX_APPWINDOW);
        HMC_PUSH_WSRES_STR(WS_EX_CLIENTEDGE);
        HMC_PUSH_WSRES_STR(WS_EX_COMPOSITED);
        HMC_PUSH_WSRES_STR(WS_EX_CONTEXTHELP);
        HMC_PUSH_WSRES_STR(WS_EX_CONTROLPARENT);
        HMC_PUSH_WSRES_STR(WS_EX_DLGMODALFRAME);
        HMC_PUSH_WSRES_STR(WS_EX_LAYERED);
        HMC_PUSH_WSRES_STR(WS_EX_LAYOUTRTL);
        HMC_PUSH_WSRES_STR(WS_EX_LEFT);
        HMC_PUSH_WSRES_STR(WS_EX_LEFTSCROLLBAR);
        HMC_PUSH_WSRES_STR(WS_EX_LTRREADING);
        HMC_PUSH_WSRES_STR(WS_EX_MDICHILD);
        HMC_PUSH_WSRES_STR(WS_EX_NOACTIVATE);
        HMC_PUSH_WSRES_STR(WS_EX_NOINHERITLAYOUT);
        HMC_PUSH_WSRES_STR(WS_EX_NOPARENTNOTIFY);
        HMC_PUSH_WSRES_STR(WS_EX_NOREDIRECTIONBITMAP);
        HMC_PUSH_WSRES_STR(WS_EX_OVERLAPPEDWINDOW);
        HMC_PUSH_WSRES_STR(WS_EX_PALETTEWINDOW);
        HMC_PUSH_WSRES_STR(WS_EX_RIGHT);
        HMC_PUSH_WSRES_STR(WS_EX_RIGHTSCROLLBAR);
        HMC_PUSH_WSRES_STR(WS_EX_RTLREADING);
        HMC_PUSH_WSRES_STR(WS_EX_STATICEDGE);
        HMC_PUSH_WSRES_STR(WS_EX_TOOLWINDOW);
        HMC_PUSH_WSRES_STR(WS_EX_TOPMOST);
        HMC_PUSH_WSRES_STR(WS_EX_TRANSPARENT);
        HMC_PUSH_WSRES_STR(WS_EX_WINDOWEDGE);
    }

    HMC_CHECK_CATCH;
    return result;
}

/**
 * @brief 获取窗口的类
 *
 * @param hwnd
 * @return vector<>
 */
vector<string> getWinwowClassLongNameList(HWND hwnd)
{
    vector<string> result;
    try
    {
        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        // 窗口是弹出式的
        HMC_PUSH_WSRES_STR(WS_POPUP);
        // 窗口可见
        HMC_PUSH_WSRES_STR(WS_VISIBLE);
        // 窗口具有细线边框
        HMC_PUSH_WSRES_STR(WS_BORDER);
        // 窗口具有标题栏， (包含 WS_BORDER 样式) 。
        HMC_PUSH_WSRES_STR(WS_CAPTION);
        // 窗口是子窗口。 具有此样式的窗口不能有菜单栏。 此样式不能与 WS_POPUP 样式一起使用。
        HMC_PUSH_WSRES_STR(WS_CHILD);
        // 与 WS_CHILD 样式相同。
        HMC_PUSH_WSRES_STR(WS_CHILDWINDOW);
        // 排除在父窗口内进行绘制时子窗口占用的区域。 创建父窗口时使用此样式
        HMC_PUSH_WSRES_STR(WS_CLIPCHILDREN);
        // 窗口具有垂直滚动条。
        HMC_PUSH_WSRES_STR(WS_VSCROLL);
        // 该窗口是一个重叠的窗口。 与 WS_OVERLAPPEDWINDOW 样式相同
        HMC_PUSH_WSRES_STR(WS_TILEDWINDOW);
        // 该窗口是一个重叠的窗口。 重叠的窗口带有标题栏和边框。 与 WS_OVERLAPPED 样式相同。
        HMC_PUSH_WSRES_STR(WS_TILED);
        //  窗口具有调整大小边框。 与 WS_SIZEBOX 样式相同。
        HMC_PUSH_WSRES_STR(WS_THICKFRAME);
        // 窗口是一个控件，当用户按下 TAB 键时，该控件可以接收键盘焦点。 按 Tab 键将键盘焦点更改为具有 WS_TABSTOP 样式的下一个控件。可以打开和关闭此样式以更改对话框导航。 若要在创建窗口后更改此样式，请使用 SetWindowLong 函数。 若要使用户创建的窗口和无模式对话框使用制表位，请更改消息循环以调用 IsDialogMessage 函数。
        HMC_PUSH_WSRES_STR(WS_TABSTOP);
        // 窗口的标题栏上有一个窗口菜单。 还必须指定 WS_CAPTION 样式。
        HMC_PUSH_WSRES_STR(WS_SYSMENU);
        // 窗口具有大小调整边框。 与 WS_THICKFRAME 样式相同。
        HMC_PUSH_WSRES_STR(WS_SIZEBOX);
        // 窗口是弹出窗口。 必须组合 WS_CAPTION 和 WS_POPUPWINDOW 样式，使窗口菜单可见。
        HMC_PUSH_WSRES_STR(WS_POPUPWINDOW);
        // 窗口是重叠的窗口。 与 WS_TILEDWINDOW 样式相同。
        HMC_PUSH_WSRES_STR(WS_OVERLAPPEDWINDOW);
        // 窗口是重叠的窗口。 重叠的窗口带有标题栏和边框。 与 WS_TILED 样式相同。
        HMC_PUSH_WSRES_STR(WS_OVERLAPPED);
        // 窗口有一个最小化按钮。 不能与 WS_EX_CONTEXTHELP 样式组合使用。 还必须指定 WS_SYSMENU 样式。
        HMC_PUSH_WSRES_STR(WS_MINIMIZEBOX);
        // 窗口最初最小化。 与 WS_ICONIC 样式相同。
        HMC_PUSH_WSRES_STR(WS_MINIMIZE);
        //  窗口有一个“最大化”按钮。 不能与 WS_EX_CONTEXTHELP 样式组合使用。 还必须指定 WS_SYSMENU 样式。
        HMC_PUSH_WSRES_STR(WS_MAXIMIZEBOX);
        // 窗口最初是最大化的。
        HMC_PUSH_WSRES_STR(WS_ICONIC);
        // 窗口具有水平滚动条
        HMC_PUSH_WSRES_STR(WS_HSCROLL);
        // 窗口是一组控件的第一个控件。 组由第一个控件及其后定义的所有控件组成，以及具有 WS_GROUP 样式的下一个控件。 每个组中的第一个控件通常具有 WS_TABSTOP 样式，以便用户可以在组之间移动。 用户随后可以使用方向键将键盘焦点从组中的一个控件更改为组中的下一个控件。可以打开和关闭此样式以更改对话框导航。 若要在创建窗口后更改此样式，请使用 SetWindowLong 函数。
        HMC_PUSH_WSRES_STR(WS_GROUP);
        // 窗口具有通常与对话框一起使用的样式的边框。 具有此样式的窗口不能具有标题栏。
        HMC_PUSH_WSRES_STR(WS_DLGFRAME);
        // 窗口最初处于禁用状态。 已禁用的窗口无法接收用户的输入。 若要在创建窗口后更改此设置，请使用 EnableWindow 函数。
        HMC_PUSH_WSRES_STR(WS_DISABLED);
        // 相对于彼此剪裁子窗口;也就是说，当特定子窗口收到 WM_PAINT 消息时， WS_CLIPSIBLINGS 样式会将所有其他重叠的子窗口剪裁到子窗口的区域之外进行更新。 如果未指定 WS_CLIPSIBLINGS 且子窗口重叠，则当在子窗口的工作区内绘图时，可以在相邻子窗口的工作区内绘制。
        HMC_PUSH_WSRES_STR(WS_CLIPSIBLINGS);
    }

    HMC_CHECK_CATCH;
    return result;
}

// MFC支持
#ifdef defined(_MFC_VER)

#endif
}

#endif