export interface Native {
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
