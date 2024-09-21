#include "export.h"
#include "hmc_windows_util.h"

std::any CloseWindow2::ExecuteWorkFun(napi_env env, size_t TASK_TYPE, std::vector<std::any> *arguments_list)
{
    std::any result = std::any();
    HWND Handle = (HWND)std::any_cast<int64_t>(arguments_list->at(0));
    int grade = std::any_cast<int>(arguments_list->at(1));
    
    result = hmc_windows_util::closeWindow(Handle, grade);

    return result;
}

bool CloseWindow2::FormatArg(napi_env env, napi_callback_info info, hmc_NodeArgsValue input, std::vector<std::any> *arguments_list)
{

    if (!input.eq(0, {js_number, js_bigint}, true))
    {
        return false;
    }

    // hwnd:number
    int64_t ihwnd = at_Number64Or(0, 0);
    int igrade = at_Number64Or(1, 5);

    arguments_list->push_back(ihwnd);
    arguments_list->push_back(igrade);

    return true;
}