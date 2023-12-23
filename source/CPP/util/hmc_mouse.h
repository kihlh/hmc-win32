#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_MOUSE_H
#define MODE_INTERNAL_INCLUDE_HMC_MOUSE_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <array>
#include <thread>
#include <winuser.h>

using namespace std;


namespace hmc_mouse // hmc_mouse 是个鼠标操作功能合集
{
	struct MouseEvent // 事件数据体
	{
		long long id;    // 事件id
		long button;     // 按钮是哪个
		long wheelDelta; // 滚轮数据 如果向上则为正值 向下则为负值
		bool buttonDown; // 按钮是否按下状态的  如果滚轮则为向上
		DWORD time;      // 事件时间
		long x;          // 坐标 左到右边
		long y;          // 坐标 顶部到底部
	};

	extern bool _is_Mouse_Next_Hook;                 // 是否继续执行
	extern DWORD _This_Event_Time;                   // 上次输入体的时间
	extern HHOOK _This_MouseHook;                    // 钩子句柄
	extern DWORD shake_Event_time;                   // 消除抖动的ms
	extern long long _This_Event_id;                 // 当前id
	extern vector<MouseEvent> _This_MouseEvent_List; // 鼠标按钮的事件容器(缓冲)  预扩容了256个
	extern MouseEvent _This_Temp_MouseEvent;         // 预开劈缓冲区 每次鼠标回调不会动态创建 而是把此变量作为temp
	extern std::thread* __LimitMouseRange_worker;    // 限制鼠标可移动范围 的句柄

	/**
	 * @brief 将MouseEvent 格式化为文本json
	 *
	 * @param event 事件体
	 * @return json object
	 */
	extern string MouseEventJsonA(MouseEvent event);

	/**
	 * @brief 判断当前是否正在检测鼠标变化
	 *
	 * @return true
	 * @return false
	 */
	extern bool isStartHookMouse();

	/**
	 * @brief 推入事件容器内
	 *
	 * @param event
	 */
	extern void push_Mouse_Event(MouseEvent event);

	/**
	 * @brief winapi mouse 低级hook回调函数
	 *
	 * @param nCode
	 * @param wParam
	 * @param lParam
	 * @return LRESULT
	 */
	extern LRESULT CALLBACK WinApiCallBackMouseHook(int nCode, WPARAM wParam, LPARAM lParam);

	/**
	 * @brief 初始化一个 低级的键盘hook函数
	 *
	 */
	extern void InitHookMouse();

	/**
	 * @brief 结束监听
	 *
	 */
	extern void StopHookMouse();

	/**
	 * @brief 当前的所有事件数据并清空内存块
	 *
	 * @return 数据体copy
	 */
	extern vector<MouseEvent> getMouseEvent();

	/**
	 * @brief 当前的所有事件数据并清空内存块
	 *
	 * @return json Array <MouseEventJson>
	 */
	extern string getMouseEventListJsonA();

	/**
	 * @brief 获取当前鼠标坐标
	 *
	 * @return json {"x":null|number,"y":null|number}
	 */
	extern string getCursorPosJsonA();

	/**
	 * @brief 获取鼠标之前的64个坐标位置
	 *
	 * @return vector<MOUSEMOVEPOINT>
	 */
	extern vector<MOUSEMOVEPOINT> getMouseMovePoints();

	/**
	 * @brief 获取鼠标之前的64个坐标位置 并转为json
	 * @jsonp  json { "x": number | null, "y": number | null,  "time": number | null,  "dwExtraInfo": number | null   }
	 * @return string
	 */
	extern string getMouseMovePointsJsonA();

	/**
	 * @brief 获取最后一次输入事件的时间 （键盘/鼠标）
	 *
	 * @return DWORD
	 */
	extern DWORD getLastInputTime();

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
	extern bool setLimitMouseRange(long ms, long x, long y, long right = 1, long bottom = 1);
	// 提前结束限制鼠标可移动范围 一旦调用则立即解锁 返回的布尔是解锁线程是否成功 
	extern bool stopLimitMouseRange_worker();
	// 是否 正在调用着 限制鼠标可移动范围的线程
	extern bool hasLimitMouseRange_worker();
}

#endif // MODE_INTERNAL_INCLUDE_HMC_MOUSE_H