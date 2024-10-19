import main = require("./index");
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
declare class Iohook_Keyboard {
    private _onlistenerCountList;
    private _oncelistenerCountList;
    private _Close;
    private _next_Sleep;
    private _hook_Task_id;
    constructor();
    once(eventName: "start" | "close", listener: () => void): this;
    once(eventName: "data", listener: (data: (`${number}|0` | `${number}|1`)[]) => void): this;
    once(eventName: "change", listener: (KeyboardPoint: main.HMC2_MODE.KeyboardEvent) => void): this;
    once(listener: (KeyboardPoint: main.HMC2_MODE.KeyboardEvent) => void): this;
    on(eventName: "start" | "close", listener: () => void): this;
    on(eventName: "data", listener: (data: main.HMC2_MODE.KeyboardEvent[]) => void): this;
    on(eventName: "change", listener: (KeyboardPoint: main.HMC2_MODE.KeyboardEvent) => void): this;
    on(listener: (KeyboardPoint: main.HMC2_MODE.KeyboardEvent) => void): this;
    /**
     * 设置于hmc 对接的刷新延迟毫秒数 数字越小读取越快但是性能消耗将会增加
     * @param Sleep 要求 10ms - 10,000
     * @default 50ms
     * @returns
     */
    setRefreshRate(Sleep?: number): boolean;
    /**
     * 开始
     * @returns
     */
    start(): boolean;
    /**
     * 挂起 并且不销毁已经绑定的函数 以及当前配置
     */
    suspend(): boolean;
    /**
     * 解除suspend的挂起状态
     */
    next(): boolean;
    /**
     * 判断当前的hook是否有效 有效返回线程id
     * @returns
     */
    isValidHook(): false | number;
    /**
     * 结束
     */
    close(): void;
    emit(eventName: "data", data: (main.HMC2_MODE.KeyboardEvent)[]): boolean;
    emit(eventName: "start" | "close"): boolean;
    emit(eventName: "change", KeyboardPoint: main.HMC2_MODE.KeyboardEvent): boolean;
    /**
     * 关闭监听
     * @param eventName
     * @param data
     * @returns
     */
    off(eventName: "start" | "close" | "change" | "data", treatmentMode: "on" | "once" | Function, data?: Function): boolean;
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
export declare const keyboardHook: Iohook_Keyboard;
export {};
