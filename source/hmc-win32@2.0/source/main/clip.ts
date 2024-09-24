import main = require("./index");
import util = require("./util");
import EvalTask = require("./promiseEval");

const { ref } = util;

export module Clipboard {


    /**
     * 获取剪贴板文件路径列表 以\0切割
     * @returns 
     */
    export function getClipboardFilePaths() {
        const result: Array<string> = [];
        if (!main.Native.native.getClipboardFilePaths) return result;

        const temp = main.Native.native.getClipboardFilePaths().split("\0");
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
        if (!main.Native.native.setClipboardText) return false;
        return main.Native.native.setClipboardText(ref.string(text), is_html || false);
    }

    /**
     * 获取剪贴板文本
     * @returns 
     */
    export function getClipboardText() {
        if (!main.Native.native.getClipboardText) return null;
        return main.Native.native.getClipboardText();
    }

    /**
     * 清空剪贴板
     * @returns 
     */
    export function clearClipboard() {
        if (!main.Native.native.clearClipboard) return false;
        return main.Native.native.clearClipboard();
    }

    /**
     * 设置文件路径列表 
     * @param paths 支持以 \0 切割的路径或者单文件路径 或者数组
     */
    export function setClipboardFilePaths(paths: string | string[]) {
        if (!main.Native.native.setClipboardFilePaths) return false;
        return main.Native.native.setClipboardFilePaths(Array.isArray(paths) ? ref.stringArray(paths) : ref.string(paths));
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
    export function getClipboardHTML(): main.HMC2_MODE.CLIP_HTML_INFO | null {
        if (!main.Native.native.getClipboardHTML) return null;
        return main.Native.native.getClipboardHTML();
    }

    /**
     * 枚举剪贴板包含的格式
     * @returns 
     */
    export function enumClipboardFormats():Array<{"type":string,"type_name":string}> {
        if (!main.Native.native.enumClipboardFormats) return [];
        try {
            return JSON.parse(main.Native.native.enumClipboardFormats());
        } catch (error) { }
        return [];
    }

    /**
     * 获取剪贴板内容响应
     * @returns 
     */
    export function getClipboardInfo() {
        if (!main.Native.native.getClipboardInfo) return null;
        return main.Native.native.getClipboardInfo();
    }

};