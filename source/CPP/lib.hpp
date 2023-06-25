
#include <string>
#include <string>
#include <thread>
#include <windows.h>
#include <vector>
#include <process.h>
#include <Tlhelp32.h>
#include <iostream>

using namespace std;

/**
 * @brief 设置窗口的图标
 *
 * @param hWnd 句柄
 * @param hIcon 图标 如果没有从exe提取默认
 */
void _setIcon(HWND hWnd, HICON hIcon = NULL, int index = 0)
{
    char szFilePath[MAX_PATH];
    if (GetModuleFileNameA(NULL, szFilePath, MAX_PATH))
    {
        if (hIcon == NULL)
        {
            HINSTANCE hInst = LoadLibraryA("Shell32.dll");
            if (hInst)
            {
                HICON(WINAPI * ExtractIconA)
                (HINSTANCE hInst, LPCSTR pszExeFileName, UINT nIconIndex);
                ExtractIconA = (HICON(WINAPI *)(HINSTANCE hInst, LPCSTR pszExeFileName, UINT nIconIndex))GetProcAddress(hInst, "ExtractIconA");
                hIcon = ExtractIconA(hInst, szFilePath, index);
                FreeLibrary(hInst);
            }
        }
        HINSTANCE hIn = LoadLibraryA("user32.dll");
        if (hIn && hIcon != NULL)
        {
            LRESULT(WINAPI * SendMessageA)
            (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
            SendMessageA = (LRESULT(WINAPI *)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))GetProcAddress(hIn, "SendMessageA");
            if (SendMessageA)
            {
                SendMessageA(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
                SendMessageA(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            }
        }
    }
}

namespace hmc
{
    namespace win
    {
        /**
         * @brief 设置窗口的图标
         *
         * @param hWnd 句柄
         * @param hIcon 图标 如果没有从exe提取默认
         */
        void setIcon(HWND hWnd, HICON hIcon = NULL, int index = 0)
        {
            _setIcon((HWND)hWnd, hIcon, index);
        }
        /**
         * @brief 设置窗口的图标
         *
         * @param hWnd 句柄
         * @param hIcon 图标 如果没有从exe提取默认
         */
        void setIcon(HWND hWnd, int index)
        {
            _setIcon((HWND)hWnd, NULL, index);
        }

        void setIcon(HWND hWnd, string iconPath, int index = 0)
        {
            HICON hIcon = NULL;
            HINSTANCE hInst = LoadLibraryA("Shell32.dll");
            if (hInst)
            {
                HICON(WINAPI * ExtractIconA)
                (HINSTANCE hInst, LPCSTR pszExeFileName, UINT nIconIndex);
                ExtractIconA = (HICON(WINAPI *)(HINSTANCE hInst, LPCSTR pszExeFileName, UINT nIconIndex))GetProcAddress(hInst, "ExtractIconA");
                hIcon = ExtractIconA(hInst, iconPath.c_str(), index);
                FreeLibrary(hInst);
            }
        }

        void setIcon(long lhWnd, HICON hIcon = NULL)
        {
            _setIcon((HWND)lhWnd, hIcon);
        }

        void setIcon(long lhWnd)
        {
            _setIcon((HWND)lhWnd, NULL);
        }

        /**
         * @brief 判断此句柄是否是窗口
         *
         * @param Handle
         * @return BOOL
         */
        BOOL isWindow(HWND Handle)
        {
            return GetWindow(Handle, GW_OWNER) == (HWND)0 && IsWindowVisible(Handle);
        }
        struct WindowEnv
        {
            string title;
            string execName;
            string execPath;
            DWORD pid;
            HWND hwnd;
            DWORD dHwnd;
            
        };

        WindowEnv getWindowEnv()
        {
            WindowEnv winenv;
        }
    }

    namespace gui
    {
        /**
         * @brief 创建一个输入框GUI
         *
         * @param info 显示为什么需要输入 例如：“请输入用户名：”
         * @param input 在输入框那边预填入什么文本
         * @return string
         */
        string prompt(string info, string input = "")
        {
            string output;
            // std::thread(_prompt, info, input, output).detach();
            //_prompt("","", output);

            return output;
        }

    }
    namespace process
    {

        /*   getProcess() {
               DWORD dwMainThreadId = GetCurrentThreadId();
               DWORD dwProcessId = GetCurrentProcessId();

           }*/
    }
}
