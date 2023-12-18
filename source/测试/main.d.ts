export interface Native {
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
