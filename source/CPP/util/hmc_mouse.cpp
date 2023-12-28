#include "./hmc_mouse.h"

namespace hmc_mouse // 初始化容器
{
	bool _is_Mouse_Next_Hook = false;
	DWORD _This_Event_Time = 0;
	HHOOK _This_MouseHook = NULL;
	DWORD shake_Event_time = 35;
	long long _This_Event_id = 0;
	vector<MouseEvent> _This_MouseEvent_List = {};
	MouseEvent _This_Temp_MouseEvent = { 0 };
	std::unique_ptr<thread> __LimitMouseRange_worker = nullptr;
	bool _is_un_Mouse_Lock_worker = true;
}

void hmc_mouse::__setLimitMouseRange_async_worker(long ms, long x, long y, long right, long bottom)
{
	_is_un_Mouse_Lock_worker = false;

	// 函数正常退出时候的回调 如果没有正常退出则在主函数的 hmc_gc_func 释放 进行灾难性解锁
	std::shared_ptr<void> _shared_free_handle(nullptr, [&](void*)
		{
			ClipCursor(NULL);  //释放 
			_is_un_Mouse_Lock_worker = true;
			stopLimitMouseRange_worker(); 
		});

	RECT rect = { 0 };

	// 左上角
	rect.top = x;  // 上
	rect.left = y; // 左

	// 右下角
	rect.bottom = rect.top + bottom; // 底
	rect.right = rect.left + right;	// 右

	ClipCursor(&rect);

	// Sleep(ms);
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	ClipCursor(NULL); // 释放
}

bool hmc_mouse::setLimitMouseRange(long ms, long x, long y, long right, long bottom)
{

	// 已经存在 不能创建 超出30秒 小于30ms  直接拒绝创建
	if (hasLimitMouseRange_worker() || !_is_un_Mouse_Lock_worker || ms < 29 || ms > 1000 * 30 - 1)
	{
		return false;
	}


	// 创建处理的函数
	__LimitMouseRange_worker.reset(new std::thread(__setLimitMouseRange_async_worker, ms, x, y, right, bottom));

	return false;
}

bool hmc_mouse::hasLimitMouseRange_worker()
{

	// 已经存在 线程正常
	if (__LimitMouseRange_worker && __LimitMouseRange_worker->joinable())
	{
		return true;
	}

	// 已经存在 线程无效
	if (__LimitMouseRange_worker)
	{
		__LimitMouseRange_worker.release();
	}

	return false;
}

bool hmc_mouse::stopLimitMouseRange_worker()
{

	bool stop_cursor = ClipCursor(NULL);

	_is_un_Mouse_Lock_worker = true;

	if (!__LimitMouseRange_worker || !__LimitMouseRange_worker->joinable())
	{
		__LimitMouseRange_worker.release();
		return true;
	}

	DWORD threadId = GetThreadId(__LimitMouseRange_worker->native_handle());

	if (threadId <= 0)
	{
		return true;
	}

	for (size_t i = 0; i < 5; i++)
	{
		if (PostThreadMessage(threadId, WM_QUIT, NULL, NULL))
	{
		__LimitMouseRange_worker.release();
		return stop_cursor;
	}
	}
	
		return false;
}

string hmc_mouse::getCursorPosJsonA()
{
	POINT cursorPos = { 0 };

	if (::GetCursorPos(&cursorPos))
	{
		int x = cursorPos.x;
		int y = cursorPos.y;
		string res = string(R"({"x":)");
		res.append(to_string(x));
		res.append(string(R"(,"y":)"));
		res.append(to_string(x));
		res.append("}");
		return res;
	}

	return string(R"({"x":null,"y":null})");
}

vector<MOUSEMOVEPOINT> hmc_mouse::getMouseMovePoints()
{
	vector<MOUSEMOVEPOINT> results;

	// 预算出 计算方式 因为有可能数据是负数或者是不规整屏幕

	int nVirtualWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int nVirtualHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	int nVirtualLeft = GetSystemMetrics(SM_XVIRTUALSCREEN);
	int nVirtualTop = GetSystemMetrics(SM_YVIRTUALSCREEN);

	// 当前的鼠标位置
	POINT currentMousePosition = { 0 };
	GetCursorPos(&currentMousePosition);
	// 放置鼠标位置的容器
	MOUSEMOVEPOINT mousePositionContainer = { 0 };
	mousePositionContainer.x = currentMousePosition.x;
	mousePositionContainer.y = currentMousePosition.y;

	// 微软规定只会返回的最大数据为64
	const DWORD dwMaxPoints = 64;
	// 鼠标轨迹列表
	MOUSEMOVEPOINT mobileProgressList[dwMaxPoints] = { 0 };
	const DWORD dwMode = GMMP_USE_DISPLAY_POINTS;
	// 获取全部的 鼠标轨迹 并返回轨迹数量
	const int PointsLength = ::GetMouseMovePointsEx(sizeof(mousePositionContainer), &mousePositionContainer, mobileProgressList, dwMaxPoints, dwMode);

	if (PointsLength < 0)
	{
		return results;
	}

	// 处理多屏幕数据
	for (int i = PointsLength - 1; i >= 0; i--)
	{
		auto& mp = mobileProgressList[i];

		switch (dwMode)
		{
			// 使用显示分辨率检索点。
		case GMMP_USE_DISPLAY_POINTS:
		{
			if (mp.x >= 0x8000)
				mp.x -= 0x10000;
			if (mp.y >= 0x8000)
				mp.y -= 0x10000;
			break;
		}
		// 检索高分辨率点
		case GMMP_USE_HIGH_RESOLUTION_POINTS:
		{
			mp.x = ((mp.x * (nVirtualWidth - 1)) - (nVirtualLeft * 65536)) / nVirtualWidth;
			mp.y = ((mp.y * (nVirtualHeight - 1)) - (nVirtualTop * 65536)) / nVirtualHeight;
			break;
		}
		}

		results.push_back(MOUSEMOVEPOINT{ mp.x, mp.y, mp.time, mp.dwExtraInfo });
	}

	return results;
}

string hmc_mouse::getMouseMovePointsJsonA()
{
	string result = "[";
	auto data_list = getMouseMovePoints();
	size_t leng = data_list.size();

	for (size_t i = 0; i < leng; i++)
	{
		auto& data = data_list[i];
		string item_data = string(R"({"x":{x},"y":{y},"time":{time},"dwExtraInfo":{dwExtraInfo}})");
		item_data.replace(item_data.find("{x}"), sizeof("{x}") - 1, to_string(data.x));
		item_data.replace(item_data.find("{y}"), sizeof("{y}") - 1, to_string(data.y));
		item_data.replace(item_data.find("{time}"), sizeof("{time}") - 1, to_string(data.time));
		item_data.replace(item_data.find("{dwExtraInfo}"), sizeof("{dwExtraInfo}") - 1, to_string(data.dwExtraInfo));

		if (i + 1 < leng)
		{
			item_data.append(",");
		}

		result.append(item_data);
	}

	result.push_back(']');
	return result;
}

DWORD hmc_mouse::getLastInputTime()
{
	LASTINPUTINFO lii;
	lii.cbSize = sizeof(LASTINPUTINFO);

	if (::GetLastInputInfo(&lii))
	{
		return lii.dwTime;
	}

	return 0; // 默认返回 0，表示获取失败
}

string hmc_mouse::MouseEventJsonA(MouseEvent event)
{
	// 需要区分开两个数据结构的json 因为json序列化非常费劲 v8也不例外
	if (event.time > 0)
	{
		string item_data = event.button == WM_MOUSEMOVE ?
			// WM_MOUSEMOVE
			string(R"({ "id":{id},"time":{time},"button":{button},"x":{x},"y":{y} })")
			:
			// ...
			string(R"({ "id":{id},"time":{time},"button":{button},"buttonDown":{buttonDown},"wheelDelta":{wheelDelta},"name":"{buttonName}" })");

		item_data.replace(item_data.find("{id}"), sizeof("{id}") - 1, to_string(event.id));
		item_data.replace(item_data.find("{time}"), sizeof("{time}") - 1, to_string(event.time));
		item_data.replace(item_data.find("{button}"), sizeof("{button}") - 1, to_string(event.button));

		if (event.button == WM_MOUSEMOVE)
		{
			item_data.replace(item_data.find("{x}"), sizeof("{x}") - 1, to_string(event.x));
			item_data.replace(item_data.find("{y}"), sizeof("{y}") - 1, to_string(event.y));
		}
		else
		{

			item_data.replace(item_data.find("{buttonDown}"), sizeof("{buttonDown}") - 1, (event.buttonDown ? "true" : "false"));
			item_data.replace(item_data.find("{wheelDelta}"), sizeof("{wheelDelta}") - 1, (event.button != WM_MOUSEWHEEL ? "null" : to_string(event.wheelDelta)));

			switch (event.button)
			{
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			{

				item_data.replace(item_data.find("{buttonName}"), sizeof("{buttonName}") - 1, "left-mouse-button");
				break;
			}

			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			{

				item_data.replace(item_data.find("{buttonName}"), sizeof("{buttonName}") - 1, "right-mouse-button");
				break;
			}
			case WM_MBUTTONDOWN:
				// 中键释放
			case WM_MBUTTONUP:
			{

				item_data.replace(item_data.find("{buttonName}"), sizeof("{buttonName}") - 1, "middle-mouse-button");
				break;
			}
			default:
			{

				item_data.replace(item_data.find("\"{buttonName}\""), sizeof("\"{buttonName}\"") - 1, "null");
			}
			}
		}

		return item_data;
	}
	return string(R"({ "id":null,"time":null})");
}

bool hmc_mouse::isStartHookMouse()
{
	if (!_is_Mouse_Next_Hook)
	{
		if (_This_MouseHook != NULL)
		{
			UnhookWindowsHookEx(_This_MouseHook);
		}
	}

	return _is_Mouse_Next_Hook;
}

void hmc_mouse::push_Mouse_Event(MouseEvent event)
{
	_This_MouseEvent_List.push_back(event);
}

LRESULT CALLBACK hmc_mouse::WinApiCallBackMouseHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	//  没有键值
	if (nCode < 0)
	{
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}

	// 结束监听或者句柄丢失
	if (!_is_Mouse_Next_Hook || _This_MouseHook == NULL)
	{
		if (_This_MouseHook != NULL)
		{
			UnhookWindowsHookEx(_This_MouseHook);
		}
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}

	_This_Temp_MouseEvent.id = _This_Event_id;

	_This_Event_id = _This_Event_id + 1;

	const MSLLHOOKSTRUCT* const pMouseLLHook = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);

	switch (wParam)
	{
		// 左键按下
	case WM_LBUTTONDOWN:
		// 右键按下
	case WM_RBUTTONDOWN:
		// 左键释放
	case WM_LBUTTONUP:
		// 右键释放
	case WM_RBUTTONUP:
		// 中键按下
	case WM_MBUTTONDOWN:
		// 中键释放
	case WM_MBUTTONUP:
	{
		_This_Temp_MouseEvent.buttonDown = (wParam == WM_LBUTTONDOWN) || (wParam == WM_RBUTTONDOWN) || (wParam == WM_MBUTTONDOWN);
		_This_Temp_MouseEvent.button = (long)wParam;
		_This_Temp_MouseEvent.time = (DWORD)pMouseLLHook->time;
		push_Mouse_Event(_This_Temp_MouseEvent);
		_This_Temp_MouseEvent = { 0 };

		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
	// 滚轮 滚轮需要获取向量
	case WM_MOUSEWHEEL:
	{

		const int wheelDelta = GET_WHEEL_DELTA_WPARAM(pMouseLLHook->mouseData);

		_This_Temp_MouseEvent.buttonDown = wheelDelta > 0;
		_This_Temp_MouseEvent.wheelDelta = wheelDelta;
		_This_Temp_MouseEvent.button = WM_MOUSEWHEEL;
		_This_Temp_MouseEvent.time = (DWORD)pMouseLLHook->time;
		push_Mouse_Event(_This_Temp_MouseEvent);
		_This_Temp_MouseEvent = { 0 };

		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
	// move
	case WM_MOUSEMOVE:
	{
		// 如果是move事件进行防抖 刷新率为 < shake_Event_time ?? 35 >ms

		if (pMouseLLHook->time >= _This_Event_Time + shake_Event_time)
		{

			_This_Temp_MouseEvent.x = pMouseLLHook->pt.x;
			_This_Temp_MouseEvent.y = pMouseLLHook->pt.y;
			_This_Temp_MouseEvent.time = (DWORD)pMouseLLHook->time;
			_This_Temp_MouseEvent.button = WM_MOUSEMOVE;

			push_Mouse_Event(_This_Temp_MouseEvent);

			_This_Event_Time = _This_Temp_MouseEvent.time;

			_This_Temp_MouseEvent = { 0 };
		}

		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void hmc_mouse::StopHookMouse()
{

	if (_This_MouseHook != NULL)
	{
		if (UnhookWindowsHookEx(_This_MouseHook))
		{
			_This_MouseHook = NULL;
		}
	}

	_This_MouseEvent_List.clear();
	_This_MouseEvent_List.resize(0);

	_is_Mouse_Next_Hook = false;
	_This_Event_Time = 0;
	_This_Temp_MouseEvent = { 0 };
}

void hmc_mouse::InitHookMouse()
{
	if (isStartHookMouse())
	{
		return;
	}
	_is_Mouse_Next_Hook = true;
	_This_MouseEvent_List.reserve(256);
	_This_MouseHook = SetWindowsHookExA(
		WH_MOUSE_LL,			 // 钩子类型 安装用于监视低级别键盘输入事件的挂钩过程 与  安装用于监视低级别鼠标输入事件的挂钩过程
		WinApiCallBackMouseHook, // 指向钩子函数的指针
		nullptr,				 // 没有模块句柄
		NULL);

	BOOL bRet;
	MSG msg;

	// 获取消息循环
	while ((bRet = GetMessageW(&msg, nullptr, 0, 0)) != 0)
	{ 
		if (bRet == -1 || (!_is_Mouse_Next_Hook || _This_MouseHook == NULL))
		{
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// 移除系统钩子
	if (_This_MouseHook != NULL)
	{
		UnhookWindowsHookEx(_This_MouseHook);
	}
	StopHookMouse();
}

vector<hmc_mouse::MouseEvent> hmc_mouse::getMouseEvent()
{

	vector<MouseEvent> event_list;

	size_t len = _This_MouseEvent_List.size();

	if (len <= 0)
	{
		return event_list;
	}

	for (size_t i = 0; i < len; i++)
	{

		event_list.push_back(_This_MouseEvent_List[i]);
	}

	_This_MouseEvent_List.erase(_This_MouseEvent_List.begin() + 0, _This_MouseEvent_List.begin() + len);

	return event_list;
}

string hmc_mouse::getMouseEventListJsonA()
{
	vector<MouseEvent> event_btn_list = getMouseEvent();

	string result = "[";

	for (size_t i = 0; i < event_btn_list.size(); i++)
	{
		auto& item = event_btn_list[i];

		result.append(MouseEventJsonA(item));

		if (i + 1 < event_btn_list.size())
		{
			result.push_back(',');
		}
	}

	result.push_back(']');
	return result;
}
