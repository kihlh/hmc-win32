#include "./Mian.hpp";

napi_value getClipboardFilePaths(napi_env env)
{
    napi_value filePaths, value;
    napi_status status;
    status = napi_create_array(env, &filePaths);
    if (status != napi_ok)
        return nullptr;

    if (OpenClipboard(NULL))
    {
        HDROP hDrop = HDROP(::GetClipboardData(CF_HDROP));
        if (hDrop != NULL)
        {
            wchar_t szFilePathName[MAX_PATH + 1] = {0};
            UINT UintAllFiles = DragQueryFileW(hDrop, 0xFFFFFFFF, NULL, 0);

            for (UINT index = 0; index < UintAllFiles; index++)
            {
                memset(szFilePathName, 0, MAX_PATH + 1);
                // get path
                DragQueryFileW(hDrop, index, szFilePathName, MAX_PATH);
                value = hmc_napi_create_value::String(env, szFilePathName);
                // push path to Array
                status = napi_set_element(env, filePaths, index, value);
                if (status != napi_ok)
                    return nullptr;
            }
        }
        CloseClipboard();
    }
    return filePaths;
}

// 未修改 来自stackoverflow 授权CC BY-SA x.0
// https://stackoverflow.com/questions/14762456/getclipboarddatacf-text
class RaiiClipboard
{
public:
    RaiiClipboard()
    {
        if (!OpenClipboard(nullptr))
            throw runtime_error("Can't open clipboard.");
        // ... or define some custom exception class for clipboard errors.
    }

    ~RaiiClipboard()
    {
        CloseClipboard();
    }

    // Ban copy
private:
    RaiiClipboard(const RaiiClipboard &);
    RaiiClipboard &operator=(const RaiiClipboard &);
};
// 未修改 来自stackoverflow 授权CC BY-SA x.0
// https://stackoverflow.com/questions/14762456/getclipboarddatacf-text
class RaiiTextGlobalLock
{
public:
    explicit RaiiTextGlobalLock(HANDLE hData)
        : m_hData(hData)
    {
        m_psz = static_cast<const char *>(GlobalLock(m_hData));
        if (!m_psz)
            throw runtime_error("Can't acquire lock on clipboard text.");
    }

    ~RaiiTextGlobalLock()
    {
        GlobalUnlock(m_hData);
    }

    const char *Get() const
    {
        return m_psz;
    }

private:
    HANDLE m_hData;
    const char *m_psz;

    // Ban copy
    RaiiTextGlobalLock(const RaiiTextGlobalLock &);
    RaiiTextGlobalLock &operator=(const RaiiTextGlobalLock &);
};
// 存在修改 来自stackoverflow 授权CC BY-SA x.0
// https://stackoverflow.com/questions/14762456/getclipboarddatacf-text
string GetClipboardText()
{
    RaiiClipboard clipboard;

    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr)
        throw runtime_error("Can't get clipboard text.");

    RaiiTextGlobalLock textGlobalLock(hData);
    // 修改内容 转码
    //   string text( textGlobalLock.Get() );
    //   return text;
    return _A2U8_(textGlobalLock.Get());
}
// 写入文本到剪贴板
napi_value setClipboardText(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    if (argc)
    {
        if (argc < 1)
        {
            napi_throw_type_error(env, NULL, "Wrong length of arguments =>" + argc);
            return NULL;
        }
        napi_valuetype valuetype0;
        status = napi_typeof(env, args[0], &valuetype0);
        assert(status == napi_ok);
        if (valuetype0 != napi_string)
        {
            napi_throw_type_error(env, NULL, "Wrong Not napi_string arguments");
            return NULL;
        }
    }
    else
    {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return NULL;
    };

    string Text_UTF8 = call_String_NAPI_WINAPI_A(env, args[0]);
    size_t Set_str_len = Text_UTF8.size() + sizeof(string);
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, Set_str_len);
    memcpy(GlobalLock(hMem), Text_UTF8.c_str(), Set_str_len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    return NULL;
}

// 获取剪贴板文本
napi_value getClipboardText(napi_env env, napi_callback_info info)
{
    napi_value ClipText;
    /**
    if (!OpenClipboard(nullptr))
        return ClipText;
    HANDLE GetClipData = GetClipboardData(CF_TEXT);
    // 创建一个存放文本的指针 取消 (因为第二次获取一样的会内存溢出)
    // char *pszText = static_cast<char *>(GlobalLock(GetClipData));
    if (GetClipData != nullptr )
    {
        napi_create_string_utf8(env, _A2U8_((static_cast<char *>(GlobalLock(GetClipData)))).c_str(), NAPI_AUTO_LENGTH, &ClipText);
    }
    GlobalUnlock(GetClipData);
    // 关闭剪贴板并清空指针
    CloseClipboard();
     */

    try
    {
        string str = GetClipboardText();
        napi_create_string_utf8(env, str.c_str(), NAPI_AUTO_LENGTH, &ClipText);
    }
    catch (...)
    {
        napi_create_string_utf8(env, "", NAPI_AUTO_LENGTH, &ClipText);
        // cout << "Caught an exception in catch(...)." << endl;
    }
    return ClipText;
}

// 清空剪贴板
napi_value clearClipboard(napi_env env, napi_callback_info info)
{
    OpenClipboard(0);
    bool IsEmptyClipboard = EmptyClipboard();
    CloseClipboard();
    return _create_bool_Boolean(env, IsEmptyClipboard);
}

// https://github.com/kenan2002/electron-clipboard-ex/blob/master/src/clipboard_win.cc
// MIT
class ClipboardScope
{

    bool valid;

public:
    ClipboardScope()
    {
        valid = static_cast<bool>(OpenClipboard(NULL));
    }

    ~ClipboardScope()
    {
        CloseClipboard();
    }

    bool IsValid()
    {
        return valid;
    }
};

// https://github.com/kenan2002/electron-clipboard-ex/blob/master/src/clipboard_win.cc
// MIT 存在变更
void WriteFilePaths(vector<wstring> &file_paths_unicode)
{

    // size of DROPFILES structure followed by file paths in double null-terminated string
    SIZE_T structure_size_in_bytes = sizeof(DROPFILES);
    for (auto p = file_paths_unicode.cbegin(); p != file_paths_unicode.cend(); ++p)
    {
        structure_size_in_bytes += (p->size() + 1) * sizeof(WCHAR);
    }
    structure_size_in_bytes += sizeof(WCHAR);

    HANDLE data_handle = GlobalAlloc(GMEM_MOVEABLE, structure_size_in_bytes);
    if (!data_handle)
    {
        return;
    }

    BYTE *data_pointer = static_cast<BYTE *>(GlobalLock(data_handle));
    if (!data_pointer)
    {
        return;
    }

    DROPFILES *drop_files_pointer = reinterpret_cast<DROPFILES *>(data_pointer);
    drop_files_pointer->pFiles = sizeof(DROPFILES);
    drop_files_pointer->fWide = TRUE;

    SIZE_T current_offset_in_bytes = sizeof(DROPFILES);
    for (auto p = file_paths_unicode.cbegin(); p != file_paths_unicode.cend(); ++p)
    {
        WCHAR *target_path = reinterpret_cast<WCHAR *>(data_pointer + current_offset_in_bytes);
        SIZE_T offset_in_chars = p->size() + 1;
        SIZE_T offset_in_bytes = offset_in_chars * sizeof(WCHAR);
        memcpy(target_path, p->c_str(), offset_in_bytes);
        current_offset_in_bytes += offset_in_bytes;
    }

    WCHAR *tail = reinterpret_cast<WCHAR *>(data_pointer + current_offset_in_bytes);
    *tail = L'\0';

    GlobalUnlock(data_handle);

    ClipboardScope clipboard_scope;
    if (!clipboard_scope.IsValid())
    {
        GlobalFree(data_handle);
        return;
    }

    EmptyClipboard();

    if (!SetClipboardData(CF_HDROP, data_handle))
    {
        GlobalFree(data_handle);
        return;
    }
}

napi_value setClipboardFilePaths(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    napi_value value;
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    vector<wstring> file_paths_unicode;

    uint32_t size = 0;
    status = napi_get_array_length(env, args[0], &size);
    if (status != napi_ok)
        return NULL;

    for (size_t i = 0; i < size; i++)
    {
        status = napi_get_element(env, args[0], i, &value);
        if (status != napi_ok)
            return NULL;
        file_paths_unicode.push_back(call_String_NAPI_WINAPI_W(env, value));
    }
    WriteFilePaths(file_paths_unicode);
    return NULL;
}

napi_value getClipboardSequenceNumber(napi_env env, napi_callback_info info)
{
    return _create_int64_Number(env, GetClipboardSequenceNumber());
}

napi_value enumClipboardFormats(napi_env env, napi_callback_info info)
{
    napi_value Formats;
    napi_status status;
    status = napi_create_array(env, &Formats);
    if (status != napi_ok)
    {
        return Formats;
    }
    // UINT CF_HTML = Registerclipboardformat('HTML Format');
    UINT iFormat = 0;
    OpenClipboard(NULL);
    int index = 0;
    while (iFormat = EnumClipboardFormats(iFormat))
    {
        status = napi_set_element(env, Formats, index, _create_int64_Number(env, iFormat));
        if (status != napi_ok)
        {
            return Formats;
        }
        // 针对每个iFormat数据格式的操作
        index += 1;
    }

    CloseClipboard();
    return Formats;
}

napi_value getClipboardHTML(napi_env env, napi_callback_info info)
{
    napi_value ClipHTML;

    napi_create_string_utf8(env, "", NAPI_AUTO_LENGTH, &ClipHTML);
    return ClipHTML;
}

bool setClipboard(LPCWSTR lpszWide){
    int nUtf8Size = ::WideCharToMultiByte(CP_UTF8, 0, lpszWide, -1, NULL, 0, NULL, NULL);
    if (nUtf8Size < 1) return false;

    const int nDescLen = 105;
    HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, nDescLen + nUtf8Size);
    if (NULL != hGlobal)
    {
        bool bErr = false;
        LPSTR lpszBuf = static_cast<LPSTR>(::GlobalLock(hGlobal));
        LPSTR lpszUtf8 = lpszBuf + nDescLen;
        if (::WideCharToMultiByte(CP_UTF8, 0, lpszWide, -1, lpszUtf8, nUtf8Size, NULL, NULL) <= 0)
        {
            bErr = true;
        }
        else
        {
            LPCSTR lpszStartFrag = strstr(lpszUtf8, "<!--StartFragment-->");
            LPCSTR lpszEndFrag = strstr(lpszUtf8, "<!--EndFragment-->");
            lpszStartFrag += strlen("<!--StartFragment-->") + 2;

            int i = _snprintf(
            lpszBuf, nDescLen,
            "Version:1.0\r\nStartHTML:%010d\r\nEndHTML:%010d\r\nStartFragment:%010d\r\nEndFragment:%010d\r\n",
            nDescLen, 
            nDescLen + nUtf8Size - 1,       // offset to next char behind string
            nDescLen + static_cast<int>(lpszStartFrag - lpszUtf8), 
            nDescLen + static_cast<int>(lpszEndFrag - lpszUtf8));
        }
        ::GlobalUnlock(hGlobal);
        if (bErr)
        {
            ::GlobalFree(hGlobal);
            hGlobal = NULL;
        }

        // Get clipboard id for HTML format...
        static int cfid = 0;
        cfid = RegisterClipboardFormatW(L"HTML Format");
        // Open the clipboard...
        if(OpenClipboard(0)) {
            EmptyClipboard();
            HGLOBAL hText = GlobalAlloc(GMEM_MOVEABLE |GMEM_DDESHARE, strlen(lpszBuf)+4);
            char *ptr = (char *)GlobalLock(hText);
            strcpy(ptr, lpszBuf);
            GlobalUnlock(hText);
            ::SetClipboardData(cfid, hText);
            CloseClipboard();
            GlobalFree(hText);
        }
    }

    return NULL != hGlobal;
}

