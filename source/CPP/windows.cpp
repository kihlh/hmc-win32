#include "./Mian.hpp";
#include "hmc_napi_value_util.h"

// 获取所有窗口
napi_value getAllWindowsHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    status = napi_create_array(env, &Results);
    assert(status == napi_ok);
    // 取值
    napi_value argv[1];
    size_t argc = 1;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    assert(status == napi_ok);
    bool is_WindowsHandle = false;
    if (util_diff_napi_type(env, argv[0], napi_boolean))
    {
        napi_get_value_bool(env, argv[0], &is_WindowsHandle);
    };

    // 获取桌面句柄
    HWND hwnd = GetDesktopWindow();
    int counter = 0;
    hwnd = GetWindow(hwnd, GW_CHILD);
    while (hwnd != NULL)
    {
        if (!is_WindowsHandle)
        {
            status = napi_set_element(env, Results, counter, as_Number((int64_t)hwnd));
            if (status != napi_ok)
                return Results;
            counter++;
        }
        else if (IsWindowVisible(hwnd))
        {
            status = napi_set_element(env, Results, counter, as_Number((int64_t)hwnd));
            if (status != napi_ok)
                return Results;
            counter++;
        }
        hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);
    }

    return Results;
}


// url https://www.codeproject.com/Tips/76427/How-to-Bring-Window-to-Top-with-SetForegroundWindo
void SetForegroundWindowInternal(HWND hWnd)
{
    if (!::IsWindow(hWnd))
        return;

    // relation time of SetForegroundWindow lock
    DWORD lockTimeOut = 0;
    HWND hCurrWnd = ::GetForegroundWindow();
    DWORD dwThisTID = ::GetCurrentThreadId(),
          dwCurrTID = ::GetWindowThreadProcessId(hCurrWnd, 0);

    // we need to bypass some limitations from Microsoft :)
    if (dwThisTID != dwCurrTID)
    {
        ::AttachThreadInput(dwThisTID, dwCurrTID, TRUE);

        ::SystemParametersInfo(SPI_GETFOREGROUNDLOCKTIMEOUT, 0, &lockTimeOut, 0);
        ::SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, 0, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);

        ::AllowSetForegroundWindow(ASFW_ANY);
    }

    ::SetForegroundWindow(hWnd);

    if (dwThisTID != dwCurrTID)
    {
        ::SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0,
                               (PVOID)lockTimeOut, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
        ::AttachThreadInput(dwThisTID, dwCurrTID, FALSE);
    }
}


void SetForegroundWindowInternalc(HWND hWnd)
{
    if (!::IsWindow(hWnd))
        return;

    BYTE keyState[256] = {0};
    // to unlock SetForegroundWindow we need to imitate Alt pressing
    if (::GetKeyboardState((LPBYTE)&keyState))
    {
        if (!(keyState[VK_MENU] & 0x80))
        {
            ::keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
        }
    }

    ::SetForegroundWindow(hWnd);

    if (::GetKeyboardState((LPBYTE)&keyState))
    {
        if (!(keyState[VK_MENU] & 0x80))
        {
            ::keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
        }
    }
}

HWND fnSetForegroundWindow_Handle;
void fnSetForegroundWindow()
{
    if (!IsWindow(fnSetForegroundWindow_Handle))
    {
        return;
    }

    BOOL bVisible = IsWindowVisible(fnSetForegroundWindow_Handle);
    if (!bVisible)
    {
        ShowWindow(fnSetForegroundWindow_Handle, SW_SHOW);
    }
    SetWindowPos(fnSetForegroundWindow_Handle, HWND_TOP, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW |
                     (bVisible ? SWP_NOACTIVATE : 0));
    if (!SetForegroundWindow(fnSetForegroundWindow_Handle))
    {
        SetForegroundWindowInternalc(fnSetForegroundWindow_Handle);
    }
    Sleep(300);
    if (GetForegroundWindow() != fnSetForegroundWindow_Handle)
    {
        SetForegroundWindowInternalc(fnSetForegroundWindow_Handle);
    }
    Sleep(300);
    if (GetForegroundWindow() != fnSetForegroundWindow_Handle)
    {
        SetForegroundWindowInternal(fnSetForegroundWindow_Handle);
    }
    fnSetForegroundWindow_Handle = NULL;
}

// 获取所有窗口
napi_value setForegroundWindow(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    napi_value Results = as_Boolean( false);
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
    fnSetForegroundWindow_Handle = (HWND)NumHandle;
    std::thread(fnSetForegroundWindow).detach();
    return NULL;
}

