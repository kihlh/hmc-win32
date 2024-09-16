#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

typedef struct {
    int32_t input;        // 输入参数
    int32_t result;       // 计算结果
    napi_ref callback;    // JavaScript 回调
    napi_async_work work; // N-API 异步工作
} AsyncWorkData;


void ExecuteTask(napi_env env, void* data) {
    AsyncWorkData* workData = (AsyncWorkData*)data;
    
        std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟异步任务（例如：IO操作）

    // 模拟异步任务，耗时计算
    int input = workData->input;
    workData->result = input * 2;  // 假设任务是计算输入值的2倍
}

void CompleteTask(napi_env env, napi_status status, void* data) {
    napi_value result, callback, undefined;
    napi_status status_code;
    AsyncWorkData* workData = (AsyncWorkData*)data;

    // 创建返回值
    status_code = napi_create_int32(env, workData->result, &result);

    // 获取 undefined 值用于回调
    status_code = napi_get_undefined(env, &undefined);

    // 获取回调函数
    status_code = napi_get_reference_value(env, workData->callback, &callback);

    // 创建回调参数数组（第一个参数是错误，第二个是结果）
    napi_value argv[2];
    napi_get_null(env, &argv[0]);  // 没有错误
    argv[1] = result;

    // 调用 JavaScript 回调函数
    status_code = napi_call_function(env, undefined, callback, 2, argv, NULL);

    // 清理内存
    napi_delete_reference(env, workData->callback);
    napi_delete_async_work(env, workData->work);
    free(workData);
}


napi_value StartAsyncTask(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_value resource_name;
    napi_status status;

    // 解析输入参数
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    // 第一个参数是整数（输入值）
    int32_t input;
    napi_get_value_int32(env, args[0], &input);

    // 第二个参数是回调函数
    napi_value callback = args[1];

    // 创建异步工作数据
    AsyncWorkData* workData = (AsyncWorkData*)malloc(sizeof(AsyncWorkData));
    workData->input = input;
    napi_create_reference(env, callback, 1, &workData->callback);

    // 创建异步工作名称
    napi_create_string_utf8(env, "AsyncTask", NAPI_AUTO_LENGTH, &resource_name);

    // 创建异步工作
    napi_create_async_work(env, NULL, resource_name, ExecuteTask, CompleteTask, workData, &workData->work);

    // 将工作推入队列，开始执行异步任务
    napi_queue_async_work(env, workData->work);

    return NULL;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_value asyncTaskFunction;
    napi_create_function(env, NULL, 0, StartAsyncTask, NULL, &asyncTaskFunction);
    napi_set_named_property(env, exports, "startAsyncTask", asyncTaskFunction);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
