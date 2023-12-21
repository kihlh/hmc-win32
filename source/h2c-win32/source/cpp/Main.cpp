
#include "./Main.hpp"


#include "./util/hmc_string_util.hpp"
#include "./util/napi_value_util.hpp"
#include "./util/fmt11.hpp"


static napi_value Init(napi_env env, napi_value exports)
{

    napi_property_descriptor BIND_NAPI_METHOD[] = {
        ___EXPORT_NAPI_REMOTE_FN____PROMISE_SESSION};
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);



    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
