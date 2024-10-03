"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Window = exports.Registr = exports.sleep = exports.Sleep = exports.Process = exports.Shell = exports.Startup = exports.Auto = exports.ref = exports.Native = exports.HMC2_MODE = void 0;
const ShellMain = require("./shell");
const AutoMain = require("./auto");
const UtilMain = require("./util");
const ProcessMain = require("./Process");
const RegistrMain = require("./registr");
var HMC2_MODE;
(function (HMC2_MODE) {
    /**注册表根目录 */
    HMC2_MODE.Hkey = {
        /**用作默认用户首选设置|也作为单个用户的首选设置 */
        HKEY_CURRENT_CONFIG: "HKEY_CURRENT_CONFIG",
        /**用作默认用户首选设置|也作为单个用户的首选设置 */
        HKEY_USERS: "HKEY_USERS",
        /**是与文档类型和 OLE\COM 相关的信息的支持键。这个键是 */
        HKEY_CLASSES_ROOT: "HKEY_CLASSES_ROOT",
        /**包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息 */
        HKEY_LOCAL_MACHINE: "HKEY_LOCAL_MACHINE",
        /**管理系统当前的用户信息 */
        HKEY_CURRENT_USER: "HKEY_CURRENT_USER",
    };
    /**
     * 注册表格式类型
     */
    let REG_TYPE;
    (function (REG_TYPE) {
        /** 没有值 */
        REG_TYPE[REG_TYPE["REG_NONE"] = 0] = "REG_NONE";
        /** 以空字符结尾的字符串 */
        REG_TYPE[REG_TYPE["REG_SZ"] = 1] = "REG_SZ";
        /** 可扩展的字符串（例如环境变量） */
        REG_TYPE[REG_TYPE["REG_EXPAND_SZ"] = 2] = "REG_EXPAND_SZ";
        /** 原始的二进制数据 */
        REG_TYPE[REG_TYPE["REG_BINARY"] = 3] = "REG_BINARY";
        /** 32位数字，使用小端字节序 */
        REG_TYPE[REG_TYPE["REG_DWORD"] = 4] = "REG_DWORD";
        /** 32位数字，使用小端字节序（与 REG_DWORD 相同） */
        REG_TYPE[REG_TYPE["REG_DWORD_LITTLE_ENDIAN"] = 4] = "REG_DWORD_LITTLE_ENDIAN";
        /** 32位数字，使用大端字节序 */
        REG_TYPE[REG_TYPE["REG_DWORD_BIG_ENDIAN"] = 5] = "REG_DWORD_BIG_ENDIAN";
        /** 符号链接，使用 Unicode 编码 */
        REG_TYPE[REG_TYPE["REG_LINK"] = 6] = "REG_LINK";
        /** 多个以空字符结尾的 Unicode 字符串 */
        REG_TYPE[REG_TYPE["REG_MULTI_SZ"] = 7] = "REG_MULTI_SZ";
        /** 资源列表，存储在资源映射中 */
        REG_TYPE[REG_TYPE["REG_RESOURCE_LIST"] = 8] = "REG_RESOURCE_LIST";
        /** 硬件描述中的资源列表 */
        REG_TYPE[REG_TYPE["REG_FULL_RESOURCE_DESCRIPTOR"] = 9] = "REG_FULL_RESOURCE_DESCRIPTOR";
        /** 资源需求列表 */
        REG_TYPE[REG_TYPE["REG_RESOURCE_REQUIREMENTS_LIST"] = 10] = "REG_RESOURCE_REQUIREMENTS_LIST";
        /** 64位数字，使用小端字节序 */
        REG_TYPE[REG_TYPE["REG_QWORD"] = 11] = "REG_QWORD";
        /** 64位数字，使用小端字节序（与 REG_QWORD 相同） */
        REG_TYPE[REG_TYPE["REG_QWORD_LITTLE_ENDIAN"] = 11] = "REG_QWORD_LITTLE_ENDIAN";
    })(REG_TYPE = HMC2_MODE.REG_TYPE || (HMC2_MODE.REG_TYPE = {}));
    let FS_MK_LINK_TARGET_TYPE;
    (function (FS_MK_LINK_TARGET_TYPE) {
        /**
         * 文件夹链接
         */
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_DIR_SYMLINK"] = 166] = "CREATE_DIR_SYMLINK";
        /**
         * 软链接
         */
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_SYMLINK"] = 168] = "CREATE_SYMLINK";
        /**
         * 硬链接
         */
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_HARD_LINK"] = 170] = "CREATE_HARD_LINK";
        /**
         * 目录连接点
         */
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_SYMBOLIC_LINK"] = 172] = "CREATE_SYMBOLIC_LINK";
    })(FS_MK_LINK_TARGET_TYPE = HMC2_MODE.FS_MK_LINK_TARGET_TYPE || (HMC2_MODE.FS_MK_LINK_TARGET_TYPE = {}));
    HMC2_MODE.HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
    // 鼠标按钮变化
    let MouseKeyName;
    (function (MouseKeyName) {
        MouseKeyName["UNKNOWN"] = "unknown";
        // 左键按下
        MouseKeyName["WM_LBUTTONDOWN"] = "left-button-down";
        // 右键按下
        MouseKeyName["WM_RBUTTONDOWN"] = "right-button-down";
        // 左键释放
        MouseKeyName["WM_LBUTTONUP"] = "left-button-up";
        // 右键释放
        MouseKeyName["WM_RBUTTONUP"] = "right-button-up";
        // 中键按下
        MouseKeyName["WM_MBUTTONDOWN"] = "mouse-button-down";
        // 中键释放
        MouseKeyName["WM_MBUTTONUP"] = "mouse-button-up";
        // 滚轮向上
        MouseKeyName["WM_MOUSEWHEEL"] = "mouse-wheel";
        // 鼠标移动
        MouseKeyName["WM_MOUSEMOVE"] = "move";
    })(MouseKeyName = HMC2_MODE.MouseKeyName || (HMC2_MODE.MouseKeyName = {}));
    // 鼠标按钮变化
    let MouseKey;
    (function (MouseKey) {
        MouseKey[MouseKey["WM_MOUSEMOVE"] = 512] = "WM_MOUSEMOVE";
        // 左键按下
        MouseKey[MouseKey["WM_LBUTTONDOWN"] = 513] = "WM_LBUTTONDOWN";
        // 右键按下
        MouseKey[MouseKey["WM_RBUTTONDOWN"] = 516] = "WM_RBUTTONDOWN";
        // 左键释放
        MouseKey[MouseKey["WM_LBUTTONUP"] = 514] = "WM_LBUTTONUP";
        // 右键释放
        MouseKey[MouseKey["WM_RBUTTONUP"] = 517] = "WM_RBUTTONUP";
        // 中键按下
        MouseKey[MouseKey["WM_MBUTTONDOWN"] = 519] = "WM_MBUTTONDOWN";
        // 中键释放
        MouseKey[MouseKey["WM_MBUTTONUP"] = 520] = "WM_MBUTTONUP";
        // 滚轮
        MouseKey[MouseKey["WM_MOUSEWHEEL"] = 522] = "WM_MOUSEWHEEL";
    })(MouseKey = HMC2_MODE.MouseKey || (HMC2_MODE.MouseKey = {}));
    let ENV_INFO_COMMAND;
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
        // sleep(ms);
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["SEND_SLEEP"] = 22] = "SEND_SLEEP";
    })(ENV_INFO_COMMAND = HMC2_MODE.ENV_INFO_COMMAND || (HMC2_MODE.ENV_INFO_COMMAND = {}));
    ;
    let GET_PROCESS_NAME_TYPE;
    (function (GET_PROCESS_NAME_TYPE) {
        // 查找所有名字
        GET_PROCESS_NAME_TYPE[GET_PROCESS_NAME_TYPE["GET_AII"] = 1] = "GET_AII";
        // 使用内核法查找
        GET_PROCESS_NAME_TYPE[GET_PROCESS_NAME_TYPE["GET_NT"] = 2] = "GET_NT";
        // 获取进程快照的名字
        GET_PROCESS_NAME_TYPE[GET_PROCESS_NAME_TYPE["GET_SNP"] = 3] = "GET_SNP";
        // 找到时就停下 [默认]
        GET_PROCESS_NAME_TYPE[GET_PROCESS_NAME_TYPE["GET_FIND"] = 5] = "GET_FIND";
        // 找模块名
        GET_PROCESS_NAME_TYPE[GET_PROCESS_NAME_TYPE["GET_MODE"] = 7] = "GET_MODE";
        // 默认 找到时就停下 
        GET_PROCESS_NAME_TYPE[GET_PROCESS_NAME_TYPE["GET_DEFAULT"] = 0] = "GET_DEFAULT";
        // 即便是从可执行文件中路径获取文件名也行
        GET_PROCESS_NAME_TYPE[GET_PROCESS_NAME_TYPE["GET_FILE_NAME"] = 8] = "GET_FILE_NAME";
    })(GET_PROCESS_NAME_TYPE = HMC2_MODE.GET_PROCESS_NAME_TYPE || (HMC2_MODE.GET_PROCESS_NAME_TYPE = {}));
    ;
    (function (ENV_INFO_COMMAND) {
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["NONE"] = 0] = "NONE";
        // export function getRegistrQword(HKey: HKEY, SubKey: string, key: string | null): bigint | null;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_REGISTR_QWORD"] = 70] = "GET_REGISTR_QWORD";
        // export function setRegistrQword(HKey: HKEY, SubKey: string, key: string | null, Qword: bigint | number): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["SET_REGISTR_QWORD"] = 71] = "SET_REGISTR_QWORD";
        // export function getRegistrDword(HKey: HKEY, SubKey: string, key: string | null): number | null;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_REGISTR_DWORD"] = 72] = "GET_REGISTR_DWORD";
        // export function setRegistrDword(HKey: HKEY, SubKey: string, key: string | null, Dword: bigint | number): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["SET_REGISTR_DWORD"] = 73] = "SET_REGISTR_DWORD";
        // export function getRegistrString(HKey: HKEY, SubKey: string, key: string | null): string | null;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_REGISTR_STRING"] = 74] = "GET_REGISTR_STRING";
        // export function setRegistrString(HKey: HKEY, SubKey: string, key: string | null, String: string): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["SET_REGISTR_STRING"] = 75] = "SET_REGISTR_STRING";
        // export function getRegistrKeys(HKey: HKEY, SubKey: string, key: string | null): chQueryFolderKey;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_REGISTR_KEYS"] = 76] = "GET_REGISTR_KEYS";
        // export function getRegistrStringList(HKey: HKEY, SubKey: string, key: string | null): string[] | null;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_REGISTR_STRING_LIST"] = 77] = "GET_REGISTR_STRING_LIST";
        // export function setRegistrStringList(HKey: HKEY, SubKey: string, key: string | null, StringList?: string[]): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["SET_REGISTR_STRING_LIST"] = 78] = "SET_REGISTR_STRING_LIST";
        // export function getRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null): Buffer | null;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_REGISTR_BUFFER"] = 79] = "GET_REGISTR_BUFFER";
        // export function setRegistrBuffer(HKey: HKEY, SubKey: string, key: string | null, String: Buffer): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["SET_REGISTR_BUFFER"] = 710] = "SET_REGISTR_BUFFER";
        // export function getRegistrValue(HKey: HKEY, SubKey: string, key: string | null): REG_VALUE | null;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_REGISTR_VALUE"] = 711] = "GET_REGISTR_VALUE";
        // export function copyRegistrValue(HKey: HKEY, SourceSubKey: string, Sourcekey: string | null, NewSubKey: string, Newkey: string | null): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["COPY_REGISTR_VALUE"] = 712] = "COPY_REGISTR_VALUE";
        // export function copyRegistrFolder(HKey: HKEY, SourceSubKey: string, NewSubKey: string): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["COPY_REGISTR_FOLDER"] = 713] = "COPY_REGISTR_FOLDER";
        // export function setRegistrValue(HKey: HKEY, SubKey: string, key: string | null, data: REG_VALUE): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["SET_REGISTR_VALUE"] = 714] = "SET_REGISTR_VALUE";
        // export function getRegistrValueStat(HKey: HKEY, SubKey: string, key: string | null): RegistrValueStat;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_REGISTR_VALUE_STAT"] = 715] = "GET_REGISTR_VALUE_STAT";
        // export function getRegistrFolderStat(HKey: HKEY, SubKey: string, key: string | null): RegistrFolderStat;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["GET_REGISTR_FOLDER_STAT"] = 716] = "GET_REGISTR_FOLDER_STAT";
        // export function clearRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["CLEAR_REGISTR_VALUE"] = 717] = "CLEAR_REGISTR_VALUE";
        // export function clearRegistrFolder(HKey: HKEY, SubKey: string, key: string | null): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["CLEAR_REGISTR_FOLDER"] = 718] = "CLEAR_REGISTR_FOLDER";
        // export function removeRegistrValue(HKey: HKEY, SubKey: string, key: string | null): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["REMOVE_REGISTR_VALUE"] = 719] = "REMOVE_REGISTR_VALUE";
        // export function removeRegistrFolder(HKey: HKEY, SubKey: string): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["REMOVE_REGISTR_FOLDER"] = 720] = "REMOVE_REGISTR_FOLDER";
        // export function removeRegistrFolderTree(HKey: HKEY, SubKey: string): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["REMOVE_REGISTR_FOLDER_TREE"] = 721] = "REMOVE_REGISTR_FOLDER_TREE";
        // export function createRegistrFolder(HKey: HKEY, SubKey: string): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["CREATE_REGISTR_FOLDER"] = 722] = "CREATE_REGISTR_FOLDER";
        // export function createRegistrValueKey(HKey: HKEY, SubKey: string, key: string | string[]): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["CREATE_REGISTR_VALUE_KEY"] = 723] = "CREATE_REGISTR_VALUE_KEY";
        // export function hasRegistrKey(HKey: HKEY, SubKey: string, key: string | null): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["HAS_REGISTR_KEY"] = 724] = "HAS_REGISTR_KEY";
        // export function hasRegistrFolderKey(HKey: HKEY, SubKey: string): boolean;
        ENV_INFO_COMMAND[ENV_INFO_COMMAND["HAS_REGISTR_FOLDER_KEY"] = 725] = "HAS_REGISTR_FOLDER_KEY";
    })(ENV_INFO_COMMAND = HMC2_MODE.ENV_INFO_COMMAND || (HMC2_MODE.ENV_INFO_COMMAND = {}));
    ;
})(HMC2_MODE = exports.HMC2_MODE || (exports.HMC2_MODE = {}));
exports.Native = (() => {
    const run = {};
    let _BinPath = "";
    let _Native = {};
    let _Loaded = false;
    function LoadNodeBin() {
        try {
            // Debug 环境带入
            if (process.env) {
                if (process.env.USERNAME == "kiic" && process.env.msvc_dir && process.env.mode) {
                    _BinPath = process.env.mode;
                    _Native = require(_BinPath);
                    return _Native;
                }
            }
            if (_BinPath) {
                _Native = require(_BinPath);
                return _Native;
            }
            else {
                if (process.arch.match(/^(x32|ia32)$/)) {
                    return require("./bin/HMC@Beta_x86.node");
                }
                if (process.arch.match(/^x64$/)) {
                    return require("./bin/HMC@Beta_x64.node");
                }
            }
        }
        catch (s_O) { }
        return {};
    }
    Object.defineProperty(run, "native", {
        // configurable:false,
        enumerable: false,
        // writable:false,
        get: function () {
            if (!_Loaded && !_BinPath) {
                if (process.arch.match(/^(x32|ia32)$/)) {
                    _BinPath = "./bin/HMC@Beta_x86.node";
                }
                if (process.arch.match(/^x64$/)) {
                    _BinPath = "./bin/HMC@Beta_x64.node";
                }
            }
            if (!_Loaded) {
                _Native = LoadNodeBin();
            }
            return _Native;
        },
        set(v) { }
    });
    return run;
})();
exports.ref = UtilMain.ref;
// 键鼠/自动化相关
exports.Auto = AutoMain;
// 启动项管理
exports.Startup = ShellMain.Shell.Startup;
// win32 shell(壳) api 继承
exports.Shell = ShellMain.Shell;
// 进程操作功能集
exports.Process = ProcessMain.Process;
exports.Sleep = exports.Process.Sleep, exports.sleep = exports.Process.sleep;
//注册表编辑合集
exports.Registr = RegistrMain.Registr;
var Window;
(function (Window) {
    /**
     * 将 electron 句柄内存缓冲区转换为标准 窗口数字句柄
     * @param handleBuffer 例如 Electron.BrowserWindow.getFocusedWindow().getNativeWindowHandle()
     * @returns
     */
    function readElectronHandle(handleBuffer) {
        let num = 0;
        // Node.js 10.5.0 以上版本
        if (typeof BigInt != 'undefined') {
            let handleBigInt = handleBuffer.readBigUInt64LE();
            return (Number(handleBigInt));
        }
        else {
            if (process.platform == 'win32') {
                num = handleBuffer.readUInt32LE();
            }
            else if (process.platform == 'darwin') {
                num = handleBuffer.readUInt32LE(0) + 2 * 32 * handleBuffer.readUInt32LE(4);
            }
            else {
                num = handleBuffer.readUInt32LE(0) + 2 * 32 * handleBuffer.readUInt32LE(4);
            }
            return num;
        }
        return num;
    }
    Window.readElectronHandle = readElectronHandle;
})(Window = exports.Window || (exports.Window = {}));
