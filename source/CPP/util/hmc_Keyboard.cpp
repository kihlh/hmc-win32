#include "hmc_Keyboard.h"

namespace hmc_Keyboard // hmc_Keyboard 是个鼠标操作功能合集
{
    bool _is_Keyboard_Next_Hook = false;                      // 是否继续执行
    HHOOK _This_KeyboardHook = NULL;                          // 钩子句柄
    long long _This_Event_id = 0;                             // 当前id
    std::vector<KeyboardEvent> _This_KeyboardEvent_List;      // 鼠标按钮的事件容器(缓冲)  预扩容了256个
    DWORD _This_HookThreadID = 0;                             // 正在执行hook线程
    
    bool KeyboardEvent::is_valid()
    {
        return id != 0;
    }
    std::string KeyboardEvent::to_json()
    { 
        std::string result = R"({"id":{id},"time":{time},"down":{down},"flags":{flags},"keyCode":{keyCode},"scanCode":{scanCode}})";

        result.replace(result.find("{id}"), sizeof("{id}") - 1, std::to_string(id));
        result.replace(result.find("{time}"), sizeof("{time}") - 1, std::to_string(time));
        result.replace(result.find("{down}"), sizeof("{down}") - 1, down?"true":"false");
        result.replace(result.find("{flags}"), sizeof("{flags}") - 1, std::to_string(flags));
        result.replace(result.find("{keyCode}"), sizeof("{keyCode}") - 1, std::to_string(keyCode));
        result.replace(result.find("{scanCode}"), sizeof("{scanCode}") - 1, std::to_string(scanCode));

        return result;
    }
}

LRESULT CALLBACK hmc_Keyboard::WinApiLowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    // 没有键值
    if (nCode < 0)
    {
        return ::CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT *)lParam; // 低级键盘输入事件信息

    hmc_Keyboard::push_keyboard_data(ks);

    // 将消息传递给钩子链中的下一个钩子
    return ::CallNextHookEx(NULL, nCode, wParam, lParam);
}

bool hmc_Keyboard::InitKeyboardEventHookWorker()
{
    bool result = false;

    if (isStartHookKeyboard())
    {
        return result;
    }

    _This_Event_id = 0;

    if (_This_HookThreadID == NULL)
    {
        _This_HookThreadID = get_ThreadId(std::this_thread::get_id());
    }

    if (_This_KeyboardEvent_List.capacity() > 50)
    {
        _This_KeyboardEvent_List.reserve(128);
    }

    if (!_This_HookThreadID)
    {
        return result;
    }
    _is_Keyboard_Next_Hook = true;
    _This_KeyboardEvent_List.clear();

    _This_KeyboardHook = ::SetWindowsHookExW(
        WH_KEYBOARD_LL,             // 钩子类型 安装用于监视低级别键盘输入事件的挂钩过程 与  安装用于监视低级别鼠标输入事件的挂钩过程
        WinApiLowLevelKeyboardProc, // 指向钩子函数的指针
        GetModuleHandleA(NULL),     // 没有模块句柄
        NULL);

    if (_This_KeyboardHook == 0)
    {
        return false;
    }

    BOOL bRet;
    MSG msg;

    // 获取消息循环
    while ((bRet = ::GetMessageW(&msg, nullptr, 0, 0)) != 0)
    {
        if (bRet == -1 || (!_is_Keyboard_Next_Hook || !_This_HookThreadID || _This_KeyboardHook == NULL))
        {
            break;
        }
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    if (_This_KeyboardHook != NULL)
    {

        // 移除系统钩子
        ::UnhookWindowsHookEx(_This_KeyboardHook);
    }

    _This_KeyboardEvent_List.clear();
    _is_Keyboard_Next_Hook = false;
    _This_Event_id = 0;
    _This_HookThreadID = 0;
    _This_KeyboardHook = NULL;

    return true;
}

DWORD hmc_Keyboard::get_ThreadId(std::thread::id thread_id)
{
    DWORD ThreadIdAsInt = 0;

    try
    {
        ThreadIdAsInt = *static_cast<DWORD *>(static_cast<void *>(&thread_id));
    }
    catch (...)
    {
    }
    return ThreadIdAsInt;
}

DWORD hmc_Keyboard::get_ThreadId()
{
    return _This_HookThreadID;
}

bool hmc_Keyboard::initKeyboardEventHook()
{
    bool result = false;

    if (isStartHookKeyboard())
    {
        return result;
    }

    std::thread new_thread = std::thread(InitKeyboardEventHookWorker);

    _This_HookThreadID = get_ThreadId(new_thread.get_id());

    new_thread.detach();

    result = _This_HookThreadID != 0;
    return result;
}

bool hmc_Keyboard::isStartHookKeyboard()
{

    if (!_is_Keyboard_Next_Hook)
    {
        if (_This_KeyboardHook != NULL)
        {

            if (!::UnhookWindowsHookEx(_This_KeyboardHook))
            {
                ::UnhookWindowsHookEx(_This_KeyboardHook);
            }

            _This_KeyboardHook = NULL;
        }
    }

    return _is_Keyboard_Next_Hook;
}

void hmc_Keyboard::push_keyboard_data(KBDLLHOOKSTRUCT *input)
{
    bool is_open_mutex = false;

    KeyboardEvent data = KeyboardEvent();

    data.keyCode = input->vkCode;
    data.scanCode = input->scanCode;
    data.id = _This_Event_id;
    data.time = input->time;
    data.flags = input->flags;
    data.down = (input->flags < 128);

    _This_KeyboardEvent_List.push_back(data);

    _This_Event_id = _This_Event_id + 1;
}

std::string hmc_Keyboard::getAllKeyboardEventJson() {
    std::string result = "[";

    auto AllKeyboardEvent = hmc_Keyboard::getAllKeyboardEvent();
    auto length = AllKeyboardEvent.size();

    for (size_t i = 0; i < length; i++)
    {
        auto& it = AllKeyboardEvent[i];
        if (it.is_valid()) {
            result.append(it.to_json());
        }
        
        if (i + 1 < length) {
            result.push_back(',');
        }
    }

    result.push_back(']');

    return result;
}

std::vector<hmc_Keyboard::KeyboardEvent> hmc_Keyboard::getAllKeyboardEvent()
{
    std::vector<KeyboardEvent> event_list;

    size_t len = _This_KeyboardEvent_List.size();

    if (len <= 0)
    {
        return event_list;
    }

    for (size_t i = 0; i < len; i++)
    {

        event_list.push_back(_This_KeyboardEvent_List[i]);
    }

    _This_KeyboardEvent_List.erase(_This_KeyboardEvent_List.begin(), _This_KeyboardEvent_List.begin() + len);

    return event_list;
}

bool hmc_Keyboard::gcHookKeyboard()
{
    if (!_is_Keyboard_Next_Hook)
    {
        if (_This_KeyboardHook != NULL)
        {

            if (!::UnhookWindowsHookEx(_This_KeyboardHook))
            {
                ::UnhookWindowsHookEx(_This_KeyboardHook);
            }

            _This_KeyboardEvent_List.clear();
            _is_Keyboard_Next_Hook = false;
            _This_Event_id = 0;
            _This_HookThreadID = 0;
            _This_KeyboardHook = NULL;
            return true;
        }
        return true;
    }

    bool is_unHook = _This_KeyboardHook == NULL ? true : ::UnhookWindowsHookEx(_This_KeyboardHook);
    bool is_kiilThread = _This_HookThreadID == NULL ? true : ::PostThreadMessageW(_This_HookThreadID, WM_QUIT, NULL, NULL);

    _This_KeyboardEvent_List.clear();
    _is_Keyboard_Next_Hook = false;
    _This_Event_id = 0;
    _This_HookThreadID = 0;
    _This_KeyboardHook = NULL;

    return is_kiilThread || is_unHook;
}