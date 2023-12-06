
#include "./Main.hpp"
#include "./util/hmc_string_util.hpp"
#include "./util/napi_value_util.hpp"
#include <io.h>    // _setmode
#include <fcntl.h> // _O_U16TEXT

using namespace std;

static napi_value mode(napi_env env, napi_callback_info info)
{
    hmcNodeValue input = hmcNodeValue(env, info);

    input.eq({{0, js_error},
              {0, js_boolean},
              {0, js_null},
              {4, js_string}

             },
             true);

    // return hmc_napi_create_value::String(env, input.getStringWide(0));
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
