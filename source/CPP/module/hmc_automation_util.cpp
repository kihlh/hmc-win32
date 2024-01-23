#include "hmc_automation_util.h"

//  keyboardHook functions
namespace hmc_Keyboard
{
    bool hmc_Keyboard::keyboardHook::GpAllowHookToken = false;                                                                                               // 是否继续执行
    HHOOK hmc_Keyboard::keyboardHook::GpHookHandle = NULL;                                                                                                   // 钩子句柄
    long long hmc_Keyboard::keyboardHook::GpEventNextID = 1;                                                                                                 // 当前id
    std::vector<hmc_Keyboard::keyboardHook::KeyboardEvent> hmc_Keyboard::keyboardHook::GpEventSessionList;                                                   // 鼠标按钮的事件容器(缓冲)  预扩容了256个
    DWORD hmc_Keyboard::keyboardHook::GpWorkerThreadID = 0;                                                                                                  // 正在执行hook线程
    std::shared_mutex hmc_Keyboard::keyboardHook::GpStoreSharedMutex;                                                                                        // 存储的互斥体
    std::optional<std::function<bool(hmc_Keyboard::keyboardHook::KeyboardEvent event)>> hmc_Keyboard::keyboardHook::GpEventSessionToCallBack = std::nullopt; // 重定向到回调函数中

    void hmc_Keyboard::keyboardHook::initializeBasicValues()
    {
        if (!GpAllowHookToken && GpHookHandle == NULL)
        {
            GpAllowHookToken = false;
            GpHookHandle = NULL;
            GpEventNextID = 1;
            GpWorkerThreadID = 0;
            GpEventSessionList.clear();
            GpEventSessionToCallBack.reset();
        }
    }

    bool hmc_Keyboard::keyboardHook::KeyboardEvent::is_valid()
    {
        return time > 0 || id >= 0;
    }

    std::string hmc_Keyboard::keyboardHook::KeyboardEvent::to_json()
    {
        std::string result = R"({"id":{id},"time":{time},"down":{down},"flags":{flags},"keyCode":{keyCode},"scanCode":{scanCode},"key":"{KeyName}","code":"{KeyNameCode}"})";

        result.replace(result.find("{id}"), sizeof("{id}") - 1, std::to_string(id));
        result.replace(result.find("{time}"), sizeof("{time}") - 1, std::to_string(time));
        result.replace(result.find("{down}"), sizeof("{down}") - 1, down ? "true" : "false");
        result.replace(result.find("{flags}"), sizeof("{flags}") - 1, std::to_string(flags));
        result.replace(result.find("{keyCode}"), sizeof("{keyCode}") - 1, std::to_string(keyCode));
        result.replace(result.find("{scanCode}"), sizeof("{scanCode}") - 1, std::to_string(scanCode));

        // 小键盘回车
        if (keyCode == 13 && flags & LLKHF_EXTENDED)
        {
            keyCode = 0xE0;
        }

        std::string to_KeyName = hmc_automation_util::GpMapVirtualKey(keyCode);
        std::string to_keyCode = hmc_automation_util::GpMapVirtualCode(keyCode);

        if (!to_KeyName.empty() && to_KeyName.back() == '\\')
        {
            to_KeyName.clear();
            to_KeyName.append("\\\\");
        }

        if (!to_keyCode.empty() && to_keyCode.back() == '\\')
        {
            to_keyCode.clear();
            to_keyCode.append("\\\\");
        }

        result.replace(result.find("{KeyName}"), sizeof("{KeyName}") - 1, to_KeyName);
        result.replace(result.find("{KeyNameCode}"), sizeof("{KeyNameCode}") - 1, to_keyCode);

        return result;
    }

    LRESULT CALLBACK hmc_Keyboard::keyboardHook::WinApiLowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
    {

        // 没有键值
        if (nCode < 0)
        {
            return ::CallNextHookEx(NULL, nCode, wParam, lParam);
        }

        KBDLLHOOKSTRUCT *ks = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);
        if (!GpEventSessionToCallBack.has_value())
        {
            push_keyboard_data(ks);
        }
        else
        {

            KeyboardEvent data = KeyboardEvent();

            data.keyCode = ks->vkCode;
            data.scanCode = ks->scanCode;
            data.id = GpEventNextID;
            data.time = ks->time;
            data.flags = ks->flags;
            data.down = (ks->flags < 128);

            GpEventNextID = GpEventNextID + 1;
            bool is_next = GpEventSessionToCallBack.value()(data);
            if (!is_next)
            {
                return 1;
            }
        }

        // 将消息传递给钩子链中的下一个钩子
        return ::CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    bool hmc_Keyboard::keyboardHook::InitKeyboardEventHookWorker()
    {
        bool result = false;

        if (isValidHookKeyboard())
        {
            return result;
        }

        if (GpWorkerThreadID == NULL)
        {
            GpWorkerThreadID = hmc_automation_util::toThreadId(std::this_thread::get_id());
        }

        if (GpEventSessionList.capacity() > 50)
        {
            GpEventSessionList.reserve(128);
        }

        if (!GpWorkerThreadID)
        {
            return result;
        }
        GpAllowHookToken = true;
        GpEventSessionList.clear();

        GpHookHandle = ::SetWindowsHookExW(
            WH_KEYBOARD_LL,             // 钩子类型 安装用于监视低级别键盘输入事件的挂钩过程 与  安装用于监视低级别鼠标输入事件的挂钩过程
            WinApiLowLevelKeyboardProc, // 指向钩子函数的指针
            ::GetModuleHandleA(NULL),   // 没有模块句柄
            NULL);

        if (GpHookHandle == 0)
        {
            return false;
        }

        BOOL bRet;
        MSG msg;

        // 获取消息循环
        while ((bRet = ::GetMessageW(&msg, nullptr, 0, 0)) != 0)
        {
            if (bRet == -1 || (!GpAllowHookToken || !GpWorkerThreadID || GpHookHandle == NULL))
            {
                break;
            }
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        if (GpHookHandle != NULL)
        {

            // 移除系统钩子
            ::UnhookWindowsHookEx(GpHookHandle);
        }

        initializeBasicValues();

        return true;
    }

    DWORD hmc_Keyboard::keyboardHook::getThreadId()
    {
        return GpWorkerThreadID;
    }

    hmc_Keyboard::keyboardHook::KeyboardEvent::KeyboardEvent()
    {
        id = 0;
        keyCode = 0;
        time = 0;
        down = 0;
        scanCode = 0;
        flags = 0;
    }

    bool hmc_Keyboard::keyboardHook::initKeyboardEventHook(std::function<bool(hmc_Keyboard::keyboardHook::KeyboardEvent event)> callback)
    {
        bool result = false;

        if (isValidHookKeyboard())
        {
            return result;
        }

        initializeBasicValues();

        GpEventSessionToCallBack = callback;
        std::thread new_thread = std::thread(InitKeyboardEventHookWorker);

        GpWorkerThreadID = hmc_automation_util::toThreadId(new_thread.get_id());

        new_thread.detach();

        result = GpWorkerThreadID != 0;
        return result;
    }

    bool hmc_Keyboard::keyboardHook::initKeyboardEventHook()
    {
        bool result = false;

        if (isValidHookKeyboard())
        {
            return result;
        }

        initializeBasicValues();

        std::thread new_thread = std::thread(InitKeyboardEventHookWorker);

        GpWorkerThreadID = hmc_automation_util::toThreadId(new_thread.get_id());

        new_thread.detach();

        result = GpWorkerThreadID != 0;
        return result;
    }

    bool hmc_Keyboard::keyboardHook::isValidHookKeyboard()
    {

        if (!GpAllowHookToken)
        {
            if (GpHookHandle != NULL)
            {

                if (!::UnhookWindowsHookEx(GpHookHandle))
                {
                    ::UnhookWindowsHookEx(GpHookHandle);
                }

                GpHookHandle = NULL;
            }
        }

        return GpAllowHookToken;
    }

    void hmc_Keyboard::keyboardHook::push_keyboard_data(KBDLLHOOKSTRUCT *input)
    {

        KeyboardEvent data = KeyboardEvent();

        data.keyCode = input->vkCode;
        data.scanCode = input->scanCode;
        data.id = GpEventNextID;
        data.time = input->time;
        data.flags = input->flags;
        data.down = (input->flags < 128);

        std::unique_lock<std::shared_mutex> writer_mutex(GpStoreSharedMutex);
        GpEventSessionList.push_back(data);
        writer_mutex.unlock();

        GpEventNextID = GpEventNextID + 1;
    }

    std::string hmc_Keyboard::keyboardHook::getAllKeyboardEventJson()
    {
        std::string result = "[";

        auto AllKeyboardEvent = getAllKeyboardEvent();
        auto length = AllKeyboardEvent.size();

        for (size_t i = 0; i < length; i++)
        {
            auto &it = AllKeyboardEvent[i];
            if (it.is_valid())
            {
                result.append(it.to_json());
            }

            if (i + 1 < length)
            {
                result.push_back(',');
            }
        }
        result.push_back(']');

        return result;
    }

    std::vector<hmc_Keyboard::keyboardHook::KeyboardEvent> hmc_Keyboard::keyboardHook::getAllKeyboardEvent()
    {
        std::vector<KeyboardEvent> event_list;

        std::shared_lock<std::shared_mutex> read_mutex(GpStoreSharedMutex);

        size_t len = GpEventSessionList.size();

        if (len <= 0)
        {
            read_mutex.unlock();
            return event_list;
        }
        event_list.reserve(len);

        for (size_t i = 0; i < len; i++)
        {

            event_list.push_back(GpEventSessionList[i]);
        }

        read_mutex.unlock();

        std::unique_lock<std::shared_mutex> writer_mutex(GpStoreSharedMutex);

        GpEventSessionList.erase(GpEventSessionList.begin(), GpEventSessionList.begin() + len);

        writer_mutex.unlock();

        return event_list;
    }

    bool hmc_Keyboard::keyboardHook::stopHookKeyboard()
    {
        if (!GpAllowHookToken)
        {
            if (GpHookHandle != NULL)
            {

                if (!::UnhookWindowsHookEx(GpHookHandle))
                {
                    ::UnhookWindowsHookEx(GpHookHandle);
                }

                GpEventSessionList.clear();
                GpAllowHookToken = false;
                GpEventNextID = 0;
                GpWorkerThreadID = 0;
                GpHookHandle = NULL;
                return true;
            }
            return true;
        }

        bool is_unHook = GpHookHandle == NULL ? true : ::UnhookWindowsHookEx(GpHookHandle);
        bool is_kiilThread = GpWorkerThreadID == NULL ? true : ::PostThreadMessageW(GpWorkerThreadID, WM_QUIT, NULL, NULL);

        GpEventSessionList.clear();
        GpAllowHookToken = false;
        GpEventNextID = 0;
        GpWorkerThreadID = 0;
        GpHookHandle = NULL;

        return is_kiilThread || is_unHook;
    }

}

// MouseHook functions
namespace hmc_mouse
{
    std::shared_mutex hmc_mouse::MouseHook::GpMouseStoreSharedMutex;                                                                          // 存储的互斥体
    bool hmc_mouse::MouseHook::GpMouseAllowHookToken = false;                                                                                 // 是否继续执行
    DWORD hmc_mouse::MouseHook::GpMouseTheEventTime = 0;                                                                                      // 上次输入体的时间
    HHOOK hmc_mouse::MouseHook::GpHookMouseHandle = NULL;                                                                                     // 钩子句柄
    DWORD hmc_mouse::MouseHook::GpMouseShakeEventTime = 35;                                                                                   // 消除抖动的ms
    long long hmc_mouse::MouseHook::GpMouseEventNextID = 0;                                                                                   // 当前id
    std::vector<hmc_mouse::MouseHook::MouseEvent> hmc_mouse::MouseHook::GpMouseEventSessionList;                                              // 鼠标按钮的事件容器(缓冲)  预扩容了256个
    hmc_mouse::MouseHook::MouseEvent hmc_mouse::MouseHook::GpMouseTempEventBuffer = hmc_mouse::MouseHook::MouseEvent();                       // 预开劈缓冲区 每次鼠标回调不会动态创建 而是把此变量作为temp
    DWORD hmc_mouse::MouseHook::GpMouseWorkerThreadID = 0;                                                                                    // 正在执行hook线程
    std::optional<std::function<bool(hmc_mouse::MouseHook::MouseEvent event)>> hmc_mouse::MouseHook::GpEventSessionToCallBack = std::nullopt; // 重定向到回调函数中

    bool hmc_mouse::MouseHook::MouseEvent::is_valid()
    {
        return time == 0;
    }

    std::string hmc_mouse::MouseHook::MouseEvent::to_json()
    {
        // 需要区分开两个数据结构的json 因为json序列化非常费劲 v8也不例外
        if (time > 0)
        {
            std::string item_data = button == WM_MOUSEMOVE ?
                                                           // WM_MOUSEMOVE
                                        std::string(R"({ "id":{id},"time":{time},"button":{button},"x":{x},"y":{y} })")
                                                           :
                                                           // ...
                                        std::string(R"({ "id":{id},"time":{time},"button":{button},"buttonDown":{buttonDown},"wheelDelta":{wheelDelta},"name":"{buttonName}" })");

            item_data.replace(item_data.find("{id}"), sizeof("{id}") - 1, std::to_string(id));
            item_data.replace(item_data.find("{time}"), sizeof("{time}") - 1, std::to_string(time));
            item_data.replace(item_data.find("{button}"), sizeof("{button}") - 1, std::to_string(button));

            if (button == WM_MOUSEMOVE)
            {
                item_data.replace(item_data.find("{x}"), sizeof("{x}") - 1, std::to_string(x));
                item_data.replace(item_data.find("{y}"), sizeof("{y}") - 1, std::to_string(y));
            }
            else
            {

                item_data.replace(item_data.find("{buttonDown}"), sizeof("{buttonDown}") - 1, (buttonDown ? "true" : "false"));
                item_data.replace(item_data.find("{wheelDelta}"), sizeof("{wheelDelta}") - 1, (button != WM_MOUSEWHEEL ? "null" : std::to_string(wheelDelta)));

                switch (button)
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
        return std::string(R"({ "id":null,"time":null})");
    }

    hmc_mouse::MouseHook::MouseEvent::MouseEvent()
    {
        id = 0;
        button = 0;
        wheelDelta = 0;
        buttonDown = 0;
        time = 0;
        x = 0;
        y = 0;
    }

    bool hmc_mouse::MouseHook::isValidHookMouse()
    {
        if (!GpMouseAllowHookToken)
        {
            if (GpHookMouseHandle != NULL)
            {
                ::UnhookWindowsHookEx(GpHookMouseHandle);
            }
        }

        return GpMouseAllowHookToken;
    }

    void hmc_mouse::MouseHook::push_Mouse_Event(hmc_mouse::MouseHook::MouseEvent event)
    {

        std::unique_lock<std::shared_mutex> writer_mutex(GpMouseStoreSharedMutex);
        GpMouseEventSessionList.push_back(event);
        writer_mutex.unlock();
    }

    void hmc_mouse::MouseHook::setShakeEventTime(long time)
    {
        GpMouseShakeEventTime = time;
    }

    void hmc_mouse::MouseHook::gc_next_temp()
    {
        GpMouseTempEventBuffer.button = 0;
        GpMouseTempEventBuffer.buttonDown = 0;
        GpMouseTempEventBuffer.id = 0;
        GpMouseTempEventBuffer.time = 0;
        GpMouseTempEventBuffer.wheelDelta = 0;
        GpMouseTempEventBuffer.x = 0;
        GpMouseTempEventBuffer.y = 0;
    }

    LRESULT CALLBACK hmc_mouse::MouseHook::WinApiCallBackMouseHook(int nCode, WPARAM wParam, LPARAM lParam)
    {
        //  没有键值
        if (nCode < 0)
        {
            return ::CallNextHookEx(NULL, nCode, wParam, lParam);
        }

        // 结束监听或者句柄丢失
        if (!GpMouseAllowHookToken || GpHookMouseHandle == NULL)
        {
            if (GpHookMouseHandle != NULL)
            {
                ::UnhookWindowsHookEx(GpHookMouseHandle);
            }
            return ::CallNextHookEx(NULL, nCode, wParam, lParam);
        }

        GpMouseTempEventBuffer.id = GpMouseEventNextID;

        GpMouseEventNextID = GpMouseEventNextID + 1;

        const MSLLHOOKSTRUCT *const pMouseLLHook = reinterpret_cast<MSLLHOOKSTRUCT *>(lParam);

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
            GpMouseTempEventBuffer.buttonDown = (wParam == WM_LBUTTONDOWN) || (wParam == WM_RBUTTONDOWN) || (wParam == WM_MBUTTONDOWN);
            GpMouseTempEventBuffer.button = (long)wParam;
            GpMouseTempEventBuffer.time = (DWORD)pMouseLLHook->time;

            if (GpEventSessionToCallBack.has_value())
            {
                bool is_next = GpEventSessionToCallBack.value()(GpMouseTempEventBuffer);
                if (!is_next)
                {
                    return 1;
                }
                gc_next_temp();
            }
            else
            {
                push_Mouse_Event(GpMouseTempEventBuffer);
                gc_next_temp();
            }

            return ::CallNextHookEx(NULL, nCode, wParam, lParam);
        }
        // 滚轮 滚轮需要获取向量
        case WM_MOUSEWHEEL:
        {

            const int wheelDelta = GET_WHEEL_DELTA_WPARAM(pMouseLLHook->mouseData);

            GpMouseTempEventBuffer.buttonDown = wheelDelta > 0;
            GpMouseTempEventBuffer.wheelDelta = wheelDelta;
            GpMouseTempEventBuffer.button = WM_MOUSEWHEEL;
            GpMouseTempEventBuffer.time = (DWORD)pMouseLLHook->time;

            if (GpEventSessionToCallBack.has_value())
            {
                bool is_next = GpEventSessionToCallBack.value()(GpMouseTempEventBuffer);
                if (!is_next)
                {
                    return 1;
                }
                gc_next_temp();
            }
            else
            {
                push_Mouse_Event(GpMouseTempEventBuffer);
                gc_next_temp();
            }

            return ::CallNextHookEx(NULL, nCode, wParam, lParam);
        }
        // move
        case WM_MOUSEMOVE:
        {
            // 如果是move事件进行防抖 刷新率为 < GpMouseShakeEventTime ?? 35 >ms

            if (pMouseLLHook->time >= GpMouseTheEventTime + GpMouseShakeEventTime)
            {

                GpMouseTempEventBuffer.x = pMouseLLHook->pt.x;
                GpMouseTempEventBuffer.y = pMouseLLHook->pt.y;
                GpMouseTempEventBuffer.time = (DWORD)pMouseLLHook->time;
                GpMouseTempEventBuffer.button = WM_MOUSEMOVE;

                if (GpEventSessionToCallBack.has_value())
                {
                    bool is_next = GpEventSessionToCallBack.value()(GpMouseTempEventBuffer);
                    if (!is_next)
                    {
                        return 1;
                    }
                }
                else
                {
                    push_Mouse_Event(GpMouseTempEventBuffer);
                }

                GpMouseTheEventTime = GpMouseTempEventBuffer.time;
                gc_next_temp();
            }

            return ::CallNextHookEx(NULL, nCode, wParam, lParam);
        }
        }

        return ::CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    bool hmc_mouse::MouseHook::stopHookMouse()
    {
        bool is_kiilThread = false;
        bool is_unHook = false;

        if (GpHookMouseHandle != NULL)
        {
            if (::UnhookWindowsHookEx(GpHookMouseHandle))
            {
                GpHookMouseHandle = NULL;
                is_unHook = true;
            }
        }

        // 关闭线程
        is_kiilThread = GpMouseWorkerThreadID == NULL ? true : ::PostThreadMessageW(GpMouseWorkerThreadID, WM_QUIT, NULL, NULL);

        initializeBasicValues();
        gc_next_temp();

        return is_unHook || is_kiilThread;
    }

    void hmc_mouse::MouseHook::InitHookMouse()
    {
        GpMouseAllowHookToken = true;

        if (GpMouseEventSessionList.capacity() < 50)
        {
            GpMouseEventSessionList.reserve(256);
        }

        if (GpMouseWorkerThreadID != 0)
        {
            GpMouseWorkerThreadID = hmc_automation_util::toThreadId(std::this_thread::get_id());
        }

        GpHookMouseHandle = ::SetWindowsHookExA(
            WH_MOUSE_LL,             // 钩子类型 安装用于监视低级别键盘输入事件的挂钩过程 与  安装用于监视低级别鼠标输入事件的挂钩过程
            WinApiCallBackMouseHook, // 指向钩子函数的指针
            nullptr,                 // 没有模块句柄
            NULL);

        BOOL bRet;
        MSG msg;

        // 获取消息循环
        while ((bRet = ::GetMessageW(&msg, nullptr, 0, 0)) != 0)
        {
            if (bRet == -1 || (!GpMouseAllowHookToken || GpHookMouseHandle == NULL))
            {
                break;
            }
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        // 移除系统钩子
        if (GpHookMouseHandle != NULL)
        {
            ::UnhookWindowsHookEx(GpHookMouseHandle);
        }
        stopHookMouse();
    }

    std::vector<hmc_mouse::MouseHook::MouseEvent> hmc_mouse::MouseHook::getMouseEvent()
    {

        std::vector<MouseEvent> event_list;

        std::shared_lock<std::shared_mutex> read_mutex(GpMouseStoreSharedMutex);
        size_t len = GpMouseEventSessionList.size();

        if (len <= 0)
        {
            read_mutex.unlock();
            return event_list;
        }

        event_list.reserve(len);

        for (size_t i = 0; i < len; i++)
        {
            event_list.push_back(GpMouseEventSessionList[i]);
        }

        read_mutex.unlock();

        std::unique_lock<std::shared_mutex> writer_mutex(GpMouseStoreSharedMutex);
        GpMouseEventSessionList.erase(GpMouseEventSessionList.begin() + 0, GpMouseEventSessionList.begin() + len);
        writer_mutex.unlock();

        return event_list;
    }

    std::string hmc_mouse::MouseHook::getMouseEventListJsonA()
    {
        std::vector<MouseEvent> event_btn_list = getMouseEvent();

        std::string result = "[";

        for (size_t i = 0; i < event_btn_list.size(); i++)
        {
            auto &item = event_btn_list[i];

            result.append(item.to_json());

            if (i + 1 < event_btn_list.size())
            {
                result.push_back(',');
            }
        }

        result.push_back(']');
        return result;
    }

    void hmc_mouse::MouseHook::initializeBasicValues()
    {
        if (!GpMouseAllowHookToken || GpHookMouseHandle == NULL)
        {
            GpMouseAllowHookToken = false;
            GpHookMouseHandle = NULL;
            GpMouseEventSessionList.clear();
            GpMouseTheEventTime = 0;
            GpMouseShakeEventTime = 35;
            GpMouseEventNextID = 0;
            GpMouseWorkerThreadID = 0;
            GpEventSessionToCallBack.reset();
            gc_next_temp();
        }
    }

    bool hmc_mouse::MouseHook::initMouseEventHook()
    {
        bool result = false;

        if (isValidHookMouse())
        {
            return result;
        }
        initializeBasicValues();

        std::thread new_thread = std::thread(InitHookMouse);

        GpMouseWorkerThreadID = hmc_automation_util::toThreadId(new_thread.get_id());

        new_thread.detach();

        result = GpMouseWorkerThreadID != 0;
        return result;
    }

    bool hmc_mouse::MouseHook::initMouseEventHook(std::function<bool(MouseEvent event)> callback)
    {
        bool result = false;

        if (isValidHookMouse())
        {
            return result;
        }
        initializeBasicValues();

        GpEventSessionToCallBack = callback;

        std::thread new_thread = std::thread(InitHookMouse);

        GpMouseWorkerThreadID = hmc_automation_util::toThreadId(new_thread.get_id());

        new_thread.detach();

        result = GpMouseWorkerThreadID != 0;
        return result;
    }

    DWORD hmc_mouse::MouseHook::getThreadId()
    {
        return GpMouseWorkerThreadID;
    }

}

// LimitMouseRange functions
namespace hmc_mouse
{
    std::unique_ptr<std::thread> LimitMouseRange::GpWorkerThreadHandlePtr = nullptr;
    bool LimitMouseRange::GpUnMouseLockWorker = true;

    void hmc_mouse::LimitMouseRange::setLimitMouseRange_async_worker(long ms, long x, long y, long right, long bottom)
    {
        GpUnMouseLockWorker = false;

        // 函数正常退出时候的回调 如果没有正常退出则在主函数的 hmc_gc_func 释放 进行灾难性解锁
        std::shared_ptr<void> _shared_free_handle(nullptr, [&](void *)
                                                  {
			::ClipCursor(NULL);  //释放 
			GpUnMouseLockWorker = true;
			stopLimitMouseRange_worker(); });

        RECT rect = {0};

        // 左上角
        rect.top = x;  // 上
        rect.left = y; // 左

        // 右下角
        rect.bottom = rect.top + bottom; // 底
        rect.right = rect.left + right;  // 右

        ::ClipCursor(&rect);

        // Sleep(ms);
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        ::ClipCursor(NULL); // 释放
    }

    bool hmc_mouse::LimitMouseRange::setLimitMouseRange(long ms, long x, long y, long right, long bottom)
    {

        // 已经存在 不能创建 超出30秒 小于30ms  直接拒绝创建
        if (hasLimitMouseRange_worker() || !GpUnMouseLockWorker || ms < 29 || ms > 1000 * 30 - 1)
        {
            return false;
        }

        // 创建处理的函数
        GpWorkerThreadHandlePtr.reset(new std::thread(setLimitMouseRange_async_worker, ms, x, y, right, bottom));

        return false;
    }

    bool hmc_mouse::LimitMouseRange::hasLimitMouseRange_worker()
    {

        // 已经存在 线程正常
        if (GpWorkerThreadHandlePtr && GpWorkerThreadHandlePtr->joinable())
        {
            return true;
        }

        // 已经存在 线程无效
        if (GpWorkerThreadHandlePtr)
        {
            GpWorkerThreadHandlePtr.release();
        }

        return false;
    }

    bool hmc_mouse::LimitMouseRange::stopLimitMouseRange_worker()
    {

        bool stop_cursor = ::ClipCursor(NULL);

        GpUnMouseLockWorker = true;

        if (!GpWorkerThreadHandlePtr || !GpWorkerThreadHandlePtr->joinable())
        {
            GpWorkerThreadHandlePtr.release();
            return true;
        }

        DWORD threadId = ::GetThreadId(GpWorkerThreadHandlePtr->native_handle());

        if (threadId <= 0)
        {
            return true;
        }

        if (::PostThreadMessage(threadId, WM_QUIT, NULL, NULL))
        {
            GpWorkerThreadHandlePtr.release();
            return stop_cursor;
        }
        else
        {

            if (GpWorkerThreadHandlePtr)
            {
                if (GpWorkerThreadHandlePtr->joinable())
                {
                    GpWorkerThreadHandlePtr->detach();
                }
            }
            GpWorkerThreadHandlePtr.release();
        }

        return false;
    }

}

std::string hmc_mouse::getCursorPosJsonA()
{
    POINT cursorPos = {0};

    if (::GetCursorPos(&cursorPos))
    {
        int x = cursorPos.x;
        int y = cursorPos.y;
        std::string res = std::string(R"({"x":)");
        res.append(std::to_string(x));
        res.append(std::string(R"(,"y":)"));
        res.append(std::to_string(x));
        res.append("}");
        return res;
    }

    return std::string(R"({"x":null,"y":null})");
}

std::vector<MOUSEMOVEPOINT> hmc_mouse::getMouseMovePoints()
{
    std::vector<MOUSEMOVEPOINT> results;

    // 预算出 计算方式 因为有可能数据是负数或者是不规整屏幕

    int nVirtualWidth = ::GetSystemMetrics(SM_CXVIRTUALSCREEN);
    int nVirtualHeight = ::GetSystemMetrics(SM_CYVIRTUALSCREEN);
    int nVirtualLeft = ::GetSystemMetrics(SM_XVIRTUALSCREEN);
    int nVirtualTop = ::GetSystemMetrics(SM_YVIRTUALSCREEN);

    // 当前的鼠标位置
    POINT currentMousePosition = {0};
    ::GetCursorPos(&currentMousePosition);
    // 放置鼠标位置的容器
    MOUSEMOVEPOINT mousePositionContainer = {0};
    mousePositionContainer.x = currentMousePosition.x;
    mousePositionContainer.y = currentMousePosition.y;

    // 微软规定只会返回的最大数据为64
    const DWORD dwMaxPoints = 64;
    // 鼠标轨迹列表
    MOUSEMOVEPOINT mobileProgressList[dwMaxPoints] = {0};
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
        auto &mp = mobileProgressList[i];

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

        results.push_back(MOUSEMOVEPOINT{mp.x, mp.y, mp.time, mp.dwExtraInfo});
    }

    return results;
}

std::string hmc_mouse::getMouseMovePointsJsonA()
{
    std::string result = "[";
    auto data_list = getMouseMovePoints();
    size_t leng = data_list.size();

    for (size_t i = 0; i < leng; i++)
    {
        auto &data = data_list[i];
        std::string item_data = std::string(R"({"x":{x},"y":{y},"time":{time},"dwExtraInfo":{dwExtraInfo}})");
        item_data.replace(item_data.find("{x}"), sizeof("{x}") - 1, std::to_string(data.x));
        item_data.replace(item_data.find("{y}"), sizeof("{y}") - 1, std::to_string(data.y));
        item_data.replace(item_data.find("{time}"), sizeof("{time}") - 1, std::to_string(data.time));
        item_data.replace(item_data.find("{dwExtraInfo}"), sizeof("{dwExtraInfo}") - 1, std::to_string(data.dwExtraInfo));

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

DWORD hmc_automation_util::toThreadId(std::thread::id thread_id)
{
    DWORD ThreadIdAsInt = 0;

    try
    {
        ThreadIdAsInt = *static_cast<DWORD *>(static_cast<void *>(&thread_id));
    }
    catch (...)
    {
        auto data = std::hash<std::thread::id>()(thread_id);
        ThreadIdAsInt = static_cast<DWORD>(data);
    }

    return ThreadIdAsInt;
}

UINT hmc_automation_util::GpSendInput(UINT cInputs, LPINPUT pInputs, int cbSize)
{
    HMODULE hUser32 = ::LoadLibraryA("user32.dll");
    UINT uSent = 0;

    if (hUser32)
    {
        UINT(_stdcall * pSendInput)
        (UINT cInputs, LPINPUT pInputs, int cbSize);

        pSendInput = (UINT(_stdcall *)(UINT cInputs, LPINPUT pInputs, int cbSize))::GetProcAddress(hUser32, "SendInput");
        if (pSendInput)
        {
            uSent = pSendInput(cInputs, pInputs, cbSize);
        }
        ::FreeLibrary(hUser32);
    }
    return uSent;
}

bool hmc_automation_util::hasKeyActivate(int nVirtKey)
{
    return ::GetKeyState(nVirtKey) & 0x8000;
}

int hmc_automation_util::randomInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);
    return uni(rng);
}

hmc_Keyboard::chHasKeysBasic hmc_Keyboard::hasKeysBasic()
{
    hmc_Keyboard::chHasKeysBasic result = {0, 0, 0, 0};

    result.shift = hmc_automation_util::hasKeyActivate(VK_SHIFT);
    result.alt = hmc_automation_util::hasKeyActivate(VK_MENU);
    result.ctrl = hmc_automation_util::hasKeyActivate(VK_CONTROL);
    result.win = hmc_automation_util::hasKeyActivate(VK_RWIN) || hmc_automation_util::hasKeyActivate(VK_LWIN);

    return result;
}

hmc_mouse::chMouseBasic hmc_mouse::hasMouseBasic()
{
    hmc_mouse::chMouseBasic result = {0, 0, 0};

    result.left = hmc_automation_util::hasKeyActivate(VK_LBUTTON);
    result.middle = hmc_automation_util::hasKeyActivate(VK_MBUTTON);
    result.right = hmc_automation_util::hasKeyActivate(VK_RBUTTON);

    return result;
}

/**
 * @brief 相对符合w3c标准的 ``
 * @link https://developer.mozilla.org/zh-CN/docs/Web/API/KeyboardEvent/code
 *
 * @param input
 * @return std::string
 */
std::string hmc_automation_util::GpMapVirtualKey(std::uint8_t input)
{
    std::string result;

    result.reserve(10);

    if (
        //-> Digit0-9
        (input >= 0x30 && input <= 0x39) ||
        //-> KeyA - KeyZ
        (input >= 0x41 && input <= 0x5a) ||
        //-> Numpad0 - Numpad9
        (input >= 0x60 && input <= 0x69) ||
        //-> *+ -./
        (input >= 106 && input <= 111) ||
        //-> ;=,--./`
        (input >= 186 && input <= 192) ||
        //-> [\]'
        (input >= 219 && input <= 222) ||
        //-> \ 
        input==226
    )
    {
        UINT mappedKey = ::MapVirtualKeyA(input, MAPVK_VK_TO_CHAR);
        result.push_back((char)mappedKey);
        return result;
    }

    // F1 - F24
    if (input >= 0x70 && input <= 0x87)
    {
        std::uint8_t f1 = 0x70;

        result.push_back('F');

        for (size_t i = 0; i < 24; i++)
        {
            auto it = f1 + i;

            if (it == input)
            {
                auto num = std::to_string(i + 1);
                result.append(num);
                return result;
            }
        }
    }
    if (input == 0xa4 || input == 0x12 || input == 0xa5)
    {
        result.append("Alt");
        return result;
    }

    if (input == 0x5b || input == 0x5c)
    {
        result.append("Win");
        return result;
    }

    if (input == 0x10 || input == 0xa0 || input == 0xa1)
    {
        result.append("Shift");
        return result;
    }

    if (input == 0x11 || input == 0xa2 || input == 0xa3)
    {
        result.append("Control");
        return result;
    }

    if (input == 0x0C || input == 0xfe)
    {
        result.append("Clear");
        return result;
    }

    result.reserve(32);
    if (result.empty())
    {
        const std::map<std::uint8_t, std::string> specialKeys = {
            {VK_LBUTTON, "VK_LBUTTON"},
            {VK_RBUTTON, "VK_RBUTTON"},
            {VK_CANCEL, "VK_CANCEL"},
            {VK_MBUTTON, "VK_MBUTTON"},
            {VK_XBUTTON1, "VK_XBUTTON1"},
            {VK_XBUTTON2, "VK_XBUTTON2"},
            {0x08, "Backspace"},
            {0x09, "Tab"},
            {0x0D, "Enter"},
            {0x13, "Pause"},
            {0x14, "CapsLock"},

            {VK_KANA, "HangulMode"},
            {VK_HANGUL, "HangulMode"},
            {VK_IME_ON, "VK_IME_ON"},
            {VK_JUNJA, "JunjaMode"},
            {VK_HANJA, "HanjaMode"},
            {VK_IME_OFF, "VK_IME_OFF"},
            {VK_CONVERT, "Convert"},
            {0x18, "FinalMode"},

            // 0x1b
            {VK_ESCAPE, "Escape"},
            {VK_NONCONVERT, "NonConvert"},
            {VK_ACCEPT, "Accept"},
            {VK_MODECHANGE, "ModeChange"},
            // 0x20
            {VK_SPACE, "Space"},

            {0x21, "PageUp"},
            {0x22, "PageDown"},
            {0x23, "End"},
            {0x24, "Home"},
            {0x25, "ArrowLeft"},
            {0x26, "ArrowUp"},
            {0x27, "ArrowRight"},
            {0x28, "ArrowDown"},
            {0x29, "Select"},
            {0x2A, "VK_PRINT"},
            {0x2B, "Execute"},
            {0x2C, "PrintScreen"},
            {0x2D, "Insert"},
            {0x2E, "Delete"},
            {0x2F, "Help"},

            // 0-z-> 0x30 - 0x5a   win -> 0x5C 0x5B

            {0x5D, "ContextMenu"},
            {0x5F, "Standby"},
            // 0x60 - 0x69 Numpad0 - Numpad9
            {0x6A, "*"},
            {0x6B, "+"},
            {0x6C, "Separator"},
            {0x6D, "-"},
            {0x6E, "."},
            {0x6F, "/"},
            // 0x70 -> 0x87  F1 - F22

            {0x90, "NumLock"},
            {0x91, "ScrollLock"},
            // 0x92 - 0x96 oem
            // 0xa0 - 0xa5 ctrl ait shift
            {0xA6, "BrowserBack"},
            {0xA7, "BrowserForward"},
            {0xA8, "BrowserRefresh"},
            {0xA9, "BrowserStop"},
            {0xAA, "BrowserSearch"},
            {0xAB, "BrowserFavorites"},
            {0xAC, "BrowserHome"},
            {0xAD, "AudioVolumeMute"},
            {0xAE, "AudioVolumeDown"},
            {0xAF, "AudioVolumeUp"},
            {0xB0, "MediaTrackNext"},
            {0xB1, "MediaTrackPrevious"},
            {0xB2, "MediaStop"},
            {0xB3, "MediaPlayPause"},
            {0xB4, "LaunchMail"},
            {0xB5, "LaunchMediaPlayer"},
            {0xB6, "LaunchApplication1"},
            {0xB7, "LaunchApplication2"},
            // 0xB8-B9	预留
            {0xBA, ";"},
            {0xBB, "+"},
            {0xBC, ","},
            {0xBD, "-"},
            {0xBE, "."},
            {0xBF, "/"},
            {0xC0, "`"},
            // 0xC1-DA	保留
            {0xDB, "["},
            {0xDC, "\\"},
            {0xDD, "]"},
            {0xDE, "'"},
            // 特定字符  由键盘提供
            {0xDF, "VK_OEM_8"},
            // scanCode 的 数码键盘
            {0xE0, "Enter"},
            {0xE5, "Process"},
            {0xE7, "VK_PACKET"},
            {0xF6, "KanaMode"},
            {0xF7, "CrSel"},
            {0xF8, "ExSel"},
            {0xF9, "EraseEof"},
            {0xFA, "Play"},
            {0xFB, "ZoomToggle"},
            {0xFC, "VK_NONAME"},
            {0xFD, "VK_PA1"},
            {0xFE, "Clear"}};

        for (auto &special : specialKeys)
        {
            if (special.first == input)
            {
                result.append(special.second);
                return result;
            }
        }

        if (
            input >= 0xE9 && input <= 0xF5 ||
            input >= 0xE3 && input <= 0xE4 ||
            input == 0xE1 || input == 0xE6 ||
            input >= 0x92 && input <= 0x96)
        {
            result.append("VK_@OEM");
            return result;
        }

        if (
            input >= 0x3A && input <= 0x8F ||
            input >= 0x88 && input <= 0xE4 ||
            input == 0x5E || input == 0xE8 || input == 0xFC || input == 0 || input == 255 || input == 0x07 ||
            input >= 0x97 && input <= 0x9F ||
            input >= 0xC1 && input <= 0xDA ||
            input >= 0x0A && input <= 0x0B ||
            input >= 0x0E && input <= 0x0F ||
            input >= 0xB8 && input <= 0xB9)
        {
            result.append("Undefined");
            return result;
        }
    }

    return result;
}

namespace hmc_automation_util
{
    const std::map<std::string, UINT> hmc_automation_util::GpMouseEventList = {
        // 不支持的属性 请使用 setCursorPos 方法设置位置
        {"MOUSEEVENTF_ABSOLUTE", MOUSEEVENTF_ABSOLUTE},
        // 左键按下
        {"MOUSEEVENTF_LEFTDOWN", MOUSEEVENTF_LEFTDOWN},
        // 左边的按钮是向上的
        {"MOUSEEVENTF_LEFTUP", MOUSEEVENTF_LEFTUP},
        // 中间的按钮是向下的
        {"MOUSEEVENTF_MIDDLEDOWN", MOUSEEVENTF_MIDDLEDOWN},
        // 中间的按钮是向上的
        {"MOUSEEVENTF_MIDDLEUP", MOUSEEVENTF_MIDDLEUP},
        // 鼠标移动和按钮点击
        {"MOUSEEVENTF_MOVE", MOUSEEVENTF_MOVE},
        // 鼠标右键按下
        {"MOUSEEVENTF_RIGHTDOWN", MOUSEEVENTF_RIGHTDOWN},
        // 鼠标右键弹起
        {"MOUSEEVENTF_RIGHTUP", MOUSEEVENTF_RIGHTUP},
        // 滚轮按钮被旋转
        {"MOUSEEVENTF_WHEEL", MOUSEEVENTF_WHEEL},
        // 按下了 X 按钮
        {"MOUSEEVENTF_XDOWN", MOUSEEVENTF_XDOWN},
        // X 按钮被释放
        {"MOUSEEVENTF_XUP", MOUSEEVENTF_XUP},
        // 滚轮按钮倾斜
        {"MOUSEEVENTF_HWHEEL", MOUSEEVENTF_HWHEEL}};

    std::string hmc_automation_util::mouseEventName(UINT event)
    {
        for (auto &&MouseEvent : GpMouseEventList)
        {
            if (MouseEvent.second == event)
            {
                return MouseEvent.first;
            }
        }
        return "MOUSEEVENTF_ABSOLUTE";
    }

    UINT hmc_automation_util::mouseEventName(std::string event)
    {

        for (auto &&MouseEvent : GpMouseEventList)
        {
            if (MouseEvent.first == event)
            {
                return MouseEvent.second;
            }
        }
        return MOUSEEVENTF_ABSOLUTE;
    }
}

/**
 * @brief 相对符合w3c标准的 ``
 * @link https://developer.mozilla.org/zh-CN/docs/Web/API/KeyboardEvent/code
 *
 * @param input
 * @return std::string
 */
std::string hmc_automation_util::GpMapVirtualCode(std::uint8_t input)
{
    std::string result;
    result.reserve(32);

    if (input >= 0x30 && input <= 0x39)
    {
        result.append("Digit");
        result.append(GpMapVirtualKey(input));
        return result;
    }

    if (input >= 0x41 && input <= 0x5a)
    {
        result.append("Key");
        result.append(GpMapVirtualKey(input));
        return result;
    }

    if (input >= 0x60 && input <= 0x69)
    {
        result.append("Numpad");
        result.append(GpMapVirtualKey(input));
        return result;
    }

    if (result.empty())
    {
        const std::map<std::uint8_t, std::string> specialKeys = {
            {0x6e, "NumpadDecimal"},
            {0x6a, "NumpadMultiply"},
            {0x6b, "NumpadAdd"},
            {0x6f, "NumpadDivide"},
            {0x6d, "NumpadSubtract"},
            {0x6c, "Separator"},
            {0xba, "Semicolon"},
            {0xbb, "Equal"},
            {0xbc, "Comma"},
            {0xbd, "Minus"},
            {0xbe, "Period"},
            {0xbf, "Slash"},
            {0xc0, "Backquote"},
            {0xdb, "BracketLeft"},
            {0xdc, "Backslash"},
            {0xdd, "BracketRight"},
            {0xde, "Quote"},
            {0x10, "Shift"},
            {0xa0, "ShiftLeft"},
            {0xa1, "ShiftRight"},
            {0x5c, "MetaRight"},
            {0x5b, "MetaLeft"},
            {0x11, "Control"},
            {0xa2, "ControlLeft"},
            {0xa3, "ControlRight"},
            {0xa5, "AltRight"},
            {0xa4, "AltLeft"},
            {0x12, "Alt"},
            {0xE0, "NumpadEnter"}};

        for (auto &special : specialKeys)
        {
            if (special.first == input)
            {
                result.append(special.second);
                return result;
            }
        }
    }

    if (result.empty())
    {
        result.append(GpMapVirtualKey(input));
        return result;
    }

    return result;
}
