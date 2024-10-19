import { HMC } from "./HMC";
import PromiseEval = require("./promiseEval");
import { Registr } from "./registr";
import { promiseEvalTask } from "./promiseEval";
import { ShellPromiseEval } from "./ShellPromiseEval";
import { Native } from "./Native";
import { ref } from "./util";

const REG_KEY_EM = {
    HKEY_LOCAL_MACHINE: "HKEY_LOCAL_MACHINE",
    pathRun: "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
    pathRunOnce: "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"
};

class StartupConstructor {

    constructor() { }

    has(keyName: string) {
        return Native.HMC_SHELL_STARTUP_CLASS?.has(ref.string(keyName)) || false;
    }

    hasOnce(keyName: string) {
        return Native.HMC_SHELL_STARTUP_CLASS?.hasOnce(ref.string(keyName)) || false;
    }

    remove(keyName: string) {
        return Native.HMC_SHELL_STARTUP_CLASS?.remove(ref.string(keyName)) || false;
    }

    removeOnce(keyName: string) {
        return Native.HMC_SHELL_STARTUP_CLASS?.removeOnce(ref.string(keyName)) || false;
    }

    set(keyName: string, path: string, cmd?: string) {
        return Native.HMC_SHELL_STARTUP_CLASS?.set(ref.string(keyName), ref.string(path), ref.string(cmd || "")) || false;
    }

    setOnce(keyName: string, path: string, cmd?: string) {
        return Native.HMC_SHELL_STARTUP_CLASS?.setOnce(ref.string(keyName), ref.string(path), ref.string(cmd || "")) || false;
    }


    async enum2() {
        const obj: { [key: string]: string | null } = {};
        const keys = await this.keys2();
        const { HKEY_LOCAL_MACHINE } = HMC.Hkey;

        for (let index = 0; index < keys.length; index++) {
            let at = keys[index];
            obj[at] = await Registr.getRegistrString2(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRun, at);
        }

        return obj;
    }

    enum2Sync() {
        const obj: { [key: string]: string | null } = {};
        const keys = this.keys2Sync();
        const { HKEY_LOCAL_MACHINE } = HMC.Hkey;

        for (let index = 0; index < keys.length; index++) {
            let at = keys[index];
            obj[at] = Registr.getRegistrString2Sync(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRun, at);
        }

        return obj;
    }

    async enumOnce2() {
        const obj: { [key: string]: string | null } = {};
        const keys = await this.keysOnce2();
        const { HKEY_LOCAL_MACHINE } = HMC.Hkey;

        for (let index = 0; index < keys.length; index++) {
            let at = keys[index];
            obj[at] = await Registr.getRegistrString2(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRunOnce, at);
        }

        return obj;
    }

    enumOnce2Sync() {
        const obj: { [key: string]: string | null } = {};
        const keys = this.keysOnce2Sync();
        const { HKEY_LOCAL_MACHINE } = HMC.Hkey;

        for (let index = 0; index < keys.length; index++) {
            let at = keys[index];
            obj[at] = Registr.getRegistrString2Sync(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRunOnce, at);
        }

        return obj;
    }

    async keys2() {
        // return [];
        const { HKEY_LOCAL_MACHINE } = HMC.Hkey;
        const key = Registr.getRegistrKeys2(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRun);
        return (await key)?.valueKeyList.map(_ => _.name) || [];
    }

    keys2Sync() {
        // return [];
        const { HKEY_LOCAL_MACHINE } = HMC.Hkey;
        const key = Registr.getRegistrKeys2Sync(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRun);
        return (key)?.valueKeyList.map(_ => _.name) || [];
    }

    async keysOnce2() {
        // return [];
        const { HKEY_LOCAL_MACHINE } = HMC.Hkey;
        const key = Registr.getRegistrKeys2(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRunOnce);
        return (await key)?.valueKeyList.map(_ => _.name) || [];
    }

    keysOnce2Sync() {
        // return [];
        const { HKEY_LOCAL_MACHINE } = HMC.Hkey;
        const key = Registr.getRegistrKeys2Sync(HKEY_LOCAL_MACHINE, REG_KEY_EM.pathRunOnce);
        return (key)?.valueKeyList.map(_ => _.name) || [];
    }

}

export namespace Shell {


    /**
     * 启动项 管理
     */
    export const Startup = new StartupConstructor();

    /**
        * 弹出右键菜单的接口
        * @param hwnd 调用窗口 / 允许为null
        * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
        * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
        * @param y 坐标
        */
    export function showContextMenu(hwnd?: number | null, file?: string | string[], x?: number, y?: number) {
        return Native.HMC_SHELL_CLASS?.showContextMenu ?
            Native.HMC_SHELL_CLASS?.showContextMenu(
                ref.int(hwnd || 0),
                Array.isArray(file) ? file : ref.string(file),
                ref.int(x || 0),
                ref.int(y || 0)
            )
            : false;
    }

    /**
     * 获取托盘图标列表
     * 1.4.6 起返回json文本
     * ? win11 在22621.1000版本之后失效 具体原因查看https://github.com/kihlh/hmc-win32/issues/36
     */
    export function getTrayList2() {
        return promiseEvalTask.getTrayList2();
    }

    /**
     * 获取托盘图标列表
     * 1.4.6 起返回json文本
     * ? win11 在22621.1000版本之后失效 具体原因查看https://github.com/kihlh/hmc-win32/issues/36
     */
    export function getTrayList2Sync() {
        return promiseEvalTask.getTrayList2Sync();
    }


    /**
      * 删除文件到垃圾桶
      * @param trash_path 处理的路径
      * @param is_Recycle 可以回收 
      * @param isShow 显示窗口
      */
    export function trashFile(trash_path: string, is_Recycle: boolean, isShow: boolean) {
        if (!Native.HMC_SHELL_CLASS?.trashFile) return false;
        return Native.HMC_SHELL_CLASS.trashFile(ref.string(trash_path), ref.bool(is_Recycle), ref.bool(isShow));
    }

    /**
     * 清空回收站
     * @param root_path 文件或者根目录 
     * @param isShow 是否显示窗口
    */
    export function clearTrash(root_path: string, isShow: boolean) {
        if (!Native.HMC_SHELL_CLASS?.clearTrash) return false;
        return Native.HMC_SHELL_CLASS.clearTrash(ref.string(root_path), ref.bool(isShow));
    }

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
    export function copyFile(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean) {
        if (!Native.HMC_SHELL_CLASS?.copyFile) return false;
        return Native.HMC_SHELL_CLASS.copyFile(ref.string(filePath), ref.string(newFilePath), ref.bool(isShowConfirm), ref.bool(isShow), ref.bool(isShowProgress));

    }

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
    export function moveFile(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean) {
        if (!Native.HMC_SHELL_CLASS?.moveFile) return false;
        return Native.HMC_SHELL_CLASS.moveFile(ref.string(filePath), ref.string(newFilePath), ref.bool(isShowConfirm), ref.bool(isShow), ref.bool(isShowProgress));
    }

    /**
     * 截图为Bmp 文件/Buffer
     */
    export const captureBmp2 = PromiseEval.promiseEvalTask.captureBmp2;

    /**
    * 截图为Bmp 文件/Buffer
    */
    export const captureBmp2Sync = PromiseEval.promiseEvalTask.captureBmp2Sync;

    // 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
    export const getThumbnailPng2 = PromiseEval.promiseEvalTask.getThumbnailPng2;

    // 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
    export const getThumbnailPng2Sync = PromiseEval.promiseEvalTask.getThumbnailPng2Sync;

    // 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
    export const getFileIcon2 = PromiseEval.promiseEvalTask.getThumbnailPng2;

    // 获取 文件 / EXE / icon / folder /img 的缩略图 (png格式)
    export const getFileIcon2Sync = PromiseEval.promiseEvalTask.getThumbnailPng2Sync;

    export module Symlink {

        /**
         * 判断所有链接类型
         * - 适用 -> [文件]硬链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * - 适用 -> [文件夹]文件夹连接点
         * @param targetPath 目标路径
         * @returns 
         */
        export async function hasLink2(targetPath: string): Promise<boolean> {
            return (await getLinkPath2(targetPath)) ? true : false;
        }

        /**
         * 判断所有链接类型
         * - 适用 -> [文件]硬链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * - 适用 -> [文件夹]文件夹连接点
         * @param targetPath 目标路径
         * @returns 
         */
        export function hasLink2Sync(targetPath: string): boolean {
            return (getLinkPath2Sync(targetPath)) ? true : false;
        }

        /**
         * 判断软硬链接类型
         * - 适用 -> [文件]硬链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * - 适用 -> [文件夹]文件夹连接点
         * 
         * @param Path2 
         * @returns 
         */
        export async function getLinkType2(targetPath: string): Promise<HMC.LINK_TYPE_EQ | null> {

            const data = await ShellPromiseEval.getLinkType2(ref.string(targetPath));

            return ref.JSONP<HMC.LINK_TYPE_EQ | null>(data, null);
        }

        /**
         * 判断软硬链接类型
         * - 适用 -> [文件]硬链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * - 适用 -> [文件夹]文件夹连接点
         * 
         * @param Path2 
         * @returns 
         */
        export function getLinkType2Sync(targetPath: string): HMC.LINK_TYPE_EQ | null {

            const data = ShellPromiseEval.getLinkType2Sync(ref.string(targetPath));
            return ref.JSONP<HMC.LINK_TYPE_EQ | null>(data, null);
        }

        /**
         * 获取 软链接/ 硬链接 指向的路径
         * @param targetPath 目标路径
         */
        export function getLinkPath2(targetPath: string) {
            return ShellPromiseEval.getLinkPath2(ref.string(targetPath));
        }
        /**
         * 获取 软链接/ 硬链接 指向的路径
         * @param targetPath 目标路径
         */
        export function getLinkPath2Sync(targetPath: string) {
            return ShellPromiseEval.getLinkPath2Sync(ref.string(targetPath));
        }
        /**
         * 判断是否是符号链接
         * @example 适用 -> [文件]符号连接
         * @example 适用 -> [文件夹]符号连接
         * @example 适用 -> [文件夹]文件夹符号链接
         * @param targetPath 目标路径
         */
        export function hasFileSymbolicLink2(targetPath: string) {
            return ShellPromiseEval.hasFileSymbolicLink2(ref.string(targetPath));
        }
        /**
         * 判断是否是符号链接
         * @example 适用 -> [文件]符号连接
         * @example 适用 -> [文件夹]符号连接
         * @example 适用 -> [文件夹]文件夹符号链接
         * @param targetPath 目标路径
         */
        export function hasFileSymbolicLink2Sync(targetPath: string) {
            return ShellPromiseEval.hasFileSymbolicLink2Sync(ref.string(targetPath));
        }
        /**
         * 判断是否是硬链接
         * @example 仅适用 -> [文件]硬链接
         * @param targetPath 目标路径
         */
        export function hasFileHardLink2(targetPath: string) {
            return ShellPromiseEval.hasFileHardLink2(ref.string(targetPath));
        }
        /**
         * 判断是否是硬链接
         * @example 仅适用 -> [文件]硬链接
         * @param targetPath 目标路径
         */
        export function hasFileHardLink2Sync(targetPath: string) {
            return ShellPromiseEval.hasFileHardLink2Sync(ref.string(targetPath));
        }
        /**
         * 判断是否是文件夹符号链接
         * @example 适用 -> [文件夹]符号连接
         * @param targetPath 目标路径
         */
        export function hasDirSymbolicLink2(targetPath: string) {
            return ShellPromiseEval.hasDirSymbolicLink2(ref.string(targetPath));
        }
        /**
         * 判断是否是文件夹符号链接
         * @example 适用 -> [文件夹]符号连接
         * @param targetPath 目标路径
         */
        export function hasDirSymbolicLink2Sync(targetPath: string) {
            return ShellPromiseEval.hasDirSymbolicLink2Sync(ref.string(targetPath));
        }
        /**
         * 判断是否是 文件夹链接连接点
         * @example 仅适用 -> [文件夹]文件夹连接点
         * @param targetPath 目标路径
         */
        export function hasDirJunctionPoint2(targetPath: string) {
            return ShellPromiseEval.hasDirJunctionPoint2(ref.string(targetPath));
        }
        /**
         * 判断是否是 文件夹链接连接点
         * @example 仅适用 -> [文件夹]文件夹连接点
         * @param targetPath 目标路径
         */
        export function hasDirJunctionPoint2Sync(targetPath: string) {
            return ShellPromiseEval.hasDirJunctionPoint2Sync(ref.string(targetPath));
        }
        /**
         * 创建链接
         * @param targetType 创建类型 
         * - CREATE_HARD_LINK -> [文件]硬链接
         * - CREATE_SYMLINK -> [文件]符号连接
         * - CREATE_DIR_SYMLINK -> [文件夹]符号连接
         * - CREATE_JUNCTION_POINT_LINK -> [文件夹]目录连接点
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns 
         */
        export function createLink(targetType: HMC.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string) {
            return ShellPromiseEval.createLink(ref.int(targetType), ref.string(targetPath), ref.string(sourcePath));
        }
        /**
         * 创建链接
         * @param targetType 创建类型 
         * - CREATE_HARD_LINK -> [文件]硬链接
         * - CREATE_SYMLINK -> [文件]符号连接
         * - CREATE_DIR_SYMLINK -> [文件夹]符号连接
         * - CREATE_JUNCTION_POINT_LINK -> [文件夹]目录连接点
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns 
         */
        export function createLinkSync(targetType: HMC.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string) {
            return ShellPromiseEval.createLinkSync(ref.int(targetType), ref.string(targetPath), ref.string(sourcePath));
        }
        /**
         * 创建目录连接点
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns 
         */
        export function createDirJunctionPoint2(targetPath: string, sourcePath: string) {
            return ShellPromiseEval.createDirJunctionPoint2(ref.string(targetPath), ref.string(sourcePath));
        }
        /**
         * 创建目录连接点
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns 
         */
        export function createDirJunctionPoint2Sync(targetPath: string, sourcePath: string) {
            return ShellPromiseEval.createDirJunctionPoint2Sync(ref.string(targetPath), ref.string(sourcePath));
        }
        /**
         * 创建硬链接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns 
         */
        export function createHardLink2(targetPath: string, sourcePath: string) {
            return ShellPromiseEval.createHardLink2(ref.string(targetPath), ref.string(sourcePath));
        }
        /**
         * 创建硬链接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns 
         */
        export function createHardLink2Sync(targetPath: string, sourcePath: string) {
            return ShellPromiseEval.createHardLink2Sync(ref.string(targetPath), ref.string(sourcePath));
        }
        /**
         * 创建软链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns 
         */
        export function createSymlink2(targetPath: string, sourcePath: string) {
            return ShellPromiseEval.createSymlink2(ref.string(targetPath), ref.string(sourcePath));
        }
        /**
         * 创建软链接
         * - 适用 -> [文件]符号连接
         * - 适用 -> [文件夹]符号连接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns 
         */
        export function createSymlink2Sync(targetPath: string, sourcePath: string) {
            return ShellPromiseEval.createSymlink2Sync(ref.string(targetPath), ref.string(sourcePath));
        }
        /**
         * 创建目录符号链接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns 
         */
        export function createDirSymlink2(targetPath: string, sourcePath: string) {
            return ShellPromiseEval.createDirSymlink2(ref.string(targetPath), ref.string(sourcePath));
        }
        /**
         * 创建目录符号链接
         * @param targetPath 目标路径
         * @param sourcePath 原始文件路径
         * @returns 
         */
        export function createDirSymlink2Sync(targetPath: string, sourcePath: string) {
            return ShellPromiseEval.createDirSymlink2Sync(ref.string(targetPath), ref.string(sourcePath));
        }

    }

    /**
     * 检索指定文件或目录的文件系统属性
     * @param targetPath 指定文件或目录
     * @returns 
     */
    export function getFileAttributes2(targetPath: string) {
        return ShellPromiseEval.getFileAttributes2(ref.string(targetPath));
    }

    /**
     * 检索指定文件或目录的文件系统属性
     * @param targetPath 指定文件或目录
     * @returns 
     */
    export function getFileAttributes2Sync(targetPath: string) {
        return ShellPromiseEval.getFileAttributes2Sync(ref.string(targetPath));
    }

    /**
     * 设置文件夹图标
     * @param targetPath 目标 文件/目录 路径 
     * @param iconPath 图标路径
     * - .exe 可执行文件
     * - .ico 图标文件
     * - .png 图片文件
     * - *.* 任意文件
     * @param iconIndex 图标索引 比如exe中的0 默认是0
     * @returns 
     */
    export function setFolderIcon2(targetPath: string, iconPath: string, iconIndex?: number): Promise<boolean> {
        return ShellPromiseEval.setFolderIcon2(ref.string(targetPath), ref.string(iconPath), ref.int(iconIndex || 0));
    }

    /**
     * 设置文件夹图标
     * @param targetPath 目标 文件/目录 路径 
     * @param iconPath 图标路径
     * - .exe 可执行文件
     * - .ico 图标文件
     * - .png 图片文件
     * - *.* 任意文件
     * @param iconIndex 图标索引 比如exe中的0 默认是0
     * @returns 
     */
    export function setFolderIcon2Sync(targetPath: string, iconPath: string, iconIndex?: number): boolean {
        return ShellPromiseEval.setFolderIcon2Sync(ref.string(targetPath), ref.string(iconPath), ref.int(iconIndex || 0));
    }

    /**
     * 设置指定扩展名的 图标
     * @param extensionName 扩展名
     * @example .mp3 , .cpp , .js 
     * @param typeName 类型名字 比如 HMC打包的音频文件扩展
     * @param iconPath 图标路径
     * - .exe 可执行文件
     * - .ico 图标文件
     * - .png 图片文件
     * - *.* 任意文件
     * @param iconIndex 图标索引 比如exe中的0 默认是0
     * @returns 
     */
    export async function setExtensionIcon2(extensionName: string, typeName: string, iconPath: string, iconIndex?: number): Promise<boolean> {
        return (await ShellPromiseEval.setExtensionIcon2(ref.string(extensionName), ref.string(typeName), ref.string(iconPath), ref.int(iconIndex || 0))) || false;
    }

    /**
     * 设置指定扩展名的 图标
     * @param extensionName 扩展名
     * @example .mp3 , .cpp , .js 
     * @param typeName 类型名字 比如 HMC打包的音频文件扩展
     * @param iconPath 图标路径
     * - .exe 可执行文件
     * - .ico 图标文件
     * - .png 图片文件
     * - *.* 任意文件
     * @param iconIndex 图标索引 比如exe中的0 默认是0
     * @returns 
     */
    export function setExtensionIcon2Sync(extensionName: string, typeName: string, iconPath: string, iconIndex: number): boolean {
        return ShellPromiseEval.setExtensionIcon2Sync(ref.string(extensionName), ref.string(typeName), ref.string(iconPath), ref.int(iconIndex || 0)) || false;
    }

    /**
     * 设置url 启动协议 比如 vscode:// 启动应用vscode
     * @param protocolName 协议名 不能带有只允许字母与数字
     * @param appPath 应用路径
     * @param command 启动命令 默认 %1
     * @returns 
     */
    export function setAppURLProtocol2Sync(protocolName: string, appPath: string, command?: string | string[]) {
        if (Array.isArray(command)) {
            let command_list = "";
            for (let index = 0; index < command.length; index++) {
                const command_ = command[index];
                command_list = command_list + ` "${command_}"`;
            }

            command = command_list;
        }
        return ShellPromiseEval.setAppURLProtocol2Sync(ref.string(protocolName), ref.string(appPath), ref.string(command));
    }

    /**
     * 设置url 启动协议 比如 vscode:// 启动应用vscode
     * @param protocolName 协议名 不能带有只允许字母与数字
     * @param appPath 应用路径
     * @param command 启动命令 默认 %1
     * @returns 
     */
    export function setAppURLProtocol2(protocolName: string, appPath: string, command?: string | string[]) {
        if (Array.isArray(command)) {
            let command_list = "";
            for (let index = 0; index < command.length; index++) {
                const command_ = command[index];
                command_list = command_list + ` "${command_}"`;
            }

            command = command_list;
        }
        if (!command) {
            command = "%1";
        }

        return ShellPromiseEval.setAppURLProtocol2(ref.string(protocolName), ref.string(appPath), ref.string(command));
    }

    /**
     * 查询 快捷方式 目标路径 及 详细信息
     * @param targetPath 快捷方式路径
     * @param QueryDetaile 是否查询详细信息
     */
    export async function getShortcutLink2(targetPath: string, QueryDetaile: true): Promise<HMC.SHORTCUT_LINK | null>;

    /**
     * 查询 快捷方式 目标路径 [仅路径]
     * @param targetPath 快捷方式路径
     * @param QueryDetaile 是否查询详细信息
     */
    export async function getShortcutLink2(targetPath: string, QueryDetaile: false): Promise<string | null>;

    /**
     * 查询 快捷方式 目标路径 [仅路径]
     * @param targetPath 快捷方式路径
     */
    export async function getShortcutLink2(targetPath: string): Promise<HMC.SHORTCUT_LINK | null>;

    export async function getShortcutLink2(targetPath: string, QueryDetaile?: boolean): Promise<unknown> {

        const _QueryDetaile = typeof QueryDetaile == "boolean" ? QueryDetaile : ref.bool(QueryDetaile || true);
        const data = await ShellPromiseEval.getShortcutLink2(ref.string(targetPath), _QueryDetaile);

        if (typeof data == "string") {
            if (_QueryDetaile) {
                return ref.JSONP<HMC.SHORTCUT_LINK | null>(data, null);
            }

            return data;

        }

        return data;
    }

    /**
     * 查询 快捷方式 目标路径 及 详细信息
     * @param targetPath 快捷方式路径
     * @param QueryDetaile 是否查询详细信息
     */
    export function getShortcutLink2Sync(targetPath: string, QueryDetaile: true): HMC.SHORTCUT_LINK | null;
    /**
     * 查询 快捷方式 目标路径 [仅路径]
     * @param targetPath 快捷方式路径
     */
    export function getShortcutLink2Sync(targetPath: string, QueryDetaile: false): string | null;

    /**
     * 查询 快捷方式 目标路径 [仅路径]
     * @param targetPath 快捷方式路径
     * @param QueryDetaile 是否查询详细信息
     */
    export function getShortcutLink2Sync(targetPath: string): HMC.SHORTCUT_LINK | null;
    export function getShortcutLink2Sync(targetPath: string, QueryDetaile?: boolean): unknown {

        const _QueryDetaile = typeof QueryDetaile == "boolean" ? QueryDetaile : ref.bool(QueryDetaile || true);
        const data = ShellPromiseEval.getShortcutLink2Sync(ref.string(targetPath), _QueryDetaile);

        if (typeof data == "string") {
            if (_QueryDetaile) {
                return ref.JSONP<HMC.SHORTCUT_LINK | null>(data, null);
            }
            return data;
        }

        return data;
    }

    /**
     * 设置快捷方式
     * @param targetPath 快捷方式存放路径
     * @param FilePath 文件路径
     * @param work_dir 工作目录
     * @param desc 详情
     * @param args 命令行
     * @param iShowCmd 启动时显示的内容
     * @param icon 图标位置
     * @param iconIndex 图标索引 默认0
     * @returns 
     */
    export async function setShortcutLink2(targetPath: string, FilePath: string, work_dir?: string, desc?: string, args?: string, iShowCmd?: number, icon?: string, iconIndex?: number): Promise<boolean> {
        if (!work_dir) work_dir = "";
        if (!desc) desc = "";
        if (!args) args = "";
        if (!icon) icon = "";
        if (!iconIndex) iconIndex = 0;
        if (!iShowCmd) iShowCmd = 1;

        return ShellPromiseEval.setShortcutLink2(ref.string(targetPath), ref.string(FilePath), ref.string(work_dir), ref.string(desc), ref.string(args), ref.int(iShowCmd), ref.string(icon), ref.int(iconIndex));
    }

    /**
     * 将指定文件夹移动到回收站
     * @param trash_path 待回收文件
     * @param is_Recycle 是否可以撤回
     * @param isShow 是否显示窗口
     * @returns 
     */
    export async function trashFile2(trash_path: string, is_Recycle?: boolean, isShow?: boolean): Promise<boolean> {
        if (typeof is_Recycle != "boolean") is_Recycle = true;
        if (typeof isShow != "boolean") isShow = true;
        return ShellPromiseEval.trashFile2(ref.string(trash_path), ref.bool(is_Recycle), ref.bool(isShow));
    }

    /**
     * 清空回收站
     * @param trash_path 盘符 / 全部
     * @param isShow 是否显示窗口
     * @returns 
     */
    export async function clearTrash2(root_path?: string, isShow?: boolean): Promise<boolean> {
        if (typeof isShow != "boolean") isShow = true;
        return ShellPromiseEval.clearTrash2(ref.string(root_path || ""), ref.bool(isShow));
    }

    /**
     * 复制文件到指定位置
     * @param filePath 源文件地址
     * @param newFilePath 新的文件地址
     * @param isShowConfirm 是否显示确认窗口（比如文件已存在）
     * @param isShow 是否显示过程窗口
     * @param isShowProgress 是否显示进度条(启用时 isShow 必须为true)
     * @returns 
     */
    export async function copyFile2(filePath: string, newFilePath: string, isShowConfirm?: boolean, isShow?: boolean, isShowProgress?: boolean): Promise<boolean> {
        if (typeof isShowConfirm != "boolean") isShowConfirm = true;
        if (typeof isShow != "boolean") isShow = true;
        if (typeof isShowProgress != "boolean") isShowProgress = true;
        return ShellPromiseEval.copyFile2(ref.string(filePath), ref.string(newFilePath), ref.bool(isShowConfirm), ref.bool(isShow), ref.bool(isShowProgress));
    }

    /**
     * 移动文件到指定位置
     * @param filePath 源文件地址
     * @param newFilePath 新的文件地址
     * @param isShowConfirm 是否显示确认窗口（比如文件已存在）
     * @param isShow 是否显示过程窗口
     * @param isShowProgress 是否显示进度条(启用时 isShow 必须为true)
     * @returns 
     */
    export async function moveFile2(filePath: string, newFilePath: string, isShowConfirm?: boolean, isShow?: boolean, isShowProgress?: boolean): Promise<boolean> {
        if (typeof isShowConfirm != "boolean") isShowConfirm = true;
        if (typeof isShow != "boolean") isShow = true;
        if (typeof isShowProgress != "boolean") isShowProgress = true;
        return ShellPromiseEval.moveFile2(ref.string(filePath), ref.string(newFilePath), ref.bool(isShowConfirm), ref.bool(isShow), ref.bool(isShowProgress));
    }

    /**
     * 设置快捷方式
     * @param targetPath 快捷方式存放路径
     * @param FilePath 文件路径
     * @param work_dir 工作目录
     * @param desc 详情
     * @param args 命令行
     * @param iShowCmd 启动时显示的内容
     * @param icon 图标位置
     * @param iconIndex 图标索引 默认0
     * @returns 
     */
    export function setShortcutLink2Sync(targetPath: string, FilePath: string, work_dir?: string, desc?: string, args?: string, iShowCmd?: number, icon?: string, iconIndex?: number): boolean {
        if (!work_dir) work_dir = "";
        if (!desc) desc = "";
        if (!args) args = "";
        if (!icon) icon = "";
        if (!iconIndex) iconIndex = 0;
        if (!iShowCmd) iShowCmd = 1;

        return ShellPromiseEval.setShortcutLink2Sync(ref.string(targetPath), ref.string(FilePath), ref.string(work_dir), ref.string(desc), ref.string(args), ref.int(iShowCmd), ref.string(icon), ref.int(iconIndex));
    }

    /**
     * 将指定文件夹移动到回收站
     * @param trash_path 待回收文件
     * @param is_Recycle 是否可以撤回
     * @param isShow 是否显示窗口
     * @returns 
     */
    export function trashFile2Sync(trash_path: string, is_Recycle?: boolean, isShow?: boolean): boolean {
        if (typeof is_Recycle != "boolean") is_Recycle = true;
        if (typeof isShow != "boolean") isShow = true;

        return ShellPromiseEval.trashFile2Sync(ref.string(trash_path), ref.bool(is_Recycle), ref.bool(isShow));
    }

    /**
     * 清空回收站
     * @param trash_path 盘符 / 全部
     * @param isShow 是否显示窗口
     * @returns 
     */
    export function clearTrash2Sync(root_path?: string, isShow?: boolean): boolean {
        if (typeof isShow != "boolean") isShow = true;
        return ShellPromiseEval.clearTrash2Sync(ref.string(root_path || ""), ref.bool(isShow));
    }

    /**
     * 复制文件到指定位置
     * @param filePath 源文件地址
     * @param newFilePath 新的文件地址
     * @param isShowConfirm 是否显示确认窗口（比如文件已存在）
     * @param isShow 是否显示过程窗口
     * @param isShowProgress 是否显示进度条(启用时 isShow 必须为true)
     * @returns 
     */
    export function copyFile2Sync(filePath: string, newFilePath: string, isShowConfirm?: boolean, isShow?: boolean, isShowProgress?: boolean): boolean {
        if (typeof isShowConfirm != "boolean") isShowConfirm = true;
        if (typeof isShow != "boolean") isShow = true;
        if (typeof isShowProgress != "boolean") isShowProgress = true;

        return ShellPromiseEval.copyFile2Sync(ref.string(filePath), ref.string(newFilePath), ref.bool(isShowConfirm), ref.bool(isShow), ref.bool(isShowProgress));
    }

    /**
     * 移动文件到指定位置
     * @param filePath 源文件地址
     * @param newFilePath 新的文件地址
     * @param isShowConfirm 是否显示确认窗口（比如文件已存在）
     * @param isShow 是否显示过程窗口
     * @param isShowProgress 是否显示进度条(启用时 isShow 必须为true)
     * @returns 
     */
    export function moveFile2Sync(filePath: string, newFilePath: string, isShowConfirm?: boolean, isShow?: boolean, isShowProgress?: boolean): boolean {
        if (typeof isShowConfirm != "boolean") isShowConfirm = true;
        if (typeof isShow != "boolean") isShow = true;
        if (typeof isShowProgress != "boolean") isShowProgress = true;

        return ShellPromiseEval.moveFile2Sync(ref.string(filePath), ref.string(newFilePath), ref.bool(isShowConfirm), ref.bool(isShow), ref.bool(isShowProgress));
    }


    export const HMC_GetShellEnvInfo = ShellPromiseEval;
}