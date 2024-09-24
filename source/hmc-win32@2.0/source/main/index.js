"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Process = exports.Shell = exports.Startup = exports.Auto = exports.ref = exports.Native = exports.HMC2_MODE = void 0;
const ShellMain = require("./shell");
const AutoMain = require("./auto");
const UtilMain = require("./util");
const ProcessMain = require("./Process");
var HMC2_MODE;
(function (HMC2_MODE) {
    let FS_MK_LINK_TARGET_TYPE;
    (function (FS_MK_LINK_TARGET_TYPE) {
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_DIR_SYMLINK"] = 166] = "CREATE_DIR_SYMLINK";
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_SYMLINK"] = 168] = "CREATE_SYMLINK";
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_HARD_LINK"] = 170] = "CREATE_HARD_LINK";
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
})(HMC2_MODE = exports.HMC2_MODE || (exports.HMC2_MODE = {}));
class HMC2_Native {
    constructor(binPath) {
        this._BinPath = "";
        this._Native = {};
        this._Loaded = false;
        if (binPath) {
            this._BinPath = binPath;
            return;
        }
        if (process.arch.match(/^(x32|ia32)$/)) {
            this._BinPath = "./bin/HMC@Beta_x86.node";
        }
        if (process.arch.match(/^x64$/)) {
            this._BinPath = "./bin/HMC@Beta_x64.node";
        }
    }
    LoadNodeBin() {
        try {
            // Debug 环境带入
            if (process.env) {
                if (process.env.USERNAME == "kiic" && process.env.msvc_dir && process.env.mode) {
                    this._BinPath = process.env.mode;
                    this._Native = require(this._BinPath);
                    return;
                }
            }
            if (this._BinPath) {
                this._Native = require(this._BinPath);
                return;
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
    }
    get native() {
        if (!this._Loaded) {
            this.LoadNodeBin();
            this._Loaded = true;
        }
        return this._Native;
    }
}
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
var Auto;
(function (Auto) {
    // 限制鼠标光标可移动范围 (异步)
    Auto.setLimitMouseRange = AutoMain.setLimitMouseRange;
})(Auto = exports.Auto || (exports.Auto = {}));
// 启动项管理
exports.Startup = ShellMain.Shell.Startup;
// win32 shell api
exports.Shell = ShellMain.Shell;
// 进程操作功能集
exports.Process = ProcessMain.Process;
