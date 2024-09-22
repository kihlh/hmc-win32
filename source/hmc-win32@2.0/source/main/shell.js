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
var _Startup_instances, _Startup_Startup, _Startup_initialize, _Startup_root, _Startup_pathRun, _Startup_pathRunOnce;
Object.defineProperty(exports, "__esModule", { value: true });
exports.startup = void 0;
const main = require("./index");
const util = require("./util");
const { ref } = util;
const HMC2 = main.native;
class Startup {
    constructor() {
        _Startup_instances.add(this);
        _Startup_Startup.set(this, null);
        _Startup_root.set(this, "HKEY_LOCAL_MACHINE");
        _Startup_pathRun.set(this, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
        _Startup_pathRunOnce.set(this, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce");
    }
    has(keyName) {
        var _a;
        __classPrivateFieldGet(this, _Startup_instances, "m", _Startup_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _Startup_Startup, "f")) === null || _a === void 0 ? void 0 : _a.has(ref.string(keyName))) || false;
    }
    hasOnce(keyName) {
        var _a;
        __classPrivateFieldGet(this, _Startup_instances, "m", _Startup_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _Startup_Startup, "f")) === null || _a === void 0 ? void 0 : _a.hasOnce(ref.string(keyName))) || false;
    }
    remove(keyName) {
        var _a;
        __classPrivateFieldGet(this, _Startup_instances, "m", _Startup_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _Startup_Startup, "f")) === null || _a === void 0 ? void 0 : _a.remove(ref.string(keyName))) || false;
    }
    removeOnce(keyName) {
        var _a;
        __classPrivateFieldGet(this, _Startup_instances, "m", _Startup_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _Startup_Startup, "f")) === null || _a === void 0 ? void 0 : _a.removeOnce(ref.string(keyName))) || false;
    }
    set(keyName, path, cmd) {
        var _a;
        __classPrivateFieldGet(this, _Startup_instances, "m", _Startup_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _Startup_Startup, "f")) === null || _a === void 0 ? void 0 : _a.set(ref.string(keyName), ref.string(path), ref.string(cmd || ""))) || false;
    }
    setOnce(keyName, path, cmd) {
        var _a;
        __classPrivateFieldGet(this, _Startup_instances, "m", _Startup_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _Startup_Startup, "f")) === null || _a === void 0 ? void 0 : _a.setOnce(ref.string(keyName), ref.string(path), ref.string(cmd || ""))) || false;
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
_Startup_Startup = new WeakMap(), _Startup_root = new WeakMap(), _Startup_pathRun = new WeakMap(), _Startup_pathRunOnce = new WeakMap(), _Startup_instances = new WeakSet(), _Startup_initialize = function _Startup_initialize() {
    if (!__classPrivateFieldGet(this, _Startup_Startup, "f") && HMC2.native.HMC_SHELL_STARTUP_CLASS) {
        __classPrivateFieldSet(this, _Startup_Startup, HMC2.native.HMC_SHELL_STARTUP_CLASS(), "f");
    }
};
exports.startup = new Startup();
