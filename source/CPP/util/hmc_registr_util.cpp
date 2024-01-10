#include "./hmc_registr_util.hpp"

bool hmc_registr_util::eq_target_type(DWORD theType, DWORD targetType)
{
	switch (theType)
	{
		// 文本
	case REG_LINK:
	case REG_SZ:
	case REG_MULTI_SZ:
	case REG_EXPAND_SZ:
	{
		return targetType == REG_NONE || targetType == REG_LINK || targetType == REG_SZ || targetType == REG_MULTI_SZ || targetType == REG_EXPAND_SZ;
	}
	case REG_DWORD_BIG_ENDIAN:
	case REG_QWORD:
	case REG_DWORD:
	{
		return targetType == REG_NONE || targetType == REG_DWORD_BIG_ENDIAN || targetType == REG_QWORD || targetType == REG_DWORD;
	}
	case REG_BINARY:
	case REG_RESOURCE_LIST:
	case REG_RESOURCE_REQUIREMENTS_LIST:
	{
		return targetType == REG_NONE || targetType == REG_BINARY || targetType == REG_RESOURCE_LIST || targetType == REG_RESOURCE_REQUIREMENTS_LIST;
	}

	default:
		return false;
	}
}

std::string hmc_registr_util::chType::type_nameA()
{
	return hmc_registr_util::type_nameA(type);
}

std::wstring hmc_registr_util::chType::type_nameW()
{
	return hmc_registr_util::type_nameW(type);
}

bool hmc_registr_util::chType::type_name(std::string &output)
{
	output.clear();
	output.append(type_nameA());
	return !output.empty();
}

bool hmc_registr_util::chType::type_name(std::wstring &output)
{
	output.clear();
	output.append(type_nameW());
	return !output.empty();
}

bool hmc_registr_util::chType::isInt64()
{
	return type == REG_QWORD;
}

bool hmc_registr_util::chType::isString()
{
	return type == REG_SZ || type == REG_MULTI_SZ || type == REG_EXPAND_SZ;
}

bool hmc_registr_util::chType::isNumber()
{
	return type == REG_QWORD || type == REG_DWORD || type == REG_DWORD_BIG_ENDIAN || type == REG_DWORD_LITTLE_ENDIAN || type == REG_QWORD_LITTLE_ENDIAN;
}

bool hmc_registr_util::chType::isInt32()
{
	return type == REG_DWORD || type == REG_DWORD_BIG_ENDIAN || type == REG_DWORD_LITTLE_ENDIAN;
}

bool hmc_registr_util::chType::isBuffer()
{
	return type == REG_BINARY || REG_NONE;
}

bool hmc_registr_util::chType::diffType(DWORD type2)
{
	return type == type2;
}

std::uint32_t hmc_registr_util::chValue::getInt32()
{
	std::uint32_t res = 0ull;
	if (value.empty())
	{
		return res;
	}

	return bytesToInt32(value);

	return res;
}

std::uint16_t hmc_registr_util::chValue::getInt16()
{
	std::uint16_t res = 0ull;
	if (value.empty())
	{
		return res;
	}

	return bytesToInt16(value);

	return res;
}

std::uint64_t hmc_registr_util::chValue::getInt64()
{
	std::uint64_t res = 0ull;
	if (value.empty())
	{
		return res;
	}

	return bytesToInt64(value);
}

std::string hmc_registr_util::type_nameA(DWORD theType)
{
	switch (theType)
	{
	case REG_NONE:
		return "REG_NONE";
	case REG_SZ:
		return "REG_SZ";
	case REG_EXPAND_SZ:
		return "REG_EXPAND_SZ";
	case REG_BINARY:
		return "REG_BINARY";
	case REG_DWORD:
		return "REG_DWORD";
	case REG_QWORD:
		return "REG_QWORD";
	case REG_LINK:
		return "REG_LINK";
	case REG_MULTI_SZ:
		return "REG_MULTI_SZ";
	case REG_RESOURCE_LIST:
		return "REG_RESOURCE_LIST";
	case REG_FULL_RESOURCE_DESCRIPTOR:
		return "REG_FULL_RESOURCE_DESCRIPTOR";
	case REG_RESOURCE_REQUIREMENTS_LIST:
		return "REG_RESOURCE_REQUIREMENTS_LIST";
	}

	return "";
}

std::wstring hmc_registr_util::type_nameW(DWORD theType)
{
	switch (theType)
	{
	case REG_NONE:
		return L"REG_NONE";
	case REG_SZ:
		return L"REG_SZ";
	case REG_EXPAND_SZ:
		return L"REG_EXPAND_SZ";
	case REG_BINARY:
		return L"REG_BINARY";
	case REG_DWORD:
		return L"REG_DWORD";
	case REG_QWORD:
		return L"REG_QWORD";
	case REG_LINK:
		return L"REG_LINK";
	case REG_MULTI_SZ:
		return L"REG_MULTI_SZ";
	case REG_RESOURCE_LIST:
		return L"REG_RESOURCE_LIST";
	case REG_FULL_RESOURCE_DESCRIPTOR:
		return L"REG_FULL_RESOURCE_DESCRIPTOR";
	case REG_RESOURCE_REQUIREMENTS_LIST:
		return L"REG_RESOURCE_REQUIREMENTS_LIST";
	}

	return L"";
}

bool hmc_registr_util::hasRegistrKey(HKEY hKey, std::string FolderPath, std::string key)
{
	return getValueStat(hKey, FolderPath, key).exists;
}

bool hmc_registr_util::hasRegistrKey(HKEY hKey, std::wstring FolderPath, std::wstring key)
{
	return getValueStat(hKey, FolderPath, key).exists;
}

bool hmc_registr_util::hasRegistrValue(HKEY hKey, std::string FolderPath, std::string key)
{
	auto valueStat = getValueStat(hKey, FolderPath, key);
	return valueStat.exists && valueStat.size > 0;
}

bool hmc_registr_util::hasRegistrValue(HKEY hKey, std::wstring FolderPath, std::wstring key)
{
	auto valueStat = getValueStat(hKey, FolderPath, key);
	return valueStat.exists && valueStat.size > 0;
}

bool hmc_registr_util::hasRegistrFolder(HKEY hKey, std::string FolderPath)
{
	bool result = false;
	HKEY open_hkey;
	DWORD openResult = ::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey);
	_hmc_auto_free_HKey(open_hkey);

	switch (openResult)
	{
	case ERROR_SUCCESS:
		return true;
	case ERROR_FILE_NOT_FOUND:
		return false;
	}
	return result;
}

bool hmc_registr_util::hasRegistrFolder(HKEY hKey, std::wstring FolderPath)
{
	bool result = false;
	HKEY open_hkey;
	DWORD openResult = ::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey);
	_hmc_auto_free_HKey(open_hkey);

	switch (openResult)
	{
	case ERROR_SUCCESS:
		return true;
	case ERROR_FILE_NOT_FOUND:
		return false;
	}
	return result;
}

bool hmc_registr_util::removeRegistrFolder(HKEY hKey, std::wstring FolderPath, std::wstring FolderName, bool tree)
{
	if (tree)
	{
		return removeRegistrTree(hKey, FolderPath, FolderName);
	}

	bool result = false;
	HKEY open_hkey;
	DWORD openResult = ::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey);
	_hmc_auto_free_HKey(open_hkey);

	if (openResult == ERROR_SUCCESS)
	{
		openResult = ::RegDeleteKeyExW(HKEY_CURRENT_USER, FolderName.c_str(), KEY_WOW64_64KEY, 0);
		return (openResult == ERROR_SUCCESS) || (::RegDeleteKeyExW(HKEY_CURRENT_USER, FolderName.c_str(), KEY_WOW64_32KEY, 0) == ERROR_SUCCESS);
	}

	return false;
}

bool hmc_registr_util::removeRegistrFolder(HKEY hKey, std::string FolderPath, std::string FolderName, bool tree)
{
	if (tree)
	{
		return removeRegistrTree(hKey, FolderPath, FolderName);
	}

	bool result = false;
	HKEY open_hkey;
	DWORD openResult = ::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey);
	_hmc_auto_free_HKey(open_hkey);

	if (openResult == ERROR_SUCCESS)
	{
		openResult = ::RegDeleteKeyExA(HKEY_CURRENT_USER, FolderName.c_str(), KEY_WOW64_64KEY, 0);
		return (openResult == ERROR_SUCCESS) || (::RegDeleteKeyExA(HKEY_CURRENT_USER, FolderName.c_str(), KEY_WOW64_32KEY, 0) == ERROR_SUCCESS);
	}

	return false;
}

bool hmc_registr_util::removeRegistrValue(HKEY hKey, std::string FolderPath, std::string key)
{

	// 默认值 应该直接清空
	if (key.empty())
	{
		return removeRegistrKey(hKey, FolderPath, key);
	}

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	if (ERROR_SUCCESS == ::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey))
	{
		auto open_value = getValueStat(open_hkey, key);
		return ::RegSetValueExA(open_hkey, key.c_str(), 0, open_value.type, nullptr, 0) == ERROR_SUCCESS;
	}

	return false;
}

bool hmc_registr_util::removeRegistrValue(HKEY hKey, std::wstring FolderPath, std::wstring key)
{
	// 默认值 应该直接清空
	if (key.empty())
	{
		return removeRegistrKey(hKey, FolderPath, key);
	}

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	if (ERROR_SUCCESS == ::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey))
	{
		auto open_value = getValueStat(open_hkey, key);
		return ::RegSetValueExW(open_hkey, key.c_str(), 0, open_value.type, nullptr, 0) == ERROR_SUCCESS;
	}

	return false;
}

bool hmc_registr_util::removeRegistrKey(HKEY hKey, std::string FolderPath, std::string key)
{
	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	if (ERROR_SUCCESS == ::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey))
	{
		return ::RegDeleteValueA(open_hkey, key.c_str()) == ERROR_SUCCESS;
	}

	return false;
}

bool hmc_registr_util::removeRegistrKey(HKEY hKey, std::wstring FolderPath, std::wstring key)
{
	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	if (ERROR_SUCCESS == ::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey))
	{
		return ::RegDeleteValueW(open_hkey, key.c_str()) == ERROR_SUCCESS;
	}

	return false;
}

bool hmc_registr_util::removeRegistrTree(HKEY hKey, std::string subKey, std::string DirName)
{
	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	if (ERROR_SUCCESS == ::RegOpenKeyExA(hKey, subKey.c_str(), 0, KEY_ALL_ACCESS, &open_hkey))
	{
		RegDeleteTreeA(open_hkey, DirName.c_str());
	}
	return hasRegistrFolder(hKey, subKey + "\\" + DirName) == false;
}

bool hmc_registr_util::removeRegistrTree(HKEY hKey, std::wstring subKey, std::wstring DirName)
{
	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	if (ERROR_SUCCESS == ::RegOpenKeyExW(hKey, subKey.c_str(), 0, KEY_ALL_ACCESS, &open_hkey))
	{
		RegDeleteTreeW(open_hkey, DirName.c_str());
	}
	return hasRegistrFolder(hKey, subKey + L"\\" + DirName) == false;
}

HKEY hmc_registr_util::getHive(std::wstring hkey)
{
	if (hkey.find(L"HKEY_CURRENT_USER") != std::wstring::npos)
	{
		return HKEY_CURRENT_USER;
	}

	if (hkey.find(L"HKEY_LOCAL_MACHINE") != std::wstring::npos)
	{
		return HKEY_LOCAL_MACHINE;
	}

	if (hkey.find(L"HKEY_CLASSES_ROOT") != std::wstring::npos)
	{
		return HKEY_CLASSES_ROOT;
	}

	if (hkey.find(L"HKEY_USERS") != std::wstring::npos)
	{
		return HKEY_USERS;
	}

	if (hkey.find(L"HKEY_CURRENT_CONFIG") != std::wstring::npos)
	{
		return HKEY_CURRENT_CONFIG;
	}

	return NULL;
}

HKEY hmc_registr_util::getHive(std::string hkey)
{
	if (hkey.find("HKEY_CURRENT_USER") != std::string::npos)
	{
		return HKEY_CURRENT_USER;
	}

	if (hkey.find("HKEY_LOCAL_MACHINE") != std::string::npos)
	{
		return HKEY_LOCAL_MACHINE;
	}

	if (hkey.find("HKEY_CLASSES_ROOT") != std::string::npos)
	{
		return HKEY_CLASSES_ROOT;
	}

	if (hkey.find("HKEY_USERS") != std::string::npos)
	{
		return HKEY_USERS;
	}

	if (hkey.find("HKEY_CURRENT_CONFIG") != std::string::npos)
	{
		return HKEY_CURRENT_CONFIG;
	}

	return NULL;
}

std::string hmc_registr_util::getHiveA(HKEY hkey)
{
	if (hkey == HKEY_CURRENT_USER)
	{
		return "HKEY_CURRENT_USER";
	}

	if (hkey == HKEY_LOCAL_MACHINE)
	{
		return "HKEY_LOCAL_MACHINE";
	}

	if (hkey == HKEY_CLASSES_ROOT)
	{
		return "HKEY_CLASSES_ROOT";
	}

	if (hkey == HKEY_USERS)
	{
		return "HKEY_USERS";
	}

	if (hkey == HKEY_CURRENT_CONFIG)
	{
		return "HKEY_CURRENT_CONFIG";
	}

	return "";
}

std::wstring hmc_registr_util::getHiveW(HKEY hkey)
{
	if (hkey == HKEY_CURRENT_USER)
	{
		return L"HKEY_CURRENT_USER";
	}

	if (hkey == HKEY_LOCAL_MACHINE)
	{
		return L"HKEY_LOCAL_MACHINE";
	}

	if (hkey == HKEY_CLASSES_ROOT)
	{
		return L"HKEY_CLASSES_ROOT";
	}

	if (hkey == HKEY_USERS)
	{
		return L"HKEY_USERS";
	}

	if (hkey == HKEY_CURRENT_CONFIG)
	{
		return L"HKEY_CURRENT_CONFIG";
	}

	return L"";
}

bool hmc_registr_util::getHive(HKEY hkey, std::string &ptr_hkey)
{
	ptr_hkey.clear();
	ptr_hkey.append(getHiveA(hkey));
	return ptr_hkey.empty();
}

bool hmc_registr_util::getHive(HKEY hkey, std::wstring &ptr_hkey)
{
	ptr_hkey.clear();
	ptr_hkey.append(getHiveW(hkey));
	return ptr_hkey.empty();
}

std::string hmc_registr_util::getHive(HKEY hkey)
{
	return getHiveA(hkey);
}

hmc_registr_util::chValueStat hmc_registr_util::getValueStat(HKEY hKey, std::string subKey, std::string key)
{
	hmc_registr_util::chValueStat result = {0, 0, false};

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	if (::RegOpenKeyExA(hKey, subKey.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS)
	{
		// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
		if (open_hkey != NULL && RegQueryValueExA(open_hkey, key.c_str(), nullptr, &result.type, nullptr, &result.size) == ERROR_SUCCESS)
		{
			result.exists = true;
		}
	}

	return result;
}

hmc_registr_util::chValueStat hmc_registr_util::getValueStat(HKEY hKey, std::wstring subKey, std::wstring key)
{
	hmc_registr_util::chValueStat result = {0, 0, false};

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	if (::RegOpenKeyExW(hKey, subKey.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS)
	{
		// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
		if (open_hkey != NULL && RegQueryValueExW(open_hkey, key.c_str(), nullptr, &result.type, nullptr, &result.size) == ERROR_SUCCESS)
		{
			result.exists = true;
		}
	}

	return result;
}

hmc_registr_util::chValueStat hmc_registr_util::getValueStat(HKEY hKey, std::wstring key)
{
	hmc_registr_util::chValueStat result = {0, 0, false};

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (hKey != NULL && RegQueryValueExW(hKey, key.c_str(), nullptr, &result.type, nullptr, &result.size) == ERROR_SUCCESS)
	{
		result.exists = true;
	}
	return result;
}

hmc_registr_util::chValueStat hmc_registr_util::getValueStat(HKEY hKey, std::string key)
{
	hmc_registr_util::chValueStat result = {0, 0, false};

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (hKey != NULL && RegQueryValueExA(hKey, key.c_str(), nullptr, &result.type, nullptr, &result.size) == ERROR_SUCCESS)
	{
		result.exists = true;
	}
	return result;
}

hmc_registr_util::chFolderInfo hmc_registr_util::getRegistrFolderInfo(HKEY hKey, std::string FolderPath)
{
	auto result = chFolderInfo{0, false, 0, 0, 0};
	DWORD cbName = 0;	// 名称字符串的大小
	DWORD cSubKeys = 0; // 子键数
	DWORD cValues = 0;	// 目录键 的个数

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS)
	{
		if (open_hkey == NULL)
		{
			return result;
		}
	}

	FILETIME ftLastWriteTime; // 最后写入时间

	// 获取类名和值计数。

	DWORD retCode = RegQueryInfoKeyA(
		hKey,			   // key句柄
		nullptr,		   // 类名缓冲区
		nullptr,		   // 类字符串的大小
		NULL,			   // 无
		&cSubKeys,		   // 子键数
		nullptr,		   // 最长子键大小
		nullptr,		   // 最长类字符串
		&cValues,		   // 键的个数
		nullptr,		   // 最长值名
		nullptr,		   // 最长值数据
		nullptr,		   // 安全描述符的大小
		&ftLastWriteTime); // 最后写入时间

	if (retCode == ERROR_SUCCESS)
	{
		// 处理时间戳
		const ULONGLONG epochOffset = 116444736000000000ULL;
		ULARGE_INTEGER uli;
		uli.LowPart = ftLastWriteTime.dwLowDateTime;
		uli.HighPart = ftLastWriteTime.dwHighDateTime;
		ULONGLONG timestamp = (uli.QuadPart - epochOffset) / 10000ULL;

		result.time = static_cast<time_t>(timestamp);
		result.exists = true;
		result.keySize = cSubKeys;
		result.folderSize = cValues;
	}

	return result;
}

hmc_registr_util::chFolderInfo hmc_registr_util::getRegistrFolderInfo(HKEY hKey, std::wstring FolderPath)
{
	auto result = chFolderInfo{0, false, 0, 0, 0};
	DWORD cbName = 0;	// 名称字符串的大小
	DWORD cSubKeys = 0; // 子键数
	DWORD cValues = 0;	// 目录键 的个数

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS)
	{
		if (open_hkey == NULL)
		{
			return result;
		}
	}

	FILETIME ftLastWriteTime; // 最后写入时间

	// 获取类名和值计数。

	DWORD retCode = RegQueryInfoKeyW(
		open_hkey,		   // key句柄
		nullptr,		   // 类名缓冲区
		nullptr,		   // 类字符串的大小
		NULL,			   // 无
		&cSubKeys,		   // 子键数
		nullptr,		   // 最长子键大小
		nullptr,		   // 最长类字符串
		&cValues,		   // 键的个数
		nullptr,		   // 最长值名
		nullptr,		   // 最长值数据
		nullptr,		   // 安全描述符的大小
		&ftLastWriteTime); // 最后写入时间

	if (retCode == ERROR_SUCCESS)
	{
		// 处理时间戳
		const ULONGLONG epochOffset = 116444736000000000ULL;
		ULARGE_INTEGER uli;
		uli.LowPart = ftLastWriteTime.dwLowDateTime;
		uli.HighPart = ftLastWriteTime.dwHighDateTime;
		ULONGLONG timestamp = (uli.QuadPart - epochOffset) / 10000ULL;

		result.time = static_cast<time_t>(timestamp);
		result.exists = true;
		result.keySize = cSubKeys;
		result.folderSize = cValues;
	}

	return result;
}

size_t hmc_registr_util::getRegistrKeys(HKEY hKey, std::string path, std::vector<std::string> &QueryFolderList, std::vector<std::string> &QueryKeyList)
{

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	bool is_open = ::RegOpenKeyExA(hKey, path.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS;
	if (is_open)
	{
		return getRegistrKeys(open_hkey, QueryFolderList, QueryKeyList);
	}
	return 0;
}

size_t hmc_registr_util::getRegistrKeys(HKEY hKey, std::wstring path, std::vector<std::wstring> &QueryFolderList, std::vector<std::wstring> &QueryKeyList)
{
	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	bool is_open = ::RegOpenKeyExW(hKey, path.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS;
	if (is_open)
	{
		return getRegistrKeys(open_hkey, QueryFolderList, QueryKeyList);
	}
	return 0;
}

size_t hmc_registr_util::getRegistrKeys(HKEY hKey, std::vector<std::wstring> &QueryFolderList, std::vector<std::wstring> &QueryKeyList)
{

	QueryFolderList.clear();
	QueryKeyList.clear();

	wchar_t achKey[MAX_KEY_LENGTH] = L""; // 子键名称的缓冲区
	DWORD cbName = 0;					  // 名称字符串的大小
	wchar_t achClass[MAX_PATH] = L"";	  // 类名缓冲区
	DWORD cchClassName = MAX_PATH;		  // 类字符串的大小
	DWORD cSubKeys = 0;					  // 子键数
	DWORD cbMaxSubKey = 0;				  // 最长子键大小
	DWORD cchMaxClass = 0;				  // 最长类字符串
	DWORD cValues = 0;					  // 键值的个数
	DWORD cchMaxValue = 0;				  // 最长值名
	DWORD cbMaxValueData = 0;			  // 最长值数据
	DWORD cbSecurityDescriptor = 0;		  // 安全描述符的大小
	FILETIME ftLastWriteTime;			  // 最后写入时间

	// wchar_t achValue[MAX_VALUE_NAME]; // key存储
	std::vector<wchar_t> achValue;

	DWORD cchValue = MAX_VALUE_NAME; // 数据序号

	DWORD index, retCode;

	// 获取类名和值计数。

	retCode = RegQueryInfoKeyW(
		hKey,				   // key句柄
		achClass,			   // 类名缓冲区
		&cchClassName,		   // 类字符串的大小
		NULL,				   // 无
		&cSubKeys,			   // 子键数
		&cbMaxSubKey,		   // 最长子键大小
		&cchMaxClass,		   // 最长类字符串
		&cValues,			   // 键值的个数
		&cchMaxValue,		   // 最长值名
		&cbMaxValueData,	   // 最长值数据
		&cbSecurityDescriptor, // 安全描述符的大小
		&ftLastWriteTime);	   // 最后写入时间

	// 枚举子键，直到RegEnumKeyEx失败。
	if (cSubKeys)
	{

		for (index = 0; index < cSubKeys; index++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = ::RegEnumKeyExW(hKey, index,
									  achKey,
									  &cbName,
									  NULL,
									  NULL,
									  NULL,
									  &ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
			{
				QueryFolderList.push_back(achKey);
			}
		}
	}
	// 枚举键值。
	if (cValues)
	{
		achValue.resize(cchValue + MAX_PATH);

		for (index = 0, retCode = ERROR_SUCCESS; index < cValues; index++)
		{
			cchValue = MAX_VALUE_NAME;
			achValue[0] = '\0';
			retCode = RegEnumValueW(hKey, index,
									&achValue[0],
									&cchValue,
									NULL,
									NULL,
									NULL,
									NULL);

			if (retCode == ERROR_SUCCESS)
			{
				std::wstring str = std::wstring(achKey);
				str.resize(cchValue);
				for (size_t i = 0; i < cchValue; i++)
					str[i] = achValue[i];

				QueryKeyList.push_back(str);
			}
		}
	}

	return QueryFolderList.size() + QueryKeyList.size();
}

size_t hmc_registr_util::getRegistrKeys(HKEY hKey, std::vector<std::string> &QueryFolderList, std::vector<std::string> &QueryKeyList)
{
	QueryFolderList.clear();
	QueryKeyList.clear();

	char achKey[MAX_KEY_LENGTH] = ""; // 子键名称的缓冲区
	DWORD cbName = 0;				  // 名称字符串的大小
	// char achClass[MAX_PATH] = "";     // 类名缓冲区
	// DWORD cchClassName = MAX_PATH;  // 类字符串的大小
	DWORD cSubKeys = 0;				// 子键数
	DWORD cbMaxSubKey = 0;			// 最长子键大小
	DWORD cchMaxClass = 0;			// 最长类字符串
	DWORD cValues = 0;				// 键值的个数
	DWORD cchMaxValue = 0;			// 最长值名
	DWORD cbMaxValueData = 0;		// 最长值数据
	DWORD cbSecurityDescriptor = 0; // 安全描述符的大小
	FILETIME ftLastWriteTime;		// 最后写入时间

	// char achValue[MAX_VALUE_NAME];   // key存储
	std::vector<char> achValue;

	DWORD cchValue = MAX_VALUE_NAME; // 数据序号

	DWORD index, retCode;

	// 获取类名和值计数。

	retCode = RegQueryInfoKeyA(
		hKey,				   // key句柄
		nullptr,			   // 类名缓冲区
		nullptr,			   // 类字符串的大小
		nullptr,			   // 无
		&cSubKeys,			   // 子键数
		&cbMaxSubKey,		   // 最长子键大小
		&cchMaxClass,		   // 最长类字符串
		&cValues,			   // 键值的个数
		&cchMaxValue,		   // 最长值名
		&cbMaxValueData,	   // 最长值数据
		&cbSecurityDescriptor, // 安全描述符的大小
		&ftLastWriteTime);	   // 最后写入时间

	// 枚举子键，直到RegEnumKeyEx失败。
	if (cSubKeys)
	{

		for (index = 0; index < cSubKeys; index++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = ::RegEnumKeyExA(hKey, index,
									  achKey,
									  &cbName,
									  NULL,
									  NULL,
									  NULL,
									  &ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
			{
				QueryFolderList.push_back(achKey);
			}
		}
	}
	// 枚举键值。
	if (cValues)
	{
		achValue.resize(cchValue + MAX_PATH);

		for (index = 0, retCode = ERROR_SUCCESS; index < cValues; index++)
		{
			cchValue = MAX_VALUE_NAME;
			achValue[0] = '\0';
			retCode = RegEnumValueA(hKey, index,
									&achValue[0],
									&cchValue,
									NULL,
									NULL,
									NULL,
									NULL);

			if (retCode == ERROR_SUCCESS)
			{
				std::string str = std::string(achKey);
				str.resize(cchValue);
				for (size_t i = 0; i < cchValue; i++)
					str[i] = achValue[i];

				QueryKeyList.push_back(str);
			}
		}
	}
	return QueryFolderList.size() + QueryKeyList.size();
}

hmc_registr_util::chQueryFolderKeyW hmc_registr_util::getRegistrKeys(HKEY hKey, std::wstring path)
{
	chQueryFolderKeyW result = {{}, {}, 0};
	std::vector<std::wstring> QueryFolderList;
	std::vector<std::wstring> QueryKeyList;
	getRegistrKeys(hKey, path, QueryFolderList, QueryKeyList);

	for (size_t i = 0; i < QueryFolderList.size(); i++)
	{
		result.Folder.push_back(QueryFolderList[i]);
	}

	for (size_t i = 0; i < QueryKeyList.size(); i++)
	{
		result.key.push_back(QueryKeyList[i]);
	}

	result.size = QueryFolderList.size() + QueryKeyList.size();

	return result;
}

hmc_registr_util::chQueryFolderKeyA hmc_registr_util::getRegistrKeys(HKEY hKey, std::string path)
{
	chQueryFolderKeyA result = {{}, {}, 0};
	std::vector<std::string> QueryFolderList;
	std::vector<std::string> QueryKeyList;
	getRegistrKeys(hKey, path, QueryFolderList, QueryKeyList);

	for (size_t i = 0; i < QueryFolderList.size(); i++)
	{
		result.Folder.push_back(QueryFolderList[i]);
	}

	for (size_t i = 0; i < QueryKeyList.size(); i++)
	{
		result.key.push_back(QueryKeyList[i]);
	}

	result.size = QueryFolderList.size() + QueryKeyList.size();

	return result;
}

hmc_registr_util::chFolderInfo hmc_registr_util::chValueItme::getFolderInfo()
{
	auto result = hmc_registr_util::chFolderInfo{
		0,	   // 此所有键总数量
		false, // 此键是否存在
		0,	   // 此目录键总数量
		0,	   // 此目录键总数量
		0	   // 时间戳
	};

	if (isFolder)
	{
		result.exists = true;
		result.folderSize = type;
		result.keySize = size - type;
		result.time = time;
		result.size = size;
	}

	return result;
}

hmc_registr_util::chValue hmc_registr_util::chValueItme::getValueInfo()
{
	auto result = hmc_registr_util::chValue{
		0,	  // 值的大小
		0,	  // 类型
		{},	  // 数据
		false // 此键是否存在
	};

	if (!isFolder)
	{
		result.exists = true;
		result.size = size;
		result.value = value;
		result.type = type;
	}

	return result;
}

std::vector<hmc_registr_util::chValueItmeA> hmc_registr_util::getRegistrValueItmeList(HKEY hKey, std::string subKey)
{
	std::vector<hmc_registr_util::chValueItmeA> result = {};
	std::vector<std::string> QueryFolderList;
	std::vector<std::string> QueryKeyList;
	getRegistrKeys(hKey, subKey, QueryFolderList, QueryKeyList);

	for (size_t i = 0; i < QueryKeyList.size(); i++)
	{
		auto key = QueryKeyList[i];
		hmc_registr_util::chValueItmeA data;
		data.FolderPath = subKey;
		data.vkey = key;
		data.root = hKey;
		data.time = 0;
		data.isFolder = false;

		// 取值
		auto value_data = GetRegistrSourceValue(hKey, subKey, key);
		data.value = value_data.value;
		data.type = value_data.type;
		data.is_value = value_data.size > 0;
		data.size = value_data.size;

		result.emplace_back(data);
	}

	for (size_t i = 0; i < QueryKeyList.size(); i++)
	{
		auto key = QueryKeyList[i];
		hmc_registr_util::chValueItmeA data;
		data.FolderPath = subKey;
		data.vkey = key;
		data.root = hKey;
		data.value = {};
		data.type = 0;
		data.is_value = 0;

		auto FolderInfo = getRegistrFolderInfo(hKey, subKey + "\\" + key);

		// 有用的值
		data.size = FolderInfo.size;
		data.time = FolderInfo.time;
		data.isFolder = true;

		// 类型 在文件夹中此值将被作为 目录键数量
		data.type = FolderInfo.folderSize;

		result.emplace_back(data);
	}
	return result;
}

std::vector<hmc_registr_util::chValueItmeW> hmc_registr_util::getRegistrValueItmeList(HKEY hKey, std::wstring subKey)
{
	std::vector<hmc_registr_util::chValueItmeW> result = {};
	std::vector<std::wstring> QueryFolderList;
	std::vector<std::wstring> QueryKeyList;
	getRegistrKeys(hKey, subKey, QueryFolderList, QueryKeyList);

	for (size_t i = 0; i < QueryKeyList.size(); i++)
	{
		auto key = QueryKeyList[i];
		hmc_registr_util::chValueItmeW data;
		data.FolderPath = subKey;
		data.vkey = key;
		data.root = hKey;
		data.time = 0;
		data.isFolder = false;

		// 取值
		auto value_data = GetRegistrSourceValue(hKey, subKey, key);
		data.value = value_data.value;
		data.type = value_data.type;
		data.is_value = value_data.size > 0;
		data.size = value_data.size;

		result.emplace_back(data);
	}

	for (size_t i = 0; i < QueryKeyList.size(); i++)
	{
		auto key = QueryKeyList[i];
		hmc_registr_util::chValueItmeW data;
		data.FolderPath = subKey;
		data.vkey = key;
		data.root = hKey;
		data.value = {};
		data.type = 0;
		data.is_value = 0;

		auto FolderInfo = getRegistrFolderInfo(hKey, subKey + L"\\" + key);

		// 有用的值
		data.size = FolderInfo.size;
		data.time = FolderInfo.time;
		data.isFolder = true;

		// 类型 在文件夹中此值将被作为 目录键数量
		data.type = FolderInfo.folderSize;

		result.emplace_back(data);
	}

	return result;
}

hmc_registr_util::chValue hmc_registr_util::GetRegistrSourceValue(HKEY hKey, std::wstring FolderPath, std::wstring KeyName)
{
	hmc_registr_util::chValue result = {0, 0, {}, false};
	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS)
	{
		return GetRegistrSourceValue(open_hkey, KeyName);
	}

	return result;
}

hmc_registr_util::chValue hmc_registr_util::GetRegistrSourceValue(HKEY hKey, std::string FolderPath, std::string KeyName)
{
	hmc_registr_util::chValue result = {0, 0, {}, false};
	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS)
	{
		return GetRegistrSourceValue(open_hkey, KeyName);
	}

	return result;
}

hmc_registr_util::chValue hmc_registr_util::GetRegistrSourceValue(HKEY open_hkey, std::string KeyName)
{

	DWORD valueType;
	DWORD pDataSize = 0;
	hmc_registr_util::chValue result = {0, 0, {}, false};

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (::RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &valueType, nullptr, &pDataSize) == ERROR_SUCCESS)
	{
		result.size = pDataSize;
		result.type = valueType;
		result.exists = true;
	}

	// push data
	if (result.size)
	{
		std::vector<BYTE> value_data;
		value_data.resize(pDataSize);

		if (::RegQueryValueExA(open_hkey, KeyName.c_str(), 0, &valueType, reinterpret_cast<BYTE *>(value_data.data()), &pDataSize) == ERROR_SUCCESS)
		{
			result.value.resize(pDataSize);
			for (size_t i = 0; i < pDataSize; i++)
			{
				result.value[i] = value_data[i];
			}
		}
	}

	return result;
}

hmc_registr_util::chValue hmc_registr_util::GetRegistrSourceValue(HKEY open_hkey, std::wstring KeyName)
{
	DWORD valueType;
	DWORD pDataSize = 0;
	hmc_registr_util::chValue result = {0, 0, {}, false};

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &valueType, nullptr, &pDataSize) == ERROR_SUCCESS)
	{
		result.size = pDataSize;
		result.type = valueType;
		result.exists = true;
	}

	// push data
	if (result.size)
	{
		std::vector<BYTE> value_data;
		value_data.resize(pDataSize);

		if (::RegQueryValueExW(open_hkey, KeyName.c_str(), 0, &valueType, reinterpret_cast<BYTE *>(value_data.data()), &pDataSize) == ERROR_SUCCESS)
		{
			result.value.resize(pDataSize);
			for (size_t i = 0; i < pDataSize; i++)
			{
				result.value[i] = value_data[i];
			}
		}
	}

	return result;
}

bool hmc_registr_util::createRegistrFolder(HKEY hKey, std::string keyPath)
{
	HKEY open_hkey = nullptr;
	DWORD dwOptions = REG_OPTION_NON_VOLATILE;
	DWORD dwDisposition;
	_hmc_auto_free_HKey(open_hkey);
	long resulte = ::RegCreateKeyExA(hKey, keyPath.c_str(), 0, NULL,
									 dwOptions, KEY_WRITE, NULL, &open_hkey, &dwDisposition);
	if (resulte != ERROR_SUCCESS)
	{
		return false;
	}
	return (dwDisposition == REG_OPENED_EXISTING_KEY || dwDisposition == REG_CREATED_NEW_KEY);
}

bool hmc_registr_util::createRegistrFolder(HKEY hKey, std::wstring keyPath)
{
	HKEY open_hkey = nullptr;
	DWORD dwOptions = REG_OPTION_NON_VOLATILE;
	DWORD dwDisposition;
	_hmc_auto_free_HKey(open_hkey);

	long resulte = ::RegCreateKeyExW(hKey, keyPath.c_str(), 0, NULL,
									 dwOptions, KEY_WRITE, NULL, &open_hkey, &dwDisposition);
	if (resulte != ERROR_SUCCESS)
	{
		return false;
	}
	return (dwDisposition == REG_OPENED_EXISTING_KEY || dwDisposition == REG_CREATED_NEW_KEY);
}

bool hmc_registr_util::copyRegistrFolder(HKEY hKey, std::string sourcePath, std::string toPath)
{
	HKEY sourceHKey = nullptr;
	HKEY toHKey = nullptr;
	DWORD dwDisposition;

	_hmc_auto_free_HKey(sourceHKey);
	_hmc_auto_free_HKey(toHKey);

	if (ERROR_SUCCESS != ::RegOpenKeyExA(hKey, sourcePath.c_str(), 0, KEY_ALL_ACCESS, &sourceHKey))
	{
		return false;
	}

	if (ERROR_SUCCESS != ::RegCreateKeyExA(hKey, toPath.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &toHKey, &dwDisposition))
	{
		return false;
	}

	return (ERROR_SUCCESS == ::RegCopyTreeA(sourceHKey, nullptr, toHKey));
}

bool hmc_registr_util::copyRegistrFolder(HKEY hKey, std::wstring sourcePath, std::wstring toPath)
{
	HKEY sourceHKey = nullptr;
	HKEY toHKey = nullptr;
	DWORD dwDisposition;

	_hmc_auto_free_HKey(sourceHKey);
	_hmc_auto_free_HKey(toHKey);

	if (ERROR_SUCCESS != ::RegOpenKeyExW(hKey, sourcePath.c_str(), 0, KEY_ALL_ACCESS, &sourceHKey))
	{
		return false;
	}

	if (ERROR_SUCCESS != ::RegCreateKeyExW(hKey, toPath.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &toHKey, &dwDisposition))
	{
		return false;
	}

	return (ERROR_SUCCESS == ::RegCopyTreeW(sourceHKey, nullptr, toHKey));
}

bool hmc_registr_util::copyRegistrValue(HKEY hKey, std::string sourcePath, std::string sourceKey, std::string toPath, std::string toKey)
{
	return SetRegistrSourceValue(hKey, toPath, toKey, GetRegistrSourceValue(hKey, sourcePath, sourceKey));
}

bool hmc_registr_util::copyRegistrValue(HKEY hKey, std::wstring sourcePath, std::wstring sourceKey, std::wstring toPath, std::wstring toKey)
{
	return SetRegistrSourceValue(hKey, toPath, toKey, GetRegistrSourceValue(hKey, sourcePath, sourceKey));
}

std::wstring hmc_registr_util::joinPath(std::wstring root, std::vector<std::wstring> NameList)
{
	std::wstring result = std::wstring(root);

	// 预开劈内存 单次开辟更节省性能
	auto max_length = root.size();
	for (size_t i = 0; i < NameList.size(); i++)
	{
		max_length = max_length + NameList[i].size() + sizeof(wchar_t);
	}
	result.reserve(max_length);

	for (size_t i = 0; i < NameList.size(); i++)
	{
		auto name = NameList[i];
		if (!name.empty())
		{
			result.push_back(L'\\');
			result.append(name);
		}
	}
	return result;
}

std::string hmc_registr_util::joinPath(std::string root, std::vector<std::string> NameList)
{
	std::string result = std::string(root);

	// 预开劈内存 单次开辟更节省性能
	auto max_length = root.size();
	for (size_t i = 0; i < NameList.size(); i++)
	{
		max_length = max_length + NameList[i].size() + sizeof(char);
	}
	result.reserve(max_length);

	for (size_t i = 0; i < NameList.size(); i++)
	{
		auto name = NameList[i];
		if (!name.empty())
		{
			result.push_back('\\');
			result.append(name);
		}
	}
	return result;
}

bool hmc_registr_util::SetRegistrSourceValue(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, chValue Value)
{
	return SetRegistrSourceValue(hKey, FolderPath, KeyName, Value.type, Value.value);
}

bool hmc_registr_util::SetRegistrSourceValue(HKEY hKey, std::string FolderPath, std::string KeyName, chValue Value)
{
	return SetRegistrSourceValue(hKey, FolderPath, KeyName, Value.type, Value.value);
}

bool hmc_registr_util::SetRegistrSourceValue(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, DWORD type, const std::vector<BYTE> &value)
{
	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	bool is_open = ::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS;

	if (is_open)
	{
		return SetRegistrSourceValue(open_hkey, KeyName, type, value);
	}

	return false;
}

bool hmc_registr_util::SetRegistrSourceValue(HKEY hKey, std::string FolderPath, std::string KeyName, DWORD type, const std::vector<BYTE> &value)
{
	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);
	bool is_open = ::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS;

	if (is_open)
	{
		return SetRegistrSourceValue(open_hkey, KeyName, type, value);
	}

	return false;
}

bool hmc_registr_util::SetRegistrSourceValue(HKEY hKey, std::wstring KeyName, DWORD type, const std::vector<BYTE> &value)
{
	return ERROR_SUCCESS == ::RegSetValueExW(hKey, KeyName.c_str(), 0, type, reinterpret_cast<const BYTE *>(value.data()), static_cast<DWORD>(value.size() * sizeof(BYTE)));
}

bool hmc_registr_util::SetRegistrSourceValue(HKEY hKey, std::string KeyName, DWORD type, const std::vector<BYTE> &value)
{
	return ERROR_SUCCESS == ::RegSetValueExA(hKey, KeyName.c_str(), 0, type, reinterpret_cast<const BYTE *>(value.data()), static_cast<DWORD>(value.size() * sizeof(BYTE)));
}

bool hmc_registr_util::SetRegistrSourceValue(HKEY hKey, std::wstring KeyName, chValue Value)
{
	return SetRegistrSourceValue(hKey, KeyName, Value.type, Value.value);
}

bool hmc_registr_util::SetRegistrSourceValue(HKEY hKey, std::string KeyName, chValue Value)
{
	return SetRegistrSourceValue(hKey, KeyName, Value.type, Value.value);
}

bool hmc_registr_util::setRegistrValue::set(hmc_registr_util::REG_TYPE type, const std::vector<BYTE> &value)
{

	if (!is_ready())
		return false;

	// wstring
	if (is_wide)
	{
		return SetRegistrSourceValue(root_hKey, NameW, type, value);
	}

	// string
	return SetRegistrSourceValue(root_hKey, NameA, type, value);
}

bool hmc_registr_util::setRegistrValue::set(DWORD type, const std::vector<BYTE> &value)
{
	return set((REG_TYPE)type, value);
}

bool hmc_registr_util::setRegistrValue::set(/*REG_NONE*/)
{
	if (!is_ready())
		return false;

	if (is_wide)
	{
		return ERROR_SUCCESS == ::RegSetValueExW(open_hkey, NameW.c_str(), 0, REG_NONE, nullptr, 0ul);
	}
	return ERROR_SUCCESS == ::RegSetValueExA(open_hkey, NameA.c_str(), 0, REG_NONE, nullptr, 0ul);
}

bool hmc_registr_util::setRegistrValue::set(int64_t number, REG_TYPE type /*REG_QWORD*/)
{
	if (!is_ready())
		return false;

	if (is_wide)
	{
		return ERROR_SUCCESS == ::RegSetValueExW(open_hkey, NameW.c_str(), 0, type, reinterpret_cast<const BYTE *>(&number), static_cast<DWORD>(sizeof(number)));
	}
	return ERROR_SUCCESS == ::RegSetValueExA(open_hkey, NameA.c_str(), 0, type, reinterpret_cast<const BYTE *>(&number), static_cast<DWORD>(sizeof(number)));
}

bool hmc_registr_util::setRegistrValue::set(long number, REG_TYPE type /*REG_DWORD*/)
{
	if (!is_ready())
		return false;

	if (is_wide)
	{
		return ERROR_SUCCESS == ::RegSetValueExW(open_hkey, NameW.c_str(), 0, type, reinterpret_cast<const BYTE *>(&number), static_cast<DWORD>(sizeof(number)));
	}
	return ERROR_SUCCESS == ::RegSetValueExA(open_hkey, NameA.c_str(), 0, type, reinterpret_cast<const BYTE *>(&number), static_cast<DWORD>(sizeof(number)));
}

bool hmc_registr_util::setRegistrValue::set(std::wstring input /*REG_SZ*/, bool expand /* [true] to REG_EXPAND_SZ*/)
{
	if (!is_ready())
		return false;

	return ERROR_SUCCESS == ::RegSetValueExW(
								open_hkey,
								NameW.c_str(),
								0,
								(expand ? REG_EXPAND_SZ : REG_SZ),
								reinterpret_cast<const BYTE *>(input.c_str()),
								static_cast<DWORD>(input.size() * sizeof(wchar_t)));
}

bool hmc_registr_util::setRegistrValue::set(std::string input /*REG_SZ*/, bool expand /* [true] to REG_EXPAND_SZ*/)
{

	if (!is_ready())
		return false;

	std::vector<BYTE> input_value;

	return ERROR_SUCCESS == ::RegSetValueExA(
								open_hkey,
								NameA.c_str(),
								0,
								(expand ? REG_EXPAND_SZ : REG_SZ),
								reinterpret_cast<const BYTE *>(input.c_str()),
								static_cast<DWORD>(input.size() * sizeof(char)));
}

bool hmc_registr_util::setRegistrValue::setRegistrValue::set(/*REG_MULTI_SZ*/ const std::vector<std::wstring> &input)
{
	return SetRegistrMulti(root_hKey, subKeyW, NameW, input);
}

bool hmc_registr_util::setRegistrValue::setRegistrValue::set(/*REG_MULTI_SZ*/ const std::vector<std::string> &input)
{
	return SetRegistrMulti(root_hKey, subKeyA, NameA, input);
}

std::string hmc_registr_util::RegistrValueUtil::utf16_to_ansi(const std::wstring input)
{
	const wchar_t *pwszText = input.c_str();

	if (pwszText == NULL || wcslen(pwszText) == 0)
	{
		return std::string();
	}
	int iSizeInBytes = WideCharToMultiByte(CP_ACP, 0, pwszText, -1, NULL, 0, NULL, NULL);
	char *pMultiByte = new (std::nothrow) char[iSizeInBytes];
	if (pMultiByte == NULL)
	{
		return std::string();
	}

	memset(pMultiByte, 0, iSizeInBytes);
	WideCharToMultiByte(CP_ACP, 0, pwszText, -1, pMultiByte, iSizeInBytes, NULL, NULL);

	std::string strResult = std::string(pMultiByte);
	delete[] pMultiByte;
	pMultiByte = NULL;

	return strResult;
}

std::wstring hmc_registr_util::RegistrValueUtil::ansi_to_utf16(const std::string input)
{
	const char *pszText = input.c_str();

	if (pszText == NULL || strlen(pszText) == 0)
	{
		return std::wstring();
	}
	int iSizeInChars = MultiByteToWideChar(CP_ACP, 0, pszText, -1, NULL, 0);
	wchar_t *pWideChar = new (std::nothrow) wchar_t[iSizeInChars];
	if (pWideChar == NULL)
	{
		return std::wstring();
	}

	wmemset(pWideChar, 0, iSizeInChars);
	MultiByteToWideChar(CP_ACP, 0, pszText, -1, pWideChar, iSizeInChars);

	std::wstring strResult = std::wstring(pWideChar);
	delete[] pWideChar;
	pWideChar = NULL;
	return strResult;
}

bool hmc_registr_util::RegistrValueUtil::is_ready()
{
	return (!_is_ready || !root_hKey || (subKeyW.empty() && subKeyA.empty())) ? false : true;
}

hmc_registr_util::getRegistrValue::getRegistrValue(HKEY hKey, std::wstring subKey, std::wstring Name)
{
	root_hKey = hKey;
	_is_ready = ::RegOpenKeyExW(hKey, subKey.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS;
	subKeyW.append(subKey);
	NameW.append(Name);

	// subKeyA.append(utf16_to_ansi(subKey));
	NameA.append(utf16_to_ansi(Name));
	is_wide = true;
}

hmc_registr_util::getRegistrValue::getRegistrValue(HKEY hKey, std::string subKey, std::string Name)
{
	root_hKey = hKey;
	_is_ready = ::RegOpenKeyExA(hKey, subKey.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS;
	subKeyA.append(subKey);
	NameA.append(Name);
	// subKeyW.append(ansi_to_utf16(subKey));
	NameW.append(ansi_to_utf16(Name));
	is_wide = false;
}

hmc_registr_util::setRegistrValue::setRegistrValue(HKEY hKey, std::wstring subKey, std::wstring Name)
{
	root_hKey = hKey;
	_is_ready = ::RegOpenKeyExW(hKey, subKey.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS;
	subKeyW.append(subKey);
	NameW.append(Name);

	// subKeyA.append(utf16_to_ansi(subKey));
	NameA.append(utf16_to_ansi(Name));
	is_wide = true;
}

hmc_registr_util::setRegistrValue::setRegistrValue(HKEY hKey, std::string subKey, std::string Name)
{
	root_hKey = hKey;
	_is_ready = ::RegOpenKeyExA(hKey, subKey.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) == ERROR_SUCCESS;
	subKeyA.append(subKey);
	NameA.append(Name);
	// subKeyW.append(ansi_to_utf16(subKey));
	NameW.append(ansi_to_utf16(Name));
	is_wide = false;
}

hmc_registr_util::RegistrValueUtil::~RegistrValueUtil()
{
	if (open_hkey != nullptr)
	{
		::RegCloseKey(open_hkey);
		open_hkey = nullptr;
	}

	if (root_hKey != nullptr)
	{
		root_hKey = nullptr;
	}
}

std::vector<BYTE> hmc_registr_util::getRegistrValue::getBuff()
{
	if (!is_ready())
		return {};
	return GetRegistrSourceValue(open_hkey, NameW).value;
}

int32_t hmc_registr_util::getRegistrValue::getInt32()
{
	if (!is_ready())
		return 0;

	auto ValueStat = getValueStat(open_hkey, NameW);
	DWORD type = REG_DWORD;
	std::uint32_t result = 0;

	// 防止溢出
	if (ValueStat.size > sizeof(std::uint32_t))
	{
		return 0ull;
	}

	if (::RegQueryValueExW(open_hkey, NameW.c_str(), 0, &type, reinterpret_cast<BYTE *>(&result), &ValueStat.size) == ERROR_SUCCESS)
	{
		// 缩减
		return static_cast<std::uint32_t>(result);
	}
	return 0ul;
}

int64_t hmc_registr_util::getRegistrValue::getInt64()
{
	if (!is_ready())
		return 0ull;
	auto ValueStat = getValueStat(open_hkey, NameW);
	DWORD type = REG_QWORD;
	std::uint64_t result = 0;

	// 防止溢出
	if (ValueStat.size > sizeof(std::uint64_t))
	{
		return 0ull;
	}

	if (::RegQueryValueExW(open_hkey, NameW.c_str(), 0, &type, reinterpret_cast<BYTE *>(&result), &ValueStat.size) == ERROR_SUCCESS)
	{
		return result;
	}
	return 0ull;
}

HWND hmc_registr_util::getRegistrValue::getHwnd()
{
	if (!is_ready())
		return NULL;
	auto value = GetRegistrSourceValue(open_hkey, NameW);

	return (HWND)value.getInt64();
}

std::vector<std::wstring> hmc_registr_util::getRegistrValue::getMultiW()
{
	if (!is_ready())
		return {};
	return GetRegistrMulti(root_hKey, subKeyW, NameW);
}

std::vector<std::string> hmc_registr_util::getRegistrValue::getMultiA()
{
	if (!is_ready())
		return {};
	return GetRegistrMulti(root_hKey, subKeyA, NameA);
}

std::wstring hmc_registr_util::getRegistrValue::getStringW(bool expand)
{
	if (!is_ready())
		return L"";

	auto sizep = hmc_registr_util::getValueStat(open_hkey, NameW);

	std::wstring result = std::wstring();

	DWORD cBuffer = (sizep.size / sizeof(WCHAR)) + 1;
	LPWSTR lpData = new WCHAR[cBuffer];

	DWORD type = expand ? REG_EXPAND_SZ : REG_SZ;

	if (::RegQueryValueExW(open_hkey, NameW.c_str(), 0, &type, reinterpret_cast<std::uint8_t *>(lpData), &sizep.size) == ERROR_SUCCESS)
	{
		result.append(lpData);
	}

	return result;
}

std::string hmc_registr_util::getRegistrValue::getStringA(bool expand)
{
	if (!is_ready())
		return "";

	auto sizep = hmc_registr_util::getValueStat(open_hkey, NameA);

	std::string result = std::string();
	std::vector<std::uint8_t> value_data(sizep.size);

	DWORD type = expand ? REG_EXPAND_SZ : REG_SZ;

	if (::RegQueryValueExA(open_hkey, NameA.c_str(), 0, &type, reinterpret_cast<std::uint8_t *>(value_data.data()), &sizep.size) == ERROR_SUCCESS)
	{
		result.reserve(sizep.size);

		for (size_t i = 0; i < sizep.size; i++)
		{
			result.push_back(static_cast<char>(value_data.at(i)));
		}
	}

	return result;
}

bool hmc_registr_util::getRegistrValue::isValue()
{
	if (!is_ready())
		return false;
	return hmc_registr_util::getValueStat(open_hkey, NameW).exists;
}

bool hmc_registr_util::getRegistrValue::isString()
{
	if (!is_ready())
		return false;

	auto stat = hmc_registr_util::getValueStat(open_hkey, NameW);
	return stat.isString();
}

bool hmc_registr_util::getRegistrValue::isNumber()
{
	if (!is_ready())
		return false;
	auto stat = hmc_registr_util::getValueStat(open_hkey, NameW);
	return stat.isNumber();
}

bool hmc_registr_util::getRegistrValue::isInt64()
{
	if (!is_ready())
		return false;
	auto stat = hmc_registr_util::getValueStat(open_hkey, NameW);
	return stat.isInt64();
}

bool hmc_registr_util::getRegistrValue::isType(DWORD type)
{
	return getType() == type;
}

DWORD hmc_registr_util::getRegistrValue::getType()
{
	if (!is_ready())
		return REG_NONE;
	return hmc_registr_util::getValueStat(open_hkey, NameW).type;
}

hmc_registr_util::OpenKeyToken::operator HKEY() const
{
	return token;
}

bool hmc_registr_util::OpenKeyToken::operator!() const
{
	return (token == nullptr);
}

hmc_registr_util::OpenKeyToken::operator bool() const
{
	return (token != nullptr);
}

hmc_registr_util::OpenKeyToken::OpenKeyToken(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, bool CreateNotKey)
{
	if ((status = ::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &token)) != ERROR_SUCCESS)
	{
		if (CreateNotKey)
		{

			DWORD dwOptions = REG_OPTION_NON_VOLATILE;
			DWORD dwDisposition;

			status = ::RegCreateKeyExW(hKey, FolderPath.c_str(), 0, NULL, dwOptions, KEY_WRITE, NULL, &token, &dwDisposition);

			if (status != ERROR_SUCCESS)
			{
				return;
			}

			if ((status = ::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &token)) != ERROR_SUCCESS)
			{
				return;
			}
		}
	}
}

hmc_registr_util::OpenKeyToken::OpenKeyToken(HKEY hKey, std::string FolderPath, std::string KeyName, bool CreateNotKey)
{
	if ((status = ::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &token)) != ERROR_SUCCESS)
	{
		if (CreateNotKey)
		{

			DWORD dwOptions = REG_OPTION_NON_VOLATILE;
			DWORD dwDisposition;

			status = ::RegCreateKeyExA(hKey, FolderPath.c_str(), 0, NULL, dwOptions, KEY_WRITE, NULL, &token, &dwDisposition);

			if (status != ERROR_SUCCESS)
			{
				return;
			}

			if ((status = ::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &token)) != ERROR_SUCCESS)
			{
				return;
			}
		}
	}
}

hmc_registr_util::OpenKeyToken::~OpenKeyToken()
{
	if (token != nullptr)
	{
		::RegCloseKey(token);
		token = nullptr;
	}
}

bool hmc_registr_util::SetRegistrString(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, const std::wstring &Input, bool expand)
{
	bool result = false;
	OpenKeyToken token = OpenKeyToken(hKey, FolderPath, KeyName, true);

	if (!token)
	{
		return result;
	}

	DWORD to_type = expand ? REG_EXPAND_SZ : REG_SZ;
	DWORD buff_size = static_cast<DWORD>(Input.size() * sizeof(char));

	if (::RegSetValueExW(token, KeyName.c_str(), NULL, to_type, reinterpret_cast<const BYTE *>(Input.c_str()), buff_size) == ERROR_SUCCESS)
	{

		DWORD lpType = REG_NONE;
		DWORD pDataSize = 0;

		if (::RegQueryValueExW(token, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{
			result = lpType == to_type && pDataSize != 0;
			return result;
		}
	}

	return result;
}

bool hmc_registr_util::SetRegistrString(HKEY hKey, std::string FolderPath, std::string KeyName, const std::string &Input, bool expand)
{
	bool result = false;
	OpenKeyToken token = OpenKeyToken(hKey, FolderPath, KeyName, true);

	if (!token)
	{
		return result;
	}

	DWORD to_type = expand ? REG_EXPAND_SZ : REG_SZ;
	DWORD buff_size = static_cast<DWORD>(Input.size() * sizeof(char));

	if (::RegSetValueExA(token, KeyName.c_str(), NULL, to_type, reinterpret_cast<const BYTE *>(Input.c_str()), buff_size) == ERROR_SUCCESS)
	{

		DWORD lpType = REG_NONE;
		DWORD pDataSize = 0;

		if (::RegQueryValueExA(token, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{
			result = lpType == to_type && pDataSize != 0;
			return result;
		}
	}

	return result;
}

bool hmc_registr_util::SetRegistrString(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, const std::wstring &Input, const DWORD retype)
{
	bool result = false;
	OpenKeyToken token = OpenKeyToken(hKey, FolderPath, KeyName, true);

	if (!token)
	{
		return result;
	}

	DWORD buff_size = static_cast<DWORD>(Input.size() * sizeof(char));

	if (::RegSetValueExW(token, KeyName.c_str(), NULL, retype, reinterpret_cast<const BYTE *>(Input.c_str()), buff_size) == ERROR_SUCCESS)
	{

		DWORD lpType = REG_NONE;
		DWORD pDataSize = 0;

		if (::RegQueryValueExW(token, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{
			result = lpType == retype && pDataSize != 0;
			return result;
		}
	}

	return result;
}

bool hmc_registr_util::SetRegistrString(HKEY hKey, std::string FolderPath, std::string KeyName, const std::string &Input, const DWORD retype)
{
	bool result = false;
	OpenKeyToken token = OpenKeyToken(hKey, FolderPath, KeyName, true);

	if (!token)
	{
		return result;
	}

	DWORD buff_size = static_cast<DWORD>(Input.size() * sizeof(char));

	if (::RegSetValueExA(token, KeyName.c_str(), NULL, retype, reinterpret_cast<const BYTE *>(Input.c_str()), buff_size) == ERROR_SUCCESS)
	{

		DWORD lpType = REG_NONE;
		DWORD pDataSize = 0;

		if (::RegQueryValueExA(token, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{
			result = lpType == retype && pDataSize != 0;
			return result;
		}
	}

	return result;
}

bool hmc_registr_util::SetRegistrMulti(HKEY hKey, std::string FolderPath, std::string KeyName, const std::vector<std::string> &Input)
{
	bool result = false;
	OpenKeyToken token = OpenKeyToken(hKey, FolderPath, KeyName, true);

	if (!token)
	{
		return result;
	}

	DWORD to_type = REG_MULTI_SZ;
	DWORD buff_size = 0; // static_cast<DWORD>(Input.size() * sizeof(char));

	// 计算总大小
	size_t length = Input.size();

	for (size_t i = 0; i < length; i++)
	{
		auto it = &Input.at(i);
		buff_size += static_cast<DWORD>(it->size() * sizeof(char));
	}

	std::string input_multi = "";
	input_multi.reserve(buff_size / sizeof(char));

	length = Input.size();

	// 制作数组
	for (size_t i = 0; i < length; i++)
	{
		auto it = &Input.at(i);
		size_t it_size = it->size();

		for (size_t si = 0; si < it_size; si++)
		{
			auto it2 = it->at(si);

			if (si + 1 < it_size && it2 == '\0')
			{
				input_multi.append("\\0");
			}
			else
			{
				input_multi.push_back(it2);
			}
		}

		auto end_pos = input_multi.find_last_not_of('\0');
		if (end_pos == std::string::npos)
		{
			input_multi.push_back('\0');
		}
	}

	// 以\0\0 结尾
	input_multi.push_back('\0');

	buff_size = static_cast<DWORD>(input_multi.size() * sizeof(char));

	if (::RegSetValueExA(token, KeyName.c_str(), NULL, to_type, reinterpret_cast<const BYTE *>(input_multi.c_str()), buff_size) == ERROR_SUCCESS)
	{

		DWORD lpType = REG_NONE;
		DWORD pDataSize = 0;

		if (::RegQueryValueExA(token, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{
			result = lpType == to_type && pDataSize != 0;
			return result;
		}
	}

	return result;
}

bool hmc_registr_util::SetRegistrMulti(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, const std::vector<std::wstring> &Input)
{
	bool result = false;
	OpenKeyToken token = OpenKeyToken(hKey, FolderPath, KeyName, true);

	if (!token)
	{
		return result;
	}

	DWORD to_type = REG_MULTI_SZ;
	DWORD buff_size = 0; // static_cast<DWORD>(Input.size() * sizeof(char));

	// 计算总大小
	size_t length = Input.size();

	for (size_t i = 0; i < length; i++)
	{
		auto it = &Input.at(i);
		buff_size += static_cast<DWORD>(it->size() * sizeof(wchar_t));
	}

	std::wstring input_multi = L"";
	input_multi.reserve(buff_size / sizeof(wchar_t));

	length = Input.size();

	// 制作数组
	for (size_t i = 0; i < length; i++)
	{
		auto it = &Input.at(i);
		size_t it_size = it->size();

		for (size_t si = 0; si < it_size; si++)
		{

			auto it2 = it->at(si);

			if (si + 1 < it_size && it2 == L'\0')
			{
				input_multi.append(L"\\0");
			}
			else
			{
				input_multi.push_back(it2);
			}
		}

		auto end_pos = input_multi.find_last_not_of(L'\0');
		if (end_pos == std::string::npos)
		{
			input_multi.push_back(L'\0');
		}
	}

	// 以\0\0 结尾
	input_multi.push_back(L'\0');

	buff_size = static_cast<DWORD>(input_multi.size() * sizeof(wchar_t));

	if (::RegSetValueExW(token, KeyName.c_str(), NULL, to_type, reinterpret_cast<const BYTE *>(input_multi.c_str()), buff_size) == ERROR_SUCCESS)
	{

		DWORD lpType = REG_NONE;
		DWORD pDataSize = 0;

		if (::RegQueryValueExW(token, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{
			result = lpType == to_type && pDataSize != 0;
			return result;
		}
	}

	return result;
}

bool hmc_registr_util::SetRegistrInt32(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, const std::uint32_t &Input)
{
	bool result = false;
	OpenKeyToken token = OpenKeyToken(hKey, FolderPath, KeyName, true);

	if (!token)
	{
		return result;
	}

	DWORD to_type = REG_DWORD;
	DWORD size_ptr = sizeof(std::uint32_t);
	std::uint32_t input = Input;

	if (::RegSetValueExW(token, KeyName.c_str(), NULL, to_type, reinterpret_cast<const BYTE *>(&input), size_ptr) == ERROR_SUCCESS)
	{

		DWORD lpType = REG_NONE;
		DWORD pDataSize = 0;

		if (::RegQueryValueExW(token, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{
			result = lpType == to_type && pDataSize != 0;
			return result;
		}
	}

	return result;
}

bool hmc_registr_util::SetRegistrInt32(HKEY hKey, std::string FolderPath, std::string KeyName, const std::uint32_t &Input)
{
	bool result = false;
	OpenKeyToken token = OpenKeyToken(hKey, FolderPath, KeyName, true);

	if (!token)
	{
		return result;
	}

	DWORD to_type = REG_DWORD;
	DWORD size_ptr = sizeof(std::uint32_t);
	std::uint32_t input = Input;

	if (::RegSetValueExA(token, KeyName.c_str(), NULL, to_type, reinterpret_cast<const BYTE *>(&input), size_ptr) == ERROR_SUCCESS)
	{

		DWORD lpType = REG_NONE;
		DWORD pDataSize = 0;

		if (::RegQueryValueExA(token, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{
			result = lpType == to_type && pDataSize != 0;
			return result;
		}
	}

	return result;
}

bool hmc_registr_util::SetRegistrInt64(HKEY hKey, std::string FolderPath, std::string KeyName, const std::uint64_t &Input)
{
	bool result = false;
	OpenKeyToken token = OpenKeyToken(hKey, FolderPath, KeyName, true);

	if (!token)
	{
		return result;
	}

	DWORD to_type = REG_QWORD;
	DWORD size_ptr = sizeof(std::uint64_t);
	std::uint64_t input = Input;

	if (::RegSetValueExA(token, KeyName.c_str(), NULL, to_type, reinterpret_cast<const BYTE *>(&input), size_ptr) == ERROR_SUCCESS)
	{

		DWORD lpType = REG_NONE;
		DWORD pDataSize = 0;

		if (::RegQueryValueExA(token, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{
			result = lpType == to_type && pDataSize != 0;
			return result;
		}
	}

	return result;
}

bool hmc_registr_util::SetRegistrInt64(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, const std::uint64_t &Input)
{
	bool result = false;
	OpenKeyToken token = OpenKeyToken(hKey, FolderPath, KeyName, true);

	if (!token)
	{
		return result;
	}

	DWORD to_type = REG_QWORD;
	DWORD size_ptr = sizeof(std::uint64_t);
	std::uint64_t input = Input;

	if (::RegSetValueExW(token, KeyName.c_str(), NULL, to_type, reinterpret_cast<const BYTE *>(&input), size_ptr) == ERROR_SUCCESS)
	{

		DWORD lpType = REG_NONE;
		DWORD pDataSize = 0;

		if (::RegQueryValueExW(token, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{
			result = lpType == to_type && pDataSize != 0;
			return result;
		}
	}

	return result;
}

std::vector<std::wstring> hmc_registr_util::GetRegistrMulti(HKEY hKey, std::wstring FolderPath, std::wstring KeyName)
{

	std::vector<std::wstring> list = {};

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) != ERROR_SUCCESS)
	{
		return list;
	}

	DWORD lpType = REG_MULTI_SZ;
	DWORD pDataSize = 0;

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
	{
		std::wstring lpWstrList;
		lpWstrList.resize(pDataSize / sizeof(wchar_t));

		if (::RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, reinterpret_cast<BYTE *>(&lpWstrList[0]), &pDataSize) == ERROR_SUCCESS)
		{
			std::wstring temp = L"";

			auto end_pos = lpWstrList.size();

			// 移除所有尾部 \0
			while ((end_pos = lpWstrList.find_last_not_of(L'\0')) != lpWstrList.size() - 1)
			{
				lpWstrList.erase(end_pos + 1);
			}

			size_t len = lpWstrList.size();

			for (size_t i = 0; i < len; i++)
			{
				wchar_t it = lpWstrList[i];
				if (it == L'\0')
				{
					list.push_back(std::wstring(temp + L""));
					temp.clear();
					continue;
				}

				temp.push_back(it);
			}

			if (!temp.empty())
			{
				list.push_back(std::wstring(temp + L""));
				temp.clear();
			}
		}
	}
	return list;
}

std::vector<std::string> hmc_registr_util::GetRegistrMulti(HKEY hKey, std::string FolderPath, std::string KeyName)
{

	std::vector<std::string> list = {};

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) != ERROR_SUCCESS)
	{
		return list;
	}

	DWORD lpType = REG_MULTI_SZ;
	DWORD pDataSize = 0;

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
	{
		std::string lpWstrList;
		lpWstrList.resize(pDataSize / sizeof(char));

		if (::RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &lpType, reinterpret_cast<BYTE *>(&lpWstrList[0]), &pDataSize) == ERROR_SUCCESS)
		{
			std::string temp = "";

			auto end_pos = lpWstrList.size();

			// 移除所有尾部 \0
			while ((end_pos = lpWstrList.find_last_not_of('\0')) != lpWstrList.size() - 1)
			{
				lpWstrList.erase(end_pos + 1);
			}

			size_t len = lpWstrList.size();

			for (size_t i = 0; i < len; i++)
			{
				char it = lpWstrList[i];
				if (it == '\0')
				{
					list.push_back(std::string(temp + ""));
					temp.clear();
					continue;
				}

				temp.push_back(it);
			}

			if (!temp.empty())
			{
				list.push_back(std::string(temp + ""));
				temp.clear();
			}
		}
	}
	return list;
}

std::wstring hmc_registr_util::GetRegistrString(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, bool expand)
{

	std::wstring result = L"";

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) != ERROR_SUCCESS)
	{
		return result;
	}

	DWORD lpType = expand ? RRF_RT_REG_EXPAND_SZ : REG_SZ;
	DWORD pDataSize = 0;

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
	{

		// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
		if (RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{

			if (pDataSize < 1)
			{
				return result;
			}

			size_t char_len = pDataSize / sizeof(wchar_t);
			wchar_t *lpValue = new wchar_t[char_len];

			if (::RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, reinterpret_cast<BYTE *>(lpValue), &pDataSize) == ERROR_SUCCESS)
			{
				char_len = pDataSize / sizeof(wchar_t);
				result.reserve(char_len);

				for (size_t i = 0; i < char_len; i++)
				{
					auto it = lpValue[i];
					if (it == L'\0')
					{
						break;
					}
					result.push_back(it);
				}
			}
		}
	}

	// 内存预开劈过了 克隆新的对象
	if (result.capacity() > 0 && result.capacity() != result.size())
	{
		return std::wstring(result.c_str());
	}

	return result;
}

std::string hmc_registr_util::GetRegistrString(HKEY hKey, std::string FolderPath, std::string KeyName, bool expand)
{

	std::string result = {};

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) != ERROR_SUCCESS)
	{
		return result;
	}

	DWORD lpType = expand ? RRF_RT_REG_EXPAND_SZ : REG_SZ;
	DWORD pDataSize = 0;

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
	{

		if (pDataSize < 1)
		{
			return result;
		}

		size_t char_len = pDataSize / sizeof(char);

		char *lpValue = new char[char_len];

		if (::RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &lpType, reinterpret_cast<BYTE *>(lpValue), &pDataSize) == ERROR_SUCCESS)
		{

			char_len = pDataSize / sizeof(char);
			result.reserve(char_len);

			for (size_t i = 0; i < char_len; i++)
			{
				auto it = lpValue[i];
				if (it == '\0')
				{
					break;
				}
				result.push_back(it);
			}
		}
	}

	// 内存预开劈过了 克隆新的对象
	if (result.capacity() > 0 && result.capacity() != result.size())
	{
		return std::string(result.c_str());
	}

	return result;
}

std::uint32_t hmc_registr_util::GetRegistrInt32(HKEY hKey, std::wstring FolderPath, std::wstring KeyName)
{
	std::uint32_t result = 0;

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) != ERROR_SUCCESS)
	{
		return result;
	}

	DWORD lpType = REG_DWORD;
	DWORD pDataSize = 0;

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
	{

		// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
		if (RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{

			if (pDataSize < 1 || pDataSize > sizeof(std::uint32_t))
			{
				return result;
			}

			std::uint32_t lpValue = 0;

			if (::RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, reinterpret_cast<BYTE *>(&lpValue), &pDataSize) == ERROR_SUCCESS)
			{
				result = lpValue;
				return result;
			}
		}
	}

	return result;
}

std::uint32_t hmc_registr_util::GetRegistrInt32(HKEY hKey, std::string FolderPath, std::string KeyName)
{
	std::uint32_t result = 0;

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) != ERROR_SUCCESS)
	{
		return result;
	}

	DWORD lpType = REG_DWORD;
	DWORD pDataSize = 0;

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
	{

		// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
		if (RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{

			if (pDataSize < 1 || pDataSize > sizeof(std::uint32_t))
			{
				return result;
			}

			std::uint32_t lpValue = 0;

			if (::RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &lpType, reinterpret_cast<BYTE *>(&lpValue), &pDataSize) == ERROR_SUCCESS)
			{
				result = lpValue;
				return result;
			}
		}
	}

	return result;
}

std::uint64_t hmc_registr_util::GetRegistrInt64(HKEY hKey, std::wstring FolderPath, std::wstring KeyName)
{
	std::uint64_t result = 0;

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExW(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) != ERROR_SUCCESS)
	{
		return result;
	}

	DWORD lpType = REG_QWORD;
	DWORD pDataSize = 0;

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
	{

		// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
		if (RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{

			if (pDataSize < 1 || pDataSize > sizeof(std::uint64_t))
			{
				return result;
			}

			std::uint64_t lpValue = 0;

			if (::RegQueryValueExW(open_hkey, KeyName.c_str(), nullptr, &lpType, reinterpret_cast<BYTE *>(&lpValue), &pDataSize) == ERROR_SUCCESS)
			{
				result = lpValue;
				return result;
			}
		}
	}

	return result;
}

std::uint64_t hmc_registr_util::GetRegistrInt64(HKEY hKey, std::string FolderPath, std::string KeyName)
{
	std::uint64_t result = 0;

	HKEY open_hkey = nullptr;
	_hmc_auto_free_HKey(open_hkey);

	if (::RegOpenKeyExA(hKey, FolderPath.c_str(), 0, KEY_ALL_ACCESS, &open_hkey) != ERROR_SUCCESS)
	{
		return result;
	}

	DWORD lpType = REG_QWORD;
	DWORD pDataSize = 0;

	// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
	if (RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
	{

		// 第一次调用 RegQueryValueEx 获取值的大小，放入 dataSize 变量中
		if (RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &lpType, nullptr, &pDataSize) == ERROR_SUCCESS)
		{

			if (pDataSize < 1 || pDataSize > sizeof(std::uint64_t))
			{
				return result;
			}

			std::uint64_t lpValue = 0;

			if (::RegQueryValueExA(open_hkey, KeyName.c_str(), nullptr, &lpType, reinterpret_cast<BYTE *>(&lpValue), &pDataSize) == ERROR_SUCCESS)
			{
				result = lpValue;
				return result;
			}
		}
	}

	return result;
}
