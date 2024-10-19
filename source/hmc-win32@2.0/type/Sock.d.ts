/// <reference types="node" />
import { HMC2_MODE } from "./index";
export declare enum HMC_SOKE_PROMISEEVAL_TASK_TYPE {
    /** 获取本机局域网的ip(v4)*/
    ipv4 = 1,
    /** 获取本机局域网的ip(v4)*/
    getIpaddressList = 1,
    /**获取本机局域网的ip(适配器,v4,v6)*/
    ip = 2,
    /**获取本机局域网的ip(适配器,v4,v6)*/
    getAdapterIP2 = 3,
    /** 获取主机网络信息*/
    getNetParams2 = 8,
    /** 获取系统代理链接（仅在启用系统代理时）*/
    getSystemProxyServer2 = 14,
    /** 获取系统代理pac脚本链接*/
    getSystemProxyPac2 = 15,
    /** 从默认dns(联网)解析域名主机ip*/
    getDomainIPaddress2 = 17,
    /** 获取hosts文件的路径*/
    getHostsPath2 = 18,
    /** 获取此端口被哪个进程占用了*/
    getTCPv6PortProcessID2 = 19,
    /** 获取此端口被哪个进程占用了*/
    getUDPv6PortProcessID2 = 25,
    /** 获取此端口被哪个进程占用了*/
    getUDPv4PortProcessID2 = 26,
    /** 获取此端口被哪个进程占用了*/
    getTCPv4PortProcessID2 = 27,
    /** 枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息*/
    getConnectNetList2 = 29,
    /** 判断当前软件是否拥有管理员权限*/
    isAdmin2 = 32,
    getMacAddresses2 = 33,
    isSystemFor64bit2 = 35
}
export type HMC_SOKE_PROMISEEVAL_TASK_TYPE_ALL_NAME = keyof typeof HMC_SOKE_PROMISEEVAL_TASK_TYPE;
declare class HMC_PromiseeEvalTask {
    async: Partial<Record<HMC_SOKE_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => Promise<any>>>;
    sync: Partial<Record<HMC_SOKE_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => any>>;
    constructor();
}
interface HMC_PromiseeEvalTask {
    /** 获取本机局域网的ip(v4)*/
    ipv4(): Promise<Array<HMC2_MODE.ipv4Item>>;
    /** 获取本机局域网的ip(v4)*/
    getIpaddressList(): Promise<Array<HMC2_MODE.ipv4Item>>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    ip(): Promise<Array<HMC2_MODE.hmc_net_addr_item>>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    getAdapterIP2(): Promise<Array<HMC2_MODE.hmc_net_addr_item>>;
    /** 获取主机网络信息*/
    getNetParams2(): Promise<HMC2_MODE.hmc_NetParams | null>;
    /** 获取系统代理链接（仅在启用系统代理时）*/
    getSystemProxyServer2(): Promise<string | null>;
    /** 获取系统代理pac脚本链接*/
    getSystemProxyPac2(): Promise<string | null>;
    /** 从默认dns(联网)解析域名主机ip*/
    getDomainIPaddress2(url: string): Promise<Array<string>>;
    /** 获取hosts文件的路径*/
    getHostsPath2(): Promise<string>;
    /** 获取此端口被哪个进程占用了*/
    getTCPv6PortProcessID2(port: number): Promise<number[]>;
    /** 获取此端口被哪个进程占用了*/
    getUDPv6PortProcessID2(port: number): Promise<number[]>;
    /** 获取此端口被哪个进程占用了*/
    getUDPv4PortProcessID2(port: number): Promise<number | null>;
    /** 获取此端口被哪个进程占用了*/
    getTCPv4PortProcessID2(port: number): Promise<number | null>;
    /**
     * 枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息
     * @param tcp 枚举 TCP (v4)端口
     * @param udp 枚举 UDP (v4)端口
     * @param tcp6 枚举 TCP (v6)端口
     * @param udp6 枚举 UDP (v6)端口
     */
    getConnectNetList2(tcp: boolean, udp: boolean, tcp6: boolean, udp6: boolean): Promise<Array<HMC2_MODE.ConnectNet | HMC2_MODE.ConnectNet>>;
    /** 判断当前软件是否拥有管理员权限*/
    isAdmin2(): Promise<boolean>;
    /** 获取本机局域网的ip(v4)*/
    ipv4Sync(): Array<HMC2_MODE.ipv4Item>;
    /** 获取本机局域网的ip(v4)*/
    getIpaddressListSync(): Array<HMC2_MODE.ipv4Item>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    ipSync(): Array<HMC2_MODE.hmc_net_addr_item>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    getAdapterIP2Sync(): Array<HMC2_MODE.hmc_net_addr_item>;
    /** 获取主机网络信息*/
    getNetParams2Sync(): HMC2_MODE.hmc_NetParams | null;
    /** 获取系统代理链接（仅在启用系统代理时）*/
    getSystemProxyServer2Sync(): string | null;
    /** 获取系统代理pac脚本链接*/
    getSystemProxyPac2Sync(): string | null;
    /** 从默认dns(联网)解析域名主机ip*/
    getDomainIPaddress2Sync(url: string): Array<string>;
    /** 获取hosts文件的路径*/
    getHostsPath2Sync(): string;
    /** 获取此端口被哪个进程占用了*/
    getTCPv6PortProcessID2Sync(port: number): number[];
    /** 获取此端口被哪个进程占用了*/
    getUDPv6PortProcessID2Sync(port: number): number[];
    /** 获取此端口被哪个进程占用了*/
    getUDPv4PortProcessID2Sync(port: number): number | null;
    /** 获取此端口被哪个进程占用了*/
    getTCPv4PortProcessID2Sync(port: number): number | null;
    /**
     * 枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息
     * @param tcp 枚举 TCP (v4)端口
     * @param udp 枚举 UDP (v4)端口
     * @param tcp6 枚举 TCP (v6)端口
     * @param udp6 枚举 UDP (v6)端口
     */
    getConnectNetList2Sync(tcp: boolean, udp: boolean, tcp6: boolean, udp6: boolean): Array<HMC2_MODE.ConnectNet | HMC2_MODE.ConnectNet>;
    /** 判断当前软件是否拥有管理员权限*/
    isAdmin2Sync(): boolean;
    /**
     * 获取mac地址列表
     * @example 第一个是主网卡 地址
     */
    getMacAddresses2(): Promise<string[]>;
    /**
     * 获取mac地址列表
     * @example 第一个是主网卡 地址
     */
    getMacAddresses2Sync(): string[];
    /**
     * 判断系统是否是64位系统
     */
    isSystemFor64bit2(): Promise<boolean>;
    /**
     * 判断系统是否是64位系统
     */
    isSystemFor64bit2Sync(): boolean;
}
export declare namespace Network {
    const HMC_GetSokeEnvInfo: HMC_PromiseeEvalTask;
    function https_get_data(url: string): Promise<Buffer>;
    /**
     * 获取公网ip
     * @returns
     */
    function public_ip(): Promise<string>;
    /**
     * 获取一个tcp空闲端口 (服务)
     * @returns
     */
    function freePort(): Promise<number>;
    /**
     * 获取一个tcp空闲端口 (服务)
     * @returns
     */
    function freePortTCP(): Promise<number>;
    /**
     * 获取一个UDP空闲端口
     * @returns
     */
    function freePortUDP(): Promise<number>;
    /**
     * 判断TCP(服务)端口号正在使用/系统占用
     * @param port TCP端口
     * @returns
     */
    function hasPortTCP(port: number): Promise<boolean>;
    function hasPortTCP(port: number, callBack: (hasPort: boolean) => unknown): void;
    /**
     * 判断UDP端口号正在使用/系统占用
     * @param port TCP端口
     * @returns
     */
    function hasPortUDP(port: number): Promise<boolean>;
    function hasPortUDP(port: number, callBack: (hasPort: boolean) => unknown): void;
    const 
    /**判断当前软件是否拥有管理员权限 */
    isAdmin2: () => Promise<boolean>, 
    /**判断当前软件是否拥有管理员权限 */
    isAdmin2Sync: () => boolean, 
    /**获取mac地址列表 */
    getMacAddresses2: () => Promise<string[]>, 
    /**获取mac地址列表 */
    getMacAddresses2Sync: () => string[], 
    /**获取hosts文件的路径 */
    getHostsPath2Sync: () => string, 
    /**获取hosts文件的路径 */
    getHostsPath2: () => Promise<string>, 
    /**获取hosts文件的路径 */
    getSystemProxyPac2: () => Promise<string | null>, 
    /**获取hosts文件的路径 */
    getSystemProxyPac2Sync: () => string | null, 
    /**获取系统代理链接（仅在启用系统代理时） */
    getSystemProxyServer2: () => Promise<string | null>, 
    /**获取系统代理链接（仅在启用系统代理时） */
    getSystemProxyServer2Sync: () => string | null, 
    /**判断系统是否是64位系统 */
    isSystemFor64bit2: () => Promise<boolean>, 
    /**判断系统是否是64位系统 */
    isSystemFor64bit2Sync: () => boolean;
    /** 获取本机局域网的ip(v4)*/
    function ipv4(): Promise<Array<HMC2_MODE.ipv4Item>>;
    /** 获取本机局域网的ip(v4)*/
    function getIpaddressList(): Promise<Array<HMC2_MODE.ipv4Item>>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    function ip(): Promise<Array<HMC2_MODE.hmc_net_addr_item>>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    function getAdapterIP2(): Promise<Array<HMC2_MODE.hmc_net_addr_item>>;
    /** 获取主机网络信息*/
    function getNetParams2(): Promise<HMC2_MODE.hmc_NetParams | null>;
    /** 从默认dns(联网)解析域名主机ip*/
    function getDomainIPaddress2(url: string): Promise<Array<string>>;
    /** 获取此端口被哪个进程占用了*/
    function getTCPv6PortProcessID2(port: number): Promise<number[]>;
    /** 获取此端口被哪个进程占用了*/
    function getUDPv6PortProcessID2(port: number): Promise<number[]>;
    /** 获取此端口被哪个进程占用了*/
    function getUDPv4PortProcessID2(port: number): Promise<number | null>;
    /** 获取此端口被哪个进程占用了*/
    function getTCPv4PortProcessID2(port: number): Promise<number | null>;
    /**
     * 枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息
     * @param tcp 枚举 TCP (v4)端口
     * @param udp 枚举 UDP (v4)端口
     * @param tcp6 枚举 TCP (v6)端口
     * @param udp6 枚举 UDP (v6)端口
     */
    function getConnectNetList2(tcp?: boolean, udp?: boolean, tcp6?: boolean, udp6?: boolean): Promise<Array<HMC2_MODE.ConnectNet | HMC2_MODE.ConnectNet>>;
    /** 获取本机局域网的ip(v4)*/
    function ipv4Sync(): Array<HMC2_MODE.ipv4Item>;
    /** 获取本机局域网的ip(v4)*/
    function getIpaddressListSync(): Array<HMC2_MODE.ipv4Item>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    function ipSync(): Array<HMC2_MODE.hmc_net_addr_item>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    function getAdapterIP2Sync(): Array<HMC2_MODE.hmc_net_addr_item>;
    /** 获取主机网络信息*/
    function getNetParams2Sync(): HMC2_MODE.hmc_NetParams | null;
    /** 从默认dns(联网)解析域名主机ip*/
    function getDomainIPaddress2Sync(url: string): Array<string>;
    /** 获取此端口被哪个进程占用了*/
    function getTCPv6PortProcessID2Sync(port: number): number[];
    /** 获取此端口被哪个进程占用了*/
    function getUDPv6PortProcessID2Sync(port: number): number[];
    /** 获取此端口被哪个进程占用了*/
    function getUDPv4PortProcessID2Sync(port: number): number | null;
    /** 获取此端口被哪个进程占用了*/
    function getTCPv4PortProcessID2Sync(port: number): number | null;
    /**
     * 枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息
     * @param tcp 枚举 TCP (v4)端口
     * @param udp 枚举 UDP (v4)端口
     * @param tcp6 枚举 TCP (v6)端口
     * @param udp6 枚举 UDP (v6)端口
     */
    function getConnectNetList2Sync(tcp?: boolean, udp?: boolean, tcp6?: boolean, udp6?: boolean): Array<HMC2_MODE.ConnectNet | HMC2_MODE.ConnectNet>;
}
export {};
