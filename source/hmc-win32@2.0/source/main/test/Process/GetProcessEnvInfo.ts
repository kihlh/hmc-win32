

export const ref = {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str: any) {
        // return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
    },
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool: any) {
        return bool ? true : false;
    },
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str: any) {
        return String(Str || "");
    },
    /**
     * 格式化数字为float(强制) 浮点
     * @param Num
     * @returns
     */
    float(Num: any): number {
        if (!Num) return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num?.valueOf();
        }

        if (typeof Num == "string") {
            Num = parseFloat(Num);
            if (isNaN(Num)) return 0;

            if (Num >= Infinity) {
                Num = 999999999999999.999;
            }
            if (Num <= -Infinity) {
                Num = -999999999999999.999;
            }

            return Num;
        }

        if (typeof Num == "number" && !isNaN(Num)) return Num;
        // true == 1
        if (Num && typeof Num == "boolean") Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean") Num = 0;
        if (Num >= Infinity) {
            Num = 999999999999999.999;
        }
        if (Num <= -Infinity) {
            Num = -999999999999999.999;
        }
        return Num;
    },
    /**
     * 格式化数字为int(强制) 取整
     * @param Num
     * @returns
     */
    int(Num: any): number {
        if (!Num) return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num?.valueOf();
        }
        // 取整
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num)) return Num;
        // true == 1
        if (Num && typeof Num == "boolean") Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean") Num = 0;
        if (Num >= Infinity) {
            Num = 999999999999999;
        }
        if (Num <= -Infinity) {
            Num = -999999999999999;
        }
        return Num;
    },
    /**
     * 文本数组
     * @param array 
     * @returns 
     */
    stringArray(array: Set<any> | Array<any>) {
        let dataList: string[] = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(this.string(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(this.string(cout));
            }
        }
        return dataList;
    },
    /**
     * 文本数组
     * @param array 
     * @returns 
     */
    intArray(array: Set<any> | Array<any>) {
        let dataList: number[] = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(this.int(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(this.int(cout));
            }
        }
        return dataList;
    },

    /**
     * 将命令行内容组转为cmd文本
     * @param argv 
     */
    formatArgv(...argv: Array<any>[] | any[]): string {
        let argvs: string[] = [];
        let argvsResult: string[] = [];

        // 获取
        for (let index = 0; index < argv.length; index++) {
            const cout = argv[index];
            if (Array.isArray(cout)) {
                for (let cout_index = 0; cout_index < cout.length; cout_index++) {
                    const cout2 = cout[cout_index];
                    argvs.push(this.string(cout2));
                }
                continue;
            }
            argvs.push(this.string(cout));
        }

        // 处理
        for (let index = 0; index < argvs.length; index++) {
            let cout = argvs[index];
            if (!cout) continue;
            if (cout.match(/['"]/)) {
                cout = cout.replace(/(\\)?["']/g, "\\$0");
            }
            if (cout.match(" ")) {
                cout = `"${cout}"`;
            }
            if (cout.match(/[\n\r]/)) {
                cout = cout.replace(/(\n|\r|\r\n)/g, "$0^");
            }
            argvsResult.push(cout);
        }
        return argvsResult.join(" ");
    },
    /**注册表根目录 */

    /**
     * 拼合buff片段
     * @param buffList 
     * @returns 
     */
    concatBuff(buffList: Buffer[]): Buffer {
        let buffSize = 0;
        for (let index = 0; index < buffList.length; index++) {
            const buff = buffList[index];
            buffSize = buffSize + buff.byteLength;
        }
        let ResponseData = Buffer.concat([...buffList], buffSize);
        return ResponseData;
    }
};


export let HMC_BETA: HMC_BETA = require(String(process.env.mode));



export enum ENV_INFO_COMMAND {

    // getProcessCommandLine2   `string`
    GET_COMMAND = 1,
    // getProcessCwdPath2 `string`
    GET_CWD = 2,
    // getProcessCpuUsage2 `float`
    GET_PROCESS_CPU_USAGE = 3,
    // getProcessStartTime2 `number`
    GET_PROCESS_START_TIME = 5,
    // EnumProcesses `json`
    GET_ENUM_PROCESSES_LIST = 6,
    // getAllProcessList2(true) `json`
    GET_ALL_PROCESS_LIST_PID_NAME = 7,
    // getAllProcessList2 `json`
    GET_ALL_PROCESS_LIST_NONE_NAME = 8,
    // getDetailsProcessList2 `json`
    GET_ALL_PROCESS_LIST_DETAILS = 7,
    // getAllProcessListSnp2 `json`
    GET_ALL_PROCESS_LIST_SNP = 10,
    // getAllProcessListNt2 `json`
    GET_ALL_PROCESS_LIST_NT = 11,
    //  getProcessThreadList `json`
    GET_ALL_THREAD_LIST = 12,
    //  getParentProcessID2 `long`
    GET_PARENT_PROCESS_ID = 13,
    // existProcess `bool`
    GET_EXIST_PROCESS = 15,
    // getSubProcess `Array<int>`
    GET_SUB_PROCESS = 19,
    // isProcessWow64 `bool`
    GET_IS_PROCESS_WOW64 = 20,
    // getExecutableCwdList `Array<string>`
    GET_EXECUTABLE_CWD_LIST = 21,
};

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
export async function getProcessCwdPath2(ProcessID: number): Promise<null | string> {
    return HMC_BETA.getProcessEnvInfo2(ref.int(ProcessID), ENV_INFO_COMMAND.GET_CWD)
        .then(data => {
            return data || ref.string(data);
        })
        .catch(err => {
            return null;
        })
        ;
}

/**
 * 读取指定进程的工作目录  `Sync(同步)`
 * @param ProcessID 进程id
 * @returns 
 */
export function getProcessCwdPath2Sync(ProcessID: number): null | string {
    return HMC_BETA.getProcessEnvInfo2Sync(ref.int(ProcessID), ENV_INFO_COMMAND.GET_CWD);
}

/**
 * 读取指定进程的启动命令行  `Async(异步)`
 * @param ProcessID 进程id
 * @returns 
 */
export async function getProcessCommandLine2(ProcessID: number): Promise<null | string> {
    return HMC_BETA.getProcessEnvInfo2(ref.int(ProcessID), ENV_INFO_COMMAND.GET_COMMAND)
        .then(data => {
            return data || ref.string(data);
        })
        .catch(err => {
            return null;
        })
        ;
}

/**
 * 读取指定进程的启动命令行  `Sync(同步)`
 * @param ProcessID 进程id
 * @returns 
 */
export function getProcessCommandLine2Sync(ProcessID: number): null | string {
    return HMC_BETA.getProcessEnvInfo2Sync(ref.int(ProcessID), ENV_INFO_COMMAND.GET_COMMAND);
}

/**
 * 读取指定进程的CPU占比  `Async(异步)`
 * @param ProcessID 进程id
 * @time >= 1000ms
 * @returns 
 */
export async function getProcessCpuUsage2(ProcessID: number): Promise<number> {
    return HMC_BETA.getProcessEnvInfo2(ref.int(ProcessID), ENV_INFO_COMMAND.GET_PROCESS_CPU_USAGE)
        .then(data => {
            return ref.float(data);
        })
        .catch(err => {
            return 0;
        })
        ;
}

/**
 * 读取指定进程的CPU占比  `Sync(同步)`
 * @param ProcessID 进程id
 * @time >= 1000ms
 */
export function getProcessCpuUsage2Sync(ProcessID: number): number {
    return ref.float(HMC_BETA.getProcessEnvInfo2Sync(ref.int(ProcessID), ENV_INFO_COMMAND.GET_PROCESS_CPU_USAGE));
}

/**
 * 读取指定进程的CPU占比  `Async(异步)`
 * @param ProcessID 进程id
 * @time >= 1000ms
 */
export async function getProcessStartTime2(ProcessID: number): Promise<number> {
    return HMC_BETA.getProcessEnvInfo2(ref.int(ProcessID), ENV_INFO_COMMAND.GET_PROCESS_START_TIME)
        .then(data => {
            return ref.int(data);
        })
        .catch(err => {
            return 0;
        })
        ;
}

/**
 * 读取指定进程的启动时间  `Sync(同步)`
 * @param ProcessID 进程id
 */
export function getProcessStartTime2Sync(ProcessID: number): number {
    return ref.int(HMC_BETA.getProcessEnvInfo2Sync(ref.int(ProcessID), ENV_INFO_COMMAND.GET_PROCESS_START_TIME));
}

export async function getAllProcessList2(is_execPath?: boolean | ENV_INFO_COMMAND) {
    const {

        GET_ALL_PROCESS_LIST_NT,

        GET_ALL_PROCESS_LIST_DETAILS,
        // 
        GET_ALL_PROCESS_LIST_NONE_NAME,
        // 带路径
        GET_ALL_PROCESS_LIST_PID_NAME,
        // sup 列表
        GET_ALL_PROCESS_LIST_SNP,
        GET_ENUM_PROCESSES_LIST
    } = ENV_INFO_COMMAND;


    let SEND_TYPE = typeof is_execPath == "boolean" ? is_execPath ? GET_ALL_PROCESS_LIST_DETAILS : GET_ALL_PROCESS_LIST_NONE_NAME : GET_ALL_PROCESS_LIST_NONE_NAME;

    const INCLUDES_TYPES = [
        GET_ALL_PROCESS_LIST_NT,
        GET_ALL_PROCESS_LIST_DETAILS,
        GET_ALL_PROCESS_LIST_NONE_NAME,
        GET_ALL_PROCESS_LIST_PID_NAME,
        GET_ALL_PROCESS_LIST_SNP,
        GET_ENUM_PROCESSES_LIST
    ];

    if (typeof is_execPath == "number") {
        if (!INCLUDES_TYPES.includes(is_execPath)) {
            return Promise.reject("An illegal call to the function <getAllProcessList2> has been made.");
        }

        SEND_TYPE = is_execPath;
    }

    try {
        const data = await HMC_BETA.getProcessEnvInfo2(0, SEND_TYPE);
        const result = JSON.parse(data || "[]");

        if (GET_ALL_PROCESS_LIST_NT == SEND_TYPE ||
            GET_ALL_PROCESS_LIST_SNP == SEND_TYPE) {

            for (let index = 0; index < result.length; index++) {
                const element = result[index];
                element.name = element?.szExeFile || element?.ImageName || "";
                element.pid = element?.th32ProcessID || element?.UniqueProcessId || 0;
            }
        }
        return result;
    } catch (err) {
        return [];
    }
}

export function getAllProcessList2Sync(is_execPath?: boolean | ENV_INFO_COMMAND) {
    const {

        GET_ALL_PROCESS_LIST_NT,

        GET_ALL_PROCESS_LIST_DETAILS,
        // 
        GET_ALL_PROCESS_LIST_NONE_NAME,
        // 带路径
        GET_ALL_PROCESS_LIST_PID_NAME,
        // sup 列表
        GET_ALL_PROCESS_LIST_SNP,
        GET_ENUM_PROCESSES_LIST
    } = ENV_INFO_COMMAND;


    let SEND_TYPE = typeof is_execPath == "boolean" ? is_execPath ? GET_ALL_PROCESS_LIST_DETAILS : GET_ALL_PROCESS_LIST_NONE_NAME : GET_ALL_PROCESS_LIST_NONE_NAME;

    const INCLUDES_TYPES = [
        GET_ALL_PROCESS_LIST_NT,
        GET_ALL_PROCESS_LIST_DETAILS,
        GET_ALL_PROCESS_LIST_NONE_NAME,
        GET_ALL_PROCESS_LIST_PID_NAME,
        GET_ALL_PROCESS_LIST_SNP,
        GET_ENUM_PROCESSES_LIST
    ];

    if (typeof is_execPath == "number") {

        if (!INCLUDES_TYPES.includes(is_execPath)) {
            throw new Error("An illegal call to the function <getAllProcessList2> has been made.");
        }

        SEND_TYPE = is_execPath;
    }

    const result = JSON.parse(HMC_BETA.getProcessEnvInfo2Sync(0, SEND_TYPE) || "[]");

    if (GET_ALL_PROCESS_LIST_NT == SEND_TYPE ||
        GET_ALL_PROCESS_LIST_SNP == SEND_TYPE
    ) {

        for (let index = 0; index < result.length; index++) {
            const element = result[index];
            element.name = element?.szExeFile || element?.ImageName || "";
            element.pid = element?.th32ProcessID || element?.UniqueProcessId || 0;
        }
    }

    return result;
}

export function getAllProcessListNt2() {
    return getAllProcessList2(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT);
}

export function getAllProcessListNt2Sync() {
    return getAllProcessList2Sync(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT);
}

export function getAllProcessListSnp2() {
    return getAllProcessList2(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP);
}

export function getAllProcessListSnp2Sync() {
    return getAllProcessList2Sync(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP);
}

export function getDetailsProcessList2() {
    return getAllProcessList2(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS);
}

export function getDetailsProcessList2Sync() {
    return getAllProcessList2Sync(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS);
}

export function enumAllProcess2(): Promise<number[]> {
    return getAllProcessList2(ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST);
}

export function enumAllProcess2Sync(): number[] {
    return getAllProcessList2Sync(ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST);
}

export async function isProcessWow64Bit2(ProcessID?: number) {
    const bool = await HMC_BETA.getProcessEnvInfo2(ref.int(ProcessID || -1),
        ENV_INFO_COMMAND.GET_IS_PROCESS_WOW64);
    return !!ref.int(bool);
}

export function isProcessWow64Bit2Sync(ProcessID?: number) {
    const bool = HMC_BETA.getProcessEnvInfo2Sync(ref.int(ProcessID || -1),
        ENV_INFO_COMMAND.GET_IS_PROCESS_WOW64);
    return !!ref.int(bool);
}


export async function existProcess2(ProcessID?: number) {
    const bool = await HMC_BETA.getProcessEnvInfo2(ref.int(ProcessID || -1),
        ENV_INFO_COMMAND.GET_EXIST_PROCESS);
    return !!ref.int(bool);
}

export function existProcess2Sync(ProcessID?: number) {
    const bool = HMC_BETA.getProcessEnvInfo2Sync(ref.int(ProcessID || -1),
        ENV_INFO_COMMAND.GET_EXIST_PROCESS);
    return !!ref.int(bool);
}

export async function getParentProcess2(ProcessID?: number) {
    const long = await HMC_BETA.getProcessEnvInfo2(ref.int(ProcessID || -1),
        ENV_INFO_COMMAND.GET_PARENT_PROCESS_ID);
    return ref.int(long || 0) || null;
    ;
}

export function getParentProcess2Sync(ProcessID?: number) {
    return ref.int(HMC_BETA.getProcessEnvInfo2Sync(ref.int(ProcessID || -1),
        ENV_INFO_COMMAND.GET_PARENT_PROCESS_ID) || 0) || null;
}

/**
 * 枚举 指定/当前 的子进程
 * @param FindProcessID 查找的进程 默认当前
 * @returns 
 */
export async function getSubProcess2(ProcessID: number) {
    const anyJSON = await HMC_BETA.getProcessEnvInfo2(ref.int(ProcessID || -1),
        ENV_INFO_COMMAND.GET_SUB_PROCESS);
    return JSON.parse(anyJSON || "[]") as number[];
    ;
}

/**
 * 枚举 指定/当前 的子进程
 * @param FindProcessID 查找的进程 默认当前
 * @returns 
 */
export function getSubProcess2Sync(ProcessID?: number): number[] {
    return JSON.parse((HMC_BETA.getProcessEnvInfo2Sync(ref.int(ProcessID || -1),
        ENV_INFO_COMMAND.GET_SUB_PROCESS) || "[]"));
}

/**
 * 枚举 指定/所有 的线程
 * @param FindProcessID 查找的进程 默认所有
 * @returns 
 */
export async function getProcessThreadList2(FindProcessID?: number) {
    const anyJSON = await HMC_BETA.getProcessEnvInfo2(ref.int(FindProcessID || -1),
        ENV_INFO_COMMAND.GET_ALL_THREAD_LIST);
    return JSON.parse(anyJSON || "[]");

}

/**
 * 枚举 指定/所有 的线程
 * @param FindProcessID 查找的进程 默认所有
 * @returns 
 */
export function getProcessThreadList2Sync(FindProcessID?: number) {
    return JSON.parse((HMC_BETA.getProcessEnvInfo2Sync(ref.int(FindProcessID || -1),
        ENV_INFO_COMMAND.GET_ALL_THREAD_LIST) || "[]"));
}

/**
 * 帮我尽可能的查找此进程的所有有可能的工作路径
 * @param FindProcessID 查找的进程 默认当前
 * @returns 
 */
export async function getExecutableCwdList2(FindProcessID?: number):Promise<string[]> {
    const anyJSON = await HMC_BETA.getProcessEnvInfo2(ref.int(FindProcessID || process.pid),
        ENV_INFO_COMMAND.GET_EXECUTABLE_CWD_LIST);
    return JSON.parse(anyJSON || "[]");

}

/**
 * 帮我尽可能的查找此进程的所有有可能的工作路径
 * @param FindProcessID 查找的进程 默认当前
 * @returns 
 */
export function getExecutableCwdList2Sync(FindProcessID?: number):string[] {
    return JSON.parse((HMC_BETA.getProcessEnvInfo2Sync(ref.int(FindProcessID ||process.pid),
        ENV_INFO_COMMAND.GET_EXECUTABLE_CWD_LIST) || "[]"));
}



export async function main() {

    const PromList: Promise<any>[] = [];
    // const ProcessList = JSON.parse(await HMC_X64.getAllProcessList());
    const result: Map<number, string | null> = new Map();



    const resultSync: Map<number, string | null> = new Map();

    return { result, resultSync };
};




/**


const mode =  require(path.resolve(process.env.hmc_debug_js,"Process\\GetProcessEnvInfo.js"));

await mode.main();



*/

