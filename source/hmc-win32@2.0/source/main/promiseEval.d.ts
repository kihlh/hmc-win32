/// <reference types="node" />
export declare enum HMC_PROMISEEVAL_TASK_TYPE {
    getClipboardFilePaths2 = 1,
    captureBmp2 = 2,
    closeWindow2 = 3,
    getClipboardText2 = 5,
    getThumbnailPng2 = 6
}
export type HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME = keyof typeof HMC_PROMISEEVAL_TASK_TYPE;
declare class HMC_PromiseeEvalTask {
    async: Partial<Record<HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => Promise<any>>>;
    sync: Partial<Record<HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => any>>;
    constructor();
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
export declare const promiseEvalTask: HMC_PromiseeEvalTask;
export {};
