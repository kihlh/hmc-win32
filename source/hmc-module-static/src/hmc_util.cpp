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

// inline bool hmc_util::anyCast(std::any Data, std::wstring Output)
// {
//     bool result = false;

//     if (Data.has_value())
//     {
//         if (Data.type() != typeid(std::wstring))
//         {
//             auto temp = std::any_cast<std::wstring>(Data);
//             Output.clear();
//             Output.append(std::move(temp));
//             result = true;
//             return result;
//         }

//         //if (Data.type() != typeid(wchar_t *))
//         //{
//         //    auto temp = std::any_cast<wchar_t *>(Data);
//         //    Output.clear();
//         //    Output.append(temp);
//         //    result = true;
//         //    return result;
//         //}
//     }

//     return result;
// }

// inline bool hmc_util::anyCast(std::any Data, std::string Output)
// {
//     bool result = false;
//     if (Data.has_value())
//     {
//         if (Data.type() != typeid(std::string))
//         {
//             auto temp = std::any_cast<std::string>(Data);
//             Output.clear();
//             Output.append(std::move(temp));
//             result = true;
//             return result;
//         }

//         if (Data.type() != typeid(char *))
//         {
//             auto temp = std::any_cast<char *>(Data);
//             Output.clear();
//             Output.append(temp);
//             result = true;
//             return result;
//         }
//     }
//     return result;
// }

// #define HMC_any_Cast_EQ_TO_PTR_TEMP(EQ_T, TO_T)\
//     if (Data->type() != typeid(EQ_T))\
//     {\
//         Output = nullptr;\
//         auto temp = static_cast<TO_T>(std::any_cast<EQ_T>(Data));\
//         Output = temp;\
//         result = true;\
//         return result;\
// }

// inline bool hmc_util::anyCast(std::any *Data, size_t *Output)
// {
//     bool result = false;
//     if (Data->has_value())
//     {
//         if (Data->type() != typeid(size_t))
//         {
//             Output = nullptr;
//             auto temp = std::any_cast<size_t>(Data);
//             Output = temp;
//             result = true;
//             return result;
//         }

//         HMC_any_Cast_EQ_TO_PTR_TEMP(char, size_t*);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(int, size_t*);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(int64_t, size_t*);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(long long, size_t*);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(int32_t, size_t*);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(unsigned long, size_t*);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(long, size_t*);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(long int, size_t*);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(unsigned long, size_t*);

//     }
//     return result;
// }

// inline bool hmc_util::anyCast(std::any *Data, long long * Output)
// {
//     bool result = false;
//     if (Data->has_value())
//     {
//         if (Data->type() != typeid(long long))
//         {
//             Output = nullptr;
//             auto temp = std::any_cast<long long>(Data);
//             Output = temp;
//             result = true;
//             return result;
//         }

//         HMC_any_Cast_EQ_TO_PTR_TEMP(char, long long);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(int, long long);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(int64_t, long long);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(long long, long long);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(int32_t, long long);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(unsigned long, long long);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(long, long long);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(long int, long long);
//         HMC_any_Cast_EQ_TO_PTR_TEMP(unsigned long, long long);

//     }
//     return result;
// }

hmc_util::anyCastList::anyCastList(std::vector<std::any> *Data)
{
    m_data2 = Data;
}

/**
 * @brief 判断值是否存在
 *
 * @param index
 * @return true
 * @return false
 */
bool hmc_util::anyCastList::exists(size_t index)
{

    if (m_data2 == NULL || index >= m_data2->size())
    {
        return false;
    }
    return true;
}
/**
 * @brief 判断值是否存在
 *
 * @param index
 * @return true
 * @return false
 */
bool hmc_util::anyCastList::exists(size_t index, bool existsValue)
{

    if (m_data2 == NULL || index >= m_data2->size())
    {
        return false;
    }
    if (existsValue)
    {

        if (m_data2->at(index).has_value())
        {
            return true;
        }
        return false;
    }
    return true;
}

/**
 * @brief 取值
 *
 * @param index
 * @return std::any
 */
std::any hmc_util::anyCastList::get(size_t index)
{
    if (m_data2 == NULL || index >= m_data2->size())
    {
        return std::any();
    }
    return m_data2->at(index);
}

/**
 * @brief 取值
 *
 * @param index
 * @return std::any
 */
std::any hmc_util::anyCastList::get(size_t index, std::any orValue)
{

    std::any any_temp = get(index);
    if (any_temp.has_value())
    {
        return any_temp;
    }
    return orValue;
}

/**
 * @brief 删除指定元素
 *
 * @param Index
 * @return true
 * @return false
 */
bool hmc_util::anyCastList::removeIndex(size_t Index)
{

    if (m_data2 == NULL || Index >= m_data2->size())
    {
        return false;
    }
    m_data2->erase(m_data2->begin() + Index);
    return true;
}

/**
 * @brief 是否为空
 *
 * @return true
 * @return false
 */
bool hmc_util::anyCastList::empty()
{

    if (m_data2 == NULL || m_data2->empty())
    {
        return true;
    }
    return false;
}

/**
 * @brief 让两个位置的元素互换
 *
 * @param Index 索引1
 * @param Index2 索引2
 * @return true
 * @return false
 */
bool hmc_util::anyCastList::swap(size_t Index, size_t Index2)
{

    if (!m_data2)
    {
        return false;
    }

    if (Index >= m_data2->size() || Index2 >= m_data2->size())
    {
        return false;
    }
    std::swap(m_data2[Index], m_data2[Index2]);
    return true;
}

/**
 * @brief 替换指定的元素位置
 *
 * @param Index 索引
 * @param value 新的值
 * @return true
 * @return false
 */
bool hmc_util::anyCastList::replace(size_t Index, std::any value)
{

    if (!m_data2 || Index >= m_data2->size())
    {
        return false;
    }

    m_data2->at(Index) = value;

    return true;
}

/**
 * @brief 获取数量
 *
 * @return size_t
 */
size_t hmc_util::anyCastList::size()
{
    return m_data2 ? m_data2->size() : 0;
}

bool hmc_util::anyCastList::is_wstring(size_t index)
{
    if (m_data2 == NULL || index >= m_data2->size())
    {
        return false;
    }

    std::any *it = &m_data2->at(index);
    if (it->has_value())
    {
        if (typeid(std::wstring) == it->type() ||
            typeid(wchar_t *) == it->type())
        {
            return true;
        }
    }
    return false;
}

bool hmc_util::anyCastList::is_string(size_t index)
{
    if (m_data2 == NULL || index >= m_data2->size())
    {
        return false;
    }

    std::any *it = &m_data2->at(index);
    if (it->has_value())
    {
        if (typeid(std::string) == it->type() ||
            typeid(char *) == it->type())
        {
            return true;
        }
    }
    return false;
}

bool hmc_util::anyCastList::is_integral(size_t index)
{
    if (m_data2 == NULL || index >= m_data2->size())
    {
        return false;
    }

    std::any *it = &m_data2->at(index);
    if (it->has_value())
    {
        const std::type_info &ti = typeid(long long);

        if (typeid(int) == ti ||
            typeid(int64_t) == ti ||
            typeid(long long) == ti ||
            typeid(int32_t) == ti ||
            typeid(size_t) == ti ||
            typeid(unsigned long) == ti ||
            typeid(unsigned long long) == ti ||
            typeid(long) == ti ||
            typeid(long int) == ti ||
            typeid(unsigned char) == ti ||
            typeid(char) == ti ||
            typeid(wchar_t) == ti)
        {
            return true;
        }
    }
    return false;
}

bool hmc_util::anyCastList::is_floating_point(size_t index)
{
    if (m_data2 == NULL || index >= m_data2->size())
    {
        return false;
    }

    std::any *it = &m_data2->at(index);
    if (it->has_value())
    {
        if (typeid(short) == it->type() ||
            typeid(long double) == it->type() ||
            typeid(double) == it->type())
        {
            return true;
        }
    }
    return false;
}

const std::type_info &hmc_util::anyCastList::getTypeInfo(size_t index)
{
    const std::type_info &result = typeid(nullptr);

    if (m_data2 == NULL || index >= m_data2->size())
    {
        return result;
    }

    std::any *it = &m_data2->at(index);
    if (it->has_value())
    {
        const std::type_info &ti = it->type();
        return ti;
    }

    return result;
}

bool hmc_util::anyCastList::diffType(size_t index, const std::type_info &type)
{
    bool result = false;

    if (m_data2 == NULL || index >= m_data2->size())
    {
        return result;
    }

    std::any *it = &m_data2->at(index);
    if (it->has_value())
    {
        const std::type_info &ti = it->type();
        return ti == type;
    }

    return result;
}
