
#include "./hmc_string_util.hpp"
#include <iostream>

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
string hmc_string_util::string_join(const string &input, const string &firstInput, vector<Arguments...> data_list)
{
    string result = "";
    result.append(input);
    result.append(firstInput);
    for (auto data : data_list)
    {
        result.append(data);
    }

    return result;
}

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
wstring hmc_string_util::string_join(const wstring &input, const wstring &firstInput, vector<Arguments...> data_list)
{
    wstring result = "";
    result.append(input);
    result.append(firstInput);
    for (auto data : data_list)
    {
        result.append(data);
    }

    return result;
}

// 文本中是否有数字 并且是否是安全的 int32
bool hmc_string_util::is_int_str(const string Value)
{
    bool Result = false;
    if (Value.empty())
        return Result;
    try
    {
        int n = stoi(Value);
        Result = true;
    }
    catch (const exception &e)
    {
        return Result;
    }

    return Result;
}

// 文本中是否有数字 并且是否是安全的 long
bool hmc_string_util::is_long_str(const string Value)
{
    bool Result = false;
    if (Value.empty())
        return Result;
    try
    {
        long n = stol(Value);
        Result = true;
    }
    catch (const exception &e)
    {
        return Result;
    }

    return Result;
}

// 文本中是否有数字 并且是否是安全的 long long
bool hmc_string_util::is_longlong_str(const string Value)
{
    bool Result = false;
    if (Value.empty())
        return Result;
    try
    {
        long long n = stoll(Value);
        Result = true;
    }
    catch (const exception &e)
    {
        return Result;
    }

    return Result;
}

inline wstring hmc_string_util::utf8_to_utf16(const string input)
{
    const char *pszText = input.c_str();

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

inline string hmc_string_util::utf16_to_utf8(const wstring input)
{
    const wchar_t *pwszText = input.c_str();

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

inline string hmc_string_util::utf16_to_ansi(const wstring input)
{
    const wchar_t *pwszText = input.c_str();

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

inline wstring hmc_string_util::ansi_to_utf16(const string input)
{
    const char *pszText = input.c_str();

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

// UFT8 字符转为GBK(中文)
string hmc_string_util::utf8_to_gbk(const string u8str)
{
    string Result;
    TCHAR *pTempTstr;
    WCHAR *pTempwstr;

    int strSizeTempVar = MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, NULL, 0);
    pTempwstr = new WCHAR[strSizeTempVar + 1];

    MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, pTempwstr, strSizeTempVar);
    strSizeTempVar = WideCharToMultiByte(CP_ACP, 0, pTempwstr, -1, NULL, 0, NULL, NULL);

    pTempTstr = new TCHAR[strSizeTempVar + 1];

    WideCharToMultiByte(CP_ACP, 0, pTempwstr, -1, (LPSTR)pTempTstr, strSizeTempVar, NULL, NULL);
    Result = (char *)pTempTstr;
    delete[] pTempTstr;
    delete[] pTempwstr;

    return Result;
}

// ----------------------------------------------------------------
// A2U8
// Local CP_ACP ( Ansi [A] ) to utf8 encoding
// winapi A字符 转 utf8(win 标准[W])
// ? 推荐w字符(utf16) 损耗更少一点 napi支持直接返回utf16
// ----------------------------------------------------------------
string hmc_string_util::ansi_to_utf8(const string ansi)
{
    wstring to_utf16 = ansi_to_utf16(ansi);
    return utf16_to_utf8(to_utf16);
    return string("");
}

// ----------------------------------------------------------------
// U82A
// utf8 to Local CP_ACP ( Ansi [A] ) encoding
// utf8 字符 转 winapi A字符
// ? 推荐w字符(utf16) 损耗更少一点 napi支持直接返回utf16
// ----------------------------------------------------------------
string hmc_string_util::utf8_to_ansi(const string utf8)
{
    wstring to_utf16 = utf8_to_utf16(utf8);
    return utf16_to_ansi(to_utf16);
}

inline bool hmc_string_util::is_utf8(const string input)
{
    for (string::const_iterator str = input.begin(), eos = input.end(); str != eos; ++str)
    {
        unsigned char cuChar = static_cast<unsigned char>(*str);
        size_t len = sizeof(cuChar);
        if (cuChar == '\b' || cuChar == '\n' || cuChar == '\r' || cuChar == '\f' || cuChar == '\t')
        {
            // 转义符
        }
        // 超出utf8的大小了
        else if (static_cast<unsigned char>(cuChar) >= 0xF8)
            return false;

        else if (static_cast<unsigned char>(cuChar) >= 0xF0)
        {
            if (len < 4)
                return false;
            for (int i = 1; i <= 3; i++)
            {
                if ((*(unsigned char *)(cuChar + i) & 0xC0) != 0x80)
                    return false;
            }
            return true;
        }
        else if (static_cast<unsigned char>(cuChar) >= 0xE0)
        {
            if (len < 3)
                return false;
            for (int i = 1; i <= 2; i++)
            {
                if ((*(unsigned char *)(cuChar + i) & 0xC0) != 0x80)
                    return false;
            }
            return true;
        }
        else if (static_cast<unsigned char>(cuChar) >= 0xC0)
        {

            if (len < 2)
                return false;
            if ((*(unsigned char *)(cuChar + 1) & 0xC0) != 0x80)
                return false;
            return true;
        }
        else if (static_cast<unsigned char>(cuChar) >= 0x80)
            return false;
        else
            return true;
    }
    return true;
}

/**
 * @brief 全部替换
 *
 * @param sourcePtr
 * @param from
 * @param to
 */
inline void hmc_string_util::replaceAll(string &sourcePtr, string from, string to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

inline void hmc_string_util::replaceAll(wstring &sourcePtr, const wstring from, const wstring to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

/**
 * @brief 替换一次
 *
 * @param sourcePtr
 * @param from
 * @param to
 */
inline void hmc_string_util::replace(string &sourcePtr, string from, string to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        start_pos += to.length();
        return;
    }
}

inline void hmc_string_util::replace(wstring &sourcePtr, const wstring from, const wstring to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        return;
    }
}

/**
 * @brief 替换指定内容 仅在第N次出现的时候执行替换
 *
 * @param sourcePtr
 * @param from
 * @param bubble_index
 * @param to
 */
inline void hmc_string_util::replace(string &sourcePtr, string from, size_t bubble_index, string to)
{
    size_t start_pos = 0;
    size_t index = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != string::npos)
    {
        if (index == bubble_index)
        {
            sourcePtr.replace(start_pos, from.length(), to);
            return;
        }
        index++;
    }
}

inline string hmc_string_util::escapeJsonString(const string &input)
{
    string output;
    for (char ch : input)
    {
        switch (ch)
        {

        case '\0':
            break;
        case '\"':
            output.append("\\\"");
            break;
        case '\\':
            output.append("\\\\");
            break;
        case '\b':
            output.append("\\b");
            break;
        case '\f':
            output.append("\\f");
            break;
        case '\n':
            output.append("\\n");
            break;
        case '\r':
            output.append("\\r");
            break;
        case '\t':
            output.append("\\t");
            break;
        default:
            output.push_back(ch);
            break;
        }
    }
    return output;
}

inline wstring hmc_string_util::escapeJsonString(const wstring &input)
{
    wstring output;
    for (wchar_t ch : input)
    {
        switch (ch)
        {
        case L'\0':
            break;
        case L'\"':
            output.append(L"\\\"");
            break;
        case L'\\':
            output.append(L"\\\\");
            break;
        case L'\b':
            output.append(L"\\b");
            break;
        case L'\f':
            output.append(L"\\f");
            break;
        case L'\n':
            output.append(L"\\n");
            break;
        case L'\r':
            output.append(L"\\r");
            break;
        case L'\t':
            output.append(L"\\t");
            break;
        default:
            output.push_back(ch);
            break;
        }
    }
    return output;
}

/**
 * @brief 切割文本
 *
 * @param sourcePtr
 * @param splitter
 * @param item_list
 */
void hmc_string_util::split(string &sourcePtr, char splitter, vector<string> &item_list)
{

    item_list.clear();
    if (sourcePtr.empty())
    {
        return;
    }
    string item;
    item.reserve(sourcePtr.length());

    for (auto data : sourcePtr)
    {
        if (data == splitter)
        {
            if (!item.empty())
            {

                item_list.push_back(item);
            }
            item.clear();
        }
        else
        {
            item.push_back(data);
        }
    }

    // 最后一个元素如果是空文本则不导入
    if (!item.empty())
        item_list.push_back(move(item));
}

vector<string> hmc_string_util::split(string &sourcePtr, char splitter)
{
    if (sourcePtr.empty())
    {
        return vector<string>();
    }
    vector<string> item_list;
    split(sourcePtr, splitter, item_list);
    return item_list;
}

/**
 * @brief 切割文本
 *
 * @param sourcePtr
 * @param splitter
 * @param item_list
 */
void hmc_string_util::split(wstring &sourcePtr, wchar_t splitter, vector<wstring> &item_list)
{

    item_list.clear();
    if (sourcePtr.empty())
    {
        return;
    }

    wstring item;
    item.reserve(sourcePtr.length());

    for (auto data : sourcePtr)
    {
        if (data == splitter)
        {
            if (!item.empty())
            {

                item_list.push_back(item);
            }
            item.clear();
        }
        else
        {
            item.push_back(data);
        }
    }

    // 最后一个元素如果是空文本则不导入
    if (!item.empty())
        item_list.push_back(move(item));
}

vector<wstring> hmc_string_util::split(wstring &sourcePtr, wchar_t splitter)
{
    if (sourcePtr.empty())
    {
        return vector<wstring>();
    }
    vector<wstring> item_list;
    split(sourcePtr, splitter, item_list);
    return item_list;
}

void hmc_string_util::join(vector<string> &item_list, string splitter, string outputPtr)
{
    for (size_t i = 0; i < item_list.size(); i++)
    {
        auto item = item_list[i];
        outputPtr.append(item);
        if (item_list.size() - 1 != i)
        {
            outputPtr.append(splitter);
        }
    }
}

string hmc_string_util::join(vector<string> &item_list, string splitter)
{
    string result = string();
    for (size_t i = 0; i < item_list.size(); i++)
    {
        auto item = item_list[i];
        result.append(item);
        if (item_list.size() - 1 != i)
        {
            result.append(splitter);
        }
    }

    return result;
}
string hmc_string_util::join(vector<string> &item_list)
{
    return join(item_list, string(""));
}

void hmc_string_util::join(vector<wstring> &item_list, wstring splitter, wstring outputPtr)
{
    for (size_t i = 0; i < item_list.size(); i++)
    {
        auto item = item_list[i];
        outputPtr.append(item);
        if (item_list.size() - 1 != i)
        {
            outputPtr.append(splitter);
        }
    }
}
wstring hmc_string_util::join(vector<wstring> &item_list, wstring splitter)
{
    wstring result = wstring();
    for (size_t i = 0; i < item_list.size(); i++)
    {
        auto item = item_list[i];
        result.append(item);
        if (item_list.size() - 1 != i)
        {
            result.append(splitter);
        }
    }

    return result;
}
wstring hmc_string_util::join(vector<wstring> &item_list)
{
    return join(item_list, wstring(L""));
}

string hmc_string_util::trim(const string &input, const string &match)
{

    string temp_trim_str = trimLast(input, match);
    return trimFirst(temp_trim_str, match);
}

string hmc_string_util::trimFirst(const string &input, const string &match)
{
    auto start_pos = input.find_first_not_of(match);
    return (start_pos == string::npos) ? "" : input.substr(start_pos);
}

string hmc_string_util::trimLast(const string &input, const string &match)
{
    auto end_pos = input.find_last_not_of(match);
    return (end_pos == string::npos) ? "" : input.substr(0, end_pos + 1);
}

wstring hmc_string_util::trim(const wstring &input, const wstring &match)
{
    wstring temp_trim_str = trimLast(input, match);
    return trimFirst(temp_trim_str, match);
}

wstring hmc_string_util::trimFirst(const wstring &input, const wstring &match)
{
    auto start_pos = input.find_first_not_of(match);
    return (start_pos == string::npos) ? L"" : input.substr(start_pos);
}

wstring hmc_string_util::trimLast(const wstring &input, const wstring &match)
{
    auto end_pos = input.find_last_not_of(match);
    return (end_pos == string::npos) ? L"" : input.substr(0, end_pos + 1);
}

// 移除尾部 为xx 的指定文本
string hmc_string_util::trimLastAll(const string &input, const string &match)
{
    string result = string(input);
    if (match.empty())
    {
        return result;
    }
    for (size_t i = 0; i < input.size(); i++)
    {
        string new_result = trimLast(result, match);
        if (result.empty() || result.size() == new_result.size())
        {
            return new_result;
        }
        result.clear();
        result.append(new_result);
    }

    return result;
}

// 移除开头和尾部 为xx 的指定文本
string hmc_string_util::trimAll(const string &input, const string &match)
{
    string result = string(input);
    if (match.empty())
    {
        return result;
    }

    for (size_t i = 0; i < input.size(); i++)
    {
        string new_result = trim(result, match);
        if (result.empty() || result.size() == new_result.size())
        {
            return new_result;
        }
        result.clear();
        result.append(new_result);
    }

    return result;
}

// 移除开头为xx 的指定文本
string hmc_string_util::trimFirstAll(const string &input, const string &match)
{
    string result = string(input);
    if (match.empty())
    {
        return result;
    }

    for (size_t i = 0; i < input.size(); i++)
    {
        string new_result = trimFirst(result, match);
        if (result.empty() || result.size() == new_result.size())
        {
            return new_result;
        }
        result.clear();
        result.append(new_result);
    }

    return result;
}

// 移除尾部 为xx 的指定文本
wstring hmc_string_util::trimAll(const wstring &input, const wstring &match)
{
    wstring result = wstring(input);
    if (match.empty())
    {
        return result;
    }

    for (size_t i = 0; i < input.size(); i++)
    {
        wstring new_result = trim(result, match);
        if (result.empty() || result.size() == new_result.size())
        {
            return new_result;
        }
        result.clear();
        result.append(new_result);
    }

    return result;
}

// 移除开头和尾部 为xx 的指定文本
wstring hmc_string_util::trimLastAll(const wstring &input, const wstring &match)
{
    wstring result = wstring(input);
    if (match.empty())
    {
        return result;
    }
    for (size_t i = 0; i < input.size(); i++)
    {
        wstring new_result = trimLast(result, match);
        if (result.empty() || result.size() == new_result.size())
        {
            return new_result;
        }
        result.clear();
        result.append(new_result);
    }

    return result;
}

// 移除开头为xx 的指定文本
wstring hmc_string_util::trimFirstAll(const wstring &input, const wstring &match)
{
    wstring result = wstring(input);
    if (match.empty())
    {
        return result;
    }

    for (size_t i = 0; i < input.size(); i++)
    {
        wstring new_result = trimFirst(result, match);
        if (result.empty() || result.size() == new_result.size())
        {
            return new_result;
        }
        result.clear();
        result.append(new_result);
    }

    return result;
}

void hmc_string_util::unEscapeJsonString(string &sourcePtr)
{
    replaceAll(sourcePtr, "\\a", "\a");
    replaceAll(sourcePtr, "\\b", "\b");
    replaceAll(sourcePtr, "\\f", "\f");
    replaceAll(sourcePtr, "\\n", "\n");
    replaceAll(sourcePtr, "\\r", "\r");
    replaceAll(sourcePtr, "\\t", "\t");
    replaceAll(sourcePtr, "\\v", "\v");
    replaceAll(sourcePtr, "\\\"", "\"");
    replaceAll(sourcePtr, "\\?", "\?");
    replaceAll(sourcePtr, "\\\\", "\\");
}

void hmc_string_util::unEscapeJsonString(wstring &sourcePtr)
{
    replaceAll(sourcePtr, L"\\a", L"\a");
    replaceAll(sourcePtr, L"\\b", L"\b");
    replaceAll(sourcePtr, L"\\f", L"\f");
    replaceAll(sourcePtr, L"\\n", L"\n");
    replaceAll(sourcePtr, L"\\r", L"\r");
    replaceAll(sourcePtr, L"\\t", L"\t");
    replaceAll(sourcePtr, L"\\v", L"\v");
    replaceAll(sourcePtr, L"\\\"", L"\"");
    replaceAll(sourcePtr, L"\\?", L"\?");
    replaceAll(sourcePtr, L"\\\\", L"\\");
}

/**
 * @brief 一个空的json 数组文本
 *
 * @return string
 */
string hmc_string_util::vec_to_array_json()
{
    string result = string("[]");
    return result;
}

/**
 * @brief cpp内容数组转为json的array文本
 *
 * @tparam T
 * @param data_list
 * @return string
 */
wstring hmc_string_util::vec_to_array_json(vector<wstring> item_list)
{
    wstring result = wstring(L"[");

    for (size_t i = 0; i < item_list.size(); i++)
    {
        auto data = item_list[i];
        wstring output;
        for (wchar_t ch : data)
        {
            switch (ch)
            {

            case L'\0':
                break;
            case L'\"':
                output.append(L"\\\"");
                break;
            case L'\\':
                output.append(L"\\\\");
                break;
            case L'\b':
                output.append(L"\\b");
                break;
            case L'\f':
                output.append(L"\\f");
                break;
            case L'\n':
                output.append(L"\\n");
                break;
            case L'\r':
                output.append(L"\\r");
                break;
            case L'\t':
                output.append(L"\\t");
                break;
            default:
                output.push_back(ch);
                break;
            }
        }
        result.append(L"\"" + output + L"\"");

        if (item_list.size() - 1 > i)
        {
            result.append(L",");
        }
    }

    result.append(L"]");
    return result;
}

/**
 * @brief cpp内容数组转为json的array文本
 *
 * @tparam T
 * @param data_list
 * @return string
 */
template <typename T>
string hmc_string_util::vec_to_array_json(const std::vector<T> &data_list)
{
    string result = "[";

    static_assert(
        is_integral<T>::value ||
            is_floating_point<T>::value ||
            is_same_v<char, T> ||
            is_same_v<char *, T> ||
            is_same_v<const char *, T> ||
            is_same_v<T, string>,
        "Unsupported type preset escape (不支持的类型预设转义)");

    for (size_t index = 0; index < data_list.size(); index++)
    {
        auto value = data_list[index];

        if constexpr (is_same_v<T, bool>)
        {
            result.append((value ? "true" : "false"));
        }
        else if constexpr (is_integral<T>::value)
        {
            result.append(to_string(value));
        }
        else if constexpr (is_floating_point<T>::value)
        {
            result.append(to_string(value));
        }
        else if constexpr (is_floating_point<T>::value)
        {
            result.append(to_string(value));
        }
        else if constexpr (is_same_v<char, T> || is_same_v<char *, T> || is_same_v<const char *, T> || is_same_v<T, string>)
        {
            result.append("\"");

            string output;
            for (char ch : static_cast<string>(value))
            {
                switch (ch)
                {
                case '\0':
                    break;
                case '\"':
                    output.append("\\\"");
                    break;
                case '\\':
                    output.append("\\\\");
                    break;
                case '\b':
                    output.append("\\b");
                    break;
                case '\f':
                    output.append("\\f");
                    break;
                case '\n':
                    output.append("\\n");
                    break;
                case '\r':
                    output.append("\\r");
                    break;
                case '\t':
                    output.append("\\t");
                    break;
                default:
                    output.push_back(ch);
                    break;
                }
            }

            result.append(output);
            result.append("\"");
        }
        else
        {
            result.append("null");
        }

        if (data_list.size() - 1 > index)
        {
            result.append(",");
        }
    }

    result.append("]");

    return result;
}

string hmc_string_util::vec_to_array_jsonA(vector<string> item_list){
    return vec_to_array_json(item_list);
}

vector<wstring> hmc_string_util::ansi_to_utf16(vector<string> item_list)
{
    vector<wstring> result ={};
    for (auto item : item_list)
    {
        result.push_back(ansi_to_utf16(item));
    }
    return result;
}

vector<string> hmc_string_util::utf16_to_ansi(vector<wstring> item_list)
{
    vector<string> result = {};
    for (auto item : item_list)
    {
        result.push_back(utf16_to_ansi(item));
    }
    return result;
}

map<wstring, wstring> hmc_string_util::ansi_to_utf16(map<string, string> item_list)
{
    map<wstring, wstring> result = {};
    for (auto item : item_list)
    {
        wstring key = ansi_to_utf16(item.first);
        wstring value = ansi_to_utf16(item.second);

        result.insert(std::make_pair(key, value));
    }
    return result;
}

map<string, string> hmc_string_util::utf16_to_ansi(map<wstring, wstring> item_list)
{
    map<string, string> result = {};
    for (auto item : item_list)
    {
        string key = utf16_to_ansi(item.first);
        string value = utf16_to_ansi(item.second);

        result.insert(std::make_pair(key, value));
    }
    return result;
}

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
template <typename PtrT, typename T>
void hmc_string_util::vec_to_array_json(PtrT &stringPtr, const std::vector<T> &data_list)
{
    static_assert(is_same_v<PtrT, string> || is_same_v<PtrT, wstring>, "Unsupported type preset escape (不支持的类型预设转义)");
    stringPtr.clear();
    stringPtr.append(is_same_v<PtrT, string> ? "[" : L"[");
    static_assert(
        is_integral<T>::value ||
            is_floating_point<T>::value ||
            is_same_v<char, T> ||
            is_same_v<char *, T> ||
            is_same_v<const char *, T> ||
            is_same_v<wchar_t, T> ||
            is_same_v<wchar_t *, T> ||
            is_same_v<const wchar_t *, T> ||
            is_same_v<T, string> ||
            is_same_v<T, wstring>,
        "Unsupported type preset escape (不支持的类型预设转义)");

    for (size_t index = 0; index < data_list.size(); index++)
    {
        auto value = data_list[index];

        if constexpr (is_same_v<T, bool>)
        {
            stringPtr.append((value ? (is_same_v<PtrT, string> ? "true" : L"true") : (is_same_v<PtrT, string> ? "false" : L"false")));
        }
        else if constexpr (is_integral<T>::value)
        {
            stringPtr.append(to_string(value));
        }
        else if constexpr (is_floating_point<T>::value)
        {
            stringPtr.append(to_string(value));
        }
        else if constexpr (is_floating_point<T>::value)
        {
            stringPtr.append(to_string(value));
        }
        else if constexpr (is_same_v<PtrT, string> && (is_same_v<char, T> || is_same_v<char *, T> || is_same_v<const char *, T> || is_same_v<T, string>))
        {
            stringPtr.append("\"");

            string output;
            for (char ch : static_cast<string>(value))
            {
                switch (ch)
                {

                case '\0':
                    break;
                case '\"':
                    output.append("\\\"");
                    break;
                case '\\':
                    output.append("\\\\");
                    break;
                case '\b':
                    output.append("\\b");
                    break;
                case '\f':
                    output.append("\\f");
                    break;
                case '\n':
                    output.append("\\n");
                    break;
                case '\r':
                    output.append("\\r");
                    break;
                case '\t':
                    output.append("\\t");
                    break;
                default:
                    output.push_back(ch);
                    break;
                }
            }

            stringPtr.append(output);
            stringPtr.append("\"");
        }
        else if constexpr (is_same_v<PtrT, wstring> && (is_same_v<wchar_t, T> || is_same_v<wchar_t *, T> || is_same_v<const wchar_t *, T> || is_same_v<T, wstring>))
        {
            wstring output;
            for (wchar_t ch : static_cast<wstring>(value))
            {
                switch (ch)
                {
                case L'\0':
                    break;
                case L'\"':
                    output.append(L"\\\"");
                    break;
                case L'\\':
                    output.append(L"\\\\");
                    break;
                case L'\b':
                    output.append(L"\\b");
                    break;
                case L'\f':
                    output.append(L"\\f");
                    break;
                case L'\n':
                    output.append(L"\\n");
                    break;
                case L'\r':
                    output.append(L"\\r");
                    break;
                case L'\t':
                    output.append(L"\\t");
                    break;
                default:
                    output.push_back(ch);
                    break;
                }
            }
            stringPtr.append(L"\"" + output + L"\"");

            if (data_list.size() - 1 > index)
            {
                stringPtr.append(L",");
            }
        }

        //----
        else
        {
            stringPtr.append(is_same_v<PtrT, string> ? "null" : L"null");
        }

        if (data_list.size() - 1 > index)
        {
            stringPtr.append(is_same_v<PtrT, string> ? "," : L",");
        }
    }

    stringPtr.append(is_same_v<PtrT, string> ? "]" : L"]");
}

/**
 * @brief c内容转为json的value
 *
 * @tparam T
 * @tparam V
 * @param value
 * @return string
 */
template <typename T, typename V>
string hmc_string_util::to_json_value(T &value)
{
    string result = "";
    static_assert(
        is_integral<T>::value ||
            is_floating_point<T>::value ||
            is_same_v<char, T> ||
            is_same_v<char *, T> ||
            is_same_v<const char *, T> ||
            is_same_v<std::vector<V>, T> ||
            is_same_v<T, string>,
        "Unsupported type preset escape (不支持的类型预设转义)");

    // boolean
    if constexpr (is_same_v<T, bool>)
    {
        result.append((value ? "true" : "false"));
    }
    // number -> int
    else if constexpr (is_integral<T>::value)
    {
        result.append(to_string(value));
    }
    // number -> float
    else if constexpr (is_floating_point<T>::value)
    {
        result.append(to_string(value));
    }
    // array -> <any>[]
    else if constexpr (is_same<std::vector<V>, T>::value)
    {
        result.append(vec_to_array_json(value));
    }
    // string -> "<char*>"
    else if constexpr (is_same_v<char, T> || is_same_v<char *, T> || is_same_v<const char *, T> || is_same_v<T, string>)
    {
        result.append("\"");

        string output;
        for (char ch : static_cast<string>(value))
        {
            switch (ch)
            {
            case '\0':
                break;
            case '\"':
                output.append("\\\"");
                break;
            case '\\':
                output.append("\\\\");
                break;
            case '\b':
                output.append("\\b");
                break;
            case '\f':
                output.append("\\f");
                break;
            case '\n':
                output.append("\\n");
                break;
            case '\r':
                output.append("\\r");
                break;
            case '\t':
                output.append("\\t");
                break;
            default:
                output.push_back(ch);
                break;
            }
        }

        result.append(output);
        result.append("\"");
    }
    // null
    else
    {
        result.append("null");
    }

    return result;
}

template <typename KEY, typename V>
wstring hmc_string_util::map_to_jsonW(map<KEY, V> item_list)
{
    wstring result = L"{";

    static_assert(
        is_integral<KEY>::value ||
            is_floating_point<KEY>::value ||
            is_same_v<wchar_t, KEY> ||
            is_same_v<wchar_t *, KEY> ||
            is_same_v<const wchar_t *, KEY> ||
            is_same_v<KEY, wstring>,
        "Unsupported type preset escape (不支持的类型预设转义)");

    static_assert(
        is_integral<V>::value ||
            is_floating_point<V>::value ||
            is_same_v<wchar_t, V> ||
            is_same_v<wchar_t *, V> ||
            is_same_v<const wchar_t *, V> ||
            is_same_v<V, wstring>,
        "Unsupported type preset escape (不支持的类型预设转义)");
    size_t index = 0;

    for (auto item : item_list)
    {

        // 解析 key

        if constexpr (is_same_v<KEY, bool>)
        {
            result.append((item.first ? L"true" : L"false"));
        }
        // number -> int
        else if constexpr (is_integral<KEY>::value)
        {
            result.append(to_wstring(item.first));
        }
        // number -> float
        else if constexpr (is_floating_point<KEY>::value)
        {
            result.append(to_wstring(item.first));
        }
        //// array -> <any>[]
        // else if constexpr (is_same<std::vector<ARR_V>, KEY>::value)
        //{
        //     result.append(vec_to_array_json(value));
        // }
        //  string -> "<char*>"
        else if constexpr (is_same_v<wchar_t, KEY> || is_same_v<wchar_t *, KEY> || is_same_v<const wchar_t *, KEY> || is_same_v<KEY, wstring>)
        {
            result.append(L"\"");

            wstring output;
            for (wchar_t ch : static_cast<wstring>(item.first))
            {
                switch (ch)
                {
                case L'\0':
                    break;
                case L'\"':
                    output.append(L"\\\"");
                    break;
                case L'\\':
                    output.append(L"\\\\");
                    break;
                case L'\b':
                    output.append(L"\\b");
                    break;
                case L'\f':
                    output.append(L"\\f");
                    break;
                case L'\n':
                    output.append(L"\\n");
                    break;
                case L'\r':
                    output.append(L"\\r");
                    break;
                case L'\t':
                    output.append(L"\\t");
                    break;
                default:
                    output.push_back(ch);
                    break;
                }
            }

            result.append(output);
            result.append(L"\"");
        }
        // null
        else
        {
            result.append(to_wstring(index));
        }

        result.push_back(L':');

        // result.append(hmc_string_util::to_json_value(item.second));

        if constexpr (is_same_v<V, bool>)
        {
            result.append((item.second ? L"true" : L"false"));
        }
        // number -> int
        else if constexpr (is_integral<V>::value)
        {
            result.append(to_wstring(item.second));
        }
        // number -> float
        else if constexpr (is_floating_point<V>::value)
        {
            result.append(to_wstring(item.second));
        }
        // string -> "<char*>"
        else if constexpr (is_same_v<wchar_t, V> || is_same_v<wchar_t *, V> || is_same_v<const wchar_t *, V> || is_same_v<V, wstring>)
        {
            result.append(L"\"");

            wstring output;
            for (wchar_t ch : static_cast<wstring>(item.second))
            {
                switch (ch)
                {
                case L'\"':
                    output.append(L"\\\"");
                    break;
                case L'\\':
                    output.append(L"\\\\");
                    break;
                case L'\b':
                    output.append(L"\\b");
                    break;
                case L'\f':
                    output.append(L"\\f");
                    break;
                case L'\n':
                    output.append(L"\\n");
                    break;
                case L'\r':
                    output.append(L"\\r");
                    break;
                case L'\t':
                    output.append(L"\\t");
                    break;
                default:
                    output.push_back(ch);
                    break;
                }
            }

            result.append(output);
            result.append(L"\"");
        }
        // null
        else
        {
            result.append(L"null");
        }

        if (item_list.size() - 1 > index)
        {
            result.push_back(L',');
        }
        index++;
    }

    result.push_back(L'}');

    return result;
}

template <typename KEY, typename V>
string hmc_string_util::map_to_jsonA(map<KEY, V> item_list)
{
    string result = "{";

    static_assert(
        is_integral<KEY>::value ||
            is_floating_point<KEY>::value ||
            is_same_v<char, KEY> ||
            is_same_v<char *, KEY> ||
            is_same_v<const char *, KEY> ||
            is_same_v<KEY, string>,
        "Unsupported type preset escape (不支持的类型预设转义)");

    size_t index = 0;

    for (auto item : item_list)
    {

        // 解析 key

        if constexpr (is_same_v<KEY, bool>)
        {
            result.append((item.first ? "true" : "false"));
        }
        // number -> int
        else if constexpr (is_integral<KEY>::value)
        {
            result.append(to_string(item.first));
        }
        // number -> float
        else if constexpr (is_floating_point<KEY>::value)
        {
            result.append(to_string(item.first));
        }
        //// array -> <any>[]
        // else if constexpr (is_same<std::vector<ARR_V>, KEY>::value)
        //{
        //     result.append(vec_to_array_json(value));
        // }
        //  string -> "<char*>"
        else if constexpr (is_same_v<char, KEY> || is_same_v<char *, KEY> || is_same_v<const char *, KEY> || is_same_v<KEY, string>)
        {
            result.append("\"");

            string output;
            for (char ch : static_cast<string>(item.first))
            {
                switch (ch)
                {
                case '\"':
                    output.append("\\\"");
                    break;
                case '\\':
                    output.append("\\\\");
                    break;
                case '\b':
                    output.append("\\b");
                    break;
                case '\f':
                    output.append("\\f");
                    break;
                case '\n':
                    output.append("\\n");
                    break;
                case '\r':
                    output.append("\\r");
                    break;
                case '\t':
                    output.append("\\t");
                    break;
                default:
                    output.push_back(ch);
                    break;
                }
            }

            result.append(output);
            result.append("\"");
        }
        // null
        else
        {
            result.append(to_string(index));
        }

        result.push_back(':');

        // result.append(hmc_string_util::to_json_value(item.second));

        if constexpr (is_same_v<V, bool>)
        {
            result.append((item.second ? "true" : "false"));
        }
        // number -> int
        else if constexpr (is_integral<V>::value)
        {
            result.append(to_string(item.second));
        }
        // number -> float
        else if constexpr (is_floating_point<V>::value)
        {
            result.append(to_string(item.second));
        }
        // string -> "<char*>"
        else if constexpr (is_same_v<char, V> || is_same_v<char *, V> || is_same_v<const char *, V> || is_same_v<V, string>)
        {
            result.append("\"");

            string output;
            for (char ch : static_cast<string>(item.second))
            {
                switch (ch)
                {
                case '\"':
                    output.append("\\\"");
                    break;
                case '\\':
                    output.append("\\\\");
                    break;
                case '\b':
                    output.append("\\b");
                    break;
                case '\f':
                    output.append("\\f");
                    break;
                case '\n':
                    output.append("\\n");
                    break;
                case '\r':
                    output.append("\\r");
                    break;
                case '\t':
                    output.append("\\t");
                    break;
                default:
                    output.push_back(ch);
                    break;
                }
            }

            result.append(output);
            result.append("\"");
        }

        // null
        else
        {
            result.append("nul");
        }

        if (item_list.size() - 1 > index)
        {
            result.push_back(',');
        }
        index++;
    }

    result.push_back('}');

    return result;
}

#define ___hmc_string_util_diff_any_value_eval_map_to_fn_map(any_value, fn_name, map_type, key_type, value_type) \
    if (any_value.type() == typeid(map_type<key_type, value_type>))                                              \
    {                                                                                                            \
        return fn_name(std::any_cast<map_type<key_type, value_type>>(any_value));                                \
    }                                                                                                            \
    if (any_value.type() == typeid(map_type<value_type, key_type>))                                              \
    {                                                                                                            \
        return fn_name(std::any_cast<map_type<value_type, key_type>>(any_value));                                \
    }


string hmc_string_util::map_to_jsonA(std::any item_list)
{
    string result = "{";

    if (!item_list.has_value())
    {
        return "{}";
    }
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, string, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, char, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, char *, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, const char *, string);

    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, int, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, int64_t, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long long, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, int32_t, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, size_t, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, unsigned long, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long int, string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, unsigned long, string);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, char, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, int64_t, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long long, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, int32_t, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, size_t, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, unsigned long, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long int, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, unsigned long, char);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, char, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, int64_t, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long long, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, int32_t, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, size_t, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, unsigned long, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long int, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, unsigned long, char *);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, int64_t, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long long, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, int32_t, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, size_t, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, unsigned long, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, long int, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, map, unsigned long, const char *);

    return "{}";
}

wstring hmc_string_util::map_to_jsonW(std::any item_list)
{

    if (!item_list.has_value())
    {
        return L"{}";
    }
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, wstring, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, wchar_t, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, wchar_t *, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, const wchar_t *, wstring);

    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, int, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, int64_t, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long long, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, int32_t, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, size_t, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, unsigned long, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long int, wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, unsigned long, wstring);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, wchar_t, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, int64_t, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long long, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, int32_t, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, size_t, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, unsigned long, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long int, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, unsigned long, wchar_t);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, wchar_t, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, int64_t, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long long, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, int32_t, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, size_t, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, unsigned long, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long int, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, unsigned long, wchar_t *);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, int64_t, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long long, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, int32_t, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, size_t, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, unsigned long, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, long int, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, map, unsigned long, const wchar_t *);

    return L"{}";
}
