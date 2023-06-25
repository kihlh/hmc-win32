#include <string>
#include <vector>
#include <windows.h>
#include <filesystem>
#include <shlwapi.h>
#include <processenv.h>
#include <map>
#include <regex>

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
        wstring pwText = wstring(env);

        if (pwText.empty() && pwText.find(L'=') == 0)
            continue;

        int pszATextLen = WideCharToMultiByte(CP_ACP, 0, pwText.c_str(), -1, NULL, 0, NULL, NULL);
        char *pAChar = new (nothrow) char[pszATextLen];

        ZeroMemory(pAChar, pszATextLen + 1);
        WideCharToMultiByte(CP_ACP, 0, pwText.c_str(), -1, pAChar, pszATextLen, NULL, NULL);
        string strEnv = string(pAChar);
        delete[] pAChar;
        pAChar = NULL;
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
    string getcmd()
    {
        LPSTR commandStr = ::GetCommandLineA();
        return string(commandStr);
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
        //  DWORD processId = ::get();
        // return processId;
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
    map<string, string> getEnv()
    {
        return getVariableAll();
    }

}