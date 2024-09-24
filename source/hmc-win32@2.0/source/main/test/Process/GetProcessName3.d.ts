export declare let HMC_BETA: HMC_BETA;
export declare let HMC_X64: any;
declare enum ProcessNameGetType {
    GET_AII = 1,
    GET_NT = 2,
    GET_SNP = 3,
    GET_FIND = 5,
    GET_MODE = 7,
    GET_DEFAULT = 0,
    GET_FILE_NAME = 8
}
interface HMC_BETA {
    /**
     * 获取进程名称
     * @param pid 进程id
     * @param type 深度类型
     * @default GET_FIND
     * - GET_AII 查找所有名字并以\0分隔形式返回
     * - GET_NT 查找进程在内核中的名字
     * - GET_SNP 获取进程快照的名字(如果当前node载体是32位将找不到系统中64位应用)
     * - GET_FIND 找到时就停下 [默认]
     * - GET_MODE 找模块名(最快)
     * @returns
     */
    getProcessName2(pid: number): Promise<string | null>;
    getProcessName2(pid: number, type: ProcessNameGetType): Promise<string | null>;
    getProcessName2(pid: number, type?: unknown): Promise<unknown>;
    /**
     * 获取进程名称
     * @param pid 进程id
     * @param type 深度类型
     * @default GET_FIND
     * - GET_AII 查找所有名字并以\0分隔形式返回
     * - GET_NT 查找进程在内核中的名字
     * - GET_SNP 获取进程快照的名字(如果当前node载体是32位将找不到系统中64位应用)
     * - GET_FIND 找到时就停下 [默认]
     * - GET_MODE 找模块名(最快)
     * @returns
     */
    getProcessName2Sync(pid: number): string | null;
    getProcessName2Sync(pid: number, type: ProcessNameGetType): string | null;
    getProcessName2Sync(pid: number, type?: unknown): unknown;
}
export declare function main(): Promise<{
    result_list: {
        [key: string]: any;
    };
    result_list_JSON: {
        [key: string]: (string | string[] | null)[];
    };
}>;
export {};
/**


const mode =  require(path.resolve(process.env.hmc_debug_js,"Process\\GetProcessName3.js"));

await mode.main();
 

 */
