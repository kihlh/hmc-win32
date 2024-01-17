#ifndef HMC_IMPORT_HMC_SHELL_V2_H
#define HMC_IMPORT_HMC_SHELL_V2_H

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <thread>

#include <shobjidl.h>
#include <shlguid.h>
#include <ShlObj.h>

#include <imm.h>
#pragma comment(lib, "imm32.lib")

// 图标获取
#include <atlimage.h>
#include <shobjidl.h>
#include <shlguid.h>

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
    extern bool isSystemFor64bit();

    /**
     * @brief 复制文件/文件夹(调用的资源管理器)
     *
     * @param filePath 原来的文件路径
     * @param newFilePath 新的路径
     * @param isShow 是否显示窗口 [确认删除 并不影响选项4]
     * @param isShowProgress 是否显示进度
     * @return true
     * @return false
     */
    extern bool copyFile(const std::wstring &filePath, const std::wstring &newFilePath, bool isShowConfirm, bool isShow, bool isShowProgress);

    /**
     * @brief 移动文件/文件夹(调用的资源管理器)
     *
     * @param filePath 原来的文件路径
     * @param newFilePath 新的路径
     * @param isShow 是否显示窗口 [确认删除 并不影响选项4]
     * @param isShowProgress 是否显示进度
     * @return true
     * @return false
     */
    extern bool moveFile(const std::wstring &filePath, const std::wstring &newFilePath, bool isShowConfirm, bool isShow, bool isShowProgress);

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

    /**
     * @brief 使用win自带的运行 执行程序
     *
     * @param Path
     */
    extern void winRunApplication(const std::wstring &Path);

    /**
     * @brief 获取缩略图
     *
     * @param source 文件路径
     * @param target 保存位置
     * @param size 尺寸
     * @note 64
     * @note 128
     * @note 256
     * @return true
     * @return false
     */
    extern bool getThumbnailPngFile(const std::wstring source, const std::wstring target, int size);

    /**
     * @brief 获取缩略图
     *
     * @param source 文件路径
     * @param size 尺寸
     * @note 64
     * @note 128
     * @note 256 [默认]
     * @return std::vector<std::uint8_t>
     */
    extern std::vector<std::uint8_t> getThumbnailPng(const std::wstring source, int size);

    /**
     * @brief 电源控制
     *
     * @param flage
     * @note - 1001 关机
     * @note - 1002 重启
     * @note - 1003 注销
     * @note - 1005 锁定
     * @note - 1006 关闭显示器
     * @note - 1007 打开显示器
     */
    extern void powerControl(int flage);

    /**
     * @brief 执行注销，关机，重启
     *
     * @param dwReason
     * @note - EWX_REBOOT  重启
     * @note - EWX_LOGOFF 注销
     * @note - EWX_SHUTDOWN  关机
     * @param aims
     * @return true
     * @return false
     */
    bool powerControl(DWORD dwReason, bool aims);

    /**
     * @brief 设置文件夹夹的缩略图
     *
     * @param folderPath 文件夹路径
     * @param iconPath 路边地址
     * @param iconIndex 图标索引
     * @return true
     * @return false
     */
    extern bool SetFolderIcon(const std::wstring &folderPath, const std::wstring &iconPath, int iconIndex);

    /**
     * 播放win警告的声音
     */
    extern void beep();

    /**
     * @brief 系统启动到现在已经多久了（毫秒）
     *
     * @return long long
     */
    extern int64_t getSystemIdleTime();

    /**
     * @brief 添加软件自启动
     *
     * @param key
     * @param execPath
     * @param cmd
     * @return true
     * @return false
     */
    extern bool setStartup(const std::wstring &key, const std::wstring &execPath, const std::wstring &cmd , bool is_once );

    /**
     * @brief 移除软件自启动
     *
     * @param key
     * @return true
     * @return false
     */
    extern bool removeStartup(const std::wstring &key , bool is_once );

    /**
     * @brief 判断软件自启动
     *
     * @param key
     * @return true
     * @return false
     */
    extern bool hasStartup(const std::wstring &key , bool is_once );

    /**
     * @brief 系统时间转为时间戳 [纳秒/毫秒]
     *
     * @param st 时间戳数据体
     * @param is_Millisecond 是否转为毫秒
     * @return long long int
     */
    extern long long int getTimestamp(const SYSTEMTIME &st, bool is_Millisecond);

    /**
     * @brief 系统时间转为时间戳 [纳秒/毫秒]
     *
     * @param is_Millisecond 是否转为毫秒
     * @return long long int
     */
    extern long long int getTimestamp(bool is_Millisecond);

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

    };

    namespace Symlink
    {
        /**
         * @brief 创建文件夹软链接
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createDirSymlink(const std::wstring &targetPath, const std::wstring &sourcePath);

        /**
         * @brief 创建文件软链接
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createSymlink(const std::wstring &targetPath, const std::wstring &sourcePath);

        /**
         * @brief 创建硬链接
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createHardLink(const std::wstring &targetPath, const std::wstring &sourcePath);

        /**
         * @brief 创建目录连接点
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createSymbolicLink(const std::wstring &targetPath, const std::wstring &sourcePath);

        /**
         * @brief 判断此文件是否是链接文件
         *
         * @param Path
         */
        bool isLink(const std::wstring &Path);

        /**
         * @brief 判断此文件是否是硬链接文件
         *
         * @param filePath
         * @return true
         * @return false
         */
        bool isHardLink(const std::wstring &filePath);

        /**
         * @brief 获取软链接指向的路径
         *
         * @param symlinkPath
         * @return string
         */
        std::wstring getSymbolicLinkTarget(const std::wstring &symlinkPath);

        /**
         * @brief 获取硬链接指向的文件列表
         *
         * @param hardlinkPath
         * @return string
         */
        std::vector<std::wstring> getHardLinkList(const std::wstring &filePath);
    };

    class fileBrowser
    {
    public:
        /**
         * @brief 选取文件
         *
         * @param is_mult 是否多选
         * @param filtr 过滤
         * { "图片" , L"*.jpg;*.jpeg" },
         * { "位图", L"*.bmp" },
         * { "全选", L"*.*" },
         * @return std::vector<std::wstring>
         */
        std::vector<std::wstring> selectFile(bool is_mult = false, const std::wstring title = L"", const std::map<std::wstring, std::wstring> &filtr = {});
        std::vector<std::wstring> selectFolder(const std::wstring &folderPath, bool is_mult = false, const std::wstring title = L"");
        std::wstring selectFolderV1(const std::wstring &Title);

        struct Options
        {
            /**
             * @brief (可选)FileFilter 对象
             *
             */
            std::vector<std::tuple<std::wstring, std::wstring>> filters;
            /**
             * @brief  (可选)FileFilter 对象
             * @note 数组应为没有通配符或点的扩展名  "png" 是正确的, 而 ".png" 和 *. png " 就是错误的)。 若要显示所有文件, 请使用 "*" 通配符 (不支持其他通配符)
             * @note  { name: 'Images', extensions: ['jpg', 'png', 'gif'] },
             * @note  { name: 'Movies', extensions: ['mkv', 'avi', 'mp4'] },
             * @note  { name: 'Custom File Type', extensions: ['as'] },
             * @note  { name: 'All Files', extensions: ['*'] }
             */
            std::vector<std::tuple<std::wstring, std::vector<std::wstring>>> filters_extensions;
            std::wstring title;       // (可选) - 对话框标题。
            std::wstring defaultPath; // (可选) - 默认情况下使用的绝对目录路径、绝对文件路径或文件名。
            std::wstring buttonLabel; // (可选) - 「确认」按钮的自定义标签, 当为空时, 将使用默认标签。
            /**
             * @brief (可选) - 包含对话框相关属性。 支持以下属性值
             * @note openFile        - 允许选择文件 （如果 openFile 和 openDirectory 同时存在则为 openDirectory ）
             * @note openDirectory   - 允许选择文件夹
             * @note multiSelections - 允许多选。
             * @note showHiddenFiles - 显示对话框中的隐藏文件。
             * @note promptToCreate  - 如果输入的文件路径在对话框中不存在, 则提示创建。 这并不是真的在路径上创建一个文件，而是允许返回一些不存在的地址交由应用程序去创建。
             * @note dontAddToRecent - 要将正在打开的项目添加到最近的文档列表中
             */
            std::vector<std::wstring> properties;

            Options();
        };

    private:
        /**
         * @brief 选择文件夹 （古老的小框选择器 无法指定路径的那种）
         *
         * @param Title
         * @param SelectFolderPath
         * @return true
         * @return false
         */
        bool SelectFolderV1(const std::wstring &Title, const std::wstring &SelectFolderPath);

        /**
         * @brief 选择文件夹（单选）
         *
         * @param folderPath
         * @return true
         * @return false
         */
        bool SelectFolder(const std::wstring &folderPath);

        /**
         * @brief 选择文件夹(多选)
         *
         * @param folderPaths
         * @return true
         * @return false
         */
        bool SelectFolders(std::vector<std::wstring> &folderPaths);

        /**
         * @brief 选择文件 （多个文件）
         *
         * @param filePaths
         * @return true
         * @return false
         */
        bool SelectFiles(std::vector<std::wstring> &filePaths);

        /**
         * @brief 选择文件 （单个文件）
         *
         * @param FilePath
         * @return true
         * @return false
         */
        bool SelectFile(const std::wstring &FilePath);

        /**
         * @brief
         *
         * @param FilePath
         * @param rgSpec
         * @return true
         * @return false
         */
        bool SelectFile(const std::wstring &FilePath, std::map<std::wstring, std::wstring> filtr);

        /**
         * @brief 选择文件(多选) 外加过滤器
         *
         * @param FilePaths
         * @param filtr
         * @return true
         * @return false
         */
        bool SelectFiles(std::vector<std::wstring> &FilePaths, const std::map<std::wstring, std::wstring> &filtr);
    };
}

#endif // HMC_IMPORT_HMC_SHELL_V2_H
