
import type _hmc = require("../../../mian/hmc");
import type { HMC } from "../../../mian/hmc";

// vs编译设置里面的最后一个命令行是 .node 文件
import fs = require("fs-extra");
import jsonfm = require("jsonfm");
import shake = require("hmc-shake");

const native: _hmc.HMC.G_HMC_NATIVE & Native = require(process.argv.at(-1) || "");
import log4js = require("D:/source/魔法自动更新/node_modules/log4js");
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");

export interface Native {
    /**
     * 获取进程列表（枚举法）
     * - 枚举是最快的 最安全的 不会出现遗漏
     * @module 异步 目前仅支持单并发 
     * @time  fn() 9.691ms     fn(true)61.681ms
     * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
     * @returns 
     */
    getAllProcessList: (is_execPath?: boolean) => Promise<string> | number,
    /**
     * 获取进程列表（枚举法）
     * - 枚举是最快的 最安全的 不会出现遗漏
     * @module 同步 
     * @time  fn() 11.147ms     fn(true)44.633ms
     * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
     * @returns 
     */
    getAllProcessListSync: (is_execPath?: boolean) => string
    /**
     * 获取进程列表 (快照法)  
     * - (一般用来枚举进程树)
     * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
     * @module 异步 目前仅支持单并发
     * @time 66.428ms
     * @returns 
     */
    getAllProcessListSnp: () => Promise<string> | number,
    /**
     * 获取进程列表 (快照法)  
     * - (一般用来枚举进程树)
     * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
     * @module 同步 
     * @time 66.428ms
     * @returns 
     */
    getAllProcessListSnpSync: () => string
    /**
     * 获取进程列表 (内核法)
     * - (可以获取内核软件和系统服务的名称)
     * - 请注意 内核法有可能被杀毒软件拦截
     * - 有概率第一次获取时失败
     * @module 异步 目前仅支持单并发 
     * @time 30.542ms
     * @returns 
     */
    getAllProcessListNt: () => Promise<string> | number,
    /**
     * 获取进程列表 (内核法)
     * - (可以获取内核软件和系统服务的名称)
     * - 请注意 内核法有可能被杀毒软件拦截
     * - 有概率第一次获取时失败
     * @module 同步 
     * @time 30.542ms
     * @returns 
     */
    getAllProcessListNtSync: () => string

}


class PromiseSession {
    private data_list: Array<undefined | null | any>;
    private SessionID: number;
    /**
     * 将 PromiseSession 转为 Promise
     * @param format 数据格式化的函数
     * @returns 
     */
    public to_Promise<T>(format: (value: Array<undefined | null | any>) => T): Promise<T> {
        const this_ = this;
        return new Promise(function (resolve, reject) {
            try {
                setInterval(() => {
                    const temp = native._PromiseSession_get(this_.SessionID, 50);
                    for (let index = 0; index < (temp || []).length; index++) {
                        const element = (temp || [])[index];
                        this_.data_list.push(element);
                    }
                    if (!temp && native._PromiseSession_isClosed(this_.SessionID)) {
                        resolve(format(this_.data_list));
                    }
                }, 25);

            } catch (error) {
                reject(error);
            }
        });
    }

    /**
     * PromiseSession 转为 callBack 
     * @param format 格式化的函数 如果没有callback 此函数将被作为callBack使用
     * @param callback 回调函数 接收的第一个参数将会是 format格式化过得内容
     * @param everyCallback 是否每次回调 当此选项为false 将只会在PromiseSession接收完成时候回调
     */
    public to_callback<T>(format: (value: Array<undefined | null | any>) => T, callback?: (value: T) => any, everyCallback?: boolean) {
        try {
            const this_ = this;
            setInterval(() => {
                const temp = native._PromiseSession_get(this_.SessionID, 50);
                for (let index = 0; index < (temp || []).length; index++) {
                    const element = (temp || [])[index];
                    this_.data_list.push(element);
                    if (!everyCallback) {
                        if (callback) {
                            callback(format(element));
                        } else {
                            format(element);
                        }
                    }
                }

                if (!temp && native._PromiseSession_isClosed(this_.SessionID)) {
                    if (everyCallback) {
                        if (callback) {
                            callback(format(this_.data_list));
                        } else {
                            format(this_.data_list);
                        }
                    }
                }
            }, 25);

        } catch (error) {

        }
    }

    /**
     * 异步改同步
     */
    public await() {
        native._PromiseSession_await(this.SessionID);
        return native._PromiseSession_get(this.SessionID, 999999999);
    }

    /**
     * 提前结束
     */
    public stop() {
        native._PromiseSession_stop(this.SessionID);
    }
    /**
     * 初始化一个将 hmc_PromiseSession 转为js 异步的方法
     * hmc_PromiseSession 是一个支持并发异步的调用封装库
     * 用于解决napi无法连续创建同事件的异步空间 以及napi的异步及其难写的问题
     * @param SessionID 
     */
    constructor(SessionID: number) {
        this.SessionID = SessionID;
        this.data_list = [];
    }
}


/**
   * 获取进程列表 (快照法)  
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步 目前仅支持单并发
   * @time 66.428ms
   * @returns 
   */
export function getAllProcessListSnp(callback: (data_list: Array<HMC.PROCESSENTRY_V2>, err: null | Error) => void): void;
export function getAllProcessListSnp(): Promise<Array<HMC.PROCESSENTRY_V2>>;
export function getAllProcessListSnp(callback?: unknown) {
    const data = native.getAllProcessListSnp();
    let result: Promise<Array<HMC.PROCESSENTRY_V2>>;

    if (typeof data == "number") {
        result = (new PromiseSession(data)).to_Promise((data) => {
            return (JSON.parse(data[0]) as any[]).map(result => {
                result.pid = result.UniqueProcessId;
                result.name = result.ImageName;
                return result;
            })
        });
    } else {
        result = data.then((data) => {
            return (JSON.parse(data) as any[]).map(result => {
                result.pid = result.th32ProcessID;
                result.name = result.szExeFile;
                result.ppid = result.th32ParentProcessID;
                return result;
            })
        });
    }

    if (typeof callback === 'function') {
        result.then((data) => callback(data, null)).catch((err) => { callback([], err) });
        return void 0;
    } else return result;
}

const getAllProcessListSnpSessionBuffList: Array<HMC.PROCESSENTRY_V2> = [];

/**
   * 获取进程列表 (快照法)   带有一个临时缓冲 在1.2秒内提供高速读取
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步 目前仅支持单并发
   * @time 66.428ms
   * @returns 
   */
export function getAllProcessListSnpSession(callback: (data_list: Array<HMC.PROCESSENTRY_V2>, err: null | Error) => void): void;
export function getAllProcessListSnpSession(): Promise<Array<HMC.PROCESSENTRY_V2>>;
export function getAllProcessListSnpSession(callback?: unknown) {
    return callback ? void 0 : (new Promise<Array<HMC.PROCESSENTRY_V2>>(async (resolve, reject) => {
        if (getAllProcessListSnpSessionBuffList.length) {
            return typeof callback == "function" ? callback(getAllProcessListSnpSessionBuffList, null) : resolve(getAllProcessListSnpSessionBuffList);
        }

        for (const iterator of (await getAllProcessListSnp().catch((err) => {
            if (typeof callback == "function") {
                callback([], err);
            } else reject(err);

        })) || []) {
            getAllProcessListSnpSessionBuffList.push(iterator);
        }

        typeof callback == "function" ? callback(getAllProcessListSnpSessionBuffList, null) : resolve(getAllProcessListSnpSessionBuffList);

        setTimeout(() => {
            getAllProcessListSnpSessionBuffList.length = 0;
        }, 1200);

    }));

}

/**
   * 获取进程列表 (快照法)   带有一个临时缓冲 在1.2秒内提供高速读取
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步 目前仅支持单并发
   * @time 66.428ms
   * @returns 
   */
export function getAllProcessListSnpSessionSync(): Array<HMC.PROCESSENTRY_V2> {

    if (getAllProcessListSnpSessionBuffList.length) {
        return getAllProcessListSnpSessionBuffList;
    }

    for (const iterator of getAllProcessListSnpSync() || []) {
        getAllProcessListSnpSessionBuffList.push(iterator);
    }


    setTimeout(() => {
        getAllProcessListSnpSessionBuffList.length = 0;
    }, 1200);

    return getAllProcessListSnpSessionBuffList;
}
/**
 * 获取进程列表 (内核法)
 * - (可以获取内核软件和系统服务的名称)
 * - 请注意 内核法有可能被杀毒软件拦截
 * - 有概率第一次获取时失败
 * @module 异步 目前仅支持单并发 
 * @time 30.542ms
 * @returns 
 */
export function getAllProcessListNt(callback: (data_list: Array<HMC.PSYSTEM_PROCESS_INFORMATION & { name: string, pid: number }> | null, err: null | Error) => void): void;
export function getAllProcessListNt(): Promise<Array<HMC.PSYSTEM_PROCESS_INFORMATION & { name: string, pid: number }>>;
export function getAllProcessListNt(callback?: unknown) {
    const data = native.getAllProcessListNt();
    let result: Promise<Array<HMC.PSYSTEM_PROCESS_INFORMATION & { name: string, pid: number }>>;

    if (typeof data == "number") {
        result = (new PromiseSession(data)).to_Promise((data) => {
            return (JSON.parse(data[0]) as any[]).map(result => {
                result.pid = result.UniqueProcessId;
                result.name = result.ImageName;
                return result;
            })
        });
    } else {
        result = data.then((data) => {
            return (JSON.parse(data) as any[]).map(result => {
                result.pid = result.UniqueProcessId;
                result.name = result.ImageName;
                return result;
            })
        });
    }

    if (typeof callback === 'function') {
        result.then((data) => callback(data, null)).catch((err) => { callback(null, err) });
        return void 0;
    } else return result;

}

/**
 * 获取进程列表（枚举法）
 * - 枚举是最快的 最安全的 不会出现遗漏
 * @module 异步 目前仅支持单并发 
 * @time  fn() 9.691ms     fn(true)61.681ms
 * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
 * @returns 
 */
export function getAllProcessList(callback: ((data_list: Array<{ pid: number }> | null, err: null | Error) => void)): void;
export function getAllProcessList(callback: ((data_list: Array<{ pid: number, name: string, path: string }> | null, err: null | Error) => void), is_execPath: true): void;
export function getAllProcessList(is_execPath: true): Promise<Array<{ pid: number, name: string, path: string }>>;
export function getAllProcessList(): Promise<Array<{ pid: number }>>;
export function getAllProcessList(callback?: unknown, is_execPath?: unknown) {
    const data = is_execPath ? native.getAllProcessList(true) : native.getAllProcessList();
    let result: Promise<any[]>;

    if (typeof data == "number") {
        result = (new PromiseSession(data)).to_Promise((data) => (JSON.parse(data[0])));
    } else {
        result = data.then((data) => (JSON.parse(data) as any[]));
    }

    if (typeof callback === 'function') {
        result.then((data) => callback(data, null)).catch((err) => { callback(null, err) });
        return void 0;

    } else return result;
}

/**
 * 获取进程列表（枚举法）
 * - 枚举是最快的 最安全的 不会出现遗漏
 * @module 同步 
 * @time  fn() 11.147ms     fn(true)44.633ms
 * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
 * @returns 
 */
export function getAllProcessListSync(is_execPath?: true): Array<{ pid: number, name: string, path: string }>;
export function getAllProcessListSync(): Array<{ pid: number }>;
export function getAllProcessListSync(is_execPath?: unknown) {
    return JSON.parse(is_execPath ? native.getAllProcessListSync(true) : native.getAllProcessListSync());
}


/**
 * 获取进程列表 (内核法)
 * - (可以获取内核软件和系统服务的名称)
 * - 请注意 内核法有可能被杀毒软件拦截
 * - 有概率第一次获取时失败
 * @module 同步 
 * @time 30.542ms
 * @returns 
 */
export function getAllProcessListNtSync(): Array<HMC.PSYSTEM_PROCESS_INFORMATION & { name: string, pid: number }> {
    return JSON.parse(native.getAllProcessListNtSync());
}

/**
 * 获取进程列表 (快照法)  
 * - (一般用来枚举进程树)
 * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
 * @module 同步 
 * @time 66.428ms
 * @returns 
 */
export function getAllProcessListSnpSync(): Array<HMC.PROCESSENTRY_V2>;
export function getAllProcessListSnpSync() {
    return JSON.parse(native.getAllProcessListSnpSync());
}


/**
 * 获取匹配进程的 父进程信息
 * @param Process 需要被搜索的子进程 名称/pid/正则名称
 * @param is_SessionCache 是否启用缓冲区以提高检索速度 （缓冲区有效时间1.2秒）
 * @returns 
 */
export function getProcessParentProcessMatch(Process: string | RegExp, is_SessionCache?: boolean): Promise<Array<HMC.PROCESSENTRY_V2>>;
export function getProcessParentProcessMatch(Process: number, is_SessionCache?: boolean): Promise<HMC.PROCESSENTRY_V2>;
export function getProcessParentProcessMatch(Process: unknown, is_SessionCache = true): unknown {
    return new Promise((resolve, reject) => {
        const fun = (is_SessionCache ? getAllProcessListSnpSession : getAllProcessListSnp);
        const data_list: Array<HMC.PROCESSENTRY_V2> = [];
        fun().then(process_list => {
            for (let index = 0; index < process_list.length; index++) {
                const process = process_list[index];

                if (typeof Process == "number" && process.pid == Process) {
                    return resolve(process);
                }

                if (typeof Process == "string" && process.szExeFile == "string") {
                    data_list.push(process);
                }

                if (Process instanceof RegExp && process.szExeFile.match(Process)) {
                    data_list.push(process);
                }

            }

            return is_SessionCache ? resolve(null) : resolve(data_list);

        }).catch(reject);
    });
}


/**
 * 获取匹配进程的 父进程信息
 * @param Process 需要被搜索的子进程 名称/pid/正则名称
 * @param is_SessionCache 是否启用缓冲区以提高检索速度 （缓冲区有效时间1.2秒）
 * @returns 
 */
export function getProcessParentProcessMatchSync(Process: string | RegExp, is_SessionCache?: boolean): Array<HMC.PROCESSENTRY_V2>;
export function getProcessParentProcessMatchSync(Process: number, is_SessionCache?: boolean): HMC.PROCESSENTRY_V2 | null;
export function getProcessParentProcessMatchSync(Process: unknown, is_SessionCache = true): unknown {

    const data_list: Array<HMC.PROCESSENTRY_V2> = [];
    const process_list = is_SessionCache ? getAllProcessListSnpSync() : getAllProcessListSnpSessionSync();
    for (let index = 0; index < process_list.length; index++) {
        const process = process_list[index];

        if (typeof Process == "number" && process.pid == Process) {
            return process;
        }

        if (typeof Process == "string" && process.szExeFile == "string") {
            data_list.push(process);
        }

        if (Process instanceof RegExp && process.szExeFile.match(Process)) {
            data_list.push(process);
        }

    }

    return data_list;
}


export function getProcessNameAsync(ProcessID: number) {

}

export function getProcessFilePath(ProcessID: number){

}


export function getDetailsProcessNameList(){
   return getAllProcessListSync(true);
}

export function getDetailsProcessList(){
    return getAllProcessListSync(true);
 }
 
// const Console = console;
const Console = { time(...argv: any[]) { }, log(...argv: any[]) { }, timeEnd(...argv: any[]) { } };

// while (true)
(async function main() {
  /**

    let data: any = {};
    Console.time("getAllProcessListSnpSync");
    Console.log("getAllProcessListSnpSync->", (data["getAllProcessListSnpSync"] = getAllProcessListSnpSync()).length);
    Console.timeEnd("getAllProcessListSnpSync");

    Console.time("getAllProcessListNtSync");
    Console.log("getAllProcessListNtSync->", (data["getAllProcessListNtSync"] = getAllProcessListNtSync()).length);
    Console.timeEnd("getAllProcessListNtSync");

    Console.time("getAllProcessListSync");
    Console.log("getAllProcessListSync->", (data["getAllProcessListSync"] = getAllProcessListSync()).length);
    Console.timeEnd("getAllProcessListSync");

    Console.time("getAllProcessListSync");
    Console.log("getAllProcessListSync->", (data["getAllProcessListSync"] = getAllProcessListSync()).length);
    Console.timeEnd("getAllProcessListSync");



    Console.time("getAllProcessList[async]");
    Console.log("getAllProcessList[async]->", (getAllProcessList().then(() => Console.timeEnd("getAllProcessList[async]"))));



    Console.time("getAllProcessListSnp[async]");
    Console.log("getAllProcessListSnp[async]->", (getAllProcessListSnp().then(() => Console.timeEnd("getAllProcessListSnp[async]"))));



    Console.time("getAllProcessListNt[async]");
    Console.log("getAllProcessListNt[async]->", (getAllProcessListNt().then(() => Console.timeEnd("getAllProcessListNt[async]"))));


    Console.time("getAllProcessList[async](true)");
    Console.log("getAllProcessList[async](true)->", (getAllProcessList(true).then(() => Console.timeEnd("getAllProcessList[async](true)"))));



    Console.time("getAllProcessListSync");
    Console.log("getAllProcessListSync->", (data["getAllProcessListSync"] = getAllProcessListSync(true)).length);
    Console.timeEnd("getAllProcessListSync");

    Console.time("getAllProcessList");
    Console.log("getAllProcessList->", (data["getAllProcessList"] = await getAllProcessList()).length);
    Console.timeEnd("getAllProcessList");

    Console.time("getAllProcessListSnp");
    Console.log("getAllProcessListSnp->", (data["getAllProcessListSnp"] = await getAllProcessListSnp()).length);
    Console.timeEnd("getAllProcessListSnp");

    Console.time("getAllProcessListNt");
    Console.log("getAllProcessListNt->", (data["getAllProcessListNt"] = await getAllProcessListNt()).length);
    Console.timeEnd("getAllProcessListNt");

    Console.time("getAllProcessList");
    Console.log("getAllProcessList->", (data["getAllProcessList"] = await getAllProcessList(true)).length);
    Console.timeEnd("getAllProcessList");

    Console.time("getAllProcessListSync");
    Console.log("getAllProcessListSync->", (data["getAllProcessListSync"] = getAllProcessListSync(true)).length);
    Console.timeEnd("getAllProcessListSync");

    // fs.writeFileSync(process.cwd()+"/temp/main_log.json", jsonfm(JSON.stringify(data)) ,"utf-8");

   */


})();

process.exitCode = 666;