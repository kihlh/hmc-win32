import main = require("./index");
import { ref } from "./util";


export enum HMC_PROMISEEVAL_TASK_TYPE {
    getClipboardFilePaths2 = 1,
    captureBmp2 = 2,
    closeWindow2 = 3,
    getClipboardText2 = 5,
    getThumbnailPng2 = 6,
    getTrayList2 = 7,
};

export type HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME = keyof typeof HMC_PROMISEEVAL_TASK_TYPE;

class HMC_PromiseeEvalTask {
    async: Partial<Record<HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => Promise<any>>> = {};
    sync: Partial<Record<HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => any>> = {};
    constructor() {

        const TASK_TYPE_LIST = Object.keys(HMC_PROMISEEVAL_TASK_TYPE) as Array<HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME>;

        for (let index = 0; index < TASK_TYPE_LIST.length; index++) {
            const TASK_TYPE: HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME = TASK_TYPE_LIST[index];
            const TASK_ID = HMC_PROMISEEVAL_TASK_TYPE[TASK_TYPE];

            this.async[TASK_TYPE] = (...arg: any[]) => {
                try {

                    if (!main.Native.native?.HMC_PromiseEval) {
                        return Promise.reject(main.HMC2_MODE.HMCNotPlatform);
                    }

                    if (arg.length >= 1) {
                        return main.Native.native.HMC_PromiseEval(TASK_ID, ...arg);
                    }

                    return main.Native.native.HMC_PromiseEval(TASK_ID);

                } catch (error) {
                    return Promise.reject(error);
                }
            }

            this.sync[TASK_TYPE] = (...arg: any[]) => {
                if (!main.Native.native?.HMC_PromiseEvalSync) {
                    return null;
                }
                if (arg.length >= 1) {
                    return main.Native.native.HMC_PromiseEvalSync(TASK_ID, ...arg) || null;
                }

                return main.Native.native.HMC_PromiseEvalSync(TASK_ID);
            }

            if (!this[TASK_TYPE]) {

                this[TASK_TYPE] = this.async[TASK_TYPE];
            }

            const KEY: `${HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME}Sync` = `${TASK_TYPE}Sync`;
            if (!this[KEY]) {
                this[KEY] = this.sync[TASK_TYPE];
            }

        }
    }

    async getClipboardFilePaths2() {

        if (!promiseEvalTask?.async?.getClipboardFilePaths2) {
            return Promise.resolve([]);
        }

        const data: string | string[] | null = await (promiseEvalTask?.async?.getClipboardFilePaths2() || null);

        if (typeof data == "string") {
            const temp = data ? (data as string)?.split('\0') : [];
            if (temp.length && temp.at(-1) == "") temp.pop();
            return temp;
        }

        return data || [];
    }

    getClipboardFilePaths2Sync() {
        if (!promiseEvalTask?.sync?.getClipboardFilePaths2) {
            return [];
        }

        const data: string | string[] | null = (promiseEvalTask?.sync?.getClipboardFilePaths2() || null);

        if (typeof data == "string") {
            const temp = data ? (data as string)?.split('\0') : [];
            if (temp.length && temp.at(-1) == "") temp.pop();
            return temp;
        }

        return data || [];
    }

    async getTrayList2(): Promise<Array<main.HMC2_MODE.TRAY_ICON>> {
        if (!promiseEvalTask?.async?.getTrayList2) {
            return Promise.resolve([]);
        }

        let data: string | Array<main.HMC2_MODE.TRAY_ICON> = await (promiseEvalTask?.async?.getTrayList2() || null);

        if (typeof data == "string") {
            return ref.JSONP(data) as Array<main.HMC2_MODE.TRAY_ICON> || [];
        }

        return [];
    }

    getTrayList2Sync(): Array<main.HMC2_MODE.TRAY_ICON> {
        if (!promiseEvalTask?.sync?.getTrayList2) {
            return [];
        }

        let data: string | Array<main.HMC2_MODE.TRAY_ICON> = (promiseEvalTask?.sync?.getTrayList2() || null);

        if (typeof data == "string") {
            return ref.JSONP(data) as Array<main.HMC2_MODE.TRAY_ICON> || [];
        }

        return data || [];
    }

}

interface HMC_PromiseeEvalTask {

    /**
     * 获取剪贴板的文件列表
     */
    getClipboardFilePaths2(): Promise<string[]>;

    /**
     * 获取剪贴板的文件列表
     */
    getClipboardFilePaths2Sync(): string[];
    /**
    * 截图指定窗口
    * @param handle 句柄
    */
    captureBmp2(handle: number): Promise<Buffer | null>;
    /**
     * 截图指定窗口并保存为文件
     * @param handle 句柄
     * @param path 文件路径
     */
    captureBmp2(handle: number, path: string): Promise<boolean>;
    /**
     * 截图指定窗口并保存为文件
     * @param path 文件路径
     * @param handle 句柄
     */
    captureBmp2(path: string, handle: number): Promise<boolean>;
    /**
     * 截图整个屏幕到文件
     * @param path 文件路径
     */
    captureBmp2(path: string): Promise<boolean>;
    /**
     * 截图整个屏幕到Buffer
     */
    captureBmp2(): Promise<Buffer | null>;
    /**
     * 从指定坐标开始截图并返回为Buffer
     * @param x 左边开始的坐标 `left`
     * @param y 顶部坐标 `top`
     * @param nScopeWidth 宽度
     * @param nScopeHeight 高度
     */
    captureBmp2(x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<Buffer | null>;
    /**
     * 截图整个屏幕到文件
     * @param path 文件路径
     * @param x 左边开始的坐标 `left`
     * @param y 顶部坐标 `top`
     * @param nScopeWidth 宽度
     * @param nScopeHeight 高度
     */
    captureBmp2(path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<boolean>;
    /**
     * 截图整个屏幕到文件
     * @param x 左边开始的坐标 `left`
     * @param y 顶部坐标 `top`
     * @param nScopeWidth 宽度
     * @param nScopeHeight 高度
     * @param path 文件路径
     */
    captureBmp2(x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): Promise<boolean>;
    /**
     * 截图指定窗口
     * @param handle 句柄
     */
    captureBmp2Sync(handle: number): Buffer | null;
    /**
     * 截图指定窗口并保存为文件
     * @param handle 句柄
     * @param path 文件路径
     */
    captureBmp2Sync(handle: number, path: string): boolean;
    /**
     * 截图指定窗口并保存为文件
     * @param path 文件路径
     * @param handle 句柄
     */
    captureBmp2Sync(path: string, handle: number): boolean;
    /**
     * 截图整个屏幕到文件
     * @param path 文件路径
     */
    captureBmp2Sync(path: string): boolean;
    /**
     * 截图整个屏幕到Buffer
     */
    captureBmp2Sync(): Buffer | null;
    /**
     * 从指定坐标开始截图并返回为Buffer
     * @param x 左边开始的坐标 `left`
     * @param y 顶部坐标 `top`
     * @param nScopeWidth 宽度
     * @param nScopeHeight 高度
     */
    captureBmp2Sync(x: number, y: number, nScopeWidth: number, nScopeHeight: number): Buffer | null;
    /**
     * 截图整个屏幕到文件
     * @param path 文件路径
     * @param x 左边开始的坐标 `left`
     * @param y 顶部坐标 `top`
     * @param nScopeWidth 宽度
     * @param nScopeHeight 高度
     */
    captureBmp2Sync(path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): boolean;
    /**
     * 截图整个屏幕到文件
     * @param x 左边开始的坐标 `left`
     * @param y 顶部坐标 `top`
     * @param nScopeWidth 宽度
     * @param nScopeHeight 高度
     * @param path 文件路径
     */
    captureBmp2Sync(x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): boolean;

    /**
    * 关闭窗口 异步
    * @param handle 句柄 
    * @param grade 等级
    * - 1 关闭 / 非强制
    * - 2 关闭 / 系统级(半强制)
    * - 3 关闭线程 (强制)
    * - 5 尝试所有办法直到关闭 (默认)
    */
    closeWindow2(handle: number, grade?: 1 | 2 | 3 | 5): Promise<boolean>;

    /**
     * 关闭窗口 同步
     * @param handle 句柄 
     * @param grade 等级
     * - 1 关闭 / 非强制
     * - 2 关闭 / 系统级(半强制)
     * - 3 关闭线程 (强制)
     * - 5 尝试所有办法直到关闭 (默认)
     */
    closeWindow2Sync(handle: number, grade?: 1 | 2 | 3 | 5): boolean;

    /**
     * 获取剪贴板文本 `async` 
     */
    getClipboardText2(): Promise<string | null>;

    /**
     * 获取剪贴板文本 `sync` 
     */
    getClipboardText2Sync(): string | null;

    /**
     * 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
     * @param filePath 被获取路径
     * @param output 输出路径
     * @param img_size 图片大小 推荐: `16` `64` `128` `256`
     * @default 256
     */
    getThumbnailPng2(filePath: string, output: string, img_size: number): Promise<boolean | null>;
    /**
    * 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
    * @param filePath 被获取路径
    * @param output 输出路径
    * @default 256
    */
    getThumbnailPng2(filePath: string, output: string): Promise<boolean | null>;
    /**
     * 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
     * @param filePath 被获取路径
     * @param img_size 图片大小 推荐: `16` `64` `128` `256`
     * @default 256
     */
    getThumbnailPng2(filePath: string, img_size: number): Promise<Buffer | null>;
    /**
     * 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
     * @param filePath 被获取路径
     * @param img_size 图片大小 `256`
     */
    getThumbnailPng2(filePath: string): Promise<Buffer | null>;
    /**
     * 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
     * @param filePath 被获取路径
     * @param output 输出路径
     * @param img_size 图片大小 推荐: `16` `64` `128` `256`
     * @default 256
     */
    getThumbnailPng2(filePath: string, output?: string, img_size?: number): Promise<unknown>;

    /**
     * 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
     * @param filePath 被获取路径
     * @param output 输出路径
     * @param img_size 图片大小 推荐: `16` `64` `128` `256`
     * @default 256
     */
    getThumbnailPng2Sync(filePath: string, output: string, img_size: number): boolean | null;
    /**
    * 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
    * @param filePath 被获取路径
    * @param output 输出路径
    * @default 256
    */
    getThumbnailPng2Sync(filePath: string, output: string): boolean | null;
    /**
     * 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
     * @param filePath 被获取路径
     * @param img_size 图片大小 推荐: `16` `64` `128` `256`
     * @default 256
     */
    getThumbnailPng2Sync(filePath: string, img_size: number): Buffer | null;
    /**
     * 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
     * @param filePath 被获取路径
     * @param img_size 图片大小 `256`
     */
    getThumbnailPng2Sync(filePath: string): Buffer | null;
    /**
     * 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
     * @param filePath 被获取路径
     * @param output 输出路径
     * @param img_size 图片大小 推荐: `16` `64` `128` `256`
     * @default 256
     */
    getThumbnailPng2Sync(filePath: string, output?: string, img_size?: number): unknown;

}

export const promiseEvalTask = new HMC_PromiseeEvalTask();

