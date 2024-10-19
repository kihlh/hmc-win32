import type { VK_code, VK_key, VK_keyCode, VK_VirtualKey } from "./vkKey";
import { KeyboardcodeEmenList } from "./vkKey";
import { HMC } from "./HMC";
import { ref } from "./util";
import { Native } from "./Native";


class HMC_MOUSE_CLASS {
    constructor() { }

    initMouseEventHook() {
        return Native.HMC_MOUSE_CLASS?.initMouseEventHook() || false;
    }

    isValidHookMouse() {
        return Native.HMC_MOUSE_CLASS?.isValidHookMouse() || false;
    }

    getMouseEventListJson() {
        return Native.HMC_MOUSE_CLASS?.getMouseEventListJson() || false;
    }

    stopHookMouse() {
        return Native.HMC_MOUSE_CLASS?.stopHookMouse() || false;
    }

    setLimitMouseRange(ms: number, x: number, y: number, right: number, bottom: number) {
        return Native.HMC_MOUSE_CLASS?.setLimitMouseRange(ref.int(ms), ref.int(x), ref.int(y), ref.int(right), ref.int(bottom)) || false;
    }

    setShakeEventTime(ms: number) {
        return Native.HMC_MOUSE_CLASS?.setShakeEventTime(ref.int(ms)) || false;
    }

    hasLimitMouseRangeWorker() {
        return Native.HMC_MOUSE_CLASS?.hasLimitMouseRangeWorker() || false;
    }

    stopLimitMouseRangeWorker() {
        return Native.HMC_MOUSE_CLASS?.stopLimitMouseRangeWorker() || false;
    }

}

const HmcMouseClass = new HMC_MOUSE_CLASS();

class HMC_KEYBOARD_CLASS {
    constructor() { }

    initKeyboardEventHook() {
        return Native.HMC_KEYBOARD_CLASS?.initKeyboardEventHook() || false;
    }

    isValidHookKeyboard() {
        return Native.HMC_KEYBOARD_CLASS?.isValidHookKeyboard() || false;
    }

    getAllKeyboardEventJson(): HMC.KeyboardEvent[] {
        return JSON.parse(Native.HMC_KEYBOARD_CLASS?.getAllKeyboardEventJson() || "[]");
    }

    stopHookKeyboard() {
        return Native.HMC_KEYBOARD_CLASS?.stopHookKeyboard() || false;
    }

    hasKeysBasic() {
        return Native.HMC_KEYBOARD_CLASS?.hasKeysBasic() || {
            "alt": false,
            "ctrl": false,
            "shift": false,
            "win": false
        };
    }

    hasKeyActivate(KeysEvent: number) {
        return Native.HMC_KEYBOARD_CLASS?.hasKeyActivate(ref.int(KeysEvent)) || false;
    }

}

const HmcKeyboardClass = new HMC_KEYBOARD_CLASS();


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


class Keyboard {
    /**
     * 是否按下了shift
     */
    get shiftKey() {
        return HmcKeyboardClass.hasKeyActivate(0x10) || HmcKeyboardClass.hasKeyActivate(0xA1) || HmcKeyboardClass.hasKeyActivate(0xA0);
    }
    /***
     * 是否按下了alt
     */
    get altKey() {
        return HmcKeyboardClass.hasKeyActivate(0x12) || HmcKeyboardClass.hasKeyActivate(0xA4) || HmcKeyboardClass.hasKeyActivate(0xA5);
    }
    /***
     * 是否按下了ctrl
     */
    get ctrlKey() {
        return HmcKeyboardClass.hasKeyActivate(0x11);
    }
    /***
     * 是否按下了win
     */
    get winKey() {
        return HmcKeyboardClass.hasKeyActivate(0x5B) || HmcKeyboardClass.hasKeyActivate(0x5C);
    }

    readonly vKey: VK_VirtualKey;
    readonly key: VK_key;
    readonly code: VK_code;

    /**
     * 键值代码
     */
    readonly keyCode: VK_keyCode;

    /**事件id (每次结束时次记) */
    readonly id: number;

    /**事件时间 */
    readonly time: number;

    /**是否按下 */
    readonly down: boolean;

    /**扩展键标志 */
    readonly flags: number;

    /**执行的设备id */
    readonly scanCode: number;

    /**映射代码 例如 A 0 1 */
    readonly KeyName: string;

    /**映射代码 例如 KeyE , KeyA */
    readonly KeyNameCode: string;

    /**是否被按下 (旧版兼容) */
    readonly isDown: boolean;

    constructor(env: HMC.KeyboardEvent) {

        this.id = Number(env.id);
        this.time = Number(env.time);
        this.down = Boolean(env.down);
        this.flags = Number(env.flags);
        this.keyCode = Number(env.keyCode);
        this.scanCode = Number(env.scanCode);
        this.KeyName = String(env.key);
        this.KeyNameCode = String(env.code);


        this.vKey = Number(env.keyCode);
        this.isDown = env.down ? true : false;

        let KeyboardcodeEmen = KeyboardcodeEmenList.get(this.vKey);
        if (!KeyboardcodeEmen) {
            KeyboardcodeEmen = ["unknown", null, this.vKey, 0];
            // throw new Error("key Value Data That Does Not Exist !");
        }

        const [VK_key, VK_code, VK_keyCode, VK_VirtualKey, VK_Nickname] = KeyboardcodeEmen;

        this.keyCode = this.keyCode || VK_keyCode;
        this.key = VK_key || this.KeyName;
        this.code = VK_code || VK_key || this.KeyNameCode;

    }

}


class Iohook_Keyboard {
    private _onlistenerCountList = {
        close: [] as Function[],
        data: [] as Function[],
        start: [] as Function[],
        change: [] as Function[],
    };
    private _oncelistenerCountList = {
        close: [] as Function[],
        data: [] as Function[],
        start: [] as Function[],
        change: [] as Function[],
    };
    private _Close = false;
    private _next_Sleep = 50;
    private _hook_Task_id = 0;
    constructor() {

    }
    once(eventName: "start" | "close", listener: () => void): this;
    once(eventName: "data", listener: (data: (`${number}|0` | `${number}|1`)[]) => void): this;
    once(eventName: "change", listener: (KeyboardPoint: HMC.KeyboardEvent) => void): this;
    once(listener: (KeyboardPoint: HMC.KeyboardEvent) => void): this;
    once(eventName: unknown, listener?: unknown) {
        if (typeof eventName === "function") {
            listener = eventName;
            eventName = "change"
        }
        if (typeof listener !== "function") return keyboardHook;
        keyboardHook._oncelistenerCountList[eventName as "data"].push(listener);
        return keyboardHook;
    };
    on(eventName: "start" | "close", listener: () => void): this;
    on(eventName: "data", listener: (data: HMC.KeyboardEvent[]) => void): this;
    on(eventName: "change", listener: (KeyboardPoint: HMC.KeyboardEvent) => void): this;
    on(listener: (KeyboardPoint: HMC.KeyboardEvent) => void): this;
    on(eventName: unknown, listener?: unknown) {
        if (typeof eventName === "function") {
            listener = eventName;
            eventName = "change"
        }
        if (typeof listener !== "function") return keyboardHook;
        keyboardHook._onlistenerCountList[eventName as "data"].push(listener);
        return keyboardHook;
    };

    /**
     * 设置于hmc 对接的刷新延迟毫秒数 数字越小读取越快但是性能消耗将会增加
     * @param Sleep 要求 10ms - 10,000
     * @default 50ms
     * @returns 
     */
    setRefreshRate(Sleep = 50) {
        Sleep = Number(Sleep);

        if (isNaN(Sleep)) return false;

        // 小于10会导致访问过快照成性能消耗过大
        if (Sleep < 10) {
            return false;
        }
        // 太慢了会导致内存过大 如果内存超出了缓冲区预开辟内存大小将会变成动态开辟内存 影响单次键鼠响应的速度
        if (Sleep > 10000) {
            return false;
        }

        this._next_Sleep = Sleep;
        return true;
    }

    /**
     * 开始
     * @returns 
     */
    start() {

        let start = HmcKeyboardClass.isValidHookKeyboard();
        if (start != false) throw new Error("the Task Has Started.");

        const _hook_Task_id = this._hook_Task_id + 1;

        start = HmcKeyboardClass.initKeyboardEventHook();
        if (!start) {
            return false;
        }

        this._Close = false;

        keyboardHook.emit("start");
        let emit_getKeyboardNextSession = () => {

            let getKeyboardNextSession = HmcKeyboardClass.getAllKeyboardEventJson();
            if (getKeyboardNextSession?.length) keyboardHook.emit("data", getKeyboardNextSession);

            if (getKeyboardNextSession)
                for (let index = 0; index < getKeyboardNextSession.length; index++) {
                    const KeyboardNextSession = getKeyboardNextSession[index];
                    const KeyboardPoint = new Keyboard(KeyboardNextSession);
                    keyboardHook.emit("change", KeyboardPoint);
                }

        }

        this._hook_Task_id = _hook_Task_id;

        (async () => {
            while (true) {
                if (this._hook_Task_id != _hook_Task_id || keyboardHook._Close) return;
                await ref.Sleep(this._next_Sleep);
                emit_getKeyboardNextSession();
            }
        })();

        return start;
    }

    /**
     * 挂起 并且不销毁已经绑定的函数 以及当前配置
     */
    suspend() {
        return HmcKeyboardClass.stopHookKeyboard();
    }

    /**
     * 解除suspend的挂起状态
     */
    next() {
        const isValidHookKeyboard = HmcKeyboardClass.isValidHookKeyboard();
        if (isValidHookKeyboard) {
            HmcKeyboardClass.stopHookKeyboard();
        }
        return HmcKeyboardClass.initKeyboardEventHook();
    }

    /**
     * 判断当前的hook是否有效 有效返回线程id
     * @returns 
     */
    isValidHook(): false | number {

        let isValidHookKeyboard = HmcKeyboardClass.isValidHookKeyboard();

        if (this._Close && isValidHookKeyboard) {
            HmcKeyboardClass.stopHookKeyboard();
            isValidHookKeyboard = HmcKeyboardClass.isValidHookKeyboard();
        }

        return isValidHookKeyboard;
    }

    /**
     * 结束
     */
    close() {
        HmcKeyboardClass.stopHookKeyboard();

        keyboardHook.emit("close");
        keyboardHook._Close = true;

        keyboardHook._oncelistenerCountList.close.length = 0;
        keyboardHook._oncelistenerCountList.data.length = 0;
        keyboardHook._oncelistenerCountList.change.length = 0;
        keyboardHook._oncelistenerCountList.start.length = 0;

        keyboardHook._onlistenerCountList.close.length = 0;
        keyboardHook._onlistenerCountList.data.length = 0;
        keyboardHook._onlistenerCountList.change.length = 0;
        keyboardHook._onlistenerCountList.start.length = 0;
    }

    emit(eventName: "data", data: (HMC.KeyboardEvent)[]): boolean;
    emit(eventName: "start" | "close"): boolean;
    emit(eventName: "change", KeyboardPoint: HMC.KeyboardEvent): boolean;
    emit(eventName: unknown, ...data: unknown[]) {
        const emitFunList = keyboardHook._onlistenerCountList[eventName as "data"];
        const onceEmitFunList = keyboardHook._oncelistenerCountList[eventName as "data"];
        for (let index = 0; index < emitFunList.length; index++) {
            const emitFun = emitFunList[index];
            emitFun.apply(keyboardHook, data);
        };
        for (let index = 0; index < onceEmitFunList.length; index++) {
            const emitFun = onceEmitFunList[index];
            emitFun.apply(keyboardHook, data);
        };
        onceEmitFunList.length = 0;
        return emitFunList.length ? true : false;
    }

    /**
     * 关闭监听
     * @param eventName 
     * @param data 
     * @returns 
     */
    off(eventName: "start" | "close" | "change" | "data", treatmentMode: "on" | "once" | Function, data?: Function) {
        switch (treatmentMode) {
            case "on": {
                if (data) {
                    const listenerCountList = keyboardHook._onlistenerCountList[eventName];
                    if (listenerCountList.indexOf(data)) {
                        return keyboardHook._onlistenerCountList[eventName].splice(listenerCountList.indexOf(data), 1) ? true : false;
                    }
                } else {
                    keyboardHook._onlistenerCountList[eventName].length = 0;
                    return !keyboardHook._onlistenerCountList[eventName].length
                }
                break;
            }
            case "once": {
                if (data) {
                    const listenerCountList = keyboardHook._oncelistenerCountList[eventName];
                    if (listenerCountList.indexOf(data)) {
                        return keyboardHook._oncelistenerCountList[eventName].splice(listenerCountList.indexOf(data), 1) ? true : false;
                    }
                } else {
                    keyboardHook._oncelistenerCountList[eventName].length = 0;
                    return !keyboardHook._oncelistenerCountList[eventName].length
                }
                break;
            }
        }
        return false;
    }
}

/**
 * 设置一个键盘低级变化监听
 * @example ```javascript 
  // 添加处理函数
  hmc.Auto.keyboardHook.on("change",function(env){
     console.log(env.key,env.isDown,env);
  });
  // log => ctrl , true {...env}

  // 启动
  hmc.Auto.keyboardHook.start();

  // 暂停 / 开始
  hmc.Auto.keyboardHook.suspend()&&console.log("hook -> stop");

  hmc.Sleep(5000).then(()=>hmc.Auto.keyboardHook.next()&&console.log("hook -> next"));
   
  // close
  hmc.Sleep(15000).then(hmc.Auto.keyboardHook.close);

 *  ```
 * 
 */
export const keyboardHook = new Iohook_Keyboard();
