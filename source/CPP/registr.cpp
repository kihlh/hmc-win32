#include "./Mian.hpp";

/**
 * @brief 注册表添加内容
 *
 * @param rootKey  存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @param key 键值
 * @param value 内容
 * @return true
 * @return false
 */
bool SetRegistrValue(HKEY rootKey, string Path, string &key, string &value)
{
    HKEY hkey = nullptr;
    EnableShutDownPriv();
    LSTATUS Result = ::RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_WRITE, &hkey);
    if (Result != ERROR_SUCCESS)
    {
        Result = ::RegCreateKeyA(rootKey, Path.c_str(), &hkey);
    }
    if (Result != ERROR_SUCCESS)
    {
        return false;
    }

    shared_ptr<void> close_key(nullptr, [&](void *)
                               {
        if (hkey != nullptr) {
            ::RegCloseKey(hkey);
            hkey = nullptr;
        } });
    Result = ::RegSetValueExA(hkey, key.c_str(), 0, REG_SZ, (BYTE *)value.c_str(), value.length());
    if (Result != ERROR_SUCCESS)
    {
        return false;
    }
    return true;
}

/**
 * @brief 注册表添加内容
 *
 * @param rootKey  存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @param key 键值
 * @param value 内容
 * @return true
 * @return false
 */
bool SetRegistrDword(HKEY rootKey, string Path, string &key, DWORD value)
{
    HKEY hkey = nullptr;
    EnableShutDownPriv();
    LSTATUS Result = ::RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_WRITE, &hkey);
    if (Result != ERROR_SUCCESS)
    {
        Result = ::RegCreateKeyA(rootKey, Path.c_str(), &hkey);
    }
    if (Result != ERROR_SUCCESS)
    {
        return false;
    }

    shared_ptr<void> close_key(nullptr, [&](void *)
                               {
        if (hkey != nullptr) {
            ::RegCloseKey(hkey);
            hkey = nullptr;
        } });

    Result = ::RegSetValueExA(hkey, key.c_str(), 0, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
    if (Result != ERROR_SUCCESS)
    {
        return false;
    }
    return true;
}

/**
 * @brief 注册表添加内容
 *
 * @param rootKey  存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @param key 键值
 * @param value 内容
 * @return true
 * @return false
 */
bool SetRegistrQword(HKEY rootKey, string Path, string &key, int64_t value)
{
    HKEY hkey = nullptr;
    EnableShutDownPriv();
    LSTATUS Result = ::RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_WRITE, &hkey);
    if (Result != ERROR_SUCCESS)
    {
        Result = ::RegCreateKeyA(rootKey, Path.c_str(), &hkey);
    }
    if (Result != ERROR_SUCCESS)
    {
        return false;
    }

    shared_ptr<void> close_key(nullptr, [&](void *)
                               {
        if (hkey != nullptr) {
            ::RegCloseKey(hkey);
            hkey = nullptr;
        } });
    Result = ::RegSetValueExA(hkey, key.c_str(), 0, REG_QWORD, (LPBYTE)&value, sizeof(int64_t));
    if (Result != ERROR_SUCCESS)
    {
        return false;
    }
    return true;
}

/**
 * @brief 获取注册表里的内容 文本
 *
 * @param rootKey   存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @param key
 * @return string 键值
 */
string GetRegistrValue(HKEY rootKey, string Path, string &key)
{
    EnableShutDownPriv();
    HKEY hkey = nullptr;
    LSTATUS Result = ::RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_READ, &hkey);
    if (Result != ERROR_SUCCESS)
    {
        return "";
    }
    shared_ptr<void> close_key(nullptr, [&](void *)
                               {
        if (hkey != nullptr) {
            ::RegCloseKey(hkey);
            hkey = nullptr;
        } });
    DWORD type = REG_SZ;
    DWORD size = 0;
    Result = ::RegQueryValueExA(hkey, key.c_str(), 0, &type, nullptr, &size);
    if (Result != ERROR_SUCCESS || size <= 0)
    {
        return "";
    }
    vector<BYTE> value_data(size);
    Result = ::RegQueryValueExA(hkey, key.c_str(), 0, &type, value_data.data(), &size);
    if (Result != ERROR_SUCCESS)
    {
        return "";
    }

    return string(value_data.begin(), value_data.end());
}

/**
 * @brief 获取注册表里的内容 32位数字
 *
 * @param rootKey   存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @param key
 * @return string 键值
 */
DWORD GetRegistrDword(HKEY rootKey, string Path, string &key)
{
    EnableShutDownPriv();
    HKEY hkey = nullptr;
    LSTATUS Result = ::RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_READ, &hkey);
    if (Result != ERROR_SUCCESS)
    {
        return 0;
    }
    shared_ptr<void> close_key(nullptr, [&](void *)
                               {
        if (hkey != nullptr) {
            ::RegCloseKey(hkey);
            hkey = nullptr;
        } });
    DWORD type = REG_DWORD;
    DWORD size = 255;
    Result = ::RegQueryValueExA(hkey, key.c_str(), 0, &type, nullptr, &size);
    if (Result != ERROR_SUCCESS || size <= 0)
    {
        return 0;
    }
    DWORD value_data;
    Result = ::RegQueryValueExA(hkey, key.c_str(), 0, &type, (LPBYTE)&value_data, &size);
    if (Result != ERROR_SUCCESS)
    {
        return 0;
    }

    return value_data;
}

/**
 * @brief 获取注册表里的内容 64位数字
 *
 * @param rootKey   存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @param key
 * @return string 键值
 */
int64_t GetRegistrQword(HKEY rootKey, string Path, string &key)
{
    EnableShutDownPriv();
    HKEY hkey = nullptr;
    LSTATUS Result = ::RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_READ, &hkey);
    if (Result != ERROR_SUCCESS)
    {
        return 0;
    }
    shared_ptr<void> close_key(nullptr, [&](void *)
                               {
        if (hkey != nullptr) {
            ::RegCloseKey(hkey);
            hkey = nullptr;
        } });
    DWORD type = REG_QWORD;
    DWORD size = 255;
    Result = ::RegQueryValueExA(hkey, key.c_str(), 0, &type, nullptr, &size);
    if (Result != ERROR_SUCCESS || size <= 0)
    {
        return 0;
    }
    DWORD value_data;
    Result = ::RegQueryValueExA(hkey, key.c_str(), 0, &type, (LPBYTE)&value_data, &size);
    if (Result != ERROR_SUCCESS)
    {
        return 0;
    }

    return (int64_t)value_data;
}

/**
 * @brief 获取注册表里的内容 文本
 *
 * @param rootKey   存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @param key
 * @return BYTE 键值
 */
void GetRegistrBuffValue(HKEY rootKey, string Path, string &key, BYTE *Result)
{
    EnableShutDownPriv();
    HKEY hKey = nullptr;
    long openRegResult;
    long readRegResult;
    DWORD dwType = REG_BINARY;
    REGSAM mode = KEY_READ;
    DWORD length = 256;
    openRegResult = RegOpenKeyExA(rootKey, Path.c_str(), 0, mode, &hKey);
    if (ERROR_SUCCESS == openRegResult)
    {
        readRegResult = RegQueryValueExA(hKey, key.c_str(), 0, &dwType, Result, &length);
        if (ERROR_SUCCESS == readRegResult)
        {
            return;
        }
        else
        {
            return;
        }
    }
    RegCloseKey(hKey);
}
/**
 * @brief 判断注册表中内容是否有该键值存在
 *
 * @param rootKey   存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @param key 键值
 * @return true
 * @return false
 */
bool HasRegistrKey(HKEY rootKey, string Path, string &key)
{
    EnableShutDownPriv();
    bool HasResult = false;
    DWORD dwType = REG_SZ;
    HKEY hKey;
    LSTATUS Result = RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_READ, &hKey);
    if (Result != ERROR_SUCCESS)
    {
        return false;
    }
    Result = RegQueryValueExA(hKey, key.c_str(), NULL, &dwType, NULL, NULL);
    RegCloseKey(hKey);
    if (Result == ERROR_SUCCESS || Result == ERROR_MORE_DATA)
    {
        HasResult = true;
    }
    return HasResult;
}

/**
 * @brief 注册表创建一个路径
 *
 * @param rootKey   存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @return true
 * @return false
 */
bool CreatePathRegistr(HKEY rootKey, string Path)
{
    EnableShutDownPriv();
    HKEY hKey = NULL;
    DWORD dwOptions = REG_OPTION_NON_VOLATILE;
    DWORD dwDisposition;
    long resulte = RegCreateKeyExA(rootKey, Path.c_str(), 0, NULL,
                                   dwOptions, KEY_WRITE, NULL, &hKey, &dwDisposition);
    if (resulte != ERROR_SUCCESS)
    {
        return false;
    }
    else
    {
        switch (dwDisposition)
        {
        case REG_OPENED_EXISTING_KEY:
            return true;
        case REG_CREATED_NEW_KEY:
            return true;
        }
    }
}

/**
 * @brief 删除注册表中的键值
 *
 * @param rootKey   存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @param key 键值
 * @return true
 * @return false
 */
bool RemoveRegistrValue(HKEY rootKey, string Path, string &key)
{
    EnableShutDownPriv();
    if (!HasRegistrKey(rootKey, Path, key))
    {
        return false;
    }
    // 定义有关的hKEY,在查询结束时要关闭
    HKEY hkey = nullptr;
    if (ERROR_SUCCESS == ::RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_ALL_ACCESS, &hkey))
    {
        ::RegDeleteValueA(hkey, key.c_str());
    }
    ::RegCloseKey(hkey);
    return HasRegistrKey(rootKey, Path, key) == false;
}

bool RemoveRegistrKey(HKEY rootKey, string Path, string &key)
{
    EnableShutDownPriv();
    if (!HasRegistrKey(rootKey, Path, key))
    {
        return false;
    }
    // 定义有关的hKEY,在查询结束时要关闭
    HKEY hkey = nullptr;
    if (ERROR_SUCCESS == ::RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_ALL_ACCESS, &hkey))
    {
        ::RegDeleteKeyA(hkey, key.c_str());
    }
    ::RegCloseKey(hkey);
    return HasRegistrKey(rootKey, Path, key) == false;
}

bool RemoveRegistrKeyWalk(HKEY rootKey, string Path, string &key)
{
    EnableShutDownPriv();
    HKEY hkey = nullptr;
    if (ERROR_SUCCESS == ::RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_ALL_ACCESS, &hkey))
    {
        EnableShutDownPriv();
        RegDeleteTreeA(hkey, key.c_str());
    }
    ::RegCloseKey(hkey);
    return HasRegistrKey(rootKey, Path, key) == false;
}

vector<string> EnumRegistrKeyQuery(HKEY hKey)
{
    EnableShutDownPriv();
    vector<string> QueryKeyList;
    TCHAR achKey[MAX_KEY_LENGTH];        // 子键名称的缓冲区
    DWORD cbName;                        // 名称字符串的大小
    TCHAR achClass[MAX_PATH] = TEXT(""); // 类名缓冲区
    DWORD cchClassName = MAX_PATH;       // 类字符串的大小
    DWORD cSubKeys = 0;                  // 子键数
    DWORD cbMaxSubKey;                   // 最长子键大小
    DWORD cchMaxClass;                   // 最长类字符串
    DWORD cValues;                       // 键值的个数
    DWORD cchMaxValue;                   // 最长值名
    DWORD cbMaxValueData;                // 最长值数据
    DWORD cbSecurityDescriptor;          // 安全描述符的大小
    FILETIME ftLastWriteTime;            // 最后写入时间

    DWORD index, retCode;

    TCHAR achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

    // 获取类名和值计数。
    retCode = RegQueryInfoKeyW(
        hKey, (LPWSTR)achClass, &cchClassName, NULL, &cSubKeys, &cbMaxSubKey, &cchMaxClass, &cValues, &cchMaxValue, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime);
    // 枚举子键，直到RegEnumKeyEx失败。

    if (cSubKeys)
    {
        for (index = 0; index < cSubKeys; index++)
        {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyExW(hKey, index,
                                    (LPWSTR)achKey,
                                    &cbName,
                                    NULL,
                                    NULL,
                                    NULL,
                                    &ftLastWriteTime);
            if (retCode == ERROR_SUCCESS)
            {
                QueryKeyList.push_back(_W2A_((wchar_t *)achKey));
            }
        }
    }

    // 枚举键值。

    if (cValues)
    {
        for (index = 0, retCode = ERROR_SUCCESS; index < cValues; index++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = RegEnumValue(hKey, index,
                                   achValue,
                                   &cchValue,
                                   NULL,
                                   NULL,
                                   NULL,
                                   NULL);

            if (retCode == ERROR_SUCCESS)
            {
                QueryKeyList.push_back(_W2A_((wchar_t *)achKey));
            }
        }
    }
    return QueryKeyList;
}
/**
 * @brief 枚举注册表键值
 *
 * @param rootKey
 * @param Path
 * @return vector<string>
 */
vector<string> EnumRegistrKey(HKEY rootKey, string Path)
{
    EnableShutDownPriv();
    HKEY hTestKey;
    vector<string> defaultContent;

    if (RegOpenKeyExW(rootKey, _A2W_(Path.c_str()).c_str(),
                      0,
                      KEY_READ,
                      &hTestKey) == ERROR_SUCCESS)
    {
        return EnumRegistrKeyQuery(hTestKey);
    }

    RegCloseKey(hTestKey);
    return defaultContent;
}

/**
 * @brief 判断注册表中内容是否有该键值存在
 *
 * @param rootKey   存储位置
 * - HKEY_USERS 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_LOCAL_MACHINE  包含描述计算机及其配置的条目。其中包括关于处理器、系统主板、内存和已安装的软件和硬件的信息
 * - HKEY_CURRENT_USER 管理系统当前的用户信息
 * - HKEY_CURRENT_CONFIG 用作默认用户首选设置，也作为单个用户的首选设置
 * - HKEY_CLASSES_ROOT 是与文档类型和 OLE\COM 相关的信息的支持键。这个键是
 * @param Path 路径
 * @param key 键值
 * @return int
 */
int GetRegistrValueSize(HKEY rootKey, string Path, string &key)
{
    EnableShutDownPriv();
    HKEY hkey = nullptr;
    LSTATUS Result = ::RegOpenKeyExA(rootKey, Path.c_str(), 0, KEY_READ, &hkey);
    if (Result != ERROR_SUCCESS)
    {
        return 0;
    }
    shared_ptr<void> close_key(nullptr, [&](void *)
                               {
        if (hkey != nullptr) {
            ::RegCloseKey(hkey);
            hkey = nullptr;
        } });
    DWORD type = REG_SZ;
    DWORD size = 0;
    Result = ::RegQueryValueExA(hkey, key.c_str(), 0, &type, nullptr, &size);
    if (Result != ERROR_SUCCESS || size <= 0)
    {
        return 0;
    }
    vector<BYTE> value_data(size);
    Result = ::RegQueryValueExA(hkey, key.c_str(), 0, &type, value_data.data(), &size);
    if (Result != ERROR_SUCCESS)
    {
        return 0;
    }
    return (int)size;
}
/**
 * vscode-windows-registry
 * @URL: https://github.com/microsoft/vscode-windows-registry/tree/5206b22f1c62cfe820437dcfa972cc8a15c22cd2
 */
HKEY GetHive(string hkey)
{
    if (hkey == "HKEY_CURRENT_USER")
    {
        return HKEY_CURRENT_USER;
    }

    if (hkey == "HKEY_LOCAL_MACHINE")
    {
        return HKEY_LOCAL_MACHINE;
    }

    if (hkey == "HKEY_CLASSES_ROOT")
    {
        return HKEY_CLASSES_ROOT;
    }

    if (hkey == "HKEY_USERS")
    {
        return HKEY_USERS;
    }

    if (hkey == "HKEY_CURRENT_CONFIG")
    {
        return HKEY_CURRENT_CONFIG;
    }

    return NULL;
}

napi_value getStringRegKey(napi_env env, napi_callback_info info)
{
    napi_value argv[3];
    size_t argc = 3;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 3)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);

    napi_value napi_result;
    napi_create_string_utf8(env, _A2U8_(GetRegistrValue(hive, Path, Key).c_str()).c_str(), NAPI_AUTO_LENGTH, &napi_result);

    return napi_result;
}

napi_value removeStringRegKey(napi_env env, napi_callback_info info)
{
    napi_value argv[3];
    size_t argc = 3;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 3)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);

    return _create_bool_Boolean(env, RemoveRegistrKey(hive, Path, Key));
}

napi_value removeStringRegValue(napi_env env, napi_callback_info info)
{
    napi_value argv[3];
    size_t argc = 3;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 3)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);

    return _create_bool_Boolean(env, RemoveRegistrValue(hive, Path, Key));
}

napi_value removeStringRegKeyWalk(napi_env env, napi_callback_info info)
{
    napi_value argv[3];
    size_t argc = 3;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 3)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);

    return _create_bool_Boolean(env, RemoveRegistrKeyWalk(hive, Path, Key));
}

napi_value hasRegistrKey(napi_env env, napi_callback_info info)
{
    napi_value argv[3];
    size_t argc = 3;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 3)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);

    return _create_bool_Boolean(env, HasRegistrKey(hive, Path, Key));
}

napi_value setRegistrKey(napi_env env, napi_callback_info info)
{
    napi_value argv[4];
    size_t argc = 4;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 4)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 4; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);
    string value = call_String_NAPI_WINAPI_A(env, argv[3]);
    return _create_bool_Boolean(env, SetRegistrValue(hive, Path, Key, value));
}

napi_value createPathRegistr(napi_env env, napi_callback_info info)
{
    napi_value argv[2];
    size_t argc = 2;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 2)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 2; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    return _create_bool_Boolean(env, CreatePathRegistr(hive, Path));
}

napi_value enumRegistrKey(napi_env env, napi_callback_info info)
{
    napi_value argv[2];
    size_t argc = 2;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 2)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }
    // 检索3个参数
    for (int i = 0; i < 2; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    return _create_String_Array(env, EnumRegistrKey(hive, Path));
}

napi_value getRegistrValueSize(napi_env env, napi_callback_info info)
{
    napi_value argv[3];
    size_t argc = 3;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 3)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);
    return _create_int32_Number(env, GetRegistrValueSize(hive, Path, Key));
}

napi_value getRegistrBuffValue(napi_env env, napi_callback_info info)
{
    napi_value argv[3];
    size_t argc = 3;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 3)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);

    HKEY hKey = nullptr;
    long openRegResult;
    long readRegResult;
    DWORD dwType = REG_BINARY;
    REGSAM mode = KEY_READ;
    DWORD length = 256;
    BYTE Result[256] = {0};
    void *yourPointer;
    if (!HasRegistrKey(hive, Path, Key))
    {
        return NULL;
    }

    openRegResult = RegOpenKeyExA(hive, Path.c_str(), 0, mode, &hKey);
    if (ERROR_SUCCESS == openRegResult)
    {
        readRegResult = RegQueryValueExA(hKey, Key.c_str(), 0, &dwType, Result, &length);
        if (ERROR_SUCCESS == readRegResult)
        {
            yourPointer = Result;
            return _create_buff_Buffer(env, &yourPointer, length);
        }
        else
        {
            yourPointer = Result;
            return _create_buff_Buffer(env, &yourPointer, length);
        }
    }
    RegCloseKey(hKey);
}

napi_value getRegistrDword(napi_env env, napi_callback_info info)
{

    napi_value argv[3];
    size_t argc = 3;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 3)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);

    napi_value napi_result;
    napi_create_int64(env, GetRegistrDword(hive, Path, Key), &napi_result);
    return napi_result;
}
napi_value setRegistrDword(napi_env env, napi_callback_info info)
{
    napi_value argv[4];
    size_t argc = 4;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 4)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }
    napi_valuetype value_type;
    napi_typeof(env, argv[3], &value_type);
    if (value_type != napi_number)
    {
        napi_throw_error(env, "EINVAL", "Missing parameters typeof is not a bigint");
        return nullptr;
    }
    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);
    int32_t value;
    napi_get_value_int32(env, argv[3], &value);
    return _create_bool_Boolean(env, SetRegistrDword(hive, Path, Key, (DWORD)value));
}

napi_value getRegistrQword(napi_env env, napi_callback_info info)
{

    napi_value argv[3];
    size_t argc = 3;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 3)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }

    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);

    napi_value napi_result;
    napi_create_bigint_int64(env, GetRegistrQword(hive, Path, Key), &napi_result);
    return napi_result;
}
napi_value setRegistrQword(napi_env env, napi_callback_info info)
{
    napi_value argv[4];
    size_t argc = 4;
    napi_status status;
    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // 检查我们是否有3个参数 - Hive, Path, Name
    if (argc < 4)
    {
        napi_throw_error(env, "EINVAL", "Wrong number of arguments");
        return nullptr;
    }

    // 检索3个参数
    for (int i = 0; i < 3; i++)
    {
        napi_valuetype value_type;
        napi_typeof(env, argv[i], &value_type);
        if (value_type != napi_string)
        {
            napi_throw_error(env, "EINVAL", "Missing parameters");
            return nullptr;
        };
    }
    napi_valuetype value_type;
    napi_typeof(env, argv[3], &value_type);
    if (value_type != napi_bigint)
    {
        napi_throw_error(env, "EINVAL", "Missing parameters typeof is not a bigint");
        return nullptr;
    }
    string RootKey = call_String_NAPI_WINAPI_A(env, argv[0]);
    HKEY hive = GetHive(RootKey);
    string Path = call_String_NAPI_WINAPI_A(env, argv[1]);
    string Key = call_String_NAPI_WINAPI_A(env, argv[2]);
    int64_t value;
    bool lossless;
    // napi_get_value_int64(env, argv[3], &value);
    napi_get_value_bigint_int64(env, argv[3], &value, &lossless);
    return _create_bool_Boolean(env, SetRegistrQword(hive, Path, Key, (int64_t)value));
}
