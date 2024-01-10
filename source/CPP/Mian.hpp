#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_MAIN_HPP
#define MODE_INTERNAL_INCLUDE_HMC_MAIN_HPP

#include <windows.h>
#include <assert.h>
// 开启实验性功能 比如异步(多线程)
#define NAPI_EXPERIMENTAL
#include <node_api.h>
#include <stdio.h>
#include <malloc.h>
#include <winuser.h>
#include <ShlObj.h>
#include <string>
#include <thread>
#include <chrono>
#include <iosfwd>
#include <set>


#include <Shellapi.h>
#include <vector>
#include <process.h>
#include <Tlhelp32.h>
#include <iostream>
#include <Psapi.h>
#include <Dwmapi.h>
#include "./util.h"
#include <conio.h>
#include <time.h>
#include <signal.h>
#include <algorithm>
#include "./pch.h"

#pragma comment(lib, "Ws2_32")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "psapi.lib")
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
using namespace std;
#ifdef UNICODE
typedef LPWSTR LPTSTR;
typedef LPCWSTR LPCTSTR;
#else
typedef LPSTR LPTSTR;
typedef LPCSTR LPCTSTR;
#endif
#define $napi_get_cb_info(argc, args) napi_get_cb_info(env, info, &argc, args, NULL, NULL);
#define $runError (CharString) napi_throw_type_error(env, NULL, CharString);
// DEFINE_GUID(UsbClassGuid, 0xa5dcbf10L, 0x6530, 0x11d2, 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed);
extern bool _________HMC_DEBUG__________;

void ____HMC_DEBUG_RUN_MESS____(napi_env env, string error_message);

void ____HMC_DEBUG_RUN_MESS____(napi_env env, string error_message);
BOOL EnableShutDownPriv();

struct util_Volume
{
    wstring path;
    wstring name;
    wstring device;
};

struct HMC_PROCESSENTRY32
{
    int pollingId;
    DWORD dwSize;
    DWORD cntUsage;
    DWORD th32ProcessID; // this process
    DWORD th32DefaultHeapID;
    DWORD th32ModuleID; // associated exe
    DWORD cntThreads;
    DWORD th32ParentProcessID; // this process's parent process
    DWORD pcPriClassBase;      // Base priority of process's threads
    DWORD dwFlags;
    wstring szExeFile; // Path
};

struct HMC_PROCESSENTRY32W
{
    DWORD dwSize;
    DWORD cntUsage;
    DWORD th32ProcessID; // this process
    DWORD th32DefaultHeapID;
    DWORD th32ModuleID; // associated exe
    DWORD cntThreads;
    DWORD th32ParentProcessID; // this process's parent process
    DWORD pcPriClassBase;      // Base priority of process's threads
    DWORD dwFlags;
    wstring szExeFile; // Path
};

// 判断所有传入参数都为
#define hmc_is_argv_type(argv, start, size, type, Results)                      \
    for (int i = start; i < (size==NULL?start+1:size); i++)                         \
    {                                                                           \
        napi_valuetype value_type;                                              \
        napi_typeof(env, argv[i], &value_type);                                 \
        if (value_type != type)                                                 \
        {                                                                       \
            napi_throw_error(env, "EINVAL",                                     \
                             string("\nThe [")                                  \
                                 .append(to_string(argc))                       \
                                 .append("] parameter passed in should read [") \
                                 .append(hmc_napi_type::typeName(value_type))           \
                                 .append("] This parameter should read: ")      \
                                 .append(hmc_napi_type::typeName(type))                 \
                                 .append("\n")                                  \
                                 .c_str());                                     \
            return Results;                                                     \
        };                                                                      \
    }

// 判断传入的参数是否大于此要求
#define hmc_is_argc_size(argc, size, Results)                                                                                           \
    if (argc < size)                                                                                                                    \
    {                                                                                                                                   \
        napi_throw_type_error(env, 0, string("The number of parameters entered is not legal size =>").append(to_string(argc)).c_str()); \
        return Results;                                                                                                                 \
    }

// 开始暴露模块

// 导出一个其他cpp中的模块
#define DECLARE_NAPI_METHODRM(name, func)                       \
    {                                                           \
        name, 0, (napi_callback)&func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个模块
#define DECLARE_NAPI_METHOD(name, func)         \
    {                                           \
        name, 0, func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个js支持的内容
#define ADD_NAPI_METHOD_VALUE(name, value)       \
    {                                            \
        name, 0, 0, 0, 0, value, napi_default, 0 \
    }

// 导出一个文本内容
#define ADD_NAPI_METHOD_Str_VALUE(name, value)                        \
    {                                                                 \
        name, 0, 0, 0, 0, as_String(value), napi_default, 0 \
    }

// clip.cpp
napi_value enumClipboardFormats(napi_env env, napi_callback_info info);
napi_value setClipboardText(napi_env env, napi_callback_info info);
napi_value getClipboardText(napi_env env, napi_callback_info info);
napi_value getClipboardFilePaths(napi_env env, napi_callback_info info);
napi_value setClipboardFilePaths(napi_env env, napi_callback_info info);
napi_value clearClipboard(napi_env env, napi_callback_info info);
napi_value getClipboardInfo(napi_env env, napi_callback_info info);
napi_value getClipboardHTML(napi_env env, napi_callback_info info);
// napi_value setClipboardHTML(napi_env env, napi_callback_info info);

// usb.cpp
napi_value getHidUsbIdList(napi_env env, napi_callback_info info);
napi_value getHidUsbList(napi_env env, napi_callback_info info);
napi_value getUsbDevsInfo(napi_env env, napi_callback_info info);
napi_value getVolumeList(napi_env env, napi_callback_info info);
napi_value formatVolumePath(napi_env env, napi_callback_info info);
vector<util_Volume> util_getVolumeList();
wstring FormatVolumePath(wstring VolumeName);
// napi_value getDeviceUsbList(napi_env env, napi_callback_info info);

// auto.cpp
void InstallKeyboardHook();

napi_value unKeyboardHook(napi_env env, napi_callback_info info);

napi_value getKeyboardNextSession(napi_env env, napi_callback_info info);
napi_value installKeyboardHook(napi_env env, napi_callback_info info);
napi_value isStartKeyboardHook(napi_env env, napi_callback_info info);
napi_value hasKeyActivate(napi_env env, napi_callback_info info);
napi_value getMouseMovePoints(napi_env env, napi_callback_info info);
napi_value leftClick(napi_env env, napi_callback_info info);
napi_value rightClick(napi_env env, napi_callback_info info);
napi_value setCursorPos(napi_env env, napi_callback_info info);
napi_value getBasicKeys(napi_env env, napi_callback_info info);
napi_value mouse(napi_env env, napi_callback_info info);
napi_value sendKeyT2C(napi_env env, napi_callback_info info);
napi_value sendKeyboard(napi_env env, napi_callback_info info);
napi_value sendKeyT2CSync(napi_env env, napi_callback_info info);
napi_value sendBasicKeys(napi_env env, napi_callback_info info);
napi_value getCursorPos(napi_env env, napi_callback_info info);
napi_value isStartHookMouse2(napi_env env, napi_callback_info info);
napi_value getMouseNextSession2(napi_env env, napi_callback_info info);
napi_value unHookMouse2(napi_env env, napi_callback_info info);
napi_value installHookMouse2(napi_env env, napi_callback_info info);
napi_value getLastInputTime(napi_env env, napi_callback_info info);
napi_value hasLimitMouseRangeWorker(napi_env env, napi_callback_info info);
napi_value setLimitMouseRange(napi_env env, napi_callback_info info);
napi_value stopLimitMouseRangeWorker(napi_env env, napi_callback_info info);

// Windows.cpp
napi_value getAllWindowsHandle(napi_env env, napi_callback_info info);
napi_value setForegroundWindow(napi_env env, napi_callback_info info);



// process.cpp
napi_value killProcess(napi_env env, napi_callback_info info);
napi_value getModulePathList(napi_env env, napi_callback_info info);
napi_value enumProcessHandle(napi_env env, napi_callback_info info);
napi_value enumProcessHandlePolling(napi_env env, napi_callback_info info);
napi_value getProcessThreadList(napi_env env, napi_callback_info info);
napi_value clearEnumProcessHandle(napi_env env, napi_callback_info info);
napi_value getSubProcessID(napi_env env, napi_callback_info info);
napi_value enumAllProcess(napi_env env, napi_callback_info info);
napi_value enumAllProcessPolling(napi_env env, napi_callback_info info);
// napi_value getProcessParentProcessID(napi_env env, napi_callback_info info);
napi_value clearEnumAllProcessList(napi_env env, napi_callback_info info);

// screen.cpp

napi_value captureBmpToFile(napi_env env, napi_callback_info info);
napi_value getColor(napi_env env, napi_callback_info info);
// napi_value captureBmpToBuff(napi_env env, napi_callback_info info);

// fn_environment.cpp
napi_value fn_getVariableAll(napi_env env, napi_callback_info info);
napi_value fn_setCwd(napi_env env, napi_callback_info info);
napi_value fn_getRealGlobalVariable(napi_env env, napi_callback_info info);
napi_value fn_getUserKeyList(napi_env env, napi_callback_info info);
napi_value fn_getSystemKeyList(napi_env env, napi_callback_info info);
napi_value fn_updateThis(napi_env env, napi_callback_info info);
napi_value fn_getEnvKeyAnalysis(napi_env env, napi_callback_info info);
napi_value fn_putSystemVariable(napi_env env, napi_callback_info info);
napi_value fn_putUserVariable(napi_env env, napi_callback_info info);
napi_value fn_getSystemVariable(napi_env env, napi_callback_info info);
napi_value fn_getUserVariable(napi_env env, napi_callback_info info);
napi_value fn_removeUserVariable(napi_env env, napi_callback_info info);
napi_value fn_removeAllSingleVariable(napi_env env, napi_callback_info info);
napi_value fn_removeSystemVariable(napi_env env, napi_callback_info info);
napi_value fn_hasKeyExists(napi_env env, napi_callback_info info);
napi_value fn_hasSysKeyExists(napi_env env, napi_callback_info info);
napi_value fn_hasUseKeyExists(napi_env env, napi_callback_info info);
napi_value fn_escapeEnvVariable(napi_env env, napi_callback_info info);
napi_value fn_AllocConsole(napi_env env, napi_callback_info info);
napi_value fn_getProcessStartTime(napi_env env, napi_callback_info info);
napi_value fn_getenv(napi_env env, napi_callback_info info);
napi_value fn_getAllEnv(napi_env env, napi_callback_info info);
napi_value fn_putenv(napi_env env, napi_callback_info info);


// fn_process.cpp

vector<HMC_PROCESSENTRY32W> GetProcessSnapshot(vector<DWORD> pid_list, bool early_result = true);
vector<HMC_PROCESSENTRY32W> GetProcessSnapshot(size_t Start, size_t End);

wstring GetProcessSnapshotNameW(DWORD processID);
bool ExistProcessID(DWORD processID);
wstring GetProcessIdFilePathW(DWORD processID, bool is_snapshot_match = false);


void exports_process_all_v2_fun(napi_env env, napi_value exports);


#endif // MODE_INTERNAL_INCLUDE_HMC_MAIN_HPP