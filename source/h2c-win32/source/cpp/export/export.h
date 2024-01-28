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

// shell.cpp
extern napi_value getTrayList(napi_env env, napi_callback_info info);
extern napi_value trashFile(napi_env env, napi_callback_info info);
extern napi_value copyFile(napi_env env, napi_callback_info info);
extern napi_value moveFile(napi_env env, napi_callback_info info);
extern napi_value clearTrash(napi_env env, napi_callback_info info);
extern napi_value getThumbnailPng(napi_env env, napi_callback_info info);
extern napi_value getLinkTarget(napi_env env, napi_callback_info info);
extern napi_value setFolderIcon(napi_env env, napi_callback_info info);
extern napi_value isLinkLink(napi_env env, napi_callback_info info);
extern napi_value setShortcutLink(napi_env env, napi_callback_info info);
extern napi_value createFsLink(napi_env env, napi_callback_info info);
extern napi_value getSystemMetrics(napi_env env, napi_callback_info info);
extern napi_value getShortcutLink(napi_env env, napi_callback_info info);
extern napi_value showContextMenu(napi_env env, napi_callback_info info);
extern napi_value setConversionStatus(napi_env env, napi_callback_info info);