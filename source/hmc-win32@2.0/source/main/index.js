"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.native = exports.HMC2 = void 0;
var HMC2;
(function (HMC2) {
    let FS_MK_LINK_TARGET_TYPE;
    (function (FS_MK_LINK_TARGET_TYPE) {
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_DIR_SYMLINK"] = 166] = "CREATE_DIR_SYMLINK";
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_SYMLINK"] = 168] = "CREATE_SYMLINK";
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_HARD_LINK"] = 170] = "CREATE_HARD_LINK";
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_SYMBOLIC_LINK"] = 172] = "CREATE_SYMBOLIC_LINK";
    })(FS_MK_LINK_TARGET_TYPE = HMC2.FS_MK_LINK_TARGET_TYPE || (HMC2.FS_MK_LINK_TARGET_TYPE = {}));
    HMC2.HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
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
    })(MouseKeyName = HMC2.MouseKeyName || (HMC2.MouseKeyName = {}));
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
    })(MouseKey = HMC2.MouseKey || (HMC2.MouseKey = {}));
})(HMC2 = exports.HMC2 || (exports.HMC2 = {}));
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
exports.native = new HMC2_Native();
