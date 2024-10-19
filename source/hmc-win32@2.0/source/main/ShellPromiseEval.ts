import { HMC } from "./HMC";
import { ref } from "./util";
import { Native } from "./Native";


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
    getShortcutLink2 = 25,
    trashFile2 = 26,
    clearTrash2 = 27,
    copyFile2 = 28,
    moveFile2 = 29,
    setShortcutLink2 = 30,

};

export type HMC_PROMISEEVAL_TASK_TYPE_ALL_NAME = keyof typeof HMC_PROMISEEVAL_TASK_TYPE;
export type LINK_TYPE = HMC.LINK_TYPE;

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

                    if (!Native.native?.HMC_GetShellEnvInfo) {
                        return Promise.reject(HMC.HMCNotPlatform);
                    }

                    if (arg.length >= 1) {
                        return Native.native.HMC_GetShellEnvInfo(TASK_ID, ...arg);
                    }

                    return Native.native.HMC_GetShellEnvInfo(TASK_ID);

                } catch (error) {
                    return Promise.reject(error);
                }
            }

            _this.sync[TASK_TYPE] = (...arg: any[]) => {
                if (!Native.native?.HMC_GetShellEnvInfoSync) {
                    return null;
                }
                if (arg.length >= 1) {
                    return Native.native.HMC_GetShellEnvInfoSync(TASK_ID, ...arg) || null;
                }

                return Native.native.HMC_GetShellEnvInfoSync(TASK_ID);
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

    async getLinkTarget2(targetPath: string): Promise<HMC.LINK_TARGET | null> {
        if (!ShellPromiseEval.async.getLinkTarget2) {
            return Promise.resolve(null);
        }
        return await ShellPromiseEval.async.getLinkTarget2(targetPath).then(data => {

            if (typeof data == "string") {

                data = ref.JSONP(data);
                if (data?.type == "HARD_LINK_FILE" && data?.volume) {
                    data.volume = ref.JSONP(data.volume);
                }
            }
            return data || null;
        });
    }

    getLinkTarget2Sync(targetPath: string): HMC.LINK_TARGET | null {
        if (!ShellPromiseEval.sync.getLinkTarget2) {
            return null;
        }

        let data = ShellPromiseEval.sync.getLinkTarget2(targetPath);

        if (typeof data == "string") {

            data = ref.JSONP(data);
            if (data?.type == "HARD_LINK_FILE" && data?.volume) {
                data.volume = ref.JSONP(data.volume);
            }
        }

        return data || null;
    }

    async getFileAttributes2(targetPath: string): Promise<null | HMC.FileAttributesStat> {
        if (!ShellPromiseEval.async.getFileAttributes2) {
            return null;
        }

        let data = await ShellPromiseEval.async.getFileAttributes2(targetPath);

        const attributes_list = typeof data == "string" ? ref.JSONP(data) : data as number[] | null;
        if (attributes_list?.length) {
            return {
                "attributes": attributes_list[0],
                "list": attributes_list.length == 1 ? attributes_list : attributes_list.slice(1)
            } as HMC.FileAttributesStat;
        }

        return null;
    }

    getFileAttributes2Sync(targetPath: string): null | HMC.FileAttributesStat {
        if (!ShellPromiseEval.sync.getFileAttributes2) {
            return null;
        }

        let data = ShellPromiseEval.sync.getFileAttributes2(targetPath);

        const attributes_list = typeof data == "string" ? ref.JSONP(data) : data as number[] | null;
        if (attributes_list?.length) {
            return {
                "attributes": attributes_list[0],
                "list": attributes_list.length == 1 ? attributes_list : attributes_list.slice(1)
            } as HMC.FileAttributesStat;
        }

        return null;
    }

    async getVolumeList2(): Promise<null | HMC.Volume[]> {
        if (!ShellPromiseEval.async.getVolumeList2) {
            return Promise.resolve(null);
        }
        return await ShellPromiseEval.async.getVolumeList2().then(data => {

            if (typeof data == "string") {

                data = ref.JSONP(data);
            }

            return data || null;
        });
    }

    getVolumeList2Sync(): null | HMC.Volume[] {
        if (!ShellPromiseEval.sync.getVolumeList2) {
            return null;
        }

        let data = ShellPromiseEval.sync.getVolumeList2();

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

    getLinkType2(targetPath: string): Promise<HMC.LINK_TYPE_EQ | null>;
    getLinkType2Sync(targetPath: string): HMC.LINK_TYPE_EQ | null;

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

    createLink(targetType: HMC.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string): Promise<boolean>;
    createLinkSync(targetType: HMC.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string): boolean;

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

    getShortcutLink2(targetPath: string, QueryDetaile?: boolean): Promise<HMC.SHORTCUT_LINK | null>;
    getShortcutLink2Sync(targetPath: string, QueryDetaile?: boolean): HMC.SHORTCUT_LINK | null;

    setShortcutLink2(targetPath: string, FilePath: string, work_dir: string, desc: string, args: string, iShowCmd: number, icon: string, iconIndex: number): Promise<boolean>;
    trashFile2(trash_path: string, is_Recycle: boolean, isShow: boolean): Promise<boolean>;
    clearTrash2(root_path: string, isShow: boolean): Promise<boolean>;
    copyFile2(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean): Promise<boolean>;
    moveFile2(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean): Promise<boolean>;

    setShortcutLink2Sync(targetPath: string, FilePath: string, work_dir: string, desc: string, args: string, iShowCmd: number, icon: string, iconIndex: number): boolean;
    trashFile2Sync(trash_path: string, is_Recycle: boolean, isShow: boolean): boolean;
    clearTrash2Sync(root_path: string, isShow: boolean): boolean;
    copyFile2Sync(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean): boolean;
    moveFile2Sync(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean): boolean;

}

export const ShellPromiseEval = new HMC_PromiseeEvalTask();
