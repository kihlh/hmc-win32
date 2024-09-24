import main = require("./index");
import util = require("./util");
import { HMC2_MODE } from "./index";

const { ref } = util;


function GetProcessEnvInfo2Clone(pid: number, command: HMC2_MODE.ENV_INFO_COMMAND) {

    if (!main.Native.native?.["getProcessEnvInfo2"]) {
        return Promise.resolve(null);
    }

    return main.Native.native["getProcessEnvInfo2"](pid, command);
}

function GetProcessEnvInfo2SyncClone(pid: number, command: HMC2_MODE.ENV_INFO_COMMAND) {

    if (!main.Native.native?.["getProcessEnvInfo2Sync"]) {
        return null;
    }

    return main.Native.native["getProcessEnvInfo2Sync"](pid, command);
}


export module Process {

    /**
     * 读取指定进程的工作目录  `Async(异步)`
     * @param ProcessID 进程id
     * @returns 
     */
    export async function getProcessCwdPath2(ProcessID: number): Promise<null | string> {
        return GetProcessEnvInfo2Clone(ref.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_CWD)
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
        return GetProcessEnvInfo2SyncClone(ref.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_CWD);
    }

    /**
     * 读取指定进程的启动命令行  `Async(异步)`
     * @param ProcessID 进程id
     * @returns 
     */
    export async function getProcessCommandLine2(ProcessID: number): Promise<null | string> {
        return GetProcessEnvInfo2Clone(ref.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_COMMAND)
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
        return GetProcessEnvInfo2SyncClone(ref.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_COMMAND);
    }

    /**
     * 读取指定进程的CPU占比  `Async(异步)`
     * @param ProcessID 进程id
     * @time >= 1000ms
     * @returns 
     */
    export async function getProcessCpuUsage2(ProcessID: number): Promise<number> {
        return GetProcessEnvInfo2Clone(ref.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_CPU_USAGE)
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
        return ref.float(GetProcessEnvInfo2SyncClone(ref.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_CPU_USAGE));
    }

    /**
     * 读取指定进程的CPU占比  `Async(异步)`
     * @param ProcessID 进程id
     * @time >= 1000ms
     */
    export async function getProcessStartTime2(ProcessID: number): Promise<number> {
        return GetProcessEnvInfo2Clone(ref.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_START_TIME)
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
        return ref.int(GetProcessEnvInfo2SyncClone(ref.int(ProcessID), HMC2_MODE.ENV_INFO_COMMAND.GET_PROCESS_START_TIME));
    }

    export function getAllProcessList2(): Promise<HMC2_MODE.PROCESSENTRY_DEFAULT[]>;
    export function getAllProcessList2(is_execPath: false): Promise<HMC2_MODE.PROCESSENTRY_NONE_NAME[]>;
    export function getAllProcessList2(is_execPath: true): Promise<HMC2_MODE.PROCESSENTRY_DEFAULT[]>;
    export function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST): Promise<number[]>;
    export function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS): Promise<HMC2_MODE.PROCESSENTRY_DEFAULT[]>;
    export function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP): Promise<HMC2_MODE.PROCESSENTRY[]>;
    export function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT): Promise<HMC2_MODE.PSYSTEM_PROCESS_INFORMATION[]>;
    export function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NONE_NAME): Promise<HMC2_MODE.PROCESSENTRY_NONE_NAME[]>;
    export function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_PID_NAME): Promise<HMC2_MODE.PROCESSENTRY_DEFAULT[]>;

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
    export async function getAllProcessList2(is_execPath?: boolean | HMC2_MODE.GET_PROCESS_LIST_COMMAND): Promise<unknown> {
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
        } = HMC2_MODE.ENV_INFO_COMMAND;


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
                    element.name = element?.szExeFile || element?.ImageName || "";
                    element.pid = element?.th32ProcessID || element?.UniqueProcessId || 0;
                }
            }
            return result;
        } catch (err) {
            return [];
        }
    }

    export function getAllProcessList2Sync(): HMC2_MODE.PROCESSENTRY_DEFAULT[];
    export function getAllProcessList2Sync(is_execPath: false): HMC2_MODE.PROCESSENTRY_NONE_NAME[];
    export function getAllProcessList2Sync(is_execPath: true): HMC2_MODE.PROCESSENTRY_DEFAULT[];
    export function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST): number[];
    export function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS): HMC2_MODE.PROCESSENTRY_DEFAULT[];
    export function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP): HMC2_MODE.PROCESSENTRY[];
    export function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT): HMC2_MODE.PSYSTEM_PROCESS_INFORMATION[];
    export function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NONE_NAME): HMC2_MODE.PROCESSENTRY_NONE_NAME[];
    export function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_PID_NAME): HMC2_MODE.PROCESSENTRY_DEFAULT[];

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
    export function getAllProcessList2Sync(is_execPath?: boolean | HMC2_MODE.ENV_INFO_COMMAND): unknown {
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
        } = HMC2_MODE.ENV_INFO_COMMAND;


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

    /**
     * 获取内核进程快照
     * @returns 
     */
    export function getAllProcessListNt2(): Promise<HMC2_MODE.PSYSTEM_PROCESS_INFORMATION[]> {
        return getAllProcessList2(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT);
    }

    /**
     * 获取内核进程快照
     * @returns 
     */
    export function getAllProcessListNt2Sync(): HMC2_MODE.PSYSTEM_PROCESS_INFORMATION[] {
        return getAllProcessList2Sync(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT);
    }

    /**
     * 获取进程快照
     * @returns 
     */
    export function getAllProcessListSnp2(): Promise<HMC2_MODE.PROCESSENTRY[]> {
        return getAllProcessList2(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP);
    }

    /**
     * 获取进程快照
     * @returns 
     */
    export function getAllProcessListSnp2Sync(): HMC2_MODE.PROCESSENTRY[] {
        return getAllProcessList2Sync(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP);
    }

    /**
     * 获取带有文件路径的进程列表
     * @returns 
     */
    export function getDetailsProcessList2(): Promise<HMC2_MODE.PROCESSENTRY_DEFAULT[]> {
        return getAllProcessList2(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS);
    }

    /**
     * 获取带有文件路径的进程列表
     * @returns 
     */
    export function getDetailsProcessList2Sync(): HMC2_MODE.PROCESSENTRY_DEFAULT[] {
        return getAllProcessList2Sync(HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS);
    }

    /**
     * 枚举进程列表(pid)
     * @returns 
     */
    export function enumAllProcess2(): Promise<number[]> {
        return getAllProcessList2(HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST);
    }

    /**
     * 枚举进程列表(pid)
     * @returns 
     */
    export function enumAllProcess2Sync(): number[] {
        return getAllProcessList2Sync(HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST);
    }

    /**
     * 判断进程是否正在以Wow64仿真器运行
     * @docs 当进程是x86方式编译的 而系统是x64 进程将在wow64容器下仿真器执行
     * @param ProcessID 进程ID 
     * @default 当前进程  [ process.pid ]
     * @returns 
     */
    export async function isProcessWow64(ProcessID?: number): Promise<boolean> {
        const bool = await GetProcessEnvInfo2Clone(ref.int(ProcessID || -1),
            HMC2_MODE.ENV_INFO_COMMAND.GET_IS_PROCESS_WOW64);
        return !!ref.int(bool);
    }

    /**
     * 判断进程是否正在以Wow64仿真器运行
     * @docs 当进程是x86方式编译的 而系统是x64 进程将在wow64容器下仿真器执行
     * @param ProcessID 进程ID 
     * @default 当前进程  [ process.pid ]
     * @returns 
     */
    export function isProcessWow64Sync(ProcessID?: number): boolean {
        const bool = GetProcessEnvInfo2SyncClone(ref.int(ProcessID || -1),
            HMC2_MODE.ENV_INFO_COMMAND.GET_IS_PROCESS_WOW64);
        return !!ref.int(bool);
    }

    /**
     * 判断进程存在性
     * @docs 1.句柄能够打开->true  2.句柄不能打开-> 枚举进程ID列表 -> true/false
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns 
     */
    export async function existProcess2(ProcessID?: number): Promise<boolean> {
        const bool = await GetProcessEnvInfo2Clone(ref.int(ProcessID || -1),
            HMC2_MODE.ENV_INFO_COMMAND.GET_EXIST_PROCESS);
        return !!ref.int(bool);
    }

    /**
     * 判断进程存在性
     * @docs 1.句柄能够打开->true  2.句柄不能打开-> 枚举进程ID列表 -> true/false
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns 
     */
    export function existProcess2Sync(ProcessID?: number): boolean {
        const bool = GetProcessEnvInfo2SyncClone(ref.int(ProcessID || -1),
            HMC2_MODE.ENV_INFO_COMMAND.GET_EXIST_PROCESS);
        return !!ref.int(bool);
    }

    /**
     * 获取父进程ID
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns 
     */
    export async function getParentProcess2(ProcessID?: number): Promise<number | null> {
        const long = await GetProcessEnvInfo2Clone(ref.int(ProcessID || -1),
            HMC2_MODE.ENV_INFO_COMMAND.GET_PARENT_PROCESS_ID);
        return ref.int(long || 0) || null;
        ;
    }

    /**
     * 获取父进程ID
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns 
     */
    export function getParentProcess2Sync(ProcessID?: number): number | null {
        return ref.int(GetProcessEnvInfo2SyncClone(ref.int(ProcessID || -1),
            HMC2_MODE.ENV_INFO_COMMAND.GET_PARENT_PROCESS_ID) || 0) || null;
    }

    /**
     * 枚举 指定/当前 的子进程
     * @param FindProcessID 查找的进程
     * @default 当前进程  [ process.pid ]
     * @returns 
     */
    export async function getSubProcess2(ProcessID: number): Promise<number[]> {
        const anyJSON = await GetProcessEnvInfo2Clone(ref.int(ProcessID || -1),
            HMC2_MODE.ENV_INFO_COMMAND.GET_SUB_PROCESS);
        return JSON.parse(anyJSON || "[]") as number[];
        ;
    }

    /**
     * 枚举 指定/当前 的子进程
     * @param FindProcessID 查找的进程
     * @default 当前进程  [ process.pid ]
     * @returns 
     */
    export function getSubProcess2Sync(ProcessID?: number): number[] {
        return JSON.parse((GetProcessEnvInfo2SyncClone(ref.int(ProcessID || -1),
            HMC2_MODE.ENV_INFO_COMMAND.GET_SUB_PROCESS) || "[]"));
    }

    /**
     * 枚举 指定/所有 的线程
     * @param FindProcessID 查找的进程 
     * @default all
     * @returns 
     */
    export async function getProcessThreadList2(FindProcessID?: number): Promise<HMC2_MODE.THREADENTRY32[]> {
        const anyJSON = await GetProcessEnvInfo2Clone(ref.int(FindProcessID || -1),
            HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_THREAD_LIST);
        return JSON.parse(anyJSON || "[]");

    }

    /**
     * 枚举 指定/所有 的线程
     * @param FindProcessID 查找的进程 
     * @default all
     * @returns 
     */
    export function getProcessThreadList2Sync(FindProcessID?: number): HMC2_MODE.THREADENTRY32[] {
        return JSON.parse((GetProcessEnvInfo2SyncClone(ref.int(FindProcessID || -1),
            HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_THREAD_LIST) || "[]"));
    }

    /**
     * 帮我尽可能的查找此进程的所有有可能的工作路径
     * @param FindProcessID 查找的进程 
     * @default 当前进程  [ process.pid ]
     * @returns 
     */
    export async function getExecutableCwdList2(FindProcessID?: number): Promise<string[]> {
        const anyJSON = await GetProcessEnvInfo2Clone(ref.int(FindProcessID || process.pid),
            HMC2_MODE.ENV_INFO_COMMAND.GET_EXECUTABLE_CWD_LIST);
        return JSON.parse(anyJSON || "[]");

    }

    /**
     * 帮我尽可能的查找此进程的所有有可能的工作路径
     * @param FindProcessID 查找的进程 
     * @default 当前进程  [ process.pid ]
     * @returns 
     */
    export function getExecutableCwdList2Sync(FindProcessID?: number): string[] {
        return JSON.parse((GetProcessEnvInfo2SyncClone(ref.int(FindProcessID || process.pid),
            HMC2_MODE.ENV_INFO_COMMAND.GET_EXECUTABLE_CWD_LIST) || "[]"));
    }


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
    export function getProcessName2(pid: number): Promise<string | null>;
    export function getProcessName2(pid: number, type: HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII): Promise<string[]>;
    export function getProcessName2(pid: number, type: HMC2_MODE.GET_PROCESS_NAME_TYPE): Promise<string | null>;
    export async function getProcessName2(pid: number, type?: unknown): Promise<unknown> {

        if (!main.Native.native.getProcessName2) {
            if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
                return Promise.resolve([]);
            }
            return Promise.resolve(null);
        }

        const data: string | null | string[] = await main.Native.native.getProcessName2(ref.int(pid), type ? ref.int(type) : undefined) as string | null | string[];

        if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
            const data_list = data ? Array.isArray(data) ? data : data?.split("\0") : [];
            return data_list.filter(item => item);
        }
        return data ? String(data) : null;
    }

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
    export function getProcessName2Sync(pid: number): string | null;
    export function getProcessName2Sync(pid: number, type: HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII): string[];
    export function getProcessName2Sync(pid: number, type: HMC2_MODE.GET_PROCESS_NAME_TYPE): string | null;
    export function getProcessName2Sync(pid: number, type?: unknown): unknown {
        if (!main.Native.native.getProcessName2Sync) {
            if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
                return [];
            }
            return null;
        }

        const data: string | null | string[] = main.Native.native.getProcessName2Sync(ref.int(pid), type ? ref.int(type) : undefined) as string | null | string[];

        if (type == HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII) {
            const data_list = data ? Array.isArray(data) ? data : data?.split("\0") : [];
            return data_list.filter(item => item);
        }

        return data ? String(data) : null;
    }

}