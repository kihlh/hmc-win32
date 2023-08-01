#include <windows.h>
#include <string>
#include <windows.h>
#include <winuser.h>
#include <ShlObj.h>
#include <Shellapi.h>
#include <Psapi.h>

using namespace std;
#define HMC_IMPORT_SHELL_H
#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))
#define HMC_CHECK_CATCH catch (char *err){};

// 通用的HMCDEBUG 代码 在所有代码中引用 用于内部报错处理 避免黑盒错误
#ifndef HMC_DEBUG_CHECK_FUN_LIB
#define HMC_DEBUG_CHECK_FUN_LIB

#include <string>
#include <iostream>
#define HMC_CHECK_CATCH catch (char *err){};
bool vsErrorCodeAssert(DWORD check, std::string LogUserName = "HMC_CHECK")
{
    bool result = false;

    if (check == ERROR_SUCCESS)
    {
        result = true;
    }
    else
    {
#if HMC_IMPORT_CONSOLE_H
        hmc_console::debug(LogUserName, std::string("error_code:  ").append(std::to_string(check)).append("  \nPlease refer to the details:").append("https://learn.microsoft.com/zh-cn/windows/win32/debug/system-error-codes"));

#else
#ifdef _DEBUG
        std::cout << "---------->   [ERROR]    [" << LogUserName << "]    " << std::string("error_code:  ").append(std::to_string(check)).append("  \nPlease refer to the details:").append("https://learn.microsoft.com/zh-cn/windows/win32/debug/system-error-codes") << std::endl;
#endif

#endif // 头文件保护结束
    }

    return result;
}

#endif // 头文件保护结束

namespace hmc_shell
{
    /**
     * @brief 将文件或者文件夹放入回收站(调用的资源管理器)
     *
     * @param filePath 路径
     * @param Recycle 是否可以撤销
     * @param isShow 是否显示窗口
     * @return true
     * @return false
     */
    bool trashFile(const string &filePath, bool Recycle = true, bool isShowConfirm = true, bool isShow = true, bool isShowProgress = true)
    {
        SHFILEOPSTRUCTA fileOP = {0};
        ZeroMemory(&fileOP, sizeof(SHFILEOPSTRUCTA));
        fileOP.wFunc = FO_DELETE;
        fileOP.pFrom = filePath.c_str();
        fileOP.fFlags = (isShowConfirm ? FOF_NOCONFIRMATION : (isShowProgress ? 0 : FOF_SILENT)) | (Recycle ? FOF_ALLOWUNDO : 0) | FOF_NOCONFIRMATION | (isShow ? 0 : FOF_NO_UI);
        return vsErrorCodeAssert(SHFileOperationA(&fileOP));
    }

    /**
     * @brief 复制文件/文件夹(调用的资源管理器)
     *
     * @param filePath
     * @param newFilePath
     * @param isShow
     * @param isShowProgress
     * @return true
     * @return false
     */
    bool copyFile(const string &filePath, const string &newFilePath, bool isShowConfirm = true, bool isShow = true, bool isShowProgress = true)
    {
        SHFILEOPSTRUCTA fileOP = {0};
        ZeroMemory(&fileOP, sizeof(SHFILEOPSTRUCTA));
        fileOP.wFunc = FO_COPY;
        fileOP.pFrom = filePath.c_str();
        fileOP.pTo = newFilePath.c_str();
        fileOP.fFlags = (isShowConfirm ? 0 : (isShowProgress ? 0 : FOF_SILENT)) | FOF_NOCONFIRMATION | (isShow ? 0 : FOF_NO_UI);
        return vsErrorCodeAssert(SHFileOperationA(&fileOP));
    }

    /**
     * @brief 移动文件/文件夹(调用的资源管理器)
     *
     * @param filePath
     * @param newFilePath
     * @param isShow
     * @param isShowProgress
     * @return true
     * @return false
     */
    bool moveFile(const string &filePath, const string &newFilePath, bool isShowConfirm = true, bool isShow = true, bool isShowProgress = true)
    {
        SHFILEOPSTRUCTA fileOP = {0};
        ZeroMemory(&fileOP, sizeof(SHFILEOPSTRUCTA));
        fileOP.wFunc = FO_MOVE;
        fileOP.pFrom = filePath.c_str();
        fileOP.pTo = newFilePath.c_str();
        fileOP.fFlags = (isShowConfirm ? 0 : (isShowProgress ? 0 : FOF_SILENT)) | FOF_NOCONFIRMATION | (isShow ? 0 : FOF_NO_UI);
        return vsErrorCodeAssert(SHFileOperationA(&fileOP));
    }

    /**
     * @brief 启动一个程序并且分离管道
     *
     * @param openType 显示模式
     * - open 常规运行
     * - runas 以管理方式执行
     *
     *  启动一个程序
     * startApplication("open","node.exe","-v","f:/1/cwd",false);
     * 启动一个程序并提升到管理员
     * startApplication("runas","node.exe","-v","f:/1/cwd",false);
     * 启动一个程序 并且让他不显示窗口
     * startApplication("open","node.exe","-v","f:/1/cwd",true);
     * @param ExecuteFile 可执行文件
     * @param Parameters 执行的命令行
     * @param cwd 启始目录（工作环境）
     * @param hideExec 启动该程序 是否将其隐藏（窗口不可见）
     * @return true
     * @return false
     */
    bool startApplication(LPCSTR openType, string ExecuteFile, string Parameters, string cwd, bool hideExec)
    {

        int show_exec_code = hideExec ? SW_HIDE : SW_SHOW;
        HINSTANCE ToShellExecute = ShellExecuteA(
            NULL,
            (LPCSTR)openType,
            (LPCSTR)ExecuteFile.c_str(),
            (LPCSTR)Parameters.c_str(),
            (LPCSTR)cwd.c_str(),
            show_exec_code);

        return (int)ToShellExecute > 32 ? true : false;
    }

    /**
     * @brief 打开一个URL
     *
     * @param strURL
     * @return true
     * @return false
     */
    bool startURL(string strURL)
    {
        HINSTANCE hResult;

        hResult = ShellExecuteA(NULL, "open", strURL.c_str(), NULL, NULL, SW_SHOWNORMAL);
        return (int)hResult > 32 ? true : false;
    }

    /**
     * @brief 打开并选中此路径文件
     *
     * @param Path
     * @return true
     * @return false
     */
    bool startExternal(string Path)
    {
        string selectPathCmd = string("/select, \"");
        selectPathCmd.append(Path);
        selectPathCmd.append("\"");

        HINSTANCE hResult = ShellExecuteA(NULL, "open", "explorer.exe", selectPathCmd.c_str(), NULL, SW_SHOWNORMAL);
        return (int)hResult > 32 ? true : false;
    }

    /**
     * @brief 调用资源管理器直接运行此文件(也就是默认开启的应用执行)
     *
     * @param Path
     * @return true
     * @return false
     */
    bool startFilePath(string Path)
    {
        HINSTANCE hResult = ShellExecuteA(NULL, "open", "explorer.exe", Path.c_str(), NULL, SW_SHOWNORMAL);
        return (int)hResult > 32 ? true : false;
    }

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
        bool createDirSymlink(string targetPath, string sourcePath)
        {
            return CreateSymbolicLinkA(targetPath.c_str(), sourcePath.c_str(), 0x1);
        }

        /**
         * @brief 创建文件软链接
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createSymlink(string targetPath, string sourcePath)
        {
            return CreateSymbolicLinkA(targetPath.c_str(), sourcePath.c_str(), 0x1);
        }

        /**
         * @brief 创建硬链接
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createHardLink(string targetPath, string sourcePath)
        {
            return CreateHardLinkA(targetPath.c_str(), sourcePath.c_str(), NULL);
        }

        /**
         * @brief 创建目录连接点
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createSymbolicLink(string targetPath, string sourcePath)
        {
            return CreateSymbolicLinkA(targetPath.c_str(), sourcePath.c_str(), SYMBOLIC_LINK_FLAG_DIRECTORY);
        }

        /**
         * @brief 创建一个文件夹的文件软链接 (克隆文件夹结构)
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createDirWalkLink(string targetPath, string sourcePath)
        {
        }

        /**
         * @brief 创建一个文件夹的文件硬链接 (克隆文件夹结构)
         *
         * @param targetPath
         * @param sourcePath
         * @return true
         * @return false
         */
        bool createDirWalkHardLink(string targetPath, string sourcePath)
        {
        }

    };

    // 快捷键的信息
    struct chShortcutLinkItem
    {
        string path;    // 启动的文件路径
        WORD showCmd;   // 显示命令
        string args;    // 命令行
        string desc;    // 注释
        string icon;    // 图标路径 可以是dll ico exe ...
        WORD iconIndex; // 图标索引 例如是 0
        string cwd;     // 工作目录
        WORD hotkey;    // 热键
    };

    chShortcutLinkItem getShortcutLink(wstring Path)
    {
        chShortcutLinkItem result;
        result.args = "";
        result.cwd = "";
        result.desc = "";
        result.hotkey = 0;
        result.icon = "";
        result.path = "";
        result.showCmd = 0;
        result.iconIndex = 0;
        try
        {
            IShellLinkA *GetShellLinkContent;
            CoInitialize(0);
            char *tempGetPathString = new char[MAX_PATH];
            char *tempGetArgumentsString = new char[MAX_PATH];
            int tempGetShowCmdNum = 0;
            char *tempGetGetIconLocationString = new char[MAX_PATH];
            int piIcon = 0;
            char *tempGetGetDescriptionString = new char[MAX_PATH];
            char *tempGetWorkingDirectoryString = new char[MAX_PATH];
            WORD *pwHotkey = new WORD;
            string ss;
            HRESULT CreateHRESULT = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *)&GetShellLinkContent);
            DWORD dwReserved;
            if (SUCCEEDED(CreateHRESULT))
            {
                IPersistFile *PersistFile;
                CreateHRESULT = GetShellLinkContent->QueryInterface(IID_IPersistFile, (LPVOID *)&PersistFile);
                if (SUCCEEDED(CreateHRESULT))
                {
                    CreateHRESULT = PersistFile->Load(Path.c_str(), STGM_READ);

                    if (SUCCEEDED(CreateHRESULT))
                    {
                        WIN32_FIND_DATAA wfd;
                        GetShellLinkContent->GetPath(tempGetPathString, MAX_PATH, &wfd, SLGP_UNCPRIORITY | SLGP_RAWPATH);
                        GetShellLinkContent->GetShowCmd(&tempGetShowCmdNum);
                        GetShellLinkContent->GetArguments(tempGetArgumentsString, MAX_PATH);
                        GetShellLinkContent->GetDescription(tempGetGetDescriptionString, MAX_PATH);
                        GetShellLinkContent->GetIconLocation(tempGetGetIconLocationString, MAX_PATH, &piIcon);
                        GetShellLinkContent->GetWorkingDirectory(tempGetWorkingDirectoryString, MAX_PATH);
                        GetShellLinkContent->GetHotkey(pwHotkey);

                        result.hotkey = *pwHotkey + 0;
                        result.showCmd = tempGetShowCmdNum + 0;
                        result.cwd = tempGetWorkingDirectoryString;
                        result.path = tempGetPathString;
                        result.iconIndex = piIcon + 0;
                        result.desc = tempGetGetDescriptionString;
                        result.icon = tempGetGetIconLocationString;
                        result.args = tempGetArgumentsString;
                    }
                }
                else
                {
                }
            }
        }
        HMC_CHECK_CATCH;
        return result;
    }
    /**
     * @brief 转大写
     *
     * @param data
     * @return string
     */
    string _lib_keyUpper(string data)
    {
        string Result;
        for (char &c : data)
        {
            if (std::isalpha(static_cast<unsigned char>(c)))
            {
                Result.push_back(std::toupper(c));
            }
            else
            {
                Result.push_back(c);
            }
        }
        return Result;
    }
    string _str_WinRunApplication_Path;
    bool _has_WinRunApplication_ok = false;
   
    /**
     * @brief 使用win自带的运行 执行程序
     *
     * @param Path
     */
    void WinRunApplication(string Path)
    {
        try
        {
            _str_WinRunApplication_Path.clear();
            _str_WinRunApplication_Path.append(Path);
            keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event(0x52, 0, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event(0x52, 0, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);

            // 粘贴文本进入输入框中
            for (size_t i = 0; i < 100; i++)
            {
                if(_has_WinRunApplication_ok)return ;
                Sleep(50);
                HWND focusWin = GetForegroundWindow();

                DWORD pid = 0;
                DWORD theardId = GetWindowThreadProcessId(focusWin, &pid);
                string FilePath;
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
                bool has_ok = false;
                char lpFilename[MAX_PATH];
                if (hProcess == nullptr)
                {
                    continue;
                }

                GetModuleBaseNameA(hProcess, NULL, (LPSTR)lpFilename, MAX_PATH);
                CloseHandle(hProcess);
                FilePath.append(lpFilename);

                if (hmc_shell::_lib_keyUpper(FilePath) == string("EXPLORER.EXE"))
                {
                    EnumChildWindows(
                        focusWin, [](HWND hWnd, LPARAM lParam) -> BOOL
                        {
                            int controlId = GetDlgCtrlID(hWnd);
                            if (controlId == 1001)
                            {
                                LPSTR lpClassName = {0};
                                SendMessageA(hWnd, WM_SETTEXT, 0, (LPARAM)_str_WinRunApplication_Path.c_str());
                                Sleep(50);

                                keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY, 0);
                                keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY, 0);
                                
                                Sleep(50);
                                _has_WinRunApplication_ok = true;
                                return false;
                            }
                            return TRUE; // 返回 TRUE 以继续枚举下一个子控件
                        },
                        0);
                }
                else
                {
                    if (i > 80)
                    {
                        return;
                    }
                }
                if (has_ok)
                    return;
            }
        }
        HMC_CHECK_CATCH;
        _str_WinRunApplication_Path.clear();
    }

}
