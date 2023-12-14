
import type _hmc = require("../../../mian/hmc");
// vs编译设置里面的最后一个命令行是 .node 文件
import fs = require("fs-extra");
import jsonfm = require("jsonfm");
import shake = require("hmc-shake");

const hmc: _hmc.HMC.G_HMC_NATIVE & Native = require(process.argv.at(-1) || "");
import log4js = require("D:/source/魔法自动更新/node_modules/log4js");
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");


export interface Native {
    /**
     * 获取进程列表（枚举法）
     * - 枚举是最快的 最安全的 不会出现遗漏
     * @module 异步 目前仅支持单并发 
     * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
     * @returns 
     */
    getAllProcessList: (is_execPath?: boolean) => Promise<string>,
    /**
     * 获取进程列表（枚举法）
     * - 枚举是最快的 最安全的 不会出现遗漏
     *  @module 同步 
     *  @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
     * @returns 
     */
    getAllProcessListSync: (is_execPath?: boolean) => string
    /**
     * 获取进程列表 (快照法)  
     * - (一般用来枚举进程树)
     * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
     * @module 异步 目前仅支持单并发 
     * @param is_execPath 需要解析可执行文件路径
     * @returns 
     */
    getAllProcessListSnp: () => Promise<string>,
    /**
     * 获取进程列表 (快照法)  
     * - (一般用来枚举进程树)
     * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
     *  @module 同步 
     *  @param is_execPath 需要解析可执行文件路径
     * @returns 
     */
    getAllProcessListSnpSync: () => string
    /**
     * 获取进程列表 (内核法)
     * - (可以获取内核软件和系统服务的名称)
     * - 请注意 内核法有可能被杀毒软件拦截
     * @module 异步 目前仅支持单并发 
     * @param is_execPath 需要解析可执行文件路径
     * @returns 
     */
    getAllProcessListNt: () => Promise<string>,
    /**
     * 获取进程列表 (内核法)
     * - (可以获取内核软件和系统服务的名称)
     * - 请注意 内核法有可能被杀毒软件拦截
     *  @module 同步 
     *  @param is_execPath 需要解析可执行文件路径
     * @returns 
     */
    getAllProcessListNtSync: () => string

}
// getAllProcessList: 21.405ms
// getAllProcessListSync: 16.179ms
// getAllProcessList: 77.835ms
// getAllProcessListSync: 71.577ms


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
                    const temp = hmc._PromiseSession_get(this_.SessionID, 50);
                    for (let index = 0; index < (temp || []).length; index++) {
                        const element = (temp || [])[index];
                        this_.data_list.push(element);
                    }
                    if (!temp && hmc._PromiseSession_isClosed(this_.SessionID)) {
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
                const temp = hmc._PromiseSession_get(this_.SessionID, 50);
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

                if (!temp && hmc._PromiseSession_isClosed(this_.SessionID)) {
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
        hmc._PromiseSession_await(this.SessionID);
        return hmc._PromiseSession_get(this.SessionID, 999999999);
    }

    /**
     * 提前结束
     */
    public stop() {
        hmc._PromiseSession_stop(this.SessionID);
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


(async function main() {

    let data = "";

    console.time("getAllProcessListNtSync");

    data = await  hmc.getAllProcessListNtSync();

    console.log(data)

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