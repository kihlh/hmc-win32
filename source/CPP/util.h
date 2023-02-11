#include <windows.h>
#include <node_api.h>
#include <string>
#include <assert.h>
#include <stringapiset.h>
#include <vector>

using namespace std;
#ifdef UNICODE
typedef LPWSTR LPTSTR;
typedef LPCWSTR LPCTSTR;
#else
typedef LPSTR LPTSTR;
typedef LPCSTR LPCTSTR;
#endif
napi_value _create_false_Boolean(napi_env env);

napi_value _create_true_Boolean(napi_env env);

napi_value _create_bool_Boolean(napi_env env, bool SetBoolean);

napi_value _create_String_Array(napi_env env, vector<string> stringVector);

napi_value _create_int64_Number(napi_env env, int64_t SetNumber);

napi_value _create_int32_Number(napi_env env, int SetNumber);

napi_value _create_W2U8_string(napi_env env, wchar_t *SetString);

napi_value _create_A2U8_string(napi_env env, char *SetString);

napi_value _create_String(napi_env env, string SetString);

napi_value _create_char_string(napi_env env, char *SetString);

napi_value _create_buff_Buffer(napi_env env, void **data, size_t size);

string UTF8ToGBK(const char *str);

inline string _A2U8_(const char *pszText);
inline wstring _A2W_(const char *pszText);
inline string _U82A_(const char *pszText);
inline wstring _U82W_(const char *pszText);
inline string _W2A_(const wchar_t *pwszText);
inline string _W2U8_(const wchar_t *pwszText);

string _NAPI_Call_Type(napi_valuetype valuetype0);
wstring call_String_NAPI_WINAPI_W(napi_env env, napi_value value);

string call_String_NAPI_WINAPI_A(napi_env env, napi_value value);

string call_String_NAPI_UTF8(napi_env env, napi_value value);
