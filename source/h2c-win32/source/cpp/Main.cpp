
#include "./Main.hpp"

using namespace std;

static napi_value mode(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_boolean}, true))
    {
        return NULL;
    }

    LPSTR output = hmc_AllocVS(LPSTR, 1024);
    hmc_FreeVSAuto(output);

    return NULL;
}

static napi_value mode2(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_boolean}, true))
    {
        return NULL;
    }

    LPSTR output = hmc_AllocVS(LPSTR, 1024);
    hmc_FreeVSAuto(output);

    return NULL;
}


static napi_value Init(napi_env env, napi_value exports)
{

    napi_property_descriptor BIND_NAPI_METHOD[] = {
        EXPORT_NAPI_STATIC_FN(mode),

    };
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
