"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.main = exports.getExecutableCwdList2Sync = exports.getExecutableCwdList2 = exports.getProcessThreadList2Sync = exports.getProcessThreadList2 = exports.getSubProcess2Sync = exports.getSubProcess2 = exports.getParentProcess2Sync = exports.getParentProcess2 = exports.existProcess2Sync = exports.existProcess2 = exports.isProcessWow64Bit2Sync = exports.isProcessWow64Bit2 = exports.enumAllProcess2Sync = exports.enumAllProcess2 = exports.getDetailsProcessList2Sync = exports.getDetailsProcessList2 = exports.getAllProcessListSnp2Sync = exports.getAllProcessListSnp2 = exports.getAllProcessListNt2Sync = exports.getAllProcessListNt2 = exports.getAllProcessList2Sync = exports.getAllProcessList2 = exports.getProcessStartTime2Sync = exports.getProcessStartTime2 = exports.getProcessCpuUsage2Sync = exports.getProcessCpuUsage2 = exports.getProcessCommandLine2Sync = exports.getProcessCommandLine2 = exports.getProcessCwdPath2Sync = exports.getProcessCwdPath2 = exports.ENV_INFO_COMMAND = exports.HMC_BETA = exports.ref = void 0;
exports.ref = {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str) {
        // return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
    },
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool) {
        return bool ? true : false;
    },
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str) {
        return String(Str || "");
    },
    /**
     * 格式化数字为float(强制) 浮点
     * @param Num
     * @returns
     */
    float(Num) {
        if (!Num)
            return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num === null || Num === void 0 ? void 0 : Num.valueOf();
        }
        if (typeof Num == "string") {
            Num = parseFloat(Num);
            if (isNaN(Num))
                return 0;
            if (Num >= Infinity) {
                Num = 999999999999999.999;
            }
            if (Num <= -Infinity) {
                Num = -999999999999999.999;
            }
            return Num;
        }
        if (typeof Num == "number" && !isNaN(Num))
            return Num;
        // true == 1
        if (Num && typeof Num == "boolean")
            Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean")
            Num = 0;
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
    int(Num) {
        if (!Num)
            return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num === null || Num === void 0 ? void 0 : Num.valueOf();
        }
        // 取整
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num))
            return Num;
        // true == 1
        if (Num && typeof Num == "boolean")
            Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean")
            Num = 0;
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
    stringArray(array) {
        let dataList = [];
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
    intArray(array) {
        let dataList = [];
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
    formatArgv(...argv) {
        let argvs = [];
        let argvsResult = [];
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
            if (!cout)
                continue;
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
    concatBuff(buffList) {
        let buffSize = 0;
        for (let index = 0; index < buffList.length; index++) {
            const buff = buffList[index];
            buffSize = buffSize + buff.byteLength;
        }
        let ResponseData = Buffer.concat([...buffList], buffSize);
        return ResponseData;
    }
};
exports.HMC_BETA = require(String(process.env.mode));
var ENV_INFO_COMMAND;
(function (ENV_INFO_COMMAND) {
    // getProcessCommandLine2   `string`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_COMMAND"] = 1] = "GET_COMMAND";
    // getProcessCwdPath2 `string`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_CWD"] = 2] = "GET_CWD";
    // getProcessCpuUsage2 `float`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_PROCESS_CPU_USAGE"] = 3] = "GET_PROCESS_CPU_USAGE";
    // getProcessStartTime2 `number`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_PROCESS_START_TIME"] = 5] = "GET_PROCESS_START_TIME";
    // EnumProcesses `json`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_ENUM_PROCESSES_LIST"] = 6] = "GET_ENUM_PROCESSES_LIST";
    // getAllProcessList2(true) `json`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_ALL_PROCESS_LIST_PID_NAME"] = 7] = "GET_ALL_PROCESS_LIST_PID_NAME";
    // getAllProcessList2 `json`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_ALL_PROCESS_LIST_NONE_NAME"] = 8] = "GET_ALL_PROCESS_LIST_NONE_NAME";
    // getDetailsProcessList2 `json`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_ALL_PROCESS_LIST_DETAILS"] = 7] = "GET_ALL_PROCESS_LIST_DETAILS";
    // getAllProcessListSnp2 `json`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_ALL_PROCESS_LIST_SNP"] = 10] = "GET_ALL_PROCESS_LIST_SNP";
    // getAllProcessListNt2 `json`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_ALL_PROCESS_LIST_NT"] = 11] = "GET_ALL_PROCESS_LIST_NT";
    //  getProcessThreadList `json`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_ALL_THREAD_LIST"] = 12] = "GET_ALL_THREAD_LIST";
    //  getParentProcessID2 `long`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_PARENT_PROCESS_ID"] = 13] = "GET_PARENT_PROCESS_ID";
    // existProcess `bool`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_EXIST_PROCESS"] = 15] = "GET_EXIST_PROCESS";
    // getSubProcess `Array<int>`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_SUB_PROCESS"] = 19] = "GET_SUB_PROCESS";
    // isProcessWow64 `bool`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_IS_PROCESS_WOW64"] = 20] = "GET_IS_PROCESS_WOW64";
    // getExecutableCwdList `Array<string>`
    ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_EXECUTABLE_CWD_LIST"] = 21] = "GET_EXECUTABLE_CWD_LIST";
})(ENV_INFO_COMMAND = exports.ENV_INFO_COMMAND || (exports.ENV_INFO_COMMAND = {}));
;
/**
 * 读取指定进程的工作目录  `Async(异步)`
 * @param ProcessID 进程id
 * @returns
 */
async function getProcessCwdPath2(ProcessID) {
    return exports.HMC_BETA.getProcessEnvInfo2(exports.ref.int(ProcessID), ENV_INFO_COMMAND.GET_CWD)
        .then(data => {
        return data || exports.ref.string(data);
    })
        .catch(err => {
        return null;
    });
}
exports.getProcessCwdPath2 = getProcessCwdPath2;
/**
 * 读取指定进程的工作目录  `Sync(同步)`
 * @param ProcessID 进程id
 * @returns
 */
function getProcessCwdPath2Sync(ProcessID) {
    return exports.HMC_BETA.getProcessEnvInfo2Sync(exports.ref.int(ProcessID), ENV_INFO_COMMAND.GET_CWD);
}
exports.getProcessCwdPath2Sync = getProcessCwdPath2Sync;
/**
 * 读取指定进程的启动命令行  `Async(异步)`
 * @param ProcessID 进程id
 * @returns
 */
async function getProcessCommandLine2(ProcessID) {
    return exports.HMC_BETA.getProcessEnvInfo2(exports.ref.int(ProcessID), ENV_INFO_COMMAND.GET_COMMAND)
        .then(data => {
        return data || exports.ref.string(data);
    })
        .catch(err => {
        return null;
    });
}
exports.getProcessCommandLine2 = getProcessCommandLine2;
/**
 * 读取指定进程的启动命令行  `Sync(同步)`
 * @param ProcessID 进程id
 * @returns
 */
function getProcessCommandLine2Sync(ProcessID) {
    return exports.HMC_BETA.getProcessEnvInfo2Sync(exports.ref.int(ProcessID), ENV_INFO_COMMAND.GET_COMMAND);
}
exports.getProcessCommandLine2Sync = getProcessCommandLine2Sync;
/**
 * 读取指定进程的CPU占比  `Async(异步)`
 * @param ProcessID 进程id
 * @time >= 1000ms
 * @returns
 */
async function getProcessCpuUsage2(ProcessID) {
    return exports.HMC_BETA.getProcessEnvInfo2(exports.ref.int(ProcessID), ENV_INFO_COMMAND.GET_PROCESS_CPU_USAGE)
        .then(data => {
        return exports.ref.float(data);
    })
        .catch(err => {
        return 0;
    });
}
exports.getProcessCpuUsage2 = getProcessCpuUsage2;
/**
 * 读取指定进程的CPU占比  `Sync(同步)`
 * @param ProcessID 进程id
 * @time >= 1000ms
 */
function getProcessCpuUsage2Sync(ProcessID) {
    return exports.ref.float(exports.HMC_BETA.getProcessEnvInfo2Sync(exports.ref.int(ProcessID), ENV_INFO_COMMAND.GET_PROCESS_CPU_USAGE));
}
exports.getProcessCpuUsage2Sync = getProcessCpuUsage2Sync;
/**
 * 读取指定进程的CPU占比  `Async(异步)`
 * @param ProcessID 进程id
 * @time >= 1000ms
 */
async function getProcessStartTime2(ProcessID) {
    return exports.HMC_BETA.getProcessEnvInfo2(exports.ref.int(ProcessID), ENV_INFO_COMMAND.GET_PROCESS_START_TIME)
        .then(data => {
        return exports.ref.int(data);
    })
        .catch(err => {
        return 0;
    });
}
exports.getProcessStartTime2 = getProcessStartTime2;
/**
 * 读取指定进程的启动时间  `Sync(同步)`
 * @param ProcessID 进程id
 */
function getProcessStartTime2Sync(ProcessID) {
    return exports.ref.int(exports.HMC_BETA.getProcessEnvInfo2Sync(exports.ref.int(ProcessID), ENV_INFO_COMMAND.GET_PROCESS_START_TIME));
}
exports.getProcessStartTime2Sync = getProcessStartTime2Sync;
async function getAllProcessList2(is_execPath) {
    const { GET_ALL_PROCESS_LIST_NT, GET_ALL_PROCESS_LIST_DETAILS, 
    // 
    GET_ALL_PROCESS_LIST_NONE_NAME, 
    // 带路径
    GET_ALL_PROCESS_LIST_PID_NAME, 
    // sup 列表
    GET_ALL_PROCESS_LIST_SNP, GET_ENUM_PROCESSES_LIST } = ENV_INFO_COMMAND;
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
        const data = await exports.HMC_BETA.getProcessEnvInfo2(0, SEND_TYPE);
        const result = JSON.parse(data || "[]");
        if (GET_ALL_PROCESS_LIST_NT == SEND_TYPE ||
            GET_ALL_PROCESS_LIST_SNP == SEND_TYPE) {
            for (let index = 0; index < result.length; index++) {
                const element = result[index];
                element.name = (element === null || element === void 0 ? void 0 : element.szExeFile) || (element === null || element === void 0 ? void 0 : element.ImageName) || "";
                element.pid = (element === null || element === void 0 ? void 0 : element.th32ProcessID) || (element === null || element === void 0 ? void 0 : element.UniqueProcessId) || 0;
            }
        }
        return result;
    }
    catch (err) {
        return [];
    }
}
exports.getAllProcessList2 = getAllProcessList2;
function getAllProcessList2Sync(is_execPath) {
    const { GET_ALL_PROCESS_LIST_NT, GET_ALL_PROCESS_LIST_DETAILS, 
    // 
    GET_ALL_PROCESS_LIST_NONE_NAME, 
    // 带路径
    GET_ALL_PROCESS_LIST_PID_NAME, 
    // sup 列表
    GET_ALL_PROCESS_LIST_SNP, GET_ENUM_PROCESSES_LIST } = ENV_INFO_COMMAND;
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
    const result = JSON.parse(exports.HMC_BETA.getProcessEnvInfo2Sync(0, SEND_TYPE) || "[]");
    if (GET_ALL_PROCESS_LIST_NT == SEND_TYPE ||
        GET_ALL_PROCESS_LIST_SNP == SEND_TYPE) {
        for (let index = 0; index < result.length; index++) {
            const element = result[index];
            element.name = (element === null || element === void 0 ? void 0 : element.szExeFile) || (element === null || element === void 0 ? void 0 : element.ImageName) || "";
            element.pid = (element === null || element === void 0 ? void 0 : element.th32ProcessID) || (element === null || element === void 0 ? void 0 : element.UniqueProcessId) || 0;
        }
    }
    return result;
}
exports.getAllProcessList2Sync = getAllProcessList2Sync;
function getAllProcessListNt2() {
    return getAllProcessList2(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT);
}
exports.getAllProcessListNt2 = getAllProcessListNt2;
function getAllProcessListNt2Sync() {
    return getAllProcessList2Sync(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT);
}
exports.getAllProcessListNt2Sync = getAllProcessListNt2Sync;
function getAllProcessListSnp2() {
    return getAllProcessList2(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP);
}
exports.getAllProcessListSnp2 = getAllProcessListSnp2;
function getAllProcessListSnp2Sync() {
    return getAllProcessList2Sync(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP);
}
exports.getAllProcessListSnp2Sync = getAllProcessListSnp2Sync;
function getDetailsProcessList2() {
    return getAllProcessList2(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS);
}
exports.getDetailsProcessList2 = getDetailsProcessList2;
function getDetailsProcessList2Sync() {
    return getAllProcessList2Sync(ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS);
}
exports.getDetailsProcessList2Sync = getDetailsProcessList2Sync;
function enumAllProcess2() {
    return getAllProcessList2(ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST);
}
exports.enumAllProcess2 = enumAllProcess2;
function enumAllProcess2Sync() {
    return getAllProcessList2Sync(ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST);
}
exports.enumAllProcess2Sync = enumAllProcess2Sync;
async function isProcessWow64Bit2(ProcessID) {
    const bool = await exports.HMC_BETA.getProcessEnvInfo2(exports.ref.int(ProcessID || -1), ENV_INFO_COMMAND.GET_IS_PROCESS_WOW64);
    return !!exports.ref.int(bool);
}
exports.isProcessWow64Bit2 = isProcessWow64Bit2;
function isProcessWow64Bit2Sync(ProcessID) {
    const bool = exports.HMC_BETA.getProcessEnvInfo2Sync(exports.ref.int(ProcessID || -1), ENV_INFO_COMMAND.GET_IS_PROCESS_WOW64);
    return !!exports.ref.int(bool);
}
exports.isProcessWow64Bit2Sync = isProcessWow64Bit2Sync;
async function existProcess2(ProcessID) {
    const bool = await exports.HMC_BETA.getProcessEnvInfo2(exports.ref.int(ProcessID || -1), ENV_INFO_COMMAND.GET_EXIST_PROCESS);
    return !!exports.ref.int(bool);
}
exports.existProcess2 = existProcess2;
function existProcess2Sync(ProcessID) {
    const bool = exports.HMC_BETA.getProcessEnvInfo2Sync(exports.ref.int(ProcessID || -1), ENV_INFO_COMMAND.GET_EXIST_PROCESS);
    return !!exports.ref.int(bool);
}
exports.existProcess2Sync = existProcess2Sync;
async function getParentProcess2(ProcessID) {
    const long = await exports.HMC_BETA.getProcessEnvInfo2(exports.ref.int(ProcessID || -1), ENV_INFO_COMMAND.GET_PARENT_PROCESS_ID);
    return exports.ref.int(long || 0) || null;
    ;
}
exports.getParentProcess2 = getParentProcess2;
function getParentProcess2Sync(ProcessID) {
    return exports.ref.int(exports.HMC_BETA.getProcessEnvInfo2Sync(exports.ref.int(ProcessID || -1), ENV_INFO_COMMAND.GET_PARENT_PROCESS_ID) || 0) || null;
}
exports.getParentProcess2Sync = getParentProcess2Sync;
/**
 * 枚举 指定/当前 的子进程
 * @param FindProcessID 查找的进程 默认当前
 * @returns
 */
async function getSubProcess2(ProcessID) {
    const anyJSON = await exports.HMC_BETA.getProcessEnvInfo2(exports.ref.int(ProcessID || -1), ENV_INFO_COMMAND.GET_SUB_PROCESS);
    return JSON.parse(anyJSON || "[]");
    ;
}
exports.getSubProcess2 = getSubProcess2;
/**
 * 枚举 指定/当前 的子进程
 * @param FindProcessID 查找的进程 默认当前
 * @returns
 */
function getSubProcess2Sync(ProcessID) {
    return JSON.parse((exports.HMC_BETA.getProcessEnvInfo2Sync(exports.ref.int(ProcessID || -1), ENV_INFO_COMMAND.GET_SUB_PROCESS) || "[]"));
}
exports.getSubProcess2Sync = getSubProcess2Sync;
/**
 * 枚举 指定/所有 的线程
 * @param FindProcessID 查找的进程 默认所有
 * @returns
 */
async function getProcessThreadList2(FindProcessID) {
    const anyJSON = await exports.HMC_BETA.getProcessEnvInfo2(exports.ref.int(FindProcessID || -1), ENV_INFO_COMMAND.GET_ALL_THREAD_LIST);
    return JSON.parse(anyJSON || "[]");
}
exports.getProcessThreadList2 = getProcessThreadList2;
/**
 * 枚举 指定/所有 的线程
 * @param FindProcessID 查找的进程 默认所有
 * @returns
 */
function getProcessThreadList2Sync(FindProcessID) {
    return JSON.parse((exports.HMC_BETA.getProcessEnvInfo2Sync(exports.ref.int(FindProcessID || -1), ENV_INFO_COMMAND.GET_ALL_THREAD_LIST) || "[]"));
}
exports.getProcessThreadList2Sync = getProcessThreadList2Sync;
/**
 * 帮我尽可能的查找此进程的所有有可能的工作路径
 * @param FindProcessID 查找的进程 默认当前
 * @returns
 */
async function getExecutableCwdList2(FindProcessID) {
    const anyJSON = await exports.HMC_BETA.getProcessEnvInfo2(exports.ref.int(FindProcessID || process.pid), ENV_INFO_COMMAND.GET_EXECUTABLE_CWD_LIST);
    return JSON.parse(anyJSON || "[]");
}
exports.getExecutableCwdList2 = getExecutableCwdList2;
/**
 * 帮我尽可能的查找此进程的所有有可能的工作路径
 * @param FindProcessID 查找的进程 默认当前
 * @returns
 */
function getExecutableCwdList2Sync(FindProcessID) {
    return JSON.parse((exports.HMC_BETA.getProcessEnvInfo2Sync(exports.ref.int(FindProcessID || process.pid), ENV_INFO_COMMAND.GET_EXECUTABLE_CWD_LIST) || "[]"));
}
exports.getExecutableCwdList2Sync = getExecutableCwdList2Sync;
async function main() {
    const PromList = [];
    // const ProcessList = JSON.parse(await HMC_X64.getAllProcessList());
    const result = new Map();
    const resultSync = new Map();
    return { result, resultSync };
}
exports.main = main;
;
/**


const mode =  require(path.resolve(process.env.hmc_debug_js,"Process\\GetProcessEnvInfo.js"));

await mode.main();



*/
