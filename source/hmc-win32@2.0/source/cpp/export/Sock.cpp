#include "export.h"
#include "hmc_string_util.h"
#include "hmc_napi_value_util.h"
#include "hmc_string_util.h"
#include "hmc_process_util.h"
#include "hmc_path_util.h"
#include "hmc_sock_util.h"

#include "hmc_util.h"

#include <ShlObj.h>

namespace HMC_GetSockEnvInfo
{

    enum class HMC_GET_SOCK_ENV_INFO_ID
    {
        /**占位符 */
        NONE = 0,
        /** 获取本机局域网的ip(v4)*/
        ipv4 = 1,
        /** 获取本机局域网的ip(v4)*/
        getIpaddressList = 1,
        /**获取本机局域网的ip(适配器,v4,v6)*/
        ip = 2,
        /**获取本机局域网的ip(适配器,v4,v6)*/
        adapterIP = 3,
        /** 获取主机网络信息*/
        getNetParams = 8,
        /** 获取系统代理链接（仅在启用系统代理时）*/
        getSystemProxyServer = 14,
        /** 获取系统代理pac脚本链接*/
        getSystemProxyPac = 15,
        /** 从默认dns(联网)解析域名主机ip*/
        getDomainIPaddress = 17,
        /** 获取hosts文件的路径*/
        getHostsPath = 18,
        /** 获取此端口被哪个进程占用了*/
        getTCPv6PortProcessID = 19,
        /** 获取此端口被哪个进程占用了*/
        getUDPv6PortProcessID = 25,
        /** 获取此端口被哪个进程占用了*/
        getUDPv4PortProcessID = 26,
        /** 获取此端口被哪个进程占用了*/
        getTCPv4PortProcessID = 27,
        /** 枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息*/
        getConnectNetList = 29,
        /** 判断当前软件是否拥有管理员权限*/
        isAdmin = 32,
        getMacAddresses = 33,
    };

    const std::map<HMC_GET_SOCK_ENV_INFO_ID, std::vector<std::tuple<size_t, js_valuetype>>> GET_SOCK_EQ_TYPE_LIST = {
        {HMC_GET_SOCK_ENV_INFO_ID::NONE, {{0, js_boolean}, {1, js_boolean}, {2, js_boolean}, {3, js_boolean}}},
    };

    struct EnvNextWorkData : public HMC_PromiseUtilV2::EnvNextWorkDataTemplate<HMC_GET_SOCK_ENV_INFO_ID>
    {
    };

    void main(void *Work);

    const std::map<HMC_GET_SOCK_ENV_INFO_ID, std::function<void(EnvNextWorkData *workData)>> GET_SHELL_FUNC_LIST = {
        {HMC_GET_SOCK_ENV_INFO_ID::NONE, main}};

    void main(void *Work)
    {

        using ENV_ID = HMC_GET_SOCK_ENV_INFO_ID;

        EnvNextWorkData *work = (EnvNextWorkData *)Work;

        const ENV_ID TAKE_TYPE = work->TAKE_TYPE;

        if (TAKE_TYPE == ENV_ID::NONE)
        {
            return;
        }

        // 优先查找可引用函数列表
        if (GET_SHELL_FUNC_LIST.find(TAKE_TYPE) != GET_SHELL_FUNC_LIST.end())
        {

            for (auto &&GET_SHELL_FUNC : GET_SHELL_FUNC_LIST)
            {

                if (GET_SHELL_FUNC.first == work->TAKE_TYPE)
                {
                    auto fun = GET_SHELL_FUNC.second;
                    fun(work);
                    return;
                }
            }
        }

        if (ENV_ID::isAdmin == TAKE_TYPE)
        {

            (*work->Result) = ::IsUserAnAdmin();
            return;
        }

        if (ENV_ID::ipv4 == TAKE_TYPE || ENV_ID::getIpaddressList == TAKE_TYPE)
        {
            auto temp = hmc_sock_util::getIpaddressList();
            (*work->Result) = hmc_sock_util::chLocalVddrItemV4::to_json(temp);
            return;
        }

        if (ENV_ID::adapterIP == TAKE_TYPE || ENV_ID::ip == TAKE_TYPE)
        {
            auto temp = hmc_sock_util::getAdapterIPList();
            (*work->Result) = hmc_sock_util::chNetAdapterAddrItem::to_json(temp);
            return;
        }

        if (TAKE_TYPE == ENV_ID::getHostsPath)
        {
            auto temp = hmc_sock_util::getHostsPath();
            (*work->Result) = temp;
            return;
        }

        if (TAKE_TYPE == ENV_ID::getSystemProxyPac)
        {
            std::wstring ProxyServerUrl;
            auto temp = hmc_sock_util::getSystemProxyPac(ProxyServerUrl);
            if (temp)
            {
                (*work->Result) = ProxyServerUrl;
            }
            return;
        }

        if (TAKE_TYPE == ENV_ID::getSystemProxyServer)
        {
            std::wstring ProxyServerUrl;
            auto temp = hmc_sock_util::getSystemProxyServer(ProxyServerUrl);
            if (temp)
            {
                (*work->Result) = ProxyServerUrl;
            }
            return;
        }

        if (TAKE_TYPE == ENV_ID::getNetParams)
        {
            auto temp = hmc_sock_util::getNetParams();
            (*work->Result) = temp.to_json();
            return;
        }

        if (TAKE_TYPE == ENV_ID::getTCPv4PortProcessID ||
            TAKE_TYPE == ENV_ID::getTCPv6PortProcessID ||
            TAKE_TYPE == ENV_ID::getUDPv4PortProcessID ||
            TAKE_TYPE == ENV_ID::getUDPv6PortProcessID)
        {
            int64_t port = work->get<int64_t>(0, 0);

            if (TAKE_TYPE == ENV_ID::getTCPv4PortProcessID)
            {
                auto temp = hmc_sock_util::getPortProcessTCP((uint16_t)port);
                (*work->Result) = static_cast<int64_t>(temp);
                return;
            }

            if (TAKE_TYPE == ENV_ID::getUDPv4PortProcessID)
            {
                auto temp = hmc_sock_util::getPortProcessUDP((uint16_t)port);
                (*work->Result) = static_cast<int64_t>(temp);
                return;
            }

            if (TAKE_TYPE == ENV_ID::getTCPv6PortProcessID)
            {
                auto temp = hmc_sock_util::getPortProcessTCP6((uint16_t)port);
                (*work->Result) = hmc_util::formatNumberList<int64_t, DWORD>(temp);
                return;
            }

            if (TAKE_TYPE == ENV_ID::getUDPv6PortProcessID)
            {
                auto temp = hmc_sock_util::getPortProcessUDP6((uint16_t)port);
                (*work->Result) = hmc_util::formatNumberList<int64_t, DWORD>(temp);
                return;
            }

            return;
        }

        if (TAKE_TYPE == ENV_ID::getDomainIPaddress)
        {
            std::wstring domain;

            work->get_if<std::wstring>(0, &domain);

            if (domain.empty())
            {
                return;
            }

            auto temp = hmc_sock_util::getDomainAddress(domain);
            (*work->Result) = temp;
            return;
        }

        if (TAKE_TYPE == ENV_ID::getConnectNetList)
        {
            bool tcp = true;
            bool udp = true;
            bool tcp6 = true;
            bool udp6 = true;

            work->get_if<bool>(0, &tcp);
            work->get_if<bool>(1, &udp);
            work->get_if<bool>(2, &tcp6);
            work->get_if<bool>(3, &udp6);

            auto ConnectNetList = hmc_sock_util::enumConnectNet(tcp, udp, tcp6, udp6);

            auto ConnectNetListJson = std::wstring();

            ConnectNetListJson.reserve(ConnectNetList.size() * MAX_PATH);

            ConnectNetListJson.push_back('[');

            for (size_t i = 0; i < ConnectNetList.size(); i++)
            {
                auto &ConnectNet = ConnectNetList.at(i);

                if (std::holds_alternative<hmc_sock_util::chConnectNet>(ConnectNet))
                {

                    auto &ConnectNetUDP = std::get<hmc_sock_util::chConnectNet>(ConnectNet);

                    auto json_value = ConnectNetUDP.to_json();
                    ConnectNetListJson.append(std::move(json_value));
                }

                if (std::holds_alternative<hmc_sock_util::chConnectNetTCP>(ConnectNet))
                {

                    auto &ConnectNetTCP = std::get<hmc_sock_util::chConnectNetTCP>(ConnectNet);

                    auto json_value = ConnectNetTCP.to_json();
                    ConnectNetListJson.append(std::move(json_value));
                }

                ConnectNetListJson.push_back(',');
            }

            if (!ConnectNetList.empty())
            {
                ConnectNetListJson.pop_back();
            }

            ConnectNetListJson.push_back(']');

            ConnectNetListJson.shrink_to_fit();

            (*work->Result) = ConnectNetListJson;
            return;
        }

        if (TAKE_TYPE == ENV_ID::getMacAddresses)
        {
            auto temp = hmc_sock_util::getMacAddresses();
            (*work->Result) = temp;
            return;
        }
    }

    // async
    void ExecuteAsyncWork(napi_env env, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
        try
        {
            main(workData);
        }
        HMC_CATCH_ALL;
    }

    napi_value ExecuteSync(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Null();

        try
        {
            auto input = hmc_NodeArgsValue(env, info);
            auto *workData = EnvNextWorkData::make();

            HMC_FreeAnyAuto(EnvNextWorkData::gc(workData););

            bool is_eq_args = HMC_PromiseUtilV2::get_argumentsTemplate<HMC_GET_SOCK_ENV_INFO_ID, EnvNextWorkData>(env, input, workData, GET_SOCK_EQ_TYPE_LIST);
            if (workData == NULL || !is_eq_args)
            {
                return result;
            }

            main(workData);

            result = hmc_napi_create_value::Variant(env, *workData->Result);
            return result;
        }
        HMC_CATCH_ALL;
        return hmc_napi_create_value::Error(env, "A fatal error occurred unexpectedly.", __FUNCSIG__, "HMC_SHELL_API_CATCH");
    }

    // 异步任务完成后的回调函数
    void ResolveWork(napi_env env, napi_status status, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
        HMC_FreeAnyAuto(EnvNextWorkData::gc(workData););

        napi_value result;
        napi_get_null(env, &result);

        if (workData == NULL || workData->Result == NULL || workData->Result->index() == 0)
        {
            if (workData != NULL)
            {
                napi_resolve_deferred(env, workData->deferred, result);
                napi_delete_async_work(env, workData->work);
            }
            return;
        }

        result = hmc_napi_create_value::Variant(env, *workData->Result);

        if (result == NULL)
        {
            napi_get_null(env, &result);
        }

        napi_resolve_deferred(env, workData->deferred, result);
        napi_delete_async_work(env, workData->work);
    }

    // 启动异步任务的函数
    napi_value StartAsyncTask(napi_env env, napi_callback_info info)
    {
        napi_value promise;
        try
        {
            napi_value resourceName;
            napi_create_string_utf8(env, __FUNCSIG__, NAPI_AUTO_LENGTH, &resourceName);

            auto *workData = EnvNextWorkData::make();

            auto input = hmc_NodeArgsValue(env, info);
            bool is_eq_args = HMC_PromiseUtilV2::get_argumentsTemplate<HMC_GET_SOCK_ENV_INFO_ID, EnvNextWorkData>(env, input, workData, GET_SOCK_EQ_TYPE_LIST);
            if (workData == NULL || !is_eq_args)
            {
                EnvNextWorkData::gc(workData);
                return as_Null();
            }

            napi_create_promise(env, &workData->deferred, &promise);
            napi_create_async_work(env, nullptr, resourceName, ExecuteAsyncWork, ResolveWork, workData, &workData->work);
            napi_queue_async_work(env, workData->work);
            return promise;
        }
        HMC_CATCH_ALL;
        return hmc_napi_create_value::Error(env, "A fatal error occurred unexpectedly.", __FUNCSIG__, "HMC_SHELL_API_CATCH");
    }

}
