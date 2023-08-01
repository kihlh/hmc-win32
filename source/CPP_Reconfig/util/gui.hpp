

#include <string>
#include <windows.h>
#include <functional>
#include <iostream>
#include <windows.h>
using namespace std;

// 窗口类名
#define WINDOW_CLASS_NAME L"DllWindowClass"

// 窗口句柄
HWND g_hWnd = NULL;

// 窗口过程函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// 创建窗口函数
BOOL initializeWindow(HINSTANCE hInstance)
{
    // 注册窗口类
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(wcex));
    wcex.cbSize = sizeof(wcex);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = WINDOW_CLASS_NAME;

    if (!RegisterClassEx(&wcex))
    {
        return FALSE;
    }

    // 创建窗口
    g_hWnd = CreateWindowExW(
        0,
        WINDOW_CLASS_NAME,
        L"Dll Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!g_hWnd)
    {
        return FALSE;
    }

    // 显示和更新窗口
    ShowWindow(g_hWnd, SW_SHOW);
    UpdateWindow(g_hWnd);

    return TRUE;
}

namespace hmc_gui
{

    string __hmc_title = "hmc_gui";

    LRESULT CALLBACK ___openPuppetTrayWindow_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CREATE:

        case WM_DESTROY:

            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }

        return 0;
    }

    int __openPuppetTrayWindow()
    {
        WNDCLASSEXA wc;
        MSG Msg;
        HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

        wc.cbSize = sizeof(WNDCLASSEXA);
        wc.style = 0;
        wc.lpfnWndProc = ___openPuppetTrayWindow_WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = "hmc-window-lib";
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        RegisterClassExA(&wc);

        HWND hwnd = CreateWindowExA(WS_EX_APPWINDOW, wc.lpszClassName, "ssagsdg", WS_OVERLAPPEDWINDOW,
                                    CW_USEDEFAULT, CW_USEDEFAULT, 400, 150, NULL, NULL, hInstance, NULL);

        ShowWindow(hwnd, SW_HIDE);
        ShowWindow(hwnd, SW_SHOW);

        while (GetMessage(&Msg, NULL, 0, 0))
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }

        return Msg.wParam;
    }

    typedef std::function<void(string type, string message)> onSearchBoxCallbackFunc;

    // 输入框
    string prompt(string title, string message, string defaultInput = "")
    {
    }

    // 密码框
    string password(string title, string message, string defaultPassword = "")
    {
    }

    // 密码和用户名框
    string passLogin(string title, string message, string defaultUserName = "", string defaultPassword = "")
    {
    }

    // 搜索框 像浏览器的搜索框一样的
    class SearchBox
    {
    public:
        void close() {}
        void on(onSearchBoxCallbackFunc callBack)
        {
        }
        void setInput()
        {
        }
        void getInput()
        {
        }
        int getLen()
        {
        }
        SearchBox(int len, int start = 1) {}
        SearchBox(string input, int len, int start = 1) {}
        SearchBox(string input) {}
        SearchBox()
        {
        }
    };

    // 进度条
    class progressBar
    {
    public:
        void close(){};
        int getProgress(){};
        void setProgress(int progress){};
    };
}