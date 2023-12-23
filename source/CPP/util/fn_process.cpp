#include "../Mian.hpp";
#include "./hmc_string_util.hpp"
#include "./napi_value_util.hpp";
// #include "./environment.hpp";
// #include "./fmt11.hpp";
#include "./GetProcessCommandLineByPid.hpp";


vector<HMC_PROCESSENTRY32W> GetProcessSnapshot(vector<DWORD> pid_list, bool early_result);
vector<HMC_PROCESSENTRY32W> GetProcessSnapshot(size_t Start, size_t End);

bool ExistProcessID(DWORD processID);
wstring GetProcessIdFilePathW(DWORD processID, bool is_snapshot_match);
wstring GetProcessSnapshotNameW(DWORD processID);
vector<HMC_PROCESSENTRY32W> GetProcessSnapshot();


bool ExistProcessID(DWORD processID)
{
    if (processID == 0 || processID == 4)
    {
        return true;
    }
    HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    // gc
    std::shared_ptr<void> _shared_free_handle(nullptr, [&](void *)
                                              {
        if (hProcess != NULL) {
            ::CloseHandle(hProcess);
        } });

    // win10 + 用PROCESS_QUERY_INFORMATION| PROCESS_VM_READ 打开可能会导致失败 改权获取
    if (hProcess == NULL)
    {
        hProcess = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID);
        if (hProcess == NULL)
        {
            return false;
        }
    }

    // 复核 防止句柄获取异常
    DWORD review_pid = GetProcessId(hProcess);

    if (review_pid == processID)
    {
        return true;
    }

    return false;
}

vector<HMC_PROCESSENTRY32W> GetProcessSnapshot(vector<DWORD> pid_list, bool early_result)
{
    vector<HMC_PROCESSENTRY32W> result = {};

    DWORD PID = 0;
    HANDLE hProcessSnapshot;
    PROCESSENTRY32W PE32;

    // gc
    std::shared_ptr<void> _shared_free_handle(nullptr, [&](void*)
        {
            if (hProcessSnapshot != NULL) {
                ::CloseHandle(hProcessSnapshot);
            } });

    hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (hProcessSnapshot == INVALID_HANDLE_VALUE)
    {
        return result;
    }

    PE32.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(hProcessSnapshot, &PE32))
    {
        return result;
    }

    do
    {
        // 满足要求的数量得结束
        if (early_result && result.size() == pid_list.size())
        {
            return result;
        }

        for (size_t i = 0; i < pid_list.size(); i++)
        {
            if (pid_list[i] == PE32.th32ProcessID)
            {
                HMC_PROCESSENTRY32W data = HMC_PROCESSENTRY32W{
                    PE32.dwSize + 0,
                    PE32.cntUsage + 0,
                    PE32.th32ProcessID + 0,
                    (DWORD)PE32.th32DefaultHeapID + 0,
                    PE32.th32ModuleID + 0,
                    PE32.cntThreads + 0,
                    PE32.th32ParentProcessID + 0,
                    (DWORD)PE32.pcPriClassBase,
                    PE32.dwFlags + 0,
                    wstring(PE32.szExeFile),
                };

                result.push_back(data);
            }
        }

    } while (Process32NextW(hProcessSnapshot, &PE32));

    return result;
}


vector<HMC_PROCESSENTRY32W> GetProcessSnapshot(size_t Start, size_t End)
{
    vector<DWORD> pid_list;
    if (Start >= 0 && End >= Start)
    {
        for (size_t i = Start; i < End; i++)
        {
            pid_list.push_back((DWORD)i);
        }
        return GetProcessSnapshot(pid_list, true);
    }
    return {};
}


wstring GetProcessSnapshotNameW(DWORD processID)
{
    auto GetProcessSnapshotList = GetProcessSnapshot(vector<DWORD>({ processID }), true);
    if (GetProcessSnapshotList.empty())
    {
        return L"";
    }
    else
    {
        return GetProcessSnapshotList[0].szExeFile;
    }
    return L"";
}

wstring GetProcessIdFilePathW(DWORD processID, bool is_snapshot_match)
{

    if (processID == (DWORD)0)
    {
        return L"[System Process]";
    }

    wstring result = wstring();

    HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    // Pwstr
    result.reserve(MAX_PATH);
    result.resize(MAX_PATH);

    // gc
    std::shared_ptr<void> _shared_free_handle(nullptr, [&](void*)
        {
            if (hProcess != NULL) {
                ::CloseHandle(hProcess);
            } });

    // win10 + 用PROCESS_QUERY_INFORMATION| PROCESS_VM_READ 打开可能会导致失败 改权获取
    if (hProcess == NULL)
    {
        hProcess = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID);
        if (hProcess == NULL)
        {
            return wstring();
        }
    }

    DWORD buf_length = ::GetModuleFileNameExW(hProcess, NULL, &result[0], result.size());

    // 没获取到 用模块法
    if (buf_length == 0)
    {

        // 这里获取的不是dos路径
        buf_length = ::GetProcessImageFileNameW(hProcess, &result[0], result.size());
        if (buf_length > 0)
        {
            result.reserve(buf_length);
            result.resize(buf_length);
            return result;
        }
    }

    // 可能是服务
    if (buf_length == 0)
    {
        if (!::QueryFullProcessImageNameW(hProcess, 0, &result[0], &buf_length))
        {
            // 失败 释放string
            buf_length = 0;
            result.clear();
            result.resize(0);
            result.reserve(0);
        }
    }

    result.reserve(buf_length);
    result.resize(buf_length);

    // 处理 dos 路径
    //
    if (!result.empty() && result.front() == '\\')
    {
        // vector<util_Volume> volumeList = util_getVolumeList();

        // for (size_t i = 0; i < volumeList.size(); i++)
        // {
        //     util_Volume volume = volumeList[i];
        //     if (result.find(volume.device) == 0)
        //     {
        //         result.replace(0, volume.device.length(), volume.path);
        //     }
        // }
    }

    // 处理 ntoskrnl.exe 不可见问题
    // id 是4 (win内核的i)
    // 系统进程id一般不会
    if (result.empty() && processID < 80)
    {
        vector<HMC_PROCESSENTRY32W> ProcessSnapshotList = GetProcessSnapshot(0, processID + 1);
        DWORD ntoskrnl_pid = 0;

        // 通过特征判断是不是  ntoskrnl.exe
        for (size_t i = 0; i < ProcessSnapshotList.size(); i++)
        {
            auto data = ProcessSnapshotList[i];
            if (ntoskrnl_pid == 0 && data.szExeFile == wstring(L"System"))
            {
                ntoskrnl_pid = data.th32ProcessID;
                if (ntoskrnl_pid == processID)
                {
                    return L"C:\\Windows\\System32\\ntoskrnl.exe";
                }
            }

            if (data.th32ProcessID == processID && ntoskrnl_pid == data.th32ParentProcessID)
            {
                return L"C:\\Windows\\System32\\ntoskrnl.exe";
            }
        }

        // 不是 ntoskrnl.exe 则返回快照名称
        for (size_t i = 0; i < ProcessSnapshotList.size(); i++)
        {
            auto data = ProcessSnapshotList[i];
            if (data.th32ProcessID == processID)
            {
                return data.szExeFile;
            }
        }
    }

    // 没获取到 从进程快照中匹配
    if (result.empty() && is_snapshot_match)
    {
        return GetProcessSnapshotNameW(processID);
    }

    return result;
}


namespace fn_getAllProcessList
{
    NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP;

    wstring GetAllProcessList(bool is_execPath) {

        EnableShutDownPriv();

        DWORD processList[1024], lpcbNeeded;
        if (!EnumProcesses(processList, sizeof(processList), &lpcbNeeded))
        {
            return L"[]";
        }

        wstring jsonValue = L"[";

        int processe_leng = lpcbNeeded / sizeof(DWORD);
        for (int i = 0; i < processe_leng; ++i)
        {
            DWORD pid = processList[i];
            wstring item = wstring(L"{\"pid\":");
            item.append(to_wstring(pid));
            // {"pid":0
            if (is_execPath) {
                item.push_back(L',');
                auto exec_path = GetProcessIdFilePathW(pid, false);
                item.append(hmc_string_util::escapeJsonString(L"path", true));
                item.push_back(L':');
                item.append(hmc_string_util::escapeJsonString(exec_path, true));
                item.push_back(L',');
                // {"pid":0,"path":"...",
                item.append(hmc_string_util::escapeJsonString(L"name", true));
                item.push_back(L':');
                item.append(hmc_string_util::escapeJsonString(hmc_string_util::getPathBaseName(exec_path), true));
                // {"pid":0,"path":"...","name":"..."
            }

            item.push_back(L'}');
            if (i < processe_leng - 1) {
                item.push_back(L',');
            }

            jsonValue.append(item);
        }
        jsonValue.push_back(L']');

        return jsonValue;
    }
    // NEW_PROMISE_FUNCTION_DEFAULT_FUN end
    any PromiseWorkFunc(vector<any> arguments_list)
    {
        any result = GetAllProcessList(arguments_list.size() == 1);
        return result;
    }

    napi_value format_to_js_value(napi_env env, any result_any_data)
    {
        napi_value result;
        napi_get_null(env, &result);

        if (!result_any_data.has_value())
        {
            return result;
        }

        result = hmc_napi_create_value::String(env, any_cast<wstring>(result_any_data));
        return result;
    }
};


vector<HMC_PROCESSENTRY32W> GetProcessSnapshot()
{
    vector<HMC_PROCESSENTRY32W> result = {};

    DWORD PID = 0;
    HANDLE hProcessSnapshot;
    PROCESSENTRY32W PE32;

    // gc
    std::shared_ptr<void> _shared_free_handle(nullptr, [&](void*)
        {
            if (hProcessSnapshot != NULL) {
                ::CloseHandle(hProcessSnapshot);
            } });

    hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (hProcessSnapshot == INVALID_HANDLE_VALUE)
    {
        return result;
    }

    PE32.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(hProcessSnapshot, &PE32))
    {
        return result;
    }

    do
    {

        HMC_PROCESSENTRY32W data = HMC_PROCESSENTRY32W{
            PE32.dwSize + 0,
            PE32.cntUsage + 0,
            PE32.th32ProcessID + 0,
            (DWORD)PE32.th32DefaultHeapID + 0,
            PE32.th32ModuleID + 0,
            PE32.cntThreads + 0,
            PE32.th32ParentProcessID + 0,
            (DWORD)PE32.pcPriClassBase,
            PE32.dwFlags + 0,
            wstring(PE32.szExeFile),
        };

        result.push_back(data);

    } while (Process32NextW(hProcessSnapshot, &PE32));

    return result;
}



// 定义 ZwQuerySystemInformation 函数签名
typedef NTSTATUS(NTAPI* ZwQuerySystemInformation_t)(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);

#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004
#define STATUS_SUCCESS 0x00000000


namespace fn_getAllProcessNtList
{
    NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP;
    // NEW_PROMISE_FUNCTION_DEFAULT_FUN end

    wstring GetAllProcessList() {

        wstring jsonValue = L"[";

        // 加载 ntdll.dll
        HMODULE ntdll = LoadLibraryW(L"ntdll.dll");
        if (ntdll == NULL) {
            return L"[]";
        }
        hmc_shared_close_Library(ntdll);

        // 获取 ZwQuerySystemInformation 函数地址
        ZwQuerySystemInformation_t ZwQuerySystemInformation = (ZwQuerySystemInformation_t)GetProcAddress(ntdll, "NtQuerySystemInformation");
        if (ZwQuerySystemInformation == NULL) {
            return L"[]";
        }

        // 调用 ZwQuerySystemInformation 获取系统信息
        NTSTATUS status;
        ULONG bufferSize = 0;
        status = ZwQuerySystemInformation(SystemProcessInformation, NULL, 0, &bufferSize);
        if (status != STATUS_INFO_LENGTH_MISMATCH) {
            return L"[]";
        }


        PVOID buffer = VirtualAlloc((LPVOID)NULL, (DWORD)(bufferSize), MEM_COMMIT, PAGE_READWRITE);

        hmc_FreeVSAuto(buffer);

        if (buffer == NULL) {
            return L"[]";
        }

        status = ZwQuerySystemInformation(SystemProcessInformation, buffer, bufferSize, NULL);
        if (status != STATUS_SUCCESS) {

            return L"[]";
        }

        // 处理系统信息
        PSYSTEM_PROCESS_INFORMATION processInfo = (PSYSTEM_PROCESS_INFORMATION)buffer;
        while (processInfo->NextEntryOffset) {
            auto ImageName = hmc_string_util::unicodeStringToWString(processInfo->ImageName);

            jsonValue.append(L"{");
            jsonValue.append(hmc_string_util::push_json_value(L"ImageName", ImageName, false, true));
            jsonValue.append(hmc_string_util::push_json_value(L"UniqueProcessId", to_wstring((INT64)processInfo->UniqueProcessId), true, false));
            jsonValue.append(hmc_string_util::push_json_value(L"BasePriority", to_wstring((INT64)processInfo->BasePriority), true, false));
            jsonValue.append(hmc_string_util::push_json_value(L"NextEntryOffset", to_wstring((INT64)processInfo->NextEntryOffset), true, false));
            jsonValue.append(hmc_string_util::push_json_value(L"NumberOfThreads", to_wstring((INT64)processInfo->NumberOfThreads), true, false));
            jsonValue.append(hmc_string_util::push_json_value(L"PeakPagefileUsage", to_wstring((INT64)processInfo->PeakPagefileUsage), true, false));
            jsonValue.append(hmc_string_util::push_json_value(L"PagefileUsage", to_wstring((INT64)processInfo->PagefileUsage), true, false));
            jsonValue.append(hmc_string_util::push_json_value(L"PeakVirtualSize", to_wstring((INT64)processInfo->PeakVirtualSize), true, false));

            jsonValue.append(hmc_string_util::push_json_value(L"PeakWorkingSetSize", to_wstring((INT64)processInfo->PeakWorkingSetSize), true, false));
            jsonValue.append(hmc_string_util::push_json_value(L"QuotaNonPagedPoolUsage", to_wstring((INT64)processInfo->QuotaNonPagedPoolUsage), true, false));
            /* jsonValue.append(hmc_string_util::push_json_value(L"Reserved1", to_wstring((INT64)processInfo->Reserved1), true,false));
             jsonValue.append(hmc_string_util::push_json_value(L"Reserved2", to_wstring((INT64)processInfo->Reserved2), true, false));
             jsonValue.append(hmc_string_util::push_json_value(L"Reserved3", to_wstring((INT64)processInfo->Reserved3), true, false));
             jsonValue.append(hmc_string_util::push_json_value(L"Reserved4", to_wstring((INT64)processInfo->Reserved3), true, false));
             jsonValue.append(hmc_string_util::push_json_value(L"Reserved5", to_wstring((INT64)processInfo->Reserved4), true, false));
             jsonValue.append(hmc_string_util::push_json_value(L"Reserved6", to_wstring((INT64)processInfo->Reserved6), true, false));*/

            jsonValue.append(L"}");
            processInfo = (PSYSTEM_PROCESS_INFORMATION)((PUCHAR)processInfo + processInfo->NextEntryOffset);
            if (processInfo->NextEntryOffset) {
                jsonValue.append(L",");
            }
        }

        jsonValue.append(L"]");
        return jsonValue;
    }

    any PromiseWorkFunc(vector<any> arguments_list)
    {
        any result = GetAllProcessList();
        return result;
    }

    napi_value format_to_js_value(napi_env env, any result_any_data)
    {
        napi_value result;
        napi_get_null(env, &result);

        if (!result_any_data.has_value())
        {
            return result;
        }

        result = hmc_napi_create_value::String(env, any_cast<wstring>(result_any_data));
        return result;
    }
};


namespace fn_getAllProcessSnpList
{
    NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP;

    any PromiseWorkFunc(vector<any> arguments_list)
    {
        wstring result = L"[";

        vector<HMC_PROCESSENTRY32W> ProcessSnapshot_list = GetProcessSnapshot();

        size_t leng = ProcessSnapshot_list.size();
        for (size_t i = 0; i < leng; i++)
        {
            auto data = ProcessSnapshot_list.at(i);
            wstring item = L"{";
            item.append(hmc_string_util::push_json_value(L"szExeFile", data.szExeFile, false, true));
            item.append(hmc_string_util::push_json_value(L"th32ProcessID", to_wstring(data.th32ProcessID), true, false));
            item.append(hmc_string_util::push_json_value(L"th32ParentProcessID", to_wstring(data.th32ParentProcessID), true, false));
            item.append(hmc_string_util::push_json_value(L"cntThreads", to_wstring(data.cntThreads), true, false));
            item.append(hmc_string_util::push_json_value(L"cntUsage", to_wstring(data.cntUsage), true, false));
            item.append(hmc_string_util::push_json_value(L"dwFlags", to_wstring(data.dwFlags), true, false));
            item.append(hmc_string_util::push_json_value(L"dwSize", to_wstring(data.dwSize), true, false));
            item.append(hmc_string_util::push_json_value(L"pcPriClassBase", to_wstring(data.pcPriClassBase), true, false));
            item.append(hmc_string_util::push_json_value(L"th32DefaultHeapID", to_wstring(data.th32DefaultHeapID), true, false));
            item.append(hmc_string_util::push_json_value(L"th32ModuleID", to_wstring(data.th32ModuleID), true, false));

            item.append(L"}");

            if (i < leng - 1) {
                item.push_back(L',');
            }

            result.append(item);
        }

        result.append(L"]");
        return result;
    }

    napi_value format_to_js_value(napi_env env, any result_any_data)
    {
        napi_value result;
        napi_get_null(env, &result);

        if (!result_any_data.has_value())
        {
            return result;
        }

        result = hmc_napi_create_value::String(env, any_cast<wstring>(result_any_data));
        return result;
    }


}


/**
 * @brief 获取CPU核心数
 *
 * @return int
 */
int _hmc_getCPUCount()
{
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    return static_cast<int>(system_info.dwNumberOfProcessors);
}

// 时间格式转换
__int64 _hmc_FileTimeToInt64(const FILETIME& time)
{
    ULARGE_INTEGER tt;
    tt.LowPart = time.dwLowDateTime;
    tt.HighPart = time.dwHighDateTime;
    return (tt.QuadPart);
}

/**
 * @brief 获取指定进程CPU使用率
 *
 * @param ProcessID
 * @return double
 */
double getProcessCpuUsage(DWORD ProcessID)
{
    static int processor_count_ = -1;     // cpu核心数
    static __int64 last_system_time_ = 0; // 上一次的系统时间
    static __int64 last_time_ = 0;        // 上一次的时间

    FILETIME now;
    FILETIME creation_time;
    FILETIME exit_time;
    FILETIME kernel_time;
    FILETIME user_time;

    __int64 system_time;
    __int64 time;

    double cpu_usage = -1;

    if (processor_count_ == -1)
    {
        processor_count_ = _hmc_getCPUCount();
    }

    GetSystemTimeAsFileTime(&now);

    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, ProcessID);

    if (!hProcess)
    {
        return -1;
    }

    if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
        return -1;
    }

    system_time = (_hmc_FileTimeToInt64(kernel_time) + _hmc_FileTimeToInt64(user_time)) / processor_count_; // CPU使用时间
    time = _hmc_FileTimeToInt64(now);                                                                       // 现在的时间

    last_system_time_ = system_time;
    last_time_ = time;

    CloseHandle(hProcess);

    Sleep(1000); // 睡眠1s

    hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, ProcessID);

    if (!hProcess)
    {
        return -1;
    }

    if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
        return -1;
    }

    GetSystemTimeAsFileTime(&now);
    system_time = (_hmc_FileTimeToInt64(kernel_time) + _hmc_FileTimeToInt64(user_time)) / processor_count_; // CPU使用时间
    time = _hmc_FileTimeToInt64(now);                                                                       // 现在的时间

    CloseHandle(hProcess);

    cpu_usage = ((static_cast<double>(system_time - last_system_time_)) / (static_cast<double>(time - last_time_))) * 100;
    return cpu_usage;
}

namespace fn_getProcessCpuUsage
{
    NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP$ARG;

    void format_arguments_value(napi_env env, napi_callback_info info, std::vector<any>& ArgumentsList, hmc_NodeArgsValue args_value) {
        if (!args_value.eq(0, js_number, true)) {
            return;
        }
        ArgumentsList.push_back(args_value.getDword(0));
    }

    any PromiseWorkFunc(vector<any> arguments_list)
    {
        if (arguments_list.empty() || !arguments_list.at(0).has_value() || arguments_list.at(0).type() != typeid(DWORD)) {
            return any();
        }
        return getProcessCpuUsage(any_cast<DWORD>(arguments_list.at(0)));
    }

    napi_value format_to_js_value(napi_env env, any result_any_data)
    {
        napi_value result;
        napi_get_null(env, &result);

        if (!result_any_data.has_value())
        {
            return result;
        }

        result = hmc_napi_create_value::Number(env, any_cast<double>(result_any_data));
        return result;
    }
};

namespace fn_GetProcessIdFilePath
{
    NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP$ARG;

    void format_arguments_value(napi_env env, napi_callback_info info, std::vector<any>& ArgumentsList, hmc_NodeArgsValue args_value) {
        if (!args_value.eq(0, js_number, true)) {
            return;
        }
        ArgumentsList.push_back(args_value.getDword(0));
        //ArgumentsList.push_back(args_value.getBool(1));
    }

    any PromiseWorkFunc(vector<any> arguments_list)
    {
        if (arguments_list.empty() || !arguments_list.at(0).has_value() || arguments_list.at(0).type() != typeid(DWORD)) {
            return any();
        }
        return GetProcessIdFilePathW(any_cast<DWORD>(arguments_list.at(0)), false);
    }

    napi_value format_to_js_value(napi_env env, any result_any_data)
    {
        napi_value result;
        napi_get_null(env, &result);

        if (!result_any_data.has_value())
        {
            return result;
        }

        result = hmc_napi_create_value::String(env, any_cast<wstring>(result_any_data));
        return result;
    }
};

namespace fn_existProcess
{
    NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP$ARG;

    void format_arguments_value(napi_env env, napi_callback_info info, std::vector<any>& ArgumentsList, hmc_NodeArgsValue args_value) {
        if (!args_value.eq(0, js_number, true)) {
            return;
        }
        ArgumentsList.push_back(args_value.getDword(0));
        //ArgumentsList.push_back(args_value.getBool(1));
    }

    any PromiseWorkFunc(vector<any> arguments_list)
    {
        if (arguments_list.empty() || !arguments_list.at(0).has_value() || arguments_list.at(0).type() != typeid(DWORD)) {
            return any();
        }
        return ExistProcessID(any_cast<DWORD>(arguments_list.at(0)));
    }

    napi_value format_to_js_value(napi_env env, any result_any_data)
    {
        napi_value result;
        napi_get_null(env, &result);

        if (!result_any_data.has_value())
        {
            return result;
        }

        result = hmc_napi_create_value::Boolean(env, any_cast<bool>(result_any_data));
        return result;
    }
};

namespace fn_GetProcessCommandLineByPid
{
    NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP$ARG;

    void format_arguments_value(napi_env env, napi_callback_info info, std::vector<any>& ArgumentsList, hmc_NodeArgsValue args_value) {
        if (!args_value.eq(0, js_number, true)) {
            return;
        }
        ArgumentsList.push_back(args_value.getDword(0));
        //ArgumentsList.push_back(args_value.getBool(1));
    }

    any PromiseWorkFunc(vector<any> arguments_list)
    {
        if (arguments_list.empty() || !arguments_list.at(0).has_value() || arguments_list.at(0).type() != typeid(DWORD)) {
            return any();
        }

        long status2 = -1;
        wstring result = GetProcessCommandLineByPid(any_cast<DWORD>(arguments_list.at(0)),&status2);
        
        if (status2 != 0)
        {
            return any();
        }

        return any(result);

    }

    napi_value format_to_js_value(napi_env env, any result_any_data)
    {
        napi_value result;
        napi_get_null(env, &result);

        if (!result_any_data.has_value())
        {
            return result;
        }

        result = hmc_napi_create_value::String(env, any_cast<wstring>(result_any_data));
        return result;
    }
};

namespace fn_GetCurrentWorkingDirectory
{
    NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP$ARG;

    void format_arguments_value(napi_env env, napi_callback_info info, std::vector<any>& ArgumentsList, hmc_NodeArgsValue args_value) {
        if (!args_value.eq(0, js_number, true)) {
            return;
        }
        ArgumentsList.push_back(args_value.getDword(0));
        //ArgumentsList.push_back(args_value.getBool(1));
    }

    any PromiseWorkFunc(vector<any> arguments_list)
    {
        if (arguments_list.empty() || !arguments_list.at(0).has_value() || arguments_list.at(0).type() != typeid(DWORD)) {
            return any();
        }

        wstring result = GetCurrentWorkingDirectory(any_cast<DWORD>(arguments_list.at(0)));
        
        return any(result);
    }

    napi_value format_to_js_value(napi_env env, any result_any_data)
    {
        napi_value result;
        napi_get_null(env, &result);

        if (!result_any_data.has_value())
        {
            return result;
        }

        result = hmc_napi_create_value::String(env, any_cast<wstring>(result_any_data));
        return result;
    }
};


void exports_process_all_v2_fun(napi_env env , napi_value exports) {

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

}
