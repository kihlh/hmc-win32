"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.captureBmp2Sync = exports.captureBmp2 = exports.setFolderIcon = exports.getTrayList = exports.setClipboardFilePaths = exports.clearClipboard = exports.getClipboardText = exports.setClipboardText = exports.getClipboardFilePaths = exports.readElectronHandle = exports.showContextMenu = exports.captureBmpToFile = exports.captureBmpToBuff = exports.getThumbnailPng = exports.closeWindow2Sync = exports.closeWindow2 = exports.asyncTaskQueue = exports.native2 = exports.HMCC = void 0;
const hmc_1 = require("./hmc");
var HMCC;
(function (HMCC) {
    let FS_MK_LINK_TARGET_TYPE;
    (function (FS_MK_LINK_TARGET_TYPE) {
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_DIR_SYMLINK"] = 166] = "CREATE_DIR_SYMLINK";
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_SYMLINK"] = 168] = "CREATE_SYMLINK";
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_HARD_LINK"] = 170] = "CREATE_HARD_LINK";
        FS_MK_LINK_TARGET_TYPE[FS_MK_LINK_TARGET_TYPE["CREATE_SYMBOLIC_LINK"] = 172] = "CREATE_SYMBOLIC_LINK";
    })(FS_MK_LINK_TARGET_TYPE = HMCC.FS_MK_LINK_TARGET_TYPE || (HMCC.FS_MK_LINK_TARGET_TYPE = {}));
})(HMCC = exports.HMCC || (exports.HMCC = {}));
;
/**
 * @zh-cn 静态调用 hmc.dll (注意如果您不知道这个是什么作用 请勿随意调用 参数错误有可能会导致进程崩溃)
 * @en-us Static call to hmc.dll (Note that if you don't know what this does, don't call it at random.  Parameter errors may cause the process to crash)
 */
const get_native = (binPath) => {
    function _require_bin() {
        try {
            if (binPath)
                return require(binPath);
            if (process.arch.match(/^(x32|ia32)$/))
                return require("./bin/HMC@Beta_x86.node");
            if (process.arch.match(/^x64$/))
                return require("./bin/HMC@Beta_x64.node");
        }
        catch (O_O) {
        }
        return null;
    }
    let Native = (process.platform == "win32" ? _require_bin() : null) || {};
    return Native;
};
exports.native2 = get_native();
class AsyncFunctionTaskQueue {
    constructor() {
        this.queues = new Map();
    }
    async runTask(fn, ...args) {
        if (!this.queues.has(fn)) {
            this.queues.set(fn, {
                queue: [],
                executing: false
            });
        }
        const queueObj = this.queues.get(fn);
        return new Promise((resolve, reject) => {
            queueObj.queue.push({ args, resolve, reject });
            this.next(fn);
        });
    }
    async next(fn) {
        const queueObj = this.queues.get(fn);
        if (queueObj.executing || queueObj.queue.length === 0) {
            return;
        }
        const { args, resolve, reject } = queueObj.queue.shift();
        queueObj.executing = true;
        try {
            const result = await fn(...args);
            resolve(result);
        }
        catch (error) {
            reject(error);
        }
        finally {
            queueObj.executing = false;
            this.next(fn);
        }
    }
}
exports.asyncTaskQueue = new AsyncFunctionTaskQueue();
/**
 * 关闭窗口 异步
 * - 1 温柔的关闭 (正常关闭)
 * - 2 关闭 / 系统级(半强制)
 * - 3 关闭线程 (强制)
 */
async function closeWindow2(handle, grade) {
    if (!(exports.native2 === null || exports.native2 === void 0 ? void 0 : exports.native2.closeWindow2)) {
        return Promise.resolve(false);
    }
    return exports.asyncTaskQueue.runTask(exports.native2.closeWindow2, handle, grade);
}
exports.closeWindow2 = closeWindow2;
/**
 * [同步 不支持并发] 关闭窗口
 * - 1 温柔的关闭 (正常关闭)
 * - 2 关闭 / 系统级(半强制)
 * - 3 关闭线程 (强制)
 */
function closeWindow2Sync(handle, grade) {
    return (exports.native2 === null || exports.native2 === void 0 ? void 0 : exports.native2.closeWindow2Sync) ? exports.native2 === null || exports.native2 === void 0 ? void 0 : exports.native2.closeWindow2Sync(hmc_1.ref.int(handle), grade || 1) : false;
}
exports.closeWindow2Sync = closeWindow2Sync;
function getThumbnailPng(...args) {
    if (!args.length || typeof args[0] != "string")
        return null;
    if (args.length == 3 && typeof args[1] != "string")
        return false;
    if (args.length <= 2) {
        return exports.native2.getThumbnailPng ? exports.native2.getThumbnailPng(hmc_1.ref.string(args[0]), hmc_1.ref.int(args[1] || 256)) : null;
    }
    if (args.length == 3) {
        return exports.native2.getThumbnailPng ? exports.native2.getThumbnailPng(hmc_1.ref.string(args[0]), hmc_1.ref.string(args[1]), hmc_1.ref.int(args[2] || 256)) : false;
    }
    return null;
}
exports.getThumbnailPng = getThumbnailPng;
/**
 * 截图bmp到缓冲区
 * @param x 起点
 * @param y 起点
 * @param nScopeWidth 矩形宽
 * @param nScopeHeight 矩形高
 * @returns
 */
function captureBmpToBuff(x, y, nScopeWidth, nScopeHeight) {
    return (exports.native2 === null || exports.native2 === void 0 ? void 0 : exports.native2.captureBmpToBuff) ?
        exports.native2 === null || exports.native2 === void 0 ? void 0 : exports.native2.captureBmpToBuff(hmc_1.ref.int(x || 0), hmc_1.ref.int(y || 0), hmc_1.ref.int(nScopeWidth || 0), hmc_1.ref.int(nScopeHeight || 0))
        : null;
}
exports.captureBmpToBuff = captureBmpToBuff;
/**
 * 截图bmp到文件
 * @param x 起点
 * @param y 起点
 * @param nScopeWidth 矩形宽
 * @param nScopeHeight 矩形高
 * @returns
 */
function captureBmpToFile(path, x, y, nScopeWidth, nScopeHeight) {
    return (exports.native2 === null || exports.native2 === void 0 ? void 0 : exports.native2.captureBmpToFile) ?
        exports.native2 === null || exports.native2 === void 0 ? void 0 : exports.native2.captureBmpToFile(hmc_1.ref.string(path), hmc_1.ref.int(x || 0), hmc_1.ref.int(y || 0), hmc_1.ref.int(nScopeWidth || 0), hmc_1.ref.int(nScopeHeight || 0))
        : void 0;
}
exports.captureBmpToFile = captureBmpToFile;
/**
 * 弹出右键菜单的接口
 * @param hwnd 调用窗口 / 允许为null
 * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
 * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
 * @param y 坐标
 */
function showContextMenu(hwnd, file, x, y) {
    return (exports.native2 === null || exports.native2 === void 0 ? void 0 : exports.native2.showContextMenu) ?
        exports.native2 === null || exports.native2 === void 0 ? void 0 : exports.native2.showContextMenu(hmc_1.ref.int(hwnd || 0), Array.isArray(file) ? file : hmc_1.ref.string(file), hmc_1.ref.int(x || 0), hmc_1.ref.int(y || 0))
        : false;
}
exports.showContextMenu = showContextMenu;
/**
 * 将 electron 句柄内存缓冲区转换为标准 窗口数字句柄
 * @param handleBuffer 例如 Electron.BrowserWindow.getFocusedWindow().getNativeWindowHandle()
 * @returns
 */
function readElectronHandle(handleBuffer) {
    let num = 0;
    // Node.js 10.5.0 以上版本
    if (typeof BigInt != 'undefined') {
        let handleBigInt = handleBuffer.readBigUInt64LE();
        return (Number(handleBigInt));
    }
    else {
        if (process.platform == 'win32') {
            num = handleBuffer.readUInt32LE();
        }
        else if (process.platform == 'darwin') {
            num = handleBuffer.readUInt32LE(0) + 2 * 32 * handleBuffer.readUInt32LE(4);
        }
        else {
            num = handleBuffer.readUInt32LE(0) + 2 * 32 * handleBuffer.readUInt32LE(4);
        }
        return num;
    }
    return num;
}
exports.readElectronHandle = readElectronHandle;
/**
 * 获取剪贴板文件路径列表 以\0切割
 * @returns
 */
function getClipboardFilePaths() {
    const result = [];
    if (!exports.native2.getClipboardFilePaths)
        return result;
    const temp = exports.native2.getClipboardFilePaths().split("\0");
    if (temp.length && temp.at(-1) == "")
        temp.pop();
    return temp;
}
exports.getClipboardFilePaths = getClipboardFilePaths;
/**
 * 设置剪贴板本文或者html
 * @param text
 * @param is_html
 * @returns
 */
function setClipboardText(text, is_html) {
    if (!exports.native2.setClipboardText)
        return false;
    return exports.native2.setClipboardText(hmc_1.ref.string(text), is_html || false);
}
exports.setClipboardText = setClipboardText;
/**
 * 获取剪贴板文本
 * @returns
 */
function getClipboardText() {
    if (!exports.native2.getClipboardText)
        return null;
    return exports.native2.getClipboardText();
}
exports.getClipboardText = getClipboardText;
/**
 * 清空剪贴板
 * @returns
 */
function clearClipboard() {
    if (!exports.native2.clearClipboard)
        return false;
    return exports.native2.clearClipboard();
}
exports.clearClipboard = clearClipboard;
/**
 * 设置文件路径列表
 * @param paths 支持以 \0 切割的路径或者单文件路径 或者数组
 */
function setClipboardFilePaths(paths) {
    if (!exports.native2.setClipboardFilePaths)
        return false;
    return exports.native2.setClipboardFilePaths(Array.isArray(paths) ? hmc_1.ref.stringArray(paths) : hmc_1.ref.string(paths));
}
exports.setClipboardFilePaths = setClipboardFilePaths;
/**
 * 获取托盘图标列表
 * 1.4.6 起返回json文本
 * ? win11 在22621.1000版本之后失效 具体原因查看https://github.com/kihlh/hmc-win32/issues/36
 */
function getTrayList() {
    if (!exports.native2.getTrayList)
        return [];
    return JSON.parse(exports.native2.getTrayList());
}
exports.getTrayList = getTrayList;
/**
 * 设置文件夹的缩略图
 * @param folderPath 路径
 * @param iconPath 图标路径
 * @param iconIndex 图标索引 比如exe中的0
 * @returns
 */
function setFolderIcon(folderPath, iconPath, iconIndex) {
    if (!exports.native2.setFolderIcon)
        return false;
    return exports.native2.setFolderIcon(hmc_1.ref.string(folderPath), hmc_1.ref.string(iconPath), hmc_1.ref.int(iconIndex || 0));
}
exports.setFolderIcon = setFolderIcon;
async function captureBmp2(...args) {
    if (!exports.native2.captureBmp2)
        return Promise.resolve(null);
    if (!args.length) {
        return exports.asyncTaskQueue.runTask(exports.native2.captureBmp2);
    }
    if (args.length == 1) {
        //  captureBmp2(handle: number|HWND): Promise<Buffer | null>;
        if (typeof args[0] == "number" || typeof args[0] == "object") {
            return exports.asyncTaskQueue.runTask(exports.native2.captureBmp2, hmc_1.ref.int(args[0]));
        }
        return exports.asyncTaskQueue.runTask(exports.native2.captureBmp2, hmc_1.ref.string(args[0]));
    }
    if (args.length == 2) {
        return exports.asyncTaskQueue.runTask(exports.native2.captureBmp2, hmc_1.ref.int(args[0]), hmc_1.ref.string(args[1]));
    }
    if (args.length == 4) {
        return exports.asyncTaskQueue.runTask(exports.native2.captureBmp2, hmc_1.ref.int(args[0]), hmc_1.ref.int(args[1]), hmc_1.ref.int(args[2]), hmc_1.ref.int(args[3]));
    }
    if (args.length == 5) {
        return exports.asyncTaskQueue.runTask(exports.native2.captureBmp2, hmc_1.ref.string(args[0]), hmc_1.ref.int(args[1]), hmc_1.ref.int(args[2]), hmc_1.ref.int(args[3]), hmc_1.ref.int(args[4]));
    }
    return Promise.resolve(null);
}
exports.captureBmp2 = captureBmp2;
;
function captureBmp2Sync(...args) {
    if (!exports.native2.captureBmp2Sync)
        return null;
    if (!args.length) {
        return exports.native2.captureBmp2Sync();
    }
    if (args.length == 1) {
        //  captureBmp2(handle: number|HWND): Promise<Buffer | null>;
        if (typeof args[0] == "number" || typeof args[0] == "object") {
            return exports.native2.captureBmp2Sync(hmc_1.ref.int(args[0]));
        }
        return exports.native2.captureBmp2Sync(hmc_1.ref.string(args[0]));
    }
    if (args.length == 2) {
        return exports.native2.captureBmp2Sync(hmc_1.ref.int(args[0]), hmc_1.ref.string(args[1]));
    }
    if (args.length == 4) {
        return exports.native2.captureBmp2Sync(hmc_1.ref.int(args[0]), hmc_1.ref.int(args[1]), hmc_1.ref.int(args[2]), hmc_1.ref.int(args[3]));
    }
    if (args.length == 5) {
        return exports.native2.captureBmp2Sync(hmc_1.ref.string(args[0]), hmc_1.ref.int(args[1]), hmc_1.ref.int(args[2]), hmc_1.ref.int(args[3]), hmc_1.ref.int(args[4]));
    }
    return null;
}
exports.captureBmp2Sync = captureBmp2Sync;
;
