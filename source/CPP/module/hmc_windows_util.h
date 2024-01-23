#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_WINDOWS_V2_HPP
#define MODE_INTERNAL_INCLUDE_HMC_WINDOWS_V2_HPP

#include "./hmc_string_util.h"

#include <windows.h>
#include <string>
#include <variant>
#include <map>
#include <thread>
#include <ShlObj.h>
#include <vector>
#include <shared_mutex>
#include <optional>

namespace hmc_windows_util
{

    namespace hmc_define_util
    {

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

#define HMC_PUSH_WSRES(WS)    \
    if (style & WS)           \
    {                         \
        result.push_back(WS); \
    }

#define HMC_CASE_PUSH_WSRES(WS) \
    case WS:                    \
        result.append(##WS);    \
        break;

#define HMC_PUSH_WSRES_STR(WS)                                       \
    if (style & WS)                                                  \
    {                                                                \
        result.push_back(hmc_windows_util::winwowLongClass2str(WS)); \
    }

#define HMC_PUSH_WSRES_STR_EX(WS)                                      \
    if (style & WS)                                                    \
    {                                                                  \
        result.push_back(hmc_windows_util::winwowLongClass2strEx(WS)); \
    }

#define HMC_IS_INSIDE(x1, y1, x2, y2, x, y) ((x > x1 && x < x2 && y > y1 && y < y2) ? true : false)

#define HMC_ALL_CATCH_NONE \
    catch (...) {}

#define None std::nullopt

    }

    extern std::vector<HWND> _$_getSubWindows_temp;
    extern std::shared_mutex _$_getSubWindows_shared_mutex;

    extern std::vector<HWND> get_variant(std::variant<std::vector<HWND>, DWORD> input, std::vector<HWND> of_to);

    extern std::vector<HWND> get_variant(std::variant<std::vector<HWND>, DWORD> input);

    extern HWND get_variant(std::variant<HWND, DWORD> input, HWND of_to);

    extern HWND get_variant(std::variant<HWND, DWORD> input);

    extern std::wstring get_variant(std::variant<std::wstring, DWORD> input, std::wstring of_to);

    extern std::wstring get_variant(std::variant<std::wstring, DWORD> input);

    extern std::string get_variant(std::variant<std::string, DWORD> input, std::string of_to);

    extern std::string get_variant(std::variant<std::string, DWORD> input);

    extern std::vector<std::wstring> get_variant(std::variant<std::vector<std::wstring>, DWORD> input, std::vector<std::wstring> of_to);

    extern std::vector<std::wstring> get_variant(std::variant<std::vector<std::wstring>, DWORD> input);

    extern std::vector<std::string> get_variant(std::variant<std::vector<std::string>, DWORD> input, std::vector<std::string> of_to);

    extern std::vector<std::string> get_variant(std::variant<std::vector<std::string>, DWORD> input);

    extern bool get_variant(std::variant<bool, DWORD> input, bool of_to);

    extern bool get_variant(std::variant<bool, DWORD> input);

    extern std::vector<RECT> get_variant(std::variant<std::vector<RECT>, DWORD> input);

    extern std::vector<RECT> get_variant(std::variant<std::vector<RECT>, DWORD> input, std::vector<RECT> of_to);

    extern RECT get_variant(std::variant<RECT, DWORD> input);

    extern RECT get_variant(std::variant<RECT, DWORD> input, RECT of_to);

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
    extern std::variant<std::vector<HWND>, DWORD> getAllWindows(bool is_Windows = true);
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
     * @brief 判断此窗口是否是桌面
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isDesktopWindow(HWND hwnd);
    /**
     * @brief 设置窗口的图标 可执行文件中的ico
     *
     * @param hWnd 窗口句柄
     * @param ExtractFilePath 可执行文件 / dll 路径
     * @param index 图标索引
     * @param set_type 设置类型
     * - 1 Titlebar icon: 16x16
     * - 2 Taskbar icon:  32x32
     * - 0/nullopt all icon
     */
    extern void setWindowIconByExtract(HWND hWnd, std::optional<std::wstring> ExtractFilePath = std::nullopt, std::optional<int> index = std::nullopt, std::optional<int> set_type = std::nullopt);
    /**
     * @brief 设置窗口的图标 可执行文件中的ico
     *
     * @param hWnd 窗口句柄
     * @param ExtractFilePath ico 路径
     * @param index 图标索引
     * @param set_type 设置类型
     * - 1 Titlebar icon: 16x16
     * - 2 Taskbar icon:  32x32
     * - 0/nullopt all icon
     */
    extern void setWindowIconByIco(HWND hWnd, std::optional<std::wstring> IcoFilePath = std::nullopt, std::optional<int> index = std::nullopt, std::optional<int> set_type = std::nullopt);
    /**
     * @brief 移动窗口位置
     *
     * @param hwnd 窗口句柄
     * @param x 左边到右的距离
     * @param y 顶到底部的距离
     * @param w 宽度
     * @param h 高度
     * @return true
     * @return false
     */
    extern std::variant<bool, DWORD> setMoveWindow(HWND hwnd, std::optional<int> x = std::nullopt, std::optional<int> y = std::nullopt, std::optional<int> w = std::nullopt, std::optional<int> h = std::nullopt);
    /**
     * @brief 让这个窗口不可见(不可触) 但是他是活动状态的 （本人用来挂机小游戏）
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool setNotVisibleWindow(HWND hwnd);
    /**
     * @brief 判断窗口是否最大化
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isMaximize(HWND hwnd);
    /**
     * @brief 判断窗口是否最小化
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isMinimized(HWND hwnd);
    /**
     * @brief 判断窗口是否全屏中
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isFullScreen(HWND hwnd);
    /**
     * @brief  窗口是否处于正常状态（未最大化、未最小化、未处于全屏模式）
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isNormal(HWND hwnd);
    /**
     * @brief 设置窗口到屏幕中间
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern std::variant<bool, DWORD> setWindowCenter(HWND hwnd);
    /**
     * @brief 获取当前激活的窗口
     *
     * @return HWND
     */
    extern HWND getFocusWindow();
    /**
     * @brief 窗口是否获得焦点
     *
     * @param hwnd
     * @return true
     * @return false
     */
    extern bool isFocused(HWND hwnd);
    /**
     * @brief 获取窗口的类
     *
     * @param hwnd
     * @return vector<>
     */
    extern std::vector<LONG> getWinwowClassList(HWND hwnd);
    /**
     * @brief 获取窗口的扩展类
     *
     * @param hwnd
     * @return vector<>
     */
    extern std::vector<LONG> getWinwowClassListEx(HWND hwnd);

    /**
     * @brief 窗口扩展类(LongClass)值转文本 GWL_STYLE
     *
     * @param classLong
     * @return std::string
     */
    extern std::string winwowLongClass2str(LONG classLong);

    /**
     * @brief 窗口扩展类(LongClassEx)值转文本 GWL_EXSTYLE
     *
     * @param classLong
     * @return std::string
     */
    extern std::string winwowLongClass2strEx(LONG classLong);

    /**
     * @brief 获取窗口的扩展类
     *
     * @param hwnd
     * @return vector<>
     */
    extern std::vector<std::string> getWinwowClassLongNameList(HWND hwnd);
    /**
     * @brief 获取窗口的扩展类
     *
     * @param hwnd
     * @return vector<>
     */
    extern std::vector<std::string> getWinwowClassLongNameListEx(HWND hwnd);

    struct chWindowHwndStatus
    {
        // 当前句柄枚举的子集句柄
        std::vector<HWND> sub;
        // 父窗口
        HWND parent;
        // 当前输入的句柄
        HWND hwnd;
        // top win 排除桌面
        HWND root;
        // 下个窗口
        HWND next;
        // 上个窗口
        HWND prev;
        // 末尾窗口
        HWND end;
        // 进程id
        DWORD pid;
        // 线程id
        DWORD threadId;
        // 所有者窗口
        HWND owner;
        // 首个子窗口
        HWND firstChild;
        // 首个兄弟窗口
        HWND firstBrother;
        // 兄弟尾窗口
        HWND lastSibling;
        // 判断窗口是否是窗口而不是组件
        bool exists;
        // 默认构造函数
        chWindowHwndStatus()
        {
            parent = nullptr;
            hwnd = nullptr;
            root = nullptr;
            next = nullptr;
            prev = nullptr;
            end = nullptr;
            owner = nullptr;
            firstChild = nullptr;
            firstBrother = nullptr;
            lastSibling = nullptr;
            pid = 0;
            exists = false;
            sub = {};
        }
    };

    // ! 逻辑复杂 暂时未写
    /**
     *
     * @brief 获取窗口基础信息并且深挖他所属的进程的所有句柄
     *
     * @param hwnd
     * @return chWindowStatus
     */
    extern std::variant<chWindowHwndStatus, DWORD> getWindowHwndStatus(HWND hwnd);
    /**
     * @brief 矩形与坐标相交
     *
     * @param rect 矩形位置
     * @param x 坐标 x
     * @param y 坐标 y
     * @return true
     * @return false
     */
    extern bool isInside(RECT rect, long x, long y);
    /**
     * @brief 矩形与坐标相交
     *
     * @param x1 矩形x起点
     * @param y1 矩形y起点
     * @param x2 矩形x终点
     * @param y2 矩形y终点
     * @param x 坐标 x
     * @param y 坐标 y
     * @return true
     * @return false
     */
    extern bool isInside(long x1, long y1, long x2, long y2, long x, long y);
    /**
     * @brief 矩形与坐标相交
     *
     * @param x1 矩形x起点
     * @param y1 矩形y起点
     * @param x2 矩形x终点
     * @param y2 矩形y终点
     * @param point 坐标
     * @return true
     * @return false
     */
    extern bool isInside(long x1, long y1, long x2, long y2, POINT point);
    /**
     * @brief 矩形与坐标相交
     *
     * @param rect 矩形位置
     * @param point 坐标
     * @return true
     * @return false
     */
    extern bool isInside(RECT rect, POINT point);
    /**
     * @brief 获取所有屏幕的坐标
     *
     * @return std::vector<RECT>
     */
    extern std::variant<std::vector<RECT>, DWORD> getDeviceCapsAll();
    /**
     * @brief 获取句柄所在的屏幕位置
     *
     * @return RECT
     */
    extern std::variant<RECT, DWORD> getWinwowPointDeviceCaps(HWND hwnd);
    /**
     * @brief 获取窗口所在坐标
     *
     * @return std::variant<RECT, DWORD>
     */
    extern std::variant<RECT, DWORD> getWindowRect(HWND hwnd);
    /**
     * @brief 获取鼠标所在窗口的进程id
     *
     * @param hwnd
     * @return DWORD
     */
    extern DWORD getPointWindowProcessId(HWND hwnd);
    /**
     * @brief 获取鼠标所在窗口的线程id
     *
     * @param hwnd
     * @return DWORD
     */
    extern DWORD getPointWindowThreadId(HWND hwnd);
    /**
     * @brief 获取鼠标所在的屏幕的位置信息
     *
     * @return RECT
     */
    extern RECT getCurrentMonitorRect();
    /**
     * @brief 判断句柄的窗口是否在鼠标所在的窗口
     *
     * @param isVisible 是否要求必须可见(没被遮挡)
     * @return true
     * @return false
     */
    extern bool isMouseMonitorWindow(std::optional<bool> isVisible = std::nullopt);
    /**
     * @brief
     * @param hWndParent 父窗口
     * @param hWndChildAfter 下級窗口
     * @param className 类名
     * @param titleName 标题
     * @return true
     * @return false
     */
    extern bool findWindowEx(HWND hWndParent, HWND hWndChildAfter, std::optional<std::wstring> className = std::nullopt, std::optional<std::wstring> titleName = std::nullopt);
    /**
     * @brief 通过标题或类名搜索所有窗口句柄 (所有)
     *
     * @param className 类名
     * @param titleName 标题
     * @param isWindow 是否要求为窗口(忽略子组件) 默认 true
     * @param isCaseSensitive 忽略区分大小写 默认 true
     * @return true
     * @return false
     */
    extern bool findWindowAll(std::optional<std::wstring> className, std::optional<std::wstring> titleName = std::nullopt, bool isWindow = true, bool isCaseSensitive = true);
    /**
     * @brief 通过标题或类名搜索所有窗口句柄
     *
     * @param className 类名
     * @param titleName 标题
     * @return HWND
     */
    extern HWND findWindow(std::optional<std::wstring> className = std::nullopt, std::optional<std::wstring> titleName = std::nullopt);
    /**
     * @brief 扩展值多到离谱的功能
     *
     * @param nIndex
     * @return long long
     */
    extern long long getSystemMetrics(int nIndex);
    /**
     * @brief 标题栏的尺寸、状态和样式等信息
     *
     * @param hWnd
     * @return std::variant<TITLEBARINFO, DWORD>
     */
    extern std::variant<TITLEBARINFO, DWORD> getTitleBarInfo(HWND hWnd);

    /**
     * @brief 设置窗口类名称
     *
     * @param hWnd 句柄
     * @param className 类名称
     * @return std::variant<bool, DWORD>
     */
    extern std::variant<bool, DWORD> setWindowClassName(HWND hWnd, std::optional<std::wstring> className = std::nullopt);

    /**
     * @brief 设置窗口风格扩展值
     *
     * @param hWnd 句柄
     * @param nIndex 偏移量
     * @param dwNewLong 替换值
     * @param type 设置方式
     * - 0 添加 默认
     * - 1 移除
     * - 3 替换
     * @return std::variant<bool, DWORD>
     */
    extern std::variant<bool, DWORD> setWindowStyleLong(HWND hWnd, int nIndex, long dwNewLong, std::optional<DWORD> type = std::nullopt);

    /**
     * @brief 检索有关指定窗口的信息。
     *
     * @param hWnd
     * @return std::variant<bool, DWORD>
     */
    extern std::variant<PWINDOWINFO, DWORD> getWindowInfo(HWND hWnd);

    /**
     * @brief 更改子窗口、弹出窗口或顶级窗口的大小、位置和 Z 顺序。 这些窗口根据其在屏幕上的外观进行排序。 最上面的窗口接收最高排名，是 Z 顺序中的第一个窗口。
     *
     * @return true
     * @return false
     */
    extern bool setWindowPos(HWND hWnd, HWND hWndInsertAfter, std::optional<int> X = std::nullopt, std::optional<int> Y = std::nullopt, std::optional<int> cx = std::nullopt, std::optional<int> cy = std::nullopt, std::optional<UINT> uFlags = std::nullopt);

}

#endif // MODE_INTERNAL_INCLUDE_HMC_WINDOWS_V2_HPP