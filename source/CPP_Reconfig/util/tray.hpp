#include <string>
#include <windows.h>
#include <thread>
#include <functional>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))
#define HMC_CHECK_CATCH catch (char *err){};

#define WM_SYSICON (WM_USER + 1)
#define IDM_EXIT 9001
#define IDM_EXIT2 9003
#define IDM_EXIT3 9004

using namespace std;

// A 字符显示不了托盘 等待换成W字符

namespace hmc_tray
{
    static NOTIFYICONDATAA nid;
    HWND hWnd;
    std::string infoTitle;

    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        HMENU hMenu = CreatePopupMenu();

        switch (msg)
        {
        case WM_CREATE:
            nid.cbSize = sizeof(NOTIFYICONDATAA);
            nid.hWnd = hWnd;
            nid.uID = 0;
            nid.uVersion = NOTIFYICON_VERSION;
            nid.uCallbackMessage = WM_SYSICON;
            nid.hIcon = LoadIcon(NULL, IDI_WINLOGO);
            strncpy_s(nid.szTip, infoTitle.c_str(), sizeof(nid.szTip));
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
                    InsertMenuA(hMenu, -1, MF_BYPOSITION, IDM_EXIT, "hgk");
                    InsertMenuA(hMenu, -1, MF_BYPOSITION | MF_SEPARATOR, 3333, "7978");
                    InsertMenuA(hMenu, -1, MF_BYCOMMAND | MF_CHECKED, IDM_EXIT3, "kj;");
                    InsertMenuA(hMenu, -1, MF_BYCOMMAND | MF_UNCHECKED, IDM_EXIT2, "kj;k;");
                    // 创建子菜单
                    HMENU hSubMenu = CreatePopupMenu();
                    if (hSubMenu)
                    {
                        AppendMenuA(hSubMenu, MF_STRING, 666, "ufty");
                        AppendMenuA(hSubMenu, MF_STRING, 64, "ghk");
                        AppendMenuA(hSubMenu, MF_STRING, 455, "gh");

                        // 把子菜单加到主菜单项
                        ModifyMenuA(hMenu, IDM_EXIT, MF_POPUP, (UINT_PTR)hSubMenu, "fgk");
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
            if (LOWORD(wParam) == IDM_EXIT)
            {
                cout << "IDM_EXIT" << endl;
            }
            if (LOWORD(wParam) == IDM_EXIT3)
            {

                cout << "IDM_EXIT3" << endl;
            }
            if (LOWORD(wParam) == IDM_EXIT2)
            {
                cout << "IDM_EXIT2" << endl;
            }
            break;

        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }


    typedef enum
    {
        check = MF_CHECKED,
        separator = MF_SEPARATOR,
        menu = 60409,
    } chMenuType;

    struct chMenuItem
    {
        // 显示名称
        string name;
        // js的文本id
        string id;
        // 自动分配的id 留 0
        int messageID;
        // 按钮类型
        chMenuType type;
        // 禁用
        bool disable;
        // 子按钮列表
        vector<int> menuList;
        // 主按钮 如果是子按钮 不会被显示出来  只有主按钮中包含此键的id才会被包含到子按钮里显示
        bool rootMenu;
    };

    class CTrayIcon
    {
    public:
        bool Start()
        {
            return StartTrayPuppetWin();
        }

        /**
         * @brief 设置窗口消息
         *
         * @param trayInfo
         */
        bool setTrayInfo(string trayInfo)
        {
            string subtxt = string();
            try
            {
                if (trayInfo.length() > 255)
                {
                    subtxt.append(trayInfo.substr(0, 255));
                }
                else
                {
                    subtxt.append(trayInfo.substr(0, trayInfo.length()));
                }

                strncpy_s(nid.szTip, subtxt.c_str(), subtxt.size());
                if (Shell_NotifyIconA(NIM_MODIFY, &nid))
                {
                    infoTitle.clear();
                    infoTitle.append(subtxt);
                    return true;
                };
            }
            HMC_CHECK_CATCH;
            return false;
        }

        /**
         * @brief 设置托盘图标文件( ico / dll / exe )
         *
         * @param hNewIcon
         */
        bool setTrayIcon(string strNewIcon)
        {
            HICON hNewIcon = NULL; // 声明一个HICON句柄
            hNewIcon = ExtractIconA(GetModuleHandle(NULL), strNewIcon.c_str(), 0);
            if (hNewIcon != NULL)
            {
                nid.hIcon = hNewIcon;
                return Shell_NotifyIconA(NIM_MODIFY, &nid);
            }
            return false;
        }

        /**
         * @brief 设置托盘图标
         *
         * @param hNewIcon
         */
        bool setTrayIcon(HICON hNewIcon)
        {
            if (hNewIcon != NULL)
            {
                nid.hIcon = hNewIcon;
                return Shell_NotifyIconA(NIM_MODIFY, &nid);
            }
            return false;
        }

        /**
         * @brief 添加按钮
         *
         * @param menuItem
         * @return true
         * @return false
         */
        bool addMenuItem(chMenuItem menuItem)
        {
            if (MenuList.find(menuItem.id) != MenuList.end())
                return false;
                
            int idkey = (tray_next_id++);

            menuItem.messageID = idkey;

            MenuList.insert(std::make_pair(menuItem.id, menuItem));

            return true;
        }

 
    private:
        int tray_next_id;
        WNDCLASSEXA wc;
        std::map<string, chMenuItem> MenuList;
        std::thread *tray_worker;
     
        bool StartTrayPuppetWin()
        {

            MSG Msg;
            HMODULE hInstance = (HMODULE)GetModuleHandleA(NULL);

            wc.cbSize = sizeof(WNDCLASSEX);
            wc.style = 0;
            wc.lpfnWndProc =WndProc;
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

            hWnd = CreateWindowExA(WS_EX_APPWINDOW, wc.lpszClassName, "hmc-tray-window", WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, CW_USEDEFAULT, 1, 1, NULL, NULL, hInstance, NULL);

            ShowWindow(hWnd, SW_HIDE);

            while (GetMessageA(&Msg, NULL, 0, 0) > 0)
            {
                TranslateMessage(&Msg);
                DispatchMessageA(&Msg);
            }
            return true;
        }
        
    };

}