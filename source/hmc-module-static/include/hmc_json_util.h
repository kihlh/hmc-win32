#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_TEXT_JSON_UTIL_H
#define MODE_INTERNAL_INCLUDE_HMC_TEXT_JSON_UTIL_H

#define EPOCH_TIME UINT64_C(116444736000000000) // 1970.01.01 00:00:000 in MS Filetime

#include <string>

namespace hmc_json_util
{

    /**
     * @brief 转义到jsonValue
     *
     * @param value 如果为true 则加上 "
     * @return std::string
     */
    extern std::string toJsonValueA(const std::string &input, bool is_to_value = false);

    /**
     * @brief 转义到jsonValue
     *
     * @param value 如果为true 则加上 "
     * @return std::string
     */
    extern std::wstring toJsonValueW(const std::wstring &input, bool is_to_value = false);

    /**
     * @brief 缩进 json 文本
     *
     * @param json
     * @return std::wstring
     */
    std::wstring formatJson(const std::wstring &json);

    /**
     * @brief  缩进 json 文本
     *
     * @param json
     * @return std::string
     */
    std::string formatJson(const std::string &json);
}

#if _HAS_CXX17
#include <variant>
namespace hmc_json_util
{
    typedef std::variant<
        // std
        std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t,
        // >= 32bit
        char, wchar_t, char16_t, char32_t, int, int64_t, int32_t,
        // >= 64bit
        long long, size_t, long int, long, long long int,
        // unsigned
        unsigned char, unsigned long, unsigned long long int,
        // short
        short, long double, double, float>
        NumberType;

    /**
     * @brief 转义到jsonValue
     *
     * @param value
     * @return std::string
     */
    extern std::string toJsonValueA(NumberType value);

    /**
     * @brief 转义到jsonValue
     *
     * @param value
     * @return std::string
     */
    extern std::wstring toJsonValueW(NumberType value);
}
#endif // _HAS_CXX17

#endif // MODE_INTERNAL_INCLUDE_HMC_TEXT_JSON_UTIL_H