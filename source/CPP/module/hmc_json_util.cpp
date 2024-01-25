#include "./hmc_json_util.h"

inline std::string hmc_json_util::toJsonValueA(const std::string &input, bool is_to_value)
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

inline std::wstring hmc_json_util::toJsonValueW(const std::wstring &input, bool is_to_value)
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

std::string hmc_json_util::toJsonValueA(hmc_json_util::NumberType value)
{

    switch (value.index())
    {
        hmc_define_to_Json_Value_caseA(0);
        hmc_define_to_Json_Value_caseA(1);
        hmc_define_to_Json_Value_caseA(2);
        hmc_define_to_Json_Value_caseA(3);
        hmc_define_to_Json_Value_caseA(4);
        hmc_define_to_Json_Value_caseA(5);
        hmc_define_to_Json_Value_caseA(6);
        hmc_define_to_Json_Value_caseA(7);
        hmc_define_to_Json_Value_caseA(8);
        hmc_define_to_Json_Value_caseA(9);
        hmc_define_to_Json_Value_caseA(10);
        hmc_define_to_Json_Value_caseA(11);
        hmc_define_to_Json_Value_caseA(12);
        hmc_define_to_Json_Value_caseA(13);
        hmc_define_to_Json_Value_caseA(14);
        hmc_define_to_Json_Value_caseA(15);
        hmc_define_to_Json_Value_caseA(16);
        hmc_define_to_Json_Value_caseA(17);
        hmc_define_to_Json_Value_caseA(18);
        hmc_define_to_Json_Value_caseA(19);
        hmc_define_to_Json_Value_caseA(20);
        hmc_define_to_Json_Value_caseA(21);
        hmc_define_to_Json_Value_caseA(22);
        //hmc_define_to_Json_Value_caseA(23);
        // hmc_define_to_Json_Value_caseA(24);
        // hmc_define_to_Json_Value_caseA(25);
    }
    return "0";
}

std::wstring hmc_json_util::toJsonValueW(hmc_json_util::NumberType value)
{

    switch (value.index())
    {
        hmc_define_to_Json_Value_caseW(0);
        hmc_define_to_Json_Value_caseW(1);
        hmc_define_to_Json_Value_caseW(2);
        hmc_define_to_Json_Value_caseW(3);
        hmc_define_to_Json_Value_caseW(4);
        hmc_define_to_Json_Value_caseW(5);
        hmc_define_to_Json_Value_caseW(6);
        hmc_define_to_Json_Value_caseW(7);
        hmc_define_to_Json_Value_caseW(8);
        hmc_define_to_Json_Value_caseW(9);
        hmc_define_to_Json_Value_caseW(10);
        hmc_define_to_Json_Value_caseW(11);
        hmc_define_to_Json_Value_caseW(12);
        hmc_define_to_Json_Value_caseW(13);
        hmc_define_to_Json_Value_caseW(14);
        hmc_define_to_Json_Value_caseW(15);
        hmc_define_to_Json_Value_caseW(16);
        hmc_define_to_Json_Value_caseW(17);
        hmc_define_to_Json_Value_caseW(18);
        hmc_define_to_Json_Value_caseW(19);
        hmc_define_to_Json_Value_caseW(20);
        hmc_define_to_Json_Value_caseW(21);
        hmc_define_to_Json_Value_caseW(22);
        //hmc_define_to_Json_Value_caseW(23);
        // hmc_define_to_Json_Value_caseW(24);
        // hmc_define_to_Json_Value_caseW(25);
    }

    return L"0";
}



std::string hmc_json_util::formatJson(const std::string &json)
{
    std::string formatted;
    int indent = 0;
    for (char c : json)
    {
        switch (c)
        {
        case '{':
        case '[':
            formatted.push_back(c);
            formatted.push_back('\n');
            formatted.append(++indent * 4, '\t');
            break;
        case '}':
        case ']':
            formatted.push_back('\n');
            if (indent > 0)
            {
                formatted.append(--indent * 4, '\t');
            }
            formatted.push_back(c);
            break;
        case ',':
            formatted.push_back(c);
            formatted.push_back('\n');
            formatted.append(indent * 4, '\t');
            break;
        case ':':
            formatted.push_back(c);
            formatted.push_back(' ');
            break;
        default:
            formatted.push_back(c);
            break;
        }
    }
    return formatted;
}

std::wstring hmc_json_util::formatJson(const std::wstring &json)
{
    std::wstring formatted;
    int indent = 0;
    for (wchar_t c : json)
    {
        switch (c)
        {
        case L'{':
        case L'[':
            formatted.push_back(c);
            formatted.push_back(L'\n');
            formatted.append(++indent * 4, L'\t');
            break;
        case L'}':
        case L']':
            formatted.push_back(L'\n');
            if (indent > 0)
            {
                formatted.append(--indent * 4, L'\t');
            }
            formatted.push_back(c);
            break;
        case L',':
            formatted.push_back(c);
            formatted.push_back(L'\n');
            formatted.append(indent, L'\t');
            break;
        case L':':
            formatted.push_back(c);
            formatted.push_back(L' ');
            break;
        default:
            formatted.push_back(c);
            break;
        }
    }
    return formatted;
}

