/// <reference types="node" />
export declare const ref: {
    /**
    * 将内容格式化为文本路径
    * @param Str
    * @returns
    */
    path(Str: any): string;
    /**
     * 格式化为bool
     * @param bool
     * @returns
     */
    bool(bool: any): boolean;
    /**
     * 将内容格式化为文本
     * @param Str
     * @returns
     */
    string(Str: any): string;
    /**
     * 格式化数字为float(强制) 浮点
     * @param Num
     * @returns
     */
    float(Num: any): number;
    /**
     * 格式化数字为int(强制) 取整
     * @param Num
     * @returns
     */
    int(Num: any): number;
    /**
     * 文本数组
     * @param array
     * @returns
     */
    stringArray(array: Set<any> | Array<any>): string[];
    /**
     * 文本数组
     * @param array
     * @returns
     */
    intArray(array: Set<any> | Array<any>): number[];
    /**
     * 将命令行内容组转为cmd文本
     * @param argv
     */
    formatArgv(...argv: Array<any>[] | any[]): string;
    /**
     * 拼合buff片段
     * @param buffList
     * @returns
     */
    concatBuff(buffList: Buffer[]): Buffer;
};
