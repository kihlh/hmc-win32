#include <windows.h>
#include <string>
#include <winuser.h>
#include <ShlObj.h>
#include <Shellapi.h>
#include <Psapi.h>
#include <thread>
#include <vector>
#include <fstream>

// 输入法相关
#include <imm.h>
#pragma comment(lib, "imm32.lib")

// 图标获取
#include <atlimage.h>
#include <shobjidl.h>
#include <shlguid.h>

using namespace std;
#define HMC_IMPORT_SHELL_H
#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))
#define HMC_CHECK_CATCH catch (char *err){};
#define HMC_THREAD (code) std::thread([]() -> void { code }).detach();

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

    namespace _shell_lib
    {
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

        string _str_WinRunApplication_Path = string();
        bool _has_WinRunApplication_ok = false;

    }

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
     * @brief 清空回收站
     *
     * @return true
     * @return false
     */
    bool trashClear()
    {
        SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
        return true;
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
         * @brief 判断此文件是否是链接文件
         *
         * @param Path
         */
        bool hasLink(string Path)
        {
            DWORD dwAttr = GetFileAttributesA(Path.c_str());
            if (dwAttr == INVALID_FILE_ATTRIBUTES)
            {
                return false;
            }
            return dwAttr & FILE_ATTRIBUTE_REPARSE_POINT;
        }

        /**
         * @brief 获取软链接指向的路径
         *
         * @param symlinkPath
         * @return string
         */
        string getSymbolicLinkTarget(const std::string &symlinkPath)
        {
            HANDLE hFile = CreateFileA(symlinkPath.c_str(), 0, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return "";
            }

            char_t targetPath[MAX_PATH];
            DWORD pathSize = GetFinalPathNameByHandleA(hFile, targetPath, MAX_PATH, 0);
            if (pathSize == 0)
            {
                CloseHandle(hFile);
                return "";
            }

            std::string finalPath(targetPath, pathSize);

            CloseHandle(hFile);
            return finalPath;
        }

        /**
         * @brief 获取硬链接指向的文件列表
         *
         * @param hardlinkPath
         * @return string
         */
        vector<string> GetHardLinks(const std::string &filePath)
        {
            std::vector<std::string> hardLinks;

            WIN32_FIND_DATA findData;
            HANDLE hFind = FindFirstFileA(filePath.c_str(), &findData);

            if (hFind == INVALID_HANDLE_VALUE)
            {
                return hardLinks;
            }

            do
            {
                // 检查是否为硬链接
                if (findData.nNumberOfLinks > 1 && findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    // 硬链接的索引节点（文件ID）与原始文件的相同
                    if (findData.nFileIndexLow == findData.nFileIndexHigh)
                    {
                        hardLinks.push_back(findData.cFileName);
                    }
                }
            } while (FindNextFileA(hFind, &findData));

            FindClose(hFind);

            return hardLinks;
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
        bool status;    // 可用
                        // 构造函数
        chShortcutLinkItem()
            : path(""), showCmd(0), args(""), desc(""), icon(""), iconIndex(0), cwd(""), hotkey(0), status(false)
        {
        }
    };

    /**
     * @brief 设置输入法为英文 解决Chrome的编辑器BUG
     *
     * @param hwnd
     * @return true
     * @return false
     */
    bool switchImeEnglish(HWND hwnd = 0)
    {
        // 获取输入法上下文
        HIMC hImc = ImmGetContext(hwnd ? hwnd : GetForegroundWindow());
        if (hImc == nullptr)
        {
            return false;
        }
        // 设置输入法的首选转换模式为英文
        ImmSetConversionStatus(hImc, IME_CMODE_ALPHANUMERIC, IME_SMODE_AUTOMATIC);
        // 释放输入法上下文
        ImmReleaseContext(hwnd ? hwnd : GetForegroundWindow(), hImc);
        return true;
    }

    /**
     * @brief 显示系统选择文件时候的右键文件菜单栏
     *
     * @param filePath
     * @param x
     * @param y
     * @return true
     * @return false
     */
    bool ShowContextMenu(wstring filePath, int x = 0, int y = 0)
    {
        try
        {
            // 没有传入鼠标位置则获取当前鼠标位置
            if (x == 0 && y == 0)
            {
            }

            // 初始化COM
            CoInitialize(NULL);
            IShellItem *pItem;
            HRESULT hr = SHCreateItemFromParsingName(filePath.c_str(), NULL, IID_PPV_ARGS(&pItem));
            if (FAILED(hr))
            {
                return false;
            }
            // 获取文件的 IContextMenu 接口
            IContextMenu *pContextMenu;
            hr = pItem->BindToHandler(NULL, BHID_SFUIObject, IID_PPV_ARGS(&pContextMenu));
            if (FAILED(hr))
            {
                pItem->Release();
                return false;
            }
            // 创建菜单
            HMENU hMenu = CreatePopupMenu();
            if (hMenu == NULL)
            {
                pContextMenu->Release();
                pItem->Release();
                return false;
            }
            hr = pContextMenu->QueryContextMenu(hMenu, 0, 1, 0x7FFF, CMF_NORMAL);
            if (FAILED(hr))
            {
                DestroyMenu(hMenu);
                pContextMenu->Release();
                pItem->Release();
                return false;
            }
            // 弹出菜单
            int command = TrackPopupMenuEx(hMenu, TPM_RETURNCMD | TPM_NONOTIFY, x, y, GetForegroundWindow(), NULL);
            if (command > 0)
            {
                CMINVOKECOMMANDINFOEX info = {0};
                info.cbSize = sizeof(info);
                info.hwnd = GetForegroundWindow();
                info.lpVerb = MAKEINTRESOURCEA(command - 1);
                info.nShow = SW_NORMAL;
                pContextMenu->InvokeCommand((LPCMINVOKECOMMANDINFO)&info);
            }
            // 释放资源
            DestroyMenu(hMenu);
            pContextMenu->Release();
            pItem->Release();
            CoUninitialize();
            return true;
        }
        HMC_CHECK_CATCH;
        return false;
    }

    /**
     * @brief 获取快捷方式内容结构
     *
     * @param Path
     * @return chShortcutLinkItem
     */
    chShortcutLinkItem getShortcutLink(wstring Path)
    {
        chShortcutLinkItem result = {};
        try
        {
            std::string tempArguments;
            std::string tempWorkingDirectory;
            std::string tempShortcutPath;
            std::string tempIconPath;
            int tempGetShowCmdNum = 0;
            int tempPIcon = 0;
            WORD tempPwHotkey = 0;

            HRESULT hr;
            IShellLinkA *pShellLink;
            WIN32_FIND_DATAA findData;

            // 初始化 COM
            hr = CoInitialize(NULL);
            if (FAILED(hr))
                return result;

            // 创建 IShellLink 接口对象
            hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (LPVOID *)&pShellLink);
            if (FAILED(hr))
            {
                CoUninitialize();
                return result;
            }

            // 使用 IPersistFile 接口打开快捷方式文件
            IPersistFile *pPersistFile;
            hr = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID *)&pPersistFile);
            if (FAILED(hr))
            {
                pShellLink->Release();
                CoUninitialize();
                return result;
            }

            // 加载快捷方式文件
            hr = pPersistFile->Load((LPWSTR)Path.c_str(), STGM_READ);
            if (FAILED(hr))
            {
                pPersistFile->Release();
                pShellLink->Release();
                CoUninitialize();
                return result;
            }

            // 获取快捷方式的目标路径
            hr = pShellLink->GetPath((LPSTR)tempShortcutPath.data(), MAX_PATH, &findData, SLGP_UNCPRIORITY);
            if (SUCCEEDED(hr))
            {
                result.path.append(tempShortcutPath);
                tempShortcutPath.clear();
            }

            // 获取快捷方式的参数
            hr = pShellLink->GetArguments((LPSTR)tempArguments.data(), MAX_PATH);
            if (SUCCEEDED(hr))
            {
                result.args.append(tempArguments);
                tempArguments.clear();
            }

            // 获取快捷方式的工作目录
            hr = pShellLink->GetWorkingDirectory((LPSTR)tempWorkingDirectory.data(), MAX_PATH);
            if (SUCCEEDED(hr))
            {
                result.cwd.append(tempWorkingDirectory);
                tempWorkingDirectory.clear();
            }

            // 获取图标
            hr = pShellLink->GetIconLocation((LPSTR)tempIconPath.data(), MAX_PATH, &tempPIcon);
            if (SUCCEEDED(hr))
            {
                result.icon.append(tempIconPath);
                result.iconIndex = tempPIcon;
                tempIconPath.clear();
            }

            // Hotkey
            hr = pShellLink->GetHotkey(&tempPwHotkey);
            if (SUCCEEDED(hr))
            {
                result.hotkey = tempPwHotkey;
            }

            // ShowCmd
            hr = pShellLink->GetShowCmd(&tempGetShowCmdNum);
            if (SUCCEEDED(hr))
            {
                result.showCmd = tempGetShowCmdNum;
            }

            // 释放资源
            pPersistFile->Release();
            pShellLink->Release();
            CoUninitialize();
        }
        HMC_CHECK_CATCH;
        return result;
    }

    /**
     * @brief 使用win自带的运行 执行程序
     *
     * @param Path
     */
    void winRunApplication(string Path)
    {
        _shell_lib::_str_WinRunApplication_Path.clear();
        _shell_lib::_str_WinRunApplication_Path.append(Path);
        std::thread([]() -> void
                    {
        try
        {
           
            keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event(0x52, 0, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event(0x52, 0, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);

            // 粘贴文本进入输入框中
            for (size_t i = 0; i < 100; i++)
            {
                if ( _shell_lib::_has_WinRunApplication_ok)
                    return;
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

                if (hmc_shell:: _shell_lib::_lib_keyUpper(FilePath) == string("EXPLORER.EXE"))
                {
                    EnumChildWindows(
                        focusWin, [](HWND hWnd, LPARAM lParam) -> BOOL
                        {
                            int controlId = GetDlgCtrlID(hWnd);
                            if (controlId == 1001)
                            {
                                LPSTR lpClassName = {0};
                                SendMessageA(hWnd, WM_SETTEXT, 0, (LPARAM) _shell_lib::_str_WinRunApplication_Path.c_str());
                                Sleep(50);

                                keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY, 0);
                                keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY, 0);

                                Sleep(50);
                                 _shell_lib::_has_WinRunApplication_ok = true;
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
         _shell_lib::_str_WinRunApplication_Path.clear(); })
            .detach();
    }

    /**
     * @brief 获取缩略图
     *
     * @param source
     * @param target
     * @param size
     * @return true
     * @return false
     */
    bool getThumbnailPngFile(std::wstring source, wstring target, int size = 256)
    {
        CoInitialize(NULL);
        IShellItemImageFactory *itemImageFactory;
        HBITMAP bitmap;
        SIZE s = {size, size};
        if (SUCCEEDED(SHCreateItemFromParsingName(source.c_str(), NULL, IID_PPV_ARGS(&itemImageFactory))))
        {
            itemImageFactory->GetImage(s, SIIGBF_ICONONLY, &bitmap);
            itemImageFactory->Release();
        }
        CoUninitialize();
        if (NULL == &bitmap)
        {
            return false;
        }
        else
        {
            CImage image;
            image.Attach(bitmap);
            image.SetHasAlphaChannel(1);
            image.Save(target.c_str());
            return true;
        }
        return false;
    }

    bool setShortcutLink(wstring Path, chShortcutLinkItem ShortcutLinkItem)
    {
        HRESULT hRes = CoInitialize(NULL);
        if (!SUCCEEDED(hRes))
        {

            return false;
        }
        IShellLinkA *pIShellLink;
        hRes = ::CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&pIShellLink);
        if (!SUCCEEDED(hRes))
        {

            return false;
        }
        hRes = pIShellLink->SetPath((LPCSTR)ShortcutLinkItem.path.c_str());
        if (!SUCCEEDED(hRes))
        {

            return false;
        }
        hRes = pIShellLink->SetDescription((LPCSTR)ShortcutLinkItem.desc.c_str());
        if (!SUCCEEDED(hRes))
        {

            return false;
        }
        hRes = pIShellLink->SetWorkingDirectory((LPCSTR)ShortcutLinkItem.cwd.c_str());
        if (!SUCCEEDED(hRes))
        {

            return false;
        }
        hRes = pIShellLink->SetArguments((LPCSTR)ShortcutLinkItem.args.c_str());
        if (!SUCCEEDED(hRes))
        {

            return false;
        }
        hRes = pIShellLink->SetShowCmd(ShortcutLinkItem.showCmd);
        if (!SUCCEEDED(hRes))
        {

            return false;
        }

        hRes = pIShellLink->SetIconLocation((LPCSTR)ShortcutLinkItem.icon.c_str(), ShortcutLinkItem.iconIndex);
        if (!SUCCEEDED(hRes))
        {

            return false;
        }
        IPersistFile *pIPersistFile;
        hRes = pIShellLink->QueryInterface(IID_IPersistFile, (void **)&pIPersistFile);
        if (!SUCCEEDED(hRes))
        {

            return false;
        }

        hRes = pIPersistFile->Save(Path.c_str(), FALSE);
        if (!SUCCEEDED(hRes))
        {

            return false;
        }
        pIPersistFile->Release();
        pIShellLink->Release();
        return true;
    }

    /**
     * @brief 设置文件夹夹的缩略图
     *
     * @param folderPath
     * @param iconPath
     * @param iconIndex
     * @return true
     * @return false
     */
    bool SetFolderIcon(const std::string &folderPath, const std::string &iconPath, int iconIndex = 0)
    {
        try
        {
            // 设置文件夹属性为只读，保护 desktop.ini 文件
            DWORD folderAttributes = GetFileAttributesA(folderPath.c_str());
            if (folderAttributes == INVALID_FILE_ATTRIBUTES)
                return false;

            if ((folderAttributes & FILE_ATTRIBUTE_READONLY) != FILE_ATTRIBUTE_READONLY)
                SetFileAttributes(folderPath.c_str(), folderAttributes | FILE_ATTRIBUTE_READONLY);

            // 构建 desktop.ini 文件路径
            std::string desktopIniPath = folderPath + L"\\desktop.ini";

            // 写入 desktop.ini 文件内容
            std::string iniContent = "[.ShellClassInfo]\nIconResource=" + iconPath + "," + std::to_string(iconIndex) + "\n";
            if (!WritePrivateProfileStringA(".ShellClassInfo", L"IconResource", (iconPath + "," + std::to_string(iconIndex)).c_str(), desktopIniPath.c_str()))
                return false;

            // 设置 desktop.ini 文件属性为隐藏和系统
            SetFileAttributesA(desktopIniPath.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);

            // 将文件夹的只读属性恢复
            SetFileAttributesA(folderPath.c_str(), folderAttributes);

            // 使文件夹的缩略图设置生效
            SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
        }
        HMC_CHECK_CATCH;

        return true;
    }

    /**
     * @brief 系统启动到现在已经多久了
     *
     * @return long long
     */
    long getSystemIdleTime()
    {
        int64_t SystemIdleTime = 0;
        try
        {
            LASTINPUTINFO lpi;
            lpi.cbSize = sizeof(lpi);
            GetLastInputInfo(&lpi);
            SystemIdleTime = ((GetTickCount() - lpi.dwTime) / 1000);
        }
        HMC_CHECK_CATCH;
        return SystemIdleTime;
    }

    /**
     * @brief 电源控制
     *
     * @param flage
     * - 1001 关机
     * - 1002 重启
     * - 1003 注销
     * - 1005 锁定
     * - 1006 关闭显示器
     * - 1007 打开显示器
     */
    void powerControl(int flage)
    {
        switch (Flage)
        {
        case 1001: // 关机
            ReSetWindows(EWX_SHUTDOWN, true);
            break;
        case 1002: // 重启
            ReSetWindows(EWX_REBOOT, true);
            break;
        case 1003: // 注销
            ReSetWindows(EWX_LOGOFF, false);
            break;
        case 1005: // 锁定
            LockWorkStation();
            break;
        case 1006: // 关闭显示器
            SendMessage(FindWindow(0, 0), WM_SYSCOMMAND, SC_MONITORPOWER, 2);
            break;
        case 1007: // 打开显示器
            SendMessage(FindWindow(0, 0), WM_SYSCOMMAND, SC_MONITORPOWER, -1);
            break;
        }
    }

    /**
     * @brief 锁定键盘与鼠标
     *
     * @param lockb
     * @return BOOL
     */
    BOOL lockSystemInteraction(bool lockb = false)
    {
        HINSTANCE hIn = NULL;
        hIn = LoadLibraryA("user32.dll");
        if (hIn)
        {
            BOOL(_stdcall * BlockInput)
            (BOOL bFlag);
            BlockInput = (BOOL(_stdcall *)(BOOL bFlag))GetProcAddress(hIn, "BlockInput");
            if (BlockInput)
                return !!BlockInput(lockb);
            else
                return FALSE;
        }
        else
            return FALSE;
        return FALSE;
    }

    /**
     * 播放例如win警告的声音
     */
    void beep()
    {
        try
        {
            MessageBeep(MB_ICONWARNING);
        }
        HMC_CHECK_CATCH;
    }
}
