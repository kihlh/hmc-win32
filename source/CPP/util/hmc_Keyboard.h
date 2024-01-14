#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_KEYBOARD_H
#define MODE_INTERNAL_INCLUDE_HMC_KEYBOARD_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <array>
#include <thread>
#include <winuser.h>
#include <shared_mutex>
#include <atomic>

namespace hmc_Keyboard // hmc_Keyboard 是个鼠标操作功能合集
{
    struct KeyboardEvent // 事件数据体
    {
        long long id;   // 事件id
        long keyCode;   // 键码
        DWORD time;     // 事件时间
        bool down;      // 按键是否被按下
        DWORD scanCode; // 执行的设备id
        DWORD flags;    // 扩展键标志
        KeyboardEvent()
        {
            id = 0;
            keyCode = 0;
            time = 0;
            down = 0;
            scanCode = 0;
            flags = 0;
        }

        bool is_valid();
        std::string to_json();
    };

    extern bool _is_Keyboard_Next_Hook;                         // 是否继续执行
    extern HHOOK _This_KeyboardHook;                            // 钩子句柄
    extern long long _This_Event_id;                            // 当前id
    extern std::vector<KeyboardEvent> _This_KeyboardEvent_List; // 鼠标按钮的事件容器(缓冲)  预扩容了256个
    extern DWORD _This_HookThreadID;                            // 正在执行hook线程

    extern DWORD get_ThreadId(std::thread::id thread_id);
    extern DWORD get_ThreadId();
    /**
     * @brief 添加一个低级hook 的工作空间(这里不是异步的)
     *
     * @return true
     * @return false
     */
    extern bool InitKeyboardEventHookWorker();

    /**
     * @brief 添加一个低级hook 的工作空间(这里不是异步的)
     *
     * @return true
     * @return false
     */
    extern bool initKeyboardEventHook();

    /**
     * @brief 将KeyboardEvent 格式化为文本json (utf8 string)
     *
     * @param event 事件体
     * @return json object
     */
    extern std::string getAllKeyboardEventJson();

    /**
     * @brief 判断当前是否正在检测鼠标变化
     *
     * @return true
     * @return false
     */
    extern bool isStartHookKeyboard();

    // 低级回调
    extern LRESULT CALLBACK WinApiLowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam);

    /**
     * @brief 结束并且释放hook线程以及hook函数
     *
     * @return true
     * @return false
     */
    extern bool gcHookKeyboard();

    /**
     * @brief 添加数据体
     *
     * @param input
     */
    extern void push_keyboard_data(KBDLLHOOKSTRUCT *input);

    /**
     * @brief 取出数据
     *
     */
    extern std::vector<KeyboardEvent> getAllKeyboardEvent();
}

#endif // MODE_INTERNAL_INCLUDE_HMC_KEYBOARD_Hv