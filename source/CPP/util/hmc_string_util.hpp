#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_STRING_UTIL_HPP
#define MODE_INTERNAL_INCLUDE_HMC_STRING_UTIL_HPP

#include <string>
#include <vector>
#include <windows.h>
#include <crtdbg.h> // For _ASSERTE()
#include <iomanip>
#include <map>
#include <any>
#include <sstream>
#include <tuple>
#include <limits>	 // For numeric_limits
#include <stdexcept> // For overflow_error
#include <winternl.h>

// using namespace std;

// 自动释放dll
#define hmc_shared_close_Library(hModule) std::shared_ptr<void>##hModule##_shared_close_Library_(nullptr, [&](void *) {if (hModule != NULL) {::FreeLibrary(hModule);} });
// 自动释放文本
#define hmc_shared_close_lpsz(lpwsz) std::shared_ptr<void>##lpwsz##_shared_close_lpsz_(nullptr, [&](void *) {if (lpwsz != NULL) {::GlobalFree(lpwsz);lpwsz = 0; } });
// 释放进程句柄
#define hmc_shared_close_handle(handle) std::shared_ptr<void>##lpwsz##_shared_free_handle(nullptr, [&](void *) {if (handle != NULL) { try{::CloseHandle(handle);}catch(...){}} });

// 开辟内存 (请注意需要调用 FreeVS 或者 hmc_FreeVSAuto 释放)
// -> LPSTR pszMem = AllocVS(LPSTR, leng + 1);
#define hmc_AllocVS(Type, leng) \
	(Type)::VirtualAlloc((LPVOID)NULL, (DWORD)(leng), MEM_COMMIT, PAGE_READWRITE);

// 释放空间
// -> LPSTR pszMem = hmc_AllocVS(LPSTR, leng + 1);
// -> FreeVS(pszMem);
#define hmc_FreeVS(Virtua) \
	if (Virtua != NULL)    \
		::VirtualFree(Virtua, 0, MEM_RELEASE);

// 释放空间
// -> LPSTR pszMem = hmc_AllocVS(LPSTR, leng + 1);
// -> FreeVSAuto(pszMem);
#define hmc_FreeVSAuto(Virtua) \
	std::shared_ptr<void>##Virtua##_shared_close_FreeVSAuto_(nullptr, [&](void *) {if (Virtua != NULL) {::VirtualFree(Virtua, 0, MEM_RELEASE);} });

// 开辟内存
#define hmc_AllocHeap(variable) ::HeapAlloc(::GetProcessHeap(), 0, (variable))
// 释放内存
#define hmc_FreeHeap(variable) ::HeapFree(::GetProcessHeap(), 0, (variable))

// 让代码在异步线程中执行
#define hmc_Thread (code) std::thread([]() -> void { code }).detach();

#define hmc_Catch                                                                                  \
	catch (char *e) { std::cout << "ERROR:"                                                        \
								<< "<" << __FUNCSIG__ << " @ " << __LINE__ << "> " << e << "\n"; } \
	catch (const std::exception &ex)                                                               \
	{                                                                                              \
		std::cout << "exception:"                                                                  \
				  << "<" << __FUNCSIG__ << " @ " << __LINE__ << "> " << ex.what() << "\n";         \
	}                                                                                              \
	catch (...) { std::cout << "ERROR:"                                                            \
							<< "<" << __FUNCSIG__ << " @ " << __LINE__ << "> "                     \
							<< "unknown"                                                           \
							<< "\n"; };

namespace hmc_string_util
{

#define ___hmc_string_util_eq(types) (input.type() == typeid(types) ? true : false)
#define ___hmc_string_util_eqt(types) (input.type() == types ? true : false)
#define ___hmc_string_util_diff_any_value_eval_map_to_fn_map(any_value, fn_name, map_type, key_type, value_type) \
	if (any_value.type() == typeid(map_type<key_type, value_type>))                                              \
	{                                                                                                            \
		return fn_name(std::any_cast<map_type<key_type, value_type>>(any_value));                                \
	}                                                                                                            \
	if (any_value.type() == typeid(map_type<value_type, key_type>))                                              \
	{                                                                                                            \
		return fn_name(std::any_cast<map_type<value_type, key_type>>(any_value));                                \
	}

	/**
	 * @brief 获取路径的文件名
	 *
	 * @param path
	 * @return std::wstring
	 */
	extern std::wstring getPathBaseName(const std::wstring &path);

	/**
	 * @brief 获取路径的文件名
	 *
	 * @param path
	 * @return std::wstring
	 */
	extern std::string getPathBaseName(const std::string &path);

	// ----------------------------------------------------------------
	// W2U8
	// utf 16 to utf8 encoding
	// utf16(win 标准) 转 utf8 字符(win 标准)
	// ----------------------------------------------------------------
	extern std::string utf16_to_utf8(const std::wstring utf16);

	// ----------------------------------------------------------------
	// U82W
	// utf 8 to utf16 encoding
	// utf8(win 标准) 转 utf16 字符(win 标准)
	// ----------------------------------------------------------------

	extern std::wstring utf8_to_utf16(const std::string utf8);

	// ----------------------------------------------------------------
	// W2A
	// utf 16 to Local CP_ACP ( Ansi [A] ) encoding
	// utf16(win 标准[W]) 转 winapi A字符
	// ----------------------------------------------------------------
	extern std::string utf16_to_ansi(const std::wstring utf16);

	// ----------------------------------------------------------------
	// A2W
	// Local CP_ACP ( Ansi [A] ) to utf16 encoding
	// winapi A字符 转 utf16(win 标准[W])
	// ----------------------------------------------------------------
	extern std::wstring ansi_to_utf16(const std::string ansi);

	// ----------------------------------------------------------------
	// A2U8
	// Local CP_ACP ( Ansi [A] ) to utf8 encoding
	// winapi A字符 转 utf8(win 标准[W])
	// ? 推荐w字符(utf16) 损耗更少一点 napi支持直接返回utf16
	// ----------------------------------------------------------------
	extern std::string ansi_to_utf8(const std::string ansi);

	// ----------------------------------------------------------------
	// U82A
	// utf8 to Local CP_ACP ( Ansi [A] ) encoding
	// utf8 字符 转 winapi A字符
	// ? 推荐w字符(utf16) 损耗更少一点 napi支持直接返回utf16
	// ----------------------------------------------------------------
	extern std::string utf8_to_ansi(const std::string utf8);
	// UFT8 字符转为GBK(中文)
	extern std::string utf8_to_gbk(std::string u8str);

	extern std::vector<std::wstring> ansi_to_utf16(std::vector<std::string> item_list);
	extern std::vector<std::string> utf16_to_ansi(std::vector<std::wstring> item_list);
	extern std::map<std::wstring, std::wstring> ansi_to_utf16(std::map<std::string, std::string> item_list);
	extern std::map<std::string, std::string> utf16_to_ansi(std::map<std::wstring, std::wstring> item_list);
	// 判断此文本是否符合utf8特征
	extern bool is_utf8(const std::string input);
	// 文本中是否有数字 并且是否是安全的 int32
	extern bool is_int_str(const std::string Value);
	// 文本中是否有数字 并且是否是安全的 long
	extern bool is_long_str(const std::string Value);
	// 文本中是否有数字 并且是否是安全的 long long
	extern bool is_longlong_str(const std::string Value);

	// 拼接文本
	extern std::wstring join(std::vector<std::wstring> &item_list);
	extern std::wstring join(std::vector<std::wstring> &item_list, std::wstring splitter);
	extern void join(std::vector<std::wstring> &item_list, std::wstring splitter, std::wstring outputPtr);
	extern std::string join(std::vector<std::string> &item_list);
	extern std::string join(std::vector<std::string> &item_list, std::string splitter);
	extern void join(std::vector<std::string> &item_list, std::string splitter, std::string outputPtr);
	/**
	 * @brief 仅拼接文本
	 *
	 * @tparam Arguments
	 * @param input
	 * @param firstInput
	 * @param data_list
	 * @return string
	 */
	template <class... Arguments>
	extern std::string string_join(const std::string &input, const std::string &firstInput, std::vector<Arguments...> data_list);
	/**
	 * @brief 仅拼接文本
	 *
	 * @tparam Arguments
	 * @param input
	 * @param firstInput
	 * @param data_list
	 * @return wstring
	 */
	template <class... Arguments>
	extern std::wstring string_join(const std::wstring &input, const std::wstring &firstInput, std::vector<Arguments...> data_list);

	// 分割文本
	extern std::vector<std::wstring> split(std::wstring &sourcePtr, wchar_t splitter);
	extern void split(std::wstring &sourcePtr, wchar_t splitter, std::vector<std::wstring> &item_list);
	extern std::vector<std::string> split(std::string &sourcePtr, char splitter);
	extern void split(std::string &sourcePtr, char splitter, std::vector<std::string> &item_list);

	// 转义json文本
	extern std::wstring escapeJsonString(const std::wstring &input, bool is_to_value = false);
	extern std::string escapeJsonString(const std::string &input, bool is_to_value = false);

	// 替换单次
	extern void replace(std::wstring &sourcePtr, const std::wstring from, const std::wstring to);
	extern void replace(std::string &sourcePtr, std::string from, std::string to);
	extern void replace(std::string &sourcePtr, std::vector<std::tuple<std::string, std::string>> list);
	extern void replace(std::wstring &sourcePtr, std::vector<std::tuple<std::wstring, std::wstring>> list);

	/**
	 * @brief 替换指定内容 在第N次出现的时候(仅本次)
	 *
	 * @param sourcePtr 源文本
	 * @param from 搜索
	 * @param bubble_index 冒泡索引次数
	 * @param to 到新文本
	 */
	extern void replace(std::string &sourcePtr, std::string from, size_t bubble_index, std::string to);

	// 替换全部
	extern void replaceAll(std::wstring &sourcePtr, const std::wstring from, const std::wstring to);
	extern void replaceAll(std::string &sourcePtr, std::string from, std::string to);
	extern void replaceAll(std::string &sourcePtr, std::vector<std::tuple<std::string, std::string>> list);
	extern void replaceAll(std::wstring &sourcePtr, std::vector<std::tuple<std::wstring, std::wstring>> list);

	// 移除尾部 为xx 的指定文本
	extern std::string trimLast(const std::string &input, const std::string &match);
	// 移除开头和尾部 为xx 的指定文本
	extern std::string trim(const std::string &input, const std::string &match);
	// 移除开头为xx 的指定文本
	extern std::string trimFirst(const std::string &input, const std::string &match);
	// 移除尾部 为xx 的指定文本
	extern std::wstring trim(const std::wstring &input, const std::wstring &match);
	// 移除开头和尾部 为xx 的指定文本
	extern std::wstring trimLast(const std::wstring &input, const std::wstring &match);
	// 移除开头为xx 的指定文本
	extern std::wstring trimFirst(const std::wstring &input, const std::wstring &match);

	// 移除尾部 为xx 的指定文本
	extern std::string trimLastAll(const std::string &input, const std::string &match);
	// 移除开头和尾部 为xx 的指定文本
	extern std::string trimAll(const std::string &input, const std::string &match);
	// 移除开头为xx 的指定文本
	extern std::string trimFirstAll(const std::string &input, const std::string &match);
	// 移除尾部 为xx 的指定文本
	extern std::wstring trimAll(const std::wstring &input, const std::wstring &match);
	// 移除开头和尾部 为xx 的指定文本
	extern std::wstring trimLastAll(const std::wstring &input, const std::wstring &match);
	// 移除开头为xx 的指定文本
	extern std::wstring trimFirstAll(const std::wstring &input, const std::wstring &match);

	// 反特殊字符序列化
	extern void unEscapeJsonString(std::string &sourcePtr);
	// 反特殊字符序列化
	extern void unEscapeJsonString(std::wstring &sourcePtr);

	// c数组转json

	/**
	 * @brief c内容数组转为json的array文本
	 *
	 * @tparam PtrT string or wstring
	 * @tparam T
	 * - string
	 * - char *
	 * - int
	 * - float
	 * - bool
	 * @param stringPtr
	 * @param data_list
	 */
	template <class PtrT, class T>
	extern void vec_to_array_json(PtrT &stringPtr, const std::vector<T> &data_list);
	/**
	 * @brief 一个空的json 数组文本
	 *
	 * @return string
	 */
	extern std::string vec_to_array_json();
	/**
	 * @brief cpp内容数组转为json的array文本
	 *
	 * @tparam T
	 * @param data_list
	 * @return string
	 */
	extern std::wstring vec_to_array_json(std::vector<std::wstring> item_list);

	/**
	 * @brief cpp内容数组转为json的array文本
	 *
	 * @tparam T
	 * @param data_list
	 * @return string
	 */
	extern std::string vec_to_array_jsonA(std::vector<std::string> item_list);

	/**
	 * @brief cpp内容数组转为json的array文本
	 *
	 * @tparam T
	 * @param data_list
	 * @return string
	 */
	template <class T>
	extern std::string vec_to_array_json_any(const std::vector<T> data_list);

	extern std::string vec_to_array_json(const std::vector<char> data_list);
	extern std::string vec_to_array_json(const std::vector<double> data_list);
	extern std::string vec_to_array_json(const std::vector<long double> data_list);
	extern std::string vec_to_array_json(const std::vector<short> data_list);
	extern std::string vec_to_array_json(const std::vector<long> data_list);
	extern std::string vec_to_array_json(const std::vector<int> data_list);
	extern std::string vec_to_array_json(const std::vector<unsigned long long> data_list);
	extern std::string vec_to_array_json(const std::vector<unsigned int> data_list);
	extern std::string vec_to_array_json(const std::vector<unsigned char> data_list);
	extern std::string vec_to_array_json(const std::vector<unsigned long> data_list);
	extern std::string vec_to_array_json(std::vector<std::string> item_list);

	/**
	 * @brief c内容转为json的value
	 *
	 * @tparam T
	 * @param value
	 * @return string
	 */
	template <class T, class V>
	extern std::string to_json_value(T &value);

	/**
	 * @brief map 容器转为 json object
	 *
	 * @tparam KEY
	 * @tparam V
	 * @param item_list
	 * @return wstring
	 */
	template <class KEY, class V>
	extern std::wstring map_to_jsonW(std::map<KEY, V> item_list);

	/**
	 * @brief map 容器转为 json object
	 *
	 * @tparam KEY
	 * @tparam V
	 * @param item_list
	 * @return string
	 */
	template <class KEY, class V>
	extern std::string map_to_jsonA(std::map<KEY, V> item_list);
	// 大写
	extern std::string text_to_upper(std::string data);
	// 大写
	extern std::wstring text_to_upper(std::wstring data);
	// 小写
	extern std::string text_to_lower(std::string data);
	// 小写
	extern std::wstring text_to_lower(std::wstring data);
	/**
	 * @brief 文本转为严格的文本指针
	 *
	 * @param input
	 * @param psize
	 * @return LPWSTR
	 */
	extern LPWSTR string_to_lpstr(std::wstring input);

	/**
	 * @brief 文本转为严格的文本指针
	 *
	 * @param input
	 * @param psize
	 * @return LPWSTR
	 */
	extern LPCSTR string_to_lpstr(std::string input);

	/**
	 * @brief 文本转为严格的文本指针 (以\0结尾)
	 *
	 * @param input
	 * @param psize
	 * @return LPWSTR
	 */
	extern LPWSTR string_to_lpstr(std::wstring input, size_t &psize);

	/**
	 * @brief 文本转为严格的 C文本指针 (以\0结尾)
	 *
	 * @param input
	 * @param psize
	 * @return LPWSTR
	 */
	extern LPCSTR string_to_lpstr(std::string input, size_t &psize);

	/**
	 * @brief 从指针获取文本到string容器
	 *
	 * @param input 文本的指针
	 * @param nBufSize 当前文本指针有多大
	 * @param earlyTruncation 允许提前遇到 `\0` 时候截断
	 * @return wstring
	 */
	extern std::wstring lpstr_to_string(LPWSTR input, int nBufSize, bool earlyTruncation = false);
	/**
	 * @brief 从指针获取文本到string容器
	 *
	 * @param input 文本的指针
	 * @param nBufSize 当前文本指针有多大
	 * @param earlyTruncation 允许提前遇到 `\0` 时候截断
	 * @return string
	 */
	extern std::string lpstr_to_string(LPSTR input, int nBufSize, bool earlyTruncation = false);
	/**
	 * @brief 从指针获取文本到string容器
	 *
	 * @param input 文本的指针 以`\0`结尾
	 * @return wstring
	 */
	extern std::wstring lpstr_to_string(LPWSTR input);
	/**
	 * @brief 从指针获取文本到string容器
	 *
	 * @param input 文本的指针 以`\0`结尾
	 * @return string
	 */
	extern std::string lpstr_to_string(LPSTR input);

	/**
	 * @brief 删除 string 容器内部的开头与结尾 或全部 的 \0
	 *
	 * @param str
	 * @return std::string
	 */
	extern std::string removeNullCharacters(std::string str, bool start = true, bool tail = true, bool all = false);

	/**
	 * @brief 删除 string 容器内部的开头与结尾 或全部 的 \0
	 *
	 * @param str
	 * @return std::wstring
	 */
	extern std::wstring removeNullCharacters(std::wstring str, bool start = true, bool tail = true, bool all = false);

	/**
	 * @brief 删除 string 容器内部的全部 的 \0
	 *
	 * @param str
	 * @return std::string
	 */
	extern std::string removeNullCharactersAll(std::string str);

	/**
	 * @brief 删除 string 容器内部全部 的 \0
	 *
	 * @param str
	 * @return std::wstring
	 */
	extern std::wstring removeNullCharactersAll(std::wstring str);

	extern std::wstring unicodeStringToWString(UNICODE_STRING unicodeString);

	// 删除空白字符
	extern std::string StripSpaces(const std::string &str);
	// 删除空白字符
	extern std::wstring StripSpaces(const std::wstring &str);
#if _HAS_CXX17
	/**
	 * @brief 判断这个vec是否可以被 hmc string 工具转换到json
	 *
	 * @param input
	 * @return true
	 * @return false
	 */
	extern bool is_vec_json(std::any input);
	/**
	 * @brief 判断这个map是否是整数型
	 *
	 * @param input
	 * @return true
	 * @return false
	 */
	extern bool is_int(std::any input);
	/**
	 * @brief 判断这个map是否可以被 hmc string 工具转换到json
	 *
	 * @param input
	 * @return true
	 * @return false
	 */
	extern bool is_map_json(std::any input);
	/**
	 * @brief 尝试将any转换到string
	 *
	 * @param input 输入
	 * @param output 输出 wstring / string
	 * @return true
	 * @return false
	 */
	extern bool any_to_string(std::any input, std::string &output);
	/**
	 * @brief 尝试将any转换到string
	 *
	 * @param input 输入
	 * @param output 输出 wstring / string
	 * @return true
	 * @return false
	 */
	extern bool any_to_string(std::any input, std::wstring &output);
	/**
	 * @brief any map 容器转为 json object
	 *
	 * @tparam KEY
	 * @tparam V
	 * @param item_list
	 * @return string
	 */
	extern std::string map_to_jsonA(std::any item_list);
	/**
	 * @brief any map 容器转为 json object
	 *
	 * @tparam KEY
	 * @tparam V
	 * @param item_list
	 * @return string
	 */
	extern std::wstring map_to_jsonW(std::any item_list);
	extern std::wstring push_json_value(std::wstring key, std::any value, bool is_append = false, bool esp_type = true);

#endif //_HAS_CXX17
};

#endif // MODE_INTERNAL_INCLUDE_HMC_STRING_UTIL_HPP