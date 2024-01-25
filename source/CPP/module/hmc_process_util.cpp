#include "./hmc_process_util.h"
// #include "./hmc_util.h"
#include "./hmc_usb_util.h"
#include "./hmc_util.h"

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
    dwSize = input.dwSize;                                           // 结构体的大小，以字节为单位。
    cntUsage = input.cntUsage;                                       // 引用计数。
    th32ProcessID = input.th32ProcessID;                             // 进程 ID
    th32DefaultHeapID = static_cast<DWORD>(input.th32DefaultHeapID); // 默认堆 ID
    th32ModuleID = input.th32ModuleID;                               // 模块 ID
    cntThreads = input.cntThreads;                                   // 线程计数器。
    th32ParentProcessID = input.th32ParentProcessID;                 // 父进程 ID。
    pcPriClassBase = input.pcPriClassBase;                           // 基本优先级。
    dwFlags = input.dwFlags;                                         // 标志位。
    szExeFile = std::wstring(input.szExeFile);                       // 进程名。
}

std::wstring hmc_process_util::ch_PROCESSENTRY32W::to_json()
{
    std::wstring result = LR"({"szExeFile":"{szExeFile}","th32ProcessID":{th32ProcessID},"th32ParentProcessID":{th32ParentProcessID},"cntThreads":{cntThreads},"cntUsage":{cntUsage},"dwFlags":{dwFlags},"dwSize":{dwSize},"pcPriClassBase":{pcPriClassBase},"th32DefaultHeapID":{th32DefaultHeapID},"th32ModuleID":{th32ModuleID} })";

    result.reserve(result.size() + MAX_PATH + szExeFile.size());

    hmc_util::replace(result, L"{szExeFile}", hmc_util::escapeJsonString(szExeFile));

    hmc_util::replace(result, L"{th32ProcessID}", std::to_wstring(th32ProcessID));
    hmc_util::replace(result, L"{th32ParentProcessID}", std::to_wstring(th32ParentProcessID));
    hmc_util::replace(result, L"{cntThreads}", std::to_wstring(cntThreads));
    hmc_util::replace(result, L"{cntUsage}", std::to_wstring(cntUsage));
    hmc_util::replace(result, L"{dwFlags}", std::to_wstring(dwFlags));
    hmc_util::replace(result, L"{dwSize}", std::to_wstring(dwSize));
    hmc_util::replace(result, L"{pcPriClassBase}", std::to_wstring(pcPriClassBase));
    hmc_util::replace(result, L"{th32DefaultHeapID}", std::to_wstring(th32DefaultHeapID));
    hmc_util::replace(result, L"{th32ModuleID}", std::to_wstring(th32ModuleID));

    return result;
}

hmc_process_util::openProcessToken::~openProcessToken()
{
    if (GpHProcess != NULL)
    {
        GpProcessId = 0;
        ::CloseHandle(GpHProcess);
    }
}

hmc_process_util::openProcessToken::openProcessToken(DWORD ProcessId, bool isEnableShutDownPriv)
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

hmc_process_util::openProcessToken::operator HANDLE() const
{
    return GpHProcess;
}

bool hmc_process_util::openProcessToken::operator!() const
{
    return (GpHProcess == NULL);
}

hmc_process_util::openProcessToken::operator bool() const
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

    auto process = hmc_process_util::openProcessToken(processID);

    if (process)
    {
        return true;
    }

    return false;
}

std::vector<hmc_process_util::ch_PROCESSENTRY32W> hmc_process_util::getProcessSnapshot()
{
    std::vector<ch_PROCESSENTRY32W> result;
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
    auto process = hmc_process_util::openProcessToken(processID, true);

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
            obj.replace(obj.find(L"{ProcessName}"), sizeof("{ProcessName}") - 1, hmc_util::escapeJsonString(data.ProcessName));
        }

        //.userName
        if (data.UserName.empty())
        {
            obj.replace(obj.find(L"\"{UserName}\""), sizeof("\"{UserName}\"") - 1, L"null");
        }
        else
        {
            obj.replace(obj.find(L"{UserName}"), sizeof("{UserName}") - 1, hmc_util::escapeJsonString(data.UserName));
        }

        //.domainName
        if (data.DomainName.empty())
        {
            obj.replace(obj.find(L"\"{DomainName}\""), sizeof("\"{DomainName}\"") - 1, L"null");
        }
        else
        {
            obj.replace(obj.find(L"{DomainName}"), sizeof("{DomainName}") - 1, hmc_util::escapeJsonString(data.DomainName));
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
        for (DWORD i = 0; i < dwCount; i++)
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

    auto hProcess = openProcessToken(processID);

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
    ImageName = hmc_util::unicodeStringToWString(processInfo->ImageName);
    UniqueProcessId = ::GetProcessId(processInfo->UniqueProcessId);
    BasePriority = (DWORD)processInfo->BasePriority;
    NextEntryOffset = (DWORD)processInfo->NextEntryOffset;
    NumberOfThreads = (DWORD)processInfo->NumberOfThreads;
    PeakPagefileUsage = (DWORD)processInfo->PeakPagefileUsage;
    PagefileUsage = (DWORD)processInfo->PagefileUsage;
    PeakVirtualSize = (DWORD)processInfo->PeakVirtualSize;
    PeakWorkingSetSize = (DWORD)processInfo->PeakWorkingSetSize;
    QuotaNonPagedPoolUsage = (DWORD)processInfo->QuotaNonPagedPoolUsage;
}

std::wstring hmc_process_util::ch_PSYSTEM_PROCESS_INFORMATION::to_json()
{

    std::wstring result = LR"({"ImageName":"{ImageName}","UniqueProcessId":{UniqueProcessId},"BasePriority":{BasePriority},"NextEntryOffset":{NextEntryOffset},"NumberOfThreads":{NumberOfThreads},"PeakPagefileUsage":{PeakPagefileUsage},"PagefileUsage":{PagefileUsage},"PeakVirtualSize":{PeakVirtualSize},"PeakWorkingSetSize":{PeakWorkingSetSize},"QuotaNonPagedPoolUsage":{QuotaNonPagedPoolUsage}})";
    result.reserve(result.size() + MAX_PATH + ImageName.size());

    hmc_util::replace(result, L"{ImageName}", hmc_util::escapeJsonString(ImageName));
    hmc_util::replace(result, L"{UniqueProcessId}", std::to_wstring(UniqueProcessId));
    hmc_util::replace(result, L"{BasePriority}", std::to_wstring(BasePriority));
    hmc_util::replace(result, L"{NextEntryOffset}", std::to_wstring(NextEntryOffset));
    hmc_util::replace(result, L"{NumberOfThreads}", std::to_wstring(NumberOfThreads));
    hmc_util::replace(result, L"{PeakPagefileUsage}", std::to_wstring(PeakPagefileUsage));
    hmc_util::replace(result, L"{PagefileUsage}", std::to_wstring(PagefileUsage));
    hmc_util::replace(result, L"{PeakVirtualSize}", std::to_wstring(PeakVirtualSize));
    hmc_util::replace(result, L"{PeakWorkingSetSize}", std::to_wstring(PeakWorkingSetSize));
    hmc_util::replace(result, L"{QuotaNonPagedPoolUsage}", std::to_wstring(QuotaNonPagedPoolUsage));

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

    auto hPocess = hmc_process_util::openProcessToken(processID, true);

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

    auto hProcess = hmc_process_util::openProcessToken(processID, true);

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
bool hmc_process_util::EnableShutDownPriv(DWORD DesiredAccess)
{
    HANDLE Handle_Token = NULL;
    TOKEN_PRIVILEGES PermissionAttribute = {0};
    // 打开当前程序的权限令牌
    bool is_Open_Process_Token = ::OpenProcessToken(::GetCurrentProcess(), DesiredAccess, &Handle_Token);
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

bool hmc_process_util::EnableShutDownPriv()
{
    return EnableShutDownPriv((TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY));
}

#else
bool hmc_process_util::EnableShutDownPriv()
{
    return true;
}
bool hmc_process_util::EnableShutDownPriv(DWORD DesiredAccess)
{
    return true;
}
#endif // HMC_ENABLE_SHUT_DOWN_PRIV_TOKEN

std::wstring hmc_process_util::getProcessNameSnp(DWORD processID)
{

    auto Snapshot = hmc_process_util::getProcessSnapshot();

    size_t count = Snapshot.size();

    for (size_t i = 0; i < count; i++)
    {
        auto it = &Snapshot.at(i);
        if (it->th32ProcessID == processID)
        {
            hmc_util::removeAllCharPtr(it->szExeFile, L'\0');
            it->szExeFile.push_back(L'\0');

            return it->szExeFile;
        }
    }

    return L"";
}

std::wstring hmc_process_util::getProcessNameNt(DWORD processID)
{

    auto Snapshot = hmc_process_util::getAllProcessNtList();

    size_t count = Snapshot.size();

    for (size_t i = 0; i < count; i++)
    {
        auto it = &Snapshot.at(i);
        if (it->UniqueProcessId == processID)
        {
            hmc_util::removeAllCharPtr(it->ImageName, L'\0');
            return it->ImageName;
        }
    }

    return L"";
}

std::wstring hmc_process_util::getProcessName(DWORD processID)
{
    std::wstring result = L"";

    result.resize(MAX_PATH);

    auto hProcess = hmc_process_util::openProcessToken(processID, true);

    if (!hProcess)
    {
        result.clear();
        result.resize(0);
        auto path2 = getProcessFilePath(processID, false, true);

        if (!path2.empty())
        {

            size_t count = path2.size();

            for (size_t i = 0; i < count; i++)
            {
                auto it = path2.at(i);
                if (it == L'\\' || it == L'/')
                {
                    path2.erase(0, i);
                }
            }
            result.append(path2.begin(), path2.end());
        }
        return result;
    }

    DWORD buf_length = ::GetModuleBaseNameW(&hProcess, NULL, &result[0], MAX_PATH);

    if (buf_length != 0)
    {
        result.resize(buf_length);
        return result;
    }

    return L"";
}

std::wstring hmc_process_util::GpGetProcessNameEx(DWORD processID)
{
    std::wstring result = L"";
    result.reserve(MAX_PATH);
    // 没有获取到 从名称获取
    if (result.empty())
    {
        result.append(getProcessNameSnp(processID));
    }

    // 还没有获取到
    if (result.empty())
    {
        result.append(getProcessNameNt(processID));
    }
    return result;
}

std::vector<THREADENTRY32> hmc_process_util::getThreadSnapshot()
{
    std::vector<THREADENTRY32> result;

    HANDLE hProcessSnapshot;
    THREADENTRY32 TE32;

    hmc_shared_close_handle(hProcessSnapshot);

    hProcessSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    if (hProcessSnapshot == INVALID_HANDLE_VALUE)
    {
        return result;
    }

    TE32.dwSize = sizeof(THREADENTRY32);

    if (!::Thread32First(hProcessSnapshot, &TE32))
    {
        return result;
    }

    do
    {
        result.push_back(TE32);

    } while (::Thread32Next(hProcessSnapshot, &TE32));

    return result;
}

std::vector<THREADENTRY32> hmc_process_util::getProcessThreadList(DWORD processID)
{
    std::vector<THREADENTRY32> result;

    const auto tempSnapshotList = getThreadSnapshot();
    const size_t tempSnapshotCount = tempSnapshotList.size();

    for (size_t i = 0; i < tempSnapshotCount; i++)
    {
        const auto &it = tempSnapshotList.at(i);

        if (it.th32OwnerProcessID == processID)
        {
            result.push_back(it);
        }
    }

    return result;
}

std::vector<std::wstring> hmc_process_util::getProcessModuleList(DWORD processID)
{
    std::vector<std::wstring> result = {};

    auto hPocess = hmc_process_util::openProcessToken(processID, true);

    if (!hPocess)
    {
        return result;
    }

    DWORD module_get_bit_size_temp = 0;
    DWORD module_get_bit_size_Ok = 0;

    if (::EnumProcessModules(hPocess, nullptr, 0, &module_get_bit_size_temp))
    {

        std::unique_ptr<HMODULE[]> modules(new HMODULE[module_get_bit_size_temp / sizeof(HMODULE)]);

        if (!EnumProcessModules(hPocess, modules.get(), module_get_bit_size_temp, &module_get_bit_size_Ok))
        {
            return result;
        }

        size_t count = module_get_bit_size_Ok / sizeof(HMODULE);

        for (size_t i = 0; i < count; i++)
        {
            auto &it = modules[i];

            std::wstring module_name = L"";
            module_name.resize(MAX_PATH);

            if (::GetModuleFileNameExW(hPocess,
                                       it,
                                       &module_name[0], MAX_PATH))
            {
                result.push_back(module_name);
            }
        }
    }
    return result;
}

namespace hmc_process_util
{
    std::wstring hmc_process_util::getProcessFilePath(DWORD processID, bool isEnumListExists = true, bool isSnapshotName = true)
    {

        std::wstring result = L"";

        if (isEnumListExists && !existProcessInEnum(processID))
        {
            return result;
        }

        auto hProcess = hmc_process_util::openProcessToken(processID, true);

        if (!hProcess)
        {
            result.clear();
            result.resize(0);

            if (isSnapshotName)
            {
                return GpGetProcessNameEx(processID);
            }

            return result;
        }

        result.resize(MAX_PATH);

        DWORD buf_length = ::GetModuleFileNameExW(&hProcess, NULL, &result[0], static_cast<DWORD>(result.size()));

        if (buf_length == 0)
        {
            // 这里获取的不是dos路径
            buf_length = ::GetProcessImageFileNameW(&hProcess, &result[0], static_cast<DWORD>(result.size()));
            if (buf_length > 0)
            {
                result.resize(buf_length);
                return hmc_usb_util::formatVolumePath(result);
            }
        }

        // 可能是服务
        if (buf_length == 0)
        {
            if (::QueryFullProcessImageNameW(&hProcess, 0, &result[0], &buf_length))
            {
                result.resize(buf_length);
                return hmc_usb_util::formatVolumePath(result);
            }
        }

        hmc_util::removeAllCharPtr(result, L'\0');

        // 返回单名称

        if (isSnapshotName)
        {
            result.clear();
            result.resize(0);

            return GpGetProcessNameEx(processID);
        }

        return result;
    }

}

void hmc_process_util::CpGetProcessCwdPath::initializeNtCall()
{

    if (nt.p_ntdll == NULL)
        nt.p_ntdll = ::GetModuleHandleW(L"ntdll.dll");

    if (nt.close == NULL)
        nt.close = nt_close(::GetProcAddress(nt.p_ntdll, "NtClose"));

    if (nt.openProcess == NULL)
        nt.openProcess = nt_openProcess(::GetProcAddress(nt.p_ntdll, "NtOpenProcess"));

    if (nt.queryInformationProcess == NULL)
        nt.queryInformationProcess = nt_queryInformationProcess(::GetProcAddress(nt.p_ntdll, "NtQueryInformationProcess"));

    if (nt.readVirtualMemory == NULL)
        nt.readVirtualMemory = nt_readVirtualMemory(::GetProcAddress(nt.p_ntdll, "NtReadVirtualMemory"));
}

hmc_process_util::CpGetProcessCwdPath::CpGetProcessCwdPath(DWORD processID)
{
    try
    {

        PWCHAR temp = NULL;

        NTSTATUS status = readCwd(&temp, processID);

        if (!NT_SUCCESS(status))
        {
            return;
        }

        cwdPath.append(temp);
    }
    catch (...)
    {
        return;
    }

    return;
}

std::wstring hmc_process_util::getProcessCwdPath(DWORD processID)
{
    auto temp = CpGetProcessCwdPath(processID);
    return std::wstring(temp.cwdPath.begin(), temp.cwdPath.end());
}

// mit 2.0 https://github.com/Axosoft/get-cwd-of-process
NTSTATUS hmc_process_util::CpGetProcessCwdPath::readCwd(wchar_t **outputString, unsigned long pid)
{
    initializeNtCall();

    HANDLE processHandle = NULL;
    PWCHAR cwdString;
    CLIENT_ID clientId{
        UlongToHandle(pid),
        NULL};
    OBJECT_ATTRIBUTES objectAttributes{
        sizeof(OBJECT_ATTRIBUTES),
        NULL,
        0,
        NULL,
        NULL,
        NULL};
    NTSTATUS status;

    if (!NT_SUCCESS(status = nt.openProcess(
                        &processHandle,
                        PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ,
                        &objectAttributes,
                        &clientId)))
    {
        return status;
    }

    ULONG_PTR wow64;
    if (!NT_SUCCESS(status = nt.queryInformationProcess(
                        processHandle,
                        ProcessWow64Information,
                        &wow64,
                        sizeof(ULONG_PTR),
                        NULL)))
    {
        return status;
    }

    if (!wow64)
    {
        ULONG offset = FIELD_OFFSET(LOCAL_RTL_USER_PROCESS_PARAMETERS, CurrentDirectory);
        PROCESS_BASIC_INFORMATION basicInfo;
        PVOID processParameters;
        if (!NT_SUCCESS(status = nt.queryInformationProcess(
                            processHandle,
                            ProcessBasicInformation,
                            &basicInfo,
                            sizeof(PROCESS_BASIC_INFORMATION),
                            NULL)))
        {
            return status;
        }

        if (!NT_SUCCESS(status = nt.readVirtualMemory(
                            processHandle,
                            PTR_ADD_OFFSET(basicInfo.PebBaseAddress, FIELD_OFFSET(PEB, ProcessParameters)),
                            &processParameters,
                            sizeof(PVOID),
                            NULL)))
        {
            return status;
        }

        UNICODE_STRING initReadString;
        if (!NT_SUCCESS(status = nt.readVirtualMemory(
                            processHandle,
                            PTR_ADD_OFFSET(processParameters, offset),
                            &initReadString,
                            sizeof(UNICODE_STRING),
                            NULL)))
        {
            return status;
        }

        if (initReadString.Length == 0)
        {
            nt.close(processHandle);
            *outputString = new WCHAR[1];
            *outputString[0] = '\0';
            return status;
        }

        size_t strLength = initReadString.Length + 1;
        cwdString = new WCHAR[strLength];
        cwdString[strLength / 2] = 0;
        if (!NT_SUCCESS(status = nt.readVirtualMemory(
                            processHandle,
                            initReadString.Buffer,
                            cwdString,
                            initReadString.Length,
                            NULL)))
        {
            return status;
        }
    }
    else
    {
        ULONG offset = FIELD_OFFSET(LOCAL_RTL_USER_PROCESS_PARAMETERS32, CurrentDirectory);
        PVOID peb32;
        ULONG processParameters32;

        if (!NT_SUCCESS(status = nt.queryInformationProcess(
                            processHandle,
                            ProcessWow64Information,
                            &peb32,
                            sizeof(ULONG_PTR),
                            NULL)))
        {
            return status;
        }

        if (!NT_SUCCESS(status = nt.readVirtualMemory(
                            processHandle,
                            PTR_ADD_OFFSET(peb32, FIELD_OFFSET(PEB32, ProcessParameters)),
                            &processParameters32,
                            sizeof(unsigned long),
                            NULL)))
        {
            return status;
        }

        UNICODE_STRING32 initReadString;
        if (!NT_SUCCESS(status = nt.readVirtualMemory(
                            processHandle,
                            PTR_ADD_OFFSET(processParameters32, offset),
                            &initReadString,
                            sizeof(UNICODE_STRING32),
                            NULL)))
        {
            return status;
        }

        if (initReadString.Length == 0)
        {
            nt.close(processHandle);
            *outputString = new wchar_t[1];
            *outputString[0] = '\0';
            return status;
        }

        size_t strLength = initReadString.Length + 1;
        cwdString = new WCHAR[strLength];
        cwdString[strLength / 2] = 0;
        if (!NT_SUCCESS(status = nt.readVirtualMemory(
                            processHandle,
                            UlongToPtr(initReadString.Buffer),
                            cwdString,
                            initReadString.Length,
                            NULL)))
        {
            return status;
        }
    }

    *outputString = cwdString;
    nt.close(processHandle);
    return status;
}


namespace hmc_process_util
{

    namespace hmc_define_util
    {
        typedef struct _RTL_HEAP_PARAMETERS
        {
            ULONG Length;
            SIZE_T SegmentReserve;
            SIZE_T SegmentCommit;
            SIZE_T DeCommitFreeBlockThreshold;
            SIZE_T DeCommitTotalFreeThreshold;
            SIZE_T MaximumAllocationSize;
            SIZE_T VirtualMemoryThreshold;
            SIZE_T InitialCommit;
            SIZE_T InitialReserve;
            HANDLE CommitRoutine;
            SIZE_T Reserved[2];
        } RTL_HEAP_PARAMETERS, *PRTL_HEAP_PARAMETERS;

        typedef PVOID(NTAPI *_RtlAllocateHeap)(
            _In_ PVOID HeapHandle,
            _In_opt_ ULONG Flags,
            _In_ SIZE_T Size);

        typedef ULONG(NTAPI *_RtlFreeHeap)(
            _In_ PVOID HeapHandle,
            _In_opt_ ULONG Flags,
            _Frees_ptr_opt_ PVOID BaseAddress);

        typedef PVOID(NTAPI *_RtlCreateHeap)(
            _In_ ULONG Flags,
            _In_opt_ PVOID HeapBase,
            _In_opt_ SIZE_T ReserveSize,
            _In_opt_ SIZE_T CommitSize,
            _In_opt_ PVOID Lock,
            _In_opt_ PRTL_HEAP_PARAMETERS Parameters);

        typedef NTSTATUS(NTAPI *_NtQueryInformationProcess)(
            HANDLE ProcessHandle,
            DWORD ProcessInformationClass,
            PVOID ProcessInformation,
            DWORD ProcessInformationLength,
            PDWORD ReturnLength);

        typedef NTSTATUS(NTAPI *_RtlGetVersion)(
            _Out_ PRTL_OSVERSIONINFOEXW VersionInformation // PRTL_OSVERSIONINFOW
        );

        typedef NTSTATUS(NTAPI *_RtlSetHeapInformation)(
            _In_ PVOID HeapHandle,
            _In_ HEAP_INFORMATION_CLASS HeapInformationClass,
            _In_opt_ PVOID HeapInformation,
            _In_opt_ SIZE_T HeapInformationLength);

        BOOLEAN PhHeapInitialization(
            _In_opt_ SIZE_T HeapReserveSize,
            _In_opt_ SIZE_T HeapCommitSize);

        NTSTATUS PhpQueryProcessVariableSize(
            _In_ HANDLE ProcessHandle,
            _In_ _PROCESSINFOCLASS ProcessInformationClass,
            _Out_ PVOID *Buffer);

        PVOID PhHeapHandle = NULL;

        RTL_OSVERSIONINFOEXW PhOsVersion = {0};

#ifndef _INC_VERSIONHELPERS

        inline bool IsWindowsVersionOrGreater(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor)
        {
            OSVERSIONINFOEXW osvi = {sizeof(osvi), 0, 0, 0, 0, {0}, 0, 0};
            DWORDLONG const dwlConditionMask = ::VerSetConditionMask(
                ::VerSetConditionMask(
                    VerSetConditionMask(
                        0, VER_MAJORVERSION, VER_GREATER_EQUAL),
                    VER_MINORVERSION, VER_GREATER_EQUAL),
                VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

            osvi.dwMajorVersion = wMajorVersion;
            osvi.dwMinorVersion = wMinorVersion;
            osvi.wServicePackMajor = wServicePackMajor;

            return ::VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;
        }

#endif

        BOOLEAN PhHeapInitialization(_In_opt_ SIZE_T HeapReserveSize, _In_opt_ SIZE_T HeapCommitSize)
        {

            _RtlSetHeapInformation RtlSetHeapInformation = (_RtlSetHeapInformation)::GetProcAddress(::GetModuleHandleA("ntdll.dll"), "RtlSetHeapInformation");
            _RtlCreateHeap RtlCreateHeap = (_RtlCreateHeap)::GetProcAddress(::GetModuleHandleA("ntdll.dll"), "RtlCreateHeap");

            if (!RtlSetHeapInformation || !RtlCreateHeap)
            {
                return FALSE;
            }

            if (IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINBLUE), 0, 0))
            {
                if (!PhHeapHandle)
                {
                    PhHeapHandle = RtlCreateHeap(
                        HEAP_GROWABLE | HEAP_CREATE_SEGMENT_HEAP | 0x00001000,
                        NULL,
                        0,
                        0,
                        NULL,
                        NULL);
                }
            }

            if (!PhHeapHandle)
            {
                PhHeapHandle = RtlCreateHeap(
                    HEAP_GROWABLE | 0x00001000,
                    NULL,
                    HeapReserveSize ? HeapReserveSize : 2 * 1024 * 1024, // 2 MB
                    HeapCommitSize ? HeapCommitSize : 1024 * 1024,       // 1 MB
                    NULL,
                    NULL);

                if (!PhHeapHandle)
                    return FALSE;

                if (IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), 0, 0))
                {
                    ULONG uTmp = 2UL;
                    RtlSetHeapInformation(
                        PhHeapHandle,
                        HeapCompatibilityInformation,
                        &uTmp,
                        sizeof(ULONG));
                }
            }

            return TRUE;
        }

        _Post_writable_byte_size_(Size)

            NTSTATUS PhpQueryProcessVariableSize(_In_ HANDLE ProcessHandle, _In_ _PROCESSINFOCLASS ProcessInformationClass, _Out_ PVOID *Buffer)
        {
            NTSTATUS status;
            PVOID buffer;
            ULONG returnLength = 0;
            _RtlAllocateHeap RtlAllocateHeap = (_RtlAllocateHeap)::GetProcAddress(::GetModuleHandleA("ntdll.dll"), "RtlAllocateHeap");
            _NtQueryInformationProcess NtQueryInformationProcessEx = (_NtQueryInformationProcess)::GetProcAddress(::GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");

            if (!RtlAllocateHeap || !NtQueryInformationProcessEx)
            {
                return -1;
            }

            status = NtQueryInformationProcessEx(
                ProcessHandle,
                ProcessInformationClass,
                NULL,
                0,
                &returnLength);

            if (
                // STATUS_BUFFER_OVERFLOW
                status != ((NTSTATUS)0xC0000023L) &&
                // STATUS_BUFFER_TOO_SMALL
                status != ((NTSTATUS)0xC0000023L) &&
                // STATUS_INFO_LENGTH_MISMATCH
                status != ((NTSTATUS)0xC0000004L))
                return status;

            buffer = RtlAllocateHeap(PhHeapHandle, HEAP_GENERATE_EXCEPTIONS, returnLength);
            status = NtQueryInformationProcessEx(
                ProcessHandle,
                ProcessInformationClass,
                buffer,
                returnLength,
                &returnLength);

            if (NT_SUCCESS(status))
            {
                *Buffer = buffer;
            }
            else
            {
                _RtlFreeHeap RtlFreeHeap = (_RtlFreeHeap)::GetProcAddress(::GetModuleHandleA("ntdll.dll"), "RtlFreeHeap");

                if (!RtlFreeHeap)
                {
                    return -1;
                }

                RtlFreeHeap(PhHeapHandle, 0, buffer);
            }

            return status;
        }

        PVOID GetPebAddress(HANDLE ProcessHandle)
        {
            PROCESS_BASIC_INFORMATION pbi;
            _NtQueryInformationProcess NtQueryInformationProcessEx = (_NtQueryInformationProcess)::GetProcAddress(::GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
            if (!NtQueryInformationProcessEx)
            {
                return nullptr;
            }

            NtQueryInformationProcessEx(ProcessHandle, 0, &pbi, sizeof(pbi), NULL);

            return pbi.PebBaseAddress;
        }

        std::wstring GetProcessCommandLineNew(_In_ HANDLE ProcessHandle, _Out_ long *status)
        {
            PUNICODE_STRING commandLine;

            if (!NT_SUCCESS(*status = PhpQueryProcessVariableSize(
                                ProcessHandle,
                                (PROCESSINFOCLASS)60,
                                (PVOID *)&commandLine)))
                return L"";

            return std::wstring(commandLine->Buffer, 0,
                                commandLine->Length / sizeof(wchar_t));
        }

        std::wstring GetProcessCommandLineOld(_In_ HANDLE ProcessHandle, _Out_ long *status)
        {
            PVOID pebAddress = GetPebAddress(ProcessHandle);
            PVOID rtlUserProcParamsAddress;
            UNICODE_STRING commandLine;

            if (!ReadProcessMemory(ProcessHandle, (PCHAR)pebAddress + 0x10,
                                   &rtlUserProcParamsAddress, sizeof(PVOID), NULL))
            {
                *status = GetLastError();
                return L"";
            }

            if (!ReadProcessMemory(ProcessHandle, (PCHAR)rtlUserProcParamsAddress + 0x40,
                                   &commandLine, sizeof(commandLine), NULL))
            {
                *status = GetLastError();
                return NULL;
            }

            wchar_t *commandLineContents = new wchar_t[commandLine.Length];

            if (!ReadProcessMemory(ProcessHandle, commandLine.Buffer,
                                   commandLineContents, commandLine.Length, NULL))
            {
                *status = GetLastError();
                return NULL;
            }
            return commandLineContents;
        }
    }

    std::wstring getProcessCommandLine(DWORD pid)
    {
        std::wstring result = L"";

        try
        {
            long status = 0;
            hmc_process_util::EnableShutDownPriv(TOKEN_ADJUST_PRIVILEGES);

            HANDLE ProcessHandle = ::OpenProcess(
                PROCESS_QUERY_INFORMATION | /* required for NtQueryInformationProcess */
                    PROCESS_VM_READ,        /* required for ReadProcessMemory */
                FALSE, pid);

            if (ProcessHandle == NULL)
            {
                return result;
            }

            hmc_shared_close_handle(ProcessHandle);

            hmc_process_util::EnableShutDownPriv(TOKEN_ADJUST_PRIVILEGES);

            if (hmc_define_util::PhHeapHandle == NULL)
            {

                if (!hmc_define_util::PhHeapInitialization(0, 0))
                {
                    status = -1;
                    return result;
                }
            }

            if (hmc_define_util::IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINBLUE), 0, 0))
                return hmc_define_util::GetProcessCommandLineNew(ProcessHandle, &status);

            return hmc_define_util::GetProcessCommandLineOld(ProcessHandle, &status);
        }
        catch (...)
        {
            return result;
        }
        return result;
    }

}

