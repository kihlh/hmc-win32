#include "./export.h"
#include "hmc_string_util.h"
#include "hmc_napi_value_util.h"
#include "hmc_string_util.h"
#include "hmc_shell_util.h"
#include "hmc_process_util.h"

// 获取托盘图标
napi_value getTrayList(napi_env env, napi_callback_info info)
{
    return hmc_napi_create_value::String(env, hmc_shell_util::GetTaryIconList::getTrayListJsonW());
}

napi_value trashFile(napi_env env, napi_callback_info info)
{
    napi_value result = as_Number32(0x10000);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string},
              {1, js_boolean},
              {2, js_boolean}});

    std::wstring trash_path = at_StringW(0);
    bool is_Recycle = at_BooleanOr(1, true);
    bool isShow = at_BooleanOr(2, true);

    int trash_ok = hmc_shell_util::trashFile(trash_path, is_Recycle, isShow);
    result = as_Number32(trash_ok);
    return result;
}

napi_value copyFile(napi_env env, napi_callback_info info)
{
    napi_value result = as_Boolean(false);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string},
              {1, js_string},
              {2, js_boolean},
              {3, js_boolean},
              {4, js_boolean}},
             true);

    std::wstring filePath = at_StringW(0);
    std::wstring newFilePath = at_StringW(1);
    bool isShowConfirm = at_BooleanOr(2, true);
    bool isShow = at_BooleanOr(3, true);
    bool isShowProgress = at_BooleanOr(4, true);
    bool trash_ok = hmc_shell_util::copyFile(filePath, newFilePath, isShowConfirm, isShow, isShowProgress);

    result = as_Boolean(trash_ok);

    return result;
}

napi_value moveFile(napi_env env, napi_callback_info info)
{
    napi_value result = as_Boolean(false);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string},
              {1, js_string},
              {2, js_boolean},
              {3, js_boolean},
              {4, js_boolean}},
             true);

    std::wstring filePath = at_StringW(0);
    std::wstring newFilePath = at_StringW(1);
    bool isShowConfirm = at_BooleanOr(2, true);
    bool isShow = at_BooleanOr(3, true);
    bool isShowProgress = at_BooleanOr(4, true);

    bool trash_ok = hmc_shell_util::moveFile(filePath, newFilePath, isShowConfirm, isShow, isShowProgress);

    result = as_Boolean(trash_ok);

    return result;
}

napi_value clearTrash(napi_env env, napi_callback_info info)
{
    napi_value result = as_Boolean(false);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string},
              {1, js_boolean}},
             true);
    bool trash_ok = false;

    std::wstring RootPath = at_StringWOr(0, L"");
    bool isShow = at_BooleanOr(1, true);

    DWORD show_flag = isShow ? NULL : SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND;

    trash_ok = hmc_shell_util::clearTrash(NULL, RootPath, show_flag);
    result = as_Boolean(trash_ok);
    return result;
}

napi_value getThumbnailPng(napi_env env, napi_callback_info info)
{
    napi_value result = as_Null();
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string},
              {1, js_number}},
             true);
    bool trash_ok = false;

    std::wstring source = at_StringWOr(0, L"");
    int isShow = at_Number32Or(1, 256);

    std::vector<std::uint8_t> buff = hmc_shell_util::getThumbnailPng(source, isShow);

    if (!buff.empty())
    {
        return as_Buffer(buff);
    }

    return result;
}

napi_value getLinkTarget(napi_env env, napi_callback_info info)
{
    napi_value result = as_Null();
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string}},
             true);

    std::wstring Linkath = at_StringWOr(0, L"");

    // 硬链接·
    if (hmc_shell_util::Symlink::isHardLink(Linkath))
    {
        auto buff = hmc_shell_util::Symlink::getHardLinkList(at_StringW(0));

        if (!buff.empty())
        {
            return hmc_napi_create_value::Array::String(env, buff);
        }
    }

    // 软链接
    if (hmc_shell_util::Symlink::isLink(Linkath))
    {
        auto buff = hmc_shell_util::Symlink::getSymbolicLinkTarget(at_StringW(0));

        if (!buff.empty())
        {
            return as_String(buff);
        }
    }

    return result;
}

napi_value setFolderIcon(napi_env env, napi_callback_info info)
{
    napi_value result = as_Boolean(false);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string}, {1, js_string}}, true);

    std::wstring folderPath = at_StringW(0);
    std::wstring iconPath = at_StringW(0);
    int iconIndex = at_Number32(0);

    bool c_result = hmc_shell_util::SetFolderIcon(folderPath, iconPath, iconIndex);

    result = as_Boolean(c_result);

    return result;
}

napi_value isHardLink(napi_env env, napi_callback_info info)
{
    napi_value result = as_Boolean(false);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq(0, js_string, true);

    std::wstring atPath = at_StringW(0);

    bool c_result = hmc_shell_util::Symlink::isHardLink(atPath);

    result = as_Boolean(c_result);

    return result;
}

napi_value isLinkLink(napi_env env, napi_callback_info info)
{
    napi_value result = as_Number32(0);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq(0, js_string, true);

    std::wstring atPath = at_StringW(0);

    if (hmc_shell_util::Symlink::isHardLink(atPath))
    {
        result = as_Number32(2);
    }

    if (hmc_shell_util::Symlink::isLink(atPath))
    {
        result = as_Number32(6);
    }

    return result;
}

napi_value setShortcutLink(napi_env env, napi_callback_info info)
{
    napi_value result = as_Boolean(false);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string},
              {1, js_string},
              {2, js_string},
              {3, js_string},
              {4, js_string},
              {5, js_number},
              {6, js_string},
              {7, js_number}},
             true);

    std::wstring lnkPath = at_StringW(0);
    std::wstring FilePath = at_StringW(1);
    std::wstring work_dir = at_StringW(2);
    std::wstring desc = at_StringW(3);
    std::wstring args = at_StringW(4);
    DWORD iShowCmd = at_Number32(5);
    std::wstring icon = at_StringW(6);
    DWORD iconIndex = at_Number32(7);

    bool c_result = hmc_shell_util::setShortcutLink(lnkPath, FilePath, work_dir, desc, args, iShowCmd, icon, iconIndex);

    result = as_Boolean(c_result);

    return result;
}

napi_value getShortcutLink(napi_env env, napi_callback_info info)
{
    napi_value result = as_Null();
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string}},
             true);

    std::wstring lnkPath = at_StringW(0);

    auto c_result = hmc_shell_util::getShortcutLink(lnkPath);
    if (c_result.isValid())
    {

        napi_value Results;
        napi_create_object(env, &Results);

        hmc_napi_create_value::Object::putValue(env, Results, "path", as_String(c_result.path));
        hmc_napi_create_value::Object::putValue(env, Results, "showCmd", as_Number32(c_result.showCmd));
        hmc_napi_create_value::Object::putValue(env, Results, "args", as_String(c_result.args));
        hmc_napi_create_value::Object::putValue(env, Results, "desc", as_String(c_result.desc));
        hmc_napi_create_value::Object::putValue(env, Results, "icon", as_String(c_result.icon));
        hmc_napi_create_value::Object::putValue(env, Results, "iconIndex", as_Number32(c_result.iconIndex));
        hmc_napi_create_value::Object::putValue(env, Results, "cwd", as_String(c_result.cwd));
        hmc_napi_create_value::Object::putValue(env, Results, "hotkey", as_Number32(c_result.hotkey));

        return Results;
    }

    return result;
}

napi_value powerControl(napi_env env, napi_callback_info info)
{
    auto input = hmc_NodeArgsValue(env, info);
    input.eq(0, js_string, true);

    int atFlage = at_Number32(0);

    // 1001: // 关机
    // 1002: // 重启
    // 1003: // 注销
    // 1005: // 锁定
    // 1006: // 关闭显示器
    // 1007: // 打开显示器
    if (atFlage > 1000 && atFlage < 1010)
    {
        hmc_shell_util::powerControl(atFlage);
    }

    // beep
    if (atFlage == 6660)
    {
        hmc_shell_util::beep();
    }

    return NULL;
}

napi_value createFsLink(napi_env env, napi_callback_info info)
{
    napi_value result = as_Boolean(false);
    auto input = hmc_NodeArgsValue(env, info);

    input.eq({{0, js_number}, {1, js_string}, {2, js_string}}, true);

    int targetType = at_Number32(0);
    std::wstring targetPath = at_StringW(1);
    std::wstring sourcePath = at_StringW(2);

    bool c_result = false;

    // 文件夹链接
    const int CREATE_DIR_SYMLINK = 166;
    // 软链接
    const int CREATE_SYMLINK = 168;
    // 硬链接
    const int CREATE_HARD_LINK = 170;
    // 目录连接点
    const int CREATE_SYMBOLIC_LINK = 172;

    switch (targetType)
    {
    case CREATE_DIR_SYMLINK:
        c_result = hmc_shell_util::Symlink::createDirSymlink(targetPath, sourcePath);
        break;
    case CREATE_SYMLINK:
        c_result = hmc_shell_util::Symlink::createSymlink(targetPath, sourcePath);
        break;
    case CREATE_HARD_LINK:
        c_result = hmc_shell_util::Symlink::createHardLink(targetPath, sourcePath);
        break;
    case CREATE_SYMBOLIC_LINK:
        c_result = hmc_shell_util::Symlink::createSymbolicLink(targetPath, sourcePath);
        break;
    }

    result = as_Boolean(c_result);
    return result;
}

napi_value getSystemMetrics(napi_env env, napi_callback_info info)
{
    napi_value result = as_Number32(0);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq(0, js_number, true);

    int nIndex = at_Number32(0);

    if (nIndex > 999999)
    {
        result = as_Number(::GetSystemMetrics(nIndex));
        return result;
    }

    if (nIndex == 1000000)
    {
        result = as_Number((int)hmc_shell_util::isSystemFor64bit());
        return result;
    }

    if (nIndex == 1100001)
    {
        result = as_Number((int)hmc_shell_util::isFocusWindowFullScreen());
        return result;
    }

    if (nIndex == 1200002)
    {
        result = as_Number((int)hmc_shell_util::isFullScreen());
        return result;
    }

    if (nIndex == 1300003)
    {
        result = as_Number((int64_t)hmc_shell_util::getTimestamp(false));
        return result;
    }

    if (nIndex == 1400004)
    {
        result = as_Number((int64_t)hmc_shell_util::getSystemIdleTime());
        return result;
    }

    if (nIndex == 1500005)
    {
        result = as_Number((int64_t)::GetTickCount64());
        return result;
    }

    if (nIndex == 1600006)
    {
        result = as_Number((int)hmc_process_util::isProcessWow64());
        return result;
    }

    if (nIndex == 1700007)
    {
        DWORD pid = _getpid();
        result = as_Number((int64_t)hmc_process_util::getProcessStartTime(pid));
        return result;
    }

    if (nIndex == 1800008)
    {
        result = as_Number((int)IsUserAnAdmin());
        return result;
    }

    return result;
}

napi_value showContextMenu(napi_env env, napi_callback_info info)
{
    napi_value result = as_Boolean(false);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_number},
              {1, js_string},
              {2, js_number},
              {3, js_number}},
             true);

    HWND hwnd = (HWND)at_Number64(0);
    std::wstring filePath = at_StringW(1);
    int x = at_Number32(2);
    int y = at_Number32(3);

    bool c_result_ok = hmc_shell_util::showContextMenu(hwnd, filePath, x, y);

    result = as_Boolean(c_result_ok);

    return result;
}

napi_value setConversionStatus(napi_env env, napi_callback_info info)
{
    napi_value result = as_Boolean(false);
    auto input = hmc_NodeArgsValue(env, info);
    input.eq({{0, js_string},
              {1, js_number},
              {2, js_number}},
             true);

    HWND hwnd = (HWND)at_Number64(0);

    DWORD sentencePatterns = at_Number64(1);
    DWORD unnamedParam3 = at_Number64(2);

    bool c_result_ok = hmc_shell_util::setConversionStatus(hwnd, sentencePatterns, unnamedParam3);

    result = as_Boolean(c_result_ok);

    return result;
}
