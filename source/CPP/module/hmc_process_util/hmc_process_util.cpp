#include "./hmc_process_util.h"
#include "./hmc_string_util.h"

hmc_process_util::ch_PROCESSENTRY32W::ch_PROCESSENTRY32W()
{
    dwSize = 0;              // 结构体的大小，以字节为单位。
    cntUsage = 0;            // 引用计数。
    th32ProcessID = 0;       // 进程 ID
    th32DefaultHeapID = 0;   // 默认堆 ID
    th32ModuleID = 0;        // 模块 ID
    cntThreads = 0;          // 线程计数器。
    th32ParentProcessID = 0; // 父进程 ID。
    pcPriClassBase = 0;      // 基本优先级。
    dwFlags = 0;             // 标志位。
    szExeFile = L"";         // 进程名。
}

hmc_process_util::ch_PROCESSENTRY32W::ch_PROCESSENTRY32W(PROCESSENTRY32W input)
{
    dwSize = input.dwSize;                           // 结构体的大小，以字节为单位。
    cntUsage = input.cntUsage;                       // 引用计数。
    th32ProcessID = input.th32ProcessID;             // 进程 ID
    th32DefaultHeapID = input.th32DefaultHeapID;     // 默认堆 ID
    th32ModuleID = input.th32ModuleID;               // 模块 ID
    cntThreads = input.cntThreads;                   // 线程计数器。
    th32ParentProcessID = input.th32ParentProcessID; // 父进程 ID。
    pcPriClassBase = input.pcPriClassBase;           // 基本优先级。
    dwFlags = input.dwFlags;                         // 标志位。
    szExeFile = std::wstring(input.szExeFile);       // 进程名。
}

std::wstring hmc_process_util::ch_PROCESSENTRY32W::to_json()
{
    std::wstring result = LR"({"szExeFile":"{szExeFile}","th32ProcessID":{th32ProcessID},"th32ParentProcessID":{th32ParentProcessID},"cntThreads":{cntThreads},"cntUsage":{cntUsage},"dwFlags":{dwFlags},"dwSize":{dwSize},"pcPriClassBase":{pcPriClassBase},"th32DefaultHeapID":{th32DefaultHeapID},"th32ModuleID":{th32ModuleID} })";

    result.reserve(result.size() + MAX_PATH + szExeFile.size());

    hmc_string_util::replace(result, L"{szExeFile}", hmc_string_util::escapeJsonString(szExeFile));

    hmc_string_util::replace(result, L"{th32ProcessID}", std::to_wstring(th32ProcessID));
    hmc_string_util::replace(result, L"{th32ParentProcessID}", std::to_wstring(th32ParentProcessID));
    hmc_string_util::replace(result, L"{cntThreads}", std::to_wstring(cntThreads));
    hmc_string_util::replace(result, L"{cntUsage}", std::to_wstring(cntUsage));
    hmc_string_util::replace(result, L"{dwFlags}", std::to_wstring(dwFlags));
    hmc_string_util::replace(result, L"{dwSize}", std::to_wstring(dwSize));
    hmc_string_util::replace(result, L"{pcPriClassBase}", std::to_wstring(pcPriClassBase));
    hmc_string_util::replace(result, L"{th32DefaultHeapID}", std::to_wstring(th32DefaultHeapID));
    hmc_string_util::replace(result, L"{th32ModuleID}", std::to_wstring(th32ModuleID));

    return result;
}

hmc_process_util::OpenProcessToken::~OpenProcessToken()
{
    if (GpHProcess != NULL)
    {
        GpProcessId = 0;
        ::CloseHandle(GpHProcess);
    }
}

hmc_process_util::OpenProcessToken::OpenProcessToken(DWORD ProcessId, bool isEnableShutDownPriv)
{

    if (isEnableShutDownPriv)
    {
        hmc_process_util::EnableShutDownPriv();
    }

    GpHProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessId);

    // win10 + 用PROCESS_QUERY_INFORMATION| PROCESS_VM_READ 打开可能会导致失败 改权获取
    if (GpHProcess == NULL)
    {
        if (isEnableShutDownPriv)
        {
            hmc_process_util::EnableShutDownPriv();
        }

        GpHProcess = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, ProcessId);
        if (GpHProcess == NULL)
        {
            return;
        }
    }

    // 复核 防止句柄获取异常
    DWORD review_pid = GetProcessId(GpHProcess);

    if (review_pid != ProcessId)
    {
        GpHProcess = NULL;
        return;
    }

    GpProcessId = review_pid;
}

hmc_process_util::OpenProcessToken::operator HANDLE() const
{
    return GpHProcess;
}

bool hmc_process_util::OpenProcessToken::operator!() const
{
    return (GpHProcess == NULL);
}

hmc_process_util::OpenProcessToken::operator bool() const
{
    return (GpHProcess != NULL);
}

std::vector<DWORD> hmc_process_util::enumProcessIDList()
{
    DWORD lp_cblength = 4096;
    std::vector<DWORD> processList = {};
    processList.resize(lp_cblength);

    if (!::EnumProcesses(processList.data(), sizeof(DWORD) * lp_cblength, &lp_cblength))
    {
        processList.resize(0);
        return processList;
    }

    processList.resize(lp_cblength / sizeof(DWORD));

    // 去重
    std::unordered_set<DWORD> new_process_ID_List = {};

    size_t count = processList.size();

    for (size_t i = 0; i < count; i++)
    {
        auto &it = processList.at(i);
        new_process_ID_List.insert(it);
    }

    processList.clear();

    // 克隆 取消内存预开劈

    std::vector<DWORD> processList2 = {};

    processList2.reserve(new_process_ID_List.size());

    for (auto &&it : new_process_ID_List)
    {
        processList2.push_back(it);
    }

    return processList2;
}

bool hmc_process_util::existProcessInEnum(DWORD processID)
{

    std::vector<DWORD> processList = enumProcessIDList();

    size_t count = processList.size();

    for (size_t i = 0; i < count; i++)
    {
        auto &it = processList.at(i);
        if (it == processID)
        {
            return true;
        }
    }
    return false;
}

bool hmc_process_util::existProcess(DWORD processID)
{
    if (processID == 0 || processID == 4)
    {
        return true;
    }

    auto process = hmc_process_util::OpenProcessToken(processID);

    if (process)
    {
        return true;
    }

    return false;
}

std::vector<hmc_process_util::ch_PROCESSENTRY32W> hmc_process_util::getProcessSnapshot()
{
    std::vector<ch_PROCESSENTRY32W> result;
    DWORD PID = 0;
    HANDLE hProcessSnapshot;
    PROCESSENTRY32W PE32;
    hmc_shared_close_handle(hProcessSnapshot);

    hProcessSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (hProcessSnapshot == INVALID_HANDLE_VALUE)
    {
        return result;
    }

    PE32.dwSize = sizeof(PROCESSENTRY32W);

    if (!::Process32FirstW(hProcessSnapshot, &PE32))
    {
        return result;
    }

    do
    {

        auto data = hmc_process_util::ch_PROCESSENTRY32W(PE32);
        result.push_back(data);

    } while (::Process32NextW(hProcessSnapshot, &PE32));

    return result;
}

bool hmc_process_util::killProcess(DWORD processID)
{
    auto process = hmc_process_util::OpenProcessToken(processID, true);

    if (!process)
    {
        return false;
    }

    bool isTerminate = ::TerminateProcess(&process, 0);
    return isTerminate;
}

std::vector<DWORD> hmc_process_util::getSubProcess(DWORD processID)
{
    std::vector<DWORD> result;

    const auto tempSnapshotList = getProcessSnapshot();
    const size_t tempSnapshotCount = tempSnapshotList.size();

    for (size_t i = 0; i < tempSnapshotCount; i++)
    {
        const auto &it = tempSnapshotList.at(i);

        if (it.th32ParentProcessID == processID)
        {
            result.push_back(it.th32ProcessID);
        }
    }

    return result;
}

DWORD hmc_process_util::getParentProcess(DWORD processID)
{
    DWORD result = 0;

    WORD PID = 0;
    HANDLE hProcessSnapshot;
    PROCESSENTRY32W PE32;
    hmc_shared_close_handle(hProcessSnapshot);

    hProcessSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (hProcessSnapshot == INVALID_HANDLE_VALUE)
    {
        return result;
    }

    PE32.dwSize = sizeof(PROCESSENTRY32W);

    if (!::Process32FirstW(hProcessSnapshot, &PE32))
    {
        return result;
    }

    do
    {
        if (PE32.th32ProcessID == processID)
        {
            return PE32.th32ParentProcessID;
        }

    } while (::Process32NextW(hProcessSnapshot, &PE32));

    return result;
}

std::vector<hmc_process_util::EnumProcessUserName::PROCESS_INFO> hmc_process_util::EnumProcessUserName::get_list()
{
    return data_list;
}

std::wstring hmc_process_util::EnumProcessUserName::to_json()
{
    std::wstring result = std::wstring(L"[");
    result.reserve(json_temp.size() * data_list.size() + 512);

    for (size_t i = 0; i < data_list.size(); i++)
    {
        auto data = data_list[i];
        auto obj = json_temp + L"";
        obj.reserve(54 + MAX_PATH * 2);

        obj.replace(obj.find(L"{ProcessId}"), sizeof("{ProcessId}") - 1, std::to_wstring((long)data.ProcessId));
        obj.replace(obj.find(L"{SessionId}"), sizeof("{SessionId}") - 1, std::to_wstring((long)data.SessionId));
        obj.replace(obj.find(L"{UserSid}"), sizeof("{UserSid}") - 1, std::to_wstring((long)data.SessionId));

        //.processName
        if (data.ProcessName.empty())
        {
            obj.replace(obj.find(L"\"{ProcessName}\""), sizeof("\"{ProcessName}\"") - 1, L"null");
        }
        else
        {
            obj.replace(obj.find(L"{ProcessName}"), sizeof("{ProcessName}") - 1, hmc_string_util::escapeJsonString(data.ProcessName));
        }

        //.userName
        if (data.UserName.empty())
        {
            obj.replace(obj.find(L"\"{UserName}\""), sizeof("\"{UserName}\"") - 1, L"null");
        }
        else
        {
            obj.replace(obj.find(L"{UserName}"), sizeof("{UserName}") - 1, hmc_string_util::escapeJsonString(data.UserName));
        }

        //.domainName
        if (data.DomainName.empty())
        {
            obj.replace(obj.find(L"\"{DomainName}\""), sizeof("\"{DomainName}\"") - 1, L"null");
        }
        else
        {
            obj.replace(obj.find(L"{DomainName}"), sizeof("{DomainName}") - 1, hmc_string_util::escapeJsonString(data.DomainName));
        }

        result.append(obj);

        if (i < data_list.size() - 1)
        {
            result.push_back(L',');
        }
    }

    result.push_back(L']');
    return result;
}

hmc_process_util::EnumProcessUserName::EnumProcessUserName(bool QueryName)
{
    if (!::IsUserAnAdmin())
        return;
    std::shared_ptr<void> close_pi(nullptr, [&](void *)
                                   {
			if (pi != NULL) {
				::WTSFreeMemory(pi);
				pi = NULL;
			} });

    if (pi != NULL)
    {
        return;
    }

    if (::WTSEnumerateProcessesW(NULL, 0, 1, &pi, &dwCount))
    {
        for (i = 0; i < dwCount; i++)
        {
            auto data = &pi[i];

            auto cchSidNameLeng = DWORD{};
            auto cchSidDomainLeng = DWORD{};
            auto SidNameUse = SidTypeUnknown;

            // 获取成功才动态开辟内存
            auto sidNameBuf = std::wstring();
            auto sidDomainBuf = std::wstring();

            if (QueryName && ::IsValidSid(data->pUserSid))
            {
                cchSidNameLeng = 0;
                cchSidDomainLeng = 0;

                // 开辟最大空间
                sidNameBuf.reserve(MAX_PATH);
                sidDomainBuf.reserve(MAX_PATH);

                ::LookupAccountSidW(nullptr, data->pUserSid, nullptr, &cchSidNameLeng, nullptr, &cchSidDomainLeng, &SidNameUse);

                if (!cchSidNameLeng && !cchSidDomainLeng)
                {
                    goto to_push_null;
                    continue;
                }
                sidNameBuf.clear();
                sidDomainBuf.clear();
                sidNameBuf.resize(cchSidNameLeng);
                sidDomainBuf.resize(cchSidDomainLeng);

                if (!::LookupAccountSidW(nullptr, data->pUserSid, &sidNameBuf[0], &cchSidNameLeng, &sidDomainBuf[0], &cchSidDomainLeng, &SidNameUse))
                {
                    goto to_push_null;
                    continue;
                }

                if (sidDomainBuf.empty())
                {
                    goto to_push_null;
                    continue;
                }

                data_list.push_back(PROCESS_INFO{
                    data->ProcessId,
                    data->SessionId,
                    (long long)data->pUserSid,
                    std::wstring(data->pProcessName),
                    std::wstring(sidNameBuf),
                    std::wstring(sidDomainBuf)});

                continue;
            }

        to_push_null:
            data_list.push_back(PROCESS_INFO{
                data->ProcessId,
                data->SessionId,
                (long long)data->pUserSid,
                std::wstring(data->pProcessName),
                std::wstring(),
                std::wstring()});
        }
    }
}

ULONGLONG hmc_process_util::getProcessStartTime(DWORD processID)
{

    ULONGLONG elapsedTime = 0;

    auto hProcess = hmc_process_util::OpenProcessToken(processID);

    if (!hProcess)
    {
        return elapsedTime;
    }

    FILETIME createTime, exitTime, kernelTime, userTime;
    if (::GetProcessTimes(&hProcess, &createTime, &exitTime, &kernelTime, &userTime))
    {
        ULARGE_INTEGER startTime;
        startTime.LowPart = createTime.dwLowDateTime;
        startTime.HighPart = createTime.dwHighDateTime;

        // 获取当前系统时间
        FILETIME currentTime;
        ::GetSystemTimeAsFileTime(&currentTime);

        ULARGE_INTEGER systemTime;
        systemTime.LowPart = currentTime.dwLowDateTime;
        systemTime.HighPart = currentTime.dwHighDateTime;

        // 计算启动时间（单位为100纳秒）
        ULONGLONG startTime64 = startTime.QuadPart;
        ULONGLONG systemTime64 = systemTime.QuadPart;
        elapsedTime = systemTime64 - startTime64;
    }

    return elapsedTime;
}

hmc_process_util::ch_PSYSTEM_PROCESS_INFORMATION::ch_PSYSTEM_PROCESS_INFORMATION(PSYSTEM_PROCESS_INFORMATION processInfo)
{
    ImageName = hmc_string_util::unicodeStringToWString(processInfo->ImageName);
    UniqueProcessId = (INT64)processInfo->UniqueProcessId;
    BasePriority = (INT64)processInfo->BasePriority;
    NextEntryOffset = (INT64)processInfo->NextEntryOffset;
    NumberOfThreads = (INT64)processInfo->NumberOfThreads;
    PeakPagefileUsage = (INT64)processInfo->PeakPagefileUsage;
    PagefileUsage = (INT64)processInfo->PagefileUsage;
    PeakVirtualSize = (INT64)processInfo->PeakVirtualSize;
    PeakWorkingSetSize = (INT64)processInfo->PeakWorkingSetSize;
    QuotaNonPagedPoolUsage = (INT64)processInfo->QuotaNonPagedPoolUsage;
}

std::wstring hmc_process_util::ch_PSYSTEM_PROCESS_INFORMATION::to_json()
{

    std::wstring result = LR"({"ImageName":"{ImageName}","UniqueProcessId":{UniqueProcessId},"BasePriority":{BasePriority},"NextEntryOffset":{NextEntryOffset},"NumberOfThreads":{NumberOfThreads},"PeakPagefileUsage":{PeakPagefileUsage},"PagefileUsage":{PagefileUsage},"PeakVirtualSize":{PeakVirtualSize},"PeakWorkingSetSize":{PeakWorkingSetSize},"QuotaNonPagedPoolUsage":{QuotaNonPagedPoolUsage}})";
    result.reserve(result.size() + MAX_PATH + ImageName.size());

    hmc_string_util::replace(result, L"{ImageName}", hmc_string_util::escapeJsonString(ImageName));
    hmc_string_util::replace(result, L"{UniqueProcessId}", std::to_wstring(UniqueProcessId));
    hmc_string_util::replace(result, L"{BasePriority}", std::to_wstring(BasePriority));
    hmc_string_util::replace(result, L"{NextEntryOffset}", std::to_wstring(NextEntryOffset));
    hmc_string_util::replace(result, L"{NumberOfThreads}", std::to_wstring(NumberOfThreads));
    hmc_string_util::replace(result, L"{PeakPagefileUsage}", std::to_wstring(PeakPagefileUsage));
    hmc_string_util::replace(result, L"{PagefileUsage}", std::to_wstring(PagefileUsage));
    hmc_string_util::replace(result, L"{PeakVirtualSize}", std::to_wstring(PeakVirtualSize));
    hmc_string_util::replace(result, L"{PeakWorkingSetSize}", std::to_wstring(PeakWorkingSetSize));
    hmc_string_util::replace(result, L"{QuotaNonPagedPoolUsage}", std::to_wstring(QuotaNonPagedPoolUsage));

    return result;
};

std::vector<hmc_process_util::ch_PSYSTEM_PROCESS_INFORMATION> hmc_process_util::getAllProcessNtList()
{

    auto result = std::vector<ch_PSYSTEM_PROCESS_INFORMATION>();

    // 加载 ntdll.dll
    HMODULE ntdll = ::LoadLibraryW(L"ntdll.dll");
    if (ntdll == NULL)
    {
        return result;
    }

    hmc_shared_close_Library(ntdll);

    // 获取 ZwQuerySystemInformation 函数地址
    hmc_define_util::ZwQuerySystemInformation_t ZwQuerySystemInformation = (hmc_define_util::ZwQuerySystemInformation_t)::GetProcAddress(ntdll, "NtQuerySystemInformation");

    if (ZwQuerySystemInformation == NULL)
    {
        return result;
    }

    // 调用 ZwQuerySystemInformation 获取系统信息
    NTSTATUS status;
    ULONG bufferSize = 0;
    status = ZwQuerySystemInformation(SystemProcessInformation, NULL, 0, &bufferSize);

    // 重試
    if (status != STATUS_INFO_LENGTH_MISMATCH || bufferSize == 0)
    {
        status = ZwQuerySystemInformation(SystemProcessInformation, NULL, 0, &bufferSize);
        if (status != STATUS_INFO_LENGTH_MISMATCH || bufferSize == 0)
        {
            return result;
        }
    }

    PVOID buffer = ::VirtualAlloc((LPVOID)NULL, (DWORD)(bufferSize), MEM_COMMIT, PAGE_READWRITE);

    if (buffer == NULL)
    {
        return result;
    }

    hmc_FreeVSAuto(buffer);

    status = ZwQuerySystemInformation(SystemProcessInformation, buffer, bufferSize, NULL);

    if (status != 0x00000000 /*STATUS_SUCCESS*/)
    {

        // 重試
        status = ZwQuerySystemInformation(SystemProcessInformation, buffer, bufferSize, NULL);

        if (status != 0x00000000 /*STATUS_SUCCESS*/)
        {

            return result;
        }
    }

    // 处理系统信息
    PSYSTEM_PROCESS_INFORMATION processInfo = (PSYSTEM_PROCESS_INFORMATION)buffer;

    while (processInfo->NextEntryOffset)
    {
        auto it = ch_PSYSTEM_PROCESS_INFORMATION(processInfo);

        result.push_back(it);

        processInfo = (PSYSTEM_PROCESS_INFORMATION)((PUCHAR)processInfo + processInfo->NextEntryOffset);
    }

    return result;
}

bool hmc_process_util::isProcessWow64(DWORD processID)
{
    BOOL bIsWow64 = FALSE;

    auto hPocess = hmc_process_util::OpenProcessToken(processID, true);

    if (!hPocess)
    {
        return false;
    }

    auto fnIsWow64Process = (hmc_define_util::LPFN_ISWOW64PROCESS)::GetProcAddress(::GetModuleHandleW(L"kernel32"), "IsWow64Process");

    if (NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(hPocess, &bIsWow64))
        {
            return false;
        }
    }

    return bIsWow64 ? true : false;
}

bool hmc_process_util::isProcessWow64()
{
    BOOL bIsWow64 = FALSE;

    auto fnIsWow64Process = (hmc_define_util::LPFN_ISWOW64PROCESS)::GetProcAddress(::GetModuleHandleW(L"kernel32"), "IsWow64Process");

    if (NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(::GetCurrentProcess(), &bIsWow64))
        {
            return false;
        }
    }

    return bIsWow64 ? true : false;
}

int hmc_process_util::_hmc_getCPUCount()
{
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    return static_cast<int>(system_info.dwNumberOfProcessors);
}

__int64 hmc_process_util::_hmc_FileTimeToInt64(const FILETIME &time)
{
    ULARGE_INTEGER tt;
    tt.LowPart = time.dwLowDateTime;
    tt.HighPart = time.dwHighDateTime;
    return (tt.QuadPart);
}

double hmc_process_util::getProcessCpuUsage(DWORD processID)
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

    ::GetSystemTimeAsFileTime(&now);

    auto hProcess = hmc_process_util::OpenProcessToken(processID, true);

    if (!hProcess || !::GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
        return -1;
    }

    system_time = (_hmc_FileTimeToInt64(kernel_time) + _hmc_FileTimeToInt64(user_time)) / processor_count_; // CPU使用时间
    time = _hmc_FileTimeToInt64(now);                                                                       // 现在的时间

    last_system_time_ = system_time;
    last_time_ = time;

    ::Sleep(1000); // 睡眠1s

    if (!::GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
        return -1;
    }

    ::GetSystemTimeAsFileTime(&now);

    system_time = (_hmc_FileTimeToInt64(kernel_time) + _hmc_FileTimeToInt64(user_time)) / processor_count_; // CPU使用时间
    time = _hmc_FileTimeToInt64(now);

    cpu_usage = ((static_cast<double>(system_time - last_system_time_)) / (static_cast<double>(time - last_time_))) * 100;
    return cpu_usage;
}



#if HMC_ENABLE_SHUT_DOWN_PRIV_TOKEN == 1

/**
 * @brief 临时提权令牌
 *
 * @return bool
 */
bool hmc_process_util::EnableShutDownPriv()
{
    HANDLE Handle_Token = NULL;
    TOKEN_PRIVILEGES PermissionAttribute = {0};
    // 打开当前程序的权限令牌
    bool is_Open_Process_Token = ::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &Handle_Token);
    if (!is_Open_Process_Token)
    {
        return false;
    }
    // 获得某一特定权限的权限标识LUID 保存到权限属性中
    if (!::LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &PermissionAttribute.Privileges[0].Luid))
    {
        ::CloseHandle(Handle_Token);
        return false;
    }
    PermissionAttribute.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    PermissionAttribute.PrivilegeCount = 1;
    // 提升到系统权限
    if (!::AdjustTokenPrivileges(Handle_Token, FALSE, &PermissionAttribute, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
    {
        ::CloseHandle(Handle_Token);
        return false;
    }
    return true;
}

#else
/**
 * @brief 临时提权令牌
 *
 * @return bool
 */
bool hmc_process_util::EnableShutDownPriv()
{
    return true;
}
#endif // HMC_ENABLE_SHUT_DOWN_PRIV_TOKEN

namespace hmc_process_util
{
    std::wstring hmc_process_util::getProcessFilePath(DWORD processID, bool isEnumListExists = true, bool isService = false, bool isSnapshotName = true)
    {

        std::wstring result = L"";
        result.reserve(MAX_PATH);

        return result;
    }

}
