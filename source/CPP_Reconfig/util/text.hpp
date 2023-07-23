#include <string>
#include <windows.h>
#include <codecvt>
#include <regex>
using namespace std;

namespace hmc_text_regexp
{

}

// 文本工具
namespace hmc_text_util
{
    string W2A(const wstring &pwText);
    string A2U8(const string &pText);
    string UTF8ToGBK(string u8str);
    bool haslongStr(string Value);
    string W2U8(wstring pwText);
    wstring A2W(const string &paText);
    wstring U82W(const string &pszText);
    string U82A(const string &pText);
    bool haslonglongStr(string Value);
    bool hasIntStr(string Value);

    //  WIDE to ANSI
    string W2A(const wstring &pwText)
    {
        string strResult = string();
        if (pwText.empty())
            return strResult;

        int pszATextLen = WideCharToMultiByte(CP_ACP, 0, pwText.c_str(), -1, NULL, 0, NULL, NULL);
        char *pAChar = new (nothrow) char[pszATextLen];
        if (pAChar == NULL)
        {
            return strResult;
        }

        ZeroMemory(pAChar, pszATextLen + 1);
        WideCharToMultiByte(CP_ACP, 0, pwText.c_str(), -1, pAChar, pszATextLen, NULL, NULL);

        strResult.append(pAChar);
        delete[] pAChar;
        pAChar = NULL;

        return strResult;
    }

    //  ANSI to WIDE
    wstring A2W(const string &paText)
    {
        wstring strResult = wstring();

        if (paText.empty())
            return strResult;

        int pszWTextLen = MultiByteToWideChar(CP_ACP, 0, paText.c_str(), -1, NULL, 0);
        wchar_t *pWideChar = new (nothrow) wchar_t[pszWTextLen];

        if (pWideChar == NULL)
            return strResult;

        ZeroMemory(pWideChar, pszWTextLen + 1);
        MultiByteToWideChar(CP_ACP, 0, paText.c_str(), -1, pWideChar, pszWTextLen);

        strResult.append(pWideChar);
        delete[] pWideChar;
        pWideChar = NULL;

        return strResult;
    }

    // 宽字符字符串转UTF-8字符串
    string W2U8(wstring pwText)
    {
        string strResult = string();
        if (pwText.empty())
            return strResult;

        int pszATextLen = WideCharToMultiByte(CP_UTF8, 0, pwText.c_str(), -1, NULL, 0, NULL, NULL);
        char *pUTF8 = new char[pszATextLen + 1];
        if (pUTF8 == NULL)
            return strResult;
        ZeroMemory(pUTF8, pszATextLen + 1);
        WideCharToMultiByte(CP_UTF8, 0, pwText.c_str(), -1, pUTF8, pszATextLen, NULL, NULL);
        strResult.append(pUTF8);

        delete[] pUTF8;
        pUTF8 = NULL;

        return strResult;
    }

    // UTF-8字符串转宽字符
    wstring U82W(const string &pszText)
    {
        wstring strResult = wstring();
        if (pszText.size() == 0)
            return strResult;

        int pszWTextLen = MultiByteToWideChar(CP_UTF8, 0, pszText.c_str(), -1, NULL, NULL);
        wchar_t *pszWText = new wchar_t[pszWTextLen + 1];

        if (pszWText == NULL)
            return strResult;
        ZeroMemory(pszWText, pszWTextLen + 1);
        MultiByteToWideChar(CP_UTF8, 0, pszText.c_str(), -1, pszWText, pszWTextLen);
        strResult.append(pszWText);
        delete[] pszWText;
        pszWText = NULL;

        return strResult;
    }

    // 多字节字符串转UTF-8字符串
    string A2U8(const string &pText)
    {
        return W2U8(A2W(pText));
    }

    // UTF-8字符串转多字节字符串
    string U82A(const string &pText)
    {
        return W2A(U82W(pText));
    }

    // unicode 转A
    string U82A(UNICODE_STRING unicodeString)
    {
        return W2A(unicodeStringToWString(unicodeString));
    }
    
    // unicode 转W
    wstring U82W(UNICODE_STRING unicodeString)
    {
        return unicodeStringToWString(unicodeString);
    }

    // UFT8 字符转为GBK(中文)
    string UTF8ToGBK(string u8str)
    {
        string Result;
        TCHAR *pTempTstr;
        WCHAR *pTempwstr;

        int strSizeTempVar = MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, NULL, 0);
        pTempwstr = new WCHAR[strSizeTempVar + 1];

        MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, pTempwstr, strSizeTempVar);
        strSizeTempVar = WideCharToMultiByte(CP_ACP, 0, pTempwstr, -1, NULL, 0, NULL, NULL);

        pTempTstr = new TCHAR[strSizeTempVar + 1];

        WideCharToMultiByte(CP_ACP, 0, pTempwstr, -1, (LPSTR)pTempTstr, strSizeTempVar, NULL, NULL);
        Result = (char *)pTempTstr;
        delete[] pTempTstr;
        delete[] pTempwstr;

        return Result;
    }

    // 文本中是否有数字 并且是否是安全的 int32
    bool hasIntStr(string Value)
    {
        bool Result = false;
        if (Value.empty())
            return Result;
        try
        {
            int n = stoi(Value);
            Result = true;
        }
        catch (const std::exception &e)
        {
            return Result;
        }

        return Result;
    }

    // 文本中是否有数字 并且是否是安全的 long
    bool haslongStr(string Value)
    {
        bool Result = false;
        if (Value.empty())
            return Result;
        try
        {
            long n = stol(Value);
            Result = true;
        }
        catch (const std::exception &e)
        {
            return Result;
        }

        return Result;
    }

    // 文本中是否有数字 并且是否是安全的 long long
    bool haslonglongStr(string Value)
    {
        bool Result = false;
        if (Value.empty())
            return Result;
        try
        {
            long long n = stoll(Value);
            Result = true;
        }
        catch (const std::exception &e)
        {
            return Result;
        }

        return Result;
    }

    wstring unicodeStringToWString(UNICODE_STRING unicodeString)
    {
        wstring result;
        if (unicodeString.Buffer)
        {
            result = wstring(unicodeString.Buffer, unicodeString.Length / sizeof(wchar_t));
        }
        return result;
    }

#ifdef defined(_MFC_VER)

    CString UTF8ToCString(string utf8str)
    {
        // 计算所需空间的大小
        int nLen = MultiByteToWideChar(CP_UTF8, NULL,
                                       utf8str.data(), utf8str.size(), NULL, 0);

        // 转换为Unicode
        wstring wbuffer;
        wbuffer.resize(nLen);
        MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(),
                            (LPWSTR)(wbuffer.data()), wbuffer.length());

#ifdef UNICODE
        // 如果是Unicode编码，直接返回Unicode字符串
        return (CString(wbuffer.data(), wbuffer.length()));
#else
        /*
         * 转换为ANSI编码
         * 得到转换后长度
         */
        nLen = WideCharToMultiByte(CP_ACP, 0,
                                   wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);

        string ansistr;
        ansistr.resize(nLen);

        // 把Unicode字符串转成ANSI编码字符串
        WideCharToMultiByte(CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(),
                            (LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
        return (CString(ansistr.data(), ansistr.length()));
#endif
    }

    string CStringToUTF8(CString strValue)
    {
        wstring wbuffer;
#ifdef _UNICODE
        // 如果是Unicode编码，直接获取Unicode字符串
        wbuffer.assign(strValue.GetString(), strValue.GetLength());
#else
        /*
         * 转换ANSI编码到Unicode编码
         * 获取转换后长度
         */
        int length = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, (LPCTSTR)strValue, -1, NULL, 0);
        wbuffer.resize(length);
        /* 转换 */
        MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strValue, -1, (LPWSTR)(wbuffer.data()), wbuffer.length());
#endif

        /* 获取转换后长度 */
        int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wbuffer.data(), wbuffer.size(), NULL, 0, NULL, NULL);
        /* 获取转换后内容 */
        string utf8Buffer;
        utf8Buffer.resize(utf8Length);

        WideCharToMultiByte(CP_UTF8, 0, wbuffer.data(), -1, (LPSTR)(utf8Buffer.data()), utf8Length, NULL, NULL);
        return (utf8Buffer);
    }
#endif

}
