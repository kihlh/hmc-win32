export declare let HMC_BETA: HMC_BETA;
export declare let HMC_X64: any;
interface HMC_BETA {
    /**
     * 获取指定进程的可执行文件路径
     * @param pid 进程id
     * @param isEnumListExists 是否必须出现在进程列表中的
     * @default false
     * @param isSnapshotName 获取失败时获取进程名称
     * @default false
     */
    getProcessFilePath2(pid: number, isEnumListExists?: boolean, isSnapshotName?: boolean): Promise<string | null>;
    /**
     * 获取指定进程的可执行文件路径
     * @param pid 进程id
     * @param isEnumListExists 是否必须出现在进程列表中的
     * @default false
     * @param isSnapshotName 获取失败时获取进程名称
     * @default false
     */
    getProcessFilePath2Sync(pid: number, isEnumListExists?: boolean, isSnapshotName?: boolean): string | null;
}
export declare function main(): Promise<{
    result: Map<number, string | null>;
    resultSync: Map<number, string | null>;
}>;
export declare function main2AddSnapshotName(): Promise<{
    result: Map<number, string | null>;
    resultSync: Map<number, string | null>;
}>;
export {};
/**


const mode =  require(path.resolve(process.env.hmc_debug_js,"Process\\getProcessFilePath2.js"));

await mode.main();
await mode.main2AddSnapshotName();


getProcessFilePath2: 53.5361328125 ms
node:internal/console/constructor:625 getProcessFilePath2: 53.825ms


getProcessFilePath2.js:33 getProcessFilePath2Sync: 77.722900390625 ms
node:internal/console/constructor:625 getProcessFilePath2Sync: 77.851ms




await mode.main2AddSnapshotName();

getProcessFilePath2: 1250.31982421875 ms
node:internal/console/constructor:625 getProcessFilePath2: 1.251s

getProcessFilePath2.js:65 getProcessFilePath2Sync: 3608.93994140625 ms
node:internal/console/constructor:625 getProcessFilePath2Sync: 3.609s

*/ 
