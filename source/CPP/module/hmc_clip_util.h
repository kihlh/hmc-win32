#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_CLIP_UTIL_H
#define MODE_INTERNAL_INCLUDE_HMC_CLIP_UTIL_H

#include <windows.h>
#include <vector>
#include <string>
#include <Shlobj.h>
#include <memory>

namespace hmc_clip_util
{

    // 写入剪贴板文本
    extern bool SetClipboardText(std::wstring text);
    // 写入剪贴板文本
    extern bool SetClipboardText(std::string text);
    // 获取剪贴板文本
    extern std::wstring GetClipboardTextW();
    // 获取剪贴板文本
    extern std::string GetClipboardTextA();
    // 设置剪贴板文件列表
    extern bool SetClipboardPathList(const std::vector<std::string> &PathList);
    // 设置剪贴板文件列表
    extern bool SetClipboardPathList(const std::vector<std::wstring> &PathList);
    // 获取剪贴板中的文件列表
    extern std::vector<std::string> GetClipboardPathListA();
    // 获取剪贴板中的文件列表
    extern std::vector<std::wstring> GetClipboardPathListW();
    // 清空剪贴板
    extern bool ClearClipboard();
    // 获取当前剪贴板内容唯一id
    extern DWORD GetClipboardSequenceID();
    // 枚举剪贴板中的格式列表
    extern std::vector<UINT> EnumClipboardFormatList();
    // 剪贴板中的格式转文本
    extern std::wstring GetClipboardFormatNameW(UINT format);
    // 剪贴板中的格式转文本
    extern std::string GetClipboardFormatNameA(UINT format);
    // 判断剪贴板里面是否有图片
    extern bool HasClipboardImage();
    // 判断格式是否有效
    extern bool isFormatAvailable(UINT uCF);

    // 获取剪贴板的html文本
    class GetClipboardHtml
    {
    public:
        struct chClipHtmlItem
        {
            bool is_valid;
            std::string data;
            float Version;
            int StartHTML;
            int EndHTML;
            int StartFragment;
            int EndFragment;
            std::string SourceURL;
        };
        GetClipboardHtml(HWND hWnd);
        GetClipboardHtml();
        // 判断内容是否有效
        bool isHtml();
        // 获取内容
        chClipHtmlItem getHtmlItem();
        static void lib_rp_setw_10(std::string &sourcePtr, std::string from, size_t len);

    private:
        std::string SourceData;
        bool is_valid = false;
        float Version = 0.9f;
        int StartHTML = 0;
        int EndHTML = 0;
        int StartFragment = 0;
        int EndFragment = 0;
        std::string SourceURL;
        bool ParsingHtml();
        size_t html_indexof(std::string name);
    };

    // 写入html文本到剪贴板 必须是utf8编码
    extern bool SetClipboardHtml(const std::string &text, const std::string SourceURL = "");

    struct chClipInfo
    {
        HWND hwnd;
        DWORD id;
        std::vector<UINT> format;
        UINT formatCount;
    };

    chClipInfo GetClipboardInfo();
}

#endif // MODE_INTERNAL_INCLUDE_HMC_CLIP_UTIL_H
