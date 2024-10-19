import { isRegExp } from "util/types";
import { ref } from "./util";
import { ShellPromiseEval } from "./ShellPromiseEval";
import { HMC } from "./HMC";


export namespace Usb {

    export type Volume = HMC.Volume;

    /**
     * 格式化 Volume路径
     * @example 
     * - volumeid -> "\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\123456\\1234"
     * - nt -> "\\Device\\HarddiskVolume2"
     * @param Path 路径
     * @returns 
     */
    export async function formatVolumePath2(Path: string) {
        return (await ShellPromiseEval.formatVolumePath2(ref.string(Path))) || "";
    }

    /**
     * 格式化 Volume路径
     * @example 
     * - volumeid -> "\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\123456\\1234"
     * - nt -> "\\Device\\HarddiskVolume2"
     * @param Path 路径
     * @returns 
     */
    export function formatVolumePath2Sync(Path: string) {
        return (ShellPromiseEval.formatVolumePath2Sync(ref.string(Path))) || "";
    }

    /**
     * 格式化 Volume路径
     * @example "\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\123456\\1234"
     * @param Path 路径
     * @returns 
     */
    export function formatVolumeName2(Path: string) {
        return ShellPromiseEval.formatVolumeName2(Path)
    }

    /**
     * 格式化 Volume路径
     * @example "\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\123456\\1234"
     * @param Path 路径
     * @returns 
     */
    export function formatVolumeName2Sync(Path: string) {
        return ShellPromiseEval.formatVolumeName2Sync(Path)
    }

    /**
     * 格式化 Nt路径
     * @example "\\Device\\HarddiskVolume2"
     * @param Path 路径
     * @returns 
     */
    export function formatVolumeNtName2(Path: string) {
        return ShellPromiseEval.formatVolumeNtName2(Path)
    }

    /**
     * 格式化 Nt路径
     * @example "\\Device\\HarddiskVolume2"
     * @param Path 路径
     * @returns 
     */
    export function formatVolumeNtName2Sync(Path: string) {
        return ShellPromiseEval.formatVolumeNtName2Sync(Path)
    }

    /**
     * 枚举指定匹配磁盘的Volume信息
     * @param search 匹配信息 正则/文本 如:
     * - {68de5ae6-0000-0000-0000-100000000000}
     * - D:
     * - HarddiskVolume2
     */
    export function getVolumeList2(search: string | RegExp): Promise<Volume | null>;
    /**
     * 枚举所有的磁盘的Volume信息
     * @returns
     */
    export function getVolumeList2(): Promise<Volume[]>;
    export function getVolumeList2(search?: unknown): unknown {
        return new Promise<Volume[] | Volume | null>(async (resolve, reject) => {
            try {
                const VolumeList: Volume[] | null | undefined = await ShellPromiseEval.getVolumeList2();
                if ((typeof search == "string" || isRegExp(search)) && VolumeList) {
                    for (let index = 0; index < VolumeList.length; index++) {
                        const element: HMC.Volume = VolumeList[index];
                        if (element.path) {
                            const match = element.path.match(search) || element.device.match(search) || element.name.match(search);
                            if (match) {
                                resolve(element);
                                return;
                            }
                        }
                    }

                    resolve(null);
                    return;
                }

                resolve(VolumeList || []);
            } catch (error) {
                reject(error);
            }
        });
    }

    /**
     * 枚举指定匹配磁盘的Volume信息
     * @param search 匹配信息 正则/文本 如:
     * - {68de5ae6-0000-0000-0000-100000000000}
     * - D:
     * - HarddiskVolume2
     */
    export function getVolumeList2Sync(search: string | RegExp): Volume | null;
    /**
     * 枚举所有的磁盘的Volume信息
     * @returns
     */
    export function getVolumeList2Sync(): Volume[];
    export function getVolumeList2Sync(search?: unknown): unknown {
        const VolumeList: Volume[] | null | undefined = ShellPromiseEval.getVolumeList2Sync();
        if ((typeof search == "string" || isRegExp(search)) && VolumeList) {
            for (let index = 0; index < VolumeList.length; index++) {
                const element: HMC.Volume = VolumeList[index];
                if (element.path) {
                    const match = element.path.match(search) || element.device.match(search) || element.name.match(search);
                    if (match) {
                        return element;
                    }
                }
            }
            return null;
        }

        return VolumeList || [];
    }

}
