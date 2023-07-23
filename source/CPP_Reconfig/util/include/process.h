#include <string>
#include <windows.h>
#include <Psapi.h>
#include <Shellapi.h>
#include <vector>
#include <map>
using namespace std;

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
