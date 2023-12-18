#include "./Mian.hpp";
void util_getSubProcessList(DWORD ProcessId, vector<DWORD> &SubProcessIDList);
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
            string szFilePathw2a = _W2A_(szFilePath);
            string findStr = "\\\\?\\";
            if (szFilePathw2a.find(findStr) == 0)
            {
                szFilePathw2a.replace(0, findStr.length(), "");
            }
            resultsData.push_back(szFilePathw2a);
        }
        delete[] szFilePath;
        CloseHandle(*it);
    }

    CloseHandle(hProcess);
    return resultsData;
}

// string Attain_getProcessidFilePath(int ProcessID)
// {
//     EnableShutDownPriv();

//     string Run_lpFilename = "";
//     HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
//     char lpFilename[1024];
//     if (hProcess == nullptr)
//     {
//         CloseHandle(hProcess);
//         return Run_lpFilename;
//     }
//     GetModuleFileNameExA(hProcess, NULL, (LPSTR)lpFilename, 1024);
//     CloseHandle(hProcess);
//     return _A2U8_(lpFilename);
// }

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

    vector<string> ModulePathList = util_getModulePathList(ProcessID);
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

vector<DWORD> ListProcessThreads(DWORD dwOwnerPID)
{
    vector<DWORD> ProcessThreadsList = {};
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    // `THREADENTRY32` 是一个结构体，它定义在 `tlhelp32.h` 头文件中。它描述了在系统执行快照时正在执行的线程列表中的条目。以下是 `THREADENTRY32` 结构体中的各个变量的含义：⁴⁵
    // - dwSize：结构体的大小，以字节为单位。
    // - cntUsage：线程使用计数。
    // - th32ThreadID：线程标识符，与 `CreateProcess` 函数返回的线程标识符兼容。
    // - th32OwnerProcessID：创建线程的进程标识符。
    // - tpBasePri：分配给线程的内核基优先级。
    // - tpDeltaPri：线程优先级相对于基本优先级的增量。
    // - dwFlags：保留，不再使用。
    THREADENTRY32 te32;

    // 对所有正在运行的线程进行快照
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE)
        return ProcessThreadsList;

    // 在使用前填写结构的大小。
    te32.dwSize = sizeof(THREADENTRY32);

    // 检索第一个线程的信息、
    // 并在不成功的情况下退出
    if (!Thread32First(hThreadSnap, &te32))
    {
        CloseHandle(hThreadSnap); // 必须清理快照对象
        return ProcessThreadsList;
    }

    // 现在走一下系统的线程列表、
    // 并显示每个线程的信息
    // 与指定进程相关的
    do
    {
        if (te32.th32OwnerProcessID == dwOwnerPID)
        {

            ProcessThreadsList.push_back(te32.th32ThreadID);
        }
    } while (Thread32Next(hThreadSnap, &te32));

    //  不要忘记清理快照对象。
    CloseHandle(hThreadSnap);
    return ProcessThreadsList;
}

struct enumHandleCout
{
    long long handle;
    wstring type;
    wstring name;
    int id;
};
vector<enumHandleCout> resultsEnumHandleList = {};
int EnumHandleQueryID = 0;

//#define NT_SUCCESS(x) ((x) >= 0)
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
    vector<DWORD> ProcessThreadsList = ListProcessThreads(ProcessId);
    vector<DWORD> ProcessIDList = ListProcessThreads(ProcessId);
    vector<util_Volume> volumeList = util_getVolumeList();
    int id = EnumHandleQueryID;
    for (size_t i = 0; i < ProcessThreadsList.size(); i++)
    {
        DWORD ThreadsID = ProcessThreadsList[i];
        enumHandleCout handleCout;
        handleCout.id = id;
        handleCout.handle = 0;
        handleCout.name = to_wstring(ThreadsID);
        handleCout.type = L"Thread";
        resultsEnumHandleList.push_back(handleCout);
    }

    util_getSubProcessList(ProcessId, ProcessIDList);

    for (size_t i = 0; i < ProcessIDList.size(); i++)
    {
        DWORD ThreadsID = ProcessIDList[i];
        enumHandleCout handleCout;
        handleCout.id = id;
        handleCout.handle = 0;
        handleCout.name = to_wstring(ThreadsID);
        handleCout.type = L"Process";
        resultsEnumHandleList.push_back(handleCout);
    }

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
                    handleCout.type = hmc_string_util::unicodeStringToWString(objectTypeInfo->Name);
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

                    handleCout.name = hmc_string_util::unicodeStringToWString(objectName);
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
        if (!handleCout.name.empty() || !handleCout.type.empty())
        {
            // if(handleCout.type ==L"Thread"&&!ProcessThreadsList.empty()){
            //     enumHandleCout PushNewHandleCout ;
            //     PushNewHandleCout.id=id;
            //     PushNewHandleCout.type = L"Thread";
            //     PushNewHandleCout.name = L"";
            //     PushNewHandleCout.handle =0;
            //     DWORD ThreadsPID = ProcessThreadsList.front();
            //     PushNewHandleCout.name = to_wstring(ThreadsPID);
            //     ProcessThreadsList.erase(ProcessThreadsList.begin());
            //     resultsEnumHandleList.push_back(PushNewHandleCout);
            // }
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
        resultsEnumHandleList.erase(begin(resultsEnumHandleList) + index);
    }
    if (push_data_len == 0)
    {
        return NULL;
    }
    return resultsModulePathList;
};

napi_value getProcessThreadList(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    napi_value resultsModulePathList;
    status = napi_create_array(env, &resultsModulePathList);
    hmc_is_argv_type(args, 0, 1, napi_number, resultsModulePathList);

    int64_t ProcessID;
    bool returnDetail = false;
    status = napi_get_value_int64(env, args[0], &ProcessID);
    assert(status == napi_ok);
    int push_data_len = 0;
    if (argc == 2)
    {
        hmc_is_argv_type(args, 1, 2, napi_boolean, resultsModulePathList);
        status = napi_get_value_bool(env, args[1], &returnDetail);
        assert(status == napi_ok);
    }
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    // `THREADENTRY32` 是一个结构体，它定义在 `tlhelp32.h` 头文件中。它描述了在系统执行快照时正在执行的线程列表中的条目。以下是 `THREADENTRY32` 结构体中的各个变量的含义：⁴⁵
    // - dwSize：结构体的大小，以字节为单位。
    // - cntUsage：线程使用计数。
    // - th32ThreadID：线程标识符，与 `CreateProcess` 函数返回的线程标识符兼容。
    // - th32OwnerProcessID：创建线程的进程标识符。
    // - tpBasePri：分配给线程的内核基优先级。
    // - tpDeltaPri：线程优先级相对于基本优先级的增量。
    // - dwFlags：保留，不再使用。
    THREADENTRY32 te32;

    // 对所有正在运行的线程进行快照
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE)
        return resultsModulePathList;

    // 在使用前填写结构的大小。
    te32.dwSize = sizeof(THREADENTRY32);

    // 检索第一个线程的信息、
    // 并在不成功的情况下退出
    if (!Thread32First(hThreadSnap, &te32))
    {
        CloseHandle(hThreadSnap); // 必须清理快照对象
        return resultsModulePathList;
    }

    // 现在走一下系统的线程列表、
    // 并显示每个线程的信息
    // 与指定进程相关的
    do
    {
        if (te32.th32OwnerProcessID == ProcessID)
        {
            if (returnDetail)
            {

                napi_value cur_item;
                status = napi_create_object(env, &cur_item);
                if (status != napi_ok)
                {
                    break;
                    return resultsModulePathList;
                }
                status = napi_set_property(env, cur_item, _create_char_string(env, "cntUsage"), _create_int64_Number(env, te32.cntUsage));
                if (status != napi_ok)
                {
                    return resultsModulePathList;
                }
                status = napi_set_property(env, cur_item, _create_char_string(env, "dwFlags"), _create_int64_Number(env, te32.dwFlags));
                if (status != napi_ok)
                {
                    return resultsModulePathList;
                }
                status = napi_set_property(env, cur_item, _create_char_string(env, "dwSize"), _create_int64_Number(env, te32.dwSize));
                if (status != napi_ok)
                {
                    return resultsModulePathList;
                }
                status = napi_set_property(env, cur_item, _create_char_string(env, "th32OwnerProcessID"), _create_int64_Number(env, te32.th32OwnerProcessID));
                if (status != napi_ok)
                {
                    return resultsModulePathList;
                }
                status = napi_set_property(env, cur_item, _create_char_string(env, "th32ThreadID"), _create_int64_Number(env, te32.th32ThreadID));
                if (status != napi_ok)
                {
                    return resultsModulePathList;
                }
                status = napi_set_property(env, cur_item, _create_char_string(env, "tpBasePri"), _create_int64_Number(env, te32.tpBasePri));
                if (status != napi_ok)
                {
                    return resultsModulePathList;
                }
                status = napi_set_property(env, cur_item, _create_char_string(env, "tpDeltaPri"), _create_int64_Number(env, te32.tpDeltaPri));
                if (status != napi_ok)
                {
                    return resultsModulePathList;
                }
                status = napi_set_element(env, resultsModulePathList, push_data_len, cur_item);
                push_data_len++;
                if (status != napi_ok)
                {
                    return resultsModulePathList;
                }
            }
            else
            {
                status = napi_set_element(env, resultsModulePathList, push_data_len, _create_int64_Number(env, te32.th32ThreadID));
                push_data_len++;
                if (status != napi_ok)
                {
                    return resultsModulePathList;
                }
            }
        }
    } while (Thread32Next(hThreadSnap, &te32));

    //  不要忘记清理快照对象。
    CloseHandle(hThreadSnap);

    return resultsModulePathList;
};

napi_value clearEnumProcessHandle(napi_env env, napi_callback_info info)
{
    resultsEnumHandleList.clear();
    return NULL;
}

#define MAX_KEY_LENGTH 255

vector<HMC_PROCESSENTRY32> enumeratesProcessSnapshotStorage;
int enumeratesProcessPollingId = 0;

void start_enumAllProcess(int pollingId)
{

    EnableShutDownPriv();
    vector<HMC_PROCESSENTRY32> enumProcessList;

    HANDLE hProcessSnap;
    PROCESSENTRY32W pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return;

    pe32.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return;
    }

    do
    {
        HMC_PROCESSENTRY32 _pe32;
        _pe32.cntThreads = pe32.cntThreads;
        _pe32.cntUsage = pe32.cntUsage;
        _pe32.dwFlags = pe32.dwFlags;
        _pe32.dwSize = pe32.dwSize;
        _pe32.pcPriClassBase = pe32.pcPriClassBase;

        _pe32.szExeFile = pe32.szExeFile;
        _pe32.th32DefaultHeapID = pe32.th32DefaultHeapID;
        _pe32.th32ModuleID = pe32.th32ModuleID;
        _pe32.th32ParentProcessID = pe32.th32ParentProcessID;
        _pe32.th32ProcessID = pe32.th32ProcessID;
        _pe32.pollingId = pollingId;
        enumProcessList.push_back(_pe32);

    } while (Process32NextW(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    for (size_t i = 0; i < enumProcessList.size(); i++)
    {
        HMC_PROCESSENTRY32 p32 = enumProcessList[i];
        // p32.szExeFile = L"";
        // HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, p32.th32ProcessID);

        // wchar_t processName[MAX_PATH];
        // if (GetModuleBaseNameW(hProcess, NULL, processName, MAX_PATH))
        // {
        //     p32.szExeFile = processName;
        // };
        // CloseHandle(hProcess);
        // enumeratesProcessSnapshotStorage.push_back(p32);

        // Sleep(5);
        enumeratesProcessSnapshotStorage.push_back(p32);
    }

    HMC_PROCESSENTRY32 _p32end;
    _p32end.cntThreads = 0;
    _p32end.cntUsage = 0;
    _p32end.dwFlags = 0;
    _p32end.dwSize = 0;
    _p32end.pcPriClassBase = 0;
    _p32end.szExeFile = L"HMC::endl::";
    _p32end.th32DefaultHeapID = 0;
    _p32end.th32ModuleID = 0;
    _p32end.th32ParentProcessID = 0;
    _p32end.th32ProcessID = 0;
    _p32end.pollingId = pollingId;
    enumeratesProcessSnapshotStorage.push_back(_p32end);
};

void util_getSubProcessList(DWORD ProcessId, vector<DWORD> &SubProcessIDList)
{

    EnableShutDownPriv();
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // 获取进程快照
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE)
    {
        return;
    }

    // 枚举第一个进程
    if (Process32First(hSnap, &pe32))
    {
        do
        {
            // 打开进程句柄
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
            if (hProcess)
            {
                // 子进程的进程 ID
                bool is_sub = pe32.th32ParentProcessID == ProcessId;

                // 二次子进程
                if (!is_sub)
                {
                    if (find(SubProcessIDList.begin(), SubProcessIDList.end(), pe32.th32ParentProcessID) != SubProcessIDList.end())
                    {
                        is_sub = true;
                    }
                }

                if (is_sub)
                {
                    if (!(find(SubProcessIDList.begin(), SubProcessIDList.end(), pe32.th32ProcessID) != SubProcessIDList.end()))
                    {
                        SubProcessIDList.push_back(pe32.th32ProcessID);
                    }
                }
                CloseHandle(hProcess);
            }
        } while (Process32Next(hSnap, &pe32));
    }

    CloseHandle(hSnap);
};

napi_value getSubProcessID(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    napi_value resultsSubProcessIDList;
    status = napi_create_array(env, &resultsSubProcessIDList);
    hmc_is_argv_type(args, 0, 1, napi_number, resultsSubProcessIDList);

    int64_t ProcessID;
    bool returnDetail = false;
    status = napi_get_value_int64(env, args[0], &ProcessID);
    assert(status == napi_ok);
    int push_data_len = 0;

    vector<DWORD> SubProcessIDList = {};
    util_getSubProcessList(ProcessID, SubProcessIDList);
    for (size_t i = 0; i < SubProcessIDList.size(); i++)
    {
        status = napi_set_element(env, resultsSubProcessIDList, push_data_len, _create_int64_Number(env, SubProcessIDList[i]));
        push_data_len++;
        if (status != napi_ok)
        {
            return resultsSubProcessIDList;
        }
    }

    SubProcessIDList.clear();
    return resultsSubProcessIDList;
};

napi_value getProcessParentProcessID(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    hmc_is_argv_type(args, 0, 1, napi_number, NULL);
    int64_t ProcessID;
    status = napi_get_value_int64(env, args[0], &ProcessID);
    assert(status == napi_ok);

    DWORD CurrentProcessId = 0;

    EnableShutDownPriv();
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // 获取进程快照
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE)
    {
        return NULL;
    }

    // 枚举第一个进程
    if (Process32First(hSnap, &pe32))
    {
        do
        {
            // 打开进程句柄
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
            if (hProcess)
            {
                if (pe32.th32ProcessID == ProcessID)
                {
                    CurrentProcessId = pe32.th32ParentProcessID;
                    CloseHandle(hProcess);
                    break;
                }
                CloseHandle(hProcess);
            }
        } while (Process32Next(hSnap, &pe32));
    }

    CloseHandle(hSnap);
    if (CurrentProcessId == 0)
    {
        napi_value result;
        napi_get_null(env, &result);
        return result;
    }
    return _create_int64_Number(env, CurrentProcessId);
};

napi_value clearEnumAllProcessList(napi_env env, napi_callback_info info)
{
    enumeratesProcessSnapshotStorage.clear();
    enumeratesProcessPollingId = 0;
    return NULL;
}

napi_value enumAllProcess(napi_env env, napi_callback_info info)
{
    enumeratesProcessPollingId++;
    thread(start_enumAllProcess, enumeratesProcessPollingId).detach();
    return _create_int32_Number(env, enumeratesProcessPollingId);
};

napi_value enumAllProcessPolling(napi_env env, napi_callback_info info)
{
    if (enumeratesProcessSnapshotStorage.empty())
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

    int QueryID;
    status = napi_get_value_int32(env, args[0], &QueryID);
    assert(status == napi_ok);
    int push_data_len = 0;
    for (size_t index = 0; index < enumeratesProcessSnapshotStorage.size(); index++)
    {
        HMC_PROCESSENTRY32 th32 = enumeratesProcessSnapshotStorage[index];
        if (th32.pollingId != QueryID)
            continue;
        napi_value item;
        status = napi_create_object(env, &item);
        if (status != napi_ok)
        {
            break;
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "szExeFile"), _create_W2U8_string(env, (wchar_t *)th32.szExeFile.c_str()));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "th32ProcessID"), _create_int64_Number(env, th32.th32ProcessID));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "th32ParentProcessID"), _create_int64_Number(env, th32.th32ParentProcessID));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "cntThreads"), _create_int64_Number(env, th32.cntThreads));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "cntUsage"), _create_int64_Number(env, th32.cntUsage));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "dwFlags"), _create_int64_Number(env, th32.dwFlags));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "dwSize"), _create_int64_Number(env, th32.dwSize));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "pcPriClassBase"), _create_int64_Number(env, th32.pcPriClassBase));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "th32DefaultHeapID"), _create_int64_Number(env, th32.th32DefaultHeapID));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "th32ModuleID"), _create_int64_Number(env, th32.th32ModuleID));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "th32ParentProcessID"), _create_int64_Number(env, th32.th32ParentProcessID));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        status = napi_set_property(env, item, _create_char_string(env, "th32ProcessID"), _create_int64_Number(env, th32.th32ProcessID));
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }

        status = napi_set_element(env, resultsModulePathList, (int)index, item);
        push_data_len++;
        if (status != napi_ok)
        {
            return resultsModulePathList;
        }
        enumeratesProcessSnapshotStorage.erase(begin(enumeratesProcessSnapshotStorage) + index);
    }
    if (push_data_len == 0)
    {
        return NULL;
    }
    return resultsModulePathList;
};
