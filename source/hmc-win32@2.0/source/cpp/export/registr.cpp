#include "export.h"
#include "hmc_napi_value_util.h"
#include "hmc_util.h"
#include "hmc_registr_util.h"


namespace HR = hmc_registr_util;

namespace HMC_GetRegistrEnvInfo
{

    enum class ENV_INFO_COMMAND
    {
        NONE = 0,

        //* export function getRegistrQword(HKey: HKEY, SubKey: string, key: string | null): bigint | null;

        GET_REGISTR_QWORD = 70,

        //* export function setRegistrQword(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): boolean;

        SET_REGISTR_QWORD = 71,

        //* export function getRegistrDword(HKey: HKEY, SubKey: string, key: string | null): number | null;

        GET_REGISTR_DWORD = 72,

        //* export function setRegistrDword(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): boolean;

        SET_REGISTR_DWORD = 73,

        //* export function getRegistrString(HKey: HKEY, SubKey: string, key: string | null): string | null;

        GET_REGISTR_STRING = 74,

        //* export function setRegistrString(HKey: HKEY, SubKey: string, key: string | null, String: string): boolean;

        SET_REGISTR_STRING = 75,

        //* export function getRegistrKeys(HKey: HKEY, SubKey: string, key: string | null): chQueryFolderKey;

        GET_REGISTR_KEYS = 76,

        //* export function getRegistrStringList(HKey: HKEY, SubKey: string, key: string | null): string[] | null;

        GET_REGISTR_STRING_LIST = 77,

        //* export function setRegistrStringList(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[]): boolean;

        SET_REGISTR_STRING_LIST = 78,

        //* export function getRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null): Buffer | null;

        GET_REGISTR_BUFFER = 79,

        //* export function setRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null, String: Buffer): boolean;

        SET_REGISTR_BUFFER = 710,

        //* export function getRegistrValue(HKey: HKEY, SubKey: string, key: string | null): REG_VALUE | null;

        GET_REGISTR_VALUE = 711,

        //* export function copyRegistrValue(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): boolean;

        COPY_REGISTR_VALUE = 712,

        //* export function copyRegistrFolder(HKey: HKEY, SourceSubKey: string, NewSubKey: string): boolean;

        COPY_REGISTR_FOLDER = 713,

        //* export function setRegistrValue(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): boolean;

        SET_REGISTR_VALUE = 714,

        //* export function getRegistrValueStat(HKey: HKEY, SubKey: string, key: string | null): RegistrValueStat;

        GET_REGISTR_VALUE_STAT = 715,

        //* export function getRegistrFolderStat(HKey: HKEY, SubKey: string, key: string | null): RegistrFolderStat;

        GET_REGISTR_FOLDER_STAT = 716,

        //* export function clearRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;

        CLEAR_REGISTR_VALUE = 717,

        //* export function clearRegistrFolder(HKey: HKEY, SubKey: string, key: string | null): boolean;

        CLEAR_REGISTR_FOLDER = 718,

        //* export function removeRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;

        REMOVE_REGISTR_VALUE = 719,

        //* export function removeRegistrFolder(HKey: HKEY, SubKey: string): boolean;

        REMOVE_REGISTR_FOLDER = 720,

        //* export function removeRegistrFolderTree(HKey: HKEY, SubKey: string): boolean;

        REMOVE_REGISTR_FOLDER_TREE = 721,

        //* export function createRegistrFolder(HKey: HKEY, SubKey: string): boolean;

        CREATE_REGISTR_FOLDER = 722,

        //* export function createRegistrValueKey(HKey: HKEY, SubKey: string, key: string | string[]): boolean;

        CREATE_REGISTR_VALUE_KEY = 723,

        //* export function hasRegistrKey(HKey: HKEY, SubKey: string, key: string | null): boolean;

        HAS_REGISTR_KEY = 724,

        //* export function hasRegistrFolderKey(HKey: HKEY, SubKey: string): boolean;

        HAS_REGISTR_FOLDER_KEY = 725,
    };

    const ENV_INFO_COMMAND allCommands[] = {
        ENV_INFO_COMMAND::GET_REGISTR_QWORD,
        ENV_INFO_COMMAND::SET_REGISTR_QWORD,
        ENV_INFO_COMMAND::GET_REGISTR_DWORD,
        ENV_INFO_COMMAND::SET_REGISTR_DWORD,
        ENV_INFO_COMMAND::GET_REGISTR_STRING,
        ENV_INFO_COMMAND::SET_REGISTR_STRING,
        ENV_INFO_COMMAND::GET_REGISTR_KEYS,
        ENV_INFO_COMMAND::GET_REGISTR_STRING_LIST,
        ENV_INFO_COMMAND::SET_REGISTR_STRING_LIST,
        ENV_INFO_COMMAND::GET_REGISTR_BUFFER,
        ENV_INFO_COMMAND::SET_REGISTR_BUFFER,
        ENV_INFO_COMMAND::GET_REGISTR_VALUE,
        ENV_INFO_COMMAND::COPY_REGISTR_VALUE,
        ENV_INFO_COMMAND::COPY_REGISTR_FOLDER,
        ENV_INFO_COMMAND::SET_REGISTR_VALUE,
        ENV_INFO_COMMAND::GET_REGISTR_VALUE_STAT,
        ENV_INFO_COMMAND::GET_REGISTR_FOLDER_STAT,
        ENV_INFO_COMMAND::CLEAR_REGISTR_VALUE,
        ENV_INFO_COMMAND::CLEAR_REGISTR_FOLDER,
        ENV_INFO_COMMAND::REMOVE_REGISTR_VALUE,
        ENV_INFO_COMMAND::REMOVE_REGISTR_FOLDER,
        ENV_INFO_COMMAND::REMOVE_REGISTR_FOLDER_TREE,
        ENV_INFO_COMMAND::CREATE_REGISTR_FOLDER,
        ENV_INFO_COMMAND::CREATE_REGISTR_VALUE_KEY,
        ENV_INFO_COMMAND::HAS_REGISTR_KEY,
        ENV_INFO_COMMAND::HAS_REGISTR_FOLDER_KEY};

    typedef std::map<int, std::vector<js_valuetype>> EQ_ARG_ITEM;

    std::map<ENV_INFO_COMMAND, EQ_ARG_ITEM> ArgumentsEQ;

    struct EnvNextWorkData
    {
        napi_deferred deferred;
        napi_async_work work;
        ENV_INFO_COMMAND command;
        HKEY HKey;
        std::wstring *SubKey;
        std::wstring *key;
        std::vector<std::any> *arguments;
        std::any *result;
    };
    /**
     * @brief 创建 输入参数类型 的预设置 类型
     *
     * @return EQ_ARG_ITEM
     */
    EQ_ARG_ITEM makeAllEqArgItem();
    /**
     * @brief 初始化输入参数类型 的预设置
     *
     */
    void init_Arguments_EQ_type();
    /**
     * @brief 垃圾回收
     *
     * @param workData
     */
    void GC(EnvNextWorkData *workData);
    /**
     * @brief 格式化输入参数
     *
     * @param env
     * @param input
     * @return EnvNextWorkData*
     */
    EnvNextWorkData *GetArguments(napi_env env, hmc_NodeArgsValue input);
    /**
     * @brief 执行异步函数
     *
     * @param env
     * @param data
     */
    void ExecuteAsyncWork(napi_env env, void *data);
    /**
     * @brief 输入判断 如果为NONE请立刻拒绝api调用请求
     *
     * @param env
     * @param input
     * @return ENV_INFO_COMMAND
     */
    ENV_INFO_COMMAND EQ(napi_env env, hmc_NodeArgsValue input);
    /**
     * @brief 获取 HKEY 如果为null请立刻拒绝api调用请求
     *
     * @param env
     * @param input
     * @return HKEY
     */
    HKEY GET_HKEY(napi_env env, hmc_NodeArgsValue input);
    /**
     * @brief 处理同步的函数
     *
     * @param env
     * @param info
     * @return napi_value
     */
    napi_value ExecuteSync(napi_env env, napi_callback_info info);
    /**
     * @brief 异步任务完成后的回调函数
     *
     * @param env
     * @param status
     * @param data
     */
    void ResolveWork(napi_env env, napi_status status, void *data);
    /**
     * @brief 启动异步任务的函数
     *
     * @param env
     * @param info
     * @return napi_value
     */
    napi_value StartAsyncTask(napi_env env, napi_callback_info info);
    /**
     * @brief 格式化到结果
     *
     * @param env
     * @param result
     * @return napi_value
     */
    napi_value FormatToResult(napi_env env, EnvNextWorkData *workData);
    /**
     * @brief 执行函数
     *
     * @param env
     * @param result
     * @return napi_value
     */
    void fun_call(napi_env env, EnvNextWorkData *workData);

}

HMC_GetRegistrEnvInfo::EQ_ARG_ITEM HMC_GetRegistrEnvInfo::makeAllEqArgItem()
{
    EQ_ARG_ITEM result = EQ_ARG_ITEM();
    // 第一位永久为 HKEY
    result.insert(std::make_pair(0, std::vector<js_valuetype>({js_string})));
    // 第二位永久为 string
    result.insert(std::make_pair(1, std::vector<js_valuetype>({js_string})));
    return result;
}

void HMC_GetRegistrEnvInfo::init_Arguments_EQ_type()
{
    if (ArgumentsEQ.size() >= 1)
    {
        return;
    }

    for (auto command : allCommands)
    {
        ArgumentsEQ.insert(std::pair<ENV_INFO_COMMAND, EQ_ARG_ITEM>(command, makeAllEqArgItem()));
    }

    //* export function *(HKey: HKEY, SubKey: string, key: string | null)

    const ENV_INFO_COMMAND allCommands_beSimilar[] = {
        ENV_INFO_COMMAND::GET_REGISTR_QWORD,
        ENV_INFO_COMMAND::GET_REGISTR_DWORD,
        ENV_INFO_COMMAND::GET_REGISTR_STRING,
        ENV_INFO_COMMAND::GET_REGISTR_KEYS,
        ENV_INFO_COMMAND::GET_REGISTR_STRING_LIST,
        ENV_INFO_COMMAND::GET_REGISTR_BUFFER,
        ENV_INFO_COMMAND::GET_REGISTR_VALUE,
        ENV_INFO_COMMAND::GET_REGISTR_VALUE_STAT,
        ENV_INFO_COMMAND::GET_REGISTR_FOLDER_STAT,
        ENV_INFO_COMMAND::CLEAR_REGISTR_VALUE,
        ENV_INFO_COMMAND::CLEAR_REGISTR_FOLDER,
        ENV_INFO_COMMAND::REMOVE_REGISTR_VALUE,
        ENV_INFO_COMMAND::HAS_REGISTR_KEY};

    for (auto command : allCommands_beSimilar)
    {
        if (ArgumentsEQ.find(command) != ArgumentsEQ.end())
        {
            auto &at = ArgumentsEQ.at(command);
            auto temp = std::make_pair(2, std::vector<js_valuetype>({js_string, js_null}));
            at.insert(temp);
        }
    }

    if (ArgumentsEQ.find(ENV_INFO_COMMAND::SET_REGISTR_QWORD) != ArgumentsEQ.end())
    {
        auto &at = ArgumentsEQ.at(ENV_INFO_COMMAND::SET_REGISTR_QWORD);
        auto temp1 = std::make_pair(2, std::vector<js_valuetype>({js_string}));

        auto temp2 = std::make_pair(3, std::vector<js_valuetype>({js_bigint, js_number}));
        at.insert(temp1);
        at.insert(temp2);
    }

    if (ArgumentsEQ.find(ENV_INFO_COMMAND::SET_REGISTR_DWORD) != ArgumentsEQ.end())
    {
        auto &at = ArgumentsEQ.at(ENV_INFO_COMMAND::SET_REGISTR_DWORD);
        auto temp1 = std::make_pair(2, std::vector<js_valuetype>({js_string}));

        auto temp2 = std::make_pair(3, std::vector<js_valuetype>({js_bigint, js_number}));
        at.insert(temp1);
        at.insert(temp2);
    }

    if (ArgumentsEQ.find(ENV_INFO_COMMAND::SET_REGISTR_STRING) != ArgumentsEQ.end())
    {
        auto &at = ArgumentsEQ.at(ENV_INFO_COMMAND::SET_REGISTR_STRING);
        auto temp = std::make_pair(2, std::vector<js_valuetype>({js_string}));

        auto temp2 = std::make_pair(3, std::vector<js_valuetype>({js_string}));
        at.insert(temp);
        at.insert(temp2);
    }

    if (ArgumentsEQ.find(ENV_INFO_COMMAND::SET_REGISTR_STRING_LIST) != ArgumentsEQ.end())
    {
        auto &at = ArgumentsEQ.at(ENV_INFO_COMMAND::SET_REGISTR_STRING_LIST);

        auto temp1 = std::make_pair(2, std::vector<js_valuetype>({js_string}));
        at.insert(temp1);

        auto temp = std::make_pair(3, std::vector<js_valuetype>({js_array, js_string}));
        at.insert(temp);
    }

    if (ArgumentsEQ.find(ENV_INFO_COMMAND::SET_REGISTR_BUFFER) != ArgumentsEQ.end())
    {
        auto &at = ArgumentsEQ.at(ENV_INFO_COMMAND::SET_REGISTR_BUFFER);

        auto temp1 = std::make_pair(2, std::vector<js_valuetype>({js_string}));
        at.insert(temp1);

        auto temp = std::make_pair(3, std::vector<js_valuetype>({js_buffer}));
        at.insert(temp);
    }

    if (ArgumentsEQ.find(ENV_INFO_COMMAND::COPY_REGISTR_FOLDER) != ArgumentsEQ.end())
    {
        auto &at = ArgumentsEQ.at(ENV_INFO_COMMAND::COPY_REGISTR_FOLDER);

        auto temp = std::make_pair(2, std::vector<js_valuetype>({js_string}));
        at.insert(temp);
    }

    if (ArgumentsEQ.find(ENV_INFO_COMMAND::CREATE_REGISTR_VALUE_KEY) != ArgumentsEQ.end())
    {
        auto &at = ArgumentsEQ.at(ENV_INFO_COMMAND::CREATE_REGISTR_VALUE_KEY);

        auto temp = std::make_pair(2, std::vector<js_valuetype>({js_string}));
        auto temp2 = std::make_pair(3, std::vector<js_valuetype>({js_number}));
        at.insert(temp);
        at.insert(temp2);
    }

    if (ArgumentsEQ.find(ENV_INFO_COMMAND::SET_REGISTR_VALUE) != ArgumentsEQ.end())
    {
        auto &at = ArgumentsEQ.at(ENV_INFO_COMMAND::SET_REGISTR_VALUE);

        auto temp1 = std::make_pair(2, std::vector<js_valuetype>({js_string}));
        at.insert(temp1);

        auto temp = std::make_pair(3, std::vector<js_valuetype>({js_string, js_bigint, js_number, js_null, js_array, js_buffer}));
        at.insert(temp);

        auto temp2 = std::make_pair(4, std::vector<js_valuetype>({js_number}));
        at.insert(temp2);
    }

    if (ArgumentsEQ.find(ENV_INFO_COMMAND::COPY_REGISTR_VALUE) != ArgumentsEQ.end())
    {
        auto &at = ArgumentsEQ.at(ENV_INFO_COMMAND::COPY_REGISTR_VALUE);
        auto temp0 = std::make_pair(2, std::vector<js_valuetype>({js_string, js_null}));
        auto temp1 = std::make_pair(3, std::vector<js_valuetype>({js_string}));
        auto temp2 = std::make_pair(4, std::vector<js_valuetype>({js_string, js_null}));
        at.insert(temp0);
        at.insert(temp1);
        at.insert(temp2);
    }
}

void HMC_GetRegistrEnvInfo::GC(HMC_GetRegistrEnvInfo::EnvNextWorkData *workData)
{

    if (workData == NULL)
    {
        return;
    }

    HMC_VcFreeAuto(workData);

    if (workData->arguments != NULL)
    {
        workData->arguments->clear();
        delete workData->arguments;
    }

    if (workData->SubKey != NULL)
        delete workData->SubKey;
    if (workData->key != NULL)
        delete workData->key;
    if (workData->result != NULL)
        delete workData->result;
}

HMC_GetRegistrEnvInfo::EnvNextWorkData *HMC_GetRegistrEnvInfo::GetArguments(napi_env env, hmc_NodeArgsValue input)
{

    ENV_INFO_COMMAND COMMAND = EQ(env, input);
    if (COMMAND == ENV_INFO_COMMAND::NONE)
    {
        return NULL;
    }

    HKEY Hkey = GET_HKEY(env, input);
    if (Hkey == NULL)
    {
        return NULL;
    }

    EnvNextWorkData *workData = HMC_VcAllocAutoLength(EnvNextWorkData);

    if (workData)
    {
        workData->arguments = new std::vector<std::any>();
        workData->command = ENV_INFO_COMMAND::NONE;
        workData->HKey = nullptr;
        workData->SubKey = nullptr;
        workData->deferred = nullptr;
        workData->result = new std::any();
        workData->work = nullptr;
        workData->key = nullptr;

        workData->HKey = Hkey;
        workData->command = COMMAND;

        auto subKey = input.getStringWide(2, L"");

        workData->SubKey = new std::wstring(subKey.begin(), subKey.end());

        std::wstring Key = std::wstring();

        // 初始化简单数值的寄存区
        switch (COMMAND)
        {

        // get value  3 arg  (HKEY, string, string)
        case ENV_INFO_COMMAND::GET_REGISTR_QWORD:
        case ENV_INFO_COMMAND::GET_REGISTR_DWORD:
        case ENV_INFO_COMMAND::GET_REGISTR_KEYS:
        case ENV_INFO_COMMAND::GET_REGISTR_STRING_LIST:
        case ENV_INFO_COMMAND::GET_REGISTR_BUFFER:
        case ENV_INFO_COMMAND::GET_REGISTR_VALUE:
        case ENV_INFO_COMMAND::GET_REGISTR_VALUE_STAT:
        case ENV_INFO_COMMAND::GET_REGISTR_FOLDER_STAT:

            // has value  3 arg  (HKEY, string, string)
        case ENV_INFO_COMMAND::HAS_REGISTR_KEY:

        // clear value  3 arg  (HKEY, string, string)
        case ENV_INFO_COMMAND::CLEAR_REGISTR_VALUE:
        case ENV_INFO_COMMAND::CLEAR_REGISTR_FOLDER:
        case ENV_INFO_COMMAND::REMOVE_REGISTR_VALUE:

        // set value  4 arg   (HKEY, string, string , any )
        case ENV_INFO_COMMAND::SET_REGISTR_BUFFER:
        case ENV_INFO_COMMAND::SET_REGISTR_STRING_LIST:
        case ENV_INFO_COMMAND::SET_REGISTR_STRING:
        case ENV_INFO_COMMAND::SET_REGISTR_DWORD:
        case ENV_INFO_COMMAND::SET_REGISTR_QWORD:
        case ENV_INFO_COMMAND::SET_REGISTR_VALUE:

        // copy value  3 arg (HKey: HKEY, SourceSubKey: string, NewSubKey: string)
        case ENV_INFO_COMMAND::COPY_REGISTR_FOLDER:

            Key.append(input.getStringWide(3, L""));
            break;

        // ?-----------------------------------------------------------------------------------------
        case ENV_INFO_COMMAND::GET_REGISTR_STRING:
        {

            Key.append(input.getStringWide(3, L""));

            if (workData->arguments != NULL)
            {
                workData->arguments->push_back(input.getBool(4, false));
            }

            break;
        }
        // create value  3 arg   (HKEY, string, string[]|string[] )
        case ENV_INFO_COMMAND::CREATE_REGISTR_VALUE_KEY:
        {

            if (input.eq(3, {js_string}, false) && input.eq(4, {js_number}, false))
            {
                auto key = input.getStringWide(3, L"");
                auto key_type = input.getInt(4, 0);

                if (workData->arguments != NULL)
                {
                    workData->arguments->push_back(key);
                    workData->arguments->push_back(key_type);
                }

                break;
            }
            // Key.append(input.getStringWide(3, L""));
            break;
        }

        // copy value  5 arg   (HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null)
        case ENV_INFO_COMMAND::COPY_REGISTR_VALUE:
        {

            if (workData->arguments != NULL)
            {
                workData->arguments->push_back(input.getStringWide(2, L""));
                workData->arguments->push_back(input.getStringWide(3, L""));
                workData->arguments->push_back(input.getStringWide(4, L""));
                workData->arguments->push_back(input.getStringWide(5, L""));
            }

            break;
        }

        // ?-----------------------------------------------------------------------------------------
        // (HKey: HKEY, SubKey: string)
        case ENV_INFO_COMMAND::REMOVE_REGISTR_FOLDER:
        case ENV_INFO_COMMAND::REMOVE_REGISTR_FOLDER_TREE:
        case ENV_INFO_COMMAND::HAS_REGISTR_FOLDER_KEY:
        case ENV_INFO_COMMAND::CREATE_REGISTR_FOLDER:

        // none
        case ENV_INFO_COMMAND::NONE:
            break;

        default:
            break;
        }

        // 复杂数值的寄存区
        switch (COMMAND)
        {

        // set value  5 arg   (HKEY, string, string ,number|Buffer|null|string[]|bigint, number )
        case ENV_INFO_COMMAND::SET_REGISTR_VALUE:
        {

            if (workData->arguments != NULL)
            {
                if (input.eq(3, {js_bigint, js_number}, false))
                {
                    auto value = input.getInt64(3);
                    workData->arguments->push_back(value);
                }
                else if (input.eq(3, {js_string}, false))
                {
                    auto value = input.getStringWide(3);
                    workData->arguments->push_back(value);
                }
                else if (input.eq(3, {js_array}, false))
                {
                    auto value = input.getArrayWstring(3);
                    workData->arguments->push_back(value);
                }
                else
                {
                    workData->arguments->push_back(std::any());
                }

                if (input.eq(4, {js_number}, false))
                {
                    auto value = input.getInt64(3);
                    workData->arguments->push_back(value);
                }
            }

            break;
        }
        case ENV_INFO_COMMAND::SET_REGISTR_BUFFER:
        {

            if (workData->arguments != NULL)
            {
                workData->arguments->push_back(input.getBuffer(4, {}));
            }
            break;
        }
        case ENV_INFO_COMMAND::SET_REGISTR_STRING_LIST:
        {
            if (workData->arguments != NULL)
            {
                if (input.eq(4, {js_array}, false))
                {
                    workData->arguments->push_back(input.getArrayWstring(4));
                    break;
                }

                workData->arguments->push_back(input.getStringWide(4, L""));
            }
            break;
        }
        case ENV_INFO_COMMAND::SET_REGISTR_STRING:
        {
            if (workData->arguments != NULL)
            {
                workData->arguments->push_back(input.getStringWide(4, L""));
                workData->arguments->push_back(input.getBool(5, false));
            }
            break;
        }
        case ENV_INFO_COMMAND::SET_REGISTR_DWORD:
        {
            if (workData->arguments != NULL)
            {
                workData->arguments->push_back(input.getDword(4, 0));
            }
            break;
        }
        case ENV_INFO_COMMAND::SET_REGISTR_QWORD:
        {
            if (workData->arguments != NULL)
            {
                workData->arguments->push_back(input.getInt64(4, 0));
            }
            break;
        }
        default:
            break;
        }
        workData->key = new std::wstring(Key.begin(), Key.end());
    }

    return workData;
}

void HMC_GetRegistrEnvInfo::ExecuteAsyncWork(napi_env env, void *data)
{
    EnvNextWorkData *workData = (EnvNextWorkData *)data;

    if (workData->result == NULL)
    {
        return;
    }

    fun_call(env, workData);
}

HMC_GetRegistrEnvInfo::ENV_INFO_COMMAND HMC_GetRegistrEnvInfo::EQ(napi_env env, hmc_NodeArgsValue input)
{
    if (!input.eq({{0, js_number}}, true))
    {
        return ENV_INFO_COMMAND::NONE;
    }

    init_Arguments_EQ_type();

    size_t EnvInfoCommandTemp = static_cast<size_t>(at_Number64Or(0, 0));

    ENV_INFO_COMMAND COMMAND = ENV_INFO_COMMAND::NONE;

    for (ENV_INFO_COMMAND command : allCommands)
    {
        if (EnvInfoCommandTemp == static_cast<size_t>(command))
        {
            COMMAND = command;
        }
    }

    if (COMMAND == ENV_INFO_COMMAND::NONE)
    {

        std::string msg_data =
            "The expected value for `arguments[0]` \n"
            "does not match the value currently set by the function. "
            "\n";

        napi_throw_error(env, "ENV_INFO_COMMAND_UNKNOWN", msg_data.c_str());
        return ENV_INFO_COMMAND::NONE;
    }

    bool is_eq_ok = false;

    for (auto &&arg_qe : ArgumentsEQ)
    {
        const ENV_INFO_COMMAND first = arg_qe.first;
        auto &second = arg_qe.second;
        if (first == COMMAND)
        {
            is_eq_ok = true;
            for (auto &&arg : second)
            {
                // 第一位是校验位 所以从 1 开始

                const int index = arg.first + 1;
                const std::vector<js_valuetype> eq_type = arg.second;

                if (!input.eq(index, eq_type, true))
                {
                    is_eq_ok = false;
                    return ENV_INFO_COMMAND::NONE;
                }
            }
        }
    }

    if (!is_eq_ok)
    {
        std::string msg_data =
            "[unknownError] -> The expected value for `arguments[0]` \n"
            "does not match the value currently set by the function. "
            "\n";

        napi_throw_error(env, "ENV_INFO_COMMAND_UNKNOWN", msg_data.c_str());
        return ENV_INFO_COMMAND::NONE;
    }

    return COMMAND;
}

HKEY HMC_GetRegistrEnvInfo::GET_HKEY(napi_env env, hmc_NodeArgsValue input)
{

    auto Hkey_temp = input.getStringWide(1, std::wstring());
    HKEY Hkey = hmc_registr_util::getHive(Hkey_temp);

    if (Hkey == NULL)
    {
        std::string msg_data =
            "[unknown HKEY] -> The expected value for `arguments[1]` \n"
            "does not match the value currently set by the function. \n"
            "HKEY -> 'HKEY_CURRENT_USER' 'HKEY_LOCAL_MACHINE' 'HKEY_CLASSES_ROOT' 'HKEY_USERS' 'HKEY_CURRENT_CONFIG' \n"
            "\n";

        napi_throw_error(env, "ENV_INFO_COMMAND_UNKNOWN", msg_data.c_str());
        return Hkey;
    }

    return Hkey;
}

napi_value HMC_GetRegistrEnvInfo::ExecuteSync(napi_env env, napi_callback_info info)
{
    napi_value result = as_Null();

    auto input = hmc_NodeArgsValue(env, info);

    EnvNextWorkData *workData = GetArguments(env, input);
    if (workData == NULL)
    {
        return NULL;
    }

    HMC_FreeAnyAuto(GC(workData););

    HMC_GetRegistrEnvInfo::fun_call(env, workData);
    result = HMC_GetRegistrEnvInfo::FormatToResult(env, workData);

    if (result == NULL)
    {
        result = as_Null();
    }

    return result;
}

void HMC_GetRegistrEnvInfo::ResolveWork(napi_env env, napi_status status, void *data)
{
    EnvNextWorkData *workData = (EnvNextWorkData *)data;

    if (status != napi_ok)
    {
        return;
    }

    napi_value result;
    napi_get_null(env, &result);

    if (workData == NULL)
    {
        return;
    }

    HMC_FreeAnyAuto(GC(workData););

    if (workData->result == NULL || !workData->result->has_value())

    {
        napi_resolve_deferred(env, workData->deferred, result);
        napi_delete_async_work(env, workData->work);
        return;
    }

    result = HMC_GetRegistrEnvInfo::FormatToResult(env, workData);

    if (result == NULL)
    {
        result = as_Null();
    }

    napi_resolve_deferred(env, workData->deferred, result);
    napi_delete_async_work(env, workData->work);
}

napi_value HMC_GetRegistrEnvInfo::StartAsyncTask(napi_env env, napi_callback_info info)
{
    napi_value promise;
    napi_value resourceName;
    napi_create_string_utf8(env, __FUNCSIG__, NAPI_AUTO_LENGTH, &resourceName);

    auto input = hmc_NodeArgsValue(env, info);

    EnvNextWorkData *workData = GetArguments(env, input);
    if (workData == NULL)
    {
        return NULL;
    }

    napi_create_promise(env, &workData->deferred, &promise);
    napi_create_async_work(env, nullptr, resourceName, ExecuteAsyncWork, ResolveWork, workData, &workData->work);
    napi_queue_async_work(env, workData->work);
    return promise;
}

void HMC_GetRegistrEnvInfo::fun_call(napi_env env, HMC_GetRegistrEnvInfo::EnvNextWorkData *workData)
{
    if (workData == NULL)
    {
        return;
    }
    if (workData->result == NULL)
    {
        workData->result = new std::any();
    }

    ENV_INFO_COMMAND COMMAND = workData->command;
    HKEY HKey = workData->HKey;
    std::wstring SubKey = workData->SubKey == NULL ? std::wstring() : std::wstring(workData->SubKey->begin(), workData->SubKey->end());
    std::wstring Key = workData->key == NULL ? std::wstring() : std::wstring(workData->key->begin(), workData->key->end());
    auto arguments = hmc_util::anyCastList(workData->arguments);

    //* export function getRegistrQword(HKey: HKEY, SubKey: string, key: string | null): bigint | null;

    if (COMMAND == ENV_INFO_COMMAND::GET_REGISTR_QWORD)
    {
        uint64_t temp = HR::GetRegistrInt64(HKey, SubKey, Key);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function setRegistrQword(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): boolean;

    if (COMMAND == ENV_INFO_COMMAND::SET_REGISTR_QWORD)
    {
        if (arguments.exists(0, true))
        {
            const uint64_t Input = std::any_cast<int64_t>(arguments.get(0));
            auto temp = HR::SetRegistrInt64(HKey, SubKey, Key, Input);
            std::any temp_any = std::any(temp);
            workData->result->reset();
            workData->result->swap(temp_any);
        }
    }

    //* export function getRegistrDword(HKey: HKEY, SubKey: string, key: string | null): number | null;

    if (COMMAND == ENV_INFO_COMMAND::GET_REGISTR_DWORD)
    {
        uint32_t temp = HR::GetRegistrInt32(HKey, SubKey, Key);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function setRegistrDword(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): boolean;

    if (COMMAND == ENV_INFO_COMMAND::SET_REGISTR_DWORD)
    {
        if (arguments.exists(0, true))
        {
            const DWORD Input = std::any_cast<DWORD>(arguments.get(0));
            auto temp = HR::SetRegistrInt32(HKey, SubKey, Key, Input);
            std::any temp_any = std::any(temp);
            workData->result->reset();
            workData->result->swap(temp_any);
        }
    }

    //* export function getRegistrString(HKey: HKEY, SubKey: string, key: string | null): string | null;

    if (COMMAND == ENV_INFO_COMMAND::GET_REGISTR_STRING)
    {
        bool expand = false;

        if (arguments.exists(0, true))
        {
            auto at = arguments.at(0);
            expand = at.get_bool(false);
        }
        auto temp = HR::GetRegistrString(HKey, SubKey, Key, expand);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function setRegistrString(HKey: HKEY, SubKey: string, key: string | null, String: string): boolean;

    if (COMMAND == ENV_INFO_COMMAND::SET_REGISTR_STRING)
    {
        if (arguments.exists(0, true))
        {
            bool expand = false;

            if (arguments.exists(1, true))
            {
                auto at = arguments.at(1);
                expand = at.get_bool(false);
            }

            const std::wstring Input = std::any_cast<std::wstring>(arguments.get(0));
            auto temp = HR::SetRegistrString(HKey, SubKey, Key, Input, expand);
            std::any temp_any = std::any(temp);
            workData->result->reset();
            workData->result->swap(temp_any);
        }
    }

    //* export function getRegistrKeys(HKey: HKEY, SubKey: string, key: string | null): chQueryFolderKey;

    if (COMMAND == ENV_INFO_COMMAND::GET_REGISTR_KEYS)
    {

        auto temp = HR::queryRegistrFolderInfo(HKey, SubKey, true, true);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function getRegistrStringList(HKey: HKEY, SubKey: string, key: string | null): string[] | null;

    if (COMMAND == ENV_INFO_COMMAND::GET_REGISTR_STRING_LIST)
    {
        std::vector<std::wstring> temp = HR::GetRegistrMulti(HKey, SubKey, Key);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function setRegistrStringList(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[]): boolean;

    if (COMMAND == ENV_INFO_COMMAND::SET_REGISTR_STRING_LIST)
    {
        if (arguments.exists(0, true))
        {
            const auto arg = arguments.get(0);

            if (typeid(std::vector<std::wstring>) == arg.type())
            {

                const std::vector<std::wstring> Multilist = std::any_cast<std::vector<std::wstring>>(arguments.get(0));

                auto temp = HR::SetRegistrMulti(HKey, SubKey, Key, Multilist);
                std::any temp_any = std::any(temp);
                workData->result->reset();
                workData->result->swap(temp_any);
            }

            else if (typeid(std::wstring) == arg.type())
            {

                const std::wstring Input = std::any_cast<std::wstring>(arguments.get(0));
                const std::vector<std::wstring> Multilist = hmc_string_util::convertMultiStringArray(Input);
                auto temp = HR::SetRegistrMulti(HKey, SubKey, Key, Multilist);
                std::any temp_any = std::any(temp);
                workData->result->reset();
                workData->result->swap(temp_any);
            }
        }
    }

    //* export function getRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null): Buffer | null;

    if (COMMAND == ENV_INFO_COMMAND::GET_REGISTR_BUFFER)
    {
        auto temp = HR::GetRegistrSourceValue(HKey, SubKey, Key);
        if (temp.exists)
        {

            std::any temp_any = std::any(temp.value);
            workData->result->reset();
            workData->result->swap(temp_any);
        }
    }

    //* export function setRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null, String: Buffer): boolean;

    if (COMMAND == ENV_INFO_COMMAND::SET_REGISTR_BUFFER)
    {
        if (arguments.exists(0, true))
        {
            const std::vector<uint8_t> Input = std::any_cast<std::vector<uint8_t>>(arguments.get(0));

            auto temp = HR::SetRegistrSourceValue(HKey, SubKey, Key, REG_BINARY, Input);
            std::any temp_any = std::any(temp);
            workData->result->reset();
            workData->result->swap(temp_any);
        }
    }

    //* export function getRegistrValue(HKey: HKEY, SubKey: string, key: string | null): REG_VALUE | null;

    if (COMMAND == ENV_INFO_COMMAND::GET_REGISTR_VALUE)
    {

        std::any value = std::any();
        auto Stat = HR::getValueStat(HKey, SubKey, Key);

        if (Stat.exists)
        {
            if (Stat.type == REG_QWORD || Stat.type == (REG_QWORD_LITTLE_ENDIAN))
            {
                auto temp = HR::GetRegistrInt64(HKey, SubKey, Key);
                value = temp;
            }
            else if (Stat.type == (REG_DWORD) || Stat.type == (REG_DWORD_BIG_ENDIAN) || Stat.type == (REG_DWORD_LITTLE_ENDIAN))
            {
                auto temp = HR::GetRegistrInt32(HKey, SubKey, Key);
                value = temp;
            }
            else if (Stat.type == REG_SZ || Stat.type == REG_EXPAND_SZ)
            {
                auto temp = HR::GetRegistrString(HKey, SubKey, Key, Stat.type == REG_EXPAND_SZ);
                value = temp;
            }
            else if (Stat.type == REG_MULTI_SZ)
            {
                auto temp = HR::GetRegistrMulti(HKey, SubKey, Key);
                value = temp;
            }
            else
            {
                auto temp = HR::getRegistrBuffer(HKey, SubKey, Key).value;
                value = temp;
            }
        }

        std::any temp_any = std::any(std::pair<std::any, hmc_registr_util::chValueStat>(value, Stat));
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function copyRegistrValue(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): boolean;

    if (COMMAND == ENV_INFO_COMMAND::COPY_REGISTR_VALUE)
    {
        if (arguments.size() >= 4)
        {

            const std::wstring SourceSubKey = std::any_cast<std::wstring>(arguments.get(0));
            const std::wstring Sourcekey = std::any_cast<std::wstring>(arguments.get(1));
            const std::wstring NewSubKey = std::any_cast<std::wstring>(arguments.get(2));
            const std::wstring Newkey = std::any_cast<std::wstring>(arguments.get(3));

            auto temp = HR::copyRegistrValue(HKey, SourceSubKey, Sourcekey, NewSubKey, Newkey);
            if (!temp)
            {
                if (!HR::hasRegistrFolder(HKey, NewSubKey))
                {
                    HR::createRegistrFolder(HKey, NewSubKey);
                    temp = HR::copyRegistrValue(HKey, SourceSubKey, Sourcekey, NewSubKey, Newkey);
                }
            }
            std::any temp_any = std::any(temp);
            workData->result->reset();
            workData->result->swap(temp_any);
        }
    }

    //* export function copyRegistrFolder(HKey: HKEY, SourceSubKey: string, NewSubKey: string): boolean;

    if (COMMAND == ENV_INFO_COMMAND::COPY_REGISTR_FOLDER)
    {
        auto temp = HR::copyRegistrFolder(HKey, SubKey, Key);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function setRegistrValue(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): boolean;

    if (COMMAND == ENV_INFO_COMMAND::SET_REGISTR_VALUE)
    {
        if (arguments.exists(0, false) && arguments.exists(1, true))
        {
            bool result = false;
            auto at_data = arguments.at(0);
            DWORD at_type = arguments.at(1).get_uint32(0);

            if (!at_data.is_value())
            {
                auto temp = HR::createRegistrValueKey(HKey, SubKey, Key, at_type);
                result = temp;
            }
            else if (at_data.is_wstring())
            {
                auto temp = HR::SetRegistrString(HKey, SubKey, Key, at_data.get_wstring(std::wstring()), at_type == REG_EXPAND_SZ);
                result = temp;
            }
            else if (at_data.is_int64())
            {
                if (at_type == REG_DWORD || at_type == REG_DWORD_BIG_ENDIAN)
                {
                    auto temp = HR::SetRegistrInt32(HKey, SubKey, Key, at_data.get_uint32(0));
                    result = temp;
                }
                else
                {
                    auto temp = HR::SetRegistrInt64(HKey, SubKey, Key, at_data.get_uint64(0));
                    result = temp;
                }
            }
            else if (arguments.exists(0, true) && typeid(std::vector<std::wstring>) == arguments.get(0).type())
            {
                auto at = std::any_cast<std::vector<std::wstring>>(arguments.get(0));

                auto temp = HR::SetRegistrMulti(HKey, SubKey, Key, at);
                result = temp;
            }
            else if (at_data.is_buffer())
            {
                auto temp = HR::SetRegistrSourceValue(HKey, SubKey, Key, at_type, at_data.get_buffer({}));
                result = temp;
            }

            std::any temp_any = std::any(result);
            workData->result->reset();
            workData->result->swap(temp_any);
        }
    }

    //* export function getRegistrValueStat(HKey: HKEY, SubKey: string, key: string | null): RegistrValueStat;

    if (COMMAND == ENV_INFO_COMMAND::GET_REGISTR_VALUE_STAT)
    {
        auto temp = HR::getValueStat(HKey, SubKey, Key);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function getRegistrFolderStat(HKey: HKEY, SubKey: string, key: string | null): RegistrFolderStat;

    if (COMMAND == ENV_INFO_COMMAND::GET_REGISTR_FOLDER_STAT)
    {
        auto temp = HR::queryRegistrFolderInfo(HKey, SubKey, false, false);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function clearRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;

    if (COMMAND == ENV_INFO_COMMAND::CLEAR_REGISTR_VALUE)
    {
        auto temp = HR::removeRegistrValue(HKey, SubKey, Key);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function clearRegistrFolder(HKey: HKEY, SubKey: string, key: string | null): boolean;

    if (COMMAND == ENV_INFO_COMMAND::CLEAR_REGISTR_FOLDER)
    {
        auto temp = HR::queryRegistrFolderInfo(HKey, SubKey, false, true);
        bool is_rm = HR::removeRegistrKey(HKey, SubKey, temp.getValueKeys());

        std::any temp_any = std::any(is_rm);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function removeRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;

    if (COMMAND == ENV_INFO_COMMAND::REMOVE_REGISTR_VALUE)
    {

        auto temp = HR::removeRegistrKey(HKey, SubKey, Key);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function removeRegistrFolder(HKey: HKEY, SubKey: string): boolean;

    if (COMMAND == ENV_INFO_COMMAND::REMOVE_REGISTR_FOLDER)
    {
        auto temp = HR::removeRegistrFolder(HKey, SubKey);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function removeRegistrFolderTree(HKey: HKEY, SubKey: string): boolean;

    if (COMMAND == ENV_INFO_COMMAND::REMOVE_REGISTR_FOLDER_TREE)
    {
        auto temp = HR::removeRegistrTree(HKey, SubKey);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function createRegistrFolder(HKey: HKEY, SubKey: string): boolean;

    if (COMMAND == ENV_INFO_COMMAND::CREATE_REGISTR_FOLDER)
    {
        auto temp = HR::createRegistrFolder(HKey, SubKey);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function createRegistrValueKey(HKey: HKEY, SubKey: string, key: string | string[]): boolean;

    if (COMMAND == ENV_INFO_COMMAND::CREATE_REGISTR_VALUE_KEY)
    {
        if (arguments.exists(0, true) && arguments.exists(1, true))
        {
            auto key = arguments.at(0);
            auto type = arguments.at(1);

            auto temp = HR::createRegistrValueKey(HKey, SubKey, key.get_wstring(L""), (DWORD)type.get_uint32(0));
            std::any temp_any = std::any(temp);
            workData->result->reset();
            workData->result->swap(temp_any);
        }
    }

    //* export function hasRegistrKey(HKey: HKEY, SubKey: string, key: string | null): boolean;

    if (COMMAND == ENV_INFO_COMMAND::HAS_REGISTR_KEY)
    {
        auto temp = HR::hasRegistrKey(HKey, SubKey, Key);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }

    //* export function hasRegistrFolderKey(HKey: HKEY, SubKey: string): boolean;

    if (COMMAND == ENV_INFO_COMMAND::HAS_REGISTR_FOLDER_KEY)
    {
        auto temp = HR::hasRegistrFolder(HKey, SubKey);
        std::any temp_any = std::any(temp);
        workData->result->reset();
        workData->result->swap(temp_any);
    }
}

napi_value HMC_GetRegistrEnvInfo::FormatToResult(napi_env env, HMC_GetRegistrEnvInfo::EnvNextWorkData *workData)
{
    napi_value result = as_Null();

    if (workData == NULL || workData->result == NULL || !workData->result->has_value())
    {
        return result;
    }

    const std::any *ResultPtr = workData->result;

    if (ResultPtr == NULL)
    {
        return result;
    }

    if (typeid(hmc_registr_util::chValue) == ResultPtr->type())
    {
        const auto Input = std::any_cast<hmc_registr_util::chValue>(ResultPtr);
        auto teme = hmc_napi_create_value::jsObject(env);
        // DWORD size;				 // 值的大小
        // std::vector<BYTE> value; // 数据
        // bool exists;			 // 此键是否存在
        teme.putBoolean("exists", Input->exists);
        teme.putBuffer("value", Input->value);
        teme.putNumber("size", (int64_t)Input->size);
        teme.putNumber("type", (int64_t)Input->type);

        return teme.toValue();
    }

    if (typeid(hmc_registr_util::chValueStat) == ResultPtr->type())
    {
        const auto Input = std::any_cast<hmc_registr_util::chValueStat>(ResultPtr);
        auto temp = hmc_napi_create_value::jsObject(env);

        // DWORD size;  // 此所有键总数量
        // bool exists; // 此键是否存在
        // DWORD type;  // 类型

        temp.putBoolean("exists", Input->exists);
        temp.putNumber("size", (int64_t)Input->size);
        temp.putNumber("type", (int64_t)Input->type);
        temp.putString("type_name", hmc_registr_util::type_nameW(Input->type));

        return temp.toValue();
    }

    if (typeid(std::pair<std::any, hmc_registr_util::chValueStat>) == ResultPtr->type())
    {

        auto result = std::any_cast<std::pair<std::any, hmc_registr_util::chValueStat>>(ResultPtr);

        auto temp = hmc_napi_create_value::jsObject(env);
        auto first = result->first;
        auto type = (int64_t)result->second.type;

        temp.putString("type_name", hmc_registr_util::type_nameW(type));
        temp.putBoolean("exists", result->second.exists);
        temp.putNumber("size", (int64_t)result->second.size);
        temp.putNumber("type", type);

        if (!first.has_value())
        {
            temp.putNull("data");
        }
        else
        {

            auto at = hmc_util::anyCast(&first);

            if (at.is_uint64())
            {
                auto data = at.get_uint64(0);
                if (type == REG_QWORD || type == REG_QWORD_LITTLE_ENDIAN)
                {
                    temp.putValue("data", hmc_napi_create_value::Bigint(env, data));
                }
                else
                {
                    temp.putValue("data", hmc_napi_create_value::Number(env, data));
                }
            }
            else if (at.is_wstring())
            {
                auto data = at.get_wstring(L"");
                temp.putString("data", data, data.size());
            }
            else if (at.is_buffer())
            {
                auto buff = at.get_buffer({});
                temp.putBuffer("data", buff);
            }
            else if (at.is_value() && first.type() == typeid(std::vector<std::wstring>))
            {
                auto Input = std::any_cast<std::vector<std::wstring>>(first);
                auto array = hmc_napi_create_value::jsArray(env);

                for (size_t i = 0; i < Input.size(); i++)
                {
                    auto &at = Input.at(i);
                    array.putString(at, at.size());
                }

                temp.putValue("data", array.toValue());
            }
        }

        return temp.toValue();
    }
    if (typeid(hmc_registr_util::chQueryFolderInfoW) == ResultPtr->type())
    {
        auto Input = std::any_cast<hmc_registr_util::chQueryFolderInfoW>(ResultPtr);
        std::wstring temp = hmc_registr_util::chQueryFolderInfoW::to_json(*Input);
        return as_String(temp);
    }

    if (typeid(hmc_registr_util::chQueryFolderInfoA) == ResultPtr->type())
    {
        auto Input = std::any_cast<hmc_registr_util::chQueryFolderInfoA>(ResultPtr);
        std::string temp = hmc_registr_util::chQueryFolderInfoA::to_json(*Input);
        return as_StringA(temp);
    }

    if (typeid(std::vector<std::wstring>) == ResultPtr->type())
    {
        auto Input = *std::any_cast<std::vector<std::wstring>>(ResultPtr);
        auto array = hmc_napi_create_value::jsArray(env);
        for (size_t i = 0; i < Input.size(); i++)
        {
            auto &at = Input.at(i);
            array.putString(at, at.size());
        }
        return array.toValue();
    }

    result = hmc_napi_create_value::New(env, *ResultPtr);

    return result;
}