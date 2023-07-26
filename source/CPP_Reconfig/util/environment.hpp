#define _CRT_SECURE_NO_WARNINGS
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
#include <ShlObj.h>

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "Shlwapi.lib")
#define MAX_KEY_LENGTH 255
#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))

using namespace std;

// 获取指定的环境变量
static bool GetVariable(string const &name, string &data)
{
    data.clear();
#if defined(_MSC_VER)
    size_t size;
    getenv_s(&size, NULL, 0, name.c_str());
    if (size > 0)
    {
        vector<char> tmpvar(size);
        errno_t result = getenv_s(&size, tmpvar.data(), size, name.c_str());
        string variable = (result == 0 ? string(tmpvar.data()) : "");
        data.append(variable);
        return true;
    }
    else
    {
        return false;
    }
#else
    char const *variable = getenv(name.c_str());
    if (variable ? true : false)
    {
        data.append(variable);
    }
    return variable ? true : false;
#endif
}

// 二进制编译的版本
static string GetBinaryArch()
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
static BOOL isSystemFor64bit()
{
    SYSTEM_INFO SystemInfo;
    ::GetNativeSystemInfo(&SystemInfo);
    if (SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 || SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        return TRUE;
    else
        return FALSE;
}

static map<string, string> getVariableAll()
{
    map<string, string> envStrMap;

    // 注意这里A字符很乱 请勿改成A （OEM ，Unicode ，ANSI）
    try
    {
        LPWSTR lpszVariable;
        LPWCH lpvEnv;

        lpvEnv = GetEnvironmentStringsW();
        if (lpvEnv != nullptr)
        {

            lpszVariable = reinterpret_cast<LPWSTR>(lpvEnv);
            while (*lpszVariable)
            {
                string strEnv(hmc_text_util::W2A(lpszVariable));

                int sep = strEnv.rfind("=");
                string key = strEnv.substr(0, sep);
                string value = strEnv.substr(sep + 1);
                if (!key.empty() && string(&key.at(0)) != string("="))
                    envStrMap.insert(pair<string, string>(key, value));
                lpszVariable += lstrlenW(lpszVariable) + 1;
            }

            FreeEnvironmentStringsW(lpvEnv);
        }
    }
    catch (const exception &e)
    {
    }

    return envStrMap;
}

static map<string, string> getGlobalVariableAll()
{
    map<string, string> envStrMap;

    // 注意这里A字符很乱 请勿改成A （OEM ，Unicode ，ANSI）
    try
    {
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
                    if (!name.empty())
                    {
                        envStrMap.insert(pair<string, string>(name, value));
                    }
                }
            }
            env += wcslen(env) + 1;
        }
    }
    catch (const exception &e)
    {
    }

    return envStrMap;
}

namespace hmc_env
{
    /**
     * @brief 获取环境变量值
     *
     * @param name
     * @return string
     */
    bool getenv(string const &name, string &data)
    {
        if (GetVariable(name, data))
        {
            return true;
        };
        return false;
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
        int n_cmd_args = 0;
        LPWSTR *cmd_arg_list = CommandLineToArgvW(GetCommandLineW(), &n_cmd_args);

        for (size_t i = 1; i < n_cmd_args; ++i)
        {
            LPWSTR arg = cmd_arg_list[i];
            cmdList.push_back(hmc_text_util::W2A(arg));
        }

        if (!n_cmd_args)
            return cmdList;

        FREE(cmd_arg_list);

        return cmdList;
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
        CHAR lpFilename[MAX_PATH];
        ::GetModuleFileNameA(NULL, lpFilename, MAX_PATH);
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

        CHAR lpFilename[MAX_PATH];
        ::GetModuleFileNameA(NULL, lpFilename, MAX_PATH);
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
     * @brief 判断是否存在此环境变量的键值
     *
     * @param key
     * @return true
     * @return false
     */
    bool hasEnvKey(string key)
    {

        if (GetEnvironmentVariableA(key.c_str(), NULL, 0) > 0 ||
            GetLastError() == ERROR_SUCCESS)
        {
            return true;
        }
        return false;
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
     * @brief 添加环境变量 请注意这会传递到所有子进程
     *
     * @param key
     * @param Value
     * @return true
     * @return false
     */
    bool putenv(string key, string Value, bool append = false)
    {
        string newValue;

        if (append)
        {
            if (!GetVariable(key, newValue))
            {
                return false;
            };
            newValue.append(";");
            newValue.append(Value);
            int b_Result = _putenv_s(key.c_str(), newValue.c_str());
            return b_Result == 0;
        }

        return false;
    }

    /**
     * @brief 添加环境变量内容数组
     *
     * @param key
     * @param Value
     * @return true
     * @return false
     */
    bool putenv(string key, vector<string> Value)
    {
        string ValueStr = string();
        for (auto &&data : Value)
        {
            ValueStr.append(data);
            ValueStr.append(";");
        }

        if (!ValueStr.empty() && ValueStr.back() == ';')
            ValueStr.pop_back();

        int b_Result = _putenv_s(key.c_str(), ValueStr.c_str());
        return b_Result == 0;
    }

    /**
     * @brief 获取当前的变量环境列表
     *
     * @return map<string, string>
     */
    map<string, string> getEnvList()
    {
        return getVariableAll();
    }

    /**
     * @brief 删除指定的变量值
     *
     * @param key
     * @return true
     * @return false
     */
    bool removeEnv(string key)
    {
        bool rc = true;
        if (key.at(0) == '=' || !SetEnvironmentVariableA(key.c_str(), NULL))
        {

            rc = GetEnvironmentVariableA(key.c_str(), NULL, NULL) == 0 &&
                 GetLastError() != ERROR_SUCCESS;
        }
        return rc;
    }
    /**
     * @brief 获取当前的变量环境列表（强制从注册表实时读取）
     *
     * @return map<string, string>
     */
    map<string, string> getGlobalEnvList()
    {
        return getGlobalVariableAll();
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

            if (!has(MutexName))
            {
                AllMutexHandles.erase(MutexName);
                return true;
            }
            return false;
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

    /**
     * @brief 判断当前进程是否拥有管理员权限
     *
     * @return true
     * @return false
     */
    bool isAdmin()
    {
        return IsUserAnAdmin();
    }

    /**
     * @brief 系统变量操作（会写入系统和运行环境）
     *
     */
    namespace systemEnv
    {
        /**
         * @brief 转大写
         *
         * @param data
         * @return string
         */
        string keyUpper(string data)
        {
            string Result;
            Result.append(data);
            for (char &c : data)
            {
                if (std::isalpha(static_cast<unsigned char>(c)))
                {
                    c = std::toupper(c);
                }
            }
            return Result;
        }

        /**
         * @brief 对比两个键是否相等
         *
         * @param key
         * @param key2
         */
        bool keyDiff(string key, string key2)
        {
            return keyUpper(key) == keyUpper(key);
        }

        /**
         * @brief 这些值不允许删除也不允许修改
         *
         */
        vector<string> freezeEnvKeys = {"CommonProgramFiles(x86)",
                                        "PUBLIC",
                                        "SystemDrive",
                                        "ProgramFiles(x86)",
                                        "ProgramData",
                                        "COMPUTERNAME",
                                        "ALLUSERSPROFILE",
                                        "HOMEDRIVE",
                                        "LOGONSERVER",
                                        "USERDOMAIN",
                                        "APPDATA",
                                        "LOCALAPPDATA",
                                        "HOMEPATH",
                                        "SESSIONNAME",
                                        "USERPROFILE",
                                        "USERNAME",
                                        "CommonProgramFiles",
                                        "ProgramFiles",
                                        "ProgramW6432",
                                        "SystemRoot"};

        /**
         * @brief 获取指定键值 按照默认优先级
         * ?- 用户变量和系统变量同时有非数组键  -> 用户变量
         * ?- 用户变量和系统变量同时为数组键    -> 用户变量数组
         * ?- 用户变量为数组键 系统变量为文本键  -> 用户文本键 排除系统
         * ?- 系统变量为文本键 用户变量为数组    -> 用户变量数组 排除系统
         * ?- 系统变量存在 用户变量为空文本      -> 排除此变量
         * ?- PATH                          -> 合并数组
         * @param key 键
         * @param pEnvStr 数据写入到此传址string变量
         * @param transMean 转义(默认true)
         * @return true
         * @return false
         */
        bool get(string key, string &pEnvStr, bool transMean = true) {}

        /**
         * @brief 获取指定键值(从系统)
         *
         * @param key
         * @param pEnvStr
         * @param transMean
         * @return true
         * @return false
         */
        bool getSys(string key, string &pEnvStr, bool transMean = true) {}

        /**
         * @brief 写入变量到系统变量
         *
         * @param key 键
         * @param Value 值
         * @param append 添加到尾部 而不是替换
         * - 默认 false
         * @param transMean 是自字符转义
         * - 默认 false
         * @return true
         * @return false
         */
        bool putSys(string key, string Value, bool append = false, bool transMean = false)
        {
        }

        /**
         * @brief 写入变量 自动判断
         *
         * @param key 键
         * @param Value 值
         * @param append 添加到尾部 而不是替换
         * - 默认 false
         * @param transMean 是自字符转义
         * - 默认 false
         * @return true
         * @return false
         */
        bool put(string key, string Value, bool append = false, bool transMean = false)
        {
        }

        /**
         * @brief 写入变量 到用户
         *
         * @param key 键
         * @param Value 值
         * @param append 添加到尾部 而不是替换
         * - 默认 false
         * @param transMean 是自字符转义
         * - 默认 false
         * @return true
         * @return false
         */
        bool putUse(string key, string Value, bool append = false, bool transMean = false)
        {
        }

        /**
         * @brief 获取系统环境变量
         *
         * @param key 键
         * @param pEnvStr 数据写入到此传址string变量
         * @param transMean 转义(默认true)
         * @return true
         * @return false
         */
        bool getUse(string key, string &pEnvStr, bool transMean = true)
        {
        }

        /**
         * @brief 获取系统变量
         *
         * @param key 键
         * @param pEnvStr 数据写入到此传址string变量
         * @param transMean 转义(默认true)
         * @return true
         * @return false
         */
        bool getSys(string key, string &pEnvStr, bool transMean = true)
        {
        }

        /**
         * @brief 按照默认优先级删除
         * ?部分key 如 SystemDeive 是自动忽略的
         *
         * @param key 键
         * @return true
         * @return false
         */
        bool remove(string key)
        {
        }

        /**
         * @brief 删除用户变量
         *
         * @param key 键
         * @return true
         * @return false
         */
        bool removeUse(string key)
        {
        }

        /**
         * @brief 删除系统变量
         * ?部分key 如 SystemDeive 是自动忽略的
         * @param key 键
         * @return true
         * @return false
         */
        bool removeSys(string key)
        {
        }

        /**
         * @brief 删除所有此变量
         * ?部分key 如 SystemDeive 是自动忽略的
         * @param key 键
         * @return true
         * @return false
         */
        bool removeAll(string key)
        {
        }

        /**
         * @brief 从注册表读取并更新到当前环境
         *
         * @return true
         * @return false
         */
        bool updateThis() {}

        /**
         * @brief 判断是否存在此键
         *
         * @param key 键
         * @return true
         * @return false
         */
        bool hasSys(string key)
        {
        }

        /**
         * @brief 判断是否存在此键
         *
         * @param key 键
         * @return true
         * @return false
         */
        bool hasUse(string key) {}

        /**
         * @brief 判断是否存在此键（不区分系统和用户）
         * ?- 用户变量和系统变量同时有非数组键  -> 用户变量
         * ?- 用户变量和系统变量同时为数组键    -> 用户变量
         * ?- 用户变量为数组键 系统变量为文本键  -> 用户
         * ?- 系统变量为文本键 用户变量为数组    -> 用户变量
         * ?- 系统变量存在 用户变量为空文本      -> 排除
         * @param key 键
         * @return true
         * @return false
         */
        bool has(string key)
        {
        }

        /**
         * @brief 必须系统和用户都存在此键才返回true
         *
         * @param key 键
         * @return true
         * @return false
         */
        bool hasAll(string key)
        {
        }

        /**
         * @brief 是个可扩展的值
         *
         * @param key
         * @return true
         * @return false
         */
        bool hasExpval(string key)
        {
        }

        // 枚举所有的变量数据的data
        struct ListSystemEnvCont
        {
            // 转义完成的系统变量列表
            map<string, vector<string>> system;
            // 转义完成的系统变量列表
            map<string, vector<string>> user;
            // 系统变量  [注册表里的原始文本(未转义)]
            map<string, vector<string>> systemOrig;
            // 用户变量  [注册表里的原始文本(未转义)]
            map<string, vector<string>> userOrig;
            // 按照环境进行合并
            map<string, vector<string>> env;
        };

        /**
         * @brief 获取系统 所有变量名 但是不查询值
         *
         */
        vector<string> keySysList()
        {
        }

        /**
         * @brief 获取用户 所有变量名 但是不查询值
         *
         */
        vector<string> keyUseList()
        {
        }

        /**
         * @brief 枚举注册表内的变量
         *
         * @return listSystemEnvCont
         */
        ListSystemEnvCont list()
        {
            struct ListSystemEnvCont listSystemEnvCont;
        }

    }
}
