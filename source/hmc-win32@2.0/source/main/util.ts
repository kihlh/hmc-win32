
import _path = require('path');

export module ref {

    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    export function path(Str: any) {
        return _path.resolve(String(Str || "")).replace(/([\0\n\r]+)?$/, '\0');
    }

    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    export function bool(bool: any) {
        if (bool && typeof bool == "string") {

            const TEMP = bool.toUpperCase();

            if (TEMP == "0" || TEMP == "FALSE" || TEMP == "NULL" || TEMP == "NONE") {
                return false;
            }

            return true;
        }
        return bool ? true : false;
    }

    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    export function string(Str: any) {
        if (!Str && typeof Str == "object") {
            return "null";
        }
        if (typeof Str == "object" && Str instanceof String) {
            Str = Str?.toString() || String(Str);
            return Str;
        }

        if (typeof Str == "object" || Array.isArray(Str)) {
            try {
                return JSON.stringify(Str)
            } catch (error) {
                return String(Str)
            }
        }

        if (typeof Str == "number") {
            Str = String(Str);
            return Str;
        }

        if (typeof Str == "boolean") {
            Str = Str ? "true" : "false";
            return Str;
        }

        return String(Str || "");
    }

    /**
     * 格式化数字为float(强制) 浮点
     * @param Num
     * @returns
     */
    export function float(Num: any): number {
        if (!Num) return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num?.valueOf();
        }

        const MAX_VALUE = Math.pow(2, 31);
        const MIN_VALUE = -(Math.pow(2, 31));

        if (typeof Num == "string") {
            Num = parseFloat(Num);
            if (isNaN(Num)) return 0;

            if (Num >= MAX_VALUE) {
                Num = parseFloat(string(MAX_VALUE - 1) + ".999");
            }

            if (Num <= MIN_VALUE) {
                Num = parseFloat(string(MIN_VALUE) + ".999");
            }

            return Num;
        }

        if (typeof Num == "number" && !isNaN(Num)) return Num;
        // true == 1
        if (Num && typeof Num == "boolean") Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean") Num = 0;


        if (Num >= MAX_VALUE) {
            Num = parseFloat(string(MAX_VALUE - 1) + ".999");
        }

        if (Num <= MIN_VALUE) {
            Num = parseFloat(string(MIN_VALUE) + ".999");
        }

        return Num;
    }

    /**
     * 格式化数字为int(强制) 取整
     * @param Num 整数型
     * @returns
     */
    export function int(Num: any): number {
        if (!Num) return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num?.valueOf();
        }

        if (typeof Num == "bigint") {
            Num = Number(Num);
        }
        // 取整
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num)) return Num;
        // true == 1
        if (Num && typeof Num == "boolean") Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean") Num = 0;

        const MAX_VALUE = Math.pow(2, 31);
        const MIN_VALUE = -(Math.pow(2, 31));

        // 64bit log 
        if (Num >= MAX_VALUE) {
            Num = MAX_VALUE - 1;
        }

        if (Num <= MIN_VALUE) {
            Num = MIN_VALUE;
        }

        return Num;
    }
    /**
     * 格式化数字为int(强制) 取整
     * @param Num 整数型
     * @returns
     */
    export function long(Num: any): number {
        if (!Num) return 0;
        if (typeof Num == "object" && Num instanceof Number) {
            Num = Num?.valueOf();
        }
        if (typeof Num == "bigint") {
            Num = Number(Num);
        }
        // 取整
        Num = Math.trunc(Num + 0);
        if (typeof Num == "number" && !isNaN(Num)) return Num;
        // true == 1
        if (Num && typeof Num == "boolean") Num = 1;
        // false = 0;
        if (!Num && typeof Num == "boolean") Num = 0;

        const MAX_VALUE = Math.pow(2, 63);
        const MIN_VALUE = -(Math.pow(2, 63));

        // 64bit log 
        if (Num >= MAX_VALUE) {
            Num = MAX_VALUE - 1;
        }

        if (Num <= MIN_VALUE) {
            Num = MIN_VALUE;
        }

        return Num;
    }

    /**
     * 文本数组
     * @param array 
     * @returns 
     */
    export function stringArray(array: Set<any> | Array<any>) {
        let dataList: string[] = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(string(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(string(cout));
            }
        }
        return dataList;
    }

    export function is_stringArray(array: Array<any>): array is Array<string> {
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                if (typeof cout != "string") {
                    return false;
                }

            }
        } else { return false; }

        return true;
    }
    export function convertMultiStringArray(input: string): string[];
    export function convertMultiStringArray(input: Array<string | number>): string;
    export function convertMultiStringArray(input: Set<string | number>): string;
    /**
     * 纯文本数组 \0 截断单个string  \0\0结束
     * @param input 
     */
    export function convertMultiStringArray(input: unknown): unknown {
        if (typeof input == "string") {
            const temp = input.replace(/[\0]+$/, '').split("\0");

            for (let index = 0; index < 2; index++) {
                if (temp.at(-1)) {
                    return temp;
                }
                temp && temp.pop();
            }
        }

        if (Array.isArray(input)) {
            let temp = "";
            for (let index = 0; index < input.length; index++) {
                const element = input[index];
                temp += string(element) + "\0";
            }

            return temp.replace(/[\0]+$/, '\0\0');
        }

        if (input && input instanceof Set) {
            let temp = "";
            for (const element of input) {
                temp += string(element) + "\0";
            }
            return temp.replace(/[\0]+$/, '\0\0');
        }

        return []
    }


    /**
     * 文本数组
     * @param array 
     * @returns 
     */
    export function intArray(array: Set<any> | Array<any>) {
        let dataList: number[] = [];
        if (Array.isArray(array)) {
            for (let index = 0; index < array.length; index++) {
                const cout = array[index];
                dataList.push(int(cout));
            }
        }
        if (array instanceof Set) {
            for (const cout of array) {
                dataList.push(int(cout));
            }
        }
        return dataList;
    }

    /**
     * 将命令行内容组转为cmd文本
     * @param argv 
     */
    export function formatArgv(...argv: Array<any>[] | any[]): string {
        let argvs: string[] = [];
        let argvsResult: string[] = [];

        // 获取
        for (let index = 0; index < argv.length; index++) {
            const cout = argv[index];
            if (Array.isArray(cout)) {
                for (let cout_index = 0; cout_index < cout.length; cout_index++) {
                    const cout2 = cout[cout_index];
                    argvs.push(string(cout2));
                }
                continue;
            }
            argvs.push(string(cout));
        }

        // 处理
        for (let index = 0; index < argvs.length; index++) {
            let cout = argvs[index];
            if (!cout) continue;
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
    }

    /**
     * 拼合buff片段
     * @param buffList 
     * @returns 
     */
    export function concatBuff(buffList: Buffer[]): Buffer {
        let buffSize = 0;
        for (let index = 0; index < buffList.length; index++) {
            const buff = buffList[index];
            buffSize = buffSize + buff.byteLength;
        }
        let ResponseData = Buffer.concat([...buffList], buffSize);
        return ResponseData;
    }

    export function JSONP<T>(input: any, orData: T): T;
    export function JSONP(input: any): { [key: string | number]: any } | Array<any> | null;
    /**
     * 格式化json文本
     * @param input 
     * @returns 
     */
    export function JSONP(..._input: any[]): { [key: string | number]: any } | Array<any> | null {

        const result = {
            input: _input[0],
            is_or: _input.length >= 2,
            orData: _input.length >= 2 ? _input[1] : null,
        };

        const { input } = result;

        if (input && (typeof input == "object" || Array.isArray(input))) {
            return input;
        }

        try {
            return JSON.parse(input);
        } catch (error) { }


        if (result.is_or) {
            return result.orData;
        }

        return null;
    }

};

