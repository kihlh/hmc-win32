export interface Native {
}
/**
 * 获取指定进程的工作目录
 * @time 5.449ms
 * @description 由于跨进程权限问题 不保证获取得到
 * !此功能需要读取进程内存
 * @module 异步async
 * @param pid
 */
export declare function getProcessCwd2(pid: number): Promise<string | null>;
/**
 * 获取指定进程的工作目录
 * @time 0.435ms
 * @description 由于跨进程权限问题 不保证获取得到
 * !此功能需要读取进程内存
 * @module 同步Sync
 * @param pid
 */
export declare function getProcessCwd2Sync(pid: number): string | null;
/**
 * 获取指定进程得出命令行
 * @time 1.095ms
 * @description 由于跨进程权限问题 不保证获取得到
 * ?此功能在win8及以下系统 需要读取进程内存
 * @module 异步async
 * @param pid 进程id
 */
export declare function getProcessCommand2(pid: number): Promise<string>;
/**
 * 获取指定进程得出命令行
 * @time 0.386ms
 * @description 由于跨进程权限问题 不保证获取得到
 * ?此功能在win8及以下系统 需要读取进程内存
 * @module 同步Sync
 * @param pid
 */
export declare function getProcessCommand2Sync(pid: number): string | null;
/**
 * 限制鼠标光标可移动范围 (异步)
 * @description 可以调用 stop 提前结束
 * ?最高不允许超过30000ms (30秒) 最低不允许低于31ms
 * ?范围为正方形 如果没有设置right与bottom的值则将限制为1x1的正方形 (不可动)
 * @param ms 本次限制的时间
 * @param x 限制左边初始化点的位置
 * @param y 限制顶部初始化点的位置
 * @param right 允许的范围(左边到右边部)
 * @param bottom 允许光标移动的范围(顶到底部)
 */
export declare function setLimitMouseRange(ms: number, x: number, y: number, right?: number, bottom?: number): {
    ms: number;
    x: number;
    y: number;
    right: number;
    bottom: number;
    closed: boolean;
    /**
     * 停止本次
     * @returns
     */
    close(): boolean;
    /**
     * 是否正在执行中
     * @returns
     */
    has(): boolean;
};
