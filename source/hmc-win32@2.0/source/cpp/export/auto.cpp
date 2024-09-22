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
        napi_create_string_utf8(env, __FUNCSIG__, NAPI_AUTO_LENGTH, &resourceName);

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

namespace HMC_Keyboard
{

    using KHOOK = hmc_Keyboard::keyboardHook;

    // 构造函数的声明周期句柄
    napi_ref CONSTRUCTOR_LIFETIME_HANDLE = NULL;

    napi_value initKeyboardEventHook(napi_env env, napi_callback_info info)
    {

        bool isInitKeyboardEventHook = KHOOK::initKeyboardEventHook();

        return as_Boolean(isInitKeyboardEventHook);
    }

    napi_value isValidHookKeyboard(napi_env env, napi_callback_info info)
    {

        bool isValidHookKeyboard = KHOOK::isValidHookKeyboard();
        if (isValidHookKeyboard)
        {
            return as_Number32(KHOOK::getThreadId());
        }
        return as_Boolean(isValidHookKeyboard);
    }

    napi_value hasKeyActivate(napi_env env, napi_callback_info info)
    {

        napi_value result = as_Boolean(false);
        auto input = hmc_NodeArgsValue(env, info);
        input.eq({{0, js_number}}, true);
        std::uint8_t keyName = at_Number32(0);
        result = as_Boolean(hmc_automation_util::hasKeyActivate(keyName));
        return result;
    }

    napi_value hasKeysBasic(napi_env env, napi_callback_info info)
    {

        auto Basic = hmc_Keyboard::hasKeysBasic();

        napi_value result = NULL;

        napi_create_object(env, &result);
        napi_set_named_property(env, result, "shift", as_Boolean(Basic.shift));
        napi_set_named_property(env, result, "alt", as_Boolean(Basic.alt));
        napi_set_named_property(env, result, "win", as_Boolean(Basic.win));
        napi_set_named_property(env, result, "ctrl", as_Boolean(Basic.ctrl));

        return result;
    }

    napi_value getAllKeyboardEventJson(napi_env env, napi_callback_info info)
    {

        std::string utf8JsonInfo = KHOOK::getAllKeyboardEventJson();

        return as_String(utf8JsonInfo);
    }

    napi_value stopHookKeyboard(napi_env env, napi_callback_info info)
    {
        bool isStopHookKeyboard = KHOOK::stopHookKeyboard();

        return as_Boolean(isStopHookKeyboard);
    }

    napi_value StartupClassConstructor(napi_env env, napi_callback_info info)
    {

        if (CONSTRUCTOR_LIFETIME_HANDLE != NULL)
        {
            return NULL;
        }

        napi_value constructor;
        napi_value result;
        napi_status status;

        napi_create_object(env, &result);

        napi_set_named_property(env, result, as_ExFunctionNameAp(initKeyboardEventHook));
        napi_set_named_property(env, result, as_ExFunctionNameAp(isValidHookKeyboard));
        napi_set_named_property(env, result, as_ExFunctionNameAp(getAllKeyboardEventJson));
        napi_set_named_property(env, result, as_ExFunctionNameAp(stopHookKeyboard));
        napi_set_named_property(env, result, as_ExFunctionNameAp(hasKeysBasic));
        napi_set_named_property(env, result, as_ExFunctionNameAp(hasKeyActivate));

        // 注册长生命周期
        status = napi_create_reference(env, result, 1, &CONSTRUCTOR_LIFETIME_HANDLE);
        if (status != napi_ok)
            return NULL;

        return result;
    }

}

namespace HMC_mouse
{

    using MHOOK = hmc_mouse::MouseHook;

    // 构造函数的声明周期句柄
    napi_ref CONSTRUCTOR_LIFETIME_HANDLE = NULL;

    napi_value initMouseEventHook(napi_env env, napi_callback_info info)
    {

        bool isInitKeyboardEventHook = MHOOK::initMouseEventHook();

        return as_Boolean(isInitKeyboardEventHook);
    }

    napi_value isValidHookMouse(napi_env env, napi_callback_info info)
    {

        bool isValid = MHOOK::isValidHookMouse();
        if (isValid)
        {
            return as_Number32(MHOOK::getThreadId());
        }
        return as_Boolean(isValid);
    }

    napi_value getMouseEventListJson(napi_env env, napi_callback_info info)
    {

        std::string utf8JsonInfo = MHOOK::getMouseEventListJsonA();

        return as_String(utf8JsonInfo);
    }

    napi_value stopHookMouse(napi_env env, napi_callback_info info)
    {
        bool isStopHookKeyboard = MHOOK::stopHookMouse();

        return as_Boolean(isStopHookKeyboard);
    }

    napi_value setShakeEventTime(napi_env env, napi_callback_info info)
    {

        napi_value result = as_Null();

        auto input = hmc_NodeArgsValue(env, info);
        input.eq({{0, js_number}}, true);

        long ShakeEventTime = at_Number64(0);
        MHOOK::setShakeEventTime(ShakeEventTime);

        return result;
    }

    napi_value setLimitMouseRange(napi_env env, napi_callback_info info)
    {

        napi_value result = as_Boolean(false);

        auto input = hmc_NodeArgsValue(env, info);
        input.eq({js_number,js_number,js_number,js_number,js_number}, true);

        long ms = at_Number64(0);
        long x = at_Number64(1);
        long y = at_Number64(2);
        long right = at_Number64(3);
        long bottom = at_Number64(4);


        bool res_temp = hmc_mouse::LimitMouseRange::setLimitMouseRange(ms,x,y,right,bottom);

        result = as_Boolean(res_temp);
        return result;
    }

    napi_value hasLimitMouseRangeWorker(napi_env env, napi_callback_info info)
    {
        bool state =  hmc_mouse::LimitMouseRange::hasLimitMouseRange_worker();

        return as_Boolean(state);
    }

    napi_value stopLimitMouseRangeWorker(napi_env env, napi_callback_info info)
    {
        bool state =  hmc_mouse::LimitMouseRange::stopLimitMouseRange_worker();

        return as_Boolean(state);
    }

    napi_value StartupClassConstructor(napi_env env, napi_callback_info info)
    {

        if (CONSTRUCTOR_LIFETIME_HANDLE != NULL)
        {
            return NULL;
        }

        napi_value constructor;
        napi_value result;
        napi_status status;

        napi_create_object(env, &result);

        napi_set_named_property(env, result, as_ExFunctionNameAp(initMouseEventHook));
        napi_set_named_property(env, result, as_ExFunctionNameAp(isValidHookMouse));
        napi_set_named_property(env, result, as_ExFunctionNameAp(getMouseEventListJson));
        napi_set_named_property(env, result, as_ExFunctionNameAp(stopHookMouse));
        napi_set_named_property(env, result, as_ExFunctionNameAp(setShakeEventTime));

        napi_set_named_property(env, result, as_ExFunctionNameAp(setLimitMouseRange));
        napi_set_named_property(env, result, as_ExFunctionNameAp(hasLimitMouseRangeWorker));
        napi_set_named_property(env, result, as_ExFunctionNameAp(stopLimitMouseRangeWorker));

        // 注册长生命周期
        status = napi_create_reference(env, result, 1, &CONSTRUCTOR_LIFETIME_HANDLE);
        if (status != napi_ok)
            return NULL;

        return result;
    }

}