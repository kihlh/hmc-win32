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
var _HMC_MOUSE_CLASS_instances, _HMC_MOUSE_CLASS_fun, _HMC_MOUSE_CLASS_initialize, _HMC_KEYBOARD_CLASS_instances, _HMC_KEYBOARD_CLASS_fun, _HMC_KEYBOARD_CLASS_initialize;
Object.defineProperty(exports, "__esModule", { value: true });
exports.setLimitMouseRange = exports.HmcKeyboardClass = exports.HmcMouseClass = void 0;
const main = require("./index");
const util = require("./util");
const { ref } = util;
class HMC_MOUSE_CLASS {
    constructor() {
        _HMC_MOUSE_CLASS_instances.add(this);
        _HMC_MOUSE_CLASS_fun.set(this, null);
    }
    initMouseEventHook() {
        var _a;
        __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_instances, "m", _HMC_MOUSE_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.initMouseEventHook()) || false;
    }
    isValidHookMouse() {
        var _a;
        __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_instances, "m", _HMC_MOUSE_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.isValidHookMouse()) || false;
    }
    getMouseEventListJson() {
        var _a;
        __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_instances, "m", _HMC_MOUSE_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.getMouseEventListJson()) || false;
    }
    stopHookMouse() {
        var _a;
        __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_instances, "m", _HMC_MOUSE_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.stopHookMouse()) || false;
    }
    setLimitMouseRange(ms, x, y, right, bottom) {
        var _a;
        __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_instances, "m", _HMC_MOUSE_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.setLimitMouseRange(ref.int(ms), ref.int(x), ref.int(y), ref.int(right), ref.int(bottom))) || false;
    }
    setShakeEventTime(ms) {
        var _a;
        __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_instances, "m", _HMC_MOUSE_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.setShakeEventTime(ref.int(ms))) || false;
    }
    hasLimitMouseRangeWorker() {
        var _a;
        __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_instances, "m", _HMC_MOUSE_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.hasLimitMouseRangeWorker()) || false;
    }
    stopLimitMouseRangeWorker() {
        var _a;
        __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_instances, "m", _HMC_MOUSE_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_MOUSE_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.stopLimitMouseRangeWorker()) || false;
    }
}
_HMC_MOUSE_CLASS_fun = new WeakMap(), _HMC_MOUSE_CLASS_instances = new WeakSet(), _HMC_MOUSE_CLASS_initialize = function _HMC_MOUSE_CLASS_initialize() {
    if (!__classPrivateFieldGet(this, _HMC_MOUSE_CLASS_fun, "f") && main.Native.native.HMC_MOUSE_CLASS) {
        __classPrivateFieldSet(this, _HMC_MOUSE_CLASS_fun, main.Native.native.HMC_MOUSE_CLASS(), "f");
    }
};
exports.HmcMouseClass = new HMC_MOUSE_CLASS();
class HMC_KEYBOARD_CLASS {
    constructor() {
        _HMC_KEYBOARD_CLASS_instances.add(this);
        _HMC_KEYBOARD_CLASS_fun.set(this, null);
    }
    initKeyboardEventHook() {
        var _a;
        __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_instances, "m", _HMC_KEYBOARD_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.initKeyboardEventHook()) || false;
    }
    isValidHookKeyboard() {
        var _a;
        __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_instances, "m", _HMC_KEYBOARD_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.isValidHookKeyboard()) || false;
    }
    getAllKeyboardEventJson() {
        var _a;
        __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_instances, "m", _HMC_KEYBOARD_CLASS_initialize).call(this);
        return JSON.parse(((_a = __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.getAllKeyboardEventJson()) || "[]");
    }
    stopHookKeyboard() {
        var _a;
        __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_instances, "m", _HMC_KEYBOARD_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.stopHookKeyboard()) || false;
    }
    hasKeysBasic() {
        var _a;
        __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_instances, "m", _HMC_KEYBOARD_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.hasKeysBasic()) || {
            "alt": false,
            "ctrl": false,
            "shift": false,
            "win": false
        };
    }
    hasKeyActivate(KeysEvent) {
        var _a;
        __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_instances, "m", _HMC_KEYBOARD_CLASS_initialize).call(this);
        return ((_a = __classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_fun, "f")) === null || _a === void 0 ? void 0 : _a.hasKeyActivate(ref.int(KeysEvent))) || false;
    }
}
_HMC_KEYBOARD_CLASS_fun = new WeakMap(), _HMC_KEYBOARD_CLASS_instances = new WeakSet(), _HMC_KEYBOARD_CLASS_initialize = function _HMC_KEYBOARD_CLASS_initialize() {
    if (!__classPrivateFieldGet(this, _HMC_KEYBOARD_CLASS_fun, "f") && main.Native.native.HMC_KEYBOARD_CLASS) {
        __classPrivateFieldSet(this, _HMC_KEYBOARD_CLASS_fun, main.Native.native.HMC_KEYBOARD_CLASS(), "f");
    }
};
exports.HmcKeyboardClass = new HMC_KEYBOARD_CLASS();
/**
 * 限制鼠标光标可移动范围 (异步)
 * @description 可以调用 stop 提前结束
 * ?最高不允许超过30000ms (30秒) 最低不允许低于31ms
 * ?范围为正方形 如果没有设置right与bottom的值则将限制为1x1的正方形 (不可动)
 * @param ms 本次限制的时间
 * @param x 限制左边初始化点的位置
 * @param y 限制顶部初始化点的位置
 * @param right 允许的范围(左边到右边部)
 * @param bottom 允许光标移动的范围(顶到底部)
 */
function setLimitMouseRange(ms, x, y, right = 1, bottom = 1) {
    ms = Math.abs(ref.int(ms));
    x = Math.abs(ref.int(x));
    y = Math.abs(ref.int(y));
    right = Math.abs(ref.int(right)) || 1;
    bottom = Math.abs(ref.int(bottom)) || 1;
    if (ms > 30 * 1000 || ms < 30) {
        throw new Error("The range is only allowed from 31 milliseconds to 30 seconds (31ms-30000).");
    }
    exports.HmcMouseClass.setLimitMouseRange(ms, x, y, right, bottom);
    const res = {
        ms, x, y, right, bottom,
        closed: (() => {
            setTimeout(() => {
                // !请注意此地方不能取消
                // 防止node提前退出 导致解锁失败(双保险)
                res.closed = exports.HmcMouseClass.hasLimitMouseRangeWorker();
            }, ms + 80);
            return false;
        })(),
        /**
         * 停止本次
         * @returns
         */
        close() {
            return exports.HmcMouseClass.stopLimitMouseRangeWorker();
        },
        // 停止本次
        stop() {
            return this.close();
        },
        /**
         * 是否正在执行中
         * @returns
         */
        has() {
            return !exports.HmcMouseClass.hasLimitMouseRangeWorker();
        }
    };
    return res;
}
exports.setLimitMouseRange = setLimitMouseRange;
