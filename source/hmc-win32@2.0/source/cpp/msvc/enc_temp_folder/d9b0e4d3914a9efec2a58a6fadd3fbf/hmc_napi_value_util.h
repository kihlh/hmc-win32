#pragma once

//  导入模块之前必须已经导入 node_api.h

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_NAPI_VALUE_UTIL_HPP
#define MODE_INTERNAL_INCLUDE_HMC_NAPI_VALUE_UTIL_HPP

#define NAPI_EXPERIMENTAL
#include "node/node_api.h"

#include <atomic>
#include <windows.h>
#include <assert.h>
#include <any>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <functional>
#include <unordered_map>
#include <thread>
#include <shared_mutex>
#include <variant>

#include "hmc_string_util.h"
#include "hmc_util.h"

#if defined(__x86_64__) || defined(_M_X64)
const size_t BIT_2GB = 8589934592ull;
#elif defined(__i386__) || defined(_M_IX86)
const size_t BIT_2GB = 8589934592ui32;
#endif

#ifdef _WIN64
// 如果发现无法找到静态文件可以测试以下方法(其中一种)
// 1. 将路径替换为绝对的路径(d:/SharedLibrary/node_x64.lib)
// 2. 在vs属性页中配置 VC++目录 ->常规->库目录 ($(静态模块位置)/SharedLibrary)
// 3. 在vs属性页中配置 链接器->常规->附加库目录($(静态模块位置)/SharedLibrary)
#pragma comment(lib, "node_x64.lib")
#else
#pragma comment(lib, "node_x86.lib")
#endif

#define NAME_STR(func) #func

// 导出一个 static 函数
#define EXPORT_NAPI_STATIC_FN(func) \
	{                               \
		#func, 0, func, 0, 0, 0, napi_default, 0}
// 导出一个 static 函数
#define EXPORT_NAPI_STATIC_PAIR(name, func) \
	{                                       \
		name, 0, func, 0, 0, 0, napi_default, 0}

// 导出一个 其他文件的 函数
#define EXPORT_NAPI_REMOTE_FN(func) \
	{                               \
		#func, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0}

// 导出一个 其他文件的 函数 并设置名称
#define EXPORT_NAPI_REMOTE_FNPAIR(name, func) \
	{                                         \
		name, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0}
#define as_Number(data) hmc_napi_create_value::Number(env, (int64_t)data)
// 必须是utf8
#define as_String(data) hmc_napi_create_value::String(env, data)
#define as_Boolean(data) hmc_napi_create_value::Boolean(env, data)
#define as_Null() hmc_napi_create_value::Null(env)
#define as_Bigint(data) hmc_napi_create_value::Bigint(env, (long long)data)
#define as_Numberf(data) hmc_napi_create_value::Number(env, (double)data)
#define as_Buffer(data) hmc_napi_create_value::Buffer(env, data)
#define as_StringA(data) hmc_napi_create_value::StringA(env, data)
#define as_Number32(data) hmc_napi_create_value::Number(env, (int)data)
#define as_ArrayNul() hmc_napi_create_value::Array::Number(env, std::vector<int>())

#define as_ExFunction(func) hmc_napi_create_value::ExFunction(env, #func, func)
#define as_ExFunctionNameAp(func) #func, hmc_napi_create_value::ExFunction(env, #func, func)

#define at_Boolean(index) (input.exists(index) ? input.getBool(index, false) : false)
#define at_StringW(index) (input.exists(index) ? input.getStringWide(index, L"") : L"")
#define at_Number32(index) (input.exists(index) ? input.getInt(index, 0) : 0)
#define at_Number64(index) (input.exists(index) ? input.getInt64(index, 0) : 0)

#define at_BooleanOr(index, or_value) (input.exists(index) ? input.getBool(index, or_value) : or_value)
#define at_StringWOr(index, or_value) (input.exists(index) ? input.getStringWide(index, or_value) : or_value)
#define at_Number32Or(index, or_value) (input.exists(index) ? input.getInt(index, or_value) : or_value)
#define at_Number64Or(index, or_value) (input.exists(index) ? input.getInt64(index, or_value) : or_value)

typedef enum
{
	// ES6 types (corresponds to typeof)
	js_undefined = napi_undefined,
	js_null = napi_null,
	js_boolean = napi_boolean,
	js_number = napi_number,
	js_string = napi_string,
	js_symbol = napi_symbol,
	js_object = napi_object,
	js_function = napi_function,
	js_external = napi_external,
	js_bigint = napi_bigint,
	js_array = 95270,
	js_date = 95271,
	js_error = 95272,
	js_buffer = 95273,
	// js_point = 95277,
	// js_array_string = 95279,
	// js_array_number = 95281,
	// js_array_boolean = 95282,
	// js_array_bigint = 95283,
	js_promise = 95285,
	js_promise_function = 95286,
	// js_rect = 95288,
	js_unknown = 955666,
	// js_array_any = 95290,
} js_valuetype;

typedef std::variant<std::wstring, std::string, std::vector<std::wstring>, std::vector<std::string>> STR_VARIANT_VALUE;

typedef std::variant<
	std::monostate,
	std::wstring,
	std::string,
	bool,
	std::vector<std::wstring>,
	std::vector<std::string>,
	std::vector<int64_t>,
	int,
	long long,
	unsigned long long,
	std::vector<uint8_t>,
	long double,
	std::vector<int>,
	std::vector<unsigned long long>,
	// any 只允许存放 std::vector<js_variant_value>  std::map<std::string,js_variant_value>   std::map<std::wstring,js_variant_value>
	std::pair<js_valuetype, std::any>>
	js_variant_value;

namespace hmc_napi_get_value
{
	/**
	 * @brief 仅能取值支持以下值
	 * @param type `vector<wstring>` `vector<int64_t>` `int64_t` `wstring` `vector<uint8_t>` `bool` `Array<wstring>`
	 *
	 * @param env
	 * @param nodeValue
	 * @return js_variant_value
	 */
	extern js_variant_value get_variant(napi_env env, napi_value nodeValue);

	extern std::map<std::wstring, js_variant_value> get_object_variant_utf16(napi_env env, napi_value nodeValue);

	extern std::map<std::string, js_variant_value> get_object_variant_utf8(napi_env env, napi_value nodeValue);

	extern std::vector<js_variant_value> get_array_variant(napi_env env, napi_value nodeValue);

	extern std::vector<js_variant_value> get_array_variant(napi_env env, const std::vector<napi_value> nodeValueList);

	/**
	 * @brief 数字转int
	 *
	 * @param env
	 * @param nodeValue
	 * @return int
	 */
	extern int number_int(napi_env env, napi_value nodeValue, int defaultValue = 0);
	/**
	 * @brief 数字转int64
	 *
	 * @param env
	 * @param nodeValue
	 * @return int64_t
	 */
	extern int64_t number_int64(napi_env env, napi_value nodeValue, int64_t defaultValue = 0);
	/**
	 * @brief 数字转64位浮点
	 *
	 * @param env
	 * @param nodeValue
	 * @return double
	 */
	extern double number_double(napi_env env, napi_value nodeValue, double defaultValue = 0.0);
	/**
	 * @brief bigint转long
	 *
	 * @param env
	 * @param nodeValue
	 * @return long long
	 */
	extern long long bigint_longlong(napi_env env, napi_value nodeValue, long long defaultValue = 0);
	/**
	 * @brief 获取buff
	 *
	 * @param env
	 * @param nodeValue
	 * @param buffer
	 */
	template <typename T>
	extern void buffer_vector(napi_env env, napi_value nodeValue, std::vector<T> &buffer);
	/**
	 * @brief 获取为布尔值
	 *
	 * @param env
	 * @param nodeValue
	 * @return true
	 * @return false
	 */
	extern bool boolean_bool(napi_env env, napi_value nodeValue, bool defaultValue = false);
	/**
	 * @brief 获取为utf8标准的文本
	 *
	 * @param env
	 * @param nodeValue
	 * @return string
	 */
	extern std::string string_utf8(napi_env env, napi_value nodeValue, std::string defaultValue = std::string(""));
	/**
	 * @brief 获取为utf8标准的文本
	 *
	 * @param env
	 * @param nodeValue
	 * @return string
	 */
	extern std::wstring string_utf16(napi_env env, napi_value nodeValue, std::wstring defaultValue = std::wstring(L""));
	/**
	 * @brief 获取为窄(A)文本
	 *
	 * @param env
	 * @param nodeValue
	 * @return string
	 */
	extern std::string string_ansi(napi_env env, napi_value nodeValue, std::string defaultValue = std::string(""));
	/**
	 * @brief 获取为宽(W)文本
	 *
	 * @param env
	 * @param nodeValue
	 * @return wstring
	 */
	extern std::wstring string_wide(napi_env env, napi_value nodeValue, std::wstring defaultValue = std::wstring(L""));
	/**
	 * @brief 获取文本数组
	 *
	 * @param env
	 * @param nodeValue
	 * @return vector<string>
	 */
	extern std::vector<std::string> array_string_utf8(napi_env env, napi_value nodeValue);
	/**
	 * @brief 获取文本数组
	 *
	 * @param env
	 * @param nodeValue
	 * @return vector<string>
	 */
	extern std::vector<std::wstring> array_string_utf16(napi_env env, napi_value nodeValue);

	extern std::vector<napi_value> get_array_value_list(napi_env env, napi_value nodeValue);

	extern std::vector<std::pair<std::wstring, napi_value>> get_object_value_list_utf16(napi_env env, napi_value nodeValue);
	extern std::vector<std::pair<std::string, napi_value>> get_object_value_list_utf8(napi_env env, napi_value nodeValue);

	extern std::vector<std::wstring> get_object_keys_utf16(napi_env env, napi_value nodeValue);
	extern std::vector<std::string> get_object_keys_utf8(napi_env env, napi_value nodeValue);
	extern std::vector<napi_value> get_object_keys(napi_env env, napi_value nodeValue);

	/**
	 * @brief 获取数字数组
	 *
	 * @param env
	 * @param nodeValue
	 * @return vector<int>
	 */
	extern std::vector<int> array_int(napi_env env, napi_value nodeValue);
	/**
	 * @brief 获取数字数组
	 *
	 * @param env
	 * @param nodeValue
	 * @return vector<int>
	 */
	extern std::vector<int64_t> array_int64(napi_env env, napi_value nodeValue);
	/**
	 * @brief 获取数字数组
	 *
	 * @param env
	 * @param nodeValue
	 * @return vector<int>
	 */
	extern std::vector<double> array_double(napi_env env, napi_value nodeValue);
	/**
	 * @brief 将文本的显示状态转为CPP的显示状态代码
	 *
	 * @param env
	 * @param nodeValue
	 * @return UINT
	 */
	extern UINT showType_UINT(napi_env env, napi_value nodeValue);
	/**
	 * @brief 转 DWORD
	 *
	 * @param env
	 * @param nodeValue
	 * @return DWORD
	 */
	extern DWORD number_DWORD(napi_env env, napi_value nodeValue, int defaultValue = 0);
	/**
	 * @brief 转窗口句柄
	 *
	 * @param env
	 * @param nodeValue
	 * @return HWND
	 */
	extern HWND number_HWND(napi_env env, napi_value nodeValue, HWND defaultValue = NULL);
	/**
	 * @brief 获取buff内容
	 *
	 * @param env
	 * @param nodeValue
	 * @return vector<unsigned char>
	 */
	extern std::vector<unsigned char> buffer_vector(napi_env env, napi_value nodeValue);
	/**
	 * @brief 传入缓冲是utf16的文本
	 *
	 * @param env
	 * @param nodeValue
	 * @return wstring
	 */
	extern std::wstring buffer_utf16_strW(napi_env env, napi_value nodeValue);
	/**
	 * @brief 传入缓冲是ansi的文本（winapi转换过得）
	 *
	 * @param env
	 * @param nodeValue
	 * @return string
	 */
	extern std::string buffer_ansi_strA(napi_env env, napi_value nodeValue);
	/**
	 * @brief 传入缓冲是utf8的文本
	 *
	 * @param env
	 * @param nodeValue
	 * @return string
	 */
	extern std::string buffer_utf8_strU8(napi_env env, napi_value nodeValue);
	/**
	 * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
	 * @param env
	 * @param nodeValue
	 * @return const wchar_t* c标准接口的  const char *
	 */
	extern const wchar_t *buffer_utf16_clpStrW(napi_env env, napi_value nodeValue);
	/**
	 * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
	 * @param env
	 * @param nodeValue
	 * @return const char* c标准接口的  const char *
	 */
	extern const char *buffer_utf8_clpStrU8(napi_env env, napi_value nodeValue);
	/**
	 * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
	 * @param env
	 * @param nodeValue
	 * @return const char* c标准接口的  const char *
	 */
	extern const char *buffer_ansi_clpStrA(napi_env env, napi_value nodeValue);
	/**
	 * @brief 获取一个对象并将其转换为 POINT
	 *
	 * @param env
	 * @param objectValue
	 * @return POINT
	 */
	extern POINT point(napi_env env, napi_value objectValue);
	/**
	 * @brief 使用键获取napi_value 的值
	 *
	 * @param env
	 * @param objectValue
	 * @param key
	 * @return napi_value
	 */
	extern napi_value get_object_value(napi_env env, napi_value objectValue, std::string key);
	/**
	 * @brief 使用键取值为int
	 *
	 * @param env
	 * @param objectValue
	 * @param key
	 * @param defaultValue
	 * @return int
	 */
	extern int get_object_value_int(napi_env env, napi_value objectValue, std::string key, int defaultValue = 0);
	/**
	 * @brief 使用键取值为int64
	 *
	 * @param env
	 * @param objectValue
	 * @param key
	 * @param defaultValue
	 * @return int64_t
	 */
	extern int64_t get_object_value_int64(napi_env env, napi_value objectValue, std::string key, int64_t defaultValue = 0);
	/**
	 * @brief 使用键取值为double
	 *
	 * @param env
	 * @param objectValue
	 * @param key
	 * @param defaultValue
	 * @return double
	 */
	extern double get_object_value_double(napi_env env, napi_value objectValue, std::string key, double defaultValue = 0);
	/**
	 * @brief 使用键取值为bool
	 *
	 * @param env
	 * @param objectValue
	 * @param key
	 * @param defaultValue
	 * @return true
	 * @return false
	 */
	extern bool get_object_value_bool(napi_env env, napi_value objectValue, std::string key, bool defaultValue = false);
	/**
	 * @brief 使用键取值为 utf16
	 *
	 * @param env
	 * @param objectValue
	 * @param key
	 * @param defaultValue
	 * @return wstring
	 */
	extern std::wstring get_object_value_utf16(napi_env env, napi_value objectValue, std::string key, std::wstring defaultValue = std::wstring(L""));
	/**
	 * @brief 使用键取值为utf8
	 *
	 * @param env
	 * @param objectValue
	 * @param key
	 * @param defaultValue
	 * @return string
	 */
	extern std::string get_object_value_utf8(napi_env env, napi_value objectValue, std::string key, std::string defaultValue = std::string(""));
	/**
	 * @brief 使用键取值为ansi
	 *
	 * @param env
	 * @param objectValue
	 * @param key
	 * @param defaultValue
	 * @return string
	 */
	extern std::string get_object_value_ansi(napi_env env, napi_value objectValue, std::string key, std::string defaultValue = std::string(""));
	/**
	 * @brief 使用键取值为 RECT
	 *
	 * @param env
	 * @param objectValue
	 * @return RECT
	 */
	extern RECT rect(napi_env env, napi_value objectValue);
	/**
	 * @brief 获取为时间戳
	 *
	 * @param env
	 * @param objectValue
	 */
	extern double date(napi_env env, napi_value objectValue);
}

namespace hmc_napi_type
{

	/**
	 * @brief 获取napi数据的类型文本
	 *
	 * @param valuetype
	 * @return string
	 */
	extern std::string typeName(js_valuetype valuetype);
	/**
	 * @brief 获取napi数据的类型文本
	 *
	 * @param valuetype
	 * @return string
	 */
	extern std::string typeName(napi_valuetype valuetype);
	/**
	 * @brief 获取napi类型变量名称（人话）
	 *
	 * @param env
	 * @param valuetype
	 * @return string
	 */
	extern std::string typeName(napi_env env, napi_value valuetype);

	/**
	 * @brief 获取node类型的枚举值
	 *
	 * @param env
	 * @param valuetype
	 * @return string
	 */
	extern js_valuetype getType(napi_env env, napi_value valuetype);

	extern std::vector<js_valuetype> getType(napi_env env, std::vector<napi_value> valuetype);

	/**
	 * @brief 对比两个变量类型是否相等
	 *
	 * @param valuetype
	 * @param valuetype2
	 * @return BOOL
	 */
	extern bool diff(napi_valuetype valuetype, napi_valuetype valuetype2);

	extern bool diff(js_valuetype valuetype, std::vector<js_valuetype> valuetype2);

	/**
	 * @brief 判断值与多种类型是否一致
	 *
	 * @param valuetype
	 * @param valuetype2
	 * @param first
	 * @param args
	 * @return true
	 * @return false
	 */
	template <typename... Args>
	extern bool diff(napi_valuetype valuetype, const napi_valuetype &first, const Args &...args);
	/**
	 * @brief 判断值与多种类型是否一致
	 *
	 * @tparam Args
	 * @param env
	 * @param nodeValue
	 * @param first
	 * @param args
	 * @return int
	 */
	template <typename... Args>
	extern bool diff(napi_env env, napi_value nodeValue, const napi_valuetype &first, const Args &...args);

	/**
	 * @brief 判断值与类型是否一致
	 *
	 * @param env
	 * @param jsValue
	 * @param valuetype
	 * @return true
	 * @return false
	 */
	extern bool diff(napi_env env, napi_value jsValue, napi_valuetype valuetype);
	/**
	 * @brief 判断两个值的类型是否一致
	 *
	 * @param env
	 * @param jsValue
	 * @param jsValue2
	 * @return true
	 * @return false
	 */
	extern bool diff(napi_env env, napi_value jsValue, napi_value jsValue2);
	/**
	 * @brief 判断传入的值数量是否符合当前的要求
	 *
	 * @param env
	 * @param nodeValue
	 * @param argLength
	 * @param index
	 * @return true
	 * @return false
	 */
	extern bool argsSize(napi_env env, size_t argLength, int minLength, int maxLength);
	/**
	 * @brief 判断传入的值数量是否符合当前的要求
	 *
	 * @param env
	 * @param nodeValue
	 * @param argLength
	 * @param index
	 * @return true
	 * @return false
	 */
	extern bool argsSize(napi_env env, size_t argLength, int minLength);
	/**
	 * @brief 是buff
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isBuffer(napi_env env, napi_value value);
	/**
	 * @brief 是文本
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isString(napi_env env, napi_value value);
	/**
	 * @brief 是数字
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isNumber(napi_env env, napi_value value);
	/**
	 * @brief 是布尔
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isBoolean(napi_env env, napi_value value);
	/**
	 * @brief 是 Bigint
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isBigint(napi_env env, napi_value value);
	/**
	 * @brief 是函数
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isFunction(napi_env env, napi_value value);
	/**
	 * @brief 是对象
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isObject(napi_env env, napi_value value);
	/**
	 * @brief 是 Undefined
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isUndefined(napi_env env, napi_value value);
	/**
	 * @brief 是null
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isNull(napi_env env, napi_value value);
	/**
	 * @brief 在 JavaScript 中显示为普通对象
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isExternal(napi_env env, napi_value value);
	/**
	 * @brief 判断是否是 obj 并且包含了 此key
	 *
	 * @param env
	 * @param objectValue
	 * @param key
	 * @return true
	 * @return false
	 */
	extern bool isObjectkeyExists(napi_env env, napi_value objectValue, std::string key);
	/**
	 * @brief 是数组
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isArray(napi_env env, napi_value value);
	/**
	 * @brief 是Date
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isDate(napi_env env, napi_value value);
	/**
	 * @brief 是 Error
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isError(napi_env env, napi_value value);
	/**
	 * @brief 是 C Point
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isPoint(napi_env env, napi_value value);
	/**
	 * @brief 是 Promise
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isPromise(napi_env env, napi_value value);
	/**
	 * @brief 是 C Rect
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	extern bool isRect(napi_env env, napi_value value);
}

namespace hmc_napi_create_value
{

	extern napi_value Variant(napi_env env, js_variant_value var);
	extern napi_value Variant(napi_env env, std::vector<js_variant_value> var);
	extern napi_value Variant(napi_env env, std::map<std::string, js_variant_value> var);
	extern napi_value Variant(napi_env env, std::map<std::wstring, js_variant_value> var);

	/**
	 * @brief Buffer 的释放函数
	 *
	 * @param env
	 * @param data
	 * @param hint
	 */
	extern void BufferFinalizer(napi_env env, void *data, void *hint);

	/**
	 * @brief 创建一个函数
	 *
	 * @param env 上下文
	 * @param name 函数名称
	 * @param cb 函数
	 * @return napi_value
	 */
	extern napi_value ExFunction(napi_env env, std::string name, napi_callback cb);

	/**
	 * @brief 创建一个错误
	 *
	 * @param env 上下文
	 * @param error 错误信息
	 * @param fn_name 函数名
	 * @return napi_value
	 */
	extern napi_value Error(napi_env env, std::string error, std::string fn_name = "", std::string ErrorCode = "HMC_NAPI_ERROR");
	/**
	 * @brief 立即报错 并返回null 给node
	 *
	 * @param env 上下文
	 * @param error 错误信息
	 * @param fn_name 函数名
	 * @return napi_value
	 */
	extern napi_value Error(napi_env env, std::wstring error, std::wstring fn_name = L"", std::wstring ErrorCode = L"HMC_NAPI_ERROR");
	/**
	 * @brief 立即报错 并返回null 给node 只能是utf8文本
	 *
	 * @param env 上下文
	 * @param immediately 是否立即报错
	 * @param error 错误信息
	 * @param fn_name 函数名
	 * @return napi_value
	 */
	extern napi_value ErrorBreak(napi_env env, std::string error, std::string fn_name = "", std::string ErrorCode = "HMC_NAPI_ERROR");
	/**
	 * @brief 立即报错 并返回null 给node 只能是A文本
	 *
	 * @param env 上下文
	 * @param immediately 是否立即报错
	 * @param error 错误信息
	 * @param fn_name 函数名
	 * @return napi_value
	 */
	extern napi_value ErrorBreakA(napi_env env, std::string error, std::string fn_name = "", std::string ErrorCode = "HMC_NAPI_ERROR");
	/**
	 * @brief 立即报错 并返回null 给node 只能是utf16文本
	 *
	 * @param env 上下文
	 * @param immediately 是否立即报错
	 * @param error 错误信息
	 * @param fn_name 函数名
	 * @return napi_value
	 */
	extern napi_value ErrorBreak(napi_env env, std::wstring error, std::wstring fn_name = L"", std::wstring ErrorCode = L"HMC_NAPI_ERROR");

	// 创建一个布尔型
	extern napi_value Boolean(napi_env env, bool value = false);
	// 创建一个布尔型
	extern napi_value Boolean(napi_env env, int value = 0);

	// 返回一个 string utf8 string
	extern napi_value String(napi_env env, std::string value, size_t re_size = NAPI_AUTO_LENGTH);

	// 返回一个 string utf8 string
	extern napi_value StringA(napi_env env, std::string value, size_t re_size = NAPI_AUTO_LENGTH);
	// 返回一个 string utf16 string
	extern napi_value String(napi_env env, std::wstring value, size_t re_size = NAPI_AUTO_LENGTH);

	extern napi_value String(napi_env env);

	/**
	 * @brief 返回一个 number到js
	 *
	 * @param number
	 * @return napi_value
	 */
	extern napi_value Number(napi_env env, int number = 0);
	/**
	 * @brief 返回一个 number到js
	 *
	 * @param number
	 * @return napi_value
	 */
	extern napi_value Number(napi_env env, int64_t number = 0);
	/**
	 * @brief 返回一个 number到js
	 *
	 * @param number
	 * @return napi_value
	 */
	extern napi_value Number(napi_env env, double number = 0.0);
	/**
	 * @brief 返回一个 number到js
	 *
	 * @param number
	 * @return napi_value
	 */
	extern napi_value Number(napi_env env, HWND number);
	extern napi_value Number(napi_env env, unsigned long long number);
	/**
	 * @brief 返回一个 number到js
	 *
	 * @param bigint
	 * @return napi_value
	 */
	extern napi_value Bigint(napi_env env, int64_t bigint = 0);
	/**
	 * @brief 返回一个 number到js
	 *
	 * @param bigint
	 * @return napi_value
	 */
	extern napi_value Bigint(napi_env env, unsigned long long bigint = 0);
	/**
	 * @brief 返回一个 Buffer到js(返回的是空值 napi 不支持)
	 *
	 * @param env
	 * @param data
	 * @param size
	 * @return napi_value
	 */
	extern napi_value Buffer(napi_env env, std::vector<unsigned char> &buffer);

	/**
	 * @brief 返回一个 null
	 *
	 * @param env
	 * @param data
	 * @param size
	 * @return napi_value
	 */
	extern napi_value Null(napi_env env);
	/**
	 * @brief RECT (位置信息转为Object)
	 *
	 * @param env
	 * @param rect
	 * @return napi_value
	 */
	extern napi_value Rect(napi_env env, RECT rect);
	extern napi_value Point(napi_env env, POINT point);

	/**
	 * @brief 返回一个 undefined
	 *
	 * @param env
	 * @param data
	 * @param size
	 * @return napi_value
	 */
	extern napi_value Undefined(napi_env env);
	/**
	 * @brief 自识别类型
	 *
	 * @param env
	 * @param anyValue
	 * @return napi_value
	 */
	extern napi_value New(napi_env env, std::any anyValue);

	extern napi_value New(napi_env env);

	class jsArray
	{
	private:
		napi_env node_env = nullptr;
		std::vector<napi_value> napi_value_list;
		napi_value array_value = nullptr;
		bool is_ready_ok = false;
		napi_status status = napi_ok;

	public:
		size_t size();
		void clear();
		jsArray(napi_env env);
		void putValue(napi_value Object);
		void putBigint(int64_t Object);
		void putBigint(unsigned long long Object);
		void putNumber(int64_t Object);
		void putNumber(double Object);
		void putNull();
		void putUndefined();
		void putBuffer(std::vector<unsigned char> input);
		void putBoolean(bool Boolean);
		void putString(std::wstring Object, size_t re_size = NAPI_AUTO_LENGTH);
		void putString(std::string Object, size_t re_size = NAPI_AUTO_LENGTH);
		void putStringA(std::string Object, size_t re_size = NAPI_AUTO_LENGTH);
		napi_value toValue();
	};

	typedef std::variant<std::wstring, std::string> StringVar;

	class jsObject
	{
	private:
		napi_env node_env = nullptr;
		std::map<StringVar, napi_value> napi_value_list;
		napi_value object_value = nullptr;
		bool is_ready_ok = false;
		napi_status status = napi_ok;

	public:
		size_t size();
		void clear();
		jsObject(napi_env env);
		void putValue(StringVar key, napi_value Object);
		void putBigint(StringVar key, int64_t Object);
		void putNumber(StringVar key, int64_t Object);
		void putNumber(StringVar key, double Object);
		void putNull(StringVar key);
		void putUndefined(StringVar key);
		void putBuffer(StringVar key, std::vector<unsigned char> input);
		void putBoolean(StringVar key, bool Boolean);
		void putString(StringVar key, std::wstring Object, size_t re_size = NAPI_AUTO_LENGTH);
		void putString(StringVar key, std::string Object, size_t re_size = NAPI_AUTO_LENGTH);
		void putStringA(StringVar key, std::string Object, size_t re_size = NAPI_AUTO_LENGTH);
		napi_value toValue();
	};

}

class js_value
{
private:
	std::any data;

public:
	js_valuetype type;
	js_value(napi_env env, napi_callback_info info);
	js_value(napi_env env, napi_callback_info info, size_t index);
	js_value(napi_env env, napi_value nodeValue);
	/**
	 * @brief 获取此数据的值
	 *
	 * @return string
	 */
	std::string typeName();
	/**
	 * @brief 获取指定索引为 int
	 *
	 * @param index
	 * @param defaultValue
	 * @return int
	 */
	int getInt(int defaultValue = 0);
	/**
	 * @brief 获取指定索引为 int 64
	 *
	 * @param index
	 * @param defaultValue
	 * @return int64_t
	 */
	int64_t getInt64(int64_t defaultValue = 0);
	/**
	 * @brief 获取指定索引为 String Ansi
	 *
	 * @param index
	 * @param defaultValue
	 * @return string
	 */
	std::string getStringAnsi(std::string defaultValue = std::string(""));
	/**
	 * @brief 获取指定索引为  String Wide
	 *
	 * @param index
	 * @param defaultValue
	 * @return wstring
	 */
	std::wstring getStringWide(std::wstring defaultValue = std::wstring(L""));
	/**
	 * @brief 获取指定索引为  String Utf8
	 *
	 * @param index
	 * @param defaultValue
	 * @return string
	 */
	std::string getStringUtf8(std::string defaultValue = std::string(""));
	/**
	 * @brief 获取指定索引为 布尔
	 *
	 * @param index
	 * @param defaultValue
	 * @return true
	 * @return false
	 */
	bool getBool(bool defaultValue = false);
	/**
	 * @brief 获取指定索引为  Buffer
	 *
	 * @param index
	 * @param defaultValue
	 * @return vector<unsigned char>
	 */
	std::vector<unsigned char> getBuffer(std::vector<unsigned char> defaultValue = {});
	/**
	 * @brief 获取指定索引为  Double
	 *
	 * @param index
	 * @param defaultValue
	 * @return double
	 */
	double getDouble(double defaultValue = 0.0);
	/**
	 * @brief 获取指定索引为 DWORD
	 *
	 * @param index
	 * @param defaultValue
	 * @return DWORD
	 */
	DWORD getDword(DWORD defaultValue = 0);
	/**
	 * @brief 获取指定索引为 HWND
	 *
	 * @param index
	 * @param defaultValue
	 * @return HWND
	 */
	HWND getHwnd(HWND defaultValue = NULL);
	/**
	 * @brief 获取指定索引为 String 数组
	 *
	 * @param index
	 * @param defaultValue
	 * @return vector<string>
	 */
	std::vector<std::string> getArrayString(std::vector<std::string> defaultValue = {});
	/**
	 * @brief 获取指定索引为 int 数组
	 *
	 * @param index
	 * @param defaultValue
	 * @return vector<int>
	 */
	std::vector<int> getArrayInt(std::vector<int> defaultValue = {});
	/**
	 * @brief 获取指定索引为 utf16 数组
	 *
	 * @param index
	 * @param defaultValue
	 * @return vector<wstring>
	 */
	std::vector<std::wstring> getArrayWstring(std::vector<std::wstring> defaultValue = {});
	/**
	 * @brief 判断值是否存在
	 *
	 * @param index
	 * @return true
	 * @return false
	 */
	bool has_value();
	/**
	 * @brief 是buff
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isBuffer();
	/**
	 * @brief 是文本
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isString();
	/**
	 * @brief 是数字
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isNumber();
	/**
	 * @brief 是布尔
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isBoolean();
	/**
	 * @brief 是 Bigint
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isBigint();
	/**
	 * @brief 是函数
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isFunction();
	/**
	 * @brief 是对象
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isObject();
	/**
	 * @brief 是 Undefined
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isUndefined();
	/**
	 * @brief 是null
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isNull();
	/**
	 * @brief 在 JavaScript 中显示为普通对象
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isExternal();
	/**
	 * @brief 判断是否是 obj 并且包含了 此key
	 *
	 * @param env
	 * @param objectValue
	 * @param key
	 * @return true
	 * @return false
	 */
	bool isObjectkeyExists(napi_env env, napi_value objectValue, std::string key);
	/**
	 * @brief 是数组
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isArray();
	/**
	 * @brief 是Date
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isDate();
	/**
	 * @brief 是 Error
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isError();
	/**
	 * @brief 是 C Point
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isPoint();
	/**
	 * @brief 是 Promise
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isPromise();
	/**
	 * @brief 是 C Rect
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isRect();

	~js_value();
};

// 快速关闭句柄 (作用域内)
class open_handle_scope
{
private:
	napi_handle_scope _scope = NULL;
	napi_env _env = NULL;
	napi_status _status = napi_ok;
	bool _is_close = false;

public:
	open_handle_scope(napi_env env);
	bool close();
	// !
	bool operator!() const
	{
		return _status != napi_ok || _scope == nullptr || _env == nullptr;
	}
	// if
	operator bool() const
	{
		return _status == napi_ok && _scope != nullptr || _env != nullptr;
	}

	~open_handle_scope();
};

class hmc_NodeArgsValue
{
private:
	std::vector<napi_value> args;
	// std::vector<js_valuetype> type_args;
	napi_env env;

public:
	hmc_NodeArgsValue(napi_env env, napi_callback_info info);
	~hmc_NodeArgsValue();
	std::vector<napi_value> get_args();
	napi_value at(size_t index);
	std::vector<js_value> get_values();

	/**
	 * @brief 取值并进行基础型转换
	 *
	 * @param index
	 * @return js_variant_value
	 */
	js_variant_value get_variant(size_t index);

	using callback_type = std::function<js_variant_value(napi_env env, napi_value value, hmc_NodeArgsValue *input, size_t index)>;

	/**
	 * @brief 使用自定义函数格式化napi_value 到variant
	 *
	 * @param index
	 * @param CallBack
	 * @return js_variant_value
	 */
	js_variant_value get_variant(size_t index, callback_type CallBack);
	/**
	 * @brief 获取为数组
	 *
	 * @param index
	 * @return std::vector<js_variant_value>
	 */
	std::vector<js_variant_value> getArrayVariant(size_t index);
	/**
	 * @brief 获取为对象
	 *
	 * @param index
	 * @return std::map<std::wstring, js_variant_value>
	 */
	std::map<std::wstring, js_variant_value> getObjecVariant_utf16(size_t index);
	/**
	 * @brief 获取为对象
	 *
	 * @param index
	 * @return std::map<std::string, js_variant_value>
	 */
	std::map<std::string, js_variant_value> getObjecVariant_utf8(size_t index);
	/**
	 * @brief 获取值为js_value
	 *
	 * @param index
	 * @return js_value
	 */
	js_value get_value(size_t index);
	/**
	 * @brief 获取数量
	 *
	 * @return size_t
	 */
	size_t size();
	/**
	 * @brief 获取指定索引为 int
	 *
	 * @param index
	 * @param defaultValue
	 * @return int
	 */
	int getInt(size_t index, int defaultValue = 0);
	/**
	 * @brief 获取指定索引为 int 64
	 *
	 * @param index
	 * @param defaultValue
	 * @return int64_t
	 */
	int64_t getInt64(size_t index, int64_t defaultValue = 0);
	/**
	 * @brief 获取指定索引为 String Ansi
	 *
	 * @param index
	 * @param defaultValue
	 * @return string
	 */
	std::string getStringAnsi(size_t index, std::string defaultValue = std::string(""));
	/**
	 * @brief 获取指定索引为  String Wide
	 *
	 * @param index
	 * @param defaultValue
	 * @return wstring
	 */
	std::wstring getStringWide(size_t index, std::wstring defaultValue = std::wstring(L""));
	/**
	 * @brief 获取指定索引为  String Utf8
	 *
	 * @param index
	 * @param defaultValue
	 * @return string
	 */
	std::string getStringUtf8(size_t index, std::string defaultValue = std::string(""));
	/**
	 * @brief 获取指定索引为 布尔
	 *
	 * @param index
	 * @param defaultValue
	 * @return true
	 * @return false
	 */
	bool getBool(size_t index, bool defaultValue = false);
	/**
	 * @brief 获取指定索引为  Buffer
	 *
	 * @param index
	 * @param defaultValue
	 * @return vector<unsigned char>
	 */
	std::vector<unsigned char> getBuffer(size_t index, std::vector<unsigned char> defaultValue = {});
	/**
	 * @brief 获取指定索引为  Double
	 *
	 * @param index
	 * @param defaultValue
	 * @return double
	 */
	double getDouble(size_t index, double defaultValue = 0.0);
	/**
	 * @brief 获取指定索引为 DWORD
	 *
	 * @param index
	 * @param defaultValue
	 * @return DWORD
	 */
	DWORD getDword(size_t index, DWORD defaultValue = 0);
	/**
	 * @brief 获取指定索引为 HWND
	 *
	 * @param index
	 * @param defaultValue
	 * @return HWND
	 */
	HWND getHwnd(size_t index, HWND defaultValue = NULL);
	/**
	 * @brief 获取指定索引为 String 数组
	 *
	 * @param index
	 * @param defaultValue
	 * @return vector<string>
	 */
	std::vector<std::string> getArrayString(size_t index, std::vector<std::string> defaultValue = {});
	/**
	 * @brief 获取指定索引为 int 数组
	 *
	 * @param index
	 * @param defaultValue
	 * @return vector<int>
	 */
	std::vector<int> getArrayInt(size_t index, std::vector<int> defaultValue = {});
	/**
	 * @brief 获取指定索引为 utf16 数组
	 *
	 * @param index
	 * @param defaultValue
	 * @return vector<wstring>
	 */
	std::vector<std::wstring> getArrayWstring(size_t index, std::vector<std::wstring> defaultValue = {});
	/**
	 * @brief 判断值是否存在
	 *
	 * @param index
	 * @return true
	 * @return false
	 */
	bool exists(size_t index);
	/**
	 * @brief 判断值长度是否符合
	 *
	 * @param min_length 最少有多少个
	 * @param max_length 最多有多少个
	 * @return true
	 * @return false
	 */
	bool argsSize(size_t min_length, size_t max_length, bool throw_error = false);
	/**
	 * @brief 判断当前传入的值是否是期待值
	 *
	 * @param eq_type
	 * @return true
	 * @return false
	 */
	bool eq(size_t index, js_valuetype type, bool throw_error = false);
	/**
	 * @brief 判断当前传入的值是否是期待值
	 *
	 * @param eq_type
	 * @return true
	 * @return false
	 */
	bool eq(std::vector<std::tuple<size_t, js_valuetype>> eq_type, bool throw_error = false);

	/**
	 * @brief 判断当前传入的值是否是期待值
	 *
	 * @param eq_type
	 * @return true
	 * @return false
	 */
	bool eq(std::vector<js_valuetype> eq_type, bool throw_error = false);

	/**
	 * @brief 判断当前传入的值是否是期待值
	 *
	 * @param eq_type
	 * @return true
	 * @return false
	 */
	bool eq(size_t index, napi_valuetype type, bool throw_error = false);
	/**
	 * @brief 判断当前传入的值是否是期待值
	 *
	 * @param eq_type
	 * @return true
	 * @return false
	 */
	bool eq(std::vector<std::tuple<size_t, napi_valuetype>> eq_type, bool throw_error = false);
	/**
	 * @brief 判断当前传入的值是否是期待值
	 *
	 * @param eq_type
	 * @return true
	 * @return false
	 */
	bool eq(size_t index, std::vector<js_valuetype> type_list = {}, bool throw_error = false);
	/**
	 * @brief 判断当前传入的值是否是期待值
	 *
	 * @param eq_type
	 * @return true
	 * @return false
	 */
	bool eq(size_t index, std::vector<napi_valuetype> type_list = {}, bool throw_error = false);
	/**
	 * @brief 获取类型列表
	 *
	 * @return vector<js_valuetype>
	 */
	std::vector<js_valuetype> getType();
	/**
	 * @brief 获取指定索引的 类型
	 *
	 * @param index
	 * @return js_valuetype
	 */
	js_valuetype getType(size_t index);

	/**
	 * @brief 删除指定元素
	 *
	 * @param Index
	 * @return true
	 * @return false
	 */
	bool removeIndex(size_t Index);
	/**
	 * @brief 是否为空
	 *
	 * @return true
	 * @return false
	 */
	bool empty();

	/**
	 * @brief 让两个位置的元素互换
	 *
	 * @param Index 索引1
	 * @param Index2 索引2
	 * @return true
	 * @return false
	 */
	bool swap(size_t Index, size_t Index2);

	/**
	 * @brief 替换指定的元素位置
	 *
	 * @param Index 索引
	 * @param value 新的值
	 * @return true
	 * @return false
	 */
	bool replace(size_t Index, napi_value value);
};

class PromiseFunctionUtil
{
public:
	typedef std::function<std::any(std::vector<std::any> *arguments_list)> WorkFuncType;
	typedef std::function<napi_value(napi_env env, std::any *result_any_data)> FuncFormatResultValue;
	typedef std::function<void(napi_env env, napi_callback_info info, std::vector<std::any> *ArgumentsList, hmc_NodeArgsValue args_value)> formatArgsCallBackType;
	typedef std::atomic<napi_async_work> workHandle;
	typedef std::atomic<napi_async_work> *pWorkHandle;
	typedef std::atomic<napi_deferred> deferredHandle;
	typedef std::atomic<napi_deferred> *pdeferredHandle;

	static void exports(napi_env env, napi_value exports, std::string name, napi_callback cb);
	static void exports(napi_env env, napi_value exports, std::string name, napi_callback cbAsync, napi_callback cbSync);
	static void completeWork(napi_env env, napi_status status, std::atomic<napi_async_work> *work, std::atomic<napi_deferred> *deferred, std::vector<std::any> *arguments_list, std::any *resultSend, FuncFormatResultValue FormatResultValue);

	// 由参数自定义格式化方法
	static napi_value startWork(napi_env env, napi_callback_info info, std::atomic<napi_async_work> *work, std::atomic<napi_deferred> *deferred, napi_async_execute_callback execute, napi_async_complete_callback complete, std::vector<std::any> *arguments_list, std::optional<formatArgsCallBackType> formatArgsCallBack);
	static napi_value startSync(napi_env env, napi_callback_info info, std::function<std::any(std::vector<std::any> *arguments_list)> PromiseWorkFunc, std::function<napi_value(napi_env env, std::any *result_any_data)> FormatResultValue, std::optional<formatArgsCallBackType> formatArgsCallBack);

private:
};

// 初始化模块
extern void InitAsyncFunction(napi_env env, napi_value exports, const char *utf8name, napi_callback StartAsyncTask, napi_callback ExecuteSync);

namespace HMC_PromiseStore
{
	struct EnvNextWorkData
	{
		napi_deferred deferred;
		napi_async_work work;
		size_t TASK_TYPE;
		std::any *ResultStore;
		std::vector<std::any> *ArgsStore;
	};

	// 执行取值格式化任务 返回为false时结束任务并返回null
	typedef std::function<bool(napi_env env, napi_callback_info info, hmc_NodeArgsValue ArgsValue, std::vector<std::any> *data_list)> chFormatArgFun;
	// 执行异步任务 并返回内容
	typedef std::function<std::any(napi_env env, size_t TASK_TYPE, std::vector<std::any> *data_list)> chExecuteWorkFun;
	// 执行异步任务 并返回内容
	typedef std::function<napi_value(napi_env env, napi_status status, std::any *ResultStore, std::vector<std::any> *data_list)> chExecuteResultFormatFun;
	extern std::map<size_t, chFormatArgFun> PromiseFormatEventListenerFunList;
	extern std::map<size_t, chExecuteWorkFun> PromiseWorkEventListenerFunList;
	extern std::map<size_t, chExecuteResultFormatFun> PromiseResultFormatEventListenerFunList;

}

namespace HMC_PromiseUtilV2
{
	template <typename GET_SHELL_ENV_INFO_ID>
	struct EnvNextWorkDataTemplate
	{
		napi_deferred deferred;
		napi_async_work work;

		// 没有格式化的话默认-> `vector<wstring>` `vector<int64_t>` `int64_t` `wstring` `vector<uint8_t>` `bool` `Array<wstring>`
		std::vector<js_variant_value> *arguments;
		// js_variant_value *index1;
		js_variant_value *Result;
		GET_SHELL_ENV_INFO_ID TAKE_TYPE;

		static void gc(EnvNextWorkDataTemplate *work)
		{
			if (work == NULL)
				return;

			if (work->arguments != NULL)
			{
				work->arguments->clear();
				work->arguments->shrink_to_fit();
				delete work->arguments;
				work->arguments = nullptr;
			}

			HMC_GC_CPP_BASIC_PTR(work->Result);
			::VirtualFree(work, 0, 0x00008000);
		}

		static EnvNextWorkDataTemplate *make()
		{
			EnvNextWorkDataTemplate *workData = HMC_VcAllocAutoLength(EnvNextWorkDataTemplate);

			if (workData != NULL)
			{
				workData->arguments = new std::vector<js_variant_value>();
				workData->Result = new js_variant_value();
				workData->TAKE_TYPE = GET_SHELL_ENV_INFO_ID::NONE;
			}

			return workData;
		}

		bool exists(size_t index, bool existsValue = false)
		{
			bool result = (this->arguments->size() > index);
			if (existsValue)
			{
				result = this->arguments->at(index).index() != 0;
			}

			return result;
		}

		template <typename T>
		bool exists(size_t index)
		{
			bool result = (this->arguments->size() > index);
			return result;
		}

		bool exists(size_t index, size_t valueIndex)
		{
			bool result = (this->arguments->size() > index);

			auto temp = this->arguments->at(index);
			result = temp.index() == valueIndex;

			return result;
		}

		template <typename T>
		T get(size_t index)
		{
			T result = T();
			if (this->exists<T>(index))
			{
				result = std::get<T>(this->arguments->at(index));
			}

			return result;
		}

		template <typename T>
		bool get_if(size_t index,T *varPtr)
		{
			bool result = false;
			if (this->exists<T>(index))
			{
				(*varPtr) = std::get<T>(this->arguments->at(index));
				result = true;
			}

			return result;
		}
	};

	template <typename GET_SHELL_ENV_INFO_ID, typename EnvNextWorkData>
	bool get_argumentsTemplate(napi_env env, hmc_NodeArgsValue input, void *Work, const std::map<GET_SHELL_ENV_INFO_ID, std::vector<std::tuple<size_t, js_valuetype>>> &GET_SHELL_EQ_TYPE_LIST)
	{
		EnvNextWorkData *work = (EnvNextWorkData *)Work;

		if (!input.eq(0, js_number, true))
		{
			return false;
		}

		work->TAKE_TYPE = (GET_SHELL_ENV_INFO_ID)at_Number32Or(0, 0);

		// 移除掉第一位的命令位
		input.removeIndex(0);

		for (auto &&EQ_TYPE : GET_SHELL_EQ_TYPE_LIST)
		{
			if (EQ_TYPE.first == work->TAKE_TYPE)
			{

				auto second = EQ_TYPE.second;
				if (!input.eq(second, true))
				{
					return false;
				}

				break;
			}
		}

		for (size_t index = 0; index < input.size(); index++)
		{
			if (input.exists(index))
			{
				auto temp = input.get_variant(index);
				work->arguments->push_back(temp);
			}
		}

		return true;
	}

	template <typename GET_SHELL_ENV_INFO_ID, typename EnvNextWorkData>
	napi_value ExecuteSyncTemplate(napi_env env, napi_callback_info info, const std::map<GET_SHELL_ENV_INFO_ID, std::vector<std::tuple<size_t, js_valuetype>>> &GET_SHELL_EQ_TYPE_LIST, std::function<void(EnvNextWorkData *work)> main)
	{
		napi_value result = as_Null();

		try
		{
			auto input = hmc_NodeArgsValue(env, info);
			auto *workData = EnvNextWorkData::make();

			HMC_FreeAnyAuto(EnvNextWorkData::gc(workData););

			bool is_eq_args = HMC_PromiseUtilV2::get_arguments<GET_SHELL_ENV_INFO_ID, EnvNextWorkData>(env, input, workData, GET_SHELL_EQ_TYPE_LIST);
			if (workData == NULL || !is_eq_args)
			{
				return result;
			}

			main(workData);

			result = hmc_napi_create_value::Variant(env, *workData->Result);
			return result;
		}
		HMC_CATCH_ALL;
		return hmc_napi_create_value::Error(env, "A fatal error occurred unexpectedly.", __FUNCSIG__, "HMC_SHELL_API_CATCH");
	}

	template <typename EnvNextWorkData>
	void ExecuteAsyncWorkTemplate(napi_env env, void *data, std::function<void(EnvNextWorkData *work)> main)
	{
		EnvNextWorkData *workData = (EnvNextWorkData *)data;
		try
		{
			main(workData);
		}
		HMC_CATCH_ALL;
	}

	// 异步任务完成后的回调函数

	template <typename EnvNextWorkData>
	void ResolveWorkTemplate(napi_env env, napi_status status, void *data)
	{
		EnvNextWorkData *workData = (EnvNextWorkData *)data;
		HMC_FreeAnyAuto(EnvNextWorkData::gc(workData););

		napi_value result;
		napi_get_null(env, &result);

		if (workData == NULL || workData->Result == NULL || workData->Result->index() == 0)
		{
			if (workData != NULL)
			{
				napi_resolve_deferred(env, workData->deferred, result);
				napi_delete_async_work(env, workData->work);
			}
			return;
		}

		result = hmc_napi_create_value::Variant(env, *workData->Result);

		if (result == NULL)
		{
			napi_get_null(env, &result);
		}

		napi_resolve_deferred(env, workData->deferred, result);
		napi_delete_async_work(env, workData->work);
	}

	// 启动异步任务的函数

	template <typename GET_SHELL_ENV_INFO_ID, typename EnvNextWorkData>
	napi_value StartAsyncTaskTemplate(
		napi_env env,
		napi_callback_info info,
		const std::map<GET_SHELL_ENV_INFO_ID, std::vector<std::tuple<size_t, js_valuetype>>> &GET_SHELL_EQ_TYPE_LIST,
		napi_async_execute_callback execute,
		napi_async_complete_callback complete)
	{
		napi_value promise;
		try
		{
			napi_value resourceName;
			napi_create_string_utf8(env, __FUNCSIG__, NAPI_AUTO_LENGTH, &resourceName);

			auto *workData = EnvNextWorkData::make();

			auto input = hmc_NodeArgsValue(env, info);
			bool is_eq_args = HMC_PromiseUtilV2::get_arguments<GET_SHELL_ENV_INFO_ID, EnvNextWorkData>(env, input, workData, GET_SHELL_EQ_TYPE_LIST);
			if (workData == NULL || !is_eq_args)
			{
				EnvNextWorkData::gc(workData);
				return as_Null();
			}

			napi_create_promise(env, &workData->deferred, &promise);
			napi_create_async_work(env, nullptr, resourceName, execute, complete, workData, &workData->work);
			napi_queue_async_work(env, workData->work);
			return promise;
		}
		HMC_CATCH_ALL;
		return hmc_napi_create_value::Error(env, "A fatal error occurred unexpectedly.", __FUNCSIG__, "HMC_SHELL_API_CATCH");
	}

}

class HMC_PromiseEval
{
public:
	static void ExecuteAsyncWork(napi_env env, void *data);
	static void GCEnvNextWorkData(void *data);
	static napi_value StartAsyncTask(napi_env env, napi_callback_info info);
	static void ResolveWork(napi_env env, napi_status status, void *data);
	static napi_value ExecuteSync(napi_env env, napi_callback_info info);
	static void append(size_t ID, std::optional<HMC_PromiseStore::chFormatArgFun> FormatFun, HMC_PromiseStore::chExecuteWorkFun WorkFun, std::optional<HMC_PromiseStore::chExecuteResultFormatFun> ResultFormatFun);
};

extern size_t getVariantEstimateSize(js_variant_value js_variant);
extern std::string formatVariantJSONStr_utf8(std::map<std::string, js_variant_value> js_variant);
extern std::string formatVariantJSONStr_utf8(std::map<std::wstring, js_variant_value> js_variant);
extern std::string formatVariantJSONStr_utf8(js_variant_value js_variant);
extern std::string formatVariantJSONStr_utf8(std::vector<js_variant_value> js_variant);

extern std::wstring formatVariantJSONStr_utf16(std::map<std::string, js_variant_value> js_variant);
extern std::wstring formatVariantJSONStr_utf16(std::map<std::wstring, js_variant_value> js_variant);
extern std::wstring formatVariantJSONStr_utf16(js_variant_value js_variant);
extern std::wstring formatVariantJSONStr_utf16(std::vector<js_variant_value> js_variant);

#endif // MODE_INTERNAL_INCLUDE_HMC_NAPI_VALUE_UTIL_HPP