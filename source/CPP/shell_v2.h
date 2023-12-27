#ifndef HMC_IMPORT_SHELL_V2_H
#define HMC_IMPORT_SHELL_V2_H

#include <windows.h>
#include <string>
#include <vector>
using namespace std;

class GetTaryIconList
{
public:

    struct TaryIcon
    {
        HWND hwnd;
        wstring path;
        wstring title;
        long index;
        TaryIcon(HWND hwnd, wstring path, wstring title, long index) : hwnd(hwnd), path(path), title(title), index(index) {}
    };

    static vector<TaryIcon> getTrayList();
    static wstring getTrayListJsonW();
private:
    static constexpr int _WM_USER = 0x0400;
    static constexpr int _TB_BUTTONCOUNT = WM_USER + 24;	// WM_USER+24
    static constexpr int _TB_GETBUTTON = WM_USER + 23;	// WM_USER+23
    static constexpr int _TB_DELETEBUTTON = WM_USER + 22;	// WM_USER+22

    // 判断 x64 系统
    static BOOL IsSystemFor64bit();
    // 获取折叠托盘窗口句柄
    static HWND GetNotifyOverflowTryHwnd();
    // 获取托盘窗口句柄
    static HWND GetSystemTrayHwnd();
    // 枚举控件句柄
    static vector<TaryIcon> EnumCommctrlList(HWND hWnd);
};

extern  BOOL isSystemFor64bit();


#endif
