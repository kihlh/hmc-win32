#include "hmc_windows_util.hpp"

namespace hmc_windows_util
{
    std::vector<HWND> _$_getSubWindows_temp;
    std::shared_mutex _$_getSubWindows_shared_mutex;
}

// 这里写需要预设值的函数
namespace hmc_windows_util
{
    void hmc_windows_util::setWindowIconByExtract(HWND hWnd, std::optional<std::wstring> ExtractFilePath, std::optional<int> index, std::optional<int> set_type)
    {
        // 我用vsdebug的时候发现打开图标的过程是会导致异常的 而不是可以通过 GetLastError 查询不报错的错误
        // 例如用户传入的是个exe 但是调用的是 ico文件方法 将会导致非winapi异常
        try
        {

            // 没有窗口 查找当前进程的主窗口
            if (hWnd == NULL)
            {
                return;
            }

            std::wstring filePath = ExtractFilePath.value_or(L"");

            if (filePath.empty())
            {

                wchar_t *szFilePath = new wchar_t[MAX_PATH + 1];
                size_t len = ::GetModuleFileNameW(NULL, szFilePath, MAX_PATH + 1);
                if (len <= 1)
                {
                    return;
                }
            }

            HINSTANCE hInst = ::LoadLibraryA("Shell32.dll");

            HICON hIcon = NULL;

            if (hInst)
            {
                HMC_LibraryFreeAuto(hInst);
                HICON(WINAPI * ExtractIconW)
                (HINSTANCE hInst, LPCWSTR pszExeFileName, UINT nIconIndex);
                ExtractIconW = (HICON(WINAPI *)(HINSTANCE hInst, LPCWSTR pszExeFileName, UINT nIconIndex))GetProcAddress(hInst, "ExtractIconW");
                hIcon = ExtractIconW(hInst, reinterpret_cast<LPCWSTR>(filePath.c_str()), index.value_or(0));
            }

            HINSTANCE hIn = ::LoadLibraryA("user32.dll");
            if (hIn && hIcon != NULL)
            {
                HMC_LibraryFreeAuto(hIn);
                LRESULT(WINAPI * SendMessageW)
                (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
                SendMessageW = (LRESULT(WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))GetProcAddress(hIn, "SendMessageW");
                if (SendMessageW)
                {
                    if (set_type.value_or(0) == 0)
                    {
                        SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
                        SendMessageW(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
                        ::UpdateWindow(hWnd);
                        return;
                    }

                    // Titlebar icon: 16x16
                    if (set_type.value_or(0) == 1)
                    {
                        SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
                        ::UpdateWindow(hWnd);
                        return;
                    }

                    // Taskbar icon:  32x32
                    if (set_type.value_or(0) == 2)
                    {
                        SendMessageW(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
                        ::UpdateWindow(hWnd);
                        return;
                    }
                }
            }
        }
        HMC_ALL_CATCH_NONE;
    }

    bool hmc_windows_util::closeWindow(HWND hwnd, bool destroy)
    {
        bool result = false;

        if (hwnd == NULL)
        {
            return result;
        }

        HWND copy_hwnd = (HWND)(long long)hwnd;

        if (!destroy)
        {
            result = ::CloseWindow(copy_hwnd);
        }

        else
        {
            result = ::DestroyWindow(copy_hwnd);
            // 销毁不掉  执行复杂逻辑的销毁流程
            if (copy_hwnd != NULL && ::IsWindow(copy_hwnd))
            {
                ::CloseHandle(hwnd);

                if (copy_hwnd == NULL)
                {
                    return result;
                }

                // 有可能数据会丢失 重新复制一份
                copy_hwnd = (HWND)(long long)hwnd;

                result = !IsWindow(copy_hwnd);

                if (!result)
                {
                    DWORD lpdwThreadId = NULL;

                    // 销毁不掉 销毁窗口所属的线程
                    ::GetWindowThreadProcessId(copy_hwnd, &lpdwThreadId);
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

    void hmc_windows_util::setWindowIconByIco(HWND hWnd, std::optional<std::wstring> IcoFilePath, std::optional<int> index, std::optional<int> set_type)
    {
        // 我用vsdebug的时候发现打开图标的过程是会导致异常的 而不是可以通过 GetLastError 查询不报错的错误
        // 例如用户传入的是个ico 但是调用的是 exe文件方法 将会导致非winapi异常
        try
        {
            // 没有窗口 查找当前进程的主窗口
            if (hWnd == NULL)
            {
                return;
            }

            if (!IcoFilePath.has_value())
            {
                return;
            }

            HINSTANCE hInst = ::LoadLibraryA("Shell32.dll");

            HICON hWindowIcon = NULL;
            HICON hWindowIconBig = NULL;

            hWindowIcon = (HICON)LoadImageW(GetModuleHandle(NULL), IcoFilePath.value_or(L"").c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
            hWindowIconBig = (HICON)LoadImageW(GetModuleHandle(NULL), IcoFilePath.value_or(L"").c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

            std::shared_ptr<void> Icon_Auto_Close_Library(nullptr, [&](void *)
                                                          { 
    if (hWindowIcon != NULL)
        DestroyIcon(hWindowIcon);
    if (hWindowIconBig != NULL)
        DestroyIcon(hWindowIconBig); });

            HINSTANCE hIn = ::LoadLibraryA("user32.dll");
            if (hIn)
            {
                HMC_LibraryFreeAuto(hIn);
                LRESULT(WINAPI * SendMessageW)
                (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
                SendMessageW = (LRESULT(WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))GetProcAddress(hIn, "SendMessageW");
                if (SendMessageW)
                {
                    if (set_type.value_or(0) == 0)
                    {
                        SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hWindowIcon);
                        SendMessageW(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hWindowIconBig);
                        ::UpdateWindow(hWnd);
                        return;
                    }

                    // Titlebar icon: 16x16
                    if (set_type.value_or(0) == 1)
                    {
                        SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hWindowIcon);
                        ::UpdateWindow(hWnd);
                        return;
                    }

                    // Taskbar icon:  32x32
                    if (set_type.value_or(0) == 2)
                    {
                        SendMessageW(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hWindowIconBig);
                        ::UpdateWindow(hWnd);
                        return;
                    }
                }
            }
        }
        HMC_ALL_CATCH_NONE;
    }

    std::variant<std::vector<HWND>, DWORD> hmc_windows_util::getAllWindows(bool is_Windows)
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

    std::variant<bool, DWORD> hmc_windows_util::setMoveWindow(HWND hwnd, std::optional<int> x, std::optional<int> y, std::optional<int> w, std::optional<int> h)
    {

        if (hwnd == NULL)
            return false;

        RECT rect = {0, 0, 0, 0};
        if ((!w.has_value() || !h.has_value()) && !::GetWindowRect(hwnd, &rect))
        {
            DWORD Last_Error_Code = ::GetLastError();
            if (Last_Error_Code != 0)
            {
                return Last_Error_Code;
            }
        }

        int DeviceCapsWidth = ::GetSystemMetrics(SM_CXSCREEN);
        int DeviceCapsHeight = ::GetSystemMetrics(SM_CYSCREEN);

        int Env_height = (DeviceCapsHeight - rect.top) - (DeviceCapsHeight - rect.bottom);
        int Env_width = (DeviceCapsWidth - rect.left) - (DeviceCapsWidth - rect.right);

        int to_x = (x.has_value() ? x.value() : NULL);
        int to_y = (y.has_value() ? y.value() : NULL);
        int to_width = w.value_or(0) < 1 ? Env_width : w.value_or(0);
        int to_height = h.value_or(0) < 1 ? Env_height : h.value_or(0);

        // 重新设置窗口大小
        return ::MoveWindow(hwnd, to_x, to_y, to_width, to_height, true) ? true : ::GetLastError();
    }

}

std::variant<std::wstring, DWORD> hmc_windows_util::getWindowTitle(HWND hwnd)
{
    std::wstring result = std::wstring();

    // 计算缓冲区大小

    DWORD buff_size = ::GetWindowTextLengthW(hwnd);

    HMC_EQ_RUN_LAST(buff_size);

    wchar_t *pszMem = new wchar_t[buff_size + sizeof(wchar_t)];

    size_t leng = ::GetWindowTextW(hwnd, pszMem, buff_size + sizeof(wchar_t));

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
        int temp_len = (int)leng + 1;
        LPWSTR pszMem = HMC_VirtualAlloc(LPWSTR, temp_len);
        HMC_VirtualFreeAuto(pszMem);
        leng = ::GetWindowTextW(hwndCombo, pszMem, temp_len);
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
            int temp_len = (int)leng + 1;
            LPWSTR pszMem = HMC_VirtualAlloc(LPWSTR, temp_len);
            HMC_VirtualFreeAuto(pszMem);
            leng = _GetWindowTextW(hwndCombo, pszMem, temp_len);

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
    std::vector<HWND> subWindows;

    bool isEnum = ::EnumChildWindows(
        hwnd, [](HWND hWnd, LPARAM lParam) -> BOOL
        {
            auto pSubWindows = reinterpret_cast<std::vector<HWND> *>(lParam);
            pSubWindows->push_back(hWnd);
            return TRUE; // 继续枚举下一个子控件
        },
        reinterpret_cast<LPARAM>(&subWindows));

    if (!isEnum)
    {
        return ::GetLastError();
    }

    return subWindows;
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
    if ((long long)::GetForegroundWindow() != (long long)hwnd)
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
    if (hwnd == NULL || (::GetWindowThreadProcessId(hwnd, &pid) != 0) || pid == NULL)
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

std::vector<LONG> hmc_windows_util::getWinwowClassList(HWND hwnd)
{
    std::vector<LONG> result;

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

    return result;
}

std::string hmc_windows_util::winwowLongClass2str(LONG classLong)
{
    std::string result;
    switch (classLong)
    {
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
    case WS_TILEDWINDOW:
        result.append("WS_TILEDWINDOW");
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
    case WS_POPUPWINDOW:
        result.append("WS_POPUPWINDOW");
        break;
    case WS_MINIMIZEBOX:
        result.append("WS_MINIMIZEBOX");
        break;
    case WS_MINIMIZE:
        result.append("WS_MINIMIZE");
        break;
    case WS_CLIPSIBLINGS:
        result.append("WS_CLIPSIBLINGS");
        break;
    case WS_DLGFRAME:
        result.append("WS_DLGFRAME");
        break;
    case WS_HSCROLL:
        result.append("WS_HSCROLL");
        break;
    case WS_DISABLED:
        result.append("WS_DISABLED");
        break;
    }
    return result.size() ? result : std::string("WS_UNKNOWN");
}

std::string hmc_windows_util::winwowLongClass2strEx(LONG classLong)
{
    std::string result;
    switch (classLong)
    {
    case WS_EX_ACCEPTFILES:
        result.append("WS_EX_ACCEPTFILES");
        break;
    case WS_EX_APPWINDOW:
        result.append("WS_EX_APPWINDOW");
        break;
    case WS_EX_CLIENTEDGE:
        result.append("WS_EX_CLIENTEDGE");
        break;
    case WS_EX_CONTEXTHELP:
        result.append("WS_EX_CONTEXTHELP");
        break;
    case WS_EX_CONTROLPARENT:
        result.append("WS_EX_CONTROLPARENT");
        break;
    case WS_EX_DLGMODALFRAME:
        result.append("WS_EX_DLGMODALFRAME");
        break;
    case WS_EX_LAYERED:
        result.append("WS_EX_LAYERED");
        break;
    case WS_EX_LAYOUTRTL:
        result.append("WS_EX_LAYOUTRTL");
        break;
    case WS_EX_LEFT:
        result.append("WS_EX_LEFT");
        break;
    case WS_EX_COMPOSITED:
        result.append("WS_EX_COMPOSITED");
        break;
    case WS_EX_LEFTSCROLLBAR:
        result.append("WS_EX_LEFTSCROLLBAR");
        break;
    case WS_EX_NOACTIVATE:
        result.append("WS_EX_NOACTIVATE");
        break;
    case WS_EX_MDICHILD:
        result.append("WS_EX_MDICHILD");
        break;
    case WS_EX_NOINHERITLAYOUT:
        result.append("WS_EX_NOINHERITLAYOUT");
        break;
    case WS_EX_NOPARENTNOTIFY:
        result.append("WS_EX_NOPARENTNOTIFY");
        break;
    case WS_EX_NOREDIRECTIONBITMAP:
        result.append("WS_EX_NOREDIRECTIONBITMAP");
        break;
    case WS_EX_OVERLAPPEDWINDOW:
        result.append("WS_EX_OVERLAPPEDWINDOW");
        break;
    case WS_EX_PALETTEWINDOW:
        result.append("WS_EX_PALETTEWINDOW");
        break;
    case WS_EX_RIGHT:
        result.append("WS_EX_RIGHT");
        break;
    case WS_EX_STATICEDGE:
        result.append("WS_EX_STATICEDGE");
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
    return result.size() ? result : std::string("WS_EX_UNKNOWN");
}

std::vector<LONG> hmc_windows_util::getWinwowClassListEx(HWND hwnd)
{
    std::vector<LONG> result;

    LONG style = ::GetWindowLong(hwnd, GWL_EXSTYLE);

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

    return result;
}

std::vector<std::string> hmc_windows_util::getWinwowClassLongNameListEx(HWND hwnd)
{
    std::vector<std::string> result;

    LONG style = ::GetWindowLong(hwnd, GWL_EXSTYLE);

    // 窗口接受拖放文件。
    HMC_PUSH_WSRES_STR_EX(WS_EX_ACCEPTFILES);

    HMC_PUSH_WSRES_STR_EX(WS_EX_APPWINDOW);
    HMC_PUSH_WSRES_STR_EX(WS_EX_CLIENTEDGE);
    HMC_PUSH_WSRES_STR_EX(WS_EX_COMPOSITED);
    HMC_PUSH_WSRES_STR_EX(WS_EX_CONTEXTHELP);
    HMC_PUSH_WSRES_STR_EX(WS_EX_CONTROLPARENT);
    HMC_PUSH_WSRES_STR_EX(WS_EX_DLGMODALFRAME);
    HMC_PUSH_WSRES_STR_EX(WS_EX_LAYERED);
    HMC_PUSH_WSRES_STR_EX(WS_EX_LAYOUTRTL);
    HMC_PUSH_WSRES_STR_EX(WS_EX_LEFT);
    HMC_PUSH_WSRES_STR_EX(WS_EX_LEFTSCROLLBAR);
    HMC_PUSH_WSRES_STR_EX(WS_EX_LTRREADING);
    HMC_PUSH_WSRES_STR_EX(WS_EX_MDICHILD);
    HMC_PUSH_WSRES_STR_EX(WS_EX_NOACTIVATE);
    HMC_PUSH_WSRES_STR_EX(WS_EX_NOINHERITLAYOUT);
    HMC_PUSH_WSRES_STR_EX(WS_EX_NOPARENTNOTIFY);
    HMC_PUSH_WSRES_STR_EX(WS_EX_NOREDIRECTIONBITMAP);
    HMC_PUSH_WSRES_STR_EX(WS_EX_OVERLAPPEDWINDOW);
    HMC_PUSH_WSRES_STR_EX(WS_EX_PALETTEWINDOW);
    HMC_PUSH_WSRES_STR_EX(WS_EX_RIGHT);
    HMC_PUSH_WSRES_STR_EX(WS_EX_RIGHTSCROLLBAR);
    HMC_PUSH_WSRES_STR_EX(WS_EX_RTLREADING);
    HMC_PUSH_WSRES_STR_EX(WS_EX_STATICEDGE);
    HMC_PUSH_WSRES_STR_EX(WS_EX_TOOLWINDOW);
    HMC_PUSH_WSRES_STR_EX(WS_EX_TOPMOST);
    HMC_PUSH_WSRES_STR_EX(WS_EX_TRANSPARENT);
    HMC_PUSH_WSRES_STR_EX(WS_EX_WINDOWEDGE);

    return result;
}

std::vector<std::string> hmc_windows_util::getWinwowClassLongNameList(HWND hwnd)
{
    std::vector<std::string> result;

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

    return result;
}

bool hmc_windows_util::isMaximize(HWND hwnd)
{
    return ::IsZoomed(hwnd);
}

bool hmc_windows_util::isMinimized(HWND hwnd)
{
    return ::IsIconic(hwnd);
}

bool hmc_windows_util::isFullScreen(HWND hwnd)
{
    bool result = false;

    // 获取窗口工作区的大小
    RECT rect = {0, 0, 0, 0};
    ::GetClientRect(hwnd, &rect);

    // 获取屏幕分辨率
    int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

    // 检查窗口工作区大小是否与屏幕分辨率相同
    if (rect.right == screenWidth && rect.bottom == screenHeight)
    {
        return true;
    }
    return result;
}

bool hmc_windows_util::isNormal(HWND hwnd)
{
    return ::IsWindow(hwnd) && ::IsZoomed(hwnd) && ::IsIconic(hwnd) && isFullScreen(hwnd);
}

HWND hmc_windows_util::getFocusWindow()
{
    return ::GetForegroundWindow();
}

bool hmc_windows_util::isFocused(HWND hwnd)
{
    return (long long)::GetForegroundWindow() == (long long)hwnd;
}

bool hmc_windows_util::setNotVisibleWindow(HWND hwnd)
{
    bool result = false;

    if (!hmc_windows_util::isWindow(hwnd))
    {
        return result;
    }
    hmc_windows_util::setWindowTransparent(hwnd, 0);
    hmc_windows_util::setWindowInTaskbarVisible(hwnd, false);
    hmc_windows_util::setWindowEnabled(hwnd, true);
    hmc_windows_util::setMoveWindow(hwnd, 999999, 99999999, std::nullopt, std::nullopt);
    hmc_windows_util::setWindowTop(hwnd, true);

    return true;
}

bool hmc_windows_util::isInside(long x1, long y1, long x2, long y2, long x, long y)
{
    return (x > x1 && x < x2 && y > y1 && y < y2) ? true : false;
}

bool hmc_windows_util::isInside(RECT rect, long x, long y)
{
    return HMC_IS_INSIDE(rect.left, rect.top, rect.right, rect.bottom, x, y);
}

bool hmc_windows_util::isInside(long x1, long y1, long x2, long y2, POINT point)
{
    return HMC_IS_INSIDE(x1, y1, x2, y2, point.x, point.y);
}

bool hmc_windows_util::isInside(RECT rect, POINT point)
{
    return HMC_IS_INSIDE(rect.left, rect.top, rect.right, rect.bottom, point.x, point.y);
}

std::variant<std::vector<RECT>, DWORD> hmc_windows_util::getDeviceCapsAll()
{
    std::vector<RECT> CrectList;
    DISPLAY_DEVICE displayDevice;
    ::ZeroMemory(&displayDevice, sizeof(displayDevice));
    displayDevice.cb = sizeof(displayDevice);
    DEVMODE devMode;
    ::ZeroMemory(&devMode, sizeof(devMode));
    devMode.dmSize = sizeof(devMode);

    for (int i = 0; ::EnumDisplayDevices(NULL, i, &displayDevice, 0); ++i)
    {
        if (::EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
        {
            int left = devMode.dmPosition.x;
            int top = devMode.dmPosition.y;
            int right = devMode.dmPosition.x + devMode.dmPelsWidth;
            int bottom = devMode.dmPosition.y + devMode.dmPelsHeight;
            RECT rect;
            rect.bottom = bottom;
            rect.left = left;
            rect.top = top;
            rect.right = right;
            CrectList.push_back(rect);
        }
    }

    if (CrectList.empty())
    {
        return ::GetLastError();
    }

    return CrectList;
}

std::variant<RECT, DWORD> hmc_windows_util::getWinwowPointDeviceCaps(HWND hwnd)
{
    RECT lpWindowRect = {0, 0, 0, 0};
    if (!GetWindowRect(hwnd, &lpWindowRect))
    {
        return ::GetLastError();
    }

    auto device_caps_list_v = getDeviceCapsAll();
    if (device_caps_list_v.index() == 1)
    {
        return std::get<DWORD>(device_caps_list_v);
    }

    std::vector<RECT> device_caps_list = std::get<std::vector<RECT>>(device_caps_list_v);

    size_t count = device_caps_list.size();
    for (size_t i = 0; i < count; i++)
    {
        auto device = device_caps_list.at(i);
        if (isInside(device, lpWindowRect.left, lpWindowRect.top))
        {
            return device;
        }
    }

    return (DWORD)0;
}

std::variant<bool, DWORD> hmc_windows_util::setWindowCenter(HWND hwnd)
{
    // 获取父窗口句柄，如果没有父窗口，则为 GetDesktopWindow()
    HWND hParent = ::GetAncestor(hwnd, GA_PARENT);
    if (hParent == nullptr)
    {
        hParent = ::GetDesktopWindow();
    }

    // 获取父窗口或屏幕的客户区域大小
    RECT rcParent;
    if (!::GetClientRect(hParent, &rcParent))
    {
        return ::GetLastError();
    }

    // 获取窗口大小
    RECT rcWindow;
    if (!::GetWindowRect(hwnd, &rcWindow))
    {
        return ::GetLastError();
    }

    int width = rcWindow.right - rcWindow.left;
    int height = rcWindow.bottom - rcWindow.top;

    // 计算居中位置
    int x = (rcParent.right + rcParent.left - width) / 2;
    int y = (rcParent.bottom + rcParent.top - height) / 2;

    // 设置窗口位置

    if (!::SetWindowPos(hwnd, nullptr, x, y, width, height, SWP_SHOWWINDOW | SWP_NOZORDER))
    {
        return ::GetLastError();
    };

    return true;
}

std::variant<RECT, DWORD> hmc_windows_util::getWindowRect(HWND hwnd)
{
    RECT lpRect = {0, 0, 0, 0};
    if (GetWindowRect(hwnd, &lpRect))
    {
        return lpRect;
    }

    return ::GetLastError();
}

std::variant<hmc_windows_util::chWindowHwndStatus, DWORD> hmc_windows_util::getWindowHwndStatus(HWND hwnd){
    chWindowHwndStatus status = chWindowHwndStatus();
    status.hwnd = hwnd;
    status.exists = ::IsWindow(hwnd);
    if (!status.exists) {
        return ::GetLastError();
    }

    // 获取父窗口
    status.parent = ::GetParent(hwnd);

    // 获取根窗口
    status.root = ::GetAncestor(hwnd, GA_ROOT);

    // 获取进程ID
    DWORD threadId = ::GetWindowThreadProcessId(hwnd, &status.pid);
    status.threadId = threadId;

    auto temp  = getSubWindows(hwnd);
    
    if (temp.index()==0) {
        status.sub = std::get<std::vector<HWND>>(temp);
    }

    // 获取相邻窗口
    status.next = ::GetNextWindow(hwnd, GW_HWNDNEXT);
    status.prev = ::GetNextWindow(hwnd, GW_HWNDPREV);
    status.end = ::GetNextWindow(hwnd, GW_HWNDLAST);
    status.owner = ::GetWindow(hwnd, GW_OWNER);
    status.firstChild = ::GetWindow(hwnd, GW_CHILD);
    status.firstBrother = ::GetWindow(hwnd, GW_HWNDFIRST);
    status.lastSibling = ::GetWindow(hwnd, GW_HWNDLAST);


    return status;
}
