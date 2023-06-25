#include <windows.h>
#include <assert.h>
#define NAPI_EXPERIMENTAL // 开启实验性功能 比如异步(多线程)
#include <node_api.h>
#include "./util/napi_util.hpp";

using namespace napi_util;
using namespace std;











static napi_value Init(napi_env env, napi_value exports)
{
    // napi_util::textEscaper::A2W("dshh");
    napi_property_descriptor BIND_NAPI_METHOD[] = {
        { "version", 0, 0, 0, 0, napi_util::create_value::String(env,"1.0.0"), napi_default, 0 }
    };

    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
