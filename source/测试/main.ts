import type _hmc = require("../mian/hmc");
import fs = require("fs-extra");
import jsonfm = require("jsonfm");
import shake = require("hmc-shake");
import log4js = require("log4js");

import hmc, { ref, PromiseSP } from "../../";
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");

process.exitCode = 666;
const native: _hmc.HMC.Native & Native = require(process.argv.at(-1) || "");

export interface Native {

}


/**
 * 获取指定进程的工作目录
 * @time 5.449ms
 * @description 由于跨进程权限问题 不保证获取得到
 * !此功能需要读取进程内存
 * @module 异步async
 * @param pid 
 */
export function getProcessCwd2(pid: number): Promise<string | null> {
    return PromiseSP(native.getProcessCwd(ref.int(pid)), (data) => {
        if (typeof data === 'string') return data;
        return data?.[0] ? String(data?.[0]) : null;
    });
}

/**
 * 获取指定进程的工作目录
 * @time 0.435ms
 * @description 由于跨进程权限问题 不保证获取得到
 * !此功能需要读取进程内存
 * @module 同步Sync
 * @param pid 
 */
export function getProcessCwd2Sync(pid: number): string | null {
    return native.getProcessCwdSync(ref.int(pid));
}

/**
 * 获取指定进程得出命令行 
 * @time 1.095ms
 * @description 由于跨进程权限问题 不保证获取得到
 * ?此功能在win8及以下系统 需要读取进程内存
 * @module 异步async
 * @param pid 进程id
 */
export function getProcessCommand2(pid: number): Promise<string> {
    return PromiseSP(native.getProcessCommand(ref.int(pid)), (data) => {
        if (typeof data === 'string') return data;

        return String(data?.[0] || "");
    });
}

/**
 * 获取指定进程得出命令行
 * @time 0.386ms
 * @description 由于跨进程权限问题 不保证获取得到
 * ?此功能在win8及以下系统 需要读取进程内存
 * @module 同步Sync
 * @param pid 
 */
export function getProcessCommand2Sync(pid: number): string | null {
    return native.getProcessCommandSync(ref.int(pid));
}


/**
 * 限制鼠标光标可移动范围 (异步)
 * @description 可以调用 stop 提前结束 
 * ?最高不允许超过30000ms (30秒) 最低不允许低于31ms 
 * ?范围为正方形 如果没有设置right与bottom的值则将限制为1x1的正方形 (不可动)
 * @param ms 本次限制的时间
 * @param x 限制左边初始化点的位置
 * @param y 限制顶部初始化点的位置
 * @param right 允许的范围(左边到右边部)
 * @param bottom 允许光标移动的范围(顶到底部)
 */
export function setLimitMouseRange(ms: number, x: number, y: number, right: number = 1, bottom: number = 1) {

    ms = Math.abs(ref.int(ms));
    x = Math.abs(ref.int(x));
    y = Math.abs(ref.int(y));
    right = Math.abs(ref.int(right)) || 1;
    bottom = Math.abs(ref.int(bottom)) || 1;
    
    if(ms>30*1000||ms<30){
        throw new Error("The range is only allowed from 31 milliseconds to 30 seconds (31ms-30000).")
    }
    
    native.setLimitMouseRange(ms,x,y,right,bottom);
    

    const res =  {
        ms, x, y, right, bottom,
        closed:(()=>{
            setTimeout(()=>{
                // 这一步看着很多余实际上确实多余
                // !请注意此地方不能取消
                /*请注意此地方不能取消 不然node提前结束将会导致无法解锁 避免进程提前退出导致无法结束 */
                res.closed = native.hasLimitMouseRangeWorker();
                },ms+80);
            return false;
        })() as boolean,
        /**
         * 停止本次
         * @returns 
         */
        close() {
            return native.stopLimitMouseRangeWorker();
        },

        /**
         * 是否正在执行中
         * @returns 
         */
        has() {
            return !native.hasLimitMouseRangeWorker();
        }

    }

    return res;
}


(async function main() {

    // console.time("hmc.getProcessCwd()->");
    // console.log("hmc.getProcessCwd()->", await getProcessCwd2(process.pid));
    // console.timeEnd("hmc.getProcessCwd()->");


    // console.time("hmc.getProcessCwdSync()->");
    // console.log("hmc.getProcessCwdSync()->", getProcessCwd2Sync(process.pid));
    // console.timeEnd("hmc.getProcessCwdSync()->");


    // console.time("hmc.getProcessCommand()->");
    // console.log("hmc.getProcessCommand()->", await getProcessCommand2(process.pid));
    // console.timeEnd("hmc.getProcessCommand()->");


    // console.time("hmc.getProcessCommand()->");
    // console.log("hmc.getProcessCommand()->", getProcessCommand2Sync(process.pid));
    // console.timeEnd("hmc.getProcessCommand()->");

    const setLimitMouse = setLimitMouseRange(5000,1,1,1,500);
   
    hmc.Auto.mouseHook.on("mouse",console.log);
    hmc.Auto.mouseHook.start();

    // 模拟意外退出
    process.exit(555);

})();





