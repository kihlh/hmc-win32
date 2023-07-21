#include <windows.h>
#include <string>
#include <Psapi.h>
#include <Shellapi.h>
using namespace std;

namespace hmc_window
{
    HWND toHWND(DWORD hwnd)
    {
        return (HWND)hwnd;
    }
    HWND toHWND(int hwnd)
    {
        return (HWND)hwnd;
    }
    HWND toHWND(long hwnd)
    {
        return (HWND)hwnd;
    }
    HWND toHWND(HWND hwnd)
    {
        return (HWND)hwnd;
    }
    /**
     * @brief 数字转为句柄
     *
     * @param hwnd
     * @return HWND
     */
    HWND toHWND(string hwnd)
    {
        if (hmc_text_util::haslongStr(hwnd))
        {
            long n = stol(hwnd);
            return (HWND)n;
        }
        return NULL;
    }

    bool isWindow(HWND hwnd)
    {
        return (GetWindow(hwnd, GW_OWNER) == (HWND)0 && IsWindowVisible(hwnd));
    }

    string getClassName(HWND hwnd)
    {

        LPSTR lpClassName;

        if (!GetClassNameA(hwnd, lpClassName, MAX_PATH))
        {
            lpClassName = "";
        };

        return string(lpClassName);
    }

    DWORD getStyle(HWND hwnd)
    {
        return GetClassLongA(hwnd, GCL_STYLE);
    }

#ifdef defined(_MFC_VER)

#endif
}