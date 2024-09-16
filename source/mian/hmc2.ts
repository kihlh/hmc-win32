import { native } from "hmc-win32";
import { HMC } from "./hmc";
import { HWND, ref } from "./hmc";


export module HMCC {
    export type CLIP_HTML_INFO = {
        data: string;
        EndFragment: number;
        EndHTML: number;
        is_valid: boolean;
        SourceURL: string;
        StartFragment: number;
        StartHTML: number;
        Version: number;
    }
    export enum FS_MK_LINK_TARGET_TYPE {
        CREATE_DIR_SYMLINK = 166,
        CREATE_SYMLINK = 168,
        CREATE_HARD_LINK = 170,
        CREATE_SYMBOLIC_LINK = 172
    }
}



export type HMCC = {

    /**
     * 关闭窗口 同步
     * @param handle 句柄 
     * @param grade 等级
     * - 1 关闭 / 非强制
     * - 2 关闭 / 系统级(半强制)
     * - 3 关闭线程 (强制)
     */
    closeWindow2?: (handle: number, grade: 1 | 2 | 3) => Promise<boolean>;

    /**
     * 关闭窗口 同步
     * @param handle 句柄 
     * @param grade 等级
     * - 1 关闭 / 非强制
     * - 2 关闭 / 系统级(半强制)
     * - 3 关闭线程 (强制)
     */
    closeWindow2Sync?: (handle: number, grade: 1 | 2 | 3) => boolean;
    // 截图到缓冲区中
    captureBmpToBuff?: (x: number, y: number, nScopeWidth: number, nScopeHeight: number) => null | Buffer;
    // 截图到文件中
    captureBmpToFile?: (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number) => undefined;
    // 截图
    captureBmp2?: HMCC.CaptureBmp;
    // 截图
    captureBmp2Sync?: HMCC.CaptureBmpSync;
    // 获取剪贴板文件路径列表 以\0切割
    getClipboardFilePaths?: () => string;
    // 设置剪贴板本文或者html
    setClipboardText?: (text: string, is_html?: boolean) => boolean;
    // 获取剪贴板文本
    getClipboardText?: () => string | null;
    // 清空剪贴板
    clearClipboard?: () => boolean;
    // 设置文件路径列表 支持以 \0 切割 或者数组
    setClipboardFilePaths?: (paths: string | string[]) => boolean;
    // 获取剪贴板内容响应
    getClipboardInfo?: () => {
        // json数组(文本)
        format: string;
        // 设置剪贴板的窗口句柄
        hwnd: number;
        // 剪贴板唯一id
        id: number;
        // 当前格式包含数量
        formatCount: number;
    };
    // 枚举剪贴板包含的格式
    enumClipboardFormats?: () => `{"type":${string},"type_name":${string}}...[]`;

    /**
     * 获取剪贴板中的html
     */
    getClipboardHTML?: () => HMCC.CLIP_HTML_INFO | null;
    /**
     * 获取托盘图标列表
     * ? win11 在22621.1000版本之后失效 具体原因查看https://github.com/kihlh/hmc-win32/issues/36
     */
    getTrayList?: () => string;
    /**
     * 删除文件到垃圾桶
     * @param trash_path 处理的路径
     * @param is_Recycle 可以回收 
     * @param isShow 显示窗口
     */
    trashFile?: (trash_path: string, is_Recycle: boolean, isShow: boolean) => boolean;
    /**
     * 清空回收站
     * @param root_path 文件或者根目录 
     * @param isShow 是否显示窗口
     */
    clearTrash?: (root_path: string, isShow: boolean) => boolean;
    /**
     * 
     * @param filePath 
     * @param newFilePath 
     * @param isShowConfirm 
     * @param isShow 
     * @param isShowProgress 
     * @param trash_ok 
     * @returns 
     */
    copyFile?: (filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean, trash_ok: boolean) => boolean;

    /**
     * 
     * @param filePath 
     * @param newFilePath 
     * @param isShowConfirm 
     * @param isShow 
     * @param isShowProgress 
     * @param trash_ok 
     * @returns 
     */
    moveFile?: (filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean, trash_ok: boolean) => boolean;

    getThumbnailPng?: (...args: unknown[]) => unknown;
    // getThumbnailPng?: (source: string, img_size: 16 | 64 | 128 | 256) => Buffer;
    // getThumbnailPng?: (source: string, output: string, img_size: 16 | 64 | 128 | 256) => boolean;

    /**
     * 获取 软/硬 链接的指向内容
     * @param Linkath 
     */
    getLinkTarget?: (Linkath: string) => string | string[] | null;

    /**
     * 设置文件夹的缩略图
     * @param folderPath 路径
     * @param iconPath 图标路径
     * @param iconIndex 图标索引 比如exe中的0
     * @returns 
     */
    setFolderIcon?: (folderPath: string, iconPath: string, iconIndex?: number) => boolean;

    /**
     * 判断指定文件是否是 软链接/硬链接
     * @param path 
     * @returns 
     */
    isLinkLink?: (path: string) => boolean;

    /**
     * 创建 软链接/硬链接/目录连接点/文件夹链接
     * @param targetType 创建类型
     * - 文件夹链接 CREATE_DIR_SYMLINK = 166
     * - 软链接 CREATE_SYMLINK = 168
     * - 硬链接 CREATE_HARD_LINK = 170
     * - 目录连接点 CREATE_SYMBOLIC_LINK = 172
     * @param targetPath 目标位置
     * @param sourcePath 源文件路径
     * @returns 
     */
    createFsLink?: (targetType: HMCC.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string) => boolean;
    // DECLARE_NAPI_METHODRM("setShortcutLink", setShortcutLink),
    // DECLARE_NAPI_METHODRM("getSystemMetrics", getSystemMetrics),
    // DECLARE_NAPI_METHODRM("getShortcutLink", getShortcutLink),
    // DECLARE_NAPI_METHODRM("setConversionStatus", setConversionStatus),
    /**
     * 弹出右键菜单的接口
     * @param hwnd 调用窗口 / 允许为null
     * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
     * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
     * @param y 坐标
     */
    showContextMenu?: (hwnd: number | null, file: string | string[], x: number, y: number) => boolean;

    StartupClassConstructor: () => any;
};



export module HMCC {
    export interface CaptureBmp {
        (handle: number): Promise<Buffer | null>;
        (handle: number, path: string): Promise<boolean>;
        (path: string): Promise<boolean>;
        (): Promise<Buffer | null>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<Buffer | null>;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<boolean>;
    }

    export interface CaptureBmpSync {
        (handle: number): Buffer | null;
        (handle: number, path: string): boolean;
        (path: string): boolean;
        (): Buffer | null;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Buffer | null;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): boolean;
    }

};

/**
 * @zh-cn 静态调用 hmc.dll (注意如果您不知道这个是什么作用 请勿随意调用 参数错误有可能会导致进程崩溃)
 * @en-us Static call to hmc.dll (Note that if you don't know what this does, don't call it at random.  Parameter errors may cause the process to crash)
 */
const get_native: () => HMCC = (binPath?: string) => {
    function _require_bin(): HMCC | null {
        try {
            if (binPath) return require(binPath);
            if (process.arch.match(/^(x32|ia32)$/)) return require("./bin/HMC@Beta_x86.node");
            if (process.arch.match(/^x64$/)) return require("./bin/HMC@Beta_x64.node");
        } catch (O_O) {

        }
        return null;
    }

    // @ts-expect-error
    let Native: HMCC = (process.platform == "win32" ? _require_bin() : null) || {};

    return Native;
};

export const native2: HMCC = get_native();

class AsyncFunctionTaskQueue {
    queues: Map<(...args: any[]) => Promise<any>, any>;
    constructor() {
        this.queues = new Map();
    }

    async runTask<T>(fn: (...args: any[]) => Promise<T>, ...args: any[]): Promise<T> {
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

    async next<T>(fn: (...args: any[]) => Promise<T>) {
        const queueObj = this.queues.get(fn);

        if (queueObj.executing || queueObj.queue.length === 0) {
            return;
        }

        const { args, resolve, reject } = queueObj.queue.shift();
        queueObj.executing = true;

        try {
            const result = await fn(...args);
            resolve(result);
        } catch (error) {
            reject(error);
        } finally {
            queueObj.executing = false;
            this.next(fn);
        }
    }
}


export const asyncTaskQueue = new AsyncFunctionTaskQueue();

class Startup {
    #Startup: null | {
        has: (keyName: string) => boolean;
        hasOnce: (keyName: string) => boolean;
        remove: (keyName: string) => boolean;
        removeOnce: (keyName: string) => boolean;
        set: (keyName: string, path: string, cmd: string) => boolean;
        setOnce: (keyName: string, path: string, cmd: string) => boolean;
    } = null;

    #initialize() {
        if (!this.#Startup) {
            this.#Startup = native2.StartupClassConstructor();
        }
    }
    
    #root:"HKEY_LOCAL_MACHINE" = "HKEY_LOCAL_MACHINE";
    #pathRun ="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    #pathRunOnce = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
    constructor() { }

    has(keyName: string) {
        this.#initialize();
        return this.#Startup?.has(ref.string(keyName)) || false;
    }

    hasOnce(keyName: string) {
        this.#initialize();
        return this.#Startup?.hasOnce(ref.string(keyName)) || false;
    }


    remove(keyName: string) {
        this.#initialize();
        return this.#Startup?.remove(ref.string(keyName)) || false;
    }


    removeOnce(keyName: string) {
        this.#initialize();
        return this.#Startup?.removeOnce(ref.string(keyName)) || false;
    }

    set(keyName: string, path: string, cmd?: string) {
        this.#initialize();
        return this.#Startup?.set(ref.string(keyName), ref.string(path), ref.string(cmd || "")) || false;
    }

    setOnce(keyName: string, path: string, cmd?: string) {
        this.#initialize();
        return this.#Startup?.setOnce(ref.string(keyName), ref.string(path), ref.string(cmd || "")) || false;
    }

    enum() {
        const obj:{[key:string]:string} = {};
        const keys = native.enumRegistrKey(this.#root, this.#pathRun);
        for (let index = 0; index < keys.length; index++) {
            let at = keys[index];
            obj[at] = native.getStringRegKey(this.#root, this.#pathRun, at);
        }
        return obj;
    }
    
    enumOnce() {
        const obj:{[key:string]:string} = {};
        const keys = native.enumRegistrKey(this.#root, this.#pathRunOnce);
        for (let index = 0; index < keys.length; index++) {
            let at = keys[index];
            obj[at] = native.getStringRegKey(this.#root, this.#pathRunOnce, at);
        }
        return obj;
    }

    keys(){
        return native.enumRegistrKey(this.#root,this.#pathRun);
    }
    
    keysOnce(){
        return native.enumRegistrKey(this.#root,this.#pathRunOnce);
    }
}

export const startup = new Startup();

/**
 * 关闭窗口 异步
 * - 1 温柔的关闭 (正常关闭)
 * - 2 关闭 / 系统级(半强制)
 * - 3 关闭线程 (强制)
 */
export async function closeWindow2(handle: number | HWND, grade?: 1 | 2 | 3) {
    if (!native2?.closeWindow2) {
        return Promise.resolve(false)
    }

    return asyncTaskQueue.runTask(native2.closeWindow2, handle, grade);
}

/**
 * [同步 不支持并发] 关闭窗口
 * - 1 温柔的关闭 (正常关闭)
 * - 2 关闭 / 系统级(半强制)
 * - 3 关闭线程 (强制)
 */
export function closeWindow2Sync(handle: number | HWND, grade?: 1 | 2 | 3) {
    return native2?.closeWindow2Sync ? native2?.closeWindow2Sync(ref.int(handle), grade || 1) : false;
}

/**
 *  获取文件缩略图
 * @param source 文件
 * @param output 保存到
 * @param img_size 要求尺寸 建议为：
 * - 16 
 * - 32
 * - 64
 * - 128
 * - 256
 */
export function getThumbnailPng(source: string, output: string, img_size: 16 | 64 | 128 | 256): boolean;

/**
 *  获取文件缩略图
 * @param source 文件
 * @param img_size 要求尺寸 建议为：
 * - 16 
 * - 32
 * - 64
 * - 128
 * - 256
 */
export function getThumbnailPng(source: string, img_size: 16 | 64 | 128 | 256): Buffer | null;
export function getThumbnailPng(...args: unknown[]): unknown;

export function getThumbnailPng(...args: unknown[]): unknown {
    if (!args.length || typeof args[0] != "string") return null;

    if (args.length == 3 && typeof args[1] != "string") return false;

    if (args.length <= 2) {
        return native2.getThumbnailPng ? native2.getThumbnailPng(ref.string(args[0]), ref.int(args[1] || 256)) : null;
    }

    if (args.length == 3) {
        return native2.getThumbnailPng ? native2.getThumbnailPng(ref.string(args[0]), ref.string(args[1]), ref.int(args[2] || 256)) : false;
    }

    return null;
}

/**
 * 截图bmp到缓冲区
 * @param x 起点
 * @param y 起点
 * @param nScopeWidth 矩形宽 
 * @param nScopeHeight 矩形高
 * @returns 
 */
export function captureBmpToBuff(x?: number, y?: number, nScopeWidth?: number, nScopeHeight?: number) {
    return native2?.captureBmpToBuff ?
        native2?.captureBmpToBuff(ref.int(x || 0), ref.int(y || 0), ref.int(nScopeWidth || 0), ref.int(nScopeHeight || 0))
        : null;
}

/**
 * 截图bmp到文件
 * @param x 起点
 * @param y 起点
 * @param nScopeWidth 矩形宽 
 * @param nScopeHeight 矩形高
 * @returns 
 */
export function captureBmpToFile(path: string, x?: number, y?: number, nScopeWidth?: number, nScopeHeight?: number) {
    return native2?.captureBmpToFile ?
        native2?.captureBmpToFile(ref.string(path), ref.int(x || 0), ref.int(y || 0), ref.int(nScopeWidth || 0), ref.int(nScopeHeight || 0))
        : void 0;
}

/**
 * 弹出右键菜单的接口
 * @param hwnd 调用窗口 / 允许为null
 * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
 * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
 * @param y 坐标
 */
export function showContextMenu(hwnd?: number | null, file?: string | string[], x?: number, y?: number) {
    return native2?.showContextMenu ?
        native2?.showContextMenu(
            ref.int(hwnd || 0),
            Array.isArray(file) ? file : ref.string(file),
            ref.int(x || 0),
            ref.int(y || 0)
        )
        : false;
}

/**
 * 将 electron 句柄内存缓冲区转换为标准 窗口数字句柄
 * @param handleBuffer 例如 Electron.BrowserWindow.getFocusedWindow().getNativeWindowHandle()
 * @returns 
 */
export function readElectronHandle(handleBuffer: any) {
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


/**
 * 获取剪贴板文件路径列表 以\0切割
 * @returns 
 */
export function getClipboardFilePaths() {
    const result: Array<string> = [];
    if (!native2.getClipboardFilePaths) return result;

    const temp = native2.getClipboardFilePaths().split("\0");
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
    if (!native2.setClipboardText) return false;
    return native2.setClipboardText(ref.string(text), is_html || false);
}

/**
 * 获取剪贴板文本
 * @returns 
 */
export function getClipboardText() {
    if (!native2.getClipboardText) return null;
    return native2.getClipboardText();
}

/**
 * 清空剪贴板
 * @returns 
 */
export function clearClipboard() {
    if (!native2.clearClipboard) return false;
    return native2.clearClipboard();
}

/**
 * 设置文件路径列表 
 * @param paths 支持以 \0 切割的路径或者单文件路径 或者数组
 */
export function setClipboardFilePaths(paths: string | string[]) {
    if (!native2.setClipboardFilePaths) return false;
    return native2.setClipboardFilePaths(Array.isArray(paths) ? ref.stringArray(paths) : ref.string(paths));
}

/**
 * 获取托盘图标列表
 * 1.4.6 起返回json文本
 * ? win11 在22621.1000版本之后失效 具体原因查看https://github.com/kihlh/hmc-win32/issues/36
 */
export function getTrayList(): Array<HMC.TRAY_ICON> {
    if (!native2.getTrayList) return [];
    return JSON.parse(native2.getTrayList());
}

/**
 * 设置文件夹的缩略图
 * @param folderPath 路径
 * @param iconPath 图标路径
 * @param iconIndex 图标索引 比如exe中的0
 * @returns 
 */
export function setFolderIcon(folderPath: string, iconPath: string, iconIndex?: number) {

    if (!native2.setFolderIcon) return false;
    return native2.setFolderIcon(ref.string(folderPath), ref.string(iconPath), ref.int(iconIndex || 0));

}

/**
 * 截图主屏幕为bmp缓冲区 [异步]
 */
export function captureBmp2(): Promise<Buffer | null>;
/**
 * 截图窗口句柄区域为bmp缓冲区  [异步]
 * @param handle 句柄
 */
export function captureBmp2(handle: number | HWND): Promise<Buffer | null>;
/**
 * 截图主屏幕到文件中 [异步]
 * @param path 文件路径
 */
export function captureBmp2(path: string): Promise<boolean>;
/**
 * 截图窗口句柄区域为文件 [异步]
 * ? 不会提前将窗口前置 因此会包含其他信息
 * @param handle 句柄
 * @param path 文件路径
 */
export function captureBmp2(handle: number | HWND, path: string): Promise<boolean>;
/**
 * 截图主屏幕为bmp缓冲区 [异步]
 * @param x (x) 从屏幕左边到所在位置得像素数
 * @param y (y) 从屏幕顶部边到所在位置得像素数
 * @param nScopeWidth 要求宽度
 * @param nScopeHeight 要求高度
 */
export function captureBmp2(x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<Buffer | null>;
/**
 * 截图主屏幕为bmp文件 [异步]
 * @param x (x) 从屏幕左边到所在位置得像素数
 * @param y (y) 从屏幕顶部边到所在位置得像素数
 * @param nScopeWidth 要求宽度
 * @param nScopeHeight 要求高度
 */
export function captureBmp2(path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<boolean>;

export async function captureBmp2(...args: unknown[]): Promise<unknown> {

    if (!native2.captureBmp2) return Promise.resolve(null);
    if (!args.length) {
        return asyncTaskQueue.runTask(native2.captureBmp2);
    }

    if (args.length == 1) {
        //  captureBmp2(handle: number|HWND): Promise<Buffer | null>;
        if (typeof args[0] == "number" || typeof args[0] == "object") {
            return asyncTaskQueue.runTask(native2.captureBmp2, ref.int(args[0]));
        }
        return asyncTaskQueue.runTask(native2.captureBmp2, ref.string(args[0]));
    }


    if (args.length == 2) {
        return asyncTaskQueue.runTask(native2.captureBmp2, ref.int(args[0]), ref.string(args[1]));
    }

    if (args.length == 4) {
        return asyncTaskQueue.runTask(native2.captureBmp2, ref.int(args[0]), ref.int(args[1]), ref.int(args[2]), ref.int(args[3]),);
    }


    if (args.length == 5) {
        return asyncTaskQueue.runTask(native2.captureBmp2, ref.string(args[0]), ref.int(args[1]), ref.int(args[2]), ref.int(args[3]), ref.int(args[4]));
    }

    return Promise.resolve(null);
};


/**
 * 截图主屏幕为bmp缓冲区 [同步]
 */
export function captureBmp2Sync(): Buffer | null;
/**
 * 截图窗口句柄区域为bmp缓冲区  [同步]
 * @param handle 句柄
 */
export function captureBmp2Sync(handle: number | HWND): Buffer | null;
/**
 * 截图主屏幕到文件中 [同步]
 * @param path 文件路径
 */
export function captureBmp2Sync(path: string): boolean;
/**
 * 截图窗口句柄区域为文件 [同步]
 * ? 不会提前将窗口前置 因此会包含其他信息
 * @param handle 句柄
 * @param path 文件路径
 */
export function captureBmp2Sync(handle: number | HWND, path: string): boolean;
/**
 * 截图主屏幕为bmp缓冲区 [同步]
 * @param x (x) 从屏幕左边到所在位置得像素数
 * @param y (y) 从屏幕顶部边到所在位置得像素数
 * @param nScopeWidth 要求宽度
 * @param nScopeHeight 要求高度
 */
export function captureBmp2Sync(x: number, y: number, nScopeWidth: number, nScopeHeight: number): Buffer | null;
/**
 * 截图主屏幕为bmp文件 [同步]
 * @param x (x) 从屏幕左边到所在位置得像素数
 * @param y (y) 从屏幕顶部边到所在位置得像素数
 * @param nScopeWidth 要求宽度
 * @param nScopeHeight 要求高度
 */
export function captureBmp2Sync(path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): boolean;

export function captureBmp2Sync(...args: unknown[]): unknown {

    if (!native2.captureBmp2Sync) return null;
    if (!args.length) {
        return native2.captureBmp2Sync();
    }

    if (args.length == 1) {
        //  captureBmp2(handle: number|HWND): Promise<Buffer | null>;
        if (typeof args[0] == "number" || typeof args[0] == "object") {
            return native2.captureBmp2Sync(ref.int(args[0]));
        }
        return native2.captureBmp2Sync(ref.string(args[0]));
    }


    if (args.length == 2) {
        return native2.captureBmp2Sync(ref.int(args[0]), ref.string(args[1]));
    }

    if (args.length == 4) {
        return native2.captureBmp2Sync(ref.int(args[0]), ref.int(args[1]), ref.int(args[2]), ref.int(args[3]),);
    }


    if (args.length == 5) {
        return native2.captureBmp2Sync(ref.string(args[0]), ref.int(args[1]), ref.int(args[2]), ref.int(args[3]), ref.int(args[4]));
    }

    return null;
};
