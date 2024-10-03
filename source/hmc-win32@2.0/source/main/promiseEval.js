"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.promiseEvalTask = exports.HMC_PROMISEEVAL_TASK_TYPE = void 0;
const main = require("./index");
var HMC_PROMISEEVAL_TASK_TYPE;
(function (HMC_PROMISEEVAL_TASK_TYPE) {
    HMC_PROMISEEVAL_TASK_TYPE[HMC_PROMISEEVAL_TASK_TYPE["getClipboardFilePaths2"] = 1] = "getClipboardFilePaths2";
    HMC_PROMISEEVAL_TASK_TYPE[HMC_PROMISEEVAL_TASK_TYPE["captureBmp2"] = 2] = "captureBmp2";
    HMC_PROMISEEVAL_TASK_TYPE[HMC_PROMISEEVAL_TASK_TYPE["closeWindow2"] = 3] = "closeWindow2";
    HMC_PROMISEEVAL_TASK_TYPE[HMC_PROMISEEVAL_TASK_TYPE["getClipboardText2"] = 5] = "getClipboardText2";
    HMC_PROMISEEVAL_TASK_TYPE[HMC_PROMISEEVAL_TASK_TYPE["getThumbnailPng2"] = 6] = "getThumbnailPng2";
})(HMC_PROMISEEVAL_TASK_TYPE = exports.HMC_PROMISEEVAL_TASK_TYPE || (exports.HMC_PROMISEEVAL_TASK_TYPE = {}));
;
class HMC_PromiseeEvalTask {
    constructor() {
        this.async = {};
        this.sync = {};
        const TASK_TYPE_LIST = Object.keys(HMC_PROMISEEVAL_TASK_TYPE);
        for (let index = 0; index < TASK_TYPE_LIST.length; index++) {
            const TASK_TYPE = TASK_TYPE_LIST[index];
            const TASK_ID = HMC_PROMISEEVAL_TASK_TYPE[TASK_TYPE];
            this.async[TASK_TYPE] = (...arg) => {
                var _a;
                try {
                    if (!((_a = main.Native.native) === null || _a === void 0 ? void 0 : _a.HMC_PromiseEval)) {
                        return Promise.reject(main.HMC2_MODE.HMCNotPlatform);
                    }
                    if (arg.length >= 1) {
                        return main.Native.native.HMC_PromiseEval(TASK_ID, ...arg);
                    }
                    return main.Native.native.HMC_PromiseEval(TASK_ID);
                }
                catch (error) {
                    return Promise.reject(error);
                }
            };
            this.sync[TASK_TYPE] = (...arg) => {
                var _a;
                if (!((_a = main.Native.native) === null || _a === void 0 ? void 0 : _a.HMC_PromiseEvalSync)) {
                    return null;
                }
                if (arg.length >= 1) {
                    return main.Native.native.HMC_PromiseEvalSync(TASK_ID, ...arg) || null;
                }
                return main.Native.native.HMC_PromiseEvalSync(TASK_ID);
            };
            if (!this[TASK_TYPE]) {
                this[TASK_TYPE] = this.async[TASK_TYPE];
            }
            const KEY = `${TASK_TYPE}Sync`;
            if (!this[KEY]) {
                this[KEY] = this.sync[TASK_TYPE];
            }
        }
    }
    async getClipboardFilePaths2() {
        var _a, _b;
        if (!((_a = exports.promiseEvalTask === null || exports.promiseEvalTask === void 0 ? void 0 : exports.promiseEvalTask.async) === null || _a === void 0 ? void 0 : _a.getClipboardFilePaths2)) {
            return Promise.resolve([]);
        }
        const data = await (((_b = exports.promiseEvalTask === null || exports.promiseEvalTask === void 0 ? void 0 : exports.promiseEvalTask.async) === null || _b === void 0 ? void 0 : _b.getClipboardFilePaths2()) || null);
        if (typeof data == "string") {
            const temp = data ? data === null || data === void 0 ? void 0 : data.split('\0') : [];
            if (temp.length && temp.at(-1) == "")
                temp.pop();
            return temp;
        }
        return data || [];
    }
    getClipboardFilePaths2Sync() {
        var _a, _b;
        if (!((_a = exports.promiseEvalTask === null || exports.promiseEvalTask === void 0 ? void 0 : exports.promiseEvalTask.sync) === null || _a === void 0 ? void 0 : _a.getClipboardFilePaths2)) {
            return [];
        }
        const data = (((_b = exports.promiseEvalTask === null || exports.promiseEvalTask === void 0 ? void 0 : exports.promiseEvalTask.sync) === null || _b === void 0 ? void 0 : _b.getClipboardFilePaths2()) || null);
        if (typeof data == "string") {
            const temp = data ? data === null || data === void 0 ? void 0 : data.split('\0') : [];
            if (temp.length && temp.at(-1) == "")
                temp.pop();
            return temp;
        }
        return data || [];
    }
}
exports.promiseEvalTask = new HMC_PromiseeEvalTask();
