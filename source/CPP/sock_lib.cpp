#pragma once
#include "./sock_lib.hpp"

/**
 * @brief 获取主机信息
 *
 * @return hmc_NetParams
 */
hmc_NetParams getNetParams()
{
    hmc_NetParams NetParams;
    NetParams.enableArpProxy = false;
    NetParams.enableDns = false;
    NetParams.dnsServers = {};
    NetParams.dhcpScopeName = "";
    NetParams.hostName = "";
    NetParams.nodeType = "";
    NetParams.enableRouting = false;

    try
    {
        FIXED_INFO *pFixedInfo;
        ULONG ulOutBufLen;
        DWORD dwRetVal;
        IP_ADDR_STRING *pIPAddr;

        pFixedInfo = (FIXED_INFO *)MALLOC(sizeof(FIXED_INFO));
        if (pFixedInfo == NULL)
        {
            return NetParams;
        }
        ulOutBufLen = sizeof(FIXED_INFO);

        if (GetNetworkParams(pFixedInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
        {
            FREE(pFixedInfo);
            pFixedInfo = (FIXED_INFO *)MALLOC(ulOutBufLen);
            if (pFixedInfo == NULL)
            {
                return NetParams;
            }
        }

        if (dwRetVal = GetNetworkParams(pFixedInfo, &ulOutBufLen) == NO_ERROR)
        {

            NetParams.hostName = pFixedInfo->HostName;
            NetParams.domainName = pFixedInfo->DomainName;

            NetParams.dnsServers.push_back(pFixedInfo->DnsServerList.IpAddress.String);

            pIPAddr = pFixedInfo->DnsServerList.Next;
            while (pIPAddr)
            {
                NetParams.dnsServers.push_back(pIPAddr->IpAddress.String);
                pIPAddr = pIPAddr->Next;
            }

            switch (pFixedInfo->NodeType)
            {
            case BROADCAST_NODETYPE:
                NetParams.nodeType = "BROADCAST_NODETYPE";
                break;
            case PEER_TO_PEER_NODETYPE:
                NetParams.nodeType = "PEER_TO_PEER_NODETYPE";
                break;
            case MIXED_NODETYPE:
                NetParams.nodeType = "MIXED_NODETYPE";
                break;
            case HYBRID_NODETYPE:
                NetParams.nodeType = "HYBRID_NODETYPE";
                break;
            default:
                NetParams.nodeType = string("UNKNOWN:").append(to_string(pFixedInfo->NodeType));
                break;
            }

            NetParams.domainName = pFixedInfo->ScopeId;
            NetParams.enableArpProxy = pFixedInfo->EnableProxy ? true : false;
            NetParams.enableRouting = pFixedInfo->EnableRouting ? true : false;
            NetParams.enableDns = pFixedInfo->EnableDns ? true : false;
        }
        else
        {
            return NetParams;
        }

        if (pFixedInfo)
            FREE(pFixedInfo);
    }
    catch (const std::exception &e)
    {
    }

    return NetParams;
}

/**
 * @brief 获取占用指定TCP端口的进程id
 *
 * @param port
 * @return DWORD
 */
DWORD GetTCPPortProcessID(unsigned short port)
{
    try
    {
        // hmc_EnableShutDownPriv();
        ULONG ulSize = sizeof(MIB_TCPTABLE2);
        PMIB_TCPTABLE2 pTcpTable = (PMIB_TCPTABLE2)MALLOC(ulSize);

        if (pTcpTable == nullptr)
            return 0;

        if (GetTcpTable2(pTcpTable, &ulSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)
        {
            FREE(pTcpTable);
            pTcpTable = (PMIB_TCPTABLE2)MALLOC(ulSize);
            if (pTcpTable == nullptr)
                return 0;
        }

        if (GetTcpTable2(pTcpTable, &ulSize, TRUE) == NO_ERROR)
        {
            // ::_pTcpTable_::
            // dwState：TCP 连接的状态，可以是 MIB_TCP_STATE 枚举中定义的值之一，如 CLOSED、LISTEN、ESTABLISHED 等。
            // dwLocalAddr：本地计算机上的 TCP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
            // dwLocalPort：本地计算机上的 TCP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
            // dwRemoteAddr：远程计算机上的 TCP 连接的 IPv4 地址。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此值没有意义。
            // dwRemotePort：远程计算机上的 TCP 连接的网络字节顺序中的远程端口号。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此成员没有意义。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
            // dwOwningPid：发出此 TCP 连接的上下文绑定的进程 PID。
            // dwOffloadState：此 TCP 连接的卸载状态。此参数可以是 TCP_CONNECTION_OFFLOAD_STATE 的枚举值之一，如 InHost、Offloading、Offloaded 等。

            for (int index = 0; index < pTcpTable->dwNumEntries; index++)
            {
                MIB_TCPROW2 mibTcprow2 = pTcpTable->table[index];
                // 得到端口号
                unsigned short localPort = ntohs((u_short)mibTcprow2.dwLocalPort);

                // 发现目标端口，返回pid
                if (port == localPort)
                {
                    // 得到占用端口的进程pid
                    DWORD ProcessID = mibTcprow2.dwOwningPid;

                    FREE(pTcpTable);
                    return ProcessID;
                }
            }
        }

        FREE(pTcpTable);
    }
    catch (const char *msg)
    {
        return 0;
    }

    return 0;
}

/**
 * @brief 获取占用指定UDP端口的进程id
 *
 * @param port
 * @return DWORD
 */
DWORD GetUDPPortProcessID(unsigned short port)
{
    try
    {
        // hmc_EnableShutDownPriv();
        MIB_UDPTABLE_OWNER_PID *pUdpTable = nullptr;
        ULONG ulSize = 0;
        DWORD dwRetVal = 0;

        // 第一次获取大小,初始化pTcpTable
        if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) ==
            ERROR_INSUFFICIENT_BUFFER)
        {
            pUdpTable = (MIB_UDPTABLE_OWNER_PID *)MALLOC(ulSize);
            if (pUdpTable == NULL)
                return 0;
        }

        // 第二次获取数据
        if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) == NO_ERROR)
        {
            if (pUdpTable == NULL)
                return 0;

            for (size_t i = 0; i < pUdpTable->dwNumEntries; i++)
            {
                // ::_MIB_UDPROW_OWNER_PID_::
                // dwLocalAddr：本地计算机上的 UDP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
                // dwLocalPort：本地计算机上的 UDP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                // dwOwningPid：发出此 UDP 连接的上下文绑定的进程 PID。

                MIB_UDPROW_OWNER_PID mibUdprowOwnerPid = pUdpTable->table[i];

                unsigned short localPort = ntohs((u_short)mibUdprowOwnerPid.dwLocalPort);
                if (localPort == port)
                {
                    return mibUdprowOwnerPid.dwOwningPid;
                }
            }
        }
        else
        {
            FREE(pUdpTable);
            return 0;
        }

        if (pUdpTable != NULL)
        {
            FREE(pUdpTable);
            pUdpTable = NULL;
        }
        return 0;
    }
    catch (const char *msg)
    {
        return 0;
    }

    return 0;
}

/**
 * @brief 获取占用指定UDP端口的进程id
 *
 * @param port
 * @return DWORD
 */
vector<DWORD> GetUDP6PortProcessID(unsigned short port)
{
    vector<DWORD> res;
    set<DWORD> resn;
    try
    {
        // hmc_EnableShutDownPriv();
        MIB_UDP6TABLE_OWNER_PID *pUdpTable = nullptr;
        ULONG ulSize = 0;
        DWORD dwRetVal = 0;

        // 第一次获取大小,初始化pTcpTable
        if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET6, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) ==
            ERROR_INSUFFICIENT_BUFFER)
        {
            pUdpTable = (MIB_UDP6TABLE_OWNER_PID *)MALLOC(ulSize);
            if (pUdpTable == NULL)
                return res;
        }

        // 第二次获取数据
        if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET6, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) == NO_ERROR)
        {
            if (pUdpTable == NULL)
                return res;

            for (size_t i = 0; i < pUdpTable->dwNumEntries; i++)
            {

                MIB_UDP6ROW_OWNER_PID mibUdprowOwnerPid = pUdpTable->table[i];
                if (ntohs((u_short)mibUdprowOwnerPid.dwLocalPort) == port)
                {
                    if (resn.find(mibUdprowOwnerPid.dwOwningPid) == resn.end())
                    {
                        resn.insert(mibUdprowOwnerPid.dwOwningPid);
                        res.push_back(mibUdprowOwnerPid.dwOwningPid);
                    }
                }
            }
        }
        else
        {
            FREE(pUdpTable);
            return res;
        }

        if (pUdpTable != NULL)
        {
            FREE(pUdpTable);
            pUdpTable = NULL;
        }
        return res;
    }
    catch (const char *msg)
    {
        return res;
    }

    return res;
}

/**
 * @brief 获取占用指定TCP端口的进程id
 *
 * @param port
 * @return DWORD
 */
vector<DWORD> GetTCP6PortProcessID(unsigned short port)
{
    vector<DWORD> res;
    set<DWORD> resn;
    try
    {
        ULONG ulSize = sizeof(MIB_TCPTABLE2);
        PMIB_TCP6TABLE2 pTcpTable = (PMIB_TCP6TABLE2)MALLOC(ulSize);

        if (pTcpTable != nullptr)
        {

            if (GetTcp6Table2(pTcpTable, &ulSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)
            {
                FREE(pTcpTable);
                pTcpTable = (PMIB_TCP6TABLE2)MALLOC(ulSize);
                if (pTcpTable == nullptr)
                    return res;
            }

            if (GetTcp6Table2(pTcpTable, &ulSize, TRUE) == NO_ERROR)
            {
                // ::_pTcpTable_::
                // dwState：TCP 连接的状态，可以是 MIB_TCP_STATE 枚举中定义的值之一，如 CLOSED、LISTEN、ESTABLISHED 等。
                // dwLocalAddr：本地计算机上的 TCP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
                // dwLocalPort：本地计算机上的 TCP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                // dwRemoteAddr：远程计算机上的 TCP 连接的 IPv4 地址。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此值没有意义。
                // dwRemotePort：远程计算机上的 TCP 连接的网络字节顺序中的远程端口号。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此成员没有意义。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                // dwOwningPid：发出此 TCP 连接的上下文绑定的进程 PID。
                // dwOffloadState：此 TCP 连接的卸载状态。此参数可以是 TCP_CONNECTION_OFFLOAD_STATE 的枚举值之一，如 InHost、Offloading、Offloaded 等。

                for (int index = 0; index < pTcpTable->dwNumEntries; index++)
                {
                    MIB_TCP6ROW2 mibTcprow2 = pTcpTable->table[index];
                    if (ntohs((u_short)mibTcprow2.dwLocalPort) == port)
                    {
                        if (resn.find(mibTcprow2.dwOwningPid) == resn.end())
                        {
                            resn.insert(mibTcprow2.dwOwningPid);
                            res.push_back(mibTcprow2.dwOwningPid);
                        }
                    }
                }
            }
        }
        FREE(pTcpTable);
    }
    catch (const char *msg)
    {
        return res;
    }

    return res;
}

/**
 * @brief 将状态码转为人可以读取的UDP
 *
 * @param dwState
 * @return string
 */
string GetStateName(DWORD dwState)
{
    string state = string();
    switch (dwState)
    {
    case MIB_TCP_STATE_CLOSED:
        state.append("CLOSED");
        break;
    case MIB_TCP_STATE_LISTEN:
        state.append("LISTEN");
        break;
    case MIB_TCP_STATE_SYN_SENT:
        state.append("SYN-SENT");
        break;
    case MIB_TCP_STATE_SYN_RCVD:
        state.append("SYN-RECEIVED");
        break;
    case MIB_TCP_STATE_ESTAB:
        state.append("ESTABLISHED");
        break;
    case MIB_TCP_STATE_FIN_WAIT1:
        state.append("FIN-WAIT-1");
        break;
    case MIB_TCP_STATE_FIN_WAIT2:
        state.append("FIN-WAIT-2");
        break;
    case MIB_TCP_STATE_CLOSE_WAIT:
        state.append("CLOSE-WAIT");
        break;
    case MIB_TCP_STATE_CLOSING:
        state.append("CLOSING");
        break;
    case MIB_TCP_STATE_LAST_ACK:
        state.append("LAST-ACK");
        break;
    case MIB_TCP_STATE_TIME_WAIT:
        state.append("TIME-WAIT");
        break;
    case MIB_TCP_STATE_DELETE_TCB:
        state.append("DELETE-TCB");
        break;
    default:
        state = ("UNKNOWN");
        break;
    }
    return state;
}

/**
 * @brief 枚举本机所有的已经打开的端口信息
 *
 * @param ConnectNetList
 * @param tcp 是否返回tcp
 * @param udp 是否返回udp
 */
void enumConnectNet(vector<ConnectNet> &ConnectNetList, bool tcp = true, bool udp = true, bool tcp6 = true, bool udp6 = true)
{
    // hmc_EnableShutDownPriv();

    if (tcp)
    {
        try
        {
            ULONG ulSize = sizeof(MIB_TCPTABLE2);
            PMIB_TCPTABLE2 pTcpTable = (PMIB_TCPTABLE2)MALLOC(ulSize);

            if (pTcpTable != nullptr)
            {

                if (GetTcpTable2(pTcpTable, &ulSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)
                {
                    FREE(pTcpTable);
                    pTcpTable = (PMIB_TCPTABLE2)MALLOC(ulSize);
                    if (pTcpTable == nullptr)
                        return;
                }

                if (GetTcpTable2(pTcpTable, &ulSize, TRUE) == NO_ERROR)
                {
                    // ::_pTcpTable_::
                    // dwState：TCP 连接的状态，可以是 MIB_TCP_STATE 枚举中定义的值之一，如 CLOSED、LISTEN、ESTABLISHED 等。
                    // dwLocalAddr：本地计算机上的 TCP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
                    // dwLocalPort：本地计算机上的 TCP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                    // dwRemoteAddr：远程计算机上的 TCP 连接的 IPv4 地址。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此值没有意义。
                    // dwRemotePort：远程计算机上的 TCP 连接的网络字节顺序中的远程端口号。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此成员没有意义。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                    // dwOwningPid：发出此 TCP 连接的上下文绑定的进程 PID。
                    // dwOffloadState：此 TCP 连接的卸载状态。此参数可以是 TCP_CONNECTION_OFFLOAD_STATE 的枚举值之一，如 InHost、Offloading、Offloaded 等。

                    ConnectNet connectNet;
                    for (int index = 0; index < pTcpTable->dwNumEntries; index++)
                    {
                        connectNet.ip = "0.0.0.0";
                        connectNet.ipAddr = 0;
                        connectNet.pid = 0;
                        connectNet.port = 0;
                        connectNet.remoteIP = "0.0.0.0";
                        connectNet.remoteIPAddr = 0;
                        connectNet.remotePort = 0;
                        connectNet.state = "UNKNOWN";
                        connectNet.type = 6;
                        connectNet.typeName = "TCP";

                        MIB_TCPROW2 mibTcprow2 = pTcpTable->table[index];

                        // IP解析
                        connectNet.ipAddr = mibTcprow2.dwLocalAddr;
                        connectNet.remoteIPAddr = mibTcprow2.dwRemoteAddr;
                        connectNet.ip = formatIP(mibTcprow2.dwLocalAddr);
                        connectNet.remoteIP = formatIP(mibTcprow2.dwRemoteAddr);

                        // 状态和进程
                        connectNet.state = GetStateName(mibTcprow2.dwState);
                        connectNet.pid = mibTcprow2.dwOwningPid;

                        // 端口
                        connectNet.port = ntohs((u_short)mibTcprow2.dwLocalPort);
                        connectNet.remotePort = ntohs((u_short)mibTcprow2.dwRemotePort);
                        if (connectNet.port != 0)
                            ConnectNetList.push_back(connectNet);
                    }
                }
            }
            FREE(pTcpTable);
        }
        catch (const char *msg)
        {
        }
    }

    if (tcp6)
    {
        try
        {
            ULONG ulSize = sizeof(MIB_TCPTABLE2);
            PMIB_TCP6TABLE2 pTcpTable = (PMIB_TCP6TABLE2)MALLOC(ulSize);

            if (pTcpTable != nullptr)
            {

                if (GetTcp6Table2(pTcpTable, &ulSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)
                {
                    FREE(pTcpTable);
                    pTcpTable = (PMIB_TCP6TABLE2)MALLOC(ulSize);
                    if (pTcpTable == nullptr)
                        return;
                }

                if (GetTcp6Table2(pTcpTable, &ulSize, TRUE) == NO_ERROR)
                {
                    // ::_pTcpTable_::
                    // dwState：TCP 连接的状态，可以是 MIB_TCP_STATE 枚举中定义的值之一，如 CLOSED、LISTEN、ESTABLISHED 等。
                    // dwLocalAddr：本地计算机上的 TCP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
                    // dwLocalPort：本地计算机上的 TCP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                    // dwRemoteAddr：远程计算机上的 TCP 连接的 IPv4 地址。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此值没有意义。
                    // dwRemotePort：远程计算机上的 TCP 连接的网络字节顺序中的远程端口号。当 dwState 成员为 MIB_TCP_STATE_LISTEN 时，此成员没有意义。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                    // dwOwningPid：发出此 TCP 连接的上下文绑定的进程 PID。
                    // dwOffloadState：此 TCP 连接的卸载状态。此参数可以是 TCP_CONNECTION_OFFLOAD_STATE 的枚举值之一，如 InHost、Offloading、Offloaded 等。

                    ConnectNet connectNet;
                    for (int index = 0; index < pTcpTable->dwNumEntries; index++)
                    {
                        connectNet.ip = "0.0.0.0";
                        connectNet.ipAddr = 0;
                        connectNet.pid = 0;
                        connectNet.port = 0;
                        connectNet.remoteIP = "0.0.0.0";
                        connectNet.remoteIPAddr = 0;
                        connectNet.remotePort = 0;
                        connectNet.state = "UNKNOWN";
                        connectNet.type = 6;
                        connectNet.typeName = "TCP6";

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
                        connectNet.state = GetStateName(mibTcprow2.State);
                        connectNet.pid = mibTcprow2.dwOwningPid;

                        // 端口
                        connectNet.port = ntohs((u_short)mibTcprow2.dwLocalPort);
                        connectNet.remotePort = ntohs((u_short)mibTcprow2.dwRemotePort);
                        if (connectNet.port != 0)
                            ConnectNetList.push_back(connectNet);
                    }
                }
            }
            FREE(pTcpTable);
        }
        catch (const char *msg)
        {
        }
    }

    if (udp)
    {
        try
        {
            // hmc_EnableShutDownPriv();
            MIB_UDPTABLE_OWNER_PID *pUdpTable = nullptr;
            ULONG ulSize = 0;
            DWORD dwRetVal = 0;

            // 第一次获取大小,初始化pTcpTable
            if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) ==
                ERROR_INSUFFICIENT_BUFFER)
            {
                pUdpTable = (MIB_UDPTABLE_OWNER_PID *)MALLOC(ulSize);
                if (pUdpTable == NULL)
                    return;
            }

            // 第二次获取数据
            if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) == NO_ERROR)
            {
                if (pUdpTable == NULL)
                    return;

                ConnectNet connectNet;
                for (size_t i = 0; i < pUdpTable->dwNumEntries; i++)
                {
                    // ::_MIB_UDPROW_OWNER_PID_::
                    // dwLocalAddr：本地计算机上的 UDP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
                    // dwLocalPort：本地计算机上的 UDP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                    // dwOwningPid：发出此 UDP 连接的上下文绑定的进程 PID。
                    connectNet.ip = "0.0.0.0";
                    connectNet.ipAddr = 0;
                    connectNet.pid = 0;
                    connectNet.port = 0;
                    connectNet.remoteIP = "0.0.0.0";
                    connectNet.remoteIPAddr = 0;
                    connectNet.remotePort = 0;
                    connectNet.state = "UNKNOWN";
                    connectNet.type = 17;
                    connectNet.typeName = "UDP";
                    MIB_UDPROW_OWNER_PID mibUdprowOwnerPid = pUdpTable->table[i];

                    connectNet.port = ntohs((u_short)mibUdprowOwnerPid.dwLocalPort);
                    connectNet.pid = mibUdprowOwnerPid.dwOwningPid;
                    connectNet.ipAddr = mibUdprowOwnerPid.dwLocalAddr;
                    connectNet.ip = formatIP(mibUdprowOwnerPid.dwLocalAddr);
                    if (connectNet.port != 0)
                        ConnectNetList.push_back(connectNet);
                }
            }
            else
            {
                FREE(pUdpTable);
                return;
            }

            if (pUdpTable != NULL)
            {
                FREE(pUdpTable);
                pUdpTable = NULL;
            }
            return;
        }
        catch (const char *msg)
        {
            return;
        }
    }

    if (udp6)
    {
        try
        {
            // hmc_EnableShutDownPriv();
            MIB_UDP6TABLE_OWNER_PID *pUdpTable = nullptr;
            ULONG ulSize = 0;
            DWORD dwRetVal = 0;

            // 第一次获取大小,初始化pTcpTable
            if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET6, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) ==
                ERROR_INSUFFICIENT_BUFFER)
            {
                pUdpTable = (MIB_UDP6TABLE_OWNER_PID *)MALLOC(ulSize);
                if (pUdpTable == NULL)
                    return;
            }

            // 第二次获取数据
            if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET6, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) == NO_ERROR)
            {
                if (pUdpTable == NULL)
                    return;

                ConnectNet connectNet;
                for (size_t i = 0; i < pUdpTable->dwNumEntries; i++)
                {
                    // ::_MIB_UDPROW_OWNER_PID_::
                    // dwLocalAddr：本地计算机上的 UDP 连接的本地 IPv4 地址。值为零表示侦听器可以接受任何接口上的连接。
                    // dwLocalPort：本地计算机上的 UDP 连接的本地端口号（以网络字节顺序排列）。IP 端口号的最大大小为 16 位，因此应仅使用较低的 16 位。
                    // dwOwningPid：发出此 UDP 连接的上下文绑定的进程 PID。
                    connectNet.ip = "0.0.0.0";
                    connectNet.ipAddr = 0;
                    connectNet.pid = 0;
                    connectNet.port = 0;
                    connectNet.remoteIP = "0.0.0.0";
                    connectNet.remoteIPAddr = 0;
                    connectNet.remotePort = 0;
                    connectNet.state = "UNKNOWN";
                    connectNet.type = 17;
                    connectNet.typeName = "UDP6";
                    MIB_UDP6ROW_OWNER_PID mibUdprowOwnerPid = pUdpTable->table[i];

                    connectNet.port = ntohs((u_short)mibUdprowOwnerPid.dwLocalPort);
                    connectNet.pid = mibUdprowOwnerPid.dwOwningPid;

                    /* char ipv6String[INET6_ADDRSTRLEN];
                     if (RtlIpv6AddressToStringA(reinterpret_cast<IN6_ADDR*>(&mibUdprowOwnerPid.ucLocalAddr), ipv6String) == NULL) {
                         continue ;
                     }
                     connectNet.ip = ipv6String;*/
                    connectNet.ip = formatIP(mibUdprowOwnerPid.ucLocalAddr);
                    // mibUdprowOwnerPid.dwLocalScopeId
                    // connectNet.ipAddr = mibUdprowOwnerPid.dwLocalAddr;
                    // connectNet.ip = formatIP(mibUdprowOwnerPid.dwLocalAddr);
                    if (connectNet.port != 0)
                        ConnectNetList.push_back(connectNet);
                }
            }
            else
            {
                FREE(pUdpTable);
                return;
            }

            if (pUdpTable != NULL)
            {
                FREE(pUdpTable);
                pUdpTable = NULL;
            }
            return;
        }
        catch (const char *msg)
        {
            return;
        }
    }
}

string formatIP(DWORD dwLocalAddr)
{
    size_t a = dwLocalAddr >> 24 & 0xFF;
    size_t b = dwLocalAddr >> 16 & 0xFF;
    size_t c = dwLocalAddr >> 8 & 0xFF;
    size_t d = dwLocalAddr & 0xFF;

    return string(to_string((long)d) + "." + to_string((long)c) + "." + to_string((long)b) + "." + to_string((long)a));
}

string formatIP(IN6_ADDR dwLocalAddr)
{
    char ipv6String[INET6_ADDRSTRLEN];
    if (RtlIpv6AddressToStringA(reinterpret_cast<IN6_ADDR *>(&dwLocalAddr), ipv6String) == NULL)
    {
        return "";
    }
    return string(ipv6String);
}

string formatIP(UCHAR ucLocalAddr[16])
{
    char ipv6String[INET6_ADDRSTRLEN];
    if (RtlIpv6AddressToStringA(reinterpret_cast<IN6_ADDR *>(ucLocalAddr), ipv6String) == NULL)
    {
        return "";
    }
    return string(ipv6String);
}

hmc_v4_addr_item get_v4_addr(MIB_IPADDRROW addr)
{
    char addr_str[BUFSIZ];
    char mask_str[BUFSIZ];

    DWORD broadcast;
    char broadcast_str[BUFSIZ];

    broadcast = (addr.dwAddr & addr.dwMask) | (addr.dwMask ^ (DWORD)0xffffffff);

    inet_ntop(AF_INET, (void *)&addr.dwAddr, addr_str, BUFSIZ);
    inet_ntop(AF_INET, (void *)&addr.dwMask, mask_str, BUFSIZ);
    inet_ntop(AF_INET, (void *)&broadcast, broadcast_str, BUFSIZ);

    hmc_v4_addr_item result;
    result.broadcast = string(broadcast_str);
    result.ipaddress = string(addr_str);
    result.netmask = string(mask_str);

    return result;
}

bool get_v4_ipaddress_list(vector<hmc_v4_addr_item> &addrList)
{
    WSAData d;
    if (WSAStartup(MAKEWORD(2, 2), &d) != 0)
    {
        return false;
    }

    DWORD rv, size;
    PMIB_IPADDRTABLE ipaddrtable;

    rv = GetIpAddrTable(NULL, &size, 0);
    if (rv != ERROR_INSUFFICIENT_BUFFER)
    {
        // fprintf(stderr, "GetIpAddrTable() failed...");
        return false;
    }
    ipaddrtable = (PMIB_IPADDRTABLE)malloc(size);

    rv = GetIpAddrTable(ipaddrtable, &size, 0);
    if (rv != NO_ERROR)
    {
        // fprintf(stderr, "GetIpAddrTable() failed...");
        free(ipaddrtable);
        return false;
    }

    for (DWORD i = 0; i < ipaddrtable->dwNumEntries; ++i)
    {
        addrList.push_back(
            get_v4_addr(ipaddrtable->table[i]));
    }

    free(ipaddrtable);

    WSACleanup();
    return true;
}

hmc_addr_item ua_to_hmc_addr_item(PIP_ADAPTER_UNICAST_ADDRESS ua)
{
    hmc_addr_item result;

    int family = ua->Address.lpSockaddr->sa_family;

    result.typeName = family == AF_INET ? L"IPv4" : L"IPv6";
    result.type = family;

    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    getnameinfo(ua->Address.lpSockaddr, ua->Address.iSockaddrLength, buf, sizeof(buf), NULL, 0, NI_NUMERICHOST);
    result.ipaddress = hmc_string_util::ansi_to_utf16(buf);

    return result;
}

bool get_net_ipaddress_list(vector<hmc_net_addr_item> &addrList)
{
    bool result = false;
    WSAData d;

    if (WSAStartup(MAKEWORD(2, 2), &d) != 0)
    {
        return result;
    }

    DWORD rv, size;
    PIP_ADAPTER_ADDRESSES adapter_addresses, aa;
    PIP_ADAPTER_UNICAST_ADDRESS ua;

    rv = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, NULL, &size);
    if (rv != ERROR_BUFFER_OVERFLOW)
    {
        return false;
    }
    adapter_addresses = (PIP_ADAPTER_ADDRESSES)malloc(size);

    rv = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, adapter_addresses, &size);
    if (rv != ERROR_SUCCESS)
    {
        free(adapter_addresses);
        return false;
    }

    for (aa = adapter_addresses; aa != NULL; aa = aa->Next)
    {
        hmc_net_addr_item addr_item;
        addr_item.name = aa->FriendlyName;
        addr_item.addr_item = {};

        for (ua = aa->FirstUnicastAddress; ua != NULL; ua = ua->Next)
        {
            addr_item.addr_item.push_back(ua_to_hmc_addr_item(ua));
        }

        addrList.push_back(addr_item);
    }

    free(adapter_addresses);

    WSACleanup();
    result = true;

    return result;
}

// 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
// 本文链接：https : // blog.csdn.net/u010745620/article/details/98471504

/**
 * @brief 获取系统代理链接
 *
 * @param system_proxy_server_url
 * @return true
 * @return false
 */
bool get_system_proxy_server(wstring &system_proxy_server_url)
{
    system_proxy_server_url.clear();

    HKEY key;
    auto ret = RegOpenKeyExW(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Internet Settings)", 0, KEY_ALL_ACCESS, &key);
    if (ret != ERROR_SUCCESS)
    {
        return false;
    }

    DWORD values_count, max_value_name_len, max_value_len;
    ret = RegQueryInfoKeyW(key, NULL, NULL, NULL, NULL, NULL, NULL,
                           &values_count, &max_value_name_len, &max_value_len, NULL, NULL);
    if (ret != ERROR_SUCCESS)
    {
        return false;
    }

    std::vector<std::tuple<std::shared_ptr<wchar_t>, DWORD, std::shared_ptr<BYTE>>> values;
    for (int i = 0; i < values_count; i++)
    {
        std::shared_ptr<wchar_t> value_name(new wchar_t[max_value_name_len + 1],
                                            std::default_delete<wchar_t[]>());
        DWORD value_name_len = max_value_name_len + 1;
        DWORD value_type, value_len;
        RegEnumValueW(key, i, value_name.get(), &value_name_len, NULL, &value_type, NULL, &value_len);
        std::shared_ptr<BYTE> value(new BYTE[value_len],
                                    std::default_delete<BYTE[]>());
        value_name_len = max_value_name_len + 1;
        RegEnumValueW(key, i, value_name.get(), &value_name_len, NULL, &value_type, value.get(), &value_len);
        values.push_back(std::make_tuple(value_name, value_type, value));
    }

    DWORD ProxyEnable = 0;
    for (auto x : values)
    {
        if (wcscmp(std::get<0>(x).get(), L"ProxyEnable") == 0)
        {
            ProxyEnable = *(DWORD *)(std::get<2>(x).get());
        }
    }

    if (ProxyEnable)
    {
        for (auto x : values)
        {
            if (wcscmp(std::get<0>(x).get(), L"ProxyServer") == 0)
            {
                system_proxy_server_url.append((wchar_t *)(std::get<2>(x).get()));
                return true;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

/**
 * @brief 获取系统代理pac脚本链接
 *
 * @param system_proxy_pac_url
 * @return true
 * @return false
 */
bool get_system_proxy_pac(wstring &system_proxy_pac_url)
{
    system_proxy_pac_url.clear();
    HKEY hKey;
    LPCWSTR pacKeyPath = L"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings";
    LPCWSTR pacValueName = L"AutoConfigURL";

    if (RegOpenKeyExW(HKEY_CURRENT_USER, pacKeyPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        WCHAR pacURL[256] = {0};
        DWORD dataSize = sizeof(pacURL);

        if (RegQueryValueExW(hKey, pacValueName, NULL, NULL, (LPBYTE)pacURL, &dataSize) == ERROR_SUCCESS)
        {
            if (pacURL[0] != '\0')
            {
                system_proxy_pac_url.append(pacURL);
                // std::wcout << "PAC URL: " << pacURL << std::endl;
            }
            else
            {
                // std::cout << "PAC proxy is not enabled." << std::endl;
                return false;
            }
        }
        else
        {
            // std::cerr << "Failed to query registry value." << std::endl;
            return false;
        }

        RegCloseKey(hKey);
    }
    else
    {
        // std::cerr << "Failed to open registry key." << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief 从默认dns(联网)解析域名主机ip
 *
 * @param domainName
 * @param hosts_ip_address
 * @return true
 * @return false
 */
bool getDomainIPaddress(wstring domainName, vector<wstring> &hosts_ip_address)
{
    hosts_ip_address.clear();
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return false;
    }

    struct addrinfoW hints;
    struct addrinfoW *result;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // 使用 IPv4 或 IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (GetAddrInfoW(domainName.c_str(), NULL, &hints, &result) != 0)
    {
        WSACleanup();
        return false;
    }

    struct addrinfoW *ptr = nullptr;
    wchar_t ipBuffer[NI_MAXHOST];
    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
    {
        if (GetNameInfoW(ptr->ai_addr, ptr->ai_addrlen, ipBuffer, sizeof(ipBuffer), nullptr, 0, NI_NUMERICHOST) != 0)
        {
            // std::cerr << "Failed to get name info" << std::endl;
            continue;
        }
        hosts_ip_address.push_back(ipBuffer);
        // std::cout << "IP address: " << ipBuffer << std::endl;
    }

    FreeAddrInfoW(result);
    WSACleanup();
    return true;
}

/**
 * @brief 获取hosts文件的路径
 *
 * @return wstring
 */
wstring getHostsPath()
{
    wchar_t systemDir[MAX_PATH];
    UINT len = GetSystemDirectoryW(systemDir, sizeof(systemDir));

    if (len != 0)
    {
        std::wstring hostFilePath = std::wstring(systemDir) + L"\\drivers\\etc\\hosts";
        return hostFilePath;
    }
    else
    {
        std::wstring hostFilePath = std::wstring(systemDir) + L"C:\\Windows\\system32\\drivers\\etc\\hosts";
        return hostFilePath;
    }
}

#ifndef FMT11_VERSION
// ? 不加这段编译会找不到链接库 应该是 template 是高cpp标准的 而extern 导不出 这个标准 napi的作用域真是搞的我头疼
// 能跑就不要动 。。
template <unsigned trail_args, typename Map, typename... Args>
static inline std::string fmt11hlp(const Map *ctx, const char *format, Args... args)
{
    std::stringstream out;
    if (format)
    {
        auto tpl = std::tuple_cat(std::tuple<Args...>{args...}, std::make_tuple(0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
        char raw[64], tag[32], fmt[32];
        unsigned fix, dig, counter = 0;
        while (*format)
        {
            if (*format++ != '{')
            {
                out << format[-1];
            }
            else
            {
                auto parse = [](char raw[64], char tag[32], char fmt[32], unsigned &fix, unsigned &dig, const char *in) -> int
                {
                    int lv = 0; // parses [{] { [tag][:][fmt] } [}] expressions; returns num of bytes parsed or 0 if error
                    char *o = raw, *m = tag, *g = 0;
                    while (*in && *in == '{')
                    {
                        *o++ = *in++, ++lv;
                        if ((o - raw) >= 63)
                            return 0;
                    }
                    while (*in && lv > 0)
                    {
                        /**/ if (*in < 32)
                            return 0;
                        else if (*in < '0' && !g)
                            return 0;
                        else if (*in == '}')
                            --lv, *o++ = *in++;
                        else if (*in == ':')
                            g = fmt, *o++ = *in++;
                        else
                            *(g ? g : m)++ = *o++ = *in++;
                        if (((o - raw) >= 63) || ((m - tag) >= 31) || (g && (g - fmt) >= 31))
                            return 0;
                    }
                    *o = *m = *(g ? g : fmt) = 0;
                    if (0 != lv)
                    {
                        return 0;
                    }
                    fix = dig = 0;
                    for (char *f = fmt; *f != 0; ++f)
                    {
                        char *input = f;
                        if (*input >= '0' && *input <= '9')
                        {
                            double dbl = atof(input);
                            fix = int(dbl), dig = int(dbl * 1000 - fix * 1000);
                            while (dig && !(dig % 10))
                                dig /= 10;
                            // printf("%s <> %d %d\n", input, fix, dig );
                            break;
                        }
                    }
                    return o - raw;
                };
                int read_bytes = parse(raw, tag, fmt, fix, dig, &format[-1]);
                if (!read_bytes)
                {
                    out << format[-1];
                }
                else
                {
                    // style
                    format += read_bytes - 1;
                    for (char *f = fmt; *f; ++f)
                        switch (*f)
                        {
                        default:
                            if (f[0] >= '0' && f[0] <= '9')
                            {
                                while ((f[0] >= '0' && f[0] <= '9') || f[0] == '.')
                                    ++f;
                                --f;
                                out << std::setw(fix);
                                out << std::fixed;
                                out << std::setprecision(dig);
                            }
                            else
                            {
                                out.fill(f[0]);
                            }
                            break;
                        case '#':
                            out << std::showbase;
                            break;
                        case 'b':
                            out << std::boolalpha;
                            break;
                        case 'D':
                            out << std::dec << std::uppercase;
                            break;
                        case 'd':
                            out << std::dec;
                            break;
                        case 'O':
                            out << std::oct << std::uppercase;
                            break;
                        case 'o':
                            out << std::oct;
                            break;
                        case 'X':
                            out << std::hex << std::uppercase;
                            break;
                        case 'x':
                            out << std::hex;
                            break;
                        case 'f':
                            out << std::fixed;
                            break;
                        case '<':
                            out << std::left;
                            break;
                        case '>':
                            out << std::right;
                        }
                    // value
                    char arg = tag[0];
                    if (!arg)
                    {
                        if (counter < (sizeof...(Args) - trail_args))
                        {
                            arg = '0' + counter++;
                        }
                        else
                        {
                            arg = '\0';
                        }
                        // printf("arg %d/%d\n", int(counter), (sizeof...(Args) - trail_args));
                    }
                    switch (arg)
                    {
                    default:
                        if (ctx)
                        {
                            auto find = ctx->find(tag);
                            if (find == ctx->end())
                                out << raw;
                            else
                                out << find->second;
                        }
                        else
                        {
                            out << raw;
                        }
                        break;
                    case 0:
                        out << raw;
                        break;
                    case '0':
                        out << std::get<0>(tpl);
                        break;
                    case '1':
                        out << std::get<1>(tpl);
                        break;
                    case '2':
                        out << std::get<2>(tpl);
                        break;
                    case '3':
                        out << std::get<3>(tpl);
                        break;
                    case '4':
                        out << std::get<4>(tpl);
                        break;
                    case '5':
                        out << std::get<5>(tpl);
                        break;
                    case '6':
                        out << std::get<6>(tpl);
                        break;
                    case '7':
                        out << std::get<7>(tpl);
                        break;
                    case '8':
                        out << std::get<8>(tpl);
                        break;
                    case '9':
                        out << std::get<9>(tpl);
                    }
                }
            }
        }
    }
    return out.str();
}

static inline std::string fmt11(const char *format)
{
    return fmt11hlp<1, std::map<std::string, std::string>>(nullptr, format, 0);
}

template <typename... Args>
static inline std::string fmt11(const char *format, Args... args)
{
    return fmt11hlp<0, std::map<std::string, std::string>>(nullptr, format, args...);
}

template <typename Map>
static inline std::string fmt11map(const Map &ctx, const char *format)
{
    return fmt11hlp<1>(&ctx, format, 0);
}

template <typename Map, typename... Args>
static inline std::string fmt11map(const Map &ctx, const char *format, Args... args)
{
    return fmt11hlp<0>(&ctx, format, args...);
}

#endif // FMT11_VERSION

// ------------------------------------------

// 序列化工具预设

string hmc_v4_addr_item::to_josn()
{
    string result = string("{");
    result.append("\"ipaddress\":\"").append(hmc_string_util::escapeJsonString(ipaddress)).append("\",");
    result.append("\"netmask\":\"").append(hmc_string_util::escapeJsonString(netmask)).append("\",");
    result.append("\"broadcast\":\"").append(hmc_string_util::escapeJsonString(broadcast)).append("\"");
    result.append("}");
    return result;
}

string ConnectNet::to_josn()

{

    string result = string("{");
    // string
    result.append(fmt11(R"( "typeName" : "{}" , )", hmc_string_util::escapeJsonString(typeName)));
    result.append(fmt11(R"( "remoteIP" : "{}" , )", hmc_string_util::escapeJsonString(remoteIP)));
    result.append(fmt11(R"( "state" : "{}" , )", hmc_string_util::escapeJsonString(state)));
    result.append(fmt11(R"( "ip" : "{}" , )", hmc_string_util::escapeJsonString(ip)));

    // num
    result.append(fmt11(R"( "type" : {} , )", type));
    result.append(fmt11(R"( "ipAddr" : {} , )", ipAddr));
    result.append(fmt11(R"( "port" : {} , )", port));
    result.append(fmt11(R"( "pid" : {} , )", pid));
    result.append(fmt11(R"( "remotePort" : {} , )", remotePort));
    result.append(fmt11(R"( "remoteIPAddr" : {} )", remoteIPAddr));

    result.append("}");
    return result;
}

string hmc_NetParams::to_josn()
{

    string result = string("{");
    // string
    result.append(hmc_string_util ::fmt11(R"( "hostName" : "{}" , )", hmc_string_util::escapeJsonString(hostName)));
    result.append(fmt11(R"( "domainName" : "{}" , )", hmc_string_util::escapeJsonString(domainName)));
    result.append(fmt11(R"( "nodeType" : "{}" , )", hmc_string_util::escapeJsonString(nodeType)));
    result.append(fmt11(R"( "dhcpScopeName" : "{}" , )", hmc_string_util::escapeJsonString(dhcpScopeName)));

    // array

    result.append(fmt11(R"( "dnsServers" : {} , )", hmc_string_util::vec2json(dnsServers)));

    // bool
    result.append(fmt11(R"( "enableDns" : {} , )", enableDns ? "true" : "false"));
    result.append(fmt11(R"( "enableRouting" : {} , )", enableRouting ? "true" : "false"));
    result.append(fmt11(R"( "enableArpProxy" : {} )", enableArpProxy ? "true" : "false"));

    result.append("}");
    return result;
}

wstring hmc_net_addr_item::to_josn()
{
    wstring result = wstring(L"{");
    result.append(LR"("name" : ")" + hmc_string_util::escapeJsonString(name) + L"\",");
    wstring addr_item_list_to_str = L"";

    for (size_t i = 0; i < addr_item.size(); i++)
    {
        auto addr_item_data = addr_item[i];
        addr_item_list_to_str.append(addr_item_data.to_josn());

        if (addr_item.size() - 1 > i)
        {
            addr_item_list_to_str.append(L",");
        }
    }

    result.append(LR"( "addr_item" : [)" + addr_item_list_to_str + L"]");

    result.append(L"}");
    return result;
}

wstring hmc_addr_item::to_josn()
{
    wstring result = wstring(L"{");
    result.append(L"\"ipaddress\":\"").append(hmc_string_util::escapeJsonString(ipaddress)).append(L"\",");
    result.append(L"\"typeName\":\"").append(typeName.c_str()).append(L"\",");
    result.append(L"\"type\":").append(to_wstring(type));
    result.append(L"}");
    return result;
}

extern string sock_lib_to_json(vector<ConnectNet> data)
{
    string result = string("");
    __HMC_STRUCT_TO_JSON_ARRAY(result, data);
    return result;
}

extern string sock_lib_to_json(ConnectNet data)
{
    return data.to_josn();
}

extern string sock_lib_to_json(hmc_NetParams data)
{
    return data.to_josn();
}

extern string sock_lib_to_json(hmc_v4_addr_item data)
{
    return data.to_josn();
}

extern string sock_lib_to_json(vector<hmc_v4_addr_item> data)
{
    string result = string("");
    __HMC_STRUCT_TO_JSON_ARRAY(result, data);
    return result;
}

extern wstring sock_lib_to_json(hmc_net_addr_item data)
{
    return data.to_josn();
}

extern wstring sock_lib_to_json(hmc_addr_item data)
{
    return data.to_josn();
}

extern wstring sock_lib_to_json(vector<hmc_net_addr_item> data_list)
{
    wstring result = wstring(L"");
    __HMC_STRUCT_TO_JSON_ARRAYW(result, data_list);

    return result;
}
