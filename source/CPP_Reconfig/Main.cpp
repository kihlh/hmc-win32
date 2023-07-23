#include "Main.h"
#include "./util/util.h";
#include "./util/include/global.hpp";
#include "./util/newhmc.hpp";

static napi_value getProcessList(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info(argsLen, args, "getProcessList");

    // 参数最少要求1个
    if (!hmc_napi_util::assert::argsSize(env, argsLen, 0, 1))
    {
        return NULL;
    }
}

static napi_value Init(napi_env env, napi_value exports)
{
    newHMC();
    napi_property_descriptor BIND_NAPI_METHOD[] = {
        DECLARE_NAPI_VALUE("version","0.0.0"),                                                   // add 2023-07-23
        DECLARE_NAPI_VALUE("desc","hmc 2.0 : ' HMC Connection System api ' "),                   // add 2023-07-23
        DECLARE_NAPI_VALUE("platform","win32"),                                                  // add 2023-07-23
        DECLARE_NAPI_VALUE("binArch",GetBinaryArch()),                                           // add 2023-07-23
        DECLARE_NAPI_VALUE("arch",isSystemFor64bit()?"64bit":"32bit"),                           // add 2023-07-23
        
    };
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
