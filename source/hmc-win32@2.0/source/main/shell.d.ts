/// <reference types="node" />
import main = require("./index");
declare class StartupConstructor {
    #private;
    constructor();
    has(keyName: string): boolean;
    hasOnce(keyName: string): boolean;
    remove(keyName: string): boolean;
    removeOnce(keyName: string): boolean;
    set(keyName: string, path: string, cmd?: string): boolean;
    setOnce(keyName: string, path: string, cmd?: string): boolean;
    enum(): {
        [key: string]: string;
    };
    enumOnce(): {
        [key: string]: string;
    };
    keys(): never[];
    keysOnce(): never[];
}
export declare module Shell {
    /**
     * 启动项 管理
     */
    const Startup: StartupConstructor;
    /**
     * 截图为Bmp 文件/Buffer
     */
    const captureBmp2: {
        (handle: number): Promise<Buffer | null>;
        (handle: number, path: string): Promise<boolean>;
        (path: string, handle: number): Promise<boolean>;
        (path: string): Promise<boolean>;
        (): Promise<Buffer | null>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<Buffer | null>;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): Promise<boolean>;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): Promise<boolean>;
    };
    /**
    * 截图为Bmp 文件/Buffer
    */
    const captureBmp2Sync: {
        (handle: number): Buffer | null;
        (handle: number, path: string): boolean;
        (path: string, handle: number): boolean;
        (path: string): boolean;
        (): Buffer | null;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number): Buffer | null;
        (path: string, x: number, y: number, nScopeWidth: number, nScopeHeight: number): boolean;
        (x: number, y: number, nScopeWidth: number, nScopeHeight: number, path: string): boolean;
    };
    const getThumbnailPng2: {
        (filePath: string, output: string, img_size: number): Promise<boolean | null>;
        (filePath: string, output: string): Promise<boolean | null>;
        (filePath: string, img_size: number): Promise<Buffer | null>;
        (filePath: string): Promise<Buffer | null>;
        (filePath: string, output?: string | undefined, img_size?: number | undefined): Promise<unknown>;
    };
    const getThumbnailPng2Sync: {
        (filePath: string, output: string, img_size: number): boolean | null;
        (filePath: string, output: string): boolean | null;
        (filePath: string, img_size: number): Buffer | null;
        (filePath: string): Buffer | null;
        (filePath: string, output?: string | undefined, img_size?: number | undefined): unknown;
    };
    const getFileIcon2: {
        (filePath: string, output: string, img_size: number): Promise<boolean | null>;
        (filePath: string, output: string): Promise<boolean | null>;
        (filePath: string, img_size: number): Promise<Buffer | null>;
        (filePath: string): Promise<Buffer | null>;
        (filePath: string, output?: string | undefined, img_size?: number | undefined): Promise<unknown>;
    };
    const getFileIcon2Sync: {
        (filePath: string, output: string, img_size: number): boolean | null;
        (filePath: string, output: string): boolean | null;
        (filePath: string, img_size: number): Buffer | null;
        (filePath: string): Buffer | null;
        (filePath: string, output?: string | undefined, img_size?: number | undefined): unknown;
    };
    /**
     * 弹出右键菜单的接口
     * @param hwnd 调用窗口 / 允许为null
     * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
     * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
     * @param y 坐标
     */
    function showContextMenu(hwnd?: number | null, file?: string | string[], x?: number, y?: number): boolean;
    /**
     * 获取托盘图标列表
     * 1.4.6 起返回json文本
     * ? win11 在22621.1000版本之后失效 具体原因查看https://github.com/kihlh/hmc-win32/issues/36
     */
    function getTrayList(): Array<main.HMC2_MODE.TRAY_ICON>;
    /**
     * 设置文件夹的缩略图
     * @param folderPath 路径
     * @param iconPath 图标路径
     * @param iconIndex 图标索引 比如exe中的0
     * @returns
     */
    function setFolderIcon(folderPath: string, iconPath: string, iconIndex?: number): boolean;
}
export {};
