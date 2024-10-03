import { HMC2_MODE } from "./index";
export declare module Process {
    /**
     * 获取指定进程的工作目录
     * @dosc 由于跨进程权限问题 不保证获取得到
     * !此功能需要读取进程内存
     * @module 异步async
     * @returns
     */
    function getProcessCwdPath2(ProcessID: number): Promise<null | string>;
    /**
     * 获取指定进程的工作目录
     * @dosc 由于跨进程权限问题 不保证获取得到
     * !此功能需要读取进程内存
     * @module 同步Sync
     * @returns
     */
    function getProcessCwdPath2Sync(ProcessID: number): null | string;
    /**
     * 读取指定进程的启动命令行  `Async(异步)`
     * @dosc 由于跨进程权限问题 不保证获取得到
     * ?此功能在win8及以下系统 需要读取进程内存
     * @module 异步async
     * @param ProcessID 进程id
     * @returns
     */
    function getProcessCommandLine2(ProcessID: number): Promise<null | string>;
    /**
     * 读取指定进程的启动命令行  `Sync(同步)`
     * @dosc 由于跨进程权限问题 不保证获取得到
     * ?此功能在win8及以下系统 需要读取进程内存
     * @module 同步Sync
     * @param ProcessID 进程id
     * @returns
     */
    function getProcessCommandLine2Sync(ProcessID: number): null | string;
    /**
     * 读取指定进程的CPU占比  `Async(异步)`
     * @param ProcessID 进程id
     * @time >= 1000ms
     * @returns
     */
    function getProcessCpuUsage2(ProcessID: number): Promise<number>;
    /**
     * 读取指定进程的CPU占比  `Sync(同步)`
     * @param ProcessID 进程id
     * @time >= 1000ms
     */
    function getProcessCpuUsage2Sync(ProcessID: number): number;
    /**
     * 读取指定进程的CPU占比  `Async(异步)`
     * @param ProcessID 进程id
     * @time >= 1000ms
     */
    function getProcessStartTime2(ProcessID: number): Promise<number>;
    /**
     * 读取指定进程的启动时间  `Sync(同步)`
     * @param ProcessID 进程id
     */
    function getProcessStartTime2Sync(ProcessID: number): number;
    function getAllProcessList2(): Promise<HMC2_MODE.PROCESSENTRY_DEFAULT[]>;
    function getAllProcessList2(is_execPath: false): Promise<HMC2_MODE.PROCESSENTRY_NONE_NAME[]>;
    function getAllProcessList2(is_execPath: true): Promise<HMC2_MODE.PROCESSENTRY_DEFAULT[]>;
    function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST): Promise<number[]>;
    function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS): Promise<HMC2_MODE.PROCESSENTRY_DEFAULT[]>;
    function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP): Promise<HMC2_MODE.PROCESSENTRY[]>;
    function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT): Promise<HMC2_MODE.PSYSTEM_PROCESS_INFORMATION[]>;
    function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NONE_NAME): Promise<HMC2_MODE.PROCESSENTRY_NONE_NAME[]>;
    function getAllProcessList2(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_PID_NAME): Promise<HMC2_MODE.PROCESSENTRY_DEFAULT[]>;
    function getAllProcessList2Sync(): HMC2_MODE.PROCESSENTRY_DEFAULT[];
    function getAllProcessList2Sync(is_execPath: false): HMC2_MODE.PROCESSENTRY_NONE_NAME[];
    function getAllProcessList2Sync(is_execPath: true): HMC2_MODE.PROCESSENTRY_DEFAULT[];
    function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ENUM_PROCESSES_LIST): number[];
    function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_DETAILS): HMC2_MODE.PROCESSENTRY_DEFAULT[];
    function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_SNP): HMC2_MODE.PROCESSENTRY[];
    function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NT): HMC2_MODE.PSYSTEM_PROCESS_INFORMATION[];
    function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_NONE_NAME): HMC2_MODE.PROCESSENTRY_NONE_NAME[];
    function getAllProcessList2Sync(is_execPath: HMC2_MODE.ENV_INFO_COMMAND.GET_ALL_PROCESS_LIST_PID_NAME): HMC2_MODE.PROCESSENTRY_DEFAULT[];
    /**
     * 获取内核进程快照
     * @returns
     */
    function getAllProcessListNt2(): Promise<HMC2_MODE.PSYSTEM_PROCESS_INFORMATION[]>;
    /**
     * 获取内核进程快照
     * @returns
     */
    function getAllProcessListNt2Sync(): HMC2_MODE.PSYSTEM_PROCESS_INFORMATION[];
    /**
     * 获取进程快照
     * @returns
     */
    function getAllProcessListSnp2(): Promise<HMC2_MODE.PROCESSENTRY[]>;
    /**
     * 获取进程快照
     * @returns
     */
    function getAllProcessListSnp2Sync(): HMC2_MODE.PROCESSENTRY[];
    /**
     * 获取带有文件路径的进程列表
     * @returns
     */
    function getDetailsProcessList2(): Promise<HMC2_MODE.PROCESSENTRY_DEFAULT[]>;
    /**
     * 获取带有文件路径的进程列表
     * @returns
     */
    function getDetailsProcessList2Sync(): HMC2_MODE.PROCESSENTRY_DEFAULT[];
    /**
     * 枚举进程列表(pid)
     * @returns
     */
    function enumAllProcess2(): Promise<number[]>;
    /**
     * 枚举进程列表(pid)
     * @returns
     */
    function enumAllProcess2Sync(): number[];
    /**
     * 判断进程是否正在以Wow64仿真器运行
     * @docs 当进程是x86方式编译的 而系统是x64 进程将在wow64容器下仿真器执行
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function isProcessWow64(ProcessID?: number): Promise<boolean>;
    /**
     * 判断进程是否正在以Wow64仿真器运行
     * @docs 当进程是x86方式编译的 而系统是x64 进程将在wow64容器下仿真器执行
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function isProcessWow64Sync(ProcessID?: number): boolean;
    /**
     * 判断进程存在性
     * @docs 1.句柄能够打开->true  2.句柄不能打开-> 枚举进程ID列表 -> true/false
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function existProcess2(ProcessID?: number): Promise<boolean>;
    /**
     * 判断进程存在性
     * @docs 1.句柄能够打开->true  2.句柄不能打开-> 枚举进程ID列表 -> true/false
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function existProcess2Sync(ProcessID?: number): boolean;
    /**
     * 获取父进程ID
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function getParentProcess2(ProcessID?: number): Promise<number | null>;
    /**
     * 获取父进程ID
     * @param ProcessID 进程ID
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function getParentProcess2Sync(ProcessID?: number): number | null;
    /**
     * 枚举 指定/当前 的子进程
     * @param FindProcessID 查找的进程
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function getSubProcess2(ProcessID: number): Promise<number[]>;
    /**
     * 枚举 指定/当前 的子进程
     * @param FindProcessID 查找的进程
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function getSubProcess2Sync(ProcessID?: number): number[];
    /**
     * 枚举 指定/所有 的线程
     * @param FindProcessID 查找的进程
     * @default all
     * @returns
     */
    function getProcessThreadList2(FindProcessID?: number): Promise<HMC2_MODE.THREADENTRY32[]>;
    /**
     * 枚举 指定/所有 的线程
     * @param FindProcessID 查找的进程
     * @default all
     * @returns
     */
    function getProcessThreadList2Sync(FindProcessID?: number): HMC2_MODE.THREADENTRY32[];
    /**
     * 帮我尽可能的查找此进程的所有有可能的工作路径
     * @param FindProcessID 查找的进程
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function getExecutableCwdList2(FindProcessID?: number): Promise<string[]>;
    /**
     * 帮我尽可能的查找此进程的所有有可能的工作路径
     * @param FindProcessID 查找的进程
     * @default 当前进程  [ process.pid ]
     * @returns
     */
    function getExecutableCwdList2Sync(FindProcessID?: number): string[];
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
    function getProcessName2(pid: number): Promise<string | null>;
    function getProcessName2(pid: number, type: HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII): Promise<string[]>;
    function getProcessName2(pid: number, type: HMC2_MODE.GET_PROCESS_NAME_TYPE): Promise<string | null>;
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
    function getProcessName2Sync(pid: number): string | null;
    function getProcessName2Sync(pid: number, type: HMC2_MODE.GET_PROCESS_NAME_TYPE.GET_AII): string[];
    function getProcessName2Sync(pid: number, type: HMC2_MODE.GET_PROCESS_NAME_TYPE): string | null;
    /**
     * 获取指定进程的可执行文件路径
     * @param pid 进程id
     * @param isEnumListExists 是否必须出现在进程列表中的
     * @default false
     * @param isSnapshotName 获取失败时获取进程名称
     * @default false
     */
    function getProcessFilePath2(pid: number, isEnumListExists?: boolean, isSnapshotName?: boolean): Promise<string | null>;
    /**
     * 获取指定进程的可执行文件路径
     * @param pid 进程id
     * @param isEnumListExists 是否必须出现在进程列表中的
     * @default false
     * @param isSnapshotName 获取失败时获取进程名称
     * @default false
     */
    function getProcessFilePath2Sync(pid: number, isEnumListExists?: boolean, isSnapshotName?: boolean): string | null;
    /**
     * 获取匹配进程的 父进程信息
     * @param Process 需要被搜索的子进程 名称/pid/正则名称
     * @returns
     */
    function getProcessParentProcessMatch2(Process: string | RegExp): Promise<Array<HMC2_MODE.PROCESSENTRY>>;
    function getProcessParentProcessMatch2(Process: number): Promise<HMC2_MODE.PROCESSENTRY>;
    /**
     * 获取匹配进程的 父进程信息
     * @param Process 需要被搜索的子进程 名称/pid/正则名称
     * @returns
     */
    function getProcessParentProcessMatch2Sync(Process: string | RegExp): Array<HMC2_MODE.PROCESSENTRY>;
    function getProcessParentProcessMatch2Sync(Process: number): HMC2_MODE.PROCESSENTRY | null;
    /**
     * 按照名称搜索进程
     * @param ProcessName
     * @returns
     */
    function findProcess2(ProcessName: string | RegExp | number): Promise<{
        pid: number;
        name: string | null;
        path: string | null;
    }[]>;
    /**
     * 按照名称搜索进程
     * @param ProcessName
     * @returns
     */
    function findProcess2Sync(ProcessName: string | RegExp | number): Array<{
        pid: number;
        name: string;
        path: string;
    }>;
    /**
    * `Sync` 同步阻塞(进程)
    * @param awaitTime
    * @returns
    */
    function sleep(awaitTime: number): string | null;
    /**
     * `async` 异步阻塞(进程)
     * @param awaitTime
     * @returns
     */
    function Sleep(awaitTime: number, Sync?: boolean): Promise<unknown>;
}
