#include "./Mian.hpp"
#include "./shell_v2.h"
#include "./util/hmc_string_util.hpp"

vector<GetTaryIconList::TaryIcon> GetTaryIconList::getTrayList()
{
    vector<TaryIcon> result = {};

    // win11
    if (::FindWindowW(L"TopLevelWindowForOverflowXamlIsland", NULL))
    {
        return result;
    }

    vector<HWND> hWndList = {GetSystemTrayHwnd(), GetNotifyOverflowTryHwnd()};

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

wstring GetTaryIconList::getTrayListJsonW()
{
    wstring result = L"[";
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
        wstring obj = LR"({ "info":"{info}","path":"{path}","handle":{handle} })";
        obj.reserve(54 + MAX_PATH * 2);

        obj.replace(obj.find(L"{info}"), sizeof("{info}") - 1, hmc_string_util::escapeJsonString(data.title));
        obj.replace(obj.find(L"{path}"), sizeof("{path}") - 1, hmc_string_util::escapeJsonString(data.path));
        obj.replace(obj.find(L"{handle}"), sizeof("{handle}") - 1, to_wstring((long)data.hwnd));

        if (i + 1 < result.size())
        {
            result.push_back(',');
        }

        result.append(obj);
    }

    result.push_back(']');

    return result;
}

// 判断 x64 系统
BOOL GetTaryIconList::IsSystemFor64bit()
{
    SYSTEM_INFO SystemInfo;
    GetNativeSystemInfo(&SystemInfo);
    if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 || SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        return TRUE;
    else
        return FALSE;
}

// 获取折叠托盘窗口句柄
HWND GetTaryIconList::GetNotifyOverflowTryHwnd()
{
    HWND hWnd = ::FindWindowW(L"NotifyIconOverflowWindow", NULL);

    if (hWnd != NULL)
    {
        hWnd = ::FindWindowExW(hWnd, NULL, L"ToolbarWindow32", NULL);
    }

    return hWnd;
}

// 获取托盘窗口句柄
HWND GetTaryIconList::GetSystemTrayHwnd()
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

// 枚举控件句柄
vector<GetTaryIconList::TaryIcon> GetTaryIconList::EnumCommctrlList(HWND hWnd)
{
    vector<TaryIcon> result = {};
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
                VirtualFreeEx(hProcess, Pointer_Icon_Buttons, 0, MEM_RELEASE);
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
        Index_data_Close_Set += 4;
        Index_String_Close_Set += 6;
    }

    // 获取托盘图标个数
    int Tray_Length = 0;
    Tray_Length = ::SendMessage(hWnd, _TB_BUTTONCOUNT, 0, 0);
    if (Tray_Length == 0)
        return result;

    // 遍历托盘
    for (int i = 0; i < Tray_Length; i++)
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

            wstring path = (WCHAR *)Byte_Buffer_Pointer + Index_String_Close_Set;
            wstring title = (WCHAR *)Byte_Buffer_Pointer + Index_String_Close_Set + MAX_PATH;
            long index = Index_Icon_Buttons_id;

            result.push_back(TaryIcon(icon_hwnd, path, title, index));
        }

        Index_Icon_Buttons = 0;
    }

    return result;
}

// 判断 x64 系统
BOOL isSystemFor64bit()
{
    SYSTEM_INFO SystemInfo;
    GetNativeSystemInfo(&SystemInfo);
    if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 || SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        return TRUE;
    else
        return FALSE;
}

int API_TrashFile(std::wstring FromPath, bool bRecycle, bool isShow)
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
            FileOp.fFlags |= FOF_ALLOWUNDO | FOF_NOCONFIRMATION;
        }
    }
    FileOp.pFrom = FromPath.c_str();
    FileOp.pTo = NULL;        // 一定要是NULL
    FileOp.wFunc = FO_DELETE; // 删除操作
    return SHFileOperationW(&FileOp);
}


napi_value TrashFile(napi_env env, napi_callback_info info)
{
    napi_value Results = as_Number32(0x10000);
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    bool isShow = false;
    bool bRecycle = true;
    status = $napi_get_cb_info(argc, argv);
    if (status != napi_ok)
    {
        return Results;
    };
    hmc_is_argc_size(argc, 1, Results);
    hmc_is_argv_type(argv, 0, 1, napi_string, Results);
    // 检索3个参数合法性
    switch (argc)
    {
    case 2:
        hmc_is_argv_type(argv, 1, 2, napi_boolean, Results);
        napi_get_value_bool(env, argv[1], &bRecycle);
        break;
    case 3:
        hmc_is_argv_type(argv, 1, 3, napi_boolean, Results);
        napi_get_value_bool(env, argv[1], &bRecycle);
        napi_get_value_bool(env, argv[2], &isShow);
        break;
    }

    wstring Paths = hmc_napi_get_value::string_wide(env, argv[0]);
    int Info = API_TrashFile(Paths, bRecycle, isShow);
    Results = as_Number32(Info);
    return Results;
}

napi_value createDirSymlink(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value args[2];

    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc <= 2)
    {
        for (size_t i = 0; i < argc; i++)
        {
            napi_valuetype type_value;
            napi_typeof(env, args[i], &type_value);
            if (type_value != napi_string)
            {
                napi_throw_type_error(env, 0, string("The input parameter is not legal and should be string").append("\n\nvalue").append(to_string(i)).append("_type:").append(hmc_napi_type::typeName(type_value)).c_str());
                return NULL;
            }
        }
    }
    else
    {
        napi_throw_type_error(env, 0, string("The number of parameters entered is not legal size =>").append(to_string(argc)).c_str());
        return NULL;
    }

    bool mk_OK = false;
    wstring mapPath = hmc_napi_get_value::string_wide(env, args[0]);
    wstring sourcePath = hmc_napi_get_value::string_wide(env, args[1]);
    mk_OK = CreateSymbolicLinkW(mapPath.c_str(), sourcePath.c_str(), 0x1);
    return as_Boolean(mk_OK);
}

napi_value createSymlink(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value args[2];

    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc <= 2)
    {
        for (size_t i = 0; i < argc; i++)
        {
            napi_valuetype type_value;
            napi_typeof(env, args[i], &type_value);
            if (type_value != napi_string)
            {
                napi_throw_type_error(env, 0, string("The input parameter is not legal and should be string").append("\n\nvalue").append(to_string(i)).append("_type:").append(hmc_napi_type::typeName(type_value)).c_str());
                return NULL;
            }
        }
    }
    else
    {
        napi_throw_type_error(env, 0, string("The number of parameters entered is not legal size =>").append(to_string(argc)).c_str());
        return NULL;
    }

    bool mk_OK = false;
    wstring mapPath = hmc_napi_get_value::string_wide(env, args[0]);
    wstring sourcePath = hmc_napi_get_value::string_wide(env, args[1]);
    mk_OK = CreateSymbolicLinkW(mapPath.c_str(), sourcePath.c_str(), 0x0);
    return as_Boolean(mk_OK);
}

napi_value createHardLink(napi_env env, napi_callback_info info)
{
    napi_status status;
    //    napi_value isOK;
    size_t argc = 2;
    napi_value args[2];

    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc <= 2)
    {
        for (size_t i = 0; i < argc; i++)
        {
            napi_valuetype type_value;
            napi_typeof(env, args[i], &type_value);
            if (type_value != napi_string)
            {
                napi_throw_type_error(env, 0, string("The input parameter is not legal and should be string").append("\n\nvalue").append(to_string(i)).append("_type:").append(hmc_napi_type::typeName(type_value)).c_str());
                return NULL;
            }
        }
    }
    else
    {
        napi_throw_type_error(env, 0, string("The number of parameters entered is not legal size =>").append(to_string(argc)).c_str());
        return NULL;
    }
    bool mk_OK = false;
    wstring mapPath = hmc_napi_get_value::string_utf16(env, args[0]);
    wstring sourcePath = hmc_napi_get_value::string_utf16(env, args[1]);
    mk_OK = CreateHardLinkW(mapPath.c_str(), sourcePath.c_str(), NULL);
    return as_Boolean(mk_OK);
}

