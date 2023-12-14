"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
// vs编译设置里面的最后一个命令行是 .node 文件
const fs = require("fs-extra");
const shake = require("hmc-shake");
const hmc = require(process.argv.at(-1) || "");
const log4js = require("D:/source/\u9B54\u6CD5\u81EA\u52A8\u66F4\u65B0/node_modules/log4js");
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");
// getAllProcessList: 21.405ms
// getAllProcessListSync: 16.179ms
// getAllProcessList: 77.835ms
// getAllProcessListSync: 71.577ms
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
                    const temp = hmc._PromiseSession_get(this_.SessionID, 50);
                    for (let index = 0; index < (temp || []).length; index++) {
                        const element = (temp || [])[index];
                        this_.data_list.push(element);
                    }
                    if (!temp && hmc._PromiseSession_isClosed(this_.SessionID)) {
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
                const temp = hmc._PromiseSession_get(this_.SessionID, 50);
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
                if (!temp && hmc._PromiseSession_isClosed(this_.SessionID)) {
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
        hmc._PromiseSession_await(this.SessionID);
        return hmc._PromiseSession_get(this.SessionID, 999999999);
    }
    /**
     * 提前结束
     */
    stop() {
        hmc._PromiseSession_stop(this.SessionID);
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
(async function main() {
    let data = "";
    console.time("getAllProcessListNtSync");
    data = await hmc.getAllProcessListNtSync();
    console.log(data);
    console.timeEnd("getAllProcessListNtSync");
    fs.writeFileSync(`./temp/getAllProcessListNtSync${shake.ID()}.json`, data, "utf8");
    // console.time("getAllProcessList");
    // data = await hmc.getAllProcessList();
    // console.timeEnd("getAllProcessList");
    // fs.writeFileSync(`./temp/getAllProcessList_${shake.ID()}.json`, data, "utf8");
    // console.time("getAllProcessListSync");
    // data = await hmc.getAllProcessListSync();
    // console.timeEnd("getAllProcessListSync");
    // fs.writeFileSync(`./temp/getAllProcessListSync${shake.ID()}.json`, data, "utf8");
    // console.time("getAllProcessList");
    // data = await hmc.getAllProcessList(true);
    // console.timeEnd("getAllProcessList");
    // fs.writeFileSync(`./temp/getAllProcessList${shake.ID()}.json`, data, "utf8");
    // console.time("getAllProcessListSync");
    // data = await hmc.getAllProcessListSync(true);
    // console.timeEnd("getAllProcessListSync");
    // fs.writeFileSync(`./temp/getAllProcessListSync${shake.ID()}.json`, data, "utf8");
    // getAllProcessList: 9.691ms
    // getAllProcessListSync: 11.147ms
    // getAllProcessList: 61.681ms
    // getAllProcessListSync: 44.633ms
})().then(() => process.exit(666));
