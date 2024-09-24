"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Clipboard = void 0;
const main = require("./index");
const util = require("./util");
const EvalTask = require("./promiseEval");
const { ref } = util;
var Clipboard;
(function (Clipboard) {
    /**
     * 获取剪贴板文件路径列表 以\0切割
     * @returns
     */
    function getClipboardFilePaths() {
        const result = [];
        if (!main.Native.native.getClipboardFilePaths)
            return result;
        const temp = main.Native.native.getClipboardFilePaths().split("\0");
        if (temp.length && temp.at(-1) == "")
            temp.pop();
        return temp;
    }
    Clipboard.getClipboardFilePaths = getClipboardFilePaths;
    /**
     * 设置剪贴板本文或者html
     * @param text
     * @param is_html
     * @returns
     */
    function setClipboardText(text, is_html) {
        if (!main.Native.native.setClipboardText)
            return false;
        return main.Native.native.setClipboardText(ref.string(text), is_html || false);
    }
    Clipboard.setClipboardText = setClipboardText;
    /**
     * 获取剪贴板文本
     * @returns
     */
    function getClipboardText() {
        if (!main.Native.native.getClipboardText)
            return null;
        return main.Native.native.getClipboardText();
    }
    Clipboard.getClipboardText = getClipboardText;
    /**
     * 清空剪贴板
     * @returns
     */
    function clearClipboard() {
        if (!main.Native.native.clearClipboard)
            return false;
        return main.Native.native.clearClipboard();
    }
    Clipboard.clearClipboard = clearClipboard;
    /**
     * 设置文件路径列表
     * @param paths 支持以 \0 切割的路径或者单文件路径 或者数组
     */
    function setClipboardFilePaths(paths) {
        if (!main.Native.native.setClipboardFilePaths)
            return false;
        return main.Native.native.setClipboardFilePaths(Array.isArray(paths) ? ref.stringArray(paths) : ref.string(paths));
    }
    Clipboard.setClipboardFilePaths = setClipboardFilePaths;
    /**
     * 获取剪贴板文本 `async`
     * @returns
     */
    Clipboard.getClipboardText2 = EvalTask.promiseEvalTask.getClipboardText2;
    /**
     * 获取剪贴板文本 `sync`
     */
    Clipboard.getClipboardText2Sync = Clipboard.getClipboardText2;
    /**
     * 获取剪贴板中的文件列表 `async`
     * @returns
     */
    Clipboard.getClipboardFilePaths2 = EvalTask.promiseEvalTask.getClipboardFilePaths2;
    /**
     * 获取剪贴板中的文件列表 `sync`
     */
    Clipboard.getClipboardFilePaths2Sync = getClipboardFilePaths;
    /**
     * 获取剪贴板中的html
     * @returns
     */
    function getClipboardHTML() {
        if (!main.Native.native.getClipboardHTML)
            return null;
        return main.Native.native.getClipboardHTML();
    }
    Clipboard.getClipboardHTML = getClipboardHTML;
    /**
     * 枚举剪贴板包含的格式
     * @returns
     */
    function enumClipboardFormats() {
        if (!main.Native.native.enumClipboardFormats)
            return [];
        try {
            return JSON.parse(main.Native.native.enumClipboardFormats());
        }
        catch (error) { }
        return [];
    }
    Clipboard.enumClipboardFormats = enumClipboardFormats;
    /**
     * 获取剪贴板内容响应
     * @returns
     */
    function getClipboardInfo() {
        if (!main.Native.native.getClipboardInfo)
            return null;
        return main.Native.native.getClipboardInfo();
    }
    Clipboard.getClipboardInfo = getClipboardInfo;
})(Clipboard = exports.Clipboard || (exports.Clipboard = {}));
;
