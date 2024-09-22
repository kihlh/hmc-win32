export let HMC_BETA: HMC_BETA = require(String(process.env.mode));
export let HMC_X64 = require("F:/source/module/hmc-win32/bin/HMC_x64.node");


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

export async function main() {

    const PromList: Promise<any>[] = [];
    const ProcessList = JSON.parse(await HMC_X64.getAllProcessList());
    const result: Map<number, string | null> = new Map();

    console.time("getProcessFilePath2");
    for (let index = 0; index < ProcessList.length; index++) {
        const { pid } = ProcessList[index];

        const temp = HMC_BETA.getProcessFilePath2(pid)
            .then(data => {
                result.set(pid, data);
                return data;
            })
            .catch(data => {
                result.set(pid, data);
                return data;
            })
            ;

        PromList.push(temp);
    }

    await Promise.allSettled(PromList);

    console.timeEnd("getProcessFilePath2");




    const resultSync: Map<number, string | null> = new Map();

    console.time("getProcessFilePath2Sync");
    for (let index = 0; index < ProcessList.length; index++) {
        const { pid } = ProcessList[index];

        const temp = HMC_BETA.getProcessFilePath2Sync(pid);
        resultSync.set(pid, temp);
    }


    console.timeEnd("getProcessFilePath2Sync");


    return { result, resultSync };
};



export async function main2AddSnapshotName() {

    const PromList: Promise<any>[] = [];
    const ProcessList = JSON.parse(await HMC_X64.getAllProcessList());
    const result: Map<number, string | null> = new Map();

    console.time("getProcessFilePath2");
    for (let index = 0; index < ProcessList.length; index++) {
        const { pid } = ProcessList[index];

        const temp = HMC_BETA.getProcessFilePath2(pid,true,true)
            .then(data => {
                result.set(pid, data);
                return data;
            })
            .catch(data => {
                result.set(pid, data);
                return data;
            })
            ;

        PromList.push(temp);
    }

    await Promise.allSettled(PromList);

    console.timeEnd("getProcessFilePath2");




    const resultSync: Map<number, string | null> = new Map();

    console.time("getProcessFilePath2Sync");
    for (let index = 0; index < ProcessList.length; index++) {
        const { pid } = ProcessList[index];

        const temp = HMC_BETA.getProcessFilePath2Sync(pid,true,true);
        resultSync.set(pid, temp);
    }


    console.timeEnd("getProcessFilePath2Sync");


    return { result, resultSync };
};



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