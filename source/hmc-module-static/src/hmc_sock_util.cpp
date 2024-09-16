
// WINSOCKAPI 会和winsock2.h 冲突 难以避免 索性提前禁用 WINSOCKAPI
// !  windows.h 会默认把<winsock.h> 放进来 如果在之前引用了需要把这句放进前面 但是 winsock.h 会和 winsock2.h 冲突导致无法使用ipv6
#define _WINSOCKAPI_

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>
#include <ip2string.h>
#include <iphlpapi.h>
#include <Psapi.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Ntdll.lib")

#include <hmc_sock_util.h>
#include <hmc_util.h>


//不公开
namespace hmc_sock_util {

    /**
     * @brief ip 列表 转换函数 [内联]
     *
     * @param ua
     * @return chNetAdapterAddrList
     */
    extern chNetAdapterAddrList CpUaToAddrItem(PIP_ADAPTER_UNICAST_ADDRESS ua);

    // 格式化ip
    extern std::wstring formatIP(IN6_ADDR dwLocalAddr);
    extern std::optional<std::wstring> GetSystemProxyServer();
}



std::string hmc_sock_util::formatMacAddress(const std::uint8_t* address, int length , char joinChar)
{
    std::string macAddress;
    try
    {
        for (int i = 0; i < length; ++i)
        {
            if (i > 0)
            {
                macAddress.push_back(joinChar);
            }

            char buffer[3];
            ::snprintf(buffer, sizeof(buffer), "%02X", address[i]);
            macAddress += buffer;
        }
    }
    catch (...)
    {
    }
    return macAddress;
}

std::vector<std::string>  hmc_sock_util::getMacAddresses(char joinChar) {
    std::vector<std::string> result;
    try
    {
        DWORD dwSize = 0;
        DWORD dwRetVal = 0;
        PIP_ADAPTER_INFO pAdapter = NULL;

        dwRetVal = ::GetAdaptersInfo(NULL, &dwSize);
        if (dwRetVal != ERROR_BUFFER_OVERFLOW)
        {
            return result;
        }

       

        auto pAdapterInfo = VcRef<IP_ADAPTER_INFO>(dwSize);
       
        if (pAdapterInfo == NULL)
        {
            return result;
        }

        dwRetVal = ::GetAdaptersInfo(pAdapterInfo, &dwSize);
        if (dwRetVal != ERROR_SUCCESS)
        {
            return result;
        }

        pAdapter = pAdapterInfo;
        while (pAdapter)
        {

            std::string macAddress = formatMacAddress(pAdapter->Address, pAdapter->AddressLength,joinChar);
            result.push_back(macAddress);

            pAdapter = pAdapter->Next;
        }
        
    }
    catch (...)
    {
    }
    return result;
}

std::vector<std::string>  hmc_sock_util::getMacAddresses(){
    return getMacAddresses(':');
}

std::wstring hmc_sock_util::formatIP(DWORD dwLocalAddr)
{
    std::uint8_t a = static_cast<std::uint8_t>(dwLocalAddr >> 24 & 0xFF);
    std::uint8_t b = static_cast<std::uint8_t>(dwLocalAddr >> 16 & 0xFF);
    std::uint8_t c = static_cast<std::uint8_t>(dwLocalAddr >> 8 & 0xFF);
    std::uint8_t d = static_cast<std::uint8_t>(dwLocalAddr & 0xFF);

    std::wstring result = std::wstring();

    // max -> 255.255.255.255
    result.reserve(sizeof("255.255.255.255"));
    result.append(std::to_wstring(a));
    result.push_back('.');
    result.append(std::to_wstring(b));
    result.push_back('.');
    result.append(std::to_wstring(c));
    result.push_back('.');
    result.append(std::to_wstring(d));

    return result;
}

std::wstring hmc_sock_util::formatIP(IN6_ADDR dwLocalAddr)
{
    std::wstring result = std::wstring();

    result.resize(INET6_ADDRSTRLEN);

    ::RtlIpv6AddressToStringW(reinterpret_cast<IN6_ADDR*>(&dwLocalAddr), &result[0]);

    hmc_util::removeAllCharPtr(result, L'\0');

    return result;
}

std::wstring hmc_sock_util::formatIP(UCHAR ucLocalAddr[16])
{
    std::wstring result = std::wstring();

    result.resize(INET6_ADDRSTRLEN);

    ::RtlIpv6AddressToStringW(reinterpret_cast<IN6_ADDR*>(&ucLocalAddr), &result[0]);

    hmc_util::removeAllCharPtr(result, L'\0');

    return result;
}

std::vector<hmc_sock_util::chConnectNetTCP> hmc_sock_util::CpEnumConnectNetConnectTCP6()
{
    std::vector<hmc_sock_util::chConnectNetTCP> result;

    try
    {
        ULONG ulSize = sizeof(MIB_TCPTABLE2);
        auto pTcpTable = VcRef<MIB_TCP6TABLE2>();

        if (::GetTcp6Table2(pTcpTable, &ulSize, TRUE) == ERROR_INSUFFICIENT_BUFFER && !pTcpTable.reserve(ulSize))
        {
            return result;
        }

        pTcpTable.reserve(ulSize);

        if (::GetTcp6Table2(pTcpTable, &ulSize, TRUE) == NO_ERROR)
        {
            // ::_pTcpTable_::
            // dwState：TCP 连接的状态，可以是 MIB_TCP_STATE 枚举中定义的值之一，如 CLOSED、LISTEN、ESTABLISHED 等。
            // dwLocalAddr：本地计算机上的 TCP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
            // dwLocalPort：本地计算机上的 TCP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
            // dwRemoteAddr：远程计算机上的 TCP 连接的 IPv4 地址。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此值没有意义。
            // dwRemotePort：远程计算机上的 TCP 连接的网络字节顺序中的远程端口号。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此成员没有意义。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
            // dwOwningPid：发出此 TCP 连接的上下文绑定的进程 PID。
            // dwOffloadState：此 TCP 连接的卸载状态。此参数可以是 TCP_CONNECTION_OFFLOAD_STATE 的枚举值之一，如 InHost、Offloading、Offloaded 等。

            chConnectNetTCP connectNet;
            for (DWORD index = 0; index < pTcpTable->dwNumEntries; index++)
            {
                connectNet.ip = L"0.0.0.0";
                connectNet.ipAddr = 0;
                connectNet.pid = 0;
                connectNet.port = 0;
                connectNet.remoteIP = L"0.0.0.0";
                connectNet.remoteIPAddr = 0;
                connectNet.remotePort = 0;
                connectNet.state = L"UNKNOWN";
                connectNet.type = 6;
                connectNet.typeName = L"TCP6";

                MIB_TCP6ROW2 mibTcprow2 = pTcpTable->table[index];

                // IP解析
                // connectNet.ipAddr = mibTcprow2.dwLocalAddr;
                // connectNet.remoteIPAddr = mibTcprow2.dwRemoteAddr;
                // connectNet.ip = formatIP(mibTcprow2.dwLocalAddr);
                // connectNet.remoteIP = formatIP(mibTcprow2.dwRemoteAddr);
                /*       char ipv6String[INET6_ADDRSTRLEN];
                       if (RtlIpv6AddressToStringA(reinterpret_cast<IN6_ADDR*>(&mibTcprow2.LocalAddr), ipv6String) == NULL) {
                           continue;
                       }
                       char remoteIPv6String[INET6_ADDRSTRLEN];
                       if (RtlIpv6AddressToStringA(reinterpret_cast<IN6_ADDR*>(&mibTcprow2.RemoteAddr), remoteIPv6String) == NULL) {
                           continue;
                       }*/

                connectNet.ip = formatIP(mibTcprow2.LocalAddr);
                connectNet.remoteIP = formatIP(mibTcprow2.RemoteAddr);
                //// 状态和进程
                connectNet.state = getStateName(mibTcprow2.State);
                connectNet.pid = mibTcprow2.dwOwningPid;
                connectNet.existsProcess = false;
                // 端口
                connectNet.port = ntohs((u_short)mibTcprow2.dwLocalPort);
                connectNet.remotePort = ntohs((u_short)mibTcprow2.dwRemotePort);
                if (connectNet.port != 0)
                    result.push_back(connectNet);
            }
        }
    }
    catch (...)
    {
    }
    return result;
}

std::vector<hmc_sock_util::chConnectNetTCP> hmc_sock_util::CpEnumConnectNetConnectTCP4()
{
    std::vector<hmc_sock_util::chConnectNetTCP> result;

    try
    {
        ULONG ulSize = sizeof(MIB_TCPTABLE2);
        auto pTcpTable = VcRef<MIB_TCPTABLE2>();

        if (::GetTcpTable2(pTcpTable, &ulSize, TRUE) == ERROR_INSUFFICIENT_BUFFER && !pTcpTable.reserve(ulSize))
        {
            return result;
        }

        pTcpTable.reserve(ulSize);

        if (::GetTcpTable2(pTcpTable, &ulSize, TRUE) == NO_ERROR)
        {
            // ::_pTcpTable_::
            // dwState：TCP 连接的状态，可以是 MIB_TCP_STATE 枚举中定义的值之一，如 CLOSED、LISTEN、ESTABLISHED 等。
            // dwLocalAddr：本地计算机上的 TCP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
            // dwLocalPort：本地计算机上的 TCP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
            // dwRemoteAddr：远程计算机上的 TCP 连接的 IPv4 地址。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此值没有意义。
            // dwRemotePort：远程计算机上的 TCP 连接的网络字节顺序中的远程端口号。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此成员没有意义。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
            // dwOwningPid：发出此 TCP 连接的上下文绑定的进程 PID。
            // dwOffloadState：此 TCP 连接的卸载状态。此参数可以是 TCP_CONNECTION_OFFLOAD_STATE 的枚举值之一，如 InHost、Offloading、Offloaded 等。

            chConnectNetTCP connectNet;
            for (DWORD index = 0; index < pTcpTable->dwNumEntries; index++)
            {
                connectNet.ip = L"0.0.0.0";
                connectNet.ipAddr = 0;
                connectNet.pid = 0;
                connectNet.port = 0;
                connectNet.remoteIP = L"0.0.0.0";
                connectNet.remoteIPAddr = 0;
                connectNet.remotePort = 0;
                connectNet.state = L"UNKNOWN";
                connectNet.type = 6;
                connectNet.typeName = L"TCP";

                MIB_TCPROW2 mibTcprow2 = pTcpTable->table[index];

                // IP解析
                connectNet.ipAddr = mibTcprow2.dwLocalAddr;
                connectNet.remoteIPAddr = mibTcprow2.dwRemoteAddr;
                connectNet.ip = formatIP(mibTcprow2.dwLocalAddr);
                connectNet.remoteIP = formatIP(mibTcprow2.dwRemoteAddr);

                // 状态和进程
                connectNet.state = getStateName(mibTcprow2.dwState);
                connectNet.pid = mibTcprow2.dwOwningPid;
                connectNet.existsProcess = false;

                // 端口
                connectNet.port = ::ntohs((u_short)mibTcprow2.dwLocalPort);
                connectNet.remotePort = ::ntohs((u_short)mibTcprow2.dwRemotePort);
                if (connectNet.port != 0)
                {
                    result.push_back(connectNet);
                }
            }
        }
    }
    catch (...)
    {
    }

    return result;
}

std::vector<hmc_sock_util::chConnectNet> hmc_sock_util::CpEnumConnectNetConnectUDP6()
{
    std::vector<hmc_sock_util::chConnectNet> result;

    try
    {

        auto pUdpTable = VcRef<MIB_UDP6TABLE_OWNER_PID>();
        ULONG ulSize = 0;
        DWORD dwRetVal = 0;

        // 第一次获取大小,初始化pTcpTable
        if (

            (dwRetVal = ::GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET6, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) == ERROR_INSUFFICIENT_BUFFER && !pUdpTable.reserve(ulSize))
        {
            return result;
        }

        // 第二次获取数据
        if ((dwRetVal = ::GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET6, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) == NO_ERROR)
        {

            chConnectNet connectNet;
            for (size_t i = 0; i < pUdpTable->dwNumEntries; i++)
            {
                // ::_MIB_UDPROW_OWNER_PID_::
                // dwLocalAddr：本地计算机上的 UDP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
                // dwLocalPort：本地计算机上的 UDP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                // dwOwningPid：发出此 UDP 连接的上下文绑定的进程 PID。
                connectNet.ip = L"0.0.0.0";
                connectNet.ipAddr = 0;
                connectNet.pid = 0;
                connectNet.port = 0;
                connectNet.type = 17;
                connectNet.typeName = L"UDP6";
                MIB_UDP6ROW_OWNER_PID mibUdprowOwnerPid = pUdpTable->table[i];

                connectNet.port = ::ntohs((u_short)mibUdprowOwnerPid.dwLocalPort);
                connectNet.pid = mibUdprowOwnerPid.dwOwningPid;
                connectNet.existsProcess = false;

                connectNet.ip = formatIP(mibUdprowOwnerPid.ucLocalAddr);

                if (connectNet.port != 0)
                    result.push_back(connectNet);
            }
        }
    }
    catch (...)
    {
    }

    return result;
}

std::vector<hmc_sock_util::chConnectNet> hmc_sock_util::CpEnumConnectNetConnectUDP4()
{
    std::vector<hmc_sock_util::chConnectNet> result;

    try
    {

        auto pUdpTable = VcRef<MIB_UDPTABLE_OWNER_PID>();

        ULONG ulSize = 0;
        DWORD dwRetVal = 0;

        // 第一次获取大小,初始化pTcpTable
        if (
            (dwRetVal = ::GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) == ERROR_INSUFFICIENT_BUFFER && !pUdpTable.reserve(ulSize))
        {
            return result;
        }

        // 第二次获取数据
        if ((dwRetVal = ::GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) == NO_ERROR)
        {

            chConnectNet connectNet;
            for (size_t i = 0; i < pUdpTable->dwNumEntries; i++)
            {
                // ::_MIB_UDPROW_OWNER_PID_::
                // dwLocalAddr：本地计算机上的 UDP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
                // dwLocalPort：本地计算机上的 UDP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                // dwOwningPid：发出此 UDP 连接的上下文绑定的进程 PID。
                connectNet.ip = L"0.0.0.0";
                connectNet.ipAddr = 0;
                connectNet.pid = 0;
                connectNet.port = 0;

                connectNet.type = 17;
                connectNet.typeName = L"UDP";
                MIB_UDPROW_OWNER_PID mibUdprowOwnerPid = pUdpTable->table[i];

                connectNet.port = ::ntohs((u_short)mibUdprowOwnerPid.dwLocalPort);
                connectNet.pid = mibUdprowOwnerPid.dwOwningPid;
                connectNet.existsProcess = false;

                connectNet.ipAddr = mibUdprowOwnerPid.dwLocalAddr;
                connectNet.ip = formatIP(mibUdprowOwnerPid.dwLocalAddr);
                if (connectNet.port != 0)
                    result.push_back(connectNet);
            }
        }
    }
    catch (...)
    {
    }

    return result;
}

hmc_sock_util::ConnectNetList hmc_sock_util::enumConnectNet(bool tcp, bool udp, bool tcp6, bool udp6)
{
    ConnectNetList result;

    if (tcp)
    {
        auto NetConnectTCP4List = CpEnumConnectNetConnectTCP4();
        size_t count = NetConnectTCP4List.size();

        for (size_t i = 0; i < count; i++)
        {
            auto& netConnect = NetConnectTCP4List.at(i);
            result.push_back(netConnect);
        }
    }

    if (tcp6)
    {
        auto NetConnectTCP6List = CpEnumConnectNetConnectTCP6();
        size_t count = NetConnectTCP6List.size();

        for (size_t i = 0; i < count; i++)
        {
            auto& netConnect = NetConnectTCP6List.at(i);
            result.push_back(netConnect);
        }
    }

    if (udp)
    {
        auto NetConnectUDP4List = CpEnumConnectNetConnectUDP4();
        size_t count = NetConnectUDP4List.size();

        for (size_t i = 0; i < count; i++)
        {
            auto& netConnect = NetConnectUDP4List.at(i);
            result.push_back(netConnect);
        }
    }

    if (udp6)
    {
        auto NetConnectUDP6List = CpEnumConnectNetConnectUDP6();
        size_t count = NetConnectUDP6List.size();

        for (size_t i = 0; i < count; i++)
        {
            auto& netConnect = NetConnectUDP6List.at(i);
            result.push_back(netConnect);
        }
    }

    // 判断进程有效性

    DWORD lp_cblength = 4096;
    std::vector<DWORD> processList = {};
    processList.resize(lp_cblength);

    // 最好使用大型数组，因为很难预测在调用 EnumProcesses 时将存在多少个进程。
    if (!::EnumProcesses(processList.data(), sizeof(DWORD) * lp_cblength, &lp_cblength))
    {
        processList.resize(0);
        return result;
    }

    processList.resize(lp_cblength / sizeof(DWORD));

    size_t count = result.size();
    for (size_t i = 0; i < count; i++)
    {
        auto& it = result.at(i);
        DWORD pid = 0;

        if (it.index() == 0)
        {
            auto value = &std::get<0>(it);
            pid = value->pid;
            value->existsProcess = false;
            for (size_t i = 0; i < count; i++)
            {
                auto at = processList.at(i);
                if (pid == at)
                {
                    value->existsProcess = true;
                }
            }

            continue;
        }

        if (it.index() == 1)
        {
            auto value = &std::get<1>(it);
            pid = value->pid;
            value->existsProcess = false;
            for (size_t i = 0; i < count; i++)
            {
                auto at = processList.at(i);
                if (pid == at)
                {
                    value->existsProcess = true;
                }
            }
        }
    }
    return result;
}

DWORD hmc_sock_util::getPortProcessTCP(DWORD port)
{
    DWORD result = 0;
    ULONG ulSize = sizeof(MIB_TCPTABLE2);

    auto pTcpTable = VcRef<MIB_TCPTABLE2>();

    if (!pTcpTable)
        return result;

    if (::GetTcpTable2(pTcpTable, &ulSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)
    {
        if (!pTcpTable.resize(ulSize))
            return result;
    }

    // 如果不够再增 够的话就跳过
    pTcpTable.reserve(ulSize);

    if (::GetTcpTable2(pTcpTable, &ulSize, TRUE) == NO_ERROR)
    {

        if (&pTcpTable == nullptr)
            return result;

        for (DWORD index = 0; index < pTcpTable->dwNumEntries; index++)
        {
            MIB_TCPROW2 mibTcprow2 = pTcpTable->table[index];
            // 得到端口号
            unsigned short localPort = ::ntohs((u_short)mibTcprow2.dwLocalPort);

            // 发现目标端口，返回pid
            if (port == localPort)
            {
                // 得到占用端口的进程pid
                result = mibTcprow2.dwOwningPid;

                return result;
            }
        }
    }
    return result;
}

DWORD hmc_sock_util::getPortProcessUDP(DWORD port)
{
    DWORD result = 0;

    auto pUdpTable = VcRef<MIB_UDPTABLE_OWNER_PID>();
    ULONG ulSize = 0;
    DWORD dwRetVal = 0;

    // 第一次获取大小,初始化pTcpTable
    if ((dwRetVal = ::GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) ==
        ERROR_INSUFFICIENT_BUFFER)
    {
        if (!pUdpTable.resize(ulSize))
        {
            return result;
        }
    }

    // 如果不够再增 够的话就跳过
    pUdpTable.reserve(ulSize);

    // 第二次获取数据
    if ((dwRetVal = ::GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) == NO_ERROR)
    {
        if (&pUdpTable == nullptr)
            return result;

        for (size_t i = 0; i < pUdpTable->dwNumEntries; i++)
        {
            MIB_UDPROW_OWNER_PID mibUdprowOwnerPid = pUdpTable->table[i];

            unsigned short localPort = ::ntohs((u_short)mibUdprowOwnerPid.dwLocalPort);
            if (localPort == port)
            {
                return mibUdprowOwnerPid.dwOwningPid;
            }
        }
    }

    return result;
}

std::vector<DWORD> hmc_sock_util::getPortProcessUDP6(DWORD port)
{
    std::vector<DWORD> result;
    std::set<DWORD> result_temp;

    auto pUdpTable = VcRef<MIB_UDP6TABLE_OWNER_PID>();
    ULONG ulSize = 0;
    DWORD dwRetVal = 0;

    // 第一次获取大小,初始化pTcpTable
    if ((dwRetVal = ::GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET6, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) ==
        ERROR_INSUFFICIENT_BUFFER)
    {
        if (!pUdpTable.resize(ulSize))
        {
            return result;
        }
    }

    // 如果不够再增 够的话就跳过
    pUdpTable.reserve(ulSize);

    // 第二次获取数据
    if ((dwRetVal = ::GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET6, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) == NO_ERROR)
    {
        if (&pUdpTable == NULL)
        {
            return result;
        }

        for (size_t i = 0; i < pUdpTable->dwNumEntries; i++)
        {

            MIB_UDP6ROW_OWNER_PID mibUdprowOwnerPid = pUdpTable->table[i];

            if (::ntohs((u_short)mibUdprowOwnerPid.dwLocalPort) == port)
            {
                result_temp.insert(mibUdprowOwnerPid.dwOwningPid);
            }
        }
    }

    for (auto&& it : result_temp)
        result.push_back(it);
    return result;
}

std::vector<DWORD> hmc_sock_util::getPortProcessTCP6(DWORD port)
{
    std::vector<DWORD> result;
    std::set<DWORD> result_temp;
    ULONG ulSize = sizeof(MIB_TCPTABLE2);

    auto pTcpTable = VcRef<MIB_TCP6TABLE2>();

    if (::GetTcp6Table2(pTcpTable, &ulSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)
    {
        if (!pTcpTable.resize(ulSize))
        {
            return result;
        }
    }

    // 如果不够再增 够的话就跳过
    pTcpTable.reserve(ulSize);

    if (::GetTcp6Table2(pTcpTable, &ulSize, TRUE) == NO_ERROR)
    {
        for (DWORD index = 0; index < pTcpTable->dwNumEntries; index++)
        {
            MIB_TCP6ROW2 mibTcprow2 = pTcpTable->table[index];
            if (::ntohs((u_short)mibTcprow2.dwLocalPort) == port)
            {
                result_temp.insert(mibTcprow2.dwOwningPid);
            }
        }
    }

    for (auto&& it : result_temp)
    {
        result.push_back(it);
    }

    return result;
}

std::wstring hmc_sock_util::getStateName(DWORD dwState)
{
    std::wstring state = std::wstring();
    switch (dwState)
    {
    case MIB_TCP_STATE_CLOSED:
        state.append(L"CLOSED");
        break;
    case MIB_TCP_STATE_LISTEN:
        state.append(L"LISTEN");
        break;
    case MIB_TCP_STATE_SYN_SENT:
        state.append(L"SYN-SENT");
        break;
    case MIB_TCP_STATE_SYN_RCVD:
        state.append(L"SYN-RECEIVED");
        break;
    case MIB_TCP_STATE_ESTAB:
        state.append(L"ESTABLISHED");
        break;
    case MIB_TCP_STATE_FIN_WAIT1:
        state.append(L"FIN-WAIT-1");
        break;
    case MIB_TCP_STATE_FIN_WAIT2:
        state.append(L"FIN-WAIT-2");
        break;
    case MIB_TCP_STATE_CLOSE_WAIT:
        state.append(L"CLOSE-WAIT");
        break;
    case MIB_TCP_STATE_CLOSING:
        state.append(L"CLOSING");
        break;
    case MIB_TCP_STATE_LAST_ACK:
        state.append(L"LAST-ACK");
        break;
    case MIB_TCP_STATE_TIME_WAIT:
        state.append(L"TIME-WAIT");
        break;
    case MIB_TCP_STATE_DELETE_TCB:
        state.append(L"DELETE-TCB");
        break;
    default:
        state = (L"UNKNOWN");
        break;
    }
    return state;
}

hmc_sock_util::chNetAdapterAddrList hmc_sock_util::CpUaToAddrItem(PIP_ADAPTER_UNICAST_ADDRESS ua)
{
    chNetAdapterAddrList result;

    int family = ua->Address.lpSockaddr->sa_family;

    result.typeName = family == AF_INET ? L"IPv4" : L"IPv6";
    result.type = family;

    char buf[BUFSIZ];
    ::memset(buf, 0, BUFSIZ);
    ::getnameinfo(ua->Address.lpSockaddr, ua->Address.iSockaddrLength, buf, sizeof(buf), NULL, 0, NI_NUMERICHOST);
    result.ipaddress = hmc_util::asciiConvers(buf);

    return result;
}

std::vector<hmc_sock_util::chNetAdapterAddrItem> hmc_sock_util::getAdapterIPList()
{
    std::vector<hmc_sock_util::chNetAdapterAddrItem> result;

    try
    {
        WSAData d;

        if (::WSAStartup(MAKEWORD(2, 2), &d) != 0)
        {
            return result;
        }

        DWORD rv = 0;
        DWORD size = 0;

        PIP_ADAPTER_ADDRESSES aa;
        PIP_ADAPTER_UNICAST_ADDRESS ua;

        auto adapter_addresses = VcRef<IP_ADAPTER_ADDRESSES>();

        rv = ::GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, NULL, &size);

        if (rv == ERROR_BUFFER_OVERFLOW && !adapter_addresses.reserve(size))
        {
            return result;
        }

        // 如果不够再增 够的话就跳过
        adapter_addresses.reserve(size);

        rv = ::GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, adapter_addresses, &size);
        if (rv != ERROR_SUCCESS)
        {

            return result;
        }

        for (aa = adapter_addresses; aa != NULL; aa = aa->Next)
        {
            chNetAdapterAddrItem addr_item;
            addr_item.name = aa->FriendlyName;
            addr_item.addr_item = {};

            for (ua = aa->FirstUnicastAddress; ua != NULL; ua = ua->Next)
            {
                addr_item.addr_item.push_back(CpUaToAddrItem(ua));
            }

            result.push_back(addr_item);
        }

        ::WSACleanup();
    }HMC_CATCH_ALL;

    return result;
}

hmc_sock_util::chNetParams hmc_sock_util::getNetParams()
{
    hmc_sock_util::chNetParams result = { "", "", {}, "", "", false, false, false };

    // api太古老了 虽然没测试出错误 但是还是不相信他安全
    try
    {
        ULONG ulOutBufLen = sizeof(FIXED_INFO);
        DWORD dwRetVal;
        IP_ADDR_STRING* pIPAddr;

        auto pFixedInfoRef = VcRef<FIXED_INFO>();

        if (::GetNetworkParams(nullptr, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
        {
            pFixedInfoRef.resize(ulOutBufLen);
        }

        // 如果不够再增 够的话就跳过
        pFixedInfoRef.reserve(pFixedInfoRef);

        if (dwRetVal = ::GetNetworkParams(pFixedInfoRef, &ulOutBufLen) == NO_ERROR)
        {

            result.hostName = pFixedInfoRef->HostName;
            result.domainName = pFixedInfoRef->DomainName;

            chNetDnsServers it = {
                pFixedInfoRef->DnsServerList.IpAddress.String,
                pFixedInfoRef->DnsServerList.IpMask.String,
                pFixedInfoRef->DnsServerList.Context };

            result.dnsServers.emplace_back(std::move(it));

            pIPAddr = pFixedInfoRef->DnsServerList.Next;

            while (pIPAddr)
            {

                it = {
                    pFixedInfoRef->DnsServerList.IpAddress.String,
                    pFixedInfoRef->DnsServerList.IpMask.String,
                    pFixedInfoRef->DnsServerList.Context };

                result.dnsServers.emplace_back(std::move(it));

                pIPAddr = pIPAddr->Next;
            }

            switch (pFixedInfoRef->NodeType)
            {
            case BROADCAST_NODETYPE:
                result.nodeType = "BROADCAST_NODETYPE";
                break;
            case PEER_TO_PEER_NODETYPE:
                result.nodeType = "PEER_TO_PEER_NODETYPE";
                break;
            case MIXED_NODETYPE:
                result.nodeType = "MIXED_NODETYPE";
                break;
            case HYBRID_NODETYPE:
                result.nodeType = "HYBRID_NODETYPE";
                break;
            default:
                result.nodeType = std::string("UNKNOWN:").append(std::to_string(pFixedInfoRef->NodeType));
                break;
            }

            result.domainName = pFixedInfoRef->ScopeId;
            result.enableArpProxy = pFixedInfoRef->EnableProxy ? true : false;
            result.enableRouting = pFixedInfoRef->EnableRouting ? true : false;
            result.enableDns = pFixedInfoRef->EnableDns ? true : false;
        }
    }
    catch (...)
    {
    }

    return result;
}

std::optional<std::wstring> hmc_sock_util::GetSystemProxyServer()
{
    std::optional<std::wstring> result;
    try
    {

        HKEY hKey;
        auto ret = ::RegOpenKeyExW(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Internet Settings)", 0, KEY_ALL_ACCESS, &hKey);
        if (hKey == NULL || ret != ERROR_SUCCESS)
        {
            return result;
        }

        HMC_FreeRegKeyAuto(hKey);

        DWORD values_count, max_value_name_len, max_value_len;
        ret = ::RegQueryInfoKeyW(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &values_count, &max_value_name_len, &max_value_len, NULL, NULL);
        if (ret != ERROR_SUCCESS)
        {
            return result;

        }

        std::vector<std::tuple<std::shared_ptr<wchar_t>, DWORD, std::shared_ptr<BYTE>>> values;

        for (DWORD i = 0; i < values_count; i++)
        {
            std::shared_ptr<wchar_t> value_name(new wchar_t[(size_t)((int64_t)max_value_name_len + 1)],
                std::default_delete<wchar_t[]>());

            DWORD value_name_len = max_value_name_len + 1;
            DWORD value_type = 0;
            DWORD value_len = 0;

            ::RegEnumValueW(hKey, i, value_name.get(), &value_name_len, NULL, &value_type, NULL, &value_len);

            std::shared_ptr<BYTE> value(new BYTE[value_len],
                std::default_delete<BYTE[]>());

            value_name_len = max_value_name_len + 1;
            ::RegEnumValueW(hKey, i, value_name.get(), &value_name_len, NULL, &value_type, value.get(), &value_len);
            values.push_back(std::make_tuple(value_name, value_type, value));
        }

        DWORD ProxyEnable = 0;
        for (auto x : values)
        {
            if (::wcscmp(std::get<0>(x).get(), L"ProxyEnable") == 0)
            {
                ProxyEnable = *(DWORD*)(std::get<2>(x).get());
            }
        }

        if (ProxyEnable)
        {
            for (auto x : values)
            {
                if (::wcscmp(std::get<0>(x).get(), L"ProxyServer") == 0)
                {
                    result = (wchar_t*)(std::get<2>(x).get());
                    return result;
                }
            }
        }

    }
    HMC_CATCH_ALL;
    return result;
}

bool hmc_sock_util::getSystemProxyServer(std::wstring& ProxyServerUrl) {
    std::optional<std::wstring> result = GetSystemProxyServer();
    if (result.has_value()) {
        ProxyServerUrl.append(result.value());
        return true;
    }
    return false;
}

bool hmc_sock_util::getSystemProxyPac(std::wstring& ProxyServerUrl) {
        
        ProxyServerUrl.clear();
        HKEY hKey;
        LPCWSTR pacKeyPath = L"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings";
        LPCWSTR pacValueName = L"AutoConfigURL";
    
        if (::RegOpenKeyExW(HKEY_CURRENT_USER, pacKeyPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
        {
            WCHAR pacURL[256] = { 0 };
            DWORD dataSize = sizeof(pacURL);
    
            HMC_FreeRegKeyAuto(hKey);
    
            if (::RegQueryValueExW(hKey, pacValueName, NULL, NULL, (LPBYTE)pacURL, &dataSize) == ERROR_SUCCESS)
            {
                if (pacURL[0] != '\0')
                {
                    ProxyServerUrl.append(std::wstring(pacURL));
                    return true;
                }
            }
        }
    
        return false;
}

std::vector<std::wstring> hmc_sock_util::getDomainAddress(std::wstring domainName)
{
    std::vector<std::wstring> result;

    try
    {
        WSADATA wsaData;
        if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            return result;
        }

        struct addrinfoW hints;
        struct addrinfoW* addrInfoResult;

        ::ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC; // 使用 IPv4 或 IPv6
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        if (::GetAddrInfoW(domainName.c_str(), NULL, &hints, &addrInfoResult) != 0)
        {
            ::WSACleanup();
            return result;
        }

        struct addrinfoW* ptr = nullptr;

        std::vector<wchar_t> ipBuffer = {};
        ipBuffer.reserve(NI_MAXHOST);
        ipBuffer.resize(NI_MAXHOST);

        for (ptr = addrInfoResult; ptr != nullptr; ptr = ptr->ai_next)
        {
            if (::GetNameInfoW(ptr->ai_addr, static_cast<socklen_t>(ptr->ai_addrlen), ipBuffer.data(), NI_MAXHOST, nullptr, 0, NI_NUMERICHOST) != 0)
            {
                continue;
            }

            std::wstring temp_buff = L"";

            size_t count = ipBuffer.size();

            for (size_t i = 0; i < count; i++)
            {
                auto it = &ipBuffer.at(i);
                if (it != reinterpret_cast<wchar_t*>(L'\0'))
                {
                    temp_buff.push_back(ipBuffer.at(i));
                    *it = L'\0';
                }
            }
            result.push_back(temp_buff);
        }

        ::FreeAddrInfoW(addrInfoResult);
        ::WSACleanup();

    } HMC_CATCH_ALL;
    return result;
}

std::wstring hmc_sock_util::getHostsPath()
{
    std::wstring result;
    result.reserve(MAX_PATH + 1);
    result.resize(MAX_PATH + 1);

    UINT len = ::GetSystemDirectoryW(&result[0], MAX_PATH);

    hmc_util::removeAllCharPtr(result, L'\0');

    if (len <= 0)
    {
        result.append(L"C:\\Windows\\system32\\drivers\\etc\\hosts");
        return result;
    }

    result.append(L"\\drivers\\etc\\hosts");
    return result;
}

std::wstring hmc_sock_util::chLocalVddrItemV4::to_json()
{
    std::wstring result = LR"({"broadcast":"{broadcast}","netmask":"{netmask}","ipaddress":"{ipaddress}"})";
    result.reserve(result.size() + MAX_PATH + broadcast.size() + netmask.size() + ipaddress.size());

    hmc_util::replace(result, L"{broadcast}", hmc_util::escapeJsonString(broadcast));
    hmc_util::replace(result, L"{netmask}", hmc_util::escapeJsonString(netmask));
    hmc_util::replace(result, L"{ipaddress}", hmc_util::escapeJsonString(ipaddress));

    return std::wstring(result.begin(), result.end());
}

std::string hmc_sock_util::chNetDnsServers::to_json()
{
    std::string result = R"({"IpAddress":"{IpAddress}","IpMask":"{IpMask}","context":{context}})";
    result.reserve(result.size() + MAX_PATH + IpAddress.size() + IpMask.size());

    hmc_util::replace(result, "{IpAddress}", hmc_util::escapeJsonString(IpAddress));
    hmc_util::replace(result, "{IpMask}", hmc_util::escapeJsonString(IpMask));
    hmc_util::replace(result, "{context}", std::to_string(Context));

    return std::string(result.begin(), result.end());
}

std::string hmc_sock_util::chNetParams::to_json()
{
    std::string result = R"({"hostName":"{hostName}","domainName":"{domainName}","dnsServers":[{dnsServers}],"nodeType":"{nodeType}","dhcpScopeName":"{dhcpScopeName}","enableRouting":{enableRouting},"enableArpProxy":{enableArpProxy},"enableDns":{enableDns}})";
    result.reserve(result.size() + MAX_PATH + 1024);

    hmc_util::replace(result, "{hostName}", hmc_util::escapeJsonString(hostName));
    hmc_util::replace(result, "{domainName}", hmc_util::escapeJsonString(domainName));
    hmc_util::replace(result, "{nodeType}", hmc_util::escapeJsonString(nodeType));
    hmc_util::replace(result, "{dhcpScopeName}", hmc_util::escapeJsonString(dhcpScopeName));
    hmc_util::replace(result, "{enableRouting}", (enableRouting ? "true" : "false"));
    hmc_util::replace(result, "{enableArpProxy}", (enableArpProxy ? "true" : "false"));
    hmc_util::replace(result, "{enableDns}", (enableDns ? "true" : "false"));

    std::string json_array = "";

    size_t count = dnsServers.size();

    for (size_t i = 0; i < count; i++)
    {
        auto it = &dnsServers.at(i);
        json_array.append(it->to_json());
        if (i + 1 < count)
        {
            json_array.push_back(',');
        }
    }

    hmc_util::replace(result, "{dnsServers}", json_array);

    return std::string(result.begin(), result.end());
}

std::wstring hmc_sock_util::chNetAdapterAddrList::to_json()
{
    std::wstring result = LR"({"ipaddress":"{ipaddress}","typeName":"{typeName}","type":{type}})";
    result.reserve(result.size() + MAX_PATH * 3);

    hmc_util::replace(result, L"{ipaddress}", hmc_util::escapeJsonString(ipaddress));
    hmc_util::replace(result, L"{typeName}", hmc_util::escapeJsonString(typeName));
    hmc_util::replace(result, L"{type}", std::to_wstring(type));

    return std::wstring(result.begin(), result.end());
}

std::wstring hmc_sock_util::chConnectNetTCP::to_json()
{
    std::wstring result = LR"({"typeName":"{typeName}","type":{type},"ipAddr":{ipAddr},"ip":"{ip}","port":{port},"pid":{pid},"existsProcess":{existsProcess},"remotePort":{remotePort},"remoteIPAddr":{remoteIPAddr},"state":"{state}","remoteIP":"{remoteIP}"})";
    result.reserve(result.size() + 1024);

    hmc_util::replace(result, L"{remoteIP}", hmc_util::escapeJsonString(remoteIP));
    hmc_util::replace(result, L"{state}", hmc_util::escapeJsonString(state));
    hmc_util::replace(result, L"{remotePort}", std::to_wstring(remotePort));
    hmc_util::replace(result, L"{remoteIPAddr}", std::to_wstring(remoteIPAddr));

    hmc_util::replace(result, L"{typeName}", hmc_util::escapeJsonString(typeName));
    hmc_util::replace(result, L"{type}", std::to_wstring(type));
    hmc_util::replace(result, L"{ipAddr}", std::to_wstring(ipAddr));
    hmc_util::replace(result, L"{ip}", hmc_util::escapeJsonString(ip));
    hmc_util::replace(result, L"{port}", std::to_wstring(port));
    hmc_util::replace(result, L"{pid}", std::to_wstring(pid));
    hmc_util::replace(result, L"{existsProcess}", (existsProcess ? L"true" : L"false"));

    return std::wstring(result.begin(), result.end());
}

std::wstring hmc_sock_util::chConnectNet::to_json()
{
    std::wstring result = LR"({"typeName":"{typeName}","type":{type},"ipAddr":{ipAddr},"ip":"{ip}","port":{port},"pid":{pid},"existsProcess":{existsProcess}})";

    result.reserve(result.size() + MAX_PATH * 3);

    hmc_util::replace(result, L"{typeName}", hmc_util::escapeJsonString(typeName));
    hmc_util::replace(result, L"{type}", std::to_wstring(type));
    hmc_util::replace(result, L"{ipAddr}", std::to_wstring(ipAddr));
    hmc_util::replace(result, L"{ip}", hmc_util::escapeJsonString(ip));
    hmc_util::replace(result, L"{port}", std::to_wstring(port));
    hmc_util::replace(result, L"{pid}", std::to_wstring(pid));
    hmc_util::replace(result, L"{existsProcess}", (existsProcess ? L"true" : L"false"));

    return std::wstring(result.begin(), result.end());
}

std::wstring hmc_sock_util::chNetAdapterAddrItem::to_json()
{
    std::wstring result = LR"({"name":"{name}","addr_item":[{addr_item}]})";
    result.reserve(result.size() + MAX_PATH * 3);

    hmc_util::replace(result, L"{name}", hmc_util::escapeJsonString(name));

    std::wstring json_array = L"";

    size_t count = addr_item.size();

    for (size_t i = 0; i < count; i++)
    {
        auto it = &addr_item.at(i);

        json_array.append(it->to_json());

        if (i + 1 < count)
        {
            json_array.push_back(L',');
        }
    }

    hmc_util::replace(result, L"{addr_item}", json_array);

    return std::wstring(result.begin(), result.end());
}
