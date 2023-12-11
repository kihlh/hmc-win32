#include "../Mian.hpp";
#include "./hmc_string_util.hpp"
#include "./napi_value_util.hpp";
// #include "./environment.hpp";
// #include "./fmt11.hpp";


vector<HMC_PROCESSENTRY32W> GetProcessSnapshot(vector<DWORD> pid_list, bool early_result)
{
    vector<HMC_PROCESSENTRY32W> result = {};

    DWORD PID = 0;
    HANDLE hProcessSnapshot;
    PROCESSENTRY32W PE32;

    // gc
    std::shared_ptr<void> _shared_free_handle(nullptr, [&](void *)
                                              {
        if (hProcessSnapshot != NULL) {
            ::CloseHandle(hProcessSnapshot);
        } });

    hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (hProcessSnapshot == INVALID_HANDLE_VALUE)
    {
        return result;
    }

    PE32.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(hProcessSnapshot, &PE32))
    {
        return result;
    }

    do
    {
        // 满足要求的数量得结束
        if (early_result && result.size() == pid_list.size())
        {
            return result;
        }

        for (size_t i = 0; i < pid_list.size(); i++)
        {
            if (pid_list[i] == PE32.th32ProcessID)
            {
                HMC_PROCESSENTRY32W data = HMC_PROCESSENTRY32W{
                    PE32.dwSize + 0,
                    PE32.cntUsage + 0,
                    PE32.th32ProcessID + 0,
                    (DWORD)PE32.th32DefaultHeapID + 0,
                    PE32.th32ModuleID + 0,
                    PE32.cntThreads + 0,
                    PE32.th32ParentProcessID + 0,
                    (DWORD)PE32.pcPriClassBase,
                    PE32.dwFlags + 0,
                    wstring(PE32.szExeFile),
                };

                result.push_back(data);
            }
        }

    } while (Process32NextW(hProcessSnapshot, &PE32));

    return result;
}
vector<HMC_PROCESSENTRY32W> GetProcessSnapshot(size_t Start, size_t End)
{
    vector<DWORD> pid_list;
    if (Start >= 0 && End >= Start)
    {
        for (size_t i = Start; i < End; i++)
        {
            pid_list.push_back((DWORD)i);
        }
        return GetProcessSnapshot(pid_list, true);
    }
    return {};
}

DWORD GetParentProcessID(DWORD processID)
{
    auto GetProcessSnapshotList = GetProcessSnapshot({processID});
    if (GetProcessSnapshotList.empty())
    {
        return NULL;
    }
    else
    {
        return GetProcessSnapshotList[0].th32ParentProcessID;
    }
    return NULL;
}

wstring GetProcessSnapshotNameW(DWORD processID)
{
    auto GetProcessSnapshotList = GetProcessSnapshot({processID});
    if (GetProcessSnapshotList.empty())
    {
        return L"";
    }
    else
    {
        return GetProcessSnapshotList[0].szExeFile;
    }
    return L"";
}

bool ExistProcessID(DWORD processID)
{
    if (processID == 0 || processID == 4)
    {
        return true;
    }
    HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    // gc
    std::shared_ptr<void> _shared_free_handle(nullptr, [&](void *)
                                              {
        if (hProcess != NULL) {
            ::CloseHandle(hProcess);
        } });

    // win10 + 用PROCESS_QUERY_INFORMATION| PROCESS_VM_READ 打开可能会导致失败 改权获取
    if (hProcess == NULL)
    {
        hProcess = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID);
        if (hProcess == NULL)
        {
            return false;
        }
    }

    // 复核 防止句柄获取异常
    DWORD review_pid = GetProcessId(hProcess);

    if (review_pid == processID)
    {
        return true;
    }

    return false;
}

wstring GetProcessIdFilePathW(DWORD processID)
{

    if (processID == (DWORD)0)
    {
        return L"[System Process]";
    }

    wstring result = wstring();

    HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    // Pwstr
    result.reserve(MAX_PATH);
    result.resize(MAX_PATH);

    // gc
    std::shared_ptr<void> _shared_free_handle(nullptr, [&](void *)
                                              {
        if (hProcess != NULL) {
            ::CloseHandle(hProcess);
        } });

    // win10 + 用PROCESS_QUERY_INFORMATION| PROCESS_VM_READ 打开可能会导致失败 改权获取
    if (hProcess == NULL)
    {
        hProcess = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID);
        if (hProcess == NULL)
        {
            return wstring();
        }
    }

    DWORD buf_length = ::GetProcessImageFileNameW(hProcess, &result[0], result.size());

    // 没获取到 用模块法
    if (buf_length == 0)
    {

        // 这里获取的不是dos路径
        buf_length = ::GetModuleFileNameExW(hProcess, NULL, &result[0], result.size());
        if (buf_length > 0)
        {
            result.reserve(buf_length);
            result.resize(buf_length);
            return result;
        }
    }

    // 可能是服务
    if (buf_length == 0)
    {
        if (!::QueryFullProcessImageNameW(hProcess, 0, &result[0], &buf_length))
        {
            // 失败 释放string
            buf_length = 0;
            result.clear();
            result.resize(0);
            result.reserve(0);
        }
    }

    result.reserve(buf_length);
    result.resize(buf_length);

    // 处理 dos 路径
    //
    if (!result.empty() && result.front() == '\\')
    {
        vector<util_Volume> volumeList = util_getVolumeList();

        for (size_t i = 0; i < volumeList.size(); i++)
        {
            util_Volume volume = volumeList[i];
            if (result.find(volume.device) == 0)
            {
                result.replace(0, volume.device.length(), volume.path);
            }
        }
    }

    // 处理 ntoskrnl.exe 不可见问题
    // id 是4 (win内核的i)
    // 系统进程id一般不会
    if (result.empty() && processID < 80)
    {
        vector<HMC_PROCESSENTRY32W> ProcessSnapshotList = GetProcessSnapshot(0, processID + 1);
        DWORD ntoskrnl_pid = 0;

        // 通过特征判断是不是  ntoskrnl.exe
        for (size_t i = 0; i < ProcessSnapshotList.size(); i++)
        {
            auto data = ProcessSnapshotList[i];
            if (ntoskrnl_pid == 0 && data.szExeFile == wstring(L"System"))
            {
                ntoskrnl_pid = data.th32ProcessID;
                if (ntoskrnl_pid == processID)
                {
                    return L"C:\\Windows\\System32\\ntoskrnl.exe";
                }
            }

            if (data.th32ProcessID == processID && ntoskrnl_pid == data.th32ParentProcessID)
            {
                return L"C:\\Windows\\System32\\ntoskrnl.exe";
            }
        }

        // 不是 ntoskrnl.exe 则返回快照名称
        for (size_t i = 0; i < ProcessSnapshotList.size(); i++)
        {
            auto data = ProcessSnapshotList[i];
            if (data.th32ProcessID == processID)
            {
                return data.szExeFile;
            }
        }
    }

    return result;
}

wstring GetProcessNameW(DWORD processID)
{
    wstring result = GetProcessIdFilePathW(processID);
    return hmc_string_util::getPathBaseName(result);
}

napi_value fn_getProcessidFilePath_v2(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_number}, true))
    {
        return NULL;
    }
    EnableShutDownPriv();

    return hmc_napi_create_value::String(env, GetProcessIdFilePathW(input.getInt64(0)));
}

napi_value fn_getProcessidBaseName_v2(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_number}, true))
    {
        return NULL;
    }
    EnableShutDownPriv();

    return hmc_napi_create_value::String(env, GetProcessNameW(input.getInt64(0)));
}

napi_value fn_hasProcess_v2(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_number}, true))
    {
        return NULL;
    }
    EnableShutDownPriv();
    auto out = ExistProcessID(input.getInt64(0));

    return hmc_napi_create_value::Boolean(env, out);
}

namespace Promise_getProcessidFilePath
{

    typedef struct
    {
        // 工作环境
        napi_async_work work;
        // napi处理延迟的内联
        napi_deferred deferred;
        // 数据体的内存 必须是固定大小的值 不能动态调整内存
        // vector<string> data;
    } PromiseData;

    DWORD __Promise_getProcessidFilePath_work_Pid = 0;
    wstring __Promise_getProcessidFilePath__work_path;
    /**
     * @brief 处理数据更新 这里是异步的
     *
     * @param env
     * @param data
     */
    void asyncWorkFun(napi_env env, void *data)
    {
        PromiseData *addon_data = (PromiseData *)data;
        __Promise_getProcessidFilePath__work_path.append(GetProcessIdFilePathW(__Promise_getProcessidFilePath_work_Pid));
    }

    /**
     * @brief 运行结束的时候会执行此 这里是同步的
     *
     * @param env
     * @param status
     * @param data
     */
    void completeWork(napi_env env, napi_status status, void *data)
    {
        if (status != napi_ok)
        {
            return;
        }

        PromiseData *addon_data = (PromiseData *)data;

        napi_resolve_deferred(env, addon_data->deferred, hmc_napi_create_value::String(env, __Promise_getProcessidFilePath__work_path));
        __Promise_getProcessidFilePath_work_Pid = 0;
        __Promise_getProcessidFilePath__work_path.clear();
        __Promise_getProcessidFilePath__work_path.resize(0);
        __Promise_getProcessidFilePath__work_path.reserve(0);
        // 清理与此运行关联的工作环境
        napi_delete_async_work(env, addon_data->work);

        // 将这两个值都设置为NULL，这样JavaScript可以启动新的线程运行。
        addon_data->work = NULL;
        addon_data->deferred = NULL;
    }

    /**
     * @brief 创建一个 promise对象
     *
     * @param env
     * @param info
     * @return napi_value
     */
    napi_value startWork(napi_env env, napi_callback_info info)
    {
        napi_value work_name, promise;
        PromiseData *addon_data;

        string work_message = string(__FUNCTION__).append("  work_message ->  ");

        // 获取插件的工作数据。
        napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)(&addon_data));

        // 添加一个工作线程的 结构体

        if (addon_data->work != NULL)
        {
            work_message.append("error < Promise workspace has not been released. > ");
            napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
            return NULL;
        }

        // 创建一个字符串来描述这个异步操作。

        work_message.append("Node-API Deferred Promise from Async Work Item");
        napi_create_string_utf8(
            env, work_message.c_str(), work_message.length(), &work_name);

        hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

        // 参数预设 如果不符合则返回void
        if (!input.eq(0, {js_number}, true))
        {
            return NULL;
        }
        EnableShutDownPriv();
        
        __Promise_getProcessidFilePath_work_Pid = input.getDword(0);

        // 创建一个延迟的promise对象，在完成时我们将解决它
        napi_create_promise(env, &(addon_data->deferred), &promise);

        // 创建一个异步工作项，传递插件数据，这将使
        // 工作线程访问上述创建的延迟的 promise对象
        napi_create_async_work(env,
                               NULL,
                               work_name,
                               asyncWorkFun,
                               completeWork,
                               addon_data,
                               &(addon_data->work));

        // 添加进node的异步队列
        napi_queue_async_work(env, addon_data->work);

        return promise;
    }

    /**
     * @brief 释放内存 请注意这里是模块卸载时候才执行
     *
     * @param env
     * @param data
     * @param hint
     */
    void gcWork(napi_env env, void *data, void *hint)
    {
        PromiseData *addon_data = (PromiseData *)data;

        free(addon_data);
    }

    /**
     * @brief 导出这个异步函数
     *
     * @param env
     * @param exports
     * @param name
     */
    void exports(napi_env env, napi_value exports, string name)
    {
        PromiseData *addon_data = (PromiseData *)malloc(sizeof(*addon_data));

        addon_data->work = NULL;

        napi_value exported_function;

        napi_create_function(env,
                             name.c_str(),
                             NAPI_AUTO_LENGTH,
                             startWork,
                             addon_data,
                             &exported_function);

        napi_set_named_property(env, exports, name.c_str(), exported_function);

        // 回收
        napi_wrap(env, exports, addon_data, gcWork, NULL, NULL);
    }

} // namespace PromiseFun

void _fn_process_exports(napi_env env, napi_value exports)
{

    Promise_getProcessidFilePath::exports(env, exports, "getProcessidFilePathAsync");
}
