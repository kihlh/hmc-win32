#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <string>
#include <ws2tcpip.h>
#include <Windows.h>
#include <winsock2.h>
#include <psapi.h>
#include <iphlpapi.h>
#include <ip2string.h>
#include <Mstcpip.h>
#include <vector>
#include <set>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Ntdll.lib")

using namespace std;

#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))

struct hmc_NetParams
{
    string hostName;           // 主机名称
    string domainName;         // 域名名称
    vector<string> dnsServers; // dns服务器列表
    /**
     * @brief 节点类型
     * - BROADCAST_NODETYPE;
     * - HYBRID_NODETYPE
     * - MIXED_NODETYPE
     * - PEER_TO_PEER_NODETYPE
     * - UNKNOWN:<UINT>
     */
    string nodeType;
    string dhcpScopeName; // dhcp 范围名称
    bool enableRouting;   // 是否启用路由选择
    bool enableArpProxy;  // 是否ARP代理
    bool enableDns;       // 是否启用dns
};

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
        FIXED_INFO* pFixedInfo;
        ULONG ulOutBufLen;
        DWORD dwRetVal;
        IP_ADDR_STRING* pIPAddr;

        pFixedInfo = (FIXED_INFO*)MALLOC(sizeof(FIXED_INFO));
        if (pFixedInfo == NULL)
        {
            return NetParams;
        }
        ulOutBufLen = sizeof(FIXED_INFO);

        if (GetNetworkParams(pFixedInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
        {
            FREE(pFixedInfo);
            pFixedInfo = (FIXED_INFO*)MALLOC(ulOutBufLen);
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
    catch (const std::exception& e)
    {
    }

    return NetParams;
}

/**
 * @brief 临时提权令牌
 *
 * @return BOOL
 */
BOOL hmc_EnableShutDownPriv()
{
    HANDLE Handle_Token = NULL;
    TOKEN_PRIVILEGES PermissionAttribute = { 0 };
    // 打开当前程序的权限令牌
    bool is_Open_Process_Token = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &Handle_Token);
    if (!is_Open_Process_Token)
    {
        return FALSE;
    }
    // 获得某一特定权限的权限标识LUID 保存到权限属性中
    if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &PermissionAttribute.Privileges[0].Luid))
    {
        CloseHandle(Handle_Token);
        return FALSE;
    }
    PermissionAttribute.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    PermissionAttribute.PrivilegeCount = 1;
    // 提升到系统权限
    if (!AdjustTokenPrivileges(Handle_Token, FALSE, &PermissionAttribute, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
    {
        CloseHandle(Handle_Token);
        return FALSE;
    }
    return TRUE;
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
        hmc_EnableShutDownPriv();
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
    catch (const char* msg)
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
        hmc_EnableShutDownPriv();
        MIB_UDPTABLE_OWNER_PID* pUdpTable = nullptr;
        ULONG ulSize = 0;
        DWORD dwRetVal = 0;

        // 第一次获取大小,初始化pTcpTable
        if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) ==
            ERROR_INSUFFICIENT_BUFFER)
        {
            pUdpTable = (MIB_UDPTABLE_OWNER_PID*)MALLOC(ulSize);
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
    catch (const char* msg)
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
        hmc_EnableShutDownPriv();
        MIB_UDP6TABLE_OWNER_PID* pUdpTable = nullptr;
        ULONG ulSize = 0;
        DWORD dwRetVal = 0;

        // 第一次获取大小,初始化pTcpTable
        if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET6, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) ==
            ERROR_INSUFFICIENT_BUFFER)
        {
            pUdpTable = (MIB_UDP6TABLE_OWNER_PID*)MALLOC(ulSize);
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
    catch (const char* msg)
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
    catch (const char* msg)
    {
        return res;
    }

    return res;
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
    if (RtlIpv6AddressToStringA(reinterpret_cast<IN6_ADDR*>(&dwLocalAddr), ipv6String) == NULL)
    {
        return "";
    }
    return string(ipv6String);
}
string formatIP(UCHAR ucLocalAddr[16])
{
    char ipv6String[INET6_ADDRSTRLEN];
    if (RtlIpv6AddressToStringA(reinterpret_cast<IN6_ADDR*>(ucLocalAddr), ipv6String) == NULL)
    {
        return "";
    }
    return string(ipv6String);
}
// https://en.wikipedia.org/wiki/Transmission_Control_Protocol
// https://learn.microsoft.com/zh-cn/windows/win32/api/iphlpapi/nf-iphlpapi-gettcp6table
struct ConnectNet
{
    string typeName; // "UDP" / "TCP" / "TCP6" / "UDP6"
    DWORD type = 0;  // 6 tcp / tcp6   17 udp / udp6
    DWORD ipAddr;    // dwLocalAddr
    string ip;       // 解析出来的实际ip
    DWORD port;      // 占用的端口
    DWORD pid;       // 占用此端口的进程
    // 以下参数仅支持TCP
    DWORD remotePort;   // 远程的端口
    DWORD remoteIPAddr; // 远程的ip (LocalAddr)
    string remoteIP;    // 解析出来的实际远程ip
    string state;       // 状态码 "CLOSED"|"LISTEN"|"SYN-SENT"|"SYN-RECEIVED"|"ESTABLISHED"|"FIN-WAIT-1"|"FIN-WAIT-2"|"CLOSE-WAIT"|"CLOSING"|"LAST-ACK"|"TIME-WAIT"|"DELETE-TCB"|"UNKNOWN"
};

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
void enumConnectNet(vector<ConnectNet>& ConnectNetList, bool tcp = true, bool udp = true, bool tcp6 = true, bool udp6 = true)
{
    hmc_EnableShutDownPriv();

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
        catch (const char* msg)
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
        catch (const char* msg)
        {
        }
    }

    if (udp)
    {
        try
        {
            hmc_EnableShutDownPriv();
            MIB_UDPTABLE_OWNER_PID* pUdpTable = nullptr;
            ULONG ulSize = 0;
            DWORD dwRetVal = 0;

            // 第一次获取大小,初始化pTcpTable
            if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) ==
                ERROR_INSUFFICIENT_BUFFER)
            {
                pUdpTable = (MIB_UDPTABLE_OWNER_PID*)MALLOC(ulSize);
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
        catch (const char* msg)
        {
            return;
        }
    }

    if (udp6)
    {
        try
        {
            hmc_EnableShutDownPriv();
            MIB_UDP6TABLE_OWNER_PID* pUdpTable = nullptr;
            ULONG ulSize = 0;
            DWORD dwRetVal = 0;

            // 第一次获取大小,初始化pTcpTable
            if ((dwRetVal = GetExtendedUdpTable(pUdpTable, &ulSize, TRUE, AF_INET6, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0)) ==
                ERROR_INSUFFICIENT_BUFFER)
            {
                pUdpTable = (MIB_UDP6TABLE_OWNER_PID*)MALLOC(ulSize);
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
        catch (const char* msg)
        {
            return;
        }
    }
}

int __cdecl main()
{
    std::cout << "getNetParams:" << endl;

    hmc_NetParams netParams = getNetParams();
    std::cout << "hostName :  " << netParams.hostName << std::endl;
    std::cout << "domainName :  " << netParams.domainName << std::endl;

    std::cout << "dnsServers :  " << netParams.dnsServers.size() << std::endl;
    std::cout << "nodeType :  " << netParams.nodeType << std::endl;
    std::cout << "dhcpScopeName :  " << netParams.dhcpScopeName << std::endl;
    std::cout << "enableArpProxy :  " << netParams.enableArpProxy << std::endl;
    std::cout << "enableDns :  " << netParams.enableDns << std::endl;
    std::cout << "enableRouting :  " << netParams.enableRouting << std::endl;
    std::cout << "-----------------------------------------------------" << endl;

    std::cout << "Port:" << endl;

    std::cout << "TCP[445]  ProcessID :  " << GetTCPPortProcessID(445) << std::endl;
    std::cout << "UDP[123]  ProcessID :  " << GetUDPPortProcessID(123) << std::endl;

    vector<ConnectNet> ConnectNetList;
    enumConnectNet(ConnectNetList, true /*tcp*/, true /*udp*/);
    std::cout << "enumConnectNet:" << endl;

    std::cout << "ConnectNetSize :  " << ConnectNetList.size() << endl;
    for (size_t i = 0; i < ConnectNetList.size(); i++)
    {
        ConnectNet connectNet = ConnectNetList[i];

        std::cout << "------------" << endl;

        std::cout << "ip :  " << connectNet.ip << std::endl;
        std::cout << "ipAddr :  " << connectNet.ipAddr << std::endl;
        std::cout << "pid :  " << connectNet.pid << std::endl;
        std::cout << "port :  " << connectNet.port << std::endl;
        std::cout << "remoteIP :  " << connectNet.remoteIP << std::endl;
        std::cout << "remoteIPAddr :  " << connectNet.remoteIPAddr << std::endl;
        std::cout << "remotePort :  " << connectNet.remotePort << std::endl;
        std::cout << "state :  " << connectNet.state << std::endl;
        std::cout << "type :  " << connectNet.type << std::endl;
        std::cout << "http :  "
            << "http://" << connectNet.ip << ":" << connectNet.port << std::endl;

        std::cout << "------------" << endl;
    }

    system("pause");

    return 0;
}