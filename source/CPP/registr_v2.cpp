#include "./util/hmc_string_util.hpp"
#include "./util/hmc_registr_util.hpp"
#include "./registr_v2.hpp"
#include "./Mian.hpp"
#include <format>

napi_value getStringRegKey(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");
    bool expand = nodeArgsValueList.getBool(3, false);

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }
    auto open_registr = hmc_registr_util::getRegistrValue(root_hive, Path, key);

    if (open_registr.isString())
    {
        return hmc_napi_create_value::String(env, open_registr.getStringW(expand));
    }

    return result;
}

napi_value removeRegistrFolder(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null},
                               {3, js_boolean}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");
    bool tree = nodeArgsValueList.exists(3) && nodeArgsValueList.getBool(3, false);

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }
    bool is_rm = hmc_registr_util::removeRegistrFolder(root_hive, Path, key, tree);
    result = hmc_napi_create_value::Boolean(env, is_rm);
    return result;
}

napi_value removeRegistrValue(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }
    bool is_rm = hmc_registr_util::removeRegistrKey(root_hive, Path, key);
    result = hmc_napi_create_value::Boolean(env, is_rm);
    return result;
}

napi_value hasRegistrValue(napi_env env, napi_callback_info info)
{

    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }
    bool is_exist = hmc_registr_util::hasRegistrValue(root_hive, Path, key);
    result = hmc_napi_create_value::Boolean(env, is_exist);
    return result;
}

napi_value createRegistrFolder(napi_env env, napi_callback_info info)
{

    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }
    bool is_exist = hmc_registr_util::createRegistrFolder(root_hive, Path);
    result = hmc_napi_create_value::Boolean(env, is_exist);
    return result;
}

napi_value getRegistrFolderStat(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {1, js_boolean}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto is_keys = nodeArgsValueList.getBool(2, false);

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }
    std::vector<std::wstring> QueryFolderList;
    std::vector<std::wstring> QueryKeyList;

    if (is_keys)
        hmc_registr_util::getRegistrKeys(root_hive, Path, QueryFolderList, QueryKeyList);

    auto folderInfo = hmc_registr_util::getRegistrFolderInfo(root_hive, Path);

    // 预计算出大概需要多少内存 以减少文本处理 开辟内存的性能消耗 也能替换过程
    size_t get_reserve_size = 0;

    if (is_keys)
    {
        size_t list_len = QueryFolderList.size();

        for (size_t i = 0; i < list_len; i++)
        {
            get_reserve_size += QueryFolderList.at(i).size() + 16;
        }

        list_len = QueryKeyList.size();
        for (size_t i = 0; i < list_len; i++)
        {
            get_reserve_size += QueryKeyList.at(i).size() + 16;
        }
    }

    wstring jsonw = LR"({"key":{key} ,"folder":{folder} ,"size": {size} , "exists":{exists} , "folderSize":{folderSize} ,"keySize":{keySize} , "time":{time} })";
    jsonw.reserve(get_reserve_size + jsonw.size());

    hmc_string_util::replace(jsonw, L"{folder}", hmc_string_util::vec_to_array_json(QueryFolderList));
    hmc_string_util::replace(jsonw, L"{key}", hmc_string_util::vec_to_array_json(QueryKeyList));

    hmc_string_util::replace(jsonw, L"{exists}", folderInfo.exists ? L"true" : L"false");
    hmc_string_util::replace(jsonw, L"{size}", to_wstring(QueryFolderList.size() + QueryKeyList.size()));
    hmc_string_util::replace(jsonw, L"{folderSize}", to_wstring(folderInfo.folderSize));
    hmc_string_util::replace(jsonw, L"{keySize}", to_wstring(folderInfo.keySize));
    hmc_string_util::replace(jsonw, L"{time}", folderInfo.time < 1 ? L"null" : to_wstring(folderInfo.time));

    result = hmc_napi_create_value::String(env, jsonw);
    return result;
}

napi_value getRegistrValueStat(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }
    auto ValueStat = hmc_registr_util::getValueStat(root_hive, Path, key);

    wstring jsonw = LR"({"exists":{exists},"size":{size},"type":"{type}"})";
    jsonw.reserve(MAX_PATH + jsonw.size());

    hmc_string_util::replace(jsonw, L"{exists}", ValueStat.exists ? L"true" : L"false");
    hmc_string_util::replace(jsonw, L"{size}", to_wstring(ValueStat.size));
    hmc_string_util::replace(jsonw, L"{type}", ValueStat.type_nameW());

    result = hmc_napi_create_value::String(env, jsonw);
    return result;
}

napi_value getRegistrBuffValue(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }

    auto ValueStat = hmc_registr_util::GetRegistrSourceValue(root_hive, Path, key);

    result = hmc_napi_create_value::Buffer(env, ValueStat.value);

    return result;
}

napi_value getRegistrDword(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }

    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }

    auto open_registr = hmc_registr_util::getRegistrValue(root_hive, Path, key);

    if (open_registr.isNumber())
    {
        return hmc_napi_create_value::Number(env, open_registr.getInt64());
    }

    return result;
}

napi_value setRegistrDword(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null},
                               {3, js_number}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");
    auto Dword = nodeArgsValueList.getInt(3, 0);

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }
    bool is_exist = hmc_registr_util::setRegistrValue(root_hive, Path, key).set((long)Dword);
    result = hmc_napi_create_value::Boolean(env, is_exist);
    return result;
}

napi_value getRegistrQword(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }
    auto open_registr = hmc_registr_util::getRegistrValue(root_hive, Path, key);

    if (open_registr.isNumber())
    {
        return hmc_napi_create_value::Bigint(env, open_registr.getInt64());
    }

    return result;
}

napi_value setRegistrQword(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Null(env);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null},
                               {3, js_bigint}}))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");
    auto Dword = nodeArgsValueList.getInt64(3, 0);

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }
    bool is_exist = hmc_registr_util::setRegistrValue(root_hive, Path, key).set((int64_t)Dword);
    result = hmc_napi_create_value::Boolean(env, is_exist);
    return result;
}

napi_value setRegistrValue(napi_env env, napi_callback_info info)
{
    auto result = hmc_napi_create_value::Boolean(env, false);
    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string},
                               {2, js_null},
                               {3, js_number},
                               {3, js_bigint},
                               {3, js_string},
                               {3, js_buffer},
                               {3, js_boolean},
                               {3, js_date},
                               {3, js_null},
                               {4, js_boolean},
                               {4, js_number},
                               {4, js_undefined}},
                              true))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto key = nodeArgsValueList.getStringWide(2, L"");
    int to_type =(nodeArgsValueList.exists(4) && nodeArgsValueList.eq(4, js_number)) ? nodeArgsValueList.getInt(4) :-1;

    if (root_key.empty() || Path.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }
    auto root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }

    if (!nodeArgsValueList.exists(3))
    {
        return hmc_napi_create_value::ErrorBreak(env, "empty value", __FUNCTION__, "value <empty> Error");
    }

    auto open_regist = hmc_registr_util::setRegistrValue(root_hive, Path, key);

    // bool / int
    if (nodeArgsValueList.exists(3) && nodeArgsValueList.eq({{3, js_number}, {3, js_boolean}}, false))
    {
        long Dword = hmc_napi_type::isBoolean(env, nodeArgsValueList.at(3)) ? nodeArgsValueList.getBool(3, false) : nodeArgsValueList.getInt(3, 0);
        bool is_exist = open_regist.set((long)Dword);
        result = hmc_napi_create_value::Boolean(env, is_exist);
        return result;
    }

    // int64
    if (nodeArgsValueList.exists(3) && nodeArgsValueList.eq({{3, js_bigint}}, false))
    {
        auto buffer_ptr = nodeArgsValueList.getInt64(3, 0);
        bool is_exist = open_regist.set(buffer_ptr);
        result = hmc_napi_create_value::Boolean(env, is_exist);
        return result;
    }

    // string
    if (nodeArgsValueList.exists(3) && nodeArgsValueList.eq({{3, js_string}}, false))
    {
        auto string_ptr = nodeArgsValueList.getStringWide(3, L"");
        // 转义
        bool _is_expand = nodeArgsValueList.exists(4) ? nodeArgsValueList.getBool(4, false) : false;

        bool is_exist = open_regist.set(string_ptr, _is_expand);
        result = hmc_napi_create_value::Boolean(env, is_exist);
        return result;
    }

    // buffer
    if (nodeArgsValueList.exists(3) && hmc_napi_type::isBuffer(env, nodeArgsValueList.at(3)))
    {
        auto buffer_ptr = nodeArgsValueList.getBuffer(3, {});
        bool is_exist = hmc_registr_util::SetRegistrSourceValue(root_hive, Path, key, REG_BINARY, buffer_ptr);
        result = hmc_napi_create_value::Boolean(env, is_exist);
        return result;
    }

    // 时间戳
    if (nodeArgsValueList.exists(3) && hmc_napi_type::isDate(env, nodeArgsValueList.at(3)))
    {
        auto date = hmc_napi_get_value::date(env, nodeArgsValueList.at(3));

        vector<BYTE> rawBytes(sizeof(double));
        memcpy(&rawBytes[0], &date, sizeof(double));

        bool is_exist = hmc_registr_util::SetRegistrSourceValue(root_hive, Path, key, REG_BINARY, rawBytes);

        result = hmc_napi_create_value::Boolean(env, is_exist);
        return result;
    }

    // not
    if (nodeArgsValueList.exists(3) && nodeArgsValueList.eq(3, js_null, false))
    {
        bool is_exist = open_regist.set();
        result = hmc_napi_create_value::Boolean(env, is_exist);
        return result;
    }

    return result;
}