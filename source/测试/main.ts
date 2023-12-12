import type _hmc = require("../mian/hmc");

export interface Native {
    // [key: string]: any;

    /**
     * 获取指定id的  [Session Promise] 的所有已经完成的内容 同时回收空间
     * @param SessionID 内容id
     * @param size 最多取出多少个
     * @default 999
     */
    _PromiseSession_get(SessionID: number, size?: number): undefined | null | any[];
    /**
     * 判断指定的  [Session Promise] 是否已经结束
     * @param SessionID id
     */
    _PromiseSession_isClosed(SessionID: number): boolean;
    /**
     * 停止一个  [Session Promise] 事件
     * @param SessionID id
     */
    _PromiseSession_stop(SessionID: number): void;
    /**
     * 获取当前  Session ID 已经到哪里了
     */
    _PromiseSession_max_id(): number;
    /**
     * 获取指定的id存在了多少个数据
     * @param SessionID id
     */
    _PromiseSession_data_size(SessionID: number): number;
    /**
     * 设置每次获取 Session Promise 的毫秒数
     * @param sleep_time 毫秒
     * @default 5 ms
     */
    _PromiseSession_set_sleep_time(sleep_time: number): number;
    /**
     * 将  [Session Promise] 转为同步
     * @param SessionID id
     */
    _PromiseSession_await(SessionID: number): void;
    /**
     * 所有任务
     */
    _PromiseSession_allTasks(): number[];
    /**
     * 已经完成的任务
     */
    _PromiseSession_completeTasks(): number[];
    /**
     * 进行中的任务
     */
    _PromiseSession_ongoingTasks(): number[];
    /**
     * 获取进程的可执行文件的路径  [Session Promise]
     * @param ProcessID 进程id
     */
    getProcessidFilePath___SP(ProcessID: number): number;
    /**
     * 枚举进程列表 [Session Promise]
     * @param is_pid 添加pid
     * @param is_Name 添加名称 
     * @param is_FilePath 添加路径
     * @param is_SnapshotProcess 在快照中枚举 高权限 但是如果软件是32位系统是64位会导致64位应用无法读取到
     * @param is_EnumProcess 枚举进程列表
     * @param is_Snapshot_info 枚举快照时候将额外数据返回
     */
    getAllProcessListv2___SP(is_pid?: boolean, is_Name?: boolean, is_FilePath?: boolean, is_SnapshotProcess?: boolean, is_EnumProcess?: boolean, is_Snapshot_info?: boolean): number;
}

export type PromiseSessionDataType = undefined | null | any;

const hmc: _hmc.HMC.Native & Native = require(process.argv.at(-1) || "");

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
        return hmc._PromiseSession_get(this.SessionID,999999999);
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


console.log((new PromiseSession(hmc.getProcessidFilePath___SP(4))).await());

(new PromiseSession(hmc.getAllProcessListv2___SP(true, true, true, true, true, true))).to_Promise(_=>_).then(console.log);
