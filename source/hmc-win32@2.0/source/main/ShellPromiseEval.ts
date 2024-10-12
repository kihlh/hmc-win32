import fs from "fs";
import main = require("./index");
import { ref } from "./util";

export enum HMC_PROMISEEVAL_TASK_TYPE {
    getLinkTarget2 = 1,
    getFileAttributes2 = 2,

    getVolumeList2 = 3,
    formatVolumePath2 = 5,
    formatVolumeName2 = 6,
    formatVolumeNtName2 = 7,

    getLinkPath2 = 8,
    hasFileSymbolicLink2 = 9,
    hasFileHardLink2 = 10,
    hasDirSymbolicLink2 = 12,
    hasDirJunctionPoint2 = 13,
    getLinkType2 = 15,

    createLink = 16,
    createDirJunctionPoint2 = 17,
    createHardLink2 = 18,
    createSymlink2 = 19,
    createDirSymlink2 = 20,

    setFolderIcon2 = 21,
    setExtensionIcon2 = 22,
    setAppURLProtocol2 = 23,
    getShortcutLink = 25,

};

export type HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME = keyof typeof HMC_PROMISEEVAL_TASK_TYPE;
export type LINK_TYPE = main.HMC2_MODE.LINK_TYPE;

class HMC_PromiseeEvalTask {
    async: Partial<Record<HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => Promise<any>>> = {};
    sync: Partial<Record<HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME, (...arg: any[]) => any>> = {};
    constructor() {

        const TASK_TYPE_LIST = Object.keys(HMC_PROMISEEVAL_TASK_TYPE) as Array<HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME>;
        const _this = this;

        for (let index = 0; index < TASK_TYPE_LIST.length; index++) {
            const TASK_TYPE: HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME = TASK_TYPE_LIST[index];
            if (!TASK_TYPE || TASK_TYPE?.match(/^\d+/)) continue;

            const TASK_ID = HMC_PROMISEEVAL_TASK_TYPE[TASK_TYPE];

            _this.async[TASK_TYPE] = (...arg: any[]) => {
                try {

                    if (!main.Native.native?.HMC_GetShellEnvInfo) {
                        return Promise.reject(main.HMC2_MODE.HMCNotPlatform);
                    }

                    if (arg.length >= 1) {
                        return main.Native.native.HMC_GetShellEnvInfo(TASK_ID, ...arg);
                    }

                    return main.Native.native.HMC_GetShellEnvInfo(TASK_ID);

                } catch (error) {
                    return Promise.reject(error);
                }
            }

            _this.sync[TASK_TYPE] = (...arg: any[]) => {
                if (!main.Native.native?.HMC_GetShellEnvInfoSync) {
                    return null;
                }
                if (arg.length >= 1) {
                    return main.Native.native.HMC_GetShellEnvInfoSync(TASK_ID, ...arg) || null;
                }

                return main.Native.native.HMC_GetShellEnvInfoSync(TASK_ID);
            }

            if (!_this[TASK_TYPE]) {

                _this[TASK_TYPE] = _this.async[TASK_TYPE];
            }

            const KEY: `${HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME}Sync` = `${TASK_TYPE}Sync`;

            if (!_this[KEY]) {

                _this[KEY] = _this.sync[TASK_TYPE];
            }

        }
    }

    async getLinkTarget2(targetPath: string): Promise<main.HMC2_MODE.LINK_TARGET | null> {
        if (!promiseEvalTask.async.getLinkTarget2) {
            return Promise.resolve(null);
        }
        return await promiseEvalTask.async.getLinkTarget2(targetPath).then(data => {

            if (typeof data == "string") {

                data = ref.JSONP(data);
                if (data?.type == "HARD_LINK_FILE" && data?.volume) {
                    data.volume = ref.JSONP(data.volume);
                }
            }
            return data || null;
        });
    }

    getLinkTarget2Sync(targetPath: string): main.HMC2_MODE.LINK_TARGET | null {
        if (!promiseEvalTask.sync.getLinkTarget2) {
            return null;
        }

        let data = promiseEvalTask.sync.getLinkTarget2(targetPath);

        if (typeof data == "string") {

            data = ref.JSONP(data);
            if (data?.type == "HARD_LINK_FILE" && data?.volume) {
                data.volume = ref.JSONP(data.volume);
            }
        }

        return data || null;
    }

    async getFileAttributes2(targetPath: string): Promise<null | main.HMC2_MODE.FileAttributesStat> {
        if (!promiseEvalTask.async.getFileAttributes2) {
            return null;
        }

        let data = await promiseEvalTask.async.getFileAttributes2(targetPath);

        const attributes_list = typeof data == "string" ? ref.JSONP(data) : data as number[] | null;
        if (attributes_list?.length) {
            return {
                "attributes": attributes_list[0],
                "list": attributes_list.length == 1 ? attributes_list : attributes_list.slice(1)
            } as main.HMC2_MODE.FileAttributesStat;
        }

        return null;
    }

    getFileAttributes2Sync(targetPath: string): null | main.HMC2_MODE.FileAttributesStat {
        if (!promiseEvalTask.sync.getFileAttributes2) {
            return null;
        }

        let data = promiseEvalTask.sync.getFileAttributes2(targetPath);

        const attributes_list = typeof data == "string" ? ref.JSONP(data) : data as number[] | null;
        if (attributes_list?.length) {
            return {
                "attributes": attributes_list[0],
                "list": attributes_list.length == 1 ? attributes_list : attributes_list.slice(1)
            } as main.HMC2_MODE.FileAttributesStat;
        }

        return null;
    }

    async getVolumeList2(): Promise<null | main.HMC2_MODE.Volume[]> {
        if (!promiseEvalTask.async.getVolumeList2) {
            return Promise.resolve(null);
        }
        return await promiseEvalTask.async.getVolumeList2().then(data => {

            if (typeof data == "string") {

                data = ref.JSONP(data);
            }

            return data || null;
        });
    }

    getVolumeList2Sync(): null | main.HMC2_MODE.Volume[] {
        if (!promiseEvalTask.sync.getVolumeList2) {
            return null;
        }

        let data = promiseEvalTask.sync.getVolumeList2();

        if (typeof data == "string") {

            data = ref.JSONP(data);

        }

        return data || null;
    }

}

interface HMC_PromiseeEvalTask {

    formatVolumePath2(Path2: string): Promise<null | string>;
    formatVolumePath2Sync(Path2: string): null | string;
    formatVolumeName2(Path2: string): Promise<null | string>;
    formatVolumeName2Sync(Path2: string): null | string;
    formatVolumeNtName2(Path2: string): Promise<null | string>;
    formatVolumeNtName2Sync(Path2: string): null | string;

    getLinkType2(targetPath: string): Promise<main.HMC2_MODE.LINK_TYPE_EQ | null>;
    getLinkType2Sync(targetPath: string): main.HMC2_MODE.LINK_TYPE_EQ | null;

    /**
     * 获取 软链接/ 硬链接 指向的路径
     * @param targetPath 
     */
    getLinkPath2(targetPath: string): Promise<string | string[] | null>;
    /**
     * 获取 软链接/ 硬链接 指向的路径
     * @param targetPath 
     */
    getLinkPath2Sync(targetPath: string): string | string[] | null;
    /**
     * 判断是否是符号链接
     * @example 适用 -> [文件]符号连接
     * @example 适用 -> [文件夹]符号连接
     * @example 适用 -> [文件夹]文件夹符号链接
     * @param targetPath 
     */
    hasFileSymbolicLink2(targetPath: string): Promise<boolean>;
    /**
     * 判断是否是符号链接
     * @example 适用 -> [文件]符号连接
     * @example 适用 -> [文件夹]符号连接
     * @example 适用 -> [文件夹]文件夹符号链接
     * @param targetPath 
     */
    hasFileSymbolicLink2Sync(targetPath: string): boolean;
    /**
     * 判断是否是硬链接
     * @example 仅适用 -> [文件]硬链接
     * @param targetPath 
     */
    hasFileHardLink2(targetPath: string): Promise<boolean>;
    /**
     * 判断是否是硬链接
     * @example 仅适用 -> [文件]硬链接
     * @param targetPath 
     */
    hasFileHardLink2Sync(targetPath: string): boolean;
    /**
     * 判断是否是文件夹符号链接
     * @example 适用 -> [文件夹]符号连接
     * @param targetPath 
     */
    hasDirSymbolicLink2(targetPath: string): Promise<boolean>;
    /**
     * 判断是否是文件夹符号链接
     * @example 适用 -> [文件夹]符号连接
     * @param targetPath 
     */
    hasDirSymbolicLink2Sync(targetPath: string): boolean;
    /**
     * 判断是否是 文件夹链接连接点
     * @example 仅适用 -> [文件夹]文件夹连接点
     * @param targetPath 
     */
    hasDirJunctionPoint2(targetPath: string): Promise<boolean>;
    /**
     * 判断是否是 文件夹链接连接点
     * @example 仅适用 -> [文件夹]文件夹连接点
     * @param targetPath 
     */
    hasDirJunctionPoint2Sync(targetPath: string): boolean;

    createLink(targetType: main.HMC2_MODE.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string): Promise<boolean>;
    createLinkSync(targetType: main.HMC2_MODE.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string): boolean;

    createDirJunctionPoint2(targetPath: string, sourcePath: string): Promise<boolean>;
    createDirJunctionPoint2Sync(targetPath: string, sourcePath: string): boolean;
    createHardLink2(targetPath: string, sourcePath: string): Promise<boolean>;
    createHardLink2Sync(targetPath: string, sourcePath: string): boolean;
    createSymlink2(targetPath: string, sourcePath: string): Promise<boolean>;
    createSymlink2Sync(targetPath: string, sourcePath: string): boolean;
    createDirSymlink2(targetPath: string, sourcePath: string): Promise<boolean>;
    createDirSymlink2Sync(targetPath: string, sourcePath: string): boolean;
    setFolderIcon2(targetPath: string, iconPath: string, iconIndex: number): Promise<boolean>;
    setFolderIcon2Sync(targetPath: string, iconPath: string, iconIndex: number): boolean;
    setExtensionIcon2(extensionName: string, typeName: string, iconPath: string, iconIndex: number): Promise<boolean>;
    setExtensionIcon2Sync(extensionName: string, typeName: string, iconPath: string, iconIndex: number): boolean;
    setAppURLProtocol2(protocolName: string, appPath: string, command: string): Promise<boolean>;
    setAppURLProtocol2Sync(protocolName: string, appPath: string, command: string): boolean;

    getShortcutLink(targetPath: string, QueryDetaile?: boolean): Promise<main.HMC2_MODE.SHORTCUT_LINK | null>;
    getShortcutLinkSync(targetPath: string, QueryDetaile?: boolean): main.HMC2_MODE.SHORTCUT_LINK | null;

}

export const promiseEvalTask = new HMC_PromiseeEvalTask();

