
#include "Main.hpp"

// #pragma comment(lib, "./AutoItX3/AutoItX3_DLL.lib")
// #pragma comment(lib, "./AutoItX3/AutoItX3\\AutoItX3_x64_DLL.lib")

#ifdef _MSC_VER

#ifdef _M_IX86
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_DLL.lib")

#elif defined(_M_X64) || defined(_M_AMD64)
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_x64_DLL.lib")

#endif //_M_IX86
#endif //_MSC_VER

// HMC_CHECK_CATCH
// 在node环境
#ifdef SRC_NODE_API_H_
#define HMC_CHECK_CATCH                        \
    catch (char *err)                          \
    {                                          \
        napi_throw_type_error(env, NULL, err); \
        return NULL;                           \
    }

// 不在node环境
#else
#define HMC_CHECK_CATCH            \
    catch (char *err)              \
    {                              \
        if (HMC_IS_DEUG_COUT == 1) \
        {                          \
            cout << err << "\n";   \
        }                          \
    }
#endif // SRC_NODE_API_H_




static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor BIND_NAPI_METHOD[] = {
        // DECLARE_NAPI_METHOD("Init", nfn_AU3_Init),
    };
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
