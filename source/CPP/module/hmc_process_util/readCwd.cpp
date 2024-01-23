#include <iostream>
#include <string>
#include <windows.h>
#include <winternl.h>

#define PTR_ADD_OFFSET(Pointer, Offset) ((PVOID)((ULONG_PTR)(Pointer) + (ULONG_PTR)(Offset)))

struct CURDIR {
  UNICODE_STRING DosPath;
  HANDLE Handle;
};

struct LOCAL_RTL_USER_PROCESS_PARAMETERS {
  ULONG _1[4];
  HANDLE _2;
  ULONG _3;
  HANDLE _4[3];
  CURDIR CurrentDirectory;
};

struct UNICODE_STRING32 {
  USHORT Length;
  USHORT MaximumLength;
  ULONG Buffer;
};

struct CURDIR32 {
  UNICODE_STRING32 DosPath;
  ULONG Handle;
};

struct LOCAL_RTL_USER_PROCESS_PARAMETERS32 {
  ULONG _1[9];
  CURDIR32 CurrentDirectory;
};

struct PEB32 {
  BOOLEAN _1[4];
  ULONG _2[3];
  ULONG ProcessParameters;
};

typedef NTSTATUS(__stdcall *nt_close)(HANDLE);
typedef NTSTATUS(__stdcall *nt_openProcess)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, CLIENT_ID *);
typedef NTSTATUS(__stdcall *nt_queryInformationProcess)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, ULONG_PTR);
typedef NTSTATUS(__stdcall *nt_readVirtualMemory)(HANDLE, PVOID, PVOID, SIZE_T, PSIZE_T);
struct NtCall {
  HMODULE p_ntdll;
  nt_close close;
  nt_openProcess openProcess;
  nt_queryInformationProcess queryInformationProcess;
  nt_readVirtualMemory readVirtualMemory;
} nt;

void initializeNtCall() {
  nt.p_ntdll = GetModuleHandleW(L"ntdll.dll");
  nt.close = nt_close(GetProcAddress(nt.p_ntdll, "NtClose"));
  nt.openProcess = nt_openProcess(GetProcAddress(nt.p_ntdll, "NtOpenProcess"));
  nt.queryInformationProcess = nt_queryInformationProcess(GetProcAddress(nt.p_ntdll, "NtQueryInformationProcess"));
  nt.readVirtualMemory = nt_readVirtualMemory(GetProcAddress(nt.p_ntdll, "NtReadVirtualMemory"));
}

NTSTATUS readCwd(wchar_t **outputString, unsigned long pid) {
  initializeNtCall();

  HANDLE processHandle = NULL;
  PWCHAR cwdString;
  CLIENT_ID clientId{
    UlongToHandle(pid),
    NULL
  };
  OBJECT_ATTRIBUTES objectAttributes{
    sizeof(OBJECT_ATTRIBUTES),
    NULL,
    0,
    NULL,
    NULL,
    NULL
  };
  NTSTATUS status;

  if (!NT_SUCCESS(status = nt.openProcess(
    &processHandle,
    PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ,
    &objectAttributes,
    &clientId
  ))) {
    return status;
  }

  ULONG_PTR wow64;
  if (!NT_SUCCESS(status = nt.queryInformationProcess(
    processHandle,
    ProcessWow64Information,
    &wow64,
    sizeof(ULONG_PTR),
    NULL
  ))) {
    return status;
  }

  if (!wow64) {
    ULONG offset = FIELD_OFFSET(LOCAL_RTL_USER_PROCESS_PARAMETERS, CurrentDirectory);
    PROCESS_BASIC_INFORMATION basicInfo;
    PVOID processParameters;
    if (!NT_SUCCESS(status = nt.queryInformationProcess(
      processHandle,
      ProcessBasicInformation,
      &basicInfo,
      sizeof(PROCESS_BASIC_INFORMATION),
      NULL
    ))) {
      return status;
    }

    if (!NT_SUCCESS(status = nt.readVirtualMemory(
      processHandle,
      PTR_ADD_OFFSET(basicInfo.PebBaseAddress, FIELD_OFFSET(PEB, ProcessParameters)),
      &processParameters,
      sizeof(PVOID),
      NULL
    ))) {
      return status;
    }

    UNICODE_STRING initReadString;
    if (!NT_SUCCESS(status = nt.readVirtualMemory(
      processHandle,
      PTR_ADD_OFFSET(processParameters, offset),
      &initReadString,
      sizeof(UNICODE_STRING),
      NULL
    ))) {
      return status;
    }

    if (initReadString.Length == 0) {
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
      NULL
    ))) {
      return status;
    }
  } else {
    ULONG offset = FIELD_OFFSET(LOCAL_RTL_USER_PROCESS_PARAMETERS32, CurrentDirectory);
    PVOID peb32;
    ULONG processParameters32;


    if (!NT_SUCCESS(status = nt.queryInformationProcess(
      processHandle,
      ProcessWow64Information,
      &peb32,
      sizeof(ULONG_PTR),
      NULL
    ))) {
      return status;
    }


    if (!NT_SUCCESS(status = nt.readVirtualMemory(
      processHandle,
      PTR_ADD_OFFSET(peb32, FIELD_OFFSET(PEB32, ProcessParameters)),
      &processParameters32,
      sizeof(unsigned long),
      NULL
    ))) {
      return status;
    }

    UNICODE_STRING32 initReadString;
    if (!NT_SUCCESS(status = nt.readVirtualMemory(
      processHandle,
      PTR_ADD_OFFSET(processParameters32, offset),
      &initReadString,
      sizeof(UNICODE_STRING32),
      NULL
    ))) {
      return status;
    }

    if (initReadString.Length == 0) {
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
      NULL
    ))) {
      return status;
    }
  }

  *outputString = cwdString;
  nt.close(processHandle);
  return status;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    return -1;
  }

  NTSTATUS status;
  PWCHAR str;
	if (!NT_SUCCESS(status = readCwd(&str, std::stoul(std::string(argv[1]), nullptr, 10)))) {
    return -1;
  }

	std::wcout << str;
  return 0;
}
