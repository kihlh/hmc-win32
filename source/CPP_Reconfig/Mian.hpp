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

#include <Shellapi.h>
#include <vector>
#include <process.h>
#include <Tlhelp32.h>
#include <iostream>
#include <Psapi.h>
#include <Dwmapi.h>
#include <conio.h>
#include <time.h>
#include <signal.h>
#include <algorithm>

using namespace std;

#pragma comment(lib, "Ws2_32")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "psapi.lib")

