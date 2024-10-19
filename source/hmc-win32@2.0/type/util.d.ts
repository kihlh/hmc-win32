/// <reference types="node" />
export declare namespace ref {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    function path(Str: any): string;
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    function bool(bool: any): boolean;
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    function string(Str: any): any;
    /**
     * 格式化数字为float(强制) 浮点
     * @param Num
     * @returns
     */
    function float(Num: any): number;
    /**
     * 格式化数字为int(强制) 取整
     * @param Num 整数型
     * @returns
     */
    function int(Num: any): number;
    /**
     * 格式化数字为int(强制) 取整
     * @param Num 整数型
     * @returns
     */
    function long(Num: any): number;
    /**
     * 文本数组
     * @param array
     * @returns
     */
    function stringArray(array: Set<any> | Array<any>): string[];
    function is_stringArray(array: Array<any>): array is Array<string>;
    function convertMultiStringArray(input: string): string[];
    function convertMultiStringArray(input: Array<string | number>): string;
    function convertMultiStringArray(input: Set<string | number>): string;
    /**
     * 文本数组
     * @param array
     * @returns
     */
    function intArray(array: Set<any> | Array<any>): number[];
    /**
     * 将命令行内容组转为cmd文本
     * @param argv
     */
    function formatArgv(...argv: Array<any>[] | any[]): string;
    /**
     * 拼合buff片段
     * @param buffList
     * @returns
     */
    function concatBuff(buffList: Buffer[]): Buffer;
    function JSONP<T>(input: any, orData: T): T;
    function JSONP(input: any): {
        [key: string | number]: any;
    } | Array<any> | null;
}
