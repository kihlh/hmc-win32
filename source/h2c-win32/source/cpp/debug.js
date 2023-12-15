"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.getDetailsProcessList = exports.getDetailsProcessNameList = exports.getProcessFilePath = exports.getProcessNameAsync = exports.getProcessParentProcessMatchSync = exports.getProcessParentProcessMatch = exports.getAllProcessListSnpSync = exports.getAllProcessListNtSync = exports.getAllProcessListSync = exports.getAllProcessList = exports.getAllProcessListNt = exports.getAllProcessListSnpSessionSync = exports.getAllProcessListSnpSession = exports.getAllProcessListSnp = void 0;
const native = require(process.argv.at(-1) || "");
const log4js = require("D:/source/\u9B54\u6CD5\u81EA\u52A8\u66F4\u65B0/node_modules/log4js");
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
function getAllProcessListSnp(callback) {
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
exports.getAllProcessListSnp = getAllProcessListSnp;
const getAllProcessListSnpSessionBuffList = [];
function getAllProcessListSnpSession(callback) {
    return callback ? void 0 : (new Promise(async (resolve, reject) => {
        if (getAllProcessListSnpSessionBuffList.length) {
            return typeof callback == "function" ? callback(getAllProcessListSnpSessionBuffList, null) : resolve(getAllProcessListSnpSessionBuffList);
        }
        for (const iterator of (await getAllProcessListSnp().catch((err) => {
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
exports.getAllProcessListSnpSession = getAllProcessListSnpSession;
/**
   * 获取进程列表 (快照法)   带有一个临时缓冲 在1.2秒内提供高速读取
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步 目前仅支持单并发
   * @time 66.428ms
   * @returns
   */
function getAllProcessListSnpSessionSync() {
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
exports.getAllProcessListSnpSessionSync = getAllProcessListSnpSessionSync;
function getAllProcessListNt(callback) {
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
exports.getAllProcessListNt = getAllProcessListNt;
function getAllProcessList(callback, is_execPath) {
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
exports.getAllProcessList = getAllProcessList;
function getAllProcessListSync(is_execPath) {
    return JSON.parse(is_execPath ? native.getAllProcessListSync(true) : native.getAllProcessListSync());
}
exports.getAllProcessListSync = getAllProcessListSync;
/**
 * 获取进程列表 (内核法)
 * - (可以获取内核软件和系统服务的名称)
 * - 请注意 内核法有可能被杀毒软件拦截
 * - 有概率第一次获取时失败
 * @module 同步
 * @time 30.542ms
 * @returns
 */
function getAllProcessListNtSync() {
    return JSON.parse(native.getAllProcessListNtSync());
}
exports.getAllProcessListNtSync = getAllProcessListNtSync;
function getAllProcessListSnpSync() {
    return JSON.parse(native.getAllProcessListSnpSync());
}
exports.getAllProcessListSnpSync = getAllProcessListSnpSync;
function getProcessParentProcessMatch(Process, is_SessionCache = true) {
    return new Promise((resolve, reject) => {
        const fun = (is_SessionCache ? getAllProcessListSnpSession : getAllProcessListSnp);
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
exports.getProcessParentProcessMatch = getProcessParentProcessMatch;
function getProcessParentProcessMatchSync(Process, is_SessionCache = true) {
    const data_list = [];
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
exports.getProcessParentProcessMatchSync = getProcessParentProcessMatchSync;
function getProcessNameAsync(ProcessID) {
}
exports.getProcessNameAsync = getProcessNameAsync;
function getProcessFilePath(ProcessID) {
}
exports.getProcessFilePath = getProcessFilePath;
function getDetailsProcessNameList() {
    return getAllProcessListSync(true);
}
exports.getDetailsProcessNameList = getDetailsProcessNameList;
function getDetailsProcessList() {
    return getAllProcessListSync(true);
}
exports.getDetailsProcessList = getDetailsProcessList;
// const Console = console;
const Console = { time(...argv) { }, log(...argv) { }, timeEnd(...argv) { } };
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
