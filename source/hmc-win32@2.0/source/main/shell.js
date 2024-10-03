"use strict";
var __classPrivateFieldGet = (this && this.__classPrivateFieldGet) || function (receiver, state, kind, f) {
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a getter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot read private member from an object whose class did not declare it");
    return kind === "m" ? f : kind === "a" ? f.call(receiver) : f ? f.value : state.get(receiver);
};
var __classPrivateFieldSet = (this && this.__classPrivateFieldSet) || function (receiver, state, value, kind, f) {
    if (kind === "m") throw new TypeError("Private method is not writable");
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a setter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot write private member to an object whose class did not declare it");
    return (kind === "a" ? f.call(receiver, value) : f ? f.value = value : state.set(receiver, value)), value;
};
var _StartupConstructor_instances, _StartupConstructor_Startup, _StartupConstructor_initialize, _StartupConstructor_root, _StartupConstructor_pathRun, _StartupConstructor_pathRunOnce;
Object.defineProperty(exports, "__esModule", { value: true });
exports.Shell = void 0;
const main = require("./index");
const util = require("./util");
const PromiseEval = require("./promiseEval");
const { ref } = util;
class StartupConstructor {
    constructor() {
        _StartupConstructor_instances.add(this);
        _StartupConstructor_Startup.set(this, null);
        _StartupConstructor_root.set(this, "HKEY_LOCAL_MACHINE");
        _StartupConstructor_pathRun.set(this, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
        _StartupConstructor_pathRunOnce.set(this, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce");
    }
    has(keyName) {
        var _a;
        __classPrivateFieldGet(this, _StartupConstructor_instances, "m", _StartupConstructor_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _StartupConstructor_Startup, "f")) === null || _a === void 0 ? void 0 : _a.has(ref.string(keyName))) || false;
    }
    hasOnce(keyName) {
        var _a;
        __classPrivateFieldGet(this, _StartupConstructor_instances, "m", _StartupConstructor_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _StartupConstructor_Startup, "f")) === null || _a === void 0 ? void 0 : _a.hasOnce(ref.string(keyName))) || false;
    }
    remove(keyName) {
        var _a;
        __classPrivateFieldGet(this, _StartupConstructor_instances, "m", _StartupConstructor_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _StartupConstructor_Startup, "f")) === null || _a === void 0 ? void 0 : _a.remove(ref.string(keyName))) || false;
    }
    removeOnce(keyName) {
        var _a;
        __classPrivateFieldGet(this, _StartupConstructor_instances, "m", _StartupConstructor_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _StartupConstructor_Startup, "f")) === null || _a === void 0 ? void 0 : _a.removeOnce(ref.string(keyName))) || false;
    }
    set(keyName, path, cmd) {
        var _a;
        __classPrivateFieldGet(this, _StartupConstructor_instances, "m", _StartupConstructor_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _StartupConstructor_Startup, "f")) === null || _a === void 0 ? void 0 : _a.set(ref.string(keyName), ref.string(path), ref.string(cmd || ""))) || false;
    }
    setOnce(keyName, path, cmd) {
        var _a;
        __classPrivateFieldGet(this, _StartupConstructor_instances, "m", _StartupConstructor_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _StartupConstructor_Startup, "f")) === null || _a === void 0 ? void 0 : _a.setOnce(ref.string(keyName), ref.string(path), ref.string(cmd || ""))) || false;
    }
    enum() {
        const obj = {};
        // const keys = native.enumRegistrKey(this.#root, this.#pathRun);
        // for (let index = 0; index < keys.length; index++) {
        //     let at = keys[index];
        //     obj[at] = native.getStringRegKey(this.#root, this.#pathRun, at);
        // }
        return obj;
    }
    enumOnce() {
        const obj = {};
        // const keys = native.enumRegistrKey(this.#root, this.#pathRunOnce);
        // for (let index = 0; index < keys.length; index++) {
        //     let at = keys[index];
        //     obj[at] = native.getStringRegKey(this.#root, this.#pathRunOnce, at);
        // }
        return obj;
    }
    keys() {
        return [];
        // return native.enumRegistrKey(this.#root,this.#pathRun);
    }
    keysOnce() {
        return [];
        // return native.enumRegistrKey(this.#root,this.#pathRunOnce);
    }
}
_StartupConstructor_Startup = new WeakMap(), _StartupConstructor_root = new WeakMap(), _StartupConstructor_pathRun = new WeakMap(), _StartupConstructor_pathRunOnce = new WeakMap(), _StartupConstructor_instances = new WeakSet(), _StartupConstructor_initialize = function _StartupConstructor_initialize() {
    if (!__classPrivateFieldGet(this, _StartupConstructor_Startup, "f") && main.Native.native.HMC_SHELL_STARTUP_CLASS) {
        __classPrivateFieldSet(this, _StartupConstructor_Startup, main.Native.native.HMC_SHELL_STARTUP_CLASS(), "f");
    }
};
var Shell;
(function (Shell) {
    /**
     * 启动项 管理
     */
    Shell.Startup = new StartupConstructor();
    /**
     * 截图为Bmp 文件/Buffer
     */
    Shell.captureBmp2 = PromiseEval.promiseEvalTask.captureBmp2;
    /**
    * 截图为Bmp 文件/Buffer
    */
    Shell.captureBmp2Sync = PromiseEval.promiseEvalTask.captureBmp2Sync;
    // 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
    Shell.getThumbnailPng2 = PromiseEval.promiseEvalTask.getThumbnailPng2;
    // 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
    Shell.getThumbnailPng2Sync = PromiseEval.promiseEvalTask.getThumbnailPng2Sync;
    // 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
    Shell.getFileIcon2 = PromiseEval.promiseEvalTask.getThumbnailPng2;
    // 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
    Shell.getFileIcon2Sync = PromiseEval.promiseEvalTask.getThumbnailPng2Sync;
    /**
     * 弹出右键菜单的接口
     * @param hwnd 调用窗口 / 允许为null
     * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
     * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
     * @param y 坐标
     */
    function showContextMenu(hwnd, file, x, y) {
        var _a, _b;
        return ((_a = main.Native.native) === null || _a === void 0 ? void 0 : _a.showContextMenu) ?
            (_b = main.Native.native) === null || _b === void 0 ? void 0 : _b.showContextMenu(ref.int(hwnd || 0), Array.isArray(file) ? file : ref.string(file), ref.int(x || 0), ref.int(y || 0))
            : false;
    }
    Shell.showContextMenu = showContextMenu;
    /**
     * 获取托盘图标列表
     * 1.4.6 起返回json文本
     * ? win11 在22621.1000版本之后失效 具体原因查看https://github.com/kihlh/hmc-win32/issues/36
     */
    function getTrayList() {
        if (!main.Native.native.getTrayList)
            return [];
        return JSON.parse(main.Native.native.getTrayList());
    }
    Shell.getTrayList = getTrayList;
    /**
     * 设置文件夹的缩略图
     * @param folderPath 路径
     * @param iconPath 图标路径
     * @param iconIndex 图标索引 比如exe中的0
     * @returns
     */
    function setFolderIcon(folderPath, iconPath, iconIndex) {
        if (!main.Native.native.setFolderIcon)
            return false;
        return main.Native.native.setFolderIcon(ref.string(folderPath), ref.string(iconPath), ref.int(iconIndex || 0));
    }
    Shell.setFolderIcon = setFolderIcon;
})(Shell = exports.Shell || (exports.Shell = {}));
