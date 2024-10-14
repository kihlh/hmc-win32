#include "export.h"
#include "hmc_string_util.h"
#include "hmc_napi_value_util.h"
#include "hmc_string_util.h"
#include "hmc_shell_util.h"
#include "hmc_process_util.h"
#include "hmc_usb_util.h"
#include "hmc_path_util.h"

#include "hmc_util.h"

#include <ShlObj.h>

namespace HMC_shell
{

    // // 获取托盘图标
    // napi_value getTrayList(napi_env env, napi_callback_info info)
    // {
    //     return hmc_napi_create_value::String(env, hmc_shell_util::GetTaryIconList::getTrayListJsonW());
    // }

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

        if (input.eq({js_string, js_number}, false))
        {

            std::wstring source = at_StringWOr(0, L"");
            int img_size = at_Number32Or(1, 256);

            std::vector<std::uint8_t> buff = hmc_shell_util::getThumbnailBuffer(source, img_size);

            if (!buff.empty())
            {
                return as_Buffer(buff);
            }
        }

        if (input.eq({js_string, js_string, js_number}, false))
        {

            std::wstring source = at_StringWOr(0, L"");
            std::wstring output = at_StringWOr(1, L"");
            int img_size = at_Number32Or(2, 256);

            bool is_ok = hmc_shell_util::getThumbnailToFile(source, output, img_size);

            return as_Boolean(is_ok);
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
                auto Result = hmc_napi_create_value::jsArray(env);
                for (auto &&item : buff)
                {
                    Result.putString(item, item.size());
                }

                return Result.toValue();
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
        std::wstring iconPath = at_StringW(1);
        int iconIndex = at_Number32Or(2, 0);

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

            auto Results = hmc_napi_create_value::jsObject(env);

            Results.putValue("path", as_String(c_result.path));
            Results.putValue("showCmd", as_Number32(c_result.showCmd));
            Results.putValue("args", as_String(c_result.args));
            Results.putValue("desc", as_String(c_result.desc));
            Results.putValue("icon", as_String(c_result.icon));
            Results.putValue("iconIndex", as_Number32(c_result.iconIndex));
            Results.putValue("cwd", as_String(c_result.cwd));
            Results.putValue("hotkey", as_Number32(c_result.hotkey));

            return Results.toValue();
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
            bool isadmin = IsUserAnAdmin();

            result = as_Number((int)isadmin);
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

    napi_ref CONSTRUCTOR_LIFETIME_HANDLE = NULL;

    napi_value StartupClassConstructor(napi_env env, napi_callback_info info)
    {

        // if(CONSTRUCTOR_LIFETIME_HANDLE!=NULL){
        //     return NULL;
        // }

        napi_value constructor;
        napi_value result;
        napi_status status;

        napi_create_object(env, &result);
        // DECLARE_NAPI_METHODRM("getTrayList", getTrayList),
        // DECLARE_NAPI_METHODRM("trashFile", trashFile),
        // DECLARE_NAPI_METHODRM("clearTrash", clearTrash),
        // DECLARE_NAPI_METHODRM("copyFile", copyFile),
        // DECLARE_NAPI_METHODRM("moveFile", moveFile),
        // DECLARE_NAPI_METHODRM("getThumbnailPng", getThumbnailPng),
        // DECLARE_NAPI_METHODRM("getLinkTarget", getLinkTarget),
        // DECLARE_NAPI_METHODRM("setFolderIcon", setFolderIcon),
        // DECLARE_NAPI_METHODRM("isLinkLink", isLinkLink),
        // DECLARE_NAPI_METHODRM("setShortcutLink", setShortcutLink),
        // DECLARE_NAPI_METHODRM("createFsLink", createFsLink),
        // DECLARE_NAPI_METHODRM("getSystemMetrics", getSystemMetrics),
        // DECLARE_NAPI_METHODRM("getShortcutLink", getShortcutLink),
        // DECLARE_NAPI_METHODRM("showContextMenu", showContextMenu),
        // DECLARE_NAPI_METHODRM("setConversionStatus", setConversionStatus),
        // napi_set_named_property(env, result, as_ExFunctionNameAp(getTrayList));
        napi_set_named_property(env, result, as_ExFunctionNameAp(trashFile));
        napi_set_named_property(env, result, as_ExFunctionNameAp(clearTrash));
        napi_set_named_property(env, result, as_ExFunctionNameAp(copyFile));
        napi_set_named_property(env, result, as_ExFunctionNameAp(moveFile));
        napi_set_named_property(env, result, as_ExFunctionNameAp(getLinkTarget));
        napi_set_named_property(env, result, as_ExFunctionNameAp(setFolderIcon));
        napi_set_named_property(env, result, as_ExFunctionNameAp(isLinkLink));
        napi_set_named_property(env, result, as_ExFunctionNameAp(setShortcutLink));
        napi_set_named_property(env, result, as_ExFunctionNameAp(createFsLink));
        napi_set_named_property(env, result, as_ExFunctionNameAp(getSystemMetrics));
        napi_set_named_property(env, result, as_ExFunctionNameAp(getShortcutLink));
        napi_set_named_property(env, result, as_ExFunctionNameAp(showContextMenu));
        napi_set_named_property(env, result, as_ExFunctionNameAp(setConversionStatus));

        // 注册长生命周期
        status = napi_create_reference(env, result, 1, &CONSTRUCTOR_LIFETIME_HANDLE);
        if (status != napi_ok)
            return NULL;

        return result;
    }

}

namespace HMC_shell_startup
{

    napi_value has(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Boolean(false);
        auto input = hmc_NodeArgsValue(env, info);
        input.eq({{0, js_string}}, true);

        std::wstring keyName = at_StringW(0);

        bool c_result_ok = hmc_shell_util::Startup::has(keyName);

        result = as_Boolean(c_result_ok);

        return result;
    }

    napi_value hasOnce(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Boolean(false);
        auto input = hmc_NodeArgsValue(env, info);
        input.eq({{0, js_string}}, true);

        std::wstring keyName = at_StringW(0);

        bool c_result_ok = hmc_shell_util::Startup::hasOnce(keyName);

        result = as_Boolean(c_result_ok);

        return result;
    }

    napi_value remove(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Boolean(false);
        auto input = hmc_NodeArgsValue(env, info);
        input.eq({{0, js_string}}, true);

        std::wstring keyName = at_StringW(0);

        bool c_result_ok = hmc_shell_util::Startup::remove(keyName);

        result = as_Boolean(c_result_ok);

        return result;
    }

    napi_value removeOnce(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Boolean(false);
        auto input = hmc_NodeArgsValue(env, info);
        input.eq({{0, js_string}}, true);

        std::wstring keyName = at_StringW(0);

        bool c_result_ok = hmc_shell_util::Startup::removeOnce(keyName);

        result = as_Boolean(c_result_ok);

        return result;
    }

    napi_value set(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Boolean(false);
        auto input = hmc_NodeArgsValue(env, info);
        input.eq({{0, js_string},
                  {1, js_string},
                  {2, js_string}},
                 true);

        std::wstring keyName = at_StringW(0);
        std::wstring execPath = at_StringW(1);
        std::wstring cmd = at_StringW(2);

        bool c_result_ok = hmc_shell_util::Startup::set(keyName, execPath, cmd);

        result = as_Boolean(c_result_ok);

        return result;
    }

    napi_value setOnce(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Boolean(false);
        auto input = hmc_NodeArgsValue(env, info);
        input.eq({{0, js_string},
                  {1, js_string},
                  {2, js_string}},
                 true);

        std::wstring keyName = at_StringW(0);
        std::wstring execPath = at_StringW(1);
        std::wstring cmd = at_StringW(2);

        bool c_result_ok = hmc_shell_util::Startup::set(keyName, execPath, cmd);

        result = as_Boolean(c_result_ok);

        return result;
    }

    napi_ref CONSTRUCTOR_LIFETIME_HANDLE = NULL;

    napi_value StartupClassConstructor(napi_env env, napi_callback_info info)
    {

        // if(CONSTRUCTOR_LIFETIME_HANDLE!=NULL){
        //     return NULL;
        // }

        napi_value constructor;
        napi_value result;
        napi_status status;

        napi_create_object(env, &result);

        napi_set_named_property(env, result, as_ExFunctionNameAp(set));
        napi_set_named_property(env, result, as_ExFunctionNameAp(setOnce));
        napi_set_named_property(env, result, as_ExFunctionNameAp(remove));
        napi_set_named_property(env, result, as_ExFunctionNameAp(removeOnce));
        napi_set_named_property(env, result, as_ExFunctionNameAp(has));
        napi_set_named_property(env, result, as_ExFunctionNameAp(hasOnce));

        // 注册长生命周期
        status = napi_create_reference(env, result, 1, &CONSTRUCTOR_LIFETIME_HANDLE);
        if (status != napi_ok)
            return NULL;

        return result;
    }
}

std::any GetThumbnailPng2::ExecuteWorkFun(napi_env env, size_t TASK_TYPE, std::vector<std::any> *data_list)
{
    std::any result = std::any();
    auto arg = hmc_util::anyCastList(data_list);

    if (arg.empty() && arg.is_wstring(0) && arg.is_integral(1) && arg.is_wstring(1))
    {
        return result;
    }

    std::wstring filePath = std::any_cast<std::wstring>(data_list->at(0));
    size_t img_size = std::any_cast<size_t>(data_list->at(1));
    std::wstring output = std::any_cast<std::wstring>(data_list->at(2));

    if (!img_size || img_size > 50000)
    {
        img_size = 256;
    }

    if (output.empty())
    {
        std::vector<std::uint8_t> buff = hmc_shell_util::getThumbnailBuffer(filePath, img_size);

        if (!buff.empty())
        {
            result = buff;
        }

        return result;
    }

    result = hmc_shell_util::getThumbnailToFile(filePath, output, img_size);

    return result;
}

bool GetThumbnailPng2::FormatArg(napi_env env, napi_callback_info info, hmc_NodeArgsValue input, std::vector<std::any> *arguments_list)
{
    bool result = true;

    if (input.eq({js_string, js_string, js_number}, false))
    {
        std::wstring source = at_StringWOr(0, L"");
        std::wstring output = at_StringWOr(1, L"");
        size_t img_size = at_Number32Or(2, 256);
        arguments_list->push_back(source);
        arguments_list->push_back(img_size);
        arguments_list->push_back(output);

        return result;
    }

    if (input.eq({js_string, js_number, js_string}, false))
    {
        std::wstring source = at_StringWOr(0, L"");
        size_t img_size = at_Number32Or(1, 256);
        std::wstring output = at_StringWOr(2, L"");
        arguments_list->push_back(source);
        arguments_list->push_back(img_size);
        arguments_list->push_back(output);

        return result;
    }

    if (input.eq({js_string, js_number}, false))
    {
        std::wstring source = at_StringWOr(0, L"");
        std::wstring output = L"";
        size_t img_size = at_Number32Or(1, 256);
        arguments_list->push_back(source);
        arguments_list->push_back(img_size);
        arguments_list->push_back(output);

        return result;
    }

    if (input.eq({js_string, js_string}, false))
    {
        std::wstring source = at_StringWOr(0, L"");
        std::wstring output = at_StringWOr(1, L"");
        size_t img_size = 256;
        arguments_list->push_back(source);
        arguments_list->push_back(img_size);
        arguments_list->push_back(output);
        return result;
    }

    return result;
}

std::any GetTrayList(napi_env env, size_t TASK_TYPE, std::vector<std::any> *data_list)
{
    std::wstring result = hmc_shell_util::GetTaryIconList::getTrayListJsonW();
    return result;
}

namespace HMC_GetShellEnvInfo
{

    enum class GET_SHELL_ENV_INFO_ID
    {
        NONE = 0,
        getLinkTarget = 1,
        getFileAttributes = 2,

        getVolumeList = 3,
        formatVolumePath = 5,
        formatVolumeName = 6,
        formatVolumeNtName = 7,

        getLinkPath = 8,
        hasFsLink = 9,
        hasHardLink = 10,
        hasDirLink = 12,
        hasSymbolicDirLink = 13,
        getLinkType = 15,

        createFsLink = 16,
        createSymbolicLink = 17,
        createHardLink = 18,
        createSymlink = 19,
        createDirSymlink = 20,

        setFolderIcon = 21,
        setExtensionIcon = 22,
        setAppURLProtocol = 23,

        getShortcutLink = 25,
        trashFile = 26,
        clearTrash = 27,
        copyFile = 28,
        moveFile = 29,

        setShortcutLink = 30,
    };

    const std::map<GET_SHELL_ENV_INFO_ID, std::vector<std::tuple<size_t, js_valuetype>>> GET_SHELL_EQ_TYPE_LIST = {
        {GET_SHELL_ENV_INFO_ID::getLinkTarget, {{0, js_string}}},
        {GET_SHELL_ENV_INFO_ID::getFileAttributes, {{0, js_string}}},
        {GET_SHELL_ENV_INFO_ID::getVolumeList, {}},
        {GET_SHELL_ENV_INFO_ID::formatVolumePath, {{0, js_string}}},
        {GET_SHELL_ENV_INFO_ID::formatVolumeName, {{0, js_string}}},
        {GET_SHELL_ENV_INFO_ID::formatVolumeNtName, {{0, js_string}}},

        {GET_SHELL_ENV_INFO_ID::getLinkPath, {{0, js_string}}},
        {GET_SHELL_ENV_INFO_ID::hasFsLink, {{0, js_string}}},
        {GET_SHELL_ENV_INFO_ID::hasHardLink, {{0, js_string}}},
        {GET_SHELL_ENV_INFO_ID::hasDirLink, {{0, js_string}}},
        {GET_SHELL_ENV_INFO_ID::hasSymbolicDirLink, {{0, js_string}}},

        {GET_SHELL_ENV_INFO_ID::createFsLink, {{0, js_number}, {1, js_string}, {2, js_string}}},
        {GET_SHELL_ENV_INFO_ID::createSymbolicLink, {{0, js_string}, {1, js_string}}},
        {GET_SHELL_ENV_INFO_ID::createHardLink, {{0, js_string}, {1, js_string}}},
        {GET_SHELL_ENV_INFO_ID::createSymlink, {{0, js_string}, {1, js_string}}},
        {GET_SHELL_ENV_INFO_ID::createDirSymlink, {{0, js_string}, {1, js_string}}},
        {GET_SHELL_ENV_INFO_ID::setFolderIcon, {{0, js_string}, {1, js_string}, {2, js_number}}},
        {GET_SHELL_ENV_INFO_ID::setExtensionIcon, {{0, js_string}, {1, js_string}, {2, js_string}, {3, js_number}}},
        {GET_SHELL_ENV_INFO_ID::setAppURLProtocol, {{0, js_string}, {1, js_string}, {2, js_string}}},

        {GET_SHELL_ENV_INFO_ID::getLinkTarget, {{0, js_string}}},
        {GET_SHELL_ENV_INFO_ID::getShortcutLink, {{0, js_string}}},

        {GET_SHELL_ENV_INFO_ID::trashFile, {{0, js_string}, {1, js_boolean}, {2, js_boolean}}},
        {GET_SHELL_ENV_INFO_ID::clearTrash, {{0, js_string}, {1, js_boolean}}},
        {GET_SHELL_ENV_INFO_ID::copyFile, {{0, js_string}, {1, js_string}, {2, js_boolean}, {3, js_boolean}, {4, js_boolean}, {5, js_boolean}}},
        {GET_SHELL_ENV_INFO_ID::moveFile, {{0, js_string}, {1, js_string}, {2, js_boolean}, {3, js_boolean}, {4, js_boolean}, {5, js_boolean}}},
        {GET_SHELL_ENV_INFO_ID::setShortcutLink, {{0, js_string}, {1, js_string}, {2, js_string}, {3, js_string}, {4, js_string}, {5, js_number}, {6, js_string}, {7, js_number}}},
    };

    struct EnvNextWorkData : public HMC_PromiseUtilV2::EnvNextWorkDataTemplate<GET_SHELL_ENV_INFO_ID>
    {
    };

    void GetLinkTarget(EnvNextWorkData *workData);
    void HasFsLink(EnvNextWorkData *workData);
    void CreateFsLink(EnvNextWorkData *workData);
    void ExplorerShell(EnvNextWorkData *workData);

    const std::map<GET_SHELL_ENV_INFO_ID, std::function<void(EnvNextWorkData *workData)>> GET_SHELL_FUNC_LIST = {
        {GET_SHELL_ENV_INFO_ID::getLinkTarget, GetLinkTarget},
        {GET_SHELL_ENV_INFO_ID::getLinkPath, GetLinkTarget},
        {GET_SHELL_ENV_INFO_ID::hasFsLink, HasFsLink},
        {GET_SHELL_ENV_INFO_ID::hasHardLink, HasFsLink},
        {GET_SHELL_ENV_INFO_ID::hasDirLink, HasFsLink},
        {GET_SHELL_ENV_INFO_ID::hasSymbolicDirLink, HasFsLink},
        {GET_SHELL_ENV_INFO_ID::getLinkType, HasFsLink},

        {GET_SHELL_ENV_INFO_ID::createFsLink, CreateFsLink},
        {GET_SHELL_ENV_INFO_ID::createSymbolicLink, CreateFsLink},
        {GET_SHELL_ENV_INFO_ID::createHardLink, CreateFsLink},
        {GET_SHELL_ENV_INFO_ID::createSymlink, CreateFsLink},
        {GET_SHELL_ENV_INFO_ID::createDirSymlink, CreateFsLink},

        {GET_SHELL_ENV_INFO_ID::trashFile, ExplorerShell},
        {GET_SHELL_ENV_INFO_ID::clearTrash, ExplorerShell},
        {GET_SHELL_ENV_INFO_ID::copyFile, ExplorerShell},
        {GET_SHELL_ENV_INFO_ID::moveFile, ExplorerShell},

    };

    void main(void *Work)
    {

        EnvNextWorkData *work = (EnvNextWorkData *)Work;

        const GET_SHELL_ENV_INFO_ID TAKE_TYPE = work->TAKE_TYPE;

        // 优先查找可引用函数列表
        if (GET_SHELL_FUNC_LIST.find(TAKE_TYPE) != GET_SHELL_FUNC_LIST.end())
        {

            for (auto &&GET_SHELL_FUNC : GET_SHELL_FUNC_LIST)
            {

                if (GET_SHELL_FUNC.first == work->TAKE_TYPE)
                {
                    auto fun = GET_SHELL_FUNC.second;
                    fun(work);
                    return;
                }
            }
        }

        const bool FORMAT_VOLUME_ANY = TAKE_TYPE == GET_SHELL_ENV_INFO_ID::formatVolumePath || TAKE_TYPE == GET_SHELL_ENV_INFO_ID::formatVolumeNtName || TAKE_TYPE == GET_SHELL_ENV_INFO_ID::formatVolumeName;

        if (FORMAT_VOLUME_ANY)
        {
            if (std::wstring *_LinkPath = std::get_if<std::wstring>(&work->arguments->at(0)))
            {
                std::wstring result;

                if (work->TAKE_TYPE == GET_SHELL_ENV_INFO_ID::formatVolumePath)
                {
                    result = hmc_usb_util::formatVolumePath(*_LinkPath);
                }

                if (work->TAKE_TYPE == GET_SHELL_ENV_INFO_ID::formatVolumeNtName)
                {
                    result = hmc_usb_util::formatVolumeNtName(*_LinkPath);
                }

                if (work->TAKE_TYPE == GET_SHELL_ENV_INFO_ID::formatVolumeName)
                {
                    result = hmc_usb_util::formatVolumeName(*_LinkPath);
                }

                *work->Result = result;
                return;
            }
        }

        if (work->TAKE_TYPE == GET_SHELL_ENV_INFO_ID::getFileAttributes)
        {
            if (std::wstring *_LinkPath = std::get_if<std::wstring>(&work->arguments->at(0)))
            {
                auto temp = hmc_shell_util::getFileAttributesInfoList(*_LinkPath);
                std::vector<int64_t> temp2;
                for (auto &&i : temp)
                {
                    temp2.push_back(static_cast<int64_t>(i));
                }
                *work->Result = temp2;
                return;
            }
        }

        if (work->TAKE_TYPE == GET_SHELL_ENV_INFO_ID::getVolumeList)
        {
            auto volumeList = hmc_usb_util::getVolumeList();
            std::wstring volumeListResult = hmc_usb_util::chVolume::to_json(volumeList);
            *work->Result = volumeListResult;
            return;
        }

        if (work->TAKE_TYPE == GET_SHELL_ENV_INFO_ID::setFolderIcon)
        {
            std::wstring targetPath = std::get<std::wstring>(work->arguments->at(0));
            std::wstring iconPath = std::get<std::wstring>(work->arguments->at(1));
            int64_t iconIndex = std::get<int64_t>(work->arguments->at(2));
            bool result = hmc_shell_util::SetFolderIcon(targetPath, iconPath, iconIndex);
            *work->Result = result;
            return;
        }

        if (work->TAKE_TYPE == GET_SHELL_ENV_INFO_ID::setExtensionIcon)
        {

            std::wstring extensionName = std::get<std::wstring>(work->arguments->at(0));
            std::wstring typeName = std::get<std::wstring>(work->arguments->at(1));
            std::wstring iconPath = std::get<std::wstring>(work->arguments->at(2));
            int64_t iconIndex = std::get<int64_t>(work->arguments->at(3));
            bool result = hmc_shell_util::SetExtensionIcon(extensionName, typeName, iconPath, iconIndex);
            *work->Result = result;
            return;
        }

        if (work->TAKE_TYPE == GET_SHELL_ENV_INFO_ID::setAppURLProtocol)
        {

            std::wstring protocolName = std::get<std::wstring>(work->arguments->at(0));
            std::wstring appPath = std::get<std::wstring>(work->arguments->at(1));
            std::wstring command = std::get<std::wstring>(work->arguments->at(2));

            bool result = hmc_shell_util::SetAppURLProtocol(protocolName, appPath, command);
            *work->Result = result;
            return;
        }

        if (work->TAKE_TYPE == GET_SHELL_ENV_INFO_ID::getShortcutLink)
        {

            std::wstring targetPath = std::get<std::wstring>(work->arguments->at(0));
            bool QueryDetaile = true;

            work->get_if<bool>(1, &QueryDetaile);

            if (QueryDetaile)
            {

                auto result = hmc_shell_util::getShortcutLink(targetPath);
                if (result.isValid())
                {

                    *work->Result = result.to_json();
                }
                return;
            }

            std::wstring ouput;
            auto result = hmc_shell_util::getShortcutLink(targetPath, &ouput);
            if (result)
            {
                *work->Result = ouput;
            }
            return;
        }

        if (work->TAKE_TYPE == GET_SHELL_ENV_INFO_ID::setShortcutLink)
        {

            std::wstring none = std::wstring();

            std::wstring lnkPath = work->get<std::wstring>(0, none);
            std::wstring FilePath = work->get<std::wstring>(1, none);
            std::wstring work_dir = work->get<std::wstring>(2, none);
            std::wstring desc = work->get<std::wstring>(3, none);
            std::wstring args = work->get<std::wstring>(4, none);
            DWORD iShowCmd = work->get<int64_t>(5, SW_SHOW);
            std::wstring icon = work->get<std::wstring>(6, none);
            DWORD iconIndex = work->get<int64_t>(7, 0);

            bool c_result = hmc_shell_util::setShortcutLink(lnkPath, FilePath, work_dir, desc, args, iShowCmd, icon, iconIndex);
            (*work->Result) = c_result;
        }
    }

    // async
    void ExecuteAsyncWork(napi_env env, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
        try
        {
            main(workData);
        }
        HMC_CATCH_ALL;
    }

    napi_value ExecuteSync(napi_env env, napi_callback_info info)
    {
        napi_value result = as_Null();

        try
        {
            auto input = hmc_NodeArgsValue(env, info);
            auto *workData = EnvNextWorkData::make();

            HMC_FreeAnyAuto(EnvNextWorkData::gc(workData););

            bool is_eq_args = HMC_PromiseUtilV2::get_argumentsTemplate<GET_SHELL_ENV_INFO_ID, EnvNextWorkData>(env, input, workData, GET_SHELL_EQ_TYPE_LIST);
            if (workData == NULL || !is_eq_args)
            {
                return result;
            }

            main(workData);

            result = hmc_napi_create_value::Variant(env, *workData->Result);
            return result;
        }
        HMC_CATCH_ALL;
        return hmc_napi_create_value::Error(env, "A fatal error occurred unexpectedly.", __FUNCSIG__, "HMC_SHELL_API_CATCH");
    }

    // 异步任务完成后的回调函数
    void ResolveWork(napi_env env, napi_status status, void *data)
    {
        EnvNextWorkData *workData = (EnvNextWorkData *)data;
        HMC_FreeAnyAuto(EnvNextWorkData::gc(workData););

        napi_value result;
        napi_get_null(env, &result);

        if (workData == NULL || workData->Result == NULL || workData->Result->index() == 0)
        {
            if (workData != NULL)
            {
                napi_resolve_deferred(env, workData->deferred, result);
                napi_delete_async_work(env, workData->work);
            }
            return;
        }

        result = hmc_napi_create_value::Variant(env, *workData->Result);

        if (result == NULL)
        {
            napi_get_null(env, &result);
        }

        napi_resolve_deferred(env, workData->deferred, result);
        napi_delete_async_work(env, workData->work);
    }

    // 启动异步任务的函数
    napi_value StartAsyncTask(napi_env env, napi_callback_info info)
    {
        napi_value promise;
        try
        {
            napi_value resourceName;
            napi_create_string_utf8(env, __FUNCSIG__, NAPI_AUTO_LENGTH, &resourceName);

            auto *workData = EnvNextWorkData::make();

            auto input = hmc_NodeArgsValue(env, info);
            bool is_eq_args = HMC_PromiseUtilV2::get_argumentsTemplate<GET_SHELL_ENV_INFO_ID, EnvNextWorkData>(env, input, workData, GET_SHELL_EQ_TYPE_LIST);
            if (workData == NULL || !is_eq_args)
            {
                EnvNextWorkData::gc(workData);
                return as_Null();
            }

            napi_create_promise(env, &workData->deferred, &promise);
            napi_create_async_work(env, nullptr, resourceName, ExecuteAsyncWork, ResolveWork, workData, &workData->work);
            napi_queue_async_work(env, workData->work);
            return promise;
        }
        HMC_CATCH_ALL;
        return hmc_napi_create_value::Error(env, "A fatal error occurred unexpectedly.", __FUNCSIG__, "HMC_SHELL_API_CATCH");
    }

}

void HMC_GetShellEnvInfo::ExplorerShell(EnvNextWorkData *work)
{
    if (work == nullptr)
    {
        return;
    }

    HMC_GetShellEnvInfo::GET_SHELL_ENV_INFO_ID TAKE_TYPE = work->TAKE_TYPE;
    std::wstring none = std::wstring();

    if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::clearTrash)
    {
        bool trash_ok = false;

        std::wstring RootPath = work->get<std::wstring>(0, none);
        hmc_string_util::formatCStr(RootPath);
        bool isShow = work->get<bool>(1, true);

        DWORD show_flag = isShow ? 0 : (SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);

        trash_ok = hmc_shell_util::clearTrash(NULL, RootPath, show_flag);
        (*work->Result) = trash_ok;
    }

    if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::trashFile)
    {
        std::wstring trash_path = work->get<std::wstring>(0, none);
        hmc_string_util::formatCStr(trash_path);
        bool is_Recycle = work->get<bool>(1, true);
        bool isShow = work->get<bool>(2, true);

        int trash_ok = hmc_shell_util::trashFile(trash_path, is_Recycle, isShow);
        (*work->Result) = trash_ok;
    }

    if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::copyFile || TAKE_TYPE == GET_SHELL_ENV_INFO_ID::moveFile)
    {
        std::wstring sourcePath = work->get<std::wstring>(0, none);
        std::wstring targetPath = work->get<std::wstring>(1, none);
        hmc_string_util::formatCStr(sourcePath);
        hmc_string_util::formatCStr(targetPath);
        bool isShowConfirm = work->get<bool>(2, true);
        bool isShow = work->get<bool>(3, true);
        bool isShowProgress = work->get<bool>(4, true);

        bool trash_ok = hmc_shell_util::moveFile(sourcePath, targetPath, isShowConfirm, isShow, isShowProgress);

        (*work->Result) = trash_ok;
    }
}

void HMC_GetShellEnvInfo::GetLinkTarget(EnvNextWorkData *work)
{

    if (work == nullptr)
    {
        return;
    }

    using SYMLINK_LINK_TYPE = hmc_shell_util::Symlink::LINK_TYPE;

    HMC_GetShellEnvInfo::GET_SHELL_ENV_INFO_ID TAKE_TYPE = work->TAKE_TYPE;

    if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::getLinkPath)
    {

        if (std::wstring *_LinkPath = std::get_if<std::wstring>(&work->arguments->at(0)))
        {
            std::wstring LinkPath = *_LinkPath;

            auto attributesInfo = hmc_shell_util::getFileAttributesInfo(*_LinkPath);

            SYMLINK_LINK_TYPE LINK_TYPE = hmc_shell_util::Symlink::getLinkType(LinkPath);

            bool isValid = LINK_TYPE != SYMLINK_LINK_TYPE::UNKNOWN;
            bool isdir = attributesInfo & FILE_ATTRIBUTE_DIRECTORY;

            if (isValid)
            {

                if (!isdir)
                {
                    // 硬链接·
                    if (LINK_TYPE == SYMLINK_LINK_TYPE::HARD_LINK_FILE)
                    {
                        std::vector<std::wstring> HardLinkList = hmc_shell_util::Symlink::getHardLinkList(LinkPath);
                        *work->Result = HardLinkList;
                        return;
                    }
                }

                // 软链接
                if (LINK_TYPE == SYMLINK_LINK_TYPE::SOFT_LINK_FILE)
                {
                    auto linkPath = hmc_shell_util::Symlink::getSymbolicLinkTarget(LinkPath);
                    *work->Result = linkPath;
                    return;
                }

                return;
            }
        }

        return;
    }

    std::map<std::wstring, js_variant_value> result;

    if (std::wstring *_LinkPath = std::get_if<std::wstring>(&work->arguments->at(0)))
    {
        std::wstring LinkPath = *_LinkPath;

        auto attributesInfo = hmc_shell_util::getFileAttributesInfo(*_LinkPath);

        SYMLINK_LINK_TYPE LINK_TYPE = hmc_shell_util::Symlink::getLinkType(LinkPath);

        bool isValid = LINK_TYPE != SYMLINK_LINK_TYPE::UNKNOWN;
        bool isdir = attributesInfo & FILE_ATTRIBUTE_DIRECTORY;

        result.insert(std::make_pair(L"valid", isValid));
        result.insert(std::make_pair(L"isdir", isdir));

        if (!isValid)
        {
            result.insert(std::make_pair(L"path", std::monostate()));
            result.insert(std::make_pair(L"type", std::wstring(L"UNKNOWN")));
            result.insert(std::make_pair(L"size", 0));

            goto go_return;
            return;
        }

        if (!isdir)
        {
            // 硬链接·
            if (LINK_TYPE == SYMLINK_LINK_TYPE::HARD_LINK_FILE)
            {
                result.insert(std::make_pair(L"type", std::wstring(L"HARD_LINK_FILE")));

                std::vector<std::wstring> HardLinkList = hmc_shell_util::Symlink::getHardLinkList(LinkPath);

                result.insert(std::make_pair(L"size", static_cast<int64_t>(HardLinkList.size())));

                result.insert(std::make_pair(L"path", HardLinkList));

                if (!HardLinkList.empty())
                {

                    auto volumeList = hmc_usb_util::getVolumeList();
                    auto hardLink_0 = HardLinkList.at(0);

                    if (hardLink_0.empty() || volumeList.empty())
                    {
                        result.insert(std::make_pair(L"volume", std::monostate()));
                        goto go_return;
                        return;
                    }

                    for (size_t i = 0; i < volumeList.size(); i++)
                    {
                        auto at = volumeList.at(i);

                        if (at.path.empty() || hardLink_0.empty())
                            continue;

                        auto p = at.path[0];
                        auto hl = hardLink_0[0];

                        if (
                            (hmc_string_util::is_letter(p) && hmc_string_util::is_letter(hl)) &&
                            std::toupper(p) == std::toupper(hl))
                        {
                            result.insert(std::make_pair(L"volume", at.to_json()));

                            goto go_return;
                            return;
                        }
                    }

                    result.insert(std::make_pair(L"volume", std::monostate()));
                }

                result.insert(std::make_pair(L"volume", std::monostate()));

                goto go_return;
                return;
            }

            // 软链接
            if (LINK_TYPE == SYMLINK_LINK_TYPE::SOFT_LINK_FILE)
            {
                auto linkPath = hmc_shell_util::Symlink::getSymbolicLinkTarget(LinkPath);

                result.insert(std::make_pair(L"type", std::wstring(L"SOFT_LINK_FILE")));

                result.insert(std::make_pair(L"size", 1));

                result.insert(std::make_pair(L"path", linkPath));

                goto go_return;
                return;
            }
        }

        // 文件夹软链接
        if (LINK_TYPE == SYMLINK_LINK_TYPE::SOFT_LINK_DIR)
        {
            auto linkPath = hmc_shell_util::Symlink::getSymbolicLinkTarget(LinkPath);

            result.insert(std::make_pair(L"type", std::wstring(L"SOFT_LINK_DIR")));

            result.insert(std::make_pair(L"size", 1));

            result.insert(std::make_pair(L"path", linkPath));

            goto go_return;
            return;
        }

        // 目录连接点
        if (LINK_TYPE == SYMLINK_LINK_TYPE::JUNCTION_POINT_DIR)
        {
            auto linkPath = hmc_shell_util::Symlink::getSymbolicLinkTarget(LinkPath);

            result.insert(std::make_pair(L"type", std::wstring(L"SYMBOLIC_LINK_DIR")));

            result.insert(std::make_pair(L"size", 1));

            result.insert(std::make_pair(L"path", linkPath));

            goto go_return;
            return;
        }
    }

go_return:
    *work->Result = formatVariantJSONStr_utf16(result);
    return;
}

void HMC_GetShellEnvInfo::HasFsLink(EnvNextWorkData *work)
{

    if (work == nullptr)
    {
        return;
    }

    GET_SHELL_ENV_INFO_ID TAKE_TYPE = work->TAKE_TYPE;

    if (std::wstring *_LinkPath = std::get_if<std::wstring>(&work->arguments->at(0)))
    {
        if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::hasFsLink)
        {

            bool result = hmc_shell_util::Symlink::isLink(*_LinkPath);
            *work->Result = result;
            return;
        }

        if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::hasHardLink)
        {

            bool result = hmc_shell_util::Symlink::isHardLink(*_LinkPath);
            *work->Result = result;
            return;
        }

        if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::hasSymbolicDirLink)
        {

            bool result = hmc_shell_util::Symlink::isSymbolicDirLink(*_LinkPath);
            *work->Result = result;
            return;
        }

        if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::getLinkType)
        {
            using LINK_TYPE_T = hmc_shell_util::Symlink::LINK_TYPE;

            std::map<std::wstring, js_variant_value> result;

            auto LINK_TYPE = hmc_shell_util::Symlink::getLinkType(*_LinkPath);

            bool isdir = LINK_TYPE == LINK_TYPE_T::JUNCTION_POINT_DIR || LINK_TYPE == LINK_TYPE_T::SOFT_LINK_DIR;

            result.insert(std::make_pair(L"type", static_cast<int64_t>(LINK_TYPE)));
            result.insert(std::make_pair(L"isdir", isdir));

            switch (LINK_TYPE)
            {
            case LINK_TYPE_T::HARD_LINK_FILE:
                result.insert(std::make_pair(L"type_name", std::wstring(L"HARD_LINK_FILE")));
                break;

            case LINK_TYPE_T::JUNCTION_POINT_DIR:
                result.insert(std::make_pair(L"type_name", std::wstring(L"JUNCTION_POINT_DIR")));
                break;

            case LINK_TYPE_T::SOFT_LINK_DIR:
                result.insert(std::make_pair(L"type_name", std::wstring(L"SOFT_LINK_DIR")));
                break;

            case LINK_TYPE_T::SOFT_LINK_FILE:
                result.insert(std::make_pair(L"type_name", std::wstring(L"SOFT_LINK_FILE")));
                break;
            }

            if (LINK_TYPE != LINK_TYPE_T::UNKNOWN)
            {
                *work->Result = formatVariantJSONStr_utf16(result);
            }

            return;
        }

        if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::hasDirLink)
        {

            bool result = hmc_shell_util::Symlink::isDirLink(*_LinkPath);
            *work->Result = result;
            return;
        }
    }
}

void HMC_GetShellEnvInfo::CreateFsLink(EnvNextWorkData *work)
{
    if (work == nullptr)
    {
        return;
    }

    GET_SHELL_ENV_INFO_ID TAKE_TYPE = work->TAKE_TYPE;

    // 这里是三个参数 (唯一一个)
    if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::createFsLink)
    {
        if (work->arguments->size() < 3)
        {
            return;
        }

        int64_t targetType = std::get<int64_t>(work->arguments->at(0));

        // 文件夹链接
        const int CREATE_DIR_SYMLINK = 166;
        // 软链接
        const int CREATE_SYMLINK = 168;
        // 硬链接
        const int CREATE_HARD_LINK = 170;
        // 目录连接点
        const int CREATE_SYMBOLIC_LINK = 172;

        std::wstring targetPath = std::get<std::wstring>(work->arguments->at(1));
        std::wstring sourcePath = std::get<std::wstring>(work->arguments->at(2));

        switch (targetType)
        {
        case CREATE_DIR_SYMLINK:
            *(work->Result) = hmc_shell_util::Symlink::createDirSymlink(targetPath, sourcePath);
            return;
        case CREATE_SYMLINK:
            *(work->Result) = hmc_shell_util::Symlink::createSymlink(targetPath, sourcePath);
            return;
        case CREATE_HARD_LINK:
            *(work->Result) = hmc_shell_util::Symlink::createHardLink(targetPath, sourcePath);
            return;
        case CREATE_SYMBOLIC_LINK:
            *(work->Result) = hmc_shell_util::Symlink::createSymbolicLink(targetPath, sourcePath);
            return;
        }

        return;
    }

    std::wstring targetPath = std::get<std::wstring>(work->arguments->at(0));
    std::wstring sourcePath = std::get<std::wstring>(work->arguments->at(1));

    if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::createSymbolicLink)
    {
        *(work->Result) = hmc_shell_util::Symlink::createSymbolicLink(targetPath, sourcePath);
        return;
    }

    if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::createHardLink)
    {
        *(work->Result) = hmc_shell_util::Symlink::createHardLink(targetPath, sourcePath);
        return;
    }

    if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::createSymlink)
    {
        *(work->Result) = hmc_shell_util::Symlink::createSymlink(targetPath, sourcePath);
        return;
    }

    if (TAKE_TYPE == GET_SHELL_ENV_INFO_ID::createDirSymlink)
    {
        *(work->Result) = hmc_shell_util::Symlink::createDirSymlink(targetPath, sourcePath);
        return;
    }
}