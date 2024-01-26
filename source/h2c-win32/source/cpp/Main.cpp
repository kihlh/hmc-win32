#include "./main.h"
#include "./export/export.h"
#include "./module/hmc_automation_util.h"



static void hmc_gc_func()
{
    // 防止鼠标被锁定
    if (hmc_mouse::LimitMouseRange::hasLimitMouseRange_worker())
    {
        hmc_mouse::LimitMouseRange::stopLimitMouseRange_worker();
    }

    // 释放鼠标监听的线程
    if (!hmc_mouse::MouseHook::isValidHookMouse())
    {
        hmc_mouse::MouseHook::stopHookMouse();
    }

    // 释放键盘监听的线程
    if (!hmc_Keyboard::keyboardHook::isValidHookKeyboard())
    {
        hmc_Keyboard::keyboardHook::stopHookKeyboard();
    }

}

static napi_value Init(napi_env env, napi_value exports)
{

    napi_property_descriptor BIND_NAPI_METHOD[] = {

        // clip.cpp
        DECLARE_NAPI_METHODRM("_load_ClipboardFunc", ClipboardFunc),
        
    };
    
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);

    atexit(hmc_gc_func);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
