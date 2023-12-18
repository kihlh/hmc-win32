import type { HMC } from "../../../mian/hmc";
export interface Native {
    /**
     * 获取进程列表（枚举法）
     * - 枚举是最快的 最安全的 不会出现遗漏
     * @module 异步
     * @time  fn() 9.691ms     fn(true)61.681ms
     * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
     * @returns
     */
    getAllProcessList: (is_execPath?: boolean) => Promise<string> | number;
    /**
     * 获取进程列表（枚举法）
     * - 枚举是最快的 最安全的 不会出现遗漏
     * @module 同步
     * @time  fn() 11.147ms     fn(true)44.633ms
     * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
     * @returns
     */
    getAllProcessListSync: (is_execPath?: boolean) => string;
    /**
     * 获取进程列表 (快照法)
     * - (一般用来枚举进程树)
     * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
     * @module 异步
     * @time 66.428ms
     * @returns
     */
    getAllProcessListSnp: () => Promise<string> | number;
    /**
     * 获取进程列表 (快照法)
     * - (一般用来枚举进程树)
     * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
     * @module 同步
     * @time 66.428ms
     * @returns
     */
    getAllProcessListSnpSync: () => string;
    /**
     * 获取进程列表 (内核法)
     * - (可以获取内核软件和系统服务的名称)
     * - 请注意 内核法有可能被杀毒软件拦截
     * - 有概率第一次获取时失败
     * @module 异步
     * @time 30.542ms
     * @returns
     */
    getAllProcessListNt: () => Promise<string> | number;
    /**
     * 获取进程列表 (内核法)
     * - (可以获取内核软件和系统服务的名称)
     * - 请注意 内核法有可能被杀毒软件拦截
     * - 有概率第一次获取时失败
     * @module 同步
     * @time 30.542ms
     * @returns
     */
    getAllProcessListNtSync: () => string;
    /**
     * 获取指定进程的cpu百分比 (10% -> 10.02515102152)
     * @module 异步
     * @time 1000ms+
     * @param pid
     */
    getProcessCpuUsage(pid: number): Promise<number>;
    /**
     * 获取指定进程的cpu百分比 (10% -> 10.02515102152)
     * @module 同步
     * ! 请注意此函数会阻塞进程最少1000ms 因为运算cpu占比需要一秒内进行两次对比
     * @param pid 进程id
     */
    getProcessCpuUsageSync(pid: number): number;
    /**
     * 获取指定进程的文件路径
     * @module 异步
     * @param pid 进程id
     */
    getProcessFilePath(pid: number): Promise<string | null>;
    /**
     * @module 同步
     * @param pid 进程id
     */
    getProcessFilePathSync(pid: number): string | null;
}
/**
   * 获取进程列表 (快照法)
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步
   * @time 66.428ms
   * @returns
   */
export declare function getAllProcessListSnp2(callback: (data_list: Array<HMC.PROCESSENTRY_V2>, err: null | Error) => void): void;
export declare function getAllProcessListSnp2(): Promise<Array<HMC.PROCESSENTRY_V2>>;
/**
   * 获取进程列表 (快照法)   带有一个临时缓冲 在1.2秒内提供高速读取
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步
   * @time 66.428ms
   * @returns
   */
export declare function getAllProcessListSnpSession2(callback: (data_list: Array<HMC.PROCESSENTRY_V2>, err: null | Error) => void): void;
export declare function getAllProcessListSnpSession2(): Promise<Array<HMC.PROCESSENTRY_V2>>;
/**
   * 获取进程列表 (快照法)   带有一个临时缓冲 在1.2秒内提供高速读取
   * - (一般用来枚举进程树)
   * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
   * @module 异步
   * @time 66.428ms
   * @returns
   */
export declare function getAllProcessListSnpSession2Sync(): Array<HMC.PROCESSENTRY_V2>;
/**
 * 获取进程列表 (内核法)
 * - (可以获取内核软件和系统服务的名称)
 * - 请注意 内核法有可能被杀毒软件拦截
 * - 有概率第一次获取时失败
 * @module 异步
 * @time 30.542ms
 * @returns
 */
export declare function getAllProcessListNt2(callback: (data_list: Array<HMC.PSYSTEM_PROCESS_INFORMATION & {
    name: string;
    pid: number;
}> | null, err: null | Error) => void): void;
export declare function getAllProcessListNt2(): Promise<Array<HMC.PSYSTEM_PROCESS_INFORMATION & {
    name: string;
    pid: number;
}>>;
/**
 * 获取进程列表（枚举法）
 * - 枚举是最快的 最安全的 不会出现遗漏
 * @module 异步
 * @time  fn() 9.691ms     fn(true)61.681ms
 * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
 * @returns
 */
export declare function getAllProcessList2(callback: ((data_list: Array<{
    pid: number;
}> | null, err: null | Error) => void)): void;
export declare function getAllProcessList2(callback: ((data_list: Array<{
    pid: number;
    name: string;
    path: string;
}> | null, err: null | Error) => void), is_execPath: true): void;
export declare function getAllProcessList2(is_execPath: true): Promise<Array<{
    pid: number;
    name: string;
    path: string;
}>>;
export declare function getAllProcessList2(): Promise<Array<{
    pid: number;
}>>;
/**
 * 获取进程列表（枚举法）
 * - 枚举是最快的 最安全的 不会出现遗漏
 * @module 同步
 * @time  fn() 11.147ms     fn(true)44.633ms
 * @param is_execPath 需要解析可执行文件路径 (获取延时50ms左右)
 * @returns
 */
export declare function getAllProcessList2Sync(is_execPath?: true): Array<{
    pid: number;
    name: string;
    path: string;
}>;
export declare function getAllProcessList2Sync(): Array<{
    pid: number;
}>;
/**
 * 获取进程列表 (内核法)
 * - (可以获取内核软件和系统服务的名称)
 * - 请注意 内核法有可能被杀毒软件拦截
 * - 有概率第一次获取时失败
 * @module 同步
 * @time 30.542ms
 * @returns
 */
export declare function getAllProcessListNt2Sync(): Array<HMC.PSYSTEM_PROCESS_INFORMATION & {
    name: string;
    pid: number;
}>;
/**
 * 获取进程列表 (快照法)
 * - (一般用来枚举进程树)
 * - ?请注意 如果可执行文件是32位而系统是64位将获取不到64位进程的信息
 * @module 同步
 * @time 66.428ms
 * @returns
 */
export declare function getAllProcessListSnp2Sync(): Array<HMC.PROCESSENTRY_V2>;
/**
 * 获取匹配进程的 父进程信息
 * @param Process 需要被搜索的子进程 名称/pid/正则名称
 * @param is_SessionCache 是否启用缓冲区以提高检索速度 （缓冲区有效时间1.2秒）
 * @returns
 */
export declare function getProcessParentProcessMatch2(Process: string | RegExp, is_SessionCache?: boolean): Promise<Array<HMC.PROCESSENTRY_V2>>;
export declare function getProcessParentProcessMatch2(Process: number, is_SessionCache?: boolean): Promise<HMC.PROCESSENTRY_V2>;
/**
 * 获取匹配进程的 父进程信息
 * @param Process 需要被搜索的子进程 名称/pid/正则名称
 * @param is_SessionCache 是否启用缓冲区以提高检索速度 （缓冲区有效时间1.2秒）
 * @returns
 */
export declare function getProcessParentProcessMatch2Sync(Process: string | RegExp, is_SessionCache?: boolean): Array<HMC.PROCESSENTRY_V2>;
export declare function getProcessParentProcessMatch2Sync(Process: number, is_SessionCache?: boolean): HMC.PROCESSENTRY_V2 | null;
/**
 * 获取指定进程的可执行文件路径
 * @param ProcessID 进程id
 * @param callback 回调函数 如果没有则返回一个 Promise
 * @returns
 */
export declare function getProcessFilePath2(ProcessID: number, callback: (path: string | null, err: null | Error) => void): void;
export declare function getProcessFilePath2(ProcessID: number): Promise<string | null>;
/**
 * 获取指定进程的可执行文件路径
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessFilePath2Sync(ProcessID: number): string | null;
/**
 * 获取一个带有exe path 的进程列表
 * @returns
 */
export declare function getDetailsProcessList2(): {
    pid: number;
    name: string;
    path: string;
}[];
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @param is_SessionCache  是否使用缓存提高速度
 * @returns
 */
export declare function getProcessNameSnp2Sync(ProcessID: number, is_SessionCache?: boolean): string | null;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @param is_SessionCache  是否使用缓存提高速度
 * @returns
 */
export declare function getProcessNameSnp2(ProcessID: number, is_SessionCache?: boolean): Promise<null | string>;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessNameNt2Sync(ProcessID: number): string | null;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessNameNt2(ProcessID: number): Promise<null | string>;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessName2(ProcessID: number): Promise<null | string>;
/**
 * 获取进程名称 (快照法)
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessName2Sync(ProcessID: number): string | null;
/**
 * 按照名称搜索进程
 * @param ProcessName
 * @returns
 */
export declare function findProcess2(ProcessName: string | RegExp | number, isMacthFile?: boolean): Promise<{
    pid: number;
    name: string | null;
    path: string | null;
}[]>;
/**
 * 按照名称搜索进程
 * @param ProcessName
 * @returns
 */
export declare function findProcess2Sync(ProcessName: string | RegExp | number, isMacthFile?: boolean): Array<{
    pid: number;
    name: string;
    path: string;
}>;
