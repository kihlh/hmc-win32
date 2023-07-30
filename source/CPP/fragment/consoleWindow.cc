#include <iostream>
#include <windows.h>

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

int main()
{

    HINSTANCE hInstance = GetModuleHandle(NULL);
    initializeWindow(hInstance);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

}
