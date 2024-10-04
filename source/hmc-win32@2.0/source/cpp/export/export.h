#include "hmc_napi_value_util.h"

#ifdef _DEBUG
#ifdef _WIN64
#pragma comment(lib, "hmc-module-static_DEBUG_X64.lib")
#else
#pragma comment(lib, "hmc-module-static_DEBUG_X86.lib")
#endif
#else
#ifdef _WIN64
#pragma comment(lib, "hmc-module-static_RELEASE_X64.lib")
#else
#pragma comment(lib, "hmc-module-static_RELEASE_X86.lib")
#endif
#endif

// clip.cpp
extern napi_value getClipboardFilePaths(napi_env env, napi_callback_info info);
extern napi_value setClipboardText(napi_env env, napi_callback_info info);
extern napi_value getClipboardText(napi_env env, napi_callback_info info);
extern napi_value clearClipboard(napi_env env, napi_callback_info info);
extern napi_value setClipboardFilePaths(napi_env env, napi_callback_info info);
extern napi_value getClipboardInfo(napi_env env, napi_callback_info info);
extern napi_value enumClipboardFormats(napi_env env, napi_callback_info info);
extern napi_value getClipboardHTML(napi_env env, napi_callback_info info);

extern std::any GetClipboardFilePaths2(napi_env env, size_t TASK_TYPE, std::vector<std::any> *data_list);
extern std::any GetClipboardText2(napi_env env, size_t TASK_TYPE, std::vector<std::any> *data_list);
extern std::any GetThumbnailPng2(napi_env env, size_t TASK_TYPE, std::vector<std::any> *data_list);

// screen.cpp
extern napi_value captureBmpToBuff(napi_env env, napi_callback_info info);
extern napi_value captureBmpToFile(napi_env env, napi_callback_info info);

// window.cpp

void exports_window_async_fun(napi_env env, napi_value exports);
void exports_screen_async_fun(napi_env env, napi_value exports);

namespace HMC_shell_startup
{
    extern napi_value set(napi_env env, napi_callback_info info);
    extern napi_value setOnce(napi_env env, napi_callback_info info);
    extern napi_value remove(napi_env env, napi_callback_info info);
    extern napi_value has(napi_env env, napi_callback_info info);
    extern napi_value removeOnce(napi_env env, napi_callback_info info);
    extern napi_value hasOnce(napi_env env, napi_callback_info info);
    extern napi_value StartupClassConstructor(napi_env env, napi_callback_info info);
}

namespace HMC_shell
{

    // shell.cpp
    extern napi_value getTrayList(napi_env env, napi_callback_info info);
    extern napi_value trashFile(napi_env env, napi_callback_info info);
    extern napi_value copyFile(napi_env env, napi_callback_info info);
    extern napi_value moveFile(napi_env env, napi_callback_info info);
    extern napi_value clearTrash(napi_env env, napi_callback_info info);
    extern napi_value getThumbnailPng(napi_env env, napi_callback_info info);
    extern napi_value getLinkTarget(napi_env env, napi_callback_info info);
    extern napi_value setFolderIcon(napi_env env, napi_callback_info info);
    extern napi_value isLinkLink(napi_env env, napi_callback_info info);
    extern napi_value setShortcutLink(napi_env env, napi_callback_info info);
    extern napi_value createFsLink(napi_env env, napi_callback_info info);
    extern napi_value getSystemMetrics(napi_env env, napi_callback_info info);
    extern napi_value getShortcutLink(napi_env env, napi_callback_info info);
    extern napi_value showContextMenu(napi_env env, napi_callback_info info);
    extern napi_value setConversionStatus(napi_env env, napi_callback_info info);
    extern napi_value StartupClassConstructor(napi_env env, napi_callback_info info);
}

namespace HMC_GetProcessName
{
    napi_value ExecuteSync(napi_env env, napi_callback_info info);
    napi_value StartAsyncTask(napi_env env, napi_callback_info info);
}

namespace HMC_GetProcessFilePath
{
    napi_value ExecuteSync(napi_env env, napi_callback_info info);
    napi_value StartAsyncTask(napi_env env, napi_callback_info info);
}

namespace HMC_GetProcessEnvInfo
{
    napi_value ExecuteSync(napi_env env, napi_callback_info info);
    napi_value StartAsyncTask(napi_env env, napi_callback_info info);
}

namespace HMC_GetRegistrEnvInfo
{
    napi_value ExecuteSync(napi_env env, napi_callback_info info);
    napi_value StartAsyncTask(napi_env env, napi_callback_info info);
}

namespace HMC_Keyboard
{
    extern napi_value initKeyboardEventHook(napi_env env, napi_callback_info info);
    extern napi_value isValidHookKeyboard(napi_env env, napi_callback_info info);
    extern napi_value hasKeyActivate(napi_env env, napi_callback_info info);
    extern napi_value hasKeysBasic(napi_env env, napi_callback_info info);
    extern napi_value getAllKeyboardEventJson(napi_env env, napi_callback_info info);
    extern napi_value stopHookKeyboard(napi_env env, napi_callback_info info);
    // Init
    extern napi_value StartupClassConstructor(napi_env env, napi_callback_info info);
}

namespace HMC_mouse
{
    extern napi_value initMouseEventHook(napi_env env, napi_callback_info info);
    extern napi_value isValidHookMouse(napi_env env, napi_callback_info info);
    extern napi_value getMouseEventListJson(napi_env env, napi_callback_info info);
    extern napi_value stopHookMouse(napi_env env, napi_callback_info info);
    extern napi_value setShakeEventTime(napi_env env, napi_callback_info info);
    extern napi_value setLimitMouseRange(napi_env env, napi_callback_info info);
    extern napi_value hasLimitMouseRangeWorker(napi_env env, napi_callback_info info);
    extern napi_value stopLimitMouseRangeWorker(napi_env env, napi_callback_info info);
    // Init
    extern napi_value StartupClassConstructor(napi_env env, napi_callback_info info);
}

class CaptureBmp2
{
public:
    // 输入命令格式化或拒绝任务
    static bool FormatArg(napi_env env, napi_callback_info info, hmc_NodeArgsValue ArgsValue, std::vector<std::any> *data_list);
    // 执行任务
    static std::any ExecuteWorkFun(napi_env env, size_t TASK_TYPE, std::vector<std::any> *data_list);
    // 值自定义格式化
    static napi_value ResultFormat(napi_env env, napi_status status, std::any *ResultStore, std::vector<std::any> *data_list);
    // 初始化函数
    static void initialize(const int ID)
    {
        HMC_PromiseEval::append(ID, FormatArg, ExecuteWorkFun, ResultFormat);
    }
};

class CloseWindow2
{
public:
    // 输入命令格式化或拒绝任务
    static bool FormatArg(napi_env env, napi_callback_info info, hmc_NodeArgsValue input, std::vector<std::any> *arguments_list);
    // 执行任务
    static std::any ExecuteWorkFun(napi_env env, size_t TASK_TYPE, std::vector<std::any> *arguments_list);
    // 值自定义格式化
    // static napi_value ResultFormat(napi_env env, napi_status status, std::any *ResultStore, std::vector<std::any> *arguments_list);
    // 初始化函数
    static void initialize(const int ID)
    {
        HMC_PromiseEval::append(ID, FormatArg, ExecuteWorkFun, std::nullopt);
    }
};

class GetThumbnailPng2
{
public:
    // 输入命令格式化或拒绝任务
    static bool FormatArg(napi_env env, napi_callback_info info, hmc_NodeArgsValue input, std::vector<std::any> *arguments_list);
    // 执行任务
    static std::any ExecuteWorkFun(napi_env env, size_t TASK_TYPE, std::vector<std::any> *arguments_list);
    // 值自定义格式化
    // static napi_value ResultFormat(napi_env env, napi_status status, std::any *ResultStore, std::vector<std::any> *arguments_list);
    // 初始化函数
    static void initialize(const int ID)
    {
        HMC_PromiseEval::append(ID, FormatArg, ExecuteWorkFun, std::nullopt);
    }
};

// class GetClipboardFilePaths2
// {
// public:
//     // 输入命令格式化或拒绝任务
//     static bool FormatArg(napi_env env, napi_callback_info info, hmc_NodeArgsValue input, std::vector<std::any> *arguments_list);
//     // 执行任务
//     static std::any ExecuteWorkFun(napi_env env, size_t TASK_TYPE, std::vector<std::any> *arguments_list);
//     // 值自定义格式化
//     static napi_value ResultFormat(napi_env env, napi_status status, std::any *ResultStore, std::vector<std::any> *arguments_list);
//     // 初始化函数
//     static void initialize(const int ID){
//         HMC_PromiseEval::append(ID,FormatArg,ExecuteWorkFun,ResultFormat);
//         HMC_PromiseEval::append(ID,std::nullopt,ExecuteWorkFun,ResultFormat);
//         HMC_PromiseEval::append(ID,std::nullopt,ExecuteWorkFun,std::nullopt);
//     }
// };

// bool 输入命令格式化或拒绝任务(napi_env env, napi_callback_info info, hmc_NodeArgsValue ArgsValue, std::vector<std::any> *data_list);
// std::any 执行任务(napi_env env, size_t TASK_TYPE, std::vector<std::any> *data_list);
// napi_value 值自定义格式化(napi_env env, napi_status status, std::any *ResultStore, std::vector<std::any> *data_list);
// 暴露
// HMC_PromiseEval::append(1,输入命令格式化或拒绝任务,执行任务,值自定义格式化);
// HMC_PromiseEval::append(1,输入命令格式化或拒绝任务,执行任务);
// HMC_PromiseEval::append(1,执行任务);
