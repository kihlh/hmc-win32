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
        // export function getRegistrQword(HKey: HKEY, SubKey: string, key: string | null): bigint | null;
        GET_REGISTR_QWORD = 70,
        // export function setRegistrQword(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): boolean;
        SET_REGISTR_QWORD = 71,
        // export function getRegistrDword(HKey: HKEY, SubKey: string, key: string | null): number | null;
        GET_REGISTR_DWORD = 72,
        // export function setRegistrDword(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): boolean;
        SET_REGISTR_DWORD = 73,
        // export function getRegistrString(HKey: HKEY, SubKey: string, key: string | null): string | null;
        GET_REGISTR_STRING = 74,
        // export function setRegistrString(HKey: HKEY, SubKey: string, key: string | null, String: string): boolean;
        SET_REGISTR_STRING = 75,
        // export function getRegistrKeys(HKey: HKEY, SubKey: string, key: string | null): chQueryFolderKey;
        GET_REGISTR_KEYS = 76,
        // export function getRegistrStringList(HKey: HKEY, SubKey: string, key: string | null): string[] | null;
        GET_REGISTR_STRING_LIST = 77,
        // export function setRegistrStringList(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[]): boolean;
        SET_REGISTR_STRING_LIST = 78,
        // export function getRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null): Buffer | null;
        GET_REGISTR_BUFFER = 79,
        // export function setRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null, String: Buffer): boolean;
        SET_REGISTR_BUFFER = 710,
        // export function getRegistrValue(HKey: HKEY, SubKey: string, key: string | null): REG_VALUE | null;
        GET_REGISTR_VALUE = 711,
        // export function copyRegistrValue(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): boolean;
        COPY_REGISTR_VALUE = 712,
        // export function copyRegistrFolder(HKey: HKEY, SourceSubKey: string, NewSubKey: string): boolean;
        COPY_REGISTR_FOLDER = 713,
        // export function setRegistrValue(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): boolean;
        SET_REGISTR_VALUE = 714,
        // export function getRegistrValueStat(HKey: HKEY, SubKey: string, key: string | null): RegistrValueStat;
        GET_REGISTR_VALUE_STAT = 715,
        // export function getRegistrFolderStat(HKey: HKEY, SubKey: string, key: string | null): RegistrFolderStat;
        GET_REGISTR_FOLDER_STAT = 716,
        // export function clearRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;
        CLEAR_REGISTR_VALUE = 717,
        // export function clearRegistrFolder(HKey: HKEY, SubKey: string, key: string | null): boolean;
        CLEAR_REGISTR_FOLDER = 718,
        // export function removeRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;
        REMOVE_REGISTR_VALUE = 719,
        // export function removeRegistrFolder(HKey: HKEY, SubKey: string): boolean;
        REMOVE_REGISTR_FOLDER = 720,
        // export function removeRegistrFolderTree(HKey: HKEY, SubKey: string): boolean;
        REMOVE_REGISTR_FOLDER_TREE = 721,
        // export function createRegistrFolder(HKey: HKEY, SubKey: string): boolean;
        CREATE_REGISTR_FOLDER = 722,
        // export function createRegistrValueKey(HKey: HKEY, SubKey: string, key: string | string[]): boolean;
        CREATE_REGISTR_VALUE_KEY = 723,
        // export function hasRegistrKey(HKey: HKEY, SubKey: string, key: string | null): boolean;
        HAS_REGISTR_KEY = 724,
        // export function hasRegistrFolderKey(HKey: HKEY, SubKey: string): boolean;
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
    EQ_ARG_ITEM makeAllEqArgItem();
    void init_Arguments_EQ_type();
    void GC(EnvNextWorkData* workData);
    EnvNextWorkData* GetArguments(napi_env env, hmc_NodeArgsValue input);
    void ExecuteAsyncWork(napi_env env, void* data);
    ENV_INFO_COMMAND EQ(napi_env env, hmc_NodeArgsValue input);
    HKEY GET_HKEY(napi_env env, hmc_NodeArgsValue input);
    napi_value ExecuteSync(napi_env env, napi_callback_info info);
    void ResolveWork(napi_env env, napi_status status, void* data);
    napi_value StartAsyncTask(napi_env env, napi_callback_info info);

    //---------------

    EQ_ARG_ITEM makeAllEqArgItem()
    {
        EQ_ARG_ITEM result = EQ_ARG_ITEM();
        // 第一位永久为 HKEY
        result.insert(std::make_pair(0, std::vector<js_valuetype>({js_string})));
        // 第二位永久为 string
        result.insert(std::make_pair(1, std::vector<js_valuetype>({js_string})));
        return result;
    }

    void init_Arguments_EQ_type()
    {
        if (ArgumentsEQ.size() >= 1)
        {
            return;
        }

        for (auto command : allCommands)
        {
            ArgumentsEQ.insert(std::pair<ENV_INFO_COMMAND, EQ_ARG_ITEM>(command, makeAllEqArgItem()));
        }

        // export function *(HKey: HKEY, SubKey: string, key: string | null)
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

            auto temp = std::make_pair(2, std::vector<js_valuetype>({js_string, js_array}));
            at.insert(temp);
        }

        if (ArgumentsEQ.find(ENV_INFO_COMMAND::SET_REGISTR_VALUE) != ArgumentsEQ.end())
        {
            auto &at = ArgumentsEQ.at(ENV_INFO_COMMAND::SET_REGISTR_VALUE);

            auto temp1 = std::make_pair(2, std::vector<js_valuetype>({js_string}));
            at.insert(temp1);

            auto temp = std::make_pair(3, std::vector<js_valuetype>({js_object}));
            at.insert(temp);
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

    void GC(EnvNextWorkData *workData)
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

    EnvNextWorkData *GetArguments(napi_env env, hmc_NodeArgsValue input)
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
            case ENV_INFO_COMMAND::GET_REGISTR_STRING:
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
            case ENV_INFO_COMMAND::SET_REGISTR_VALUE:
            case ENV_INFO_COMMAND::SET_REGISTR_BUFFER:
            case ENV_INFO_COMMAND::SET_REGISTR_STRING_LIST:
            case ENV_INFO_COMMAND::SET_REGISTR_STRING:
            case ENV_INFO_COMMAND::SET_REGISTR_DWORD:
            case ENV_INFO_COMMAND::SET_REGISTR_QWORD:

            // copy value  3 arg (HKey: HKEY, SourceSubKey: string, NewSubKey: string)
            case ENV_INFO_COMMAND::COPY_REGISTR_FOLDER:

                Key.append(input.getStringWide(3, L""));
                break;

            // ?-----------------------------------------------------------------------------------------

            // create value  3 arg   (HKEY, string, string[]|string[] )
            case ENV_INFO_COMMAND::CREATE_REGISTR_VALUE_KEY:
            {

                if (input.eq(3, {js_array}, false))
                {
                    Key = hmc_string_util::convertMultiStringArray(input.getArrayWstring(3, {}));
                    break;
                }
                Key.append(input.getStringWide(3, L""));
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
                // set value  4 arg   (HKEY, string, string , any )
            case ENV_INFO_COMMAND::SET_REGISTR_VALUE:
            {

                if (workData->arguments != NULL)
                {
                    // workData->arguments->push_back(input.getStringWide(4, L""));
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

    // async
    void ExecuteAsyncWork(napi_env env, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;

        if (workData->result == NULL)
        {
            return;
        }
    }

    ENV_INFO_COMMAND EQ(napi_env env, hmc_NodeArgsValue input)
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

    HKEY GET_HKEY(napi_env env, hmc_NodeArgsValue input)
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

    napi_value ExecuteSync(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Null();

        auto input = hmc_NodeArgsValue(env, info);

        EnvNextWorkData *workData = GetArguments(env, input);
        if (workData == NULL)
        {
            return NULL;
        }

        HMC_FreeAnyAuto(GC(workData););

        return result;
    }

    // 异步任务完成后的回调函数
    void ResolveWork(napi_env env, napi_status status, void *data)
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

        napi_resolve_deferred(env, workData->deferred, result);
        napi_delete_async_work(env, workData->work);
    }

    // 启动异步任务的函数
    napi_value StartAsyncTask(napi_env env, napi_callback_info info)
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

};
