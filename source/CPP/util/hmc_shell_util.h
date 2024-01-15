#ifndef HMC_IMPORT_HMC_SHELL_V2_H
#define HMC_IMPORT_HMC_SHELL_V2_H

#include <windows.h>
#include <string>
#include <vector>
#include <map>

#include <shobjidl.h>
#include <shlguid.h>

#include <imm.h>
#pragma comment(lib, "imm32.lib")

namespace hmc_shell_util
{
    // 快捷方式的信息
    struct chShortcutLinkItem
    {
        std::wstring path; // 目标路径
        int64_t showCmd;   // 启动属性
        std::wstring args; // 启动命令
        std::wstring desc; // 描述
        std::wstring icon; // 进程图标(例如来自1.dll)
        int64_t iconIndex; // 图标索引位置 (例如来自1.dll 里的第1个 )
        std::wstring cwd;  // 工作环境文件夹
        int64_t hotkey;    // hotkey

        // 有效性判断
        bool isValid();

        chShortcutLinkItem();
    };

    /**
     * @brief 判断当前系统是否是64位
     *
     * @return BOOL
     */
    extern BOOL isSystemFor64bit();

    /**
     * @brief 删除文件到回收站
     *
     * @param FromPath 需要删除的文件
     * @param bRecycle 放入回收站而不是删除
     * @param isShow 是否显示对话框
     * @return int
     */
    extern int trashFile(std::wstring FromPath, bool bRecycle, bool isShow);

    /**
     * @brief 清空回收站
     *
     * @param hwnd 窗口句柄
     * @param RootPath 根目录为空则全部清楚
     * @param dwFlags 显示类型
     * - SHERB_NOCONFIRMATION 不会显示确认删除对象的对话框。
     * - SHERB_NOPROGRESSUI 不显示指示进度的对话框
     * - SHERB_NOSOUND 操作完成后，不会播放任何声音
     * @return true
     * @return false
     */
    extern bool clearTrash(HWND hwnd, std::wstring RootPath, DWORD dwFlags);

    /**
     * @brief 获取快捷方式的信息
     *
     * @param lnkPath 快捷方式的路径
     * @return chShortcutLinkItem
     */
    extern chShortcutLinkItem getShortcutLink(std::wstring lnkPath);

    /**
     * @brief 创建快捷方式
     * 
     * @param lnkPath 快捷方式位置
     * @param FilePath 关联的文件
     * @param work_dir 工作目录
     * @param desc 简介
     * @param args 启动命令
     * @param iShowCmd 显示方式
     * @param icon 使用的图标如dll,exe,icon
     * @param iconIndex 图标索引（二进制的第n个）
     * @return true 
     * @return false 
     */
    extern bool setShortcutLink(std::wstring lnkPath, std::wstring FilePath, std::wstring work_dir, std::wstring desc, std::wstring args, DWORD iShowCmd, std::wstring icon, DWORD iconIndex);
    
    /**
     * @brief 创建快捷方式
     * 
     * @param lnkPath 快捷方式位置
     * @param shortcutLinkItem 快捷方式的信息
     * @return true 
     * @return false 
     */
    extern bool setShortcutLink(std::wstring lnkPath, chShortcutLinkItem shortcutLinkItem);

    /**
     * @brief 显示文件的系统右键
     *
     * @param hwnd 窗口句柄
     * @param filePath 文件路径
     * @param x 左到右的坐标
     * @param y 上到下的坐标
     * @return true
     * @return false
     */
    extern bool showContextMenu(HWND hwnd, std::wstring filePath, int x, int y);

    /**
     * @brief 切换系统输入法
     *
     * @param hwnd 执行的窗口
     * @param sentencePatterns 输入法句子模式值
     * - IME_SMODE_AUTOMATIC   IME 在自动模式下执行转换处理。
     * - IME_SMODE_NONE  没有句子信息。
     * - IME_SMODE_PHRASEPREDICT  IME 使用短语信息来预测下一个字符。
     * - IME_SMODE_PLURALCLAUSE  IME 使用复数子句信息来执行转换处理
     * - IME_SMODE_SINGLECONVERT  IME 在单字符模式下执行转换处理。
     * - IME_SMODE_CONVERSATION  输入法使用对话模式。 这对于聊天应用程序很有用。
     * @param conversionModeValue IME 转换模式值
     * - IME_CMODE_ALPHANUMERIC  字母数字输入模式。 这是默认设置，定义为 0x0000。
     * - IME_CMODE_CHARCODE  如果字符代码输入模式，则设置为 1;如果不是，则为 0。
     * - IME_CMODE_EUDC  如果 EUDC 转换模式，则设置为 1;如果不是，则为 0。
     * - IME_CMODE_FIXED  Windows Me/98、Windows 2000、Windows XP： 如果固定转换模式，则设置为 1;如果不是，则为 0。
     * - IME_CMODE_FULLSHAPE  如果全形状模式，则设置为 1;如果半形状模式，则为 0。
     * - IME_CMODE_HANJACONVERT  如果 HANJA 转换模式，则设置为 1;如果不是，则为 0。
     * - IME_CMODE_KATAKANA  如果片假名模式，则设置为 1;如果平假名模式，则为 0。
     * - IME_CMODE_NATIVE  如果 NATIVE 模式，则设置为 1;如果 ALPHANUMERIC 模式，则为 0。
     * - IME_CMODE_NOCONVERSION  设置为 1 可阻止 IME 处理转换;如果不是，则为 0。
     * - IME_CMODE_ROMAN  如果 ROMAN 输入模式，则设置为 1;如果不是，则为 0。
     * - IME_CMODE_SOFTKBD  如果软键盘模式，则设置为 1;如果不是，则为 0。
     * - IME_CMODE_SYMBOL 	如果 SYMBOL 转换模式，则设置为 1;如果不是，则为 0。
     * @return true
     * @return false
     */
    extern bool setConversionStatus(HWND hwnd, DWORD sentencePatterns, DWORD unnamedParam3);

    /**
     * @brief 当前处于全屏模式
     *
     * @return true
     * @return false
     */
    extern bool isFullScreen();

    /**
     * @brief 判断聚焦中的窗口是否是全屏
     *
     * @return true
     * @return false
     */
    extern bool isFocusWindowFullScreen();

    // 枚举tray列表
    class GetTaryIconList
    {
    public:
        // 数据体
        struct TaryIcon
        {
            HWND hwnd;
            std::wstring path;
            std::wstring title;
            long index;
            TaryIcon(HWND hwnd, std::wstring path, std::wstring title, long index) : hwnd(hwnd), path(path), title(title), index(index) {}
        };
        // 枚举tray列表
        static std::vector<TaryIcon> getTrayList();
        // 枚举tray列表并转为json
        static std::wstring getTrayListJsonW();

    private:
        static constexpr int _WM_USER = 0x0400;
        static constexpr int _TB_BUTTONCOUNT = WM_USER + 24;  // WM_USER+24
        static constexpr int _TB_GETBUTTON = WM_USER + 23;    // WM_USER+23
        static constexpr int _TB_DELETEBUTTON = WM_USER + 22; // WM_USER+22

        // 判断 x64 系统
        static BOOL IsSystemFor64bit();
        // 获取折叠托盘窗口句柄
        static HWND GetNotifyOverflowTryHwnd();
        // 获取托盘窗口句柄
        static HWND GetSystemTrayHwnd();
        // 枚举控件句柄
        static std::vector<TaryIcon> EnumCommctrlList(HWND hWnd);
    };

    // 运行
    class ShellOpen
    {
    public:
        /**
         * @brief 打开程序
         *
         * @param AppPath 程序路径
         * @param Command 启动命令
         * @param cwd 工作文件夹
         * @param isHide 是否隐藏
         * @param isAdmin 是否以管理员方式启动
         * @return int
         */
        static int openApp(std::wstring AppPath, std::wstring Command = L"", std::wstring cwd = L"", bool isHide = false, bool isAdmin = false);
        /**
         * @brief 打开链接
         *
         * @param AppPath 打开链接
         * @param isCurrentBrowser 是否在当前执行中的浏览器中打开
         * @return int
         */
        static int openUrl(std::wstring Url, bool isCurrentBrowser = false);

        /**
         * @brief 在资源管理器中打开并且尽可能选中此文件
         *
         * @param Path 文件路径/文件夹路径
         * @param isSelect 是否选中此文件
         * @return int
         */
        static int showItemInFolder(std::wstring Path, bool isSelect = false);

    private:
        // 显示方式
        enum SW_SHOW_TYPE
        {
            WIN_SW_HIDE = 0,
            WIN_SW_SHOWNORMAL = 1,
            WIN_SW_NORMAL = 1,
            WIN_SW_SHOWMINIMIZED = 2,
            WIN_SW_SHOWMAXIMIZED = 3,
            WIN_SW_MAXIMIZE = 3,
            WIN_SW_SHOWNOACTIVATE = 4,
            WIN_SW_SHOW = 5,
            WIN_SW_MINIMIZE = 6,
            WIN_SW_SHOWMINNOACTIVE = 7,
            WIN_SW_SHOWNA = 8,
            WIN_SW_RESTORE = 9,
            WIN_SW_SHOWDEFAULT = 10,
            WIN_SW_FORCEMINIMIZE = 11,
            WIN_SW_MAX = 11
        };

        const wchar_t op_find[5] = L"find";
        const wchar_t op_explore[8] = L"explore";
        const wchar_t op_open[5] = L"open";
        const wchar_t op_runas[6] = L"runas";
    };

}

#endif // HMC_IMPORT_HMC_SHELL_V2_H
