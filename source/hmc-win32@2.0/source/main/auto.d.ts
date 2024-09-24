import main = require("./index");
declare class HMC_MOUSE_CLASS {
    #private;
    constructor();
    initMouseEventHook(): boolean;
    isValidHookMouse(): boolean;
    getMouseEventListJson(): string | false;
    stopHookMouse(): boolean;
    setLimitMouseRange(ms: number, x: number, y: number, right: number, bottom: number): boolean;
    setShakeEventTime(ms: number): boolean;
    hasLimitMouseRangeWorker(): boolean;
    stopLimitMouseRangeWorker(): boolean;
}
export declare const HmcMouseClass: HMC_MOUSE_CLASS;
declare class HMC_KEYBOARD_CLASS {
    #private;
    constructor();
    initKeyboardEventHook(): boolean;
    isValidHookKeyboard(): boolean;
    getAllKeyboardEventJson(): any;
    stopHookKeyboard(): boolean;
    hasKeysBasic(): main.HMC2_MODE.BASIC_KEYS;
    hasKeyActivate(KeysEvent: number): boolean;
}
export declare const HmcKeyboardClass: HMC_KEYBOARD_CLASS;
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
export declare function setLimitMouseRange(ms: number, x: number, y: number, right?: number, bottom?: number): {
    ms: number;
    x: number;
    y: number;
    right: number;
    bottom: number;
    closed: boolean;
    /**
     * 停止本次
     * @returns
     */
    close(): boolean;
    stop(): boolean;
    /**
     * 是否正在执行中
     * @returns
     */
    has(): boolean;
};
export {};
