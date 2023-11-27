
#include "./hmc_string_util.hpp"

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

/**
 * @brief 仅拼接文本
 *
 * @tparam Arguments
 * @param input
 * @param firstInput
 * @param data_list
 * @return string
 */
template <typename... Arguments>
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
template <typename... Arguments>
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

inline wstring hmc_string_util::utf8_to_utf16(const string utf8)
{
    // 源作者@ https://github.com/GiovanniDicanio/UnicodeConversions/    for MIT license 注意：与原稿对比有多处改动

    // Result of the conversion
    wstring utf16;

    // First, handle the special case of empty input string
    if (utf8.empty())
    {
        _ASSERTE(utf16.empty());
        return utf16;
    }

    // Safely fail if an invalid UTF-8 character sequence is encountered
    constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;

    // Safely cast the length of the source UTF-8 string (expressed in chars)
    // from size_t (returned by string::length()) to int
    // for the MultiByteToWideChar API.
    // If the size_t value is too big to be stored into an int,
    // throw an exception to prevent conversion errors like huge size_t values
    // converted to *negative* integers.
    if (utf8.length() > static_cast<size_t>((numeric_limits<int>::max)()))
    {
        //  __HMC_debug(string("Utf8ToUtf16"), string("Input string too long: size_t-length doesn't fit into int."));
    }
    const int utf8Length = static_cast<int>(utf8.length());

    // Get the size of the destination UTF-16 string
    const int utf16Length = ::MultiByteToWideChar(
        CP_UTF8,     // source string is in UTF-8
        kFlags,      // conversion flags
        utf8.data(), // source UTF-8 string pointer
        utf8Length,  // length of the source UTF-8 string, in chars
        nullptr,     // unused - no conversion done in this step
        0            // request size of destination buffer, in wchar_ts
    );
    if (utf16Length == 0)
    {
        // Conversion error: capture error code and throw
        const DWORD error = ::GetLastError();
        // hmc::error

        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-8 sequence found in input string." : "Cannot convert from UTF-8 to UTF-16 (WideCharToMultiByte failed).");
        //  __HMC_debug(string("Utf16ToUtf8"), error_message, to_string(error));
    }

    // Make room in the destination string for the converted bits
    utf16.resize(utf16Length);

    // Do the actual conversion from UTF-8 to UTF-16
    int result = ::MultiByteToWideChar(
        CP_UTF8,     // source string is in UTF-8
        kFlags,      // conversion flags
        utf8.data(), // source UTF-8 string pointer
        utf8Length,  // length of source UTF-8 string, in chars
        &utf16[0],   // pointer to destination buffer
        utf16Length  // size of destination buffer, in wchar_ts
    );
    if (result == 0)
    {
        // Conversion error: capture error code and throw
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-8 sequence found in input string." : "Cannot convert from UTF-8 to UTF-16 (WideCharToMultiByte failed).");
        //  __HMC_debug(string("Utf16ToUtf8"), error_message, to_string(error));
    }

    return utf16;
}

inline string hmc_string_util::utf16_to_utf8(const wstring utf16)
{
    // 源作者@ https://github.com/GiovanniDicanio/UnicodeConversions/    for MIT license 注意：与原稿对比有多处改动
    // Result of the conversion
    string utf8;

    // First, handle the special case of empty input string
    if (utf16.empty())
    {
        _ASSERTE(utf8.empty());
        return utf8;
    }

    // Safely fail if an invalid UTF-16 character sequence is encountered
    constexpr DWORD kFlags = WC_ERR_INVALID_CHARS;

    // Safely cast the length of the source UTF-16 string (expressed in wchar_ts)
    // from size_t (returned by wstring::length()) to int
    // for the WideCharToMultiByte API.
    // If the size_t value is too big to be stored into an int,
    // throw an exception to prevent conversion errors like huge size_t values
    // converted to *negative* integers.
    if (utf16.length() > static_cast<size_t>((numeric_limits<int>::max)()))
    {
        //  __HMC_debug(string("Utf16ToUtf8"), string("Input string too long: size_t-length doesn't fit into int."));
    }
    const int utf16Length = static_cast<int>(utf16.length());

    // Get the length, in chars, of the resulting UTF-8 string
    const int utf8Length = ::WideCharToMultiByte(
        CP_UTF8,         // convert to UTF-8
        kFlags,          // conversion flags
        utf16.data(),    // source UTF-16 string
        utf16Length,     // length of source UTF-16 string, in wchar_ts
        nullptr,         // unused - no conversion required in this step
        0,               // request size of destination buffer, in chars
        nullptr, nullptr // unused
    );
    if (utf8Length == 0)
    {
        // Conversion error: capture error code and throw
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-16 sequence found in input string." : "Cannot convert from UTF-16 to UTF-8 (WideCharToMultiByte failed).");
        //  __HMC_debug(string("Utf16ToUtf8"), error_message, to_string(error));
    }

    // Make room in the destination string for the converted bits
    utf8.resize(utf8Length);

    // Do the actual conversion from UTF-16 to UTF-8
    int result = ::WideCharToMultiByte(
        CP_UTF8,         // convert to UTF-8
        kFlags,          // conversion flags
        utf16.data(),    // source UTF-16 string
        utf16Length,     // length of source UTF-16 string, in wchar_ts
        &utf8[0],        // pointer to destination buffer
        utf8Length,      // size of destination buffer, in chars
        nullptr, nullptr // unused
    );
    if (result == 0)
    {
        // Conversion error: capture error code and throw
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-16 sequence found in input string." : "Cannot convert from UTF-16 to UTF-8 (WideCharToMultiByte failed).");
        //  __HMC_debug(string("Utf16ToUtf8"), error_message, to_string(error));
    }

    return utf8;
}

inline string hmc_string_util::utf16_to_ansi(const wstring utf16)
{

    string ansi;

    if (utf16.empty())
    {
        _ASSERTE(ansi.empty());
        return ansi;
    }

    constexpr DWORD kFlags = WC_ERR_INVALID_CHARS;

    if (utf16.length() > static_cast<size_t>((numeric_limits<int>::max)()))
    {
        //  __HMC_debug(string("Utf16ToAnsi"), string("Input string too long: size_t-length doesn't fit into int."));
        return ansi;
    }

    const int utf16Length = static_cast<int>(utf16.length());

    const int ansiLength = ::WideCharToMultiByte(
        CP_ACP,
        kFlags,
        utf16.data(),
        utf16Length,
        nullptr,
        0,
        nullptr, nullptr);
    if (ansiLength == 0)
    {
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-16 sequence found in input string." : "Cannot convert from UTF-16 to CP_ACP (WideCharToMultiByte failed).");
        //  __HMC_debug(string("Utf16ToAnsi"), error_message, to_string(error));
    }

    ansi.resize(ansiLength);

    int result = ::WideCharToMultiByte(
        CP_ACP,
        kFlags,
        utf16.data(),
        utf16Length,
        &ansi[0],
        ansiLength,
        nullptr, nullptr);
    if (result == 0)
    {
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-16 sequence found in input string." : "Cannot convert from UTF-16 to CP_ACP (WideCharToMultiByte failed).");
        //  __HMC_debug(string("Utf16ToAnsi"), error_message, to_string(error));
    }

    return ansi;
}

inline wstring hmc_string_util::ansi_to_utf16(const string ansi)
{

    wstring utf16;

    if (ansi.empty())
    {
        _ASSERTE(utf16.empty());
        return utf16;
    }

    constexpr DWORD _kFlags = MB_ERR_INVALID_CHARS;

    if (ansi.length() > static_cast<size_t>((numeric_limits<int>::max)()))
    {
        //  __HMC_debug(string("AnsiToUtf16"), string("Input string too long: size_t-length doesn't fit into int."));
    }
    const int utf8Length = static_cast<int>(ansi.length());

    const int utf16Length = ::MultiByteToWideChar(
        CP_ACP,
        _kFlags,
        ansi.data(),
        utf8Length,
        nullptr,
        0);
    if (utf16Length == 0)
    {
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid ansi sequence found in input string." : "Cannot convert from ansi to UTF-16 (WideCharToMultiByte failed).");
        //  __HMC_debug(string("AnsiToUtf16"), error_message, to_string(error));
    }

    utf16.resize(utf16Length);

    int result = ::MultiByteToWideChar(
        CP_ACP,
        _kFlags,
        ansi.data(),
        utf8Length,
        &utf16[0],
        utf16Length);
    if (result == 0)
    {
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid ansi sequence found in input string." : "Cannot convert from ansi to UTF-16 (WideCharToMultiByte failed).");
        //  __HMC_debug(string("AnsiToUtf16"), error_message, to_string(error));
    }

    return utf16;
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
