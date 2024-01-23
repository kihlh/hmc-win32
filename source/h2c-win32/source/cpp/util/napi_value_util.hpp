#pragma once

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

#include "./hmc_string_util.h"

using namespace std;

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

// 导出一个 其他文件的 函数 并设置名称
#define ___EXPORT_NAPI_REMOTE_FN____PROMISE_SESSION                                                    \
                                                EXPORT_NAPI_REMOTE_FNPAIR("_PromiseSession_get",_PromiseSession_getAll),     \
                                                EXPORT_NAPI_REMOTE_FN(_PromiseSession_isClosed),       \
                                                EXPORT_NAPI_REMOTE_FN(_PromiseSession_stop),           \
                                                EXPORT_NAPI_REMOTE_FN(_PromiseSession_max_id),         \
                                                EXPORT_NAPI_REMOTE_FN(_PromiseSession_data_size),      \
                                                EXPORT_NAPI_REMOTE_FN(_PromiseSession_set_sleep_time), \
                                                EXPORT_NAPI_REMOTE_FN(_PromiseSession_await),          \
                                                EXPORT_NAPI_REMOTE_FN(_PromiseSession_ongoingTasks),   \
                                                EXPORT_NAPI_REMOTE_FN(_PromiseSession_completeTasks),  \
                                                EXPORT_NAPI_REMOTE_FN(_PromiseSession_get_sleep_time), \
                                                EXPORT_NAPI_REMOTE_FN(_PromiseSession_allTasks)

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
    extern void buffer_vector(napi_env env, napi_value nodeValue, vector<T>& buffer);
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
    extern string string_utf8(napi_env env, napi_value nodeValue, string defaultValue = string(""));
    /**
     * @brief 获取为utf8标准的文本
     *
     * @param env
     * @param nodeValue
     * @return string
     */
    extern wstring string_utf16(napi_env env, napi_value nodeValue, wstring defaultValue = wstring(L""));
    /**
     * @brief 获取为窄(A)文本
     *
     * @param env
     * @param nodeValue
     * @return string
     */
    extern string string_ansi(napi_env env, napi_value nodeValue, string defaultValue = string(""));
    /**
     * @brief 获取为宽(W)文本
     *
     * @param env
     * @param nodeValue
     * @return wstring
     */
    extern wstring string_wide(napi_env env, napi_value nodeValue, wstring defaultValue = wstring(L""));
    /**
     * @brief 获取文本数组
     *
     * @param env
     * @param nodeValue
     * @return vector<string>
     */
    extern vector<string> array_string_utf8(napi_env env, napi_value nodeValue);
    /**
     * @brief 获取文本数组
     *
     * @param env
     * @param nodeValue
     * @return vector<string>
     */
    extern vector<wstring> array_string_utf16(napi_env env, napi_value nodeValue);
    /**
     * @brief 获取数字数组
     *
     * @param env
     * @param nodeValue
     * @return vector<int>
     */
    extern vector<int> array_int(napi_env env, napi_value nodeValue);
    /**
     * @brief 获取数字数组
     *
     * @param env
     * @param nodeValue
     * @return vector<int>
     */
    extern vector<int64_t> array_int64(napi_env env, napi_value nodeValue);
    /**
     * @brief 获取数字数组
     *
     * @param env
     * @param nodeValue
     * @return vector<int>
     */
    extern vector<double> array_double(napi_env env, napi_value nodeValue);
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
    extern vector<unsigned char> buffer_vector(napi_env env, napi_value nodeValue);
    /**
     * @brief 传入缓冲是utf16的文本
     *
     * @param env
     * @param nodeValue
     * @return wstring
     */
    extern wstring buffer_utf16_strW(napi_env env, napi_value nodeValue);
    /**
     * @brief 传入缓冲是ansi的文本（winapi转换过得）
     *
     * @param env
     * @param nodeValue
     * @return string
     */
    extern string buffer_ansi_strA(napi_env env, napi_value nodeValue);
    /**
     * @brief 传入缓冲是utf8的文本
     *
     * @param env
     * @param nodeValue
     * @return string
     */
    extern string buffer_utf8_strU8(napi_env env, napi_value nodeValue);
    /**
     * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
     * @param env
     * @param nodeValue
     * @return const wchar_t* c标准接口的  const char *
     */
    extern const wchar_t* buffer_utf16_clpStrW(napi_env env, napi_value nodeValue);
    /**
     * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
     * @param env
     * @param nodeValue
     * @return const char* c标准接口的  const char *
     */
    extern const char* buffer_utf8_clpStrU8(napi_env env, napi_value nodeValue);
    /**
     * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
     * @param env
     * @param nodeValue
     * @return const char* c标准接口的  const char *
     */
    extern const char* buffer_ansi_clpStrA(napi_env env, napi_value nodeValue);
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
    extern napi_value get_object_value(napi_env env, napi_value objectValue, string key);
    /**
     * @brief 使用键取值为int
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return int
     */
    extern int get_object_value_int(napi_env env, napi_value objectValue, string key, int defaultValue = 0);
    /**
     * @brief 使用键取值为int64
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return int64_t
     */
    extern int64_t get_object_value_int64(napi_env env, napi_value objectValue, string key, int64_t defaultValue = 0);
    /**
     * @brief 使用键取值为double
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return double
     */
    extern double get_object_value_double(napi_env env, napi_value objectValue, string key, double defaultValue = 0);
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
    extern bool get_object_value_bool(napi_env env, napi_value objectValue, string key, bool defaultValue = false);
    /**
     * @brief 使用键取值为 utf16
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return wstring
     */
    extern wstring get_object_value_utf16(napi_env env, napi_value objectValue, string key, wstring defaultValue = wstring(L""));
    /**
     * @brief 使用键取值为utf8
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return string
     */
    extern string get_object_value_utf8(napi_env env, napi_value objectValue, string key, string defaultValue = string(""));
    /**
     * @brief 使用键取值为ansi
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return string
     */
    extern string get_object_value_ansi(napi_env env, napi_value objectValue, string key, string defaultValue = string(""));
    /**
     * @brief 使用键取值为 RECT
     *
     * @param env
     * @param objectValue
     * @return RECT
     */
    extern RECT rect(napi_env env, napi_value objectValue);
}

namespace hmc_napi_type
{

    /**
     * @brief 获取napi数据的类型文本
     *
     * @param valuetype
     * @return string
     */
    extern string typeName(js_valuetype valuetype);
    /**
     * @brief 获取napi数据的类型文本
     *
     * @param valuetype
     * @return string
     */
    extern string typeName(napi_valuetype valuetype);
    /**
     * @brief 获取napi类型变量名称（人话）
     *
     * @param env
     * @param valuetype
     * @return string
     */
    extern string typeName(napi_env env, napi_value valuetype);

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
    extern bool diff(napi_valuetype valuetype, const napi_valuetype& first, const Args &...args);
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
    extern bool diff(napi_env env, napi_value nodeValue, const napi_valuetype& first, const Args &...args);

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
    extern bool isObjectkeyExists(napi_env env, napi_value objectValue, string key);
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

    // 创建一个布尔型
    napi_value Boolean(napi_env env, bool value = false);
    // 创建一个布尔型
    napi_value Boolean(napi_env env, int value = 0);

    // 返回一个 string utf8 string
    napi_value String(napi_env env, string value);

    // 返回一个 string utf8 string
    napi_value StringA(napi_env env, string value);
    // 返回一个 string utf16 string
    napi_value String(napi_env env, wstring value);
    napi_value String(napi_env env, wchar_t* value);
    napi_value String(napi_env env, char* value);
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
    napi_value Buffer(napi_env env, vector<unsigned char>& buffer);
    napi_value Buffer(napi_env env, void* data, size_t size);

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
    napi_value New(napi_env env, any anyValue);

    napi_value New(napi_env env);

    namespace Array
    {
        /**
         * @brief 支持多种类型的数组
         *
         * @param env
         * @param wstringVector
         * @return napi_value
         */
        napi_value New(napi_env env, vector<napi_value> wstringVector);
        napi_value New(napi_env env, vector<any> wstringVector);
        /**
         * @brief 创建一个全是文本的数组
         *
         * @param env
         * @param stringVector
         * @return napi_value
         */
        napi_value String(napi_env env, vector<string> stringVector);
        napi_value String(napi_env env, vector<wstring> wstringVector);
        /**
         * @brief 创建一个全是数字的数组
         *
         * @param env
         * @param intVector
         * @return napi_value
         */
        napi_value Number(napi_env env, vector<int> intVector);

        /**
         * @brief 创建一个全是数字的数组
         *
         * @param env
         * @param intVector
         * @return napi_value
         */
        napi_value Bigint(napi_env env, vector<int> intVector);
        /**
         * @brief 创建一个全是数字的数组
         *
         * @param env
         * @param intVector
         * @return napi_value
         */
        napi_value Boolean(napi_env env, vector<bool> boolVector);
    }

    namespace Object
    {
        /**
         * @brief 创建一个全是文本的 键值对对象
         *
         * @param env
         * @param mapObject
         * @return napi_value
         */
        napi_value Object(napi_env env, map<string, string> mapObject);
        /**
         * @brief 创建一个全是文本的 键值对对象
         *
         * @param env
         * @param mapObject
         * @return napi_value
         */
        napi_value Object(napi_env env, map<wstring, wstring> mapObject);

        /**
         * @brief 创建一个全是int的 键值对对象
         *
         * @param env
         * @param mapObject
         * @return napi_value
         */
        napi_value Object(napi_env env, map<string, int> mapObject);
        /**
         * @brief 创建一个全是napi_value的 键值对对象
         *
         * @param env
         * @param mapObject
         * @return napi_value
         */
        napi_value Object(napi_env env, map<string, napi_value> mapObject);
        /**
         * @brief 创建一个任意js支持的类型
         *
         * @param env
         * @param mapObject
         * @return napi_value
         */
        napi_value Object(napi_env env, map<string, any> mapObject);
    }

}
class js_value
{
private:
    any data;

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
    string typeName();
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
    string getStringAnsi(string defaultValue = string(""));
    /**
     * @brief 获取指定索引为  String Wide
     *
     * @param index
     * @param defaultValue
     * @return wstring
     */
    wstring getStringWide(wstring defaultValue = wstring(L""));
    /**
     * @brief 获取指定索引为  String Utf8
     *
     * @param index
     * @param defaultValue
     * @return string
     */
    string getStringUtf8(string defaultValue = string(""));
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
    vector<unsigned char> getBuffer(vector<unsigned char> defaultValue = {});
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
    vector<string> getArrayString(vector<string> defaultValue = {});
    /**
     * @brief 获取指定索引为 int 数组
     *
     * @param index
     * @param defaultValue
     * @return vector<int>
     */
    vector<int> getArrayInt(vector<int> defaultValue = {});
    /**
     * @brief 获取指定索引为 utf16 数组
     *
     * @param index
     * @param defaultValue
     * @return vector<wstring>
     */
    vector<wstring> getArrayWstring(vector<wstring> defaultValue = {});
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
    bool isObjectkeyExists(napi_env env, napi_value objectValue, string key);
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
    string getStringAnsi(size_t index, string defaultValue = string(""));
    /**
     * @brief 获取指定索引为  String Wide
     *
     * @param index
     * @param defaultValue
     * @return wstring
     */
    wstring getStringWide(size_t index, wstring defaultValue = wstring(L""));
    /**
     * @brief 获取指定索引为  String Utf8
     *
     * @param index
     * @param defaultValue
     * @return string
     */
    string getStringUtf8(size_t index, string defaultValue = string(""));
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
    vector<unsigned char> getBuffer(size_t index, vector<unsigned char> defaultValue = {});
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
    vector<string> getArrayString(size_t index, vector<string> defaultValue = {});
    /**
     * @brief 获取指定索引为 int 数组
     *
     * @param index
     * @param defaultValue
     * @return vector<int>
     */
    vector<int> getArrayInt(size_t index, vector<int> defaultValue = {});
    /**
     * @brief 获取指定索引为 utf16 数组
     *
     * @param index
     * @param defaultValue
     * @return vector<wstring>
     */
    vector<wstring> getArrayWstring(size_t index, vector<wstring> defaultValue = {});
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
    bool eq(vector<std::tuple<size_t, js_valuetype>> eq_type, bool throw_error = false);

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
    bool eq(vector<std::tuple<size_t, napi_valuetype>> eq_type, bool throw_error = false);
    /**
     * @brief 判断当前传入的值是否是期待值
     *
     * @param eq_type
     * @return true
     * @return false
     */
    bool eq(size_t index, vector<js_valuetype> type_list = {}, bool throw_error = false);
    /**
     * @brief 判断当前传入的值是否是期待值
     *
     * @param eq_type
     * @return true
     * @return false
     */
    bool eq(size_t index, vector<napi_valuetype> type_list = {}, bool throw_error = false);
    /**
     * @brief 获取类型列表
     *
     * @return vector<js_valuetype>
     */
    vector<js_valuetype> getType();
    /**
     * @brief 获取指定索引的 类型
     *
     * @param index
     * @return js_valuetype
     */
    js_valuetype getType(size_t index);
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
    extern std::unordered_map<size_t, vector<any>> ____$hmcPromise_PromiseTaskList;
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
    extern bool send(size_t SessionId, any data = any());
    /**
     * @brief 提交数据push进容器
     *
     * @param SessionId 任务id
     * @param data_list 数据
     */
    extern void send(size_t SessionId, vector<any> data_list);
    /**
     * @brief 提交此ID已经完成 并在 getAll/get 后释放掉容器
     *
     * @param SessionId
     * @param data
     */
    extern void end(size_t SessionId, any data = any());
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
    extern vector<any> getAll(size_t PromiseID, size_t size = 999);
    extern int64_t get_next_index(size_t PromiseID);

    extern size_t ___get_open_id();
    /**
     * @brief 在新的线程 启动一个函数 并传入一个vector<any>指针 以及监听此函数的运行结束的回调
     *
     * @param func
     * @return size_t
     */
    extern size_t open(std::function<void(vector<any>* data_list)> func);
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
    extern size_t open(std::function<any()> func);
    /**
     * @brief 在新的线程 启动一个函数 以及监听此函数的运行结束的回调
     *
     * @param func
     * @return size_t
     */
    extern size_t open(std::function<void()> func);

    template <class _Fn, class... _Args>
    extern size_t open2(_Fn&& _Fx, _Args &&..._Ax);

    extern size_t max_id();
    extern vector<int> allTasks();
    extern vector<int> ongoingTasks();
    extern vector<int> completeTasks();
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
#define NEW_PROMISE_FUNCTION_DEFAULT_FUN \
    std::any resultSend = std::any();\
    std::vector<any> arguments_list = {};\
    napi_value format_to_js_value(napi_env env, std::any result_any_data);\
    std::any PromiseWorkFunc(std::vector<std::any> arguments_list);\
    class PromiseFunction\
    {\
    private:\
        static constexpr std::atomic<napi_async_work> work = NULL;\
        static constexpr std::atomic<napi_deferred> deferred = NULL;\
    public:\
        static void exports(napi_env env, napi_value exports, std::string name)\
        {\
            napi_value exported_function;\
            napi_create_function(env,\
                                 name.c_str(),\
                                 name.length(),\
                                 startWork,\
                                 NULL,\
                                 &exported_function);\
            napi_set_named_property(env, exports, name.c_str(), exported_function);\
            napi_wrap(env, exports, NULL, NULL, NULL, NULL);\
        }\
        static void exportsSync(napi_env env, napi_value exports, std::string name)\
        {\
            napi_value exported_function;\
            napi_create_function(env,\
                                 name.c_str(),\
                                 name.length(),\
                                 startSync,\
                                 NULL,\
                                 &exported_function);\
            napi_set_named_property(env, exports, name.c_str(), exported_function);\
            napi_wrap(env, exports, NULL, NULL, NULL, NULL);\
        }\
    protected:\
        static void asyncWorkFun(napi_env env, void *data)\
        {\
            resultSend = PromiseWorkFunc(arguments_list);\
        }\
        static void completeWork(napi_env env, napi_status status, void *data)\
        {\
            napi_resolve_deferred(env, deferred, format_to_js_value(env, resultSend));\
            napi_delete_async_work(env, work);\
            deferred._Storage._Value = NULL;\
            work._Storage._Value = NULL;\
            resultSend.reset();\
            resultSend = std::any();\
            arguments_list.clear();\
            arguments_list.resize(0);\
        }\
        static napi_value startWork(napi_env env, napi_callback_info info)\
        {\
            napi_value result, work_name, promise;\
            napi_get_null(env, &result);\
            std::string work_message = std::string(__FUNCTION__).append("  work_message ->  ");\
            if (work != NULL)\
            {\
                work_message.append("error < Promise workspace has not been released. > ");\
                napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());\
                return result;\
            }\
            work_message.append("Node-API Deferred Promise from Async Work Item");\
            napi_create_string_utf8(env, work_message.c_str(), work_message.length(), &work_name);\
            napi_async_work addon_napi_async_work = NULL;\
            napi_deferred addon_deferred = NULL;\
            if (napi_create_promise(env, &addon_deferred, &promise) != napi_ok)\
            {\
                work_message.append("error < Promise Creation failed. > ");\
                napi_throw_error(env, "Creation_failed", work_message.c_str());\
                return result;\
            };\
            auto input = hmc_NodeArgsValue(env, info).get_values();\
            for (size_t i = 0; i < input.size(); i++)\
            {\
                arguments_list.push_back(input.at(i));\
            }\
            if (napi_create_async_work(env,\
                                       NULL,\
                                       work_name,\
                                       asyncWorkFun,\
                                       completeWork, NULL, &addon_napi_async_work) != napi_ok)\
            {\
                work_message.append("error < Promise Creation work async failed. > ");\
                napi_throw_error(env, "Creation_failed", work_message.c_str());\
                return result;\
            };\
            napi_queue_async_work(env, addon_napi_async_work);\
            work._Storage._Value = addon_napi_async_work;\
            deferred._Storage._Value = addon_deferred;\
            return promise;\
        }\
        static napi_value startSync(napi_env env, napi_callback_info info)\
        {\
            napi_value result, work_name, promise;\
            napi_get_null(env, &result);\
            std::any resultSend = std::any();\
            std::vector<std::any> arguments_list = {};\
            auto input = hmc_NodeArgsValue(env, info).get_values();\
            for (size_t i = 0; i < input.size(); i++)\
            {\
                arguments_list.push_back(input.at(i));\
            }\
            try\
            {\
                std::any data = PromiseWorkFunc(arguments_list);\
                return format_to_js_value(env, data);\
            }\
            catch (const std::exception &err)\
            {\
                napi_throw_error(env, "catch (const std::exception&)", err.what());\
                return result;\
            }\
            catch (...)\
            {\
                napi_throw_error(env, "catch (...)", "");\
                return result;\
            }\
            return result;\
        }\
    };\
    void exports(napi_env env, napi_value exports, std::string name)\
    {\
        (new PromiseFunction)->exports(env, exports, name.c_str());\
    }\
    void exportsSync(napi_env env, napi_value exports, std::string name)\
    {\
        (new PromiseFunction)->exportsSync(env, exports, name.c_str());\
    }




#define NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP \
    std::any resultSend = std::any();\
    std::vector<any> arguments_list = {};\
    napi_value format_to_js_value(napi_env env, std::any result_any_data);\
    std::any PromiseWorkFunc(std::vector<std::any> arguments_list);\
     void startWorkSession(size_t resultSendSessionID) {\
thread([resultSendSessionID]()\
    {\
        auto data = PromiseWorkFunc(arguments_list);\
        hmc_PromiseSession::send(resultSendSessionID, data);\
        hmc_PromiseSession::end(resultSendSessionID);\
    }).detach();}\
    class PromiseFunction\
    {\
    private:\
        static constexpr std::atomic<napi_async_work> work = NULL;\
        static constexpr std::atomic<napi_deferred> deferred = NULL;\
    public:\
        static void exports(napi_env env, napi_value exports, std::string name)\
        {\
            napi_value exported_function;\
            napi_create_function(env,\
                                 name.c_str(),\
                                 name.length(),\
                                 startWork,\
                                 NULL,\
                                 &exported_function);\
            napi_set_named_property(env, exports, name.c_str(), exported_function);\
            napi_wrap(env, exports, NULL, NULL, NULL, NULL);\
        }\
        static void exportsSync(napi_env env, napi_value exports, std::string name)\
        {\
            napi_value exported_function;\
            napi_create_function(env,\
                                 name.c_str(),\
                                 name.length(),\
                                 startSync,\
                                 NULL,\
                                 &exported_function);\
            napi_set_named_property(env, exports, name.c_str(), exported_function);\
            napi_wrap(env, exports, NULL, NULL, NULL, NULL);\
        }\
    protected:\
        static void asyncWorkFun(napi_env env, void *data)\
        {\
            resultSend = PromiseWorkFunc(arguments_list);\
        }\
        static void completeWork(napi_env env, napi_status status, void *data)\
        {\
            napi_resolve_deferred(env, deferred, format_to_js_value(env, resultSend));\
            napi_delete_async_work(env, work);\
            deferred._Storage._Value = NULL;\
            work._Storage._Value = NULL;\
            resultSend.reset();\
            resultSend = std::any();\
            arguments_list.clear();\
            arguments_list.resize(0);\
        }\
        static napi_value startWork(napi_env env, napi_callback_info info)\
        {\
            napi_value result, work_name, promise;\
            napi_get_null(env, &result);\
            std::string work_message = std::string(__FUNCTION__).append("  work_message ->  ");\
            if (work != NULL)\
            {\
                size_t resultSendSessionID = hmc_PromiseSession::open();\
            auto input = hmc_NodeArgsValue(env, info).get_values();\
            for (size_t i = 0; i < input.size(); i++)\
            {\
                arguments_list.push_back(input.at(i));\
            }\
                   startWorkSession(resultSendSessionID); \
                return hmc_napi_create_value::Number(env,(int64_t)resultSendSessionID);\
            }\
            work_message.append("Node-API Deferred Promise from Async Work Item");\
            napi_create_string_utf8(env, work_message.c_str(), work_message.length(), &work_name);\
            napi_async_work addon_napi_async_work = NULL;\
            napi_deferred addon_deferred = NULL;\
            if (napi_create_promise(env, &addon_deferred, &promise) != napi_ok)\
            {\
                work_message.append("error < Promise Creation failed. > ");\
                napi_throw_error(env, "Creation_failed", work_message.c_str());\
                return result;\
            };\
            auto input = hmc_NodeArgsValue(env, info).get_values();\
            for (size_t i = 0; i < input.size(); i++)\
            {\
                arguments_list.push_back(input.at(i));\
            }\
            if (napi_create_async_work(env,\
                                       NULL,\
                                       work_name,\
                                       asyncWorkFun,\
                                       completeWork, NULL, &addon_napi_async_work) != napi_ok)\
            {\
                work_message.append("error < Promise Creation work async failed. > ");\
                napi_throw_error(env, "Creation_failed", work_message.c_str());\
                return result;\
            };\
            napi_queue_async_work(env, addon_napi_async_work);\
            work._Storage._Value = addon_napi_async_work;\
            deferred._Storage._Value = addon_deferred;\
            return promise;\
        }\
        static napi_value startSync(napi_env env, napi_callback_info info)\
        {\
            napi_value result, work_name, promise;\
            napi_get_null(env, &result);\
            std::any resultSend = std::any();\
            std::vector<std::any> arguments_list = {};\
            auto input = hmc_NodeArgsValue(env, info).get_values();\
            for (size_t i = 0; i < input.size(); i++)\
            {\
                arguments_list.push_back(input.at(i));\
            }\
            try\
            {\
                std::any data = PromiseWorkFunc(arguments_list);\
                return format_to_js_value(env, data);\
            }\
            catch (const std::exception &err)\
            {\
                napi_throw_error(env, "catch (const std::exception&)", err.what());\
                return result;\
            }\
            catch (...)\
            {\
                napi_throw_error(env, "catch (...)", "");\
                return result;\
            }\
            return result;\
        }\
    };\
    void exports(napi_env env, napi_value exports, std::string name)\
    {\
        (new PromiseFunction)->exports(env, exports, name.c_str());\
    }\
    void exportsSync(napi_env env, napi_value exports, std::string name)\
    {\
        (new PromiseFunction)->exportsSync(env, exports, name.c_str());\
    }




#define NEW_PROMISE_FUNCTION_DEFAULT_FUN$SP$ARG \
    std::any resultSend = std::any();\
    std::vector<any> arguments_list = {};\
    napi_value format_to_js_value(napi_env env, std::any result_any_data);\
    void format_arguments_value(napi_env env, napi_callback_info info,std::vector<any> &ArgumentsList,hmc_NodeArgsValue args_value);\
    std::any PromiseWorkFunc(std::vector<std::any> arguments_list);\
     void startWorkSession(size_t resultSendSessionID) {\
thread([resultSendSessionID]()\
    {\
        auto data = PromiseWorkFunc(arguments_list);\
        hmc_PromiseSession::send(resultSendSessionID, data);\
        hmc_PromiseSession::end(resultSendSessionID);\
    }).detach();}\
    class PromiseFunction\
    {\
    private:\
        static constexpr std::atomic<napi_async_work> work = NULL;\
        static constexpr std::atomic<napi_deferred> deferred = NULL;\
    public:\
        static void exports(napi_env env, napi_value exports, std::string name)\
        {\
            napi_value exported_function;\
            napi_create_function(env,\
                                 name.c_str(),\
                                 name.length(),\
                                 startWork,\
                                 NULL,\
                                 &exported_function);\
            napi_set_named_property(env, exports, name.c_str(), exported_function);\
            napi_wrap(env, exports, NULL, NULL, NULL, NULL);\
        }\
        static void exportsSync(napi_env env, napi_value exports, std::string name)\
        {\
            napi_value exported_function;\
            napi_create_function(env,\
                                 name.c_str(),\
                                 name.length(),\
                                 startSync,\
                                 NULL,\
                                 &exported_function);\
            napi_set_named_property(env, exports, name.c_str(), exported_function);\
            napi_wrap(env, exports, NULL, NULL, NULL, NULL);\
        }\
    protected:\
        static void asyncWorkFun(napi_env env, void *data)\
        {\
            resultSend = PromiseWorkFunc(arguments_list);\
        }\
        static void completeWork(napi_env env, napi_status status, void *data)\
        {\
            napi_resolve_deferred(env, deferred, format_to_js_value(env, resultSend));\
            napi_delete_async_work(env, work);\
            deferred._Storage._Value = NULL;\
            work._Storage._Value = NULL;\
            resultSend.reset();\
            resultSend = std::any();\
            arguments_list.clear();\
            arguments_list.resize(0);\
        }\
        static napi_value startWork(napi_env env, napi_callback_info info)\
        {\
            napi_value result, work_name, promise;\
            napi_get_null(env, &result);\
            std::string work_message = std::string(__FUNCTION__).append("  work_message ->  ");\
            if (work != NULL)\
            {\
                size_t resultSendSessionID = hmc_PromiseSession::open();\
            auto input = hmc_NodeArgsValue(env, info).get_values();\
            for (size_t i = 0; i < input.size(); i++)\
            {\
                arguments_list.push_back(input.at(i));\
            }\
                   startWorkSession(resultSendSessionID); \
                return hmc_napi_create_value::Number(env,(int64_t)resultSendSessionID);\
            }\
            work_message.append("Node-API Deferred Promise from Async Work Item");\
            napi_create_string_utf8(env, work_message.c_str(), work_message.length(), &work_name);\
            napi_async_work addon_napi_async_work = NULL;\
            napi_deferred addon_deferred = NULL;\
            if (napi_create_promise(env, &addon_deferred, &promise) != napi_ok)\
            {\
                work_message.append("error < Promise Creation failed. > ");\
                napi_throw_error(env, "Creation_failed", work_message.c_str());\
                return result;\
            };\
            auto input = hmc_NodeArgsValue(env, info);\
            format_arguments_value(env, info,arguments_list,input);\
            if (napi_create_async_work(env,\
                                       NULL,\
                                       work_name,\
                                       asyncWorkFun,\
                                       completeWork, NULL, &addon_napi_async_work) != napi_ok)\
            {\
                work_message.append("error < Promise Creation work async failed. > ");\
                napi_throw_error(env, "Creation_failed", work_message.c_str());\
                return result;\
            };\
            napi_queue_async_work(env, addon_napi_async_work);\
            work._Storage._Value = addon_napi_async_work;\
            deferred._Storage._Value = addon_deferred;\
            return promise;\
        }\
        static napi_value startSync(napi_env env, napi_callback_info info)\
        {\
            napi_value result, work_name, promise;\
            napi_get_null(env, &result);\
            std::any resultSend = std::any();\
            std::vector<std::any> arguments_list = {};\
            auto input = hmc_NodeArgsValue(env, info);\
            format_arguments_value(env, info,arguments_list,input);\
            try\
            {\
                std::any data = PromiseWorkFunc(arguments_list);\
                return format_to_js_value(env, data);\
            }\
            catch (const std::exception &err)\
            {\
                napi_throw_error(env, "catch (const std::exception&)", err.what());\
                return result;\
            }\
            catch (...)\
            {\
                napi_throw_error(env, "catch (...)", "");\
                return result;\
            }\
            return result;\
        }\
    };\
    void exports(napi_env env, napi_value exports, std::string name)\
    {\
        (new PromiseFunction)->exports(env, exports, name.c_str());\
    }\
    void exportsSync(napi_env env, napi_value exports, std::string name)\
    {\
        (new PromiseFunction)->exportsSync(env, exports, name.c_str());\
    }
#endif // MODE_INTERNAL_INCLUDE_HMC_NAPI_VALUE_UTIL_HPP