"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.setLimitMouseRange = exports.getProcessCommand2Sync = exports.getProcessCommand2 = exports.getProcessCwd2Sync = exports.getProcessCwd2 = void 0;
const log4js = require("log4js");
const __1 = require("../../");
const { Sleep } = require("hmc-win32");
log4js.configure({ appenders: { cheese: { type: "file", filename: "cheese.log" } }, categories: { default: { appenders: ["cheese"], level: "error" } } });
const log = log4js.getLogger("cheese");
process.exitCode = 666;
const native = require(process.argv.at(-1) || "");
/**
 * 获取指定进程的工作目录
 * @time 5.449ms
 * @description 由于跨进程权限问题 不保证获取得到
 * !此功能需要读取进程内存
 * @module 异步async
 * @param pid
 */
function getProcessCwd2(pid) {
    return (0, __1.PromiseSP)(native.getProcessCwd(__1.ref.int(pid)), (data) => {
        if (typeof data === 'string')
            return data;
        return (data === null || data === void 0 ? void 0 : data[0]) ? String(data === null || data === void 0 ? void 0 : data[0]) : null;
    });
}
exports.getProcessCwd2 = getProcessCwd2;
/**
 * 获取指定进程的工作目录
 * @time 0.435ms
 * @description 由于跨进程权限问题 不保证获取得到
 * !此功能需要读取进程内存
 * @module 同步Sync
 * @param pid
 */
function getProcessCwd2Sync(pid) {
    return native.getProcessCwdSync(__1.ref.int(pid));
}
exports.getProcessCwd2Sync = getProcessCwd2Sync;
/**
 * 获取指定进程得出命令行
 * @time 1.095ms
 * @description 由于跨进程权限问题 不保证获取得到
 * ?此功能在win8及以下系统 需要读取进程内存
 * @module 异步async
 * @param pid 进程id
 */
function getProcessCommand2(pid) {
    return (0, __1.PromiseSP)(native.getProcessCommand(__1.ref.int(pid)), (data) => {
        if (typeof data === 'string')
            return data;
        return String((data === null || data === void 0 ? void 0 : data[0]) || "");
    });
}
exports.getProcessCommand2 = getProcessCommand2;
/**
 * 获取指定进程得出命令行
 * @time 0.386ms
 * @description 由于跨进程权限问题 不保证获取得到
 * ?此功能在win8及以下系统 需要读取进程内存
 * @module 同步Sync
 * @param pid
 */
function getProcessCommand2Sync(pid) {
    return native.getProcessCommandSync(__1.ref.int(pid));
}
exports.getProcessCommand2Sync = getProcessCommand2Sync;
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
function setLimitMouseRange(ms, x, y, right = 1, bottom = 1) {
    ms = Math.abs(__1.ref.int(ms));
    x = Math.abs(__1.ref.int(x));
    y = Math.abs(__1.ref.int(y));
    right = Math.abs(__1.ref.int(right)) || 1;
    bottom = Math.abs(__1.ref.int(bottom)) || 1;
    if (ms > 30 * 1000 - 1 || ms < 30 - 1) {
        throw new Error("The range is only allowed from 31 milliseconds to 30 seconds (31ms-30000).");
    }
    native.setLimitMouseRange(ms, x, y, right, bottom);
    const res = {
        ms, x, y, right, bottom,
        closed: (() => {
            setTimeout(() => {
                // 这一步看着很多余实际上确实多余
                // !请注意此地方不能取消
                /*请注意此地方不能取消 不然node提前结束将会导致无法解锁 避免进程提前退出导致无法结束 */
                res.closed = native.hasLimitMouseRangeWorker();
            }, ms + 80);
            return false;
        })(),
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
    };
    return res;
}
exports.setLimitMouseRange = setLimitMouseRange;
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
    const setLimitMouse = setLimitMouseRange(5000, 1, 1, 1, 500);
    await Sleep(2000);
    setLimitMouse.close();
    setLimitMouse.close();
    setLimitMouse.close();
    for (let index = 0; index < 100; index++) {
        setLimitMouse.close();
    }
    // hmc.Auto.mouseHook.on("mouse",()=>{});
    // hmc.Auto.mouseHook.start();
    // 模拟意外退出
    // process.exit(555);
})();
