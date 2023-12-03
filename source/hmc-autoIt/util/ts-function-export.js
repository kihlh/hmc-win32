"use strict";
var _a, _b;
Object.defineProperty(exports, "__esModule", { value: true });
// @ts-ignore
const fs = require("fs");
const fn_type_list = JSON.parse(fs.readFileSync("../AutoItX3.hpp.json", "utf-8"));
function cpp_type_to_js_type(type) {
    switch (type) {
        case "HWND":
        case 'int':
        case 'unsigned int':
            return "number";
        case "int64_t":
        case "long long":
            return "bigint";
        case 'bool':
            return "boolean";
        case 'string':
        case 'wstring':
            return "string";
        case 'void':
            return "undefined";
        case 'POINT':
            return "{x:number, y:number}";
        case 'RECT':
        case 'LPRECT':
            return "{left:number, top:number,right:number, bottom:number}";
    }
    return "undefined";
}
let code = String.raw `
import path = require("path");

const AU3_INTDEFAULT = -2147483647;
const SW_SHOWNORMAL    =   1;

/**
 * @zh-cn 静态调用 .dll (注意如果您不知道这个是什么作用 请勿随意调用 参数错误有可能会导致进程崩溃)
 * @en-us Static call to .dll (Note that if you don't know what this does, don't call it at random.  Parameter errors may cause the process to crash)
 */
const get_native: () => HMN.Native = (binPath?: string) => {
    function _require_bin(): HMN.Native | null {
        try {
            if (binPath) return require(binPath);
            if (process.arch.match(/^x32|ia32$/)) return require("./bin/AutoItX_x86.node");
            if (process.arch.match(/^x64$/)) return require("./bin/AutoItX_x64.node");
        } catch (X_X) {

        }
        return null;
    }
    let Native: HMN.Native = (process.platform == "win32" ? _require_bin() : null) || (() => {
        let HMCNotPlatform = "HMC::HMC current method only supports win32 platform";
        function fnBool(...args: any[]) { console.error(HMCNotPlatform); return false }
        function fnVoid(...args: any[]) { console.error(HMCNotPlatform); return undefined }
        function fnNull(...args: any[]) { console.error(HMCNotPlatform); return null }
        function fnNum(...args: any[]) { console.error(HMCNotPlatform); return 0 }
        function fnStrList(...args: any[]) { console.error(HMCNotPlatform); return [] as string[] }
        function fnStr(...args: any[]) { console.error(HMCNotPlatform); return '' }
        function fnAnyArr(...args: any[]) { console.error(HMCNotPlatform); return [] as any[] }
        function fnArrayStr(...args: any[]) { console.error(HMCNotPlatform); return '[]' }
        return {/*{{not::fn::HMN.Native}}*/}
    })();
    return Native;
};
export const native: HMN.Native = get_native();


// 类型
export module HMN {
    export interface Native {}
}

export const ref = {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str: any) {
        return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
    },
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool: any) {
        return bool ? true : false;
    },
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str: any) {
        return String(Str || "");
    },
    /**
     * 格式化数字为int(强制)
     * @param Num
     * @returns
     */
    int(Num: any): number {
        if (!Num) return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num?.valueOf();
        }
        // 取整
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num)) return Num;
        // true == 1
        if (Num && typeof Num == "boolean") Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean") Num = 0;
        if (Num >= Infinity) {
            Num = 999999999999999;
        }
        if (Num <= -Infinity) {
            Num = -999999999999999;
        }
        return Num;
    },
    /**
     * 文本数组
     * @param array 
     * @returns 
     */
    stringArray(array: Set<any> | Array<any>) {
        let dataList: string[] = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(this.string(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(this.string(cout));
            }
        }
        return dataList;
    },
    /**
     * 文本数组
     * @param array 
     * @returns 
     */
    intArray(array: Set<any> | Array<any>) {
        let dataList: number[] = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(this.int(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(this.int(cout));
            }
        }
        return dataList;
    },
    /**
     * 拼合buff片段
     * @param buffList 
     * @returns 
     */
    concatBuff(buffList: Buffer[]): Buffer {
        let buffSize = 0;
        for (let index = 0; index < buffList.length; index++) {
            const buff = buffList[index];
            buffSize = buffSize + buff.byteLength;
        }
        let ResponseData = Buffer.concat([...buffList], buffSize);
        return ResponseData;
    },
};


`;
let export_Native = "";
let args_export_Not_Native = "";
function get_description(fn_name) {
    let description = "\n// " + fn_name;
    for (let index = 0; index < fn_type_list.length; index++) {
        const element = fn_type_list[index];
        if (element.exports == fn_name || element.name == fn_name) {
            const el_description = element.description;
            if (!el_description)
                break;
            description = `
            /**`;
            if (el_description["zh-cn"]) {
                description += "\n* @zh-cn " + el_description["zh-cn"];
            }
            if (el_description["en-us"]) {
                description += "\n* @en-us " + el_description["en-us"];
            }
            description += `\n* @link https://documentation.help/AutoItX/${fn_name.replace(/ByHandle$/, "")}.htm`;
            if (el_description.arg && Array.isArray(el_description.arg)) {
                for (let index = 0; index < el_description.arg.length; index++) {
                    const element = el_description.arg[index];
                    let desc = element.desc.replace(/[\n\r]|^[\t\n ]+|[\t\n ]+$/g, " ");
                    if (!desc) {
                        switch (element.name) {
                            case "nTrans":
                                desc = "不透明度 阿尔法通道值  0 - 255 ";
                                break;
                            case "hWnd":
                                desc = "窗口句柄数字";
                                break;
                            case "Title":
                                desc = "窗口标题";
                                break;
                            case "nX":
                                desc = "x (left To Right) ";
                                break;
                            case "nY":
                                desc = "y (top To Bottom) ";
                                break;
                            case "Text":
                                desc = "窗口/控件文本";
                                break;
                            case "nWidth":
                                desc = "宽度";
                                break;
                            case "nHeight":
                                desc = "高度";
                                break;
                            case "Process":
                                desc = "进程名称";
                                break;
                            case "lpRect":
                                desc = "位置";
                                break;
                            case "Control":
                                desc = "与之交互的控件。请参阅[控件](https://documentation.help/AutoItX/controls.htm)";
                                break;
                            case "SendText":
                                desc = "发送的文本内容";
                                break;
                            case "Command":
                                desc = "命令";
                                break;
                        }
                    }
                    description += "\n* @param " + element.name + " " + desc;
                    if (element.defaultv) {
                        description += "\n* @default " + String(element.defaultv).replace(/L"/, "\"");
                    }
                }
            }
            if (el_description["returns"]) {
                description += "\n* @returns " + el_description["returns"];
            }
            description += "\n*/";
        }
    }
    return description + "\n";
}
for (let index = 0; index < fn_type_list.length; index++) {
    const fn_type = fn_type_list[index];
    let args_eval = "";
    let args_fn = "";
    let args_export_Native = "";
    for (let index = 0; index < fn_type.argv.length; index++) {
        const argv = fn_type.argv[index];
        if (!argv.defaultv) {
            args_fn = args_fn + `${argv.name} : ${cpp_type_to_js_type(argv.type)} , `;
        }
        else {
            args_fn = args_fn + `${argv.name} : ${cpp_type_to_js_type(argv.type)} = ${(_a = argv.defaultv) === null || _a === void 0 ? void 0 : _a.replace(/L"/, "\"")}, `;
        }
        args_export_Native = args_export_Native + `${argv.name} ${argv.defaultv ? "?" : ""}: ${cpp_type_to_js_type(argv.type)} , `;
        switch (cpp_type_to_js_type(argv.type)) {
            case "boolean":
                args_eval = args_eval + ` ref.bool(typeof ${argv.name} == "undefined" ? ${argv.defaultv ? argv.defaultv : "false"} : ${argv.name} ) ,\n`;
                break;
            case "undefined":
                args_eval = args_eval + ` undefined ,`;
                break;
            case "string":
                args_eval = args_eval + ` ref.string(typeof ${argv.name} == "undefined" ? ${argv.defaultv ? (_b = argv.defaultv) === null || _b === void 0 ? void 0 : _b.replace(/L"/, "\"") : "\"\""} : ${argv.name} ) ,\n`;
                break;
            case "bigint":
                args_eval = args_eval + ` ref.int(typeof ${argv.name} == "undefined" ? ${argv.defaultv ? argv.defaultv : "0n"} : ${argv.name} ) ,\n`;
                break;
            case "number":
                args_eval = args_eval + ` ref.int(typeof ${argv.name} == "undefined" ? ${argv.defaultv ? argv.defaultv : "0"} : ${argv.name} ) ,\n`;
                break;
            case "{left:number, top:number,right:number, bottom:number}":
                args_eval = args_eval + `{
                    left : ref.int(${argv.name}.left),
                    top : ref.int(${argv.name}.top),
                    right : ref.int(${argv.name}.right),
                    bottom : ref.int(${argv.name}.bottom)
                     } ,\n`;
                break;
            case '{x:number, y:number}':
                args_eval = args_eval + `{x : ref.int(${argv.name}.x , y : ref.int(${argv.name}.y},\n`;
                break;
            case "null":
            default:
                args_eval = args_eval + `null ,\n`;
                break;
        }
    }
    args_fn = args_fn.replace(/[, \n\t]+$/, "");
    args_eval = args_eval.replace(/[, \n\t]+$/, "");
    args_export_Native = args_export_Native.replace(/[, \n\t]+$/, "");
    code = `${code} 
     ${get_description(fn_type.exports)}
     export function ${fn_type.exports} (${args_fn}) :${fn_type.js_type}|void {
        return native.${fn_type.exports}(${args_eval});
     }
     
    `;
    export_Native = export_Native + `${fn_type.exports} (${args_export_Native}) :${fn_type.js_type}|void;\n`;
    switch (fn_type.js_type) {
        case "boolean":
            args_export_Not_Native = args_export_Not_Native + `${fn_type.exports}:fnBool,\n`;
            break;
        case "number":
            args_export_Not_Native = args_export_Not_Native + `${fn_type.exports}:fnNum,\n`;
            break;
        case "null":
            args_export_Not_Native = args_export_Not_Native + `${fn_type.exports}:fnNull,\n`;
            break;
        case "string":
            args_export_Not_Native = args_export_Not_Native + `${fn_type.exports}:fnStr,\n`;
            break;
        case "undefined":
            args_export_Not_Native = args_export_Not_Native + `${fn_type.exports}:fnVoid,\n`;
            break;
        case "bigint":
            args_export_Not_Native = args_export_Not_Native + `${fn_type.exports}:(...arg:any[])=>0n ,\n`;
            break;
        case "{left:number, top:number,right:number, bottom:number}":
            args_export_Not_Native = args_export_Not_Native + `${fn_type.exports}:(...arg:any[])=>{return {left:0, top:0,right:0,bottom:0} as any } ,\n`;
            break;
        case "{x:number, y:number}":
            args_export_Not_Native = args_export_Not_Native + `${fn_type.exports}:(...arg:any[])=>{return {x:0, y:0} as any } ,\n`;
            break;
        default:
            args_export_Not_Native = args_export_Not_Native + `${fn_type.exports}:(...arg:any[])=>{return undefined as any; /*${fn_type.js_type}*/  } ,\n`;
            break;
    }
}
code = code.replace("export interface Native {}", `export interface Native {
    ${export_Native}
}`);
code = code.replace("{/*{{not::fn::HMN.Native}}*/}", `{
    ${args_export_Not_Native}
}`);
fs.writeFileSync("./out.ts", code);
