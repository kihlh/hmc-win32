import main = require("./index");
import util = require("./util");
import PromiseEval = require("./promiseEval");


const { ref } = util;

const STARTUP_CONSTRUCTOR_DATA = {

    _Startup: null as null | main.HMC2_MODE.HMC_SHELL_STARTUP_CLASS,
    _initialize() {
        if (!STARTUP_CONSTRUCTOR_DATA._Startup && main.Native.native.HMC_SHELL_STARTUP_CLASS) {
            STARTUP_CONSTRUCTOR_DATA._Startup = main.Native.native.HMC_SHELL_STARTUP_CLASS();
        }
    },
    _root: "HKEY_LOCAL_MACHINE",
    _pathRun: "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
    _pathRunOnce: "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"
}

class StartupConstructor {

    constructor() { }

    has(keyName: string) {
        STARTUP_CONSTRUCTOR_DATA._initialize()
        return STARTUP_CONSTRUCTOR_DATA._Startup?.has(ref.string(keyName)) || false;
    }

    hasOnce(keyName: string) {
        STARTUP_CONSTRUCTOR_DATA._initialize()
        return STARTUP_CONSTRUCTOR_DATA._Startup?.hasOnce(ref.string(keyName)) || false;
    }

    remove(keyName: string) {
        STARTUP_CONSTRUCTOR_DATA._initialize()
        return STARTUP_CONSTRUCTOR_DATA._Startup?.remove(ref.string(keyName)) || false;
    }

    removeOnce(keyName: string) {
        STARTUP_CONSTRUCTOR_DATA._initialize()
        return STARTUP_CONSTRUCTOR_DATA._Startup?.removeOnce(ref.string(keyName)) || false;
    }

    set(keyName: string, path: string, cmd?: string) {
        STARTUP_CONSTRUCTOR_DATA._initialize()
        return STARTUP_CONSTRUCTOR_DATA._Startup?.set(ref.string(keyName), ref.string(path), ref.string(cmd || "")) || false;
    }

    setOnce(keyName: string, path: string, cmd?: string) {
        STARTUP_CONSTRUCTOR_DATA._initialize()
        return STARTUP_CONSTRUCTOR_DATA._Startup?.setOnce(ref.string(keyName), ref.string(path), ref.string(cmd || "")) || false;
    }

    enum() {
        const obj: { [key: string]: string } = {};
        // const keys = native.enumRegistrKey(this.#root, this.#pathRun);
        // for (let index = 0; index < keys.length; index++) {
        //     let at = keys[index];
        //     obj[at] = native.getStringRegKey(this.#root, this.#pathRun, at);
        // }
        return obj;
    }

    enumOnce() {
        const obj: { [key: string]: string } = {};
        // const keys = native.enumRegistrKey(this.#root, this.#pathRunOnce);
        // for (let index = 0; index < keys.length; index++) {
        //     let at = keys[index];
        //     obj[at] = native.getStringRegKey(this.#root, this.#pathRunOnce, at);
        // }
        return obj;
    }

    keys() {
        return [];
        // return native.enumRegistrKey(this.#root,this.#pathRun);
    }

    keysOnce() {
        return [];
        // return native.enumRegistrKey(this.#root,this.#pathRunOnce);
    }
}

export module Shell {

    /**
     * 启动项 管理
     */
    export const Startup = new StartupConstructor();

    let _SHELL: null | main.HMC2_MODE.HMC_SHELL_CLASS = null;

    function SHELL_initialize() {
        if (!_SHELL && main.Native.native.HMC_SHELL_CLASS) {
            _SHELL = main.Native.native.HMC_SHELL_CLASS();
        }
    }


    /**
        * 弹出右键菜单的接口
        * @param hwnd 调用窗口 / 允许为null
        * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
        * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
        * @param y 坐标
        */
    export function showContextMenu(hwnd?: number | null, file?: string | string[], x?: number, y?: number) {
        SHELL_initialize()
        return _SHELL?.showContextMenu ?
            _SHELL?.showContextMenu(
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
    export function getTrayList(): Array<main.HMC2_MODE.TRAY_ICON> {
        SHELL_initialize()
        if (!_SHELL?.getTrayList) return [];
        return JSON.parse(_SHELL.getTrayList());
    }

    /**
     * 设置文件夹的缩略图
     * @param folderPath 路径
     * @param iconPath 图标路径
     * @param iconIndex 图标索引 比如exe中的0
     * @returns 
     */
    export function setFolderIcon(folderPath: string, iconPath: string, iconIndex?: number) {
        SHELL_initialize()
        if (!_SHELL?.setFolderIcon) return false;
        return _SHELL.setFolderIcon(ref.string(folderPath), ref.string(iconPath), ref.int(iconIndex || 0));
    }

    /**
      * 删除文件到垃圾桶
      * @param trash_path 处理的路径
      * @param is_Recycle 可以回收 
      * @param isShow 显示窗口
      */
    export function trashFile(trash_path: string, is_Recycle: boolean, isShow: boolean) {
        SHELL_initialize()
        if (!_SHELL?.trashFile) return false;
        return _SHELL.trashFile(ref.string(trash_path), ref.bool(is_Recycle), ref.bool(isShow));
    }

    /**
     * 清空回收站
     * @param root_path 文件或者根目录 
     * @param isShow 是否显示窗口
    */
    export function clearTrash(root_path: string, isShow: boolean) {
        SHELL_initialize()
        if (!_SHELL?.clearTrash) return false;
        return _SHELL.clearTrash(ref.string(root_path), ref.bool(isShow));
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
    export function copyFile(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean, trash_ok: boolean) {
        SHELL_initialize()
        if (!_SHELL?.copyFile) return false;
        return _SHELL.copyFile(ref.string(filePath), ref.string(newFilePath), ref.bool(isShowConfirm), ref.bool(isShow), ref.bool(isShowProgress), ref.bool(trash_ok));

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
    export function moveFile(filePath: string, newFilePath: string, isShowConfirm: boolean, isShow: boolean, isShowProgress: boolean, trash_ok: boolean) {
        SHELL_initialize()
        if (!_SHELL?.moveFile) return false;
        return _SHELL.moveFile(ref.string(filePath), ref.string(newFilePath), ref.bool(isShowConfirm), ref.bool(isShow), ref.bool(isShowProgress), ref.bool(trash_ok));
    }

    /**
     * 获取 软/硬 链接的指向内容
     * @param Linkath 
     */
    export function getLinkTarget(Linkath: string) {
        SHELL_initialize()
        if (!_SHELL?.getLinkTarget) return false;
        return _SHELL.getLinkTarget(ref.string(Linkath));
    }

    /**
     * 判断指定文件是否是 软链接/硬链接
     * @param path 
     * @returns 
     */
    export function isLinkLink(path: string) {
        SHELL_initialize()
        if (!_SHELL?.isLinkLink) return false;
        return _SHELL.isLinkLink(ref.string(path));
    }

    /**
     * 创建 软链接/硬链接/目录连接点/文件夹链接
     * @param targetType 创建类型
     * - 文件夹链接 CREATE_DIR_SYMLINK = 166
     * - 软链接 CREATE_SYMLINK = 168
     * - 硬链接 CREATE_HARD_LINK = 170
     * - 目录连接点 CREATE_SYMBOLIC_LINK = 172
     * @param targetPath 目标位置
     * @param sourcePath 源文件路径
     * @returns 
     */
    export function createFsLink(targetType: main.HMC2_MODE.FS_MK_LINK_TARGET_TYPE, targetPath: string, sourcePath: string) {
        SHELL_initialize()
        if (!_SHELL?.createFsLink) return false;
        return _SHELL.createFsLink(ref.int(targetType), ref.string(targetPath), ref.string(sourcePath));
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



}