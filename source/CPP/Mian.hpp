#include <windows.h>
#include <assert.h>
// 开启实验性功能 比如异步(多线程)
#define NAPI_EXPERIMENTAL
#include <node_api.h>
#include <stdio.h>
#include <malloc.h>
#include "./include/pch.h"
#include <winuser.h>
#include <ShlObj.h>
#include <string>
#include <thread>
#include <chrono>

#include <Shellapi.h>
#include <vector>
#include <process.h>
#include <Tlhelp32.h>
#include <iostream>
#include <Psapi.h>
#include <Dwmapi.h>
#include "./util.h"

#pragma comment(lib, "dwmapi.lib")
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

BOOL EnableShutDownPriv();







// clip.cpp
napi_value setClipboardText(napi_env env, napi_callback_info info);
napi_value getClipboardText(napi_env env, napi_callback_info info);
napi_value getClipboardFilePaths(napi_env env);
napi_value setClipboardFilePaths(napi_env env, napi_callback_info info);
napi_value clearClipboard(napi_env env, napi_callback_info info);
// registr.cpp

napi_value getStringRegKey(napi_env env, napi_callback_info info);

napi_value removeStringRegKey(napi_env env, napi_callback_info info);

napi_value removeStringRegValue(napi_env env, napi_callback_info info);

napi_value removeStringRegKeyWalk(napi_env env, napi_callback_info info);

napi_value hasRegistrKey(napi_env env, napi_callback_info info);

napi_value setRegistrKey(napi_env env, napi_callback_info info);

napi_value createPathRegistr(napi_env env, napi_callback_info info);

napi_value enumRegistrKey(napi_env env, napi_callback_info info);

napi_value getRegistrValueSize(napi_env env, napi_callback_info info);

napi_value getRegistrBuffValue(napi_env env, napi_callback_info info);

napi_value getRegistrDword(napi_env env, napi_callback_info info);

napi_value setRegistrDword(napi_env env, napi_callback_info info);

napi_value getRegistrQword(napi_env env, napi_callback_info info);

napi_value setRegistrQword(napi_env env, napi_callback_info info);

// usb.cpp

napi_value getHidUsbList(napi_env env, napi_callback_info info);
napi_value usbDevsInfo(napi_env env, napi_callback_info info);
napi_value getDeviceUsbList(napi_env env, napi_callback_info info);
