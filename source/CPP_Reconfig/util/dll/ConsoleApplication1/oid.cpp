#include <windows.h>
#define IDM_EXIT 9001
#define IDM_EXIT2 9003
#define IDM_EXIT3 9004
#include <iostream>
#include <shellapi.h>
using namespace std;

#define WM_SYSICON (WM_USER + 1)
static NOTIFYICONDATA nid;

//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 

// 修改托盘图标
void ModifyTrayIcon()
{
    HICON hNewIcon = NULL;  // 声明一个HICON句柄
    hNewIcon = ExtractIcon(GetModuleHandle(NULL), L"D:\\usersData\\Downloads\\YoudaoDictSetup.exe", 0);

    nid.hIcon = hNewIcon;
    Shell_NotifyIcon(NIM_MODIFY, &nid);
}

// 修改托盘显示的消息内容
void ModifyTrayInfo(const wchar_t* pszNewInfo)
{
    wcscpy_s(nid.szTip, pszNewInfo);
    Shell_NotifyIcon(NIM_MODIFY, &nid);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HMENU hMenu = CreatePopupMenu();
    switch (message)
    {
    case WM_CREATE:
        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = hWnd;
        nid.uID = 0;
        nid.uVersion = NOTIFYICON_VERSION;
        nid.uCallbackMessage = WM_SYSICON;
        nid.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        //strncpy(nid.szTip, L"Test Tip", sizeof(nid.szTip));
        nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        Shell_NotifyIcon(NIM_ADD, &nid);
        break;

    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0);
        break;

    case WM_SYSICON:
    {
        // 转发给窗口监听处理程序
        switch (lParam)
        {
        case WM_RBUTTONDOWN:
            cout << "WM_RBUTTONDOWN" << endl;
            break;
        case WM_RBUTTONUP:
            cout << "WM_RBUTTONUP" << endl;
            break;
        case WM_LBUTTONDOWN:
            cout << "WM_LBUTTONDOWN" << endl;
            break;
        case WM_LBUTTONUP:
            cout << "WM_LBUTTONUP" << endl;
            break;
        case WM_LBUTTONDBLCLK:
            cout << "WM_LBUTTONDBLCLK" << endl;
            break;
        }

        // 如果是右键显示右键菜单
        if (lParam == WM_RBUTTONUP)
        {
            POINT curPoint;
            GetCursorPos(&curPoint);
            SetForegroundWindow(hWnd);


            if (hMenu)
            {
                InsertMenu(hMenu, -1, MF_BYPOSITION, IDM_EXIT, L"退出");
                InsertMenu(hMenu, -1, MF_BYPOSITION | MF_SEPARATOR, 3333, L"退v出");
                InsertMenu(hMenu, -1, MF_BYCOMMAND | MF_CHECKED, IDM_EXIT3, L"退v出");
                InsertMenu(hMenu, -1, MF_BYCOMMAND | MF_UNCHECKED, IDM_EXIT2, L"退v出");
                // 创建子菜单
                HMENU hSubMenu = CreatePopupMenu();
                if (hSubMenu) {
                    AppendMenu(hSubMenu, MF_STRING, 666, L"永久退出");
                    AppendMenu(hSubMenu, MF_STRING, 64, L"隐藏窗口");
                    AppendMenu(hSubMenu, MF_STRING, 455, L"结束进程");

                    // 把子菜单加到主菜单项
                    ModifyMenu(hMenu, IDM_EXIT, MF_POPUP, (UINT_PTR)hSubMenu, L"退出");
                }
                // 这让菜单显示为需要的样子，例如处理具有复选菜单项的菜单
                SetMenuDefaultItem(hMenu, IDM_EXIT, FALSE);


                TrackPopupMenu(hMenu, TPM_BOTTOMALIGN, curPoint.x, curPoint.y, 0, hWnd, NULL);
                DestroyMenu(hMenu);
            }
        }
    }
    break;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDM_EXIT) {
            cout << "IDM_EXIT" << endl;
            ModifyTrayIcon();

        }
        if (LOWORD(wParam) == IDM_EXIT3) {

            cout << "IDM_EXIT3" << endl;
            ModifyTrayIcon();
        }
        if (LOWORD(wParam) == IDM_EXIT2) {
            ModifyTrayInfo(L"sdagddfhfgjghkhgl");
            cout << "IDM_EXIT2" << endl;
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int main() {
    WNDCLASSEX wc;
    HWND hWnd;
    MSG Msg;
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"myWindowClass";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(WS_EX_APPWINDOW, wc.lpszClassName, L"title", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1, 1, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, SW_HIDE);
    //ShowWindow(hWnd, SW_SHOW);

    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}






#include <windows.h>
#define IDM_EXIT 9001
#define IDM_EXIT2 9003
#define IDM_EXIT3 9004
#include <iostream>
#include <shellapi.h>
using namespace std;

#define WM_SYSICON (WM_USER + 1)
static NOTIFYICONDATAA nid;

//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 

// 修改托盘图标
void ModifyTrayIcon()
{
    HICON hNewIcon = NULL;  // 声明一个HICON句柄
    hNewIcon = ExtractIconA(GetModuleHandle(NULL), "D:\\usersData\\Downloads\\YoudaoDictSetup.exe", 0);

    nid.hIcon = hNewIcon;
    Shell_NotifyIconA(NIM_MODIFY, &nid);
}

// 修改托盘显示的消息内容
void ModifyTrayInfo(const wchar_t* pszNewInfo)
{
    //wcscpy_s(nid.szTip, pszNewInfo);
    //Shell_NotifyIconA(NIM_MODIFY, &nid);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HMENU hMenu = CreatePopupMenu();
    switch (message)
    {
    case WM_CREATE:
        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = hWnd;
        nid.uID = 0;
        nid.uVersion = NOTIFYICON_VERSION;
        nid.uCallbackMessage = WM_SYSICON;
        nid.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        //strncpy(nid.szTip, L"Test Tip", sizeof(nid.szTip));
        nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        Shell_NotifyIconA(NIM_ADD, &nid);
        break;

    case WM_DESTROY:
        Shell_NotifyIconA(NIM_DELETE, &nid);
        PostQuitMessage(0);
        break;

    case WM_SYSICON:
    {
        // 转发给窗口监听处理程序
        switch (lParam)
        {
        case WM_RBUTTONDOWN:
            cout << "WM_RBUTTONDOWN" << endl;
            break;
        case WM_RBUTTONUP:
            cout << "WM_RBUTTONUP" << endl;
            break;
        case WM_LBUTTONDOWN:
            cout << "WM_LBUTTONDOWN" << endl;
            break;
        case WM_LBUTTONUP:
            cout << "WM_LBUTTONUP" << endl;
            break;
        case WM_LBUTTONDBLCLK:
            cout << "WM_LBUTTONDBLCLK" << endl;
            break;
        }

        // 如果是右键显示右键菜单
        if (lParam == WM_RBUTTONUP)
        {
            POINT curPoint;
            GetCursorPos(&curPoint);
            SetForegroundWindow(hWnd);


            if (hMenu)
            {
                InsertMenu(hMenu, -1, MF_BYPOSITION, IDM_EXIT, L"退出");
                InsertMenu(hMenu, -1, MF_BYPOSITION | MF_SEPARATOR, 3333, L"退v出");
                InsertMenu(hMenu, -1, MF_BYCOMMAND | MF_CHECKED, IDM_EXIT3, L"退v出");
                InsertMenu(hMenu, -1, MF_BYCOMMAND | MF_UNCHECKED, IDM_EXIT2, L"退v出");
                // 创建子菜单
                HMENU hSubMenu = CreatePopupMenu();
                if (hSubMenu) {
                    AppendMenu(hSubMenu, MF_STRING, 666, L"永久退出");
                    AppendMenu(hSubMenu, MF_STRING, 64, L"隐藏窗口");
                    AppendMenu(hSubMenu, MF_STRING, 455, L"结束进程");

                    // 把子菜单加到主菜单项
                    ModifyMenu(hMenu, IDM_EXIT, MF_POPUP, (UINT_PTR)hSubMenu, L"退出");
                }
                // 这让菜单显示为需要的样子，例如处理具有复选菜单项的菜单
                SetMenuDefaultItem(hMenu, IDM_EXIT, FALSE);


                TrackPopupMenu(hMenu, TPM_BOTTOMALIGN, curPoint.x, curPoint.y, 0, hWnd, NULL);
                DestroyMenu(hMenu);
            }
        }
    }
    break;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDM_EXIT) {
            cout << "IDM_EXIT" << endl;
            ModifyTrayIcon();

        }
        if (LOWORD(wParam) == IDM_EXIT3) {

            cout << "IDM_EXIT3" << endl;
            ModifyTrayIcon();
        }
        if (LOWORD(wParam) == IDM_EXIT2) {
            ModifyTrayInfo(L"sdagddfhfgjghkhgl");
            cout << "IDM_EXIT2" << endl;
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int main() {
    WNDCLASSEXA wc;
    HWND hWnd;
    MSG Msg;
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "myWindowClass";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassExA(&wc);

    hWnd = CreateWindowExA(WS_EX_APPWINDOW, wc.lpszClassName, "title", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1, 1, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, SW_HIDE);
    //ShowWindow(hWnd, SW_SHOW);

    while (GetMessageA(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}
