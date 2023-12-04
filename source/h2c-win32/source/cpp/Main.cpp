#include <node_api.h>
#include <Windows.h>
#include <winternl.h>
#include <assert.h>
#include <stdio.h>
#include <atlstr.h>
#include <iostream>
// #include "./Main.hpp"
using namespace std;

static napi_value fnGetCurrentWorkingDirectory(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;

    return result;
}


#define _DECLARE_NAPI_METHODRM(func)                             \
    {                                                              \
        #func, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
    }

#define _DECLARE_NAPI_METHODRM(name, func)                      \
    {                                                             \
        name, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
    }

#define HAS_COMMA(...) HAS_COMMA_16__(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0)
#define HAS_COMMA_16__(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define CAT_(X, Y) X##Y
#define CAT(X, Y) CAT_(X, Y)
#define BAR(... /*All*/) CAT(BAR, HAS_COMMA(__VA_ARGS__))(__VA_ARGS__)
#define BAR0(func)                                                   \
    {                                                                \
        #func, 0, (napi_callback) & ##func, 0, 0, 0, napi_default, 0 \
    }
#define BAR1(name, func, ...)                                       \
    {                                                               \
        ##name, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
    }

static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor BIND_NAPI_METHOD[] = {
        // DECLARE_NAPI_METHODRM(fnGetCurrentWorkingDirectory),
        BAR("GetCurrentWorkingDirectory", fnGetCurrentWorkingDirectory),
        BAR(fnGetCurrentWorkingDirectory),

    };
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
