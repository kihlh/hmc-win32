#include "./export.h"
#include "hmc_string_util.h"
#include "hmc_napi_value_util.h"
#include "hmc_string_util.h"
#include "hmc_shell_util.h"

// 获取托盘图标
napi_value getTrayList(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::String(env, hmc_shell_util::GetTaryIconList::getTrayListJsonW());
}

napi_value fn_shellFile(napi_env env, napi_callback_info info)
{
    napi_value result = as_Number32(0x10000);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string}});

    std::wstring trash_path = input.getStringWide(0); 
    bool is_Recycle = at_BooleanOr(1,true);
    bool isShow = at_Boolean(2);
    

    int trash_ok = hmc_shell_util::trashFile(trash_path, is_Recycle,isShow);
    result = as_Number32(trash_ok);

    return result;
}

napi_value fn_createLink(napi_env env, napi_callback_info info)
{
 
    return as_Boolean(false);
}
