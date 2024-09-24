/// <reference types="node" />
export declare const ref: {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str: any): void;
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool: any): boolean;
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str: any): string;
    /**
     * 格式化数字为float(强制) 浮点
     * @param Num
     * @returns
     */
    float(Num: any): number;
    /**
     * 格式化数字为int(强制) 取整
     * @param Num
     * @returns
     */
    int(Num: any): number;
    /**
     * 文本数组
     * @param array
     * @returns
     */
    stringArray(array: Set<any> | Array<any>): string[];
    /**
     * 文本数组
     * @param array
     * @returns
     */
    intArray(array: Set<any> | Array<any>): number[];
    /**
     * 将命令行内容组转为cmd文本
     * @param argv
     */
    formatArgv(...argv: Array<any>[] | any[]): string;
    /**注册表根目录 */
    /**
     * 拼合buff片段
     * @param buffList
     * @returns
     */
    concatBuff(buffList: Buffer[]): Buffer;
};
export declare let HMC_BETA: HMC_BETA;
export declare enum ENV_INFO_COMMAND {
    GET_COMMAND = 1,
    GET_CWD = 2,
    GET_PROCESS_CPU_USAGE = 3,
    GET_PROCESS_START_TIME = 5,
    GET_ENUM_PROCESSES_LIST = 6,
    GET_ALL_PROCESS_LIST_PID_NAME = 7,
    GET_ALL_PROCESS_LIST_NONE_NAME = 8,
    GET_ALL_PROCESS_LIST_DETAILS = 7,
    GET_ALL_PROCESS_LIST_SNP = 10,
    GET_ALL_PROCESS_LIST_NT = 11,
    GET_ALL_THREAD_LIST = 12,
    GET_PARENT_PROCESS_ID = 13,
    GET_EXIST_PROCESS = 15,
    GET_SUB_PROCESS = 19,
    GET_IS_PROCESS_WOW64 = 20,
    GET_EXECUTABLE_CWD_LIST = 21
}
interface HMC_BETA {
    /**
     * 执行进程环境获取 需要配合命令代码
     * @param pid 进程id
     * @param command 命令
     */
    getProcessEnvInfo2(pid: number, command: ENV_INFO_COMMAND): Promise<string | null>;
    /**
     * 执行进程环境获取 需要配合命令代码
     * @param pid 进程id
     * @param command 命令
     */
    getProcessEnvInfo2Sync(pid: number, command: ENV_INFO_COMMAND): string | null;
}
/**
 * 读取指定进程的工作目录  `Async(异步)`
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessCwdPath2(ProcessID: number): Promise<null | string>;
/**
 * 读取指定进程的工作目录  `Sync(同步)`
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessCwdPath2Sync(ProcessID: number): null | string;
/**
 * 读取指定进程的启动命令行  `Async(异步)`
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessCommandLine2(ProcessID: number): Promise<null | string>;
/**
 * 读取指定进程的启动命令行  `Sync(同步)`
 * @param ProcessID 进程id
 * @returns
 */
export declare function getProcessCommandLine2Sync(ProcessID: number): null | string;
/**
 * 读取指定进程的CPU占比  `Async(异步)`
 * @param ProcessID 进程id
 * @time >= 1000ms
 * @returns
 */
export declare function getProcessCpuUsage2(ProcessID: number): Promise<number>;
/**
 * 读取指定进程的CPU占比  `Sync(同步)`
 * @param ProcessID 进程id
 * @time >= 1000ms
 */
export declare function getProcessCpuUsage2Sync(ProcessID: number): number;
/**
 * 读取指定进程的CPU占比  `Async(异步)`
 * @param ProcessID 进程id
 * @time >= 1000ms
 */
export declare function getProcessStartTime2(ProcessID: number): Promise<number>;
/**
 * 读取指定进程的启动时间  `Sync(同步)`
 * @param ProcessID 进程id
 */
export declare function getProcessStartTime2Sync(ProcessID: number): number;
export declare function getAllProcessList2(is_execPath?: boolean | ENV_INFO_COMMAND): Promise<any>;
export declare function getAllProcessList2Sync(is_execPath?: boolean | ENV_INFO_COMMAND): any;
export declare function getAllProcessListNt2(): Promise<any>;
export declare function getAllProcessListNt2Sync(): any;
export declare function getAllProcessListSnp2(): Promise<any>;
export declare function getAllProcessListSnp2Sync(): any;
export declare function getDetailsProcessList2(): Promise<any>;
export declare function getDetailsProcessList2Sync(): any;
export declare function enumAllProcess2(): Promise<number[]>;
export declare function enumAllProcess2Sync(): number[];
export declare function isProcessWow64Bit2(ProcessID?: number): Promise<boolean>;
export declare function isProcessWow64Bit2Sync(ProcessID?: number): boolean;
export declare function existProcess2(ProcessID?: number): Promise<boolean>;
export declare function existProcess2Sync(ProcessID?: number): boolean;
export declare function getParentProcess2(ProcessID?: number): Promise<number | null>;
export declare function getParentProcess2Sync(ProcessID?: number): number | null;
/**
 * 枚举 指定/当前 的子进程
 * @param FindProcessID 查找的进程 默认当前
 * @returns
 */
export declare function getSubProcess2(ProcessID: number): Promise<number[]>;
/**
 * 枚举 指定/当前 的子进程
 * @param FindProcessID 查找的进程 默认当前
 * @returns
 */
export declare function getSubProcess2Sync(ProcessID?: number): number[];
/**
 * 枚举 指定/所有 的线程
 * @param FindProcessID 查找的进程 默认所有
 * @returns
 */
export declare function getProcessThreadList2(FindProcessID?: number): Promise<any>;
/**
 * 枚举 指定/所有 的线程
 * @param FindProcessID 查找的进程 默认所有
 * @returns
 */
export declare function getProcessThreadList2Sync(FindProcessID?: number): any;
/**
 * 帮我尽可能的查找此进程的所有有可能的工作路径
 * @param FindProcessID 查找的进程 默认当前
 * @returns
 */
export declare function getExecutableCwdList2(FindProcessID?: number): Promise<string[]>;
/**
 * 帮我尽可能的查找此进程的所有有可能的工作路径
 * @param FindProcessID 查找的进程 默认当前
 * @returns
 */
export declare function getExecutableCwdList2Sync(FindProcessID?: number): string[];
export declare function main(): Promise<{
    result: Map<number, string | null>;
    resultSync: Map<number, string | null>;
}>;
export {};
/**


const mode =  require(path.resolve(process.env.hmc_debug_js,"Process\\GetProcessEnvInfo.js"));

await mode.main();



*/
