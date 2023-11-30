#include "Main.h"
#include <map>
#include "./AutoItX3/AutoItX3_DLL.h"
#include "../CPP_Reconfig/util/include/json.hpp"
using json = nlohmann::json;
#include "../CPP_Reconfig/util/console.hpp"
#include "../CPP_Reconfig/util/text.hpp"
#include "../CPP_Reconfig/util/napi_util.hpp"

// #pragma comment(lib, "./AutoItX3/AutoItX3_DLL.lib")
// #pragma comment(lib, "./AutoItX3/AutoItX3\\AutoItX3_x64_DLL.lib")

#ifdef _MSC_VER

#ifdef _M_IX86
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_DLL.lib")

#elif defined(_M_X64) || defined(_M_AMD64)
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_x64_DLL.lib")

#endif //_M_IX86
#endif//_MSC_VER

#ifdef SRC_NODE_API_H_
#define HMC_NAPI_CHECK_CATCH              \
    catch (char *err)                     \
    {                                     \
        napi_get_undefined(env, &result); \
    }
;
#else 
#define HMC_NAPI_CHECK_CATCH              \
    catch (char *err)                     \
    {                                     \
       cout << err << "\n";                \ 
    }

#endif //SRC_NODE_API_H_


static napi_value hmc_au3_Init(napi_env env, napi_callback_info info)
{
    napi_value result;
    napi_get_undefined(env, &result);
    try
    {
        AU3_Init();
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_error(napi_env env, napi_callback_info info)
{
    napi_value result;
    try
    {
        result = hmc_napi_util::create_value::Number(env, AU3_error());
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_AutoItSetOption(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    $napi_get_cb_info(argc, argv, "hmc_au3_AutoItSetOption");
    napi_value result;
    napi_get_undefined(env, &result);

    try
    {
        wstring szOption = hmc_napi_util::get_value::string_wide(env, argv[0]);
        int nValue = hmc_napi_util::get_value::number_int(env, argv[1]);
        result = hmc_napi_util::create_value::Number(env, AU3_AutoItSetOption((LPWSTR)szOption.c_str(), nValue));
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ClipGet(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    $napi_get_cb_info(argc, argv, "hmc_au3_ClipGet");
    napi_value result;
    napi_get_undefined(env, &result);

    try
    {
        int nBufSize = hmc_napi_util::get_value::number_int(env, argv[0]);
        // 这里要动态开辟内存
        AU3_ClipGet((LPWSTR)szClip.c_str(), nBufSize);
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ClipPut(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    $napi_get_cb_info(argc, argv, "hmc_au3_ClipPut");
    napi_get_undefined(env, &result);

    try
    {
        wstring szClip = hmc_napi_util::get_value::string_wide(env, argv[0]);
        AU3_ClipPut(szClip.c_str());
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlClick(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlClickByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlCommand(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlCommandByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlListView(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlListViewByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlDisable(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlDisableByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlEnable(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlEnableByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlFocus(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlFocusByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlGetFocus(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlGetFocusByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlGetHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlGetHandleAsText(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlGetPos(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlGetPosByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlGetText(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlGetTextByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlHide(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlHideByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlMove(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlMoveByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlSend(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlSendByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlSetText(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlSetTextByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlShow(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlShowByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlTreeView(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ControlTreeViewByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_DriveMapAdd(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_DriveMapDel(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_DriveMapGet(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_IsAdmin(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_MouseClick(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_MouseClickDrag(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_MouseDown(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_MouseGetCursor(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_MouseGetPos(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_MouseMove(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_MouseUp(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_MouseWheel(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_Opt(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_PixelChecksum(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_PixelGetColor(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_PixelSearch(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ProcessClose(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ProcessExists(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ProcessSetPriority(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ProcessWait(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ProcessWaitClose(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_Run(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_RunWait(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_RunAs(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_RunAsWait(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_Send(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_Shutdown(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_Sleep(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_StatusbarGetText(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_StatusbarGetTextByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_ToolTip(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinActivate(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinActivateByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinActive(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinActiveByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinClose(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinCloseByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinExists(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinExistsByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetCaretPos(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetClassList(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetClassListByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetClientSize(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetClientSizeByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetHandleAsText(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetPos(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetPosByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetProcess(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetProcessByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetState(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetStateByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetText(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetTextByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetTitle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinGetTitleByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinKill(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinKillByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinMenuSelectItem(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinMenuSelectItemByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinMinimizeAll(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinMinimizeAllUndo(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinMove(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinMoveByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinSetOnTop(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinSetOnTopByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinSetState(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinSetStateByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinSetTitle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinSetTitleByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinSetTrans(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinSetTransByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinWait(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinWaitByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinWaitActive(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinWaitActiveByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinWaitClose(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinWaitCloseByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinWaitNotActive(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value hmc_au3_WinWaitNotActiveByHandle(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    try
    {
    }
    HMC_NAPI_CHECK_CATCH;
    return result;
}

static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor BIND_NAPI_METHOD[] = {
        DECLARE_NAPI_METHOD("Init", hmc_au3_Init),
        DECLARE_NAPI_METHOD("error", hmc_au3_error),
        DECLARE_NAPI_METHOD("AutoItSetOption", hmc_au3_AutoItSetOption),
        DECLARE_NAPI_METHOD("ClipGet", hmc_au3_ClipGet),
        DECLARE_NAPI_METHOD("ClipPut", hmc_au3_ClipPut),
        DECLARE_NAPI_METHOD("ControlClick", hmc_au3_ControlClick),
        DECLARE_NAPI_METHOD("ControlClickByHandle", hmc_au3_ControlClickByHandle),
        DECLARE_NAPI_METHOD("ControlCommand", hmc_au3_ControlCommand),
        DECLARE_NAPI_METHOD("ControlCommandByHandle", hmc_au3_ControlCommandByHandle),
        DECLARE_NAPI_METHOD("ControlListView", hmc_au3_ControlListView),
        DECLARE_NAPI_METHOD("ControlListViewByHandle", hmc_au3_ControlListViewByHandle),
        DECLARE_NAPI_METHOD("ControlDisable", hmc_au3_ControlDisable),
        DECLARE_NAPI_METHOD("ControlDisableByHandle", hmc_au3_ControlDisableByHandle),
        DECLARE_NAPI_METHOD("ControlEnable", hmc_au3_ControlEnable),
        DECLARE_NAPI_METHOD("ControlEnableByHandle", hmc_au3_ControlEnableByHandle),
        DECLARE_NAPI_METHOD("ControlFocus", hmc_au3_ControlFocus),
        DECLARE_NAPI_METHOD("ControlFocusByHandle", hmc_au3_ControlFocusByHandle),
        DECLARE_NAPI_METHOD("ControlGetFocus", hmc_au3_ControlGetFocus),
        DECLARE_NAPI_METHOD("ControlGetFocusByHandle", hmc_au3_ControlGetFocusByHandle),
        DECLARE_NAPI_METHOD("ControlGetHandle", hmc_au3_ControlGetHandle),
        DECLARE_NAPI_METHOD("ControlGetHandleAsText", hmc_au3_ControlGetHandleAsText),
        DECLARE_NAPI_METHOD("ControlGetPos", hmc_au3_ControlGetPos),
        DECLARE_NAPI_METHOD("ControlGetPosByHandle", hmc_au3_ControlGetPosByHandle),
        DECLARE_NAPI_METHOD("ControlGetText", hmc_au3_ControlGetText),
        DECLARE_NAPI_METHOD("ControlGetTextByHandle", hmc_au3_ControlGetTextByHandle),
        DECLARE_NAPI_METHOD("ControlHide", hmc_au3_ControlHide),
        DECLARE_NAPI_METHOD("ControlHideByHandle", hmc_au3_ControlHideByHandle),
        DECLARE_NAPI_METHOD("ControlMove", hmc_au3_ControlMove),
        DECLARE_NAPI_METHOD("ControlMoveByHandle", hmc_au3_ControlMoveByHandle),
        DECLARE_NAPI_METHOD("ControlSend", hmc_au3_ControlSend),
        DECLARE_NAPI_METHOD("ControlSendByHandle", hmc_au3_ControlSendByHandle),
        DECLARE_NAPI_METHOD("ControlSetText", hmc_au3_ControlSetText),
        DECLARE_NAPI_METHOD("ControlSetTextByHandle", hmc_au3_ControlSetTextByHandle),
        DECLARE_NAPI_METHOD("ControlShow", hmc_au3_ControlShow),
        DECLARE_NAPI_METHOD("ControlShowByHandle", hmc_au3_ControlShowByHandle),
        DECLARE_NAPI_METHOD("ControlTreeView", hmc_au3_ControlTreeView),
        DECLARE_NAPI_METHOD("ControlTreeViewByHandle", hmc_au3_ControlTreeViewByHandle),
        DECLARE_NAPI_METHOD("DriveMapAdd", hmc_au3_DriveMapAdd),
        DECLARE_NAPI_METHOD("DriveMapDel", hmc_au3_DriveMapDel),
        DECLARE_NAPI_METHOD("DriveMapGet", hmc_au3_DriveMapGet),
        DECLARE_NAPI_METHOD("IsAdmin", hmc_au3_IsAdmin),
        DECLARE_NAPI_METHOD("MouseClick", hmc_au3_MouseClick),
        DECLARE_NAPI_METHOD("MouseClickDrag", hmc_au3_MouseClickDrag),
        DECLARE_NAPI_METHOD("MouseDown", hmc_au3_MouseDown),
        DECLARE_NAPI_METHOD("MouseGetCursor", hmc_au3_MouseGetCursor),
        DECLARE_NAPI_METHOD("MouseGetPos", hmc_au3_MouseGetPos),
        DECLARE_NAPI_METHOD("MouseMove", hmc_au3_MouseMove),
        DECLARE_NAPI_METHOD("MouseUp", hmc_au3_MouseUp),
        DECLARE_NAPI_METHOD("MouseWheel", hmc_au3_MouseWheel),
        DECLARE_NAPI_METHOD("Opt", hmc_au3_Opt),
        DECLARE_NAPI_METHOD("PixelChecksum", hmc_au3_PixelChecksum),
        DECLARE_NAPI_METHOD("PixelGetColor", hmc_au3_PixelGetColor),
        DECLARE_NAPI_METHOD("PixelSearch", hmc_au3_PixelSearch),
        DECLARE_NAPI_METHOD("ProcessClose", hmc_au3_ProcessClose),
        DECLARE_NAPI_METHOD("ProcessExists", hmc_au3_ProcessExists),
        DECLARE_NAPI_METHOD("ProcessSetPriority", hmc_au3_ProcessSetPriority),
        DECLARE_NAPI_METHOD("ProcessWait", hmc_au3_ProcessWait),
        DECLARE_NAPI_METHOD("ProcessWaitClose", hmc_au3_ProcessWaitClose),
        DECLARE_NAPI_METHOD("Run", hmc_au3_Run),
        DECLARE_NAPI_METHOD("RunWait", hmc_au3_RunWait),
        DECLARE_NAPI_METHOD("RunAs", hmc_au3_RunAs),
        DECLARE_NAPI_METHOD("RunAsWait", hmc_au3_RunAsWait),
        DECLARE_NAPI_METHOD("Send", hmc_au3_Send),
        DECLARE_NAPI_METHOD("Shutdown", hmc_au3_Shutdown),
        DECLARE_NAPI_METHOD("Sleep", hmc_au3_Sleep),
        DECLARE_NAPI_METHOD("StatusbarGetText", hmc_au3_StatusbarGetText),
        DECLARE_NAPI_METHOD("StatusbarGetTextByHandle", hmc_au3_StatusbarGetTextByHandle),
        DECLARE_NAPI_METHOD("ToolTip", hmc_au3_ToolTip),
        DECLARE_NAPI_METHOD("WinActivate", hmc_au3_WinActivate),
        DECLARE_NAPI_METHOD("WinActivateByHandle", hmc_au3_WinActivateByHandle),
        DECLARE_NAPI_METHOD("WinActive", hmc_au3_WinActive),
        DECLARE_NAPI_METHOD("WinActiveByHandle", hmc_au3_WinActiveByHandle),
        DECLARE_NAPI_METHOD("WinClose", hmc_au3_WinClose),
        DECLARE_NAPI_METHOD("WinCloseByHandle", hmc_au3_WinCloseByHandle),
        DECLARE_NAPI_METHOD("WinExists", hmc_au3_WinExists),
        DECLARE_NAPI_METHOD("WinExistsByHandle", hmc_au3_WinExistsByHandle),
        DECLARE_NAPI_METHOD("WinGetCaretPos", hmc_au3_WinGetCaretPos),
        DECLARE_NAPI_METHOD("WinGetClassList", hmc_au3_WinGetClassList),
        DECLARE_NAPI_METHOD("WinGetClassListByHandle", hmc_au3_WinGetClassListByHandle),
        DECLARE_NAPI_METHOD("WinGetClientSize", hmc_au3_WinGetClientSize),
        DECLARE_NAPI_METHOD("WinGetClientSizeByHandle", hmc_au3_WinGetClientSizeByHandle),
        DECLARE_NAPI_METHOD("WinGetHandle", hmc_au3_WinGetHandle),
        DECLARE_NAPI_METHOD("WinGetHandleAsText", hmc_au3_WinGetHandleAsText),
        DECLARE_NAPI_METHOD("WinGetPos", hmc_au3_WinGetPos),
        DECLARE_NAPI_METHOD("WinGetPosByHandle", hmc_au3_WinGetPosByHandle),
        DECLARE_NAPI_METHOD("WinGetProcess", hmc_au3_WinGetProcess),
        DECLARE_NAPI_METHOD("WinGetProcessByHandle", hmc_au3_WinGetProcessByHandle),
        DECLARE_NAPI_METHOD("WinGetState", hmc_au3_WinGetState),
        DECLARE_NAPI_METHOD("WinGetStateByHandle", hmc_au3_WinGetStateByHandle),
        DECLARE_NAPI_METHOD("WinGetText", hmc_au3_WinGetText),
        DECLARE_NAPI_METHOD("WinGetTextByHandle", hmc_au3_WinGetTextByHandle),
        DECLARE_NAPI_METHOD("WinGetTitle", hmc_au3_WinGetTitle),
        DECLARE_NAPI_METHOD("WinGetTitleByHandle", hmc_au3_WinGetTitleByHandle),
        DECLARE_NAPI_METHOD("WinKill", hmc_au3_WinKill),
        DECLARE_NAPI_METHOD("WinKillByHandle", hmc_au3_WinKillByHandle),
        DECLARE_NAPI_METHOD("WinMenuSelectItem", hmc_au3_WinMenuSelectItem),
        DECLARE_NAPI_METHOD("WinMenuSelectItemByHandle", hmc_au3_WinMenuSelectItemByHandle),
        DECLARE_NAPI_METHOD("WinMinimizeAll", hmc_au3_WinMinimizeAll),
        DECLARE_NAPI_METHOD("WinMinimizeAllUndo", hmc_au3_WinMinimizeAllUndo),
        DECLARE_NAPI_METHOD("WinMove", hmc_au3_WinMove),
        DECLARE_NAPI_METHOD("WinMoveByHandle", hmc_au3_WinMoveByHandle),
        DECLARE_NAPI_METHOD("WinSetOnTop", hmc_au3_WinSetOnTop),
        DECLARE_NAPI_METHOD("WinSetOnTopByHandle", hmc_au3_WinSetOnTopByHandle),
        DECLARE_NAPI_METHOD("WinSetState", hmc_au3_WinSetState),
        DECLARE_NAPI_METHOD("WinSetStateByHandle", hmc_au3_WinSetStateByHandle),
        DECLARE_NAPI_METHOD("WinSetTitle", hmc_au3_WinSetTitle),
        DECLARE_NAPI_METHOD("WinSetTitleByHandle", hmc_au3_WinSetTitleByHandle),
        DECLARE_NAPI_METHOD("WinSetTrans", hmc_au3_WinSetTrans),
        DECLARE_NAPI_METHOD("WinSetTransByHandle", hmc_au3_WinSetTransByHandle),
        DECLARE_NAPI_METHOD("WinWait", hmc_au3_WinWait),
        DECLARE_NAPI_METHOD("WinWaitByHandle", hmc_au3_WinWaitByHandle),
        DECLARE_NAPI_METHOD("WinWaitActive", hmc_au3_WinWaitActive),
        DECLARE_NAPI_METHOD("WinWaitActiveByHandle", hmc_au3_WinWaitActiveByHandle),
        DECLARE_NAPI_METHOD("WinWaitClose", hmc_au3_WinWaitClose),
        DECLARE_NAPI_METHOD("WinWaitCloseByHandle", hmc_au3_WinWaitCloseByHandle),
        DECLARE_NAPI_METHOD("WinWaitNotActive", hmc_au3_WinWaitNotActive),
        DECLARE_NAPI_METHOD("WinWaitNotActiveByHandle", hmc_au3_WinWaitNotActiveByHandle)};
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
