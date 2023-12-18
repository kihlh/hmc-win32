"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.findProcess2Sync = exports.findProcess2 = exports.getProcessName2Sync = exports.getProcessName2 = exports.getProcessNameNt2 = exports.getProcessNameNt2Sync = exports.getProcessNameSnp2 = exports.getProcessNameSnp2Sync = exports.getDetailsProcessList2 = exports.getProcessFilePath2Sync = exports.getProcessFilePath2 = exports.getProcessParentProcessMatch2Sync = exports.getProcessParentProcessMatch2 = exports.getAllProcessListSnp2Sync = exports.getAllProcessListNt2Sync = exports.getAllProcessList2Sync = exports.getAllProcessList2 = exports.getAllProcessListNt2 = exports.getAllProcessListSnpSession2Sync = exports.getAllProcessListSnpSession2 = exports.getAllProcessListSnp2 = void 0;
const native = require(process.argv.at(-1) || "");
const log4js = require("D:/source/\u9B54\u6CD5\u81EA\u52A8\u66F4\u65B0/node_modules/log4js");
const hmc_win32_1 = require("hmc-win32");
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");
class PromiseSession {
    /**
     * 将 PromiseSession 转为 Promise
     * @param format 数据格式化的函数
     * @returns
     */
    to_Promise(format) {
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
            }
            catch (error) {
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
    to_callback(format, callback, everyCallback) {
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
                        }
                        else {
                            format(element);
                        }
                    }
                }
                if (!temp && native._PromiseSession_isClosed(this_.SessionID)) {
                    if (everyCallback) {
                        if (callback) {
                            callback(format(this_.data_list));
                        }
                        else {
                            format(this_.data_list);
                        }
                    }
                }
            }, 25);
        }
        catch (error) {
        }
    }
    /**
     * 异步改同步
     */
    await() {
        native._PromiseSession_await(this.SessionID);
        return native._PromiseSession_get(this.SessionID, 999999999);
    }
    /**
     * 提前结束
     */
    stop() {
        native._PromiseSession_stop(this.SessionID);
    }
    /**
     * 初始化一个将 hmc_PromiseSession 转为js 异步的方法
     * hmc_PromiseSession 是一个支持并发异步的调用封装库
     * 用于解决napi无法连续创建同事件的异步空间 以及napi的异步及其难写的问题
     * @param SessionID
     */
    constructor(SessionID) {
        this.SessionID = SessionID;
        this.data_list = [];
    }
}
function getAllProcessListSnp2(callback) {
    const data = native.getAllProcessListSnp();
    let result;
    if (typeof data == "number") {
        result = (new PromiseSession(data)).to_Promise((data) => {
            return JSON.parse(data[0]).map(result => {
                result.pid = result.UniqueProcessId;
                result.name = result.ImageName;
                return result;
            });
        });
    }
    else {
        result = data.then((data) => {
            return JSON.parse(data).map(result => {
                result.pid = result.th32ProcessID;
                result.name = result.szExeFile;
                result.ppid = result.th32ParentProcessID;
                return result;
            });
        });
    }
    if (typeof callback === 'function') {
        result.then((data) => callback(data, null)).catch((err) => { callback([], err); });
        return void 0;
    }
    else
        return result;
}
exports.getAllProcessListSnp2 = getAllProcessListSnp2;
const getAllProcessListSnpSessionBuffList = [];
function getAllProcessListSnpSession2(callback) {
    return callback ? void 0 : (new Promise(async (resolve, reject) => {
        if (getAllProcessListSnpSessionBuffList.length) {
            return typeof callback == "function" ? callback(getAllProcessListSnpSessionBuffList, null) : resolve(getAllProcessListSnpSessionBuffList);
        }
        for (const iterator of (await getAllProcessListSnp2().catch((err) => {
            if (typeof callback == "function") {
                callback([], err);
            }
            else
                reject(err);
        })) || []) {
            getAllProcessListSnpSessionBuffList.push(iterator);
        }
        typeof callback == "function" ? callback(getAllProcessListSnpSessionBuffList, null) : resolve(getAllProcessListSnpSessionBuffList);
        setTimeout(() => {
            getAllProcessListSnpSessionBuffList.length = 0;
        }, 1200);
    }));
}
exports.getAllProcessListSnpSession2 = getAllProcessListSnpSession2;
/**
   * 获取进程列表 (快照法)   带有一个临时缓冲 在1.2秒内提供高速读取
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步
   * @time 66.428ms
   * @returns
   */
function getAllProcessListSnpSession2Sync() {
    if (getAllProcessListSnpSessionBuffList.length) {
        return getAllProcessListSnpSessionBuffList;
    }
    for (const iterator of getAllProcessListSnp2Sync() || []) {
        getAllProcessListSnpSessionBuffList.push(iterator);
    }
    setTimeout(() => {
        getAllProcessListSnpSessionBuffList.length = 0;
    }, 1200);
    return getAllProcessListSnpSessionBuffList;
}
exports.getAllProcessListSnpSession2Sync = getAllProcessListSnpSession2Sync;
function getAllProcessListNt2(callback) {
    const data = native.getAllProcessListNt();
    let result;
    if (typeof data == "number") {
        result = (new PromiseSession(data)).to_Promise((data) => {
            return JSON.parse(data[0]).map(result => {
                result.pid = result.UniqueProcessId;
                result.name = result.ImageName;
                return result;
            });
        });
    }
    else {
        result = data.then((data) => {
            return JSON.parse(data).map(result => {
                result.pid = result.UniqueProcessId;
                result.name = result.ImageName;
                return result;
            });
        });
    }
    if (typeof callback === 'function') {
        result.then((data) => callback(data, null)).catch((err) => { callback(null, err); });
        return void 0;
    }
    else
        return result;
}
exports.getAllProcessListNt2 = getAllProcessListNt2;
function getAllProcessList2(callback, is_execPath) {
    const data = is_execPath ? native.getAllProcessList(true) : native.getAllProcessList();
    let result;
    if (typeof data == "number") {
        result = (new PromiseSession(data)).to_Promise((data) => (JSON.parse(data[0])));
    }
    else {
        result = data.then((data) => JSON.parse(data));
    }
    if (typeof callback === 'function') {
        result.then((data) => callback(data, null)).catch((err) => { callback(null, err); });
        return void 0;
    }
    else
        return result;
}
exports.getAllProcessList2 = getAllProcessList2;
function getAllProcessList2Sync(is_execPath) {
    return JSON.parse(is_execPath ? native.getAllProcessListSync(true) : native.getAllProcessListSync());
}
exports.getAllProcessList2Sync = getAllProcessList2Sync;
/**
 * 获取进程列表 (内核法)
 * - (可以获取内核软件和系统服务的名称)
 * - 请注意 内核法有可能被杀毒软件拦截
 * - 有概率第一次获取时失败
 * @module 同步
 * @time 30.542ms
 * @returns
 */
function getAllProcessListNt2Sync() {
    return JSON.parse(native.getAllProcessListNtSync());
}
exports.getAllProcessListNt2Sync = getAllProcessListNt2Sync;
function getAllProcessListSnp2Sync() {
    return JSON.parse(native.getAllProcessListSnpSync());
}
exports.getAllProcessListSnp2Sync = getAllProcessListSnp2Sync;
function getProcessParentProcessMatch2(Process, is_SessionCache = true) {
    return new Promise((resolve, reject) => {
        const fun = (is_SessionCache ? getAllProcessListSnpSession2 : getAllProcessListSnp2);
        const data_list = [];
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
exports.getProcessParentProcessMatch2 = getProcessParentProcessMatch2;
function getProcessParentProcessMatch2Sync(Process, is_SessionCache = true) {
    const data_list = [];
    const process_list = is_SessionCache ? getAllProcessListSnp2Sync() : getAllProcessListSnpSession2Sync();
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
exports.getProcessParentProcessMatch2Sync = getProcessParentProcessMatch2Sync;
function getProcessFilePath2(ProcessID, callback) {
    const data = native.getProcessFilePath(hmc_win32_1.ref.int(ProcessID));
    let result;
    if (typeof data == "number") {
        result = (new PromiseSession(data)).to_Promise((data) => {
            return (data[0] || null);
        });
    }
    else {
        result = data.then((data) => data || null);
    }
    if (typeof callback === 'function') {
        result.then((data) => callback(data, null)).catch((err) => { callback(null, err); });
        return void 0;
    }
    else
        return result;
}
exports.getProcessFilePath2 = getProcessFilePath2;
/**
 * 获取指定进程的可执行文件路径
 * @param ProcessID 进程id
 * @returns
 */
function getProcessFilePath2Sync(ProcessID) {
    const data = native.getProcessFilePathSync(hmc_win32_1.ref.int(ProcessID));
    return data || null;
}
exports.getProcessFilePath2Sync = getProcessFilePath2Sync;
/**
 * 获取一个带有exe path 的进程列表
 * @returns
 */
function getDetailsProcessList2() {
    return getAllProcessList2Sync(true);
}
exports.getDetailsProcessList2 = getDetailsProcessList2;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @param is_SessionCache  是否使用缓存提高速度
 * @returns
 */
function getProcessNameSnp2Sync(ProcessID, is_SessionCache) {
    const data_list = is_SessionCache ? getAllProcessListSnpSession2Sync() : getAllProcessListSnp2Sync();
    for (let index = 0; index < data_list.length; index++) {
        const element = data_list[index];
        if (element.pid == ProcessID) {
            return element.szExeFile;
        }
    }
    return null;
}
exports.getProcessNameSnp2Sync = getProcessNameSnp2Sync;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @param is_SessionCache  是否使用缓存提高速度
 * @returns
 */
function getProcessNameSnp2(ProcessID, is_SessionCache) {
    return new Promise(async (resolve, reject) => {
        const data_list = await (is_SessionCache ? getAllProcessListSnpSession2().catch(reject) : getAllProcessListSnp2().catch(reject)) || [];
        for (let index = 0; index < data_list.length; index++) {
            const element = data_list[index];
            if (element.pid == ProcessID) {
                resolve(element.szExeFile);
                return;
            }
        }
        resolve(null);
    });
}
exports.getProcessNameSnp2 = getProcessNameSnp2;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
function getProcessNameNt2Sync(ProcessID) {
    const data_list = getAllProcessListNt2Sync();
    for (let index = 0; index < data_list.length; index++) {
        const element = data_list[index];
        if (element.pid == ProcessID) {
            return element.ImageName;
        }
    }
    return null;
}
exports.getProcessNameNt2Sync = getProcessNameNt2Sync;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
function getProcessNameNt2(ProcessID) {
    return new Promise(async (resolve, reject) => {
        const data_list = await getAllProcessListNt2();
        for (let index = 0; index < data_list.length; index++) {
            const element = data_list[index];
            if (element.pid == ProcessID) {
                resolve(element.ImageName);
                return;
            }
        }
        resolve(null);
    });
}
exports.getProcessNameNt2 = getProcessNameNt2;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
function getProcessName2(ProcessID) {
    return new Promise(async (resolve, reject) => {
        var _a;
        let FilePath = await ((_a = getProcessFilePath2(ProcessID)) === null || _a === void 0 ? void 0 : _a.catch(reject));
        if (FilePath) {
            resolve(FilePath.split(/[\\\/]+/).pop() || null);
        }
        return resolve(null);
    });
}
exports.getProcessName2 = getProcessName2;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
function getProcessName2Sync(ProcessID) {
    let FilePath = getProcessFilePath2Sync(ProcessID);
    if (FilePath) {
        return (FilePath.split(/[\\\/]+/).pop() || null);
    }
    return null;
}
exports.getProcessName2Sync = getProcessName2Sync;
/**
 * 按照名称搜索进程
 * @param ProcessName
 * @returns
 */
async function findProcess2(ProcessName, isMacthFile = false) {
    return new Promise(async (resolve, reject) => {
        var _a;
        let result = [];
        let ProcessList = await (isMacthFile ? getAllProcessList2(true) : getAllProcessList2()).catch(reject) || [];
        for (let index = 0; index < ProcessList.length; index++) {
            const Process = ProcessList[index];
            if (typeof ProcessName == "string") {
                // @ts-expect-error
                if (Process.name.includes(ProcessName) || ((_a = Process === null || Process === void 0 ? void 0 : Process.path) === null || _a === void 0 ? void 0 : _a.includes(ProcessName))) {
                    result.push(Process);
                }
            }
            else if (typeof ProcessName == "number") {
                if (Process.pid == ProcessName) {
                    let path = await getProcessFilePath2(ProcessName).catch(reject);
                    // @ts-expect-error
                    Process.path = path || null;
                    // @ts-expect-error
                    Process.name = (path === null || path === void 0 ? void 0 : path.split(/[\\\/]+/).at(-1)) || null;
                    result.push(Process);
                }
            }
            else {
                // @ts-expect-error
                if (Process.name.match(ProcessName) || (typeof (Process === null || Process === void 0 ? void 0 : Process.path) == "string") ? Process.path.match(ProcessName) : false) {
                    result.push(Process);
                }
            }
        }
        resolve(result);
    });
}
exports.findProcess2 = findProcess2;
/**
 * 按照名称搜索进程
 * @param ProcessName
 * @returns
 */
function findProcess2Sync(ProcessName, isMacthFile = false) {
    var _a;
    let result = [];
    let ProcessList = (isMacthFile ? getAllProcessList2Sync(true) : getAllProcessList2Sync()) || [];
    for (let index = 0; index < ProcessList.length; index++) {
        const Process = ProcessList[index];
        if (typeof ProcessName == "string") {
            if (Process.name.includes(ProcessName) || ((_a = Process === null || Process === void 0 ? void 0 : Process.path) === null || _a === void 0 ? void 0 : _a.includes(ProcessName))) {
                result.push(Process);
            }
        }
        else if (typeof ProcessName == "number") {
            if (Process.pid == ProcessName) {
                let path = getProcessFilePath2Sync(ProcessName);
                // @ts-expect-error
                Process.path = path || null;
                // @ts-expect-error
                Process.name = (path === null || path === void 0 ? void 0 : path.split(/[\\\/]+/).at(-1)) || null;
                result.push(Process);
            }
        }
        else {
            if (Process.name.match(ProcessName) || (typeof (Process === null || Process === void 0 ? void 0 : Process.path) == "string") ? Process.path.match(ProcessName) : false) {
                result.push(Process);
            }
        }
    }
    return result;
}
exports.findProcess2Sync = findProcess2Sync;
// const Console = console;
const Console = { time(...argv) { }, log(...argv) { }, timeEnd(...argv) { } };
let data = {};
Console.time("getAllProcessListSnpSync");
Console.log("getAllProcessListSnpSync->", (data["getAllProcessListSnpSync"] = getAllProcessListSnp2Sync()).length);
Console.timeEnd("getAllProcessListSnpSync");
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
    console.log("getProcessCpuUsageSync-> ", native.getProcessCpuUsageSync(7064));
    console.log("getProcessCpuUsage-> ", await native.getProcessCpuUsage(7064));
})();
process.exitCode = 666;
