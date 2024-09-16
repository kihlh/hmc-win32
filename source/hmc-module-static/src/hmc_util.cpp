#include "./hmc_util.h"

inline size_t hmc_util::removeAllCharPtr(std::wstring &input, wchar_t matching)
{
    size_t replacementFrequency = 0;

    auto end_pos = input.size();
    while ((end_pos = input.find_last_not_of(matching)) != input.size() - 1)
    {
        input.erase(end_pos + 1);
        replacementFrequency++;
    }

    return replacementFrequency;
}

inline size_t hmc_util::removeAllCharPtr(std::string &input, char matching)
{
    size_t replacementFrequency = 0;

    auto end_pos = input.size();
    while ((end_pos = input.find_last_not_of(matching)) != input.size() - 1)
    {
        input.erase(end_pos + 1);
        replacementFrequency++;
    }

    return replacementFrequency;
}

inline void hmc_util::replaceAll(std::string &sourcePtr, const std::string from, const std::string to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

inline void hmc_util::replaceAll(std::wstring &sourcePtr, const std::wstring from, const std::wstring to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

inline void hmc_util::replace(std::string &sourcePtr, const std::string from, const std::string to)
{
    size_t start_pos = 0;
    if ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        return;
    }
}

inline void hmc_util::replace(std::wstring &sourcePtr, const std::wstring from, const std::wstring to)
{
    size_t start_pos = 0;
    if ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        return;
    }
}

inline std::string hmc_util::escapeJsonString(const std::string &input, bool is_to_value)
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

inline std::wstring hmc_util::escapeJsonString(const std::wstring &input, bool is_to_value)
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

inline std::wstring hmc_util::asciiConvers(std::string input)
{
    std::wstring result = std::wstring();

    result.reserve(input.size());

    for (auto &&item : input)
    {
        if (127 >= item && item >= 0)
        {
            result.push_back(static_cast<wchar_t>(item));
        }
    }

    return result;
}

inline std::string hmc_util::asciiConvers(std::wstring input)
{
    std::string result = std::string();
    result.reserve(input.size());

    for (auto &&item : input)
    {
        if (127 >= item && item >= 0)
        {
            result.push_back(static_cast<char>(item));
        }
    }

    return result;
}

inline std::wstring hmc_util::vec2ar(std::vector<std::wstring> input)
{
    std::wstring result = std::wstring();

    size_t buff_size = MAX_PATH;

    size_t count = input.size();
    for (size_t i = 0; i < count; i++)
    {
        auto it = &input[i];
        buff_size += it->size();
    }

    result.reserve(buff_size);

    result.push_back(L'[');

    count = input.size();
    for (size_t i = 0; i < count; i++)
    {
        auto it = &input[i];
        result.append(it->begin(), it->end());
        if (i + 1 < count)
        {
            result.push_back(L',');
        }
    }

    result.push_back(L']');
    return result;
}

inline std::string hmc_util::vec2ar(std::vector<std::string> input)
{
    std::string result = std::string();

    DWORD buff_size = MAX_PATH;

    int count = static_cast<int>(input.size());

    for (int i = 0; i < count; i++)
    {
        auto it = &input[i];
        buff_size += static_cast<int>(it->size());
    }

    result.reserve(buff_size);

    result.push_back('[');

    count = static_cast<int>(input.size());
    for (int i = 0; i < count; i++)
    {
        auto it = &input[i];
        result.append(it->begin(), it->end());
        if (i + 1 < count)
        {
            result.push_back(',');
        }
    }

    result.push_back(']');

    return result;
}

inline bool hmc_util::is_utf8(const std::string input)
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

unsigned long hmc_util::toThreadId(std::thread::id thread_id)
{
    unsigned long ThreadIdAsInt = 0;

    try
    {
        ThreadIdAsInt = *static_cast<unsigned long *>(static_cast<void *>(&thread_id));
    }
    catch (...)
    {
        auto data = std::hash<std::thread::id>()(thread_id);
        ThreadIdAsInt = static_cast<unsigned long>(data);
    }

    return ThreadIdAsInt;
}

std::string hmc_util::getBaseName(const std::string path)
{
    std::string result = std::string();

    int length = static_cast<int>(path.size());

    for (int i = length - 1; i >= 0; i--)
    {
        auto it = path.at(i);

        if (it == '\\' || it == '/')
        {
            break;
        }

        result.insert(0, 1, it);
    }

    return result;
}

std::wstring hmc_util::getBaseName(const std::wstring path)
{
    std::wstring result = std::wstring();

    int length = static_cast<int>(path.size());

    for (int i = length - 1; i >= 0; i--)
    {
        auto it = path.at(i);

        if (it == '\\' || it == '/')
        {
            break;
        }

        result.insert(0, 1, it);
    }

    return result;
}

bool hmc_util::diffBaseName(const std::string path1, const std::string path2)
{
    bool result = false;
    std::vector<std::string> baseNameList;
    baseNameList.push_back(std::string(path1.end(), path1.end()));
    baseNameList.push_back(std::string(path2.end(), path2.end()));

    return result;
}

bool hmc_util::diffBaseName(const std::wstring path1, const std::wstring path2)
{
    bool result = false;
    std::vector<std::wstring> baseNameList;
    baseNameList.push_back(std::wstring(path1.end(), path1.end()));
    baseNameList.push_back(std::wstring(path2.end(), path2.end()));

    return result;
}
