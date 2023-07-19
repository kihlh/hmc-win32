#include <string>
#include <windows.h>
#include <Psapi.h>
#include <Shellapi.h>



#include "./environment.hpp"
using namespace hmc_env;

using namespace std;

namespace hmc_process
{
    /**
     * @brief 临时提权令牌
     *
     * @return BOOL
     */
    BOOL EnableShutDownPriv()
    {
        HANDLE Handle_Token = NULL;
        TOKEN_PRIVILEGES PermissionAttribute = {0};
        // 打开当前程序的权限令牌
        bool is_Open_Process_Token = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &Handle_Token);
        if (!is_Open_Process_Token)
        {
            return FALSE;
        }
        // 获得某一特定权限的权限标识LUID 保存到权限属性中
        if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &PermissionAttribute.Privileges[0].Luid))
        {
            CloseHandle(Handle_Token);
            return FALSE;
        }
        PermissionAttribute.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        PermissionAttribute.PrivilegeCount = 1;
        // 提升到系统权限
        if (!AdjustTokenPrivileges(Handle_Token, FALSE, &PermissionAttribute, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
        {
            CloseHandle(Handle_Token);
            return FALSE;
        }
        return TRUE;
    }

    /**
     * @brief 获取当前进程的父进程id
     *
     * @param matchProcessID
     * @return DWORD
     */
    DWORD getParentProcessID(DWORD matchProcessID)
    {
        DWORD CurrentProcessId = 0;
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        // 获取进程快照
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap == INVALID_HANDLE_VALUE)
        {
            return NULL;
        }

        // 枚举第一个进程
        if (Process32First(hSnap, &pe32))
        {
            do
            {
                // 打开进程句柄
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
                if (hProcess)
                {
                    if (pe32.th32ProcessID == matchProcessID)
                    {
                        CurrentProcessId = pe32.th32ParentProcessID;
                        CloseHandle(hProcess);
                        break;
                    }
                    CloseHandle(hProcess);
                }
            } while (Process32Next(hSnap, &pe32));
        }

        CloseHandle(hSnap);
        return CurrentProcessId;
    }

    /**
     * @brief 获取当前进程的所有子进程
     *
     * @param ProcessId
     * @param SubProcessIDList
     */
    void getSubProcessList(DWORD dwProcessID, vector<DWORD> &SubProcessIDList)
    {

        EnableShutDownPriv();
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        // 获取进程快照
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap == INVALID_HANDLE_VALUE)
        {
            return;
        }

        // 枚举第一个进程
        if (Process32First(hSnap, &pe32))
        {
            do
            {
                // 打开进程句柄
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
                if (hProcess)
                {
                    // 子进程的进程 ID
                    bool is_sub = pe32.th32ParentProcessID == dwProcessID;

                    // 二次子进程
                    if (!is_sub)
                    {
                        if (find(SubProcessIDList.begin(), SubProcessIDList.end(), pe32.th32ParentProcessID) != SubProcessIDList.end())
                        {
                            is_sub = true;
                        }
                    }

                    if (is_sub)
                    {
                        if (!(find(SubProcessIDList.begin(), SubProcessIDList.end(), pe32.th32ProcessID) != SubProcessIDList.end()))
                        {
                            SubProcessIDList.push_back(pe32.th32ProcessID);
                        }
                    }
                    CloseHandle(hProcess);
                }
            } while (Process32Next(hSnap, &pe32));
        }

        CloseHandle(hSnap);
    };

    /**
     * @brief 获取进程可执行文件路径
     *
     * @param ProcessID
     * @return string
     */
    string getFilePath(DWORD dwProcessID)
    {
        LPSTR lpFilename;
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);

        if (hProcess == nullptr)
        {
            CloseHandle(hProcess);
            return string("");
        }
        ::GetModuleFileNameExA(hProcess, NULL, lpFilename, MAX_PATH);
        return string(lpFilename);
    }

    /**
     * @brief 结束指定进程
     *
     * @param ProcessID
     * @return BOOL
     */
    BOOL kill(DWORD dwProcessID)
    {
        bool is_kill_success = false;
        EnableShutDownPriv();
        HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, dwProcessID);
        if (killHandle != NULL)
        {
            is_kill_success = TerminateProcess(killHandle, 0);
        }
        return is_kill_success;
    }

    /**
     * @brief 判断进程是否存在
     *
     * @param ProcessID
     * @return BOOL
     */
    BOOL exists(DWORD dwProcessID)
    {
        EnableShutDownPriv();
        bool exists_process = false;
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
        if (GetLastError())
            return false;

        exists_process = hProcess != NULL;
        CloseHandle(hProcess);
        return exists_process;
    }

    /**
     * @brief 获取进程的HWND
     *
     * @param dwProcessID
     * @return HWND
     */
    HWND getHwnd(DWORD dwProcessID)
    {
        HWND win_next_it = GetTopWindow(0);
        HWND result = NULL;
        while (win_next_it)
        {
            DWORD pid = 0;
            DWORD theardId = GetWindowThreadProcessId(win_next_it, &pid);
            if (theardId != 0)
            {
                if (pid == dwProcessID && GetParent(win_next_it) == NULL && ::IsWindowVisible(win_next_it))
                {

                    result = win_next_it;
                }
            }
            win_next_it = GetNextWindow(win_next_it, GW_HWNDNEXT);
        }
        return result;
    }

    /**
     * @brief 获取可执行文件名称
     *
     * @param dwProcessID
     * @return string
     */
    string getBaseName(DWORD dwProcessID)
    {
        string FilePath;
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
        char lpFilename[MAX_PATH];
        if (hProcess == nullptr)
        {

            return FilePath;
        }
        GetModuleBaseNameA(hProcess, NULL, (LPSTR)lpFilename, MAX_PATH);
        CloseHandle(hProcess);
        FilePath.append(lpFilename);
        return FilePath;
    }

    /**
     * @brief 枚举进程的线程信息
     *
     * @param dwProcessID
     * @param resultsModulePathList
     */
    void getThreadList(DWORD dwProcessID, vector<THREADENTRY32> &resultsModulePathList)
    {
        HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
        // `THREADENTRY32` 是一个结构体，它定义在 `tlhelp32.h` 头文件中。它描述了在系统执行快照时正在执行的线程列表中的条目。以下是 `THREADENTRY32` 结构体中的各个变量的含义：⁴⁵
        // - dwSize：结构体的大小，以字节为单位。
        // - cntUsage：线程使用计数。
        // - th32ThreadID：线程标识符，与 `CreateProcess` 函数返回的线程标识符兼容。
        // - th32OwnerProcessID：创建线程的进程标识符。
        // - tpBasePri：分配给线程的内核基优先级。
        // - tpDeltaPri：线程优先级相对于基本优先级的增量。
        // - dwFlags：保留，不再使用。
        THREADENTRY32 te32;

        // 对所有正在运行的线程进行快照
        hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if (hThreadSnap == INVALID_HANDLE_VALUE)
            return;

        te32.dwSize = sizeof(THREADENTRY32);

        // 检索第一个线程的信息
        if (!Thread32First(hThreadSnap, &te32))
        {
            CloseHandle(hThreadSnap);
            return;
        }

        do
        {
            if (te32.th32OwnerProcessID == dwProcessID)
            {
                resultsModulePathList.push_back(te32);
            }
        } while (Thread32Next(hThreadSnap, &te32));

        CloseHandle(hThreadSnap);
    }

    /**
     * @brief 获取进程引用的模块列表
     *
     * @param dwProcessID
     * @param resultsData
     */
    void getModulePathList(DWORD dwProcessID, vector<string> &resultsData)
    {

        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessID);
        if (hProcess == NULL)
            return;

        vector<HANDLE> vecFileHandles;

        // 枚举进程打开的文件句柄
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
        if (hSnapshot != INVALID_HANDLE_VALUE)
        {
            PROCESSENTRY32 pe32;
            pe32.dwSize = sizeof(PROCESSENTRY32);
            if (Process32First(hSnapshot, &pe32))
            {
                do
                {
                    if (pe32.th32ProcessID == dwProcessID)
                    {
                        HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessID);
                        if (hModuleSnap != INVALID_HANDLE_VALUE)
                        {
                            MODULEENTRY32 me32;
                            me32.dwSize = sizeof(MODULEENTRY32);
                            if (Module32First(hModuleSnap, &me32))
                            {
                                do
                                {
                                    HANDLE hFile = CreateFile(me32.szExePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                                    if (hFile != INVALID_HANDLE_VALUE)
                                    {
                                        vecFileHandles.push_back(hFile);
                                    }
                                } while (Module32Next(hModuleSnap, &me32));
                            }
                            CloseHandle(hModuleSnap);
                        }
                    }
                } while (Process32Next(hSnapshot, &pe32));
            }
            CloseHandle(hSnapshot);
        }

        // 输出文件路径
        for (auto it = vecFileHandles.begin(); it != vecFileHandles.end(); ++it)
        {
            LPSTR szFilePath = new CHAR[MAX_PATH];
            DWORD dwSize = GetFinalPathNameByHandleA(*it, szFilePath, MAX_PATH, FILE_NAME_NORMALIZED);
            if (dwSize > 0 && dwSize < MAX_PATH)
            {
                string strFilePath = szFilePath;
                string findStr = "\\\\?\\";
                if (strFilePath.find(findStr) == 0)
                {
                    strFilePath.replace(0, findStr.length(), "");
                }
                resultsData.push_back(strFilePath);
            }
            delete[] szFilePath;
            CloseHandle(*it);
        }

        CloseHandle(hProcess);
        return;
    }

    /**
     * @brief 获取鼠标所在的句柄的进程id
     *
     * @return DWORD
     */
    DWORD getPointWindowProcessId()
    {
        DWORD processId = 0;
        POINT curPoint;
        if (!GetCursorPos(&curPoint))
            return processId;
        HWND mainWindow = WindowFromPoint(curPoint);
        GetWindowThreadProcessId(mainWindow, &processId);
        return processId;
    }

    /**
     * @brief 获取鼠标所在的窗口的进程文件名
     *
     * @return string
     */
    string getPointWindowProcessBaseName()
    {
        return getBaseName(getPointWindowProcessId());
    }

    /**
     * @brief 获取当前聚焦的窗口的进程id
     *
     * @return DWORD
     */
    DWORD getFocusWindowProcessID()
    {
        DWORD processId;
        GetWindowThreadProcessId(GetForegroundWindow(), &processId);
        return processId;
    }

    /**
     * @brief 获取聚焦的窗口的进程文件名
     *
     * @return string
     */
    string getFocusWindowProcessBaseName()
    {
        return getBaseName(getFocusWindowProcessID());
    }

}