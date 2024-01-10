#include "hmc_windows_util.hpp"

namespace hmc_windows_util
{
    std::vector<HWND> _$_getSubWindows_temp;
    std::shared_mutex _$_getSubWindows_shared_mutex;
}

std::variant<std::wstring, DWORD> hmc_windows_util::getWindowTitle(HWND hwnd)
{
    std::wstring result = std::wstring();

    // 计算缓冲区大小

    DWORD buff_size = ::GetWindowTextLengthW(hwnd);

    HMC_EQ_RUN_LAST(buff_size);

    wchar_t *pszMem = new wchar_t[buff_size + 1];

    size_t leng = ::GetWindowTextW(hwnd, pszMem, buff_size + 1);

    HMC_EQ_RUN_LAST(leng);

    // 添加内容
    result.reserve(leng);

    for (size_t i = 0; i < leng; i++)
    {
        auto it = pszMem[i];
        if (it != L'\0')
        {
            result.push_back(it);
        }
    }

    return result;
}

std::variant<std::wstring, DWORD> hmc_windows_util::getWindowTitleInternal(HWND hwnd)
{
    std::wstring result = std::wstring();

    // 缓冲区

    wchar_t *pszMem = new wchar_t[512 + 1];

    size_t leng = ::InternalGetWindowText(hwnd, pszMem, 512 + 1);

    HMC_EQ_RUN_LAST(leng);

    // 添加内容
    result.reserve(leng);

    for (size_t i = 0; i < leng; i++)
    {
        auto it = pszMem[i];
        if (it != L'\0')
        {
            result.push_back(it);
        }
    }

    return result;
}

std::variant<std::wstring, DWORD> hmc_windows_util::getWindowText(HWND hwnd, int dlgItemID)
{
    std::wstring result = std::wstring();

    // 无法提权

    HWND hwndCombo = ::GetDlgItem(hwnd, dlgItemID);
    size_t leng = ::GetWindowTextLengthW(hwndCombo);
    if (leng > 0)
    {
        LPWSTR pszMem = HMC_VirtualAlloc(LPWSTR, leng + 1);
        HMC_VirtualFreeAuto(pszMem);
        leng = ::GetWindowTextW(hwndCombo, pszMem, leng + 1);
        HMC_EQ_RUN_LAST(leng);

        if (leng >= 1 && pszMem != NULL)
        {
            result.reserve(leng + 1);
            for (size_t i = 0; i < leng; i++)
            {
                auto at = pszMem[i];
                result.push_back(at);
            }
        }
    }

    // 提权到系统级
    if (result.empty())
    {
        HINSTANCE hDllInst = ::LoadLibraryA("User32.dll");

        if (hDllInst == NULL)
        {
            return ::GetLastError();
        }

        HMC_LibraryFreeAuto(hDllInst);

        typedef int(WINAPI * Type_GetWindowTextW)(_In_ HWND hWnd, _Out_writes_(nMaxCount) LPWSTR lpString, _In_ int nMaxCount);
        typedef HWND(WINAPI * Type_GetDlgItem)(_In_opt_ HWND hDlg, _In_ int nIDDlgItem);
        typedef int(WINAPI * Type_GetWindowTextLengthW)(_In_ HWND hWnd);

        Type_GetWindowTextW _GetWindowTextW = (Type_GetWindowTextW)::GetProcAddress(hDllInst, "GetWindowTextW");
        Type_GetWindowTextLengthW _GetWindowTextLengthA = (Type_GetWindowTextLengthW)::GetProcAddress(hDllInst, "GetWindowTextLengthW");
        Type_GetDlgItem _GetDlgItem = (Type_GetDlgItem)::GetProcAddress(hDllInst, "GetDlgItem");

        HWND hwndCombo = _GetDlgItem(hwnd, dlgItemID);
        size_t leng = _GetWindowTextLengthA(hwndCombo);
        HMC_EQ_RUN_LAST(leng);
        if (leng <= 1)
        {
            LPWSTR pszMem = HMC_VirtualAlloc(LPWSTR, leng + 1);
            HMC_VirtualFreeAuto(pszMem);
            leng = _GetWindowTextW(hwndCombo, pszMem, leng + 1);

            HMC_EQ_RUN_LAST(leng);

            result.reserve(leng + 1);
            if (leng >= 1 && pszMem != NULL)
            {
                for (size_t i = 0; i < leng; i++)
                {
                    auto at = pszMem[i];
                    result.push_back(at);
                }
            }
        }
    }

    return result;
}

std::variant<bool, DWORD> hmc_windows_util::setWindowTitle(HWND hwnd, std::wstring title)
{
    if (!::SetWindowTextW(hwnd, title.c_str() + L'\0'))
    {
        return ::GetLastError();
    }
    return true;
}

std::variant<std::vector<HWND>, DWORD> hmc_windows_util::getAllWindows(bool is_Windows = true)
{
    std::vector<HWND> result = {};
    // 获取桌面句柄
    HWND hwnd = ::GetDesktopWindow();

    HMC_EQ_RUN_LAST(hwnd);
    int counter = 0;

    hwnd = ::GetWindow(hwnd, GW_CHILD);
    HMC_EQ_RUN_LAST(hwnd);

    while (hwnd != NULL)
    {
        if (is_Windows && ::IsWindowVisible(hwnd))
        {
            result.push_back(hwnd);
        }
        else
        {
            result.push_back(hwnd);
        }
        hwnd = ::GetNextWindow(hwnd, GW_HWNDNEXT);
    }

    if (result.empty())
    {
        return ::GetLastError();
    }

    return result;
}

bool hmc_windows_util::isWindow(HWND hwnd)
{
    return (::GetWindow(hwnd, GW_OWNER) == (HWND)0 && ::IsWindowVisible(hwnd));
}

std::variant<std::wstring, DWORD> hmc_windows_util::getClassName(HWND hwnd)
{
    std::wstring result = std::wstring();
    wchar_t *className = new wchar_t[MAX_PATH + 1];
    int leng = ::GetClassNameW(hwnd, className, MAX_PATH + 1);

    HMC_EQ_RUN_LAST(leng);
    // 添加内容
    result.reserve(leng);

    for (int i = 0; i < leng; i++)
    {
        auto it = className[i];
        if (it != L'\0')
        {
            result.push_back(it);
        }
    }

    return result;
}

std::variant<std::vector<HWND>, DWORD> hmc_windows_util::getSubWindows(HWND hwnd)
{
    std::vector<HWND> result = {};
    result.clear();
    hmc_windows_util::_$_getSubWindows_shared_mutex.lock();

    bool isEnum = ::EnumChildWindows(
        hwnd, [](HWND hWnd, LPARAM lParam) -> BOOL
        {
            hmc_windows_util::_$_getSubWindows_temp.push_back(hWnd);
            return TRUE; // 返回 TRUE 以继续枚举下一个子控件
        },
        0);

    if (!isEnum)
    {
        hmc_windows_util::_$_getSubWindows_temp.clear();
        hmc_windows_util::_$_getSubWindows_shared_mutex.unlock();
        return ::GetLastError();
    }

    for (auto &&hWnd : hmc_windows_util::_$_getSubWindows_temp)
    {
        result.push_back(hWnd);
    }

    hmc_windows_util::_$_getSubWindows_temp.clear();

    hmc_windows_util::_$_getSubWindows_shared_mutex.unlock();

    return result;
}

std::variant<HWND, DWORD> hmc_windows_util::getParentWindow(HWND hwnd)
{
    HWND parent = ::GetParent(hwnd);
    if (parent == NULL)
    {
        DWORD error_code = ::GetLastError();
        if (error_code != 0)
        {
            return error_code;
        }
    }
    return parent;
}

bool hmc_windows_util::isChildWindow(HWND hWndParent, HWND hwnd)
{
    return ::IsChild(hWndParent, hwnd);
}

std::variant<HWND, DWORD> hmc_windows_util::getTopWindow(HWND hwnd)
{
    HWND result = NULL;
    result = ::GetTopWindow(hwnd);
    if (result == NULL)
    {
        DWORD error_code = ::GetLastError();
        if (error_code != 0)
        {
            return error_code;
        }
    }
    return result;
}

bool hmc_windows_util::updateWindow(HWND hwnd)
{
    return ::UpdateWindow(hwnd);
}

HWND hmc_windows_util::getPointWindow(POINT Point)
{
    return ::WindowFromPoint(Point);
}

HWND hmc_windows_util::getPointWindow()
{
    POINT curPoint;
    if (!::GetCursorPos(&curPoint))
    {
        return NULL;
    }

    return ::WindowFromPoint(curPoint);
}

HWND hmc_windows_util::getPointWindow(int x, int y)
{
    POINT Point;
    Point.x = x;
    Point.y = y;

    return ::WindowFromPoint(Point);
}

bool hmc_windows_util::setWindowEnabled(HWND hwnd, bool isEnabled)
{
    ::EnableWindow(hwnd, isEnabled);
    return (BOOL)isEnabled == ::IsWindowEnabled(hwnd);
}

bool hmc_windows_util::setWindowFocus(HWND hwnd)
{

    ::SetForegroundWindow(hwnd);
    if ((long long )::GetForegroundWindow() != (long long)hwnd)
    {
        return true;
    }

    ::SetActiveWindow(hwnd);
    if ((long long)::GetForegroundWindow() != (long long)hwnd)
    {
        return true;
    }

    ::ShowWindow(hwnd, SW_SHOW);
    if ((long long)::GetForegroundWindow() != (long long)hwnd)
    {
        return true;
    }

    return false;
}

std::variant<bool, DWORD> hmc_windows_util::killWindowProcess(HWND hwnd)
{

    DWORD pid = 0;
    if (hwnd != NULL || (::GetWindowThreadProcessId(hwnd, &pid) != 0) || pid == NULL)
    {
        if (hwnd != NULL)
        {
            return ::GetLastError();
        }
        else
        {
            return false;
        }
    }

    HANDLE process_Handle = ::OpenProcess(PROCESS_ALL_ACCESS, false, pid);

    if (process_Handle != NULL)
    {
        if (!::TerminateProcess(process_Handle, 0))
        {
            return ::GetLastError();
        }
        return true;
    }

    return false;
}

DWORD hmc_windows_util::getWindowProcessID(HWND hwnd)
{
    DWORD pid = 0;
    ::GetWindowThreadProcessId(hwnd, &pid);
    return pid;
}

bool hmc_windows_util::setWindowTop(HWND hwnd, bool isWindowTop)
{
    bool result = false;

    RECT rect;
    if (!::GetWindowRect(hwnd, &rect))
        return result;

    if (::GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST)
    {
        result = ::SetWindowPos(hwnd, HWND_NOTOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW);
    }
    else
        result = ::SetWindowPos(hwnd, HWND_TOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW);

    return result;
}

bool hmc_windows_util::isWindowTop(HWND hwnd)
{
    bool result = ::GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST;
    return result;
}

void hmc_windows_util::setWindowShake(HWND hWnd, int shakeCount, int shakeDistance, int shakeDuration)
{

    std::thread([hWnd, shakeCount, shakeDistance, shakeDuration]() -> void
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
                    ::SetWindowPos(hWnd, NULL, originalX, originalY, 0, 0, SWP_NOSIZE | SWP_NOZORDER); })
        .detach();
}

bool hmc_windows_util::isWindowEnabled(HWND hwnd)
{
    return ::IsWindowEnabled(hwnd);
}

bool hmc_windows_util::setWindowInTaskbarVisible(HWND hwnd, bool visible)
{
    bool result = false;

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

    return result;
}

bool hmc_windows_util::setWindowTransparent(HWND hwnd, int Transparent)
{
    bool result = false;

    BYTE _Alpha = (BYTE)Transparent;
    // 获取窗口的拓展属性
    LONG SetWindowsStyleEx = ::GetWindowLong(hwnd, GWL_EXSTYLE);
    // 在原来的拓展属性之上, 新增 WS_EX_LAYERED 拓展属性
    SetWindowsStyleEx = SetWindowsStyleEx | WS_EX_LAYERED;
    ::SetWindowLong(hwnd, GWL_EXSTYLE, SetWindowsStyleEx);
    // 设置窗口半透明度
    ::SetLayeredWindowAttributes(hwnd, NULL, _Alpha, LWA_ALPHA | LWA_COLORKEY);

    return result;
}

bool hmc_windows_util::setHandleTransparent(HWND hwnd, double Transparent)
{
    bool result = false;

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

    return result;
}

bool hmc_windows_util::closedHandle(HWND hwnd)
{
    return ::CloseHandle(hwnd);
}

/**
 * @brief 关闭指定窗口
 *
 * @param hwnd
 * @return true
 * @return false
 */
bool hmc_windows_util::closeWindow(HWND hwnd, bool destroy)
{
    bool result = false;

    if (!destroy)
    {
        result = ::CloseWindow(hwnd);
    }
    else
    {
        result = ::DestroyWindow(hwnd);
        // 销毁不掉  执行复杂逻辑的销毁流程
        if (::IsWindow(hwnd))
        {
            ::CloseHandle(hwnd);

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
                        ::CloseHandle(threadHandle);
                    }
                }
            }
        }
    }

    return result;
}

bool hmc_windows_util::setWindowFileIcon(HWND hwnd, std::string iconStr, bool titleIcon, bool Icon)
{
    bool result = false;

    HICON hIcon;
    hIcon = (HICON)ExtractIconA(NULL, iconStr.c_str(), 0);
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

    return result;
}

bool hmc_windows_util::isDesktopWindow(HWND hwnd)
{

    bool result = false;

    // 获取窗口的窗口类名
    wchar_t *className = new wchar_t[MAX_PATH + 1];
    DWORD length = 0;
    if ((length = ::GetClassNameW(hwnd, className, MAX_PATH + 1)) == 0)
    {
        // 获取窗口类名失败
        return false;
    }

    // 移除空白
    std::wstring className_temp = L"";
    className_temp.reserve(length);
    for (size_t i = 0; i < length; i++)
    {
        auto it = className[i];
        if (it != L'\0')
        {
            className_temp.push_back(it);
        }
    }

    // 检查窗口类名是否是 "Progman" 或 "WorkerW"
    if (::wcscmp(className, L"Progman") == 0 || ::wcscmp(className, L"WorkerW") == 0)
    {
        return true;
    }

    return false;
}

void hmc_windows_util::setWindowIcon(HWND hWnd, HICON hIcon , int index)
{

    char szFilePath[MAX_PATH];
    if (GetModuleFileNameA(NULL, szFilePath, MAX_PATH))
    {
        if (hIcon == NULL)
        {
            HINSTANCE hInst = LoadLibraryA("Shell32.dll");
            if (hInst)
            {
                HICON(WINAPI * ExtractIconA)
                (HINSTANCE hInst, LPCSTR pszExeFileName, UINT nIconIndex);
                ExtractIconA = (HICON(WINAPI *)(HINSTANCE hInst, LPCSTR pszExeFileName, UINT nIconIndex))GetProcAddress(hInst, "ExtractIconA");
                hIcon = ExtractIconA(hInst, szFilePath, index);
                FreeLibrary(hInst);
            }
        }
        HINSTANCE hIn = LoadLibraryA("user32.dll");
        if (hIn && hIcon != NULL)
        {
            LRESULT(WINAPI * SendMessageA)
            (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
            SendMessageA = (LRESULT(WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))GetProcAddress(hIn, "SendMessageA");
            if (SendMessageA)
            {
                SendMessageA(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
                SendMessageA(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            }
        }
    }
}

extern void hmc_windows_util::setWindowIcon(HWND hWnd, std::string iconPath, int index)
{
    HICON hIcon = NULL;
    HINSTANCE hInst = LoadLibraryA("Shell32.dll");
    if (hInst)
    {
        HICON(WINAPI * ExtractIconA)
        (HINSTANCE hInst, LPCSTR pszExeFileName, UINT nIconIndex);
        ExtractIconA = (HICON(WINAPI *)(HINSTANCE hInst, LPCSTR pszExeFileName, UINT nIconIndex))GetProcAddress(hInst, "ExtractIconA");
        hIcon = ExtractIconA(hInst, iconPath.c_str(), index);
        FreeLibrary(hInst);
    }

    if (hIcon != NULL)
    {
        setWindowIcon(hWnd, iconPath, index);
    }
}
