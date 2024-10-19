
import { HMC } from "./HMC";
import https from "node:https";
import http from "node:http";
import dgram from "node:dgram";
import net from "node:net";
import { Native } from "./Native";
import { ref } from "./util";


export enum HMC_SOKE_PROMISEEVAL_TASK_TYPE {

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
    // 获取本机的mac地址
    getMacAddresses2 = 33,

    isSystemFor64bit2 = 35,
};

export type HMC_SOKE_PROMISEEVAL_TASK_TYPE_ALL_NAME = keyof typeof HMC_SOKE_PROMISEEVAL_TASK_TYPE;


class HMC_PromiseeEvalTask {
    async: Partial<Record<HMC_SOKE_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => Promise<any>>> = {};
    sync: Partial<Record<HMC_SOKE_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => any>> = {};
    constructor() {

        const TASK_TYPE_LIST = Object.keys(HMC_SOKE_PROMISEEVAL_TASK_TYPE) as Array<HMC_SOKE_PROMISEEVAL_TASK_TYPE_ALL_NAME>;
        const _this: HMC_PromiseeEvalTask = this;

        for (let index = 0; index < TASK_TYPE_LIST.length; index++) {
            const TASK_TYPE: HMC_SOKE_PROMISEEVAL_TASK_TYPE_ALL_NAME = TASK_TYPE_LIST[index];
            if (!TASK_TYPE || TASK_TYPE?.match(/^\d+/)) continue;

            const TASK_ID = HMC_SOKE_PROMISEEVAL_TASK_TYPE[TASK_TYPE];

            _this.async[TASK_TYPE] = (...arg: any[]) => {
                try {

                    if (!Native.native?.HMC_GetSockEnvInfo) {
                        return Promise.reject(HMC.HMCNotPlatform);
                    }

                    if (arg.length >= 1) {
                        return Native.native.HMC_GetSockEnvInfo(TASK_ID, ...arg);
                    }

                    return Native.native.HMC_GetSockEnvInfo(TASK_ID);

                } catch (error) {
                    return Promise.reject(error);
                }
            }

            _this.sync[TASK_TYPE] = (...arg: any[]) => {
                if (!Native.native?.HMC_GetSockEnvInfoSync) {
                    return null;
                }
                if (arg.length >= 1) {
                    return Native.native.HMC_GetSockEnvInfoSync(TASK_ID, ...arg) || null;
                }

                return Native.native.HMC_GetSockEnvInfoSync(TASK_ID);
            }

            if (!_this[TASK_TYPE]) {

                _this[TASK_TYPE] = _this.async[TASK_TYPE];
            }

            const KEY: `${HMC_SOKE_PROMISEEVAL_TASK_TYPE_ALL_NAME}Sync` = `${TASK_TYPE}Sync`;

            if (!_this[KEY]) {

                _this[KEY] = _this.sync[TASK_TYPE];
            }

        }
    }

}


interface HMC_PromiseeEvalTask {

    /** 获取本机局域网的ip(v4)*/
    ipv4(): Promise<Array<HMC.ipv4Item>>;
    /** 获取本机局域网的ip(v4)*/
    getIpaddressList(): Promise<Array<HMC.ipv4Item>>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    ip(): Promise<Array<HMC.hmc_net_addr_item>>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    getAdapterIP2(): Promise<Array<HMC.hmc_net_addr_item>>;
    /** 获取主机网络信息*/
    getNetParams2(): Promise<HMC.hmc_NetParams | null>;
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
    getConnectNetList2(tcp: boolean, udp: boolean, tcp6: boolean, udp6: boolean): Promise<Array<HMC.ConnectNet | HMC.ConnectNet>>;
    /** 判断当前软件是否拥有管理员权限*/
    isAdmin2(): Promise<boolean>;

    // ----------------------------------------------------

    /** 获取本机局域网的ip(v4)*/
    ipv4Sync(): Array<HMC.ipv4Item>;
    /** 获取本机局域网的ip(v4)*/
    getIpaddressListSync(): Array<HMC.ipv4Item>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    ipSync(): Array<HMC.hmc_net_addr_item>;
    /**获取本机局域网的ip(适配器,v4,v6)*/
    getAdapterIP2Sync(): Array<HMC.hmc_net_addr_item>;
    /** 获取主机网络信息*/
    getNetParams2Sync(): HMC.hmc_NetParams | null;
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
    getConnectNetList2Sync(tcp: boolean, udp: boolean, tcp6: boolean, udp6: boolean): Array<HMC.ConnectNet | HMC.ConnectNet>;
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


export namespace Network {

    export const HMC_GetSokeEnvInfo = new HMC_PromiseeEvalTask();

    export function https_get_data(url: string) {
        return new Promise<Buffer>((resolve, reject) => {
            const buffList: Buffer[] = [];
            (() => {
                if (url.match("https://")) {
                    return https;
                } else {
                    return http;
                }
            })().get(url, (res) => {
                if (res.statusCode !== 200) {
                    reject(new Error(`get failure statusCode: ${res.statusCode || 404}`));
                    return;
                }

                res.on("data", (data) => {
                    buffList.push(data);
                });

                res.once("error", (err) => {
                    reject(err);
                });

                res.on('end', () => {
                    const buff = ref.concatBuff(buffList);
                    resolve(buff);
                    buffList.length = 0;
                });

            });
        });
    }

    /**
     * 获取公网ip
     * @returns 
     */
    export function public_ip(): Promise<string> {

        return new Promise<string>(async (resolve, reject) => {
            let result_ok = false;

            // http://ipwho.is/: 295.327880859375 ms
            // http://httpbin.org/ip: 540.3720703125 ms
            // https://ipapi.co/json/: 811.548095703125 ms
            // https://api.ipify.org/?format=json: 846.34814453125 ms
            // https://api.ip.sb/geoip: 1026.965087890625 ms
            // https://freeipapi.com/api/json/: 1932.1220703125 ms
            // http://ip-api.com/json/?lang=zh-CN: 5383.945068359375 ms
            // ... 超时

            let ip_server_list = [
                ["http://ipwho.is/", "ip"],
                ["http://httpbin.org/ip", "origin"],
                ["https://ipapi.co/json/", "ip"],
                ["https://api.ipify.org/?format=json", "ip"],
                ["https://freeipapi.com/api/json/", "ipAddress"],
                ["https://api.ip.sb/geoip", "ip"],
                ["https://api.myip.com/", "ip"],
                ["http://ip-api.com/json/?lang=zh-CN", "ip"],

            ];

            for (const iterator of ip_server_list) {
                try {
                    await https_get_data(iterator[0]).catch(() => Buffer.alloc(0)).then((response) => {
                        try {
                            let data = JSON.parse(response.toString("utf-8"));
                            if (data[iterator[1]]) {
                                result_ok = true;
                                resolve(data[iterator[1]]);
                            }
                        } catch (e) { }
                    });
                    if (result_ok) {
                        return;
                    }

                } catch (e) { }
            }


            reject();
        });

    }


    /**
     * 获取一个tcp空闲端口 (服务)
     * @returns 
     */
    export function freePort(): Promise<number> {
        return new Promise((resolve, reject) => {
            let sock = net.createServer(function () { });
            sock.listen(0, () => {
                // @ts-expect-error
                resolve(Number(sock?.address()?.port as string));
                sock.close();
            });

            sock.once("error", reject);
        });
    }

    /**
     * 获取一个tcp空闲端口 (服务)
     * @returns 
     */
    export function freePortTCP(): Promise<number> {
        return freePort();
    }

    /**
     * 获取一个UDP空闲端口
     * @returns 
     */
    export function freePortUDP(): Promise<number> {
        return new Promise((resolve, reject) => {
            let udp4 = dgram.createSocket('udp4');
            udp4.bind(0);

            udp4.on("listening", function () {
                resolve && resolve(udp4.address().port);
                udp4.close();
            });

            udp4.once("error", reject);
        });
    }

    /**
     * 判断TCP(服务)端口号正在使用/系统占用
     * @param port TCP端口
     * @returns 
     */
    export function hasPortTCP(port: number): Promise<boolean>;
    export function hasPortTCP(port: number, callBack: (hasPort: boolean) => unknown): void;
    /**
     * 判断TCP(服务)端口号正在使用/系统占用
     * @param port TCP端口
     * @returns 
     */
    export function hasPortTCP(port: number, callBack?: (hasPort: boolean) => unknown): unknown {
        let resolve: ((hasPort: boolean) => unknown) | null = null;
        let prom;
        let sock = net.createServer(function () { });
        sock.listen(port);
        if (typeof callBack == 'function') {
            resolve = callBack;
        } else {
            prom = new Promise((Prom_resolve) => {
                resolve = Prom_resolve;
            });
        }
        sock.on("error", function (err) {
            resolve && resolve(true);
            sock.close();
        });
        sock.on("listening", function () {
            resolve && resolve(false);
            sock.close();
        });
        if (typeof callBack !== 'function') {
            return prom;
        }
    }


    /**
     * 判断UDP端口号正在使用/系统占用
     * @param port TCP端口
     * @returns 
     */
    export function hasPortUDP(port: number): Promise<boolean>;
    export function hasPortUDP(port: number, callBack: (hasPort: boolean) => unknown): void;
    /**
     * 判断UDP端口号正在使用/系统占用
     * @param port TCP端口
     * @returns 
     */
    export function hasPortUDP(port: number, callBack?: (hasPort: boolean) => unknown): unknown {
        let resolve: ((hasPort: boolean) => unknown) | null = null;
        let prom;
        let udp4 = dgram.createSocket('udp4');
        udp4.bind(port);
        if (typeof callBack == 'function') {
            resolve = callBack;
        } else {
            prom = new Promise((Prom_resolve) => {
                resolve = Prom_resolve;
            });
        }
        udp4.on("error", function (err) {
            resolve && resolve(true);
            udp4.close();
        });
        udp4.on("listening", function () {
            resolve && resolve(false);
            udp4.close();
        });
        if (typeof callBack !== 'function') {
            return prom;
        }
    }

    export const {
        /**判断当前软件是否拥有管理员权限 */
        isAdmin2,
        /**判断当前软件是否拥有管理员权限 */
        isAdmin2Sync,
        /**获取mac地址列表 */
        getMacAddresses2,
        /**获取mac地址列表 */
        getMacAddresses2Sync,
        /**获取hosts文件的路径 */
        getHostsPath2Sync,
        /**获取hosts文件的路径 */
        getHostsPath2,
        /**获取hosts文件的路径 */
        getSystemProxyPac2,
        /**获取hosts文件的路径 */
        getSystemProxyPac2Sync,
        /**获取系统代理链接（仅在启用系统代理时） */
        getSystemProxyServer2,
        /**获取系统代理链接（仅在启用系统代理时） */
        getSystemProxyServer2Sync,
        /**判断系统是否是64位系统 */
        isSystemFor64bit2,
        /**判断系统是否是64位系统 */
        isSystemFor64bit2Sync,
    } = HMC_GetSokeEnvInfo;

    /** 获取本机局域网的ip(v4)*/
    export async function ipv4(): Promise<Array<HMC.ipv4Item>> {
        return ref.JSONP<Array<HMC.ipv4Item>>(await HMC_GetSokeEnvInfo.ipv4(), []);
    }

    /** 获取本机局域网的ip(v4)*/
    export async function getIpaddressList(): Promise<Array<HMC.ipv4Item>> {
        return ref.JSONP<Array<HMC.ipv4Item>>(await HMC_GetSokeEnvInfo.getIpaddressList(), []);
    }

    /**获取本机局域网的ip(适配器,v4,v6)*/
    export async function ip(): Promise<Array<HMC.hmc_net_addr_item>> {
        return ref.JSONP<Array<HMC.hmc_net_addr_item>>(await HMC_GetSokeEnvInfo.ip(), []);
    }

    /**获取本机局域网的ip(适配器,v4,v6)*/
    export async function getAdapterIP2(): Promise<Array<HMC.hmc_net_addr_item>> {
        return ref.JSONP<Array<HMC.hmc_net_addr_item>>(await HMC_GetSokeEnvInfo.getAdapterIP2(), []);
    }

    /** 获取主机网络信息*/
    export async function getNetParams2(): Promise<HMC.hmc_NetParams | null> {
        return ref.JSONP<HMC.hmc_NetParams | null>(await HMC_GetSokeEnvInfo.getNetParams2(), null);
    }

    /** 从默认dns(联网)解析域名主机ip*/
    export async function getDomainIPaddress2(url: string): Promise<Array<string>> {
        return HMC_GetSokeEnvInfo.getDomainIPaddress2(ref.string(url || ""));
    }

    /** 获取此端口被哪个进程占用了*/
    export async function getTCPv6PortProcessID2(port: number): Promise<number[]> {
        return HMC_GetSokeEnvInfo.getTCPv6PortProcessID2(ref.int(port));
    }

    /** 获取此端口被哪个进程占用了*/
    export async function getUDPv6PortProcessID2(port: number): Promise<number[]> {
        return HMC_GetSokeEnvInfo.getUDPv6PortProcessID2(ref.int(port));
    }

    /** 获取此端口被哪个进程占用了*/
    export async function getUDPv4PortProcessID2(port: number): Promise<number | null> {
        return HMC_GetSokeEnvInfo.getUDPv4PortProcessID2(ref.int(port));
    }

    /** 获取此端口被哪个进程占用了*/
    export async function getTCPv4PortProcessID2(port: number): Promise<number | null> {
        return HMC_GetSokeEnvInfo.getTCPv4PortProcessID2(ref.int(port));
    }

    /**
     * 枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息
     * @param tcp 枚举 TCP (v4)端口
     * @param udp 枚举 UDP (v4)端口
     * @param tcp6 枚举 TCP (v6)端口
     * @param udp6 枚举 UDP (v6)端口
     */
    export async function getConnectNetList2(tcp?: boolean, udp?: boolean, tcp6?: boolean, udp6?: boolean): Promise<Array<HMC.ConnectNet | HMC.ConnectNet>> {
        return ref.JSONP<Array<HMC.ConnectNet | HMC.ConnectNet>>(await HMC_GetSokeEnvInfo.getConnectNetList2(
            typeof tcp == "boolean" ? tcp : true,
            typeof udp == "boolean" ? udp : true,
            typeof tcp6 == "boolean" ? tcp6 : true,
            typeof udp6 == "boolean" ? udp6 : true), []);
    }

    /** 获取本机局域网的ip(v4)*/
    export function ipv4Sync(): Array<HMC.ipv4Item> {
        return ref.JSONP<Array<HMC.ipv4Item>>(HMC_GetSokeEnvInfo.ipv4Sync(), []);
    }

    /** 获取本机局域网的ip(v4)*/
    export function getIpaddressListSync(): Array<HMC.ipv4Item> {
        return ref.JSONP<Array<HMC.ipv4Item>>(HMC_GetSokeEnvInfo.getIpaddressListSync(), []);
    }

    /**获取本机局域网的ip(适配器,v4,v6)*/
    export function ipSync(): Array<HMC.hmc_net_addr_item> {
        return ref.JSONP<Array<HMC.hmc_net_addr_item>>(HMC_GetSokeEnvInfo.ipSync(), []);
    }

    /**获取本机局域网的ip(适配器,v4,v6)*/
    export function getAdapterIP2Sync(): Array<HMC.hmc_net_addr_item> {
        return ref.JSONP<Array<HMC.hmc_net_addr_item>>(HMC_GetSokeEnvInfo.getAdapterIP2Sync(), []);
    }

    /** 获取主机网络信息*/
    export function getNetParams2Sync(): HMC.hmc_NetParams | null {
        return ref.JSONP<HMC.hmc_NetParams | null>(HMC_GetSokeEnvInfo.getNetParams2Sync(), null);
    }

    /** 从默认dns(联网)解析域名主机ip*/
    export function getDomainIPaddress2Sync(url: string): Array<string> {
        return HMC_GetSokeEnvInfo.getDomainIPaddress2Sync(ref.string(url || ""));
    }

    /** 获取此端口被哪个进程占用了*/
    export function getTCPv6PortProcessID2Sync(port: number): number[] {
        return HMC_GetSokeEnvInfo.getTCPv6PortProcessID2Sync(ref.int(port));
    }

    /** 获取此端口被哪个进程占用了*/
    export function getUDPv6PortProcessID2Sync(port: number): number[] {
        return HMC_GetSokeEnvInfo.getUDPv6PortProcessID2Sync(ref.int(port));
    }

    /** 获取此端口被哪个进程占用了*/
    export function getUDPv4PortProcessID2Sync(port: number): number | null {
        return HMC_GetSokeEnvInfo.getUDPv4PortProcessID2Sync(ref.int(port));
    }

    /** 获取此端口被哪个进程占用了*/
    export function getTCPv4PortProcessID2Sync(port: number): number | null {
        return HMC_GetSokeEnvInfo.getTCPv4PortProcessID2Sync(ref.int(port));
    }

    /**
     * 枚举此电脑中的 端口 ipv4 and ipv6 的 TCP，UDP 端口信息
     * @param tcp 枚举 TCP (v4)端口
     * @param udp 枚举 UDP (v4)端口
     * @param tcp6 枚举 TCP (v6)端口
     * @param udp6 枚举 UDP (v6)端口
     */
    export function getConnectNetList2Sync(tcp?: boolean, udp?: boolean, tcp6?: boolean, udp6?: boolean): Array<HMC.ConnectNet | HMC.ConnectNet> {
        return ref.JSONP<Array<HMC.ConnectNet | HMC.ConnectNet>>(HMC_GetSokeEnvInfo.getConnectNetList2Sync(
            typeof tcp == "boolean" ? tcp : true,
            typeof udp == "boolean" ? udp : true,
            typeof tcp6 == "boolean" ? tcp6 : true,
            typeof udp6 == "boolean" ? udp6 : true), []);
    }

}