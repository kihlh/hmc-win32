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

#define shared_close_Library(hModule) std::shared_ptr<void> _shared_close_Library_(nullptr, [&](void *) {if (hModule != NULL) {FreeLibrary(hModule);} });
#define shared_close_lpsz(lpwsz) std::shared_ptr<void> _shared_close_lpsz_(nullptr, [&](void *) {if (lpwsz != NULL) {GlobalFree(lpwsz);lpwsz = 0; } });

#define HMCERR_Catch                                                                          \
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
