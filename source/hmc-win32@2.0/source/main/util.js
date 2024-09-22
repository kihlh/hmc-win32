"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ref = void 0;
const path = require("path");
exports.ref = {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str) {
        return path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
    },
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool) {
        if (typeof bool == "string") {
            const TEMP = bool.toUpperCase();
            if (TEMP == "0" || TEMP == "FALSE" || TEMP == "NULL" || TEMP == "NONE") {
                return false;
            }
            return true;
        }
        return bool ? true : false;
    },
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str) {
        return String(Str || "");
    },
    /**
     * 格式化数字为float(强制) 浮点
     * @param Num
     * @returns
     */
    float(Num) {
        if (!Num)
            return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num === null || Num === void 0 ? void 0 : Num.valueOf();
        }
        if (typeof Num == "string") {
            Num = parseFloat(Num);
            if (isNaN(Num))
                return 0;
            if (Num >= Infinity) {
                Num = 999999999999999.999;
            }
            if (Num <= -Infinity) {
                Num = -999999999999999.999;
            }
            return Num;
        }
        if (typeof Num == "number" && !isNaN(Num))
            return Num;
        // true == 1
        if (Num && typeof Num == "boolean")
            Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean")
            Num = 0;
        if (Num >= Infinity) {
            Num = 999999999999999.999;
        }
        if (Num <= -Infinity) {
            Num = -999999999999999.999;
        }
        return Num;
    },
    /**
     * 格式化数字为int(强制) 取整
     * @param Num
     * @returns
     */
    int(Num) {
        if (!Num)
            return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num === null || Num === void 0 ? void 0 : Num.valueOf();
        }
        // 取整
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num))
            return Num;
        // true == 1
        if (Num && typeof Num == "boolean")
            Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean")
            Num = 0;
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
    stringArray(array) {
        let dataList = [];
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
    intArray(array) {
        let dataList = [];
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
     * 将命令行内容组转为cmd文本
     * @param argv
     */
    formatArgv(...argv) {
        let argvs = [];
        let argvsResult = [];
        // 获取
        for (let index = 0; index < argv.length; index++) {
            const cout = argv[index];
            if (Array.isArray(cout)) {
                for (let cout_index = 0; cout_index < cout.length; cout_index++) {
                    const cout2 = cout[cout_index];
                    argvs.push(this.string(cout2));
                }
                continue;
            }
            argvs.push(this.string(cout));
        }
        // 处理
        for (let index = 0; index < argvs.length; index++) {
            let cout = argvs[index];
            if (!cout)
                continue;
            if (cout.match(/['"]/)) {
                cout = cout.replace(/(\\)?["']/g, "\\$0");
            }
            if (cout.match(" ")) {
                cout = `"${cout}"`;
            }
            if (cout.match(/[\n\r]/)) {
                cout = cout.replace(/(\n|\r|\r\n)/g, "$0^");
            }
            argvsResult.push(cout);
        }
        return argvsResult.join(" ");
    },
    /**
     * 拼合buff片段
     * @param buffList
     * @returns
     */
    concatBuff(buffList) {
        let buffSize = 0;
        for (let index = 0; index < buffList.length; index++) {
            const buff = buffList[index];
            buffSize = buffSize + buff.byteLength;
        }
        let ResponseData = Buffer.concat([...buffList], buffSize);
        return ResponseData;
    }
};
