#include "../Mian.hpp";
#include "hmc_string_util.h"
#include "hmc_napi_value_util.h";
#include "./environment.hpp";
//#include "./fmt11.hpp";

#define $napi_get_cb_info_v2(argsLen, args, fnName)                         \
    if (napi_get_cb_info(env, info, &argsLen, args, NULL, NULL) != napi_ok) \
    {                                                                       \
        napi_throw_type_error(env, NULL, string(fnName).c_str());           \
        return NULL;                                                        \
    }

// 获取全部的变量
napi_value fn_getVariableAll(napi_env env, napi_callback_info info)
{
    // wstring variableListJson = hmc_string_util::map_to_jsonW(getVariableAllW());
    return hmc_napi_create_value::Object::Object(env, getVariableAllW());
}

// 设置当前进程的工作路径
napi_value fn_setCwd(napi_env env, napi_callback_info info)
{

    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info_v2(argsLen, args, "fn_setCwd");
    // 参数最少要求1个
    if (!hmc_napi_type::argsSize(env, argsLen, 0, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_setCwd ( utf16(String) )").c_str());
        return NULL;
    }

    wstring w_path = hmc_napi_get_value::string_utf16(env, args[0]);

    return hmc_napi_create_value::Boolean(env, hmc_env::setCwd(w_path));
}

HWND __HMC_G_ConsoleHwnd = NULL;
FILE *__HMC_G_pConsoleStream;
bool __HMC_G_DEBUG = false;

napi_value fn_AllocConsole(napi_env env, napi_callback_info info)
{
    if (::AllocConsole())
    {
        ::freopen_s(&__HMC_G_pConsoleStream, "CONOUT$", "w", stdout);
        __HMC_G_DEBUG = true;
        __HMC_G_ConsoleHwnd = ::GetConsoleWindow();
        std::cout << "[ HMC-DEUG ] Current debug mode has been enabled. Please note that debug mode will increase performance overhead, and the window can only be closed by calling hmc.hmc_debug_end() first. Otherwise, it may cause the process to crash." << std::endl;
    }
    return NULL;
}

// 从注册表读取现在的真实环境变量 但不更新到进程环境
napi_value fn_getRealGlobalVariable(napi_env env, napi_callback_info info)
{

    // wstring result = L"";

    // string map_to_jsonA = hmc_string_util::map_to_jsonA((std::any)hmc_env::systemEnv::getGlobalVariable());

    // result.append(hmc_string_util::ansi_to_utf16(map_to_jsonA));
    // return hmc_napi_create_value::String(env, result);

    map<wstring, wstring> result = {};

    for (auto globalVariable : hmc_env::systemEnv::getGlobalVariable())
    {
        if (hmc_string_util::text_to_upper(globalVariable.first) != "PATH")
        {
            wstring key = hmc_string_util::ansi_to_utf16(globalVariable.first);
            wstring value = hmc_string_util::ansi_to_utf16(globalVariable.second);
            result.insert(std::make_pair(key, value));
        }
    }

    string path_value_join = hmc_env::systemEnv::getUse("Path") + ";" + hmc_env::systemEnv::getSys("Path");
    wstring path_value = hmc_string_util::ansi_to_utf16(path_value_join);
    result.insert(std::make_pair(L"Path", path_value));

    // return hmc_napi_create_value::String(env, hmc_string_util::map_to_jsonW(result) );

    return hmc_napi_create_value::Object::Object(env, result);
}

// user 变量的 key 列表
napi_value fn_getUserKeyList(napi_env env, napi_callback_info info)
{
    wstring result = L"";
    std::vector<std::wstring> keyList2W = hmc_string_util::ansi_to_utf16(hmc_env::systemEnv::keyUseList());

    // wstring keyList2json = hmc_string_util::vec_to_array_json(keyList2W);

    return hmc_napi_create_value::Array::String(env, keyList2W);
}

// systm 变量的 key 列表
napi_value fn_getSystemKeyList(napi_env env, napi_callback_info info)
{
    std::vector<std::wstring> keyList2W = hmc_string_util::ansi_to_utf16(hmc_env::systemEnv::keySysList());
    wstring keyList2json = hmc_string_util::vec_to_array_json(keyList2W);
    return hmc_napi_create_value::Array::String(env, keyList2W);
}

/**
 * @brief 从注册表读取并更新到当前环境
 *
 * @param remove 删除 已经消失的环境 到当前进程
 * @param update 更新 新的变量到当前进程
 */
napi_value fn_updateThis(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 2;
    napi_value args[2];

    $napi_get_cb_info_v2(argsLen, args, "fn_updateThis");
    bool arg0_remove = hmc_napi_type::isBoolean(env, args[0]) ? hmc_napi_get_value::boolean_bool(env, args[0]) : true;
    bool arg1_update = hmc_napi_type::isBoolean(env, args[1]) ? hmc_napi_get_value::boolean_bool(env, args[1]) : true;

    hmc_env::systemEnv::updateThis(arg0_remove, arg1_update);

    return NULL;
}

/**
 * @brief 获取指定键值 按照默认优先级
 * ?- 用户变量和系统变量同时有非数组键  -> 用户变量
 * ?- 用户变量和系统变量同时为数组键    -> 用户变量数组
 * ?- 用户变量为数组键 系统变量为文本键  -> 用户文本键 排除系统
 * ?- 系统变量为文本键 用户变量为数组    -> 用户变量数组 排除系统
 * ?- 系统变量存在 用户变量为空文本      -> 排除此变量
 * ?- PATH                          -> 合并数组
 * @param key 键
 * @param pEnvStr 数据写入到此传址string变量
 * @return true
 * @return false
 */
napi_value fn_getEnvKeyAnalysis(napi_env env, napi_callback_info info)
{

    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];

    $napi_get_cb_info_v2(argsLen, args, "fn_getEnvKeyAnalysis");
    // 参数最少要求1个
    if (!hmc_napi_type::argsSize(env, argsLen, 0, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_getEnvKeyAnalysis ( ansi(String)  )").c_str());
        return NULL;
    }

    string envKey = hmc_napi_get_value::string_ansi(env, args[0]);
    string pEnvStr = "";

    if (hmc_env::systemEnv::get(envKey, pEnvStr))
    {
        return hmc_napi_create_value::StringA(env, pEnvStr);
    }

    return hmc_napi_create_value::Null(env);
}

napi_value fn_putUserVariable(napi_env env, napi_callback_info info)
{

    napi_status status;
    size_t argsLen = 4;
    napi_value args[4];
    $napi_get_cb_info_v2(argsLen, args, "fn_putUserVariable");
    // 参数最少要求2个 且 args[0], args[1] 都必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 4) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_putUserVariable ( ansi(String) , ansi(String)  )").c_str());
        return NULL;
    }

    //? (key:string,value?:string,append?:boolean,transMean?:boolean)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);
    std::string arg_Value = hmc_napi_get_value::string_ansi(env, args[1]);
    bool arg_append = (hmc_napi_type::isBoolean(env, args[2]) ? hmc_napi_get_value::boolean_bool(env, args[2]) : false);
    bool arg_transMean = (hmc_napi_type::isBoolean(env, args[3]) ? hmc_napi_get_value::boolean_bool(env, args[3]) : false);

    bool result = hmc_env::systemEnv::putUse(arg_key, arg_Value, arg_append, arg_transMean);

    return hmc_napi_create_value::Boolean(env, result);
}

napi_value fn_putSystemVariable(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 4;
    napi_value args[4];
    $napi_get_cb_info_v2(argsLen, args, "fn_putSystemVariable");
    // 参数最少要求2个 且 args[0], args[1] 都必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 4) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_putSystemVariable ( ansi(String) , ansi(String)  )").c_str());
        return NULL;
    }

    //? (key:string,value?:string,append?:boolean,transMean?:boolean)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);
    std::string arg_Value = hmc_napi_get_value::string_ansi(env, args[1]);
    bool arg_append = (hmc_napi_type::isBoolean(env, args[2]) ? hmc_napi_get_value::boolean_bool(env, args[2]) : false);
    bool arg_transMean = (hmc_napi_type::isBoolean(env, args[3]) ? hmc_napi_get_value::boolean_bool(env, args[3]) : false);

    bool result = hmc_env::systemEnv::putSys(arg_key, arg_Value, arg_append, arg_transMean);

    return hmc_napi_create_value::Boolean(env, result);
}

napi_value fn_getUserVariable(napi_env env, napi_callback_info info)
{

    napi_status status;
    size_t argsLen = 2;
    napi_value args[2];
    $napi_get_cb_info_v2(argsLen, args, "fn_getUserVariable");
    // 参数最少要求1个 且 args[0] 必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_getUserVariable ( ansi(String)  transMean?:boolean )").c_str());
        return NULL;
    }

    //? (key:string,transMean?:boolean)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);
    bool arg_transMean = hmc_napi_type::isBoolean(env, args[1]) ? hmc_napi_get_value::boolean_bool(env, args[1]) : true;

    std::string pEnvStr;

    bool result = hmc_env::systemEnv::getUse(arg_key, pEnvStr, arg_transMean);
    if (result)
    {
        return hmc_napi_create_value::StringA(env, pEnvStr);
    }

    return hmc_napi_create_value::Null(env);
}

napi_value fn_getSystemVariable(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 2;
    napi_value args[2];
    $napi_get_cb_info_v2(argsLen, args, "fn_getSystemVariable");
    // 参数最少要求1个 且 args[0] 必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_getSystemVariable ( ansi(String)  transMean?:boolean )").c_str());
        return NULL;
    }

    //? (key:string,transMean?:boolean)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);
    bool arg_transMean = hmc_napi_type::isBoolean(env, args[1]) ? hmc_napi_get_value::boolean_bool(env, args[1]) : true;

    std::string pEnvStr;

    bool result = hmc_env::systemEnv::getSys(arg_key, pEnvStr, arg_transMean);
    if (result)
    {
        return hmc_napi_create_value::StringA(env, pEnvStr);
    }

    return hmc_napi_create_value::Null(env);
}

napi_value fn_removeSystemVariable(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];
    $napi_get_cb_info_v2(argsLen, args, "fn_removeSystemVariable");
    // 参数最少要求1个 且 args[0] 必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_removeSystemVariable ( ansi(u16) (String) )").c_str());
        return NULL;
    }

    //? (key:string,transMean?:boolean)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);

    bool result = hmc_env::systemEnv::removeSys(arg_key);

    return hmc_napi_create_value::Boolean(env, result);
}

napi_value fn_removeUserVariable(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];
    $napi_get_cb_info_v2(argsLen, args, "fn_removeUserVariable");
    // 参数最少要求1个 且 args[0] 必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_removeUserVariable ( ansi(u16) (String) )").c_str());
        return NULL;
    }

    //? (key:string,transMean?:boolean)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);

    bool result = hmc_env::systemEnv::removeUse(arg_key);

    return hmc_napi_create_value::Boolean(env, result);
}

napi_value fn_removeAllSingleVariable(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];
    $napi_get_cb_info_v2(argsLen, args, "fn_removeAllSingleVariable");
    // 参数最少要求1个 且 args[0] 必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_removeAllSingleVariable ( ansi(u16) (String) )").c_str());
        return NULL;
    }

    //? (key:string,transMean?:boolean)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);

    bool result = hmc_env::systemEnv::removeAll(arg_key);

    return hmc_napi_create_value::Boolean(env, result);
}

napi_value fn_escapeEnvVariable(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];
    $napi_get_cb_info_v2(argsLen, args, "fn_escapeEnvVariable");
    // 参数最少要求1个 且 args[0] 必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_escapeEnvVariable ( ansi(u16) (String) )").c_str());
        return NULL;
    }

    //? (key:string)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);

    string result = hmc_env::systemEnv::escapeEnvVariable(arg_key);

    return hmc_napi_create_value::StringA(env, result);
}

napi_value fn_hasKeyExists(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];
    $napi_get_cb_info_v2(argsLen, args, "fn_hasKeyExists");
    // 参数最少要求1个 且 args[0] 必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_hasKeyExists ( ansi(u16) (String) )").c_str());
        return NULL;
    }

    //? (key:string)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);

    bool result = hmc_env::systemEnv::hasKeyExists(arg_key);

    return hmc_napi_create_value::Boolean(env, result);
}

napi_value fn_hasSysKeyExists(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];
    $napi_get_cb_info_v2(argsLen, args, "hasSysKeyExists");
    // 参数最少要求1个 且 args[0] 必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect hasSysKeyExists ( ansi(u16) (String) )").c_str());
        return NULL;
    }

    //? (key:string)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);

    bool result = hmc_env::systemEnv::hasSysKeyExists(arg_key);

    return hmc_napi_create_value::Boolean(env, result);
}

napi_value fn_hasUseKeyExists(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];
    $napi_get_cb_info_v2(argsLen, args, "hasUseKeyExists");
    // 参数最少要求1个 且 args[0] 必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 1) && hmc_napi_type::isString(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect hasUseKeyExists ( ansi(u16) (String) )").c_str());
        return NULL;
    }

    //? (key:string)=>boolean
    std::string arg_key = hmc_napi_get_value::string_ansi(env, args[0]);

    bool result = hmc_env::systemEnv::hasUseKeyExists(arg_key);

    return hmc_napi_create_value::Boolean(env, result);
}

napi_value fn_getProcessStartTime(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argsLen = 1;
    napi_value args[1];
    $napi_get_cb_info_v2(argsLen, args, "fn_getProcessStartTime");
    // 参数最少要求1个 且 args[0] 必须是string
    if (!hmc_napi_type::argsSize(env, argsLen, 1, 1) && hmc_napi_type::isNumber(env, args[0]))
    {
        napi_throw_type_error(env, NULL, string("parameter Is Incorrect fn_getProcessStartTime ( DWORD (Number) )").c_str());
        return NULL;
    }

    DWORD ProcessID = (DWORD)hmc_napi_get_value::number_int64(env, args[0]);

    ULONGLONG elapsedTime = 0;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, ProcessID);
    if (hProcess != NULL)
    {
        FILETIME createTime, exitTime, kernelTime, userTime;
        if (GetProcessTimes(hProcess, &createTime, &exitTime, &kernelTime, &userTime))
        {
            ULARGE_INTEGER startTime;
            startTime.LowPart = createTime.dwLowDateTime;
            startTime.HighPart = createTime.dwHighDateTime;

            // 获取当前系统时间
            FILETIME currentTime;
            GetSystemTimeAsFileTime(&currentTime);

            ULARGE_INTEGER systemTime;
            systemTime.LowPart = currentTime.dwLowDateTime;
            systemTime.HighPart = currentTime.dwHighDateTime;

            // 计算启动时间（单位为100纳秒）
            ULONGLONG startTime64 = startTime.QuadPart;
            ULONGLONG systemTime64 = systemTime.QuadPart;
            elapsedTime = systemTime64 - startTime64;

            // 将单位从100纳秒转换为毫秒
            elapsedTime = elapsedTime / 10000;
        }
        CloseHandle(hProcess);
    }

    if (elapsedTime == 0)
    {
        return hmc_napi_create_value::Null(env);
    }

    return hmc_napi_create_value::Number(env, (long long)elapsedTime);
}

napi_value fn_putenv(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value MessageBoxInfo;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    hmc_is_argv_type(args, 0, 2, napi_string, NULL);

    string lpkey = hmc_napi_get_value::string_ansi(env, args[0]);
    string lpdata = hmc_napi_get_value::string_ansi(env, args[1]);

    int b_Result = _putenv_s(lpkey.c_str(), lpdata.c_str());

    return as_Boolean(b_Result == 0);
}

napi_value fn_getenv(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value MessageBoxInfo;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    hmc_is_argv_type(args, 0, 1, napi_string, NULL);

    string envkey = hmc_napi_get_value::string_ansi(env, args[0]);
    return hmc_napi_create_value::String(env, hmc_env::getenv(envkey));
}

napi_value fn_getAllEnv(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Object::Object(env, hmc_env::getEnvListW());
}
