#ifndef HMC_IMPORT_HMC_SHELL_V2_H
#define HMC_IMPORT_HMC_SHELL_V2_H
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

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
    extern bool copyFile(const std::wstring& filePath, const std::wstring& newFilePath, bool isShowConfirm, bool isShow, bool isShowProgress);

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
    extern bool moveFile(const std::wstring& filePath, const std::wstring& newFilePath, bool isShowConfirm, bool isShow, bool isShowProgress);

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
     * @brief 显示文件的系统右键
     *
     * @param hwnd 窗口句柄
     * @param filePath 文件路径
     * @param x 左到右的坐标
     * @param y 上到下的坐标
     * @return true
     * @return false
     */
    extern bool showContextMenu(HWND hwnd, std::vector<std::wstring> filePathList, int x, int y);

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
    extern bool SetFolderIcon(const std::wstring& folderPath, const std::wstring& iconPath, int iconIndex);

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
     * @brief 系统时间转为时间戳 [纳秒/毫秒]
     *
     * @param st 时间戳数据体
     * @param is_Millisecond 是否转为毫秒
     * @return long long int
     */
    extern long long int getTimestamp(const SYSTEMTIME& st, bool is_Millisecond);

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
        static constexpr int _TB_BUTTONCOUNT = _WM_USER + 24;  // WM_USER+24
        static constexpr int _TB_GETBUTTON = _WM_USER + 23;    // WM_USER+23
        static constexpr int _TB_DELETEBUTTON = _WM_USER + 22; // WM_USER+22

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

        /**
         * @brief 使用资源管理器默认关联格式开启路径
         *
         * @param Path
         * @return int
         */
        static int openInExplorer(std::wstring Path);
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
        bool createDirSymlink(const std::wstring& targetPath, const std::wstring& sourcePath);

        /**
         * @brief 创建文件软链接
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createSymlink(const std::wstring& targetPath, const std::wstring& sourcePath);

        /**
         * @brief 创建硬链接
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createHardLink(const std::wstring& targetPath, const std::wstring& sourcePath);

        /**
         * @brief 创建目录连接点
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createSymbolicLink(const std::wstring& targetPath, const std::wstring& sourcePath);

        /**
         * @brief 判断此文件是否是链接文件
         *
         * @param Path
         */
        bool isLink(const std::wstring& Path);

        /**
         * @brief 判断此文件是否是硬链接文件
         *
         * @param filePath
         * @return true
         * @return false
         */
        bool isHardLink(const std::wstring& filePath);

        /**
         * @brief 获取软链接指向的路径
         *
         * @param symlinkPath
         * @return string
         */
        std::wstring getSymbolicLinkTarget(const std::wstring& symlinkPath);

        /**
         * @brief 获取硬链接指向的文件列表
         *
         * @param hardlinkPath
         * @return string
         */
        std::vector<std::wstring> getHardLinkList(const std::wstring& filePath);
    };


    class Dialog
    {

    public:

        /**
         * @brief 选取文件夹
         *
         * @param folderPaths 写入文件夹路径的文本数组
         * @param initRootDir 初始化的文件夹位置
         * @param initSelectName 当前选中的文件的名称
         * @param title 选取器标题
         * @param confirmLabel 确认选择按钮的显示文字
         * @param multSelect 是否允许多选(多个文件)
         * @param dontAddToRecent   不写入到近期打开文件列表
         * @return true
         * @return false
         */
        static bool SelectFolder(std::vector<std::wstring>& folderPaths, const std::wstring& initRootDir = L"", const std::wstring& initSelectName = L"", const std::wstring& title = L"", const std::wstring& confirmLabel = L"", bool multSelect = true, bool dontAddToRecent = false);
        
        /**
         * @brief 选取文件夹
         *
         * @param folderPath 写入文件夹路径的文本
         * @param initRootDir 初始化的文件夹位置
         * @param initSelectName 当前选中的文件的名称
         * @param title 选取器标题
         * @param confirmLabel 确认选择按钮的显示文字
         * @param dontAddToRecent   不写入到近期打开文件列表
         * @return true
         * @return false
         */
        static bool SelectFolder(std::wstring& folderPath, const std::wstring& initRootDir = L"", const std::wstring& initSelectName = L"", const std::wstring& title = L"", const std::wstring& confirmLabel = L"", bool dontAddToRecent = false);
        
        /**
         * @brief 选取文件
         *
         * @param FilePaths 写入文件路径的数组
         * @param initRootDir 初始化的文件夹位置
         * @param initSelectName 当前选中的文件的名称
         * @param title 选取器标题
         * @param confirmLabel 确认选择按钮的显示文字
         * @param filters 文件类型过滤器 filtr 过滤
         * { "图片" , L"*.jpg;*.jpeg" },
         * { "位图", L"*.bmp" },
         * { "全选", L"*.*" },
         * @param dontAddToRecent   不写入到近期打开文件列表
         * @param multSelect 是否允许多选(多个文件)
         * @return true
         * @return false
         */
        static bool SelectFile(std::vector<std::wstring>& FilePaths, const std::wstring& initRootDir = L"", const std::wstring& initSelectName = L"", const std::wstring& title = L"", const std::wstring& confirmLabel = L"", const std::vector<std::pair<std::wstring, std::wstring>>& filters = {}, bool dontAddToRecent = false, bool multSelect = true);
        
        /**
         * @brief 选取文件
         *
         * @param FilePath 写入文件路径的文本
         * @param initRootDir 初始化的文件夹位置
         * @param initSelectName 当前选中的文件的名称
         * @param title 选取器标题
         * @param confirmLabel 确认选择按钮的显示文字
         * @param filters 文件类型过滤器 filtr 过滤
         * { "图片" , L"*.jpg;*.jpeg" },
         * { "位图", L"*.bmp" },
         * { "全选", L"*.*" },
         * @param dontAddToRecent   不写入到近期打开文件列表
         * @return true
         * @return false
         */
        static bool SelectFile(std::wstring& FilePath, const std::wstring& initRootDir = L"", const std::wstring& initSelectName = L"", const std::wstring& title = L"", const std::wstring& confirmLabel = L"", const std::vector<std::pair<std::wstring, std::wstring>>& filters = {}, bool dontAddToRecent = false);
       
        /**
         * @brief 选取文件
         *
         * @param filters 文件类型过滤器 filtr 过滤
         * { "图片" , L"*.jpg;*.jpeg" },
         * { "位图", L"*.bmp" },
         * { "全选", L"*.*" },
         * @param multSelect 是否允许多选(多个文件)
         * @return std::vector<std::wstring>
         */
        static std::vector<std::wstring> SelectFile(const std::vector<std::pair<std::wstring, std::wstring>>& filters = {}, bool multSelect = true);

        /**
         * @brief 选取文件夹
         *
         * @param multSelect 是否允许多选(多个文件)
         * @return std::vector<std::wstring>
         */
        static std::vector<std::wstring> SelectFolder(bool multSelect = true);

        /**
         * @brief 选择一个保存到的文件选定框
         *
         * @param filePath 文件路径
         * @param selectExt 扩展名
         * @param initFolder 初始化的文件夹路径
         * @param defaultName 当前默认的文件名称
         * @param title 保存选取框的标题
         * @param confirmLabel 保存按钮的显示文字
         * @param extensionList 扩展名选择器
         * @return true
         * @return false
         */
        static bool SelectSaveFile(std::wstring& filePath, std::wstring& selectExt, const std::wstring& initFolder = L"", const std::wstring& defaultName = L"", const std::wstring& title = L"", const std::wstring& confirmLabel = L"", const std::vector<std::pair<std::wstring, std::wstring>>& extensionList = {});

        /**
         * @brief 选择一个保存到的文件夹选定框
         *
         * @param folderPath 文件夹路径
         * @param initFolder 初始化的文件夹路径
         * @param defaultName 当前默认的文件名称
         * @param title 保存选取框的标题
         * @param confirmLabel 保存按钮的显示文字
         * @return true
         * @return false
         */
        static bool SelectSaveFolder(std::wstring& folderPath, const std::wstring& initFolder = L"", const std::wstring& defaultName = L"", const std::wstring& title = L"", const std::wstring& confirmLabel = L"");

        /**
         * @brief 选取文件夹 旧版
         *
         * @param folderPath 文件夹路径获取到
         * @param title 设置窗口标题
         * @return true
         * @return false
         */
        static bool SelectFolderOld(std::wstring& folderPath, const std::wstring& title = L""); 
    };

    /**
    * @brief 获取文件缩略图到文件中
    *
    * @param input 文件
    * @param nSize 要求尺寸
    * @return
    */
    extern std::vector<std::uint8_t> getThumbnailBuffer(std::wstring input, int nSize = 256);
    /**
     * @brief 获取文件缩略图到文件中
     *
     * @param input 文件
     * @param output 输出
     * @param nSize 要求尺寸
     * @return
     */
    extern bool getThumbnailToFile(std::wstring input, std::wstring output, int nSize = 256);

    class Startup
	{
	private:
        static const wchar_t WIN32_RunOnceW[50];
        static const wchar_t WIN32_RunW[46];

        static const char WIN32_RunOnceA[50];
        static const char WIN32_RunA[46];
	public:
		/**
		 * @brief 设置自启动
		 *
		 * @param key 项目名称
		 * @param execPath 启动的可执行文件路径
		 * @param cmd 带入的命令行
		 * @return true
		 * @return false
		 */
		static bool set(const std::wstring &key, const std::wstring &execPath, const std::wstring &cmd = L"");
		/**
		 * @brief 设置自启动 (仅单次启动)
		 *
		 * @param key 项目名称
		 * @param execPath 启动的可执行文件路径
		 * @param cmd 带入的命令行
		 * @return true
		 * @return false
		 */
		static bool setOnce(const std::wstring &key, const std::wstring &execPath, const std::wstring &cmd = L"");

		/**
		 * @brief 删除自启动项目
		 *
		 * @param key 项目名称
		 * @return true
		 * @return false
		 */
		static bool remove(const std::wstring &key);
		/**
		 * @brief 判断自启动存在性
		 *
		 * @param key 项目名称
		 * @return true
		 * @return false
		 */
		static bool has(const std::wstring &key);
		/**
		 * @brief 删除自启动项目 (仅单次启动)
		 *
		 * @param key 项目名称
		 * @return true
		 * @return false
		 */
		static bool removeOnce(const std::wstring &key);
		/**
		 * @brief 判断自启动存在性 (仅单次启动)
		 *
		 * @param key 项目名称
		 * @return true
		 * @return false
		 */
		static bool hasOnce(const std::wstring &key);

				/**
		 * @brief 设置自启动
		 *
		 * @param key 项目名称
		 * @param execPath 启动的可执行文件路径
		 * @param cmd 带入的命令行
		 * @return true
		 * @return false
		 */
		static bool set(const std::string &key, const std::string &execPath, const std::string &cmd = "");
		/**
		 * @brief 设置自启动 (仅单次启动)
		 *
		 * @param key 项目名称
		 * @param execPath 启动的可执行文件路径
		 * @param cmd 带入的命令行
		 * @return true
		 * @return false
		 */
		static bool setOnce(const std::string &key, const std::string &execPath, const std::string &cmd = "");

		/**
		 * @brief 删除自启动项目
		 *
		 * @param key 项目名称
		 * @return true
		 * @return false
		 */
		static bool remove(const std::string &key);
		/**
		 * @brief 判断自启动存在性
		 *
		 * @param key 项目名称
		 * @return true
		 * @return false
		 */
		static bool has(const std::string &key);
		/**
		 * @brief 删除自启动项目 (仅单次启动)
		 *
		 * @param key 项目名称
		 * @return true
		 * @return false
		 */
		static bool removeOnce(const std::string &key);
		/**
		 * @brief 判断自启动存在性 (仅单次启动)
		 *
		 * @param key 项目名称
		 * @return true
		 * @return false
		 */
		static bool hasOnce(const std::string &key);
	};

}


#endif // HMC_IMPORT_HMC_SHELL_V2_H
