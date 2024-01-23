
#include "./hmc_string_util.h"

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
std::string hmc_string_util::string_join(const std::string &input, const std::string &firstInput, std::vector<Arguments...> data_list)
{
    std::string result = "";
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
std::wstring hmc_string_util::string_join(const std::wstring &input, const std::wstring &firstInput, std::vector<Arguments...> data_list)
{
    std::wstring result = "";
    result.append(input);
    result.append(firstInput);
    for (auto data : data_list)
    {
        result.append(data);
    }

    return result;
}

// 文本中是否有数字 并且是否是安全的 int32
bool hmc_string_util::is_int_str(const std::string Value)
{
    bool Result = false;
    if (Value.empty())
        return Result;
    try
    {
        int n = std::stoi(Value);
        Result = true;
    }
    catch (...)
    {
        return Result;
    }

    return Result;
}

// 文本中是否有数字 并且是否是安全的 long
bool hmc_string_util::is_long_str(const std::string Value)
{
    bool Result = false;
    if (Value.empty())
        return Result;
    try
    {
        long n = std::stol(Value);
        Result = true;
    }
    catch (...)
    {
        return Result;
    }

    return Result;
}

// 文本中是否有数字 并且是否是安全的 long long
bool hmc_string_util::is_longlong_str(const std::string Value)
{
    bool Result = false;
    if (Value.empty())
        return Result;
    try
    {
        long long n = std::stoll(Value);
        Result = true;
    }
    catch (...)
    {
        return Result;
    }

    return Result;
}

inline std::wstring hmc_string_util::utf8_to_utf16(const std::string input)
{
    const char *pszText = input.c_str();

    if (pszText == NULL || strlen(pszText) == 0)
    {
        return std::wstring();
    }
    int iSizeInChars = ::MultiByteToWideChar(CP_UTF8, 0, pszText, -1, NULL, 0);
    wchar_t *pWideChar = new (std::nothrow) wchar_t[iSizeInChars];
    if (pWideChar == NULL)
    {
        return std::wstring();
    }

    ::wmemset(pWideChar, 0, iSizeInChars);
    ::MultiByteToWideChar(CP_UTF8, 0, pszText, -1, pWideChar, iSizeInChars);

    std::wstring strResult = std::wstring(pWideChar);
    delete[] pWideChar;
    pWideChar = NULL;
    return strResult;
}

inline std::string hmc_string_util::utf16_to_utf8(const std::wstring input)
{
    const wchar_t *pwszText = input.c_str();

    if (pwszText == NULL || ::wcslen(pwszText) == 0)
    {
        return std::string();
    }
    int iSizeInBytes = ::WideCharToMultiByte(CP_UTF8, 0, pwszText, -1, NULL, 0, NULL, NULL);
    char *pUTF8 = new (std::nothrow) char[iSizeInBytes];
    if (pUTF8 == NULL)
    {
        return std::string();
    }

    ::memset(pUTF8, 0, iSizeInBytes);
    ::WideCharToMultiByte(CP_UTF8, 0, pwszText, -1, pUTF8, iSizeInBytes, NULL, NULL);

    std::string strResult = std::string(pUTF8);
    delete[] pUTF8;
    pUTF8 = NULL;
    return strResult;
}

inline std::string hmc_string_util::utf16_to_ansi(const std::wstring input)
{
    const wchar_t *pwszText = input.c_str();

    if (pwszText == NULL || ::wcslen(pwszText) == 0)
    {
        return std::string();
    }
    int iSizeInBytes = ::WideCharToMultiByte(CP_ACP, 0, pwszText, -1, NULL, 0, NULL, NULL);
    char *pMultiByte = new (std::nothrow) char[iSizeInBytes];
    if (pMultiByte == NULL)
    {
        return std::string();
    }

    ::memset(pMultiByte, 0, iSizeInBytes);
    ::WideCharToMultiByte(CP_ACP, 0, pwszText, -1, pMultiByte, iSizeInBytes, NULL, NULL);

    std::string strResult = std::string(pMultiByte);
    delete[] pMultiByte;
    pMultiByte = NULL;

    return strResult;
}

inline std::wstring hmc_string_util::ansi_to_utf16(const std::string input)
{
    const char *pszText = input.c_str();

    if (pszText == NULL || ::strlen(pszText) == 0)
    {
        return std::wstring();
    }
    int iSizeInChars = ::MultiByteToWideChar(CP_ACP, 0, pszText, -1, NULL, 0);
    wchar_t *pWideChar = new (std::nothrow) wchar_t[iSizeInChars];
    if (pWideChar == NULL)
    {
        return std::wstring();
    }

    ::wmemset(pWideChar, 0, iSizeInChars);
    ::MultiByteToWideChar(CP_ACP, 0, pszText, -1, pWideChar, iSizeInChars);

    std::wstring strResult = std::wstring(pWideChar);
    delete[] pWideChar;
    pWideChar = NULL;
    return strResult;
}

// UFT8 字符转为GBK(中文)
std::string hmc_string_util::utf8_to_gbk(const std::string u8str)
{
    std::string Result;
    TCHAR *pTempTstr;
    WCHAR *pTempwstr;

    int strSizeTempVar = ::MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, NULL, 0);
    pTempwstr = new WCHAR[strSizeTempVar + 1];

    ::MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, pTempwstr, strSizeTempVar);
    strSizeTempVar = ::WideCharToMultiByte(CP_ACP, 0, pTempwstr, -1, NULL, 0, NULL, NULL);

    pTempTstr = new TCHAR[strSizeTempVar + 1];

    ::WideCharToMultiByte(CP_ACP, 0, pTempwstr, -1, (LPSTR)pTempTstr, strSizeTempVar, NULL, NULL);
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
std::string hmc_string_util::ansi_to_utf8(const std::string ansi)
{
    std::wstring to_utf16 = ansi_to_utf16(ansi);
    return utf16_to_utf8(to_utf16);
    return std::string("");
}

// ----------------------------------------------------------------
// U82A
// utf8 to Local CP_ACP ( Ansi [A] ) encoding
// utf8 字符 转 winapi A字符
// ? 推荐w字符(utf16) 损耗更少一点 napi支持直接返回utf16
// ----------------------------------------------------------------
std::string hmc_string_util::utf8_to_ansi(const std::string utf8)
{
    std::wstring to_utf16 = utf8_to_utf16(utf8);
    return utf16_to_ansi(to_utf16);
}

inline bool hmc_string_util::is_utf8(const std::string input)
{
    for (std::string::const_iterator str = input.begin(), eos = input.end(); str != eos; ++str)
    {
        std::uint8_t cuChar = static_cast<std::uint8_t>(*str);
        size_t len = sizeof(cuChar);
        if (cuChar == '\b' || cuChar == '\n' || cuChar == '\r' || cuChar == '\f' || cuChar == '\t')
        {
            // 转义符
        }
        // 超出utf8的大小了
        else if (static_cast<std::uint8_t>(cuChar) >= 0xF8)
            return false;

        else if (static_cast<std::uint8_t>(cuChar) >= 0xF0)
        {
            if (len < 4)
                return false;
            for (int i = 1; i <= 3; i++)
            {
                std::uint8_t diff_cuChar = (cuChar + i);

                if ((diff_cuChar & 0xC0) != 0x80)
                    return false;
            }
            return true;
        }
        else if (static_cast<std::uint8_t>(cuChar) >= 0xE0)
        {
            if (len < 3)
                return false;
            for (int i = 1; i <= 2; i++)
            {
                std::uint8_t diff_cuChar = (cuChar + i);

                if ((diff_cuChar & 0xC0) != 0x80)
                    return false;
            }
            return true;
        }
        else if (static_cast<std::uint8_t>(cuChar) >= 0xC0)
        {

            if (len < 2)
                return false;
            std::uint8_t diff_cuChar = (cuChar + 1);

            if ((diff_cuChar & 0xC0) != 0x80)
                return false;
            return true;
        }
        else if (static_cast<std::uint8_t>(cuChar) >= 0x80)
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
inline void hmc_string_util::replaceAll(std::string &sourcePtr, std::string from, std::string to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

inline void hmc_string_util::replaceAll(std::wstring &sourcePtr, const std::wstring from, const std::wstring to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

inline void hmc_string_util::replaceAll(std::string &sourcePtr, std::vector<std::tuple<std::string, std::string>> list)
{

    size_t len = list.size();

    for (size_t i = 0; i < len; i++)
    {

        std::string from = std::get<0>(list[i]);
        std::string to = std::get<1>(list[i]);

        size_t start_pos = 0;
        while ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
        {
            sourcePtr.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    }
}

inline void hmc_string_util::replaceAll(std::wstring &sourcePtr, std::vector<std::tuple<std::wstring, std::wstring>> list)
{
    size_t len = list.size();

    for (size_t i = 0; i < len; i++)
    {

        std::wstring from = std::get<0>(list[i]);
        std::wstring to = std::get<1>(list[i]);

        size_t start_pos = 0;
        while ((start_pos = sourcePtr.find(from, start_pos)) != std::wstring::npos)
        {
            sourcePtr.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    }
}

/**
 * @brief 替换一次
 *
 * @param sourcePtr
 * @param from
 * @param to
 */
inline void hmc_string_util::replace(std::string &sourcePtr, std::string from, std::string to)
{
    size_t start_pos = 0;
    if ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        return;
    }
}

inline void hmc_string_util::replace(std::wstring &sourcePtr, const std::wstring from, const std::wstring to)
{
    size_t start_pos = 0;
    if ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        return;
    }
}

/**
 * @brief 替换一次
 *
 * @param sourcePtr
 * @param from
 * @param to
 */
inline void hmc_string_util::replace(std::string &sourcePtr, std::vector<std::tuple<std::string, std::string>> list)
{
    size_t len = list.size();

    for (size_t i = 0; i < len; i++)
    {

        std::string from = std::get<0>(list[i]);
        std::string to = std::get<1>(list[i]);
        size_t start_pos = 0;
        if ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
        {
            sourcePtr.replace(start_pos, from.length(), to);
            continue;
        }
    }
}

inline void hmc_string_util::replace(std::wstring &sourcePtr, std::vector<std::tuple<std::wstring, std::wstring>> list)
{
    size_t len = list.size();

    for (size_t i = 0; i < len; i++)
    {

        std::wstring from = std::get<0>(list[i]);
        std::wstring to = std::get<1>(list[i]);
        size_t start_pos = 0;
        if ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
        {
            sourcePtr.replace(start_pos, from.length(), to);
            continue;
        }
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
inline void hmc_string_util::replace(std::string &sourcePtr, std::string from, size_t bubble_index, std::string to)
{
    size_t start_pos = 0;
    size_t index = 0;
    if ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        if (index == bubble_index)
        {
            sourcePtr.replace(start_pos, from.length(), to);
            return;
        }
        index++;
    }
}

inline std::string hmc_string_util::escapeJsonString(const std::string &input, bool is_to_value)
{
    std::string output;
    if (is_to_value)
    {
        output.push_back('"');
    }

    for (char ch : input)
    {
        switch (ch)
        {

        case '\0':
            break;
        case '"':
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

    if (is_to_value)
    {
        output.push_back('"');
    }

    return output;
}

inline std::wstring hmc_string_util::escapeJsonString(const std::wstring &input, bool is_to_value)
{
    std::wstring output;

    if (is_to_value)
    {
        output.push_back(L'"');
    }

    for (wchar_t ch : input)
    {
        switch (ch)
        {
        case L'\0':
            break;
        case L'"':
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
    if (is_to_value)
    {
        output.push_back(L'"');
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
void hmc_string_util::split(std::string &sourcePtr, char splitter, std::vector<std::string> &item_list)
{

    item_list.clear();
    if (sourcePtr.empty())
    {
        return;
    }
    std::string item;
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
        item_list.push_back(std::move(item));
}

std::vector<std::string> hmc_string_util::split(std::string &sourcePtr, char splitter)
{
    if (sourcePtr.empty())
    {
        return std::vector<std::string>();
    }
    std::vector<std::string> item_list;
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
void hmc_string_util::split(std::wstring &sourcePtr, wchar_t splitter, std::vector<std::wstring> &item_list)
{

    item_list.clear();
    if (sourcePtr.empty())
    {
        return;
    }

    std::wstring item;
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
        item_list.push_back(std::move(item));
}

std::vector<std::wstring> hmc_string_util::split(std::wstring &sourcePtr, wchar_t splitter)
{
    if (sourcePtr.empty())
    {
        return std::vector<std::wstring>();
    }
    std::vector<std::wstring> item_list;
    split(sourcePtr, splitter, item_list);
    return item_list;
}

void hmc_string_util::join(std::vector<std::string> &item_list, std::string splitter, std::string outputPtr)
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

std::string hmc_string_util::join(std::vector<std::string> &item_list, std::string splitter)
{
    std::string result = std::string();
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
std::string hmc_string_util::join(std::vector<std::string> &item_list)
{
    return join(item_list, std::string(""));
}

void hmc_string_util::join(std::vector<std::wstring> &item_list, std::wstring splitter, std::wstring outputPtr)
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
std::wstring hmc_string_util::join(std::vector<std::wstring> &item_list, std::wstring splitter)
{
    std::wstring result = std::wstring();
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
std::wstring hmc_string_util::join(std::vector<std::wstring> &item_list)
{
    return join(item_list, std::wstring(L""));
}

std::string hmc_string_util::trim(const std::string &input, const std::string &match)
{

    std::string temp_trim_str = trimLast(input, match);
    return trimFirst(temp_trim_str, match);
}

std::string hmc_string_util::trimFirst(const std::string &input, const std::string &match)
{
    auto start_pos = input.find_first_not_of(match);
    return (start_pos == std::string::npos) ? "" : input.substr(start_pos);
}

std::string hmc_string_util::trimLast(const std::string &input, const std::string &match)
{
    auto end_pos = input.find_last_not_of(match);
    return (end_pos == std::string::npos) ? "" : input.substr(0, end_pos + 1);
}

std::wstring hmc_string_util::trim(const std::wstring &input, const std::wstring &match)
{
    std::wstring temp_trim_str = trimLast(input, match);
    return trimFirst(temp_trim_str, match);
}

std::wstring hmc_string_util::trimFirst(const std::wstring &input, const std::wstring &match)
{
    auto start_pos = input.find_first_not_of(match);
    return (start_pos == std::string::npos) ? L"" : input.substr(start_pos);
}

std::wstring hmc_string_util::trimLast(const std::wstring &input, const std::wstring &match)
{
    auto end_pos = input.find_last_not_of(match);
    return (end_pos == std::string::npos) ? L"" : input.substr(0, end_pos + 1);
}

// 移除尾部 为xx 的指定文本
std::string hmc_string_util::trimLastAll(const std::string &input, const std::string &match)
{
    std::string result = std::string(input);
    if (match.empty())
    {
        return result;
    }
    for (size_t i = 0; i < input.size(); i++)
    {
        std::string new_result = trimLast(result, match);
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
std::string hmc_string_util::trimAll(const std::string &input, const std::string &match)
{
    std::string result = std::string(input);
    if (match.empty())
    {
        return result;
    }

    for (size_t i = 0; i < input.size(); i++)
    {
        std::string new_result = trim(result, match);
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
std::string hmc_string_util::trimFirstAll(const std::string &input, const std::string &match)
{
    std::string result = std::string(input);
    if (match.empty())
    {
        return result;
    }

    for (size_t i = 0; i < input.size(); i++)
    {
        std::string new_result = trimFirst(result, match);
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
std::wstring hmc_string_util::trimAll(const std::wstring &input, const std::wstring &match)
{
    std::wstring result = std::wstring(input);
    if (match.empty())
    {
        return result;
    }

    for (size_t i = 0; i < input.size(); i++)
    {
        std::wstring new_result = trim(result, match);
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
std::wstring hmc_string_util::trimLastAll(const std::wstring &input, const std::wstring &match)
{
    std::wstring result = std::wstring(input);
    if (match.empty())
    {
        return result;
    }
    for (size_t i = 0; i < input.size(); i++)
    {
        std::wstring new_result = trimLast(result, match);
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
std::wstring hmc_string_util::trimFirstAll(const std::wstring &input, const std::wstring &match)
{
    std::wstring result = std::wstring(input);
    if (match.empty())
    {
        return result;
    }

    for (size_t i = 0; i < input.size(); i++)
    {
        std::wstring new_result = trimFirst(result, match);
        if (result.empty() || result.size() == new_result.size())
        {
            return new_result;
        }
        result.clear();
        result.append(new_result);
    }

    return result;
}

std::wstring hmc_string_util::StripSpaces(const std::wstring &str)
{
    const std::size_t s = str.find_first_not_of(L" \t\r\n");

    if (str.npos != s)
        return str.substr(s, str.find_last_not_of(L" \t\r\n") - s + 1);
    else
        return str;
}

std::string hmc_string_util::StripSpaces(const std::string &str)
{
    const std::size_t s = str.find_first_not_of(" \t\r\n");

    if (str.npos != s)
        return str.substr(s, str.find_last_not_of(" \t\r\n") - s + 1);
    else
        return str;
}

void hmc_string_util::unEscapeJsonString(std::string &sourcePtr)
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

void hmc_string_util::unEscapeJsonString(std::wstring &sourcePtr)
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

std::vector<std::wstring> hmc_string_util::ansi_to_utf16(std::vector<std::string> item_list)
{
    std::vector<std::wstring> result = {};
    for (auto item : item_list)
    {
        result.push_back(ansi_to_utf16(item));
    }
    return result;
}

std::vector<std::string> hmc_string_util::utf16_to_ansi(std::vector<std::wstring> item_list)
{
    std::vector<std::string> result = {};
    for (auto item : item_list)
    {
        result.push_back(utf16_to_ansi(item));
    }
    return result;
}

std::map<std::wstring, std::wstring> hmc_string_util::ansi_to_utf16(std::map<std::string, std::string> item_list)
{
    std::map<std::wstring, std::wstring> result = {};
    for (auto item : item_list)
    {
        std::wstring key = ansi_to_utf16(item.first);
        std::wstring value = ansi_to_utf16(item.second);

        result.insert(std::make_pair(key, value));
    }
    return result;
}

std::map<std::string, std::string> hmc_string_util::utf16_to_ansi(std::map<std::wstring, std::wstring> item_list)
{
    std::map<std::string, std::string> result = {};
    for (auto item : item_list)
    {
        std::string key = utf16_to_ansi(item.first);
        std::string value = utf16_to_ansi(item.second);

        result.insert(std::make_pair(key, value));
    }
    return result;
}

/**
 * @brief 转大写
 *
 * @param data
 * @return string
 */
std::string hmc_string_util::text_to_upper(std::string data)
{
    std::string Result;
    for (char &c : data)
    {
        if (std::isalpha(static_cast<std::uint8_t>(c)))
        {
            Result.push_back(std::toupper(c));
        }
        else
        {
            Result.push_back(c);
        }
    }
    return Result;
}

/**
 * @brief 转大写
 *
 * @param data
 * @return string
 */
std::wstring hmc_string_util::text_to_upper(std::wstring data)
{
    std::wstring Result;
    for (wchar_t &c : data)
    {
        if (std::isalpha(static_cast<wchar_t>(c)))
        {
            Result.push_back(std::toupper(c));
        }
        else
        {
            Result.push_back(c);
        }
    }
    return Result;
}

/**
 * @brief 转大写
 *
 * @param data
 * @return string
 */
std::string hmc_string_util::text_to_lower(std::string data)
{
    std::string Result;
    for (char &c : data)
    {
        if (std::isalpha(static_cast<std::uint8_t>(c)))
        {
            Result.push_back(std::tolower(c));
        }
        else
        {
            Result.push_back(c);
        }
    }
    return Result;
}

/**
 * @brief 转大写
 *
 * @param data
 * @return string
 */
std::wstring hmc_string_util::text_to_lower(std::wstring data)
{
    std::wstring Result;
    for (wchar_t &c : data)
    {
        if (std::isalpha(static_cast<wchar_t>(c)))
        {
            Result.push_back(std::tolower(c));
        }
        else
        {
            Result.push_back(c);
        }
    }
    return Result;
}

LPCSTR hmc_string_util::string_to_lpstr(std::string input, size_t *psize)
{

    std::string copy_input = std::string(input.begin(), input.end());

    copy_input.erase(std::remove(copy_input.begin(), copy_input.end(), '\0'),
                     copy_input.end());

    char *output = new char[copy_input.size() + sizeof(char)];

    for (size_t i = 0; i < copy_input.size(); i++)
    {
        char data = copy_input[i];
        output[i] = data;
    }
    const size_t end = copy_input.size();
    // 正好是 output-1 的位置
    output[end] = '\0';
    (*psize) = end;
    return output;
}

LPWSTR hmc_string_util::string_to_lpstr(std::wstring input, size_t *psize)
{

    std::wstring copy_input = std::wstring(input.begin(), input.end());

    copy_input.erase(std::remove(copy_input.begin(), copy_input.end(), L'\0'),
                     copy_input.end());

    wchar_t *output = new wchar_t[copy_input.size() + sizeof(wchar_t)];

    for (size_t i = 0; i < copy_input.size(); i++)
    {
        wchar_t data = copy_input[i];
        output[i] = data;
    }
    const size_t end = copy_input.size();
    // 正好是 output-1 的位置
    output[end] = L'\0';
    (*psize) = end;
    return output;
}

LPWSTR hmc_string_util::string_to_lpstr(std::vector<std::wstring> input_list, size_t *psize)
{

    std::wstring copy_input_list;

    const size_t count = input_list.size();

    size_t temp = 0;

    for (size_t i = 0; i < count; i++)
    {
        auto it = string_to_lpstr(input_list[i], &temp);
        copy_input_list.append(it);

        if (copy_input_list.back() != L'\0')
        {
            copy_input_list.push_back(L'\0');
        }
    }

    copy_input_list.push_back(L'\0');

    size_t len = copy_input_list.size();
    wchar_t *output = new wchar_t[len];

    for (size_t i = 0; i < len; i++)
    {
        output[i] = copy_input_list[i];
    }

    (*psize) = len;

    return output;
}

LPCSTR hmc_string_util::string_to_lpstr(std::vector<std::string> input_list, size_t *psize)
{

    std::string copy_input_list;

    const size_t count = input_list.size();

    size_t temp = 0;

    for (size_t i = 0; i < count; i++)
    {
        auto it = string_to_lpstr(input_list[i], &temp);
        copy_input_list.append(it);

        if (copy_input_list.back() != '\0')
        {
            copy_input_list.push_back('\0');
        }
    }

    copy_input_list.push_back('\0');

    size_t len = copy_input_list.size();
    char *output = new char[len];

    for (size_t i = 0; i < len; i++)
    {
        output[i] = copy_input_list[i];
    }

    (*psize) = len;

    return output;
}

LPCSTR hmc_string_util::string_to_lpstr(std::string input)
{
    size_t psize = 0;
    return string_to_lpstr(input, &psize);
}

LPWSTR hmc_string_util::string_to_lpstr(std::wstring input)
{

    size_t psize = 0;
    return string_to_lpstr(input, &psize);
}

std::wstring hmc_string_util::lpstr_to_string(LPWSTR input)
{

    std::wstring result = L"";
    if (input != nullptr)
    {
        LPWSTR current = input;
        while (*current != L'\0')
        {
            // 打印当前字符
            result.push_back(*current);
            // 指针移动到下一个字符
            current++;
        }
    }
    return result;
}

std::string hmc_string_util::lpstr_to_string(LPSTR input)
{

    std::string result = "";
    if (input != nullptr)
    {
        LPSTR current = input;
        while (*current != '\0')
        {
            // 打印当前字符
            result.push_back(*current);
            // 指针移动到下一个字符
            current++;
        }
    }
    return result;
}

std::wstring hmc_string_util::lpstr_to_string(LPWSTR input, int nBufSize, bool earlyTruncation)
{
    std::wstring result = L"";
    if (input == nullptr && nBufSize < 0)
        return result;
    // 预留\0位置
    // result.reserve(nBufSize + 1);
    result.reserve(nBufSize);
    result.resize(nBufSize);
    for (size_t i = 0; i < (size_t)nBufSize; i++)
    {
        wchar_t data = static_cast<wchar_t>(input[i]);
        if (earlyTruncation && data == L'\0')
        {
            break;
        }
        result[i] = data;
    }
    // result[result.size() - 1] = L'\0';
    return result;
}

std::string hmc_string_util::lpstr_to_string(LPSTR input, int nBufSize, bool earlyTruncation)
{
    std::string result = "";
    if (input == nullptr && nBufSize < 0)
        return result;
    // result.reserve(nBufSize + 1);
    result.reserve(nBufSize);
    result.resize(nBufSize);
    for (size_t i = 0; i < (size_t)nBufSize; i++)
    {
        char data = static_cast<char>(input[i]);
        if (earlyTruncation && data == '\0')
        {
            break;
        }
        result[i] = data;
    }
    // result[result.size() - 1] = '\0';
    return result;
}

/**
 * @brief 移除和结尾开头的空字符
 *
 * @param str
 * @return std::string
 */
std::string hmc_string_util::removeNullCharacters(std::string str, bool start, bool tail, bool all)
{

    std::string result = std::string();

    if (all)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            char data = result[i];
            if (data != '\0')
            {
                result.push_back(data);
            }
        }
        return result;
    }

    result.append(str);

    // 移除开头的空字符
    if (start)
    {

        while (!result.empty() && result.front() == '\0')
        {
            result.erase(0, 1);
        }
    }

    // 移除末尾的空字符
    if (tail)
    {
        while (!result.empty() && result.back() == '\0')
        {
            result.pop_back();
        }
    }

    return result;
}

std::wstring hmc_string_util::removeNullCharacters(std::wstring str, bool start, bool tail, bool all)
{

    std::wstring result = std::wstring();

    if (all)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            wchar_t data = result[i];
            if (data != L'\0')
            {
                result.push_back(data);
            }
        }
        return result;
    }

    result.append(str);

    // 移除开头的空字符
    if (start)
    {

        while (!result.empty() && result.front() == L'\0')
        {
            result.erase(0, 1);
        }
    }

    // 移除末尾的空字符
    if (tail)
    {
        while (!result.empty() && result.back() == L'\0')
        {
            result.pop_back();
        }
    }

    return result;
}

std::wstring hmc_string_util::removeNullCharactersAll(std::wstring str)
{
    return removeNullCharacters(str, false, false, true);
}

std::string hmc_string_util::removeNullCharactersAll(std::string str)
{
    return removeNullCharacters(str, false, false, true);
}

/**
 * @brief 一个空的json 数组文本
 *
 * @return string
 */
std::string hmc_string_util::vec_to_array_json()
{
    std::string result = std::string("[]");
    return result;
}

/**
 * @brief cpp内容数组转为json的array文本
 *
 * @tparam T
 * @param data_list
 * @return string
 */
std::wstring hmc_string_util::vec_to_array_json(std::vector<std::wstring> item_list)
{
    std::wstring result = std::wstring(L"[");

    for (size_t i = 0; i < item_list.size(); i++)
    {
        auto data = item_list[i];
        std::wstring output;
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

namespace hmc_string_util
{

    bool hmc_string_util::removeMatchCharPtr(std::wstring &input, const wchar_t match_char, hmc_string_util::IGNORE_NULL_CHAR_TYPE ignore = hmc_string_util::IGNORE_NULL_CHAR_TYPE::ALL_IGNORE)
    {
        bool result = false;

        size_t the_size = input.size();

        if (the_size == 0)
        {
            return false;
        }

        // 全部删除
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::ALL_IGNORE)
        {
            input.erase(std::remove(input.begin(), input.end(), match_char),
                        input.end());
            return the_size != input.size();
        }

        // 判断是否全是此字符
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::END_IGNORE || ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::START_IGNORE)
        {
            size_t length = input.size();
            bool is_all_match_char = true;

            for (size_t i = 0; i < length; i++)
            {
                wchar_t it = input[i];
                if (it != match_char)
                {
                    is_all_match_char = false;
                    break;
                }
            }

            if (is_all_match_char)
            {
                input.clear();
                return the_size != input.size();
            }
        }

        // 只删除开头
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::START_IGNORE)
        {

            size_t front_index = 0;
            size_t length = input.size();
            for (size_t i = 0; i < length; i++)
            {
                wchar_t it = input[i];
                if (i != 0 && it != match_char)
                {
                    front_index = i - 1;
                    break;
                }
            }

            if (front_index > 0)
            {
                input.erase(0, front_index);
            }

            return the_size != input.size();
        }

        // 只删除结尾
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::END_IGNORE)
        {

            size_t length = input.size();
            size_t end_index = length;

            for (size_t i = length - 1; i >= 0; i--)
            {
                wchar_t it = input[i];
                if (i != 0 && it != match_char)
                {
                    end_index = i + 1;
                    break;
                }
            }

            if (end_index < length)
            {
                input.erase(end_index, length);
            }

            return the_size != input.size();
        }

        // 只删除中间 并忽略开头结尾出现的
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::MIDDLE_IGNORE)
        {

            size_t length = input.size();
            // 开头结尾 都不等于此字符 删除全部此字符
            if (input.front() != match_char && input.back() != match_char)
            {
                input.erase(std::remove(input.begin(), input.end(), match_char),
                            input.end());
                return the_size != input.size();
            }
            // 新的开头
            size_t ready_front_index = 0;
            // 尾部需要忽略多少个字符
            size_t ready_end_size = 0;

            // 全部都是 match_char 应当拒绝处理
            if (input.size() <= ready_end_size + 1)
            {
                return the_size != input.size();
            }

            // 计算出开头
            if (input.front() == match_char)
            {
                for (size_t i = 0; i < length; i++)
                {
                    wchar_t it = input[i];
                    if (it != match_char)
                    {
                        ready_front_index = i;
                        break;
                    }
                }
            }

            // 计算出结尾
            if (input.front() == match_char)
            {
                for (size_t i = length - 1; i >= 0; i--)
                {
                    wchar_t it = input[i];
                    if (it != match_char)
                    {
                        break;
                    }
                    ready_end_size++;
                }
            }

            for (size_t i = ready_front_index; i < input.size(); i++)
            {

                // 结尾完成
                if (i + 1 > input.size() - ready_end_size)
                {
                    break;
                }

                if (input[i] == match_char)
                {
                    input.erase(i, 1);
                    i--;
                }
            }
        }

        return result;
    }

    std::wstring hmc_string_util::removeMatchChar(const std::wstring &Input_, const wchar_t match_char, hmc_string_util::IGNORE_NULL_CHAR_TYPE ignore = hmc_string_util::IGNORE_NULL_CHAR_TYPE::ALL_IGNORE)
    {
        std::wstring input = std::wstring(Input_.begin(), Input_.end());

        bool result = false;

        size_t the_size = input.size();

        if (the_size == 0)
        {
            return input;
        }

        // 全部删除
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::ALL_IGNORE)
        {
            input.erase(std::remove(input.begin(), input.end(), match_char),
                        input.end());
            return input;
        }

        // 判断是否全是此字符
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::END_IGNORE || ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::START_IGNORE)
        {
            size_t length = input.size();
            bool is_all_match_char = true;

            for (size_t i = 0; i < length; i++)
            {
                wchar_t it = input[i];
                if (it != match_char)
                {
                    is_all_match_char = false;
                    break;
                }
            }

            if (is_all_match_char)
            {
                input.clear();
                return input;
            }
        }

        // 只删除开头
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::START_IGNORE)
        {

            size_t front_index = 0;
            size_t length = input.size();
            for (size_t i = 0; i < length; i++)
            {
                wchar_t it = input[i];
                if (i != 0 && it != match_char)
                {
                    front_index = i - 1;
                    break;
                }
            }

            if (front_index > 0)
            {
                input.erase(0, front_index);
            }

            return input;
        }

        // 只删除结尾
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::END_IGNORE)
        {

            size_t length = input.size();
            size_t end_index = length;

            for (size_t i = length - 1; i >= 0; i--)
            {
                wchar_t it = input[i];
                if (i != 0 && it != match_char)
                {
                    end_index = i + 1;
                    break;
                }
            }

            if (end_index < length)
            {
                input.erase(end_index, length);
            }

            return input;
        }

        // 只删除中间 并忽略开头结尾出现的
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::MIDDLE_IGNORE)
        {

            size_t length = input.size();
            // 开头结尾 都不等于此字符 删除全部此字符
            if (input.front() != match_char && input.back() != match_char)
            {
                input.erase(std::remove(input.begin(), input.end(), match_char),
                            input.end());
                return input;
            }
            // 新的开头
            size_t ready_front_index = 0;
            // 尾部需要忽略多少个字符
            size_t ready_end_size = 0;

            // 全部都是 match_char 应当拒绝处理
            if (input.size() <= ready_end_size + 1)
            {
                return input;
            }

            // 计算出开头
            if (input.front() == match_char)
            {
                for (size_t i = 0; i < length; i++)
                {
                    wchar_t it = input[i];
                    if (it != match_char)
                    {
                        ready_front_index = i;
                        break;
                    }
                }
            }

            // 计算出结尾
            if (input.front() == match_char)
            {
                for (size_t i = length - 1; i >= 0; i--)
                {
                    wchar_t it = input[i];
                    if (it != match_char)
                    {
                        break;
                    }
                    ready_end_size++;
                }
            }

            for (size_t i = ready_front_index; i < input.size(); i++)
            {

                // 结尾完成
                if (i + 1 > input.size() - ready_end_size)
                {
                    break;
                }

                if (input[i] == match_char)
                {
                    input.erase(i, 1);
                    i--;
                }
            }
        }

        return input;
    }

    bool hmc_string_util::removeMatchCharPtr(std::string &input, const char match_char, hmc_string_util::IGNORE_NULL_CHAR_TYPE ignore = hmc_string_util::IGNORE_NULL_CHAR_TYPE::ALL_IGNORE)
    {
        bool result = false;

        size_t the_size = input.size();

        if (the_size == 0)
        {
            return false;
        }

        // 全部删除
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::ALL_IGNORE)
        {
            input.erase(std::remove(input.begin(), input.end(), match_char),
                        input.end());
            return the_size != input.size();
        }

        // 判断是否全是此字符
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::END_IGNORE || ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::START_IGNORE)
        {
            size_t length = input.size();
            bool is_all_match_char = true;

            for (size_t i = 0; i < length; i++)
            {
                char it = input[i];
                if (it != match_char)
                {
                    is_all_match_char = false;
                    break;
                }
            }

            if (is_all_match_char)
            {
                input.clear();
                return the_size != input.size();
            }
        }

        // 只删除开头
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::START_IGNORE)
        {

            size_t front_index = 0;
            size_t length = input.size();
            for (size_t i = 0; i < length; i++)
            {
                char it = input[i];
                if (i != 0 && it != match_char)
                {
                    front_index = i - 1;
                    break;
                }
            }

            if (front_index > 0)
            {
                input.erase(0, front_index);
            }

            return the_size != input.size();
        }

        // 只删除结尾
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::END_IGNORE)
        {

            size_t length = input.size();
            size_t end_index = length;

            for (size_t i = length - 1; i >= 0; i--)
            {
                char it = input[i];
                if (i != 0 && it != match_char)
                {
                    end_index = i + 1;
                    break;
                }
            }

            if (end_index < length)
            {
                input.erase(end_index, length);
            }

            return the_size != input.size();
        }

        // 只删除中间 并忽略开头结尾出现的
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::MIDDLE_IGNORE)
        {

            size_t length = input.size();
            // 开头结尾 都不等于此字符 删除全部此字符
            if (input.front() != match_char && input.back() != match_char)
            {
                input.erase(std::remove(input.begin(), input.end(), match_char),
                            input.end());
                return the_size != input.size();
            }
            // 新的开头
            size_t ready_front_index = 0;
            // 尾部需要忽略多少个字符
            size_t ready_end_size = 0;

            // 全部都是 match_char 应当拒绝处理
            if (input.size() <= ready_end_size + 1)
            {
                return the_size != input.size();
            }

            // 计算出开头
            if (input.front() == match_char)
            {
                for (size_t i = 0; i < length; i++)
                {
                    char it = input[i];
                    if (it != match_char)
                    {
                        ready_front_index = i;
                        break;
                    }
                }
            }

            // 计算出结尾
            if (input.front() == match_char)
            {
                for (size_t i = length - 1; i >= 0; i--)
                {
                    char it = input[i];
                    if (it != match_char)
                    {
                        break;
                    }
                    ready_end_size++;
                }
            }

            for (size_t i = ready_front_index; i < input.size(); i++)
            {

                // 结尾完成
                if (i + 1 > input.size() - ready_end_size)
                {
                    break;
                }

                if (input[i] == match_char)
                {
                    input.erase(i, 1);
                    i--;
                }
            }
        }

        return result;
    }

    std::string hmc_string_util::removeMatchChar(const std::string &Input_, const char match_char, hmc_string_util::IGNORE_NULL_CHAR_TYPE ignore = hmc_string_util::IGNORE_NULL_CHAR_TYPE::ALL_IGNORE)
    {
        std::string input = std::string(Input_.begin(), Input_.end());

        bool result = false;

        size_t the_size = input.size();

        if (the_size == 0)
        {
            return input;
        }

        // 全部删除
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::ALL_IGNORE)
        {
            input.erase(std::remove(input.begin(), input.end(), match_char),
                        input.end());
            return input;
        }

        // 判断是否全是此字符
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::END_IGNORE || ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::START_IGNORE)
        {
            size_t length = input.size();
            bool is_all_match_char = true;

            for (size_t i = 0; i < length; i++)
            {
                char it = input[i];
                if (it != match_char)
                {
                    is_all_match_char = false;
                    break;
                }
            }

            if (is_all_match_char)
            {
                input.clear();
                return input;
            }
        }

        // 只删除开头
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::START_IGNORE)
        {

            size_t front_index = 0;
            size_t length = input.size();
            for (size_t i = 0; i < length; i++)
            {
                char it = input[i];
                if (i != 0 && it != match_char)
                {
                    front_index = i - 1;
                    break;
                }
            }

            if (front_index > 0)
            {
                input.erase(0, front_index);
            }

            return input;
        }

        // 只删除结尾
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::END_IGNORE)
        {

            size_t length = input.size();
            size_t end_index = length;

            for (size_t i = length - 1; i >= 0; i--)
            {
                char it = input[i];
                if (i != 0 && it != match_char)
                {
                    end_index = i + 1;
                    break;
                }
            }

            if (end_index < length)
            {
                input.erase(end_index, length);
            }

            return input;
        }

        // 只删除中间 并忽略开头结尾出现的
        if (ignore == hmc_string_util::IGNORE_NULL_CHAR_TYPE::MIDDLE_IGNORE)
        {

            size_t length = input.size();
            // 开头结尾 都不等于此字符 删除全部此字符
            if (input.front() != match_char && input.back() != match_char)
            {
                input.erase(std::remove(input.begin(), input.end(), match_char),
                            input.end());
                return input;
            }
            // 新的开头
            size_t ready_front_index = 0;
            // 尾部需要忽略多少个字符
            size_t ready_end_size = 0;

            // 全部都是 match_char 应当拒绝处理
            if (input.size() <= ready_end_size + 1)
            {
                return input;
            }

            // 计算出开头
            if (input.front() == match_char)
            {
                for (size_t i = 0; i < length; i++)
                {
                    char it = input[i];
                    if (it != match_char)
                    {
                        ready_front_index = i;
                        break;
                    }
                }
            }

            // 计算出结尾
            if (input.front() == match_char)
            {
                for (size_t i = length - 1; i >= 0; i--)
                {
                    char it = input[i];
                    if (it != match_char)
                    {
                        break;
                    }
                    ready_end_size++;
                }
            }

            for (size_t i = ready_front_index; i < input.size(); i++)
            {

                // 结尾完成
                if (i + 1 > input.size() - ready_end_size)
                {
                    break;
                }

                if (input[i] == match_char)
                {
                    input.erase(i, 1);
                    i--;
                }
            }
        }

        return input;
    }

    bool hmc_string_util::diffNullCharacters(const std::wstring str1, const std::wstring str2, hmc_string_util::IGNORE_NULL_CHAR_TYPE Ignore = hmc_string_util::IGNORE_NULL_CHAR_TYPE::ALL_IGNORE)
    {
        std::wstring input_01 = std::wstring(str1.begin(), str1.end());
        input_01.reserve(input_01.size());
        std::wstring input_02 = std::wstring(str2.begin(), str2.end());
        input_02.reserve(input_02.size());

        hmc_string_util::removeMatchCharPtr(input_01, L'\0', Ignore);
        hmc_string_util::removeMatchCharPtr(input_02, L'\0', Ignore);
        if (input_01.size() != input_02.size())
        {
            return false;
        }

        const size_t length = input_01.size();
        for (size_t i = 0; i < length; i++)
        {
            const wchar_t it1 = input_01.at(i);
            const wchar_t it2 = input_02.at(i);

            if (it1 != it2)
            {
                return false;
            }
        }
        return true;
    }

    bool hmc_string_util::diffNullCharacters(const std::string str1, const std::string str2, hmc_string_util::IGNORE_NULL_CHAR_TYPE Ignore = hmc_string_util::IGNORE_NULL_CHAR_TYPE::ALL_IGNORE)
    {
        std::string input_01 = std::string(str1.begin(), str1.end());
        input_01.reserve(input_01.size());
        std::string input_02 = std::string(str2.begin(), str2.end());
        input_02.reserve(input_02.size());

        hmc_string_util::removeMatchCharPtr(input_01, '\0', Ignore);
        hmc_string_util::removeMatchCharPtr(input_02, '\0', Ignore);

        if (input_01.size() != input_02.size())
        {
            return false;
        }

        const size_t length = input_01.size();
        for (size_t i = 0; i < length; i++)
        {
            const char it1 = input_01.at(i);
            const char it2 = input_02.at(i);

            if (it1 != it2)
            {
                return false;
            }
        }
        return true;
    }

}

#if _HAS_CXX17

/**
 * @brief c内容转为json的value
 *
 * @tparam T
 * @tparam V
 * @param value
 * @return string
 */
template <typename T, typename V>
std::string hmc_string_util::to_json_value(T &value)
{
    std::string result = "";
    static_assert(
        std::is_integral<T>::value ||
            std::is_floating_point<T>::value ||
            std::is_same_v<char, T> ||
            std::is_same_v<char *, T> ||
            std::is_same_v<const char *, T> ||
            std::is_same_v<std::vector<V>, T> ||
            std::is_same_v<T, std::string>,
        "Unsupported type preset escape (不支持的类型预设转义)");

    // boolean
    if constexpr (std::is_same_v<T, bool>)
    {
        result.append((value ? "true" : "false"));
    }
    // number -> int
    else if constexpr (std::is_integral<T>::value)
    {
        result.append(std::to_string(value));
    }
    // number -> float
    else if constexpr (std::is_floating_point<T>::value)
    {
        result.append(std::to_string(value));
    }
    // array -> <any>[]
    else if constexpr (std::is_same<std::vector<V>, T>::value)
    {
        result.append(hmc_string_util::vec_to_array_json(value));
    }
    // string -> "<char*>"
    else if constexpr (std::is_same_v<char, T> || std::is_same_v<char *, T> || std::is_same_v<const char *, T> || std::is_same_v<T, std::string>)
    {
        result.append("\"");

        std::string output;
        for (char ch : static_cast<std::string>(value))
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
std::wstring hmc_string_util::map_to_jsonW(std::map<KEY, V> item_list)
{
    std::wstring result = L"{";

    static_assert(
        std::is_integral<KEY>::value ||
            std::is_floating_point<KEY>::value ||
            std::is_same_v<wchar_t, KEY> ||
            std::is_same_v<wchar_t *, KEY> ||
            std::is_same_v<const wchar_t *, KEY> ||
            std::is_same_v<KEY, std::wstring>,
        "Unsupported type preset escape (不支持的类型预设转义)");

    static_assert(
        std::is_integral<V>::value ||
            std::is_floating_point<V>::value ||
            std::is_same_v<wchar_t, V> ||
            std::is_same_v<wchar_t *, V> ||
            std::is_same_v<const wchar_t *, V> ||
            std::is_same_v<V, std::wstring>,
        "Unsupported type preset escape (不支持的类型预设转义)");
    size_t index = 0;

    for (auto item : item_list)
    {

        // 解析 key

        if constexpr (std::is_same_v<KEY, bool>)
        {
            result.append((item.first ? L"true" : L"false"));
        }
        // number -> int
        else if constexpr (std::is_integral<KEY>::value)
        {
            result.append(std::to_wstring(item.first));
        }
        // number -> float
        else if constexpr (std::is_floating_point<KEY>::value)
        {
            result.append(std::to_wstring(item.first));
        }

        else if constexpr (std::is_same_v<wchar_t, KEY> || std::is_same_v<wchar_t *, KEY> || std::is_same_v<const wchar_t *, KEY> || std::is_same_v<KEY, std::wstring>)
        {
            result.append(L"\"");

            std::wstring output;
            for (wchar_t ch : static_cast<std::wstring>(item.first))
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
            result.append(std::to_wstring(index));
        }

        result.push_back(L':');

        // result.append(hmc_string_util::to_json_value(item.second));

        if constexpr (std::is_same_v<V, bool>)
        {
            result.append((item.second ? L"true" : L"false"));
        }
        // number -> int
        else if constexpr (std::is_integral<V>::value)
        {
            result.append(std::to_wstring(item.second));
        }
        // number -> float
        else if constexpr (std::is_floating_point<V>::value)
        {
            result.append(std::to_wstring(item.second));
        }
        // string -> "<char*>"
        else if constexpr (std::is_same_v<wchar_t, V> || std::is_same_v<wchar_t *, V> || std::is_same_v<const wchar_t *, V> || std::is_same_v<V, std::wstring>)
        {
            result.append(L"\"");

            std::wstring output;
            for (wchar_t ch : static_cast<std::wstring>(item.second))
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
std::string hmc_string_util::map_to_jsonA(std::map<KEY, V> item_list)
{
    std::string result = "{";

    static_assert(
        std::is_integral<KEY>::value ||
            std::is_floating_point<KEY>::value ||
            std::is_same_v<char, KEY> ||
            std::is_same_v<char *, KEY> ||
            std::is_same_v<const char *, KEY> ||
            std::is_same_v<KEY, std::string>,
        "Unsupported type preset escape (不支持的类型预设转义)");

    size_t index = 0;

    for (auto item : item_list)
    {

        // 解析 key

        if constexpr (std::is_same_v<KEY, bool>)
        {
            result.append((item.first ? "true" : "false"));
        }
        // number -> int
        else if constexpr (std::is_integral<KEY>::value)
        {
            result.append(std::to_string(item.first));
        }
        // number -> float
        else if constexpr (std::is_floating_point<KEY>::value)
        {
            result.append(std::to_string(item.first));
        }
        //// array -> <any>[]
        // else if constexpr (is_same<std::vector<ARR_V>, KEY>::value)
        //{
        //     result.append(vec_to_array_json(value));
        // }
        //  string -> "<char*>"
        else if constexpr (std::is_same_v<char, KEY> || std::is_same_v<char *, KEY> || std::is_same_v<const char *, KEY> || std::is_same_v<KEY, std::string>)
        {
            result.append("\"");

            std::string output;
            for (char ch : static_cast<std::string>(item.first))
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
            result.append(std::to_string(index));
        }

        result.push_back(':');

        // result.append(hmc_string_util::to_json_value(item.second));

        if constexpr (std::is_same_v<V, bool>)
        {
            result.append((item.second ? "true" : "false"));
        }
        // number -> int
        else if constexpr (std::is_integral<V>::value)
        {
            result.append(std::to_string(item.second));
        }
        // number -> float
        else if constexpr (std::is_floating_point<V>::value)
        {
            result.append(to_string(item.second));
        }
        // string -> "<char*>"
        else if constexpr (std::is_same_v<char, V> || std::is_same_v<char *, V> || std::is_same_v<const char *, V> || std::is_same_v<V, std::string>)
        {
            result.append("\"");

            std::string output;
            for (char ch : static_cast<std::string>(item.second))
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

/**
 * @brief cpp内容数组转为json的array文本
 *
 * @tparam T
 * @param data_list
 * @return string
 */
template <typename T>
std::string hmc_string_util::vec_to_array_json_any(const std::vector<T> data_list)
{
    std::string result = "[";

    static_assert(
        std::is_integral<T>::value ||
            std::is_floating_point<T>::value ||
            std::is_same_v<char, T> ||
            std::is_same_v<char *, T> ||
            std::is_same_v<const char *, T> ||
            std::is_same_v<T, std::string>,
        "Unsupported type preset escape (不支持的类型预设转义)");

    for (size_t index = 0; index < data_list.size(); index++)
    {
        auto value = data_list[index];

        if constexpr (std::is_same_v<T, bool>)
        {
            result.append((value ? "true" : "false"));
        }
        else if constexpr (std::is_integral<T>::value)
        {
            result.append(std::to_string(value));
        }
        else if constexpr (std::is_floating_point<T>::value)
        {
            result.append(std::to_string(value));
        }
        else if constexpr (std::is_floating_point<T>::value)
        {
            result.append(std::to_string(value));
        }
        else if constexpr (std::is_same_v<char, T> || std::is_same_v<char *, T> || std::is_same_v<const char *, T> || std::is_same_v<T, std::string>)
        {
            result.append("\"");

            std::string output;
            for (char ch : static_cast<std::string>(value))
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

std::string hmc_string_util::vec_to_array_jsonA(std::vector<std::string> item_list)
{
    return vec_to_array_json_any(item_list);
}

std::string hmc_string_util::vec_to_array_json(std::vector<std::string> item_list)
{
    return vec_to_array_json_any(item_list);
}

std::string hmc_string_util::map_to_jsonA(std::any item_list)
{
    std::string result = "{";

    if (!item_list.has_value())
    {
        return "{}";
    }
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, std::string, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, char, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, char *, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, const char *, std::string);

    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, int, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, int64_t, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long long, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, int32_t, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, size_t, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, unsigned long, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long int, std::string);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, unsigned long, std::string);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, char, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, int64_t, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long long, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, int32_t, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, size_t, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, unsigned long, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long int, char);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, unsigned long, char);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, char, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, int64_t, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long long, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, int32_t, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, size_t, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, unsigned long, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long int, char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, unsigned long, char *);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, int64_t, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long long, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, int32_t, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, size_t, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, unsigned long, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, long int, const char *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonA, std::map, unsigned long, const char *);

    return "{}";
}

std::wstring hmc_string_util::map_to_jsonW(std::any item_list)
{

    if (!item_list.has_value())
    {
        return L"{}";
    }
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, std::wstring, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, wchar_t, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, wchar_t *, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, const wchar_t *, std::wstring);

    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, int, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, int64_t, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long long, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, int32_t, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, size_t, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, unsigned long, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long int, std::wstring);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, unsigned long, std::wstring);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, wchar_t, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, int64_t, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long long, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, int32_t, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, size_t, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, unsigned long, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long int, wchar_t);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, unsigned long, wchar_t);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, wchar_t, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, int64_t, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long long, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, int32_t, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, size_t, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, unsigned long, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long int, wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, unsigned long, wchar_t *);

    // string
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, int64_t, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long long, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, int32_t, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, size_t, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, unsigned long, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, long int, const wchar_t *);
    ___hmc_string_util_diff_any_value_eval_map_to_fn_map(item_list, map_to_jsonW, std::map, unsigned long, const wchar_t *);

    return L"{}";
}

bool hmc_string_util::is_map_json(std::any input)
{

    if (!input.has_value())
    {
        return false;
    }
    if (
        ___hmc_string_util_eqt(typeid(std::map<std::string, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char *, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<const char *, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<int, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<int64_t, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long long, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<int32_t, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<size_t, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<unsigned long, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long int, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<int64_t, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long long, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<int32_t, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<size_t, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<unsigned long, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long int, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<int64_t, char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long long, char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<int32_t, char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<size_t, char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<unsigned long, char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long, char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long int, char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<int64_t, const char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long long, const char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<int32_t, const char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<size_t, const char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<unsigned long, const char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long, const char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<long int, const char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, std::string>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, const char *>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, int>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, int64_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, long long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, int32_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, size_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, unsigned long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<std::string, long int>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, int64_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, long long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, int32_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, size_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, unsigned long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char, long int>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char *, char>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char *, int64_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char *, long long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char *, int32_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char *, size_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char *, unsigned long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char *, long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<char *, long int>)) ||
        ___hmc_string_util_eqt(typeid(std::map<const char *, int64_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<const char *, long long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<const char *, int32_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<const char *, size_t>)) ||
        ___hmc_string_util_eqt(typeid(std::map<const char *, unsigned long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<const char *, long>)) ||
        ___hmc_string_util_eqt(typeid(std::map<const char *, long int>)))
    {
        return true;
    }
    return false;
}

bool hmc_string_util::is_int(std::any input)
{

    if (!input.has_value())
    {
        return false;
    }
    if (
        ___hmc_string_util_eq(std::uint8_t) ||
        ___hmc_string_util_eq(unsigned int) ||
        ___hmc_string_util_eq(unsigned long) ||
        ___hmc_string_util_eq(unsigned long long) ||
        ___hmc_string_util_eq(int) ||
        ___hmc_string_util_eq(long long) ||
        ___hmc_string_util_eq(long))
    {
        return true;
    }
    return false;
}

bool hmc_string_util::is_vec_json(std::any input)
{

    if (!input.has_value())
    {
        return false;
    }
    if (
        ___hmc_string_util_eq(std::vector<char *>) ||
        ___hmc_string_util_eq(std::vector<std::uint8_t>) ||
        ___hmc_string_util_eq(std::vector<unsigned int>) ||
        ___hmc_string_util_eq(std::vector<unsigned long>) ||
        ___hmc_string_util_eq(std::vector<unsigned long>) ||
        ___hmc_string_util_eq(std::vector<unsigned long long>) ||
        ___hmc_string_util_eq(std::vector<int>) ||
        ___hmc_string_util_eq(std::vector<long>) ||
        ___hmc_string_util_eq(std::vector<short>) ||
        ___hmc_string_util_eq(std::vector<long double>) ||
        ___hmc_string_util_eq(std::vector<double>) ||
        ___hmc_string_util_eq(std::vector<std::string>) ||
        ___hmc_string_util_eq(std::vector<std::wstring>) ||
        ___hmc_string_util_eq(std::vector<wchar_t *>) ||
        ___hmc_string_util_eq(std::vector<wchar_t>))
    {
        return true;
    }
    return false;
}

bool hmc_string_util::any_to_string(std::any input, std::string &output)
{
    bool result = false;
#define Input(types) std::any_cast<types>(input)

    output.clear();

    if (input.type() == typeid(char *))
    {
        output.append(Input(char *));
        return true;
    }

    if (input.type() == typeid(std::string))
    {
        output.append(Input(std::string));
        return true;
    }

    if (input.type() == typeid(std::wstring))
    {
        output.append(utf16_to_ansi(Input(std::wstring)));
        return true;
    }

    if (input.type() == typeid(wchar_t *))
    {
        output.append(utf16_to_ansi(Input(wchar_t *)));
        return true;
    }

    if (input.type() == typeid(char))
    {
        output.push_back(std::any_cast<char>(input));
        return true;
    }

    if (input.type() == typeid(wchar_t))
    {
        std::wstring temp = std::wstring();
        temp.push_back(Input(wchar_t));
        output.append(utf16_to_ansi(temp));
        return true;
    }

#define ReturnToArrayA(types)                                                           \
    if (input.type() == typeid(types))                                                  \
    {                                                                                   \
        output.append(hmc_string_util::vec_to_array_json(std::any_cast<types>(input))); \
        return true;                                                                    \
    }

    ReturnToArrayA(std::vector<std::uint8_t>);
    // ReturnToArray(std::vector<unsigned wchar_t>);
    ReturnToArrayA(std::vector<unsigned int>);
    ReturnToArrayA(std::vector<unsigned long>);
    ReturnToArrayA(std::vector<unsigned long>);
    ReturnToArrayA(std::vector<unsigned long long>);

    ReturnToArrayA(std::vector<int>);
    ReturnToArrayA(std::vector<long>);
    ReturnToArrayA(std::vector<short>);
    ReturnToArrayA(std::vector<long double>);
    ReturnToArrayA(std::vector<double>);
    // ReturnToArray(std::vector<char *>);
    ReturnToArrayA(std::vector<std::string>);

    if (input.type() == typeid(std::vector<std::wstring>))
    {
        std::wstring data = hmc_string_util::vec_to_array_json(std::any_cast<std::vector<std::wstring>>(input));
        output.append(utf16_to_ansi(data));
        return true;
    }

    // 整数型
    if (is_int(input))
    {
        output.append(std::to_string(Input(unsigned long long)));
        return true;
    }

    // 浮点
    if (___hmc_string_util_eq(short) || ___hmc_string_util_eq(long double) || ___hmc_string_util_eq(double))
    {
        output.append(std::to_string(Input(long double)));
        return true;
    }

    if (is_map_json(input))
    {
        output.append(map_to_jsonA(input));
        return true;
    }

    return result;
}

bool hmc_string_util::any_to_string(std::any input, std::wstring &output)
{
    bool result = false;
#define Input(types) std::any_cast<types>(input)

    output.clear();

    if (input.type() == typeid(char *))
    {
        output.append(ansi_to_utf16(Input(char *)));
        return true;
    }

    if (input.type() == typeid(std::string))
    {
        output.append(ansi_to_utf16(Input(std::string)));
        return true;
    }

    if (input.type() == typeid(std::wstring))
    {
        output.append(Input(std::wstring));
        return true;
    }

    if (input.type() == typeid(wchar_t *))
    {
        output.append(Input(wchar_t *));
        return true;
    }

    if (input.type() == typeid(char))
    {
        output.push_back(std::any_cast<char>(input));
        return true;
    }

    if (input.type() == typeid(wchar_t))
    {
        std::wstring temp = std::wstring();
        temp.push_back(Input(wchar_t));
        output.append(temp);
        return true;
    }

#define ReturnToArrayW(types)                                                               \
    if (input.type() == typeid(types))                                                      \
    {                                                                                       \
        std::string temp = hmc_string_util::vec_to_array_json(std::any_cast<types>(input)); \
        output.append(ansi_to_utf16(temp));                                                 \
        return true;                                                                        \
    }

    ReturnToArrayW(std::vector<std::uint8_t>);
    // ReturnToArray(std::vector<unsigned wchar_t>);
    ReturnToArrayW(std::vector<unsigned int>);
    ReturnToArrayW(std::vector<unsigned long>);
    ReturnToArrayW(std::vector<unsigned long>);
    ReturnToArrayW(std::vector<unsigned long long>);

    ReturnToArrayW(std::vector<int>);
    ReturnToArrayW(std::vector<long>);
    ReturnToArrayW(std::vector<short>);
    ReturnToArrayW(std::vector<long double>);
    ReturnToArrayW(std::vector<double>);
    // ReturnToArray(std::vector<char *>);
    ReturnToArrayW(std::vector<std::string>);

    if (input.type() == typeid(std::vector<std::wstring>))
    {
        std::wstring data = hmc_string_util::vec_to_array_json(std::any_cast<std::vector<std::wstring>>(input));
        output.append(data);
        return true;
    }

    // 整数型
    if (is_int(input))
    {
        output.append(std::to_wstring(Input(unsigned long long)));
        return true;
    }

    // 浮点
    if (___hmc_string_util_eq(short) || ___hmc_string_util_eq(long double) || ___hmc_string_util_eq(double))
    {
        output.append(std::to_wstring(Input(long double)));
        return true;
    }

    if (is_map_json(input))
    {
        output.append(map_to_jsonW(input));
        return true;
    }

    return result;
}

std::wstring hmc_string_util::push_json_value(std::wstring key, std::any value, bool is_append, bool esp_type)
{
    std::wstring result;
    if (is_append)
    {
        result.append(L",");
    }
    result.append(hmc_string_util::escapeJsonString(key, true));
    result.append(L":");
    std::wstring output;

    if (any_to_string(value, output))
    {
        if (is_int(value))
        {
            result.append(output);
        }
        // else if (is)(value)) {

        //}
        else
        {
            result.append(hmc_string_util::escapeJsonString(output, (esp_type ? true : false)));
        }
    }
    else
    {
        result.append(hmc_string_util::escapeJsonString(L"undefined", false));
    }

    return result;
}

std::string hmc_string_util::vec_to_array_json(const std::vector<char> data_list)
{
    return vec_to_array_json_any(std::any_cast<std::vector<char>>(data_list));
}

std::string hmc_string_util::vec_to_array_json(const std::vector<double> data_list)
{
    return vec_to_array_json_any(std::any_cast<std::vector<double>>(data_list));
}
std::string hmc_string_util::vec_to_array_json(const std::vector<long double> data_list)
{
    return vec_to_array_json_any(std::any_cast<std::vector<long double>>(data_list));
}
std::string hmc_string_util::vec_to_array_json(const std::vector<short> data_list)
{
    return vec_to_array_json_any(std::any_cast<std::vector<short>>(data_list));
}
std::string hmc_string_util::vec_to_array_json(const std::vector<long> data_list)
{
    return vec_to_array_json_any(std::any_cast<std::vector<long>>(data_list));
}
std::string hmc_string_util::vec_to_array_json(const std::vector<int> data_list)
{
    return vec_to_array_json_any(std::any_cast<std::vector<int>>(data_list));
}
std::string hmc_string_util::vec_to_array_json(const std::vector<unsigned long long> data_list)
{
    return vec_to_array_json_any(std::any_cast<std::vector<unsigned long long>>(data_list));
}

std::string hmc_string_util::vec_to_array_json(const std::vector<unsigned int> data_list)
{
    return vec_to_array_json_any(std::any_cast<std::vector<unsigned int>>(data_list));
}

std::string hmc_string_util::vec_to_array_json(const std::vector<std::uint8_t> data_list)
{
    return vec_to_array_json_any(std::any_cast<std::vector<std::uint8_t>>(data_list));
}

std::string hmc_string_util::vec_to_array_json(const std::vector<unsigned long> data_list)
{

    return vec_to_array_json_any(std::any_cast<std::vector<unsigned long>>(data_list));
}

#endif //_HAS_CXX17

std::wstring hmc_string_util::getPathBaseName(const std::wstring &path)
{
    size_t lastSlashIndex = path.find_last_of(L"\\/");
    if (lastSlashIndex != std::wstring::npos)
    {
        return path.substr(lastSlashIndex + 1);
    }
    return path;
}

std::string hmc_string_util::getPathBaseName(const std::string &path)
{
    size_t lastSlashIndex = path.find_last_of("\\/");
    if (lastSlashIndex != std::string::npos)
    {
        return path.substr(lastSlashIndex + 1);
    }
    return path;
}

std::wstring hmc_string_util::unicodeStringToWString(UNICODE_STRING unicodeString)
{
    std::wstring result;
    if (unicodeString.Buffer)
    {
        result = std::wstring(unicodeString.Buffer, unicodeString.Length / sizeof(wchar_t));
    }
    return result;
}

std::string hmc_string_util::base64_encode(const std::string &input)
{
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string encoded_temp;

    if (input.empty())
    {
        return encoded_temp;
    }

    // 在Base64编码中，每3个字节的数据会编码为4个字符
    size_t base64_size = ((input.size() / 3) + 1) * 4 + 52;
    encoded_temp.reserve(base64_size);

    int i = 0;
    int j = 0;
    unsigned char array3[3];
    unsigned char array4[4];
    sizeof(unsigned char) == sizeof(char);

    for (char c : input)
    {
        array3[i++] = c;
        if (i == 3)
        {
            array4[0] = (array3[0] & 0xfc) >> 2;
            array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
            array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);
            array4[3] = array3[2] & 0x3f;

            for (int k = 0; k < 4; k++)
            {
                auto it = base64_chars[array4[k]];
                encoded_temp.push_back(it);
            }

            i = 0;
        }
    }

    if (i != 0)
    {
        for (int k = i; k < 3; k++)
            array3[k] = '\0';

        // 对照表
        array4[0] = (array3[0] & 0xfc) >> 2;
        array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
        array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);
        array4[3] = array3[2] & 0x3f;

        for (int k = 0; k < i + 1; k++)
        {
            auto it = base64_chars[array4[k]];
            encoded_temp.push_back(it);
        }

        //  尾部不足4的倍数 添加=
        while (i++ < 3)
        {
            encoded_temp.push_back('=');
        }
    }

    return std::string(encoded_temp.begin(), encoded_temp.end());
}

std::string hmc_string_util::base64_encode(const std::vector<std::uint8_t> &input)
{
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string output;

    if (input.empty())
    {
        return output;
    }

    // 在Base64编码中，每3个字节的数据会编码为4个字符
    size_t base64_size = ((input.size() / 3) + 1) * 4 + 52;
    output.reserve(base64_size);

    const unsigned char *bytes_to_encode = &input[0];
    unsigned int len = input.size();
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
            {
                const auto it = base64_chars[char_array_4[i]];
                output.push_back(it);
            }
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; (j < i + 1); j++)
        {
            const auto it = base64_chars[char_array_4[i]];
            output.push_back(it);
        }

        while ((i++ < 3))
        {
            output.push_back('=');
        }
    }

    return std::string(output.begin(), output.end());
}

#ifndef HMC_IMPORT_HMC_BYTE_UTIL_H
namespace hmc_string_util
{
std::vector<std::uint8_t> int32ToBytes(const std::uint32_t data)
{
    std::vector<std::uint8_t> bytes = std::vector<std::uint8_t>();
    bytes.reserve(4);
    bytes.push_back((data >> 24) & 0xFF);
    bytes.push_back((data >> 16) & 0xFF);
    bytes.push_back((data >> 8) & 0xFF);
    bytes.push_back(data & 0xFF);
    return bytes;
}

std::vector<std::uint8_t> wstringToBytes(const wchar_t &bytes_string)
{
    std::vector<std::uint8_t> buff = {};

    // utf32
    if (bytes_string >= 0x10FFFF)
    {
        std::uint32_t value = static_cast<std::uint32_t>(bytes_string);
        auto int32Bytes = int32ToBytes(value);

        for (size_t i = 0; i < int32Bytes.size(); i++)
        {
            buff.push_back(int32Bytes.at(i));
        }
    }
    else
    {

        // utf16
        std::uint16_t value = static_cast<std::uint16_t>(bytes_string);
        std::uint8_t partA = (std::uint8_t)((value & 0xFF00) >> 8);
        std::uint8_t partB = (std::uint8_t)(value & 0x00FF);
        buff.push_back(partA);
        buff.push_back(partB);
    }

    return buff;
}
}

#endif // HMC_IMPORT_HMC_BYTE_UTIL_H

std::string hmc_string_util::base64_encode(const std::wstring &input)
{
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string encoded_temp;

    if (input.empty())
    {
        return encoded_temp;
    }

    return std::string(encoded_temp.begin(), encoded_temp.end());
}