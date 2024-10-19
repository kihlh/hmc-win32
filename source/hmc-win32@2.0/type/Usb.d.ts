import main = require("./index");
export declare namespace Usb {
    type Volume = main.HMC2_MODE.Volume;
    /**
     * 格式化 Volume路径
     * @example
     * - volumeid -> "\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\123456\\1234"
     * - nt -> "\\Device\\HarddiskVolume2"
     * @param Path 路径
     * @returns
     */
    function formatVolumePath2(Path: string): Promise<string>;
    /**
     * 格式化 Volume路径
     * @example
     * - volumeid -> "\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\123456\\1234"
     * - nt -> "\\Device\\HarddiskVolume2"
     * @param Path 路径
     * @returns
     */
    function formatVolumePath2Sync(Path: string): string;
    /**
     * 格式化 Volume路径
     * @example "\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\123456\\1234"
     * @param Path 路径
     * @returns
     */
    function formatVolumeName2(Path: string): Promise<string | null>;
    /**
     * 格式化 Volume路径
     * @example "\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\123456\\1234"
     * @param Path 路径
     * @returns
     */
    function formatVolumeName2Sync(Path: string): string | null;
    /**
     * 格式化 Nt路径
     * @example "\\Device\\HarddiskVolume2"
     * @param Path 路径
     * @returns
     */
    function formatVolumeNtName2(Path: string): Promise<string | null>;
    /**
     * 格式化 Nt路径
     * @example "\\Device\\HarddiskVolume2"
     * @param Path 路径
     * @returns
     */
    function formatVolumeNtName2Sync(Path: string): string | null;
    /**
     * 枚举指定匹配磁盘的Volume信息
     * @param search 匹配信息 正则/文本 如:
     * - {68de5ae6-0000-0000-0000-100000000000}
     * - D:
     * - HarddiskVolume2
     */
    function getVolumeList2(search: string | RegExp): Promise<Volume | null>;
    /**
     * 枚举所有的磁盘的Volume信息
     * @returns
     */
    function getVolumeList2(): Promise<Volume[]>;
    /**
     * 枚举指定匹配磁盘的Volume信息
     * @param search 匹配信息 正则/文本 如:
     * - {68de5ae6-0000-0000-0000-100000000000}
     * - D:
     * - HarddiskVolume2
     */
    function getVolumeList2Sync(search: string | RegExp): Volume | null;
    /**
     * 枚举所有的磁盘的Volume信息
     * @returns
     */
    function getVolumeList2Sync(): Volume[];
}
