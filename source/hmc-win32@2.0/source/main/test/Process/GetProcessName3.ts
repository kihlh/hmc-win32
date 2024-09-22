export let HMC_BETA: HMC_BETA = require(String(process.env.mode));
export let HMC_X64 = require("F:/source/module/hmc-win32/bin/HMC_x64.node");

enum ProcessNameGetType {
    // 查找所有名字
    GET_AII = 1,
    // 使用内核法查找
    GET_NT = 2,
    // 获取进程快照的名字
    GET_SNP = 3,
    // 找到时就停下 [默认]
    GET_FIND = 5,
    // 找模块名
    GET_MODE = 7,
    // 默认 找到时就停下 
    GET_DEFAULT = 0,
    // 即便是从可执行文件中路径获取文件名也行
    GET_FILE_NAME = 8
};

const TYPE_TEST: { [key: string]: ProcessNameGetType } = {
    "▶️ 我全都要🤏": ProcessNameGetType.GET_AII,
    "▶️ 内核名称": ProcessNameGetType.GET_NT,
    "▶️ 进程快照名": ProcessNameGetType.GET_SNP,
    "▶️ 找到就行": ProcessNameGetType.GET_FIND,
    "▶️ 模块名称": ProcessNameGetType.GET_MODE,
    "▶️ 可执行文件 文件名": ProcessNameGetType.GET_FILE_NAME,
    "▶️ 没有参数[默认]": 0,
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
    // GetProcessName3(pid: number, type: ProcessNameGetType.GET_AII):  Promise<string | null>;
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

export async function main() {



    const result_list: { [key: string]: any } = {};
    const result_list_JSON: { [key: string]: Array<null | string | string[]> } = {};


    for (const KEY_GET_TYPE in TYPE_TEST) {

        console.time(KEY_GET_TYPE);
        const ProcessList = JSON.parse(await HMC_X64.getAllProcessList());

        console.log(`[${KEY_GET_TYPE}] size -> `, ProcessList.length);

        for (let index = 0; index < ProcessList.length; index++) {
            const { pid } = ProcessList[index];

            const temp = HMC_BETA.getProcessName2(pid, TYPE_TEST[KEY_GET_TYPE])
                .then(data => {
                    const store = result_list_JSON[KEY_GET_TYPE] || [];
                    store.push(data);
                    result_list_JSON[KEY_GET_TYPE] = store;
                    return data;
                }).catch(() => {
                    const store = result_list_JSON[KEY_GET_TYPE] || [];
                    store.push(null);
                    result_list_JSON[KEY_GET_TYPE] = store;
                })
                ;

            ProcessList[index] = temp;
        }

        const result = await Promise.allSettled(ProcessList);
        console.timeEnd(KEY_GET_TYPE);

        result_list[KEY_GET_TYPE] = result;
        console.log(`[${KEY_GET_TYPE}] result -> `, result);

        console.log("?----------------------------------------------------------------");
    }

    return { result_list, result_list_JSON }

};


/**


const mode =  require(path.resolve(process.env.hmc_debug_js,"Process\\GetProcessName3.js"));

await mode.main();
 

 */

/*
[▶️ 我全都要🤏] size ->  353
GetProcessName3.js:62 ▶️ 我全都要🤏: 18117.739013671875 ms
node:internal/console/constructor:625 ▶️ 我全都要🤏: 18.118s
GetProcessName3.js:64 [▶️ 我全都要🤏] result ->  (353) [{…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, …]


?----------------------------------------------------------------
GetProcessName3.js:45 [▶️ 内核名称] size ->  362
GetProcessName3.js:62 ▶️ 内核名称: 10609.31103515625 ms
node:internal/console/constructor:625 ▶️ 内核名称: 10.609s
GetProcessName3.js:64 [▶️ 内核名称] result ->  (362) [{…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, …]


?----------------------------------------------------------------
GetProcessName3.js:45 [▶️ 进程快照名] size ->  354
GetProcessName3.js:62 ▶️ 进程快照名: 11299.777099609375 ms
node:internal/console/constructor:625 ▶️ 进程快照名: 11.299s
GetProcessName3.js:64 [▶️ 进程快照名] result ->  (354) [{…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, …]


?----------------------------------------------------------------
GetProcessName3.js:45 [▶️ 找到就行] size ->  352
GetProcessName3.js:62 ▶️ 找到就行: 8318.43115234375 ms
node:internal/console/constructor:625 ▶️ 找到就行: 8.319s
GetProcessName3.js:64 [▶️ 找到就行] result ->  (352) [{…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, …]


?----------------------------------------------------------------
GetProcessName3.js:45 [▶️ 模块名称] size ->  352
GetProcessName3.js:62 ▶️ 模块名称: 8548.23486328125 ms
node:internal/console/constructor:625 ▶️ 模块名称: 8.548s
GetProcessName3.js:64 [▶️ 模块名称] result ->  (352) [{…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, …]


?----------------------------------------------------------------
GetProcessName3.js:45 [▶️ 没有参数[默认]] size ->  353
GetProcessName3.js:62 ▶️ 没有参数[默认]: 9290.088134765625 ms
node:internal/console/constructor:625 ▶️ 没有参数[默认]: 9.290s
GetProcessName3.js:64 [▶️ 没有参数[默认]] result ->  (353) [{…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, {…}, …]


?----------------------------------------------------------------
{result_list: {…}, result_list_JSON: {…}}

*/