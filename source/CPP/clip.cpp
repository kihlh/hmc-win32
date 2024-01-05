#include "./Mian.hpp";

#include <windows.h>
#include <vector>
#include <string>
#include <Shlobj.h>

namespace clip_util
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

clip_util::chClipInfo clip_util::GetClipboardInfo()
{
    clip_util::chClipInfo result;
    result.hwnd = ::GetClipboardOwner();
    result.format = EnumClipboardFormatList();
    result.formatCount = ::CountClipboardFormats();
    result.id = ::GetClipboardSequenceNumber();
    return result;
}

void clip_util::GetClipboardHtml::lib_rp_setw_10(std::string &sourcePtr, std::string from, size_t len)
{
    std::string result;

    char temp[11];
    sprintf_s(temp, 11, "%010u", len);

    result.append(temp);

    size_t start_pos = 0;
    if ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), std::string(temp));
    }
}

bool clip_util::SetClipboardHtml(const std::string &html, const std::string SourceURL)
{

    bool result = false;

    size_t html_len = html.size();

    std::string temp_clip_input;
    temp_clip_input.reserve(html_len + 512);

    // 制作html数据体
    // 标准见 https://learn.microsoft.com/zh-cn/windows/win32/dataxchg/html-clipboard-format

    temp_clip_input.append("Version:0.9\r\n");
    temp_clip_input.append("StartHTML:A000000000\r\n");
    temp_clip_input.append("EndHTML:B000000000\r\n");
    temp_clip_input.append("StartFragment:C000000000\r\n");
    temp_clip_input.append("EndFragment:D000000000\r\n");

    if (!SourceURL.empty())
    {
        temp_clip_input.append("SourceURL:");
        temp_clip_input.append(SourceURL);
        temp_clip_input.append("\r\n");
    }

    // 因为数据体置前 所以 第一次只会匹配到 StartHTML:0000000000\r\n 以此类推
    GetClipboardHtml::lib_rp_setw_10(temp_clip_input, "A000000000", temp_clip_input.size());

    temp_clip_input.append("<html>\r\n<body>\r\n");

    temp_clip_input.append("<!--StartFragment-->");

    GetClipboardHtml::lib_rp_setw_10(temp_clip_input, "C000000000", temp_clip_input.size());

    // push html
    temp_clip_input.append(html);

    // EndHTML:0000000nnn\r\n

    GetClipboardHtml::lib_rp_setw_10(temp_clip_input, "D000000000", temp_clip_input.size());

    temp_clip_input.append("<!--EndFragment-->\r\n");

    temp_clip_input.append("</body>\r\n</html>");

    // EndFragment:0000000nnn\r\n
    GetClipboardHtml::lib_rp_setw_10(temp_clip_input, "B000000000", temp_clip_input.size());

    // 开始写入

    HANDLE handle = NULL;

    if (::OpenClipboard(NULL))
    {

        // 清空
        if (!::EmptyClipboard())
        {
            ::CloseClipboard();
            return result;
        }

        size_t len = (temp_clip_input.size() + 1) * sizeof(char);
        HANDLE handle = ::GlobalAlloc(GMEM_MOVEABLE, len);

        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      {
                if (handle != NULL) {
                    ::GlobalUnlock(handle);
                    ::GlobalFree(handle);
                    ::CloseClipboard();
                } });

        auto hMem_ptr = ::GlobalLock(handle);

        if (hMem_ptr != 0)
        {
            ::memcpy(hMem_ptr, temp_clip_input.c_str(), len);
            ::OpenClipboard(0);
            ::EmptyClipboard();
        }

        const UINT _CF_HTML = RegisterClipboardFormatA("HTML Format");

        ::SetClipboardData(_CF_HTML, handle);

        return true;
    }

    return result;
}

DWORD clip_util::GetClipboardSequenceID()
{
    return ::GetClipboardSequenceNumber();
}

bool clip_util::ClearClipboard()
{
    ::OpenClipboard(NULL);
    bool IsEmptyClipboard = ::EmptyClipboard();
    ::CloseClipboard();
    return IsEmptyClipboard;
}

bool clip_util::SetClipboardText(std::wstring text)
{
    HANDLE handle = NULL;

    if (::OpenClipboard(NULL))
    {

        HANDLE handle = ::GlobalAlloc(GMEM_MOVEABLE, (text.size() + 1) * sizeof(wchar_t));

        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      {
                if (handle != NULL) {
                    ::GlobalFree(handle);
                    ::CloseClipboard();
                } });

        wchar_t *wstr = (wchar_t *)::GlobalLock(handle);

        if (wstr != 0)
        {
            ::memcpy(wstr, text.c_str(), (text.size() + 1) * sizeof(wchar_t));
            ::GlobalUnlock(handle);
        }
        else
        {
            return false;
        }

        ::SetClipboardData(CF_UNICODETEXT, handle);
        return true;
    }
    return false;
}

bool clip_util::SetClipboardText(std::string text)
{
    HANDLE handle = NULL;

    if (::OpenClipboard(NULL))
    {
        size_t len = (text.size() + 1) * sizeof(char);
        HANDLE handle = ::GlobalAlloc(GMEM_MOVEABLE, len);

        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      {
                if (handle != NULL) {
                    ::GlobalUnlock(handle);
                    ::GlobalFree(handle);
                    ::CloseClipboard();
                } });

        auto hMem_ptr = ::GlobalLock(handle);

        if (hMem_ptr != 0)
        {
            ::memcpy(hMem_ptr, text.c_str(), len);
            ::OpenClipboard(0);
            ::EmptyClipboard();
        }

        ::SetClipboardData(CF_TEXT, handle);

        return true;
    }
    return false;
}

bool clip_util::SetClipboardPathList(const std::vector<std::wstring> &PathList)
{
    HANDLE handle = NULL;
    bool result = false;

    // 计算缓冲区大小
    size_t buffer_size = sizeof(DROPFILES) + sizeof(wchar_t) /* \0 */;
    size_t length = PathList.size();

    for (size_t i = 0; i < length; i++)
    {
        auto itPtr = &PathList[i];
        buffer_size += (itPtr->size() + 1) * sizeof(wchar_t);
    }

    handle = ::GlobalAlloc(GMEM_MOVEABLE, buffer_size);
    if (!handle)
        return result;

    std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                  {
            if (handle != NULL) {
                ::GlobalFree(handle);
                ::CloseClipboard();
            } });

    BYTE *data_pointer = static_cast<std::uint8_t *>(::GlobalLock(handle));
    if (!data_pointer)
        return result;

    // 制作缓冲区
    DROPFILES *drop_files_pointer = reinterpret_cast<DROPFILES *>(data_pointer);
    drop_files_pointer->pFiles = sizeof(DROPFILES);
    drop_files_pointer->fWide = true;

    size_t current_offset_in_bytes = sizeof(DROPFILES);

    length = PathList.size();
    for (size_t i = 0; i < length; i++)
    {
        auto itPtr = &PathList[i];
        wchar_t *target_path = reinterpret_cast<wchar_t *>(data_pointer + current_offset_in_bytes);
        size_t offset_in_chars = itPtr->size() + 1;
        size_t offset_in_bytes = offset_in_chars * sizeof(wchar_t);
        ::memcpy(target_path, itPtr->c_str(), offset_in_bytes);
        current_offset_in_bytes += offset_in_bytes;
    }

    wchar_t *tail = reinterpret_cast<wchar_t *>(data_pointer + current_offset_in_bytes);
    *tail = L'\0';

    ::GlobalUnlock(handle);

    if (::OpenClipboard(NULL))
    {

        ::EmptyClipboard();

        if (::SetClipboardData(CF_HDROP, handle))
        {
            result = true;
        }
    }

    return result;
}

bool clip_util::SetClipboardPathList(const std::vector<std::string> &PathList)
{
    HANDLE handle = NULL;
    bool result = false;

    // 计算缓冲区大小
    size_t buffer_size = sizeof(DROPFILES) + sizeof(char) /* \0 */;
    size_t length = PathList.size();

    for (size_t i = 0; i < length; i++)
    {
        auto itPtr = &PathList[i];
        buffer_size += (itPtr->size() + 1) * sizeof(char);
    }

    handle = ::GlobalAlloc(GMEM_MOVEABLE, buffer_size);
    if (!handle)
        return result;

    std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                  {
            if (handle != NULL) {
                GlobalFree(handle);
                CloseClipboard();
            } });

    BYTE *data_pointer = static_cast<std::uint8_t *>(::GlobalLock(handle));
    if (!data_pointer)
        return result;

    // 制作缓冲区
    DROPFILES *drop_files_pointer = reinterpret_cast<DROPFILES *>(data_pointer);
    drop_files_pointer->pFiles = sizeof(DROPFILES);
    drop_files_pointer->fWide = false;

    size_t current_offset_in_bytes = sizeof(DROPFILES);

    length = PathList.size();
    for (size_t i = 0; i < length; i++)
    {
        auto itPtr = &PathList[i];
        char *target_path = reinterpret_cast<char *>(data_pointer + current_offset_in_bytes);
        size_t offset_in_chars = itPtr->size() + 1;
        size_t offset_in_bytes = offset_in_chars * sizeof(char);
        ::memcpy(target_path, itPtr->c_str(), offset_in_bytes);
        current_offset_in_bytes += offset_in_bytes;
    }

    char *tail = reinterpret_cast<char *>(data_pointer + current_offset_in_bytes);
    *tail = '\0';

    ::GlobalUnlock(handle);

    if (::OpenClipboard(NULL))
    {

        ::EmptyClipboard();

        if (::SetClipboardData(CF_HDROP, handle))
        {
            result = true;
        }
    }

    return result;
}

bool clip_util::HasClipboardImage()
{
    if (!::OpenClipboard(NULL))
        return false;
    std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                  { ::CloseClipboard(); });

    return static_cast<bool>(::GetClipboardData(CF_BITMAP));
}

bool clip_util::isFormatAvailable(UINT uCF)
{
    return IsClipboardFormatAvailable(uCF) != false;
}

std::wstring clip_util::GetClipboardTextW()
{
    std::wstring result = L"";
    HANDLE handle = NULL;
    if (!::OpenClipboard(NULL))
    {
        return result;
    }

    std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                  {
            if (handle != NULL) {
                ::GlobalUnlock(handle);
                ::GlobalFree(handle);
                ::CloseClipboard();
            } });

    handle = ::GetClipboardData(CF_UNICODETEXT);
    const wchar_t *m_psz;

    m_psz = static_cast<const wchar_t *>(::GlobalLock(handle));
    if (!m_psz)
        return result;

    result.append(m_psz);

    return result;
}

std::string clip_util::GetClipboardTextA()
{
    std::string result = "";
    HANDLE handle = NULL;
    if (!::OpenClipboard(NULL))
    {
        return result;
    }

    std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                  {
            if (handle != NULL) {
                ::GlobalUnlock(handle);
                ::GlobalFree(handle);
                ::CloseClipboard();
            } });

    handle = ::GetClipboardData(CF_TEXT);
    const char *m_psz;

    m_psz = static_cast<const char *>(::GlobalLock(handle));
    if (!m_psz)
        return result;

    result.append(m_psz);

    return result;
}

std::vector<UINT> clip_util::EnumClipboardFormatList()
{
    std::vector<UINT> result = {};

    UINT iFormat = 0;
    if (::OpenClipboard(NULL))
    {
        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      { ::CloseClipboard(); });
    }
    else
        return result;

    int index = 0;

    while (iFormat = ::EnumClipboardFormats(iFormat))
    {
        result.push_back(iFormat);
        // 针对每个iFormat数据格式的操作
        index += 1;
    }

    return result;
}

std::vector<std::string> clip_util::GetClipboardPathListA()
{
    std::vector<std::string> result = {};
    if (::OpenClipboard(NULL))
    {
        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      { ::CloseClipboard(); });

        HDROP hDrop = HDROP(::GetClipboardData(CF_HDROP));
        if (hDrop != NULL)
        {
            char szFilePathName[MAX_PATH + 1] = {0};
            UINT UintAllFiles = ::DragQueryFileA(hDrop, 0xFFFFFFFF, NULL, 0);

            for (UINT index = 0; index < UintAllFiles; index++)
            {
                ::memset(szFilePathName, 0, MAX_PATH + 1);
                // get path
                ::DragQueryFileA(hDrop, index, szFilePathName, MAX_PATH);
                result.push_back(szFilePathName);
            }
        }
        ::CloseClipboard();
    }
    return result;
}

std::vector<std::wstring> clip_util::GetClipboardPathListW()
{
    std::vector<std::wstring> result = {};
    if (::OpenClipboard(NULL))
    {
        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      { ::CloseClipboard(); });

        HDROP hDrop = HDROP(::GetClipboardData(CF_HDROP));
        if (hDrop != NULL)
        {
            wchar_t szFilePathName[MAX_PATH + 1] = {0};
            UINT UintAllFiles = ::DragQueryFileW(hDrop, 0xFFFFFFFF, NULL, 0);

            for (UINT index = 0; index < UintAllFiles; index++)
            {
                ::memset(szFilePathName, 0, MAX_PATH + 1);
                // get path
                ::DragQueryFileW(hDrop, index, szFilePathName, MAX_PATH);
                result.push_back(szFilePathName);
            }
        }
        ::CloseClipboard();
    }
    return result;
}

std::wstring clip_util::GetClipboardFormatNameW(UINT format)
{
    std::wstring result = L"";
    result.reserve(MAX_PATH);
    wchar_t lpszFormatName[MAX_PATH];
    int cchMaxCount = MAX_PATH;
    int cchCount = ::GetClipboardFormatNameW(format, (LPTSTR)lpszFormatName, cchMaxCount);
    if (cchCount > 1)
    {

        for (size_t i = 0; i < cchCount; i++)
        {
            result.push_back(lpszFormatName[i]);
        }
        return result;
    }
    return result;
}

std::string clip_util::GetClipboardFormatNameA(UINT format)
{
    std::string result = "";
    result.reserve(MAX_PATH);
    char lpszFormatName[MAX_PATH];
    int cchMaxCount = MAX_PATH;
    int cchCount = ::GetClipboardFormatNameA(format, (LPSTR)lpszFormatName, cchMaxCount);
    if (cchCount > 1)
    {

        for (size_t i = 0; i < cchCount; i++)
        {
            result.push_back(lpszFormatName[i]);
        }
        return result;
    }
    return result;
}

clip_util::GetClipboardHtml::chClipHtmlItem clip_util::GetClipboardHtml::getHtmlItem()
{

    clip_util::GetClipboardHtml::chClipHtmlItem result = {
        is_valid,
        SourceData,
        Version,
        StartHTML,
        EndHTML,
        StartFragment,
        EndFragment,
        SourceURL};

    return result;
}

clip_util::GetClipboardHtml::GetClipboardHtml()
{
    GetClipboardHtml(NULL);
}

bool clip_util::GetClipboardHtml::isHtml()
{
    return is_valid;
}

size_t clip_util::GetClipboardHtml::html_indexof(std::string name)
{
    size_t result = 0;

    size_t start_pos = 0;
    size_t data_len = SourceData.size();

    if ((start_pos = SourceData.find(name, start_pos)) != std::string::npos)
    {
        std::string item = "";
        for (size_t i = start_pos + name.size(); i < data_len; i++)
        {
            auto at = SourceData.at(i);

            // 0-9 .
            if ((at >= '0' && at <= '9'))
            {
                item.push_back(at);
            }
            else
            {
                break;
            }
        }
        result = std::atol(item.c_str());
        return result;
    }

    return result;
}

bool clip_util::GetClipboardHtml::ParsingHtml()
{

    size_t start_pos = 0;
    size_t data_len = SourceData.size();

    // Version:0.9
    if ((start_pos = SourceData.find("Version:", start_pos)) != std::string::npos)
    {

        std::string item = "";

        for (size_t i = start_pos + 8; i < data_len; i++)
        {
            auto at = SourceData.at(i);

            // 0-9 .
            if (at == '.' || (at >= '0' && at <= '9'))
            {
                item.push_back(at);
            }
            else
            {
                break;
            }
        }

        Version = std::atof(item.c_str());
    }

    // SourceURL:https://....
    if ((start_pos = SourceData.find("SourceURL:", start_pos)) != std::string::npos)
    {
        for (size_t i = start_pos + 10; i < data_len; i++)
        {
            auto at = SourceData.at(i);
            if (at == '\n' || at == '\r' || at == '\0')
            {
                break;
            }

            SourceURL.push_back(SourceData.at(i));
        }
    }

    StartHTML = html_indexof("StartHTML:");
    EndHTML = html_indexof("EndHTML:");
    StartFragment = html_indexof("StartFragment:");
    EndFragment = html_indexof("EndFragment:");

    if (StartHTML == 0 || StartFragment == 0 || EndHTML > SourceData.length() || EndFragment > SourceData.length())
    {
        return false;
    }

    return true;
}

clip_util::GetClipboardHtml::GetClipboardHtml(HWND hWnd)
{
    static int CF_HTML = ::RegisterClipboardFormatA("HTML Format");
    HANDLE handle = NULL;

    if (!::IsClipboardFormatAvailable(CF_HTML) || !::OpenClipboard(hWnd))
        return;

    std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                  {
            ::GlobalUnlock(handle);
            ::CloseClipboard(); });

    handle = ::GetClipboardData(CF_HTML);

    if (!handle)
        return;

    LPCSTR temp_ptr = (LPCSTR)::GlobalLock(handle);

    if (!temp_ptr)
        return;

    SourceData.append(temp_ptr);
    is_valid = ParsingHtml();
}

napi_value getClipboardFilePaths(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::String(env, hmc_string_util::vec_to_array_json(clip_util::GetClipboardPathListW()));
}

napi_value setClipboardText(napi_env env, napi_callback_info info)
{
    auto input = hmc_NodeArgsValue(env, info);
    input.eq(0, js_string);

    return hmc_napi_create_value::Boolean(env, clip_util::SetClipboardText(input.getStringWide(0, L"")));
}

napi_value getClipboardText(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::String(env, clip_util::GetClipboardTextW());
}

// 清空剪贴板
napi_value clearClipboard(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Boolean(env, clip_util::ClearClipboard());
}

napi_value setClipboardFilePaths(napi_env env, napi_callback_info info)
{
    auto input = hmc_NodeArgsValue(env, info);
    if (input.exists(0))
    {

        auto ArrayWstring = input.getArrayWstring(0, {});
        bool res = clip_util::SetClipboardPathList(ArrayWstring);
        return hmc_napi_create_value::Boolean(env, res);
        }

    return hmc_napi_create_value::Boolean(env, false);
}

napi_value getClipboardInfo(napi_env env, napi_callback_info info)
{
    auto data = clip_util::GetClipboardInfo();
    napi_value Results;
    napi_create_object(env, &Results);

    hmc_napi_create_value::Object::putValue(env, Results, "format", hmc_string_util::vec_to_array_json(data.format));
    hmc_napi_create_value::Object::putValue(env, Results, "format", as_Number(data.formatCount));
    hmc_napi_create_value::Object::putValue(env, Results, "hwnd", as_Number(data.hwnd));
    hmc_napi_create_value::Object::putValue(env, Results, "id", as_Number(data.id));

    return Results;
}

napi_value enumClipboardFormats(napi_env env, napi_callback_info info)
{
    auto formats = clip_util::EnumClipboardFormatList();
    auto count = formats.size();
    wstring formatJson = L"[";

    formatJson.reserve(512);

    for (size_t i = 0; i < count; i++)
    {
        wstring obj = LR"({"type":{type},"type_name":"{type_name}"})";
        auto it = formats.at(i);
        auto name = clip_util::GetClipboardFormatNameW((UINT)it);
        hmc_string_util::replace(obj, L"{type_name}", name);
        hmc_string_util::replace(obj, L"{type}", to_wstring(it));
        if (i + 1 < count)
        {
            obj.push_back(L',');
        }
        formatJson.append(obj);
    }

    formatJson.push_back(']');
    return hmc_napi_create_value::String(env, formatJson);
}

napi_value getClipboardHTML(napi_env env, napi_callback_info info)
{
    auto ClipboardHtml = clip_util::GetClipboardHtml();
    if (ClipboardHtml.isHtml())
    {
        auto HtmlItem = ClipboardHtml.getHtmlItem();
        napi_value Results;
        napi_create_object(env, &Results);

        hmc_napi_create_value::Object::putValue(env, Results, "data", HtmlItem.data);
        hmc_napi_create_value::Object::putValue(env, Results, "EndFragment", as_Number(env, HtmlItem.EndFragment));
        hmc_napi_create_value::Object::putValue(env, Results, "EndHTML", as_Number(HtmlItem.EndHTML));
        hmc_napi_create_value::Object::putValue(env, Results, "is_valid", as_Boolean(HtmlItem.is_valid));
        hmc_napi_create_value::Object::putValue(env, Results, "SourceURL", HtmlItem.SourceURL);
        hmc_napi_create_value::Object::putValue(env, Results, "StartFragment", as_Number(HtmlItem.StartFragment));
        hmc_napi_create_value::Object::putValue(env, Results, "StartHTML", as_Number(HtmlItem.StartHTML));
        hmc_napi_create_value::Object::putValue(env, Results, "Version", as_Numberf(HtmlItem.Version));

        return Results;
    }

    return hmc_napi_create_value::Null(env);
}
