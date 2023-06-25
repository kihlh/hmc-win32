#define NAPI_EXPERIMENTAL // 开启实验性功能 比如异步(多线程)
#include <node_api.h>
#include <assert.h>
#include "./text.hpp"
#include "./environment.hpp"

#define _HMC_ALL_UTIL 0x0666
using namespace std;
using namespace hmc_text_util;
using namespace hmc_env;

namespace napi_util
{
    namespace text_util
    {
        using namespace hmc_text_util;
    };
    namespace env
    {
        using namespace hmc_env;
    };

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

        // 返回一个 false js value
        napi_value _false(napi_env env)
        {
            return Boolean(env, false);
        }

        // 返回一个true js value
        napi_value _true(napi_env env)
        {
            return Boolean(env, true);
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
        // 返回一个 ""
        napi_value _string(napi_env env)
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
        namespace Array
        {

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
                    napi_value push_item;
                    string push_item_data = stringVector[index];
                    status = napi_create_string_utf8(env, push_item_data.c_str(), NAPI_AUTO_LENGTH, &push_item);
                    assert(status == napi_ok);
                    status = napi_set_element(env, ResultforArray, index, push_item);
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
                    napi_value push_item;
                    wstring push_item_data = wstringVector[index];
                    status = napi_create_string_utf8(env, W2U8(push_item_data).c_str(), NAPI_AUTO_LENGTH, &push_item);
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
    };

    namespace get_value
    {

    };

    namespace assert
    {

    }
}
