#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_AUTOMATION_H
#define MODE_INTERNAL_INCLUDE_HMC_AUTOMATION_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <array>
#include <thread>
#include <winuser.h>
#include <shared_mutex>
#include <atomic>
#include <random>
#include <map>
#include <optional>
#include <functional>

namespace hmc_Keyboard // hmc_Keyboard 是个鼠标操作功能合集
{

    class keyboardHook
    {
    public:
        struct KeyboardEvent // 事件数据体
        {
            long long id;   // 事件id
            long keyCode;   // 键码
            DWORD time;     // 事件时间
            bool down;      // 按键是否被按下
            DWORD scanCode; // 执行的设备id
            DWORD flags;    // 扩展键标志
            // 开辟内存
            KeyboardEvent();
            // 判断内容是否有效
            bool is_valid();
            // 转为json
            std::string to_json();
        };

        /**
         * @brief 添加一个低级hook 的工作空间(异步的)
         * @return true
         * @return false
         */
        static bool initKeyboardEventHook();

        /**
         * @brief 添加一个低级hook 的工作空间(异步的)
         * @return true
         * @return false
         */
        static bool initKeyboardEventHook(std::function<bool(KeyboardEvent event)> callback);

        /**
         * @brief 将KeyboardEvent 格式化为文本json (utf8 string)
         *
         * @param event 事件体
         * @return json object
         */
        static std::string getAllKeyboardEventJson();

        /**
         * @brief 判断当前是否正在检测鼠标变化
         *
         * @return true
         * @return false
         */
        static bool isValidHookKeyboard();

        /**
         * @brief 取出数据
         *
         */
        static std::vector<KeyboardEvent> getAllKeyboardEvent();

        /**
         * @brief 结束并且释放hook线程以及hook函数
         *
         * @return true
         * @return false
         */
        static bool stopHookKeyboard();

        /**
         * @brief 获取当前hook线程的线程id
         *
         * @return DWORD
         */
        static DWORD getThreadId();

    private:
        static bool GpAllowHookToken;                                                            // 是否继续执行
        static HHOOK GpHookHandle;                                                               // 钩子句柄
        static long long GpEventNextID;                                                          // 当前id
        static std::vector<KeyboardEvent> GpEventSessionList;                                    // 鼠标按钮的事件容器(缓冲)  预扩容了256个
        static DWORD GpWorkerThreadID;                                                           // 正在执行hook线程
        static std::shared_mutex GpStoreSharedMutex;                                             // 存储的互斥体
        static std::optional<std::function<bool(KeyboardEvent event)>> GpEventSessionToCallBack; // 当此值为存在的时候将不会触发存储 但是会执行回调

        /**
         * @brief 添加一个低级hook 的工作空间(这里不是异步的)
         *
         * @return true
         * @return false
         */
        static bool InitKeyboardEventHookWorker();

        /**
         * @brief 低级回调
         *
         * @param nCode
         * @param wParam
         * @param lParam
         * @return LRESULT
         */
        static LRESULT CALLBACK WinApiLowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam);

        /**
         * @brief 添加数据体
         *
         * @param input
         */
        static void push_keyboard_data(KBDLLHOOKSTRUCT *input);

        /**
         * @brief 重置数据
         *
         */
        static void initializeBasicValues();
    };

    // 键盘四大功能键的状态
    struct chHasKeysBasic
    {
        bool shift; // shift 被按下
        bool alt;   // alt 被按下
        bool ctrl;  // ctrl 被按下
        bool win;   // win 被按下
    };

    /**
     * @brief 判断四大键盘功能键的状态
     * 
     * @return chHasKeysBasic 
     */
    extern chHasKeysBasic hasKeysBasic();
    
    typedef hmc_Keyboard::keyboardHook::KeyboardEvent chKeyboardHookEvent;

}

namespace hmc_mouse // hmc_mouse 是个鼠标操作功能合集
{

    struct chMouseBasic
    {
        bool middle; // 鼠标中键被按下
        bool right;  // 鼠标右键被按下
        bool left;   // 鼠标左键被按下
    };

    /**
     * @brief 判断基础的鼠标按钮是否被按下
     *
     * @return chMouseBasic
     */
    extern chMouseBasic hasMouseBasic();

    /**
     * @brief 获取当前鼠标坐标
     *
     * @return json {"x":null|number,"y":null|number}
     */
    extern std::string getCursorPosJsonA();

    /**
     * @brief 获取鼠标之前的64个坐标位置
     *
     * @return vector<MOUSEMOVEPOINT>
     */
    extern std::vector<MOUSEMOVEPOINT> getMouseMovePoints();

    /**
     * @brief 获取鼠标之前的64个坐标位置 并转为json [ascii]
     * @jsonp  json { "x": number | null, "y": number | null,  "time": number | null,  "dwExtraInfo": number | null   }
     * @return string
     */
    extern std::string getMouseMovePointsJsonA();

    /**
     * @brief 获取最后一次输入事件的时间 （键盘/鼠标）
     *
     * @return DWORD
     */
    extern DWORD getLastInputTime();

    class MouseHook
    {
    public:
        struct MouseEvent // 事件数据体
        {
            long long id;    // 事件id
            long button;     // 按钮是哪个
            long wheelDelta; // 滚轮数据 如果向上则为正值 向下则为负值
            bool buttonDown; // 按钮是否按下状态的  如果滚轮则为向上
            DWORD time;      // 事件时间
            long x;          // 坐标 左到右边
            long y;          // 坐标 顶部到底部
            // 开辟内存
            MouseEvent();
            // 判断内容是否有效
            bool is_valid();
            // 转到json
            std::string to_json();
        };

        /**
         * @brief 判断当前是否正在检测鼠标变化
         *
         * @return true
         * @return false
         */
        static bool isValidHookMouse();

        /**
         * @brief 结束监听
         *
         */
        static bool stopHookMouse();

        /**
         * @brief 当前的所有事件数据并清空内存块
         *
         * @return 数据体copy
         */
        static std::vector<MouseEvent> getMouseEvent();

        /**
         * @brief 当前的所有事件数据并清空内存块
         *
         * @return json Array <MouseEventJson>
         */
        static std::string getMouseEventListJsonA();
        /**
         * @brief 添加一个低级鼠标hook 的工作空间(异步的)
         *
         */
        static bool initMouseEventHook();
        /**
         * @brief 添加一个低级鼠标hook 的工作空间(异步的)
         *
         */
        static bool initMouseEventHook(std::function<bool(MouseEvent event)> callback);

        /**
         * @brief 设置鼠标位置抖动时间(本次有效) [init以后才能调用]
         * 
         * @param time 
         * @return true 
         * @return false 
         */
        static void setShakeEventTime(long time);

        /**
         * @brief 获取当前hook线程的线程id
         *
         * @return DWORD
         */
        static DWORD getThreadId();

    private:
        static std::shared_mutex GpMouseStoreSharedMutex;       // 存储的互斥体
        static bool GpMouseAllowHookToken;                      // 是否继续执行
        static DWORD GpMouseTheEventTime;                       // 上次输入体的时间
        static HHOOK GpHookMouseHandle;                         // 钩子句柄
        static DWORD GpMouseShakeEventTime;                     // 消除抖动的ms
        static long long GpMouseEventNextID;                    // 当前id
        static std::vector<MouseEvent> GpMouseEventSessionList; // 鼠标按钮的事件容器(缓冲)  预扩容了256个
        static MouseEvent GpMouseTempEventBuffer;               // 预开劈缓冲区 每次鼠标回调不会动态创建 而是把此变量作为temp
        static DWORD GpMouseWorkerThreadID;                     // 正在执行hook线程
        static std::optional<std::function<bool(MouseEvent event)>> GpEventSessionToCallBack; // 当此值为存在的时候将不会触发存储 但是会执行回调

        /**
         * @brief 推入事件容器内
         *
         * @param event
         */
        static void push_Mouse_Event(MouseEvent event);

        /**
         * @brief winapi mouse 低级hook回调函数
         *
         * @param nCode
         * @param wParam
         * @param lParam
         * @return LRESULT
         */
        static LRESULT CALLBACK WinApiCallBackMouseHook(int nCode, WPARAM wParam, LPARAM lParam);

        /**
         * @brief 清空每次获取时候的临时内存
         *
         */
        static void gc_next_temp();

        /**
         * @brief 重置数据
         *
         */
        static void initializeBasicValues();

        /**
         * @brief 初始化一个 低级的键盘hook函数
         *
         */
        static void InitHookMouse();
    };

    class LimitMouseRange
    {

        /**
         * @brief 限制鼠标可移动范围
         *
         * @param ms 本次限制的时间
         * @param x 限制左边初始化点的位置
         * @param y 限制顶部初始化点的位置
         * @param right 允许的范围(左边到右边部)
         * @param bottom 允许光标移动的范围(顶到底部)
         * @return 是否成功
         */
        static bool setLimitMouseRange(long ms, long x, long y, long right, long bottom);
        // 提前结束限制鼠标可移动范围 一旦调用则立即解锁 返回的布尔是解锁线程是否成功
        static bool hasLimitMouseRange_worker();
        // 是否 正在调用着 限制鼠标可移动范围的线程
        static bool stopLimitMouseRange_worker();

    private:
        static std::unique_ptr<std::thread> GpWorkerThreadHandlePtr; // 限制鼠标可移动范围 的句柄
        static bool GpUnMouseLockWorker;                             // 本次的鼠标光标是否解锁了 当进程奔溃或者退出时候将访问此布尔 进行灾难性解锁
        // 异步工作空间
        static void setLimitMouseRange_async_worker(long ms, long x, long y, long right, long bottom);
    };

    typedef MouseHook::MouseEvent chMouseHookEvent;
}

namespace hmc_automation_util
{

    /**
     * @brief 线程id转数字
     *
     * @param thread_id
     * @return DWORD
     */
    extern DWORD toThreadId(std::thread::id thread_id);

    /**
     * @brief mouse_event 参数文本互转
     *
     * @param event
     * @return std::wstring
     */
    extern std::wstring mouseEventName(UINT event);

    /**
     * @brief mouse_event 参数文本互转
     *
     * @param event
     * @return UINT
     */
    extern UINT mouseEventName(std::wstring event);

    /**
     * @brief 随机数
     *
     * @param min 最小
     * @param max 最大
     * @return int
     */
    extern int randomInt(int min, int max);

    /**
     * @brief 合成键击、鼠标动作和按钮单击。
     *
     * @param cInputs pInputs 数组中的结构数。
     * @param pInputs INPUT 结构的数组。 每个结构都表示要插入键盘或鼠标输入流的事件
     * @param cbSize INPUT 结构的大小（以字节为单位）。 如果 cbSize 不是 INPUT 结构的大小，则函数将失败
     * @return UINT
     */
    extern UINT GpSendInput(UINT cInputs, LPINPUT pInputs, int cbSize);

    /**
     * @brief 判断指定的值是否被按下
     *
     * @param nVirtKey
     * @return true
     * @return false
     */
    extern bool hasKeyActivate(int nVirtKey);

    /**
     * @brief 相对符合w3c标准的 `Key`
     * @link https://developer.mozilla.org/zh-CN/docs/Web/API/KeyboardEvent/code
     *
     * @param input
     * @return std::string
     */
    extern std::string GpMapVirtualKey(std::uint8_t input);

    /**
     * @brief 相对符合w3c标准的 `Code`
     * @link https://developer.mozilla.org/zh-CN/docs/Web/API/KeyboardEvent/code
     *
     * @param input
     * @return std::string
     */
    extern std::string GpMapVirtualCode(std::uint8_t input);

}

#endif // MODE_INTERNAL_INCLUDE_HMC_AUTOMATION_H