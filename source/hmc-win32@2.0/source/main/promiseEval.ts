import main = require("./index");

const HMC2 = main.native;


export enum HMC_PROMISEEVAL_TASK_TYPE {
    getClipboardFilePaths2 = 1,
    captureBmp2 = 2,
    closeWindow2 = 3,
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

                    if (!HMC2.native?.HMC_PromiseEval) {
                        return Promise.reject(main.HMC2.HMCNotPlatform);
                    }

                    if (arg.length >= 1) {
                        return HMC2.native.HMC_PromiseEval(TASK_ID, ...arg);
                    }

                    return HMC2.native.HMC_PromiseEval(TASK_ID);

                } catch (error) {
                    return Promise.reject(error);
                }
            }

            this.sync[TASK_TYPE] = (...arg: any[]) => {
                if (!HMC2.native?.HMC_PromiseEvalSync) {
                    return null;
                }
                if (arg.length >= 1) {
                    return HMC2.native.HMC_PromiseEvalSync(TASK_ID, ...arg) || null;
                }

                return HMC2.native.HMC_PromiseEvalSync(TASK_ID);
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

        if (!promisee?.async?.getClipboardFilePaths2) {
            return Promise.resolve([]);
        }

        const data: string | string[] | null = await (promisee?.async?.getClipboardFilePaths2() || null);

        if (typeof data == "string") {
            return data ? (data as string)?.split('\0') : [];
        }

        return data || [];
    }

    getClipboardFilePaths2Sync() {
        if (!promisee?.sync?.getClipboardFilePaths2) {
            return [];
        }

        const data: string | string[] | null = (promisee?.sync?.getClipboardFilePaths2() || null);

        if (typeof data == "string") {
            return data ? (data as string)?.split('\0') : [];
        }

        return data || [];
    }


}

export module CaptureBmp {
    export interface CaptureBmp {
        (handle: number): Promise<Buffer | null>;
        (handle: number, path: string): Promise<boolean>;
        (path: string, handle: number): Promise<boolean>;
        (path: string): Promise<boolean>;
        (): Promise<Buffer | null>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<Buffer | null>;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<boolean>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): Promise<boolean>;
    }

    export interface CaptureBmpSync {
        (handle: number): Buffer | null;
        (handle: number, path: string): boolean;
        (path: string, handle: number): boolean;
        (path: string): boolean;
        (): Buffer | null;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Buffer | null;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): boolean;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): boolean;
    }

};

interface HMC_PromiseeEvalTask {
    /**
     * 获取剪贴板的文件列表
     */
    getClipboardFilePaths2(): Promise<string[]>;
    /**
     * 获取剪贴板的文件列表
     */
    getClipboardFilePaths2Sync(): string[];
    // 截图
    captureBmp2: CaptureBmp.CaptureBmp;
    // 截图
    captureBmp2Sync: CaptureBmp.CaptureBmpSync;
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

export const promisee = new HMC_PromiseeEvalTask();

