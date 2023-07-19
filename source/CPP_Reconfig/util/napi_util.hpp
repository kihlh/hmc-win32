#define NAPI_EXPERIMENTAL // 开启实验性功能 比如异步(多线程)
#include <node_api.h>
#include <assert.h>
#include <any>
#include "./text.hpp"
#include "./environment.hpp"

#define _HMC_ALL_UTIL 0x0666
using namespace std;
// using namespace hmc_text_util;
using namespace hmc_env;

namespace napi_util
{

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
        napi_value Buffer(napi_env env, void **data, size_t size)
        {
            napi_status status;
            napi_value Results;
            status = napi_create_buffer(env, size, data, &Results);
            assert(status == napi_ok);
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

            napi_value New(napi_env env)
            {
                return Object(env, map<string, int>{});
            }
        }
    };

    namespace assert
    { /**
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

    }

    namespace get_value
    {
        string stringU8(napi_env env, napi_value nodeValue)
        {
            string result = string("");
            if (!nodeValue)
            {
                return result;
            }
            if (napi_util::assert::diff(env, nodeValue, napi_string))
            {
                size_t str_len = 0;
                napi_get_value_string_utf8(env, nodeValue, nullptr, 0, &str_len);
                result.reserve(str_len + 1);
                result.resize(str_len);
                napi_get_value_string_utf8(env, nodeValue, &result[0], result.capacity(), nullptr);
                return result;
            }
        }
        string stringA(napi_env env, napi_value nodeValue)
        {
            return hmc_text_util::U82A(stringU8(env, nodeValue));
        }

        wstring stringW(napi_env env, napi_value nodeValue)
        {
            return hmc_text_util::U82W(stringU8(env, nodeValue));
        }
    };

    bool _hmc_debug = false;

}
