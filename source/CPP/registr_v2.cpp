#include "./module/hmc_string_util.h"
#include "./module/hmc_napi_value_util.h";
#include "./module/hmc_registr_util.h"
#include "./registr_v2.hpp"
#include "./Mian.hpp"
#include <format>

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
                               {1, js_string}},
                              true))
    {
        return result;
    }

    auto root_key = nodeArgsValueList.getStringWide(0, L"");
    auto Path = nodeArgsValueList.getStringWide(1, L"");
    auto is_keys = nodeArgsValueList.exists(2) && nodeArgsValueList.getBool(2, false);

    if (root_key.empty())
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

    auto folderInfo = hmc_registr_util::getRegistrFolderInfo(root_hive, Path);

    if (is_keys && folderInfo.exists)
        hmc_registr_util::getRegistrKeys(root_hive, Path, QueryFolderList, QueryKeyList);

    if (!folderInfo.exists)
    {
        return as_Null();
    }

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

    if (!ValueStat.exists)
    {
        return as_Null();
    }

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

    if (root_key.empty())
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
                               {3,js_array},
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
    int to_type = (nodeArgsValueList.exists(4) && nodeArgsValueList.eq(4, js_number)) ? nodeArgsValueList.getInt(4) : -1;

    if (root_key.empty())
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

    // string[]
    if (nodeArgsValueList.exists(3) && nodeArgsValueList.eq({{3, js_array}}, false))
    {
        auto string_ptr = nodeArgsValueList.getArrayWstring(3, {});
       
        bool is_exist = open_regist.set(string_ptr);
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

napi_value getRegistrValue(napi_env env, napi_callback_info info)
{

    napi_value result = hmc_napi_create_value::Object::Object(env);

    auto nodeArgsValueList = hmc_NodeArgsValue(env, info);

    if (!nodeArgsValueList.eq({{0, js_string},
                               {1, js_string},
                               {2, js_string}},
                              true))
    {
        return result;
    }

    wstring root_key = nodeArgsValueList.getStringWide(0, L"");
    wstring Path = nodeArgsValueList.getStringWide(1, L"");
    wstring Key = nodeArgsValueList.getStringWide(2, L"");

    if (root_key.empty())
    {

        return hmc_napi_create_value::ErrorBreak(env, "empty parameter <root_key,folder_path>", __FUNCTION__, "parameter <empty> Error");
    }

    HKEY root_hive = hmc_registr_util::getHive(root_key);

    if (root_hive == NULL)
    {

        return hmc_napi_create_value::ErrorBreak(env, R"((root_key!="HKEY_USERS"||root_key!="HKEY_LOCAL_MACHINE"||root_key!="HKEY_CURRENT_USER"||root_key!="HKEY_CURRENT_CONFIG"||root_key!="HKEY_CLASSES_ROOT"))", __FUNCTION__, "parameter <unknown> Error");
    }

    auto ValueStat = hmc_registr_util::getRegistrValue(root_hive, Path, Key);

    if (!ValueStat.isValue())
    {
        return as_Null();
    }
    auto type = ValueStat.getType();
    wstring typeName = hmc_registr_util::type_nameW(type);

    hmc_napi_create_value::Object::putValue(env, result, L"type", as_Number(type));
    hmc_napi_create_value::Object::putValue(env, result, L"typeName", as_String(typeName));
    bool is_push_ok = false;

    if (!is_push_ok && ValueStat.isString())
    {
        auto data = ValueStat.getStringW();

        if( ValueStat.isType(REG_EXPAND_SZ) ) {
            auto data2 = ValueStat.getStringW(true);
            hmc_napi_create_value::Object::putValue(env, result, L"dataExpand", as_String(data2));
        }
        
        else if( ValueStat.isType(REG_MULTI_SZ) ) {
            auto data2 = ValueStat.getMultiW();
            hmc_napi_create_value::Object::putValue(env, result, L"data", hmc_napi_create_value::Array::String(env, data2));
        }

        else{
            hmc_napi_create_value::Object::putValue(env, result, L"data", as_String(data));
        }
        
        is_push_ok = true;
    }

    if (!is_push_ok && ValueStat.isNumber())
    {
        auto data = ValueStat.getInt64();
        if (ValueStat.isInt64())
        {
            hmc_napi_create_value::Object::putValue(env, result, L"data", as_Bigint(data));
        }
        else
        {

            hmc_napi_create_value::Object::putValue(env, result, L"data", as_Number(data));
        }
        is_push_ok = true;
    }
    if (!is_push_ok)
    {
        vector<unsigned char> buff = ValueStat.getBuff();
        napi_value buffer = hmc_napi_create_value::Buffer(env, buff);
        hmc_napi_create_value::Object::putValue(env, result, L"data", buffer);
        is_push_ok = true;
    }

    return result;
}