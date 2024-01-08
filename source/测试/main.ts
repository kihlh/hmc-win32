import type _hmc = require("../mian/hmc");
import fs = require("fs-extra");
import jsonfm = require("jsonfm");
import shake = require("hmc-shake");
import log4js = require("log4js");

import hmc, { ref, PromiseSP, HMC } from "../../";
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");

process.exitCode = 666;

console.time("load hmc dll");
const native: _hmc.HMC.Native & Native = require(process.argv.at(-1) || "");
console.timeEnd("load hmc dll");

export interface Native {
    /**
     * 设置注册表值 （提供了初级和低级操作）
     * @param Hive 根目录
     * @param folderPath 目录路径
     * @param keyName 值键
     * @param data 数据体
     * - null 设置空值
     * - string 约 2^31 - 1 个字符 (2GB) 但是不建议存储过大数据 会出问题
     * - number DWORD 标准范围约为 0(0x0) 到 4294967295(0xffffffff) (即 2^32 - 1)
     * - bigint QWORD 标准范围约为  0n(0x0) 到 18446744073709551615n (0xffffffffffffffff)（即 2^64 - 1）
     * - boolean 布尔 以DWORD状态存储 范围 0-1
     * - Buffer 二进制  1024KB 以内
     * - Date 时间戳 以浮点二进制存储
     * - string[] 文本数组 REG_MULTI_SZ格式 允许存储空文本但是不建议 (因为非标准) 但是数组末尾的元素是空文本会被清空
     * @param type 类型
     * - true 文本时将转义到转义类型
     * - HMC.REG_TYPE 强制转义 仅限二进制类型
     */
    setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null, data: null | number | bigint | boolean | Buffer | Date | string | string[], type: undefined | boolean | HMC.REG_TYPE): boolean;
}

/**
 * 设置注册表值 
 * @param Hive 根目录
 * @param folderPath 目录路径
 * @param keyName 值键
 * @param data 数据体
 * @param is_expand 是否让其可以被自动转义 例如 %temp%/123 -> c:.../temp/123
 */
export function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null, data: string, is_expand?: boolean): boolean;
/**
 * 设置注册表值
 * @param Hive 根目录
 * @param folderPath 目录路径
 * @param keyName 值键
 * @param data 数据体
 * @param to_type 转义类型 详见 HMC.REG_TYPE https://learn.microsoft.com/zh-cn/windows/win32/sysinfo/registry-value-types
 */
export function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null, data: Buffer, to_type?: HMC.REG_TYPE): boolean;

/**
 * 设置注册表值
 * @param Hive 根目录
 * @param folderPath 目录路径
 * @param keyName 值键
 */
export function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null): boolean;

/**
 * 设置注册表值 文本数组
 * - REG_MULTI_SZ格式 
 * ? 允许存储空文本但是不建议 (因为非标准) 但是数组末尾的元素是空文本会被清空
 * @param Hive 根目录
 * @param folderPath 目录路径
 * @param keyName 值键
 */
export function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string ,data:string[]): boolean;

/**
 * 设置注册表值
 * @param Hive 根目录
 * @param folderPath 目录路径
 * @param keyName 值键
 * @param data 数据体
 * - number DWORD 标准范围约为 0(0x0) 到 4294967295(0xffffffff) (即 2^32 - 1)
 * - bigint QWORD 标准范围约为  0n(0x0) 到 18446744073709551615n (0xffffffffffffffff)（即 2^64 - 1）
 * - boolean 布尔 以DWORD状态存储 范围 0-1
 * - Buffer 二进制  1024KB 以内
 * - Date 时间戳 以浮点二进制存储
 */
export function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: string | null, data: number | bigint | boolean | Date ): boolean;

export function setRegistrValue(Hive: HMC.HKEY, folderPath: string, keyName: unknown, data: unknown = null, type: unknown = undefined): boolean {
    const hive_value = ref.string(Hive || "HKEY_CURRENT_USER") as HMC.HKEY;
    // 虽然不符合规范 都是根目录下是允许写数据的
    const folder_path = ref.string(folderPath || "").replace(/[\\\/]+/g, "\\");
    const key_name = ref.string(keyName || "");
    let data_output: string | number | bigint | boolean | Buffer | Date | null | string[] = data as Buffer;
    let types: HMC.REG_TYPE | undefined | boolean = undefined;
    let is_type_valid: boolean = false;

    // !这里有个判断文件夹的逻辑 因为设置值不会创建目录

    // 处理转义
    if (Buffer.isBuffer(data_output)) {
        if (typeof type == "number") {
            types = type as HMC.REG_TYPE;
        }
    } else
        if (typeof data_output == "string") {
            if (typeof type == "boolean" || type == 2) {
                types = type ? true : false;
            }
        }

    // 判断值有效
    if (
        typeof data_output == "boolean" ||
        typeof data_output == "string" ||
        typeof data_output == "number" ||
        typeof data_output == "bigint" ||
        data_output instanceof Date ||
        data_output === null ||
        Array.isArray(data_output)||
        Buffer.isBuffer(data_output)
    ) {
        is_type_valid = true;
    } else return is_type_valid;

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

    if(data_output&&!Buffer.isBuffer(data_output) &&Array.isArray(data_output)){
        data_output = ref.stringArray(data_output);
    }

    // 处理 负数 浮点 的逻辑

    return native.setRegistrValue(hive_value, folder_path, key_name, data_output, types);
}

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
if (require("node:inspector")?.url()) {
    setInterval(function () { }, 500000);
}



