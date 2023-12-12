"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const hmc = require(process.argv.at(-1) || "");
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
console.log((new PromiseSession(hmc.getProcessidFilePath___SP(4))).await());
(new PromiseSession(hmc.getAllProcessListv2___SP(true, true, true, true, true, true))).to_Promise(_ => _).then(console.log);
