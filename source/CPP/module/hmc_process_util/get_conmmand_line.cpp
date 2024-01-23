#include <Windows.h>
#include <winternl.h>
#include <stdio.h>
#include <atlstr.h>
#include <iostream>

#define STATUS_BUFFER_OVERFLOW ((NTSTATUS)0x80000005L)
#define STATUS_BUFFER_TOO_SMALL ((NTSTATUS)0xC0000023L)
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)

#define WINDOWS_ANCIENT 0
#define WINDOWS_XP 51
#define WINDOWS_VISTA 60
#define WINDOWS_7 61
#define WINDOWS_8 62
#define WINDOWS_8_1 63
#define WINDOWS_10 100 // TH1
#define WINDOWS_10_TH2 101
#define WINDOWS_10_RS1 102
#define WINDOWS_10_RS2 103
#define WINDOWS_10_RS3 104
#define WINDOWS_10_RS4 105
#define WINDOWS_10_RS5 106
#define WINDOWS_10_19H1 107
#define WINDOWS_10_19H2 108
#define WINDOWS_10_20H1 109
#define WINDOWS_10_20H2 110
#define WINDOWS_NEW ULONG_MAX

#define HEAP_CLASS_1 0x00001000

#define _May_raise_

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

extern _RtlAllocateHeap RtlAllocateHeap;
extern _RtlFreeHeap RtlFreeHeap;
extern _NtQueryInformationProcess NtQueryInformationProcessEx;
extern _RtlCreateHeap RtlCreateHeap;
extern _RtlGetVersion RtlGetVersion;
extern _RtlSetHeapInformation RtlSetHeapInformation;

extern PVOID PhHeapHandle;
extern ULONG WindowsVersion;

BOOLEAN PhHeapInitialization(
    _In_opt_ SIZE_T HeapReserveSize,
    _In_opt_ SIZE_T HeapCommitSize);

NTSTATUS PhpQueryProcessVariableSize(
    _In_ HANDLE ProcessHandle,
    _In_ _PROCESSINFOCLASS ProcessInformationClass,
    _Out_ PVOID *Buffer);

ULONG GetWindowsVersion(void);

PVOID PhHeapHandle = NULL;
ULONG WindowsVersion = WINDOWS_NEW;
BOOL DebugPriviliges = FALSE;
RTL_OSVERSIONINFOEXW PhOsVersion = {0};

_RtlAllocateHeap RtlAllocateHeap =
    (_RtlAllocateHeap)GetProcAddress(
        GetModuleHandleA("ntdll.dll"), "RtlAllocateHeap");
_RtlFreeHeap RtlFreeHeap =
    (_RtlFreeHeap)GetProcAddress(
        GetModuleHandleA("ntdll.dll"), "RtlFreeHeap");
_NtQueryInformationProcess NtQueryInformationProcessEx =
    (_NtQueryInformationProcess)GetProcAddress(
        GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
_RtlCreateHeap RtlCreateHeap =
    (_RtlCreateHeap)GetProcAddress(
        GetModuleHandleA("ntdll.dll"), "RtlCreateHeap");
_RtlGetVersion RtlGetVersion =
    (_RtlGetVersion)GetProcAddress(
        GetModuleHandleA("ntdll.dll"), "RtlGetVersion");
_RtlSetHeapInformation RtlSetHeapInformation =
    (_RtlSetHeapInformation)GetProcAddress(
        GetModuleHandleA("ntdll.dll"), "RtlSetHeapInformation");

ULONG __stdcall InitializeWindowsVersion(void)
{
    RTL_OSVERSIONINFOEXW versionInfo;
    ULONG majorVersion;
    ULONG minorVersion;
    ULONG buildVersion;

    ::memset(&versionInfo, 0, sizeof(RTL_OSVERSIONINFOEXW));
    versionInfo.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW);

    if (!NT_SUCCESS(RtlGetVersion(&versionInfo)))
    {
        WindowsVersion = WINDOWS_NEW;
        return WindowsVersion;
    }

    ::memcpy(&PhOsVersion, &versionInfo, sizeof(RTL_OSVERSIONINFOEXW));
    majorVersion = versionInfo.dwMajorVersion;
    minorVersion = versionInfo.dwMinorVersion;
    buildVersion = versionInfo.dwBuildNumber;

    // Windows 7, Windows Server 2008 R2
    if (majorVersion == 6 && minorVersion == 1)
    {
        WindowsVersion = WINDOWS_7;
    }
    // Windows 8, Windows Server 2012
    else if (majorVersion == 6 && minorVersion == 2)
    {
        WindowsVersion = WINDOWS_8;
    }
    // Windows 8.1, Windows Server 2012 R2
    else if (majorVersion == 6 && minorVersion == 3)
    {
        WindowsVersion = WINDOWS_8_1;
    }
    // Windows 10, Windows Server 2016
    else if (majorVersion == 10 && minorVersion == 0)
    {
        if (buildVersion >= 19042)
        {
            WindowsVersion = WINDOWS_10_20H2;
        }
        else if (buildVersion >= 19041)
        {
            WindowsVersion = WINDOWS_10_20H1;
        }
        else if (buildVersion >= 18363)
        {
            WindowsVersion = WINDOWS_10_19H2;
        }
        else if (buildVersion >= 18362)
        {
            WindowsVersion = WINDOWS_10_19H1;
        }
        else if (buildVersion >= 17763)
        {
            WindowsVersion = WINDOWS_10_RS5;
        }
        else if (buildVersion >= 17134)
        {
            WindowsVersion = WINDOWS_10_RS4;
        }
        else if (buildVersion >= 16299)
        {
            WindowsVersion = WINDOWS_10_RS3;
        }
        else if (buildVersion >= 15063)
        {
            WindowsVersion = WINDOWS_10_RS2;
        }
        else if (buildVersion >= 14393)
        {
            WindowsVersion = WINDOWS_10_RS1;
        }
        else if (buildVersion >= 10586)
        {
            WindowsVersion = WINDOWS_10_TH2;
        }
        else if (buildVersion >= 10240)
        {
            WindowsVersion = WINDOWS_10;
        }
        else
        {
            WindowsVersion = WINDOWS_10;
        }
    }
    else
    {
        WindowsVersion = WINDOWS_NEW;
    }

    return WindowsVersion;
}

ULONG GetWindowsVersion(void)
{
    return WindowsVersion;
}

BOOLEAN PhHeapInitialization(_In_opt_ SIZE_T HeapReserveSize, _In_opt_ SIZE_T HeapCommitSize)
{

    if (WindowsVersion >= WINDOWS_8)
    {
        PhHeapHandle = RtlCreateHeap(
            HEAP_GROWABLE | HEAP_CREATE_SEGMENT_HEAP | HEAP_CLASS_1,
            NULL,
            0,
            0,
            NULL,
            NULL);
    }

    if (!PhHeapHandle)
    {
        PhHeapHandle = RtlCreateHeap(
            HEAP_GROWABLE | HEAP_CLASS_1,
            NULL,
            HeapReserveSize ? HeapReserveSize : 2 * 1024 * 1024, // 2 MB
            HeapCommitSize ? HeapCommitSize : 1024 * 1024,       // 1 MB
            NULL,
            NULL);

        if (!PhHeapHandle)
            return FALSE;

        if (WindowsVersion >= WINDOWS_VISTA)
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

_May_raise_
_Post_writable_byte_size_(Size)

PVOID PhAllocate(_In_ SIZE_T Size)
{
    return RtlAllocateHeap(PhHeapHandle, HEAP_GENERATE_EXCEPTIONS, Size);
}

VOID PhFree(_Frees_ptr_opt_ PVOID Memory)
{
    RtlFreeHeap(PhHeapHandle, 0, Memory);
}

NTSTATUS PhpQueryProcessVariableSize(_In_ HANDLE ProcessHandle, _In_ _PROCESSINFOCLASS ProcessInformationClass, _Out_ PVOID *Buffer)
{
    NTSTATUS status;
    PVOID buffer;
    ULONG returnLength = 0;

    status = NtQueryInformationProcessEx(
        ProcessHandle,
        ProcessInformationClass,
        NULL,
        0,
        &returnLength);

    if (status != STATUS_BUFFER_OVERFLOW && status != STATUS_BUFFER_TOO_SMALL && status != STATUS_INFO_LENGTH_MISMATCH)
        return status;

    buffer = PhAllocate(returnLength);
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
        PhFree(buffer);
    }

    return status;
}

PVOID GetPebAddress(HANDLE ProcessHandle)
{
    PROCESS_BASIC_INFORMATION pbi;

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

    WCHAR *commandLineContents = (WCHAR *)malloc(commandLine.Length);

    if (!ReadProcessMemory(ProcessHandle, commandLine.Buffer,
                           commandLineContents, commandLine.Length, NULL))
    {
        *status = GetLastError();
        return NULL;
    }

    CloseHandle(ProcessHandle);

    return commandLineContents;
}

std::wstring __stdcall GetProcessCommandLine(_In_ HANDLE ProcessHandle, _Out_ long *status)
{

    if (PhHeapHandle == NULL)
    {

        InitializeWindowsVersion();

        if (!PhHeapInitialization(0, 0))
        {
            *status = -1;
            return L"";
        }
    }

    if (WindowsVersion >= WINDOWS_8_1)
        return GetProcessCommandLineNew(ProcessHandle, status);

    return GetProcessCommandLineOld(ProcessHandle, status);
}

std::wstring GetProcessCommandLineByPid(_In_ int pid, _Out_ long *status)
{
    HANDLE ProcessHandle = NULL;
    AdjustDebugPriviliges();

    ProcessHandle = ::OpenProcess(
        PROCESS_QUERY_INFORMATION | /* required for NtQueryInformationProcess */
            PROCESS_VM_READ,        /* required for ReadProcessMemory */
        FALSE, pid);

    AdjustDebugPriviliges();

    if (PhHeapHandle == NULL)
    {

        InitializeWindowsVersion();

        if (!PhHeapInitialization(0, 0))
        {
            *status = -1;
            return L"";
        }
    }
    else
    {
        // return GetLastError();
    }

    if (WindowsVersion >= WINDOWS_8_1)
        return GetProcessCommandLineNew(ProcessHandle, status);

    return GetProcessCommandLineOld(ProcessHandle, status);
}
