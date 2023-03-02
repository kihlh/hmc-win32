#include "./Mian.hpp";

HHOOK keyboardHook = 0; // 钩子句柄、
HHOOK MouseHook = 0;    // 钩子句柄、
bool Keyboard_HOOK_next = false;
bool Mouse_HOOK_next = false;
vector<vector<int>> KeyboardRecordList;
vector<vector<int>> MouseRecordList;

int oid_is_key_Down = 0;
int oid_is_key_vkCode = 0;

LRESULT CALLBACK LowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    // 没有键值
    if (nCode < 0)
    {
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT *)lParam; // 低级键盘输入事件信息
    bool is_Down = false;
    if (ks->flags < 128)
    {
        is_Down = true;
    }
    int i_is_Down = is_Down ? 1 : 0;
    int vkCode = (int)ks->vkCode;
    if (oid_is_key_Down != i_is_Down || vkCode != oid_is_key_vkCode)
    {
        vector<int> push = {vkCode, i_is_Down};
        // 监控键盘
        // cout << (ks->vkCode) << "->" << is_Down << endl;
        oid_is_key_Down = i_is_Down;
        oid_is_key_vkCode = vkCode;
        KeyboardRecordList.push_back(push);
    }

    // 将消息传递给钩子链中的下一个钩子
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int oid_MouseRecord_x = 0;
int oid_MouseRecord_y = 0;
int oid_MouseRecord_isDown = 0;
clock_t MouseRecord_update_time = clock();

LRESULT CALLBACK Call_MouseHook(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    // 没有键值
    if (nCode < 0)
    {
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    MOUSEHOOKSTRUCT *ms = (MOUSEHOOKSTRUCT *)lParam; // 低级键盘输入事件信息
    int x = 0;
    int y = 0;
    int isDown = 0;
    if (ms->pt.x > 0 && ms->pt.x < 400000000)
    {
        x = ms->pt.x;
    }
    if (ms->pt.y > 0 && ms->pt.y < 400000000)
    {
        y = ms->pt.y;
    }

    // 按下了
    if (wParam == WM_LBUTTONDOWN)
        isDown = 1;
    // 降低反馈的刷新激进程度 为每次相距10px以上（且间隔15ms）  或者有松放变化 或者超过45ms 数据无变化时拒绝反馈
    clock_t end = clock();

    if (x != oid_MouseRecord_x && y != oid_MouseRecord_y || isDown != oid_MouseRecord_isDown)
        if (
            // 间隔大于45ms
            (end - MouseRecord_update_time > 45) ||
            // 相距上次的数据5px以上
            (((x - oid_MouseRecord_x > 10 || x - oid_MouseRecord_x > -10) ||
              (y - oid_MouseRecord_y > 10 || y - oid_MouseRecord_y > -10)) &&
             end - MouseRecord_update_time > 15) ||
            // 按键按下或者取消有变化
            isDown != oid_MouseRecord_isDown)
        {

            // 监控鼠标
            vector<int> push = {x, y, isDown};
            MouseRecordList.push_back(push);
            MouseRecord_update_time = clock();
            oid_MouseRecord_x = x;
            oid_MouseRecord_y = y;
            oid_MouseRecord_isDown = isDown;
        }
    // cout << x << "-" << y << "-" << isDown << endl;
    // 将消息传递给钩子链中的下一个钩子
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void InstallKeyboardHook()
{
    Keyboard_HOOK_next = true;

    keyboardHook = SetWindowsHookExA(
        WH_KEYBOARD_LL,         // 钩子类型 安装用于监视低级别键盘输入事件的挂钩过程 与  安装用于监视低级别鼠标输入事件的挂钩过程
        LowLevelKeyboardProc,   // 指向钩子函数的指针
        GetModuleHandleA(NULL), // 没有模块句柄
        NULL);
    if (keyboardHook == 0)
    {
        return;
    }

    // 消息处理 并且每次都进行返回
    MSG tagMSG;
    while (Keyboard_HOOK_next)
    {
        // 如果消息队列中有消息
        if (PeekMessageA(&tagMSG, NULL, NULL, NULL, PM_REMOVE))
        {
            // 按键消息传递给字符消息
            TranslateMessage(&tagMSG);

            // 消息分发给窗口程序处理
            DispatchMessageA(&tagMSG);
        }
        else
            Sleep(2); // 避免资源消耗
    }
    // 移除系统钩子
    UnhookWindowsHookEx(keyboardHook);
    KeyboardRecordList.clear();
}

void InstallHookMouse()
{
    Mouse_HOOK_next = true;

    MouseHook = SetWindowsHookExA(
        WH_MOUSE_LL,            // 钩子类型 安装用于监视低级别键盘输入事件的挂钩过程 与  安装用于监视低级别鼠标输入事件的挂钩过程
        Call_MouseHook,         // 指向钩子函数的指针
        GetModuleHandleA(NULL), // 没有模块句柄
        NULL);
    if (MouseHook == 0)
    {
        return;
    }

    // 消息处理 并且每次都进行返回
    MSG tagMSG;
    while (Mouse_HOOK_next)
    {
        // 如果消息队列中有消息
        if (PeekMessageA(&tagMSG, NULL, NULL, NULL, PM_REMOVE))
        {
            // 按键消息传递给字符消息
            TranslateMessage(&tagMSG);

            // 消息分发给窗口程序处理
            DispatchMessageA(&tagMSG);
        }
        else
            Sleep(2); // 避免资源消耗
    }
    // 移除系统钩子
    UnhookWindowsHookEx(MouseHook);
    MouseRecordList.clear();
}

napi_value installKeyboardHook(napi_env env, napi_callback_info info)
{
    if (Keyboard_HOOK_next)
    {
        return NULL;
    }
    std::thread(InstallKeyboardHook).detach();
    return NULL;
}

napi_value installHookMouse(napi_env env, napi_callback_info info)
{
    if (Mouse_HOOK_next)
    {
        return NULL;
    }
    std::thread(InstallHookMouse).detach();
    return NULL;
}

napi_value unKeyboardHook(napi_env env, napi_callback_info info)
{
    Keyboard_HOOK_next = false;
    KeyboardRecordList.clear();
    return NULL;
}

napi_value unHookMouse(napi_env env, napi_callback_info info)
{
    Mouse_HOOK_next = false;
    MouseRecordList.clear();
    return NULL;
}

napi_value getMouseNextSession(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    if (!Mouse_HOOK_next || !MouseRecordList.size())
    {
        return NULL;
    }
    status = napi_create_array(env, &Results);
    assert(status == napi_ok);
    // 复制并清空上次的所有记录
    vector<vector<int>> copy_MouseRecordList;
    for (int index = 0; index < MouseRecordList.size(); index++)
    {
        vector<int> mouse = MouseRecordList[index];
        copy_MouseRecordList.push_back(mouse);
    }
    MouseRecordList.clear();

    // 枚举并返回数据
    for (int index = 0; index < copy_MouseRecordList.size(); index++)
    {
        vector<int> mouse = copy_MouseRecordList[index];
        // "x|y|is"
        string mouseInfo = "";
        mouseInfo.append(to_string(mouse[0]));
        mouseInfo.append("|");
        mouseInfo.append(to_string(mouse[1]));
        mouseInfo.append("|");
        mouseInfo.append(to_string(mouse[2]));
        // push
        status = napi_set_element(env, Results, index, _create_String(env, mouseInfo));
        if (status != napi_ok)
        {
            return Results;
        };
        mouse.clear();
    }

    return Results;
}

napi_value getKeyboardNextSession(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    if (!Keyboard_HOOK_next || !KeyboardRecordList.size())
    {
        return NULL;
    }
    status = napi_create_array(env, &Results);
    assert(status == napi_ok);

    // 复制并清空上次的所有记录
    vector<vector<int>> copy_KeyboardRecordList;
    for (int index = 0; index < KeyboardRecordList.size(); index++)
    {
        vector<int> mouse = KeyboardRecordList[index];
        copy_KeyboardRecordList.push_back(mouse);
    }
    KeyboardRecordList.clear();

    // 枚举并返回数据
    for (int index = 0; index < copy_KeyboardRecordList.size(); index++)
    {
        vector<int> keyboard = copy_KeyboardRecordList[index];
        // "key|is"
        string keyboardInfo = "";
        keyboardInfo.append(to_string(keyboard[0]));
        keyboardInfo.append("|");
        keyboardInfo.append(to_string(keyboard[1]));
        // push
        status = napi_set_element(env, Results, index, _create_String(env, keyboardInfo));
        if (status != napi_ok)
        {
            return Results;
        };
        keyboard.clear();
    }

    return Results;
}

napi_value isStartKeyboardHook(napi_env env, napi_callback_info info)
{
    return _create_bool_Boolean(env, Keyboard_HOOK_next);
}

napi_value isStartHookMouse(napi_env env, napi_callback_info info)
{
    return _create_bool_Boolean(env, Mouse_HOOK_next);
}

// 判断是否按下三大金刚
napi_value getBasicKeys(napi_env env, napi_callback_info info)
{
    napi_value Points;
    napi_create_object(env, &Points);
    napi_set_property(env, Points, _create_char_string(env, "shift"), _create_bool_Boolean(env, GetKeyState(VK_SHIFT) & 0x8000));
    napi_set_property(env, Points, _create_char_string(env, "alt"), _create_bool_Boolean(env, GetKeyState(VK_MENU) & 0x8000));
    napi_set_property(env, Points, _create_char_string(env, "ctrl"), _create_bool_Boolean(env, GetKeyState(VK_CONTROL) & 0x8000));
    napi_set_property(env, Points, _create_char_string(env, "win"), _create_bool_Boolean(env, GetKeyState(VK_RWIN) & 0x8000 || GetKeyState(VK_LWIN) & 0x8000));
    return Points;
}

// 设置键盘位置
napi_value setCursorPos(napi_env env, napi_callback_info info)
{
    napi_status status;
    const size_t M_Size = 2;
    size_t argc = M_Size;
    napi_value args[M_Size];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);
    }
    int x;
    napi_get_value_int32(env, args[0], &x);

    int y;
    napi_get_value_int32(env, args[1], &y);

    return _create_bool_Boolean(env, SetCursorPos(x, y));
}

// 右键点击
napi_value rightClick(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    int Set_Sleep_time;
    if (argc < 1)
        Set_Sleep_time = 0;
    if (argc)
        napi_get_value_int32(env, args[0], &Set_Sleep_time);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    if (Set_Sleep_time)
        Sleep(Set_Sleep_time);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    return NULL;
}

// 左键点击
napi_value leftClick(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    int Set_Sleep_time;
    if (argc < 1)
        Set_Sleep_time = 0;
    if (argc)
        napi_get_value_int32(env, args[0], &Set_Sleep_time);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    if (Set_Sleep_time)
        Sleep(Set_Sleep_time);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    return NULL;
}

// 获取鼠标前64次的位置
napi_value getMouseMovePoints(napi_env env, napi_callback_info info)
{
    // 当前的鼠标位置
    POINT currentMousePosition = {0};
    GetCursorPos(&currentMousePosition);
    // 放置鼠标位置的容器
    MOUSEMOVEPOINT mousePositionContainer = {0};
    mousePositionContainer.x = currentMousePosition.x;
    mousePositionContainer.y = currentMousePosition.y;
    // 微软规定只会返回的最大数据为64 任何大于64的值都是错误的
    const DWORD dwMaxPoints = 64;
    // 鼠标轨迹列表
    MOUSEMOVEPOINT mobileProgressList[dwMaxPoints] = {0};
    const DWORD dwMode = GMMP_USE_DISPLAY_POINTS;
    // 获取全部的 鼠标轨迹 并返回轨迹数量
    const int PointsLength = GetMouseMovePointsEx(sizeof(mousePositionContainer), &mousePositionContainer, mobileProgressList, dwMaxPoints, dwMode);
    // 容器
    napi_value mobileProgressJavaScriptArrayList;
    napi_create_array(env, &mobileProgressJavaScriptArrayList);
    for (int PointsIndex = 0; PointsIndex < PointsLength; PointsIndex++)
    {
        napi_value Points;
        napi_create_object(env, &Points);
        napi_set_property(env, Points, _create_char_string(env, "x"), _create_int64_Number(env, mobileProgressList[PointsIndex].x));
        napi_set_property(env, Points, _create_char_string(env, "y"), _create_int64_Number(env, mobileProgressList[PointsIndex].y));
        napi_set_property(env, Points, _create_char_string(env, "time"), _create_int64_Number(env, mobileProgressList[PointsIndex].time));
        napi_set_property(env, Points, _create_char_string(env, "dwExtraInfo"), _create_int64_Number(env, mobileProgressList[PointsIndex].dwExtraInfo));
        // [].push({x:number, y:number,time:number,dwExtraInfo:number});
        napi_set_element(env, mobileProgressJavaScriptArrayList, PointsIndex, Points);
    }

    return mobileProgressJavaScriptArrayList;
}

// 判断是否按下当前按键
napi_value hasKeyActivate(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    int theCurrentKey;
    if (argc)
    {
        size_t argc = 1;
        napi_value args[1];
        status = $napi_get_cb_info(argc, args);
        assert(status == napi_ok);

        napi_valuetype valuetype;
        status = napi_typeof(env, args[0], &valuetype);
        assert(status == napi_ok);

        if (valuetype != napi_number)
        {
            napi_throw_type_error(env, NULL, "Wrong arguments");
            return NULL;
        }
        napi_get_value_int32(env, args[0], &theCurrentKey);
    }
    return _create_bool_Boolean(env, GetKeyState(theCurrentKey) & 0x8000);
}

// 自定义点击事件
napi_value mouse(napi_env env, napi_callback_info info)
{
    napi_status status;
    const size_t M_Size = 2;
    size_t argc = M_Size;
    napi_value args[M_Size];
    status = $napi_get_cb_info(argc, args);
    int Set_event;
    int Set_Sleep_time;
    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    switch (argc)
    {
    case 0:
        napi_throw_type_error(env, NULL, "Wrong arguments size=> 0");
        return NULL;
    case 1:
        Set_Sleep_time = 0;
        break;
    case 2:
        napi_get_value_int32(env, args[1], &Set_Sleep_time);
        break;
    }
    if (valuetype0 == napi_number)
    {
        napi_get_value_int32(env, args[0], &Set_event);
    }
    else if (valuetype0 == napi_string)
    {
        string lpParameters0 = call_String_NAPI_WINAPI_A(env, args[1]);
        if (lpParameters0 == "MOUSEEVENTF_ABSOLUTE")
            Set_event = MOUSEEVENTF_ABSOLUTE;
        else if (lpParameters0 == "MOUSEEVENTF_LEFTDOWN")
            Set_event = MOUSEEVENTF_LEFTDOWN;
        else if (lpParameters0 == "MOUSEEVENTF_LEFTUP")
            Set_event = MOUSEEVENTF_LEFTUP;
        else if (lpParameters0 == "MOUSEEVENTF_MIDDLEDOWN")
            Set_event = MOUSEEVENTF_MIDDLEDOWN;
        else if (lpParameters0 == "MOUSEEVENTF_MIDDLEUP")
            Set_event = MOUSEEVENTF_MIDDLEUP;
        else if (lpParameters0 == "MOUSEEVENTF_MOVE")
            Set_event = MOUSEEVENTF_MOVE;
        else if (lpParameters0 == "MOUSEEVENTF_RIGHTDOWN")
            Set_event = MOUSEEVENTF_RIGHTDOWN;
        else if (lpParameters0 == "MOUSEEVENTF_WHEEL")
            Set_event = MOUSEEVENTF_WHEEL;
        else if (lpParameters0 == "MOUSEEVENTF_XDOWN")
            Set_event = MOUSEEVENTF_XDOWN;
        else if (lpParameters0 == "MOUSEEVENTF_XUP")
            Set_event = MOUSEEVENTF_XUP;
        else if (lpParameters0 == "MOUSEEVENTF_HWHEEL")
            Set_event = MOUSEEVENTF_HWHEEL;
        else
            Set_event = MOUSEEVENTF_MOVE;
    }
    else
    {
        napi_throw_type_error(env, NULL, "Parameter types are not supported");
        return NULL;
    }
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    if (Set_Sleep_time)
        Sleep(Set_Sleep_time);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    return NULL;
}
