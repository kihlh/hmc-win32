#include "./hmc_shell_util.h"
#include "./hmc_string_util.hpp"

// ?GetTaryIconList

std::vector<hmc_shell_util::GetTaryIconList::TaryIcon> hmc_shell_util::GetTaryIconList::getTrayList()
{
    std::vector<TaryIcon> result = {};

    // win11
    if (::FindWindowW(L"TopLevelWindowForOverflowXamlIsland", NULL))
    {
        return result;
    }

    std::vector<HWND> hWndList = {GetSystemTrayHwnd(), GetNotifyOverflowTryHwnd()};

    for (size_t i = 0; i < hWndList.size(); i++)
    {
        HWND hwnd = hWndList[i];

        if (hwnd == NULL)
            continue;

        auto list = EnumCommctrlList(hwnd);

        for (size_t i = 0; i < list.size(); i++)
        {
            result.push_back(list[i]);
        }
    }

    return result;
}

std::wstring hmc_shell_util::GetTaryIconList::getTrayListJsonW()
{
    std::wstring result = L"[";
    result.reserve(2);

    auto data_list = getTrayList();

    if (data_list.empty())
    {
        result.push_back(']');
        return result;
    }

    result.reserve(4096);

    for (size_t i = 0; i < data_list.size(); i++)
    {
        auto data = data_list[i];
        std::wstring obj = LR"({ "info":"{info}","path":"{path}","handle":{handle} })";
        obj.reserve(54 + MAX_PATH * 2);

        obj.replace(obj.find(L"{info}"), sizeof("{info}") - 1, hmc_string_util::escapeJsonString(data.title));
        obj.replace(obj.find(L"{path}"), sizeof("{path}") - 1, hmc_string_util::escapeJsonString(data.path));
        obj.replace(obj.find(L"{handle}"), sizeof("{handle}") - 1, std::to_wstring((long long)data.hwnd));

        if (i + 1 < result.size())
        {
            result.push_back(',');
        }

        result.append(obj);
    }

    result.push_back(']');

    return result;
}

BOOL hmc_shell_util::GetTaryIconList::IsSystemFor64bit()
{
    SYSTEM_INFO SystemInfo;
    ::GetNativeSystemInfo(&SystemInfo);
    if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 || SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        return TRUE;
    else
        return FALSE;
}

HWND hmc_shell_util::GetTaryIconList::GetNotifyOverflowTryHwnd()
{
    HWND hWnd = ::FindWindowW(L"NotifyIconOverflowWindow", NULL);

    if (hWnd != NULL)
    {
        hWnd = ::FindWindowExW(hWnd, NULL, L"ToolbarWindow32", NULL);
    }

    return hWnd;
}

HWND hmc_shell_util::GetTaryIconList::GetSystemTrayHwnd()
{
    HWND hWnd = ::FindWindowW(L"Shell_TrayWnd", NULL);
    if (hWnd)
    {
        hWnd = ::FindWindowExW(hWnd, NULL, L"TrayNotifyWnd", NULL);
        if (hWnd)
        {
            hWnd = ::FindWindowExW(hWnd, NULL, L"SysPager", NULL);
            if (hWnd)
                hWnd = ::FindWindowExW(hWnd, NULL, L"ToolbarWindow32", NULL);
        }
    }
    if (!hWnd)
        return NULL;
    return hWnd;
};

std::vector<hmc_shell_util::GetTaryIconList::TaryIcon> hmc_shell_util::GetTaryIconList::EnumCommctrlList(HWND hWnd)
{
    std::vector<TaryIcon> result = {};
    if (hWnd == NULL)
        return result;

    // 获取托盘进程ID
    DWORD dwProcessId = 0;
    ::GetWindowThreadProcessId(hWnd, &dwProcessId);
    if (dwProcessId == 0)
        return result;

    // 获取托盘进程句柄
    HANDLE hProcess = ::OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, dwProcessId);
    if (hProcess == NULL)
        return result;

    // 分配内存，用来接收 TBBUTTON 结构体
    LPVOID Pointer_Icon_Buttons = ::VirtualAllocEx(hProcess, 0, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    // gc
    std::shared_ptr<void> _shared_free_handle(nullptr, [&](void *)
                                              {
            if (Pointer_Icon_Buttons != NULL) {
                ::VirtualFreeEx(hProcess, Pointer_Icon_Buttons, 0, MEM_RELEASE);
            }
            if (hProcess != NULL) {
                ::CloseHandle(hProcess);
            } });

    if (Pointer_Icon_Buttons == NULL)
        return result;

    // 初始化
    BYTE Byte_Buffer_Pointer[1024] = {0};
    DWORD Index_Icon_Buttons = 0;
    HWND Main_HWND = NULL;

    long Index_Icon_Buttons_id = 0;
    int Index_data_Close_Set = 12;
    int Index_String_Close_Set = 18;

    // 判断 x64(64位和32位字数不一样)
    if (IsSystemFor64bit())
    {
        Index_data_Close_Set = Index_data_Close_Set + 4;
        Index_String_Close_Set = Index_String_Close_Set + 6;
    }

    // 获取托盘图标个数
    size_t Tray_Length = 0;
    Tray_Length = ::SendMessage(hWnd, _TB_BUTTONCOUNT, 0, 0);

    if (Tray_Length == 0)
        return result;

    // 遍历托盘
    for (size_t i = 0; i < Tray_Length; i++)
    {
        // 获取 TBBUTTON 结构
        if (!::SendMessage(hWnd, _TB_GETBUTTON, i, (LPARAM)Pointer_Icon_Buttons))
            break;

        // 获取 TBBUTTON.dwData
        if (!::ReadProcessMemory(hProcess, (LPVOID)((DWORD)Pointer_Icon_Buttons + Index_data_Close_Set), &Index_Icon_Buttons, 4, 0))
            break;

        // 解析文本
        if (Index_Icon_Buttons)
        {
            if (!::ReadProcessMemory(hProcess, (LPCVOID)Index_Icon_Buttons, Byte_Buffer_Pointer, 1024, 0))
                break;

            HWND icon_hwnd = (*((HWND *)Byte_Buffer_Pointer));

            if (icon_hwnd == NULL)
                continue;

            std::wstring path = (WCHAR *)Byte_Buffer_Pointer + Index_String_Close_Set;
            std::wstring title = (WCHAR *)Byte_Buffer_Pointer + Index_String_Close_Set + MAX_PATH;
            long index = Index_Icon_Buttons_id;

            result.push_back(TaryIcon(icon_hwnd, path, title, index));
        }

        Index_Icon_Buttons = 0;
    }

    return result;
}

// ? API  function

BOOL hmc_shell_util::isSystemFor64bit()
{
    SYSTEM_INFO SystemInfo;
    ::GetNativeSystemInfo(&SystemInfo);
    if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 || SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        return TRUE;
    else
        return FALSE;
}

int hmc_shell_util::trashFile(std::wstring FromPath, bool bRecycle, bool isShow)
{
    SHFILEOPSTRUCTW FileOp = {0};
    if (bRecycle)
    {
        if (isShow)
        {
            FileOp.fFlags |= FOF_ALLOWUNDO;
        }
        else
        {
            FileOp.fFlags |= FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT;
        }
    }
    FileOp.pFrom = FromPath.c_str();
    FileOp.pTo = NULL;        // 一定要是NULL
    FileOp.wFunc = FO_DELETE; // 删除操作
    return ::SHFileOperationW(&FileOp);
}

namespace hmc_shell_util
{

    bool hmc_shell_util::clearTrash(HWND hwnd = NULL, std::wstring RootPath = L"", DWORD dwFlags = SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND)
    {
        return S_OK == ::SHEmptyRecycleBinW(hwnd, RootPath.empty() ? NULL : RootPath.c_str(), dwFlags);
    }

    bool setConversionStatus(HWND hwnd = NULL, DWORD sentencePatterns = IME_CMODE_ALPHANUMERIC, DWORD conversionModeValue = IME_SMODE_AUTOMATIC)
    {
        auto is_ok = false;

        // 获取输入法上下文
        HIMC hImc = ImmGetContext(hwnd);

        if (hImc == nullptr)
        {
            return false;
        }

        is_ok = ::ImmSetConversionStatus(hImc, sentencePatterns, conversionModeValue) != 0;

        if (is_ok)
        {
            is_ok = ::ImmReleaseContext(hwnd, hImc) != 0;
        }

        return is_ok;
    }

    bool hmc_shell_util::setShortcutLink(std::wstring lnkPath, std::wstring FilePath, std::wstring work_dir = L"", std::wstring desc = L"", std::wstring args = L"", DWORD iShowCmd = 0, std::wstring icon = L"", DWORD iconIndex = 0)
    {

        bool result = false;

        HRESULT hRes = CoInitialize(NULL);
        if (!SUCCEEDED(hRes))
        {
            return result;
        }

        IShellLinkW *pIShellLink;
        hRes = ::CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&pIShellLink);
        if (!SUCCEEDED(hRes))
        {
            return result;
        }
        hRes = pIShellLink->SetPath(FilePath.c_str());
        if (!SUCCEEDED(hRes))
        {
            return result;
        }
        hRes = pIShellLink->SetDescription(desc.c_str());
        if (!SUCCEEDED(hRes))
        {
            return result;
        }
        hRes = pIShellLink->SetWorkingDirectory(work_dir.c_str());
        if (!SUCCEEDED(hRes))
        {
            return result;
        }
        hRes = pIShellLink->SetArguments(args.c_str());
        if (!SUCCEEDED(hRes))
        {
            return result;
        }

        hRes = pIShellLink->SetShowCmd(iShowCmd);
        if (!SUCCEEDED(hRes))
        {
            return result;
        }

        hRes = pIShellLink->SetIconLocation(icon.c_str(), iconIndex);
        if (!SUCCEEDED(hRes))
        {
            return result;
        }
        IPersistFile *pIPersistFile;
        hRes = pIShellLink->QueryInterface(IID_IPersistFile, (void **)&pIPersistFile);
        if (!SUCCEEDED(hRes))
        {

            return result;
        }

        hRes = pIPersistFile->Save(lnkPath.c_str(), FALSE);
        if (!SUCCEEDED(hRes))
        {

            return result;
        }

        pIPersistFile->Release();
        pIShellLink->Release();

        result = true;

        return result;
    }

}

int hmc_shell_util::ShellOpen::showItemInFolder(std::wstring Path, bool isSelect)
{
    std::wstring explor_cmd = L"/select, ";

    explor_cmd.reserve(Path.size() + 15);

    if (!isSelect)
    {
        explor_cmd.clear();
    }

    explor_cmd.push_back('"');
    explor_cmd.append(Path.c_str());
    explor_cmd.push_back('"');

    HINSTANCE hResult = ShellExecuteW(NULL, L"open", L"explorer.exe", explor_cmd.c_str(), NULL, SW_SHOWNORMAL);

    return (int)(UINT_PTR)hResult;
}

int hmc_shell_util::ShellOpen::openUrl(std::wstring Url, bool isCurrentBrowser)
{
    int result = 0;

    if (!isCurrentBrowser)
    {
        HINSTANCE hResult = ShellExecuteW(NULL, L"open", Url.c_str(), NULL, NULL, SW_SHOWNORMAL);
        result = (int)(UINT_PTR)hResult;
    }

    return result;
}

int hmc_shell_util::ShellOpen::openApp(std::wstring AppPath, std::wstring Command, std::wstring cwd, bool isHide, bool isAdmin)
{
    const LPCWSTR flag = isAdmin ? L"runas" : L"open";
    const int sw_command = isHide ? 0 : 5;

    HINSTANCE hResult = ShellExecuteW(
        // hwnd
        NULL,
        // lpOperation
        flag,
        // lpFile
        AppPath.c_str(),
        // lpParameters
        Command.empty() ? NULL : Command.c_str(),
        // lpDirectory
        cwd.empty() ? NULL : cwd.c_str(),
        // nShowCmd
        sw_command);

    return (int)(UINT_PTR)hResult;
}

bool hmc_shell_util::chShortcutLinkItem::isValid()
{
    return !path.empty();
}

hmc_shell_util::chShortcutLinkItem::chShortcutLinkItem()
{
    // 目标路径
    path = L"";
    // 启动属性
    showCmd = 0;
    // 启动命令
    args = L"";
    // 描述
    desc = L"";
    // 进程图标(例如来自1.dll)
    icon = L"";
    // 图标索引位置
    iconIndex = 0;
    // 工作环境文件夹
    cwd = L"";
    // hotkey
    hotkey = 0;
}

hmc_shell_util::chShortcutLinkItem hmc_shell_util::getShortcutLink(std::wstring lnkPath)
{
    auto lnkItem = chShortcutLinkItem();

    IShellLinkW *GetShellLinkContent = NULL;

    auto temp_coinit = ::CoInitialize(0);

    LPWSTR temp_GetPathString = new wchar_t[MAX_PATH + 1];
    LPWSTR temp_GetArgumentsString = new wchar_t[MAX_PATH + 1];
    int temp_GetShowCmdNum = 0;
    LPWSTR temp_GetGetIconLocationString = new wchar_t[MAX_PATH + 1];
    int piIcon = 0;
    LPWSTR temp_GetGetDescriptionString = new wchar_t[MAX_PATH + 1];
    LPWSTR temp_GetWorkingDirectoryString = new wchar_t[MAX_PATH + 1];
    WORD pwHotkey = 0;

    HRESULT CreateHRESULT = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *)&GetShellLinkContent);
    DWORD dwReserved = 0;

    if (SUCCEEDED(CreateHRESULT))
    {
        IPersistFile *PersistFile;
        CreateHRESULT = GetShellLinkContent->QueryInterface(IID_IPersistFile, (LPVOID *)&PersistFile);
        if (SUCCEEDED(CreateHRESULT))
        {
            CreateHRESULT = PersistFile->Load(lnkPath.c_str(), STGM_READ);

            if (SUCCEEDED(CreateHRESULT))
            {
                WIN32_FIND_DATAW wfd = WIN32_FIND_DATAW();

                GetShellLinkContent->GetPath(temp_GetPathString, MAX_PATH, &wfd, SLGP_UNCPRIORITY | SLGP_RAWPATH);

                GetShellLinkContent->GetShowCmd(&temp_GetShowCmdNum);
                GetShellLinkContent->GetArguments(temp_GetArgumentsString, MAX_PATH);
                GetShellLinkContent->GetDescription(temp_GetGetDescriptionString, MAX_PATH);
                GetShellLinkContent->GetIconLocation(temp_GetGetIconLocationString, MAX_PATH, &piIcon);
                GetShellLinkContent->GetWorkingDirectory(temp_GetWorkingDirectoryString, MAX_PATH);
                GetShellLinkContent->GetHotkey(&pwHotkey);
            }
        }
    }

    if (GetShellLinkContent != NULL)
    {
        GetShellLinkContent->Release();
    }

    CreateHRESULT = NULL;

    lnkItem.args.append(temp_GetArgumentsString);
    lnkItem.cwd.append(temp_GetWorkingDirectoryString);
    lnkItem.desc.append(temp_GetGetDescriptionString);
    lnkItem.path.append(temp_GetPathString);
    lnkItem.icon.append(temp_GetGetIconLocationString);

    lnkItem.hotkey = pwHotkey;
    lnkItem.iconIndex = piIcon;
    lnkItem.showCmd = temp_GetShowCmdNum;

    if (CreateHRESULT > 0)
    {

        ::CoUninitialize();
    }

    return lnkItem;
}

bool hmc_shell_util::showContextMenu(HWND hwnd, std::wstring filePath, int x, int y)
{

    auto temp_coinit = ::CoInitialize(NULL);

    IShellItem *pItem;
    HRESULT hr = SHCreateItemFromParsingName(filePath.c_str(), NULL, IID_PPV_ARGS(&pItem));
    if (FAILED(hr))
    {
        return false;
    }

    IContextMenu *pContextMenu;
    hr = pItem->BindToHandler(NULL, BHID_SFUIObject, IID_PPV_ARGS(&pContextMenu));
    if (FAILED(hr))
    {
        pItem->Release();
        return false;
    }

    HMENU hMenu = ::CreatePopupMenu();
    if (hMenu == NULL)
    {
        pContextMenu->Release();
        pItem->Release();
        return false;
    }

    hr = pContextMenu->QueryContextMenu(hMenu, 0, 1, 0x7FFF, CMF_NORMAL);

    if (FAILED(hr))
    {
        ::DestroyMenu(hMenu);
        pContextMenu->Release();
        pItem->Release();
        return false;
    }

    if (!::IsWindow(hwnd))
    {
        return false;
    }

    int command = ::TrackPopupMenuEx(hMenu, TPM_RETURNCMD | TPM_NONOTIFY, x, y, hwnd, NULL);
    if (command > 0)
    {
        CMINVOKECOMMANDINFOEX info = {0};
        info.cbSize = sizeof(info);
        info.hwnd = hwnd;
        info.lpVerb = MAKEINTRESOURCEA(command - 1);
        info.nShow = SW_NORMAL;
        pContextMenu->InvokeCommand((LPCMINVOKECOMMANDINFO)&info);
    }

    // 释放资源
    ::DestroyMenu(hMenu);
    pContextMenu->Release();
    pItem->Release();

    if (temp_coinit > 0)
    {
        ::CoUninitialize();
    }

    return true;
}

bool hmc_shell_util::setShortcutLink(std::wstring lnkPath, chShortcutLinkItem shortcutLinkItem)
{
    if (!shortcutLinkItem.isValid())
    {
        return false;
    }

    std::wstring FilePath = shortcutLinkItem.path;
    std::wstring work_dir = shortcutLinkItem.cwd;
    std::wstring desc = shortcutLinkItem.desc;
    std::wstring args = shortcutLinkItem.args;
    int64_t iShowCmd = shortcutLinkItem.showCmd;
    std::wstring icon = shortcutLinkItem.icon;
    int64_t iconIndex = shortcutLinkItem.iconIndex;

    return setShortcutLink(lnkPath, FilePath, work_dir, desc, args, iShowCmd, icon, iconIndex);
}

#ifndef MODE_INTERNAL_INCLUDE_HMC_WINDOWS_V2_HPP
namespace hmc_windows_util
{
    bool isDesktopWindow(HWND hwnd)
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

}
#endif // MODE_INTERNAL_INCLUDE_HMC_WINDOWS_V2_HPP

/**
 * @brief 判断是否存在尺寸铺满整个屏幕的软件
 *
 * @return true
 * @return false
 */
bool hmc_shell_util::isFocusWindowFullScreen()
{
    // 全屏应用必定是一个前台窗口
    HWND focusWindow = ::GetForegroundWindow();

    if (focusWindow == NULL)
    {
        return false;
    }

    // 获取活动窗口的位置信息
    RECT windowRect = {0};
    ::GetWindowRect(focusWindow, &windowRect);

    // 获取包含活动窗口的显示器句柄
    HMONITOR monitor = ::MonitorFromWindow(focusWindow, MONITOR_DEFAULTTONEAREST);

    // 获取主显示信息
    MONITORINFO monitorInfo = {sizeof(MONITORINFO)};
    ::GetMonitorInfo(monitor, &monitorInfo);

    // 获取屏幕的尺寸
    int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

    if (windowRect.left <= 0 && windowRect.top <= 0 &&
        windowRect.right >= screenWidth && windowRect.bottom >= screenHeight &&
        monitorInfo.rcMonitor.left == 0 && monitorInfo.rcMonitor.top == 0 &&
        monitorInfo.rcMonitor.right == screenWidth && monitorInfo.rcMonitor.bottom == screenHeight)
    {
        return !hmc_windows_util::isDesktopWindow(focusWindow);
    }

    return false;
}

bool hmc_shell_util::isFullScreen()
{
    bool result = false;

    QUERY_USER_NOTIFICATION_STATE state;
    HRESULT hr = ::SHQueryUserNotificationState(&state);
    if (hr != S_OK)
        return false;

    switch (state)
    {

    // 全屏应用程序 第三方桌面可能也会导致识别错误
    case QUNS_BUSY:
        return isFocusWindowFullScreen();
    // Direct3D 应用程序正在运行) 全屏 (独占模式。
    case QUNS_RUNNING_D3D_FULL_SCREEN:
    // 用户已激活 Windows 演示文稿设置以阻止通知和弹出消息。
    case QUNS_PRESENTATION_MODE:
        return true;

    // 显示屏幕保护程序、锁定计算机或正在进行非活动快速用户切换会话。
    case QUNS_NOT_PRESENT:
    // 找不到其他状态，可以自由发送通知。
    case QUNS_ACCEPTS_NOTIFICATIONS:
    //  当前用户处于“静默时间”，这是新用户首次登录到其帐户后的第一小时
    case QUNS_QUIET_TIME:
    // Windows 应用商店应用正在运行
    case QUNS_APP:
        return false;
    };

    return false;
}
