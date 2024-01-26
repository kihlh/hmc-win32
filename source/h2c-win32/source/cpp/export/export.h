#include <node_api.h>



// clip.cpp
extern napi_value getClipboardFilePaths(napi_env env, napi_callback_info info);
extern napi_value setClipboardText(napi_env env, napi_callback_info info);
extern napi_value getClipboardText(napi_env env, napi_callback_info info);
extern napi_value clearClipboard(napi_env env, napi_callback_info info);
extern napi_value setClipboardFilePaths(napi_env env, napi_callback_info info);
extern napi_value getClipboardInfo(napi_env env, napi_callback_info info);
extern napi_value enumClipboardFormats(napi_env env, napi_callback_info info);
extern napi_value getClipboardHTML(napi_env env, napi_callback_info info);
extern napi_value ClipboardFunc(napi_env env, napi_callback_info info);


// shell.cpp
extern napi_value fn_shellFile(napi_env env, napi_callback_info info);
