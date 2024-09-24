/// <reference types="node" />
export declare let HMC_BETA: HMC_BETA;
interface HMC_BETA {
    /**
     * 执行进程环境获取 需要配合命令代码
     * @param pid 进程id
     * @param command 命令
     */
    HMC_PromiseEval(command: HMC_PROMISEEVAL_TASK_TYPE, ...arg: any[]): Promise<any>;
    /**
     * 执行进程环境获取 需要配合命令代码
     * @param pid 进程id
     * @param command 命令
     */
    HMC_PromiseEvalSync(command: HMC_PROMISEEVAL_TASK_TYPE, ...arg: any[]): any;
}
declare enum HMC_PROMISEEVAL_TASK_TYPE {
    getClipboardFilePaths2 = 1,
    captureBmp2 = 2,
    closeWindow2 = 3
}
type HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME = keyof typeof HMC_PROMISEEVAL_TASK_TYPE;
declare class HMC_PromiseeEvalTask {
    async: Partial<Record<HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => Promise<any>>>;
    sync: Partial<Record<HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => any>>;
    constructor();
}
export declare module HMCC {
    interface CaptureBmp {
        (handle: number): Promise<Buffer | null>;
        (handle: number, path: string): Promise<boolean>;
        (path: string, handle: number): Promise<boolean>;
        (path: string): Promise<boolean>;
        (): Promise<Buffer | null>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<Buffer | null>;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<boolean>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): Promise<boolean>;
    }
    interface CaptureBmpSync {
        (handle: number): Buffer | null;
        (handle: number, path: string): boolean;
        (path: string, handle: number): boolean;
        (path: string): boolean;
        (): Buffer | null;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Buffer | null;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): boolean;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): boolean;
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
    captureBmp2: HMCC.CaptureBmp;
    captureBmp2Sync: HMCC.CaptureBmpSync;
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
}
export declare const promisee: HMC_PromiseeEvalTask;
export {};
/**
 *

console.time("mode.HMC_BETA.getClipboardFilePaths");
let data = mode.HMC_BETA.getClipboardFilePaths()
data = data? (data)?.split('\0'):[];
console.log('size-> %d',data.length);
console.timeEnd("mode.HMC_BETA.getClipboardFilePaths");


console.time("mode.promisee.getClipboardFilePaths2Sync");
let data2 = getClipboardFilePaths2Sync();
console.log('size-> %d',data2.length);
console.timeEnd("mode.promisee.getClipboardFilePaths2Sync");


VM1006:4 size-> 23273
VM1006:5 mode.HMC_BETA.getClipboardFilePaths: 17136.48095703125 ms
node:internal/console/constructor:625 mode.HMC_BETA.getClipboardFilePaths: 17.137s


VM1006:10 size-> 23272
VM1006:11 mode.promisee.getClipboardFilePaths2Sync: 17776.4990234375 ms
node:internal/console/constructor:625 mode.promisee.getClipboardFilePaths2Sync: 17.777s


 */
