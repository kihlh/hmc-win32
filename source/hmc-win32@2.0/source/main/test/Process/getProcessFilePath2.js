"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.main2AddSnapshotName = exports.main = exports.HMC_X64 = exports.HMC_BETA = void 0;
exports.HMC_BETA = require(String(process.env.mode));
exports.HMC_X64 = require("F:/source/module/hmc-win32/bin/HMC_x64.node");
async function main() {
    const PromList = [];
    const ProcessList = JSON.parse(await exports.HMC_X64.getAllProcessList());
    const result = new Map();
    console.time("getProcessFilePath2");
    for (let index = 0; index < ProcessList.length; index++) {
        const { pid } = ProcessList[index];
        const temp = exports.HMC_BETA.getProcessFilePath2(pid)
            .then(data => {
            result.set(pid, data);
            return data;
        })
            .catch(data => {
            result.set(pid, data);
            return data;
        });
        PromList.push(temp);
    }
    await Promise.allSettled(PromList);
    console.timeEnd("getProcessFilePath2");
    const resultSync = new Map();
    console.time("getProcessFilePath2Sync");
    for (let index = 0; index < ProcessList.length; index++) {
        const { pid } = ProcessList[index];
        const temp = exports.HMC_BETA.getProcessFilePath2Sync(pid);
        resultSync.set(pid, temp);
    }
    console.timeEnd("getProcessFilePath2Sync");
    return { result, resultSync };
}
exports.main = main;
;
async function main2AddSnapshotName() {
    const PromList = [];
    const ProcessList = JSON.parse(await exports.HMC_X64.getAllProcessList());
    const result = new Map();
    console.time("getProcessFilePath2");
    for (let index = 0; index < ProcessList.length; index++) {
        const { pid } = ProcessList[index];
        const temp = exports.HMC_BETA.getProcessFilePath2(pid, true, true)
            .then(data => {
            result.set(pid, data);
            return data;
        })
            .catch(data => {
            result.set(pid, data);
            return data;
        });
        PromList.push(temp);
    }
    await Promise.allSettled(PromList);
    console.timeEnd("getProcessFilePath2");
    const resultSync = new Map();
    console.time("getProcessFilePath2Sync");
    for (let index = 0; index < ProcessList.length; index++) {
        const { pid } = ProcessList[index];
        const temp = exports.HMC_BETA.getProcessFilePath2Sync(pid, true, true);
        resultSync.set(pid, temp);
    }
    console.timeEnd("getProcessFilePath2Sync");
    return { result, resultSync };
}
exports.main2AddSnapshotName = main2AddSnapshotName;
;
/**


const mode =  require(path.resolve(process.env.hmc_debug_js,"Process\\getProcessFilePath2.js"));

await mode.main();
await mode.main2AddSnapshotName();


getProcessFilePath2: 53.5361328125 ms
node:internal/console/constructor:625 getProcessFilePath2: 53.825ms


getProcessFilePath2.js:33 getProcessFilePath2Sync: 77.722900390625 ms
node:internal/console/constructor:625 getProcessFilePath2Sync: 77.851ms




await mode.main2AddSnapshotName();

getProcessFilePath2: 1250.31982421875 ms
node:internal/console/constructor:625 getProcessFilePath2: 1.251s

getProcessFilePath2.js:65 getProcessFilePath2Sync: 3608.93994140625 ms
node:internal/console/constructor:625 getProcessFilePath2Sync: 3.609s

*/ 
