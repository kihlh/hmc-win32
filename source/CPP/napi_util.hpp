#define NAPI_EXPERIMENTAL // 开启实验性功能 比如异步(多线程)
#include <node_api.h>
#include <assert.h>
#include <any>
#include <vector>
#include <map>
#include <iostream>
#include <windows.h>

#include "text.hpp"
#include "./include/json.hpp"
using json = nlohmann::json;

#define _HMC_ALL_UTIL 0x0666
#define napi_ass_false -66666666

using namespace std;

namespace hmc_napi_util
{
    bool _hmc_debug = false;
    long _hmc_Object_id = 0;
    /**
     * @brief 由于any序列化大量的obj会出现内存溢出 所有部分获取将会返回一个数字id（ _hmc_Object_id + 1 ） 然后通过这个id查询获取对象
     *
     */
    map<long, map<string, any>> AllObjectValueList;

    namespace create_value
    {

        // 创建一个布尔型
        napi_value Boolean(napi_env env, bool value = false)
        {
            napi_status status;
            napi_value result;
            status = napi_get_boolean(env, value, &result);
            assert(status == napi_ok);
            return result;
        }
        // 创建一个布尔型
        napi_value Boolean(napi_env env, int value = 0)
        {
            napi_status status;
            napi_value result;
            status = napi_get_boolean(env, (bool)value, &result);
            assert(status == napi_ok);
            return result;
        }

        // 返回一个 string
        napi_value String(napi_env env, string value)
        {
            napi_status status;
            napi_value result;
            status = napi_create_string_utf8(env, hmc_text_util::A2U8(value).c_str(), NAPI_AUTO_LENGTH, &result);
            assert(status == napi_ok);
            return result;
        }
        napi_value String(napi_env env, wstring value)
        {
            napi_status status;
            napi_value result;
            status = napi_create_string_utf8(env, hmc_text_util::W2U8(value).c_str(), NAPI_AUTO_LENGTH, &result);
            assert(status == napi_ok);
            return result;
        }
        napi_value String(napi_env env, wchar_t *value)
        {
            return String(env, wstring(value));
        }
        napi_value String(napi_env env, char *value)
        {
            return String(env, string(value));
        }
        napi_value String(napi_env env)
        {
            return String(env, "");
        }
        /**
         * @brief 返回json 对象 napi的js脚本应当对文本的开头进行判断 如果含有"hmc::api::::json::::" 应当转义为json
         * 
         * @param env 
         * @param jsonValue 
         * @return napi_value 
         */
        napi_value JSON(napi_env env, json jsonValue)
        {
            string jsonValuetoString = string("hmc::api::::json::::");
            jsonValue.get_to(jsonValuetoString);
            return String(env, jsonValuetoString);
        }
        /**
         * @brief 返回一个 number到js
         *
         * @param number
         * @return napi_value
         */
        napi_value Number(napi_env env, int number = 0)
        {
            napi_status status;
            napi_value result;
            status = napi_create_int32(env, number, &result);
            assert(status == napi_ok);
            return result;
        }
        /**
         * @brief 返回一个 number到js
         *
         * @param number
         * @return napi_value
         */
        napi_value Number(napi_env env, int64_t number = 0)
        {
            napi_status status;
            napi_value result;
            status = napi_create_int64(env, number, &result);
            assert(status == napi_ok);
            return result;
        }
        /**
         * @brief 返回一个 number到js
         *
         * @param number
         * @return napi_value
         */
        napi_value Number(napi_env env, double number = 0.0)
        {
            napi_status status;
            napi_value result;
            status = napi_create_double(env, number, &result);
            assert(status == napi_ok);
            return result;
        }
        /**
         * @brief 返回一个 number到js
         *
         * @param number
         * @return napi_value
         */
        napi_value Number(napi_env env, HWND number)
        {
            napi_status status;
            napi_value result;
            status = napi_create_int64(env, (long long)number, &result);
            assert(status == napi_ok);
            return result;
        }
        napi_value Number(napi_env env, unsigned long number)
        {
            napi_status status;
            napi_value result;
            status = napi_create_int64(env, (long)number, &result);
            assert(status == napi_ok);
            return result;
        }
        /**
         * @brief 返回一个 number到js
         *
         * @param bigint
         * @return napi_value
         */
        napi_value Bigint(napi_env env, long bigint = 0)
        {
            napi_status status;
            napi_value result;
            status = napi_create_bigint_int64(env, bigint, &result);
            assert(status == napi_ok);
            return result;
        }
        /**
         * @brief 返回一个 number到js
         *
         * @param bigint
         * @return napi_value
         */
        napi_value Bigint(napi_env env, long long bigint = 0)
        {
            napi_status status;
            napi_value result;
            status = napi_create_bigint_int64(env, bigint, &result);
            assert(status == napi_ok);
            return result;
        }
        /**
         * @brief 返回一个 Buffer到js(返回的是空值 napi 不支持)
         *
         * @param env
         * @param data
         * @param size
         * @return napi_value
         */
        napi_value Buffer(napi_env env, vector<unsigned char> &buffer)
        {
            napi_status status;
            napi_value Results;
            try
            {

                void *yourPointer = malloc(buffer.size());

                // 很迷惑的函数 这个只能创建空白内存而不是buff
                // status = napi_create_arraybuffer(env, buffer.size(), &yourPointer, &Results);
                // assert(status == napi_ok);

                memcpy(yourPointer, buffer.data(), buffer.size());
                status = napi_create_external_buffer(env, buffer.size(), yourPointer, NULL, NULL, &Results);
                assert(status == napi_ok);
                // free(yourPointer);
            }
            catch (const std::exception &e)
            {
            }

            return Results;
        }
        napi_value Buffer(napi_env env, void *data, size_t size)
        {
            napi_status status;
            napi_value Results;
            try
            {
                status = napi_create_external_buffer(env, size, data, NULL, NULL, &Results);
                assert(status == napi_ok);
            }
            catch (const std::exception &e)
            {
                void *yourPointer = malloc(0);
                status = napi_create_buffer(env, 0, &yourPointer, &Results);
                assert(status == napi_ok);
            }
            return Results;
        }

        /**
         * @brief 返回一个 null
         *
         * @param env
         * @param data
         * @param size
         * @return napi_value
         */
        napi_value Null(napi_env env)
        {
            napi_status status;
            napi_value Results;
            status = napi_get_null(env, &Results);
            assert(status == napi_ok);
            return Results;
        }
        /**
         * @brief RECT (位置信息转为Object)
         *
         * @param env
         * @param rect
         * @return napi_value
         */
        napi_value Rect(napi_env env, RECT rect)
        {
            napi_value ResultforObject;
            napi_status status;
            status = napi_create_object(env, &ResultforObject);
            assert(status == napi_ok);

            status = napi_set_property(env, ResultforObject, create_value::String(env, "bottom"), create_value::Number(env, rect.bottom));
            assert(status == napi_ok);

            status = napi_set_property(env, ResultforObject, create_value::String(env, "left"), create_value::Number(env, rect.left));
            assert(status == napi_ok);

            status = napi_set_property(env, ResultforObject, create_value::String(env, "right"), create_value::Number(env, rect.right));
            assert(status == napi_ok);

            status = napi_set_property(env, ResultforObject, create_value::String(env, "top"), create_value::Number(env, rect.top));
            assert(status == napi_ok);

            return ResultforObject;
        }
        /**
         * @brief 返回一个 undefined
         *
         * @param env
         * @param data
         * @param size
         * @return napi_value
         */
        napi_value Undefined(napi_env env)
        {
            napi_status status;
            napi_value Results;
            status = napi_get_undefined(env, &Results);
            assert(status == napi_ok);
            return Results;
        }
        /**
         * @brief 自识别类型
         *
         * @param env
         * @param anyValue
         * @return napi_value
         */
        napi_value New(napi_env env, any anyValue)
        {
            napi_status status;
            napi_value ResultForAny;
            if (anyValue.has_value())
            {
                // 整形
                if (anyValue.type() == typeid(DWORD))
                {
                    ResultForAny = Number(env, any_cast<DWORD>(anyValue));
                }
                else if (anyValue.type() == typeid(int))
                {
                    ResultForAny = Number(env, any_cast<int>(anyValue));
                }
                else if (anyValue.type() == typeid(long))
                {
                    ResultForAny = Number(env, any_cast<long>(anyValue));
                }
                else if (anyValue.type() == typeid(long long))
                {
                    ResultForAny = Number(env, any_cast<long long>(anyValue));
                }
                else if (anyValue.type() == typeid(HWND))
                {
                    ResultForAny = Number(env, any_cast<HWND>(anyValue));
                }
                else if (anyValue.type() == typeid(int64_t))
                {
                    ResultForAny = Number(env, any_cast<int64_t>(anyValue));
                }
                else if (anyValue.type() == typeid(short))
                {
                    ResultForAny = Number(env, any_cast<short>(anyValue));
                }
                else if (anyValue.type() == typeid(unsigned long long) || anyValue.type() == typeid(unsigned long))
                {
                    ResultForAny = Number(env, (unsigned long)any_cast<unsigned long long>(anyValue));
                }
                // 浮点
                else if (anyValue.type() == typeid(float))
                {
                    ResultForAny = Number(env, (double)any_cast<float>(anyValue));
                }
                else if (anyValue.type() == typeid(double))
                {
                    ResultForAny = Number(env, any_cast<double>(anyValue));
                }
                else if (anyValue.type() == typeid(long double))
                {
                    ResultForAny = Number(env, (double)any_cast<long double>(anyValue));
                }
                // 文本型
                else if (anyValue.type() == typeid(string))
                {
                    ResultForAny = String(env, any_cast<string>(anyValue));
                }
                else if (anyValue.type() == typeid(wstring))
                {
                    ResultForAny = String(env, any_cast<wstring>(anyValue));
                }
                else if (anyValue.type() == typeid(char *))
                {
                    ResultForAny = String(env, any_cast<char *>(anyValue));
                }
                else if (anyValue.type() == typeid(CHAR *))
                {
                    ResultForAny = String(env, any_cast<CHAR *>(anyValue));
                }
                else if (anyValue.type() == typeid(WCHAR *))
                {
                    ResultForAny = String(env, any_cast<WCHAR *>(anyValue));
                }
                // bool
                else if (anyValue.type() == typeid(bool))
                {
                    ResultForAny = Boolean(env, any_cast<bool>(anyValue));
                }
                else if (anyValue.type() == typeid(BOOL))
                {
                    ResultForAny = Boolean(env, any_cast<BOOL>(anyValue));
                }

                else
                {
                    ResultForAny = Undefined(env);
                }
            }

            return ResultForAny;
        }
        /**
         * @brief 返回json 对象 napi的js脚本应当对文本的开头进行判断 如果含有"hmc::api::::json::::" 应当转义为json
         * 
         * @param env 
         * @param jsonValue 
         * @return napi_value 
         */
        napi_value New(napi_env env, json jsonValue)
        {
            string jsonValuetoString = string("hmc::api::::json::::");
            jsonValue.get_to(jsonValuetoString);
            return String(env, jsonValuetoString);
        }
        napi_value New(napi_env env)
        {
            return Undefined(env);
        }
        namespace Array
        {
            /**
             * @brief 支持多种类型的数组
             *
             * @param env
             * @param wstringVector
             * @return napi_value
             */
            napi_value New(napi_env env, vector<napi_value> wstringVector)
            {
                napi_status status;
                napi_value ResultforArray;
                status = napi_create_array(env, &ResultforArray);
                assert(status == napi_ok);
                for (unsigned index = 0; index < wstringVector.size(); index++)
                {
                    napi_value push_item_data = wstringVector[index];
                    status = napi_set_element(env, ResultforArray, index, push_item_data);
                    assert(status == napi_ok);
                }
                return ResultforArray;
            }
            napi_value New(napi_env env, vector<any> wstringVector)
            {
                napi_status status;
                napi_value ResultforArray;
                status = napi_create_array(env, &ResultforArray);
                assert(status == napi_ok);
                for (unsigned index = 0; index < wstringVector.size(); index++)
                {
                    any push_item_data = wstringVector[index];
                    napi_set_element(env, ResultforArray, index, create_value::New(env, push_item_data));
                    assert(status == napi_ok);
                }
                return ResultforArray;
            }
            /**
             * @brief 创建一个全是文本的数组
             *
             * @param env
             * @param stringVector
             * @return napi_value
             */
            napi_value String(napi_env env, vector<string> stringVector)
            {
                napi_status status;
                napi_value ResultforArray;
                status = napi_create_array(env, &ResultforArray);
                assert(status == napi_ok);
                for (unsigned index = 0; index < stringVector.size(); index++)
                {
                    string push_item_data = stringVector[index];
                    status = napi_set_element(env, ResultforArray, index, create_value::String(env, push_item_data));
                    assert(status == napi_ok);
                }
                return ResultforArray;
            }
            napi_value String(napi_env env, vector<wstring> wstringVector)
            {
                napi_status status;
                napi_value ResultforArray;
                status = napi_create_array(env, &ResultforArray);
                assert(status == napi_ok);
                for (unsigned index = 0; index < wstringVector.size(); index++)
                {
                    wstring push_item_data = wstringVector[index];
                    status = napi_set_element(env, ResultforArray, index, create_value::String(env, push_item_data));
                    assert(status == napi_ok);
                }
                return ResultforArray;
            }
            /**
             * @brief 创建一个全是数字的数组
             *
             * @param env
             * @param intVector
             * @return napi_value
             */
            napi_value Number(napi_env env, vector<int> intVector)
            {
                napi_status status;
                napi_value ResultforArray;
                status = napi_create_array(env, &ResultforArray);
                assert(status == napi_ok);
                for (unsigned index = 0; index < intVector.size(); index++)
                {
                    napi_value push_item;
                    int push_item_data = intVector[index];
                    status = napi_create_int64(env, push_item_data, &push_item);
                    assert(status == napi_ok);
                    status = napi_set_element(env, ResultforArray, index, push_item);
                    assert(status == napi_ok);
                }
                return ResultforArray;
            }
            /**
             * @brief 创建一个全是数字的数组
             *
             * @param env
             * @param intVector
             * @return napi_value
             */
            napi_value Bigint(napi_env env, vector<int> intVector)
            {
                napi_status status;
                napi_value ResultforArray;
                status = napi_create_array(env, &ResultforArray);
                assert(status == napi_ok);
                for (unsigned index = 0; index < intVector.size(); index++)
                {
                    napi_value push_item;
                    int push_item_data = intVector[index];
                    status = napi_create_int64(env, push_item_data, &push_item);
                    assert(status == napi_ok);
                    status = napi_set_element(env, ResultforArray, index, push_item);
                    assert(status == napi_ok);
                }
                return ResultforArray;
            }
            /**
             * @brief 创建一个全是数字的数组
             *
             * @param env
             * @param intVector
             * @return napi_value
             */
            napi_value Boolean(napi_env env, vector<bool> boolVector)
            {
                napi_status status;
                napi_value ResultforArray;
                status = napi_create_array(env, &ResultforArray);
                assert(status == napi_ok);
                for (unsigned index = 0; index < boolVector.size(); index++)
                {
                    napi_value push_item;
                    bool push_item_data = boolVector[index];
                    status = napi_get_boolean(env, push_item_data, &push_item);
                    assert(status == napi_ok);
                    status = napi_set_element(env, ResultforArray, index, push_item);
                    assert(status == napi_ok);
                }
                return ResultforArray;
            }
        }
        namespace Object
        {
            napi_value New(napi_env env);
            napi_value New(napi_env env, map<string, napi_value> mapObject);
            napi_value New(napi_env env, map<string, int> mapObject);
            napi_value New(napi_env env, map<string, string> mapObject);
            napi_value New(napi_env env, map<string, any> mapObject);
            napi_value New(napi_env env, long hmc_obj_id);
            napi_value Object(napi_env env, map<string, string> mapObject);
            napi_value Object(napi_env env, map<string, int> mapObject);
            napi_value Object(napi_env env, map<string, napi_value> mapObject);
            napi_value Object(napi_env env, map<string, any> mapObject);
            napi_value Object(napi_env env, long hmc_obj_id);

            /**
             * @brief 创建一个全是文本的 键值对对象
             *
             * @param env
             * @param mapObject
             * @return napi_value
             */
            napi_value Object(napi_env env, map<string, string> mapObject)
            {
                napi_status status;
                napi_value ResultforObject;
                status = napi_create_object(env, &ResultforObject);
                assert(status == napi_ok);
                map<string, string>::iterator it = mapObject.begin();

                while (it != mapObject.end())
                {
                    status = napi_set_property(env, ResultforObject, create_value::String(env, it->first), create_value::String(env, it->second));
                    assert(status == napi_ok);
                    it++;
                }

                return ResultforObject;
            }
            /**
             * @brief 创建一个全是int的 键值对对象
             *
             * @param env
             * @param mapObject
             * @return napi_value
             */
            napi_value Object(napi_env env, map<string, int> mapObject)
            {
                napi_status status;
                napi_value ResultforObject;
                status = napi_create_object(env, &ResultforObject);
                assert(status == napi_ok);
                map<string, int>::iterator it = mapObject.begin();

                while (it != mapObject.end())
                {
                    status = napi_set_property(env, ResultforObject, create_value::String(env, it->first), create_value::Number(env, it->second));
                    assert(status == napi_ok);
                    it++;
                }

                return ResultforObject;
            }
            /**
             * @brief 创建一个全是napi_value的 键值对对象
             *
             * @param env
             * @param mapObject
             * @return napi_value
             */
            napi_value Object(napi_env env, map<string, napi_value> mapObject)
            {
                napi_status status;
                napi_value ResultforObject;
                status = napi_create_object(env, &ResultforObject);
                assert(status == napi_ok);
                map<string, napi_value>::iterator it = mapObject.begin();

                while (it != mapObject.end())
                {
                    status = napi_set_property(env, ResultforObject, create_value::String(env, it->first), it->second);
                    assert(status == napi_ok);
                    it++;
                }

                return ResultforObject;
            }
            /**
             * @brief 创建一个任意js支持的类型
             *
             * @param env
             * @param mapObject
             * @return napi_value
             */
            napi_value Object(napi_env env, map<string, any> mapObject)
            {
                napi_status status;
                napi_value ResultforObject;
                status = napi_create_object(env, &ResultforObject);
                assert(status == napi_ok);
                map<string, any>::iterator it = mapObject.begin();

                while (it != mapObject.end())
                {
                    status = napi_set_property(env, ResultforObject, create_value::String(env, it->first), create_value::New(env, it->second));
                    assert(status == napi_ok);
                    it++;
                }

                return ResultforObject;
            }
            /**
             * @brief 通过查询id获取对象
             *
             * @param env
             * @param hmc_obj_id
             * @return napi_value
             */
            napi_value Object(napi_env env, long hmc_obj_id)
            {
                if (AllObjectValueList.find(hmc_obj_id) != AllObjectValueList.end())
                {
                    return Object::Object(env, AllObjectValueList[hmc_obj_id]);
                }
                else
                {
                    return Object::New(env);
                }
            }
            napi_value New(napi_env env, map<string, any> mapObject)
            {

                return Object(env, mapObject);
            }
            napi_value New(napi_env env, map<string, string> mapObject)
            {

                return Object(env, mapObject);
            }
            napi_value New(napi_env env, map<string, int> mapObject)
            {

                return Object(env, mapObject);
            }
            napi_value New(napi_env env, map<string, napi_value> mapObject)
            {

                return Object(env, mapObject);
            }
            napi_value New(napi_env env, long hmc_obj_id)
            {
                if (AllObjectValueList.find(hmc_obj_id) != AllObjectValueList.end())
                {
                    return Object::Object(env, AllObjectValueList[hmc_obj_id]);
                }
                else
                {
                    return Object::New(env);
                }
            }
            napi_value New(napi_env env)
            {
                return Object(env, map<string, int>{});
            }
        }
    };

    namespace assert
    {
        template <typename... Args>
        int expect(napi_valuetype valuetype, const napi_valuetype &first, const Args &...args);
        template <typename... Args>
        int expect(napi_env env, napi_value nodeValue, const napi_valuetype &first, const Args &...args);
        string TypeName(napi_valuetype valuetype);
        string TypeName(napi_env env, napi_value valuetype);
        BOOL diff(napi_valuetype valuetype, napi_valuetype valuetype2);
        BOOL diff(napi_env env, napi_value jsValue, napi_valuetype valuetype);
        BOOL diff(napi_env env, napi_value jsValue, napi_value jsValue2);
        bool argsSize(napi_env env, size_t argLength, int ExpectLength[]);
        bool argsSize(napi_env env, size_t argLength, int ExpectLength);

        /**
         * @brief 获取napi数据的类型文本
         *
         * @param valuetype
         * @return string
         */
        string TypeName(napi_valuetype valuetype)
        {
            string getTypeName = string();
            switch (valuetype)
            {
            case napi_null:
                getTypeName.append("null");
                break;
            case napi_number:
                getTypeName.append("number");
                break;
            case napi_string:
                getTypeName.append("string");
                break;
            case napi_undefined:
                getTypeName.append("undefined");
                break;
            case napi_object:
                getTypeName.append("object");
                break;
            case napi_function:
                getTypeName.append("function");
                break;
            case napi_boolean:
                getTypeName.append("boolean");
                break;
            default:
                getTypeName.append("unknown");
            }
            return getTypeName;
        }

        /**
         * @brief 获取napi类型变量名称（人话）
         *
         * @param env
         * @param valuetype
         * @return string
         */
        string TypeName(napi_env env, napi_value valuetype)
        {
            napi_valuetype value_type;
            napi_typeof(env, valuetype, &value_type);
            return TypeName(value_type);
        }

        /**
         * @brief 对比两个变量类型是否相等
         *
         * @param valuetype
         * @param valuetype2
         * @return BOOL
         */
        BOOL diff(napi_valuetype valuetype, napi_valuetype valuetype2)
        {
            return (valuetype == valuetype2);
        }

        BOOL diff(napi_env env, napi_value jsValue, napi_valuetype valuetype)
        {
            napi_valuetype value_type;
            napi_typeof(env, jsValue, &value_type);
            return (valuetype == value_type);
        }

        BOOL diff(napi_env env, napi_value jsValue, napi_value jsValue2)
        {
            napi_valuetype value_type;
            napi_typeof(env, jsValue, &value_type);
            napi_valuetype value_type2;
            napi_typeof(env, jsValue2, &value_type2);
            return (value_type2 == value_type);
        }

        /**
         * @brief 断言是否存在支持的类型 成功则返回类型 失败则报错并返回napi_ass_false
         *
         * @return int
         */
        template <typename... Args>
        int expect(napi_valuetype valuetype, const napi_valuetype &first, const Args &...args)
        {
            int result = napi_ass_false;
            try
            {
                napi_valuetype temp[] = {first, args...};
                size_t length = sizeof(temp) / sizeof(temp[0]);

                for (size_t i = 0; i < length; i++)
                {
                    if (temp[i] == valuetype)
                        return temp[i];
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }
            return result;
        }

        /**
         * @brief 断言是否存在支持的类型 成功则返回类型 失败则报错并返回napi_ass_false
         *
         * @return int
         */
        template <typename... Args>
        int expect(napi_env env, napi_value nodeValue, const napi_valuetype &first, const Args &...args)
        {
            napi_valuetype value_type;
            napi_typeof(env, nodeValue, &value_type);
            int result = napi_ass_false;
            try
            {
                napi_valuetype temp[] = {first, args...};
                size_t length = sizeof(temp) / sizeof(temp[0]);

                for (size_t i = 0; i < length; i++)
                {
                    if (temp[i] == value_type)
                        return temp[i];
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }
            if (_hmc_debug)
            {
            }
            return result;
        }
        /**
         * @brief 判断传入的值数量是否符合当前的要求
         *
         * @param env
         * @param nodeValue
         * @param argLength
         * @param index
         * @return true
         * @return false
         */
        bool argsSize(napi_env env, size_t argLength, int ExpectLength[])
        {
            bool argsSizeOK = false;
            string argSizeEq = "";
            size_t length = sizeof(ExpectLength) / sizeof(ExpectLength[0]);
            for (size_t i = 0; i < length; i++)
            {
                int of_expectLength = ExpectLength[i];
                if (argLength >= of_expectLength)
                {
                    argsSizeOK = true;
                    return argsSizeOK;
                }
                argSizeEq.append(to_string(of_expectLength)).append(" , ");
            }
            if (!argsSizeOK)
            {
                napi_throw_error(env, "EINVAL",
                                 string()
                                     .append("The current number of parameters passed is lower than required. The input is [")
                                     .append(to_string(argLength))
                                     .append("], and the ideal number of parameters should be [")
                                     .append(argSizeEq)
                                     .append("].\n")
                                     .c_str());
            }
            return argsSizeOK;
        }
        /**
         * @brief 判断传入的值数量是否符合当前的要求
         *
         * @param env
         * @param nodeValue
         * @param argLength
         * @param index
         * @return true
         * @return false
         */
        bool argsSize(napi_env env, size_t argLength, int ExpectLength)
        {
            if (argLength >= ExpectLength)
            {
                return true;
            }
            else
            {
                napi_throw_error(env, "EINVAL",
                                 string()
                                     .append("The current number of parameters passed is lower than required. The input is [")
                                     .append(to_string(argLength))
                                     .append("], and the ideal number of parameters should be [")
                                     .append(to_string(ExpectLength))
                                     .append("].\n")
                                     .c_str());
                return false;
            }
        }
    }

    namespace get_value
    {
        int number_int(napi_env env, napi_value nodeValue);
        string string_utf8(napi_env env, napi_value nodeValue);
        string string_ansi(napi_env env, napi_value nodeValue);
        wstring string_wide(napi_env env, napi_value nodeValue);
        int number_int(napi_env env, napi_value nodeValue);
        int64_t number_int64(napi_env env, napi_value nodeValue);
        long long bigint_longlong(napi_env env, napi_value nodeValue);
        double number_double(napi_env env, napi_value nodeValue);
        vector<string> array_string_utf8(napi_env env, napi_value nodeValue);
        vector<double> array_double(napi_env env, napi_value nodeValue);
        vector<int> array_int(napi_env env, napi_value nodeValue);
        UINT showType_UINT(napi_env env, napi_value nodeValue);
        HWND number_HWND(napi_env env, napi_value nodeValue);
        DWORD number_DWORD(napi_env env, napi_value nodeValue);

        /**
         * @brief 获取为utf8标准的文本
         *
         * @param env
         * @param nodeValue
         * @return string
         */
        string string_utf8(napi_env env, napi_value nodeValue)
        {
            string result = string("");
            try
            {
                if (!nodeValue)
                {
                    return result;
                }
                if (hmc_napi_util::assert::diff(env, nodeValue, napi_string))
                {
                    size_t str_len = 0;
                    napi_get_value_string_utf8(env, nodeValue, nullptr, 0, &str_len);
                    result.reserve(str_len + 1);
                    result.resize(str_len);
                    napi_get_value_string_utf8(env, nodeValue, &result[0], result.capacity(), nullptr);
                    return result;
                }
                else if (hmc_napi_util::assert::diff(env, nodeValue, napi_number))
                {
                    result.append(to_string(hmc_napi_util::get_value::number_int(env, nodeValue)));
                    return result;
                }
                else if (hmc_napi_util::assert::diff(env, nodeValue, napi_undefined))
                {
                    return result;
                }
                else
                {
                    if (_hmc_debug)
                    {
                    }
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }

            return result;
        }

        /**
         * @brief 获取为窄(A)文本
         *
         * @param env
         * @param nodeValue
         * @return string
         */
        string string_ansi(napi_env env, napi_value nodeValue)
        {
            return hmc_text_util::U82A(string_utf8(env, nodeValue));
        }

        /**
         * @brief 获取为宽(W)文本
         *
         * @param env
         * @param nodeValue
         * @return wstring
         */
        wstring string_wide(napi_env env, napi_value nodeValue)
        {
            return hmc_text_util::U82W(string_utf8(env, nodeValue));
        }

        /**
         * @brief 数字转int
         *
         * @param env
         * @param nodeValue
         * @return int
         */
        int number_int(napi_env env, napi_value nodeValue)
        {
            int result = 0;
            try
            {
                if (hmc_napi_util::assert::expect(env, nodeValue, napi_number, napi_boolean))
                {
                    napi_get_value_int32(env, nodeValue, &result);
                    return result;
                }

                else if (hmc_napi_util::assert::expect(env, nodeValue, napi_undefined, napi_null))
                {
                    return result;
                }
                else
                {
                    if (_hmc_debug)
                    {
                    }
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }
            return result;
        }

        /**
         * @brief 数字转int64
         *
         * @param env
         * @param nodeValue
         * @return int64_t
         */
        int64_t number_int64(napi_env env, napi_value nodeValue)
        {
            int64_t result = 0;
            try
            {
                if (hmc_napi_util::assert::diff(env, nodeValue, napi_number) || hmc_napi_util::assert::diff(env, nodeValue, napi_boolean))
                {
                    napi_get_value_int64(env, nodeValue, &result);
                    return result;
                }
                else if (hmc_napi_util::assert::expect(env, nodeValue, napi_undefined, napi_boolean, napi_null))
                {
                    return result;
                }
                else
                {
                    if (_hmc_debug)
                    {
                    }
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }

            return result;
        }

        /**
         * @brief 数字转64位浮点
         *
         * @param env
         * @param nodeValue
         * @return double
         */
        double number_double(napi_env env, napi_value nodeValue)
        {
            double result = 0;
            try
            {
                if (hmc_napi_util::assert::diff(env, nodeValue, napi_number) || hmc_napi_util::assert::diff(env, nodeValue, napi_boolean))
                {
                    napi_get_value_double(env, nodeValue, &result);
                    return result;
                }
                else if (hmc_napi_util::assert::expect(env, nodeValue, napi_undefined, napi_boolean, napi_null))
                {
                    return result;
                }
                else
                {
                    if (_hmc_debug)
                    {
                    }
                }
            }
            catch (const std::exception &e)
            {
                return result;
            }
        }

        /**
         * @brief bigint转long
         *
         * @param env
         * @param nodeValue
         * @return long long
         */
        long long bigint_longlong(napi_env env, napi_value nodeValue)
        {
            long long result = 0;
            try
            {
                if (hmc_napi_util::assert::diff(env, nodeValue, napi_bigint) || hmc_napi_util::assert::diff(env, nodeValue, napi_boolean))
                {
                    return result;
                }
                else if (hmc_napi_util::assert::expect(env, nodeValue, napi_undefined, napi_boolean, napi_null))
                {
                    return result;
                }
                else
                {
                    if (_hmc_debug)
                    {
                    }
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }
            return result;
        }

        /**
         * @brief 获取为布尔值
         *
         * @param env
         * @param nodeValue
         * @return true
         * @return false
         */
        bool boolean_bool(napi_env env, napi_value nodeValue)
        {
            bool result = 0;
            try
            {
                if (hmc_napi_util::assert::diff(env, nodeValue, napi_number) || hmc_napi_util::assert::diff(env, nodeValue, napi_boolean))
                {
                    napi_get_value_bool(env, nodeValue, &result);
                    return result;
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }

            return result;
        }

        /**
         * @brief 获取文本数组
         *
         * @param env
         * @param nodeValue
         * @return vector<string>
         */
        vector<string> array_string_utf8(napi_env env, napi_value nodeValue)
        {
            vector<string> unicode_str;

            try
            {
                napi_status status;
                uint32_t size = 0;
                status = napi_get_array_length(env, nodeValue, &size);
                if (status != napi_ok)
                    return unicode_str;

                napi_value value;

                for (size_t i = 0; i < size; i++)
                {
                    status = napi_get_element(env, nodeValue, i, &value);
                    if (status != napi_ok)
                    {
                        if (_hmc_debug)
                        {
                        }
                        return unicode_str;
                    }
                    unicode_str.push_back(string_utf8(env, value));
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }

            return unicode_str;
        }

        /**
         * @brief 获取数字数组
         *
         * @param env
         * @param nodeValue
         * @return vector<int>
         */
        vector<int> array_int(napi_env env, napi_value nodeValue)
        {
            vector<int> num_list;

            try
            {
                napi_status status;
                uint32_t size = 0;
                status = napi_get_array_length(env, nodeValue, &size);
                if (status != napi_ok)
                    return num_list;

                napi_value value;

                for (size_t i = 0; i < size; i++)
                {
                    status = napi_get_element(env, nodeValue, i, &value);
                    if (status != napi_ok)
                    {
                        if (_hmc_debug)
                        {
                        }
                        return num_list;
                    }
                    num_list.push_back(number_int(env, value));
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }

            return num_list;
        }

        /**
         * @brief 获取数字数组
         *
         * @param env
         * @param nodeValue
         * @return vector<int>
         */
        vector<int64_t> array_int64(napi_env env, napi_value nodeValue)
        {
            vector<int64_t> num_list;

            try
            {
                napi_status status;
                uint32_t size = 0;
                status = napi_get_array_length(env, nodeValue, &size);
                if (status != napi_ok)
                    return num_list;

                napi_value value;

                for (size_t i = 0; i < size; i++)
                {
                    status = napi_get_element(env, nodeValue, i, &value);
                    if (status != napi_ok)
                    {
                        if (_hmc_debug)
                        {
                        }
                        return num_list;
                    }
                    num_list.push_back(number_int64(env, value));
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }

            return num_list;
        }

        /**
         * @brief 获取数字数组
         *
         * @param env
         * @param nodeValue
         * @return vector<int>
         */
        vector<double> array_double(napi_env env, napi_value nodeValue)
        {
            vector<double> num_list;

            try
            {
                napi_status status;
                uint32_t size = 0;
                status = napi_get_array_length(env, nodeValue, &size);
                if (status != napi_ok)
                    return num_list;

                napi_value value;

                for (size_t i = 0; i < size; i++)
                {
                    status = napi_get_element(env, nodeValue, i, &value);
                    if (status != napi_ok)
                    {
                        if (_hmc_debug)
                        {
                        }
                        return num_list;
                    }
                    num_list.push_back(number_double(env, value));
                }
            }
            catch (const std::exception &e)
            {
                if (_hmc_debug)
                {
                }
            }

            return num_list;
        }

        /**
         * @brief 将文本的显示状态转为CPP的显示状态代码
         *
         * @param env
         * @param nodeValue
         * @return UINT
         */
        UINT showType_UINT(napi_env env, napi_value nodeValue)
        {

            string key = string_ansi(env, nodeValue);
            if (key == "MB_OK")
                return MB_OK;
            if (key == "MB_ABORTRETRYIGNORE")
                return MB_ABORTRETRYIGNORE;
            if (key == "MB_SERVICE_NOTIFICATION")
                return MB_SERVICE_NOTIFICATION;
            if (key == "MB_TOPMOST")
                return MB_TOPMOST;
            if (key == "MB_SETFOREGROUND")
                return MB_SETFOREGROUND;
            if (key == "MB_RTLREADING")
                return MB_RTLREADING;
            if (key == "MB_RIGHT")
                return MB_RIGHT;
            if (key == "MB_DEFAULT_DESKTOP_ONLY")
                return MB_DEFAULT_DESKTOP_ONLY;
            if (key == "MB_TASKMODAL")
                return MB_TASKMODAL;
            if (key == "MB_SYSTEMMODAL")
                return MB_SYSTEMMODAL;
            if (key == "MB_APPLMODAL")
                return MB_APPLMODAL;
            if (key == "MB_DEFBUTTON4")
                return MB_DEFBUTTON4;
            if (key == "MB_DEFBUTTON3")
                return MB_DEFBUTTON3;
            if (key == "MB_DEFBUTTON2")
                return MB_DEFBUTTON2;
            if (key == "MB_ICONHAND")
                return MB_ICONHAND;
            if (key == "MB_DEFBUTTON1")
                return MB_DEFBUTTON1;
            if (key == "MB_ICONERROR")
                return MB_ICONERROR;
            if (key == "MB_ICONSTOP")
                return MB_ICONSTOP;
            if (key == "MB_ICONQUESTION")
                return MB_ICONQUESTION;
            if (key == "MB_ICONASTERISK")
                return MB_ICONASTERISK;
            if (key == "MB_ICONINFORMATION")
                return MB_ICONINFORMATION;
            if (key == "MB_ICONWARNING")
                return MB_ICONWARNING;
            if (key == "MB_ICONEXCLAMATION")
                return MB_ICONEXCLAMATION;
            if (key == "MB_YESNOCANCEL")
                return MB_YESNOCANCEL;
            if (key == "MB_YESNO")
                return MB_YESNO;
            if (key == "MB_RETRYCANCEL")
                return MB_RETRYCANCEL;
            if (key == "MB_OKCANCEL")
                return MB_OKCANCEL;
            if (key == "MB_HELP")
                return MB_HELP;
            if (key == "MB_CANCELTRYCONTINUE")
                return MB_CANCELTRYCONTINUE;

            return MB_OK;
        }

        /**
         * @brief 转 DWORD
         *
         * @param env
         * @param nodeValue
         * @return DWORD
         */
        DWORD number_DWORD(napi_env env, napi_value nodeValue)
        {
            DWORD result = (DWORD)number_int64(env, nodeValue);
            return result;
        }

        /**
         * @brief 转窗口句柄
         *
         * @param env
         * @param nodeValue
         * @return HWND
         */
        HWND number_HWND(napi_env env, napi_value nodeValue)
        {
            HWND result = (HWND)number_int64(env, nodeValue);
            return result;
        }
        /**
         * @brief 获取buff
         *
         * @param env
         * @param nodeValue
         * @param buffer
         */
        template <typename T>
        void buffer_vector(napi_env env, napi_value nodeValue, vector<T> &buffer)
        {
            try
            {
                napi_status status;
                T *dataPtr;
                size_t len;
                status = napi_get_buffer_info(env, nodeValue, reinterpret_cast<void **>(&dataPtr), &len);
                if (status != napi_ok)
                    return;
                // buffer.resize(len);
                buffer.insert(buffer.begin(), dataPtr, dataPtr + len);
            }
            catch (const std::exception &e)
            {
            }
        }

        vector<unsigned char> buffer_vector(napi_env env, napi_value nodeValue)
        {
            vector<unsigned char> buffer;
            buffer_vector<unsigned char>(env, nodeValue, buffer);
            return buffer;
        }

        wstring buffer_utf16_buffer_strW(napi_env env, napi_value nodeValue)
        {
            vector<wchar_t> buffer;
            buffer_vector<wchar_t>(env, nodeValue, buffer);
            std::wstring wideString(buffer.begin(), buffer.end()); // 将 std::vector<wchar_t> 转换为 std::wstring
            return wideString;
        }

        string buffer_ansi_buffer_strA(napi_env env, napi_value nodeValue)
        {
            vector<unsigned char> buffer;
            buffer_vector<unsigned char>(env, nodeValue, buffer);
            std::string ansiString(buffer.begin(), buffer.end());
            return ansiString;
        }

        string buffer_utf8_buffer_strU8(napi_env env, napi_value nodeValue)
        {
            vector<unsigned char> buffer;
            buffer_vector<unsigned char>(env, nodeValue, buffer);
            std::string utf8String(buffer.begin(), buffer.end());
            return utf8String;
        }

        LPCWSTR buffer_utf16_buffer_lpStrW(napi_env env, napi_value nodeValue)
        {
            vector<wchar_t> buffer;
            buffer_vector<wchar_t>(env, nodeValue, buffer);
            std::wstring wideString(buffer.begin(), buffer.end()); // 将 std::vector<wchar_t> 转换为 std::wstring
            wchar_t *utf16Ptr = new wchar_t[wideString.size() + sizeof(wchar_t)];

            for (size_t i = 0; i < wideString.size(); i++)
            {
                char data = wideString[i];
                utf16Ptr[i] = data;
            }
            const int end = wideString.size();

            utf16Ptr[end] = *L"\0";

            return utf16Ptr;
        }

        LPCSTR buffer_utf8_buffer_lpStrU8(napi_env env, napi_value nodeValue)
        {
            vector<unsigned char> buffer;
            buffer_vector<unsigned char>(env, nodeValue, buffer);
            std::string utf8String(buffer.begin(), buffer.end());

            char *utf8Ptr = new char[utf8String.size() + sizeof(char)];

            for (size_t i = 0; i < utf8String.size(); i++)
            {
                char data = utf8String[i];
                utf8Ptr[i] = data;
            }
            const int end = utf8String.size();

            utf8Ptr[end] = *"\0";

            return utf8Ptr;
        }

        LPCSTR buffer_ansi_buffer_lpStrA(napi_env env, napi_value nodeValue)
        {
            vector<unsigned char> buffer;
            buffer_vector<unsigned char>(env, nodeValue, buffer);
            std::string ansiString(buffer.begin(), buffer.end());

            char *ansiPtr = new char[ansiString.size() + sizeof(char)];

            for (size_t i = 0; i < ansiString.size(); i++)
            {
                char data = ansiString[i];
                ansiPtr[i] = data;
            }
            const int end = ansiString.size();

            ansiPtr[end] = *"\0";

            return ansiPtr;
        }
    };

    /**
     * @brief 启用hmc的开发者模式 将会对所有传递值和错误进行报错 而不是尽可能完成任务
     *
     * @param is_debug
     */
    void set_hmc_debug(bool is_debug)
    {
        _hmc_debug = is_debug;
        return;
    }
    /**
     * @brief 判断是否处于debug
     *
     * @return true
     * @return false
     */
    bool has_hmc_debug()
    {
        return _hmc_debug;
    }

}
