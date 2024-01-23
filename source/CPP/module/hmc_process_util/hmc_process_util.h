#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_PROCESS_UTIL_H
#define MODE_INTERNAL_INCLUDE_HMC_PROCESS_UTIL_H
#include <memory>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <windows.h>
#include <type_traits>
#include <unordered_set>

#include <Shellapi.h>
#include <process.h>
#include <Tlhelp32.h>
#include <Psapi.h>
#include <winuser.h>
#include <winternl.h>
#include <functional>

#include <WtsApi32.h>
#include <ShlObj_core.h>
#pragma comment(lib, "Wtsapi32.lib")

#define HMC_ENABLE_SHUT_DOWN_PRIV_TOKEN 1

// 预赋值头
namespace hmc_process_util
{

    namespace hmc_define_util
    {
// 自动释放dll
#define hmc_shared_close_Library(hModule) std::shared_ptr<void>##hModule##_shared_close_Library_(nullptr, [&](void *) {if (hModule != NULL) {::FreeLibrary(hModule);} });
// 自动释放文本
#define hmc_shared_close_lpsz(lpwsz) std::shared_ptr<void>##lpwsz##_shared_close_lpsz_(nullptr, [&](void *) {if (lpwsz != NULL) {::GlobalFree(lpwsz);lpwsz = 0; } });
// 释放进程句柄
#define hmc_shared_close_handle(handle) std::shared_ptr<void>##lpwsz##_shared_free_handle(nullptr, [&](void *) {if (handle != NULL) { try{::CloseHandle(handle);}catch(...){}} });

#define None std::nullopt

#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)

        // 定义 ZwQuerySystemInformation 函数签名
        typedef NTSTATUS(NTAPI *ZwQuerySystemInformation_t)(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);
        typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);

    }

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
        ch_PROCESSENTRY32W(PROCESSENTRY32W input);
        /**
         * @brief 转为json
         *
         * @return std::wstring
         */
        std::wstring to_json();
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

        ch_PSYSTEM_PROCESS_INFORMATION(PSYSTEM_PROCESS_INFORMATION processInfo);

        /**
         * @brief 转为json
         *
         * @return std::wstring
         */
        std::wstring to_json();
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
    extern std::wstring getProcessFilePath(DWORD processID, bool isEnumListExists, bool isService, bool isSnapshotName);

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

    class OpenProcessToken
    {
    public:
        /**
         * @brief 打开进程句柄
         *
         * @param ProcessId 进程Id
         * @param isEnableShutDownPriv 是否使用提权令牌
         */
        OpenProcessToken(DWORD ProcessId, bool isEnableShutDownPriv = false);
        ~OpenProcessToken();
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
        PWTS_PROCESS_INFOW pi = {0};
        int i = 0;
        //
        SID_NAME_USE nameuse = SidTypeUser;
        // 数据容器
        std::vector<PROCESS_INFO> data_list = {};
        // json模版
        const std::wstring json_temp = LR"({ "processId":{ProcessId} ,"sessionId":{SessionId} , "userSid":{UserSid} , "processName":"{ProcessName}" , "userName":"{UserName}" , "domainName":"{DomainName}" })";
    };

}

#endif // MODE_INTERNAL_INCLUDE_HMC_PROCESS_UTIL_H
