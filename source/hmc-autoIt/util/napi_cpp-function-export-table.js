"use strict";
var _a, _b;
Object.defineProperty(exports, "__esModule", { value: true });
// @ts-ignore
const fs = require("fs");
// ^[a-z0-9]+([a-z0-9]+) +([a-z0-9_$]+)(?: +)?\(.+?\)$
let data = fs.readFileSync(fs.existsSync("F:\\source\\module\\hmc-win32\\source\\hmc-autoIt\\AutoItX3.hpp") ? "F:\\source\\module\\hmc-win32\\source\\hmc-autoIt\\AutoItX3.hpp" : "../AutoItX3.hpp", "utf8").replace(/\t/g, " ");
let data_list = data.match(/^(?:[a-z0-9]+(?:[a-z0-9]+)|unsigned int) +(?:[a-z0-9_$]+)(?: +)?\(.+?\)$|^(?:[a-z0-9]+(?:[a-z0-9]+)|unsigned int).+\((?: +|void)?\)/mig);
/**
{
    name:"fn_AU3_ControlClickByHandle",
    type:"int",
    argc:5,
    argv:[{
        type:"HWND",
        name:"hCtrl",
        defaultv:0,
        index:0
    },{
        type:"wstring",
        name:"szButton",
        defaultv:"L\"left\"",
        index:1
    },{
        type:"int",
        name:"nNumClicks",
        defaultv:"1",
        index:2
    },{
        type:"int",
        name:"nX",
        defaultv:"AU3_INTDEFAULT",
        index:3
    },{
        type:"int",
        name:"nY",
        defaultv:"AU3_INTDEFAULT",
        index:4
    }]
}
 */
const fn_type_list = [];
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
for (let index = 0; index < (data_list ? data_list === null || data_list === void 0 ? void 0 : data_list.length : 0); index++) {
    const data = (data_list === null || data_list === void 0 ? void 0 : data_list[index]) || "";
    let function_header = data.match(/^(.+?) ([^ ]+)(?: +)?\(/i);
    if (!function_header)
        continue;
    const result_type = function_header[1];
    const fn_name = function_header[2];
    const fn_args_list = data.replace(function_header[0], "").replace(/\)([ ]+)?$/, "").split(/(?:[ ]+)?,(?:[ ]+)?/);
    const fn_Analysis = {
        name: fn_name,
        type: result_type,
        argc: 0,
        argv: [],
        exports: fn_name.replace(/fn_AU3_/, ""),
        js_type: cpp_type_to_js_type(result_type)
    };
    for (let index = 0; index < fn_args_list.length; index++) {
        const element = fn_args_list[index].replace(/^ +| +$/, "");
        if (!element || element.match(/^void$/))
            continue;
        const data = {
            type: (((_a = element.match(/^(?: +)?(.+?) /)) === null || _a === void 0 ? void 0 : _a[1]) || "any"),
            name: ((_b = element.match(/^.+? +([^ ]+)?/)) === null || _b === void 0 ? void 0 : _b[1]) || "",
            defaultv: element.match(/^[^"]+=/) ? element.replace(/^.+? +[^ ]+?(?: +)?=(?: +)?/i, "") : null,
            index: index
        };
        fn_Analysis.argc++;
        fn_Analysis.argv.push(data);
    }
    fn_type_list.push(fn_Analysis);
}
const fn_code_list = [];
for (let index = 0; index < fn_type_list.length; index++) {
    const element = fn_type_list[index];
    // 得出最少需要输入多少个参数 
    let min_argc = (() => {
        let argc = 0;
        for (let index = 0; index < element.argv.length; index++) {
            const celement = element.argv[index];
            if (!celement.defaultv) {
                argc++;
            }
            else {
                return argc;
            }
        }
        return argc;
    })();
    // 得出最大需要提供多少个命令
    let max_argc = element.argc;
    let target = (() => {
        let argc = element.name + "( ";
        for (let index = 0; index < element.argv.length; index++) {
            const celement = element.argv[index];
            argc = argc + `[${celement.index}] ${celement.name} type:( ${celement.type} ${celement.defaultv ? "default:(" + celement.defaultv + ")" : ""} ) \\n`;
        }
        argc = argc + " )";
        return argc.replace(/"|'/g, "\\$&");
    })();
    let target_eavl = (() => {
        let target = [];
        for (let index = 0; index < element.argv.length; index++) {
            const celement = element.argv[index];
            let code = `/*${celement.name} (${celement.type}) */ `;
            if (celement.type == "wstring") {
                code = code + `hmc_napi_util::get_value::string_utf16(env, argv[${index}], wstring(${celement.defaultv || "L\"\""}) )\n`;
            }
            if (celement.type == "int") {
                code = code + `hmc_napi_util::get_value::number_int(env, argv[${index}],${celement.defaultv || 0})\n`;
            }
            if (celement.type == "HWND") {
                code = code + `hmc_napi_util::get_value::number_HWND(env, argv[${index}])\n`;
            }
            if (celement.type == "LPRECT") {
                code = code + `hmc_napi_util::get_value::lprect(env, argv[${index}]) \n`;
            }
            if (celement.type == "POINT") {
                code = code + `hmc_napi_util::get_value::point(env, argv[${index}])\n`;
            }
            target.push(code);
        }
        let target_eavl_code = `${element.name}(\n${target.join(" , \n")});`;
        return target_eavl_code.replace(/\n\)$/, ")");
    })();
    // 处理返回值
    if (element.type != "void") {
        target_eavl = `${element.type} fn_result = ${target_eavl}\n`;
        switch (element.type) {
            case "HWND":
            case "long long":
            case "int":
            case "int64_t":
                {
                    target_eavl = target_eavl + `${!element.argc ? "return" : "result ="} hmc_napi_util::create_value::Number(env,fn_result);`;
                    break;
                }
            case "unsigned int": {
                target_eavl = target_eavl + `${!element.argc ? "return" : "result ="} hmc_napi_util::create_value::Number(env,(int)fn_result);`;
                break;
            }
            case 'string':
            case 'wstring':
                {
                    target_eavl = target_eavl + `${!element.argc ? "return" : "result ="} hmc_napi_util::create_value::String(env,fn_result);`;
                    break;
                }
            case 'bool':
                {
                    target_eavl = target_eavl + `${!element.argc ? "return" : "result ="} hmc_napi_util::create_value::Boolean(env,fn_result);`;
                    break;
                }
            case 'RECT':
                {
                    target_eavl = target_eavl + `${!element.argc ? "return" : "result ="} hmc_napi_util::create_value::Rect(env,fn_result);`;
                    break;
                }
            case 'POINT':
                {
                    target_eavl = target_eavl + `${!element.argc ? "return" : "result ="} hmc_napi_util::create_value::Point(env,fn_result);`;
                    break;
                }
        }
        target_eavl = target_eavl + `\n ${!element.argc ? " " : "return result; "} \n`;
    }
    let data = element.argc ? `
    
    static napi_value n${element.name} (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = ${max_argc};
    napi_value argv[${max_argc}];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "${element.name}");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  ${min_argc})
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:${min_argc}, max:${max_argc},the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("${target}");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        ${target_eavl}
    }
    HMC_CHECK_CATCH;
    return result;
}

` : `

    static napi_value n${element.name} (napi_env env, napi_callback_info info)
{
    try
    {
        ${target_eavl}
    }
    HMC_CHECK_CATCH;

    return NULL;
}

`;
    fn_code_list.push(data);
}
fn_code_list.push(`
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor BIND_NAPI_METHOD[] = {${(() => {
    let exp_list = "";
    for (let index = 0; index < fn_type_list.length; index++) {
        const element = fn_type_list[index];
        exp_list = exp_list + `DECLARE_NAPI_METHOD("${element.name.replace(/^fn_AU3_/, '')}", n${element.name}),\n`;
    }
    return exp_list;
})()}};
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);

`);
fs.writeFileSync("./Main.cpp", String.raw `
#include "Main.h"

// #pragma comment(lib, "./AutoItX3/AutoItX3_DLL.lib")
// #pragma comment(lib, "./AutoItX3/AutoItX3\\AutoItX3_x64_DLL.lib")

#ifdef _MSC_VER

#ifdef _M_IX86
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_DLL.lib")

#elif defined(_M_X64) || defined(_M_AMD64)
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_x64_DLL.lib")

#endif //_M_IX86
#endif //_MSC_VER

// HMC_CHECK_CATCH
// 在node环境
#ifdef SRC_NODE_API_H_
#define HMC_CHECK_CATCH                        \
    catch (char *err)                          \
    {                                          \
        napi_throw_type_error(env, NULL, err); \
        return NULL;                           \
    }

// 不在node环境
#else
#define HMC_CHECK_CATCH            \
    catch (char *err)              \
    {                              \
        if (HMC_IS_DEUG_COUT == 1) \
        {                          \
            cout << err << "\n";   \
        }                          \
    }
#endif // SRC_NODE_API_H_
` + fn_code_list.join("\n"));
