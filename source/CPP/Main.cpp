#include "./Mian.hpp";

#include "./module/hmc_string_util.h"
#include "./module/hmc_napi_value_util.h"
#include "./shell_v2.h"
#include "./module/hmc_automation_util.h"
#include "./module/hmc_windows_util.h"
#include "./module/hmc_shell_util.h"
#include "./registr_v2.hpp"

bool _________HMC___________;

using namespace std;
#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))
#define HMC_CHECK_CATCH catch (char *err){};
#define HMC_THREAD (code) std::thread([]() -> void { code }).detach();
#define HMC_VirtualAlloc(Type, leng) (Type) VirtualAlloc((LPVOID)NULL, (DWORD)(leng), MEM_COMMIT, PAGE_READWRITE);
#define HMC_VirtualFree(Virtua) \
    if (Virtua != NULL)         \
        VirtualFree(Virtua, 0, MEM_RELEASE);
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

void ____HMC__RUN_MESS____(napi_env env, string error_message)
{
    if (_________HMC___________)
    {
        napi_value run_script_result;
        string error_message_str = string("console.error(new Error(String.raw`\n");
        error_message_str.append(error_message);
        error_message_str.append("`))");
        napi_run_script(env, as_String(error_message_str), &run_script_result);
    }
}

// 系统空闲时间
napi_value getSystemIdleTime(napi_env env, napi_callback_info info)
{
    napi_value sum;
    LASTINPUTINFO lpi;
    lpi.cbSize = sizeof(lpi);
    GetLastInputInfo(&lpi);
    int64_t SystemIdleTime = ((GetTickCount64() - lpi.dwTime) / 1000);
    napi_create_int64(env, SystemIdleTime, &sum);
    return sum;
}

static napi_value systemStartTime(napi_env env, napi_callback_info info)
{
    // napi_status status;
    napi_value Results;
    if (_WIN32_WINNT >= 0x0600)
    {
        napi_create_int64(env, (uint64_t)GetTickCount64(), &Results);
    }
    else
    {
        napi_create_int32(env, (uint32_t)GetTickCount(), &Results);
    }
    return Results;
}

// 进程阻塞
static napi_value sleep(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);

    if (argc < 1)
    {
        napi_throw_type_error(env, NULL, "Wrong length of arguments");
        return NULL;
    }

    napi_valuetype valuetype0;
    status = napi_typeof(env, args[0], &valuetype0);
    assert(status == napi_ok);

    if (valuetype0 != napi_number)
    {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return NULL;
    }

    int Set_time;
    status = napi_get_value_int32(env, args[0], &Set_time);
    assert(status == napi_ok);
    napi_value Sleep_info;
    Sleep(Set_time);
    status = napi_get_boolean(env, true, &Sleep_info);
    assert(status == napi_ok);

    return Sleep_info;
}

// 判断是否是管理员权限
napi_value isAdmin(napi_env env, napi_callback_info info)
{
    napi_value info_isAdmin;
    napi_get_boolean(env, IsUserAnAdmin(), &info_isAdmin);
    return info_isAdmin;
}

// 权限提升
BOOL EnableShutDownPriv()
{
    HANDLE Handle_Token = NULL;
    TOKEN_PRIVILEGES PermissionAttribute = {0};
    // 打开当前程序的权限令牌
    bool is_Open_Process_Token = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &Handle_Token);
    if (!is_Open_Process_Token)
    {
        return FALSE;
    }
    // 获得某一特定权限的权限标识LUID 保存到权限属性中
    if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &PermissionAttribute.Privileges[0].Luid))
    {
        CloseHandle(Handle_Token);
        return FALSE;
    }
    PermissionAttribute.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    PermissionAttribute.PrivilegeCount = 1;
    // 提升到系统权限
    if (!AdjustTokenPrivileges(Handle_Token, FALSE, &PermissionAttribute, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
    {
        CloseHandle(Handle_Token);
        return FALSE;
    }
    return TRUE;
}
// 执行注销，关机，重启
BOOL ReSetWindows(DWORD dwReason, BOOL aims)
{
    if (dwReason != EWX_LOGOFF && dwReason != EWX_REBOOT && dwReason != EWX_SHUTDOWN)
        return FALSE;
    OSVERSIONINFO osvi = {0};
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    dwReason |= (aims != FALSE) ? EWX_FORCE : EWX_FORCEIFHUNG;
    return ExitWindowsEx(dwReason, 0);
}
// 执行注销，关机，重启，锁定
static napi_value powerControl(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);

    if (argc < 1)
    {
        napi_throw_type_error(env, NULL, "Wrong length of arguments");
        return NULL;
    }

    napi_valuetype valuetype0;
    status = napi_typeof(env, args[0], &valuetype0);
    assert(status == napi_ok);

    if (valuetype0 != napi_number)
    {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return NULL;
    }
    if (!EnableShutDownPriv())
    {
        napi_throw_type_error(env, NULL, "Unable to elevate to system privileges");
    }

    int Flage;
    status = napi_get_value_int32(env, args[0], &Flage);
    assert(status == napi_ok);
    bool is_Success = FALSE;
    napi_value napi_info_bool;
    switch (Flage)
    {
    case 1001: // 关机
        is_Success = ReSetWindows(EWX_SHUTDOWN, true);
        break;
    case 1002: // 重启
        is_Success = ReSetWindows(EWX_REBOOT, true);
        break;
    case 1003: // 注销
        is_Success = ReSetWindows(EWX_LOGOFF, false);
        break;
    case 1005: // 锁定
        is_Success = LockWorkStation();
        break;
    }
    status = napi_get_boolean(env, is_Success, &napi_info_bool);
    assert(status == napi_ok);
    return napi_info_bool;
}

// 获取前台活动窗口句柄
napi_value getForegroundWindow(napi_env env, napi_callback_info info)
{
    napi_value napi_value_info;
    HWND _ActiveWindow = GetForegroundWindow();
    int64_t nWnd = (int64_t)_ActiveWindow;
    napi_create_int64(env, nWnd, &napi_value_info);
    return napi_value_info;
}

// 关闭显示器
napi_value shutMonitors(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value napi_value_info;
    status = napi_get_boolean(env, true, &napi_value_info);
    assert(status == napi_ok);
    EnableShutDownPriv();
    SendMessage(FindWindow(0, 0), WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    return napi_value_info;
}
// 打开显示器
napi_value showMonitors(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value napi_value_info;
    status = napi_get_boolean(env, true, &napi_value_info);
    assert(status == napi_ok);
    EnableShutDownPriv();
    SendMessage(FindWindow(0, 0), WM_SYSCOMMAND, SC_MONITORPOWER, -1);
    return napi_value_info;
}

// 设置窗口的系统右键(不考虑参数正确性 在js中会定义类型安全)
static napi_value getSystemMenu(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);

    if (argc < 2)
    {
        napi_throw_type_error(env, NULL, "Wrong length of arguments");
        return as_Boolean(FALSE);
    }

    napi_valuetype valuetype1;
    status = napi_typeof(env, args[1], &valuetype1);
    assert(status == napi_ok);
    napi_valuetype valuetype0;
    status = napi_typeof(env, args[0], &valuetype0);
    assert(status == napi_ok);
    if (valuetype0 != napi_number || valuetype1 != napi_boolean)
    {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return as_Boolean(FALSE);
    }

    bool bRevert;
    status = napi_get_value_bool(env, args[1], &bRevert);
    assert(status == napi_ok);
    int64_t LookHWND;
    status = napi_get_value_int64(env, args[0], &LookHWND);
    assert(status == napi_ok);
    HWND __HWND = (HWND)LookHWND;
    bool is_GetSystemMenu = GetSystemMenu(__HWND, bRevert);
    return as_Boolean(is_GetSystemMenu);
}

/**
 * @brief 显示窗口
 * @URL: https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-showwindow?redirectedfrom=MSDN
 * (不考虑参数正确性 在js中会定义类型安全)
 * @param env
 * @param info
 * @return napi_value
 */
static napi_value fn_ShowWindow(napi_env env, napi_callback_info info)
{
    napi_value ShowWindow_info;
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    if (argc)
    {
        size_t argc = 2;
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, NULL, NULL);
        int64_t Process_HWND;
        napi_get_value_int64(env, args[0], &Process_HWND);
        int _isShowWindow;
        napi_get_value_int32(env, args[1], &_isShowWindow);
        // 查找窗口  不存在则返回false
        HWND hWnd = (HWND)Process_HWND;
        bool isWindowShow = ShowWindow(hWnd, _isShowWindow);
        napi_get_boolean(env, isWindowShow, &ShowWindow_info);
    }
    return ShowWindow_info;
}

// 判断该句柄的窗口是否正在使用中(不考虑参数正确性 在js中会定义类型安全)
static napi_value fn_WindowVisible(napi_env env, napi_callback_info info)
{
    napi_value ShowWindow_info;
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, NULL, NULL);
        int64_t Process_HWND;
        napi_get_value_int64(env, args[0], &Process_HWND);

        HWND hWnd = (HWND)Process_HWND;
        bool isWindowShow = IsWindowVisible(hWnd);
        napi_get_boolean(env, isWindowShow, &ShowWindow_info);
    }
    return ShowWindow_info;
}
// 查找并关闭该窗口(不考虑参数正确性 在js中会定义类型安全)
static napi_value fn_CloseWindow(napi_env env, napi_callback_info info)
{
    napi_value CloseWindow_info;
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, NULL, NULL);
        int64_t Process_HWND;
        napi_get_value_int64(env, args[0], &Process_HWND);

        HWND hWnd = (HWND)Process_HWND;
        bool isWindowShow = CloseWindow(hWnd);
        napi_get_boolean(env, isWindowShow, &CloseWindow_info);
    }
    return CloseWindow_info;
}
// 获取句柄对应的窗口的标题(不考虑参数正确性 在js中会定义类型安全)
static napi_value fn_GetWindowTitle(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value HandleTitle;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    int64_t Process_Handle;
    status = napi_get_value_int64(env, args[0], &Process_Handle);
    HWND hWindow = (HWND)Process_Handle;
    LRESULT result = 0;
    wchar_t wszTitle[MAX_PATH] = {0};
    result = GetWindowTextW(hWindow, wszTitle, MAX_PATH);

    napi_create_string_utf16(env, (const char16_t *)wszTitle, NAPI_AUTO_LENGTH, &HandleTitle);
    return HandleTitle;
}
// 设置句柄对应的窗口的标题(不考虑参数正确性 在js中会定义类型安全)
static napi_value fn_SetWindowTitle(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value SetTitleInfo;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    int64_t Process_Handle;
    status = napi_get_value_int64(env, args[0], &Process_Handle);
    HWND hWindow = (HWND)Process_Handle;
    wstring _Title_ = hmc_napi_get_value::string_wide(env, args[1]);
    wstring To_U8_Title;
    To_U8_Title.append(_Title_.c_str());
    bool isWindowShow = SetWindowTextW(hWindow, (LPWSTR)_Title_.c_str());
    napi_get_boolean(env, isWindowShow, &SetTitleInfo);
    return SetTitleInfo;
}
UINT TextToUINT(string key)
{
    if (key == "MB_OK")
        return MB_OK;
    if (key == "MB_ABORTRETRYIGNORE")
        return MB_ABORTRETRYIGNORE;
    if (key == "MB_SERVICE_NOTIFICATION")
        return MB_SERVICE_NOTIFICATION;
    if (key == "MB_TOPMOST")
        return MB_TOPMOST;
    if (key == "MB_SETFOREGROUND")
        return MB_SETFOREGROUND;
    if (key == "MB_RTLREADING")
        return MB_RTLREADING;
    if (key == "MB_RIGHT")
        return MB_RIGHT;
    if (key == "MB_DEFAULT_DESKTOP_ONLY")
        return MB_DEFAULT_DESKTOP_ONLY;
    if (key == "MB_TASKMODAL")
        return MB_TASKMODAL;
    if (key == "MB_SYSTEMMODAL")
        return MB_SYSTEMMODAL;
    if (key == "MB_APPLMODAL")
        return MB_APPLMODAL;
    if (key == "MB_DEFBUTTON4")
        return MB_DEFBUTTON4;
    if (key == "MB_DEFBUTTON3")
        return MB_DEFBUTTON3;
    if (key == "MB_DEFBUTTON2")
        return MB_DEFBUTTON2;
    if (key == "MB_ICONHAND")
        return MB_ICONHAND;
    if (key == "MB_DEFBUTTON1")
        return MB_DEFBUTTON1;
    if (key == "MB_ICONERROR")
        return MB_ICONERROR;
    if (key == "MB_ICONSTOP")
        return MB_ICONSTOP;
    if (key == "MB_ICONQUESTION")
        return MB_ICONQUESTION;
    if (key == "MB_ICONASTERISK")
        return MB_ICONASTERISK;
    if (key == "MB_ICONINFORMATION")
        return MB_ICONINFORMATION;
    if (key == "MB_ICONWARNING")
        return MB_ICONWARNING;
    if (key == "MB_ICONEXCLAMATION")
        return MB_ICONEXCLAMATION;
    if (key == "MB_YESNOCANCEL")
        return MB_YESNOCANCEL;
    if (key == "MB_YESNO")
        return MB_YESNO;
    if (key == "MB_RETRYCANCEL")
        return MB_RETRYCANCEL;
    if (key == "MB_OKCANCEL")
        return MB_OKCANCEL;
    if (key == "MB_HELP")
        return MB_HELP;
    if (key == "MB_CANCELTRYCONTINUE")
        return MB_CANCELTRYCONTINUE;

    return MB_OK;
}
// 消息封装
static napi_value messageBox(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value MessageBoxInfo;
    size_t argc = 3;
    napi_value args[3];
    status = $napi_get_cb_info(argc, args);
    if (argc < 3)
    {
        napi_throw_type_error(env, NULL, "Wrong length of arguments =>" + argc);
        return NULL;
    }
    for (size_t i = 0; i < 3; i++)
    {
        napi_valuetype valuetype;
        status = napi_typeof(env, args[i], &valuetype);
        assert(status == napi_ok);
        if (valuetype != napi_string)
        {
            napi_throw_type_error(env, NULL, "Wrong Not napi_string arguments");
            return NULL;
        }
    }
    string lpText = hmc_napi_get_value::string_ansi(env, args[0]);
    string lpCaption = hmc_napi_get_value::string_ansi(env, args[1]);
    string TextUINT = hmc_napi_get_value::string_ansi(env, args[2]);
    int To_MessageBoxA = MessageBoxA(NULL, (LPCSTR)lpText.c_str(), (LPCSTR)lpCaption.c_str(), TextToUINT(TextUINT));
    napi_create_int32(env, To_MessageBoxA, &MessageBoxInfo);
    return MessageBoxInfo;
}
// 消息封装
static napi_value alert(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value MessageBoxInfo;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    if (argc < 2)
    {
        napi_throw_type_error(env, NULL, "Wrong length of arguments =>" + argc);
        return NULL;
    }
    for (size_t i = 0; i < 2; i++)
    {
        napi_valuetype valuetype;
        status = napi_typeof(env, args[i], &valuetype);
        assert(status == napi_ok);
        if (valuetype != napi_string)
        {
            napi_throw_type_error(env, NULL, "Wrong Not napi_string arguments");
            return NULL;
        }
    }
    string lpText = hmc_napi_get_value::string_ansi(env, args[0]);
    string lpCaption = hmc_napi_get_value::string_ansi(env, args[1]);
    int To_MessageBoxA = MessageBoxA(NULL, (LPCSTR)lpText.c_str(), (LPCSTR)lpCaption.c_str(), MB_OK);
    if (To_MessageBoxA == 1 || To_MessageBoxA == 6)
    {
        return as_Boolean(true);
    }
    else
    {
        return as_Boolean(false);
    }
}
static napi_value confirm(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value MessageBoxInfo;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    if (argc < 2)
    {
        napi_throw_type_error(env, NULL, "Wrong length of arguments =>" + argc);
        return NULL;
    }
    for (size_t i = 0; i < 2; i++)
    {
        napi_valuetype valuetype;
        status = napi_typeof(env, args[i], &valuetype);
        assert(status == napi_ok);
        if (valuetype != napi_string)
        {
            napi_throw_type_error(env, NULL, "Wrong Not napi_string arguments");
            return NULL;
        }
    }
    string lpText = hmc_napi_get_value::string_ansi(env, args[0]);
    string lpCaption = hmc_napi_get_value::string_ansi(env, args[1]);
    int To_MessageBoxA = MessageBoxA(NULL, (LPCSTR)lpText.c_str(), (LPCSTR)lpCaption.c_str(), MB_OKCANCEL);
    if (To_MessageBoxA == 1 || To_MessageBoxA == 6)
    {
        return as_Boolean(true);
    }
    else
    {
        return as_Boolean(false);
    }
}
static napi_value MessageStop(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value MessageBoxInfo;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    if (argc < 2)
    {
        napi_throw_type_error(env, NULL, "Wrong length of arguments =>" + argc);
        return NULL;
    }
    for (size_t i = 0; i < 2; i++)
    {
        napi_valuetype valuetype;
        status = napi_typeof(env, args[i], &valuetype);
        assert(status == napi_ok);
        if (valuetype != napi_string)
        {
            napi_throw_type_error(env, NULL, "Wrong Not napi_string arguments");
            return NULL;
        }
    }
    string lpText = hmc_napi_get_value::string_ansi(env, args[0]);
    string lpCaption = hmc_napi_get_value::string_ansi(env, args[1]);
    int To_MessageBoxA = MessageBoxA(NULL, (LPCSTR)lpText.c_str(), (LPCSTR)lpCaption.c_str(), MB_ICONERROR);
    return NULL;
}

static napi_value MessageError(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value MessageBoxInfo;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    if (argc < 2)
    {
        napi_throw_type_error(env, NULL, "Wrong length of arguments =>" + argc);
        return NULL;
    }
    for (size_t i = 0; i < 2; i++)
    {
        napi_valuetype valuetype;
        status = napi_typeof(env, args[i], &valuetype);
        assert(status == napi_ok);
        if (valuetype != napi_string)
        {
            napi_throw_type_error(env, NULL, "Wrong Not napi_string arguments");
            return NULL;
        }
    }
    string lpText = hmc_napi_get_value::string_ansi(env, args[0]);
    string lpCaption = hmc_napi_get_value::string_ansi(env, args[1]);
    int To_MessageBoxA = MessageBoxA(NULL, (LPCSTR)lpText.c_str(), (LPCSTR)lpCaption.c_str(), MB_ICONEXCLAMATION);
    return NULL;
}

HWND GetHwndByPid(DWORD dwProcessID)
{
    HWND Look_Get_Top_Window_HWND = GetTopWindow(0);
    HWND Info_HWND = NULL;
    while (Look_Get_Top_Window_HWND)
    {
        DWORD pid = 0;
        DWORD of_TheardId = GetWindowThreadProcessId(Look_Get_Top_Window_HWND, &pid);
        if (of_TheardId != 0)
        {
            if (pid == dwProcessID && GetParent(Look_Get_Top_Window_HWND) == NULL && ::IsWindowVisible(Look_Get_Top_Window_HWND))
                Info_HWND = Look_Get_Top_Window_HWND;
        }
        Look_Get_Top_Window_HWND = GetNextWindow(Look_Get_Top_Window_HWND, GW_HWNDNEXT);
    }
    return Info_HWND;
}
// 获取进程id对应的窗口句柄 (如果有)
static napi_value getProcessHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value ProcessHandle;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }

    int Process_PID;
    status = napi_get_value_int32(env, args[0], &Process_PID);

    HANDLE GetProcessHandle = GetHwndByPid((DWORD)Process_PID);
    if (GetProcessHandle == nullptr)
    {
        napi_get_null(env, &ProcessHandle);
        return ProcessHandle;
    }
    napi_create_int64(env, int64_t(GetProcessHandle), &ProcessHandle);

    return ProcessHandle;
}

// 判断是否是64位系统
napi_value isSystemX64(napi_env env, napi_callback_info info)
{
    napi_value info_isAdmin;
    napi_get_boolean(env, isSystemFor64bit(), &info_isAdmin);
    return info_isAdmin;
}

// 获取托盘图标
static napi_value getTrayList(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::String(env, GetTaryIconList::getTrayListJsonW());
}

// 设置句柄的不透明度
static napi_value setHandleTransparent(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    int64_t Process_Handle;
    status = napi_get_value_int64(env, args[0], &Process_Handle);
    int Set_Process_Handle_Alpha;
    status = napi_get_value_int32(env, args[1], &Set_Process_Handle_Alpha);
    HWND hWnd = (HWND)Process_Handle;
    BYTE _Alpha = (BYTE)Set_Process_Handle_Alpha;
    // 获取窗口的拓展属性
    LONG SetWindowsStyleEx = ::GetWindowLong(hWnd, GWL_EXSTYLE);
    // 在原来的拓展属性之上, 新增 WS_EX_LAYERED 拓展属性
    SetWindowsStyleEx = SetWindowsStyleEx | WS_EX_LAYERED;
    ::SetWindowLong(hWnd, GWL_EXSTYLE, SetWindowsStyleEx);
    // 设置窗口半透明度
    ::SetLayeredWindowAttributes(hWnd, NULL, _Alpha, LWA_ALPHA);
    return NULL;
}
// 获取快捷方式内容
static napi_value getShortcutLink(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    napi_value Results;
    napi_create_object(env, &Results);
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        if (argc < 1)
        {
            napi_throw_type_error(env, NULL, "Wrong length of arguments =>" + argc);
            return NULL;
        }
        napi_valuetype valuetype0;
        status = napi_typeof(env, args[0], &valuetype0);
        assert(status == napi_ok);
        if (valuetype0 != napi_string)
        {
            napi_throw_type_error(env, NULL, "Wrong Not napi_string arguments");
            return NULL;
        }
    }
    else
    {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return NULL;
    };
    // 图标路径
    wstring lnkPath = hmc_napi_get_value::string_utf16(env, args[0]);
    IShellLinkA *GetShellLinkContent;
    CoInitialize(0);
    char *tempGetPathString = new char[MAX_PATH];
    char *tempGetArgumentsString = new char[MAX_PATH];
    int tempGetShowCmdNum = 0;
    char *tempGetGetIconLocationString = new char[MAX_PATH];
    int piIcon = 0;
    char *tempGetGetDescriptionString = new char[MAX_PATH];
    char *tempGetWorkingDirectoryString = new char[MAX_PATH];
    WORD *pwHotkey = new WORD;
    string ss;
    HRESULT CreateHRESULT = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *)&GetShellLinkContent);
    DWORD dwReserved;
    if (SUCCEEDED(CreateHRESULT))
    {
        IPersistFile *PersistFile;
        CreateHRESULT = GetShellLinkContent->QueryInterface(IID_IPersistFile, (LPVOID *)&PersistFile);
        if (SUCCEEDED(CreateHRESULT))
        {
            CreateHRESULT = PersistFile->Load(lnkPath.c_str(), STGM_READ);

            if (SUCCEEDED(CreateHRESULT))
            {
                WIN32_FIND_DATAA wfd;
                GetShellLinkContent->GetPath(tempGetPathString, MAX_PATH, &wfd, SLGP_UNCPRIORITY | SLGP_RAWPATH);
                GetShellLinkContent->GetShowCmd(&tempGetShowCmdNum);
                GetShellLinkContent->GetArguments(tempGetArgumentsString, MAX_PATH);
                GetShellLinkContent->GetDescription(tempGetGetDescriptionString, MAX_PATH);
                GetShellLinkContent->GetIconLocation(tempGetGetIconLocationString, MAX_PATH, &piIcon);
                GetShellLinkContent->GetWorkingDirectory(tempGetWorkingDirectoryString, MAX_PATH);
                GetShellLinkContent->GetHotkey(pwHotkey);
            }
        }
        else
        {
            return Results;
        }
    }
    napi_set_property(env, Results, as_String("path"), as_StringA(tempGetPathString));
    napi_set_property(env, Results, as_String("showCmd"), as_Number32(tempGetShowCmdNum));
    napi_set_property(env, Results, as_String("args"), as_StringA(tempGetArgumentsString));
    napi_set_property(env, Results, as_String("desc"), as_StringA(tempGetGetDescriptionString));
    napi_set_property(env, Results, as_String("icon"), as_StringA(tempGetGetIconLocationString));
    napi_set_property(env, Results, as_String("iconIndex"), as_Number(piIcon));
    napi_set_property(env, Results, as_String("cwd"), as_StringA(tempGetWorkingDirectoryString));
    napi_set_property(env, Results, as_String("hotkey"), as_Number((int64_t)pwHotkey));

    return Results;
}
// 获取快捷方式内容
static napi_value setShortcutLink(napi_env env, napi_callback_info info)
{
    // napi_status status;
    // napi_value Results;
    // 最高只接受这么多参数(请注意如果没有传入这么多的数据而获取会照成内存溢出)
    const size_t M_Size = 8;
    size_t argc = M_Size;
    napi_value argv[M_Size];
    $napi_get_cb_info(argc, argv);
    string lnkPath;
    string path;
    string desc;
    string work_dir;
    string Arguments;
    string icon;
    int iShowCmd;
    int iconIndex;
    string defaultParameterSettings = "\n\nThe number of target parameters is => 2-8 \nfor:\nlnkPath:string,\npath:string,\nwork_dir?:string,\ndesc?:string,\nargs?:string,\niShowCmd?:number,\nicon?:string,\niconIndex?:number\n\n";
    if (argc == 0 || argc == 1)
    {
        string ErrorString = "Wrong length of arguments =>";
        ErrorString.append(to_string(argc).c_str());
        ErrorString.append(defaultParameterSettings);
        napi_throw_type_error(env, NULL, ErrorString.c_str());
        return NULL;
    }

    for (int i = 0; i < argc; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            if ((i == 7 || i == 5) && value_type == napi_number)
                break;
            string ErrorString = "Missing parameters";
            ErrorString.append(to_string(argc).c_str());
            ErrorString.append(defaultParameterSettings).append("\nTypeof parameter :\n");
            for (int i = 0; i < argc; i++)
            {
                napi_valuetype value_type;
                napi_typeof(env, argv[i], &value_type);
                ErrorString.append("\nargc[")
                    .append(to_string(i))
                    .append("]:");
                ErrorString.append(hmc_napi_type::typeName(value_type));
            }
            napi_throw_error(env, "EINVAL", ErrorString.c_str());
            return nullptr;
        };
    }
    // 遍历方法并进行定义(因为js是接受多种参数传入的)
    switch (argc)
    {
    case 2:
        lnkPath.append(hmc_napi_get_value::string_ansi(env, argv[0]).c_str());
        path.append(hmc_napi_get_value::string_ansi(env, argv[1]).c_str());
        break;
    case 3:
        lnkPath.append(hmc_napi_get_value::string_ansi(env, argv[0]).c_str());
        path.append(hmc_napi_get_value::string_ansi(env, argv[1]).c_str());
        work_dir.append(hmc_napi_get_value::string_ansi(env, argv[2]).c_str());
        break;
    case 4:
        lnkPath.append(hmc_napi_get_value::string_ansi(env, argv[0]).c_str());
        path.append(hmc_napi_get_value::string_ansi(env, argv[1]).c_str());
        work_dir.append(hmc_napi_get_value::string_ansi(env, argv[2]).c_str());
        desc.append(hmc_napi_get_value::string_ansi(env, argv[3]).c_str());
        break;
    case 5:
        lnkPath.append(hmc_napi_get_value::string_ansi(env, argv[0]).c_str());
        path.append(hmc_napi_get_value::string_ansi(env, argv[1]).c_str());
        work_dir.append(hmc_napi_get_value::string_ansi(env, argv[2]).c_str());
        desc.append(hmc_napi_get_value::string_ansi(env, argv[3]).c_str());
        Arguments.append(hmc_napi_get_value::string_ansi(env, argv[4]).c_str());
        break;
    case 6:
        lnkPath.append(hmc_napi_get_value::string_ansi(env, argv[0]).c_str());
        path.append(hmc_napi_get_value::string_ansi(env, argv[1]).c_str());
        work_dir.append(hmc_napi_get_value::string_ansi(env, argv[2]).c_str());
        desc.append(hmc_napi_get_value::string_ansi(env, argv[3]).c_str());
        Arguments.append(hmc_napi_get_value::string_ansi(env, argv[4]).c_str());
        napi_get_value_int32(env, argv[5], &iShowCmd);
        break;
    case 7:
        defaultParameterSettings.insert(0, "The iconIndex must be included when the parameter equals 7");
        napi_throw_type_error(env, NULL, defaultParameterSettings.c_str());
        break;
    case 8:
        lnkPath.append(hmc_napi_get_value::string_ansi(env, argv[0]).c_str());
        path.append(hmc_napi_get_value::string_ansi(env, argv[1]).c_str());
        work_dir.append(hmc_napi_get_value::string_ansi(env, argv[2]).c_str());
        desc.append(hmc_napi_get_value::string_ansi(env, argv[3]).c_str());
        Arguments.append(hmc_napi_get_value::string_ansi(env, argv[4]).c_str());
        napi_get_value_int32(env, argv[5], &iShowCmd);
        icon.append(hmc_napi_get_value::string_ansi(env, argv[6]).c_str());
        napi_get_value_int32(env, argv[7], &iconIndex);
        break;
    }
    HRESULT hRes = CoInitialize(NULL);
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ESRCH", "HRESULT->CoCreateInstance Failed to create");
        return nullptr;
    }
    IShellLinkA *pIShellLink;
    hRes = ::CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&pIShellLink);
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ESRCH", "HRESULT->CoCreateInstance Failed to create");
        return nullptr;
    }
    hRes = pIShellLink->SetPath((LPCSTR)path.c_str());
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ENOEXEC", "Error => SetPath");
        return nullptr;
    }
    hRes = pIShellLink->SetDescription((LPCSTR)desc.c_str());
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ENOEXEC", "Error => SetDescription");
        return nullptr;
    }
    hRes = pIShellLink->SetWorkingDirectory((LPCSTR)work_dir.c_str());
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ENOEXEC", "Error => SetWorkingDirectory");
        return nullptr;
    }
    hRes = pIShellLink->SetArguments((LPCSTR)Arguments.c_str());
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ENOEXEC", "Error => SetArguments");
        return nullptr;
    }
    hRes = pIShellLink->SetShowCmd(iShowCmd);
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ENOEXEC", "Error => SetArguments");
        return nullptr;
    }
    hRes = pIShellLink->SetShowCmd(iShowCmd);
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ENOEXEC", "Error => SetArguments");
        return nullptr;
    }
    hRes = pIShellLink->SetIconLocation((LPCSTR)icon.c_str(), iconIndex);
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ENOEXEC", "Error => SetArguments");
        return nullptr;
    }
    IPersistFile *pIPersistFile;
    hRes = pIShellLink->QueryInterface(IID_IPersistFile, (void **)&pIPersistFile);
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ENOEXEC", "Error => QueryInterface");
        return nullptr;
    }

    hRes = pIPersistFile->Save(hmc_string_util::ansi_to_utf16(lnkPath.c_str()).c_str(), FALSE);
    if (!SUCCEEDED(hRes))
    {
        napi_throw_error(env, "ENOEXEC", "Error => Save");
        return nullptr;
    }
    pIPersistFile->Release();
    pIShellLink->Release();
    return NULL;
}
// 获取句柄对应的pid
static napi_value getHandleProcessID(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    DWORD processId;
    GetWindowThreadProcessId((HWND)NumHandle, &processId);
    return as_Number((int64_t)processId);
}
// 获取活动窗口的pid
static napi_value getForegroundWindowProcessID(napi_env env, napi_callback_info info)
{
    DWORD processId;
    GetWindowThreadProcessId(GetForegroundWindow(), &processId);
    return as_Number((int64_t)processId);
}

// 获取鼠标位置
napi_value getMetrics(napi_env env, napi_callback_info info)
{
    POINT point;
    napi_value Results;
    napi_create_object(env, &Results);
    GetCursorPos(&point);
    int x = point.x; // 鼠标x轴
    int y = point.y; // 鼠标y轴
    napi_set_property(env, Results, as_String("x"), as_Number32(x));
    napi_set_property(env, Results, as_String("y"), as_Number32(y));
    napi_set_property(env, Results, as_String("left"), as_Number32(x));
    napi_set_property(env, Results, as_String("top"), as_Number32(y));
    return Results;
}
// 获取屏幕大小
napi_value getDeviceCaps(napi_env env, napi_callback_info info)
{
    napi_value Results;
    napi_create_object(env, &Results);
    int width = GetSystemMetrics(SM_CXSCREEN);  // 鼠标x轴
    int height = GetSystemMetrics(SM_CYSCREEN); // 鼠标y轴
    napi_set_property(env, Results, as_String("width"), as_Number32(width));
    napi_set_property(env, Results, as_String("height"), as_Number32(height));
    return Results;
}
// 获取鼠标位置窗口
napi_value getPointWindow(napi_env env, napi_callback_info info)
{
    POINT curPoint;
    if (!GetCursorPos(&curPoint))
        return as_Number(0);
    HWND mainWindow = WindowFromPoint(curPoint);
    return as_Number((int64_t)mainWindow);
}
// 获取鼠标位置窗口的名称
napi_value getPointWindowName(napi_env env, napi_callback_info info)
{
    POINT curPoint;
    if (!GetCursorPos(&curPoint))
        return as_Number(0);
    HWND mainWindow = WindowFromPoint(curPoint);
    DWORD processId;
    GetWindowThreadProcessId(mainWindow, &processId);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    wchar_t lpFilename[1024];
    if (hProcess == nullptr)
    {
        return as_String("");
    }
    GetModuleBaseNameW(hProcess, NULL, (LPWSTR)lpFilename, 1024);
    return as_String(lpFilename);
}

// 获取鼠标位置窗口的pid
napi_value getPointWindowProcessId(napi_env env, napi_callback_info info)
{
    POINT curPoint;
    if (!GetCursorPos(&curPoint))
        return as_Number(0);
    HWND mainWindow = WindowFromPoint(curPoint);
    DWORD processId;
    GetWindowThreadProcessId(mainWindow, &processId);
    return as_Number32((int64_t)processId);
}
napi_value getPointWindowMain(napi_env env, napi_callback_info info)
{
    napi_value ProcessHandle;
    POINT curPoint;
    if (!GetCursorPos(&curPoint))
        return as_Number(0);
    HWND mainWindow = WindowFromPoint(curPoint);
    DWORD processId;
    GetWindowThreadProcessId(mainWindow, &processId);
    HANDLE GetProcessHandle = GetHwndByPid((DWORD)processId);

    if (GetProcessHandle == nullptr)
    {
        napi_get_null(env, &ProcessHandle);
        return ProcessHandle;
    }

    napi_create_int64(env, int64_t(GetProcessHandle), &ProcessHandle);
    return ProcessHandle;
}
// 获取窗口位置大小信息
static napi_value getWindowRect(napi_env env, napi_callback_info info)
{
    napi_value Results;
    napi_create_object(env, &Results);
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    int64_t Process_Handle;
    status = napi_get_value_int64(env, args[0], &Process_Handle);
    napi_value DefaultValue = as_Number32(0);
    napi_set_property(env, Results, as_String("top"), DefaultValue);
    napi_set_property(env, Results, as_String("bottom"), DefaultValue);
    napi_set_property(env, Results, as_String("left"), DefaultValue);
    napi_set_property(env, Results, as_String("right"), DefaultValue);
    napi_set_property(env, Results, as_String("y"), DefaultValue);
    napi_set_property(env, Results, as_String("x"), DefaultValue);
    napi_set_property(env, Results, as_String("width"), DefaultValue);
    napi_set_property(env, Results, as_String("height"), DefaultValue);

    HWND hHWND = (HWND)Process_Handle;
    if (hHWND)
    {
        // 获取窗口原始大小
        RECT lpRect;
        GetWindowRect(hHWND, &lpRect);
        napi_set_property(env, Results, as_String("top"), as_Number32(lpRect.top));
        napi_set_property(env, Results, as_String("bottom"), as_Number32(lpRect.bottom));
        napi_set_property(env, Results, as_String("left"), as_Number32(lpRect.left));
        napi_set_property(env, Results, as_String("right"), as_Number32(lpRect.right));
        napi_set_property(env, Results, as_String("y"), as_Number32(lpRect.top));
        napi_set_property(env, Results, as_String("x"), as_Number32(lpRect.left));
        napi_set_property(env, Results, as_String("width"), as_Number32(lpRect.right - lpRect.left));
        napi_set_property(env, Results, as_String("height"), as_Number32(lpRect.top - lpRect.bottom));
    }
    return Results;
}
// 设置窗口大小
static napi_value setWindowMode(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 5;
    napi_value args[5];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        if (argc < 5)
        {
            napi_throw_type_error(env, NULL, "Wrong length of arguments =>" + argc);
            return as_Boolean(FALSE);
        }
        for (size_t i = 0; i < argc; i++)
        {
            napi_valuetype valuetype;
            status = napi_typeof(env, args[i], &valuetype);
            assert(status == napi_ok);
            if (valuetype != napi_number && valuetype != napi_null)
            {
                napi_throw_type_error(env, NULL, "Wrong Not napi_number arguments");
                return as_Boolean(FALSE);
            }
        }
    }
    else
    {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return as_Boolean(FALSE);
    };
    int64_t Process_HWND;
    napi_get_value_int64(env, args[0], &Process_HWND);

    int width;
    napi_get_value_int32(env, args[3], &width);
    int height;
    napi_get_value_int32(env, args[4], &height);
    // 获取窗口原始大小
    HWND hHWND = (HWND)Process_HWND;
    if (hHWND)
    {
        RECT rect;
        GetWindowRect(hHWND, &rect);
        int DeviceCapsWidth = GetSystemMetrics(SM_CXSCREEN);
        int DeviceCapsHeight = GetSystemMetrics(SM_CYSCREEN);
        int Env_height = (DeviceCapsHeight - rect.top) - (DeviceCapsHeight - rect.bottom);
        int Env_width = (DeviceCapsWidth - rect.left) - (DeviceCapsWidth - rect.right);

        // 重新设置窗口大小
        MoveWindow(hHWND,
                   //
                   hmc_napi_type::isNumber(env, args[0]) ? hmc_napi_get_value::number_int(env, args[0]) : NULL,
                   hmc_napi_type::isNumber(env, args[1]) ? hmc_napi_get_value::number_int(env, args[1]) : NULL,
                   width < 1 ? Env_width : width,
                   height < 1 ? Env_height : height,
                   // bRepaint
                   true);
        return as_Boolean(TRUE);
    }
    else
    {
        return as_Boolean(FALSE);
    }
}

// 结束句柄对应的窗口
static napi_value closedHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    HWND Handle = (HWND)NumHandle;
    SendMessage(Handle, WM_SYSCOMMAND, SC_CLOSE, 0);
    // 让win可以回收该句柄
    CloseHandle(Handle);
    return NULL;
}

// 设置/取消窗口顶设
static napi_value setWindowTop(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    HWND Handle = (HWND)NumHandle;
    RECT rect;
    if (!GetWindowRect(Handle, &rect))
        return as_Boolean(FALSE);
    if (GetWindowLong(Handle, GWL_EXSTYLE) & WS_EX_TOPMOST)
    {
        return as_Boolean(SetWindowPos(Handle, HWND_NOTOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW));
    }
    else
        return as_Boolean(SetWindowPos(Handle, HWND_TOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW));
}

// 判断是否窗口顶设
static napi_value hasWindowTop(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    HWND Handle = (HWND)NumHandle;
    return as_Boolean(GetWindowLong(Handle, GWL_EXSTYLE) & WS_EX_TOPMOST);
}

// 判断该句柄是否有效
static napi_value isHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    HWND Handle = (HWND)NumHandle;
    return as_Boolean(GetWindow(Handle, GW_OWNER) == (HWND)0 && IsWindowVisible(Handle));
}
// 获取子窗口的父窗口
static napi_value getMainWindow(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    HWND Handle = (HWND)NumHandle;
    return as_Number((int64_t)GetTopWindow(Handle));
}
// 判断该句柄是否有效
static napi_value isEnabled(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    HWND Handle = (HWND)NumHandle;
    return as_Boolean(IsWindowEnabled(Handle));
}
// 设置窗口禁用
static napi_value setWindowEnabled(napi_env env, napi_callback_info info)
{
    napi_status status;
    const size_t M_size = 2;
    size_t argc = M_size;
    napi_value args[M_size];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = M_size;
        napi_value args[M_size];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    HWND Handle = (HWND)NumHandle;
    bool is_WindowEnabledCommand;
    napi_get_value_bool(env, args[0], &is_WindowEnabledCommand);
    return as_Boolean(EnableWindow(Handle, is_WindowEnabledCommand));
}

// 窗口抖动
static napi_value windowJitter(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    hmc_windows_util::setWindowShake((HWND)NumHandle,6,6,60);
    return NULL;
}

// 设置窗口焦点
static napi_value setWindowFocus(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    HWND Handle = (HWND)NumHandle;
    return as_Boolean(SetFocus(Handle));
}

// 判断该句柄是否有效
static napi_value updateWindow(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    HWND Handle = (HWND)NumHandle;
    return as_Boolean(UpdateWindow(Handle));
}

// 获取所有窗口
static napi_value getAllWindows(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    status = napi_create_array(env, &Results);
    assert(status == napi_ok);
    // 获取桌面句柄
    HWND hwnd = GetDesktopWindow();
    // 获取桌面子窗口句柄
    hwnd = GetWindow(hwnd, GW_CHILD);
    int counter = 0;
    for (size_t index = 0; hwnd != NULL; index++)
    {
        DWORD dwStyle = GetClassLong(hwnd, GCL_STYLE);
        LPSTR lpClassName;
        RECT lpRect;
        // 获取窗口大小
        DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &lpRect, sizeof(RECT));
        // 获取窗口名
        CHAR windowTitle[MAX_PATH] = {0};
        GetWindowTextA(hwnd, windowTitle, MAX_PATH);
        GetClassNameA(hwnd, lpClassName, MAX_PATH);
        int DeviceCapsWidth = GetSystemMetrics(SM_CXSCREEN);
        int DeviceCapsHeight = GetSystemMetrics(SM_CYSCREEN);
        // 窗口位置
        napi_value coordinateInformation;
        status = napi_create_object(env, &coordinateInformation);
        assert(status == napi_ok);
        napi_set_property(env, coordinateInformation, as_String("top"), as_Number32(lpRect.top));
        napi_set_property(env, coordinateInformation, as_String("bottom"), as_Number32(lpRect.bottom));
        napi_set_property(env, coordinateInformation, as_String("left"), as_Number32(lpRect.left));
        napi_set_property(env, coordinateInformation, as_String("right"), as_Number32(lpRect.right));
        napi_set_property(env, coordinateInformation, as_String("y"), as_Number32(lpRect.top));
        napi_set_property(env, coordinateInformation, as_String("x"), as_Number32(lpRect.left));
        napi_set_property(env, coordinateInformation, as_String("width"), as_Number32((DeviceCapsWidth - lpRect.left) - (DeviceCapsWidth - lpRect.right)));
        napi_set_property(env, coordinateInformation, as_String("height"), as_Number32((DeviceCapsHeight - lpRect.top) - (DeviceCapsHeight - lpRect.bottom)));
        // {handle,rect:coordinateInformation,title}
        napi_value PushwindowContents;
        status = napi_create_object(env, &PushwindowContents);
        assert(status == napi_ok);
        // napi_set_property(env, PushwindowContents, as_String( "rect"), coordinateInformation);
        napi_set_property(env, PushwindowContents, as_String("title"), as_StringA(windowTitle));
        napi_set_property(env, PushwindowContents, as_String("handle"), as_Number((int64_t)hwnd));
        napi_set_property(env, PushwindowContents, as_String("style"), as_Number((int64_t)dwStyle));
        napi_set_property(env, PushwindowContents, as_String("className"), as_StringA(lpClassName));
        status = napi_set_element(env, Results, counter, PushwindowContents);
        assert(status == napi_ok);
        hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);
        counter = counter + 1;
    }

    return Results;
}

static napi_value getAllWindowsNot(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    status = napi_create_array(env, &Results);
    assert(status == napi_ok);
    return Results;
}

// 隐藏托盘图标
static napi_value SetWindowInTaskbarVisible(napi_env env, napi_callback_info info)
{
    napi_status status;
    const size_t M_size = 2;
    size_t argc = M_size;
    napi_value args[M_size];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = M_size;
        napi_value args[M_size];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int64_t NumHandle;
    napi_get_value_int64(env, args[0], &NumHandle);
    HWND Handle = (HWND)NumHandle;
    bool is_WindowEnabledCommand;
    napi_get_value_bool(env, args[1], &is_WindowEnabledCommand);
    // 初始化COM
    LPVOID lp_COM = NULL;
    CoInitialize(lp_COM);
    // 获取托盘
    HRESULT hr;
    ITaskbarList *pTaskbarList;
    hr = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void **)&pTaskbarList);
    // 开始操作
    if (SUCCEEDED(hr))
    {
        pTaskbarList->HrInit();
        if (is_WindowEnabledCommand)
            pTaskbarList->AddTab(Handle);
        else
            pTaskbarList->DeleteTab(Handle);
        pTaskbarList->Release();
        return as_Boolean(true);
    }
    return as_Boolean(false);
}

static napi_value SetBlockInput(napi_env env, napi_callback_info info)
{
    napi_status status;
    // 最高只接受这么多参数(请注意如果没有传入这么多的数据而获取会照成内存溢出)
    const size_t M_Size = 1;
    size_t argc = M_Size;
    napi_value args[M_Size];
    status = $napi_get_cb_info(argc, args);
    // int parameter_01;
    if (argc == 0)
        napi_throw_type_error(env, NULL, "Wrong arguments size=> 0\n parameter_01:boolean");
    bool Set_Block;
    napi_get_value_bool(env, args[0], &Set_Block);
    return as_Boolean(BlockInput(Set_Block));
}

static napi_value CallSystem(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    // 最高只接受这么多参数(请注意如果没有传入这么多的数据而获取会照成内存溢出)
    const size_t M_Size = 1;
    size_t argc = M_Size;
    napi_value args[M_Size];
    status = $napi_get_cb_info(argc, args);
    string Command = hmc_napi_get_value::string_ansi(env, args[0]);
    int int_Results = system(Command.c_str());
    Results = as_Number(int_Results);
    return Results;
}

BOOL lockSystemInteraction(bool lockb = false)
{
    HINSTANCE hIn = NULL;
    hIn = LoadLibraryA("user32.dll");
    if (hIn)
    {
        BOOL(_stdcall * BlockInput)
        (BOOL bFlag);
        BlockInput = (BOOL(_stdcall *)(BOOL bFlag))GetProcAddress(hIn, "BlockInput");
        if (BlockInput)
            return !!BlockInput(lockb);
        else
            return FALSE;
    }
    else
        return FALSE;
    return FALSE;
}

static napi_value SetSystemHOOK(napi_env env, napi_callback_info info)
{
    napi_status status;
    // 最高只接受这么多参数(请注意如果没有传入这么多的数据而获取会照成内存溢出)
    const size_t M_Size = 1;
    size_t argc = M_Size;
    napi_value args[M_Size];
    status = $napi_get_cb_info(argc, args);
    // int parameter_01;
    if (argc == 0)
        napi_throw_type_error(env, NULL, "Wrong arguments size=> 0\n parameter_01:boolean");
    bool Set_Block;
    napi_get_value_bool(env, args[0], &Set_Block);
    return as_Boolean(lockSystemInteraction(Set_Block));
}

napi_value openURL(napi_env env, napi_callback_info info)
{
   auto input = hmc_NodeArgsValue(env, info);

    input.eq({
        {0, js_string}
        },true);
    
    // 参数1 打开的可执行文件
    wstring lpUrl = input.getStringWide(0,L"");
    // 执行
    bool is_success = hmc_shell_util::ShellOpen::openUrl(lpUrl)>= 31 ;

    return as_Boolean(is_success);
}

napi_value openExternal(napi_env env, napi_callback_info info)
{
    auto input = hmc_NodeArgsValue(env, info);

    input.eq({
        {0, js_string}
        },true);
    
    // 参数1 打开的可执行文件
    wstring lpFile = input.getStringWide(0,L"");
    
    bool isSelect = input.exists(0) ? input.getBool(0,false) : false;

    // 执行
    bool is_success = hmc_shell_util::ShellOpen::showItemInFolder(lpFile,isSelect)>= 31 ;

    return as_Boolean(is_success);
}

napi_value openPath(napi_env env, napi_callback_info info)
{
    auto input = hmc_NodeArgsValue(env, info);

    input.eq({
        {0, js_string}
        },true);
    
    // 参数1 打开的可执行文件
    wstring lpFile = input.getStringWide(0,L"");
    
    // 执行
    bool is_success = hmc_shell_util::ShellOpen::openInExplorer(lpFile)>= 31 ;

    return as_Boolean(is_success);
}


// 执行可执行文件让其独立运行
static napi_value openApp(napi_env env, napi_callback_info info)
{
    
    auto input = hmc_NodeArgsValue(env, info);

    input.eq({
        {0, js_string},
        {1, js_string},
        {2, js_string},
        {3, js_boolean},
        {4, js_boolean}
        },true);
    
    // 参数1 打开的可执行文件
    wstring lpFile = input.getStringWide(0,L"");
    // 参数2 命令行
    wstring lpParameters = input.getStringWide(1,L"");
    // 参数3 cwd
    wstring lpDirectory = input.getStringWide(2,L"");
    
    // 参数4 是否显示
    bool isHideWindow = input.getBool(3,false);
    
    // 参数5 是否提升到管理员权限
    bool isAdmin = input.getBool(4,false);

    // 执行
    bool is_success = hmc_shell_util::ShellOpen::openApp(lpFile,lpParameters,lpDirectory,isHideWindow,isAdmin)>= 31 ;

    return as_Boolean(is_success);
}


static napi_value enumChildWindows(napi_env env, napi_callback_info info)
{
    auto input = hmc_NodeArgsValue(env, info);
    input.eq(0, js_number,true);

    HWND Handle = input.getHwnd(0,0);

    auto subHandleList = hmc_windows_util::getSubWindows(Handle);

    if(subHandleList.index()==0){
       
        std::vector<HWND> subHandleResuleList = std::get<0>(subHandleList);
        std::vector<int> sub_num_list = {};

        size_t count = subHandleResuleList.size();
        for (size_t i = 0; i < count; i++)
        {
            auto it = subHandleResuleList.at(i);
            subHandleResuleList.push_back(it);
        }
        
       return hmc_napi_create_value::Array::Number(env, sub_num_list);

    }

    return as_ArrayNul();
}

// 获取屏幕个数
int GetSystemMetricsLen()
{

    return (int)GetSystemMetrics(SM_CMONITORS);
}

// 获取所有屏幕的位置
vector<RECT> GetDeviceCapsAll()
{
    vector<RECT> CrectList;
    DISPLAY_DEVICE displayDevice;
    ZeroMemory(&displayDevice, sizeof(displayDevice));
    displayDevice.cb = sizeof(displayDevice);
    DEVMODE devMode;
    ZeroMemory(&devMode, sizeof(devMode));
    devMode.dmSize = sizeof(devMode);

    for (int i = 0; EnumDisplayDevices(NULL, i, &displayDevice, 0); ++i)
    {
        if (EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
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
    return CrectList;
}

// 获取鼠标所在的屏幕的位置信息
RECT GetCurrentMonitorRect()
{
    RECT rcRet;
    rcRet.bottom = 0;
    rcRet.left = 0;
    rcRet.right = 0;
    rcRet.top = 0;
    POINT point;
    GetCursorPos(&point);
    static vector<RECT> DeviceCapsRectList = GetDeviceCapsAll();
    for (const RECT &DeviceCapsRectItme : DeviceCapsRectList)
    {

        if (::PtInRect(&DeviceCapsRectItme, point))
        {
            rcRet = DeviceCapsRectItme;
            break;
        }
    }
    return rcRet;
}

static napi_value getSystemMetricsLen(napi_env env, napi_callback_info info)
{
    napi_value Results;
    Results = as_Number32(GetSystemMetricsLen());
    return Results;
}

static napi_value getCurrentMonitorRect(napi_env env, napi_callback_info info)
{
    napi_value Results;
    napi_status status;
    status = napi_create_object(env, &Results);
    if (status != napi_ok)
    {
        return Results;
    };
    RECT rect = GetCurrentMonitorRect();
    status = napi_set_property(env, Results, as_String("left"), as_Number32((int)rect.left));
    if (status != napi_ok)
    {
        return Results;
    };
    status = napi_set_property(env, Results, as_String("top"), as_Number32((int)rect.top));
    if (status != napi_ok)
    {
        return Results;
    };
    status = napi_set_property(env, Results, as_String("right"), as_Number32((int)rect.right));
    if (status != napi_ok)
    {
        return Results;
    };
    status = napi_set_property(env, Results, as_String("bottom"), as_Number32((int)rect.bottom));
    if (status != napi_ok)
    {
        return Results;
    };

    return Results;
}

static napi_value getDeviceCapsAll(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    status = napi_create_array(env, &Results);
    if (status != napi_ok)
    {
        return Results;
    };
    static vector<RECT> DeviceCapsRectList = GetDeviceCapsAll();
    int NextIndex = 0;
    for (const RECT &rect : DeviceCapsRectList)
    {
        napi_value NextRect;
        status = napi_create_object(env, &NextRect);
        if (status != napi_ok)
        {
            return Results;
        };
        status = napi_set_property(env, NextRect, as_String("left"), as_Number32((int)rect.left));
        if (status != napi_ok)
        {
            return Results;
        };
        status = napi_set_property(env, NextRect, as_String("top"), as_Number32((int)rect.top));
        if (status != napi_ok)
        {
            return Results;
        };
        status = napi_set_property(env, NextRect, as_String("right"), as_Number32((int)rect.right));
        if (status != napi_ok)
        {
            return Results;
        };
        status = napi_set_property(env, NextRect, as_String("bottom"), as_Number32((int)rect.bottom));
        if (status != napi_ok)
        {
            return Results;
        };
        status = napi_set_element(env, Results, NextIndex, NextRect);
        if (status != napi_ok)
        {
            return Results;
        };
        NextIndex += 1;
    }

    return Results;
}

bool pointInRECT(POINT pt, RECT inputRect);

static napi_value isMouseMonitorWindow(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1], is_OKs;
    is_OKs = as_Boolean(false);
    status = $napi_get_cb_info(argc, args);
    if (status != napi_ok)
        return is_OKs;
    if (!argc)
    {
        napi_throw_type_error(env, 0, string("The number of parameters entered is not legal size =>").append(to_string(argc)).c_str());
    }
    // get HWND
    int64_t NumHandle;
    status = napi_get_value_int64(env, args[0], &NumHandle);
    if (status != napi_ok)
    {
        return is_OKs;
    }
    HWND Handle = (HWND)NumHandle;
    bool okk = false;
    if ((GetWindow(Handle, GW_OWNER) == (HWND)0 && IsWindowVisible(Handle)))
    {
        RECT winRect;
        GetWindowRect(Handle, &winRect);
        RECT rect = GetCurrentMonitorRect();
        POINT point;
        // 位置 左和上
        point.x = (int)winRect.left;
        point.y = (int)winRect.top;

        if (::PtInRect(&rect, point))
        {
            okk = true;
        }

        // 最边缘
        point.x = (int)winRect.left + winRect.right - 1;
        point.y = (int)winRect.top + winRect.bottom - 1;

        if (::PtInRect(&rect, point))
        {
            okk = true;
        }

        is_OKs = as_Boolean(okk);
    }

    return is_OKs;
}

static napi_value isInMonitorWindow(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1], is_OKs;
    is_OKs = as_Boolean(false);
    status = $napi_get_cb_info(argc, args);
    if (status != napi_ok)
        return is_OKs;
    if (!argc)
    {
        napi_throw_type_error(env, 0, string("The number of parameters entered is not legal size =>").append(to_string(argc)).c_str());
    }
    // get HWND
    int64_t NumHandle;
    status = napi_get_value_int64(env, args[0], &NumHandle);
    if (status != napi_ok)
    {
        return is_OKs;
    }
    HWND Handle = (HWND)NumHandle;
    if ((GetWindow(Handle, GW_OWNER) == (HWND)0 && IsWindowVisible(Handle)))
    {
        bool okk = false;
        RECT winRect;
        GetWindowRect(Handle, &winRect);
        static vector<RECT> DeviceCapsRectList = GetDeviceCapsAll();
        for (const RECT &rect : DeviceCapsRectList)
        {
            POINT point;
            // 位置 左和上
            point.x = (int)winRect.left;
            point.y = (int)winRect.top;

            if (::PtInRect(&rect, point))
            {
                okk = true;
            }

            // 最边缘
            point.x = (int)winRect.left + winRect.right;
            point.y = (int)winRect.top + winRect.bottom;

            if (::PtInRect(&rect, point))
            {
                okk = true;
            }

            // 中间点匹配
            point.x = (int)winRect.left + winRect.right - 1;
            point.y = (int)winRect.top + winRect.bottom - 1;
            point.x = point.x / 2;
            point.y = point.y / 2;

            if (::PtInRect(&rect, point))
            {
                okk = true;
            }
        }
        is_OKs = as_Boolean(okk);
    }

    return is_OKs;
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
    char className[MAX_PATH];
    if (::GetClassNameA(hwnd, className, MAX_PATH) > 0)
    {
        result.append(className);
        bHas = true;
    }

    bHas = false;
    return result;
}

static napi_value getWindowClassName(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Result = as_String("");

    if (status != napi_ok)
        return Result;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    if (status != napi_ok)
        return Result;
    if (!argc)
    {
        napi_throw_type_error(env, 0, string("The number of parameters entered is not legal size =>").append(to_string(argc)).c_str());
    }
    // get HWND
    int64_t NumHandle;
    status = napi_get_value_int64(env, args[0], &NumHandle);
    if (status != napi_ok)
        return Result;
    HWND Handle = (HWND)NumHandle;
    bool is_ok = false;
    string strClassName = string("");
    strClassName.append(getClassName(Handle, is_ok));
    Result = as_StringA((char *)strClassName.c_str());

    return Result;
}

static napi_value getWindowStyle(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Result = as_Number(0);

    if (status != napi_ok)
        return Result;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    if (status != napi_ok)
        return Result;
    if (!argc)
    {
        napi_throw_type_error(env, 0, string("The number of parameters entered is not legal size =>").append(to_string(argc)).c_str());
    }
    // get HWND
    int64_t NumHandle;
    status = napi_get_value_int64(env, args[0], &NumHandle);
    if (status != napi_ok)
        return Result;
    HWND Handle = (HWND)NumHandle;

    // is the handle
    if (!(GetWindow(Handle, GW_OWNER) == (HWND)0 && IsWindowVisible(Handle)))
        return Result;

    DWORD dwStyle = GetClassLongA(Handle, GCL_STYLE);

    Result = as_Number(dwStyle);
    return Result;
}

void SetWindowTitleIcon(HWND handle, string iconStr)
{
    HICON hWindowIcon = NULL;
    HICON hWindowIconBig = NULL;
    if (hWindowIcon != NULL)
        DestroyIcon(hWindowIcon);
    if (hWindowIconBig != NULL)
        DestroyIcon(hWindowIconBig);
    hWindowIcon = (HICON)LoadImageA(GetModuleHandle(NULL), iconStr.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
    hWindowIconBig = (HICON)LoadImageA(GetModuleHandle(NULL), iconStr.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    SendMessage(handle, WM_SETICON, ICON_SMALL, (LPARAM)hWindowIcon);
    SendMessage(handle, WM_SETICON, ICON_BIG, (LPARAM)hWindowIconBig);
}
void SetWindowTitleIconUs32(HWND handle, string iconStr)
{
    HICON hWindowIcon = NULL;
    HICON hWindowIconBig = NULL;
    if (hWindowIcon != NULL)
        DestroyIcon(hWindowIcon);
    if (hWindowIconBig != NULL)
        DestroyIcon(hWindowIconBig);
    hWindowIcon = (HICON)LoadImageA(GetModuleHandle(NULL), iconStr.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
    hWindowIconBig = (HICON)LoadImageA(GetModuleHandle(NULL), iconStr.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

    HINSTANCE hIn = NULL;
    hIn = LoadLibraryA("user32.dll");
    if (hIn)
    {
        LRESULT(WINAPI * SendMessageA)
        (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        SendMessageA = (LRESULT(WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))GetProcAddress(hIn, "SendMessageA");
        if (SendMessageA)
        {

            SendMessageA(handle, WM_SETICON, ICON_SMALL, (LPARAM)hWindowIcon);
            SendMessageA(handle, WM_SETICON, ICON_BIG, (LPARAM)hWindowIconBig);
        }
        else
        {
        }
    }
    else
    {
    }
}
void SetWindowIconForExtractUs32(HWND hwnd, string iconStr, int index)
{
    HICON hIcon;
    hIcon = (HICON)ExtractIconA(NULL, iconStr.c_str(), index);
    HINSTANCE hIn = NULL;
    hIn = LoadLibraryA("user32.dll");
    if (hIn)
    {
        LRESULT(WINAPI * SendMessageA)
        (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        SendMessageA = (LRESULT(WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))GetProcAddress(hIn, "SendMessageA");
        if (SendMessageA)
        {
            SendMessageA(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            SendMessageA(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        }
        else
        {
        }
    }
    else
    {
    }
}

void SetWindowIconForExtract(HWND hwnd, string iconStr, int index)
{
    HICON hIcon;
    hIcon = (HICON)ExtractIconA(NULL, iconStr.c_str(), index);

    SendMessageA(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    SendMessageA(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
}

static napi_value setWindowTitleIcon(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    int64_t Handle;
    status = napi_get_value_int64(env, args[0], &Handle);
    HWND handle = (HWND)Handle;
    string iconStr = hmc_napi_get_value::string_ansi(env, args[1]);

    SetWindowTitleIcon(handle, iconStr);
    UpdateWindow(handle);
    return NULL;
}
static napi_value setWindowIconForExtract(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value args[3];
    status = $napi_get_cb_info(argc, args);
    int64_t Handle;
    status = napi_get_value_int64(env, args[0], &Handle);
    HWND handle = (HWND)Handle;
    string iconStr = hmc_napi_get_value::string_ansi(env, args[1]);
    int index;
    status = napi_get_value_int32(env, args[2], &index);
    SetWindowIconForExtract(handle, iconStr, index);
    SetWindowIconForExtractUs32(handle, iconStr, index);
    UpdateWindow(handle);
    return NULL;
}

static napi_value _SET_HMC_DEBUG(napi_env env, napi_callback_info info)
{
    _________HMC___________ = !_________HMC___________;
    return as_Boolean(_________HMC___________);
}

napi_value Popen(napi_env env, napi_callback_info info)
{
    napi_status status;

    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    string cmd = hmc_napi_get_value::string_ansi(env, args[0]);
    napi_value napi_result;

    char buffer[128];
    string result = "";
    FILE *pipe = _popen(cmd.c_str(), "r");
    if (!pipe)
    {
        // std::cerr << "无法打开管道!" << std::endl;
        return napi_result;
    }
    while (fgets(buffer, sizeof buffer, pipe) != NULL)
    {
        result += buffer;
    }
    _pclose(pipe);
    string _A2U8_result = hmc_string_util::ansi_to_utf8(result.c_str());
    napi_create_string_utf8(env, _A2U8_result.c_str(), NAPI_AUTO_LENGTH, &napi_result);
    return napi_result;
}

bool CreateMutex(std::string MutexName)
{
    bool has_mut_exist = false;

    HANDLE hMutex = CreateMutexA(NULL, FALSE, MutexName.c_str());

    if (hMutex == NULL)
    {
        has_mut_exist = true;
    }
    // 检查是否已经存在同名的互斥体
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        has_mut_exist = true;
        CloseHandle(hMutex);
    }

    return !has_mut_exist;
}

bool HasMutex(std::string MutexName)
{
    bool has_mut_exist = true;

    HANDLE hMutex;

    hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, MutexName.c_str());
    if (NULL == hMutex)
    {
        has_mut_exist = false;
    }

    CloseHandle(hMutex);
    return has_mut_exist;
}

napi_value createMutex(napi_env env, napi_callback_info info)
{

    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    hmc_is_argv_type(args, 0, 1, napi_string, NULL);

    string MutexName = hmc_napi_get_value::string_ansi(env, args[0]);

    return as_Boolean(CreateMutex(MutexName));
}

napi_value hasMutex(napi_env env, napi_callback_info info)
{

    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    hmc_is_argv_type(args, 0, 1, napi_string, NULL);

    string MutexName = hmc_napi_get_value::string_ansi(env, args[0]);

    return as_Boolean(HasMutex(MutexName));
}

// 搜索窗口句柄
napi_value fn_findWindow(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    napi_value Results = hmc_napi_create_value::Null(env);

    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);

    switch (argc)
    {
    case 1:
    {
        HWND window_Handle = ::FindWindowW(hmc_napi_get_value::string_utf16(env, args[0]).c_str(), NULL);
        if (window_Handle == NULL)
        {
            return Results;
        }
        return hmc_napi_create_value::Number(env, window_Handle);
    }

    case 2:
    {
        //  fn_findWindow(null,"title")
        if (hmc_napi_type::isNull(env, args[0]))
        {
            // fn_findWindow(null,null)
            if (!hmc_napi_type::isString(env, args[1]))
            {
                return Results;
            }

            HWND window_Handle = ::FindWindowW(NULL, hmc_napi_get_value::string_utf16(env, args[1]).c_str());
            if (window_Handle == NULL)
            {
                return Results;
            }
            return hmc_napi_create_value::Number(env, window_Handle);
        }
        //  fn_findWindow("class",null)
        else if (hmc_napi_type::isNull(env, args[1]))
        {
            HWND window_Handle = ::FindWindowW(hmc_napi_get_value::string_utf16(env, args[0]).c_str(), NULL);
            if (window_Handle == NULL)
            {
                return Results;
            }
            return hmc_napi_create_value::Number(env, window_Handle);
        }
        // fn_findWindow("class","title")
        else
        {

            HWND window_Handle = ::FindWindowW(hmc_napi_get_value::string_utf16(env, args[0]).c_str(), hmc_napi_get_value::string_utf16(env, args[1]).c_str());
            if (window_Handle == NULL)
            {
                return Results;
            }
            return hmc_napi_create_value::Number(env, window_Handle);
        }
    }
    }

    return hmc_napi_create_value::Null(env);
}

// 获取子窗口句柄
napi_value fn_findWindowEx(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 4;
    napi_value args[4];
    napi_value Results = hmc_napi_create_value::Null(env);

    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);

    if (argc == 4)
    {
        HWND window_Handle = ::FindWindowExW(
            // hWndParent
            (hmc_napi_type::isNumber(env, args[0]) ? hmc_napi_get_value::number_HWND(env, args[0]) : NULL),
            // hWndChildAfter
            (hmc_napi_type::isNumber(env, args[1]) ? hmc_napi_get_value::number_HWND(env, args[1]) : NULL),
            // hWndChildAfter
            (hmc_napi_type::isString(env, args[2]) ? hmc_napi_get_value::string_utf16(env, args[2]).c_str() : NULL),
            // hWndChildAfter
            (hmc_napi_type::isString(env, args[3]) ? hmc_napi_get_value::string_utf16(env, args[3]).c_str() : NULL));

        if (window_Handle == NULL)
        {
            return Results;
        }

        return hmc_napi_create_value::Number(env, window_Handle);
    }

    return hmc_napi_create_value::Null(env);
}

#define HMC_CHECK_CATCH catch (char *err){};

/**
 * @brief 获取窗口类名
 *
 * @param hwnd
 * @param bHas
 * @return string
 */
string getClassNameA(HWND hwnd, bool &bHas)
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
            vsErrorCodeAssert(4989, "getClassName");
        }
    }
    HMC_CHECK_CATCH;
    bHas = false;
    return hmc_string_util::removeNullCharactersAll(result);
}

/**
 * @brief 获取窗口类名
 *
 * @param hwnd
 * @param bHas
 * @return string
 */
wstring getClassNameW(HWND hwnd, bool &bHas)
{
    wstring result = wstring();
    try
    {
        wchar_t className[MAX_PATH];
        if (::GetClassNameW(hwnd, className, MAX_PATH) > 0)
        {
            result.append(className);
            bHas = true;
        }
        else
        {
            vsErrorCodeAssert(49896, "getClassName");
        }
    }
    HMC_CHECK_CATCH;
    bHas = false;
    return hmc_string_util::removeNullCharactersAll(result);
}

/**
 * @brief 获取窗口标题
 *
 * @return string
 */
wstring getWindowTextW(HWND hwnd)
{
    wstring result = wstring();
    try
    {

        LPWSTR pszMem = HMC_VirtualAlloc(LPWSTR, MAX_PATH);
        size_t leng = ::GetWindowTextW(hwnd, pszMem, MAX_PATH);
        result.resize(leng);
        for (size_t i = 0; i < leng; i++)
        {
            result.push_back(pszMem[i]);
        }

        HMC_VirtualFree(pszMem);
    }

    HMC_CHECK_CATCH;
    return hmc_string_util::removeNullCharactersAll(result);
}

/**
 * @brief 获取窗口标题
 *
 * @return string
 */
string getWindowTextA(HWND hwnd)
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
    return hmc_string_util::removeNullCharactersAll(result);
}

/**
 * @brief 获取所有窗口
 *
 * @param env
 * @param info
 * - className 类名称
 * - titleName 标题
 * - isWindow 是否必须是win
 * - isCaseSensitive 大小写敏感
 * @return napi_value
 */
napi_value fn_findAllWindow(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 4;
    napi_value args[4];
    napi_value Results = hmc_napi_create_value::Array::Number(env, vector<int>());

    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);

    if (argc != 4)
    {
        return Results;
    }

    bool flag_isWindow = (hmc_napi_type::isBoolean(env, args[2]) ? hmc_napi_get_value::boolean_bool(env, args[2]) : true);
    bool flag_isCaseSensitive = (hmc_napi_type::isBoolean(env, args[3]) ? hmc_napi_get_value::boolean_bool(env, args[3]) : true);

    wstring _className = (hmc_napi_type::isString(env, args[0]) ? hmc_napi_get_value::string_utf16(env, args[0]) : wstring(L""));
    wstring _titleName = (hmc_napi_type::isString(env, args[1]) ? hmc_napi_get_value::string_utf16(env, args[1]) : wstring(L""));

    //"\0title标题\0" ->  flag_isCaseSensitive ? "TITLE标题" : "title标题"
    wstring className = flag_isCaseSensitive ? hmc_string_util::removeNullCharactersAll(_className) : hmc_string_util::text_to_upper(hmc_string_util::removeNullCharactersAll(_className));
    wstring titleName = flag_isCaseSensitive ? hmc_string_util::removeNullCharactersAll(_titleName) : hmc_string_util::text_to_upper(hmc_string_util::removeNullCharactersAll(_titleName));

    HWND winEnumerable = GetTopWindow(0);

    vector<int> hwnd_list = vector<int>();

    while (winEnumerable)
    {
        if (true)
        {

            wstring the_class = wstring();
            wstring the_titleName = wstring();

            if (!_className.empty())
            {
                bool the_class_ok = false;
                the_class = (flag_isCaseSensitive ? hmc_string_util::text_to_upper(getClassNameW(winEnumerable, the_class_ok)) : getClassNameW(winEnumerable, the_class_ok));

                if (the_class == _className)
                {

                    if (_titleName.empty())
                    {

                        hwnd_list.push_back((int)winEnumerable);
                    }
                }
            }

            if (!_titleName.empty())
            {
                bool the_title_ok = false;
                the_titleName = (flag_isCaseSensitive ? hmc_string_util::text_to_upper(getWindowTextW(winEnumerable)) : getWindowTextW(winEnumerable));
                if (the_titleName == _titleName)
                {

                    if (_className.empty())
                    {
                        hwnd_list.push_back((int)winEnumerable);
                    }
                }
            }

            if (!_className.empty() && !the_titleName.empty())
            {
                if (the_titleName == _titleName && the_class == _className)
                {
                    hwnd_list.push_back((int)winEnumerable);
                }
            }
        }
        winEnumerable = GetNextWindow(winEnumerable, GW_HWNDNEXT);
    }

    for (size_t index = 0; index < hwnd_list.size(); index++)
    {
        int hwnd = hwnd_list[index];
        napi_value number = hmc_napi_create_value::Number(env, hwnd);
        napi_set_element(env, Results, index, number);
    }
    return Results;
}

napi_value __Popen(napi_env env, napi_callback_info info)
{
    return Popen(env, info);
}
//? -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief 当进程结束或者进程奔溃时候执行的gc程序
 *
 */
static void hmc_gc_func()
{

    // 防止鼠标被锁定
    if (hmc_mouse::LimitMouseRange::hasLimitMouseRange_worker())
    {
        hmc_mouse::LimitMouseRange::stopLimitMouseRange_worker();
    }

    // 释放鼠标监听的线程
    if (!hmc_mouse::MouseHook::isValidHookMouse())
    {
        hmc_mouse::MouseHook::stopHookMouse();
    }

    // 释放键盘监听的线程
    if (!hmc_Keyboard::keyboardHook::isValidHookKeyboard())
    {
        hmc_Keyboard::keyboardHook::stopHookKeyboard();
    }

}

napi_value fn_SendMessage(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    auto res = ::SendMessageW(input.getHwnd(0), (UINT)input.getInt(1), (WPARAM)input.getInt64(2), (LPARAM)input.getInt64(3));

    return hmc_napi_create_value::Number(env, res);
}

void Init_MAIN_DATA()
{
    // 空间预开劈
    hmc_PromiseSession::____$hmcPromise_PromiseTaskList.reserve(150);
    hmc_PromiseSession::____$hmcPromise_promise_task_id_send_index_list.reserve(150);
}

static napi_value Init(napi_env env, napi_value exports)
{
    
    napi_property_descriptor BIND_NAPI_METHOD[] = {
        ADD_NAPI_METHOD_Str_VALUE("version", "0.0.0"),
        ADD_NAPI_METHOD_Str_VALUE("desc", "Easier Access to System APIs"),
        ADD_NAPI_METHOD_Str_VALUE("platform", "win32"),
        DECLARE_NAPI_METHOD("getSystemIdleTime", getSystemIdleTime),                       //=>2019
        DECLARE_NAPI_METHOD("sleep", sleep),                                               //=>2019
        DECLARE_NAPI_METHOD("isAdmin", isAdmin),                                           //=>2019
        DECLARE_NAPI_METHOD("openApp", openApp),                                           //=>2019
        DECLARE_NAPI_METHOD("openExternal", openExternal),                                 //=>2019-2-1ADD
        DECLARE_NAPI_METHOD("openURL", openURL),                                           //=>2019-2-1ADD
        DECLARE_NAPI_METHOD("openPath", openPath),                                         //=>2019-2-1ADD
        DECLARE_NAPI_METHOD("powerControl", powerControl),                                 //=>2019
        DECLARE_NAPI_METHOD("getForegroundWindow", getForegroundWindow),                   //=>2019
        DECLARE_NAPI_METHOD("showMonitors", showMonitors),                                 //=>2019
        DECLARE_NAPI_METHOD("shutMonitors", shutMonitors),                                 //=>2019
        DECLARE_NAPI_METHOD("getSystemMenu", getSystemMenu),                               //=>2019
        DECLARE_NAPI_METHOD("messageBox", messageBox),                                     //=>2019
        DECLARE_NAPI_METHOD("alert", alert),                                               //=>2019-2-1ADD
        DECLARE_NAPI_METHOD("confirm", confirm),                                           //=>2019-2-1ADD
        DECLARE_NAPI_METHOD("MessageError", MessageError),                                 //=>2019-2-1ADD
        DECLARE_NAPI_METHOD("MessageStop", MessageStop),                                   //=>2019-2-1ADD
        DECLARE_NAPI_METHOD("fn_SetWindowTitle", fn_SetWindowTitle),                       // 2019?
        DECLARE_NAPI_METHOD("fn_CloseWindow", fn_CloseWindow),                             // 2019?
        DECLARE_NAPI_METHOD("fn_WindowVisible", fn_WindowVisible),                         // 2019?
        DECLARE_NAPI_METHOD("fn_ShowWindow", fn_ShowWindow),                               // 2019?
        DECLARE_NAPI_METHOD("fn_GetWindowTitle", fn_GetWindowTitle),                       // 2019?
        DECLARE_NAPI_METHOD("getProcessHandle", getProcessHandle),                         // 2019?
        DECLARE_NAPI_METHOD("isSystemX64", isSystemX64),                                   // 2019?
        DECLARE_NAPI_METHOD("getTrayList", getTrayList),                                   // 2019?
        DECLARE_NAPI_METHOD("setHandleTransparent", setHandleTransparent),                 // 2019?
        DECLARE_NAPI_METHOD("getHandleProcessID", getHandleProcessID),                     // 2019?
        DECLARE_NAPI_METHOD("getForegroundWindowProcessID", getForegroundWindowProcessID), // 2019?
        DECLARE_NAPI_METHOD("getMetrics", getMetrics),                                     // 2019?
        DECLARE_NAPI_METHOD("getPointWindowProcessId", getPointWindowProcessId),           // 2019?
        DECLARE_NAPI_METHOD("getPointWindowName", getPointWindowName),                     // 2019?
        DECLARE_NAPI_METHOD("getPointWindow", getPointWindow),                             // 2019?
        DECLARE_NAPI_METHOD("getDeviceCaps", getDeviceCaps),                               // 2019?
        DECLARE_NAPI_METHOD("getWindowRect", getWindowRect),                               // 2019?
        DECLARE_NAPI_METHOD("setWindowMode", setWindowMode),                               // 2019?
        DECLARE_NAPI_METHOD("closedHandle", closedHandle),                                 // 2019?
        DECLARE_NAPI_METHOD("setWindowTop", setWindowTop),                                 // 2019?
        DECLARE_NAPI_METHOD("hasWindowTop", hasWindowTop),                                 // 2019?
        DECLARE_NAPI_METHOD("windowJitter", windowJitter),                                 //=>3-1UP to Asynchronous
        DECLARE_NAPI_METHOD("isHandle", isHandle),                                         // 2019?
        DECLARE_NAPI_METHOD("getPointWindowMain", getPointWindowMain),                     // 2019?
        DECLARE_NAPI_METHOD("getMainWindow", getMainWindow),                               // 2019?
        DECLARE_NAPI_METHOD("isEnabled", isEnabled),                                       // 2019?
        DECLARE_NAPI_METHOD("setWindowEnabled", setWindowEnabled),                         // 2019?
        DECLARE_NAPI_METHODRM("setWindowFocus", setForegroundWindow),                      // 2019?
        DECLARE_NAPI_METHODRM("setForegroundWindow", setForegroundWindow),                 // 2019?
        DECLARE_NAPI_METHOD("updateWindow", updateWindow),                                 // 2019?
        DECLARE_NAPI_METHOD("SetWindowInTaskbarVisible", SetWindowInTaskbarVisible),       // 2019?
        DECLARE_NAPI_METHOD("SetBlockInput", SetBlockInput),                               // 2019?
        DECLARE_NAPI_METHOD("system", CallSystem),                                         // 2019?
        DECLARE_NAPI_METHOD("SetSystemHOOK", SetSystemHOOK),                               // 2019?
        DECLARE_NAPI_METHOD("systemStartTime", systemStartTime),                           // 2019?
        DECLARE_NAPI_METHODRM("getShortcutLink", getShortcutLink),
        DECLARE_NAPI_METHODRM("setShortcutLink", setShortcutLink),
        DECLARE_NAPI_METHODRM("createSymlink", createSymlink),       //=>2022-2-9ADD
        DECLARE_NAPI_METHODRM("createHardLink", createHardLink),     //=>2022-2-9ADD
        DECLARE_NAPI_METHODRM("createDirSymlink", createDirSymlink), //=>2022-2-9ADD
        DECLARE_NAPI_METHODRM("getClipboardText", getClipboardText),
        DECLARE_NAPI_METHODRM("setClipboardText", setClipboardText),
        DECLARE_NAPI_METHODRM("clearClipboard", clearClipboard),
        DECLARE_NAPI_METHODRM("getClipboardFilePaths", getClipboardFilePaths), //=>2022-2-11ADD
        DECLARE_NAPI_METHODRM("setClipboardFilePaths", setClipboardFilePaths), //=>2022-2-11ADD
        DECLARE_NAPI_METHODRM("getClipboardHTML", getClipboardHTML),
        DECLARE_NAPI_METHOD("getHidUsbList", getHidUsbList),
        DECLARE_NAPI_METHOD("getUsbDevsInfo", getUsbDevsInfo),                 //=>2022-2-11ADD
        DECLARE_NAPI_METHOD("enumChildWindows", enumChildWindows),             //=>2022-2-11ADD
        DECLARE_NAPI_METHODRM("deleteFile", TrashFile),                        //=>2022-2-11ADD
        DECLARE_NAPI_METHODRM("getClipboardInfo", getClipboardInfo),           //=>2022-2-12ADD
        DECLARE_NAPI_METHODRM("enumClipboardFormats", enumClipboardFormats),   //=>2022-2-12ADD
        DECLARE_NAPI_METHODRM("getHidUsbIdList", getHidUsbIdList),             //=>2022-2-12ADD
        DECLARE_NAPI_METHODRM("getSystemMetricsLen", getSystemMetricsLen),     //=>2022-2-12ADD
        DECLARE_NAPI_METHODRM("getCurrentMonitorRect", getCurrentMonitorRect), //=>2022-2-12ADD
        DECLARE_NAPI_METHODRM("getDeviceCapsAll", getDeviceCapsAll),           //=>2022-2-12ADD
        DECLARE_NAPI_METHODRM("isMouseMonitorWindow", isMouseMonitorWindow),   //=>2022-2-12ADD
        DECLARE_NAPI_METHODRM("isInMonitorWindow", isInMonitorWindow),         //=>2022-2-12ADD
        DECLARE_NAPI_METHODRM("getAllWindows", getAllWindowsNot),              //=>2022-2-13ADD
        DECLARE_NAPI_METHOD("getWindowStyle", getWindowStyle),
        DECLARE_NAPI_METHOD("getWindowClassName", getWindowClassName),
        DECLARE_NAPI_METHOD("setWindowTitleIcon", setWindowTitleIcon),
        // auto.cpp
        DECLARE_NAPI_METHODRM("setCursorPos", setCursorPos),                     //=>2022-3-1UP
        DECLARE_NAPI_METHODRM("rightClick", rightClick),                         //=>2022-3-1UP
        DECLARE_NAPI_METHODRM("leftClick", leftClick),                           //=>2022-3-1UP
        DECLARE_NAPI_METHODRM("getMouseMovePoints", getMouseMovePoints),         //=>2022-3-1UP
        DECLARE_NAPI_METHODRM("hasKeyActivate", hasKeyActivate),                 //=>2022-3-1UP
        DECLARE_NAPI_METHODRM("getBasicKeys", getBasicKeys),                     //=>2022-3-1UP
        DECLARE_NAPI_METHODRM("mouse", mouse),                                   //=>2022-3-1UP
        DECLARE_NAPI_METHODRM("installKeyboardHook", installKeyboardHook),       //=>2022-3-1ADD
        DECLARE_NAPI_METHODRM("unKeyboardHook", unKeyboardHook),                 //=>2022-3-1ADD
        DECLARE_NAPI_METHODRM("getKeyboardNextSession", getKeyboardNextSession), //=>2022-3-1ADD
        DECLARE_NAPI_METHODRM("isStartKeyboardHook", isStartKeyboardHook),       //=>2022-3-1ADD
        // windows.cpp
        DECLARE_NAPI_METHODRM("getAllWindowsHandle", getAllWindowsHandle), //=>2022-3-6UP
        // process.cpp
        DECLARE_NAPI_METHODRM("killProcess", killProcess),                           //=>2022-4-1UP
        DECLARE_NAPI_METHODRM("getModulePathList", getModulePathList),               //=>2022-4-1ADD
        DECLARE_NAPI_METHODRM("enumProcessHandle", enumProcessHandle),               //=>2022-4-1ADD
        DECLARE_NAPI_METHODRM("enumProcessHandlePolling", enumProcessHandlePolling), //=>2022-4-2ADD
        DECLARE_NAPI_METHODRM("getVolumeList", getVolumeList),                       //=>2022-4-1ADD
        DECLARE_NAPI_METHODRM("formatVolumePath", formatVolumePath),                 //=>2022-4-1ADD
        DECLARE_NAPI_METHODRM("getProcessThreadList", getProcessThreadList),         //=>2022-4-3ADD
        DECLARE_NAPI_METHODRM("clearEnumProcessHandle", clearEnumProcessHandle),     //=>2022-4-3ADD
        DECLARE_NAPI_METHODRM("getSubProcessID", getSubProcessID),                   //=>2022-4-3ADD
        DECLARE_NAPI_METHODRM("enumAllProcessPolling", enumAllProcessPolling),       //=>2022-4-3ADD
        DECLARE_NAPI_METHODRM("enumAllProcess", enumAllProcess),                     //=>2022-4-3ADD
        DECLARE_NAPI_METHODRM("clearEnumAllProcessList", clearEnumAllProcessList),   //=>2022-4-3ADD
        DECLARE_NAPI_METHOD("setWindowIconForExtract", setWindowIconForExtract),     //=>2022-5-12ADD
        DECLARE_NAPI_METHOD("popen", Popen),                                         //=>2022-5-12ADD
        DECLARE_NAPI_METHOD("_popen", __Popen),                                      //=>2022-5-12ADD
        DECLARE_NAPI_METHODRM("sendKeyT2C", sendKeyT2C),                             //=>2022-5-26ADD
        DECLARE_NAPI_METHODRM("sendKeyboard", sendKeyboard),                         //=>2022-5-26ADD
        DECLARE_NAPI_METHODRM("sendKeyT2CSync", sendKeyT2CSync),                     //=>2022-5-26ADD
        DECLARE_NAPI_METHODRM("sendBasicKeys", sendBasicKeys),                       //=>2022-5-26ADD
        DECLARE_NAPI_METHODRM("captureBmpToFile", captureBmpToFile),                 //=>2022-5-27ADD
        DECLARE_NAPI_METHODRM("getColor", getColor),                                 //=>2022-5-27ADD
        DECLARE_NAPI_METHOD("createMutex", createMutex),                             //=>2022-6-21ADD
        DECLARE_NAPI_METHOD("hasMutex", hasMutex),                                   //=>2022-6-21ADD
        DECLARE_NAPI_METHODRM("putenv", fn_putenv),                                  //=>2022-6-21ADD
        DECLARE_NAPI_METHODRM("getenv", fn_getenv),                                  //=>2022-6-21ADD
        DECLARE_NAPI_METHODRM("getAllEnv", fn_getAllEnv),                            //=>2022-6-21ADD
        DECLARE_NAPI_METHOD("findWindow", fn_findWindow),                            //=>2022-11-18ADD
        DECLARE_NAPI_METHOD("findWindowEx", fn_findWindowEx),                        //=>2022-11-18ADD
        // 2023-11-27 add support
        DECLARE_NAPI_METHODRM("getVariableAll", fn_getVariableAll),
        // 2023-11-27 add support
        DECLARE_NAPI_METHODRM("getVariableAnalysis", fn_getEnvKeyAnalysis),
        // 2023-11-27 add support
        DECLARE_NAPI_METHODRM("getSystemKeyList", fn_getSystemKeyList),
        // 2023-11-27 add support
        DECLARE_NAPI_METHODRM("getUserKeyList", fn_getUserKeyList),
        // 2023-11-27 add support
        DECLARE_NAPI_METHODRM("getRealGlobalVariable", fn_getRealGlobalVariable),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("putUserVariable", fn_putUserVariable),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("putSystemVariable", fn_putSystemVariable),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("getUserVariable", fn_getUserVariable),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("getSystemVariable", fn_getSystemVariable),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("removeSystemVariable", fn_removeSystemVariable),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("removeAllSingleVariable", fn_removeAllSingleVariable),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("removeUserVariable", fn_removeUserVariable),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("escapeEnvVariable", fn_escapeEnvVariable),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("hasUseKeyExists", fn_hasUseKeyExists),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("hasSysKeyExists", fn_hasSysKeyExists),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("hasKeyExists", fn_hasKeyExists),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("__debug_AllocConsole", fn_AllocConsole),
        // 2023-11-28 add support
        DECLARE_NAPI_METHODRM("getProcessStartTime", fn_getProcessStartTime),
        // 2023-12-22 add support
        DECLARE_NAPI_METHODRM("getCursorPos", getCursorPos),
        // 2023-12-22 add support
        DECLARE_NAPI_METHODRM("isStartHookMouse2", isStartHookMouse2),
        // 2023-12-22 add support
        DECLARE_NAPI_METHODRM("getMouseNextSession2", getMouseNextSession2),
        // 2023-12-22 add support
        DECLARE_NAPI_METHODRM("unHookMouse2", unHookMouse2),
        // 2023-12-22 add support
        DECLARE_NAPI_METHODRM("installHookMouse2", installHookMouse2),
        // 2023-12-22 add support
        DECLARE_NAPI_METHODRM("getLastInputTime", getLastInputTime),

        // 2024-01-07 add support
        DECLARE_NAPI_METHODRM("removeRegistrFolder", removeRegistrFolder),
        DECLARE_NAPI_METHODRM("removeRegistrValue", removeRegistrValue),
        DECLARE_NAPI_METHODRM("createRegistrFolder", createRegistrFolder),
        DECLARE_NAPI_METHODRM("getRegistrFolderStat", getRegistrFolderStat),
        DECLARE_NAPI_METHODRM("getRegistrValueStat", getRegistrValueStat),
        DECLARE_NAPI_METHODRM("getRegistrBuffValue", getRegistrBuffValue),
        DECLARE_NAPI_METHODRM("getRegistrValue", getRegistrValue),
        DECLARE_NAPI_METHODRM("setRegistrValue", setRegistrValue),

        // 2023-12-11 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_get", _PromiseSession_getAll),
        // 2023-12-1 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_isClosed", _PromiseSession_isClosed),
        // 2023-12-1 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_stop", _PromiseSession_stop),
        // 2023-12-1 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_max_id", _PromiseSession_max_id),
        // 2023-12-1 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_data_size", _PromiseSession_data_size),
        // 2023-12-1 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_set_sleep_time", _PromiseSession_set_sleep_time),
        // 2023-12-1 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_await", _PromiseSession_await),
        // 2023-12-1 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_ongoingTasks", _PromiseSession_ongoingTasks),
        // 2023-12-1 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_completeTasks", _PromiseSession_completeTasks),
        // 2023-12-1 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_get_sleep_time", _PromiseSession_get_sleep_time),
        // 2023-12-1 add support
        DECLARE_NAPI_METHODRM("_PromiseSession_allTasks", _PromiseSession_allTasks),
        // 2023-12-23 add support
        DECLARE_NAPI_METHODRM("hasLimitMouseRangeWorker", hasLimitMouseRangeWorker),
        // 2023-12-23 add support
        DECLARE_NAPI_METHODRM("setLimitMouseRange", setLimitMouseRange),
        // 2023-12-23 add support
        DECLARE_NAPI_METHODRM("stopLimitMouseRangeWorker", stopLimitMouseRangeWorker),
        // 2023-12-28 add support
        DECLARE_NAPI_METHODRM("sendMessage", fn_SendMessage),

    };
    _________HMC___________ = false;

    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);

    // 2.0 api 异步同步双支持版本
    exports_process_all_v2_fun(/*

    fn_getAllProcessList::exports(env, exports, "getAllProcessList");
    fn_getAllProcessList::exportsSync(env, exports, "getAllProcessListSync");

    fn_getAllProcessNtList::exports(env, exports, "getAllProcessListNt");
    fn_getAllProcessNtList::exportsSync(env, exports, "getAllProcessListNtSync");

    fn_getAllProcessSnpList::exports(env, exports, "getAllProcessListSnp");
    fn_getAllProcessSnpList::exportsSync(env, exports, "getAllProcessListSnpSync");

    fn_getProcessCpuUsage::exports(env, exports, "getProcessCpuUsage");
    fn_getProcessCpuUsage::exportsSync(env, exports, "getProcessCpuUsageSync");

    fn_GetProcessIdFilePath::exports(env, exports, "getProcessFilePath");
    fn_GetProcessIdFilePath::exportsSync(env, exports, "getProcessFilePathSync");

    fn_existProcess::exports(env, exports, "existProcess");
    fn_existProcess::exportsSync(env, exports, "existProcessSync");

    fn_GetProcessCommandLineByPid::exports(env, exports, "getProcessCommand");
    fn_GetProcessCommandLineByPid::exportsSync(env, exports, "getProcessCommandSync");

    fn_GetCurrentWorkingDirectory::exports(env, exports, "getProcessCwd");
    fn_GetCurrentWorkingDirectory::exportsSync(env, exports, "getProcessCwdSync");

                               */
                               env, exports);

    atexit(hmc_gc_func);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
