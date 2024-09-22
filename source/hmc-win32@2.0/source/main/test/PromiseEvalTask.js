"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.promisee = exports.HMC_BETA = void 0;
exports.HMC_BETA = require(String(process.env.mode));
var HMC_PROMISEEVAL_TASK_TYPE;
(function (HMC_PROMISEEVAL_TASK_TYPE) {
    HMC_PROMISEEVAL_TASK_TYPE[HMC_PROMISEEVAL_TASK_TYPE["getClipboardFilePaths2"] = 1] = "getClipboardFilePaths2";
    HMC_PROMISEEVAL_TASK_TYPE[HMC_PROMISEEVAL_TASK_TYPE["captureBmp2"] = 2] = "captureBmp2";
    HMC_PROMISEEVAL_TASK_TYPE[HMC_PROMISEEVAL_TASK_TYPE["closeWindow2"] = 3] = "closeWindow2";
})(HMC_PROMISEEVAL_TASK_TYPE || (HMC_PROMISEEVAL_TASK_TYPE = {}));
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
                try {
                    if (arg.length >= 1) {
                        return exports.HMC_BETA.HMC_PromiseEval(TASK_ID, ...arg);
                    }
                    return exports.HMC_BETA.HMC_PromiseEval(TASK_ID);
                }
                catch (error) {
                    return Promise.reject(error);
                }
            };
            this.sync[TASK_TYPE] = (...arg) => {
                if (arg.length >= 1) {
                    return exports.HMC_BETA.HMC_PromiseEvalSync(TASK_ID, ...arg);
                }
                return exports.HMC_BETA.HMC_PromiseEvalSync(TASK_ID);
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
        if (!((_a = exports.promisee === null || exports.promisee === void 0 ? void 0 : exports.promisee.async) === null || _a === void 0 ? void 0 : _a.getClipboardFilePaths2)) {
            return Promise.resolve([]);
        }
        const data = await (((_b = exports.promisee === null || exports.promisee === void 0 ? void 0 : exports.promisee.async) === null || _b === void 0 ? void 0 : _b.getClipboardFilePaths2()) || null);
        if (typeof data == "string") {
            return data ? data === null || data === void 0 ? void 0 : data.split('\0') : [];
        }
        return data || [];
    }
    getClipboardFilePaths2Sync() {
        var _a, _b;
        if (!((_a = exports.promisee === null || exports.promisee === void 0 ? void 0 : exports.promisee.sync) === null || _a === void 0 ? void 0 : _a.getClipboardFilePaths2)) {
            return [];
        }
        const data = (((_b = exports.promisee === null || exports.promisee === void 0 ? void 0 : exports.promisee.sync) === null || _b === void 0 ? void 0 : _b.getClipboardFilePaths2()) || null);
        if (typeof data == "string") {
            return data ? data === null || data === void 0 ? void 0 : data.split('\0') : [];
        }
        return data || [];
    }
}
;
exports.promisee = new HMC_PromiseeEvalTask();
/**
 *

console.time("mode.HMC_BETA.getClipboardFilePaths");
let data = mode.HMC_BETA.getClipboardFilePaths()
data = data? (data)?.split('\0'):[];
console.log('size-> %d',data.length);
console.timeEnd("mode.HMC_BETA.getClipboardFilePaths");


console.time("mode.promisee.getClipboardFilePaths2Sync");
let data2 = getClipboardFilePaths2Sync();
console.log('size-> %d',data2.length);
console.timeEnd("mode.promisee.getClipboardFilePaths2Sync");


VM1006:4 size-> 23273
VM1006:5 mode.HMC_BETA.getClipboardFilePaths: 17136.48095703125 ms
node:internal/console/constructor:625 mode.HMC_BETA.getClipboardFilePaths: 17.137s


VM1006:10 size-> 23272
VM1006:11 mode.promisee.getClipboardFilePaths2Sync: 17776.4990234375 ms
node:internal/console/constructor:625 mode.promisee.getClipboardFilePaths2Sync: 17.777s


 */
