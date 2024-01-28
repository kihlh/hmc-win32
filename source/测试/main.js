"use strict";
var _a;
Object.defineProperty(exports, "__esModule", { value: true });
exports.setRegistrValue = void 0;
const log4js = require("log4js");
const __1 = require("../../");
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");
process.exitCode = 666;
console.time("load hmc dll");
let native = setTimeout(() => {
    native = require(process.argv.at(-1) || "");
});
console.timeEnd("load hmc dll");
function setRegistrValue(Hive, folderPath, keyName, data = null, type = undefined) {
    const hive_value = __1.ref.string(Hive || "HKEY_CURRENT_USER");
    // 虽然不符合规范 都是根目录下是允许写数据的
    const folder_path = __1.ref.string(folderPath || "").replace(/[\\\/]+/g, "\\");
    const key_name = __1.ref.string(keyName || "");
    let data_output = data;
    let types = undefined;
    let is_type_valid = false;
    // !这里有个判断文件夹的逻辑 因为设置值不会创建目录
    // 处理转义
    if (Buffer.isBuffer(data_output)) {
        if (typeof type == "number") {
            types = type;
        }
    }
    else if (typeof data_output == "string") {
        if (typeof type == "boolean" || type == 2) {
            types = type ? true : false;
        }
    }
    // 判断值有效
    if (typeof data_output == "boolean" ||
        typeof data_output == "string" ||
        typeof data_output == "number" ||
        typeof data_output == "bigint" ||
        data_output instanceof Date ||
        data_output === null ||
        Array.isArray(data_output) ||
        Buffer.isBuffer(data_output)) {
        is_type_valid = true;
    }
    else
        return is_type_valid;
    // 提前强转 虽然c++也会强转
    if (typeof data_output == "boolean") {
        data_output = data_output ? 1 : 0;
    }
    // 万恶的NAN
    if (typeof data_output == "number" && isNaN(data_output)) {
        data_output = null;
    }
    // 超过0xffffffff 强制到0xffffffff
    if (typeof data_output == "number" && data_output > 0xffffffff) {
        data_output = 0xffffffff;
    }
    if (data_output && !Buffer.isBuffer(data_output) && Array.isArray(data_output)) {
        data_output = __1.ref.stringArray(data_output);
    }
    // 处理 负数 浮点 的逻辑
    return native.setRegistrValue(hive_value, folder_path, key_name, data_output, types);
}
exports.setRegistrValue = setRegistrValue;
(async function main() {
    // console.time("hmc.getProcessCwd()->");
    // console.log("hmc.getProcessCwd()->", await getProcessCwd2(process.pid));
    // console.timeEnd("hmc.getProcessCwd()->");
    // console.time("hmc.getProcessCwdSync()->");
    // console.log("hmc.getProcessCwdSync()->", getProcessCwd2Sync(process.pid));
    // console.timeEnd("hmc.getProcessCwdSync()->");
    // console.time("hmc.getProcessCommand()->");
    // console.log("hmc.getProcessCommand()->", await getProcessCommand2(process.pid));
    // console.timeEnd("hmc.getProcessCommand()->");
    // console.time("hmc.getProcessCommand()->");
    // console.log("hmc.getProcessCommand()->", getProcessCommand2Sync(process.pid));
    // console.timeEnd("hmc.getProcessCommand()->");
    // const setLimitMouse = setLimitMouseRange(5000,1,1,1,500);
    // hmc.Auto.mouseHook.on("mouse",()=>{});
    // hmc.Auto.mouseHook.start();
    // 预设置对比
    // let _int64: bigint = native.getRegistrQword("HKEY_CURRENT_USER", "hmc_temp", "_int64");
    // console.log("_int64-> %d", _int64, _int64 == BigInt(151162666161616));
    // let _int32 = native.getRegistrDword("HKEY_CURRENT_USER", "hmc_temp", "_int32");
    // console.log("_int32-> %d", _int32, _int32 == 789894594);
    // let _WIDE_CHAR = native.getStringRegKey("HKEY_CURRENT_USER", "hmc_temp", "_WIDE_CHAR");
    // console.log("_WIDE_CHAR-> ", _WIDE_CHAR, _WIDE_CHAR == "宽字符中文  emoji🗺️6");
    // let int32_buff = native.getRegistrBuffValue("HKEY_CURRENT_USER", "hmc_temp", "int32");
    // console.log("int32_buff-> ", int32_buff);
    // let temp:any = [
    //     [native.setRegistrDword("HKEY_CURRENT_USER","hmc_temp","TEMP1",626641614),
    //     native.getRegistrDword("HKEY_CURRENT_USER","hmc_temp","TEMP1")==626641614],
    //     [native.setRegistrQword("HKEY_CURRENT_USER","hmc_temp","TEMP2",BigInt("6262235346436457641614")),
    //     native.getRegistrQword("HKEY_CURRENT_USER","hmc_temp","TEMP2")==BigInt("6262235346436457641614")],
    //     [native.setRegistrKey("HKEY_CURRENT_USER","hmc_temp","TEMP3","⚠️你正在尝试获取值，如果值长得像值 值又正巧等于值那么他就会是个正确的值⚠️⚠️⚠️⚠️⚠️⚠️⚠️12345567890🔄"),
    //     native.getStringRegKey("HKEY_CURRENT_USER","hmc_temp","TEMP3")=="⚠️你正在尝试获取值，如果值长得像值 值又正巧等于值那么他就会是个正确的值⚠️⚠️⚠️⚠️⚠️⚠️⚠️12345567890🔄"],
    //     [native.setRegistrKey("HKEY_CURRENT_USER","hmc_temp","TEMP4","⚠️你正在尝试获取值，如果值长得像值 值又正巧等于值那么他就会是个正确的值⚠️⚠️⚠️⚠️⚠️⚠️⚠️12345567890🔄"),
    //     native.getStringRegKey("HKEY_CURRENT_USER","hmc_temp","TEMP4")=="⚠️你正在尝试获取值，如果值长得像值 值又正巧等于值那么他就会是个正确的值⚠️⚠️⚠️⚠️⚠️⚠️⚠️12345567890🔄"],
    //     // [native.setRegistrKey("HKEY_CURRENT_USER","hmc_temp","TEMP4",Buffer.from("⚠️你正在尝试获取值，如果值长得像值 值又正巧等于值那么他就会是个正确的值⚠️⚠️⚠️⚠️⚠️⚠️⚠️12345567890🔄","utf-8")),
    //     // native.getStringRegKey("HKEY_CURRENT_USER","hmc_temp","TEMP4")=="⚠️你正在尝试获取值，如果值长得像值 值又正巧等于值那么他就会是个正确的值⚠️⚠️⚠️⚠️⚠️⚠️⚠️12345567890🔄"],
    //     native.createRegistrFolder("HKEY_CURRENT_USER\\hmc_temp"),
    //     native.getRegistrFolderStat("HKEY_CURRENT_USER","hmc_temp"),
    //     native.getRegistrValueStat("HKEY_CURRENT_USER","hmc_temp")
    // ];
    // Buffer.from( +(new Date()),"binary")
    //  console.log(temp);
})().catch(console.error);
// 调试中阻止进程退出
if ((_a = require("node:inspector")) === null || _a === void 0 ? void 0 : _a.url()) {
    setInterval(function () { }, 500000);
}
