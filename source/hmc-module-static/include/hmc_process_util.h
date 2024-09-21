#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_PROCESS_UTIL_H
#define MODE_INTERNAL_INCLUDE_HMC_PROCESS_UTIL_H

#define HMC_ENABLE_SHUT_DOWN_PRIV_TOKEN 1

#include <vector>
#include <string>
#include <windows.h>
// #include <Tlhelp32.h>
#include <winternl.h>
// #include <WtsApi32.h>

// 预赋值头
namespace hmc_process_util
{

    struct ch_THREADENTRY32
    {
        DWORD dwSize;
        DWORD cntUsage;
        DWORD th32ThreadID;       // this thread
        DWORD th32OwnerProcessID; // Process this thread is associated with
        LONG tpBasePri;
        LONG tpDeltaPri;
        DWORD dwFlags;
        /**
         * @brief 转为json
         *
         * @return std::wstring
         */
        std::wstring to_json();
        static std::wstring to_json(std::vector<ch_THREADENTRY32> data);
    };

    // （进程快照）PROCESSENTRY 结构体  它包含了进程的各种信息，如进程 ID、线程计数器、优先级等等
    struct ch_PROCESSENTRY32W
    {
        DWORD dwSize;              // 结构体的大小，以字节为单位。
        DWORD cntUsage;            // 引用计数。
        DWORD th32ProcessID;       // 进程 ID
        DWORD th32DefaultHeapID;   // 默认堆 ID
        DWORD th32ModuleID;        // 模块 ID
        DWORD cntThreads;          // 线程计数器。
        DWORD th32ParentProcessID; // 父进程 ID。
        DWORD pcPriClassBase;      // 基本优先级。
        DWORD dwFlags;             // 标志位。
        std::wstring szExeFile;    // 进程名。
        ch_PROCESSENTRY32W();
        // ch_PROCESSENTRY32W(PROCESSENTRY32W input);
        /**
         * @brief 转为json
         *
         * @return std::wstring
         */
        std::wstring to_json();

        static std::wstring to_json(std::vector<ch_PROCESSENTRY32W> data);
    };

    struct ch_ProcessHandle
    {
        // 句柄id
        long long handle;
        // 类型
        std::wstring type;
        // 名称(数据)
        std::wstring name;
        int id;
    };

    // （进程内核快照）
    struct ch_PSYSTEM_PROCESS_INFORMATION
    {
        // 下一个结构体实例的偏移量，用于遍历多个结构体。
        DWORD NextEntryOffset;
        // 进程线程数量。
        DWORD NumberOfThreads;
        // 进程的镜像名称
        std::wstring ImageName;
        // 进程的基本优先级。
        DWORD BasePriority;
        // 进程的唯一标识符。(pid)
        DWORD UniqueProcessId;
        // 进程的句柄数。
        DWORD HandleCount;
        // 进程所在的会话 ID。
        DWORD SessionId;
        // 进程的峰值虚拟内存大小。
        DWORD PeakVirtualSize;
        // 进程的虚拟内存大小。
        DWORD VirtualSize;
        // 进程的峰值工作集大小。
        DWORD PeakWorkingSetSize;
        // 进程的实际工作集大小。
        DWORD WorkingSetSize;
        // 分配给进程的分页池配额使用量。
        DWORD QuotaPagedPoolUsage;
        // 分配给进程的非分页池配额使用量。非分页池是内核提供的内存池，用于驻留在物理内存中，并且不会被换出到磁盘页面文件。该字段表示进程当前使用的非分页池内存大小。
        DWORD QuotaNonPagedPoolUsage;
        // 进程的页面文件使用量。页面文件是用于交换进程数据的虚拟内存扩展，当物理内存不足时，部分数据会被交换到页面文件中以释放内存。
        DWORD PagefileUsage;
        // 进程的峰值页面文件使用量。这是进程在其生命周期内达到的最高页面文件使用量。
        DWORD PeakPagefileUsage;
        // 进程的私有页计数。私有页是进程专用的虚拟内存页面，不被其他进程共享。
        DWORD PrivatePageCount;

        ch_PSYSTEM_PROCESS_INFORMATION(void *processInfo);

        /**
         * @brief 转为json
         *
         * @return std::wstring
         */
        std::wstring to_json();

        static std::wstring to_json(std::vector<ch_PSYSTEM_PROCESS_INFORMATION> data);
    };

    struct ch_ProcessEnumItem{
        /**
         * @brief 转为json
         *
         * @return std::wstring
         */
        std::wstring to_json();
        // 进程id
        DWORD pid;
        // 进程的名称
        std::wstring name;
        // 进程路径
        std::wstring path;

        static std::wstring to_json(std::vector<ch_ProcessEnumItem> data);
    };

    /**
     * @brief 判断进程id是否存在
     *
     * @return true
     * @return false
     */
    extern bool existProcess(DWORD ProcessId);

    /**
     * @brief 判断进程id是否存在 (枚举进程列表)
     *
     * @return true
     * @return false
     */
    extern bool existProcessInEnum(DWORD ProcessId);

    /**
     * @brief 枚举进程id列表
     *
     * @return std::vector<DWORD>
     */
    extern std::vector<DWORD> enumProcessIDList();

    /**
     * @brief 获取进程路径
     *
     * @param processID 进程id
     * @param isEnumListExists 必须在进程列表中存在
     * @param isService 如果可能是服务也尽可能获取
     * @param isSnapshotName 如果获取不到请尽可能从内核列表中获取
     * @return std::wstring
     */
    extern std::wstring getProcessFilePath(DWORD processID, bool isEnumListExists, bool isService);

    /**
     * @brief 获取进程名称 快照法
     *
     * @param processID 进程id
     * @return std::wstring
     */
    extern std::wstring getProcessNameSnp(DWORD processID);

    /**
     * @brief 获取进程名称 内核法
     *
     * @param processID 进程id
     * @return std::wstring
     */
    extern std::wstring getProcessNameNt(DWORD processID);

    /**
     * @brief 获取进程名称 尽可能获取
     *
     * @param processID 进程id
     * @return std::wstring
     */
    extern std::wstring getProcessName(DWORD processID);

    /**
     * @brief 获取进程名称 尽可能获取 但是不从文件完整名称获取
     *
     * @param processID 进程id
     * @return std::wstring
     */
    extern std::wstring GpGetProcessNameEx(DWORD processID);

    /**
     * @brief 枚举进程列表(快照)
     *
     * @return std::vector<ch_PROCESSENTRY32W>
     */
    extern std::vector<ch_PROCESSENTRY32W> getProcessSnapshot();

    /**
     * @brief 提权令牌
     *
     * @return true
     * @return false
     */
    extern bool EnableShutDownPriv();

    /**
     * @brief 提权令牌
     *
     * @return true
     * @return false
     */
    extern bool EnableShutDownPriv(DWORD DesiredAccess);

    /**
     * @brief 结束指定进程
     *
     * @param processID
     * @return true
     * @return false
     */
    extern bool killProcess(DWORD processID);

    /**
     * @brief 获取子进程id
     *
     * @param processID
     * @return std::vector<DWORD>
     */
    extern std::vector<DWORD> getSubProcess(DWORD processID);

    /**
     * @brief 获取父进程id
     *
     * @param processID
     * @return DWORD
     */
    extern DWORD getParentProcess(DWORD processID);

    /**
     * @brief 获取指定进程的从启动到现在的时间 单位纳秒(ns)
     *
     * @return long long
     */
    extern ULONGLONG getProcessStartTime(DWORD processID);

    /**
     * @brief 枚舉進程列表 内核法
     *
     * @return std::vector<ch_PSYSTEM_PROCESS_INFORMATION>
     */
    extern std::vector<ch_PSYSTEM_PROCESS_INFORMATION> getAllProcessNtList();
    
    /**
     * @brief 枚舉進程列表 
     * @details wow64 下使用 EnumProcesses 正常模式下使用镜像获取
     *
     * @return std::vector<ch_PSYSTEM_PROCESS_INFORMATION>
     */
    extern std::vector<ch_ProcessEnumItem> getAllProcessList(bool isAppendPath);

    /**
     * @brief 判断进程是否在64位系统下运行32位镜像 `WOW64 是 x86 仿真器`
     *
     * @return true
     * @return false
     */
    extern bool isProcessWow64(DWORD processID);

    /**
     * @brief 判断进程是否在64位系统下运行32位镜像 `WOW64 是 x86 仿真器`
     *
     * @return true
     * @return false
     */
    extern bool isProcessWow64();

    /**
     * @brief 获取CPU核心数
     *
     * @return int
     */
    extern int _hmc_getCPUCount();

    // 时间格式转换
    extern __int64 _hmc_FileTimeToInt64(const FILETIME &time);

    /**
     * @brief 获取指定进程CPU使用率
     *
     * @param ProcessID
     * @return double
     */
    extern double getProcessCpuUsage(DWORD ProcessID);

    /**
     * @brief 枚举进程的线程列表
     *
     * @param processID
     * @return std::vector<THREADENTRY32>
     */
    extern std::vector<ch_THREADENTRY32> getProcessThreadList(DWORD processID);

    /**
     * @brief 枚举线程快照
     *
     * @return std::vector<THREADENTRY32>
     */
    extern std::vector<ch_THREADENTRY32> getThreadSnapshot();

    /**
     * @brief 枚举进程打开的模块路径
     *
     * @return std::vector<std::wstring>
     */
    extern std::vector<std::wstring> getProcessModuleList(DWORD processID);

    /**
     * @brief 获取进程的工作路径
     *
     * @param processID
     * @return std::wstring
     */
    extern std::wstring getProcessCwdPath(DWORD processID);

    /**
     * @brief 获取指定进程的启动命令行
     *
     * @param processID
     * @return std::wstring
     */
    extern std::wstring getProcessCommandLine(DWORD processID);

    /**
     * @brief 将命令行文本转为数组
     *
     * @param commandLine
     * @return std::vector<std::wstring>
     */
    extern std::vector<std::wstring> commandLineToList(std::wstring commandLine);

    /**
     * @brief 尽可能的获取出此可执行文件的工作路径 哪怕他不是正确的
     *
     * @param processID
     * @return std::wstring
     */
    extern std::vector<std::wstring> getExecutableCwdList(DWORD processID);

    class openProcessToken
    {
    public:
        /**
         * @brief 打开进程句柄
         *
         * @param ProcessId 进程Id
         * @param isEnableShutDownPriv 是否使用提权令牌
         */
        openProcessToken(DWORD ProcessId, bool isEnableShutDownPriv = false);
        openProcessToken();
        /**
         * @brief Construct a new open Process Token object
         *
         * @param dwDesiredAccess
         * @param bInheritHandle
         * @param dwProcessId
         */
        openProcessToken(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);

        ~openProcessToken();
        DWORD GpProcessId = NULL;
        HANDLE GpHProcess = NULL;

        // if
        operator bool() const;
        // &
        operator HANDLE() const;
        // !
        bool operator!() const;

    private:
    };

    class EnumProcessUserName
    {
    public:
        /**
         * @brief 枚举进程用户组列表
         *
         * @param QueryName 是否获取用户组名称
         */
        EnumProcessUserName(bool QueryName = true);

        struct PROCESS_INFO
        {
            DWORD ProcessId;          // 唯一标识 RD 会话主机服务器上的进程的进程标识符。
            DWORD SessionId;          // 与进程关联的会话的远程桌面服务会话标识符。
            long long UserSid;        // (不适用) 指向进程的主要访问令牌中的用户 [安全标识符](https://learn.microsoft.com/zh-cn/windows/desktop/SecAuthZ/security-identifiers) 的指针。 有关 SID 和访问令牌的详细信息，请参阅[访问控制](https://learn.microsoft.com/zh-cn/windows/desktop/SecAuthZ/access-control)
            std::wstring ProcessName; // 进程名称
            std::wstring UserName;    // 进程归属的用户的id名称
            std::wstring DomainName;  // 用户名称的域的名称
        };

        std::wstring to_json();
        std::vector<PROCESS_INFO> get_list();

    private:
        DWORD dwCount = 0;
        // 取值指针容器 需要调用WTSFreeMemory释放
        // PWTS_PROCESS_INFOW pi ;

        int i = 0;
        //
        SID_NAME_USE nameuse = SidTypeUser;
        // 数据容器
        std::vector<PROCESS_INFO> data_list = {};
        // json模版
        const std::wstring json_temp = LR"({ "processId":{ProcessId} ,"sessionId":{SessionId} , "userSid":{UserSid} , "processName":"{ProcessName}" , "userName":"{UserName}" , "domainName":"{DomainName}" })";
    };

    class CpGetProcessCwdPath
    {
    private:
        struct CURDIR
        {
            UNICODE_STRING DosPath;
            HANDLE Handle;
        };

        struct LOCAL_RTL_USER_PROCESS_PARAMETERS
        {
            ULONG _1[4];
            HANDLE _2;
            ULONG _3;
            HANDLE _4[3];
            CURDIR CurrentDirectory;
        };

        struct UNICODE_STRING32
        {
            USHORT Length;
            USHORT MaximumLength;
            ULONG Buffer;
        };

        struct CURDIR32
        {
            UNICODE_STRING32 DosPath;
            ULONG Handle;
        };

        struct LOCAL_RTL_USER_PROCESS_PARAMETERS32
        {
            ULONG _1[9];
            CURDIR32 CurrentDirectory;
        };

        struct PEB32
        {
            BOOLEAN _1[4];
            ULONG _2[3];
            ULONG ProcessParameters;
        };

        typedef NTSTATUS(__stdcall *nt_close)(HANDLE);
        typedef NTSTATUS(__stdcall *nt_openProcess)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, CLIENT_ID *);
        typedef NTSTATUS(__stdcall *nt_queryInformationProcess)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, ULONG_PTR);
        typedef NTSTATUS(__stdcall *nt_readVirtualMemory)(HANDLE, PVOID, PVOID, SIZE_T, PSIZE_T);

        struct NtCall
        {
            HMODULE p_ntdll;
            nt_close close;
            nt_openProcess openProcess;
            nt_queryInformationProcess queryInformationProcess;
            nt_readVirtualMemory readVirtualMemory;
        };

        NtCall nt = {nullptr, nullptr, nullptr, nullptr, nullptr};

        void initializeNtCall();
        NTSTATUS readCwd(wchar_t **outputString, unsigned long pid);

    public:
        std::wstring cwdPath;
        CpGetProcessCwdPath(DWORD processID);
    };

    struct LocalFreeDeleter
    {
        inline void operator()(wchar_t **ptr) const { ::LocalFree(ptr); }
    };

    enum emGetNameType
    {
        // 查找所有可能性
        GET_ALL = 1,
        // 使用内核法查找
        GET_NT = 2,
        // 获取进程快照的名字
        GET_SNP = 3,
        // 找到时就停下
        GET_FIND = 5,
        // 找模块名
        GET_MODE = 7,
        // 即便是从可执行文件中路径获取也行
        GET_FILE_NAME = 8
    };

    /**
     * @brief 获取进程所有可能的名称
     * 
     * @param processID 进程id
     * @return std::vector<std::wstring> 
     */
    extern std::vector<std::wstring> getProcessAllName(DWORD ProcessID);
    /**
     * @brief 获取进程名称
     * 
     * @param processID 进程id
     * @param Type 获取类别
     * @return std::wstring 
     */
    extern std::wstring getProcessName(DWORD ProcessID, emGetNameType Type );

}

#endif // MODE_INTERNAL_INCLUDE_HMC_PROCESS_UTIL_H
