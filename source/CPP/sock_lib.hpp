#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_SOCK_LIB_SOCK_HPP
#define MODE_INTERNAL_INCLUDE_SOCK_LIB_SOCK_HPP

// WINSOCKAPI 会和winsock2.h 冲突 难以避免 索性提前禁用 WINSOCKAPI
// !  windows.h 会默认把<winsock.h> 放进来 如果在之前引用了需要把这句放进前面 但是 winsock.h 会和 winsock2.h 冲突导致无法使用ipv6
#define _WINSOCKAPI_

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <string>
#include <windows.h>
#include <vector>
#include <set>

#include <winsock2.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>
#include <ip2string.h>
#include <iphlpapi.h>
#include <node_api.h>

#include "./hmc_string_util.hpp"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Ntdll.lib")

using namespace std;

#define __HMC_CHECK_CATCH catch (char *err){};
#define __HMC_THREAD (code) std::thread([]() -> void { code }).detach();
#define __HMC_VirtualAlloc(Type, leng) (Type) VirtualAlloc((LPVOID)NULL, (DWORD)(leng), MEM_COMMIT, PAGE_READWRITE);
#define __HMC_VirtualFree(Virtua) \
    if (Virtua != NULL)           \
        VirtualFree(Virtua, 0, MEM_RELEASE);

#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))

#define __HMC_STRUCT_TO_JSON_ARRAY(str, data_list) \
    str.append("[");                               \
    for (auto item_data : data_list)               \
    {                                              \
        str.append(item_data.to_josn());           \
        str.append(",");                           \
    }                                              \
    if (!str.empty())                              \
    {                                              \
        str = hmc_string_util::trimAll(str, " ");  \
        str = hmc_string_util::trimAll(str, "\n"); \
        str = hmc_string_util::trimAll(str, ",");  \
    };                                             \
    str.append("]");

#define __HMC_STRUCT_TO_JSON_ARRAYW(str, data_list) \
    str.append(L"[");                               \
    for (size_t i = 0; i < data_list.size(); i++)   \
    {                                               \
        auto item_data = data_list[i];              \
        str.append(item_data.to_josn());            \
        if (data_list.size() - 1 > i)               \
        {                                           \
            str.append(L",");                       \
        }                                           \
    }                                               \
    str.append(L"]");

extern string formatIP(UCHAR ucLocalAddr[16]);
extern string formatIP(IN6_ADDR dwLocalAddr);
extern string formatIP(DWORD dwLocalAddr);

// 主机信息
struct hmc_v4_addr_item
{
    // 广播
    string broadcast;
    // 掩码
    string netmask;
    // ip
    string ipaddress;

    string to_josn();
};

struct hmc_addr_item
{
    // ip
    wstring ipaddress;
    // ip类型名称  ipv4 or ipv6
    wstring typeName;
    // ip类型 2(AF_INET) 23(AF_INET6)
    DWORD type = 0;

    wstring to_josn();
};

struct hmc_net_addr_item
{
    // 网络适配器名称
    wstring name;
    // ip 列表
    vector<hmc_addr_item> addr_item;
    wstring to_josn();
};

extern bool get_v4_ipaddress_list(vector<hmc_v4_addr_item> &addrList);

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
    string to_josn();
};

// 主机信息
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

    string to_josn();
};

extern hmc_NetParams getNetParams();

extern DWORD GetTCPPortProcessID(unsigned short port);
extern DWORD GetUDPPortProcessID(unsigned short port);
extern vector<DWORD> GetUDP6PortProcessID(unsigned short port);
extern vector<DWORD> GetTCP6PortProcessID(unsigned short port);

extern string GetStateName(DWORD dwState);
extern void enumConnectNet(vector<ConnectNet> &ConnectNetList, bool tcp, bool udp, bool tcp6, bool udp6);
extern bool get_system_proxy_server(wstring &system_proxy_server_url);
extern bool get_system_proxy_pac(wstring &system_proxy_pac_url);
extern bool getDomainIPaddress(wstring domainName, vector<wstring> &hosts_ip_address);
extern wstring getHostsPath();
extern string sock_lib_to_json(vector<ConnectNet> data);
extern string sock_lib_to_json(ConnectNet data);
extern wstring sock_lib_to_json(hmc_net_addr_item data);
extern string sock_lib_to_json(hmc_NetParams data);
extern wstring sock_lib_to_json(hmc_addr_item data);
extern string sock_lib_to_json(hmc_v4_addr_item data);
extern string sock_lib_to_json(vector<hmc_v4_addr_item> data);
extern wstring sock_lib_to_json(vector<hmc_net_addr_item> data);

extern bool get_net_ipaddress_list(vector<hmc_net_addr_item> &addrList);

#endif // MODE_INTERNAL_INCLUDE_SOCK_LIB_SOCK_HPP