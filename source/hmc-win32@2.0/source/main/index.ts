
import { Native } from "./Native";
import * as ShellPromiseEvalMain from "./ShellPromiseEval";
import * as RegistrMain from "./registr";
import * as ProcessMain from "./Process";
import * as UtilMain from "./util";
import * as AutoMain from "./auto";
import * as ShellMain from "./shell";
import * as PromiseEval from "./promiseEval";
import * as SokePromiseEvalMain from "./Sock";

export const { ref } = UtilMain;

// 键鼠/自动化相关
export const Auto = AutoMain;

// 启动项管理
export const Startup = ShellMain.Shell.Startup;

// win32 shell(壳) api 功能集
export const Shell = ShellMain.Shell;

// 进程操作功能集
export const Process = ProcessMain.Process;
export const { Sleep, sleep } = Process;

//注册表编辑合集
export const Registr = RegistrMain.Registr;

export namespace Window {

    /**
     * 将 electron 句柄内存缓冲区转换为标准 窗口数字句柄
     * @param handleBuffer 例如 Electron.BrowserWindow.getFocusedWindow().getNativeWindowHandle()
     * @returns 
     */
    export function readElectronHandle(handleBuffer: any) {
        let num = 0;

        // Node.js 10.5.0 以上版本
        if (typeof BigInt != 'undefined') {
            let handleBigInt = handleBuffer.readBigUInt64LE();
            return (Number(handleBigInt));
        }
        else {
            if (process.platform == 'win32') {
                num = handleBuffer.readUInt32LE();
            }
            else if (process.platform == 'darwin') {
                num = handleBuffer.readUInt32LE(0) + 2 * 32 * handleBuffer.readUInt32LE(4);
            }
            else {
                num = handleBuffer.readUInt32LE(0) + 2 * 32 * handleBuffer.readUInt32LE(4);
            }

            return num;
        }
        return num;
    }


}

// 软硬链接相关
export const Symlink = ShellMain.Shell.Symlink;

export const Network = SokePromiseEvalMain.Network;

export const { isAdmin2, isAdmin2Sync, isSystemFor64bit2, isSystemFor64bit2Sync } = Network;

const HMC_MODE = {
    Native,
    Auto,
    Startup,
    Shell,
    Process,
    Registr,
    Window,
    Symlink,
    Network,
    Sleep,
    sleep,
    isAdmin2,
    isAdmin2Sync,
    isSystemFor64bit2,
    isSystemFor64bit2Sync
};

export { Native };

export default HMC_MODE;

process.on('exit', function () {

});
