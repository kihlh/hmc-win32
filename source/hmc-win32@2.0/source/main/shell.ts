import main = require("./index");
import util = require("./util");
import PromiseEval = require("./promiseEval");


const { ref } = util;

class StartupConstructor {
    #Startup: null | main.HMC2_MODE.HMC_SHELL_STARTUP_CLASS = null;

    #initialize() {
        if (!this.#Startup && main.Native.native.HMC_SHELL_STARTUP_CLASS) {
            this.#Startup = main.Native.native.HMC_SHELL_STARTUP_CLASS();
        }
    }

    #root: "HKEY_LOCAL_MACHINE" = "HKEY_LOCAL_MACHINE";
    #pathRun = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    #pathRunOnce = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
    constructor() { }

    has(keyName: string) {
        this.#initialize();
        return this.#Startup?.has(ref.string(keyName)) || false;
    }

    hasOnce(keyName: string) {
        this.#initialize();
        return this.#Startup?.hasOnce(ref.string(keyName)) || false;
    }


    remove(keyName: string) {
        this.#initialize();
        return this.#Startup?.remove(ref.string(keyName)) || false;
    }


    removeOnce(keyName: string) {
        this.#initialize();
        return this.#Startup?.removeOnce(ref.string(keyName)) || false;
    }

    set(keyName: string, path: string, cmd?: string) {
        this.#initialize();
        return this.#Startup?.set(ref.string(keyName), ref.string(path), ref.string(cmd || "")) || false;
    }

    setOnce(keyName: string, path: string, cmd?: string) {
        this.#initialize();
        return this.#Startup?.setOnce(ref.string(keyName), ref.string(path), ref.string(cmd || "")) || false;
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


    /**
     * 弹出右键菜单的接口
     * @param hwnd 调用窗口 / 允许为null
     * @param file 指定需要被显示菜单的文件/文件夹/文件列表/ 为空 "" 为驱动器
     * @param x 坐标 x+y=0的时候将会从鼠标所在的地方显示
     * @param y 坐标
     */
    export function showContextMenu(hwnd?: number | null, file?: string | string[], x?: number, y?: number) {
        return main.Native.native?.showContextMenu ?
            main.Native.native?.showContextMenu(
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
        if (!main.Native.native.getTrayList) return [];
        return JSON.parse(main.Native.native.getTrayList());
    }

    /**
     * 设置文件夹的缩略图
     * @param folderPath 路径
     * @param iconPath 图标路径
     * @param iconIndex 图标索引 比如exe中的0
     * @returns 
     */
    export function setFolderIcon(folderPath: string, iconPath: string, iconIndex?: number) {

        if (!main.Native.native.setFolderIcon) return false;
        return main.Native.native.setFolderIcon(ref.string(folderPath), ref.string(iconPath), ref.int(iconIndex || 0));

    }

}