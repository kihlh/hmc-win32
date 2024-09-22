import main = require("./index");
import util = require("./util");
const {ref} = util;

const HMC2 = main.native;


class HMC_MOUSE_CLASS {
    #fun: null | main.HMC2.HMC_MOUSE_CLASS = null;

    #initialize() {
        if (!this.#fun&&HMC2.native.HMC_MOUSE_CLASS) {
            this.#fun = HMC2.native.HMC_MOUSE_CLASS();
        }
    }
    
    constructor() { }

    initMouseEventHook() {
        this.#initialize();
        return this.#fun?.initMouseEventHook() || false;
    }

    isValidHookMouse() {
        this.#initialize();
        return this.#fun?.isValidHookMouse()|| false;
    }
    
    getMouseEventListJson() {
        this.#initialize();
        return this.#fun?.getMouseEventListJson() || false;
    }
    
    stopHookMouse() {
        this.#initialize();
        return this.#fun?.stopHookMouse() || false;
    }

    setLimitMouseRange(ms: number, x: number, y: number, right: number, bottom: number) {
        this.#initialize();
        return this.#fun?.setLimitMouseRange(ref.int(ms),ref.int(x),ref.int(y),ref.int(right),ref.int(bottom)) || false;
    }

    setShakeEventTime(ms: number) {
        this.#initialize();
        return this.#fun?.setShakeEventTime(ref.int(ms)) || false;
    }
    
    hasLimitMouseRangeWorker() {
        this.#initialize();
        return this.#fun?.hasLimitMouseRangeWorker()|| false;
    }

    stopLimitMouseRangeWorker() {
        this.#initialize();
        return this.#fun?.stopLimitMouseRangeWorker() || false;
    }

}

export const HmcMouseClass = new HMC_MOUSE_CLASS();

class HMC_KEYBOARD_CLASS {
    #fun: null | main.HMC2.HMC_KEYBOARD_CLASS = null;

    #initialize() {
        if (!this.#fun&&HMC2.native.HMC_KEYBOARD_CLASS) {
            this.#fun = HMC2.native.HMC_KEYBOARD_CLASS();
        }
    }
    
    constructor() { }

    initKeyboardEventHook() {
        this.#initialize();
        return this.#fun?.initKeyboardEventHook() || false;
    }

    isValidHookKeyboard() {
        this.#initialize();
        return this.#fun?.isValidHookKeyboard() || false;
    }
    
    getAllKeyboardEventJson() {
        this.#initialize();
        return JSON.parse(this.#fun?.getAllKeyboardEventJson()||"[]");
    }
    
    stopHookKeyboard() {
        this.#initialize();
        return this.#fun?.stopHookKeyboard()  || false;
    }

    hasKeysBasic() {
        this.#initialize();
        return this.#fun?.hasKeysBasic() || {
            "alt":false,
            "ctrl":false,
            "shift":false,
            "win":false
        };
    }

    hasKeyActivate(KeysEvent: number) {
        this.#initialize();
        return this.#fun?.hasKeyActivate(ref.int(KeysEvent)) || false;
    }

}

export const HmcKeyboardClass = new HMC_KEYBOARD_CLASS();




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

    if (ms > 30 * 1000 || ms < 30) {
        throw new Error("The range is only allowed from 31 milliseconds to 30 seconds (31ms-30000).")
    }

    HmcMouseClass.setLimitMouseRange(ms, x, y, right, bottom);


    const res = {
        ms, x, y, right, bottom,
        closed: (() => {
            setTimeout(() => {
                // !请注意此地方不能取消
                // 防止node提前退出 导致解锁失败(双保险)
                res.closed = HmcMouseClass.hasLimitMouseRangeWorker();
            }, ms + 80);
            return false;
        })() as boolean,
        /**
         * 停止本次
         * @returns 
         */
        close() {
            return HmcMouseClass.stopLimitMouseRangeWorker();
        },
        // 停止本次
        stop() {
            return this.close();
        },
        /**
         * 是否正在执行中
         * @returns 
         */
        has() {
            return !HmcMouseClass.hasLimitMouseRangeWorker();
        }

    }

    return res;
}
