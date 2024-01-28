#include "./export.h"
#include "hmc_napi_value_util.h"
#include "hmc_clip_util.h"

napi_value getClipboardFilePaths(napi_env env, napi_callback_info info)
{
    std::vector<std::wstring> file_list = hmc_clip_util::GetClipboardPathListW();
    wstring temp = L"";
    const size_t file_size = file_list.size();

    size_t msize = 0;

    for (size_t i = 0; i < file_size; i++)
    {
        msize = msize + file_list.at(i).size();
    }

    temp.reserve(msize + file_size * 2);

    for (size_t i = 0; i < file_size; i++)
    {
        temp.append(file_list.at(i));
        temp.push_back(L'\0');
    }

    return hmc_napi_create_value::String(env, temp, temp.length());
}

napi_value setClipboardText(napi_env env, napi_callback_info info)
{
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string}});
    bool is_html = input.exists(1) ? input.getBool(1, false) : false;
    bool result = false;

    if (is_html)
    {
        string text = input.getStringUtf8(0, "");
        string url = input.exists(2) ? input.getStringUtf8(2, "") : "";
        result = hmc_clip_util::SetClipboardHtml(text, url);
    }
    else
    {
        wstring text = input.getStringWide(0, L"");
        result = hmc_clip_util::SetClipboardText(text);
    }

    return hmc_napi_create_value::Boolean(env, result);
}

napi_value getClipboardText(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::String(env, hmc_clip_util::GetClipboardTextW());
}

napi_value clearClipboard(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::Boolean(env, hmc_clip_util::ClearClipboard());
}

napi_value setClipboardFilePaths(napi_env env, napi_callback_info info)
{
    auto input = hmc_NodeArgsValue(env, info);
    if (input.exists(0))
    {
        // 是文本而不是 array<string>
        if (input.eq(0, js_string, false))
        {
            auto ArrayWstring = input.getStringWide(0, {});
            bool res = hmc_clip_util::SetClipboardPathList({ArrayWstring});
            return hmc_napi_create_value::Boolean(env, res);
        }
        auto ArrayWstring = input.getArrayWstring(0, {});
        bool res = hmc_clip_util::SetClipboardPathList(ArrayWstring);
        return hmc_napi_create_value::Boolean(env, res);
    }

    return hmc_napi_create_value::Boolean(env, false);
}

napi_value getClipboardInfo(napi_env env, napi_callback_info info)
{
    auto data = hmc_clip_util::GetClipboardInfo();
    napi_value Results;
    napi_create_object(env, &Results);

    hmc_napi_create_value::Object::putValue(env, Results, "format", hmc_string_util::vec_to_array_json(data.format));
    hmc_napi_create_value::Object::putValue(env, Results, "formatCount", as_Number(data.formatCount));
    hmc_napi_create_value::Object::putValue(env, Results, "hwnd", as_Number(data.hwnd));
    hmc_napi_create_value::Object::putValue(env, Results, "id", as_Number(data.id));

    return Results;
}

napi_value enumClipboardFormats(napi_env env, napi_callback_info info)
{
    auto formats = hmc_clip_util::EnumClipboardFormatList();
    auto count = formats.size();
    wstring formatJson = L"[";

    formatJson.reserve(512);

    for (size_t i = 0; i < count; i++)
    {
        wstring obj = LR"({"type":{type},"type_name":"{type_name}"})";
        auto it = formats.at(i);
        auto name = hmc_clip_util::GetClipboardFormatNameW((UINT)it);
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
    auto ClipboardHtml = hmc_clip_util::GetClipboardHtml(NULL);
    auto HtmlItem = ClipboardHtml.getHtmlItem();
    if (HtmlItem.is_valid)
    {
        napi_value Results;
        napi_create_object(env, &Results);

        hmc_napi_create_value::Object::putValue(env, Results, "data", HtmlItem.data);
        hmc_napi_create_value::Object::putValue(env, Results, "EndFragment", as_Number(HtmlItem.EndFragment));
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

