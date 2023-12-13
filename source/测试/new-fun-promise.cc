//#include <util\fmt11.hpp>
#define NAPI_EXPERIMENTAL
#include <node_api.h>
#include <util\hmc_string_util.hpp>
#include <util\napi_value_util.hpp>
#include <string>
#include <any>
#include <thread>
#include <vector>
#include <atomic>


namespace PromiseFunction {
    
    std::any resultSend = std::any();
    std::vector<std::any> arguments_list = {};

    std::any PromiseWorkFunc() {
        std::any result = std::any();
        return result;
    }

    napi_value format_to_js_value(napi_env env , std::any result_any_data ) {
        napi_value result;
        napi_get_null(env,&result);
        
        if (!result_any_data.has_value()) {
            return result;
        }

        return result;
    }


    class PromiseFunction
    {
    private:
        // 函数名称
        static constexpr std::atomic<napi_async_work> work = NULL;
        static constexpr std::atomic<napi_deferred> deferred = NULL;
    public:

        static void exports(napi_env env, napi_value exports, std::string name)
        {
            napi_value exported_function;

            napi_create_function(env,
                name.c_str(),
                name.length(),
                startWork,
                NULL,
                &exported_function);


            napi_set_named_property(env, exports, name.c_str(), exported_function);

            // 注册变量传递
            napi_wrap(env, exports, NULL, NULL, NULL, NULL);
        }

    protected:
        /**
         * @brief 处理数据更新 这里是异步的
         *
         * @param env
         * @param data
         */
        static void asyncWorkFun(napi_env env, void* data)
        {
            resultSend = PromiseWorkFunc();
        }

        /**
         * @brief 运行结束的时候会执行此 这里是同步的
         *
         * @param env
         * @param status
         * @param data
         */
        static void completeWork(napi_env env, napi_status status, void* data)
        {
            if (status != napi_ok)
                return;
         
            napi_resolve_deferred(env, deferred, format_to_js_value(env, resultSend));

            // 清理与此运行关联的工作环境
            napi_delete_async_work(env, work);

            deferred._Storage._Value = NULL;
            work._Storage._Value = NULL;
            resultSend.reset();
            resultSend = std::any();
            arguments_list.clear();
            arguments_list.resize(0);
        }

        static napi_value startWork(napi_env env, napi_callback_info info)
        {
            napi_value result, work_name, promise;
            napi_get_null(env, &result);

            std::string work_message = std::string(__FUNCTION__).append("  work_message ->  ");

            // 上个函数还没结束
            if (work != NULL)
            {
                work_message.append("error < Promise workspace has not been released. > ");
                napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
                return result;
            }

            // 创建一个字符串来描述这个异步操作。

            work_message.append("Node-API Deferred Promise from Async Work Item");

            napi_create_string_utf8(env, work_message.c_str(), work_message.length(), &work_name);

            napi_async_work addon_napi_async_work = NULL;
            napi_deferred addon_deferred = NULL;

            // 创建一个延迟的promise对象，在完成时我们将解决它
            napi_create_promise(env, &addon_deferred, &promise);


            // 创建一个异步工作项，传递插件数据，这将使
            // 工作线程访问上述创建的延迟的 promise对象
            napi_create_async_work(env,
                NULL,
                work_name,
                asyncWorkFun,
                completeWork, NULL, &addon_napi_async_work);

            // 添加进node的异步队列
            napi_queue_async_work(env, addon_napi_async_work);

            work._Storage._Value = addon_napi_async_work;
            deferred._Storage._Value = addon_deferred;

            return promise;
        }
    };

    void exports(napi_env env, napi_value exports,std::string name ) {
        (new PromiseFunction) -> exports(env, exports, name.c_str());
    }

};





napi_value Init(napi_env env, napi_value exports)
{
    PromiseFunction::exports(env, exports,"startThread");
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
