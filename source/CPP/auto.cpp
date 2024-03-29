#include "./Mian.hpp";
#include "hmc_automation_util.h";
#include "hmc_napi_value_util.h"

HHOOK keyboardHook = 0; // 钩子句柄、
HHOOK MouseHook = 0;    // 钩子句柄、
bool Keyboard_HOOK_next = false;
bool Mouse_HOOK_next = false;
vector<vector<int>> KeyboardRecordList;

int oid_is_key_Down = 0;
int oid_is_key_vkCode = 0;

void asyncLowLevelKeyboardProc(KBDLLHOOKSTRUCT *ks)
{
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
        cout << (ks->vkCode) << "->" << is_Down << endl;
        oid_is_key_Down = i_is_Down;
        oid_is_key_vkCode = vkCode;
        KeyboardRecordList.push_back(push);
    }
}
LRESULT CALLBACK LowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    // 没有键值
    if (nCode < 0)
    {
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT *)lParam; // 低级键盘输入事件信息
    std::thread(asyncLowLevelKeyboardProc, ks).detach();

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


	BOOL bRet;
	MSG msg;

	// 获取消息循环
	while ((bRet = GetMessageW(&msg, nullptr, 0, 0)) != 0)
	{ 
		if (bRet == -1 || (!Keyboard_HOOK_next || keyboardHook == NULL))
		{
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

    // 移除系统钩子
    UnhookWindowsHookEx(keyboardHook);
    KeyboardRecordList.clear();
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

napi_value unKeyboardHook(napi_env env, napi_callback_info info)
{
    Keyboard_HOOK_next = false;
    if (KeyboardRecordList.size() > 0)
    {
        for (size_t i = 0; i < KeyboardRecordList.size(); i++)
        {
            // 释放数组 里的int数组内存
            KeyboardRecordList[i].clear();
        }
        // 释放数组
        for (size_t i = 0; i < KeyboardRecordList.size(); i++)
        {
            KeyboardRecordList.erase(KeyboardRecordList.begin());
        }
    }
    return NULL;
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
        status = napi_set_element(env, Results, index, as_String( keyboardInfo));
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
    return as_Boolean( Keyboard_HOOK_next);
}

// 判断是否按下三大金刚
napi_value getBasicKeys(napi_env env, napi_callback_info info)
{
    napi_value Points;
    napi_create_object(env, &Points);
    napi_set_property(env, Points,as_String( "shift"), as_Boolean( GetKeyState(VK_SHIFT) & 0x8000));
    napi_set_property(env, Points,as_String( "alt"), as_Boolean( GetKeyState(VK_MENU) & 0x8000));
    napi_set_property(env, Points,as_String( "ctrl"), as_Boolean( GetKeyState(VK_CONTROL) & 0x8000));
    napi_set_property(env, Points,as_String( "win"), as_Boolean( GetKeyState(VK_RWIN) & 0x8000 || GetKeyState(VK_LWIN) & 0x8000));
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

    return as_Boolean( SetCursorPos(x, y));
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
    return as_Boolean( GetKeyState(theCurrentKey) & 0x8000);
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
        string lpParameters0 = hmc_napi_get_value::string_ansi(env, args[1]);
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

UINT _sendInput(UINT cInputs, LPINPUT pInputs, int cbSize)
{
    HMODULE hUser32 = LoadLibraryA("user32.dll");
    UINT uSent;
    uSent = 0;
    if (hUser32)
    {
        UINT(_stdcall * pSendInput)
        (UINT cInputs, LPINPUT pInputs, int cbSize);

        pSendInput = (UINT(_stdcall *)(UINT cInputs, LPINPUT pInputs, int cbSize))GetProcAddress(hUser32, "SendInput");
        if (pSendInput)
        {
            uSent = pSendInput(cInputs, pInputs, cbSize);
        }
        FreeLibrary(hUser32);
    }
    return uSent;
}

bool util_sendKeyboardSingle(WORD keyCode, bool keyDown)
{

    // sendInput很奇怪的bug 当调用取消Win按下的时候他主动按下了一次
    // Keyboard {vKey: 91, __isDown: true, keyCode: 91, key: 'Win', code: 'MetaLeft'}
    //  Keyboard {vKey: 82, __isDown: true, keyCode: 82, key: 'R', code: 'KeyR'}
    //  Keyboard {vKey: 82, __isDown: false, keyCode: 82, key: 'R', code: 'KeyR'}
    //  Keyboard {vKey: 91, __isDown: true, keyCode: 91, key: 'Win', code: 'MetaLeft'}
    //  Keyboard {vKey: 91, __isDown: false, keyCode: 91, key: 'Win', code: 'MetaLeft'}
    if (keyDown == NULL)
    {
        INPUT inputs[2] = {};
        ZeroMemory(inputs, sizeof(inputs));
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = keyCode;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = keyCode;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
        UINT uSent = _sendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            return false;
        }
        return true;
    }

    INPUT inputs[1] = {};
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = keyCode;

    if (!keyDown)
    {
        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
    }

    UINT uSent = _sendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
        return false;
    }

    return true;
    // keybd_event还是一样 留着以后解决  三金刚按键的响应单独的api完成
    // if (keyDown == NULL)
    // {
    //     INPUT inputs[2] = {};
    //     ZeroMemory(inputs, sizeof(inputs));
    //     inputs[0].type = INPUT_KEYBOARD;
    //     inputs[0].ki.wVk = keyCode;

    //     inputs[1].type = INPUT_KEYBOARD;
    //     inputs[1].ki.wVk = keyCode;
    //     inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
    //     UINT uSent = _sendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    //     if (uSent != ARRAYSIZE(inputs))
    //     {
    //         return false;
    //     }
    //     return true;
    // }
    // else if (!keyDown)
    // {
    //     keybd_event(keyCode, KEYEVENTF_KEYUP, 0, 0); // 放开C键
    //     return true;
    // }

    // INPUT inputs[1] = {};
    // ZeroMemory(inputs, sizeof(inputs));

    // inputs[0].type = INPUT_KEYBOARD;
    // inputs[0].ki.wVk = keyCode;

    // UINT uSent = _sendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    // if (uSent != ARRAYSIZE(inputs))
    // {
    //     return false;
    // }

    // return true;
}

// 自定义点击事件
napi_value sendKeyboard(napi_env env, napi_callback_info info)
{
    napi_status status;
    const size_t M_Size = 2;
    size_t argc = M_Size;
    napi_value argv[M_Size];
    status = $napi_get_cb_info(argc, argv);
    napi_value results = as_Boolean( false);

    // argv ...
    int32_t keyCode;
    bool keyDown = NULL;

    // 检测参数合法性

    switch (argc)
    {
    case 0:
        hmc_is_argc_size(argc, 1, results);
        break;
    case 1:
        napi_get_value_int32(env, argv[0], &keyCode);
        hmc_is_argv_type(argv, 0, NULL, napi_number, results);
        break;
    case 2:
        napi_get_value_int32(env, argv[0], &keyCode);
        hmc_is_argv_type(argv, 1, NULL, napi_boolean, results);
        napi_get_value_bool(env, argv[1], &keyDown);
        break;
    }

    results = as_Boolean( util_sendKeyboardSingle(keyCode, keyDown));

    return results;
}

struct keyDown_T2C_Conte
{
    int keyCode;
    bool isDown;
    int ms;
};

// 判断内容是否为全数字
bool is_digits(const string &str)
{
    return all_of(str.begin(), str.end(), ::isdigit);
}

void textKeyCode2Vector(string input, vector<keyDown_T2C_Conte> *T2C_List)
{
    size_t line_pos = 0;
    string line_token;

    while ((line_pos = input.find("\n")) != string::npos)
    {
        line_token = input.substr(0, line_pos);
        line_token.append("|");
        vector<string> arr;
        size_t single_pos = 0;
        string single_token;

        // line_token => 0|true|50|

        while ((single_pos = line_token.find("|")) != string::npos)
        {
            single_token = line_token.substr(0, single_pos);
            arr.push_back(single_token);
            line_token.erase(0, single_pos + 1);
        }

        //   arr =>  [0,true,50]
        if (arr.size() >= 3)
        {
            if (is_digits(arr[2]) && is_digits(arr[0]))
            {
                keyDown_T2C_Conte t2c;
                // t2c.ms = stoll(arr[2].c_str());
                // t2c.keyCode = stoll(arr[0].c_str());
                try
                {
                    //  此处不使用 stoll  因为 key值肯定没那么大 超过int了 必然是错误的
                    t2c.ms = atoi(arr[2].c_str());
                    t2c.keyCode = atoi(arr[0].c_str());
                }
                catch (const std::exception &e)
                {
                    t2c.ms = 0;
                    t2c.keyCode = 0;
                };

                // bool = .isDown
                if (arr[1] == "true")
                {
                    t2c.isDown = true;
                }
                else if (arr[1] == "false")
                {
                    t2c.isDown = false;
                }
                else
                {
                    t2c.isDown = NULL;
                }
                if (t2c.ms < 9999999 && t2c.ms >= 0 && t2c.keyCode > 0 && t2c.keyCode < 9999)
                    T2C_List->push_back(t2c);
            }
        }
        input.erase(0, line_pos + 1);
    }
}

int util_sendKeyT2C(string send_t2cStrA)
{
    vector<keyDown_T2C_Conte> T2C_List;
    textKeyCode2Vector(send_t2cStrA, &T2C_List);

    for (size_t i = 0; i < T2C_List.size(); i++)
    {
        keyDown_T2C_Conte t2c = T2C_List[i];
        // cout << "t2c=>"
        //      << "key:" << t2c.keyCode << ",down:" << t2c.isDown << ",ms:" << t2c.ms << endl;
        if (t2c.ms != 0)
        {
            Sleep(t2c.ms);
        }
        util_sendKeyboardSingle(t2c.keyCode, t2c.isDown);
    }

    return 0;
}
// 自定t2c指令解析
napi_value sendKeyT2CSync(napi_env env, napi_callback_info info)
{
    napi_status status;
    const size_t M_Size = 2;
    size_t argc = M_Size;
    napi_value argv[M_Size];
    status = $napi_get_cb_info(argc, argv);
    string send_textA;
    // argv ...
    char sendCodeStr;
    switch (argc)
    {
    case 0:
        hmc_is_argc_size(argc, 1, NULL);
        break;
    case 1:
        send_textA = hmc_napi_get_value::string_ansi(env, argv[0]);
        hmc_is_argv_type(argv, 0, NULL, napi_string, NULL);
        break;
    }
    util_sendKeyT2C(send_textA);
    return NULL;
}

// 自定t2c指令解析
napi_value sendKeyT2C(napi_env env, napi_callback_info info)
{
    napi_status status;
    const size_t M_Size = 2;
    size_t argc = M_Size;
    napi_value argv[M_Size];
    status = $napi_get_cb_info(argc, argv);
    string send_textA;
    // argv ...
    char sendCodeStr;
    switch (argc)
    {
    case 0:
        hmc_is_argc_size(argc, 1, NULL);
        break;
    case 1:
        send_textA = hmc_napi_get_value::string_ansi(env, argv[0]);
        hmc_is_argv_type(argv, 0, NULL, napi_string, NULL);
        break;
    }
    std::thread(util_sendKeyT2C, send_textA).detach();
    // util_sendKeyT2C(send_textA);
    return NULL;
}

// 自定义 标准快捷键响应
napi_value sendBasicKeys(napi_env env, napi_callback_info info)
{
    napi_status status;
    const size_t M_Size = 5;
    size_t argc = M_Size;
    napi_value argv[M_Size];
    status = $napi_get_cb_info(argc, argv);
    hmc_is_argc_size(argc, 5, NULL);
    hmc_is_argv_type(argv, 0, 4, napi_boolean, NULL);
    hmc_is_argv_type(argv, 4, NULL, napi_number, NULL);
    napi_value results = as_Boolean( false);
    bool ctrlKey, shiftKey, altKey, winKey;
    int keyCode;
    // sendBasicKeys(ctrlKey, shiftKey, altKey, winKey , keyCode);
    napi_get_value_bool(env, argv[0], &ctrlKey);
    napi_get_value_bool(env, argv[1], &shiftKey);
    napi_get_value_bool(env, argv[2], &altKey);
    napi_get_value_bool(env, argv[3], &winKey);
    napi_get_value_int32(env, argv[4], &keyCode);
    WORD _ctrlKey = 162;
    WORD _shiftKey = 160;
    WORD _winKey = 91;
    WORD _altKey = 164;

    if (!ctrlKey)
        _ctrlKey = NULL;
    if (!shiftKey)
        _shiftKey = NULL;
    if (!winKey)
        _winKey = NULL;
    if (!altKey)
        _altKey = NULL;

    if (keyCode > 9999 || keyCode < 0)
    {
        napi_throw_type_error(env, 0, "The number of parameters >9999 and <0 ");
    }
    const int hp_size = int(ctrlKey) + int(shiftKey) + int(altKey) + int(winKey);

    switch (hp_size)
    {
    case 0:
    {
        napi_throw_type_error(env, 0, "The ctrlKey,shiftKey,altKey,winKey is All false");
        return NULL;
    }
    case 1:
    {
        // 动态创建很容易嘎掉 只能固定了 人和程序有一个能跑就行了
        INPUT inputs[4] = {};
        ZeroMemory(inputs, sizeof(inputs));
        WORD BasicKeys_wVk = ctrlKey ? 162 : shiftKey ? 160
                                         : altKey     ? 164
                                                      : 91;
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = BasicKeys_wVk;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = keyCode;

        inputs[2].type = INPUT_KEYBOARD;
        inputs[2].ki.wVk = keyCode;
        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

        inputs[3].type = INPUT_KEYBOARD;
        inputs[3].ki.wVk = BasicKeys_wVk;
        inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

        UINT uSent = _sendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            return results;
        }
        break;
    }
    case 2:
    {
        INPUT inputs[6] = {};
        ZeroMemory(inputs, sizeof(inputs));
        WORD BasicKeys_wVk2 = _altKey ? _altKey : _winKey ? _winKey
                                              : _shiftKey ? _shiftKey
                                                          : _ctrlKey;
        WORD BasicKeys_wVk1 = _ctrlKey ? _ctrlKey : _shiftKey ? _shiftKey
                                                : _winKey     ? _winKey
                                                              : _altKey;
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = BasicKeys_wVk2;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = BasicKeys_wVk1;

        inputs[2].type = INPUT_KEYBOARD;
        inputs[2].ki.wVk = keyCode;

        inputs[3].type = INPUT_KEYBOARD;
        inputs[3].ki.wVk = keyCode;
        inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
        
        inputs[4].type = INPUT_KEYBOARD;
        inputs[4].ki.wVk = BasicKeys_wVk1;
        inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

        inputs[5].type = INPUT_KEYBOARD;
        inputs[5].ki.wVk = BasicKeys_wVk2;
        inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

        UINT uSent = _sendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            return results;
        }
        break;
    }
    case 3:
    {
        INPUT inputs[8] = {};
        ZeroMemory(inputs, sizeof(inputs));
        WORD BasicKeys_wVk1 = _ctrlKey ? _ctrlKey : _shiftKey ? _shiftKey
                                                : _winKey     ? _winKey
                                                              : _altKey;
        WORD BasicKeys_wVk2 = _altKey ? _altKey : _winKey ? _winKey
                                              : _shiftKey ? _shiftKey
                                                          : _ctrlKey;
        WORD BasicKeys_wVk3 = _winKey ? _winKey : _shiftKey;

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = BasicKeys_wVk2;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = BasicKeys_wVk1;

        inputs[2].type = INPUT_KEYBOARD;
        inputs[2].ki.wVk = BasicKeys_wVk3;

        inputs[3].type = INPUT_KEYBOARD;
        inputs[3].ki.wVk = keyCode;

        inputs[4].type = INPUT_KEYBOARD;
        inputs[4].ki.wVk = keyCode;
        inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

        inputs[5].type = INPUT_KEYBOARD;
        inputs[5].ki.wVk = BasicKeys_wVk1;
        inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

        inputs[6].type = INPUT_KEYBOARD;
        inputs[6].ki.wVk = BasicKeys_wVk3;
        inputs[6].ki.dwFlags = KEYEVENTF_KEYUP;

        inputs[7].type = INPUT_KEYBOARD;
        inputs[7].ki.wVk = BasicKeys_wVk2;
        inputs[7].ki.dwFlags = KEYEVENTF_KEYUP;

        UINT uSent = _sendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            return results;
        }
        break;
    }
    case 4:
    {
        INPUT inputs[10] = {};
        ZeroMemory(inputs, sizeof(inputs));

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = 162;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = 160;

        inputs[2].type = INPUT_KEYBOARD;
        inputs[2].ki.wVk = 164;

        inputs[3].type = INPUT_KEYBOARD;
        inputs[3].ki.wVk = 91;

        inputs[4].type = INPUT_KEYBOARD;
        inputs[4].ki.wVk = keyCode;

        inputs[5].type = INPUT_KEYBOARD;
        inputs[5].ki.wVk = keyCode;
        inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

        inputs[6].type = INPUT_KEYBOARD;
        inputs[6].ki.wVk = 162;
        inputs[6].ki.dwFlags = KEYEVENTF_KEYUP;

        inputs[7].type = INPUT_KEYBOARD;
        inputs[7].ki.wVk = 160;
        inputs[7].ki.dwFlags = KEYEVENTF_KEYUP;

        inputs[8].type = INPUT_KEYBOARD;
        inputs[8].ki.wVk = 164;
        inputs[8].ki.dwFlags = KEYEVENTF_KEYUP;

        inputs[9].type = INPUT_KEYBOARD;
        inputs[9].ki.wVk = 91;
        inputs[9].ki.dwFlags = KEYEVENTF_KEYUP;

        UINT uSent = _sendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            return results;
        }
        break;
    }
    }

    results = as_Boolean( true);
    return results;
}


napi_value getMouseMovePoints(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::String(env, hmc_mouse::getMouseMovePointsJsonA());
}

napi_value getCursorPos(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::String(env, hmc_mouse::getCursorPosJsonA());
}

napi_value installHookMouse2(napi_env env, napi_callback_info info)
{
    bool result = hmc_mouse::MouseHook::initMouseEventHook();
    return  as_Boolean(result);
}

napi_value unHookMouse2(napi_env env, napi_callback_info info)
{
     bool result = hmc_mouse::MouseHook::stopHookMouse();
    return  as_Boolean(result);
}

napi_value getMouseNextSession2(napi_env env, napi_callback_info info)
{
     std::string result = hmc_mouse::MouseHook::getMouseEventListJsonA();
    return  as_String(result);
}

napi_value isStartHookMouse2(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Boolean(env, hmc_mouse::MouseHook::isValidHookMouse());
}

napi_value getLastInputTime(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Number(env, hmc_mouse::getLastInputTime());
}

napi_value stopLimitMouseRangeWorker(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Boolean(env, hmc_mouse::LimitMouseRange::stopLimitMouseRange_worker());
}

napi_value setLimitMouseRange(napi_env env, napi_callback_info info)
{
    auto args = hmc_NodeArgsValue(env,info);

    args.eq({
        {0,js_number},
        {1,js_number},
        {2,js_number},
        {3,js_number},
        {4,js_number},
        });
    
    return hmc_napi_create_value::Boolean(env, hmc_mouse::LimitMouseRange::setLimitMouseRange(
        args.getInt64(/*ms*/0,50), 
        args.getInt64(/*x*/1,1), 
        args.getInt64(/*y*/2,1), 
        args.getInt64(/*right*/3,1), 
        args.getInt64(/*bottom*/4,1)
        ));
}


napi_value hasLimitMouseRangeWorker(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Boolean(env, hmc_mouse::LimitMouseRange::hasLimitMouseRange_worker());
}
