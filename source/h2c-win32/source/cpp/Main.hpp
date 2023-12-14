#include <windows.h>
#include <assert.h>
#define NAPI_EXPERIMENTAL // 开启实验性功能 比如异步(多线程)
#include <node_api.h>

using namespace std;

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

// 截屏的存储为文件
#include <fstream>

// 小写转换
#include <algorithm>
#include <map>


using namespace std;

#define $napi_get_cb_info(argc, argv)                                                                                          \
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)                                                       \
    {                                                                                                                          \
        napi_throw_type_error(env, NULL, string(__FUNCTION__).append(" < ").append(" napi_get_cb_info ").append(">").c_str()); \
        return NULL;                                                                                                           \
    }

// 自动释放dll
#define hmc_shared_close_Library(hModule) std::shared_ptr<void>##hModule##_shared_close_Library_(nullptr, [&](void *) {if (hModule != NULL) {FreeLibrary(hModule);} });
// 自动释放文本
#define hmc_shared_close_lpsz(lpwsz) std::shared_ptr<void>##lpwsz##_shared_close_lpsz_(nullptr, [&](void *) {if (lpwsz != NULL) {GlobalFree(lpwsz);lpwsz = 0; } });

// 开辟内存 (请注意需要调用 FreeVS 或者 hmc_FreeVSAuto 释放)
// -> LPSTR pszMem = AllocVS(LPSTR, leng + 1);
#define hmc_AllocVS(Type, leng)                                                   \
    (Type) VirtualAlloc((LPVOID)NULL, (DWORD)(leng), MEM_COMMIT, PAGE_READWRITE); 

// 释放空间
// -> LPSTR pszMem = hmc_AllocVS(LPSTR, leng + 1);
// -> FreeVS(pszMem);
#define hmc_FreeVS(Virtua) \
    if (Virtua != NULL)    \
        VirtualFree(Virtua, 0, MEM_RELEASE);

// 释放空间
// -> LPSTR pszMem = hmc_AllocVS(LPSTR, leng + 1);
// -> FreeVSAuto(pszMem);
#define hmc_FreeVSAuto(Virtua) \
    std::shared_ptr<void>##Virtua##_shared_close_FreeVSAuto_(nullptr, [&](void *) {if (Virtua != NULL) {VirtualFree(Virtua, 0, MEM_RELEASE);} });

// 开辟内存
#define hmc_AllocHeap(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
// 释放内存
#define hmc_FreeHeap(variable) HeapFree(GetProcessHeap(), 0, (variable))

// 让代码在异步线程中执行
#define hmc_Thread (code) std::thread([]() -> void { code }).detach();

#define hmc_Catch                                                                         \
    catch (char *e) { cout << "ERROR:"                                                        \
                           << "<" << __FUNCSIG__ << " @ " << __LINE__ << "> " << e << endl; } \
    catch (const std::exception &ex)                                                          \
    {                                                                                         \
        cout << "exception:"                                                                  \
             << "<" << __FUNCSIG__ << " @ " << __LINE__ << "> " << ex.what() << endl;         \
    }                                                                                         \
    catch (...) { cout << "ERROR:"                                                            \
                       << "<" << __FUNCSIG__ << " @ " << __LINE__ << "> "                     \
                       << "unknown" << endl; };

// 导出一个 static 函数
#define EXPORT_NAPI_STATIC_FN(func)              \
    {                                            \
        #func, 0, func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个 其他文件的 函数
#define EXPORT_NAPI_REMOTE_FN(func)                                \
    {                                                              \
        #func, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个 其他文件的 函数 并设置名称
#define EXPORT_NAPI_REMOTE_PAIRFN(name, func)                     \
    {                                                             \
        name, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个文本内容
#define DECLARE_NAPI_VALUE(name, value)                                                  \
    {                                                                                    \
        fn, 0, 0, 0, 0, hmc_napi_util::create_value::String(env, value), napi_default, 0 \
    }
