import { ref } from "./util";
import EvalTask = require("./promiseEval");
import { HMC } from "./HMC";
import { Native } from "./Native";

export namespace Clipboard {


    /**
     * 获取剪贴板文件路径列表 以\0切割
     * @returns 
     */
    export function getClipboardFilePaths() {
        const result: Array<string> = [];
        if (!Native.native.getClipboardFilePaths) return result;

        const temp = Native.native.getClipboardFilePaths().split("\0");
        if (temp.length && temp.at(-1) == "") temp.pop();

        return temp;
    }

    /**
     * 设置剪贴板本文或者html
     * @param text 
     * @param is_html 
     * @returns 
     */
    export function setClipboardText(text: string, is_html?: boolean) {
        if (!Native.native.setClipboardText) return false;
        return Native.native.setClipboardText(ref.string(text), is_html || false);
    }

    /**
     * 获取剪贴板文本
     * @returns 
     */
    export function getClipboardText() {
        if (!Native.native.getClipboardText) return null;
        return Native.native.getClipboardText();
    }

    /**
     * 清空剪贴板
     * @returns 
     */
    export function clearClipboard() {
        if (!Native.native.clearClipboard) return false;
        return Native.native.clearClipboard();
    }

    /**
     * 设置文件路径列表 
     * @param paths 支持以 \0 切割的路径或者单文件路径 或者数组
     */
    export function setClipboardFilePaths(paths: string | string[]) {
        if (!Native.native.setClipboardFilePaths) return false;
        return Native.native.setClipboardFilePaths(Array.isArray(paths) ? ref.stringArray(paths) : ref.string(paths));
    }

    /**
     * 获取剪贴板文本 `async` 
     * @returns 
     */
    export const getClipboardText2 = EvalTask.promiseEvalTask.getClipboardText2;

    /**
     * 获取剪贴板文本 `sync` 
     */
    export const getClipboardText2Sync = getClipboardText2;

    /**
     * 获取剪贴板中的文件列表 `async` 
     * @returns 
     */
    export const getClipboardFilePaths2 = EvalTask.promiseEvalTask.getClipboardFilePaths2;

    /**
     * 获取剪贴板中的文件列表 `sync` 
     */
    export const getClipboardFilePaths2Sync = getClipboardFilePaths;

    /**
     * 获取剪贴板中的html
     * @returns 
     */
    export function getClipboardHTML(): HMC.CLIP_HTML_INFO | null {
        if (!Native.native.getClipboardHTML) return null;
        return Native.native.getClipboardHTML();
    }

    /**
     * 枚举剪贴板包含的格式
     * @returns 
     */
    export function enumClipboardFormats(): Array<{ "type": string, "type_name": string }> {
        if (!Native.native.enumClipboardFormats) return [];
        try {
            return JSON.parse(Native.native.enumClipboardFormats());
        } catch (error) { }
        return [];
    }

    /**
     * 获取剪贴板内容响应
     * @returns 
     */
    export function getClipboardInfo() {
        if (!Native.native.getClipboardInfo) return null;
        return Native.native.getClipboardInfo();
    }

};