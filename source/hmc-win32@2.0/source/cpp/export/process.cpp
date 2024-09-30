#include "export.h"
#include "hmc_napi_value_util.h"
#include "hmc_process_util.h"
#include "hmc_util.h"

#include <Shellapi.h>
#include <process.h>
#include <Psapi.h>
#include <winuser.h>

#include <WtsApi32.h>
#include <ShlObj_core.h>
#include <Tlhelp32.h>
#include <set>

namespace HP = hmc_process_util;

namespace HMC_GetProcessName
{

    struct EnvNextWorkData
    {
        napi_deferred deferred;
        napi_async_work work;
        long long ProcessID;
        std::wstring *ProcessName;
        std::uint8_t GET_TYPE;
    };

    void GetProcessName(long long ProcessID, const std::uint8_t GET_TYPE, std::wstring *ProcessName)
    {
        auto temp = HP::getProcessName(ProcessID, (HP::emGetNameType)GET_TYPE);

        if (temp.empty())
        {
            return;
        }
        ProcessName->clear();
        ProcessName->append(temp);
    }

    // async
    void ExecuteAsyncWork(napi_env env, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
        GetProcessName(workData->ProcessID, workData->GET_TYPE, (std::wstring *)workData->ProcessName);
    }

    napi_value ExecuteSync(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Null();

        auto input = hmc_NodeArgsValue(env, info);
        input.eq(0, js_number, true);
        input.eq(1, js_number, false);

        std::uint64_t PROCESS_ID = at_Number64Or(0, 0);
        std::uint8_t GET_TYPE = at_Number32Or(1, HP::GET_FIND);
        std::wstring resultString = std::wstring();

        GetProcessName(PROCESS_ID, GET_TYPE, &resultString);

        if (resultString.empty())
        {
            return result;
        }

        result = as_String(resultString);
        return result;
    }

    // 异步任务完成后的回调函数
    void ResolveWork(napi_env env, napi_status status, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
        HMC_VcFreeAuto(workData);

        napi_value result;
        napi_get_null(env, &result);

        auto ProcessName = std::wstring(workData->ProcessName->begin(), workData->ProcessName->end());

        if (workData->ProcessName != NULL)
        {
            delete workData->ProcessName;
        }

        if (ProcessName.empty())
        {
            napi_resolve_deferred(env, workData->deferred, result);
            napi_delete_async_work(env, workData->work);

            return;
        }

        result = as_String(ProcessName);

        napi_resolve_deferred(env, workData->deferred, result);
        napi_delete_async_work(env, workData->work);
    }

    // 启动异步任务的函数
    napi_value StartAsyncTask(napi_env env, napi_callback_info info)
    {
        napi_value promise;
        napi_value resourceName;
        napi_create_string_utf8(env, __FUNCSIG__, NAPI_AUTO_LENGTH, &resourceName);

        // 初始化异步工作的数据
        EnvNextWorkData *workData = HMC_VcAllocAutoLength(EnvNextWorkData);
        workData->ProcessName = new std::wstring();
        workData->ProcessID = 0;

        auto input = hmc_NodeArgsValue(env, info);

        if (!input.eq(0, js_number, true))
        {
            return NULL;
        }

        input.eq(1, js_number, false);

        workData->ProcessID = at_Number64Or(0, 0);
        workData->GET_TYPE = at_Number64Or(1, HP::GET_FIND);

        napi_create_promise(env, &workData->deferred, &promise);
        napi_create_async_work(env, nullptr, resourceName, ExecuteAsyncWork, ResolveWork, workData, &workData->work);
        napi_queue_async_work(env, workData->work);
        return promise;
    }

}

namespace HMC_GetProcessFilePath
{

    struct EnvNextWorkData
    {
        napi_deferred deferred;
        napi_async_work work;
        DWORD ProcessID;
        std::wstring *ProcessFilePath;
        bool isEnumListExists;
        bool isSnapshotName;
    };

    // async
    void ExecuteAsyncWork(napi_env env, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
        auto temp = HP::getProcessFilePath(workData->ProcessID, workData->isEnumListExists, workData->isSnapshotName);

        if (workData->ProcessFilePath != NULL)
        {
            workData->ProcessFilePath->clear();
            workData->ProcessFilePath->append(temp);
        }
        else
        {
            workData->ProcessFilePath = new std::wstring(temp.begin(), temp.end());
        }
    }

    napi_value ExecuteSync(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Null();

        auto input = hmc_NodeArgsValue(env, info);

        if (!input.eq(0, js_number, true))
        {
            return NULL;
        }

        input.eq(1, js_boolean, false);
        input.eq(2, js_boolean, false);
        // input.eq(3, js_boolean, true);

        std::uint64_t ProcessID = at_Number64Or(0, 0);
        bool isEnumListExists = at_BooleanOr(1, false);
        bool isSnapshotName = at_BooleanOr(2, false);
        // bool isSnapshotName = at_Boolean(3,true);

        std::wstring resultString = HP::getProcessFilePath(ProcessID, isEnumListExists, isSnapshotName);

        if (resultString.empty())
        {
            return result;
        }

        result = as_String(resultString);
        return result;
    }

    // 异步任务完成后的回调函数
    void ResolveWork(napi_env env, napi_status status, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
        HMC_VcFreeAuto(workData);

        napi_value result;
        napi_get_null(env, &result);

        auto ProcessFilePath = std::wstring(workData->ProcessFilePath->begin(), workData->ProcessFilePath->end());

        if (workData->ProcessFilePath != NULL)
        {
            delete workData->ProcessFilePath;
        }

        if (ProcessFilePath.empty())
        {
            napi_resolve_deferred(env, workData->deferred, result);
            napi_delete_async_work(env, workData->work);

            return;
        }

        result = as_String(ProcessFilePath);

        napi_resolve_deferred(env, workData->deferred, result);
        napi_delete_async_work(env, workData->work);
    }

    // 启动异步任务的函数
    napi_value StartAsyncTask(napi_env env, napi_callback_info info)
    {
        napi_value promise;
        napi_value resourceName;
        napi_create_string_utf8(env, __FUNCSIG__, NAPI_AUTO_LENGTH, &resourceName);

        // 初始化异步工作的数据
        EnvNextWorkData *workData = HMC_VcAllocAutoLength(EnvNextWorkData);
        workData->ProcessFilePath = new std::wstring();
        workData->ProcessID = 0;

        auto input = hmc_NodeArgsValue(env, info);

        if (!input.eq(0, js_number, true))
        {
            return NULL;
        }

        input.eq(1, js_boolean, false);
        input.eq(2, js_boolean, false);
        // input.eq(3, js_boolean, true);

        std::uint64_t ProcessID = at_Number64Or(0, 0);
        bool isEnumListExists = at_BooleanOr(1, false);
        bool isSnapshotName = at_BooleanOr(2, false);

        workData->ProcessID = ProcessID;
        workData->isEnumListExists = isEnumListExists;
        workData->isSnapshotName = isSnapshotName;

        napi_create_promise(env, &workData->deferred, &promise);
        napi_create_async_work(env, nullptr, resourceName, ExecuteAsyncWork, ResolveWork, workData, &workData->work);
        napi_queue_async_work(env, workData->work);
        return promise;
    }

}

namespace HMC_GetProcessEnvInfo
{

    enum ENV_INFO_COMMAND
    {
        // getProcessCommandLine2   `string`
        GET_COMMAND = 1,
        // getProcessCwdPath2 `string`
        GET_CWD = 2,
        // getProcessCpuUsage2 `float`
        GET_PROCESS_CPU_USAGE = 3,
        // getProcessStartTime2 `number`
        GET_PROCESS_START_TIME = 5,
        // EnumProcesses `json`
        GET_ENUM_PROCESSES_LIST = 6,
        // getAllProcessList2(true) `json`
        GET_ALL_PROCESS_LIST_PID_NAME = 7,
        // getAllProcessList2 `json`
        GET_ALL_PROCESS_LIST_NONE_NAME = 8,
        // getDetailsProcessList2 `json`
        GET_ALL_PROCESS_LIST_DETAILS = 7,
        // getAllProcessListSnp2 `json`
        GET_ALL_PROCESS_LIST_SNP = 10,
        // getAllProcessListNt2 `json`
        GET_ALL_PROCESS_LIST_NT = 11,
        // getProcessThreadList `json`
        GET_ALL_THREAD_LIST = 12,
        // getParentProcessID2 `long`
        GET_PARENT_PROCESS_ID = 13,
        // existProcess `bool`
        GET_EXIST_PROCESS = 15,
        // getSubProcess `Array<int>`
        GET_SUB_PROCESS = 19,
        // isProcessWow64 `bool`
        GET_IS_PROCESS_WOW64 = 20,
        // getExecutableCwdList `Array<string>`
        GET_EXECUTABLE_CWD_LIST = 21,
        // sleep(ms);
        SEND_SLEEP = 22,
    };

    struct EnvNextWorkData
    {
        napi_deferred deferred;
        napi_async_work work;
        long long ProcessID;
        std::wstring *infoStr;
        int envInfoCommand;
    };

    void EvalCommandFun(long long ProcessID, int evalCommand, std::wstring *infoStr)
    {
        if (infoStr == NULL)
        {
            infoStr = new std::wstring();
            if (infoStr == NULL)
            {
                return;
            }
        }

        infoStr->clear();

        if (GET_COMMAND == evalCommand)
        {
            infoStr->append(HP::getProcessCommandLine(ProcessID));
            return;
        }

        if (GET_CWD == evalCommand)
        {
            infoStr->append(HP::getProcessCwdPath(ProcessID));
            return;
        }

        if (GET_PROCESS_CPU_USAGE == evalCommand)
        {
            auto CpuUsage = HP::getProcessCpuUsage(ProcessID);
            infoStr->append(std::to_wstring(CpuUsage));
            return;
        }

        if (GET_PROCESS_START_TIME == evalCommand)
        {
            auto CpuUsage = HP::getProcessStartTime(ProcessID);
            infoStr->append(std::to_wstring(CpuUsage));
            return;
        }

        if (GET_ENUM_PROCESSES_LIST == evalCommand)
        {

            auto pidList = hmc_process_util::enumProcessIDList();

            std::string result = hmc_string_util::vec_to_array_json(pidList);

            infoStr->append(hmc_string_util::asciiConvers(result));
            return;
        }

        if (GET_ALL_PROCESS_LIST_NONE_NAME == evalCommand || GET_ALL_PROCESS_LIST_PID_NAME == evalCommand)
        {
            auto ProcessList = hmc_process_util::getAllProcessList(GET_ALL_PROCESS_LIST_PID_NAME == evalCommand);

            infoStr->append(hmc_process_util::ch_ProcessEnumItem::to_json(ProcessList));
            return;
        }

        if (GET_ALL_PROCESS_LIST_NT == evalCommand)
        {

            auto ProcessList = hmc_process_util::getAllProcessNtList();

            infoStr->append(hmc_process_util::ch_PSYSTEM_PROCESS_INFORMATION::to_json(ProcessList));
            return;
        }

        if (GET_ALL_PROCESS_LIST_SNP == evalCommand)
        {

            auto ProcessList = hmc_process_util::getProcessSnapshot();

            infoStr->append(hmc_process_util::ch_PROCESSENTRY32W::to_json(ProcessList));
            return;
        }

        if (GET_ALL_THREAD_LIST == evalCommand)
        {

            if (ProcessID >= 0)
            {
                auto ProcessList = hmc_process_util::getProcessThreadList(ProcessID);
                infoStr->append(hmc_process_util::ch_THREADENTRY32::to_json(ProcessList));
                return;
            }

            auto ProcessList = hmc_process_util::getThreadSnapshot();
            infoStr->append(hmc_process_util::ch_THREADENTRY32::to_json(ProcessList));
            return;
        }

        if (GET_PARENT_PROCESS_ID == evalCommand)
        {
            auto PPID = hmc_process_util::getParentProcess(ProcessID);
            infoStr->append(std::to_wstring(PPID));
            return;
        }

        if (GET_EXIST_PROCESS == evalCommand)
        {
            bool exist = hmc_process_util::existProcess(ProcessID);

            if (!exist)
            {
                exist = hmc_process_util::existProcessInEnum(ProcessID);
            }

            infoStr->append(std::to_wstring(exist ? 1 : 0));
            return;
        }

        if (GET_SUB_PROCESS == evalCommand)
        {
            auto SubProcessList = hmc_process_util::getSubProcess(ProcessID);
            auto temp = hmc_string_util::vec_to_array_json(SubProcessList);
            infoStr->append(hmc_string_util::asciiConvers(temp));
        }

        if (GET_IS_PROCESS_WOW64 == evalCommand)
        {
            bool exist = false;
            if (ProcessID >= 1)
            {
                exist = hmc_process_util::isProcessWow64(ProcessID);
            }
            else
            {
                exist = hmc_process_util::isProcessWow64();
            }

            infoStr->append(std::to_wstring(exist ? 1 : 0));
            return;
        }

        if(GET_EXECUTABLE_CWD_LIST==evalCommand){
            std::vector<std::wstring> CwdList = hmc_process_util::getExecutableCwdList(ProcessID);
            std::wstring temp = hmc_string_util::vec_to_array_json(CwdList);
            
            infoStr->append(std::move(temp));
            return;
        }

        if(SEND_SLEEP==evalCommand){
            ::Sleep(ProcessID);
            return;
        }

    }

    // async
    void ExecuteAsyncWork(napi_env env, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;

        if (workData->infoStr == NULL)
        {
            return;
        }

        EvalCommandFun(workData->ProcessID, workData->envInfoCommand, workData->infoStr);
    }

    napi_value ExecuteSync(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Null();

        auto input = hmc_NodeArgsValue(env, info);

        if (!input.eq({{0, js_number}, {1, js_number}}, true))
        {
            return NULL;
        }

        long long ProcessID = at_Number64Or(0, 0);
        int funCommand = at_Number64Or(1, 0);

        std::wstring resultString;

        EvalCommandFun(ProcessID, funCommand, &resultString);

        if (resultString.empty())
        {
            return result;
        }

        result = as_String(resultString);
        return result;
    }

    // 异步任务完成后的回调函数
    void ResolveWork(napi_env env, napi_status status, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
        HMC_VcFreeAuto(workData);

        napi_value result;
        napi_get_null(env, &result);

        auto infoStr = std::wstring(workData->infoStr->begin(), workData->infoStr->end());

        if (workData->infoStr != NULL)
        {
            delete workData->infoStr;
        }

        if (infoStr.empty())
        {
            napi_resolve_deferred(env, workData->deferred, result);
            napi_delete_async_work(env, workData->work);

            return;
        }

        result = as_String(infoStr);

        napi_resolve_deferred(env, workData->deferred, result);
        napi_delete_async_work(env, workData->work);
    }

    // 启动异步任务的函数
    napi_value StartAsyncTask(napi_env env, napi_callback_info info)
    {
        napi_value promise;
        napi_value resourceName;
        napi_create_string_utf8(env, __FUNCSIG__, NAPI_AUTO_LENGTH, &resourceName);

        // 初始化异步工作的数据
        EnvNextWorkData *workData = HMC_VcAllocAutoLength(EnvNextWorkData);
        workData->infoStr = new std::wstring();
        workData->ProcessID = 0;

        auto input = hmc_NodeArgsValue(env, info);

        if (!input.eq({{0, js_number}, {1, js_number}}, true))
        {
            return NULL;
        }

        long long ProcessID = at_Number64Or(0, 0);
        int funCommand = at_Number64Or(1, 0);

        bool isProcessCommand = funCommand == GET_COMMAND;
        bool isProcessCwd = funCommand == GET_CWD;
        bool isProcessCpuUsage = funCommand == GET_PROCESS_CPU_USAGE;
        bool isProcessStartTime = funCommand == GET_PROCESS_START_TIME;

        workData->ProcessID = ProcessID;
        workData->envInfoCommand = funCommand;

        napi_create_promise(env, &workData->deferred, &promise);
        napi_create_async_work(env, nullptr, resourceName, ExecuteAsyncWork, ResolveWork, workData, &workData->work);
        napi_queue_async_work(env, workData->work);
        return promise;
    }

}

