#ifndef HMC_IMPORT_ENVIRONMENT_H
#define HMC_IMPORT_ENVIRONMENT_H

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <windows.h>
#include <shlwapi.h>
#include <processenv.h>
#include <set>
#include <map>
#include <regex>
#include <process.h>
#include <Tlhelp32.h>
#include <ShlObj.h>
// #include "./registr.hpp"
#include "../module/hmc_string_util.h"
#include "../module/hmc_registr_util.h"

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "Shlwapi.lib")
#define MAX_KEY_LENGTH 255
#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))

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

static map<wstring, wstring> getVariableAllW()
{
    map<wstring, wstring> envStrMap;

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
                wstring strEnv(lpszVariable);

                int sep = strEnv.rfind(L'=');
                wstring key = strEnv.substr(0, sep);
                wstring value = strEnv.substr(sep + 1);
                if (!key.empty() && wstring(&key.at(0)) != wstring(L"="))
                    envStrMap.insert(pair<wstring, wstring>(key, value));
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

static map<string, string> getVariableAllA()
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
                // lpszVariable
                wstring utf16 = lpszVariable;
                string ansi;

                if (utf16.empty())
                {
                    _ASSERTE(ansi.empty());
                    return envStrMap;
                }

                constexpr DWORD kFlags = WC_ERR_INVALID_CHARS;

                if (utf16.length() > static_cast<size_t>((numeric_limits<int>::max)()))
                {
                    //  __HMC_debug(string("Utf16ToAnsi"), string("Input string too long: size_t-length doesn't fit into int."));
                    return envStrMap;
                }

                const int utf16Length = static_cast<int>(utf16.length());

                const int ansiLength = ::WideCharToMultiByte(
                    CP_ACP,
                    kFlags,
                    utf16.data(),
                    utf16Length,
                    nullptr,
                    0,
                    nullptr, nullptr);
                if (ansiLength == 0)
                {
                    const DWORD error = ::GetLastError();
                    // hmc::error
                    string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-16 sequence found in input string." : "Cannot convert from UTF-16 to CP_ACP (WideCharToMultiByte failed).");
                    //  __HMC_debug(string("Utf16ToAnsi"), error_message, to_string(error));
                    return envStrMap;
                }

                ansi.resize(ansiLength);

                int result = ::WideCharToMultiByte(
                    CP_ACP,
                    kFlags,
                    utf16.data(),
                    utf16Length,
                    &ansi[0],
                    ansiLength,
                    nullptr, nullptr);
                if (result == 0)
                {
                    const DWORD error = ::GetLastError();
                    // hmc::error
                    string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-16 sequence found in input string." : "Cannot convert from UTF-16 to CP_ACP (WideCharToMultiByte failed).");
                    //  __HMC_debug(string("Utf16ToAnsi"), error_message, to_string(error));
                    return envStrMap;
                }

                int sep = ansi.rfind('=');
                string key = ansi.substr(0, sep);
                string value = ansi.substr(sep + 1);
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
     * @brief 设置当前的工作路径
     *
     * @param DirPath
     * @return true
     * @return false
     */
    bool setCwd(string const &DirPath)
    {
        return SetCurrentDirectoryA(DirPath.c_str());
    }

    /**
     * @brief 设置当前的工作路径
     *
     * @param DirPath
     * @return true
     * @return false
     */
    bool setCwd(wstring const &DirPath)
    {
        return SetCurrentDirectoryW(DirPath.c_str());
    }

    /**
     * @brief 获取环境变量值
     *
     * @param name
     * @return true
     * @return false
     */
    string getenv(string const &name)
    {
        string data;
        GetVariable(name, data);
        return data;
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
    vector<wstring> getcmd()
    {
        vector<wstring> cmdList;
        int n_cmd_args = 0;
        LPWSTR *cmd_arg_list = CommandLineToArgvW(GetCommandLineW(), &n_cmd_args);

        for (size_t i = 1; i < n_cmd_args; ++i)
        {
            LPWSTR arg = cmd_arg_list[i];
            cmdList.push_back(arg);
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
        cwdPath.append(buffer);
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
     * @return map<wstring, wstring>
     */
    map<wstring, wstring> getEnvListW()
    {
        return getVariableAllW();
    }
    /**
     * @brief 获取当前的变量环境列表
     *
     * @return map<string, string>
     */
    map<string, string> getEnvListA()
    {
        return getVariableAllA();
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
        struct chFormatVariableData
        {
            // 是否需要转义
            bool escape;
            // 是用户数据
            bool type_user;
            // 数据
            string data;
            // 名称
            string name;
            // 大写名
            string upper;
            // 数据大小
            DWORD size;
        };

        string getEnvVariable(string key);
        vector<chFormatVariableData> _lib_getGlobalVariableAll();
        string getEnvVariable(string key);
        bool getEnvVariable(string key, string &pVariable);
        string escapeEnvVariable(string path);
        map<string, string> getGlobalVariable();
        string userPath = "Environment";
        HKEY userHkey = HKEY_CURRENT_USER;

        string systmPath = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";
        HKEY systmHkey = HKEY_LOCAL_MACHINE;

        /**
         * @brief 转大写
         *
         * @param data
         * @return string
         */
        string keyUpper(string data)
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
         * @return true
         * @return false
         */
        bool get(string key, string &pEnvStr)
        {
            bool result = false;

            string newEnvStr = string();
            result = getEnvVariable(key, newEnvStr);
            pEnvStr.clear();
            pEnvStr.append(newEnvStr);

            return result;
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
            bool result = false;

            set<string> newValue = {};
            string newValueKey = string();
            string valueKey = keyUpper(key);
            for (auto key : freezeEnvKeys)
            {

                if (valueKey == keyUpper(key))
                {
                    return result;
                }
            }

            for (auto &&Values : hmc_string_util::split(Value, ';'))
            {
                newValue.insert(Values);
            }

            if (append)
            {

                string oidKey = hmc_registr_util::GetRegistrString(userHkey, userPath, key, false); // hmc_registr::getRegistrValue<string>(userHkey, userPath, key, REG_SZ);
                for (auto &&Values : hmc_string_util::split(oidKey, ';'))
                {
                    newValue.insert(Values);
                }
            }
            for (auto &&value : newValue)
                newValueKey.append(value).append(";");

            if (!newValueKey.empty() && newValueKey.back() == ';')
                newValueKey.pop_back();

            hmc_registr_util::SetRegistrString(userHkey, userPath, key, newValueKey, transMean);

            return result;
        }

        /**
         * @brief 获取指定键值(从系统)
         *
         * @param key
         * @param pEnvStr
         * @param transMean
         * @return true
         * @return false
         */
        bool getSys(string key, string &pEnvStr, bool transMean = true)
        {
            bool result = false;

            pEnvStr.clear();
            string valueKey = keyUpper(key);
            for (auto key : freezeEnvKeys)
            {

                if (valueKey == keyUpper(key))
                {
                    pEnvStr.append(getenv(key));
                    result = true;
                    return result;
                }
            }
            string UseData = hmc_registr_util::GetRegistrString(systmHkey, systmPath, key, true);
            if (transMean)
            {
                pEnvStr.append(escapeEnvVariable(UseData));
                result = pEnvStr.size() != 0;
            }
            else
            {
                pEnvStr.append(UseData);
                result = pEnvStr.size() != 0;
            }
            return result;
        }

        string getSys(string key, bool transMean = true)
        {
            std::string pEnvStr;

            if (getSys(key, pEnvStr, transMean))
            {
                return pEnvStr;
            }

            return "";
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
            bool result = false;

            pEnvStr.clear();
            string valueKey = keyUpper(key);
            for (auto key : freezeEnvKeys)
            {

                if (valueKey == keyUpper(key))
                {
                    pEnvStr.append(getenv(key));
                    result = true;
                    return result;
                }
            }
            string UseData = hmc_registr_util::GetRegistrString(userHkey, userPath, key, false);
            if (transMean)
            {
                pEnvStr.append(escapeEnvVariable(UseData));
                result = pEnvStr.size() != 0;
            }
            else
            {
                pEnvStr.append(UseData);
                result = pEnvStr.size() != 0;
            }
            return result;
        }

        string getUse(string key, bool transMean = true)
        {
            std::string pEnvStr;

            if (getUse(key, pEnvStr, transMean))
            {
                return pEnvStr;
            }

            return "";
        }

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
            bool result = false;

            set<string> newValue = {};
            string newValueKey = string();
            string valueKey = keyUpper(key);
            for (auto key : freezeEnvKeys)
            {

                if (valueKey == keyUpper(key))
                {
                    return result;
                }
            }

            for (auto &&Values : hmc_string_util::split(Value, ';'))
            {
                newValue.insert(Values);
            }

            if (append)
            {
                string oidKey = hmc_registr_util::GetRegistrString(systmHkey, systmPath, key, false);
                for (auto &&Values : hmc_string_util::split(oidKey, ';'))
                {
                    newValue.insert(Values);
                }
            }
            for (auto &&value : newValue)
                newValueKey.append(value).append(";");

            if (!newValueKey.empty() && newValueKey.back() == ';')
                newValueKey.pop_back();

            hmc_registr_util::SetRegistrString(systmHkey, systmPath, key, newValueKey, transMean);

            return result;
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
            bool result = false;

            string valueKey = keyUpper(key);

            for (auto key : freezeEnvKeys)
                if (valueKey == keyUpper(key))
                    return false;
            return hmc_registr_util::removeRegistrValue(userHkey, userPath, key);

            return result;
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
            bool result = false;

            string valueKey = keyUpper(key);

            for (auto key : freezeEnvKeys)
                if (valueKey == keyUpper(key))
                    return false;
            return hmc_registr_util::removeRegistrValue(systmHkey, systmPath, key);

            return result;
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
            bool result = false;

            string valueKey = keyUpper(key);

            for (auto key : freezeEnvKeys)
                if (valueKey == keyUpper(key))
                    return false;
            return (!hmc_registr_util::removeRegistrValue(systmHkey, systmPath, key) && !hmc_registr_util::removeRegistrValue(userHkey, userPath, key));

            return result;
        }

        /**
         * @brief 从注册表读取并更新到当前环境
         *
         * @param remove 删除 已经消失的环境 到当前进程
         * @param update 更新 新的变量到当前进程
         */
        void updateThis(bool remove = true, bool update = true)
        {

            map<string, string> globalVariable = hmc_env::systemEnv::getGlobalVariable();
            map<string, string> thisGlobalVariable = hmc_env::getEnvListA();

            // 删除已经消失的环境表
            if (remove)
                for (const auto &entry : thisGlobalVariable)
                {
                    if (globalVariable.find(entry.first) == globalVariable.end())
                    {
                        hmc_env::removeEnv(entry.first);
                    }
                }

            // 更新
            if (update)
                for (const auto &entry : globalVariable)
                {
                    hmc_env::putenv((string)entry.first, (string)entry.second, false);
                }
        }

        /**
         * @brief 判断是否存在此键
         *
         * @param key 键
         * @return true
         * @return false
         */
        bool hasSysKeyExists(string key)
        {
            bool result = false;

            string valueKey = keyUpper(key);

            for (auto key : freezeEnvKeys)
                if (valueKey == keyUpper(key))
                    return true;
            return hmc_registr_util::hasRegistrKey(systmHkey, systmPath, key);

            return result;
        }

        /**
         * @brief 判断是否存在此键
         *
         * @param key 键
         * @return true
         * @return false
         */
        bool hasUseKeyExists(string key)
        {
            bool result = false;

            string valueKey = keyUpper(key);

            for (auto key : freezeEnvKeys)
                if (valueKey == keyUpper(key))
                    return true;

            return hmc_registr_util::hasRegistrKey(userHkey, userPath, key);
            return result;
        }

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
        bool hasKeyExists(string key)
        {
            return hasUseKeyExists(key) || hasSysKeyExists(key);
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
            bool result = false;
            hmc_registr_util::chValueStat userValueStat = hmc_registr_util::getValueStat(userHkey, userPath, key);
            if (userValueStat.exists)
            {
                result = userValueStat.type == REG_EXPAND_SZ;
                return result;
            }

            hmc_registr_util::chValueStat sysValueStat = hmc_registr_util::getValueStat(systmHkey, systmPath, key);
            if (sysValueStat.exists)
            {
                result = sysValueStat.type == REG_EXPAND_SZ;
                return result;
            }
            return result;
        }

        /**
         * @brief 获取系统 所有变量名 但是不查询值
         *
         */
        vector<string> keySysList()
        {
            vector<string> result;
            {
                for (auto key : freezeEnvKeys)
                    result.push_back(key);

                for (auto key : hmc_registr_util::getRegistrKeys(systmHkey, systmPath).key)
                    result.push_back(key);
            };
            return result;
        }

        /**
         * @brief 获取用户 所有变量名 但是不查询值
         *
         */
        vector<string> keyUseList()
        {
            vector<string> result;
            {
                for (auto key : freezeEnvKeys)
                    result.push_back(key);

                for (auto key : hmc_registr_util::getRegistrKeys(userHkey, userPath).key)
                    result.push_back(key);
            };

            return result;
        }

        /**
         * @brief 从注册表读取系统变量
         *
         * @param key
         * @param pVariable
         * @return true
         * @return false
         */
        bool getEnvVariable(string key, string &pVariable)
        {
            bool result = false;
            {
                pVariable.clear();

                for (auto &&freezeEnv : freezeEnvKeys)
                {
                    if (keyDiff(freezeEnv, key))
                    {
                        string data = string();
                        bool isenv = getenv(key, data);
                        pVariable.append(data);
                        return isenv;
                    }
                }

                string userPath = "Environment";
                HKEY userHkey = HKEY_CURRENT_USER;

                string systmPath = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";
                HKEY systmHkey = HKEY_LOCAL_MACHINE;

                hmc_registr_util::chValueStat valueStat = hmc_registr_util::getValueStat(userHkey, userPath, key);

                if (valueStat.exists)
                {

                    pVariable.append(hmc_registr_util::GetRegistrString(userHkey, userPath, key, valueStat.type));
                    if (pVariable.size() != 0)
                        return true;
                }

                hmc_registr_util::chValueStat valueStat_1 = hmc_registr_util::getValueStat(systmHkey, systmPath, key);

                if (valueStat_1.exists)
                {

                    pVariable.append(hmc_registr_util::GetRegistrString(systmHkey, systmPath, key, valueStat_1.type));
                    if (pVariable.size() != 0)
                        return true;
                }
            };

            return result;
        }

        /**
         * @brief 从注册表读取系统变量
         *
         * @param key
         * @return string
         */
        string getEnvVariable(string key)
        {
            string pVariable = string();
            getEnvVariable(key, pVariable);
            return pVariable;
        }

        /**
         * @brief 获取文本并带入环境
         *
         * @param path
         * @return string
         */
        string escapeEnvVariable(string input)
        {
            string result = string();

            result.append(input);

            std::string pattern = "%";

            size_t startPos = 0;

            while ((startPos = input.find(pattern, startPos)) != std::string::npos)
            {
                size_t endPos = input.find(pattern, startPos + pattern.length());
                if (endPos != std::string::npos)
                {
                    string subStr = input.substr(startPos, endPos - startPos + pattern.length());
                    string subStrKey = keyUpper(input.substr(startPos + 1, endPos - startPos + pattern.length() - 2));
                    string value = getEnvVariable(subStrKey);
                    if (value.size() != 0)
                    {
                        size_t startReplacePos = result.find(subStr);
                        while (startReplacePos != std::string::npos)
                        {
                            result.replace(startReplacePos, subStr.size(), value);
                            startReplacePos = result.find(subStr, startReplacePos + value.length());
                        }
                    }
                    startPos = endPos + pattern.length();
                }
                else
                {
                    break;
                }
            }
            return result;
        }

        /**
         * @brief 在全局获取系统环境变量
         *
         * @return map<string, string>
         */
        vector<chFormatVariableData> getGlobalVariableAll(bool AllVariable = false)
        {
            vector<chFormatVariableData> AllVariableDataList;
            vector<chFormatVariableData> VariableDataList;
            string path_var_data = "";
            set<string> hmcDataList;

            // 这些值是固定的 不允许变动
            for (auto key : freezeEnvKeys)
            {
                chFormatVariableData variableData;
                getenv(key, variableData.data);
                variableData.escape = false;
                variableData.type_user = false;
                variableData.upper = keyUpper(key);
                variableData.name = key;
                AllVariableDataList.push_back(variableData);
            }
            // 获取用户变量

            auto key_list = hmc_registr_util::getRegistrKeys(userHkey, userPath);

            for (auto key : key_list.key)
            {
                if (key.empty())
                    continue;
                hmc_registr_util::chValueStat valueStat = hmc_registr_util::getValueStat(userHkey, userPath, key);

                if (!valueStat.exists)
                    continue;

                chFormatVariableData variableData;
                variableData.size = valueStat.size;
                variableData.type_user = true;
                variableData.upper = keyUpper(key);
                variableData.name = key;
                variableData.data = hmc_registr_util::GetRegistrString(userHkey, userPath, key, valueStat.type);
                variableData.escape = valueStat.type == REG_EXPAND_SZ;
                if (!variableData.data.size())
                {
                    variableData.data = hmc_registr_util::GetRegistrString(userHkey, userPath, key, valueStat.type);
                }

                // 处理path变量
                if (variableData.upper != string("PATH") || AllVariable)
                {
                    AllVariableDataList.push_back(variableData);
                }
                else
                {
                    path_var_data.append(variableData.data);
                }
            }
            key_list.Folder.clear();
            key_list.key.clear();

            // 获取系统变量

            key_list = hmc_registr_util::getRegistrKeys(systmHkey, systmPath);

            for (auto key : key_list.key)
            {
                if (key.empty())
                    continue;
                hmc_registr_util::chValueStat valueStat = hmc_registr_util::getValueStat(systmHkey, systmPath, key);

                if (!valueStat.exists)
                    continue;

                chFormatVariableData variableData;
                variableData.type_user = true;
                variableData.size = valueStat.size;
                variableData.upper = keyUpper(key);
                variableData.name = key;
                variableData.data = hmc_registr_util::GetRegistrString(systmHkey, systmPath, key, valueStat.type);
                if (!variableData.data.size())
                {
                    variableData.data = hmc_registr_util::GetRegistrString(systmHkey, systmPath, key, valueStat.type);
                }
                variableData.escape = valueStat.type == REG_EXPAND_SZ;

                // 处理path变量
                if (variableData.upper != string("PATH") || AllVariable)
                {
                    AllVariableDataList.push_back(variableData);
                }
                // 是path
                else
                {
                    if (!path_var_data.empty())
                    {

                        path_var_data.append(";");
                    }
                    path_var_data.append(variableData.data);
                }
            }

            key_list.Folder.clear();
            key_list.key.clear();
            // 按照结构优先级添加到返回结果

            // 按照顺序永远是用户数据优先 所以不用刻意排序
            for (auto &&VariableData : AllVariableDataList)
            {
                if (VariableData.data.size() < VariableData.size - 3)
                {
                    hmc_env::getenv(VariableData.name, VariableData.data);
                }
            }

            for (auto &&VariableData : AllVariableDataList)
            {

                if (hmcDataList.find(VariableData.name) == hmcDataList.end())
                {
                    hmcDataList.insert(VariableData.upper);
                    VariableDataList.push_back(VariableData);
                }
            }

            chFormatVariableData variableData;
            variableData.type_user = true;
            variableData.size = path_var_data.size();
            variableData.upper = keyUpper("PATH");
            variableData.name = "Path";
            variableData.data = path_var_data;
            VariableDataList.push_back(variableData);

            // 翻译变量

            for (auto &&VariableData : (AllVariable ? AllVariableDataList : VariableDataList))
            {

                // 等待解析的变量
                std::string pattern = "%";
                size_t startPos = 0;

                // 查找 %xxx%
                while ((startPos = VariableData.data.find(pattern, startPos)) != std::string::npos)
                {
                    size_t endPos = VariableData.data.find(pattern, startPos + pattern.length());
                    if (endPos != std::string::npos)
                    {
                        string subStr = VariableData.data.substr(startPos, endPos - startPos + pattern.length());
                        string subStrKey = keyUpper(VariableData.data.substr(startPos + 1, endPos - startPos + pattern.length() - 2));

                        // 查找并替换

                        // 查找对照表

                        for (auto &&lookVariableData : VariableDataList)
                        {
                            if (lookVariableData.upper == subStrKey)
                            {
                                size_t startsubStrPos = 0;
                                while ((startsubStrPos = VariableData.data.find(subStr, startsubStrPos)) != string::npos)
                                {
                                    VariableData.data.replace(startsubStrPos, subStr.length(), lookVariableData.data);
                                    startsubStrPos += lookVariableData.data.length();
                                }
                            }
                        }

                        // 下一个
                        startPos = endPos + pattern.length();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            return (AllVariable ? AllVariableDataList : VariableDataList);
        }

        /**
         * @brief 从注册表获取环境变量
         *
         */
        map<string, string> getGlobalVariable()
        {
            map<string, string> result;

            vector<chFormatVariableData> globalVariableList = getGlobalVariableAll();
            for (auto &&globalVariable : globalVariableList)
            {
                if (globalVariable.name.size() > 0 && globalVariable.data.size() > 0)
                {
                    result.insert(std::make_pair(globalVariable.name, globalVariable.data));
                }
            }
            return result;
        }

    }

}

#endif
