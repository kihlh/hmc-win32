#include <windows.h>
#include <node_api.h>
#include <string>
#include <assert.h>
#include <stringapiset.h>
#include <vector>
#include <tchar.h>
#include <map>
#include <any>

// #include <locale>
// #include <codecvt>
using namespace std;
#ifdef UNICODE
typedef LPWSTR LPTSTR;
typedef LPCWSTR LPCTSTR;
#else
typedef LPSTR LPTSTR;
typedef LPCSTR LPCTSTR;
#endif

// string _NAPI_Call_Type(napi_valuetype valuetype0);
// wstring call_String_NAPI_WINAPI_W(napi_env env, napi_value value);

// string call_String_NAPI_WINAPI_A(napi_env env, napi_value value);

string call_String_NAPI_UTF8(napi_env env, napi_value value);

bool util_diff_napi_type(napi_env env, napi_value value, napi_valuetype valuetype);
napi_valuetype util_get_napi_type(napi_env env, napi_value value);
string util_get_napi_type_name(napi_env env, napi_value value);

struct hmcRect;
bool rectInRect(hmcRect inRect, hmcRect mian);
hmcRect RECT2Rect(RECT inputRect);
bool RECTinRECT(RECT inRect, RECT mian);
bool pointInRect(POINT pt, hmcRect rect);
bool isInside(int x1, int y1, int x2, int y2, int x, int y);
vector<RECT> GetDeviceCapsAll();