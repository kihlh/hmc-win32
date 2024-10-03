"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Process = void 0;
const main = require("./index");
const util = require("./util");
const index_1 = require("./index");
const { ref } = util;
function GetProcessEnvInfo2Clone(pid, command) {
    var _a;
    if (!((_a = main.Native.native) === null || _a === void 0 ? void 0 : _a["getProcessEnvInfo2"])) {
        return Promise.resolve(null);
    }
    return main.Native.native["getProcessEnvInfo2"](pid, command);
}
function GetProcessEnvInfo2SyncClone(pid, command) {
    var _a;
    if (!((_a = main.Native.native) === null || _a === void 0 ? void 0 : _a["getProcessEnvInfo2Sync"])) {
        return null;
    }
    return main.Native.native["getProcessEnvInfo2Sync"](pid, command);
}
var Process;
(function (Process_1) {
    /**
     * 获取指定进程的工作目录
     * @dosc 由于跨进程权限问题 不保证获取得到
     * !此功能需要读取进程内存
     * @module 异步async
     * @returns
     */
    async function getProcessCwdPath2(ProcessID) {
        return GetProcessEnvInfo2Clone(ref.int(ProcessID), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_CWD)
            .then(data => {
            return data || ref.string(data);
        })
            .catch(err => {
            return null;
        });
    }
    Process_1.getProcessCwdPath2 = getProcessCwdPath2;
    /**
     * 获取指定进程的工作目录
     * @dosc 由于跨进程权限问题 不保证获取得到
     * !此功能需要读取进程内存
     * @module 同步Sync
     * @returns
     */
    function getProcessCwdPath2Sync(ProcessID) {
        return GetProcessEnvInfo2SyncClone(ref.int(ProcessID), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_CWD);
    }
    Process_1.getProcessCwdPath2Sync = getProcessCwdPath2Sync;
    /**
     * 读取指定进程的启动命令行  `Async(异步)`
     * @dosc 由于跨进程权限问题 不保证获取得到
     * ?此功能在win8及以下系统 需要读取进程内存
     * @module 异步async
     * @param ProcessID 进程id
     * @returns
     */
    async function getProcessCommandLine2(ProcessID) {
        return GetProcessEnvInfo2Clone(ref.int(ProcessID), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_COMMAND)
            .then(data => {
            return data || ref.string(data);
        })
            .catch(err => {
            return null;
        });
    }
    Process_1.getProcessCommandLine2 = getProcessCommandLine2;
    /**
     * 读取指定进程的启动命令行  `Sync(同步)`
     * @dosc 由于跨进程权限问题 不保证获取得到
     * ?此功能在win8及以下系统 需要读取进程内存
     * @module 同步Sync
     * @param ProcessID 进程id
     * @returns
     */
    function getProcessCommandLine2Sync(ProcessID) {
        return GetProcessEnvInfo2SyncClone(ref.int(ProcessID), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_COMMAND);
    }
    Process_1.getProcessCommandLine2Sync = getProcessCommandLine2Sync;
    /**
     * 读取指定进程的CPU占比  `Async(异步)`
     * @param ProcessID 进程id
     * @time >= 1000ms
     * @returns
     */
    async function getProcessCpuUsage2(ProcessID) {
        return GetProcessEnvInfo2Clone(ref.int(ProcessID), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_CPU_USAGE)
            .then(data => {
            return ref.float(data);
        })
            .catch(err => {
            return 0;
        });
    }
    Process_1.getProcessCpuUsage2 = getProcessCpuUsage2;
    /**
     * 读取指定进程的CPU占比  `Sync(同步)`
     * @param ProcessID 进程id
     * @time >= 1000ms
     */
    function getProcessCpuUsage2Sync(ProcessID) {
        return ref.float(GetProcessEnvInfo2SyncClone(ref.int(ProcessID), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_CPU_USAGE));
    }
    Process_1.getProcessCpuUsage2Sync = getProcessCpuUsage2Sync;
    /**
     * 读取指定进程的CPU占比  `Async(异步)`
     * @param ProcessID 进程id
     * @time >= 1000ms
     */
    async function getProcessStartTime2(ProcessID) {
        return GetProcessEnvInfo2Clone(ref.int(ProcessID), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_START_TIME)
            .then(data => {
            return ref.int(data);
        })
            .catch(err => {
            return 0;
        });
    }
    Process_1.getProcessStartTime2 = getProcessStartTime2;
    /**
     * 读取指定进程的启动时间  `Sync(同步)`
     * @param ProcessID 进程id
     */
    function getProcessStartTime2Sync(ProcessID) {
        return ref.int(GetProcessEnvInfo2SyncClone(ref.int(ProcessID), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_START_TIME));
    }
    Process_1.getProcessStartTime2Sync = getProcessStartTime2Sync;
    /**
     * 获取所有进程的进程列表
     * @docs 特例情况
     * - [(x64 system) run x86 node ] 将调用enum进程方式以保证数据完整 因此is_execPath为false时返回的不带有name
     * - [(x64 system) run x64 node] 将调用Snp(进程镜像) 因此会带有name内容
     * @param is_execPath 是否添加 (路径/名称)
     * @default false
     * - true {name:string,path:string,pid:number}
     * - false { name:'' (wow64) | string , path:'' , pid:number }
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_PID_NAME
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NONE_NAME
     * @returns
     */
    async function getAllProcessList2(is_execPath) {
        const { GET_ALL_PROCESS_LIST_NT, GET_ALL_PROCESS_LIST_DETAILS, 
        // 
        GET_ALL_PROCESS_LIST_NONE_NAME, 
        // 带路径
        GET_ALL_PROCESS_LIST_PID_NAME, 
        // sup 列表
        GET_ALL_PROCESS_LIST_SNP, GET_ENUM_PROCESSES_LIST } = index_1.HMC2_MODE.ENV_INFO_COMMAND;
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
            const data = await GetProcessEnvInfo2Clone(0, SEND_TYPE);
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
    Process_1.getAllProcessList2 = getAllProcessList2;
    /**
     * 获取所有进程的进程列表
     * @docs 特例情况
     * - [(x64 system) run x86 node ] 将调用enum进程方式以保证数据完整 因此is_execPath为false时返回的不带有name
     * - [(x64 system) run x64 node] 将调用Snp(进程镜像) 因此会带有name内容
     * @param is_execPath 是否添加 (路径/名称)
     * @default false
     * - true {name:string,path:string,pid:number}
     * - false { name:'' (wow64) | string , path:'' , pid:number }
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_PID_NAME
     * - HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NONE_NAME
     * @returns
     */
    function getAllProcessList2Sync(is_execPath) {
        const { GET_ALL_PROCESS_LIST_NT, GET_ALL_PROCESS_LIST_DETAILS, 
        // 
        GET_ALL_PROCESS_LIST_NONE_NAME, 
        // 带路径
        GET_ALL_PROCESS_LIST_PID_NAME, 
        // sup 列表
        GET_ALL_PROCESS_LIST_SNP, GET_ENUM_PROCESSES_LIST } = index_1.HMC2_MODE.ENV_INFO_COMMAND;
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
        const result = JSON.parse(GetProcessEnvInfo2SyncClone(0, SEND_TYPE) || "[]");
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
    Process_1.getAllProcessList2Sync = getAllProcessList2Sync;
    /**
     * 获取内核进程快照
     * @returns
     */
    function getAllProcessListNt2() {
        return getAllProcessList2(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT);
    }
    Process_1.getAllProcessListNt2 = getAllProcessListNt2;
    /**
     * 获取内核进程快照
     * @returns
     */
    function getAllProcessListNt2Sync() {
        return getAllProcessList2Sync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT);
    }
    Process_1.getAllProcessListNt2Sync = getAllProcessListNt2Sync;
    /**
     * 获取进程快照
     * @returns
     */
    function getAllProcessListSnp2() {
        return getAllProcessList2(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP);
    }
    Process_1.getAllProcessListSnp2 = getAllProcessListSnp2;
    /**
     * 获取进程快照
     * @returns
     */
    function getAllProcessListSnp2Sync() {
        return getAllProcessList2Sync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP);
    }
    Process_1.getAllProcessListSnp2Sync = getAllProcessListSnp2Sync;
    /**
     * 获取带有文件路径的进程列表
     * @returns
     */
    function getDetailsProcessList2() {
        return getAllProcessList2(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS);
    }
    Process_1.getDetailsProcessList2 = getDetailsProcessList2;
    /**
     * 获取带有文件路径的进程列表
     * @returns
     */
    function getDetailsProcessList2Sync() {
        return getAllProcessList2Sync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS);
    }
    Process_1.getDetailsProcessList2Sync = getDetailsProcessList2Sync;
    /**
     * 枚举进程列表(pid)
     * @returns
     */
    function enumAllProcess2() {
        return getAllProcessList2(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST);
    }
    Process_1.enumAllProcess2 = enumAllProcess2;
    /**
     * 枚举进程列表(pid)
     * @returns
     */
    function enumAllProcess2Sync() {
        return getAllProcessList2Sync(index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST);
    }
    Process_1.enumAllProcess2Sync = enumAllProcess2Sync;
    /**
     * 判断进程是否正在以Wow64仿真器运行
     * @docs 当进程是x86方式编译的 而系统是x64 进程将在wow64容器下仿真器执行
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    async function isProcessWow64(ProcessID) {
        const bool = await GetProcessEnvInfo2Clone(ref.int(ProcessID || -1), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_IS_PROCESS_WOW64);
        return !!ref.int(bool);
    }
    Process_1.isProcessWow64 = isProcessWow64;
    /**
     * 判断进程是否正在以Wow64仿真器运行
     * @docs 当进程是x86方式编译的 而系统是x64 进程将在wow64容器下仿真器执行
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function isProcessWow64Sync(ProcessID) {
        const bool = GetProcessEnvInfo2SyncClone(ref.int(ProcessID || -1), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_IS_PROCESS_WOW64);
        return !!ref.int(bool);
    }
    Process_1.isProcessWow64Sync = isProcessWow64Sync;
    /**
     * 判断进程存在性
     * @docs 1.句柄能够打开->true  2.句柄不能打开-> 枚举进程ID列表 -> true/false
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    async function existProcess2(ProcessID) {
        const bool = await GetProcessEnvInfo2Clone(ref.int(ProcessID || -1), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_EXIST_PROCESS);
        return !!ref.int(bool);
    }
    Process_1.existProcess2 = existProcess2;
    /**
     * 判断进程存在性
     * @docs 1.句柄能够打开->true  2.句柄不能打开-> 枚举进程ID列表 -> true/false
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function existProcess2Sync(ProcessID) {
        const bool = GetProcessEnvInfo2SyncClone(ref.int(ProcessID || -1), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_EXIST_PROCESS);
        return !!ref.int(bool);
    }
    Process_1.existProcess2Sync = existProcess2Sync;
    /**
     * 获取父进程ID
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    async function getParentProcess2(ProcessID) {
        const long = await GetProcessEnvInfo2Clone(ref.int(ProcessID || -1), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_PARENT_PROCESS_ID);
        return ref.int(long || 0) || null;
        ;
    }
    Process_1.getParentProcess2 = getParentProcess2;
    /**
     * 获取父进程ID
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function getParentProcess2Sync(ProcessID) {
        return ref.int(GetProcessEnvInfo2SyncClone(ref.int(ProcessID || -1), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_PARENT_PROCESS_ID) || 0) || null;
    }
    Process_1.getParentProcess2Sync = getParentProcess2Sync;
    /**
     * 枚举 指定/当前 的子进程
     * @param FindProcessID 查找的进程
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    async function getSubProcess2(ProcessID) {
        const anyJSON = await GetProcessEnvInfo2Clone(ref.int(ProcessID || -1), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_SUB_PROCESS);
        return JSON.parse(anyJSON || "[]");
        ;
    }
    Process_1.getSubProcess2 = getSubProcess2;
    /**
     * 枚举 指定/当前 的子进程
     * @param FindProcessID 查找的进程
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function getSubProcess2Sync(ProcessID) {
        return JSON.parse((GetProcessEnvInfo2SyncClone(ref.int(ProcessID || -1), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_SUB_PROCESS) || "[]"));
    }
    Process_1.getSubProcess2Sync = getSubProcess2Sync;
    /**
     * 枚举 指定/所有 的线程
     * @param FindProcessID 查找的进程
     * @default all
     * @returns
     */
    async function getProcessThreadList2(FindProcessID) {
        const anyJSON = await GetProcessEnvInfo2Clone(ref.int(FindProcessID || -1), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_THREAD_LIST);
        return JSON.parse(anyJSON || "[]");
    }
    Process_1.getProcessThreadList2 = getProcessThreadList2;
    /**
     * 枚举 指定/所有 的线程
     * @param FindProcessID 查找的进程
     * @default all
     * @returns
     */
    function getProcessThreadList2Sync(FindProcessID) {
        return JSON.parse((GetProcessEnvInfo2SyncClone(ref.int(FindProcessID || -1), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_THREAD_LIST) || "[]"));
    }
    Process_1.getProcessThreadList2Sync = getProcessThreadList2Sync;
    /**
     * 帮我尽可能的查找此进程的所有有可能的工作路径
     * @param FindProcessID 查找的进程
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    async function getExecutableCwdList2(FindProcessID) {
        const anyJSON = await GetProcessEnvInfo2Clone(ref.int(FindProcessID || process.pid), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_EXECUTABLE_CWD_LIST);
        return JSON.parse(anyJSON || "[]");
    }
    Process_1.getExecutableCwdList2 = getExecutableCwdList2;
    /**
     * 帮我尽可能的查找此进程的所有有可能的工作路径
     * @param FindProcessID 查找的进程
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function getExecutableCwdList2Sync(FindProcessID) {
        return JSON.parse((GetProcessEnvInfo2SyncClone(ref.int(FindProcessID || process.pid), index_1.HMC2_MODE.ENV_INFO_COMMAND.GET_EXECUTABLE_CWD_LIST) || "[]"));
    }
    Process_1.getExecutableCwdList2Sync = getExecutableCwdList2Sync;
    async function getProcessName2(pid, type) {
        if (!main.Native.native.getProcessName2) {
            if (type == index_1.HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
                return Promise.resolve([]);
            }
            return Promise.resolve(null);
        }
        const data = await main.Native.native.getProcessName2(ref.int(pid), type ? ref.int(type) : undefined);
        if (type == index_1.HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
            const data_list = data ? Array.isArray(data) ? data : data === null || data === void 0 ? void 0 : data.split("\0") : [];
            return data_list.filter(item => item);
        }
        return data ? String(data) : null;
    }
    Process_1.getProcessName2 = getProcessName2;
    function getProcessName2Sync(pid, type) {
        if (!main.Native.native.getProcessName2Sync) {
            if (type == index_1.HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
                return [];
            }
            return null;
        }
        const data = main.Native.native.getProcessName2Sync(ref.int(pid), type ? ref.int(type) : undefined);
        if (type == index_1.HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
            const data_list = data ? Array.isArray(data) ? data : data === null || data === void 0 ? void 0 : data.split("\0") : [];
            return data_list.filter(item => item);
        }
        return data ? String(data) : null;
    }
    Process_1.getProcessName2Sync = getProcessName2Sync;
    /**
     * 获取指定进程的可执行文件路径
     * @param pid 进程id
     * @param isEnumListExists 是否必须出现在进程列表中的
     * @default false
     * @param isSnapshotName 获取失败时获取进程名称
     * @default false
     */
    function getProcessFilePath2(pid, isEnumListExists, isSnapshotName) {
        return main.Native.native.getProcessFilePath2 ?
            main.Native.native.getProcessFilePath2(ref.int(pid), ...[...(isEnumListExists ? [true] : []), ...(isSnapshotName ? [true] : [])])
            : Promise.resolve(null);
    }
    Process_1.getProcessFilePath2 = getProcessFilePath2;
    /**
     * 获取指定进程的可执行文件路径
     * @param pid 进程id
     * @param isEnumListExists 是否必须出现在进程列表中的
     * @default false
     * @param isSnapshotName 获取失败时获取进程名称
     * @default false
     */
    function getProcessFilePath2Sync(pid, isEnumListExists, isSnapshotName) {
        return main.Native.native.getProcessFilePath2Sync ?
            main.Native.native.getProcessFilePath2Sync(ref.int(pid), ...[...(isEnumListExists ? [true] : []), ...(isSnapshotName ? [true] : [])])
            : null;
    }
    Process_1.getProcessFilePath2Sync = getProcessFilePath2Sync;
    function getProcessParentProcessMatch2(Process) {
        return new Promise((resolve, reject) => {
            const data_list = [];
            getAllProcessListSnp2().then(process_list => {
                for (let index = 0; index < process_list.length; index++) {
                    const for_process_item = process_list[index];
                    if (typeof Process == "number" && for_process_item.th32ProcessID == Process) {
                        return resolve(for_process_item);
                    }
                    if (typeof Process == "string" && for_process_item.szExeFile == "string") {
                        data_list.push(for_process_item);
                    }
                    if (Process instanceof RegExp && for_process_item.szExeFile.match(Process)) {
                        data_list.push(for_process_item);
                    }
                }
                return resolve(data_list);
            }).catch(reject);
        });
    }
    Process_1.getProcessParentProcessMatch2 = getProcessParentProcessMatch2;
    function getProcessParentProcessMatch2Sync(Process) {
        const data_list = [];
        const process_list = getAllProcessListSnp2Sync();
        for (let index = 0; index < process_list.length; index++) {
            const for_process_item = process_list[index];
            if (typeof Process == "number" && for_process_item.th32ProcessID == Process) {
                return for_process_item;
            }
            if (typeof Process == "string" && for_process_item.szExeFile == "string") {
                data_list.push(for_process_item);
            }
            if (Process instanceof RegExp && for_process_item.szExeFile.match(Process)) {
                data_list.push(for_process_item);
            }
        }
        return data_list;
    }
    Process_1.getProcessParentProcessMatch2Sync = getProcessParentProcessMatch2Sync;
    /**
     * 按照名称搜索进程
     * @param ProcessName
     * @returns
     */
    async function findProcess2(ProcessName) {
        return new Promise(async (resolve, reject) => {
            var _a, _b, _c, _d;
            let result = [];
            const isMacthFile = ProcessName && (typeof ProcessName != "number");
            let ProcessList = await (isMacthFile ? getAllProcessList2(true) : getAllProcessList2()).catch(reject) || [];
            for (let index = 0; index < ProcessList.length; index++) {
                const Process = ProcessList[index];
                if (typeof ProcessName == "string") {
                    if (((_a = Process === null || Process === void 0 ? void 0 : Process.name) === null || _a === void 0 ? void 0 : _a.includes(ProcessName)) || ((_b = Process === null || Process === void 0 ? void 0 : Process.path) === null || _b === void 0 ? void 0 : _b.includes(ProcessName))) {
                        result.push(Process);
                    }
                }
                else if (typeof ProcessName == "number") {
                    if (Process.pid == ProcessName) {
                        let path = await getProcessFilePath2(ProcessName).catch(reject);
                        // @ts-expect-error
                        Process.path = path || null;
                        // @ts-expect-error
                        Process.name = (path === null || path === void 0 ? void 0 : path.split(/[\\\/]+/).at(-1)) || null;
                        result.push(Process);
                    }
                }
                else {
                    if (((_c = Process === null || Process === void 0 ? void 0 : Process.name) === null || _c === void 0 ? void 0 : _c.match(ProcessName)) || (typeof (Process === null || Process === void 0 ? void 0 : Process.path) == "string") ? (_d = Process === null || Process === void 0 ? void 0 : Process.path) === null || _d === void 0 ? void 0 : _d.match(ProcessName) : false) {
                        result.push(Process);
                    }
                }
            }
            resolve(result);
        });
    }
    Process_1.findProcess2 = findProcess2;
    /**
     * 按照名称搜索进程
     * @param ProcessName
     * @returns
     */
    function findProcess2Sync(ProcessName) {
        var _a, _b, _c, _d;
        let result = [];
        const isMacthFile = ProcessName && (typeof ProcessName != "number");
        let ProcessList = (isMacthFile ? getAllProcessList2Sync(true) : getAllProcessList2Sync()) || [];
        for (let index = 0; index < ProcessList.length; index++) {
            const Process = ProcessList[index];
            if (typeof ProcessName == "string") {
                if (((_a = Process === null || Process === void 0 ? void 0 : Process.name) === null || _a === void 0 ? void 0 : _a.includes(ProcessName)) || ((_b = Process === null || Process === void 0 ? void 0 : Process.path) === null || _b === void 0 ? void 0 : _b.includes(ProcessName))) {
                    result.push(Process);
                }
            }
            else if (typeof ProcessName == "number") {
                if (Process.pid == ProcessName) {
                    let path = getProcessFilePath2Sync(ProcessName);
                    // @ts-expect-error
                    Process.path = path || null;
                    // @ts-expect-error
                    Process.name = (path === null || path === void 0 ? void 0 : path.split(/[\\\/]+/).at(-1)) || null;
                    result.push(Process);
                }
            }
            else {
                if (((_c = Process === null || Process === void 0 ? void 0 : Process.name) === null || _c === void 0 ? void 0 : _c.match(ProcessName)) || (typeof (Process === null || Process === void 0 ? void 0 : Process.path) == "string") ? (_d = Process === null || Process === void 0 ? void 0 : Process.path) === null || _d === void 0 ? void 0 : _d.match(ProcessName) : false) {
                    result.push(Process);
                }
            }
        }
        return result;
    }
    Process_1.findProcess2Sync = findProcess2Sync;
    /**
    * `Sync` 同步阻塞(进程)
    * @param awaitTime
    * @returns
    */
    function sleep(awaitTime) {
        return GetProcessEnvInfo2SyncClone(ref.int(awaitTime), index_1.HMC2_MODE.ENV_INFO_COMMAND.SEND_SLEEP);
    }
    Process_1.sleep = sleep;
    /**
     * `async` 异步阻塞(进程)
     * @param awaitTime
     * @returns
     */
    async function Sleep(awaitTime, Sync) {
        if (Sync) {
            return sleep(ref.int(awaitTime));
        }
        return new Promise((resolve) => setTimeout(resolve, ref.int(awaitTime)));
    }
    Process_1.Sleep = Sleep;
})(Process = exports.Process || (exports.Process = {}));
