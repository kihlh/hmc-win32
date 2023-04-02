#include "./Mian.hpp";

vector<string> util_getModulePathList(DWORD processID)
{

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    vector<string> resultsData = {};
    if (hProcess == NULL)
    {
        return resultsData;
    }

    vector<HANDLE> vecFileHandles;

    // 枚举进程打开的文件句柄
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe32))
        {
            do
            {
                if (pe32.th32ProcessID == processID)
                {
                    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
                    if (hModuleSnap != INVALID_HANDLE_VALUE)
                    {
                        MODULEENTRY32 me32;
                        me32.dwSize = sizeof(MODULEENTRY32);
                        if (Module32First(hModuleSnap, &me32))
                        {
                            do
                            {
                                HANDLE hFile = CreateFile(me32.szExePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                                if (hFile != INVALID_HANDLE_VALUE)
                                {
                                    vecFileHandles.push_back(hFile);
                                }
                            } while (Module32Next(hModuleSnap, &me32));
                        }
                        CloseHandle(hModuleSnap);
                    }
                }
            } while (Process32Next(hSnapshot, &pe32));
        }
        CloseHandle(hSnapshot);
    }

    // 输出文件路径
    for (auto it = vecFileHandles.begin(); it != vecFileHandles.end(); ++it)
    {
        LPWSTR szFilePath = new WCHAR[MAX_PATH];
        DWORD dwSize = GetFinalPathNameByHandleW(*it, szFilePath, MAX_PATH, FILE_NAME_NORMALIZED);
        if (dwSize > 0 && dwSize < MAX_PATH)
        {
            resultsData.push_back(_W2A_(szFilePath));
        }
        delete[] szFilePath;
        CloseHandle(*it);
    }

    CloseHandle(hProcess);
    return resultsData;
}

string Attain_getProcessidFilePath(int ProcessID)
{
    string Run_lpFilename = "";
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
    char lpFilename[1024];
    if (hProcess == nullptr)
    {
        CloseHandle(hProcess);
        return Run_lpFilename;
    }
    GetModuleFileNameExA(hProcess, NULL, (LPSTR)lpFilename, 1024);
    CloseHandle(hProcess);
    return _A2U8_(lpFilename);
}

// 枚举进程
vector<DWORD> util_enumProcessesList()
{
    vector<DWORD> AllProcessID = {};
    EnableShutDownPriv();

    DWORD processList[1024], cbNeeded;
    if (!EnumProcesses(processList, sizeof(processList), &cbNeeded))
    {
        return AllProcessID;
    }
    int numProcesses = cbNeeded / sizeof(DWORD);
    for (int i = 0; i < numProcesses; ++i)
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processList[i]);
        if (hProcess)
        {
            AllProcessID.push_back(processList[i]);
            CloseHandle(hProcess);
        }
    }
    return AllProcessID;
}

// 结束进程
napi_value killProcess(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Kill_info;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);

    if (argc)
    {
        int Process_PID;
        status = napi_get_value_int32(env, args[0], &Process_PID);
        assert(status == napi_ok);
        DWORD ProcessID = (DWORD)Process_PID;
        bool Kill_info_bool = false;
        EnableShutDownPriv();
        HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, ProcessID);
        if (killHandle == NULL)
        {
            Kill_info_bool = false;
        }
        else
        {
            bool Terminate_Kill_info_bool = TerminateProcess(killHandle, 0);
            Kill_info_bool = Terminate_Kill_info_bool;
        }
        status = napi_get_boolean(env, Kill_info_bool, &Kill_info);
        assert(status == napi_ok);
    }
    return Kill_info;
}

// 获取进程可执行文件位置
napi_value getProcessidFilePath(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value FilePath;
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

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Process_PID);
    char lpFilename[1024];
    if (hProcess == nullptr)
    {
        napi_get_null(env, &FilePath);
        return FilePath;
    }
    GetModuleFileNameExA(hProcess, NULL, (LPSTR)lpFilename, 1024);
    napi_create_string_utf8(env, _A2U8_(lpFilename).c_str(), NAPI_AUTO_LENGTH, &FilePath);

    CloseHandle(hProcess);

    return FilePath;
}

// 获取带有进程可执行文件的 进程列表(慢25ms) 有一个可忽略参数(快照获取延迟XXms)
napi_value getDetailsProcessList(napi_env env, napi_callback_info info)
{
    napi_status status;
    vector<DWORD> Pid_List;
    vector<string> NameProcessList;
    vector<string> FilePathProcessList;
    napi_value results_napi_Process_ID_List;
    status = napi_create_array(env, &results_napi_Process_ID_List);
    assert(status == napi_ok);
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    bool Set_Sleep = false;
    int Sleep_Number;
    if (argc == 1)
    {
        napi_valuetype valuetype0;
        status = napi_typeof(env, args[0], &valuetype0);
        assert(status == napi_ok);
        if (valuetype0 == napi_number)
        {
            Set_Sleep = true;
            status = napi_get_value_int32(env, args[0], &Sleep_Number);
            assert(status == napi_ok);
        }
    }
    EnableShutDownPriv();

    DWORD processList[1024], cbNeeded;
    if (!EnumProcesses(processList, sizeof(processList), &cbNeeded))
    {
    }
    int numProcesses = cbNeeded / sizeof(DWORD);
    for (int i = 0; i < numProcesses; ++i)
    {
        DWORD processID = processList[i];
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
        if (hProcess)
        {
            // LPSTR lpFilename;
            char Filename[1024];
            char processName[MAX_PATH];
            GetModuleBaseNameA(hProcess, NULL, processName, MAX_PATH);
            GetModuleFileNameExA(hProcess, NULL, Filename, 1024);
            Pid_List.emplace_back(processID);
            NameProcessList.emplace_back(processName);
            FilePathProcessList.emplace_back(string(Filename));
            CloseHandle(hProcess);
        }
    }

    if (Pid_List.size() < 1)
    {
        napi_throw_type_error(env, NULL, "Wrong GetWin32ProcessList size => 0");
    };
    for (unsigned index = 0; index < Pid_List.size(); index++)
    {
        napi_value cur_item, cur_Index, cur_Path, cur_Name, Objcet_key_Name, Objcet_key_Pid, Objcet_key_Path;
        DWORD Index = Pid_List[index];
        string IndexName = NameProcessList[index];
        string FilePath = FilePathProcessList[index];

        status = napi_create_int64(env, Index + 0, &cur_Index);
        status = napi_create_string_utf8(env, _A2U8_(IndexName.c_str()).c_str(), NAPI_AUTO_LENGTH, &cur_Name);
        status = napi_create_string_utf8(env, _A2U8_(FilePath.c_str()).c_str(), NAPI_AUTO_LENGTH, &cur_Path);
        status = napi_create_object(env, &cur_item);
        // {}.name
        string key_Name = "name";
        status = napi_create_string_utf8(env, key_Name.c_str(), NAPI_AUTO_LENGTH, &Objcet_key_Name);
        assert(status == napi_ok);
        // {}.pid
        string key_Process_id = "pid";
        status = napi_create_string_utf8(env, key_Process_id.c_str(), NAPI_AUTO_LENGTH, &Objcet_key_Pid);
        // {}.path
        string key_Process_Path = "path";
        status = napi_create_string_utf8(env, key_Process_Path.c_str(), NAPI_AUTO_LENGTH, &Objcet_key_Path);
        assert(status == napi_ok);
        // {pid:000,name:"123.exe"}
        status = napi_set_property(env, cur_item, Objcet_key_Name, cur_Name);
        status = napi_set_property(env, cur_item, Objcet_key_Pid, cur_Index);
        status = napi_set_property(env, cur_item, Objcet_key_Path, cur_Path);
        assert(status == napi_ok);
        // [].push({pid:000,name:"123.exe"})
        status = napi_set_element(env, results_napi_Process_ID_List, index, cur_item);
        assert(status == napi_ok);
        if (Set_Sleep)
        {
            Sleep(Sleep_Number);
        }
    }

    assert(status == napi_ok);
    return results_napi_Process_ID_List;
}

// 获取带有进程进程列表(10ms)
napi_value getProcessList(napi_env env, napi_callback_info info)
{
    napi_status status;
    vector<DWORD> Pid_List;
    vector<string> NameProcessList;
    napi_value results_napi_Process_ID_List;
    status = napi_create_array(env, &results_napi_Process_ID_List);
    assert(status == napi_ok);
    EnableShutDownPriv();

    DWORD processList[1024], cbNeeded;
    if (!EnumProcesses(processList, sizeof(processList), &cbNeeded))
    {
    }
    int numProcesses = cbNeeded / sizeof(DWORD);
    for (int i = 0; i < numProcesses; ++i)
    {
        DWORD processID = processList[i];
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
        if (hProcess)
        {
            char processName[MAX_PATH];
            GetModuleBaseNameA(hProcess, NULL, processName, MAX_PATH);
            Pid_List.emplace_back(processID);
            NameProcessList.emplace_back(processName);
            CloseHandle(hProcess);
        }
    }

    if (Pid_List.size() < 1)
    {
        napi_throw_type_error(env, NULL, "Wrong GetWin32ProcessList size => 0");
    };
    for (unsigned i = 0; i < Pid_List.size(); i++)
    {
        napi_value cur_item, cur_Index, cur_Name, Objcet_key_Name, Objcet_key_Pid;
        DWORD Index = Pid_List[i];
        string IndexName = NameProcessList[i];
        status = napi_create_int64(env, Index + 0, &cur_Index);
        status = napi_create_string_utf8(env, _A2U8_(IndexName.c_str()).c_str(), NAPI_AUTO_LENGTH, &cur_Name);
        status = napi_create_object(env, &cur_item);
        // {}.name
        string key_Name = "name";
        status = napi_create_string_utf8(env, key_Name.c_str(), NAPI_AUTO_LENGTH, &Objcet_key_Name);
        assert(status == napi_ok);
        // {}.pid
        string key_Process_id = "pid";
        status = napi_create_string_utf8(env, key_Process_id.c_str(), NAPI_AUTO_LENGTH, &Objcet_key_Pid);
        assert(status == napi_ok);
        // {pid:000,name:"123.exe"}
        status = napi_set_property(env, cur_item, Objcet_key_Name, cur_Name);
        status = napi_set_property(env, cur_item, Objcet_key_Pid, cur_Index);
        assert(status == napi_ok);
        // [].push({pid:000,name:"123.exe"})
        status = napi_set_element(env, results_napi_Process_ID_List, i, cur_item);
        assert(status == napi_ok);
    }

    assert(status == napi_ok);
    return results_napi_Process_ID_List;
}

napi_value hasProcess(napi_env env, napi_callback_info info)
{
    napi_status status;
    // napi_value FilePath;
    size_t argc = 1;
    napi_value args[1];
    napi_value napi_TRUE = _create_bool_Boolean(env, TRUE);
    napi_value napi_FALSE = _create_bool_Boolean(env, FALSE);

    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    else
    {
        return napi_FALSE;
    }

    napi_valuetype valuetype0;
    status = napi_typeof(env, args[0], &valuetype0);

    // 开始处理传入的方法
    switch (valuetype0)
    {
        // 传入的如果是pid
    case napi_number:
    {
        int Process_PID;
        status = napi_get_value_int32(env, args[0], &Process_PID);
        if (Process_PID == 0 || Process_PID == 4)
            return napi_TRUE;
        EnableShutDownPriv();
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Process_PID);
        if (GetLastError())
        {
            return napi_FALSE;
        }
        bool hasProcessId = hProcess != NULL;
        if (hasProcessId)
            CloseHandle(hProcess);
        return _create_bool_Boolean(env, hasProcessId);
    }
    // 传入的如果是名称或者路径
    case napi_string:
    {
        string ProcessName = call_String_NAPI_WINAPI_A(env, args[0]);
        if (ProcessName == string(""))
            return napi_FALSE;
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32W entry;
        entry.dwSize = sizeof entry;
        if (Process32FirstW(snap, &entry))
        {
            do
            {
                string ExecFileName = _W2U8_(entry.szExeFile);
                string ExecFile = Attain_getProcessidFilePath(entry.th32ProcessID);
                string AddExt_ProcessName = string("").append(ProcessName).append(".exe");

                if (ProcessName == ExecFileName ||
                    ExecFile == ProcessName ||
                    AddExt_ProcessName == ExecFile ||
                    AddExt_ProcessName == ExecFileName)
                    return napi_TRUE;

            } while (Process32NextW(snap, &entry));
        }
        return napi_FALSE;
    }

    default:
        return napi_FALSE;
    }
}
napi_value isProcess(napi_env env, napi_callback_info info)
{
    return hasProcess(env, info);
}

// 获取pid的名称
napi_value getProcessName(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value FilePath;
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

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Process_PID);
    char lpFilename[1024];
    if (hProcess == nullptr)
    {
        napi_get_null(env, &FilePath);
        return FilePath;
    }
    GetModuleBaseNameA(hProcess, NULL, (LPSTR)lpFilename, 1024);
    napi_create_string_utf8(env, _A2U8_(lpFilename).c_str(), NAPI_AUTO_LENGTH, &FilePath);

    CloseHandle(hProcess);

    return FilePath;
}

// 获取进程可执行文件位置
napi_value getModulePathList(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    napi_value resultsModulePathList;
    status = napi_create_array(env, &resultsModulePathList);

    hmc_is_argv_type(args, 0, 1, napi_number, resultsModulePathList);
    int Process_PID;
    status = napi_get_value_int32(env, args[0], &Process_PID);
    assert(status == napi_ok);
    DWORD ProcessID = (DWORD)Process_PID;

    vector<string> ModulePathList = util_getModulePathList( ProcessID);
    // thread(util_getModulePathList, ProcessID, ModulePathList).join();

    for (size_t i = 0; i < ModulePathList.size(); i++)
    {
        napi_value value = _create_String(env, ModulePathList[i]);
        // push path to Array
        status = napi_set_element(env, resultsModulePathList, i, value);
        if (status != napi_ok)
            return resultsModulePathList;
    }

    return resultsModulePathList;
}

// 获取该文件被哪些流氓进程占用着
// napi_value getLockFileProcessList(napi_env env, napi_callback_info info)
// {
//     napi_status status;
//     size_t argc = 1;
//     napi_value args[1];
//     status = $napi_get_cb_info(argc, args);
//     assert(status == napi_ok);
//     napi_value resultsModulePathList;
//     status = napi_create_array(env, &resultsModulePathList);
//     hmc_is_argv_type(args, 0, 1, napi_string, resultsModulePathList);
//     string strA_Path = call_String_NAPI_WINAPI_A(env, args[0]);

//     return resultsModulePathList;
// }

struct enumHandleCout
{
    long long handle;
    wstring type;
    wstring name;
    int id;
};
vector<enumHandleCout> resultsEnumHandleList = {};
int EnumHandleQueryID = 0;

#define NT_SUCCESS(x) ((x) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

#define SystemHandleInformation 16
#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2

typedef NTSTATUS(NTAPI *NTQUERYSYSTEMINFORMATION)(
    // 检索的信息类型
    ULONG SystemInformationClass,
    // 指向缓冲区的指针 有关系统信息的结构体
    PVOID SystemInformation,
    // 缓冲区的大小
    ULONG SystemInformationLength,
    // 实际返回的信息大小
    PULONG ReturnLength);

typedef NTSTATUS(NTAPI *NTDUPLICATEOBJECT)(
    // 源进程的句柄
    HANDLE SourceProcessHandle,
    // 复制的内核对象的句柄
    HANDLE SourceHandle,
    // 目标进程的句柄
    HANDLE TargetProcessHandle,
    // 目标进程中新对象的指针
    PHANDLE TargetHandle,
    // 新对象的访问权限
    ACCESS_MASK DesiredAccess,
    // 新对象的属性
    ULONG Attributes,
    // 复制操作的选项
    ULONG Options);
typedef NTSTATUS(NTAPI *NTQUERYOBJECT)(
    HANDLE ObjectHandle,
    ULONG ObjectInformationClass,
    PVOID ObjectInformation,
    ULONG ObjectInformationLength,
    PULONG ReturnLength);

typedef struct _SYSTEM_HANDLE
{
    ULONG ProcessId;
    BYTE ObjectTypeNumber;
    BYTE Flags;
    USHORT Handle;
    PVOID Object;
    ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, *PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
    ULONG HandleCount;
    SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef enum _POOL_TYPE
{
    NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed,
    DontUseThisType,
    NonPagedPoolCacheAligned,
    PagedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS
} POOL_TYPE,
    *PPOOL_TYPE;

typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
#ifdef MIDL_PASS
    [ size_is(MaximumLength / 2), length_is((Length) / 2) ] USHORT *Buffer;
#else  // MIDL_PASS
    _Field_size_bytes_part_opt_(MaximumLength, Length) PWCH Buffer;
#endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

wstring unicodeStringToWString(UNICODE_STRING unicodeString)
{
    wstring result;
    if (unicodeString.Buffer)
    {
        result = wstring(unicodeString.Buffer, unicodeString.Length / sizeof(wchar_t));
    }
    return result;
}

typedef struct _OBJECT_TYPE_INFORMATION
{
    // 对象名称。
    UNICODE_STRING Name;
    // 对象的总数。
    ULONG TotalNumberOfObjects;
    // 对象句柄的总数。
    ULONG TotalNumberOfHandles;
    // 对象使用的分页池内存总量。
    ULONG TotalPagedPoolUsage;
    // 对象使用的非分页池内存总量。
    ULONG TotalNonPagedPoolUsage;
    // 对象名称使用的内存总量。
    ULONG TotalNamePoolUsage;
    // 对象句柄表使用的内存总量。
    ULONG TotalHandleTableUsage;
    // 对象的最大数量。
    ULONG HighWaterNumberOfObjects;
    // 对象句柄的最大数量。
    ULONG HighWaterNumberOfHandles;
    // 对象使用的分页池内存的最大值。
    ULONG HighWaterPagedPoolUsage;
    // 对象使用的非分页池内存的最大值。
    ULONG HighWaterNonPagedPoolUsage;
    // 对象名称使用的内存的最大值。
    ULONG HighWaterNamePoolUsage;
    // 对象句柄表使用的内存的最大值。
    ULONG HighWaterHandleTableUsage;
    // 无效属性标志。
    ULONG InvalidAttributes;
    // 通用映射结构体。
    GENERIC_MAPPING GenericMapping;
    // 有效访问标志。
    ULONG ValidAccess;
    // 安全性要求标志。
    BOOLEAN SecurityRequired;
    // 维护句柄计数标志。
    BOOLEAN MaintainHandleCount;
    // 维护类型列表标志。
    USHORT MaintainTypeList;
    // 池类型。
    POOL_TYPE PoolType;
    // 分页池内存使用量。
    ULONG PagedPoolUsage;
    // 非分页池内存使用量。
    ULONG NonPagedPoolUsage;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

void EnumHandleList(DWORD ProcessId)
{
    vector<util_Volume> volumeList = util_getVolumeList();
    int id = EnumHandleQueryID;
    HMODULE hNtMod = LoadLibraryW(L"ntdll.dll");
    if (!hNtMod)
    {
        return;
    }
    NTQUERYSYSTEMINFORMATION NtQuerySystemInformation = (NTQUERYSYSTEMINFORMATION)GetProcAddress(hNtMod, "NtQuerySystemInformation");
    NTDUPLICATEOBJECT NtDuplicateObject = (NTDUPLICATEOBJECT)GetProcAddress(hNtMod, "NtDuplicateObject");
    NTQUERYOBJECT NtQueryObject = (NTQUERYOBJECT)GetProcAddress(hNtMod, "NtQueryObject");

    if (!NtQuerySystemInformation || !NtDuplicateObject || !NtQueryObject)
    {
        return;
    }

    PSYSTEM_HANDLE_INFORMATION handleInfo = NULL;
    HANDLE processHandle;
    ULONG i;
    ULONG neededSize = 0x1000;
    NTSTATUS Status = 0;
    ULONG ReturnLength = 0;
    handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(neededSize);

    if (!handleInfo)
    {
        return;
    }

    // 一直查询 直到成功
    while (STATUS_INFO_LENGTH_MISMATCH == (Status = NtQuerySystemInformation(
                                               SystemHandleInformation,
                                               handleInfo,
                                               neededSize,
                                               &ReturnLength)))
    {
        if (handleInfo)
        {
            free(handleInfo);
            handleInfo = NULL;
        }
        neededSize = ReturnLength;
        handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(neededSize);
        if (!handleInfo)
        {

            return;
        }
    }
    processHandle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, ProcessId);

    for (i = 0; i < handleInfo->HandleCount; i++)
    {
        enumHandleCout handleCout;
        handleCout.id = id;
        handleCout.handle = 0;
        handleCout.name = L"";
        handleCout.type = L"";
        SYSTEM_HANDLE handle = handleInfo->Handles[i];
        if (handle.ProcessId != ProcessId)
        {
            continue;
        }
        handleCout.handle = handle.Handle;
        if (processHandle)
        {
            HANDLE dupHandle = NULL;
            POBJECT_TYPE_INFORMATION objectTypeInfo = NULL;
            PVOID objectNameInfo = NULL;
            UNICODE_STRING objectName = {0};
            ULONG returnLength = 0;

            do
            {
                // 句柄复制失败 就不去获取类型名
                Status = NtDuplicateObject(
                    processHandle,
                    (void *)handle.Handle,
                    GetCurrentProcess(),
                    &dupHandle,
                    0,
                    0,
                    0);
                if (!NT_SUCCESS(Status))
                {
                    break;
                }

                // 获取对象类型名
                ULONG ObjectInformationLength = 0;
                while (STATUS_INFO_LENGTH_MISMATCH == (Status = NtQueryObject(
                                                           dupHandle,
                                                           ObjectTypeInformation,
                                                           objectTypeInfo,
                                                           ObjectInformationLength,
                                                           &returnLength)))
                {
                    if (objectTypeInfo)
                    {
                        free(objectTypeInfo);
                        objectTypeInfo = NULL;
                    }

                    ObjectInformationLength = returnLength;
                    objectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(ObjectInformationLength);
                    if (!objectTypeInfo)
                    {
                        break;
                    }
                }

                // 获取对象类型名成功
                if (NT_SUCCESS(Status))
                {
                    handleCout.type = unicodeStringToWString(objectTypeInfo->Name);
                }
                if (handle.GrantedAccess == 0x0012019f)
                {

                    break;
                }

                // 获取对象名
                ObjectInformationLength = 0;
                returnLength = 0;

                if (STATUS_INFO_LENGTH_MISMATCH == NtQueryObject(
                                                       dupHandle,
                                                       ObjectNameInformation,
                                                       NULL,
                                                       0,
                                                       &returnLength))
                {

                    objectNameInfo = (POBJECT_TYPE_INFORMATION)malloc(returnLength);
                    if (!objectNameInfo)
                    {
                        break;
                    }

                    ZeroMemory(objectNameInfo, returnLength);
                    Status = NtQueryObject(
                        dupHandle,
                        ObjectNameInformation,
                        objectNameInfo,
                        returnLength,
                        NULL);
                }

                // 获取对象名成功
                if (NT_SUCCESS(Status) && ((PUNICODE_STRING)objectNameInfo)->Length > 0)
                {

                    UNICODE_STRING objectName = *(PUNICODE_STRING)objectNameInfo;

                    handleCout.name = unicodeStringToWString(objectName);
                    if (handleCout.type == L"File")
                    {
                        for (size_t i = 0; i < volumeList.size(); i++)
                        {
                            util_Volume volume = volumeList[i];
                            if (handleCout.name.find(volume.device) == 0)
                            {
                                handleCout.name.replace(0, volume.device.length(), volume.path);
                            }
                        }
                    }
                }

            } while (FALSE);

            if (dupHandle)
            {
                CloseHandle(dupHandle);
                dupHandle = NULL;
            }
            if (objectTypeInfo)
            {
                free(objectTypeInfo);
                objectTypeInfo = NULL;
            }
            if (objectNameInfo)
            {
                free(objectNameInfo);
                objectNameInfo = NULL;
            }
        }
        if (!handleCout.name.empty() && !handleCout.type.empty())
        {
            resultsEnumHandleList.push_back(handleCout);
        }
        Sleep(5);
        // wcout << "id" << ":"<< handleCout.id << "   "
        //       << "handle"<< ":" << handleCout.handle << "   "
        //       << "type"<< ":" << handleCout.type << "   "
        //       << "name"<< ":" << handleCout.name << "   " << endl;
    }

    // wcout << "id" << ":"<< id << "   "
    //           << "handle"<< ":" << 0 << "   "
    //           << "type"<< ":" << "hmc::endl::" << "   "
    //           << "name"<< ":" << 0 << "   " << endl;
    enumHandleCout handleCout;
    handleCout.id = id;
    handleCout.handle = 0;
    handleCout.name = L"";
    handleCout.type = L"hmc::endl::";
    resultsEnumHandleList.push_back(handleCout);
    free(handleInfo);
};

napi_value enumProcessHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    napi_value resultsModulePathList;
    status = napi_create_array(env, &resultsModulePathList);

    hmc_is_argv_type(args, 0, 1, napi_number, resultsModulePathList);
    int Process_PID;
    status = napi_get_value_int32(env, args[0], &Process_PID);
    assert(status == napi_ok);
    DWORD ProcessID = (DWORD)Process_PID;
    EnumHandleQueryID++;
    thread(EnumHandleList, ProcessID).detach();

    return _create_int32_Number(env, EnumHandleQueryID);
};

napi_value enumProcessHandlePolling(napi_env env, napi_callback_info info)
{
    if (resultsEnumHandleList.empty())
    {
        return NULL;
    }
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    hmc_is_argv_type(args, 0, 1, napi_number, NULL);

    napi_value resultsModulePathList;
    status = napi_create_array(env, &resultsModulePathList);

    int EnumHandleQueryID;
    status = napi_get_value_int32(env, args[0], &EnumHandleQueryID);
    assert(status == napi_ok);
    int push_data_len = 0;
    for (size_t index = 0; index < resultsEnumHandleList.size(); index++)
    {
        enumHandleCout enumHandle = resultsEnumHandleList[index];
        if (enumHandle.id != EnumHandleQueryID)
            continue;
        napi_value cur_item;
        status = napi_create_object(env, &cur_item);
        if (status != napi_ok)
        {
            break;
            return resultsModulePathList;
        }
        status = napi_set_property(env, cur_item, _create_char_string(env, "name"), _create_W2U8_string(env, (wchar_t *)enumHandle.name.c_str()));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, cur_item, _create_char_string(env, "handle"), _create_int64_Number(env, enumHandle.handle));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, cur_item, _create_char_string(env, "type"), _create_W2U8_string(env, (wchar_t *)enumHandle.type.c_str()));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_element(env, resultsModulePathList, (int)index, cur_item);
        push_data_len++;
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        resultsEnumHandleList.erase(std::begin(resultsEnumHandleList) + index);
    }
    if (push_data_len == 0)
    {
        return NULL;
    }
    return resultsModulePathList;
};
