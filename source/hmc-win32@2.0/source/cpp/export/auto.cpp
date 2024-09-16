#include "export.h"
#include "hmc_napi_value_util.h"
#include "hmc_automation_util.h"

namespace NapiPromise
{
    struct EnvNextWorkData
    {
        napi_deferred deferred;
        napi_async_work work;
        int index;
        void *data;
    };

    // async
    void ExecuteAsyncWork(napi_env env, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
    }

    // 异步任务完成后的回调函数
    void ResolveWork(napi_env env, napi_status status, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
        napi_value result;
        napi_get_undefined(env, &result);

        napi_resolve_deferred(env, workData->deferred, result);
        napi_delete_async_work(env, workData->work);
        delete workData;
    }

    // 启动异步任务的函数
    napi_value StartAsyncTask(napi_env env, napi_callback_info info)
    {
        napi_value promise;
        napi_value resourceName;
        napi_create_string_utf8(env, __FUNCSIG__ , NAPI_AUTO_LENGTH, &resourceName);

        // 初始化异步工作的数据
        EnvNextWorkData *workData = new EnvNextWorkData();
        workData->index = 5;

        napi_create_promise(env, &workData->deferred, &promise);
        napi_create_async_work(env, nullptr, resourceName, ExecuteAsyncWork, ResolveWork, workData, &workData->work);
        napi_queue_async_work(env, workData->work);
        return promise;
    }

    // 初始化模块
    napi_value Init(napi_env env, napi_value exports, const char *utf8name)
    {
        napi_value asyncTaskFunction;
        napi_create_function(env, nullptr, 0, StartAsyncTask, nullptr, &asyncTaskFunction);
        napi_set_named_property(env, exports, utf8name, asyncTaskFunction);
    }

}

