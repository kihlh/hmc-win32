#include "./util.h";

// 字符串转换工具(来自MIT协议)
// https://github.com/qoddi/hikopenapi-node/blob/c4ee4d7e61e6df36d9cc77e81315a5668d19a51f/src/windows/hikopenapi.cpp
// 宽字符字符串转多字节字符串
inline string _W2A_(const wchar_t *pwszText)
{
    if (pwszText == NULL || wcslen(pwszText) == 0)
    {
        return string();
    }
    int iSizeInBytes = WideCharToMultiByte(CP_ACP, 0, pwszText, -1, NULL, 0, NULL, NULL);
    char *pMultiByte = new (nothrow) char[iSizeInBytes];
    if (pMultiByte == NULL)
    {
        return string();
    }

    memset(pMultiByte, 0, iSizeInBytes);
    WideCharToMultiByte(CP_ACP, 0, pwszText, -1, pMultiByte, iSizeInBytes, NULL, NULL);

    string strResult = string(pMultiByte);
    delete[] pMultiByte;
    pMultiByte = NULL;
    return strResult;
}
// UTF-8字符串转宽字符字符串
inline wstring _U82W_(const char *pszText)
{
    if (pszText == NULL || strlen(pszText) == 0)
    {
        return wstring();
    }
    int iSizeInChars = MultiByteToWideChar(CP_UTF8, 0, pszText, -1, NULL, 0);
    wchar_t *pWideChar = new (nothrow) wchar_t[iSizeInChars];
    if (pWideChar == NULL)
    {
        return wstring();
    }

    wmemset(pWideChar, 0, iSizeInChars);
    MultiByteToWideChar(CP_UTF8, 0, pszText, -1, pWideChar, iSizeInChars);

    wstring strResult = wstring(pWideChar);
    delete[] pWideChar;
    pWideChar = NULL;
    return strResult;
}
// UTF-8字符串转多字节字符串
inline string _U82A_(const char *pszText)
{
    return _W2A_(_U82W_(pszText).c_str());
}
// 多字节字符串转宽字符字符串
inline wstring _A2W_(const char *pszText)
{
    if (pszText == NULL || strlen(pszText) == 0)
    {
        return wstring();
    }
    int iSizeInChars = MultiByteToWideChar(CP_ACP, 0, pszText, -1, NULL, 0);
    wchar_t *pWideChar = new (nothrow) wchar_t[iSizeInChars];
    if (pWideChar == NULL)
    {
        return wstring();
    }

    wmemset(pWideChar, 0, iSizeInChars);
    MultiByteToWideChar(CP_ACP, 0, pszText, -1, pWideChar, iSizeInChars);

    wstring strResult = wstring(pWideChar);
    delete[] pWideChar;
    pWideChar = NULL;
    return strResult;
}
// 宽字符字符串转UTF-8字符串
inline string _W2U8_(const wchar_t *pwszText)
{
    if (pwszText == NULL || wcslen(pwszText) == 0)
    {
        return string();
    }
    int iSizeInBytes = WideCharToMultiByte(CP_UTF8, 0, pwszText, -1, NULL, 0, NULL, NULL);
    char *pUTF8 = new (nothrow) char[iSizeInBytes];
    if (pUTF8 == NULL)
    {
        return string();
    }

    memset(pUTF8, 0, iSizeInBytes);
    WideCharToMultiByte(CP_UTF8, 0, pwszText, -1, pUTF8, iSizeInBytes, NULL, NULL);

    string strResult = string(pUTF8);
    delete[] pUTF8;
    pUTF8 = NULL;
    return strResult;
}
// 多字节字符串转UTF-8字符串
inline string _A2U8_(const char *pszText)
{
    return _W2U8_(_A2W_(pszText).c_str());
}

// inline wstring _CW2W_(const WCHAR *pszText)
// {
//     int wstr_size = wcslen(pszText) + 1;
//     int size_needed = WideCharToMultiByte(CP_UTF8, 0, pszText, wstr_size, NULL, 0, NULL, NULL);
//     char *str = new char[size_needed];
//     WideCharToMultiByte(CP_UTF8, 0, pszText, wstr_size, str, size_needed, NULL, NULL);
//     wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
//     wstring wide_str = converter.from_bytes(str);
//     const wchar_t *result = wide_str.c_str();
// }
// UTF-8 To GBK
string UTF8ToGBK(const char *str)
{
    string Result;
    TCHAR *Temp_T_String;
    WCHAR *Teme_W_String;
    int of_Temp_Size = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    Teme_W_String = new WCHAR[of_Temp_Size + 1];
    MultiByteToWideChar(CP_UTF8, 0, str, -1, Teme_W_String, of_Temp_Size);
    of_Temp_Size = WideCharToMultiByte(CP_ACP, 0, Teme_W_String, -1, nullptr, 0, nullptr, nullptr);
    Temp_T_String = new TCHAR[of_Temp_Size + 1];
    WideCharToMultiByte(CP_ACP, 0, Teme_W_String, -1, (LPSTR)Temp_T_String, of_Temp_Size, nullptr, nullptr);
    Result = (char *)Temp_T_String;
    delete[] Temp_T_String;
    delete[] Teme_W_String;

    return Result;
}
napi_value _create_buff_Buffer(napi_env env, void **data, size_t size)
{
    napi_value Results;
    napi_create_buffer(env, size, data, &Results);
    return Results;
}
napi_value _create_char_string(napi_env env, char *SetString)
{
    napi_value Results;
    napi_create_string_utf8(env, SetString, NAPI_AUTO_LENGTH, &Results);
    return Results;
}
napi_value _create_String(napi_env env, string SetString)
{
    napi_value Results;
    napi_create_string_utf8(env, SetString.c_str(), NAPI_AUTO_LENGTH, &Results);
    return Results;
}
napi_value _create_A2U8_string(napi_env env, char *SetString)
{
    napi_value Results;
    napi_create_string_utf8(env, _A2U8_(SetString).c_str(), NAPI_AUTO_LENGTH, &Results);
    return Results;
}
napi_value _create_W2U8_string(napi_env env, wchar_t *SetString)
{
    napi_value Results;
    napi_create_string_utf8(env, _W2U8_(SetString).c_str(), NAPI_AUTO_LENGTH, &Results);
    return Results;
}
napi_value _create_int32_Number(napi_env env, int SetNumber)
{
    napi_value Results;
    napi_create_int32(env, SetNumber, &Results);
    return Results;
}
napi_value _create_int64_Number(napi_env env, int64_t SetNumber)
{
    napi_value Results;
    napi_create_int64(env, SetNumber, &Results);
    return Results;
}
napi_value _create_String_Array(napi_env env, vector<string> stringVector)
{
    napi_status status;
    napi_value ResultsList;
    status = napi_create_array(env, &ResultsList);
    assert(status == napi_ok);
    for (unsigned index = 0; index < stringVector.size(); index++)
    {
        napi_value push_item;
        string push_item_data = stringVector[index];
        status = napi_create_string_utf8(env, push_item_data.c_str(), NAPI_AUTO_LENGTH, &push_item);
        assert(status == napi_ok);
        status = napi_set_element(env, ResultsList, index, push_item);
        assert(status == napi_ok);
    }
    return ResultsList;
}
napi_value _create_bool_Boolean(napi_env env, bool SetBoolean)
{
    napi_value Results;
    napi_get_boolean(env, SetBoolean, &Results);
    return Results;
}
napi_value _create_true_Boolean(napi_env env)
{
    napi_value Results;
    napi_get_boolean(env, TRUE, &Results);
    return Results;
}
napi_value _create_false_Boolean(napi_env env)
{
    napi_value Results;
    napi_get_boolean(env, FALSE, &Results);
    return Results;
}

// JavaScript文本参数
string call_String_NAPI_UTF8(napi_env env, napi_value value)
{
    string RunNapiName;
    size_t str_len = 0;
    napi_get_value_string_utf8(env, value, nullptr, 0, &str_len);
    RunNapiName.reserve(str_len + 1);
    RunNapiName.resize(str_len);
    napi_get_value_string_utf8(env, value, &RunNapiName[0], RunNapiName.capacity(), nullptr);
    return RunNapiName;
}
// JavaScript文本参数转为A字符
string call_String_NAPI_WINAPI_A(napi_env env, napi_value value)
{
    string RunNapiName = _U82A_(call_String_NAPI_UTF8(env, value).c_str());
    return RunNapiName;
}
// JavaScript文本参数转为W字符
wstring call_String_NAPI_WINAPI_W(napi_env env, napi_value value)
{
    string RunNapiName;
    size_t str_len = 0;
    napi_get_value_string_utf8(env, value, nullptr, 0, &str_len);
    RunNapiName.reserve(str_len + 1);
    RunNapiName.resize(str_len);
    napi_get_value_string_utf8(env, value, &RunNapiName[0], RunNapiName.capacity(), nullptr);
    return _U82W_(call_String_NAPI_UTF8(env, value).c_str());
}
string _NAPI_Call_Type(napi_valuetype valuetype0)
{
    string Call_Type;
    switch (valuetype0)
    {
    case napi_null:
        Call_Type.append("null");
        break;
    case napi_number:
        Call_Type.append("number");
        break;
    case napi_string:
        Call_Type.append("string");
        break;
    case napi_undefined:
        Call_Type.append("undefined");
        break;
    case napi_object:
        Call_Type.append("object");
        break;
    case napi_function:
        Call_Type.append("function");
        break;
    case napi_boolean:
        Call_Type.append("boolean");
        break;
    default:
        Call_Type.append("unknown");
    }
    return Call_Type;
}

bool util_diff_napi_type(napi_env env, napi_value value, napi_valuetype valuetype)
{
    napi_valuetype value_type;
    napi_typeof(env, value, &value_type);
    if (value_type == valuetype)
        return true;
    return false;
}

napi_valuetype util_get_napi_type(napi_env env, napi_value value)
{
    napi_valuetype value_type;
    napi_typeof(env, value, &value_type);
    return value_type;
}

string util_get_napi_type_name(napi_env env, napi_value value)
{
    napi_valuetype value_type;
    napi_typeof(env, value, &value_type);
    return _NAPI_Call_Type(value_type);
}

struct hmcRect
{
    int x;
    int y;
    int height;
    int width;
};

//  https://blog.csdn.net/qq_32285693/article/details/126322110
//  授权 CC 4.0 BY-SA
/**
 * @brief 矩形相交判断
 *
 * @param inRect
 * @param mian
 * @return true
 * @return false
 */
bool rectInRect(hmcRect mian, hmcRect inRect)
{
    bool isInRet = true;
    // 得出对比传入的边界
    int in_x = inRect.x;
    int in_y = inRect.y;
    int in_xw = inRect.x + inRect.width;
    int in_hy = inRect.y + inRect.height;
    if (!inRect.x)
        in_x = 1;
    if (!inRect.y)
        in_y = 1;
    // 得出mian的边界
    int mian_x = mian.x;
    int mian_y = mian.y;
    int mian_xw = mian.x + mian.width;
    int mian_hy = mian.y + mian.height;

    isInRet = (((in_x >= mian_x && in_x < mian_xw) || (mian_x >= in_x && mian_x <= in_xw)) &&
               ((in_y >= mian_y && in_y < mian_hy) || (mian_y >= in_y && mian_y <= in_hy)))
                  ? false
                  : true;

    // 是否完全在另一个矩形内

    if (isInRet == false)
    {
        if (mian.x > inRect.x && mian.y > inRect.y &&
            mian.x + mian.width < inRect.x + inRect.width &&
            mian.y + mian.height < inRect.x + inRect.height)
        {
            return true;
        }

        return false;
    }
    return false;
}

//  https://blog.csdn.net/qq_32285693/article/details/126322110
//  授权 CC 4.0 BY-SA
/**
 * @brief 点在矩形中
 *
 * @param pt
 * @param rect
 * @return true
 * @return false
 */
bool pointInRect(POINT pt, hmcRect rect)
{
    if ((pt.x > rect.x) && (pt.y > rect.y) && (pt.x < (rect.x + rect.width)) && (pt.y < (rect.y + rect.height)))
    {
        return true;
    }
    return false;
}

hmcRect RECT2Rect(RECT inputRect)
{
    hmcRect out;
    out.height = inputRect.top - inputRect.bottom;
    out.width = inputRect.right - inputRect.left;
    out.x = inputRect.left;
    out.y = inputRect.top;
    return out;
}

/**
 * @brief 矩形相交判断
 *
 * @param inRect
 * @param mian
 * @return true
 * @return false
 */
bool RECTinRECT(RECT inRect, RECT mian)
{
    return rectInRect(RECT2Rect(inRect), RECT2Rect(mian));
}

/**
 * @brief 点在矩形中
 *
 * @param pt
 * @param rect
 * @return true
 * @return false
 */
bool pointInRECT(POINT pt, RECT inputRect)
{
    hmcRect rect = RECT2Rect(inputRect);
    if ((pt.x > rect.x) && (pt.y > rect.y) && (pt.x < (rect.x + rect.width)) && (pt.y < (rect.y + rect.height)))
    {
        return true;
    }
    return false;
}

bool isInside(int x1, int y1, int x2, int y2, int x, int y)
{
    if (x > x1 && x < x2 && y > y1 && y < y2)
        return true;
    return false;
}



