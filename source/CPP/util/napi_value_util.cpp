#include "../pch.h"

#include "./napi_value_util.hpp"

// ?hmc_napi_util::type
// 负责类型判断的逻辑
// ------------------------------------------------------------------------------------------------------

/**
 * @brief 获取napi数据的类型文本
 *
 * @param valuetype
 * @return string
 */
string hmc_napi_type::typeName(napi_valuetype valuetype)
{
    string getTypeName = string();
    switch (valuetype)
    {
    case napi_null:
        getTypeName.append("null");
        break;
    case napi_number:
        getTypeName.append("number");
        break;
    case napi_string:
        getTypeName.append("string");
        break;
    case napi_undefined:
        getTypeName.append("undefined");
        break;
    case napi_object:
        getTypeName.append("object");
        break;
    case napi_function:
        getTypeName.append("function");
        break;
    case napi_boolean:
        getTypeName.append("boolean");
        break;
    default:
        getTypeName.append("unknown");
    }
    return getTypeName;
}

/**
 * @brief 获取napi数据的类型文本
 *
 * @param valuetype
 * @return string
 */
string hmc_napi_type::typeName(js_valuetype valuetype)
{
    if (valuetype < 9527)
    {
        return typeName((napi_valuetype)(valuetype));
    }
    string getTypeName = string();
    switch (valuetype)
    {
    case js_valuetype::js_array:
        getTypeName.append("array<any>");
        break;
    case js_valuetype::js_date:
        getTypeName.append("date");
        break;
    case js_valuetype::js_error:
        getTypeName.append("error");
        break;
    case js_valuetype::js_buffer:
        getTypeName.append("buffer");
        break;
    case js_valuetype::js_point:
        getTypeName.append("{x:number,y:number}");
        break;
    case js_valuetype::js_rect:
        getTypeName.append("{left:number,top:number,right:number,bottom:number}");
        break;
    // case js_valuetype::js_array_string:
    //     getTypeName.append("array<string>");
    //     break;
    // case js_valuetype::js_array_number:
    //     getTypeName.append("array<number>");
    //     break;
    // case js_valuetype::js_array_boolean:
    //     getTypeName.append("array<boolean>");
    //     break;
    // case js_valuetype::js_array_bigint:
    //     getTypeName.append("array<bigint>");
    //     break;
    case js_valuetype::js_promise:
        getTypeName.append("array<promise>");
        break;
    case js_valuetype::js_promise_function:
        getTypeName.append("function< promise <any> >");
        break;
    default:
        getTypeName.append("unknown");
    }
    return getTypeName;
}

js_valuetype hmc_napi_type::getType(napi_env env, napi_value value_input)
{
    js_valuetype result = js_valuetype::js_unknown;
    bool is_type_temp = false;

    napi_valuetype value_type;
    napi_typeof(env, value_input, &value_type);

    switch (value_type)
    {
    case napi_undefined:
    case napi_null:
    case napi_boolean:
    case napi_number:
    case napi_string:
    case napi_symbol:
    case napi_external:
    case napi_bigint:
    {
        return (js_valuetype)value_type;
    }
    case napi_object:
    {
        if (
            isObjectkeyExists(env, value_input, "x") &&
            isObjectkeyExists(env, value_input, "y") &&
            isNumber(env, hmc_napi_get_value::get_object_value(env, value_input, "x")) &&
            isNumber(env, hmc_napi_get_value::get_object_value(env, value_input, "x")))
        {
            return js_point;
        }

        if (
            isObjectkeyExists(env, value_input, "bottom") &&
            isObjectkeyExists(env, value_input, "right") &&
            isObjectkeyExists(env, value_input, "top") &&
            isObjectkeyExists(env, value_input, "left") &&
            isNumber(env, hmc_napi_get_value::get_object_value(env, value_input, "bottom")) &&
            isNumber(env, hmc_napi_get_value::get_object_value(env, value_input, "right")) &&
            isNumber(env, hmc_napi_get_value::get_object_value(env, value_input, "top")) &&
            isNumber(env, hmc_napi_get_value::get_object_value(env, value_input, "left")))
        {
            return js_rect;
        }

        return js_object;
    }
    case napi_function:
    {
        napi_is_promise(env, value_input, &is_type_temp);
        if (is_type_temp)
        {
            return js_promise_function;
        }
        return js_function;
    }
    };

    napi_is_array(env, value_input, &is_type_temp);
    if (is_type_temp)
    {
        return js_array;
    }

    napi_is_error(env, value_input, &is_type_temp);
    if (is_type_temp)
    {
        return js_error;
    }

    napi_is_buffer(env, value_input, &is_type_temp);
    if (is_type_temp)
    {
        return js_buffer;
    }

    napi_is_date(env, value_input, &is_type_temp);
    if (is_type_temp)
    {
        return js_date;
    }

    napi_is_promise(env, value_input, &is_type_temp);
    if (is_type_temp)
    {
        return js_promise;
    }

    return result;
}

/**
 * @brief 获取napi类型变量名称（人话）
 *
 * @param env
 * @param valuetype
 * @return string
 */
string hmc_napi_type::typeName(napi_env env, napi_value valuetype)
{
    napi_valuetype value_type;
    napi_typeof(env, valuetype, &value_type);
    return typeName(value_type);
}

/**
 * @brief 对比两个变量类型是否相等
 *
 * @param valuetype
 * @param valuetype2
 * @return BOOL
 */
bool hmc_napi_type::diff(napi_valuetype valuetype, napi_valuetype valuetype2)
{
    return (valuetype == valuetype2);
}

/**
 * @brief 判断值与类型是否一致
 *
 * @param env
 * @param jsValue
 * @param valuetype
 * @return true
 * @return false
 */
bool hmc_napi_type::diff(napi_env env, napi_value jsValue, napi_valuetype valuetype)
{
    napi_valuetype value_type;
    napi_typeof(env, jsValue, &value_type);
    return (valuetype == value_type);
}

/**
 * @brief 判断两个值的类型是否一致
 *
 * @param env
 * @param jsValue
 * @param jsValue2
 * @return true
 * @return false
 */
bool hmc_napi_type::diff(napi_env env, napi_value jsValue, napi_value jsValue2)
{
    napi_valuetype value_type;
    napi_typeof(env, jsValue, &value_type);
    napi_valuetype value_type2;
    napi_typeof(env, jsValue2, &value_type2);
    return (value_type2 == value_type);
}

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
bool hmc_napi_type::diff(napi_valuetype valuetype, const napi_valuetype &first, const Args &...args)
{
    napi_valuetype value_type;
    napi_typeof(env, nodeValue, &value_type);
    int result = false;

    napi_valuetype temp[] = {first, args...};
    size_t length = sizeof(temp) / sizeof(temp[0]);

    for (size_t i = 0; i < length; i++)
    {
        if (temp[i] == value_type)
            return temp[i];
    }

    return result;
}

template <typename... Args>
bool hmc_napi_type::diff(napi_env env, napi_value nodeValue, const napi_valuetype &first, const Args &...args)
{
    napi_valuetype value_type;
    napi_typeof(env, nodeValue, &value_type);
    bool result = false;

    napi_valuetype temp[] = {first, args...};
    size_t length = sizeof(temp) / sizeof(temp[0]);

    for (size_t i = 0; i < length; i++)
    {
        if (temp[i] == value_type)
        {
            return true;
        }
    }

    return result;
}

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
bool hmc_napi_type::argsSize(napi_env env, size_t argLength, int minLength, int maxLength)
{
    if (argLength >= minLength && argLength <= maxLength)
    {
        return true;
    }
    else
    {
        napi_throw_error(env, "EINVAL",
                         string()
                             .append("The current number of parameters passed is lower than required. The input is [")
                             .append(to_string(argLength))
                             .append("], and the ideal number of parameters should be [")
                             .append(to_string(minLength))
                             .append("].\n")
                             .c_str());
        return false;
    }
}

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
bool hmc_napi_type::argsSize(napi_env env, size_t argLength, int minLength)
{
    if (argLength >= minLength)
    {
        return true;
    }
    else
    {
        napi_throw_error(env, "EINVAL",
                         string()
                             .append("The current number of parameters passed is lower than required. The input is [")
                             .append(to_string(argLength))
                             .append("], and the ideal number of parameters should be [")
                             .append(to_string(minLength))
                             .append("].\n")
                             .c_str());
        return false;
    }
}

/**
 * @brief 是buff
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isBuffer(napi_env env, napi_value value)
{
    bool isBuffer;
    napi_is_buffer(env, value, &isBuffer);
    return isBuffer;
}

/**
 * @brief 是文本
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isString(napi_env env, napi_value value)
{
    napi_valuetype type;
    napi_typeof(env, value, &type);
    return type == napi_string;
}

/**
 * @brief 是数字
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isNumber(napi_env env, napi_value value)
{
    napi_valuetype type;
    napi_typeof(env, value, &type);
    return type == napi_number;
}

/**
 * @brief 是布尔
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isBoolean(napi_env env, napi_value value)
{
    napi_valuetype type;
    napi_typeof(env, value, &type);
    return type == napi_boolean;
}

/**
 * @brief 是 Bigint
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isBigint(napi_env env, napi_value value)
{
    napi_valuetype type;
    napi_typeof(env, value, &type);
    return type == napi_bigint;
}

/**
 * @brief 是函数
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isFunction(napi_env env, napi_value value)
{
    napi_valuetype type;
    napi_typeof(env, value, &type);
    return type == napi_function;
}

/**
 * @brief 是对象
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isObject(napi_env env, napi_value value)
{
    napi_valuetype type;
    napi_typeof(env, value, &type);
    return type == napi_object;
}

/**
 * @brief 是 Undefined
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isUndefined(napi_env env, napi_value value)
{
    napi_valuetype type;
    napi_typeof(env, value, &type);
    return type == napi_undefined;
}

/**
 * @brief 是null
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isNull(napi_env env, napi_value value)
{
    napi_valuetype type;
    napi_typeof(env, value, &type);
    return type == napi_null;
}

/**
 * @brief 在 JavaScript 中显示为普通对象
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isExternal(napi_env env, napi_value value)
{
    napi_valuetype type;
    napi_typeof(env, value, &type);
    return type == napi_external;
}

/**
 * @brief 是 C Point
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isPoint(napi_env env, napi_value value)
{
    return getType(env, value) == js_point;
}

/**
 * @brief 是 Promise
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isPromise(napi_env env, napi_value value)
{
    return getType(env, value) == js_promise;
}

/**
 * @brief 是 C Rect
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isRect(napi_env env, napi_value value)
{
    return getType(env, value) == js_rect;
}

/**
 * @brief 判断是否是 obj 并且包含了 此key
 *
 * @param env
 * @param objectValue
 * @param key
 * @return true
 * @return false
 */
bool hmc_napi_type::isObjectkeyExists(napi_env env, napi_value objectValue, string key)
{
    bool has_property = false;

    if (!isObject(env, objectValue))
    {
        return has_property;
    }

    napi_has_named_property(env, objectValue, key.c_str(), &has_property);

    return has_property;
}

/**
 * @brief 是数组
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isArray(napi_env env, napi_value value)
{
    bool result = false;
    napi_is_array(env, value, &result);
    return result;
}

/**
 * @brief 是Date
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isDate(napi_env env, napi_value value)
{
    bool result = false;
    napi_is_date(env, value, &result);
    return result;
}

/**
 * @brief 是 Error
 *
 * @param env
 * @param value
 * @return true
 * @return false
 */
bool hmc_napi_type::isError(napi_env env, napi_value value)
{
    bool result = false;
    napi_is_error(env, value, &result);
    return result;
}

// ?hmc_napi_util::get_value
// 主要负责 获取值的逻辑
// ------------------------------------------------------------------------------------------------------

/**
 * @brief 数字转int
 *
 * @param env
 * @param nodeValue
 * @return int
 */
int hmc_napi_get_value::number_int(napi_env env, napi_value nodeValue, int defaultValue)
{
    int result = defaultValue;

    if (hmc_napi_type::diff(env, nodeValue, napi_number, napi_boolean))
    {
        napi_get_value_int32(env, nodeValue, &result);
        return result;
    }

    else if (hmc_napi_type::diff(env, nodeValue, napi_undefined, napi_null))
    {
        return result;
    }
    else
    {
        //_hmc_debug
    }

    return result;
}

/**
 * @brief 数字转int64
 *
 * @param env
 * @param nodeValue
 * @return int64_t
 */
int64_t hmc_napi_get_value::number_int64(napi_env env, napi_value nodeValue, int64_t defaultValue)
{
    int64_t result = defaultValue;

    if (hmc_napi_type::diff(env, nodeValue, napi_number, napi_boolean))
    {
        napi_get_value_int64(env, nodeValue, &result);
        return result;
    }
    else if (hmc_napi_type::diff(env, nodeValue, napi_bigint))
    {
        bool lossless;
        napi_get_value_bigint_int64(env, nodeValue, &result, &lossless);
        return result;
    }
    else if (hmc_napi_type::diff(env, nodeValue, napi_undefined, napi_boolean, napi_null))
    {
        return result;
    }
    else
    {
        //_hmc_debug
    }

    {
        // _hmc_debug
    }

    return result;
}

/**
 * @brief 数字转64位浮点
 *
 * @param env
 * @param nodeValue
 * @return double
 */
double hmc_napi_get_value::number_double(napi_env env, napi_value nodeValue, int defaultValue)
{
    double result = defaultValue;

    if (hmc_napi_type::diff(env, nodeValue, napi_number) || hmc_napi_type::diff(env, nodeValue, napi_boolean))
    {
        napi_get_value_double(env, nodeValue, &result);
        return result;
    }
    else if (hmc_napi_type::diff(env, nodeValue, napi_undefined, napi_boolean, napi_null))
    {
        return result;
    }
    else
    {
        //_hmc_debug
    }
}

/**
 * @brief bigint转long
 *
 * @param env
 * @param nodeValue
 * @return long long
 */
long long hmc_napi_get_value::bigint_longlong(napi_env env, napi_value nodeValue, long long defaultValue)
{
    long long result = defaultValue;

    if (hmc_napi_type::diff(env, nodeValue, napi_bigint) || hmc_napi_type::diff(env, nodeValue, napi_boolean))
    {
        return result;
    }
    else if (hmc_napi_type::diff(env, nodeValue, napi_undefined, napi_boolean, napi_null))
    {
        return result;
    }
    else
    {
        //_hmc_debug
    }
    return result;
}
/**
 * @brief 获取buff
 *
 * @param env
 * @param nodeValue
 * @param buffer
 */

template <typename T>
void hmc_napi_get_value::buffer_vector(napi_env env, napi_value nodeValue, vector<T> &buffer)
{

    napi_status status;
    T *dataPtr;
    size_t len;
    status = napi_get_buffer_info(env, nodeValue, reinterpret_cast<void **>(&dataPtr), &len);
    if (status != napi_ok)
        return;
    // buffer.resize(len);
    buffer.insert(buffer.begin(), dataPtr, dataPtr + len);
}

/**
 * @brief 获取为布尔值
 *
 * @param env
 * @param nodeValue
 * @return true
 * @return false
 */
bool hmc_napi_get_value::boolean_bool(napi_env env, napi_value nodeValue, bool defaultValue)
{
    bool result = defaultValue;

    if (hmc_napi_type::diff(env, nodeValue, napi_number) || hmc_napi_type::diff(env, nodeValue, napi_boolean))
    {
        napi_get_value_bool(env, nodeValue, &result);
        return result;
    }

    return result;
}

/**
 * @brief 获取为utf8标准的文本
 *
 * @param env
 * @param nodeValue
 * @return string
 */
string hmc_napi_get_value::string_utf8(napi_env env, napi_value nodeValue, string defaultValue)
{
    string result = string("");

    if (!nodeValue)
    {
        return result;
    }
    if (hmc_napi_type::diff(env, nodeValue, napi_string))
    {
        size_t str_len = 0;
        napi_get_value_string_utf8(env, nodeValue, nullptr, 0, &str_len);
        result.reserve(str_len + 1);
        result.resize(str_len);
        napi_get_value_string_utf8(env, nodeValue, &result[0], result.capacity(), nullptr);
        return result;
    }
    else if (hmc_napi_type::diff(env, nodeValue, napi_number))
    {
        result.append(to_string(number_int(env, nodeValue)));
        return result;
    }
    else if (hmc_napi_type::diff(env, nodeValue, napi_undefined))
    {
        return result;
    }
    else
    {
    }

    return result;
}

/**
 * @brief 获取为utf8标准的文本
 *
 * @param env
 * @param nodeValue
 * @return string
 */
wstring hmc_napi_get_value::string_utf16(napi_env env, napi_value nodeValue, wstring defaultValue)
{
    wstring result = wstring(L"");

    if (!nodeValue)
    {
        return result;
    }
    // Buffer.from('文本', 'utf16le')
    if (hmc_napi_type::isBuffer(env, nodeValue))
    {
        vector<wchar_t> buffer;
        buffer_vector<wchar_t>(env, nodeValue, buffer);
        std::wstring wideString(buffer.begin(), buffer.end()); // 将 std::vector<wchar_t> 转换为 std::wstring
        return wideString;
    }
    // "文本"
    if (hmc_napi_type::diff(env, nodeValue, napi_string))
    {
        size_t str_len;
        napi_value tmp;
        napi_coerce_to_string(env, nodeValue, &tmp);
        napi_get_value_string_utf16(env, tmp, NULL, 0, &str_len);
        str_len += 1;
        wchar_t *str = new wchar_t[str_len];
        napi_get_value_string_utf16(env, tmp, (char16_t *)str, str_len, NULL);

        for (size_t i = 0; i < str_len; i++)
        {
            result.push_back(str[i]);
        }
        delete[] str;
        return result;
    }
    // 506546
    else if (hmc_napi_type::diff(env, nodeValue, napi_number))
    {
        result.append(to_wstring(number_int(env, nodeValue)));
        return result;
    }
    // undefined
    else if (hmc_napi_type::diff(env, nodeValue, napi_undefined))
    {
        return result;
    }
    else if (hmc_napi_type::diff(env, nodeValue, napi_null))
    {
        result.append(L"null");
        return result;
    }
    // ...
    else
    {
        //_hmc_debug
    }
    return result;

    return result;
}

/**
 * @brief 获取为窄(A)文本
 *
 * @param env
 * @param nodeValue
 * @return string
 */
string hmc_napi_get_value::string_ansi(napi_env env, napi_value nodeValue, string defaultValue)
{
    wstring result = string_utf16(env, nodeValue);
    string string_ansi = hmc_string_util::utf16_to_ansi(result);

    return string_ansi;
}

/**
 * @brief 获取为宽(W)文本
 *
 * @param env
 * @param nodeValue
 * @return wstring
 */
wstring hmc_napi_get_value::string_wide(napi_env env, napi_value nodeValue, wstring defaultValue)
{
    return string_utf16(env, nodeValue);
}

/**
 * @brief 获取文本数组
 *
 * @param env
 * @param nodeValue
 * @return vector<string>
 */
vector<string> hmc_napi_get_value::array_string_utf8(napi_env env, napi_value nodeValue)
{
    vector<string> unicode_str;

    napi_status status;
    uint32_t size = 0;
    status = napi_get_array_length(env, nodeValue, &size);
    if (status != napi_ok)
        return unicode_str;

    napi_value value;

    for (size_t i = 0; i < size; i++)
    {
        status = napi_get_element(env, nodeValue, i, &value);
        if (status != napi_ok)
        {
            // _hmc_debug
            return unicode_str;
        }
        unicode_str.push_back(string_utf8(env, value));
    }

    return unicode_str;
}

vector<wstring> hmc_napi_get_value::array_string_utf16(napi_env env, napi_value nodeValue)
{
    vector<wstring> result;

    napi_status status;
    uint32_t size = 0;
    status = napi_get_array_length(env, nodeValue, &size);
    if (status != napi_ok)
        return result;

    napi_value value;

    for (size_t i = 0; i < size; i++)
    {
        status = napi_get_element(env, nodeValue, i, &value);
        if (status != napi_ok)
        {
            // _hmc_debug
            return result;
        }
        result.push_back(string_utf16(env, value));
    }

    return result;
}

/**
 * @brief 获取数字数组
 *
 * @param env
 * @param nodeValue
 * @return vector<int>
 */
vector<int> hmc_napi_get_value::array_int(napi_env env, napi_value nodeValue)
{
    vector<int> num_list;

    napi_status status;
    uint32_t size = 0;
    status = napi_get_array_length(env, nodeValue, &size);
    if (status != napi_ok)
        return num_list;

    napi_value value;

    for (size_t i = 0; i < size; i++)
    {
        status = napi_get_element(env, nodeValue, i, &value);
        if (status != napi_ok)
        {
            // _hmc_debug
            return num_list;
        }
        num_list.push_back(number_int(env, value));
    }

    return num_list;
}

/**
 * @brief 获取数字数组
 *
 * @param env
 * @param nodeValue
 * @return vector<int>
 */
vector<int64_t> hmc_napi_get_value::array_int64(napi_env env, napi_value nodeValue)
{
    vector<int64_t> num_list;

    napi_status status;
    uint32_t size = 0;
    status = napi_get_array_length(env, nodeValue, &size);
    if (status != napi_ok)
        return num_list;

    napi_value value;

    for (size_t i = 0; i < size; i++)
    {
        status = napi_get_element(env, nodeValue, i, &value);
        if (status != napi_ok)
        {
            // _hmc_debug
            return num_list;
        }
        num_list.push_back(number_int64(env, value));
    }

    return num_list;
}

/**
 * @brief 获取数字数组
 *
 * @param env
 * @param nodeValue
 * @return vector<int>
 */
vector<double> hmc_napi_get_value::array_double(napi_env env, napi_value nodeValue)
{
    vector<double> num_list;

    napi_status status;
    uint32_t size = 0;
    status = napi_get_array_length(env, nodeValue, &size);
    if (status != napi_ok)
        return num_list;

    napi_value value;

    for (size_t i = 0; i < size; i++)
    {
        status = napi_get_element(env, nodeValue, i, &value);
        if (status != napi_ok)
        {
            // _hmc_debug
            return num_list;
        }
        num_list.push_back(number_double(env, value));
    }

    return num_list;
}

/**
 * @brief 将文本的显示状态转为CPP的显示状态代码
 *
 * @param env
 * @param nodeValue
 * @return UINT
 */
UINT hmc_napi_get_value::showType_UINT(napi_env env, napi_value nodeValue)
{

    string key = string_ansi(env, nodeValue);
    if (key == "MB_OK")
        return MB_OK;
    if (key == "MB_ABORTRETRYIGNORE")
        return MB_ABORTRETRYIGNORE;
    if (key == "MB_SERVICE_NOTIFICATION")
        return MB_SERVICE_NOTIFICATION;
    if (key == "MB_TOPMOST")
        return MB_TOPMOST;
    if (key == "MB_SETFOREGROUND")
        return MB_SETFOREGROUND;
    if (key == "MB_RTLREADING")
        return MB_RTLREADING;
    if (key == "MB_RIGHT")
        return MB_RIGHT;
    if (key == "MB_DEFAULT_DESKTOP_ONLY")
        return MB_DEFAULT_DESKTOP_ONLY;
    if (key == "MB_TASKMODAL")
        return MB_TASKMODAL;
    if (key == "MB_SYSTEMMODAL")
        return MB_SYSTEMMODAL;
    if (key == "MB_APPLMODAL")
        return MB_APPLMODAL;
    if (key == "MB_DEFBUTTON4")
        return MB_DEFBUTTON4;
    if (key == "MB_DEFBUTTON3")
        return MB_DEFBUTTON3;
    if (key == "MB_DEFBUTTON2")
        return MB_DEFBUTTON2;
    if (key == "MB_ICONHAND")
        return MB_ICONHAND;
    if (key == "MB_DEFBUTTON1")
        return MB_DEFBUTTON1;
    if (key == "MB_ICONERROR")
        return MB_ICONERROR;
    if (key == "MB_ICONSTOP")
        return MB_ICONSTOP;
    if (key == "MB_ICONQUESTION")
        return MB_ICONQUESTION;
    if (key == "MB_ICONASTERISK")
        return MB_ICONASTERISK;
    if (key == "MB_ICONINFORMATION")
        return MB_ICONINFORMATION;
    if (key == "MB_ICONWARNING")
        return MB_ICONWARNING;
    if (key == "MB_ICONEXCLAMATION")
        return MB_ICONEXCLAMATION;
    if (key == "MB_YESNOCANCEL")
        return MB_YESNOCANCEL;
    if (key == "MB_YESNO")
        return MB_YESNO;
    if (key == "MB_RETRYCANCEL")
        return MB_RETRYCANCEL;
    if (key == "MB_OKCANCEL")
        return MB_OKCANCEL;
    if (key == "MB_HELP")
        return MB_HELP;
    if (key == "MB_CANCELTRYCONTINUE")
        return MB_CANCELTRYCONTINUE;

    return MB_OK;
}

/**
 * @brief 转 DWORD
 *
 * @param env
 * @param nodeValue
 * @return DWORD
 */
DWORD hmc_napi_get_value::number_DWORD(napi_env env, napi_value nodeValue, int defaultValue)
{
    DWORD result = (DWORD)number_int64(env, nodeValue);
    return result;
}

/**
 * @brief 转窗口句柄
 *
 * @param env
 * @param nodeValue
 * @return HWND
 */
HWND hmc_napi_get_value::number_HWND(napi_env env, napi_value nodeValue, HWND defaultValue)
{
    int64_t data = number_int64(env, nodeValue);
    if (data > 0)
    {
        HWND result = (HWND)number_int64(env, nodeValue);
    }
    return defaultValue;
}

/**
 * @brief 获取buff内容
 *
 * @param env
 * @param nodeValue
 * @return vector<unsigned char>
 */
vector<unsigned char> hmc_napi_get_value::buffer_vector(napi_env env, napi_value nodeValue)
{
    vector<unsigned char> buffer;
    buffer_vector<unsigned char>(env, nodeValue, buffer);
    return buffer;
}

/**
 * @brief 传入缓冲是utf16的文本
 *
 * @param env
 * @param nodeValue
 * @return wstring
 */
wstring hmc_napi_get_value::buffer_utf16_strW(napi_env env, napi_value nodeValue)
{
    vector<wchar_t> buffer;
    buffer_vector<wchar_t>(env, nodeValue, buffer);
    std::wstring wideString(buffer.begin(), buffer.end()); // 将 std::vector<wchar_t> 转换为 std::wstring
    return wideString;
}

/**
 * @brief 传入缓冲是ansi的文本（winapi转换过得）
 *
 * @param env
 * @param nodeValue
 * @return string
 */
string hmc_napi_get_value::buffer_ansi_strA(napi_env env, napi_value nodeValue)
{
    vector<unsigned char> buffer;
    buffer_vector<unsigned char>(env, nodeValue, buffer);
    std::string ansiString(buffer.begin(), buffer.end());
    return ansiString;
}

/**
 * @brief 传入缓冲是utf8的文本
 *
 * @param env
 * @param nodeValue
 * @return string
 */
string hmc_napi_get_value::buffer_utf8_strU8(napi_env env, napi_value nodeValue)
{
    vector<unsigned char> buffer;
    buffer_vector<unsigned char>(env, nodeValue, buffer);
    std::string utf8String(buffer.begin(), buffer.end());
    return utf8String;
}
/**
 * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
 * @param env
 * @param nodeValue
 * @return const wchar_t* c标准接口的  const char *
 */
const wchar_t *hmc_napi_get_value::buffer_utf16_clpStrW(napi_env env, napi_value nodeValue)
{
    vector<wchar_t> buffer;
    buffer_vector<wchar_t>(env, nodeValue, buffer);
    std::wstring wideString(buffer.begin(), buffer.end()); // 将 std::vector<wchar_t> 转换为 std::wstring
    wchar_t *utf16Ptr = new wchar_t[wideString.size() + 1];

    for (size_t i = 0; i < wideString.size(); i++)
    {
        wchar_t data = wideString[i];
        utf16Ptr[i] = data;
    }
    const int end = wideString.size();

    utf16Ptr[end] = *L"\0";

    return utf16Ptr;
}

/**
 * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
 * @param env
 * @param nodeValue
 * @return const char* c标准接口的  const char *
 */
const char *hmc_napi_get_value::buffer_utf8_clpStrU8(napi_env env, napi_value nodeValue)
{
    vector<unsigned char> buffer;
    buffer_vector<unsigned char>(env, nodeValue, buffer);
    std::string utf8String(buffer.begin(), buffer.end());

    char *utf8Ptr = new char[utf8String.size() + 1];

    for (size_t i = 0; i < utf8String.size(); i++)
    {
        char data = utf8String[i];
        utf8Ptr[i] = data;
    }
    const int end = utf8String.size();

    utf8Ptr[end] = *"\0";

    return utf8Ptr;
}

/**
 * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
 * @param env
 * @param nodeValue
 * @return const char* c标准接口的  const char *
 */
const char *hmc_napi_get_value::buffer_ansi_clpStrA(napi_env env, napi_value nodeValue)
{
    vector<unsigned char> buffer;
    buffer_vector<unsigned char>(env, nodeValue, buffer);
    std::string ansiString(buffer.begin(), buffer.end());

    char *ansiPtr = new char[ansiString.size() + 1];

    for (size_t i = 0; i < ansiString.size(); i++)
    {
        char data = ansiString[i];
        ansiPtr[i] = data;
    }
    const int end = ansiString.size();

    ansiPtr[end] = *"\0";

    return ansiPtr;
}

POINT hmc_napi_get_value::point(napi_env env, napi_value objectValue)
{
    POINT result = POINT{};
    result.x = 0;
    result.y = 0;
    napi_status status;
    napi_value x_value;
    napi_value y_value;

    if (napi_get_named_property(env, objectValue, "x", &x_value) != napi_ok)
    {
        napi_create_int32(env, 0, &x_value);
    }

    if (napi_get_named_property(env, objectValue, "y", &y_value) != napi_ok)
    {
        napi_create_int32(env, 0, &y_value);
    }
    result.x = number_int(env, x_value);
    result.y = number_int(env, y_value);
    return result;
}

napi_value hmc_napi_get_value::get_object_value(napi_env env, napi_value objectValue, string key)
{
    napi_value result;

    if (!hmc_napi_type::isObjectkeyExists(env, objectValue, key))
    {
        return NULL;
    }

    if (napi_get_named_property(env, objectValue, key.c_str(), &result) == napi_ok)
    {
        return result;
    }

    return NULL;
}

int hmc_napi_get_value::get_object_value_int(napi_env env, napi_value objectValue, string key, int defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isNumber(env, napi_data))
    {
        return defaultValue;
    }

    return number_int(env, napi_data, defaultValue);
}

int64_t hmc_napi_get_value::get_object_value_int64(napi_env env, napi_value objectValue, string key, int64_t defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isNumber(env, napi_data) || !hmc_napi_type::isBoolean(env, napi_data))
    {
        return defaultValue;
    }

    return number_int64(env, napi_data, defaultValue);
}

double hmc_napi_get_value::get_object_value_double(napi_env env, napi_value objectValue, string key, double defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isNumber(env, napi_data))
    {
        return defaultValue;
    }

    return number_double(env, napi_data, defaultValue);
}

bool hmc_napi_get_value::get_object_value_bool(napi_env env, napi_value objectValue, string key, bool defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isNumber(env, napi_data))
    {
        return defaultValue;
    }

    return boolean_bool(env, napi_data, defaultValue);
}

wstring hmc_napi_get_value::get_object_value_utf16(napi_env env, napi_value objectValue, string key, wstring defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isString(env, napi_data))
    {
        return defaultValue;
    }

    return string_utf16(env, napi_data, defaultValue);
}

string hmc_napi_get_value::get_object_value_utf8(napi_env env, napi_value objectValue, string key, string defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isString(env, napi_data))
    {
        return defaultValue;
    }

    return string_utf8(env, napi_data, defaultValue);
}

RECT hmc_napi_get_value::rect(napi_env env, napi_value objectValue)
{
    RECT result = RECT{};
    result.bottom = get_object_value_int(env, objectValue, "bottom", 0);
    result.top = get_object_value_int(env, objectValue, "top", 0);
    result.right = get_object_value_int(env, objectValue, "right", 0);
    result.left = get_object_value_int(env, objectValue, "left", 0);
    return result;
}

string hmc_napi_get_value::get_object_value_ansi(napi_env env, napi_value objectValue, string key, string defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isString(env, napi_data))
    {
        return defaultValue;
    }

    return string_ansi(env, napi_data, defaultValue);
}

// ?hmc_napi_util::create_value
// 负责创建返回值的逻辑
// ------------------------------------------------------------------------------------------------------

// 创建一个布尔型
napi_value hmc_napi_create_value::Boolean(napi_env env, bool value)
{
    napi_status status;
    napi_value result;
    status = napi_get_boolean(env, value, &result);
    assert(status == napi_ok);
    return result;
}
// 创建一个布尔型
napi_value hmc_napi_create_value::Boolean(napi_env env, int value)
{
    napi_status status;
    napi_value result;
    status = napi_get_boolean(env, (bool)value, &result);
    assert(status == napi_ok);
    return result;
}

// 返回一个 string utf8 string
napi_value hmc_napi_create_value::String(napi_env env, string value)
{
    napi_status status;
    napi_value result;
    status = napi_create_string_utf8(env, value.c_str(), NAPI_AUTO_LENGTH, &result);
    assert(status == napi_ok);
    return result;
}

// 返回一个 string utf8 string
napi_value hmc_napi_create_value::StringA(napi_env env, string value)
{
    napi_status status;
    napi_value result;
    wstring result2w = hmc_string_util::ansi_to_utf16(value);
    status = napi_create_string_utf16(env, (const char16_t *)result2w.c_str(), NAPI_AUTO_LENGTH, &result);
    assert(status == napi_ok);
    return result;
}

// 返回一个 string utf16 string
napi_value hmc_napi_create_value::String(napi_env env, wstring value)
{
    napi_status status;
    napi_value result;
    status = napi_create_string_utf16(env, (const char16_t *)value.c_str(), NAPI_AUTO_LENGTH, &result);
    assert(status == napi_ok);
    return result;
}

napi_value hmc_napi_create_value::String(napi_env env, wchar_t *value)
{
    return String(env, wstring(value));
}
napi_value hmc_napi_create_value::String(napi_env env, char *value)
{
    return String(env, string(value));
}
napi_value hmc_napi_create_value::String(napi_env env)
{
    return String(env, "");
}

/**
 * @brief 返回一个 number到js
 *
 * @param number
 * @return napi_value
 */
napi_value hmc_napi_create_value::Number(napi_env env, int number)
{
    napi_status status;
    napi_value result;
    status = napi_create_int32(env, number, &result);
    assert(status == napi_ok);
    return result;
}
/**
 * @brief 返回一个 number到js
 *
 * @param number
 * @return napi_value
 */
napi_value hmc_napi_create_value::Number(napi_env env, int64_t number)
{
    napi_status status;
    napi_value result;
    status = napi_create_int64(env, number, &result);
    assert(status == napi_ok);
    return result;
}
/**
 * @brief 返回一个 number到js
 *
 * @param number
 * @return napi_value
 */
napi_value hmc_napi_create_value::Number(napi_env env, double number)
{
    napi_status status;
    napi_value result;
    status = napi_create_double(env, number, &result);
    assert(status == napi_ok);
    return result;
}
/**
 * @brief 返回一个 number到js
 *
 * @param number
 * @return napi_value
 */
napi_value hmc_napi_create_value::Number(napi_env env, HWND number)
{
    napi_status status;
    napi_value result;
    status = napi_create_int64(env, (long long)number, &result);
    assert(status == napi_ok);
    return result;
}
napi_value hmc_napi_create_value::Number(napi_env env, unsigned long number)
{
    napi_status status;
    napi_value result;
    status = napi_create_int64(env, (long)number, &result);
    assert(status == napi_ok);
    return result;
}
/**
 * @brief 返回一个 number到js
 *
 * @param bigint
 * @return napi_value
 */
napi_value hmc_napi_create_value::Bigint(napi_env env, long bigint)
{
    napi_status status;
    napi_value result;
    status = napi_create_bigint_int64(env, bigint, &result);
    assert(status == napi_ok);
    return result;
}

napi_value hmc_napi_create_value::Bigint(napi_env env, long long bigint)
{
    napi_status status;
    napi_value result;
    status = napi_create_bigint_int64(env, bigint, &result);
    assert(status == napi_ok);
    return result;
}
/**
 * @brief 返回一个 Buffer到js(返回的是空值 napi 不支持)
 *
 * @param env
 * @param data
 * @param size
 * @return napi_value
 */
napi_value hmc_napi_create_value::Buffer(napi_env env, vector<unsigned char> &buffer)
{
    napi_status status;
    napi_value Results;
    try
    {

        void *yourPointer = malloc(buffer.size());

        // 很迷惑的函数 这个只能创建空白内存而不是buff
        // status = napi_create_arraybuffer(env, buffer.size(), &yourPointer, &Results);
        // assert(status == napi_ok);

        memcpy(yourPointer, buffer.data(), buffer.size());
        status = napi_create_external_buffer(env, buffer.size(), yourPointer, NULL, NULL, &Results);
        assert(status == napi_ok);
        // free(yourPointer);
    }
    catch (const std::exception &e)
    {
    }

    return Results;
}
napi_value hmc_napi_create_value::Buffer(napi_env env, void *data, size_t size)
{
    napi_status status;
    napi_value Results;
    try
    {
        status = napi_create_external_buffer(env, size, data, NULL, NULL, &Results);
        assert(status == napi_ok);
    }
    catch (const std::exception &e)
    {
        void *yourPointer = malloc(0);
        status = napi_create_buffer(env, 0, &yourPointer, &Results);
        assert(status == napi_ok);
    }
    return Results;
}

/**
 * @brief 返回一个 null
 *
 * @param env
 * @param data
 * @param size
 * @return napi_value
 */
napi_value hmc_napi_create_value::Null(napi_env env)
{
    napi_status status;
    napi_value Results;
    status = napi_get_null(env, &Results);
    assert(status == napi_ok);
    return Results;
}
/**
 * @brief RECT (位置信息转为Object)
 *
 * @param env
 * @param rect
 * @return napi_value
 */
napi_value hmc_napi_create_value::Rect(napi_env env, RECT rect)
{
    napi_value ResultforObject;
    napi_status status;
    status = napi_create_object(env, &ResultforObject);
    assert(status == napi_ok);

    status = napi_set_property(env, ResultforObject, String(env, "bottom"), Number(env, rect.bottom));
    assert(status == napi_ok);

    status = napi_set_property(env, ResultforObject, String(env, "left"), Number(env, rect.left));
    assert(status == napi_ok);

    status = napi_set_property(env, ResultforObject, String(env, "right"), Number(env, rect.right));
    assert(status == napi_ok);

    status = napi_set_property(env, ResultforObject, String(env, "top"), Number(env, rect.top));
    assert(status == napi_ok);

    return ResultforObject;
}

napi_value hmc_napi_create_value::Point(napi_env env, POINT point)
{
    napi_value ResultforObject;
    napi_status status;
    status = napi_create_object(env, &ResultforObject);
    assert(status == napi_ok);

    status = napi_set_property(env, ResultforObject, String(env, "x"), Number(env, point.x));
    assert(status == napi_ok);

    status = napi_set_property(env, ResultforObject, String(env, "y"), Number(env, point.y));
    assert(status == napi_ok);

    return ResultforObject;
}

/**
 * @brief 返回一个 undefined
 *
 * @param env
 * @param data
 * @param size
 * @return napi_value
 */
napi_value hmc_napi_create_value::Undefined(napi_env env)
{
    napi_status status;
    napi_value Results;
    status = napi_get_undefined(env, &Results);
    assert(status == napi_ok);
    return Results;
}
/**
 * @brief 自识别类型
 *
 * @param env
 * @param anyValue
 * @return napi_value
 */
napi_value hmc_napi_create_value::New(napi_env env, any anyValue)
{
    napi_status status;
    napi_value ResultForAny;
    if (anyValue.has_value())
    {
        // 整形
        if (anyValue.type() == typeid(DWORD))
        {
            ResultForAny = Number(env, any_cast<DWORD>(anyValue));
        }
        else if (anyValue.type() == typeid(int))
        {
            ResultForAny = Number(env, any_cast<int>(anyValue));
        }
        else if (anyValue.type() == typeid(long))
        {
            ResultForAny = Number(env, any_cast<long>(anyValue));
        }
        else if (anyValue.type() == typeid(long long))
        {
            ResultForAny = Number(env, any_cast<long long>(anyValue));
        }
        else if (anyValue.type() == typeid(HWND))
        {
            ResultForAny = Number(env, any_cast<HWND>(anyValue));
        }
        else if (anyValue.type() == typeid(int64_t))
        {
            ResultForAny = Number(env, any_cast<int64_t>(anyValue));
        }
        else if (anyValue.type() == typeid(short))
        {
            ResultForAny = Number(env, any_cast<short>(anyValue));
        }
        else if (anyValue.type() == typeid(unsigned long long) || anyValue.type() == typeid(unsigned long))
        {
            ResultForAny = Number(env, (unsigned long)any_cast<unsigned long long>(anyValue));
        }
        // 浮点
        else if (anyValue.type() == typeid(float))
        {
            ResultForAny = Number(env, (double)any_cast<float>(anyValue));
        }
        else if (anyValue.type() == typeid(double))
        {
            ResultForAny = Number(env, any_cast<double>(anyValue));
        }
        else if (anyValue.type() == typeid(long double))
        {
            ResultForAny = Number(env, (double)any_cast<long double>(anyValue));
        }
        // 文本型
        else if (anyValue.type() == typeid(string))
        {
            ResultForAny = String(env, any_cast<string>(anyValue));
        }
        else if (anyValue.type() == typeid(wstring))
        {
            ResultForAny = String(env, any_cast<wstring>(anyValue));
        }
        else if (anyValue.type() == typeid(char *))
        {
            ResultForAny = String(env, any_cast<char *>(anyValue));
        }
        else if (anyValue.type() == typeid(CHAR *))
        {
            ResultForAny = String(env, any_cast<CHAR *>(anyValue));
        }
        else if (anyValue.type() == typeid(WCHAR *))
        {
            ResultForAny = String(env, any_cast<WCHAR *>(anyValue));
        }
        // bool
        else if (anyValue.type() == typeid(bool))
        {
            ResultForAny = Boolean(env, any_cast<bool>(anyValue));
        }
        else if (anyValue.type() == typeid(BOOL))
        {
            ResultForAny = Boolean(env, any_cast<BOOL>(anyValue));
        }

        else
        {
            ResultForAny = Undefined(env);
        }
    }

    return ResultForAny;
}

napi_value hmc_napi_create_value::New(napi_env env)
{
    return Undefined(env);
}

/**
 * @brief 支持多种类型的数组
 *
 * @param env
 * @param wstringVector
 * @return napi_value
 */
napi_value hmc_napi_create_value::Array::New(napi_env env, vector<napi_value> wstringVector)
{
    napi_status status;
    napi_value ResultforArray;
    status = napi_create_array(env, &ResultforArray);
    assert(status == napi_ok);
    for (unsigned index = 0; index < wstringVector.size(); index++)
    {
        napi_value push_item_data = wstringVector[index];
        status = napi_set_element(env, ResultforArray, index, push_item_data);
        assert(status == napi_ok);
    }
    return ResultforArray;
}
napi_value hmc_napi_create_value::Array::New(napi_env env, vector<any> wstringVector)
{
    napi_status status;
    napi_value ResultforArray;
    status = napi_create_array(env, &ResultforArray);
    assert(status == napi_ok);
    for (unsigned index = 0; index < wstringVector.size(); index++)
    {
        any push_item_data = wstringVector[index];
        napi_set_element(env, ResultforArray, index, hmc_napi_create_value::New(env, push_item_data));
        assert(status == napi_ok);
    }
    return ResultforArray;
}
/**
 * @brief 创建一个全是文本的数组
 *
 * @param env
 * @param stringVector
 * @return napi_value
 */
napi_value hmc_napi_create_value::Array::String(napi_env env, vector<string> stringVector)
{
    napi_status status;
    napi_value ResultforArray;
    status = napi_create_array(env, &ResultforArray);
    assert(status == napi_ok);
    for (unsigned index = 0; index < stringVector.size(); index++)
    {
        string push_item_data = stringVector[index];
        status = napi_set_element(env, ResultforArray, index, hmc_napi_create_value::String(env, push_item_data));
        assert(status == napi_ok);
    }
    return ResultforArray;
}
napi_value hmc_napi_create_value::Array::String(napi_env env, vector<wstring> wstringVector)
{
    napi_status status;
    napi_value ResultforArray;
    status = napi_create_array(env, &ResultforArray);
    assert(status == napi_ok);
    for (unsigned index = 0; index < wstringVector.size(); index++)
    {
        wstring push_item_data = wstringVector[index];
        status = napi_set_element(env, ResultforArray, index, hmc_napi_create_value::String(env, push_item_data));
        assert(status == napi_ok);
    }
    return ResultforArray;
}
/**
 * @brief 创建一个全是数字的数组
 *
 * @param env
 * @param intVector
 * @return napi_value
 */
napi_value hmc_napi_create_value::Array::Number(napi_env env, vector<int> intVector)
{
    napi_status status;
    napi_value ResultforArray;
    status = napi_create_array(env, &ResultforArray);
    assert(status == napi_ok);
    for (unsigned index = 0; index < intVector.size(); index++)
    {
        napi_value push_item;
        int push_item_data = intVector[index];
        status = napi_create_int64(env, push_item_data, &push_item);
        assert(status == napi_ok);
        status = napi_set_element(env, ResultforArray, index, push_item);
        assert(status == napi_ok);
    }
    return ResultforArray;
}

/**
 * @brief 创建一个全是数字的数组
 *
 * @param env
 * @param intVector
 * @return napi_value
 */
napi_value hmc_napi_create_value::Array::Bigint(napi_env env, vector<int> intVector)
{
    napi_status status;
    napi_value ResultforArray;
    status = napi_create_array(env, &ResultforArray);
    assert(status == napi_ok);
    for (unsigned index = 0; index < intVector.size(); index++)
    {
        napi_value push_item;
        int push_item_data = intVector[index];
        status = napi_create_int64(env, push_item_data, &push_item);
        assert(status == napi_ok);
        status = napi_set_element(env, ResultforArray, index, push_item);
        assert(status == napi_ok);
    }
    return ResultforArray;
}
/**
 * @brief 创建一个全是数字的数组
 *
 * @param env
 * @param intVector
 * @return napi_value
 */
napi_value hmc_napi_create_value::Array::Boolean(napi_env env, vector<bool> boolVector)
{
    napi_status status;
    napi_value ResultforArray;
    status = napi_create_array(env, &ResultforArray);
    assert(status == napi_ok);
    for (unsigned index = 0; index < boolVector.size(); index++)
    {
        napi_value push_item;
        bool push_item_data = boolVector[index];
        status = napi_get_boolean(env, push_item_data, &push_item);
        assert(status == napi_ok);
        status = napi_set_element(env, ResultforArray, index, push_item);
        assert(status == napi_ok);
    }
    return ResultforArray;
}

/**
 * @brief 创建一个全是文本的 键值对对象
 *
 * @param env
 * @param mapObject
 * @return napi_value
 */
napi_value hmc_napi_create_value::Object::Object(napi_env env, map<string, string> mapObject)
{
    napi_status status;
    napi_value ResultforObject;
    status = napi_create_object(env, &ResultforObject);
    assert(status == napi_ok);
    map<string, string>::iterator it = mapObject.begin();

    while (it != mapObject.end())
    {
        status = napi_set_property(env, ResultforObject, String(env, it->first), String(env, it->second));
        assert(status == napi_ok);
        it++;
    }

    return ResultforObject;
}
/**
 * @brief 创建一个全是文本的 键值对对象
 *
 * @param env
 * @param mapObject
 * @return napi_value
 */
napi_value hmc_napi_create_value::Object::Object(napi_env env, map<wstring, wstring> mapObject)
{
    napi_status status;
    napi_value ResultforObject;
    status = napi_create_object(env, &ResultforObject);
    assert(status == napi_ok);
    map<wstring, wstring>::iterator it = mapObject.begin();

    while (it != mapObject.end())
    {
        status = napi_set_property(env, ResultforObject, String(env, it->first), String(env, it->second));
        assert(status == napi_ok);
        it++;
    }

    return ResultforObject;
}

/**
 * @brief 创建一个全是int的 键值对对象
 *
 * @param env
 * @param mapObject
 * @return napi_value
 */
napi_value hmc_napi_create_value::Object::Object(napi_env env, map<string, int> mapObject)
{
    napi_status status;
    napi_value ResultforObject;
    status = napi_create_object(env, &ResultforObject);
    assert(status == napi_ok);
    map<string, int>::iterator it = mapObject.begin();

    while (it != mapObject.end())
    {
        status = napi_set_property(env, ResultforObject, String(env, it->first), Number(env, it->second));
        assert(status == napi_ok);
        it++;
    }

    return ResultforObject;
}
/**
 * @brief 创建一个全是napi_value的 键值对对象
 *
 * @param env
 * @param mapObject
 * @return napi_value
 */
napi_value hmc_napi_create_value::Object::Object(napi_env env, map<string, napi_value> mapObject)
{
    napi_status status;
    napi_value ResultforObject;
    status = napi_create_object(env, &ResultforObject);
    assert(status == napi_ok);
    map<string, napi_value>::iterator it = mapObject.begin();

    while (it != mapObject.end())
    {
        status = napi_set_property(env, ResultforObject, String(env, it->first), it->second);
        assert(status == napi_ok);
        it++;
    }

    return ResultforObject;
}
/**
 * @brief 创建一个任意js支持的类型
 *
 * @param env
 * @param mapObject
 * @return napi_value
 */
napi_value hmc_napi_create_value::Object::Object(napi_env env, map<string, any> mapObject)
{
    napi_status status;
    napi_value ResultforObject;
    status = napi_create_object(env, &ResultforObject);
    assert(status == napi_ok);
    map<string, any>::iterator it = mapObject.begin();

    while (it != mapObject.end())
    {
        status = napi_set_property(env, ResultforObject, String(env, it->first), New(env, it->second));
        assert(status == napi_ok);
        it++;
    }

    return ResultforObject;
}

/**
 * @brief Destroy the hmc Node Value::hmc Node Value object
 *
 */
hmc_NodeArgsValue::~hmc_NodeArgsValue()
{
    args.clear();
    env = NULL;
}

hmc_NodeArgsValue::hmc_NodeArgsValue(napi_env envs, napi_callback_info info)
{
    env = envs;

    napi_status status;
    size_t argc = 0;

    if ((status = napi_get_cb_info(envs, info, &argc, NULL, NULL, NULL)) != napi_ok)
    {
        string error_msg = "";
        error_msg.append("napi_get_cb_info fn < ");
        error_msg.append(" >");
        error_msg.append(__FUNCTION__);
        error_msg.append("get args size ");
        error_msg.append("   ");
        error_msg.append("error code-> ");
        error_msg.append(to_string(status));
        error_msg.append("   ");

        napi_throw_type_error(envs, NULL, hmc_string_util::string_to_lpstr(error_msg));
    }

    if (argc > 0)
    {

        args.reserve(argc);
        args.resize(argc);

        if ((status = napi_get_cb_info(envs, info, &argc, reinterpret_cast<napi_value *>(&args[0]), NULL, NULL)) != napi_ok)
        {
            string error_msg = "";
            error_msg.append("napi_get_cb_info fn < ");
            error_msg.append(" >");
            error_msg.append(__FUNCTION__);
            error_msg.append("napi_get_cb_info(envs, info, &argc, reinterpret_cast<napi_value *>(&args[0]), NULL, NULL)");
            error_msg.append("   ");
            error_msg.append("error code-> ");
            error_msg.append(to_string(status));
            error_msg.append("   ");

            napi_throw_type_error(envs, NULL, hmc_string_util::string_to_lpstr(error_msg));

            args.clear();
            args.resize(0);
        }
    }
}

size_t hmc_NodeArgsValue::size()
{
    return args.size();
}

bool hmc_NodeArgsValue::argsSize(size_t min_length, size_t max_length, bool throw_error)
{
    bool results = false;
    if (this->size() >= min_length && this->size() <= max_length)
    {
        return true;
    }
    else
    {
        if (throw_error)
        {

            string error_msg = "";
            error_msg.append("args eq  < ");
            error_msg.append(__FUNCTION__);
            error_msg.append(" >\n");
            error_msg.append("The current number of parameters passed is lower than required. The input is \n");
            error_msg.append("[ ");
            error_msg.append(to_string(min_length));
            error_msg.append(" ], and the ideal number of parameters should be ");
            error_msg.append("[ ");
            error_msg.append(to_string(max_length));
            error_msg.append(" ]");

            napi_throw_type_error(env, "PARAMETER_ERROR", hmc_string_util::string_to_lpstr(error_msg));
        }
        return false;
    }
    return results;
}

wstring hmc_NodeArgsValue::getStringWide(size_t index, wstring defaultValue)
{
    wstring results = wstring(L"");
    results.append(defaultValue);
    if (!this->exists(index))
    {
        return results;
    }
    results = hmc_napi_get_value::string_utf16(env, args[index]);

    return results;
}

string hmc_NodeArgsValue::getStringAnsi(size_t index, string defaultValue)
{

    string results = string("");
    results.append(defaultValue);
    if (!this->exists(index))
    {
        return results;
    }
    results = hmc_napi_get_value::string_ansi(env, args[index]);

    return results;
}

string hmc_NodeArgsValue::getStringUtf8(size_t index, string defaultValue)
{

    string results = string("");
    results.append(defaultValue);
    if (!this->exists(index))
    {
        return results;
    }
    results = hmc_napi_get_value::string_utf8(env, args[index]);

    return results;
}

vector<string> hmc_NodeArgsValue::getArrayString(size_t index, vector<string> defaultValue)
{
    vector<string> results = {};

    if (this->exists(index))
    {
        vector<wstring> datas = hmc_napi_get_value::array_string_utf16(env, args[index]);
        for (size_t i = 0; i < datas.size(); i++)
        {
            results.push_back(hmc_string_util::utf16_to_ansi(datas[i]));
        }

        return results;
    }

    return results;
}

vector<wstring> hmc_NodeArgsValue::getArrayWstring(size_t index, vector<wstring> defaultValue)
{
    if (this->exists(index))
    {
        return hmc_napi_get_value::array_string_utf16(env, args[index]);
    }
    return defaultValue;
}

bool hmc_NodeArgsValue::getBool(size_t index, bool defaultValue)
{
    bool results = defaultValue;
    if (!this->exists(index))
    {
        return results;
    }

    results = hmc_napi_get_value::boolean_bool(env, args[index], defaultValue);

    return results;
}

vector<unsigned char> hmc_NodeArgsValue::getBuffer(size_t index, vector<unsigned char> defaultValue)
{
    if (!this->exists(index) || !hmc_napi_type::isBuffer(env, args[index]))
    {
        return defaultValue;
    }

    return hmc_napi_get_value::buffer_vector(env, args[index]);
}

double hmc_NodeArgsValue::getDouble(size_t index, double defaultValue)
{
    if (!this->exists(index))
    {
        return defaultValue;
    }
    return hmc_napi_get_value::number_double(env, args[index], defaultValue);
};

HWND hmc_NodeArgsValue::getHwnd(size_t index, HWND defaultValue)
{
    if (!this->exists(index))
    {
        return defaultValue;
    }
    return hmc_napi_get_value::number_HWND(env, args[index], defaultValue);
}

DWORD hmc_NodeArgsValue::getDword(size_t index, DWORD defaultValue)
{
    if (!this->exists(index))
    {
        return defaultValue;
    }
    return hmc_napi_get_value::number_DWORD(env, args[index], defaultValue);
}

int hmc_NodeArgsValue::getInt(size_t index, int defaultValue)
{
    if (!this->exists(index))
    {
        return defaultValue;
    }
    return hmc_napi_get_value::number_int(env, args[index], defaultValue);
}

int64_t hmc_NodeArgsValue::getInt64(size_t index, int64_t defaultValue)
{
    if (!this->exists(index))
    {
        return defaultValue;
    }
    return hmc_napi_get_value::number_int64(env, args[index], defaultValue);
}

vector<int> hmc_NodeArgsValue::getArrayInt(size_t index, vector<int> defaultValue)
{
    if (!this->exists(index))
    {
        return defaultValue;
    }

    return hmc_napi_get_value::array_int(env, args[index]);
}

bool hmc_NodeArgsValue::exists(size_t index)
{
    bool results = false;
    if (!args.size())
        return results;

    if (args.size() > index)
    {
        results = true;
    }

    return results && args[index] != NULL;
}

bool hmc_NodeArgsValue::eq(size_t index, js_valuetype type, bool throw_error)
{
    bool results = false;

    if (!this->exists(index))
    {
        if (throw_error)
        {

            string error_msg = "The current input parameter has two errors:\n";
            error_msg.append("1.The number of input parameters should be greater than NNNN.\n");
            error_msg.append("2. The current input parameter does not meet the expected requirements. The expected parameter \n");
            error_msg.append("[ ");
            error_msg.append(to_string(index));
            error_msg.append(" ] can only be of type [ ");
            error_msg.append(hmc_napi_type::typeName(type));
            error_msg.append(" ]");

            napi_throw_type_error(env, "PARAMETER_ERROR", hmc_string_util::string_to_lpstr(error_msg));
        }

        return results;
    }

    js_valuetype args_type = hmc_napi_type::getType(env, args[index]);
    results = args_type == type;

    if (throw_error && !results)
    {

        string error_msg = "";
        error_msg.append("The current input parameter has errors:\n");
        error_msg.append("The current input parameter does not meet the expected requirements. The expected parameter \n");
        error_msg.append("[ ");
        error_msg.append(to_string(index));
        error_msg.append(" ] can only be of type [ ");
        error_msg.append(hmc_napi_type::typeName(type));
        error_msg.append(" ]");

        error_msg.append(" != ");
        error_msg.append(" Your type: < ");
        error_msg.append(hmc_napi_type::typeName(args_type));
        error_msg.append(" >      ");
        error_msg.append("   \n");

        napi_throw_type_error(env, "PARAMETER_ERROR", hmc_string_util::string_to_lpstr(error_msg));
    }

    return results;
}

bool hmc_NodeArgsValue::eq(vector<std::tuple<size_t, js_valuetype>> eq_type, bool throw_error)
{
    bool results = true;
    map<size_t, vector<js_valuetype>> eq_type_index_list = {};
    string error_message = "There are discrepancies between the current parameters and the expected values. The listed type errors are as follows:\n ";

    // if(eq_type.empty()||args.empty()){
    //     return false;
    // }

    // 枚举出一共存在多少个index 需要进行判断

    for (size_t i = 0; i < eq_type.size(); i++)
    {
        size_t index = std::get<0>(eq_type[i]);
        js_valuetype type = std::get<1>(eq_type[i]);

        // 不存在则创建
        if (!eq_type_index_list.count(index))
        {
            auto value = pair<size_t, vector<js_valuetype>>(index, vector<js_valuetype>());
            eq_type_index_list.insert(value);
        }

        eq_type_index_list[index].push_back(type);
    }

    // 枚举所有索引
    for (auto eqtype : eq_type_index_list)
    {

        if (!this->exists(eqtype.first))
        {
            error_message.append("Parameter [ ");
            error_message.append(to_string(eqtype.first));
            error_message.append(" ] does not exist. Only [ ");
            error_message.append(to_string(this->args.size()));
            error_message.append(" ] parameter(s) were provided.\n");

            error_message.append("The expected parameter should be: \n [ ");

            for (auto second : eqtype.second)
            {
                error_message.append(hmc_napi_type::typeName((js_valuetype)second));
                error_message.append(" , ");
            }

            error_message = hmc_string_util::trimAll(error_message, " , ");

            error_message.append(" ]\n-------------------------------------------\n");
            results = false;

            continue;
        }

        bool has_second = false;

        auto the_type = hmc_napi_type::getType(env, args[eqtype.first]);

        string the_types = "";

        // 遍历并判断匹配
        for (auto second : eqtype.second)
        {
            the_types.append(hmc_napi_type::typeName((js_valuetype)second));
            the_types.append(" , ");

            if (the_type == second)
            {
                has_second = true;
            }
        }
        the_types = hmc_string_util::trimAll(the_types, " , ");

        if (!has_second)
        {
            error_message.append(" [ ");
            error_message.append(to_string(eqtype.first));
            error_message.append(" ]   ->  ");

            error_message.append(hmc_napi_type::typeName(the_type));

            error_message.append(" != ");
            error_message.append(" Your type: < ");
            error_message.append(the_types);
            error_message.append(" >      ");
            error_message.append("   \n");
            error_message.append("-------------------------------------------\n");
            results = false;
        }
    }

    if (throw_error && !results)
    {
        napi_throw_type_error(env, NULL, hmc_string_util::string_to_lpstr(error_message));
    }

    return results;
}

bool hmc_NodeArgsValue::eq(size_t index, napi_valuetype type, bool throw_error)
{
    return eq(index, (js_valuetype)type, throw_error);
}

bool hmc_NodeArgsValue::eq(vector<std::tuple<size_t, napi_valuetype>> eq_type, bool throw_error)
{
    vector<std::tuple<size_t, js_valuetype>> new_eq_type = {};

    for (size_t i = 0; i < eq_type.size(); i++)
    {
        new_eq_type.push_back({std::get<0>(eq_type[i]), (js_valuetype)std::get<1>(eq_type[i])});
    }

    return eq(new_eq_type, throw_error);
}

vector<js_valuetype> hmc_NodeArgsValue::getType()
{
    vector<js_valuetype> results;

    for (size_t i = 0; i < args.size(); i++)
    {
        if (args[i] == NULL)
            continue;
        results.push_back(hmc_napi_type::getType(env, args[i]));
    }

    return results;
}

js_valuetype hmc_NodeArgsValue::getType(size_t index)
{
    js_valuetype results = js_valuetype::js_undefined;

    if (!this->exists(index))
    {
        return results;
    }

    return hmc_napi_type::getType(env, args[index]);
}

bool hmc_NodeArgsValue::eq(size_t index, vector<js_valuetype> type_list, bool throw_error)
{
    bool results = false;

    if (!this->exists(index))
    {
        if (throw_error)
        {

            string error_msg = "The current input parameter has two errors:\n";
            error_msg.append("1.The number of input parameters should be greater than NNNN.\n");
            error_msg.append("2. The current input parameter does not meet the expected requirements. The expected parameter \n");
            error_msg.append("[ ");
            error_msg.append(to_string(index));
            error_msg.append(" ] can only be of type [ ");

            for (size_t i = 0; i < type_list.size(); i++)
            {
                js_valuetype type = type_list[i];
                error_msg.append(hmc_napi_type::typeName(type));
                error_msg.append(" , ");
            }
            if (!type_list.empty())
            {
                // " , "
                error_msg.pop_back();
                error_msg.pop_back();
                error_msg.pop_back();
            }
            error_msg.append(" ]");

            napi_throw_type_error(env, "PARAMETER_ERROR", hmc_string_util::string_to_lpstr(error_msg));
        }

        return results;
    }

    js_valuetype args_type = hmc_napi_type::getType(env, args[index]);

    for (size_t i = 0; i < type_list.size(); i++)
    {
        js_valuetype type = type_list[i];
        if (args_type == type)
        {
            return true;
        }
    }

    if (throw_error)
    {

        string error_msg = "";
        error_msg.append("The current input parameter has errors:\n");
        error_msg.append("The current input parameter does not meet the expected requirements. The expected parameter \n");
        error_msg.append("[ ");
        error_msg.append(to_string(index));
        error_msg.append(" ] can only be of type [ ");

        for (size_t i = 0; i < type_list.size(); i++)
        {
            js_valuetype type = type_list[i];
            error_msg.append(hmc_napi_type::typeName(type));
            error_msg.append(" , ");
        }

        if (!type_list.empty())
        {
            // " , "
            error_msg.pop_back();
            error_msg.pop_back();
            error_msg.pop_back();
        }
        error_msg.append(" ]");
        error_msg.append(" != ");
        error_msg.append("Your type:  < ");
        error_msg.append(hmc_napi_type::typeName(args_type));
        error_msg.append(" >      ");
        error_msg.append("   \n");
        napi_throw_type_error(env, "PARAMETER_ERROR", hmc_string_util::string_to_lpstr(error_msg));
    }

    return results;
}

bool hmc_NodeArgsValue::eq(size_t index, vector<napi_valuetype> type_list, bool throw_error)
{
    vector<js_valuetype> new_eq_type = {};

    for (size_t i = 0; i < type_list.size(); i++)
    {
        new_eq_type.push_back((js_valuetype)type_list[i]);
    }

    return eq(index, new_eq_type, throw_error);
}

namespace hmc_PromiseSession
{
    // 任务id
    size_t ____$hmcPromise_PromiseSessionID = 0;
    // 已经完结的任务id 当此处存在 将在取出数据后 立即被释放
    std::set<size_t> ____$hmcPromise_PromiseTaskEndStatusList = {};
    // 任务数据容器互斥体
    std::shared_mutex ____$hmcPromise_rwMutex = {};
    // 任务数据容器
    std::unordered_map<size_t, vector<any>> ____$hmcPromise_PromiseTaskList = {};
    // 任务数据 已读取索引 容器
    std::unordered_map<size_t, size_t > ____$hmcPromise_promise_task_id_send_index_list = std::unordered_map<size_t, size_t >();
    // 任务数据 工具已经初始化完成
    bool ____$hmcPromise_init = true;
    // 每次检测线程退出和线程数据的间隔
    long ___$Sleep_time = 10;
}

/**
 * @brief 判断此任务id是否已经完成 调用了end()
 *
 * @param SessionId
 * @return true
 * @return false
 */
bool hmc_PromiseSession::isClosed(size_t SessionId)
{
    return (____$hmcPromise_PromiseTaskEndStatusList.find(SessionId) != ____$hmcPromise_PromiseTaskEndStatusList.end());
}


int64_t hmc_PromiseSession::get_next_index(size_t PromiseID) {

    size_t _PromiseTaskDataListSize = 0;
    
     //未初始化
    if (____$hmcPromise_PromiseTaskList.count(PromiseID) < 1) {
        ____$hmcPromise_PromiseTaskList.insert(pair<size_t, vector<any>>(PromiseID, {}));
        return -1;
    }

    _PromiseTaskDataListSize = ____$hmcPromise_PromiseTaskList.at(PromiseID).size();

    // 未初始化索引
    if (____$hmcPromise_promise_task_id_send_index_list.count(PromiseID) > 0) {

        size_t Psize = ____$hmcPromise_promise_task_id_send_index_list.at(PromiseID);

        if (Psize == 0) { 
            ____$hmcPromise_promise_task_id_send_index_list.at(PromiseID)++;
            return (_PromiseTaskDataListSize > 0 ? 0 : -1); }

        // 溢出
        if (Psize >= _PromiseTaskDataListSize) {
            return -1;
        }
        
       ____$hmcPromise_promise_task_id_send_index_list.at(PromiseID)++;
       return Psize;
    }

    ____$hmcPromise_promise_task_id_send_index_list.insert(pair<size_t, size_t>(PromiseID, 0));
    return -1;
    
}

/**
 * @brief 提交数据push进容器
 *
 * @param SessionId 任务id
 * @param data 数据
 * @return true
 * @return false
 */
bool hmc_PromiseSession::send(size_t SessionId, any data)
{
    bool result = false;
    if (isClosed(SessionId))
    {
        return false;
    }
    ____$hmcPromise_rwMutex.lock();
    if (data.has_value())
    {
        auto da = ____$hmcPromise_PromiseTaskList;
        ____$hmcPromise_PromiseTaskList[SessionId].emplace_back(data);
    }
    else
    {
        ____$hmcPromise_PromiseTaskList[SessionId].emplace_back(any());
    }

    ____$hmcPromise_rwMutex.unlock();

    result = true;
    return result;
}

/**
 * @brief 提交数据push进容器
 *
 * @param SessionId 任务id
 * @param data_list 数据
 */
void hmc_PromiseSession::send(size_t SessionId, vector<any> data_list)
{
    if (isClosed(SessionId))
    {
        return;
    }

    // 锁定总表并push进数据
    ____$hmcPromise_rwMutex.lock();
    for (size_t i = 0; i < data_list.size(); i++)
    {
        auto data = data_list[i];
        if (data.has_value())
        {
            ____$hmcPromise_PromiseTaskList[SessionId].emplace_back(data);
        }
        else
        {
            ____$hmcPromise_PromiseTaskList[SessionId].emplace_back(any());
        }
    }
    ____$hmcPromise_rwMutex.unlock();

    return;
}

/**
 * @brief 提交此ID已经完成 并在 getAll/get 后释放掉容器
 *
 * @param SessionId
 * @param data
 */
void hmc_PromiseSession::end(size_t SessionId, any data)
{
    if (data.has_value())
        send(SessionId, data);
    ____$hmcPromise_PromiseTaskEndStatusList.insert(SessionId);
}

/**
 * @brief 判断此id是否未结束
 *
 * @param PromiseID 任务id
 * @param index 如果被赋值则在 容器中判断此索引是否存在
 * @return true
 * @return false
 */
bool hmc_PromiseSession::exists(size_t PromiseID, size_t index)
{
    if (isClosed(PromiseID))
    {
        return false;
    }
    else
    {
        if (index < 0)
        {
            return true;
        }
    }

    bool results = false;
    if (!____$hmcPromise_PromiseTaskList[PromiseID].size())
        return results;

    if (____$hmcPromise_PromiseTaskList[PromiseID].size() > index)
    {
        results = true;
    }

    return results && ____$hmcPromise_PromiseTaskList[PromiseID][index].has_value();
}

/**
 * @brief 取出内容并释放掉这部分的any容器 但不移除  如果任务已经结束时候则释放所有关联容器
 *
 * @param PromiseID
 * @return vector<any>
 */
vector<any> hmc_PromiseSession::getAll(size_t PromiseID, size_t max_size)
{
    vector<any> result;
    ____$hmcPromise_rwMutex.lock_shared();

    std::shared_ptr<void>_shared_close_lpsz_(nullptr, [&](void*) {
        ____$hmcPromise_rwMutex.unlock_shared();
        });

    auto temp_list = ____$hmcPromise_PromiseTaskList[PromiseID];


    if (!temp_list.empty()) {

        while (true)
        {
           int64_t index =  get_next_index(PromiseID);

           if (index == -1) {
               return result;
           }

           auto temp = temp_list.at(index);
           if (temp.has_value()) {
               result.push_back(temp);
           }

           //满足最大需求
           if (result.size()>= max_size) {
               return result;
           }
        }

    }
    return result;
}

/**
 * @brief 在新的线程 启动一个函数 以及监听此函数的运行结束的回调
 *
 * @param func
 * @return size_t
 */
size_t hmc_PromiseSession::open(std::function<void(vector<any> *data_list)> func)
{
    size_t PromiseID = ___get_open_id();


    std::thread data = thread([func, PromiseID]()
                              {
                                      vector<any> data_list;

                                      // 创建一个新的线程用来跑func的代码
                                      auto data_2 = new std::thread(func, &data_list);
                                      std::thread::native_handle_type handle = data_2->native_handle();
                                      vector<any> temp_data_list;
                                      size_t send_index = 0;
                                      while (true)
                                      {

                                          DWORD exitCode;
                                          if (GetExitCodeThread(handle, &exitCode) && exitCode != STILL_ACTIVE)
                                          {

                                              size_t size_max = data_list.size();
                                              for (; send_index < size_max; send_index++)
                                              {
                                                  auto data = data_list[send_index];
                                                  if (data.has_value())
                                                  {
                                                      temp_data_list.push_back(data);
                                                      data.reset();
                                                  }
                                              }

                                              data_2 = nullptr;
                                              data_list.clear();
                                              // 锁定总表并push进数据
                                               ____$hmcPromise_rwMutex.lock();

                                              for (size_t i = 0; i < temp_data_list.size(); i++)
                                              {
                                                  auto temp = temp_data_list[i];
                                                  ____$hmcPromise_PromiseTaskList[PromiseID].push_back(temp);
                                              }

                                              temp_data_list.clear();

                                              end(PromiseID);

                                               ____$hmcPromise_rwMutex.unlock();
                                              return 0;
                                          }
                                          else
                                          {
                                              size_t size_max = data_list.size();
                                              for (; send_index < size_max; send_index++)
                                              {
                                                  auto data = data_list[send_index];
                                                  if (data.has_value())
                                                  {
                                                      temp_data_list.push_back(data);
                                                      data.reset();
                                                  }
                                              }

                                              //// 锁定总表并push进数据
                                               ____$hmcPromise_rwMutex.lock();

                                              for (size_t i = 0; i < temp_data_list.size(); i++)
                                              {
                                                  auto temp = temp_data_list[i];
                                                  ____$hmcPromise_PromiseTaskList[PromiseID].push_back(temp);
                                              }

                                              temp_data_list.clear();

                                               ____$hmcPromise_rwMutex.unlock();
                                          }

                                          Sleep(___$Sleep_time);
                                      } });
    data.detach();

    return PromiseID;
}

/**
 * @brief 创建一个新的任务id 并为其开辟容器 但不为其创建 变化管理线程
 *
 * @return size_t
 */
size_t hmc_PromiseSession::open()
{
    size_t PromiseID = ___get_open_id();
    return PromiseID;
}

/**
 * @brief 在新的线程 启动一个函数 以及监听此函数的运行结束的回调
 *
 * @param func
 * @return size_t
 */
size_t hmc_PromiseSession::open(std::function<any()> func)
{
    size_t PromiseID = ___get_open_id();

    std::thread data = thread([func, PromiseID]()
                              { end(PromiseID, func()); });
    data.detach();

    return PromiseID;
}

size_t hmc_PromiseSession::data_size(size_t PromiseID)
{

    if (____$hmcPromise_PromiseTaskList.count(PromiseID) <= 0)
    {
        return 0;
    }

    return ____$hmcPromise_PromiseTaskList[PromiseID].size();
}

napi_value hmc_PromiseSession::getAll(napi_env env, size_t PromiseID, size_t size )
{
    napi_value result;

    vector<any> temp_list = getAll(PromiseID, size);
    if (temp_list.empty()) {
        napi_get_undefined(env, &result);
        return result;
    }
    napi_create_array(env, &result);

    for (size_t i = 0; i < temp_list.size(); i++)
    {
        any temp = temp_list[i];

        if (!temp.has_value())
        {
            napi_set_element(env, result, i, hmc_napi_create_value::Undefined(env));
            continue;
        }

        // 能被格式化为wstring
        if (temp.type() == typeid(vector<wstring>) || temp.type() == typeid(wstring) || temp.type() == typeid(wchar_t) || temp.type() == typeid(wchar_t *))
        {
            wstring temp_to_string = L"";
            hmc_string_util::any_to_string(temp, temp_to_string);
            napi_set_element(env, result, i, hmc_napi_create_value::String(env, temp_to_string));
            continue;
        }

        // 能被格式化为string
        string temp_to_string = "";
        if (hmc_string_util::any_to_string(temp, temp_to_string))
        {
            napi_set_element(env, result, i, hmc_napi_create_value::String(env, temp_to_string));
            continue;
        }

        // 错误
        napi_value tmep_unknown = hmc_napi_create_value::String(env, string("unknown<").append(temp.type().raw_name()).append(">"));
        napi_set_element(env, result, i, tmep_unknown);
    }

    return result;
}


size_t hmc_PromiseSession::___get_open_id() {
    
    size_t PromiseID = ____$hmcPromise_PromiseSessionID++;
    ____$hmcPromise_PromiseTaskList.insert(std::pair<size_t, vector<any>>(PromiseID, {}));
    ____$hmcPromise_promise_task_id_send_index_list.insert(pair<size_t, size_t>(PromiseID, 0));

    return PromiseID;
}

/**
 * @brief 在新的线程 启动一个函数 以及监听此函数的运行结束的回调
 *
 * @param func
 * @return size_t
 */
size_t hmc_PromiseSession::open(std::function<void()> func)
{
    size_t PromiseID = ___get_open_id();
    std::thread data = thread([func, PromiseID]()
                              { func();end(PromiseID, any()); });
    data.detach();

    return PromiseID;
}

template <class _Fn, class... _Args>
size_t hmc_PromiseSession::open2(_Fn &&_Fx, _Args &&..._Ax)
{
    size_t PromiseID = ___get_open_id();
    std::thread data = thread([_Fx, _Ax = std::forward_as_tuple(std::forward<_Args>(_Ax)...), PromiseID]()
                              { 
                            std::apply(_Fx, _Ax); // 将_Ax的值作为参数传递给_Fx
                              end(PromiseID, any()); });
    data.detach();

    return PromiseID;
}

size_t hmc_PromiseSession::max_id()
{
    return hmc_PromiseSession::____$hmcPromise_PromiseSessionID;
}

vector<int> hmc_PromiseSession::allTasks()
{
    vector<int> result;
    std::unordered_map<size_t, std::vector<std::any>> temp_List = hmc_PromiseSession::____$hmcPromise_PromiseTaskList;

    for (size_t i = 0; i < hmc_PromiseSession::____$hmcPromise_PromiseSessionID; i++)
    {
        if (temp_List.count(i) > 0)
        {
            result.push_back(i);
        }
    }
    return result;
}

vector<int> hmc_PromiseSession::ongoingTasks()
{
    vector<int> result;
    std::unordered_map<size_t, std::vector<std::any>> temp_List = hmc_PromiseSession::____$hmcPromise_PromiseTaskList;

    for (size_t i = 0; i < hmc_PromiseSession::____$hmcPromise_PromiseSessionID; i++)
    {
        if (temp_List.count(i) > 0)
        {
            // result.push_back(i);
            if (hmc_PromiseSession::____$hmcPromise_PromiseTaskEndStatusList.count(i) < 1)
            {
                result.push_back(i);
            }
        }
    }
    return result;
}

vector<int> hmc_PromiseSession::completeTasks()
{
    vector<int> result;
    std::unordered_map<size_t, std::vector<std::any>> temp_List = hmc_PromiseSession::____$hmcPromise_PromiseTaskList;

    for (size_t i = 0; i < hmc_PromiseSession::____$hmcPromise_PromiseSessionID; i++)
    {
        if (temp_List.count(i) > 0)
        {
            // result.push_back(i);
            if (hmc_PromiseSession::____$hmcPromise_PromiseTaskEndStatusList.count(i) > 0)
            {
                result.push_back(i);
            }
        }
    }
    return result;
}


napi_value _PromiseSession_getAll(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_number}, true))
    {
        return NULL;
    }
    return hmc_PromiseSession::getAll(env, input.getInt64(0), input.exists(1)? input.getInt64(1):999 );
}

napi_value _PromiseSession_stop(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_number}, true))
    {
        return NULL;
    }
    hmc_PromiseSession::end(input.getInt64(0));
    return hmc_napi_create_value::Undefined(env);
}

napi_value _PromiseSession_isClosed(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_number}, true))
    {
        return NULL;
    }
    bool isClosed = (input.getInt64(0) > hmc_PromiseSession::max_id()) ? false : hmc_PromiseSession::isClosed(input.getInt64(0));
    return hmc_napi_create_value::Boolean(env, isClosed);
}

napi_value _PromiseSession_max_id(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Number(env, (int64_t)hmc_PromiseSession::max_id());
}

napi_value _PromiseSession_data_size(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_number}, true))
    {
        return NULL;
    }
    return hmc_napi_create_value::Number(env, (int64_t)hmc_PromiseSession::data_size(input.getInt64(0)));
}

napi_value _PromiseSession_await(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_number}, true))
    {
        return NULL;
    }

    int id = input.getInt(0, -999);

    if (hmc_PromiseSession::____$hmcPromise_PromiseTaskList.count(id) > 0)
    {
        while (true)
        {
            if (!hmc_PromiseSession::isClosed(id))
            {
                Sleep(hmc_PromiseSession::___$Sleep_time);
            }
            else
            {
                return hmc_napi_create_value::Undefined(env);
            }
        }
    }

    return hmc_napi_create_value::Undefined(env);
}

napi_value _PromiseSession_set_sleep_time(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    // 参数预设 如果不符合则返回void
    if (!input.eq(0, {js_number}, true))
    {
        return NULL;
    }

    int64_t sleep_time = input.getInt64(0, 10);

    if (sleep_time > 0 && sleep_time < 1000000)
    {
        hmc_PromiseSession::___$Sleep_time = sleep_time;
    }

    return hmc_napi_create_value::Number(env, (int64_t)hmc_PromiseSession::___$Sleep_time);
}

napi_value _PromiseSession_ongoingTasks(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Array::Number(env, hmc_PromiseSession::ongoingTasks());
}

napi_value _PromiseSession_allTasks(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Array::Number(env, hmc_PromiseSession::allTasks());
}
napi_value _PromiseSession_completeTasks(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Array::Number(env, hmc_PromiseSession::completeTasks());
}