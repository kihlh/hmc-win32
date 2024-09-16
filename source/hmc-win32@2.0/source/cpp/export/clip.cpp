#include "export.h"
#include "hmc_napi_value_util.h"
#include "hmc_clip_util.h"

napi_value getClipboardFilePaths(napi_env env, napi_callback_info info)
{
    std::vector<std::wstring> file_list = hmc_clip_util::GetClipboardPathListW();
    std::wstring temp = L"";
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
        std::string text = input.getStringUtf8(0, "");
        std::string url = input.exists(2) ? input.getStringUtf8(2, "") : "";
        result = hmc_clip_util::SetClipboardHtml(text, url);
    }
    else
    {
        std::wstring text = input.getStringWide(0, L"");
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
    auto Results = hmc_napi_create_value::jsObject(env);

    Results.putString("format", hmc_string_util::vec_to_array_json(data.format));
    Results.putValue("formatCount", as_Number(data.formatCount));
    Results.putValue("hwnd", as_Number(data.hwnd));
    Results.putValue("id", as_Number(data.id));

    return Results.toValue();
}

napi_value enumClipboardFormats(napi_env env, napi_callback_info info)
{
    auto formats = hmc_clip_util::EnumClipboardFormatList();
    auto count = formats.size();
    std::wstring formatJson = L"[";

    formatJson.reserve(512);

    for (size_t i = 0; i < count; i++)
    {
        std::wstring obj = LR"({"type":{type},"type_name":"{type_name}"})";
        auto it = formats.at(i);
        auto name = hmc_clip_util::GetClipboardFormatNameW((std::uint8_t)it);
        hmc_string_util::replace(obj, L"{type_name}", name);
        hmc_string_util::replace(obj, L"{type}", std::to_wstring(it));
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

        auto Results = hmc_napi_create_value::jsObject(env);

        Results.putString("data", HtmlItem.data);
        Results.putValue("EndFragment", as_Number(HtmlItem.EndFragment));
        Results.putValue("EndHTML", as_Number(HtmlItem.EndHTML));
        Results.putValue("is_valid", as_Boolean(HtmlItem.is_valid));
        Results.putString("SourceURL", HtmlItem.SourceURL);
        Results.putValue("StartFragment", as_Number(HtmlItem.StartFragment));
        Results.putValue("StartHTML", as_Number(HtmlItem.StartHTML));
        Results.putValue("Version", as_Numberf(HtmlItem.Version));

        return Results.toValue();
    }

    return hmc_napi_create_value::Null(env);
}
