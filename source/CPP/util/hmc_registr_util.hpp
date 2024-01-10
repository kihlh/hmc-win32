#ifndef HMC_IMPORT_HMC_REGISTR_UTIL_H
#define HMC_IMPORT_HMC_REGISTR_UTIL_H 2.0

#include <windows.h>
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <type_traits>
// #include <ShlObj.h>
#include <memory>
#include <array>

#include "byte.hpp"

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

// 关闭注册表键
#define _hmc_auto_free_HKey(subHKey)                                \
	std::shared_ptr<void>##subHKey##_close_key(nullptr, [&](void *) \
											   {\
        if (subHKey != nullptr) {\
            ::RegCloseKey(subHKey);\
            subHKey = nullptr;\
        } });

namespace hmc_registr_util
{
	// 枚举键 ansi字符
	struct chQueryFolderKeyA
	{
		std::vector<std::string> key;
		std::vector<std::string> Folder;
		size_t size;
	};

	// 枚举键 wide字符
	struct chQueryFolderKeyW
	{
		std::vector<std::wstring> key;
		std::vector<std::wstring> Folder;
		size_t size;
	};

	enum REG_TYPE
	{
		_REG_NONE = 0,		// 没有类型
		_REG_SZ = 1,		// 以 nul 为结尾的文本
		_REG_EXPAND_SZ = 2, // 以 nul 为结尾的可扩展文本

		_REG_BINARY = 3,				   // 二进制
		_REG_DWORD = 4,					   // 32-bit number
		_REG_DWORD_LITTLE_ENDIAN = 4,	   // 32-bit number (same as REG_DWORD)
		_REG_DWORD_BIG_ENDIAN = 5,		   // 32-bit number
		_REG_LINK = 6,					   // Symbolic Link (unicode)
		_REG_MULTI_SZ = 7,				   // Multiple Unicode strings
		_REG_RESOURCE_LIST = 8,			   // Resource list in the resource map
		_REG_FULL_RESOURCE_DESCRIPTOR = 9, // Resource list in the hardware description
		_REG_RESOURCE_REQUIREMENTS_LIST = 10,
		_REG_QWORD = 11,			   // 64-bit number
		_REG_QWORD_LITTLE_ENDIAN = 11, // 64-bit number (same as REG_QWORD)
	};

	// 类型处理方法
	struct chType
	{
		DWORD type;				   // 类型
		std::string type_nameA();  // 获取类型的名称
		std::wstring type_nameW(); // 获取类型的名称

		bool type_name(std::string &output);  // 获取类型的名称
		bool type_name(std::wstring &output); // 获取类型的名称
		bool isInt64();						  // 符合int64特征 排除4比特(DWORD)  但是包含了bin 8比特
		bool isString();					  // 符合string类型 不会判断二进制
		bool isNumber();					  // 判断是否符合 int32 或者 int64
		bool isInt32();						  // 判断是否是int32 4比特  排除8比特(QWORD)  但是包含了bin 4比特
		bool isBuffer();					  // 判断是否是二进制类型
		bool diffType(DWORD type2);			  // 对比两个类型
	};

	// 低级数据存储体
	struct chValue : public chType
	{
		DWORD size;				 // 值的大小
		std::vector<BYTE> value; // 数据
		bool exists;			 // 此键是否存在
		// std::string getStringA(); //取值为string ([请注意]不会判断内容安全性)
		// std::wstring getStringW(); // 取值为utf16 ([请注意]不会判断内容安全性)
		std::uint16_t getInt16(); // 取值为int 16
		std::uint32_t getInt32(); // 取值为int
		std::uint64_t getInt64(); // 取值为 int64
	};

	// 获取目录信息
	struct chFolderInfo
	{
		DWORD size;		  // 此所有键总数量
		bool exists;	  // 此键是否存在
		DWORD folderSize; // 此目录键总数量
		DWORD keySize;	  // 此目录键总数量
		long long time;	  // 时间戳
	};

	// 枚举数据体 如果key是目录请勿调用type 因为他被作为目录键数量存储了
	struct chValueItme : public chType
	{
		DWORD size;				 // 值的大小
		HKEY root;				 // 根路径
		bool isFolder;			 // 是否是文件夹
		long long time;			 // 时间戳
		std::vector<BYTE> value; // 数据
		bool is_value;			 // 是否加入了数据

		// 区分出实际的内容

		chFolderInfo getFolderInfo(); // 转换成文件夹信息数据体
		chValue getValueInfo();		  // 转换成值信息数据体
	};

	// 遍历树结构的信息 ansi字符
	struct chValueItmeA : public chValueItme
	{
		std::string vkey;		// 值的名称
		std::string FolderPath; // 路径文件夹
	};

	// 遍历树结构的信息 wide字符
	struct chValueItmeW : public chValueItme
	{
		std::wstring vkey;		 // 值的名称
		std::wstring FolderPath; // 路径文件夹
	};

	// 获取值的信息
	struct chValueStat : public chType
	{
		// 此值大小
		DWORD size;
		// 此键是否存在
		bool exists;
	};

	/**
	 * @brief 对比两个注册表类型能否被隐式转换
	 *
	 * @param theType 实际类型
	 * @param targetType 强制转换为
	 * @return true
	 * @return false
	 */
	extern bool eq_target_type(DWORD theType, DWORD targetType);

	/**
	 * @brief 将类型转为文本名称
	 *
	 * @param theType
	 * @return std::string
	 */
	extern std::string type_nameA(DWORD theType);

	/**
	 * @brief 将类型转为文本名称
	 *
	 * @param theType
	 * @return std::string
	 */
	extern std::wstring type_nameW(DWORD theType);

	/**
	 * @brief 枚举注册表的同级key
	 *
	 * @param hKey 被打开的键
	 * @param QueryFolderList 目录key列表
	 * @param QueryKeyList 值key列表
	 */
	extern size_t getRegistrKeys(HKEY hKey, std::string path, std::vector<std::string> &QueryFolderList, std::vector<std::string> &QueryKeyList);

	/**
	 * @brief 枚举注册表的同级key
	 *
	 * @param hKey
	 * @param path
	 * @return chQueryFolderKeyW
	 */
	extern chQueryFolderKeyW getRegistrKeys(HKEY hKey, std::wstring path);

	/**
	 * @brief 枚举注册表的同级key
	 *
	 * @param hKey
	 * @param path
	 * @return chQueryFolderKeyA
	 */
	extern chQueryFolderKeyA getRegistrKeys(HKEY hKey, std::string path);

	/**
	 * @brief 枚举注册表的同级key
	 *
	 * @param hKey 被打开的键
	 * @param QueryFolderList 目录key列表
	 * @param QueryKeyList 值key列表
	 */
	extern size_t getRegistrKeys(HKEY hKey, std::wstring path, std::vector<std::wstring> &QueryFolderList, std::vector<std::wstring> &QueryKeyList);

	/**
	 * @brief 枚举注册表的同级key
	 *
	 * @param hKey 被打开的键
	 * @param QueryFolderList 目录key列表
	 * @param QueryKeyList 值key列表
	 */
	extern size_t getRegistrKeys(HKEY hKey, std::vector<std::wstring> &QueryFolderList, std::vector<std::wstring> &QueryKeyList);

	/**
	 * @brief 枚举注册表的同级key
	 *
	 * @param hKey 被打开的键
	 * @param QueryFolderList 目录key列表
	 * @param QueryKeyList 值key列表
	 */
	extern size_t getRegistrKeys(HKEY hKey, std::vector<std::string> &QueryFolderList, std::vector<std::string> &QueryKeyList);

	/**
	 * @brief 判断此值是否存在
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @param key 键名
	 * @return true
	 * @return false
	 */
	extern bool hasRegistrKey(HKEY hKey, std::string FolderPath, std::string key);

	/**
	 * @brief 判断此值是否存在
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @param key 键名
	 * @return true
	 * @return false
	 */
	extern bool hasRegistrKey(HKEY hKey, std::wstring FolderPath, std::wstring key);

	/**
	 * @brief 判断此值是否存在 [值]
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @param key 键名
	 * @return true
	 * @return false
	 */
	extern bool hasRegistrValue(HKEY hKey, std::string FolderPath, std::string key);

	/**
	 * @brief 判断此值是否存在 [值]
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @param key 键名
	 * @return true
	 * @return false
	 */
	extern bool hasRegistrValue(HKEY hKey, std::wstring FolderPath, std::wstring key);

	/**
	 * @brief 判断此目录是否存在
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @return true
	 * @return false
	 */
	extern bool hasRegistrFolder(HKEY hKey, std::string FolderPath);

	/**
	 * @brief 判断此目录是否存在
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @return true
	 * @return false
	 */
	extern bool hasRegistrFolder(HKEY hKey, std::wstring FolderPath);

	/**
	 * @brief 删除目录
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @return true
	 * @return false
	 */
	extern bool removeRegistrFolder(HKEY hKey, std::wstring FolderPath, std::wstring FolderName, bool tree = false);

	/**
	 * @brief 删除目录
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @return true
	 * @return false
	 */
	extern bool removeRegistrFolder(HKEY hKey, std::string FolderPath, std::string FolderName, bool tree = false);

	/**
	 * @brief 删除指定的键 [值] 键保留
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @param key 键名
	 * @return true
	 * @return false
	 */
	extern bool removeRegistrValue(HKEY hKey, std::string FolderPath, std::string key);

	/**
	 * @brief 删除指定的键 [值] 键保留
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @param key 键名
	 * @return true
	 * @return false
	 */
	extern bool removeRegistrValue(HKEY hKey, std::wstring FolderPath, std::wstring key);

	/**
	 * @brief 删除指定的键 [键]
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @param key 键名
	 * @return true
	 * @return false
	 */
	extern bool removeRegistrKey(HKEY hKey, std::string FolderPath, std::string key);

	/**
	 * @brief 删除指定的键 [键]
	 *
	 * @param hKey 根键
	 * @param FolderPath 目录路径
	 * @param key 键名
	 * @return true
	 * @return false
	 */
	extern bool removeRegistrKey(HKEY hKey, std::wstring FolderPath, std::wstring key);

	/**
	 * @brief 反HKEY解析 因为要和napi兼容
	 *
	 * @param hkey
	 * @return HKEY
	 */
	extern HKEY getHive(std::wstring hkey);

	/**
	 * @brief 反HKEY解析 因为要和napi兼容
	 *
	 * @param hkey
	 * @return HKEY
	 */
	extern HKEY getHive(std::string hkey);

	/**
	 * @brief 反HKEY解析 因为要和napi兼容
	 *
	 * @param hkey
	 * @return HKEY
	 */
	extern std::string getHiveA(HKEY hkey);

	/**
	 * @brief 反HKEY解析 因为要和napi兼容
	 *
	 * @param hkey
	 * @return HKEY
	 */
	extern std::wstring getHiveW(HKEY hkey);

	/**
	 * @brief 反HKEY解析 因为要和napi兼容
	 *
	 * @param hkey
	 * @return HKEY
	 */
	extern bool getHive(HKEY hkey, std::string &ptr_hkey);

	/**
	 * @brief 反HKEY解析 因为要和napi兼容
	 *
	 * @param hkey
	 * @return HKEY
	 */
	extern bool getHive(HKEY hkey, std::wstring &ptr_hkey);

	/**
	 * @brief 反HKEY解析 因为要和napi兼容
	 *
	 * @param hkey
	 * @return HKEY
	 */
	extern std::string getHive(HKEY hkey);

	/**
	 * @brief 获取值类型与值路径
	 *
	 * @param hKey 根
	 * @param path 路径
	 * @return true
	 * @return false
	 */
	extern chValueStat getValueStat(HKEY hKey, std::string subKey, std::string key);

	/**
	 * @brief 获取值类型与值路径
	 *
	 * @param hKey 根
	 * @param path 路径
	 * @return true
	 * @return false
	 */
	extern chValueStat getValueStat(HKEY hKey, std::wstring subKey, std::wstring key);

	/**
	 * @brief 获取值类型与值路径
	 *
	 * @param hKey 根
	 * @param path 路径
	 * @return true
	 * @return false
	 */
	extern chValueStat getValueStat(HKEY hKey, std::wstring key);

	/**
	 * @brief 获取值类型与值路径
	 *
	 * @param hKey 根
	 * @param path 路径
	 * @return true
	 * @return false
	 */
	extern chValueStat getValueStat(HKEY hKey, std::string key);

	/**
	 * @brief 创建文件夹
	 *
	 * @param hKey
	 * @param keyPath
	 * @return true
	 * @return false
	 */
	extern bool createRegistrFolder(HKEY hKey, std::string keyPath);

	/**
	 * @brief 创建文件夹
	 *
	 * @param hKey
	 * @param keyPath
	 * @return true
	 * @return false
	 */
	extern bool createRegistrFolder(HKEY hKey, std::wstring keyPath);

	/**
	 * @brief 复制指定的目录到指定目录
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool copyRegistrFolder(HKEY hKey, std::string sourcePath, std::string toPath);

	/**
	 * @brief 复制指定的目录到指定目录
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool copyRegistrFolder(HKEY hKey, std::wstring sourcePath, std::wstring toPath);

	/**
	 * @brief 复制指定的目录到指定目录
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool copyRegistrValue(HKEY hKey, std::string sourcePath, std::string sourceKey, std::string toPath, std::string toKey);

	/**
	 * @brief 复制指定的目录到指定目录
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool copyRegistrValue(HKEY hKey, std::wstring sourcePath, std::wstring sourceKey, std::wstring toPath, std::wstring toKey);

	/**
	 * @brief 删除注册表值树
	 *
	 * @param hKey
	 * @param subKey
	 * @return true
	 * @return false
	 */
	extern bool removeRegistrTree(HKEY hKey, std::string subKey, std::string DirName);

	/**
	 * @brief 删除注册表值树
	 *
	 * @param hKey
	 * @param subKey
	 * @return true
	 * @return false
	 */
	extern bool removeRegistrTree(HKEY hKey, std::wstring subKey, std::wstring DirName);

	/**
	 * @brief 将两个或者多个路径合并
	 *
	 * @tparam Args
	 * @param root 根
	 * @param Name1 join名称
	 * @param NameFlag 更多
	 * @return std::wstring
	 */
	extern std::wstring joinPath(std::wstring root, std::vector<std::wstring> NameList);

	/**
	 * @brief 将两个或者多个路径合并
	 *
	 * @tparam Args
	 * @param root 根
	 * @param Name1 join名称
	 * @param NameFlag 更多
	 * @return std::wstring
	 */
	extern std::string joinPath(std::string root, std::vector<std::string> NameList);

	/**
	 * @brief 获取同级所有数据体
	 *
	 * @param hKey
	 * @param subKey
	 * @return std::vector<chValueItmeA>
	 */
	extern std::vector<chValueItmeA> getRegistrValueItmeList(HKEY hKey, std::string subKey);

	/**
	 * @brief 获取同级所有数据体
	 *
	 * @param hKey
	 * @param subKey
	 * @return std::vector<chValueItmeA>
	 */
	extern std::vector<chValueItmeW> getRegistrValueItmeList(HKEY hKey, std::wstring subKey);

	/**
	 * @brief 获取值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern chValue GetRegistrSourceValue(HKEY hKey, std::wstring FolderPath, std::wstring KeyName);

	/**
	 * @brief 获取值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern chValue GetRegistrSourceValue(HKEY hKey, std::string FolderPath, std::string KeyName);

	/**
	 * @brief 获取值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern chValue GetRegistrSourceValue(HKEY hKey, std::string KeyName);

	/**
	 * @brief 获取值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern chValue GetRegistrSourceValue(HKEY hKey, std::wstring KeyName);

	/**
	 * @brief 获取值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrSourceValue(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, chValue Value);

	/**
	 * @brief 设置值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrSourceValue(HKEY hKey, std::string FolderPath, std::string KeyName, chValue Value);

	/**
	 * @brief 设置值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrSourceValue(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, DWORD type, const std::vector<BYTE> &value);

	/**
	 * @brief 设置值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrSourceValue(HKEY hKey, std::string FolderPath, std::string KeyName, DWORD type, const std::vector<BYTE> &value);

	/**
	 * @brief 设置值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrSourceValue(HKEY hKey, std::wstring KeyName, DWORD type, const std::vector<BYTE> &value);

	/**
	 * @brief 设置值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrSourceValue(HKEY hKey, std::string KeyName, DWORD type, const std::vector<BYTE> &value);

	/**
	 * @brief 获取值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrSourceValue(HKEY hKey, std::wstring KeyName, chValue Value);

	/**
	 * @brief 设置值 低级的二进制值
	 *
	 * @param hKey
	 * @param sourcePath
	 * @param toPath
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrSourceValue(HKEY hKey, std::string KeyName, chValue Value);

	/**
	 * @brief 获取出目录信息
	 *
	 * @param hKey
	 * @param FolderPath
	 * @return chFolderInfo
	 */
	extern chFolderInfo getRegistrFolderInfo(HKEY hKey, std::string FolderPath);

	/**
	 * @brief 获取出目录信息
	 *
	 * @param hKey
	 * @param FolderPath
	 * @return chFolderInfo
	 */
	extern chFolderInfo getRegistrFolderInfo(HKEY hKey, std::wstring FolderPath);
	// 获取文本数组REG_MULTI_SZ
	extern std::vector<std::wstring> GetRegistrMulti(HKEY hKey, std::wstring FolderPath, std::wstring KeyName);
	// 获取文本数组REG_MULTI_SZ
	extern std::vector<std::string> GetRegistrMulti(HKEY hKey, std::string FolderPath, std::string KeyName);
	/**
	 * @brief 获取文本
	 *
	 * @param hKey 根
	 * @param FolderPath 目录
	 * @param KeyName 键
	 * @param expand 是否转义
	 * @return std::wstring
	 */
	extern std::wstring GetRegistrString(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, bool expand);
	/**
	 * @brief 获取文本
	 *
	 * @param hKey 根
	 * @param FolderPath 目录
	 * @param KeyName 键
	 * @param expand 是否转义
	 * @return std::string
	 */
	extern std::string GetRegistrString(HKEY hKey, std::string FolderPath, std::string KeyName, bool expand);
	// 获取 REG_DWORD
	extern std::uint32_t GetRegistrInt32(HKEY hKey, std::wstring FolderPath, std::wstring KeyName);
	// 获取 REG_DWORD
	extern std::uint32_t GetRegistrInt32(HKEY hKey, std::string FolderPath, std::string KeyName);
	// 获取 REG_QWORD
	extern std::uint64_t GetRegistrInt64(HKEY hKey, std::wstring FolderPath, std::wstring KeyName);
	// 获取 REG_QWORD
	extern std::uint64_t GetRegistrInt64(HKEY hKey, std::string FolderPath, std::string KeyName);
	/**
	 * @brief 设置文本值
	 *
	 * @param hKey 根
	 * @param FolderPath 目录
	 * @param KeyName 键
	 * @param Input 内容
	 * @param expand 是否转义
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrString(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, const std::wstring &Input, const DWORD retype = 0);
	/**
	 * @brief 设置文本值
	 *
	 * @param hKey 根
	 * @param FolderPath 目录
	 * @param KeyName 键
	 * @param Input 内容
	 * @param expand 是否转义
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrString(HKEY hKey, std::string FolderPath, std::string KeyName, const std::string &Input, const DWORD retype = 0);
	/**
	 * @brief 设置文本值
	 *
	 * @param hKey 根
	 * @param FolderPath 目录
	 * @param KeyName 键
	 * @param Input 内容
	 * @param expand 是否转义
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrString(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, const std::wstring &Input, bool expand = false);
	/**
	 * @brief 设置文本值
	 *
	 * @param hKey 根
	 * @param FolderPath 目录
	 * @param KeyName 键
	 * @param Input 内容
	 * @param expand 是否转义
	 * @return true
	 * @return false
	 */
	extern bool SetRegistrString(HKEY hKey, std::string FolderPath, std::string KeyName, const std::string &Input, bool expand = false);
	// 设置文本数组REG_MULTI_SZ
	extern bool SetRegistrMulti(HKEY hKey, std::string FolderPath, std::string KeyName, const std::vector<std::string> &Input);
	// 设置文本数组REG_MULTI_SZ
	extern bool SetRegistrMulti(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, const std::vector<std::wstring> &Input);
	// 设置数字值 REG_DWORD
	extern bool SetRegistrInt32(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, const std::uint32_t &Input);
	// 设置数字值 REG_DWORD
	extern bool SetRegistrInt32(HKEY hKey, std::string FolderPath, std::string KeyName, const std::uint32_t &Input);
	// 设置数字值 REG_QWORD
	extern bool SetRegistrInt64(HKEY hKey, std::string FolderPath, std::string KeyName, const std::uint64_t &Input);
	// 设置数字值 REG_QWORD
	extern bool SetRegistrInt64(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, const std::uint64_t &Input);

	// 仅处理值打开
	class RegistrValueUtil
	{
	protected:
		~RegistrValueUtil();

		// RegistrValueUtil(HKEY hKey, std::wstring subKey, std::wstring Name);
		// RegistrValueUtil(HKEY hKey, std::string subKey, std::string Name);

		HKEY open_hkey = nullptr;

		std::wstring subKeyW;
		std::wstring NameW;
		std::string subKeyA;
		std::string NameA;
		bool is_wide = false;
		bool _is_ready = false;
		bool _is_dir = false;
		HKEY root_hKey = nullptr;

		std::string utf16_to_ansi(const std::wstring input);
		std::wstring ansi_to_utf16(const std::string input);

		bool is_ready();
	};

	class setRegistrValue : public RegistrValueUtil
	{
	private:
		/*    HKEY open_hkey = nullptr;

			std::wstring subKeyW;
			std::wstring NameW;
			std::string subKeyA;
			std::string NameA;
			bool is_wide = false;
			bool _is_ready = false;
			HKEY root_hKey = nullptr;*/

	public:
		setRegistrValue(HKEY hKey, std::wstring subKey, std::wstring Name);
		setRegistrValue(HKEY hKey, std::string subKey, std::string Name);

		// 0x00000000 REG_NONE 未定义
		bool set(/*REG_NONE*/);
		// 0x0000000B REG_QWORD 64 位数字
		bool set(int64_t number, REG_TYPE type = REG_TYPE::_REG_QWORD);
		// 0x00000004 REG_DWORD / REG_DWORD_LITTLE_ENDIAN 32 位数字
		bool set(long number /*REG_DWORD*/, REG_TYPE type = REG_TYPE::_REG_DWORD);
		// 0x00000001 REG_SZ 字符串 or 0x00000002 REG_EXPAND_SZ 未展开引用的字符串 例如“%PATH%”
		bool set(std::wstring input, bool expand = false);
		// 0x00000001 REG_SZ 字符串 or 0x00000002 REG_EXPAND_SZ 未展开引用的字符串 例如“%PATH%”
		bool set(std::string input, bool expand = false);
		// 7 REG_MULTI_SZ 文本数组
		bool set(/*REG_MULTI_SZ*/ const std::vector<std::wstring> &input);
		// 7 REG_MULTI_SZ 文本数组
		bool set(/*REG_MULTI_SZ*/ const std::vector<std::string> &input);

		bool set(REG_TYPE type, const std::vector<BYTE> &value);
		bool set(DWORD type, const std::vector<BYTE> &value);
	};

	class getRegistrValue : public RegistrValueUtil
	{
	private:
	public:
		getRegistrValue(HKEY hKey, std::wstring subKey, std::wstring Name);
		getRegistrValue(HKEY hKey, std::string subKey, std::string Name);

		std::vector<BYTE> getBuff();
		int32_t getInt32();
		int64_t getInt64();
		HWND getHwnd();
		std::vector<std::wstring> getMultiW();
		std::vector<std::string> getMultiA();
		std::wstring getStringW(bool expand = false);
		std::string getStringA(bool expand = false);
		bool isValue();
		bool isString();
		bool isNumber();
		bool isInt64();
		bool isType(DWORD type);
		DWORD getType();
	};

	class OpenKeyToken
	{
	public:
		OpenKeyToken(HKEY hKey, std::wstring FolderPath, std::wstring KeyName, bool CreateNotKey = false);
		OpenKeyToken(HKEY hKey, std::string FolderPath, std::string KeyName, bool CreateNotKey = false);
		~OpenKeyToken();
		HKEY token = nullptr;
		LSTATUS status = ERROR_SUCCESS;
		// if
		operator bool() const;
		// &
		operator HKEY() const;
		// !
		bool operator!() const;

	private:
	};

}

#endif // HMC_IMPORT_HMC_REGISTR_UTIL_H