#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_WINDOWS_V2_HPP
#define MODE_INTERNAL_INCLUDE_HMC_WINDOWS_V2_HPP

#include "./hmc_string_util.hpp"

#include <windows.h>
#include <string>
#include <variant>
#include <map>
#include <thread>
#include <ShlObj.h>
#include <vector>
#include <shared_mutex>

#define HMC_VirtualAlloc(Type, leng) (Type)::VirtualAlloc((LPVOID)NULL, (DWORD)(leng), MEM_COMMIT, PAGE_READWRITE);
#define HMC_VirtualFree(Virtua)                \
    if (Virtua != NULL)                        \
    {                                          \
        ::VirtualFree(Virtua, 0, MEM_RELEASE); \
    }

#define HMC_VirtualFreeAuto(Virtua)                                         \
    std::shared_ptr<void>##Virtua##_Auto_Close_Virtual(nullptr, [&](void *) \
                                                       { \
    if (Virtua != NULL) \
    { \
        ::VirtualFree(Virtua, 0, MEM_RELEASE); \
    } });

#define HMC_LibraryFreeAuto(hDllInst)                                         \
    std::shared_ptr<void>##hDllInst##_Auto_Close_Library(nullptr, [&](void *) \
                                                         { \
    if (hDllInst != NULL) \
    { \
        ::FreeLibrary(hDllInst); \
    } });

#define HMC_EQ_RUN_LAST(size)      \
    if (size == NULL || size <= 0) \
    {                              \
        return ::GetLastError();   \
    }

namespace hmc_windows_util
{
    extern std::vector<HWND> _$_getSubWindows_temp;
    extern std::shared_mutex _$_getSubWindows_shared_mutex;
    
    /**
     * @brief 获取控件文本 同进程
     *
     * @param hwnd
     * @param dlgItemID
     * @return std::variant<std::wstring, DWORD>
     */
    extern std::variant<std::wstring, DWORD> getWindowText(HWND hwnd, int dlgItemID);
    /**
     * @brief 获取窗口标题
     *
     * @param hwnd
     * @return std::variant<std::wstring, DWORD>
     */
    extern std::variant<std::wstring, DWORD> getWindowTitle(HWND hwnd);
    /**
     * @brief 获取窗口标题 比GetWindowTitle 更低级的接口
     *
     * @param hwnd
     * @return std::variant<std::wstring, DWORD>
     */
    extern std::variant<std::wstring, DWORD> getWindowTitleInternal(HWND hwnd);
    /**
     * @brief 设置窗口标题
     * 不等于1 都是错误
     * @param hwnd
     * @param title
     * @return DWORD
     */
    extern std::variant<bool, DWORD> setWindowTitle(HWND hwnd, std::wstring title);
    /**
     * @brief 获取所有窗口句柄
     *
     * @param is_Windows 要求必须是窗口句柄
     * @return std::variant<std::vector<HWND>, DWORD>
     */
    extern std::variant<std::vector<HWND>, DWORD> getAllWindows(bool is_Windows);
    /**
     * @brief 判断窗口是否有效 (不能是控件句柄)
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isWindow(HWND hwnd);
    /**
     * @brief 获取窗口的类名
     *
     * @param hwnd
     */
    extern std::variant<std::wstring, DWORD> getClassName(HWND hwnd);
    /**
     * @brief 枚举窗口子句柄
     *
     * @param hwnd
     * @return std::variant<std::vector<HWND>, DWORD>
     */
    extern std::variant<std::vector<HWND>, DWORD> getSubWindows(HWND hwnd);
    /**
     * @brief 获取父窗口句柄
     *
     * @param hwnd
     * @return std::variant<HWND, DWORD>
     */
    extern std::variant<HWND, DWORD> getParentWindow(HWND hwnd);
    /**
     * @brief 判断是否是XX的 子窗口
     *
     * @param hWndParent
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isChildWindow(HWND hWndParent, HWND hwnd);
    /**
     * @brief 获取附属的根级窗口
     *
     * @param hwnd
     * @return HWND
     */
    extern std::variant<HWND, DWORD> getTopWindow(HWND hwnd);
    /**
     * @brief 刷新指定句柄的窗口
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool updateWindow(HWND hwnd);
    /**
     * @brief 获取指定坐标位置的窗口
     *
     * @param Point
     * @return HWND
     */
    extern HWND getPointWindow(POINT Point);
    /**
     * @brief 获取指定坐标位置的窗口
     *
     * @param Point
     * @return HWND
     */
    extern HWND getPointWindow(int x, int y);
    /**
     * @brief 获取当前坐标位置的窗口
     *
     * @param Point
     * @return HWND
     */
    extern HWND getPointWindow();
    /**
     * @brief 设置启用/禁用窗口
     *
     * @param hwnd
     * @param isEnabled
     * @return true
     * @return false
     */
    extern bool setWindowEnabled(HWND hwnd, bool isEnabled);
    /**
     * @brief 窗口聚焦
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool setWindowFocus(HWND hwnd);
    /**
     * @brief 结束 窗口句柄所属的线程
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern std::variant<bool, DWORD> killWindowProcess(HWND hwnd);
    /**
     * @brief 获取指定窗口的进程id
     *
     * @param hwnd
     * @return DWORD
     */
    extern DWORD getWindowProcessID(HWND hwnd);
    /**
     * @brief 设置窗口的顶设状态
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool setWindowTop(HWND hwnd, bool isWindowTop);
    /**
     * @brief 判断窗口是否顶设
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isWindowTop(HWND hwnd);
    /**
     * @brief 窗口抖动
     *
     * @param hWnd 句柄
     * @param shakeCount 抖动次数
     * @param shakeDistance 移动像素
     * @param shakeDuration 每次延迟
     */
    extern void setWindowShake(HWND hWnd, int shakeCount, int shakeDistance, int shakeDuration);
    /**
     * @brief 判断窗口是否被禁用
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isWindowEnabled(HWND hwnd);
    /**
     * @brief 设置窗口在托盘的可见性
     *
     * @param hwnd
     * @param visible
     * @return true
     * @return false
     */
    extern bool setWindowInTaskbarVisible(HWND hwnd, bool visible);
    /**
     * @brief 设置窗口不透明度
     *
     * @param hwnd
     * @param Transparent
     * @return true
     * @return false
     */
    extern bool setWindowTransparent(HWND hwnd, int Transparent);
    /**
     * @brief 设置窗口可见性 百分比 如：0.92
     *
     * @param hwnd
     * @param Transparent
     * @return true
     * @return false
     */
    extern bool setHandleTransparent(HWND hwnd, double Transparent);
    /**
     * @brief 关闭指定句柄(强制关闭窗口)
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool closedHandle(HWND hwnd);
    /**
     * @brief 关闭指定窗口
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool closeWindow(HWND hwnd, bool destroy = false);
    /**
     * @brief 设置窗口图标
     *
     * @param hwnd
     * @param iconStr
     * @return true
     * @return false
     */
    extern bool setWindowFileIcon(HWND hwnd, std::string iconStr, bool titleIcon = true, bool Icon = true);
    /**
     * @brief 判断此窗口是否是桌面
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isDesktopWindow(HWND hwnd);

    /**
     * @brief 设置窗口的图标
     *
     * @param hWnd 句柄
     * @param hIcon 图标 如果没有从exe提取默认
     */
    extern void setWindowIcon(HWND hWnd, HICON hIcon = NULL, int index = 0);
    extern void setWindowIcon(HWND hWnd, std::string iconPath, int index = 0);
}

#endif // MODE_INTERNAL_INCLUDE_HMC_WINDOWS_V2_HPP