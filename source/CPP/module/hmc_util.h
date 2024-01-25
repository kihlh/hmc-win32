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

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

#ifndef _WINTERNL_
typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING;
#endif // _WINTERNL_

namespace hmc_util
{
    namespace hmc_define_util
    {
        // 自动释放dll
#define hmc_shared_close_Library(hModule) std::shared_ptr<void>##hModule##_shared_close_Library_(nullptr, [&](void *) {if (hModule != NULL) {::FreeLibrary(hModule);} });
// 自动释放文本
#define hmc_shared_close_lpsz(lpwsz) std::shared_ptr<void>##lpwsz##_shared_close_lpsz_(nullptr, [&](void *) {if (lpwsz != NULL) {::GlobalFree(lpwsz);lpwsz = 0; } });
// 释放进程句柄
#define hmc_shared_close_handle(handle) std::shared_ptr<void>##lpwsz##_shared_free_handle(nullptr, [&](void *) {if (handle != NULL) { try{::CloseHandle(handle);}catch(...){}} });

// 开辟内存 (请注意需要调用 FreeVS 或者 hmc_FreeVSAuto 释放)
// -> LPSTR pszMem = AllocVS(LPSTR, leng + 1);
#define hmc_AllocVS(Type, leng) \
    (Type)::VirtualAlloc((LPVOID)NULL, (DWORD)(leng), MEM_COMMIT, PAGE_READWRITE);

// 释放空间
// -> LPSTR pszMem = hmc_AllocVS(LPSTR, leng + 1);
// -> FreeVS(pszMem);
#define hmc_FreeVS(Virtua) \
    if (Virtua != NULL)    \
        ::VirtualFree(Virtua, 0, MEM_RELEASE);

// 释放空间
// -> LPSTR pszMem = hmc_AllocVS(LPSTR, leng + 1);
// -> FreeVSAuto(pszMem);
#define hmc_FreeVSAuto(Virtua) \
    std::shared_ptr<void>##Virtua##_shared_close_FreeVSAuto_(nullptr, [&](void *) {if (Virtua != NULL) {::VirtualFree(Virtua, 0, MEM_RELEASE);} });

// 开辟内存
#define hmc_AllocHeap(variable) ::HeapAlloc(::GetProcessHeap(), 0, (variable))
// 释放内存
#define hmc_FreeHeap(variable) ::HeapFree(::GetProcessHeap(), 0, (variable))

// 让代码在异步线程中执行
#define hmc_Thread (code) std::thread([]() -> void { code }).detach();
    }

    /**
     * @brief 删除指定的字符
     *
     * @param input 输入
     * @param matching 匹配的字符
     * @return size_t
     */
    extern size_t removeAllCharPtr(std::wstring &input, wchar_t matching);

    /**
     * @brief 删除指定的字符
     *
     * @param input 输入
     * @param matching 匹配的字符
     * @return size_t
     */
    extern size_t removeAllCharPtr(std::string &input, char matching);

    /**
     * @brief 替换指定文本
     *
     * @param sourcePtr 源文本
     * @param from 查找内容
     * @param to 替换到
     */
    extern void replace(std::wstring &sourcePtr, const std::wstring from, const std::wstring to);

    /**
     * @brief 替换指定文本
     *
     * @param sourcePtr 源文本
     * @param from 查找内容
     * @param to 替换到
     */
    extern void replace(std::string &sourcePtr, const std::string from, const std::string to);

    /**
     * @brief 替换指定文本 全部
     *
     * @param sourcePtr 源文本
     * @param from 查找内容
     * @param to 替换到
     */
    extern void replaceAll(std::wstring &sourcePtr, const std::wstring from, const std::wstring to);

    /**
     * @brief 替换指定文本 全部
     *
     * @param sourcePtr 源文本
     * @param from 查找内容
     * @param to 替换到
     */
    extern void replaceAll(std::string &sourcePtr, const std::string from, const std::string to);

    /**
     * @brief 转义json文本
     *
     * @param input 内容
     * @param is_to_value 如果為true 請加上"
     * @return std::wstring
     */
    extern std::wstring escapeJsonString(const std::wstring &input, bool is_to_value = false);

    /**
     * @brief 转义json文本
     *
     * @param input 内容
     * @param is_to_value 如果為true 請加上"
     * @return std::wstring
     */
    extern std::string escapeJsonString(const std::string &input, bool is_to_value = false);

    /**
     * @brief Nt文本轉爲寬文本
     * 
     * @param unicodeString 
     * @return std::wstring 
     */
    extern std::wstring unicodeStringToWString(UNICODE_STRING unicodeString);
}

#endif // MODE_INTERNAL_INCLUDE_HMC_UTIL_HPP