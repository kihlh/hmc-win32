#include "hmc_napi_value_util.h"
#include "hmc_util.h"

// ?hmc_napi_util::type
// 负责类型判断的逻辑
// ------------------------------------------------------------------------------------------------------

/**
 * @brief 获取napi数据的类型文本
 *
 * @param valuetype
 * @return string
 */
std::string hmc_napi_type::typeName(napi_valuetype valuetype)
{
    std::string getTypeName = std::string();
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
std::string hmc_napi_type::typeName(js_valuetype valuetype)
{
    if (valuetype < 9527)
    {
        return typeName((napi_valuetype)(valuetype));
    }
    std::string getTypeName = std::string();
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

    if (value_type == napi_object)
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

    return result;
}

/**
 * @brief 获取napi类型变量名称（人话）
 *
 * @param env
 * @param valuetype
 * @return string
 */
std::string hmc_napi_type::typeName(napi_env env, napi_value valuetype)
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
// template <typename... Args>
// bool hmc_napi_type::diff(napi_valuetype valuetype, const napi_valuetype &first, const Args &...args)
//{
//     napi_valuetype value_type;
//     napi_typeof(env, nodeValue, &value_type);
//     int result = false;
//
//     napi_valuetype temp[] = {first, args...};
//     size_t length = sizeof(temp) / sizeof(temp[0]);
//
//     for (size_t i = 0; i < length; i++)
//     {
//         if (temp[i] == value_type)
//             return temp[i];
//     }
//
//     return result;
// }

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
                         std::string()
                             .append("The current number of parameters passed is lower than required. The input is [")
                             .append(std::to_string(argLength))
                             .append("], and the ideal number of parameters should be [")
                             .append(std::to_string(minLength))
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
                         std::string()
                             .append("The current number of parameters passed is lower than required. The input is [")
                             .append(std::to_string(argLength))
                             .append("], and the ideal number of parameters should be [")
                             .append(std::to_string(minLength))
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
bool hmc_napi_type::isObjectkeyExists(napi_env env, napi_value objectValue, std::string key)
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
void hmc_napi_get_value::buffer_vector(napi_env env, napi_value nodeValue, std::vector<T> &buffer)
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
std::string hmc_napi_get_value::string_utf8(napi_env env, napi_value nodeValue, std::string defaultValue)
{
    std::string result = std::string("");

    if (!nodeValue)
    {
        return result;
    }
    if (hmc_napi_type::diff(env, nodeValue, napi_string))
    {

        size_t str_len;
        napi_value tmp;
        napi_status status = napi_coerce_to_string(env, nodeValue, &tmp);

        if (status == napi_ok)
        {
            status = napi_get_value_string_utf8(env, tmp, NULL, 0, &str_len);

            if (status != napi_ok || str_len >= BIT_2GB)
            {
                return result;
            }

            str_len += 1;
            result.resize(str_len);

            status = napi_get_value_string_utf8(env, tmp, (char *)&result[0], str_len, NULL);

            if (status != napi_ok)
            {
                result.clear();
                result.resize(0);
            }
        }
        return result;
    }
    else if (hmc_napi_type::diff(env, nodeValue, napi_number))
    {
        result.append(std::to_string(number_int(env, nodeValue)));
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
std::wstring hmc_napi_get_value::string_utf16(napi_env env, napi_value nodeValue, std::wstring defaultValue)
{
    std::wstring result = std::wstring(L"");

    if (!nodeValue)
    {
        return result;
    }
    // Buffer.from('文本', 'utf16le')
    if (hmc_napi_type::isBuffer(env, nodeValue))
    {
        std::vector<wchar_t> buffer;
        buffer_vector<wchar_t>(env, nodeValue, buffer);
        std::wstring wideString(buffer.begin(), buffer.end()); // 将 std::vector<wchar_t> 转换为 std::wstring
        return wideString;
    }
    // "文本"
    if (hmc_napi_type::diff(env, nodeValue, napi_string))
    {
        size_t str_len;
        napi_value tmp;
        napi_status status = napi_coerce_to_string(env, nodeValue, &tmp);

        if (status == napi_ok)
        {
            status = napi_get_value_string_utf16(env, tmp, NULL, 0, &str_len);

            if (status != napi_ok || str_len >= BIT_2GB)
            {
                return result;
            }

            str_len += 1;
            result.resize(str_len);

            status = napi_get_value_string_utf16(env, tmp, (char16_t *)&result[0], str_len, NULL);

            if (status != napi_ok)
            {
                result.clear();
                result.resize(0);
            }
        }

        return result;
    }
    // 506546
    else if (hmc_napi_type::diff(env, nodeValue, napi_number))
    {
        result.append(std::to_wstring(number_int(env, nodeValue)));
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
std::string hmc_napi_get_value::string_ansi(napi_env env, napi_value nodeValue, std::string defaultValue)
{
    std::wstring result = string_utf16(env, nodeValue);
    std::string string_ansi = hmc_string_util::utf16_to_ansi(result);

    return string_ansi;
}

/**
 * @brief 获取为宽(W)文本
 *
 * @param env
 * @param nodeValue
 * @return wstring
 */
std::wstring hmc_napi_get_value::string_wide(napi_env env, napi_value nodeValue, std::wstring defaultValue)
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
std::vector<std::string> hmc_napi_get_value::array_string_utf8(napi_env env, napi_value nodeValue)
{
    std::vector<std::string> unicode_str;

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

std::vector<std::wstring> hmc_napi_get_value::array_string_utf16(napi_env env, napi_value nodeValue)
{
    std::vector<std::wstring> result;

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
std::vector<int> hmc_napi_get_value::array_int(napi_env env, napi_value nodeValue)
{
    std::vector<int> num_list;

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
std::vector<int64_t> hmc_napi_get_value::array_int64(napi_env env, napi_value nodeValue)
{
    std::vector<int64_t> num_list;

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
std::vector<double> hmc_napi_get_value::array_double(napi_env env, napi_value nodeValue)
{
    std::vector<double> num_list;

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

    std::string key = string_ansi(env, nodeValue);
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
std::vector<unsigned char> hmc_napi_get_value::buffer_vector(napi_env env, napi_value nodeValue)
{
    std::vector<unsigned char> buffer;
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
std::wstring hmc_napi_get_value::buffer_utf16_strW(napi_env env, napi_value nodeValue)
{
    std::vector<wchar_t> buffer;
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
std::string hmc_napi_get_value::buffer_ansi_strA(napi_env env, napi_value nodeValue)
{
    std::vector<unsigned char> buffer;
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
std::string hmc_napi_get_value::buffer_utf8_strU8(napi_env env, napi_value nodeValue)
{
    std::vector<unsigned char> buffer;
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
    std::vector<wchar_t> buffer;
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
 * @brief 获取为时间戳
 *
 * @param env
 * @param objectValue
 */
double hmc_napi_get_value::date(napi_env env, napi_value nodeValue)
{
    double result = 0.0;

    if (hmc_napi_type::isDate(env, nodeValue))
    {
        napi_get_date_value(env, nodeValue, &result);
        return result;
    }

    return result;
}

/**
 * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
 * @param env
 * @param nodeValue
 * @return const char* c标准接口的  const char *
 */
const char *hmc_napi_get_value::buffer_utf8_clpStrU8(napi_env env, napi_value nodeValue)
{
    std::vector<unsigned char> buffer;
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
    std::vector<unsigned char> buffer;
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

napi_value hmc_napi_get_value::get_object_value(napi_env env, napi_value objectValue, std::string key)
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

int hmc_napi_get_value::get_object_value_int(napi_env env, napi_value objectValue, std::string key, int defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isNumber(env, napi_data))
    {
        return defaultValue;
    }

    return number_int(env, napi_data, defaultValue);
}

int64_t hmc_napi_get_value::get_object_value_int64(napi_env env, napi_value objectValue, std::string key, int64_t defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isNumber(env, napi_data) || !hmc_napi_type::isBoolean(env, napi_data))
    {
        return defaultValue;
    }

    return number_int64(env, napi_data, defaultValue);
}

double hmc_napi_get_value::get_object_value_double(napi_env env, napi_value objectValue, std::string key, double defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isNumber(env, napi_data))
    {
        return defaultValue;
    }

    return number_double(env, napi_data, defaultValue);
}

bool hmc_napi_get_value::get_object_value_bool(napi_env env, napi_value objectValue, std::string key, bool defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isNumber(env, napi_data))
    {
        return defaultValue;
    }

    return boolean_bool(env, napi_data, defaultValue);
}

std::wstring hmc_napi_get_value::get_object_value_utf16(napi_env env, napi_value objectValue, std::string key, std::wstring defaultValue)
{

    napi_value napi_data = get_object_value(env, objectValue, key);

    if (napi_data == NULL || !hmc_napi_type::isString(env, napi_data))
    {
        return defaultValue;
    }

    return string_utf16(env, napi_data, defaultValue);
}

std::string hmc_napi_get_value::get_object_value_utf8(napi_env env, napi_value objectValue, std::string key, std::string defaultValue)
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

std::string hmc_napi_get_value::get_object_value_ansi(napi_env env, napi_value objectValue, std::string key, std::string defaultValue)
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

    if (status != napi_ok)
    {
        return NULL;
    }
    return result;
}

// 创建一个布尔型
napi_value hmc_napi_create_value::Boolean(napi_env env, int value)
{
    napi_status status;
    napi_value result;
    status = napi_get_boolean(env, (bool)value, &result);

    if (status != napi_ok)
    {
        return NULL;
    }
    return result;
}

/**
 * @brief 返回一个 std::string utf8 string
 *
 * @param env 上下文
 * @param value 内容
 * @param re_size （以字节为单位）默认为 NAPI_AUTO_LENGTH
 * @return napi_value
 */
napi_value hmc_napi_create_value::String(napi_env env, std::string value, size_t re_size)
{
    napi_status status;
    napi_value result;

    if (re_size > value.size())
    {
        re_size = value.size();
    }

    if (!hmc_string_util::is_utf8(value))
    {
        return NULL;
    }

    status = napi_create_string_utf8(env, value.c_str(), re_size, &result);

    if (status != napi_ok)
    {
        return NULL;
    }

    return result;
}

/**
 * @brief 返回一个 std::string ansi string
 *
 * @param env 上下文
 * @param value 内容
 * @param re_size （以字节为单位）默认为 NAPI_AUTO_LENGTH
 * @return napi_value
 */
napi_value hmc_napi_create_value::StringA(napi_env env, std::string value, size_t re_size)
{
    napi_status status;
    napi_value result;

    std::wstring result2w = hmc_string_util::ansi_to_utf16(value);

    if (re_size > value.size())
    {
        re_size = value.size();
    }

    status = napi_create_string_utf16(env, reinterpret_cast<const char16_t *>(value.c_str()), re_size, &result);

    if (status != napi_ok)
    {
        return NULL;
    }

    return result;
}

/**
 * @brief 返回一个 std::string utf16 string
 *
 * @param env 上下文
 * @param value 内容
 * @param re_size （以字节为单位）默认为 NAPI_AUTO_LENGTH
 * @return napi_value
 */
napi_value hmc_napi_create_value::String(napi_env env, std::wstring value, size_t re_size)
{
    napi_status status;
    napi_value result;

    if (re_size > value.size())
    {
        re_size = value.size();
    }

    status = napi_create_string_utf16(env, reinterpret_cast<const char16_t *>(value.c_str()), re_size, &result);

    if (status != napi_ok)
    {
        return NULL;
    }

    return result;
}

napi_value hmc_napi_create_value::String(napi_env env)
{
    return String(env, "");
}

napi_value hmc_napi_create_value::ExFunction(napi_env env, std::string name, napi_callback cb)
{
    napi_value exported_function;
    napi_create_function(env,
                         name.c_str(),
                         name.length(),
                         cb,
                         NULL,
                         &exported_function);

    return exported_function;
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

    if (status != napi_ok)
    {
        return NULL;
    }

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

    if (status != napi_ok)
    {
        return NULL;
    }

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

    if (status != napi_ok)
    {
        return NULL;
    }

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
    DWORD hwnd = static_cast<DWORD>((DWORD)number);
    status = napi_create_int64(env, hwnd, &result);

    if (status != napi_ok)
    {
        return NULL;
    }

    return result;
}

napi_value hmc_napi_create_value::Number(napi_env env, unsigned long number)
{
    napi_status status;
    napi_value result;

    status = napi_create_int64(env, number, &result);

    if (status != napi_ok)
    {
        return NULL;
    }

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

    if (status != napi_ok)
    {
        return NULL;
    }

    return result;
}

napi_value hmc_napi_create_value::Bigint(napi_env env, long long bigint)
{

    napi_status status;
    napi_value result;

    status = napi_create_bigint_int64(env, bigint, &result);

    if (status != napi_ok)
    {
        return NULL;
    }

    return result;
}

void hmc_napi_create_value::BufferFinalizer(napi_env env, void *data, void *pointer)
{
    if (!pointer)
    {
        return;
    }
    free(pointer);
}

/**
 * @brief 返回一个 Buffer到js(返回的是空值 napi 不支持)
 *
 * @param env
 * @param data
 * @param size
 * @return napi_value
 */
napi_value hmc_napi_create_value::Buffer(napi_env env, std::vector<unsigned char> &buffer)
{
    napi_status status;
    napi_value Results = NULL;

    if (buffer.size() < 1)
    {
        return NULL;
    }

    // 此内存块会被 BufferFinalizer 自动释放
    void *yourPointer = ::malloc(buffer.size());

    if (yourPointer != NULL)
    {

        ::memcpy(yourPointer, buffer.data(), buffer.size());

        status = napi_create_external_buffer(env, buffer.size(), reinterpret_cast<void *>(yourPointer), BufferFinalizer, reinterpret_cast<void *>(yourPointer), &Results);
        if (status != napi_ok)
        {
            return NULL;
        }
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
    if (status != napi_ok)
    {
        return NULL;
    }
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

    if (status != napi_ok)
    {
        return NULL;
    }

    status = napi_set_property(env, ResultforObject, String(env, "bottom"), Number(env, (int64_t)rect.bottom));

    if (status != napi_ok)
    {
        return NULL;
    }

    status = napi_set_property(env, ResultforObject, String(env, "left"), Number(env, (int64_t)rect.left));

    if (status != napi_ok)
    {
        return NULL;
    }

    status = napi_set_property(env, ResultforObject, String(env, "right"), Number(env, (int64_t)rect.right));

    if (status != napi_ok)
    {
        return NULL;
    }

    status = napi_set_property(env, ResultforObject, String(env, "top"), Number(env, (int64_t)rect.top));
    if (status != napi_ok)
    {
        return NULL;
    }

    return ResultforObject;
}

napi_value hmc_napi_create_value::Point(napi_env env, POINT point)
{
    napi_value ResultforObject;
    napi_status status;
    status = napi_create_object(env, &ResultforObject);

    if (status != napi_ok)
    {
        return NULL;
    }

    status = napi_set_property(env, ResultforObject, String(env, "x"), Number(env, (int64_t)point.x));

    if (status != napi_ok)
    {
        return NULL;
    }

    status = napi_set_property(env, ResultforObject, String(env, "y"), Number(env, (int64_t)point.y));

    if (status != napi_ok)
    {
        return NULL;
    }

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

    if (status != napi_ok)
    {
        return NULL;
    }
    return Results;
}

/**
 * @brief 自识别类型
 *
 * @param env
 * @param anyValue
 * @return napi_value
 */
napi_value hmc_napi_create_value::New(napi_env env, std::any anyValue)
{
    napi_status status;
    napi_value ResultForAny = NULL;
    if (anyValue.has_value())
    {
        // 整形
        if (anyValue.type() == typeid(DWORD))
        {
            ResultForAny = Number(env, std::any_cast<DWORD>(anyValue));
        }
        else if (anyValue.type() == typeid(int))
        {
            ResultForAny = Number(env, std::any_cast<int>(anyValue));
        }
        else if (anyValue.type() == typeid(long))
        {
            ResultForAny = Number(env, (int64_t)std::any_cast<long>(anyValue));
        }
        else if (anyValue.type() == typeid(long long))
        {
            ResultForAny = Number(env, std::any_cast<long long>(anyValue));
        }
        else if (anyValue.type() == typeid(HWND))
        {
            ResultForAny = Number(env, std::any_cast<HWND>(anyValue));
        }
        else if (anyValue.type() == typeid(int64_t))
        {
            ResultForAny = Number(env, std::any_cast<int64_t>(anyValue));
        }
        else if (anyValue.type() == typeid(short))
        {
            ResultForAny = Number(env, std::any_cast<short>(anyValue));
        }
        else if (anyValue.type() == typeid(unsigned long long) || anyValue.type() == typeid(unsigned long))
        {
            ResultForAny = Number(env, (unsigned long)std::any_cast<unsigned long long>(anyValue));
        }
        // 浮点
        else if (anyValue.type() == typeid(float))
        {
            ResultForAny = Number(env, (double)std::any_cast<float>(anyValue));
        }
        else if (anyValue.type() == typeid(double))
        {
            ResultForAny = Number(env, std::any_cast<double>(anyValue));
        }
        else if (anyValue.type() == typeid(long double))
        {
            ResultForAny = Number(env, (double)std::any_cast<long double>(anyValue));
        }
        // 文本型
        else if (anyValue.type() == typeid(std::string))
        {
            ResultForAny = String(env, std::any_cast<std::string>(anyValue));
        }
        else if (anyValue.type() == typeid(std::wstring))
        {
            ResultForAny = String(env, std::any_cast<std::wstring>(anyValue));
        }
        else if (anyValue.type() == typeid(char *))
        {
            ResultForAny = String(env, std::any_cast<char *>(anyValue));
        }
        else if (anyValue.type() == typeid(CHAR *))
        {
            ResultForAny = String(env, std::any_cast<CHAR *>(anyValue));
        }
        else if (anyValue.type() == typeid(WCHAR *))
        {
            ResultForAny = String(env, std::any_cast<WCHAR *>(anyValue));
        }
        // bool
        else if (anyValue.type() == typeid(bool))
        {
            ResultForAny = Boolean(env, std::any_cast<bool>(anyValue));
        }
        else if (anyValue.type() == typeid(BOOL))
        {
            ResultForAny = Boolean(env, std::any_cast<BOOL>(anyValue));
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
 * @brief Destroy the hmc Node Value::hmc Node Value object
 *
 */
hmc_NodeArgsValue::~hmc_NodeArgsValue()
{
    args.clear();
    env = NULL;
}

bool hmc_NodeArgsValue::removeIndex(size_t Index)
{

    size_t oid_len = args.size();

    if (Index < oid_len)
    {
        args.erase(args.begin() + Index);
        return oid_len != args.size();
    }

    return false;
}

hmc_NodeArgsValue::hmc_NodeArgsValue(napi_env envs, napi_callback_info info)
{
    env = envs;

    napi_status status;
    size_t argc = 0;

    if ((status = napi_get_cb_info(envs, info, &argc, NULL, NULL, NULL)) != napi_ok)
    {
        std::string error_msg = "";
        error_msg.append("napi_get_cb_info fn < ");
        error_msg.append(" >");
        error_msg.append(__FUNCTION__);
        error_msg.append("get args size ");
        error_msg.append("   ");
        error_msg.append("error code-> ");
        error_msg.append(std::to_string(status));
        error_msg.append("   ");

        napi_throw_type_error(envs, NULL, hmc_string_util::string_to_lpstr(error_msg));
    }

    if (argc > 0)
    {

        args.reserve(argc);
        args.resize(argc);

        if ((status = napi_get_cb_info(envs, info, &argc, reinterpret_cast<napi_value *>(&args[0]), NULL, NULL)) != napi_ok)
        {
            std::string error_msg = "";
            error_msg.append("napi_get_cb_info fn < ");
            error_msg.append(" >");
            error_msg.append(__FUNCTION__);
            error_msg.append("napi_get_cb_info(envs, info, &argc, reinterpret_cast<napi_value *>(&args[0]), NULL, NULL)");
            error_msg.append("   ");
            error_msg.append("error code-> ");
            error_msg.append(std::to_string(status));
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

            std::string error_msg = "";
            error_msg.append("args eq  < ");
            error_msg.append(__FUNCTION__);
            error_msg.append(" >\n");
            error_msg.append("The current number of parameters passed is lower than required. The input is \n");
            error_msg.append("[ ");
            error_msg.append(std::to_string(min_length));
            error_msg.append(" ], and the ideal number of parameters should be ");
            error_msg.append("[ ");
            error_msg.append(std::to_string(max_length));
            error_msg.append(" ]");

            napi_throw_type_error(env, "PARAMETER_ERROR", hmc_string_util::string_to_lpstr(error_msg));
        }
        return false;
    }
    return results;
}

std::wstring hmc_NodeArgsValue::getStringWide(size_t index, std::wstring defaultValue)
{
    std::wstring results = std::wstring(L"");
    results.append(defaultValue);
    if (!this->exists(index))
    {
        return results;
    }
    results = hmc_napi_get_value::string_utf16(env, args[index]);

    return results;
}

std::vector<napi_value> hmc_NodeArgsValue::get_args()
{
    return args;
}

napi_value hmc_NodeArgsValue::at(size_t index)
{
    if (this->exists(index))
    {
        return this->args[index];
    }

    return NULL;
}

std::string hmc_NodeArgsValue::getStringAnsi(size_t index, std::string defaultValue)
{

    std::string results = std::string("");
    results.append(defaultValue);
    if (!this->exists(index))
    {
        return results;
    }
    results = hmc_napi_get_value::string_ansi(env, args[index]);

    return results;
}

std::string hmc_NodeArgsValue::getStringUtf8(size_t index, std::string defaultValue)
{

    std::string results = std::string("");
    results.append(defaultValue);
    if (!this->exists(index))
    {
        return results;
    }
    results = hmc_napi_get_value::string_utf8(env, args[index]);

    return results;
}

std::vector<std::string> hmc_NodeArgsValue::getArrayString(size_t index, std::vector<std::string> defaultValue)
{
    std::vector<std::string> results = {};

    if (this->exists(index))
    {
        std::vector<std::wstring> datas = hmc_napi_get_value::array_string_utf16(env, args[index]);
        for (size_t i = 0; i < datas.size(); i++)
        {
            results.push_back(hmc_string_util::utf16_to_ansi(datas[i]));
        }

        return results;
    }

    return results;
}

std::vector<std::wstring> hmc_NodeArgsValue::getArrayWstring(size_t index, std::vector<std::wstring> defaultValue)
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

std::vector<unsigned char> hmc_NodeArgsValue::getBuffer(size_t index, std::vector<unsigned char> defaultValue)
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

std::vector<int> hmc_NodeArgsValue::getArrayInt(size_t index, std::vector<int> defaultValue)
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

            std::string error_msg = "The current input parameter has two errors:\n";
            error_msg.append("1.The number of input parameters should be greater than NNNN.\n");
            error_msg.append("2. The current input parameter does not meet the expected requirements. The expected parameter \n");
            error_msg.append("[ ");
            error_msg.append(std::to_string(index));
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

        std::string error_msg = "";
        error_msg.append("The current input parameter has errors:\n");
        error_msg.append("The current input parameter does not meet the expected requirements. The expected parameter \n");
        error_msg.append("[ ");
        error_msg.append(std::to_string(index));
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

bool hmc_NodeArgsValue::eq(std::vector<js_valuetype> eq_type, bool throw_error)
{
    bool results = true;
    std::string error_message = "There are discrepancies between the current parameters and the expected values. The listed type errors are as follows:\n ";

    size_t count = eq_type.size();
    for (size_t i = 0; i < count; i++)
    {
        const auto value = eq_type[i];
        const auto index = i;

        if (!this->exists(index))
        {
            error_message.append("Parameter [ ");
            error_message.append(std::to_string(index));
            error_message.append(" ] does not exist. Only [ ");
            error_message.append(std::to_string(this->args.size()));
            error_message.append(" ] parameter(s) were provided.\n");

            error_message.append("The expected parameter should be: \n [ ");

            error_message.append(hmc_napi_type::typeName((js_valuetype)value));
            error_message.append(" , ");

            error_message = hmc_string_util::trimAll(error_message, " , ");

            error_message.append(" ]\n-------------------------------------------\n");
            results = false;

            continue;
        }

        auto the_type = hmc_napi_type::getType(env, args[index]);

        std::string the_types = hmc_napi_type::typeName((js_valuetype)value);
        bool has_second = the_type == value;

        if (!has_second)
        {
            error_message.append(" [ ");
            error_message.append(std::to_string(index));
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

bool hmc_NodeArgsValue::eq(std::vector<std::tuple<size_t, js_valuetype>> eq_type, bool throw_error)
{
    bool results = true;
    std::map<size_t, std::vector<js_valuetype>> eq_type_index_list = {};
    std::string error_message = "There are discrepancies between the current parameters and the expected values. The listed type errors are as follows:\n ";

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
            auto value = std::pair<size_t, std::vector<js_valuetype>>(index, std::vector<js_valuetype>());
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
            error_message.append(std::to_string(eqtype.first));
            error_message.append(" ] does not exist. Only [ ");
            error_message.append(std::to_string(this->args.size()));
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

        std::string the_types = "";

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
            error_message.append(std::to_string(eqtype.first));
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

bool hmc_NodeArgsValue::eq(std::vector<std::tuple<size_t, napi_valuetype>> eq_type, bool throw_error)
{
    std::vector<std::tuple<size_t, js_valuetype>> new_eq_type = {};

    for (size_t i = 0; i < eq_type.size(); i++)
    {
        new_eq_type.push_back({std::get<0>(eq_type[i]), (js_valuetype)std::get<1>(eq_type[i])});
    }

    return eq(new_eq_type, throw_error);
}

std::vector<js_valuetype> hmc_NodeArgsValue::getType()
{
    std::vector<js_valuetype> results;

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

bool hmc_NodeArgsValue::eq(size_t index, std::vector<js_valuetype> type_list, bool throw_error)
{
    bool results = false;

    if (!this->exists(index))
    {
        if (throw_error)
        {

            std::string error_msg = "The current input parameter has two errors:\n";
            error_msg.append("1.The number of input parameters should be greater than NNNN.\n");
            error_msg.append("2. The current input parameter does not meet the expected requirements. The expected parameter \n");
            error_msg.append("[ ");
            error_msg.append(std::to_string(index));
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

        std::string error_msg = "";
        error_msg.append("The current input parameter has errors:\n");
        error_msg.append("The current input parameter does not meet the expected requirements. The expected parameter \n");
        error_msg.append("[ ");
        error_msg.append(std::to_string(index));
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

bool hmc_NodeArgsValue::eq(size_t index, std::vector<napi_valuetype> type_list, bool throw_error)
{
    std::vector<js_valuetype> new_eq_type = {};

    for (size_t i = 0; i < type_list.size(); i++)
    {
        new_eq_type.push_back((js_valuetype)type_list[i]);
    }

    return eq(index, new_eq_type, throw_error);
}

js_value hmc_NodeArgsValue::get_value(size_t index)
{
    return js_value(this->env, this->at(index));
}

std::vector<js_value> hmc_NodeArgsValue::get_values()
{
    std::vector<js_value> result;
    for (size_t i = 0; i < this->size(); i++)
    {
        result.push_back(get_value(i));
    }

    return result;
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
    std::unordered_map<size_t, std::vector<std::any>> ____$hmcPromise_PromiseTaskList = {};
    // 任务数据 已读取索引 容器
    std::unordered_map<size_t, size_t> ____$hmcPromise_promise_task_id_send_index_list = std::unordered_map<size_t, size_t>();
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

int64_t hmc_PromiseSession::get_next_index(size_t PromiseID)
{

    size_t _PromiseTaskDataListSize = 0;

    // 未初始化
    if (____$hmcPromise_PromiseTaskList.count(PromiseID) < 1)
    {
        ____$hmcPromise_PromiseTaskList.insert(std::pair<size_t, std::vector<std::any>>(PromiseID, {}));
        return -1;
    }

    _PromiseTaskDataListSize = ____$hmcPromise_PromiseTaskList.at(PromiseID).size();

    // 未初始化索引
    if (____$hmcPromise_promise_task_id_send_index_list.count(PromiseID) > 0)
    {

        size_t Psize = ____$hmcPromise_promise_task_id_send_index_list.at(PromiseID);

        if (Psize == 0)
        {
            ____$hmcPromise_promise_task_id_send_index_list.at(PromiseID)++;
            return (_PromiseTaskDataListSize > 0 ? 0 : -1);
        }

        // 溢出
        if (Psize >= _PromiseTaskDataListSize)
        {
            return -1;
        }

        ____$hmcPromise_promise_task_id_send_index_list.at(PromiseID)++;
        return Psize;
    }

    ____$hmcPromise_promise_task_id_send_index_list.insert(std::pair<size_t, size_t>(PromiseID, 0));
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
bool hmc_PromiseSession::send(size_t SessionId, std::any data)
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
        ____$hmcPromise_PromiseTaskList[SessionId].emplace_back(std::any());
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
void hmc_PromiseSession::send(size_t SessionId, std::vector<std::any> data_list)
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
            ____$hmcPromise_PromiseTaskList[SessionId].emplace_back(std::any());
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
void hmc_PromiseSession::end(size_t SessionId, std::any data)
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
 * @return  std::vector<std::any>
 */
std::vector<std::any> hmc_PromiseSession::getAll(size_t PromiseID, size_t max_size)
{
    std::vector<std::any> result;
    ____$hmcPromise_rwMutex.lock_shared();

    std::shared_ptr<void> _shared_close_lpsz_(nullptr, [&](void *)
                                              { ____$hmcPromise_rwMutex.unlock_shared(); });

    auto temp_list = ____$hmcPromise_PromiseTaskList[PromiseID];

    if (!temp_list.empty())
    {

        while (true)
        {
            int64_t index = get_next_index(PromiseID);

            if (index == -1)
            {
                return result;
            }

            auto temp = temp_list.at(index);
            if (temp.has_value())
            {
                result.push_back(temp);
            }

            // 满足最大需求
            if (result.size() >= max_size)
            {
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
size_t hmc_PromiseSession::open(std::function<void(std::vector<std::any> *data_list)> func)
{
    size_t PromiseID = ___get_open_id();

    std::thread data = std::thread([func, PromiseID]()
                                   {
            std::vector<std::any> data_list;

            // 创建一个新的线程用来跑func的代码
            auto data_2 = new std::thread(func, &data_list);
            std::thread::native_handle_type handle = data_2->native_handle();
            std::vector<std::any> temp_data_list;
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
size_t hmc_PromiseSession::open(std::function<std::any()> func)
{
    size_t PromiseID = ___get_open_id();

    std::thread data = std::thread([func, PromiseID]()
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

napi_value hmc_PromiseSession::getAll(napi_env env, size_t PromiseID, size_t size)
{
    napi_value result;

    std::vector<std::any> temp_list = getAll(PromiseID, size);
    if (temp_list.empty())
    {
        napi_get_undefined(env, &result);
        return result;
    }
    napi_create_array(env, &result);

    for (size_t i = 0; i < temp_list.size(); i++)
    {
        std::any temp = temp_list[i];

        if (!temp.has_value())
        {
            napi_set_element(env, result, i, hmc_napi_create_value::Undefined(env));
            continue;
        }

        // 能被格式化为wstring
        if (temp.type() == typeid(std::vector<std::wstring>) || temp.type() == typeid(std::wstring) || temp.type() == typeid(wchar_t) || temp.type() == typeid(wchar_t *))
        {
            std::wstring temp_to_string = L"";
            hmc_string_util::any_to_string(temp, temp_to_string);
            napi_set_element(env, result, i, hmc_napi_create_value::String(env, temp_to_string));
            continue;
        }

        // 能被格式化为string
        std::string temp_to_string = "";
        if (hmc_string_util::any_to_string(temp, temp_to_string))
        {
            napi_set_element(env, result, i, hmc_napi_create_value::String(env, temp_to_string));
            continue;
        }

        // 错误
        napi_value tmep_unknown = hmc_napi_create_value::String(env, std::string("unknown<").append(temp.type().raw_name()).append(">"));
        napi_set_element(env, result, i, tmep_unknown);
    }

    return result;
}

size_t hmc_PromiseSession::___get_open_id()
{

    size_t PromiseID = ____$hmcPromise_PromiseSessionID++;
    ____$hmcPromise_PromiseTaskList.insert(std::pair<size_t, std::vector<std::any>>(PromiseID, {}));
    ____$hmcPromise_promise_task_id_send_index_list.insert(std::pair<size_t, size_t>(PromiseID, 0));

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
    std::thread data = std::thread([func, PromiseID]()
                                   { func(); end(PromiseID, std::any()); });
    data.detach();

    return PromiseID;
}

template <class _Fn, class... _Args>
size_t hmc_PromiseSession::open2(_Fn &&_Fx, _Args &&..._Ax)
{
    size_t PromiseID = ___get_open_id();
    std::thread data = std::thread([_Fx, _Ax = std::forward_as_tuple(std::forward<_Args>(_Ax)...), PromiseID]()
                                   {
        std::apply(_Fx, _Ax); // 将_Ax的值作为参数传递给_Fx
        end(PromiseID, std::any()); });
    data.detach();

    return PromiseID;
}

size_t hmc_PromiseSession::max_id()
{
    return hmc_PromiseSession::____$hmcPromise_PromiseSessionID;
}

std::vector<int> hmc_PromiseSession::allTasks()
{
    std::vector<int> result;
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

std::vector<int> hmc_PromiseSession::ongoingTasks()
{
    std::vector<int> result;
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

std::vector<int> hmc_PromiseSession::completeTasks()
{
    std::vector<int> result;
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
    return hmc_PromiseSession::getAll(env, input.getInt64(0), input.exists(1) ? input.getInt64(1) : 999);
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
                ::Sleep(hmc_PromiseSession::___$Sleep_time);
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
    auto list = hmc_PromiseSession::ongoingTasks();
    auto ouput = hmc_napi_create_value::jsArray(env);
    for (auto &&it : list)
    {
        ouput.putNumber(static_cast<int64_t>(it));
    }

    return ouput.toValue();
}

napi_value _PromiseSession_allTasks(napi_env env, napi_callback_info info)
{

    auto list = hmc_PromiseSession::allTasks();
    auto ouput = hmc_napi_create_value::jsArray(env);
    for (auto &&it : list)
    {
        ouput.putNumber(static_cast<int64_t>(it));
    }
    return ouput.toValue();
}

napi_value _PromiseSession_completeTasks(napi_env env, napi_callback_info info)
{
    auto list = hmc_PromiseSession::completeTasks();
    auto ouput = hmc_napi_create_value::jsArray(env);
    for (auto &&it : list)
    {
        ouput.putNumber(static_cast<int64_t>(it));
    }

    return ouput.toValue();
}

size_t hmc_PromiseSession::get_sleep_time()
{
    return hmc_PromiseSession::___$Sleep_time;
}

napi_value _PromiseSession_get_sleep_time(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Number(env, (int64_t)hmc_PromiseSession::___$Sleep_time);
}

js_value::js_value(napi_env env, napi_callback_info info)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);

    for (size_t i = 0; i < input.size(); i++)
    {
        if (input.exists(i))
        {
            js_value(env, input.at(i));
        }
    }
}

js_value::js_value(napi_env env, napi_callback_info info, size_t index)
{
    hmc_NodeArgsValue input = hmc_NodeArgsValue(env, info);
    if (input.exists(index))
    {
        js_value(env, input.at(index));
    }
}

js_value::js_value(napi_env env, napi_value nodeValue)
{
    switch (hmc_napi_type::getType(env, nodeValue))
    {
        // case js_valuetype::js_array:

        //     break;
        // case js_valuetype::js_date:
        //     getTypeName.append("date");
        //     break;
        // case js_valuetype::js_error:
        //     getTypeName.append("error");
        //     break;
    case js_valuetype::js_buffer:
        this->data = hmc_napi_get_value::buffer_vector(env, nodeValue);
        break;
    case js_valuetype::js_point:
        this->data = hmc_napi_get_value::point(env, nodeValue);
        break;
    case js_valuetype::js_rect:
        this->data = hmc_napi_get_value::rect(env, nodeValue);
        break;
    case napi_null:
        this->data = NULL;
        break;
    case napi_number:
        // if(hmc_napi_type::is)
        this->data = hmc_napi_get_value::number_int64(env, nodeValue);
        break;
    case napi_string:
        this->data = hmc_napi_get_value::string_utf16(env, nodeValue);
        break;
        // case napi_undefined:

        //     break;
        // case napi_object:
        //     this->data = hmc_napi_get_value::buffer_vector(env,nodeValue);
        //     break;

    case napi_boolean:
        this->data = hmc_napi_get_value::boolean_bool(env, nodeValue);
        break;
    }
}

std::string js_value::typeName()
{
    return hmc_napi_type::typeName(this->type);
}

int js_value::getInt(int defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    if (this->isNumber())
    {
        return std::any_cast<int_least16_t>(this->data);
    }
    return defaultValue;
}

int64_t js_value::getInt64(int64_t defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    if (this->isNumber())
    {
        return std::any_cast<int64_t>(this->data);
    }
    return defaultValue;
}

std::string js_value::getStringAnsi(std::string defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    if (this->isString())
    {
        return hmc_string_util::utf16_to_ansi(std::any_cast<std::wstring>(this->data));
    }
    return defaultValue;
}

std::wstring js_value::getStringWide(std::wstring defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    if (this->isString())
    {
        return (std::any_cast<std::wstring>(this->data));
    }
    return defaultValue;
}

std::string js_value::getStringUtf8(std::string defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    if (this->isString())
    {
        return hmc_string_util::utf16_to_utf8(std::any_cast<std::wstring>(this->data));
    }
    return defaultValue;
}

bool js_value::getBool(bool defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    if (this->isBoolean())
    {
        return std::any_cast<bool>(this->data);
    }
    if (this->isNumber())
    {
        return std::any_cast<int>(this->data) == 1;
    }
    return defaultValue;
}

std::vector<unsigned char> js_value::getBuffer(std::vector<unsigned char> defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    if (this->isBuffer())
    {
        return std::any_cast<std::vector<unsigned char>>(this->data);
    }
    return defaultValue;
}

double js_value::getDouble(double defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    return defaultValue;
}

DWORD js_value::getDword(DWORD defaultValue)
{
    if (this->isNumber())
    {
        return (DWORD)std::any_cast<long>(this->data);
    }
    return defaultValue;
}

HWND js_value::getHwnd(HWND defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    if (this->isNumber())
    {
        return (HWND)std::any_cast<long>(this->data);
    }
    return defaultValue;
}

std::vector<std::string> js_value::getArrayString(std::vector<std::string> defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    return defaultValue;
}

std::vector<int> js_value::getArrayInt(std::vector<int> defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;

    return defaultValue;
}

std::vector<std::wstring> js_value::getArrayWstring(std::vector<std::wstring> defaultValue)
{
    if (!this->data.has_value())
        return defaultValue;
    return defaultValue;
}

bool js_value::has_value()
{
    return this->has_value();
}

bool js_value::isBuffer()
{
    return this->type == js_valuetype::js_buffer;
}

bool js_value::isString()
{
    return this->type == js_valuetype::js_string;
}

bool js_value::isNumber()
{
    return this->type == js_valuetype::js_number;
}

bool js_value::isBoolean()
{
    return this->type == js_valuetype::js_boolean;
}

bool js_value::isBigint()
{
    return this->type == js_valuetype::js_bigint;
}

bool js_value::isFunction()
{
    return this->type == js_valuetype::js_function;
}

bool js_value::isObject()
{
    return this->type == js_valuetype::js_object;
}

bool js_value::isUndefined()
{
    return this->type == js_valuetype::js_undefined;
}

bool js_value::isNull()
{
    return this->type == js_valuetype::js_null;
}

bool js_value::isExternal()
{
    return this->type == js_valuetype::js_external;
}

bool js_value::isArray()
{
    return this->type == js_valuetype::js_array;
}

bool js_value::isDate()
{
    return this->type == js_valuetype::js_date;
}

bool js_value::isError()
{
    return this->type == js_valuetype::js_error;
}

bool js_value::isPoint()
{
    return this->type == js_valuetype::js_point;
}

bool js_value::isPromise()
{
    return (this->type == js_valuetype::js_promise) ? true : this->type == js_valuetype::js_promise_function;
}

bool js_value::isRect()
{
    return this->type == js_valuetype::js_rect;
}

js_value::~js_value()
{
    this->data.reset();
    this->data = std::any();
}

napi_value hmc_napi_create_value::Error(napi_env env, std::string error, std::string fn_name, std::string ErrorCode)
{
    napi_value result;
    std::string msg_data = fn_name + "\n";
    msg_data.append(error);
    napi_create_error(
        env,
        hmc_napi_create_value::String(env, ErrorCode),
        hmc_napi_create_value::String(env, msg_data),
        &result);
    return result;
}

napi_value hmc_napi_create_value::Error(napi_env env, std::wstring error, std::wstring fn_name, std::wstring ErrorCode)
{

    napi_value result;
    std::wstring msg_data = fn_name + L"\n";
    msg_data.append(error);
    napi_create_error(
        env,
        hmc_napi_create_value::String(env, ErrorCode),
        hmc_napi_create_value::String(env, msg_data),
        &result);
    return result;
}

napi_value hmc_napi_create_value::ErrorBreak(napi_env env, std::string error, std::string fn_name, std::string ErrorCode)
{
    std::string msg_data = fn_name + "\n";
    msg_data.append(error);
    napi_throw_error(env, ErrorCode.c_str(), msg_data.c_str());
    return hmc_napi_create_value::Null(env);
}

napi_value hmc_napi_create_value::ErrorBreakA(napi_env env, std::string error, std::string fn_name, std::string ErrorCode)
{
    std::string msg_data = fn_name + "\n";
    msg_data.append(error);
    napi_throw_error(
        env,
        hmc_string_util::ansi_to_utf8(ErrorCode).c_str(),
        hmc_string_util::ansi_to_utf8(msg_data).c_str());
    return hmc_napi_create_value::Null(env);
}

napi_value hmc_napi_create_value::ErrorBreak(napi_env env, std::wstring error, std::wstring fn_name, std::wstring ErrorCode)
{
    std::wstring msg_data = fn_name + L"\n";
    msg_data.append(error);
    napi_throw_error(
        env,
        hmc_string_util::utf16_to_utf8(ErrorCode).c_str(),
        hmc_string_util::utf16_to_utf8(ErrorCode).c_str());
    return hmc_napi_create_value::Null(env);
}

void hmc_napi_create_value::jsArray::clear()
{
    napi_value_list.clear();
}

size_t hmc_napi_create_value::jsArray::size()
{
    return napi_value_list.size();
}

hmc_napi_create_value::jsArray::jsArray(napi_env env)
{
    if (env == NULL)
    {
        return;
    }

    node_env = env;
    napi_value ResultforArray;
    status = napi_create_array(env, &array_value);
    is_ready_ok = status == napi_ok;
}

napi_value hmc_napi_create_value::jsArray::toValue()
{
    if (is_ready_ok)
    {
        size_t count = napi_value_list.size();
        for (size_t i = 0; i < count; i++)
        {
            auto &value = napi_value_list.at(i);

            status = napi_set_element(node_env, array_value, i, value);

            if (status != napi_ok)
            {
                return NULL;
            }
        }
        return array_value;
    }

    return NULL;
}

void hmc_napi_create_value::jsArray::putValue(napi_value Object)
{
    napi_value_list.push_back(Object);
}

void hmc_napi_create_value::jsArray::putBigint(int64_t Object)
{
    napi_value_list.push_back(hmc_napi_create_value::Bigint(node_env, Object));
}

void hmc_napi_create_value::jsArray::putNumber(int64_t Object)
{
    napi_value_list.push_back(hmc_napi_create_value::Number(node_env, Object));
}

void hmc_napi_create_value::jsArray::putNumber(double Object)
{
    napi_value_list.push_back(hmc_napi_create_value::Number(node_env, Object));
}

void hmc_napi_create_value::jsArray::putNull()
{
    napi_value_list.push_back(hmc_napi_create_value::Null(node_env));
}

void hmc_napi_create_value::jsArray::putUndefined()
{
    napi_value_list.push_back(hmc_napi_create_value::Undefined(node_env));
}

void hmc_napi_create_value::jsArray::putBuffer(std::vector<unsigned char> input)
{
    napi_value_list.push_back(hmc_napi_create_value::Buffer(node_env, input));
}

void hmc_napi_create_value::jsArray::putBoolean(bool Boolean)
{
    napi_value_list.push_back(hmc_napi_create_value::Boolean(node_env, Boolean));
}

void hmc_napi_create_value::jsArray::putString(std::wstring Object, size_t re_size)
{
    napi_value_list.push_back(hmc_napi_create_value::String(node_env, Object, re_size));
}

void hmc_napi_create_value::jsArray::putString(std::string Object, size_t re_size)
{
    napi_value_list.push_back(hmc_napi_create_value::String(node_env, Object, re_size));
}

void hmc_napi_create_value::jsArray::putStringA(std::string Object, size_t re_size)
{
    napi_value_list.push_back(hmc_napi_create_value::StringA(node_env, Object, re_size));
}

// !  ----------------------------------------------------------------

void hmc_napi_create_value::jsObject::clear()
{
    napi_value_list.clear();
}

size_t hmc_napi_create_value::jsObject::size()
{
    return napi_value_list.size();
}

hmc_napi_create_value::jsObject::jsObject(napi_env env)
{
    if (env == NULL)
    {
        return;
    }

    node_env = env;

    status = napi_create_object(env, &object_value);
    is_ready_ok = status == napi_ok;
}

napi_value hmc_napi_create_value::jsObject::toValue()
{
    if (is_ready_ok)
    {
        for (auto &&napi_value : napi_value_list)
        {

            if (std::holds_alternative<std::wstring>(napi_value.first))
            {
                status = napi_set_property(
                    node_env,
                    object_value,
                    hmc_napi_create_value::String(node_env, std::get<std::wstring>(napi_value.first)),
                    napi_value.second);
            }

            if (std::holds_alternative<std::string>(napi_value.first))
            {
                status = napi_set_property(
                    node_env,
                    object_value,
                    hmc_napi_create_value::String(node_env, std::get<std::string>(napi_value.first)),
                    napi_value.second);
            }

            if (status != napi_ok)
            {
                return NULL;
            }
        }

        return object_value;
    }

    return NULL;
}

void hmc_napi_create_value::jsObject::putValue(StringVar key, napi_value Object)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            Object));
}

void hmc_napi_create_value::jsObject::putBigint(StringVar key, int64_t Object)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            hmc_napi_create_value::Bigint(node_env, Object)));
}

void hmc_napi_create_value::jsObject::putNumber(StringVar key, int64_t Object)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            hmc_napi_create_value::Number(node_env, Object)));
}

void hmc_napi_create_value::jsObject::putNumber(StringVar key, double Object)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            hmc_napi_create_value::Number(node_env, Object)));
}

void hmc_napi_create_value::jsObject::putNull(StringVar key)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            hmc_napi_create_value::Null(node_env)));
}

void hmc_napi_create_value::jsObject::putUndefined(StringVar key)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            hmc_napi_create_value::Undefined(node_env)));
}

void hmc_napi_create_value::jsObject::putBuffer(StringVar key, std::vector<unsigned char> input)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            hmc_napi_create_value::Buffer(node_env, input)));
}

void hmc_napi_create_value::jsObject::putBoolean(StringVar key, bool Boolean)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            hmc_napi_create_value::Boolean(node_env, Boolean)));
}

void hmc_napi_create_value::jsObject::putString(StringVar key, std::wstring Object, size_t re_size)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            hmc_napi_create_value::String(node_env, Object, re_size)));
}

void hmc_napi_create_value::jsObject::putString(StringVar key, std::string Object, size_t re_size)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            hmc_napi_create_value::String(node_env, Object, re_size)));
}

void hmc_napi_create_value::jsObject::putStringA(StringVar key, std::string Object, size_t re_size)
{
    napi_value_list.insert(
        std::pair<StringVar, napi_value>(
            key,
            hmc_napi_create_value::StringA(node_env, Object, re_size)));
}

void PromiseFunctionUtil::exports(napi_env env, napi_value exports, std::string name, napi_callback cb)
{
    napi_value exported_function;

    napi_create_function(env,
                         name.c_str(),
                         name.length(),
                         cb,
                         NULL,
                         &exported_function);

    napi_set_named_property(env, exports, name.c_str(), exported_function);

    // 注册变量传递
    napi_wrap(env, exports, NULL, NULL, NULL, NULL);
}

void PromiseFunctionUtil::completeWork(napi_env env, napi_status status, std::atomic<napi_async_work> *work, std::atomic<napi_deferred> *deferred, std::vector<std::any> *arguments_list, std::any *resultSend, FuncFormatResultValue FormatResultValue)
{
    if (status != napi_ok)
        return;

    try
    {
        napi_resolve_deferred(env, deferred->load(), FormatResultValue(env, resultSend));
    }
    catch (...)
    {
        napi_value error = NULL;
        napi_create_string_utf8(env, "error -> FormatResultValue(env, *resultSend) an error has occurred", NAPI_AUTO_LENGTH, &error);

        napi_reject_deferred(env, deferred->load(), error);
    }

    // 清理与此运行关联的工作环境
    napi_delete_async_work(env, work->load());

    work->store(NULL);
    deferred->store(NULL);
    resultSend->reset();
    (*resultSend) = std::any();
    arguments_list->clear();
    arguments_list->resize(0);
}

void PromiseFunctionUtil::exports(napi_env env, napi_value exports, std::string name, napi_callback cbAsync, napi_callback cbSync)
{
    PromiseFunctionUtil::exports(env, exports, name, cbAsync);
    PromiseFunctionUtil::exports(env, exports, name + "Sync", cbSync);
}

napi_value PromiseFunctionUtil::startWork(napi_env env, napi_callback_info info, std::atomic<napi_async_work> *work, std::atomic<napi_deferred> *deferred, napi_async_execute_callback execute, napi_async_complete_callback complete, std::vector<std::any> *arguments_list, std::optional<formatArgsCallBackType> formatArgsCallBack)
{
    napi_value result, work_name, promise;

    if (napi_get_null(env, &result) != napi_ok)
    {
        result = NULL;
    }

    std::string work_message = std::string(__FUNCTION__).append("  work_message ->  ");

    // 上个函数还没结束
    if (work->load() != NULL)
    {
        // work_message.append("error < Promise workspace has not been released. > ");
        // napi_throw_error(env, "TASK_CONFLICT", work_message.c_str());
        return result;
    }

    // 创建一个字符串来描述这个异步操作。

    work_message.append("Node-API Deferred Promise from Async Work Item");

    napi_create_string_utf8(env, work_message.c_str(), work_message.length(), &work_name);

    napi_async_work addon_napi_async_work = NULL;
    napi_deferred addon_deferred = NULL;

    // 创建一个延迟的promise对象，在完成时我们将解决它
    if (napi_create_promise(env, &addon_deferred, &promise) != napi_ok)
    {
        work_message.append("error < Promise Creation failed. > ");
        napi_throw_error(env, "Creation_failed", work_message.c_str());
        return result;
    };
    if (formatArgsCallBack.has_value())
    {

        auto input = hmc_NodeArgsValue(env, info);
        formatArgsCallBack.value()(env, info, arguments_list, input);
    }
    else
    {

        auto input = hmc_NodeArgsValue(env, info).get_values();

        for (size_t i = 0; i < input.size(); i++)
        {
            arguments_list->push_back(input.at(i));
        }
    }

    // 创建一个异步工作项，传递插件数据，这将使
    // 工作线程访问上述创建的延迟的 promise对象
    if (napi_create_async_work(env,
                               NULL,
                               work_name,
                               execute,
                               complete, NULL, &addon_napi_async_work) != napi_ok)
    {
        work_message.append("error < Promise Creation work async failed. > ");
        napi_throw_error(env, "Creation_failed", work_message.c_str());
        return result;
    };

    // 添加进node的异步队列
    napi_queue_async_work(env, addon_napi_async_work);

    work->store(addon_napi_async_work);
    deferred->store(addon_deferred);
    return promise;
}

napi_value PromiseFunctionUtil::startSync(napi_env env, napi_callback_info info, std::function<std::any(std::vector<std::any> *arguments_list)> PromiseWorkFunc, std::function<napi_value(napi_env env, std::any *result_any_data)> FormatResultValue, std::optional<formatArgsCallBackType> formatArgsCallBack)
{
    napi_value result, work_name, promise;
    napi_get_null(env, &result);

    std::any resultSend = std::any();
    std::vector<std::any> arguments_list = {};

    try
    {
        if (formatArgsCallBack.has_value())
        {

            auto input = hmc_NodeArgsValue(env, info);
            formatArgsCallBack.value()(env, info, &arguments_list, input);
        }
        else
        {

            auto input = hmc_NodeArgsValue(env, info).get_values();

            for (size_t i = 0; i < input.size(); i++)
            {
                arguments_list.push_back(input.at(i));
            }
        }

        std::any data = PromiseWorkFunc(&arguments_list);
        return FormatResultValue(env, &data);
    }
    catch (const std::exception &err)
    {
        napi_throw_error(env, "catch (const std::exception&)", err.what());
        return result;
    }
    catch (...)
    {
        napi_throw_error(env, "catch (...)", "");
        return result;
    }

    return result;
}

// 初始化模块
void InitAsyncFunction(napi_env env, napi_value exports, const char *utf8name, napi_callback StartAsyncTask, napi_callback ExecuteSync)
{
    napi_value asyncTaskFunction;
    napi_create_function(env, nullptr, 0, StartAsyncTask, nullptr, &asyncTaskFunction);

    napi_value syncTaskFunction;
    napi_create_function(env, nullptr, 0, ExecuteSync, nullptr, &syncTaskFunction);

    napi_set_named_property(env, exports, utf8name, asyncTaskFunction);
    std::string utf8nameTemp;
    utf8nameTemp.append(utf8name);
    utf8nameTemp.append("Sync");
    napi_set_named_property(env, exports, utf8nameTemp.c_str(), syncTaskFunction);
}

std::map<size_t, HMC_PromiseStore::chFormatArgFun> HMC_PromiseStore::PromiseFormatEventListenerFunList = {};
std::map<size_t, HMC_PromiseStore::chExecuteWorkFun> HMC_PromiseStore::PromiseWorkEventListenerFunList = {};
std::map<size_t, HMC_PromiseStore::chExecuteResultFormatFun> HMC_PromiseStore::PromiseResultFormatEventListenerFunList = {};

void HMC_PromiseEval::ExecuteAsyncWork(napi_env env, void *data)
{
    HMC_PromiseStore::EnvNextWorkData *workData = (HMC_PromiseStore::EnvNextWorkData *)data;

    if (workData->ResultStore == NULL)
    {
        return;
    }
    if (HMC_PromiseStore::PromiseWorkEventListenerFunList.find(workData->TASK_TYPE) == HMC_PromiseStore::PromiseWorkEventListenerFunList.end())
    {
        return;
    }

    std::any result = HMC_PromiseStore::PromiseWorkEventListenerFunList.at(workData->TASK_TYPE)(env, workData->TASK_TYPE, workData->ArgsStore);
    workData->ResultStore->reset();
    workData->ResultStore->swap(result);
}

void HMC_PromiseEval::GCEnvNextWorkData(void *data)
{

    HMC_PromiseStore::EnvNextWorkData *workData = (HMC_PromiseStore::EnvNextWorkData *)data;
    if (workData->ArgsStore != NULL)
    {
        workData->ArgsStore->clear();
        delete workData->ArgsStore;
        workData->ArgsStore = NULL;
    }

    if (workData->ResultStore != NULL)
    {
        workData->ResultStore->reset();
        delete workData->ResultStore;
        workData->ResultStore = NULL;
    }

    HMC_VcFree(workData);
}

napi_value HMC_PromiseEval::StartAsyncTask(napi_env env, napi_callback_info info)
{
    napi_value promise;
    napi_value resourceName;
    napi_create_string_utf8(env, __FUNCSIG__, NAPI_AUTO_LENGTH, &resourceName);

    // 初始化异步工作的数据
    HMC_PromiseStore::EnvNextWorkData *workData = HMC_VcAllocAutoLength(HMC_PromiseStore::EnvNextWorkData);

    if (workData != NULL) {
        workData->ResultStore = new std::any();
     }

    auto input = hmc_NodeArgsValue(env, info);

    if (!input.eq({{0, js_number}}, true))
    {
        return NULL;
    }

    workData->TASK_TYPE = input.getInt64(0, 0);

    input.removeIndex(0);

    if (HMC_PromiseStore::PromiseFormatEventListenerFunList.find(workData->TASK_TYPE) != HMC_PromiseStore::PromiseFormatEventListenerFunList.end())
    {
        
        workData->ArgsStore = new std::vector<std::any>();
        bool is_next = HMC_PromiseStore::PromiseFormatEventListenerFunList.at(workData->TASK_TYPE)(env, info, input, workData->ArgsStore);

        if (!is_next)
        {
            napi_throw_type_error(env, NULL, hmc_string_util::string_to_lpstr("The passed argument was rejected by the formatting function"));
            return NULL;
        }
    }

    if (HMC_PromiseStore::PromiseWorkEventListenerFunList.find(workData->TASK_TYPE) == HMC_PromiseStore::PromiseWorkEventListenerFunList.end()) {
        napi_throw_type_error(env, NULL, hmc_string_util::string_to_lpstr("This task ID was not found. It may not be supported or the environment is missing"));
        return NULL;
    }

    napi_create_promise(env, &workData->deferred, &promise);
    napi_create_async_work(env, nullptr, resourceName, ExecuteAsyncWork, ResolveWork, workData, &workData->work);
    napi_queue_async_work(env, workData->work);
    return promise;
}

void HMC_PromiseEval::ResolveWork(napi_env env, napi_status status, void *data)
{
    HMC_PromiseStore::EnvNextWorkData *workData = (HMC_PromiseStore::EnvNextWorkData *)data;
    std::shared_ptr<void> O_o(nullptr, [&](void *)
                              {
            napi_delete_async_work(env, workData->work);
            GCEnvNextWorkData(workData); });

    if (status != napi_ok)
    {
        return;
    }

    napi_value result;
    napi_get_null(env, &result);

    if (workData == NULL || !workData->ResultStore->has_value())
    {
        napi_resolve_deferred(env, workData->deferred, result);
        return;
    }

    if (HMC_PromiseStore::PromiseResultFormatEventListenerFunList.find(workData->TASK_TYPE) != HMC_PromiseStore::PromiseResultFormatEventListenerFunList.end())
    {

        result = HMC_PromiseStore::PromiseResultFormatEventListenerFunList.at(workData->TASK_TYPE)(env, status, workData->ResultStore, workData->ArgsStore);
    }

    else if (workData->ResultStore->type() == typeid(napi_value))
    {
        result = (std::any_cast<napi_value>(*workData->ResultStore));
    }
    else
    {
        result = hmc_napi_create_value::New(env, *workData->ResultStore);
    }

    napi_resolve_deferred(env, workData->deferred, result);
}

napi_value HMC_PromiseEval::ExecuteSync(napi_env env, napi_callback_info info)
{
    napi_value result = as_Null();

    auto input = hmc_NodeArgsValue(env, info);

    if (!input.eq({{0, js_number}}, true))
    {
        return NULL;
    }

    size_t TASK_TYPE = input.getInt64(0, 0);
    input.removeIndex(0);
    
    auto ArgsStore = std::vector<std::any>();
    std::any ResultStore = std::any();

    if (HMC_PromiseStore::PromiseFormatEventListenerFunList.find(TASK_TYPE) != HMC_PromiseStore::PromiseFormatEventListenerFunList.end())
    {
        bool is_next = HMC_PromiseStore::PromiseFormatEventListenerFunList.at(TASK_TYPE)(env, info, input, &ArgsStore);
        if (!is_next)
        {
            napi_throw_type_error(env, NULL, hmc_string_util::string_to_lpstr("The passed argument was rejected by the formatting function"));
            return NULL;
        }
    }

    if (HMC_PromiseStore::PromiseWorkEventListenerFunList.find(TASK_TYPE) == HMC_PromiseStore::PromiseWorkEventListenerFunList.end()) {
        napi_throw_type_error(env, NULL, hmc_string_util::string_to_lpstr("This task ID was not found. It may not be supported or the environment is missing"));
        return NULL;
    }

    if (HMC_PromiseStore::PromiseWorkEventListenerFunList.find(TASK_TYPE) != HMC_PromiseStore::PromiseWorkEventListenerFunList.end())
    {
        ResultStore = HMC_PromiseStore::PromiseWorkEventListenerFunList.at(TASK_TYPE)(env, TASK_TYPE, &ArgsStore);
    }

    if (!ResultStore.has_value())
    {
        return result;
    }

    if (HMC_PromiseStore::PromiseResultFormatEventListenerFunList.find(TASK_TYPE) != HMC_PromiseStore::PromiseResultFormatEventListenerFunList.end())
    {

        result = HMC_PromiseStore::PromiseResultFormatEventListenerFunList.at(TASK_TYPE)(env, napi_ok, &ResultStore, &ArgsStore);
    }
    else
    {

        result = hmc_napi_create_value::New(env, ResultStore);
    }

    return result;
}

void HMC_PromiseEval::append(size_t ID, std::optional<HMC_PromiseStore::chFormatArgFun> FormatFun, HMC_PromiseStore::chExecuteWorkFun WorkFun, std::optional<HMC_PromiseStore::chExecuteResultFormatFun> ResultFormatFun)
{

    if (FormatFun.has_value() && HMC_PromiseStore::PromiseFormatEventListenerFunList.find(ID) != HMC_PromiseStore::PromiseFormatEventListenerFunList.end())
    {
        std::string errorName = " [ HMC_PromiseEval :: chFormatArgFun ] The current task environment ID already exists ID: < ";
        errorName.append(std::to_string(ID));
        errorName.append(" >");
        throw errorName;
        return;
    }

    if (HMC_PromiseStore::PromiseWorkEventListenerFunList.find(ID) != HMC_PromiseStore::PromiseWorkEventListenerFunList.end())
    {
        std::string errorName = " [ HMC_PromiseEval :: chExecuteWorkFun ] The current task environment ID already exists ID: < ";
        errorName.append(std::to_string(ID));
        errorName.append(" >");
        throw errorName;
        return;
    }

    if (ResultFormatFun.has_value() && HMC_PromiseStore::PromiseResultFormatEventListenerFunList.find(ID) != HMC_PromiseStore::PromiseResultFormatEventListenerFunList.end())
    {
        std::string errorName = " [ HMC_PromiseEval :: chExecuteResultFormatFun ] The current task environment ID already exists ID: < ";
        errorName.append(std::to_string(ID));
        errorName.append(" >");
        throw errorName;
        return;
    }

    if (FormatFun.has_value())
    {
        HMC_PromiseStore::PromiseFormatEventListenerFunList.insert(
            std::pair<size_t, HMC_PromiseStore::chFormatArgFun>(ID, FormatFun.value()));
    }

 
        HMC_PromiseStore::PromiseWorkEventListenerFunList.insert(
            std::pair<size_t, HMC_PromiseStore::chExecuteWorkFun>(ID, WorkFun));

    if (ResultFormatFun.has_value())
    {
        HMC_PromiseStore::PromiseResultFormatEventListenerFunList.insert(
            std::pair<size_t, HMC_PromiseStore::chExecuteResultFormatFun>(ID, ResultFormatFun.value()));
    }
}

