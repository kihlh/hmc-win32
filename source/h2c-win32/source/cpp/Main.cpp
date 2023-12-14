
#include "./Main.hpp"

#include "./util/hmc_string_util.hpp"
#include "./util/napi_value_util.hpp"

namespace fn_getAllProcessList
{
    NEW_PROMISE_FUNCTION_DEFAULT_FUN

    // NEW_PROMISE_FUNCTION_DEFAULT_FUN end
    any PromiseWorkFunc(vector<any> arguments_list)
    {
        any result = any();
        return result;
    }

    napi_value format_to_js_value(napi_env env, any result_any_data)
    {
        napi_value result;
        napi_get_null(env, &result);

        if (!result_any_data.has_value())
        {
            return result;
        }

        return result;
    }
};

static napi_value Init(napi_env env, napi_value exports)
{

    napi_property_descriptor BIND_NAPI_METHOD[] = {
        ___EXPORT_NAPI_REMOTE_FN____PROMISE_SESSION};
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);

    fn_getAllProcessList::exports(env,exports,"fn_getAllProcessList");
    fn_getAllProcessList::exportsSync(env, exports, "fn_getAllProcessListSync");

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
