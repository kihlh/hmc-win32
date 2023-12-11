#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

namespace PromiseFun {

typedef struct {
  // 工作环境
  napi_async_work work;
  // napi处理延迟的内联
  napi_deferred deferred;
  // 数据体的内存 必须是固定大小的值 不能动态调整内存
  // vector<string> data;
} PromiseData;

/**
 * @brief 处理数据更新 这里是异步的
 *
 * @param env
 * @param data
 */
void asyncWorkFun(napi_env env, void* data) {
  PromiseData* addon_data = (PromiseData*)data;
}

/**
 * @brief 运行结束的时候会执行此 这里是同步的
 *
 * @param env
 * @param status
 * @param data
 */
void completeWork(napi_env env, napi_status status, void* data) {
  if (status != napi_ok) {
    return;
  }

  PromiseData* addon_data = (PromiseData*)data;
  napi_value result;

  napi_create_array(env, &result);

  napi_resolve_deferred(env, addon_data->deferred, result);

  // 清理与此运行关联的工作环境
  napi_delete_async_work(env, addon_data->work);

  // 将这两个值都设置为NULL，这样JavaScript可以启动新的线程运行。
  addon_data->work = NULL;
  addon_data->deferred = NULL;
}

/**
 * @brief 创建一个 promise对象
 *
 * @param env
 * @param info
 * @return napi_value
 */
napi_value startWork(napi_env env, napi_callback_info info) {
  napi_value work_name, promise;
  PromiseData* addon_data;
  
  string work_message = string(__FUNCTION__).append("  work_message ->  ");

  // 获取插件的工作数据。
  napi_get_cb_info(env, info, NULL, NULL, NULL, (void**)(&addon_data));

  // 添加一个工作线程的 结构体

  if (addon_data->work != NULL) {
    work_message.append("error < Promise workspace has not been released. > ");
    napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
    return NULL;
  }

  // 创建一个字符串来描述这个异步操作。

  work_message.append("Node-API Deferred Promise from Async Work Item");
  napi_create_string_utf8(
      env, work_message.c_str(), work_message.length(), &work_name);

  // 创建一个延迟的promise对象，在完成时我们将解决它
  napi_create_promise(env, &(addon_data->deferred), &promise);

  // 创建一个异步工作项，传递插件数据，这将使
  // 工作线程访问上述创建的延迟的 promise对象
  napi_create_async_work(env,
                         NULL,
                         work_name,
                         asyncWorkFun,
                         completeWork,
                         addon_data,
                         &(addon_data->work));

  // 添加进node的异步队列
  napi_queue_async_work(env, addon_data->work);

  return promise;
}

/**
 * @brief 释放内存 请注意这里是模块卸载时候才执行
 *
 * @param env
 * @param data
 * @param hint
 */
void gcWork(napi_env env, void* data, void* hint) {
  PromiseData* addon_data = (PromiseData*)data;


  free(addon_data);
}

/**
 * @brief 导出这个异步函数
 *
 * @param env
 * @param exports
 * @param name
 */
void exports(napi_env env, napi_value exports, string name) {
  PromiseData* addon_data = (PromiseData*)malloc(sizeof(*addon_data));
  
  addon_data->work = NULL;

  napi_value exported_function;

  napi_create_function(env,
                       name.c_str(),
                       NAPI_AUTO_LENGTH,
                       startWork,
                       addon_data,
                       &exported_function);

  napi_set_named_property(env, exports, name.c_str(), exported_function);

  // 回收
  napi_wrap(env, exports, addon_data, gcWork, NULL, NULL);
}

}  // namespace PromiseFun

napi_value Init(napi_env env, napi_value exports) {
  PromiseFun::exports(env, exports, string("aaaa"));
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
