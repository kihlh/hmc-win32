#include <string>
#include <vector>
#include <windows.h>
#include <filesystem>
#include <shlwapi.h>
#include <processenv.h>
#include <map>
#include <regex>
#include <process.h>
#include <Tlhelp32.h>

#pragma comment(lib, "psapi.lib")

#include "./text.hpp"
using namespace hmc_text_util;

using namespace std;

// 获取指定的环境变量
string GetVariable(string const &name)
{
#if defined(_MSC_VER)
    size_t size;
    getenv_s(&size, nullptr, 0, name.c_str());
    if (size > 0)
    {
        vector<char> tmpvar(size);
        errno_t result = getenv_s(&size, tmpvar.data(), size, name.c_str());
        string var = (result == 0 ? string(tmpvar.data()) : "");
        return var;
    }
    else
    {
        return "";
    }
#else
    char const *variable = getenv(name.c_str());
    return variable ? string(variable) : string("");
#endif
}

// 二进制编译的版本
string GetBinaryArch()
{
#if _WIN32
    return string("x32");
#elif _WIN64
    return string("x64");
#else
    return string("ia32");
#endif
}

// 判断 x64 系统
BOOL isSystemFor64bit()
{
    SYSTEM_INFO SystemInfo;
    ::GetNativeSystemInfo(&SystemInfo);
    if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 || SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        return TRUE;
    else
        return FALSE;
}

map<string, string> getVariableAll()
{
    map<string, string> envStrMap;

    // 注意这里A字符很乱 请勿改成A （OEM ，Unicode ，ANSI）
    LPWSTR env = GetEnvironmentStringsW();

    while (*env)
    {
        string strEnv = hmc_text_util::W2A(env);

        if (strEnv.empty() && strEnv.find(L'=') == 0)
            continue;

        if (!strEnv.empty() && string(&strEnv.at(0)) != string("="))
        {
            size_t pos = strEnv.find('=');
            if (pos != string::npos)
            {
                string name = strEnv.substr(0, pos);
                string value = strEnv.substr(pos + 1);
                envStrMap.insert(pair<string, string>(name, value));
            }
        }
        env += wcslen(env) + 1;
    }
}

namespace hmc_env
{
    /**
     * @brief 获取环境变量值
     *
     * @param name
     * @return string
     */
    string getenv(string const &name)
    {
        return GetVariable(name);
    }

    /**
     * @brief 获取命令行
     *
     * @return string
     */
    string getcmdLine()
    {
        LPSTR commandStr = ::GetCommandLineA();
        return string(commandStr);
    }

    /**
     * @brief 获取启动命令
     *
     */
    vector<string> getcmd()
    {
        vector<string> cmdList;
        LPWSTR *szArglist;
        int nArgs;
        int i;

        szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
        if (NULL == szArglist)
        {
            return cmdList;
        }

        for (i = 0; i < nArgs; i++)
        {
            cmdList.push_back(hmc_text_util::W2A(szArglist[i]));
        }

        LocalFree(szArglist);
    }

    /**
     * @brief 获取pid
     *
     * @return DWORD
     */
    DWORD getpid()
    {
        DWORD processId = ::GetCurrentProcessId();
        return processId;
    }

    /**
     * @brief 获取ppid
     *
     * @return DWORD
     */
    DWORD getppid()
    {
        DWORD CurrentProcessId = 0;
        DWORD ThisProcessID = ::GetCurrentProcessId();

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
                    if (pe32.th32ProcessID == ThisProcessID)
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
     * @brief 获取工作目录
     *
     * @return DWORD
     */
    string getcwd()
    {
        string cwdPath;
        char buffer[MAX_PATH] = {0};
        DWORD size = ::GetCurrentDirectoryA(MAX_PATH, buffer);
        if (size > 0)
        {
            cwdPath.append(buffer);
            return cwdPath;
        }
        else
        {
            filesystem::path cwd = filesystem::current_path();
            cwdPath.append(cwd.string());
        }
        return cwdPath;
    }

    /**
     * @brief 获取可执行文件位置
     *
     * @return DWORD
     */
    string getexecPath()
    {
        string execFilePath = string();
        LPSTR lpFilename;
        ::GetModuleFileNameA(nullptr, lpFilename, MAX_PATH);
        execFilePath.append(lpFilename);
        return execFilePath;
    }

    /**
     * @brief 获取可执行文件所在的文件夹
     *
     * @return DWORD
     */
    string getexecDirPath()
    {
        string execDirPath = string();

        LPSTR lpFilename;
        ::GetModuleFileNameA(nullptr, lpFilename, MAX_PATH);
        ::PathRemoveFileSpecA(lpFilename);

        execDirPath.append(lpFilename);
        return execDirPath;
    }

    /**
     * @brief 获取编译的二进制平台(有些人会在x64机器跑x32应用 就很迷惑)
     *
     */
    string getbinArch()
    {
        return GetBinaryArch();
    }

    /**
     * @brief 获取当前应用的平台
     *
     * @return string
     */
    string getarch()
    {
        return (isSystemFor64bit() ? "x64" : "x32");
    }

    /**
     * @brief 添加环境变量 请注意这会传递到所有子进程
     *
     * @param key
     * @param Value
     * @return true
     * @return false
     */
    bool putenv(string key, string Value)
    {
        int b_Result = _putenv_s(key.c_str(), Value.c_str());
        return b_Result == 0;
    }

    /**
     * @brief Get the Env object
     *
     * @return map<string, string>
     */
    map<string, string> getEnvList()
    {
        return getVariableAll();
    }

    namespace Mutex
    {
        map<string, HANDLE> AllMutexHandles;
        /**
         * @brief 创建互斥体
         *
         * @param MutexName
         * @return true
         * @return false
         */
        bool create(string MutexName)
        {
            bool has_mut_exist = false;

            HANDLE hMutex = CreateMutexA(NULL, FALSE, MutexName.c_str());

            AllMutexHandles.insert(pair<string, HANDLE>(MutexName, hMutex));

            if (hMutex == NULL)
            {
                has_mut_exist = true;
            }
            // 检查是否已经存在同名的互斥体
            if (GetLastError() == ERROR_ALREADY_EXISTS)
            {
                has_mut_exist = true;
                CloseHandle(hMutex);
            }

            return !has_mut_exist;
        }
        /**
         * @brief 判断是否有这个互斥体
         *
         * @param MutexName
         * @return true
         * @return false
         */
        bool has(string MutexName)
        {
            bool has_mut_exist = true;

            HANDLE hMutex;

            hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, MutexName.c_str());
            if (NULL == hMutex)
            {
                has_mut_exist = false;
            }

            CloseHandle(hMutex);
            return has_mut_exist;
        }
        /**
         * @brief 删除通过此方法创建的互斥体
         *
         * @param MutexName
         * @return true
         * @return false
         */
        bool remove(string MutexName)
        {

            auto it = AllMutexHandles.find(MutexName);
            if (it == AllMutexHandles.end())
            {
                return false;
            }
            while (it != AllMutexHandles.end())
            {
                CloseHandle(it->second);
                it++;
            }
            return has(MutexName);
        }
        /**
         * @brief 获取当前已经创建的互斥体内容
         *
         * @return vector<string>
         */
        vector<string> list()
        {
            vector<string> list;
            map<string, HANDLE>::iterator it = AllMutexHandles.begin();

            while (it != AllMutexHandles.end())
            {
                list.push_back(it->first);
                it++;
            }
            return list;
        }
    }

}
