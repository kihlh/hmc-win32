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
})(Shell = exports.Shell || (exports.Shell = {}));
