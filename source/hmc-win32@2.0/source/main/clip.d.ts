import main = require("./index");
export declare module Clipboard {
    /**
     * 获取剪贴板文件路径列表 以\0切割
     * @returns
     */
    function getClipboardFilePaths(): string[];
    /**
     * 设置剪贴板本文或者html
     * @param text
     * @param is_html
     * @returns
     */
    function setClipboardText(text: string, is_html?: boolean): boolean;
    /**
     * 获取剪贴板文本
     * @returns
     */
    function getClipboardText(): string | null;
    /**
     * 清空剪贴板
     * @returns
     */
    function clearClipboard(): boolean;
    /**
     * 设置文件路径列表
     * @param paths 支持以 \0 切割的路径或者单文件路径 或者数组
     */
    function setClipboardFilePaths(paths: string | string[]): boolean;
    /**
     * 获取剪贴板文本 `async`
     * @returns
     */
    const getClipboardText2: () => Promise<string | null>;
    /**
     * 获取剪贴板文本 `sync`
     */
    const getClipboardText2Sync: () => Promise<string | null>;
    /**
     * 获取剪贴板中的文件列表 `async`
     * @returns
     */
    const getClipboardFilePaths2: {
        (): Promise<string[]>;
        (): Promise<string[]>;
    };
    /**
     * 获取剪贴板中的文件列表 `sync`
     */
    const getClipboardFilePaths2Sync: typeof getClipboardFilePaths;
    /**
     * 获取剪贴板中的html
     * @returns
     */
    function getClipboardHTML(): main.HMC2_MODE.CLIP_HTML_INFO | null;
    /**
     * 枚举剪贴板包含的格式
     * @returns
     */
    function enumClipboardFormats(): Array<{
        "type": string;
        "type_name": string;
    }>;
    /**
     * 获取剪贴板内容响应
     * @returns
     */
    function getClipboardInfo(): {
        format: string;
        hwnd: number;
        id: number;
        formatCount: number;
    } | null;
}
