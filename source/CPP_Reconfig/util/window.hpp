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
    bool setWindowFocus(HWND hwnd)
    {
        bool result = false;

        try
        {
            ShowWindow(hwnd, SW_SHOW);
            result = (long)::GetFocus() == (long)hwnd;

            if (!result)
            {
                result = ::setWindowFocus(hwnd);
            }

            if (!result)
            {
                ::SetActiveWindow(hwnd);
            }
        }
        HMC_CHECK_CATCH;

        return result;
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

        }HMC_CHECK_CATCH; })
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
            ::SetLayeredWindowAttributes(hwnd, NULL, _Alpha, LWA_ALPHA);
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
    bool closeWindow(HWND hwnd, bool destroy = false)
    {
        bool result = false;
        try
        {
            if (!destroy)
            {
                result = ::CloseWindow(hwnd);
            }
            else
            {
                result = DestroyWindow(hwnd);
                // 销毁不掉  执行复杂逻辑的销毁流程
                if (IsWindow(hwnd))
                {
                    CloseHandle(hwnd);
                    result = !IsWindow(hwnd);
                    if (!result)
                    {
                        DWORD lpdwThreadId = NULL;

                        // 销毁不掉 销毁窗口所属的线程
                        ::GetWindowThreadProcessId(hwnd, &lpdwThreadId);
                        if (lpdwThreadId != NULL)
                        {
                            HANDLE threadHandle = ::OpenThread(THREAD_TERMINATE, FALSE, lpdwThreadId);
                            if (threadHandle != NULL)
                            {
                                ::TerminateThread(threadHandle, 0);
                                CloseHandle(threadHandle);
                            }
                        }

                        // 还失败 用系统dll的函数销毁
                    }
                }
            }
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

// MFC支持
#ifdef defined(_MFC_VER)

#endif
}

#endif