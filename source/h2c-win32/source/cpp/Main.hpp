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

#define HMCERR_Catch                                                  \
    catch (char *e) { cout << "ERROR:"                                \
                           << "<" << __LINE__ << "> " << e << endl; } \
    catch (const std::exception &ex)                                  \
    {                                                                 \
        cout << "exception:"                                          \
             << "<" << __LINE__ << "> " << ex.what() << endl;         \
    }                                                                 \
    catch (...) { cout << "ERROR:"                                    \
                       << "<" << __LINE__ << "> "                     \
                       << "unknown" << endl; };

// 导出一个模块
#define DECLARE_NAPI_METHOD(func)                \
    {                                            \
        #func, 0, func, 0, 0, 0, napi_default, 0 \
    }

#define _SELECT(PREFIX, _5, _4, _3, _2, _1, SUFFIX, ...) PREFIX##_##SUFFIX

// #define _DECLARE_NAPI_METHODRM_1(func)                             \
//     {                                                              \
//         #func, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
//     }

// #define _DECLARE_NAPI_METHODRM_2(name, func)                      \
//     {                                                             \
//         name, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
//     }
// #define DECLARE_NAPI_METHODRM(...) _DECLARE_NAPI_METHODRM(_BAR, __VA_ARGS__, N, N, N, N, 1)(__VA_ARGS__)

#define _SELECT(PREFIX, _5, _4, _3, _2, _1, SUFFIX, ...) PREFIX##_##SUFFIX

#define _BAR_1(func)                                               \
    {                                                              \
        #func, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
    }
#define _BAR_N(func, ...) printf(fmt "\n", __VA_ARGS__);
#define BAR(...) _SELECT(_BAR, __VA_ARGS__, N, N, N, N, 1)(__VA_ARGS__)

// 导出一个文本内容
#define DECLARE_NAPI_VALUE(name, value)                                                  \
    {                                                                                    \
        fn, 0, 0, 0, 0, hmc_napi_util::create_value::String(env, value), napi_default, 0 \
    }
