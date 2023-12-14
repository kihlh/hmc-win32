#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

typedef struct {
  napi_async_work work;
  napi_deferred deferred;
  vector<string> data;
} PromiseData;

// 工作线程 上面运行的函数
static void ExecuteWork(napi_env env, void* data) {
  PromiseData* addon_data = (PromiseData*)data;
}

// ExecuteWork 运行结束的时候会执行此
static void WorkComplete(napi_env env, napi_status status, void* data) {
  if (status != napi_ok) {
    return;
  }

  PromiseData* addon_data = (PromiseData*)data;
  napi_value array;

  napi_create_array(env, &array);

  napi_resolve_deferred(env, addon_data->deferred, array);

  // 清理与此运行关联的工作环境
  napi_delete_async_work(env, addon_data->work);

  // 将这两个值都设置为NULL，这样JavaScript可以启动新的线程运行。
  addon_data->work = NULL;
  addon_data->deferred = NULL;
}

/**创建一个 promise对象*/
static napi_value StartWork(napi_env env, napi_callback_info info) {
  napi_value work_name, promise;
  PromiseData* addon_data;

  // 获取每个插件的数据。
  napi_get_cb_info(env, info, NULL, NULL, NULL, (void**)(&addon_data));

  // 添加一个工作线程的 结构体
  // addon_data->work;

  // 创建一个字符串来描述这个异步操作。

  napi_create_string_utf8(env,
                          "Node-API Deferred Promise from Async Work Item",
                          NAPI_AUTO_LENGTH,
                          &work_name);

  // 创建一个延迟的promise对象，在完成时我们将解决它
  napi_create_promise(env, &(addon_data->deferred), &promise);

  // 创建一个异步工作项，传递插件数据，这将使
  // 工作线程访问上述创建的延迟的 promise对象
  napi_create_async_work(env,
                         NULL,
                         work_name,
                         ExecuteWork,
                         WorkComplete,
                         addon_data,
                         &(addon_data->work));

  // 添加进node的异步队列
  napi_queue_async_work(env, addon_data->work);

  return promise;
}

/**
 * @brief 释放内存
 *
 * @param env
 * @param data
 * @param hint
 */
static void addon_getting_unloaded(napi_env env, void* data, void* hint) {
  PromiseData* addon_data = (PromiseData*)data;
  // addon_data->work == NULL;
  free(addon_data);
}

static napi_value Init(napi_env env, napi_value exports) {
  PromiseData* addon_data = (PromiseData*)malloc(sizeof(*addon_data));
  addon_data->work = NULL;

  // 导出模块
  napi_property_descriptor BIND_NAPI_METHOD[] = {
      {"startWork",
       NULL,
       StartWork,
       NULL,
       NULL,
       NULL,
       napi_default,
       addon_data},
  };

  napi_define_properties(env,
                         exports,
                         sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]),
                         BIND_NAPI_METHOD);
                         
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
