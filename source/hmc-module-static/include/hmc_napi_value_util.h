#pragma once

//  导入模块之前必须已经导入 node_api.h

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_NAPI_VALUE_UTIL_HPP
#define MODE_INTERNAL_INCLUDE_HMC_NAPI_VALUE_UTIL_HPP

#define NAPI_EXPERIMENTAL

#include <atomic>
#include <windows.h>
#include <assert.h>
#include <any>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <node_api.h>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <thread>
#include <shared_mutex>
#include <variant>

#include "hmc_string_util.h"

const size_t BIT_2GB = 8589934592ull

#define NAME_STR(func) #func

// 导出一个 static 函数
#define EXPORT_NAPI_STATIC_FN(func)              \
	{                                            \
		#func, 0, func, 0, 0, 0, napi_default, 0 \
	}
// 导出一个 static 函数
#define EXPORT_NAPI_STATIC_PAIR(name, func)     \
	{                                           \
		name, 0, func, 0, 0, 0, napi_default, 0 \
	}

// 导出一个 其他文件的 函数
#define EXPORT_NAPI_REMOTE_FN(func)                                \
	{                                                              \
		#func, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
	}

// 导出一个 其他文件的 函数 并设置名称
#define EXPORT_NAPI_REMOTE_FNPAIR(name, func)                     \
	{                                                             \
		name, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
	}
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

// 导出一个 其他文件的 函数 并设置名称
#define ___EXPORT_NAPI_REMOTE_FN____PROMISE_SESSION                           \
	EXPORT_NAPI_REMOTE_FNPAIR("_PromiseSession_get", _PromiseSession_getAll), \
		EXPORT_NAPI_REMOTE_FN(_PromiseSession_isClosed),                      \
		EXPORT_NAPI_REMOTE_FN(_PromiseSession_stop),                          \
		EXPORT_NAPI_REMOTE_FN(_PromiseSession_max_id),                        \
		EXPORT_NAPI_REMOTE_FN(_PromiseSession_data_size),                     \
		EXPORT_NAPI_REMOTE_FN(_PromiseSession_set_sleep_time),                \
		EXPORT_NAPI_REMOTE_FN(_PromiseSession_await),                         \
		EXPORT_NAPI_REMOTE_FN(_PromiseSession_ongoingTasks),                  \
		EXPORT_NAPI_REMOTE_FN(_PromiseSession_completeTasks),                 \
		EXPORT_NAPI_REMOTE_FN(_PromiseSession_get_sleep_time),                \
		EXPORT_NAPI_REMOTE_FN(_PromiseSession_allTasks)

	;
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
	js_point = 95277,
	// js_array_string = 95279,
	// js_array_number = 95281,
	// js_array_boolean = 95282,
	// js_array_bigint = 95283,
	js_promise = 95285,
	js_promise_function = 95286,
	js_rect = 95288,
	js_unknown = 955666,
	// js_array_any = 95290,
} js_valuetype;

namespace hmc_napi_get_value
{
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
	extern double number_double(napi_env env, napi_value nodeValue, int defaultValue = 0.0);
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

	/**
	 * @brief 对比两个变量类型是否相等
	 *
	 * @param valuetype
	 * @param valuetype2
	 * @return BOOL
	 */
	extern bool diff(napi_valuetype valuetype, napi_valuetype valuetype2);
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
	bool isPoint(napi_env env, napi_value value);
	/**
	 * @brief 是 Promise
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isPromise(napi_env env, napi_value value);
	/**
	 * @brief 是 C Rect
	 *
	 * @param env
	 * @param value
	 * @return true
	 * @return false
	 */
	bool isRect(napi_env env, napi_value value);
}

namespace hmc_napi_create_value
{

	/**
	 * @brief Buffer 的释放函数
	 *
	 * @param env
	 * @param data
	 * @param hint
	 */
	void BufferFinalizer(napi_env env, void *data, void *hint);

	/**
	 * @brief 创建一个函数
	 *
	 * @param env 上下文
	 * @param name 函数名称
	 * @param cb 函数
	 * @return napi_value
	 */
	napi_value ExFunction(napi_env env, std::string name, napi_callback cb);

	/**
	 * @brief 创建一个错误
	 *
	 * @param env 上下文
	 * @param error 错误信息
	 * @param fn_name 函数名
	 * @return napi_value
	 */
	napi_value Error(napi_env env, std::string error, std::string fn_name = "", std::string ErrorCode = "HMC_NAPI_ERROR");
	/**
	 * @brief 立即报错 并返回null 给node
	 *
	 * @param env 上下文
	 * @param error 错误信息
	 * @param fn_name 函数名
	 * @return napi_value
	 */
	napi_value Error(napi_env env, std::wstring error, std::wstring fn_name = L"", std::wstring ErrorCode = L"HMC_NAPI_ERROR");
	/**
	 * @brief 立即报错 并返回null 给node 只能是utf8文本
	 *
	 * @param env 上下文
	 * @param immediately 是否立即报错
	 * @param error 错误信息
	 * @param fn_name 函数名
	 * @return napi_value
	 */
	napi_value ErrorBreak(napi_env env, std::string error, std::string fn_name = "", std::string ErrorCode = "HMC_NAPI_ERROR");
	/**
	 * @brief 立即报错 并返回null 给node 只能是A文本
	 *
	 * @param env 上下文
	 * @param immediately 是否立即报错
	 * @param error 错误信息
	 * @param fn_name 函数名
	 * @return napi_value
	 */
	napi_value ErrorBreakA(napi_env env, std::string error, std::string fn_name = "", std::string ErrorCode = "HMC_NAPI_ERROR");
	/**
	 * @brief 立即报错 并返回null 给node 只能是utf16文本
	 *
	 * @param env 上下文
	 * @param immediately 是否立即报错
	 * @param error 错误信息
	 * @param fn_name 函数名
	 * @return napi_value
	 */
	napi_value ErrorBreak(napi_env env, std::wstring error, std::wstring fn_name = L"", std::wstring ErrorCode = L"HMC_NAPI_ERROR");

	// 创建一个布尔型
	napi_value Boolean(napi_env env, bool value = false);
	// 创建一个布尔型
	napi_value Boolean(napi_env env, int value = 0);

	// 返回一个 string utf8 string
	napi_value String(napi_env env, std::string value, size_t re_size = NAPI_AUTO_LENGTH);

	// 返回一个 string utf8 string
	napi_value StringA(napi_env env, std::string value, size_t re_size = NAPI_AUTO_LENGTH);
	// 返回一个 string utf16 string
	napi_value String(napi_env env, std::wstring value, size_t re_size = NAPI_AUTO_LENGTH);

	napi_value String(napi_env env);

	/**
	 * @brief 返回一个 number到js
	 *
	 * @param number
	 * @return napi_value
	 */
	napi_value Number(napi_env env, int number = 0);
	/**
	 * @brief 返回一个 number到js
	 *
	 * @param number
	 * @return napi_value
	 */
	napi_value Number(napi_env env, int64_t number = 0);
	/**
	 * @brief 返回一个 number到js
	 *
	 * @param number
	 * @return napi_value
	 */
	napi_value Number(napi_env env, double number = 0.0);
	/**
	 * @brief 返回一个 number到js
	 *
	 * @param number
	 * @return napi_value
	 */
	napi_value Number(napi_env env, HWND number);
	napi_value Number(napi_env env, unsigned long number);
	/**
	 * @brief 返回一个 number到js
	 *
	 * @param bigint
	 * @return napi_value
	 */
	napi_value Bigint(napi_env env, long bigint = 0);
	/**
	 * @brief 返回一个 number到js
	 *
	 * @param bigint
	 * @return napi_value
	 */
	napi_value Bigint(napi_env env, long long bigint = 0);
	/**
	 * @brief 返回一个 Buffer到js(返回的是空值 napi 不支持)
	 *
	 * @param env
	 * @param data
	 * @param size
	 * @return napi_value
	 */
	napi_value Buffer(napi_env env, std::vector<unsigned char> &buffer);

	/**
	 * @brief 返回一个 null
	 *
	 * @param env
	 * @param data
	 * @param size
	 * @return napi_value
	 */
	napi_value Null(napi_env env);
	/**
	 * @brief RECT (位置信息转为Object)
	 *
	 * @param env
	 * @param rect
	 * @return napi_value
	 */
	napi_value Rect(napi_env env, RECT rect);
	napi_value Point(napi_env env, POINT point);

	/**
	 * @brief 返回一个 undefined
	 *
	 * @param env
	 * @param data
	 * @param size
	 * @return napi_value
	 */
	napi_value Undefined(napi_env env);
	/**
	 * @brief 自识别类型
	 *
	 * @param env
	 * @param anyValue
	 * @return napi_value
	 */
	napi_value New(napi_env env, std::any anyValue);

	napi_value New(napi_env env);

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
		void putNumber(int64_t Object);
		void putNumber(double Object);
		void putNull();
		void putUndefined();
		void putBuffer(std::vector<unsigned char> input);
		void putBoolean(bool Boolean);
		void putString(std::wstring Object, size_t re_size = 0);
		void putString(std::string Object, size_t re_size = 0);
		void putStringA(std::string Object, size_t re_size = 0);
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
		void putString(StringVar key, std::wstring Object, size_t re_size = 0);
		void putString(StringVar key, std::string Object, size_t re_size = 0);
		void putStringA(StringVar key, std::string Object, size_t re_size = 0);
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

class hmc_NodeArgsValue
{
private:
	std::vector<napi_value> args;
	napi_env env;

public:
	hmc_NodeArgsValue(napi_env env, napi_callback_info info);
	~hmc_NodeArgsValue();
	std::vector<napi_value> get_args();
	napi_value at(size_t index);
	std::vector<js_value> get_values();
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
	bool swap(size_t Index,size_t Index2);

	/**
	 * @brief 替换指定的元素位置
	 * 
	 * @param Index 索引
	 * @param value 新的值
	 * @return true 
	 * @return false 
	 */
	bool replace(size_t Index , napi_value value);

};

namespace hmc_PromiseSession
{

	// 任务id
	extern size_t ____$hmcPromise_PromiseSessionID;
	// 已经完结的任务id 当此处存在 将在取出数据后 立即被释放
	extern std::set<size_t> ____$hmcPromise_PromiseTaskEndStatusList;
	// 任务数据容器互斥体
	extern std::shared_mutex ____$hmcPromise_rwMutex;
	// 任务数据容器
	extern std::unordered_map<size_t, std::vector<std::any>> ____$hmcPromise_PromiseTaskList;
	// 任务数据 已读取索引 容器
	extern std::unordered_map<size_t, size_t> ____$hmcPromise_promise_task_id_send_index_list;
	extern long ___$Sleep_time;
	/**
	 * @brief 判断此任务id是否已经完成 调用了end()
	 *
	 * @param SessionId
	 * @return true
	 * @return false
	 */
	extern bool isClosed(size_t SessionId);
	/**
	 * @brief 提交数据push进容器
	 *
	 * @param SessionId 任务id
	 * @param data 数据
	 * @return true
	 * @return false
	 */
	extern bool send(size_t SessionId, std::any data = std::any());
	/**
	 * @brief 提交数据push进容器
	 *
	 * @param SessionId 任务id
	 * @param data_list 数据
	 */
	extern void send(size_t SessionId, std::vector<std::any> data_list);
	/**
	 * @brief 提交此ID已经完成 并在 getAll/get 后释放掉容器
	 *
	 * @param SessionId
	 * @param data
	 */
	extern void end(size_t SessionId, std::any data = std::any());
	/**
	 * @brief 判断此id是否未结束
	 *
	 * @param PromiseID 任务id
	 * @param index 如果被赋值则在 容器中判断此索引是否存在
	 * @return true
	 * @return false
	 */
	extern bool exists(size_t PromiseID, size_t index = -1);

	/**
	 * @brief 取出内容并释放掉这部分的any容器 但不移除 并重定向到新的index提供下次获取
	 *
	 * @param PromiseID
	 * @return any
	 */
	extern napi_value getAll(napi_env env, size_t PromiseID, size_t size = 999);

	extern size_t data_size(size_t PromiseID);

	/**
	 * @brief 取出内容并释放掉这部分的any容器 但不移除  如果任务已经结束时候则释放所有关联容器
	 *
	 * @param PromiseID
	 * @return vector<any>
	 */
	extern std::vector<std::any> getAll(size_t PromiseID, size_t size = 999);
	extern int64_t get_next_index(size_t PromiseID);

	extern size_t ___get_open_id();
	/**
	 * @brief 在新的线程 启动一个函数 并传入一个vector<any>指针 以及监听此函数的运行结束的回调
	 *
	 * @param func
	 * @return size_t
	 */
	extern size_t open(std::function<void(std::vector<std::any> *data_list)> func);
	/**
	 * @brief 创建一个新的任务id 并为其开辟容器 但不为其创建 变化管理线程
	 *
	 * @return size_t
	 */
	extern size_t open();
	/**
	 * @brief 在新的线程 启动一个函数 以及监听此函数的运行结束的回调 数据必须由此函数返回
	 *
	 * @param func
	 * @return size_t
	 */
	extern size_t open(std::function<std::any()> func);
	/**
	 * @brief 在新的线程 启动一个函数 以及监听此函数的运行结束的回调
	 *
	 * @param func
	 * @return size_t
	 */
	extern size_t open(std::function<void()> func);

	template <class _Fn, class... _Args>
	extern size_t open2(_Fn &&_Fx, _Args &&..._Ax);

	extern size_t max_id();
	extern std::vector<int> allTasks();
	extern std::vector<int> ongoingTasks();
	extern std::vector<int> completeTasks();
	extern size_t get_sleep_time();
};

extern napi_value _PromiseSession_getAll(napi_env env, napi_callback_info info);

extern napi_value _PromiseSession_stop(napi_env env, napi_callback_info info);
extern napi_value _PromiseSession_isClosed(napi_env env, napi_callback_info info);
extern napi_value _PromiseSession_max_id(napi_env env, napi_callback_info info);
extern napi_value _PromiseSession_data_size(napi_env env, napi_callback_info info);
extern napi_value _PromiseSession_await(napi_env env, napi_callback_info info);
extern napi_value _PromiseSession_set_sleep_time(napi_env env, napi_callback_info info);
extern napi_value _PromiseSession_ongoingTasks(napi_env env, napi_callback_info info);
extern napi_value _PromiseSession_allTasks(napi_env env, napi_callback_info info);
extern napi_value _PromiseSession_completeTasks(napi_env env, napi_callback_info info);
extern napi_value _PromiseSession_get_sleep_time(napi_env env, napi_callback_info info);

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

/*
 使用宏魔法开辟一个 Promise 函数
namespace fu_New_Promise_class NEW_PROMISE_FUNCTION_DEFAULT_FUN;

std::any fu_New_Promise_class::PromiseWorkFunc(std::vector<any> arguments_list) {
	std::any result = std::any();
	return result;
}

napi_value fu_New_Promise_class::format_to_js_value(napi_env env, std::any result_any_data) {
	napi_value result;
	napi_get_null(env, &result);

	if (!result_any_data.has_value()) {
		return result;
	}

	return result;
}

*/
#define NEW_PROMISE_FUNCTION_DEFAULT_FUN                                                           \
	std::any resultSend = std::any();                                                              \
	std::vector<std::any> arguments_list = {};                                                     \
	napi_value format_to_js_value(napi_env env, std::any result_any_data);                         \
	std::any PromiseWorkFunc(std::vector<std::any> arguments_list);                                \
	class PromiseFunction                                                                          \
	{                                                                                              \
	private:                                                                                       \
		static constexpr std::atomic<napi_async_work> work = NULL;                                 \
		static constexpr std::atomic<napi_deferred> deferred = NULL;                               \
                                                                                                   \
	public:                                                                                        \
		static void exports(napi_env env, napi_value exports, std::string name)                    \
		{                                                                                          \
			napi_value exported_function;                                                          \
			napi_create_function(env,                                                              \
								 name.c_str(),                                                     \
								 name.length(),                                                    \
								 startWork,                                                        \
								 NULL,                                                             \
								 &exported_function);                                              \
			napi_set_named_property(env, exports, name.c_str(), exported_function);                \
			napi_wrap(env, exports, NULL, NULL, NULL, NULL);                                       \
		}                                                                                          \
		static void exportsSync(napi_env env, napi_value exports, std::string name)                \
		{                                                                                          \
			napi_value exported_function;                                                          \
			napi_create_function(env,                                                              \
								 name.c_str(),                                                     \
								 name.length(),                                                    \
								 startSync,                                                        \
								 NULL,                                                             \
								 &exported_function);                                              \
			napi_set_named_property(env, exports, name.c_str(), exported_function);                \
			napi_wrap(env, exports, NULL, NULL, NULL, NULL);                                       \
		}                                                                                          \
                                                                                                   \
	protected:                                                                                     \
		static void asyncWorkFun(napi_env env, void *data)                                         \
		{                                                                                          \
			resultSend = PromiseWorkFunc(arguments_list);                                          \
		}                                                                                          \
		static void completeWork(napi_env env, napi_status status, void *data)                     \
		{                                                                                          \
			napi_resolve_deferred(env, deferred, format_to_js_value(env, resultSend));             \
			napi_delete_async_work(env, work);                                                     \
			deferred._Storage._Value = NULL;                                                       \
			work._Storage._Value = NULL;                                                           \
			resultSend.reset();                                                                    \
			resultSend = std::any();                                                               \
			arguments_list.clear();                                                                \
			arguments_list.resize(0);                                                              \
		}                                                                                          \
		static napi_value startWork(napi_env env, napi_callback_info info)                         \
		{                                                                                          \
			napi_value result, work_name, promise;                                                 \
			napi_get_null(env, &result);                                                           \
			std::string work_message = std::string(__FUNCTION__).append("  work_message ->  ");    \
			if (work != NULL)                                                                      \
			{                                                                                      \
				work_message.append("error < Promise workspace has not been released. > ");        \
				napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());                      \
				return result;                                                                     \
			}                                                                                      \
			work_message.append("Node-API Deferred Promise from Async Work Item");                 \
			napi_create_string_utf8(env, work_message.c_str(), work_message.length(), &work_name); \
			napi_async_work addon_napi_async_work = NULL;                                          \
			napi_deferred addon_deferred = NULL;                                                   \
			if (napi_create_promise(env, &addon_deferred, &promise) != napi_ok)                    \
			{                                                                                      \
				work_message.append("error < Promise Creation failed. > ");                        \
				napi_throw_error(env, "Creation_failed", work_message.c_str());                    \
				return result;                                                                     \
			};                                                                                     \
			auto input = hmc_NodeArgsValue(env, info).get_values();                                \
			for (size_t i = 0; i < input.size(); i++)                                              \
			{                                                                                      \
				arguments_list.push_back(input.at(i));                                             \
			}                                                                                      \
			if (napi_create_async_work(env,                                                        \
									   NULL,                                                       \
									   work_name,                                                  \
									   asyncWorkFun,                                               \
									   completeWork, NULL, &addon_napi_async_work) != napi_ok)     \
			{                                                                                      \
				work_message.append("error < Promise Creation work async failed. > ");             \
				napi_throw_error(env, "Creation_failed", work_message.c_str());                    \
				return result;                                                                     \
			};                                                                                     \
			napi_queue_async_work(env, addon_napi_async_work);                                     \
			work._Storage._Value = addon_napi_async_work;                                          \
			deferred._Storage._Value = addon_deferred;                                             \
			return promise;                                                                        \
		}                                                                                          \
		static napi_value startSync(napi_env env, napi_callback_info info)                         \
		{                                                                                          \
			napi_value result, work_name, promise;                                                 \
			napi_get_null(env, &result);                                                           \
			std::any resultSend = std::any();                                                      \
			auto input = hmc_NodeArgsValue(env, info).get_values();                                \
			std::vector<std::any> arguments_list$SP = {};                                          \
			for (size_t i = 0; i < input.size(); i++)                                              \
			{                                                                                      \
				arguments_list$SP.push_back(input.at(i));                                          \
			}                                                                                      \
			startWorkSession(resultSendSessionID, arguments_list$SP);                              \
			try                                                                                    \
			{                                                                                      \
				std::any data = PromiseWorkFunc(arguments_list);                                   \
				return format_to_js_value(env, data);                                              \
			}                                                                                      \
			catch (const std::exception &err)                                                      \
			{                                                                                      \
				napi_throw_error(env, "catch (const std::exception&)", err.what());                \
				return result;                                                                     \
			}                                                                                      \
			catch (...)                                                                            \
			{                                                                                      \
				napi_throw_error(env, "catch (...)", "");                                          \
				return result;                                                                     \
			}                                                                                      \
			return result;                                                                         \
		}                                                                                          \
	};                                                                                             \
	void exports(napi_env env, napi_value exports, std::string name)                               \
	{                                                                                              \
		(new PromiseFunction)->exports(env, exports, name.c_str());                                \
	}                                                                                              \
	void exportsSync(napi_env env, napi_value exports, std::string name)                           \
	{                                                                                              \
		(new PromiseFunction)->exportsSync(env, exports, name.c_str());                            \
	}

#define NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP                                                        \
	std::any resultSend = std::any();                                                              \
	std::vector<std::any> arguments_list = {};                                                     \
	napi_value format_to_js_value(napi_env env, std::any result_any_data);                         \
	std::any PromiseWorkFunc(std::vector<std::any> arguments_list);                                \
	void startWorkSession(size_t resultSendSessionID, std::vector<any> arguments_list$SP)          \
	{                                                                                              \
		thread([resultSendSessionID, arguments_list$SP]()                                          \
			   {\
        auto data = PromiseWorkFunc(arguments_list$SP);\
        hmc_PromiseSession::send(resultSendSessionID, data);\
        hmc_PromiseSession::end(resultSendSessionID); })                                                                                \
			.detach();                                                                             \
	}                                                                                              \
	class PromiseFunction                                                                          \
	{                                                                                              \
	private:                                                                                       \
		static constexpr std::atomic<napi_async_work> work = NULL;                                 \
		static constexpr std::atomic<napi_deferred> deferred = NULL;                               \
                                                                                                   \
	public:                                                                                        \
		static void exports(napi_env env, napi_value exports, std::string name)                    \
		{                                                                                          \
			napi_value exported_function;                                                          \
			napi_create_function(env,                                                              \
								 name.c_str(),                                                     \
								 name.length(),                                                    \
								 startWork,                                                        \
								 NULL,                                                             \
								 &exported_function);                                              \
			napi_set_named_property(env, exports, name.c_str(), exported_function);                \
			napi_wrap(env, exports, NULL, NULL, NULL, NULL);                                       \
		}                                                                                          \
		static void exportsSync(napi_env env, napi_value exports, std::string name)                \
		{                                                                                          \
			napi_value exported_function;                                                          \
			napi_create_function(env,                                                              \
								 name.c_str(),                                                     \
								 name.length(),                                                    \
								 startSync,                                                        \
								 NULL,                                                             \
								 &exported_function);                                              \
			napi_set_named_property(env, exports, name.c_str(), exported_function);                \
			napi_wrap(env, exports, NULL, NULL, NULL, NULL);                                       \
		}                                                                                          \
                                                                                                   \
	protected:                                                                                     \
		static void asyncWorkFun(napi_env env, void *data)                                         \
		{                                                                                          \
			resultSend = PromiseWorkFunc(arguments_list);                                          \
		}                                                                                          \
		static void completeWork(napi_env env, napi_status status, void *data)                     \
		{                                                                                          \
			napi_resolve_deferred(env, deferred, format_to_js_value(env, resultSend));             \
			napi_delete_async_work(env, work);                                                     \
			deferred._Storage._Value = NULL;                                                       \
			work._Storage._Value = NULL;                                                           \
			resultSend.reset();                                                                    \
			resultSend = std::any();                                                               \
			arguments_list.clear();                                                                \
			arguments_list.resize(0);                                                              \
		}                                                                                          \
		static napi_value startWork(napi_env env, napi_callback_info info)                         \
		{                                                                                          \
			napi_value result, work_name, promise;                                                 \
			napi_get_null(env, &result);                                                           \
			std::string work_message = std::string(__FUNCTION__).append("  work_message ->  ");    \
			if (work != NULL)                                                                      \
			{                                                                                      \
				size_t resultSendSessionID = hmc_PromiseSession::open();                           \
				auto input = hmc_NodeArgsValue(env, info).get_values();                            \
				std::vector<any> arguments_list$SP = {};                                           \
				for (size_t i = 0; i < input.size(); i++)                                          \
				{                                                                                  \
					arguments_list$SP.push_back(input.at(i));                                      \
				}                                                                                  \
				startWorkSession(resultSendSessionID, arguments_list$SP);                          \
				return hmc_napi_create_value::Number(env, (int64_t)resultSendSessionID);           \
			}                                                                                      \
			work_message.append("Node-API Deferred Promise from Async Work Item");                 \
			napi_create_string_utf8(env, work_message.c_str(), work_message.length(), &work_name); \
			napi_async_work addon_napi_async_work = NULL;                                          \
			napi_deferred addon_deferred = NULL;                                                   \
			if (napi_create_promise(env, &addon_deferred, &promise) != napi_ok)                    \
			{                                                                                      \
				work_message.append("error < Promise Creation failed. > ");                        \
				napi_throw_error(env, "Creation_failed", work_message.c_str());                    \
				return result;                                                                     \
			};                                                                                     \
			auto input = hmc_NodeArgsValue(env, info).get_values();                                \
			for (size_t i = 0; i < input.size(); i++)                                              \
			{                                                                                      \
				arguments_list.push_back(input.at(i));                                             \
			}                                                                                      \
			if (napi_create_async_work(env,                                                        \
									   NULL,                                                       \
									   work_name,                                                  \
									   asyncWorkFun,                                               \
									   completeWork, NULL, &addon_napi_async_work) != napi_ok)     \
			{                                                                                      \
				work_message.append("error < Promise Creation work async failed. > ");             \
				napi_throw_error(env, "Creation_failed", work_message.c_str());                    \
				return result;                                                                     \
			};                                                                                     \
			napi_queue_async_work(env, addon_napi_async_work);                                     \
			work._Storage._Value = addon_napi_async_work;                                          \
			deferred._Storage._Value = addon_deferred;                                             \
			return promise;                                                                        \
		}                                                                                          \
		static napi_value startSync(napi_env env, napi_callback_info info)                         \
		{                                                                                          \
			napi_value result, work_name, promise;                                                 \
			napi_get_null(env, &result);                                                           \
			std::any resultSend = std::any();                                                      \
			std::vector<std::any> arguments_list = {};                                             \
			auto input = hmc_NodeArgsValue(env, info).get_values();                                \
			for (size_t i = 0; i < input.size(); i++)                                              \
			{                                                                                      \
				arguments_list.push_back(input.at(i));                                             \
			}                                                                                      \
			try                                                                                    \
			{                                                                                      \
				std::any data = PromiseWorkFunc(arguments_list);                                   \
				return format_to_js_value(env, data);                                              \
			}                                                                                      \
			catch (const std::exception &err)                                                      \
			{                                                                                      \
				napi_throw_error(env, "catch (const std::exception&)", err.what());                \
				return result;                                                                     \
			}                                                                                      \
			catch (...)                                                                            \
			{                                                                                      \
				napi_throw_error(env, "catch (...)", "");                                          \
				return result;                                                                     \
			}                                                                                      \
			return result;                                                                         \
		}                                                                                          \
	};                                                                                             \
	void exports(napi_env env, napi_value exports, std::string name)                               \
	{                                                                                              \
		(new PromiseFunction)->exports(env, exports, name.c_str());                                \
	}                                                                                              \
	void exportsSync(napi_env env, napi_value exports, std::string name)                           \
	{                                                                                              \
		(new PromiseFunction)->exportsSync(env, exports, name.c_str());                            \
	}

#define NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP$ARG                                                                                        \
	std::any resultSend = std::any();                                                                                                  \
	std::vector<std::any> arguments_list = {};                                                                                         \
	napi_value format_to_js_value(napi_env env, std::any result_any_data);                                                             \
	void format_arguments_value(napi_env env, napi_callback_info info, std::vector<any> &ArgumentsList, hmc_NodeArgsValue args_value); \
	std::any PromiseWorkFunc(std::vector<std::any> arguments_list);                                                                    \
	void startWorkSession(size_t resultSendSessionID, std::vector<any> arguments_list$SP)                                              \
	{                                                                                                                                  \
		std::thread([resultSendSessionID, arguments_list$SP]()                                                                         \
					{\
        auto data = PromiseWorkFunc(arguments_list$SP);\
        hmc_PromiseSession::send(resultSendSessionID, data);\
        hmc_PromiseSession::end(resultSendSessionID); })                                                                                                               \
			.detach();                                                                                                                 \
	}                                                                                                                                  \
	class PromiseFunction                                                                                                              \
	{                                                                                                                                  \
	private:                                                                                                                           \
		static constexpr std::atomic<napi_async_work> work = NULL;                                                                     \
		static constexpr std::atomic<napi_deferred> deferred = NULL;                                                                   \
                                                                                                                                       \
	public:                                                                                                                            \
		static void exports(napi_env env, napi_value exports, std::string name)                                                        \
		{                                                                                                                              \
			napi_value exported_function;                                                                                              \
			napi_create_function(env,                                                                                                  \
								 name.c_str(),                                                                                         \
								 name.length(),                                                                                        \
								 startWork,                                                                                            \
								 NULL,                                                                                                 \
								 &exported_function);                                                                                  \
			napi_set_named_property(env, exports, name.c_str(), exported_function);                                                    \
			napi_wrap(env, exports, NULL, NULL, NULL, NULL);                                                                           \
		}                                                                                                                              \
		static void exportsSync(napi_env env, napi_value exports, std::string name)                                                    \
		{                                                                                                                              \
			napi_value exported_function;                                                                                              \
			napi_create_function(env,                                                                                                  \
								 name.c_str(),                                                                                         \
								 name.length(),                                                                                        \
								 startSync,                                                                                            \
								 NULL,                                                                                                 \
								 &exported_function);                                                                                  \
			napi_set_named_property(env, exports, name.c_str(), exported_function);                                                    \
			napi_wrap(env, exports, NULL, NULL, NULL, NULL);                                                                           \
		}                                                                                                                              \
                                                                                                                                       \
	protected:                                                                                                                         \
		static void asyncWorkFun(napi_env env, void *data)                                                                             \
		{                                                                                                                              \
			resultSend = PromiseWorkFunc(arguments_list);                                                                              \
		}                                                                                                                              \
		static void completeWork(napi_env env, napi_status status, void *data)                                                         \
		{                                                                                                                              \
			napi_resolve_deferred(env, deferred, format_to_js_value(env, resultSend));                                                 \
			napi_delete_async_work(env, work);                                                                                         \
			deferred._Storage._Value = NULL;                                                                                           \
			work._Storage._Value = NULL;                                                                                               \
			resultSend.reset();                                                                                                        \
			resultSend = std::any();                                                                                                   \
			arguments_list.clear();                                                                                                    \
			arguments_list.resize(0);                                                                                                  \
		}                                                                                                                              \
		static napi_value startWork(napi_env env, napi_callback_info info)                                                             \
		{                                                                                                                              \
			napi_value result, work_name, promise;                                                                                     \
			napi_get_null(env, &result);                                                                                               \
			std::string work_message = std::string(__FUNCTION__).append("  work_message ->  ");                                        \
			if (work != NULL)                                                                                                          \
			{                                                                                                                          \
				size_t resultSendSessionID = hmc_PromiseSession::open();                                                               \
				auto input = hmc_NodeArgsValue(env, info).get_values();                                                                \
				std::vector<any> arguments_list$SP = {};                                                                               \
				for (size_t i = 0; i < input.size(); i++)                                                                              \
				{                                                                                                                      \
					arguments_list$SP.push_back(input.at(i));                                                                          \
				}                                                                                                                      \
				startWorkSession(resultSendSessionID, arguments_list$SP);                                                              \
				startWorkSession(resultSendSessionID, arguments_list$SP);                                                              \
				return hmc_napi_create_value::Number(env, (int64_t)resultSendSessionID);                                               \
			}                                                                                                                          \
			work_message.append("Node-API Deferred Promise from Async Work Item");                                                     \
			napi_create_string_utf8(env, work_message.c_str(), work_message.length(), &work_name);                                     \
			napi_async_work addon_napi_async_work = NULL;                                                                              \
			napi_deferred addon_deferred = NULL;                                                                                       \
			if (napi_create_promise(env, &addon_deferred, &promise) != napi_ok)                                                        \
			{                                                                                                                          \
				work_message.append("error < Promise Creation failed. > ");                                                            \
				napi_throw_error(env, "Creation_failed", work_message.c_str());                                                        \
				return result;                                                                                                         \
			};                                                                                                                         \
			auto input = hmc_NodeArgsValue(env, info);                                                                                 \
			format_arguments_value(env, info, arguments_list, input);                                                                  \
			if (napi_create_async_work(env,                                                                                            \
									   NULL,                                                                                           \
									   work_name,                                                                                      \
									   asyncWorkFun,                                                                                   \
									   completeWork, NULL, &addon_napi_async_work) != napi_ok)                                         \
			{                                                                                                                          \
				work_message.append("error < Promise Creation work async failed. > ");                                                 \
				napi_throw_error(env, "Creation_failed", work_message.c_str());                                                        \
				return result;                                                                                                         \
			};                                                                                                                         \
			napi_queue_async_work(env, addon_napi_async_work);                                                                         \
			work._Storage._Value = addon_napi_async_work;                                                                              \
			deferred._Storage._Value = addon_deferred;                                                                                 \
			return promise;                                                                                                            \
		}                                                                                                                              \
		static napi_value startSync(napi_env env, napi_callback_info info)                                                             \
		{                                                                                                                              \
			napi_value result, work_name, promise;                                                                                     \
			napi_get_null(env, &result);                                                                                               \
			std::any resultSend = std::any();                                                                                          \
			std::vector<std::any> arguments_list = {};                                                                                 \
			auto input = hmc_NodeArgsValue(env, info);                                                                                 \
			format_arguments_value(env, info, arguments_list, input);                                                                  \
			try                                                                                                                        \
			{                                                                                                                          \
				std::any data = PromiseWorkFunc(arguments_list);                                                                       \
				return format_to_js_value(env, data);                                                                                  \
			}                                                                                                                          \
			catch (const std::exception &err)                                                                                          \
			{                                                                                                                          \
				napi_throw_error(env, "catch (const std::exception&)", err.what());                                                    \
				return result;                                                                                                         \
			}                                                                                                                          \
			catch (...)                                                                                                                \
			{                                                                                                                          \
				napi_throw_error(env, "catch (...)", "");                                                                              \
				return result;                                                                                                         \
			}                                                                                                                          \
			return result;                                                                                                             \
		}                                                                                                                              \
	};                                                                                                                                 \
	void exports(napi_env env, napi_value exports, std::string name)                                                                   \
	{                                                                                                                                  \
		(new PromiseFunction)->exports(env, exports, name.c_str());                                                                    \
	}                                                                                                                                  \
	void exportsSync(napi_env env, napi_value exports, std::string name)                                                               \
	{                                                                                                                                  \
		(new PromiseFunction)->exportsSync(env, exports, name.c_str());                                                                \
	}

#define NEW_PROMISE_FUNCTION2_DEFAULT_FUN                                                                                                   \
	napi_value FormatResultValue(napi_env env, std::any *result_any_data);                                                                  \
	std::any PromiseWorkFunc(std::vector<std::any> *arguments_list);                                                                        \
	void AddArgsToCallBack(napi_env env, napi_callback_info info, std::vector<std::any> *ArgumentsList, hmc_NodeArgsValue input);           \
	std::any resultSend = std::any();                                                                                                       \
	std::vector<std::any> arguments_list = {};                                                                                              \
	std::atomic<napi_async_work> work = NULL;                                                                                               \
	std::atomic<napi_deferred> deferred = NULL;                                                                                             \
	void asyncWorkFun(napi_env env, void *data)                                                                                             \
	{                                                                                                                                       \
		resultSend = PromiseWorkFunc(&arguments_list);                                                                                      \
	}                                                                                                                                       \
	void completeWork(napi_env env, napi_status status, void *data)                                                                         \
	{                                                                                                                                       \
		return PromiseFunctionUtil::completeWork(env, status, &work, &deferred, &arguments_list, &resultSend, FormatResultValue);           \
	}                                                                                                                                       \
	napi_value startWork(napi_env env, napi_callback_info info)                                                                             \
	{                                                                                                                                       \
		return PromiseFunctionUtil::startWork(env, info, &work, &deferred, asyncWorkFun, completeWork, &arguments_list, AddArgsToCallBack); \
	}                                                                                                                                       \
	napi_value startSync(napi_env env, napi_callback_info info)                                                                             \
	{                                                                                                                                       \
		return PromiseFunctionUtil::startSync(env, info, PromiseWorkFunc, FormatResultValue, AddArgsToCallBack);                            \
	}

#endif // MODE_INTERNAL_INCLUDE_HMC_NAPI_VALUE_UTIL_HPP

/*



namespace ExpShowContextMenu
{
	NEW_PROMISE_FUNCTION2_DEFAULT_FUN;

	void ExpShowContextMenu::AddArgsToCallBack(napi_env env, napi_callback_info info, std::vector<std::any> *ArgumentsList, hmc_NodeArgsValue input)
	{
		// showContextMenu(hwnd:number, filePath:string|string[], x?:number|null, y?:number|null);
		input.eq(0, {js_null, js_number, js_bigint}, true);
		input.eq(1, {js_string, js_array}, true);

		// hwnd:number
		int64_t ihwnd = at_Number64Or(0, 0);

		HWND hwnd = ihwnd <= 0 ? ::GetForegroundWindow() : (HWND)ihwnd;
		std::variant<std::wstring, std::vector<std::wstring>> filePath;
		int x = 0;
		int y = 0;

		// filePath:string|string[]
		if (input.eq(1, js_string, false))
		{
			filePath = input.getStringWide(1);
		}
		else
		{
			filePath = input.getArrayWstring(1);
		}

		// x?:number|null, y?:number|null

		POINT point = {0};

		if (input.eq({{2, js_number}}, false))
		{
			x = input.getInt(2, 0);
		}

		if (input.eq({{3, js_number}}, false))
		{
			y = input.getInt(2, 0);
		}

		if (x + y == 0)
		{
			POINT point;
			::GetCursorPos(&point);
			x = point.x;
			y = point.y;
		}

		ArgumentsList->push_back(hwnd);

		if (std::holds_alternative<std::wstring>(filePath))
		{
			ArgumentsList->push_back(std::get<std::wstring>(filePath));
		}
		else
		{
			ArgumentsList->push_back(std::get<std::vector<std::wstring>>(filePath));
		}

		ArgumentsList->push_back(x);
		ArgumentsList->push_back(y);
	}

	// 需要异步的函数
	std::any ExpShowContextMenu::PromiseWorkFunc(std::vector<std::any> *arguments_list)
	{
		std::any result = std::any();
		HWND hwnd = std::any_cast<HWND>(arguments_list->at(0));

		int x = std::any_cast<int>(arguments_list->at(2));
		int y = std::any_cast<int>(arguments_list->at(3));

		if (arguments_list->at(1).type() == typeid(std::wstring))
		{
			std::wstring filePath = std::any_cast<std::wstring>(arguments_list->at(1));
			result = hmc_shell_util::showContextMenu(hwnd, filePath, x, y);
		}

		if (arguments_list->at(1).type() == typeid(std::vector<std::wstring>))
		{
			std::vector<std::wstring> filePathList = std::any_cast<std::vector<std::wstring>>(arguments_list->at(1));
			result = hmc_shell_util::showContextMenu(hwnd, filePathList, x, y);
		}

		return result;
	}

	// 格式化<需要异步的函数>返回值到js 返回值
	napi_value ExpShowContextMenu::FormatResultValue(napi_env env, std::any *result_any_data)
	{
		napi_value result;
		napi_get_null(env, &result);

		if (!result_any_data->has_value())
		{
			return result;
		}
		result = as_Boolean(std::any_cast<bool>(result_any_data));
		return result;
	}

};



*/
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

	enum HMC_PROMISEEVAL_TASK_TYPE
	{
		getClipboardFilePaths2 = 1,
		captureBmp2 = 2,
		closeWindow2 = 3,
		getClipboardText2 = 5,
		getThumbnailPng2 = 6,
	};

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
