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

#define $napi_get_cb_info(argsLen, args, fnName)                            \
    if (napi_get_cb_info(env, info, &argsLen, args, NULL, NULL) != napi_ok) \
    {                                                                       \
        napi_throw_type_error(env, NULL, string(fnName).c_str());           \
        return NULL;                                                        \
    }

// 导出一个其他cpp中的模块
#define DECLARE_NAPI_METHODRM(name, func)                         \
    {                                                             \
        name, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个模块
#define DECLARE_NAPI_METHOD(name, func)         \
    {                                           \
        name, 0, func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个文本内容
#define DECLARE_NAPI_VALUE(name, value)                                                    \
    {                                                                                      \
        name, 0, 0, 0, 0, hmc_napi_util::create_value::String(env, value), napi_default, 0 \
    }
