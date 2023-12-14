#define NAPI_EXPERIMENTAL
#include <node_api.h>
#include <string>
#include <any>
#include <vector>
#include <atomic>


/*
 使用宏魔法开辟一个 Promise 函数
namespace fu_New_Promise_class NEW_PROMISE_FUNCTION_DEFAULT_FUN;

std::any fu_New_Promise_class::PromiseWorkFunc(std::vector<any> arguments_list) {
    std::any result = std::any();
    return result;
}

napi_value fu_New_Promise_class::format_to_js_value(napi_env env, std::any result_any_data) {
    napi_value result;
    napi_get_null(env, &result);

    if (!result_any_data.has_value()) {
        return result;
    }

    return result;
}

*/
#define NEW_PROMISE_FUNCTION_DEFAULT_FUN {\
    std::any resultSend = std::any();\
    std::vector<any> arguments_list = {};\
    napi_value format_to_js_value(napi_env env, std::any result_any_data);\
    std::any PromiseWorkFunc(std::vector<std::any> arguments_list);\
    class PromiseFunction\
    {\
    private:\
        static constexpr std::atomic<napi_async_work> work = NULL;\
        static constexpr std::atomic<napi_deferred> deferred = NULL;\
    public:\
        static void exports(napi_env env, napi_value exports, std::string name)\
        {\
            napi_value exported_function;\
            napi_create_function(env,\
                                 name.c_str(),\
                                 name.length(),\
                                 startWork,\
                                 NULL,\
                                 &exported_function);\
            napi_set_named_property(env, exports, name.c_str(), exported_function);\
            napi_wrap(env, exports, NULL, NULL, NULL, NULL);\
        }\
        static void exportsSync(napi_env env, napi_value exports, std::string name)\
        {\
            napi_value exported_function;\
            napi_create_function(env,\
                                 name.c_str(),\
                                 name.length(),\
                                 startSync,\
                                 NULL,\
                                 &exported_function);\
            napi_set_named_property(env, exports, name.c_str(), exported_function);\
            napi_wrap(env, exports, NULL, NULL, NULL, NULL);\
        }\
    protected:\
        static void asyncWorkFun(napi_env env, void *data)\
        {\
            resultSend = PromiseWorkFunc(arguments_list);\
        }\
        static void completeWork(napi_env env, napi_status status, void *data)\
        {\
            napi_resolve_deferred(env, deferred, format_to_js_value(env, resultSend));\
            napi_delete_async_work(env, work);\
            deferred._Storage._Value = NULL;\
            work._Storage._Value = NULL;\
            resultSend.reset();\
            resultSend = std::any();\
            arguments_list.clear();\
            arguments_list.resize(0);\
        }\
        static napi_value startWork(napi_env env, napi_callback_info info)\
        {\
            napi_value result, work_name, promise;\
            napi_get_null(env, &result);\
            std::string work_message = std::string(__FUNCTION__).append("  work_message ->  ");\
            if (work != NULL)\
            {\
                work_message.append("error < Promise workspace has not been released. > ");\
                napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());\
                return result;\
            }\
            work_message.append("Node-API Deferred Promise from Async Work Item");\
            napi_create_string_utf8(env, work_message.c_str(), work_message.length(), &work_name);\
            napi_async_work addon_napi_async_work = NULL;\
            napi_deferred addon_deferred = NULL;\
            if (napi_create_promise(env, &addon_deferred, &promise) != napi_ok)\
            {\
                work_message.append("error < Promise Creation failed. > ");\
                napi_throw_error(env, "Creation_failed", work_message.c_str());\
                return result;\
            };\
            auto input = hmc_NodeArgsValue(env, info).get_values();\
            for (size_t i = 0; i < input.size(); i++)\
            {\
                arguments_list.push_back(input.at(i));\
            }\
            if (napi_create_async_work(env,\
                                       NULL,\
                                       work_name,\
                                       asyncWorkFun,\
                                       completeWork, NULL, &addon_napi_async_work) != napi_ok)\
            {\
                work_message.append("error < Promise Creation work async failed. > ");\
                napi_throw_error(env, "Creation_failed", work_message.c_str());\
                return result;\
            };\
            napi_queue_async_work(env, addon_napi_async_work);\
            work._Storage._Value = addon_napi_async_work;\
            deferred._Storage._Value = addon_deferred;\
            return promise;\
        }\
        static napi_value startSync(napi_env env, napi_callback_info info)\
        {\
            napi_value result, work_name, promise;\
            napi_get_null(env, &result);\
            std::any resultSend = std::any();\
            std::vector<std::any> arguments_list = {};\
            auto input = hmc_NodeArgsValue(env, info).get_values();\
            for (size_t i = 0; i < input.size(); i++)\
            {\
                arguments_list.push_back(input.at(i));\
            }\
            try\
            {\
                std::any data = PromiseWorkFunc(arguments_list);\
                return format_to_js_value(env, data);\
            }\
            catch (const std::exception &err)\
            {\
                napi_throw_error(env, "catch (const std::exception&)", err.what());\
                return result;\
            }\
            catch (...)\
            {\
                napi_throw_error(env, "catch (...)", "");\
                return result;\
            }\
            return result;\
        }\
    };\
    void exports(napi_env env, napi_value exports, std::string name)\
    {\
        (new PromiseFunction)->exports(env, exports, name.c_str());\
    }\
    void exportsSync(napi_env env, napi_value exports, std::string name)\
    {\
        (new PromiseFunction)->exportsSync(env, exports, name.c_str());\
    }}