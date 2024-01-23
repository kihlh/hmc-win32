#include "./hmc_clip_util.h"

hmc_clip_util::chClipInfo hmc_clip_util::GetClipboardInfo()
{
    hmc_clip_util::chClipInfo result;
    result.hwnd = ::GetClipboardOwner();
    result.format = EnumClipboardFormatList();
    result.formatCount = ::CountClipboardFormats();
    result.id = ::GetClipboardSequenceNumber();
    return result;
}

void hmc_clip_util::GetClipboardHtml::lib_rp_setw_10(std::string &sourcePtr, std::string from, size_t len)
{
    std::string result;

    char temp[11];
    sprintf_s(temp, 11, "%010u", (std::uint8_t)len);

    result.append(temp);

    size_t start_pos = 0;
    if ((start_pos = sourcePtr.find(from, start_pos)) != std::string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), std::string(temp));
    }
}

bool hmc_clip_util::SetClipboardHtml(const std::string &html, const std::string SourceURL)
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

        ::GlobalUnlock(handle);

        return true;
    }

    return result;
}

DWORD hmc_clip_util::GetClipboardSequenceID()
{
    return ::GetClipboardSequenceNumber();
}

bool hmc_clip_util::ClearClipboard()
{
    ::OpenClipboard(NULL);
    bool IsEmptyClipboard = ::EmptyClipboard();
    ::CloseClipboard();
    return IsEmptyClipboard;
}

bool hmc_clip_util::SetClipboardText(std::wstring text)
{
    HANDLE handle = NULL;

    if (::OpenClipboard(NULL))
    {

        HANDLE handle = ::GlobalAlloc(GMEM_MOVEABLE, (text.size() + 1) * sizeof(wchar_t));
        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      {
            if (handle != NULL) {
                GlobalFree(handle);
                handle = NULL;
            } 
              CloseClipboard(); });

        if (!::EmptyClipboard())
        {
            return false;
        }
        wchar_t *wstr = (wchar_t *)::GlobalLock(handle);

        if (wstr != 0)
        {
            ::memcpy(wstr, text.c_str(), (text.size() + 1) * sizeof(wchar_t));
        }
        else
        {
            ::GlobalUnlock(handle);
            return false;
        }

        ::SetClipboardData(CF_UNICODETEXT, handle);

        ::GlobalUnlock(handle);

        return true;
    }
    return false;
}

bool hmc_clip_util::SetClipboardText(std::string text)
{
    HANDLE handle = NULL;

    if (::OpenClipboard(NULL))
    {
        size_t len = (text.size() + 1) * sizeof(char);
        HANDLE handle = ::GlobalAlloc(GMEM_MOVEABLE, len);

        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      {
            if (handle != NULL) {
                GlobalFree(handle);
                handle = NULL;
            } 
              CloseClipboard(); });

        if (!::EmptyClipboard())
        {
            return false;
        }

        auto hMem_ptr = ::GlobalLock(handle);

        if (hMem_ptr != 0)
        {
            ::memcpy(hMem_ptr, text.c_str(), len);
            ::EmptyClipboard();
        }

        ::SetClipboardData(CF_TEXT, handle);
        ::GlobalUnlock(handle);

        return true;
    }
    return false;
}

bool hmc_clip_util::SetClipboardPathList(const std::vector<std::wstring> &PathList)
{
    HANDLE handle = NULL;
    bool result = false;

    if (::OpenClipboard(NULL))
    {
        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      {
                 if (handle != NULL) {
                     GlobalFree(handle);
                     handle = NULL;
                 }
                 CloseClipboard(); });

        if (!::EmptyClipboard())
        {
            return result;
        }

        // 计算缓冲区大小
        size_t length = PathList.size();
        std::wstring PathList2Str = L"";
        size_t PathList2Str_reserve_length = PathList.size();

        for (size_t i = 0; i < length; i++)
        {
            auto itPtr = &PathList[i];
            PathList2Str_reserve_length += (itPtr->size() + 1) * sizeof(wchar_t);
        }

        PathList2Str.reserve(PathList2Str_reserve_length);

        for (size_t i = 0; i < length; i++)
        {
            std::wstring path = PathList.at(i);

            auto end_pos = path.size();

            // 移除所有尾部 \0
            while ((end_pos = path.find_last_not_of(L'\0')) != path.size() - 1)
            {
                path.erase(end_pos + 1);
            }

            if (path.empty())
            {
                continue;
            }

            PathList2Str.append(path);
            PathList2Str.push_back(L'\0');
        }

        PathList2Str.push_back(L'\0');

        int nSize = sizeof(DROPFILES) + PathList2Str.size() * 2;
        handle = ::GlobalAlloc(GMEM_MOVEABLE, nSize);

        if (!handle)
        {
            return result;
        }

        LPDROPFILES pDropFiles = (LPDROPFILES)::GlobalLock(handle);

        if (!pDropFiles)
        {
            return result;
        }

        ((DROPFILES *)pDropFiles)->pFiles = sizeof(DROPFILES);
        ((DROPFILES *)pDropFiles)->fWide = TRUE;

        LPBYTE pData = (LPBYTE)pDropFiles + sizeof(DROPFILES);
        memcpy(pData, (LPBYTE)PathList2Str.data(), PathList2Str.size() * sizeof(wchar_t));

        ::GlobalUnlock(handle);

        if (::SetClipboardData(CF_HDROP, handle))
        {
            result = true;
        }
    }

    return result;
}

bool hmc_clip_util::SetClipboardPathList(const std::vector<std::string> &PathList)
{
    HANDLE handle = NULL;
    bool result = false;

    if (::OpenClipboard(NULL))
    {
        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      {
                if (handle != NULL) {
                    GlobalFree(handle);
                    handle = NULL;
                }
                CloseClipboard(); });

        if (!::EmptyClipboard())
        {
            return result;
        }

        // 计算缓冲区大小
        size_t length = PathList.size();
        std::string PathList2Str = "";
        size_t PathList2Str_reserve_length = PathList.size();

        for (size_t i = 0; i < length; i++)
        {
            auto itPtr = &PathList[i];
            PathList2Str_reserve_length += (itPtr->size() + 1) * sizeof(char);
        }

        PathList2Str.reserve(PathList2Str_reserve_length);

        for (size_t i = 0; i < length; i++)
        {
            std::string path = PathList.at(i);

            auto end_pos = path.size();

            // 移除所有尾部 \0
            while ((end_pos = path.find_last_not_of('\0')) != path.size() - 1)
            {
                path.erase(end_pos + 1);
            }

            if (path.empty())
            {
                continue;
            }

            PathList2Str.append(path);
            PathList2Str.push_back('\0');
        }

        PathList2Str.push_back('\0');

        int nSize = sizeof(DROPFILES) + PathList2Str.size() * sizeof(char);
        handle = ::GlobalAlloc(GMEM_MOVEABLE, nSize);

        if (!handle)
        {
            return result;
        }

        LPDROPFILES pDropFiles = (LPDROPFILES)::GlobalLock(handle);

        if (!pDropFiles)
        {
            return result;
        }

        ((DROPFILES *)pDropFiles)->pFiles = sizeof(DROPFILES);
        ((DROPFILES *)pDropFiles)->fWide = TRUE;

        LPBYTE pData = (LPBYTE)pDropFiles + sizeof(DROPFILES);
        memcpy(pData, (LPBYTE)PathList2Str.data(), PathList2Str.size() * sizeof(char));

        ::GlobalUnlock(handle);

        if (::SetClipboardData(CF_HDROP, handle))
        {
            result = true;
        }
    }

    return result;
}

bool hmc_clip_util::HasClipboardImage()
{
    if (!::OpenClipboard(NULL))
        return false;
    std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                  { ::CloseClipboard(); });

    return static_cast<bool>(::GetClipboardData(CF_BITMAP));
}

bool hmc_clip_util::isFormatAvailable(UINT uCF)
{
    return IsClipboardFormatAvailable(uCF) != false;
}

std::wstring hmc_clip_util::GetClipboardTextW()
{
    std::wstring result = L"";
    HANDLE handle = NULL;

    if (!::OpenClipboard(NULL))
    {
        return result;
    }

    if (!::IsClipboardFormatAvailable(CF_UNICODETEXT) && !::IsClipboardFormatAvailable(CF_TEXT))
    {
        return result;
    }

    std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                  {
                                                      ::CloseClipboard();
                                                      ::GlobalUnlock(handle);
                                                      if (handle != NULL)
                                                      {
                                                          handle = NULL;
                                                      } });

    handle = ::GetClipboardData(CF_UNICODETEXT);

    const wchar_t *memoryStrPtr = static_cast<const wchar_t *>(::GlobalLock(handle));

    ::CloseClipboard();

    if (!memoryStrPtr)
    {
        return result;
    }

    result.append(memoryStrPtr);

    return result;
}

std::string hmc_clip_util::GetClipboardTextA()
{
    std::string result = "";
    HANDLE handle = NULL;
    if (!::OpenClipboard(NULL))
    {
        return result;
    }

    if (!::IsClipboardFormatAvailable(CF_UNICODETEXT) && !::IsClipboardFormatAvailable(CF_TEXT))
    {
        return result;
    }

    std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                  {
                                                      ::CloseClipboard();
                                                      ::GlobalUnlock(handle);
                                                      if (handle != NULL)
                                                      {
                                                          handle = NULL;
                                                      } });

    handle = ::GetClipboardData(CF_TEXT);
    const char *memoryStrPtr = static_cast<const char *>(::GlobalLock(handle));

    if (!memoryStrPtr)
    {
        return result;
    }

    result.append(memoryStrPtr);

    return result;
}

std::vector<UINT> hmc_clip_util::EnumClipboardFormatList()
{
    std::vector<UINT> result = {};

    if (::OpenClipboard(NULL))
    {
        std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                      { ::CloseClipboard(); });
    }
    else
        return result;

    size_t len = CountClipboardFormats();
    result.reserve(len);

    UINT num = 0;

    for (size_t i = 0; i < len; i++)
    {
        num = ::EnumClipboardFormats(num);
        if (num != 0)
        {
            result.push_back(num);
        }
    }

    return result;
}

std::vector<std::string> hmc_clip_util::GetClipboardPathListA()
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
    }
    return result;
}

std::vector<std::wstring> hmc_clip_util::GetClipboardPathListW()
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
    }
    return result;
}

std::wstring hmc_clip_util::GetClipboardFormatNameW(UINT format)
{
    std::wstring result = L"";
    result.reserve(MAX_PATH);
    wchar_t lpszFormatName[MAX_PATH];
    int cchMaxCount = MAX_PATH;
    int cchCount = ::GetClipboardFormatNameW(format, (LPWSTR)lpszFormatName, cchMaxCount);
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

std::string hmc_clip_util::GetClipboardFormatNameA(UINT format)
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

hmc_clip_util::GetClipboardHtml::chClipHtmlItem hmc_clip_util::GetClipboardHtml::getHtmlItem()
{

    hmc_clip_util::GetClipboardHtml::chClipHtmlItem result = {
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

hmc_clip_util::GetClipboardHtml::GetClipboardHtml()
{
    GetClipboardHtml(NULL);
}

bool hmc_clip_util::GetClipboardHtml::isHtml()
{
    return is_valid;
}

size_t hmc_clip_util::GetClipboardHtml::html_indexof(std::string name)
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

bool hmc_clip_util::GetClipboardHtml::ParsingHtml()
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

hmc_clip_util::GetClipboardHtml::GetClipboardHtml(HWND hWnd)
{
    static int CF_HTML = ::RegisterClipboardFormatA("HTML Format");
    HANDLE handle = NULL;

    if (!::IsClipboardFormatAvailable(CF_HTML) || !::OpenClipboard(hWnd))
        return;

    std::shared_ptr<void> shared_close_Free_Auto_(nullptr, [&](void *)
                                                  { ::CloseClipboard(); });

    handle = ::GetClipboardData(CF_HTML);

    if (!handle)
        return;

    LPCSTR temp_ptr = (LPCSTR)::GlobalLock(handle);

    if (!temp_ptr)
    {
        ::GlobalUnlock(handle);
        return;
    }
    ::GlobalUnlock(handle);

    SourceData.append(temp_ptr);
    is_valid = ParsingHtml();
}
