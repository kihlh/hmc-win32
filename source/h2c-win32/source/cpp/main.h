#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_MAIN_V2_H
#define MODE_INTERNAL_INCLUDE_HMC_MAIN_V2_H

// 开启实验性功能 比如异步(多线程)
#define NAPI_EXPERIMENTAL
#include <node_api.h>

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

// 导出一个js支持的内容
#define ADD_NAPI_METHOD_VALUE(name, value)       \
    {                                            \
        name, 0, 0, 0, 0, value, napi_default, 0 \
    }

// 导出一个文本内容
#define ADD_NAPI_METHOD_Str_VALUE(name, value)              \
    {                                                       \
        name, 0, 0, 0, 0, as_String(value), napi_default, 0 \
    }

#endif // MODE_INTERNAL_INCLUDE_HMC_MAIN_V2_H