#include <assert.h>
#include <stdlib.h>
#define NAPI_EXPERIMENTAL
#include <node_api.h>
#include <string>

// Limit ourselves to this many primes, starting at 2
#define PRIME_COUNT 100000
#define REPORT_EVERY 1000

typedef struct
{
  napi_async_work work;
  napi_threadsafe_function tsfn;
} AddonData;


/**
 * @brief 向js发生一次回调 这里也是同步的
 * 此函数负责将来自工作线程的数据转换为napi_value项，以便传递到JavaScript，并调用JavaScript函数。
 * 
 * @param env node environment
 * @param js_cb node 的回调函数 
 * @param context  附加到生成的 napi_threadsafe_function 的可选数据。
 * @param data 数据体 的指针
 */
static void CallJs(napi_env env, napi_value js_cb, void *context, void *data)
{
  // 不使用此参数。
  (void)context;
  napi_status status;

  // 从工作线程创建的项中获取质数。
  int the_prime = *(int *)data;

  //如果Node.js处于清理阶段，并且存在来自之前由工作线程发起的线程安全调用的剩余项，则`env`和`js_cb`都可以为NULL。当`env`为NULL时，我们直接跳过对JavaScript的调用并释放这些项。
  if (env != NULL)
  {
    napi_value undefined, js_the_prime;

    // 将整数转换为napi_value。
    status = napi_create_int32(env, the_prime, &js_the_prime);
    assert(status == napi_ok);

    // 获取JavaScript中的`undefined`值，以便我们可以将其用作JavaScript函数调用的`this`值。
    status = napi_get_undefined(env, &undefined);
    assert(status == napi_ok);

    // 调用JavaScript函数并传递由辅助线程找到的质数。
    status = napi_call_function(env,
                                undefined,
                                js_cb,
                                1,
                                &js_the_prime,
                                NULL);
    assert(status == napi_ok);
  }

  // 释放内存
  free(data);
}

// 此函数在工作线程上运行。除了通过线程安全函数外，它无法访问JavaScript环境。
static void ExecuteWork(napi_env env, void *data)
{
  AddonData *addon_data = (AddonData *)data;
  int idx_inner, idx_outer;
  int prime_count = 0;
  napi_status status;

  // 在这个线程中，我们通过调用 `napi_acquire_threadsafe_function()` 来标记对线程安全函数的使用，
  // 并在线程退出之前立即调用 `napi_release_threadsafe_function()` 进行标记。
  
  status = napi_acquire_threadsafe_function(addon_data->tsfn);
  assert(status == napi_ok);

  // 使用一个极其低效的算法找出前1000个质数。
  for (idx_outer = 2; prime_count < PRIME_COUNT; idx_outer++)
  {
    for (idx_inner = 2; idx_inner < idx_outer; idx_inner++)
    {
      if (idx_outer % idx_inner == 0)
      {
        break;
      }
    }
    if (idx_inner < idx_outer)
    {
      continue;
    }

    // 我们找到一个质数。如果它是自上次发送到JavaScript以来的第十个质数，请将其发送到JavaScript。
    if (!(++prime_count % REPORT_EVERY))
    {

      // 将质数保存到堆上。JavaScript的驱动程序（CallJs）将在将其发送给JavaScript后释放此项。
      int *the_prime = (int *)malloc(sizeof(*the_prime));
      *the_prime = idx_outer;

      // 触发对JavaScript的调用。当此函数返回时，对JavaScript的调用尚未发生，但将被加入队列中。
      status = napi_call_threadsafe_function(addon_data->tsfn,
                                             the_prime,
                                             napi_tsfn_blocking);
      assert(status == napi_ok);
    }
  }

  // 表示该线程将不再使用线程安全函数。
  status = napi_release_threadsafe_function(addon_data->tsfn,
                                            napi_tsfn_release);
  assert(status == napi_ok);
}

// 异步函数结束时候发生的回调 是同步的
static void WorkComplete(napi_env env, napi_status status, void *data)
{
  AddonData *addon_data = (AddonData *)data;

  //清理与此运行相关的线程安全函数和工作项。
  status = napi_release_threadsafe_function(addon_data->tsfn,
                                            napi_tsfn_release);
  assert(status == napi_ok);
  status = napi_delete_async_work(env, addon_data->work);
  assert(status == napi_ok);

  // 将这两个值都设置为NULL，这样JavaScript可以重新启动线程的运行。
  addon_data->work = NULL;
  addon_data->tsfn = NULL;
}

// 创建一个线程安全函数和一个异步队列工作项。我们将线程安全函数传递给异步队列工作项，以便后者有机会从运行ExecuteWork回调函数的工作线程中调用JavaScript。
static napi_value StartThread(napi_env env, napi_callback_info info)
{
  size_t argc = 1;
  napi_value js_cb, work_name;
  AddonData *addon_data;
  napi_status status;

  std::string work_message = std::string(__FUNCTION__).append("  work_message ->  ");

  // 获取应该用由工作线程生成的项和插件数据调用的JavaScript回调。
  status = napi_get_cb_info(env, info, &argc, &js_cb, NULL, (void **)(&addon_data));
  assert(status == napi_ok);

  // 确保当前没有正在进行的工作。
  if (addon_data->work != NULL)
  {
    work_message.append("error < Promise workspace has not been released. > ");
    napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
    return NULL;
  }
  // 创建一个字符串来描述这个异步操作。
  work_message.append("Node-API Deferred Promise from Async Work Item");

  napi_create_string_utf8(env, work_message.c_str(), work_message.length(), &work_name);
  assert(status == napi_ok);

  // 将从JavaScript获取的回调函数转换为一个线程安全的函数，这样我们就可以从工作线程中调用它。
  status = napi_create_threadsafe_function(env,
                                           js_cb,
                                           NULL,
                                           work_name,
                                           0,
                                           1,
                                           NULL,
                                           NULL,
                                           NULL,
                                           CallJs,
                                           &(addon_data->tsfn));
  assert(status == napi_ok);

  // 创建一个异步工作项，传入插件数据，这样工作线程就可以访问上述创建的线程安全函数。
  status = napi_create_async_work(env,
                                  NULL,
                                  work_name,
                                  ExecuteWork,
                                  WorkComplete,
                                  addon_data,
                                  &(addon_data->work));
  assert(status == napi_ok);

  // 将工作项加入队列以执行。
  status = napi_queue_async_work(env, addon_data->work);
  assert(status == napi_ok);

  // 这会导致返回`undefined`给JavaScript。
  return NULL;
}

// 回收函数结束后的环境
static void addon_getting_unloaded(napi_env env, void *data, void *hint)
{
  AddonData *addon_data = (AddonData *)data;
  assert(addon_data->work == NULL &&
         "No work item in progress at module unload");
  free(addon_data);
}

// The commented-out return type and the commented out formal function
// parameters below help us keep in mind the signature of the addon
// initialization function. We write the body as though the return value were as
// commented below and as though there were parameters passed in as commented
// below.
/*napi_value*/ NAPI_MODULE_INIT(/*napi_env env, napi_value exports*/)
{
  napi_status status;
  // Define addon-level data associated with this instance of the addon.
  AddonData *addon_data = (AddonData *)malloc(sizeof(*addon_data));
  addon_data->work = NULL;

  // Define the properties that will be set on exports.
  napi_property_descriptor start_work = {
      "startThread",
      NULL,
      StartThread,
      NULL,
      NULL,
      NULL,
      napi_default,
      addon_data};

  // Decorate exports with the above-defined properties.
  status = napi_define_properties(env, exports, 1, &start_work);
  assert(status == napi_ok);

  // Associate the addon data with the exports object, to make sure that when
  // the addon gets unloaded our data gets freed.
  status = napi_wrap(env,
                     exports,
                     addon_data,
                     addon_getting_unloaded,
                     NULL,
                     NULL);
  assert(status == napi_ok);

  // Return the decorated exports object.
  return exports;
}
