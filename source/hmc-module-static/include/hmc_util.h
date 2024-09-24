/**
 * @file hmc_util.h
 * @author kiic，kihlh
 * @brief 本模块是高频调用的函数的方法合集 要求 轻且快
 * @version 0.1
 * @date 2024-01-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_UTIL_HPP
#define MODE_INTERNAL_INCLUDE_HMC_UTIL_HPP

#include <vector>
#include <string>
#include <thread>
#include <windows.h>

// 自动释放dll
#ifndef HMC_FreeLibraryAuto
#define HMC_FreeLibraryAuto(hModule) \
    std::shared_ptr<void>##hModule##_shared_close_Library_(nullptr, [&](void *) {\
    try\
    {\
        if (hModule != NULL) {::FreeLibrary(hModule);}\
    }\
    catch(...){} });
#endif // HMC_FreeLibraryAuto

// 自动释放Handle
#ifndef HMC_FreeHandleAuto
#define HMC_FreeHandleAuto(hModule) \
    std::shared_ptr<void>##hModule##_shared_close_Handle_(nullptr, [&](void *) {\
    try\
    {\
        if (hModule != NULL) {::CloseHandle(hModule);}\
    }\
    catch(...){} });
#endif // HMC_FreeHandleAuto

// 释放vc内存开辟
#ifndef HMC_VcFree
#define HMC_VcFree(Virtua) \
    if (Virtua != NULL)    \
        ::VirtualFree(Virtua, 0, MEM_RELEASE);
#endif // HMC_VcFree

#ifndef HMC_VcAlloc
#define HMC_VcAlloc(Type, leng) \
    (reinterpret_cast<Type>(::VirtualAlloc(nullptr, static_cast<DWORD>(leng), MEM_COMMIT, PAGE_READWRITE)))
#endif // HMC_VcAlloc

#ifndef HMC_VcAllocAutoLength
#define HMC_VcAllocAutoLength(Type) \
    (reinterpret_cast<Type *>(::VirtualAlloc(nullptr, static_cast<DWORD>(sizeof(Type)), MEM_COMMIT, PAGE_READWRITE)))
#endif // HMC_VcAllocAutoLength

// 自动释放内存
#ifndef HMC_VcFreeAuto
#define HMC_VcFreeAuto(Virtua) \
    std::shared_ptr<void>##Virtua##_shared_close_FreeVSAuto_(nullptr, [&](void *) {if (Virtua != NULL) {::VirtualFree(Virtua, 0, MEM_RELEASE);} });
#endif // VsFreeAuto

// 自动释放 注册表key
#ifndef HMC_FreeRegKeyAuto
// 关闭注册表键
#define HMC_FreeRegKeyAuto(subHKey) \
    std::shared_ptr<void>##subHKey##_shared_close_Library_(nullptr, [&](void *) {\
    try\
    {\
        if (subHKey != nullptr) {\
            ::RegCloseKey(subHKey);\
        subHKey = nullptr;}\
    }\
    catch(...){} });
#endif // HMC_FreeRegKeyAuto

// 自动释放 自定义释放
#ifndef HMC_FreeAnyAuto
// 自动释放 自定义释放
#define HMC_CONCAT_IMPL(x, y) x##y
#define HMC_CONCAT(x, y) HMC_CONCAT_IMPL(x, y)

#define HMC_FreeAnyAuto(code) \
    std::shared_ptr<void> HMC_CONCAT(_Shared_close_Library, __LINE__)(nullptr, [&](void *) {\
    try\
    {\
       code\
    }\
    catch(...){} });
#endif // HMC_FreeAnyAuto

// 自动释放 自定义释放
#ifndef HMC_CATCH_ALL
#define HMC_CATCH_ALL catch (...){};
#endif // HMC_FreeAnyAuto

namespace hmc_util
{

    /**
     * @brief 删除指定的字符
     *
     * @param input 输入
     * @param matching 匹配的字符
     * @return size_t
     */
    extern inline size_t removeAllCharPtr(std::wstring &input, wchar_t matching);

    /**
     * @brief 删除指定的字符
     *
     * @param input 输入
     * @param matching 匹配的字符
     * @return size_t
     */
    extern inline size_t removeAllCharPtr(std::string &input, char matching);

    /**
     * @brief 替换指定文本
     *
     * @param sourcePtr 源文本
     * @param from 查找内容
     * @param to 替换到
     */
    extern inline void replace(std::wstring &sourcePtr, const std::wstring from, const std::wstring to);

    /**
     * @brief 替换指定文本
     *
     * @param sourcePtr 源文本
     * @param from 查找内容
     * @param to 替换到
     */
    extern inline void replace(std::string &sourcePtr, const std::string from, const std::string to);

    /**
     * @brief 替换指定文本 全部
     *
     * @param sourcePtr 源文本
     * @param from 查找内容
     * @param to 替换到
     */
    extern inline void replaceAll(std::wstring &sourcePtr, const std::wstring from, const std::wstring to);

    /**
     * @brief 替换指定文本 全部
     *
     * @param sourcePtr 源文本
     * @param from 查找内容
     * @param to 替换到
     */
    extern inline void replaceAll(std::string &sourcePtr, const std::string from, const std::string to);

    /**
     * @brief 转义json文本
     *
     * @param input 内容
     * @param is_to_value 如果為true 請加上"
     * @return std::wstring
     */
    extern inline std::wstring escapeJsonString(const std::wstring &input, bool is_to_value = false);

    /**
     * @brief 转义json文本
     *
     * @param input 内容
     * @param is_to_value 如果為true 請加上"
     * @return std::wstring
     */
    extern inline std::string escapeJsonString(const std::string &input, bool is_to_value = false);

    /**
     * @brief 宽窄文本转码 但是仅限于ascii
     *
     * @param input
     * @return std::wstring
     */
    extern inline std::wstring asciiConvers(std::string input);

    /**
     * @brief 宽窄文本转码 但是仅限于ascii
     *
     * @param input
     * @return std::wstring
     */
    extern inline std::string asciiConvers(std::wstring input);

    /**
     * @brief 拼接文本对象进json
     *
     * @param input
     * @return std::wstring
     */
    extern inline std::wstring vec2ar(std::vector<std::wstring> input);

    /**
     * @brief 拼接文本对象进json
     *
     * @param input
     * @return std::string
     */
    extern inline std::string vec2ar(std::vector<std::string> input);

    extern inline bool is_utf8(const std::string input);

    /**
     * @brief 线程id转为数字id
     *
     * @param thread_id
     * @return DWORD
     */
    extern unsigned long toThreadId(std::thread::id thread_id);
    std::string getBaseName(const std::string path);
    std::wstring getBaseName(const std::wstring path);

    bool diffBaseName(const std::string path1, const std::string path2);
    bool diffBaseName(const std::wstring path1, const std::wstring path2);

}

#if _HAS_CXX17
#include <variant>
#include <optional>
#include <map>
#include <any>

namespace hmc_util
{
    extern inline bool anyCast(std::any Data, std::wstring Output);
    extern inline bool anyCast(std::any Data, std::string Output);
    extern inline bool anyCast(std::any Data, size_t *Output);
    extern inline bool anyCast(std::any Data, long long *Output);

    class anyCastList
    {
    public:
        std::vector<std::any> *m_data2;

        anyCastList(std::vector<std::any> *Data)
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
        bool exists(size_t index)
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
        bool exists(size_t index, bool existsValue)
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
        std::any get(size_t index)
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
        std::any get(size_t index, std::any orValue)
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
        bool removeIndex(size_t Index)
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
        bool empty()
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
        bool swap(size_t Index, size_t Index2)
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
        bool replace(size_t Index, std::any value)
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
        size_t size()
        {
            return m_data2 ? m_data2->size() : 0;
        }
    };

}

#endif // _HAS_CXX17

template <typename T>
class VcRef
{

public:
    VcRef()
    {
        m_data = reinterpret_cast<T *>(::VirtualAlloc(nullptr, sizeof(T), MEM_COMMIT, PAGE_READWRITE));

        if (m_data != NULL)
        {
            m_size = sizeof(T);
            is_data = true;
        }
    }

    VcRef(std::size_t size)
    {
        m_data = reinterpret_cast<T *>(::VirtualAlloc(nullptr, size, MEM_COMMIT, PAGE_READWRITE));

        if (m_data != NULL)
        {
            m_size = size;
            is_data = true;
        }
    }

    // 只增不减的内存
    bool reserve(std::size_t size)
    {
        bool is_ok = false;

        if (size <= m_size)
        {
            return is_ok;
        }

        release();
        if (size > 0)
        {
            m_data = reinterpret_cast<T *>(::VirtualAlloc(nullptr, size, MEM_COMMIT, PAGE_READWRITE));
            is_data = true;
            m_size = size;
            is_ok = true;
        }

        return is_ok;
    }

    // 调整内存块大小
    bool resize(std::size_t size)
    {
        bool is_ok = false;

        if (size > 0 && size == m_size)
        {
            return is_ok;
        }

        release();
        if (size > 0)
        {
            m_data = reinterpret_cast<T *>(::VirtualAlloc(nullptr, size, MEM_COMMIT, PAGE_READWRITE));
            is_data = true;
            m_size = size;
            is_ok = true;
        }

        return is_ok;
    }

    size_t size()
    {
        return m_size;
    }

    void release()
    {

        if (is_data || m_data != NULL)
        {

            if (!::VirtualFree(m_data, 0, MEM_RELEASE))
            {
                ::Sleep(5);
                ::VirtualFree(m_data, 0, MEM_RELEASE);
                is_data = false;
            }

            is_data = false;
            m_size = 0;
        }

        is_data = false;
        m_size = 0;
    }

    T *data() const { return m_data; }

    // if
    operator bool() const
    {
        return is_data || reinterpret_cast<void *>(m_data) != nullptr;
    }

    // *
    operator T *() const
    {
        return m_data;
    }

    // &
    operator T &() const
    {
        return m_data;
    }

    // !
    bool operator!() const
    {
        return !is_data || reinterpret_cast<void *>(m_data) == nullptr;
    }

    T *operator->() const
    {
        return m_data;
    }

    ~VcRef()
    {
        release();
    }

private:
    bool is_data = false;
    size_t m_size = 0;
    T *m_data;
};

#endif // MODE_INTERNAL_INCLUDE_HMC_UTIL_HPP