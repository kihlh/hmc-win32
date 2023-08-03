#include <windows.h>
#include <string>
#include <Psapi.h>
#include <Shellapi.h>
#include <vector>
#include <map>

using namespace std;
#ifdef defined(HMC_IMPORT_WINDOW_H)
#else

#define HMC_IMPORT_WINDOW_H

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
        return (GetWindow(hwnd, GW_OWNER) == (HWND)0 && IsWindowVisible(hwnd));
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
            if (GetClassNameA(hwnd, className, MAX_PATH) > 0)
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
        DWORD result = GetClassLongA(hwnd, GCL_STYLE);
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
        DWORD result = GetDlgCtrlID(hwnd);
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
            EnumChildWindows(
                hwnd, [](HWND hWnd, LPARAM lParam) -> BOOL
                {
                    _hmc_window_lib_::hwndEnumList.push_back(hWnd);
                    return TRUE; // 返回 TRUE 以继续枚举下一个子控件
                },
                0);
            for (auto &&hWnd : _hmc_window_lib_::hwndEnumList)
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
            HINSTANCE hDllInst = LoadLibraryA("User32.dll");

            // 无法提权
            if (!hDllInst)
            {
                HWND hwndCombo = GetDlgItem(hwnd, dlgItemID);
                size_t leng = GetWindowTextLengthA(hwndCombo);
                if (leng > 0)
                {
                    LPSTR pszMem = HMC_VirtualAlloc(LPSTR, leng + 1);
                    vsErrorCodeAssert(GetWindowTextA(hwndCombo, pszMem, leng + 1), "getWindowText");
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
            size_t leng = GetWindowTextA(hwnd, pszMem, MAX_PATH);
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
            result = GetParent(hwnd);
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
            result = IsChild(hWndParent, hwnd);
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
            result = GetTopWindow(hwnd);
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
    bool setWindowText(HWND hwnd, string data)
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
    bool setWindowText(HWND hwnd, int dlgItemID, string data)
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
            result = UpdateWindow(hwnd);
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
            result = WindowFromPoint(Point);
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

    
// MFC支持
#ifdef defined(_MFC_VER)

#endif
}

#endif