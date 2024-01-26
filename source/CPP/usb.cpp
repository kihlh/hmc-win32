#include "./Mian.hpp";
#include "hmc_napi_value_util.h"
#include <windows.h> // This is required to include before setupapi.h
#include <setupapi.h>
#include <Cfgmgr32.h>
#include <iostream>
#include <vector>
#include <string>
#include <initguid.h>
#include <Usbiodef.h>
#include <Usb100.h>
#include <Usbioctl.h>
#include <node_api.h>
#pragma comment(lib, "Setupapi.lib")
#include "./util.h";
using namespace std;

DEFINE_GUID(UsbClassGuid, 0xa5dcbf10L, 0x6530, 0x11d2, 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed);

napi_value getHidUsbList(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    status = napi_create_array(env, &Results);
    assert(status == napi_ok);
    // 获取设备数量
    UINT nDevices = 0;
    GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST));

    // 没有设备
    if (nDevices < 1)
        return Results;

    // 为设备列表分配内存
    PRAWINPUTDEVICELIST pRawInputDeviceList;
    pRawInputDeviceList = new RAWINPUTDEVICELIST[sizeof(RAWINPUTDEVICELIST) * nDevices];

    // 没有内存变量
    if (pRawInputDeviceList == NULL)
        return Results;

    // 设备列表缓冲区
    int nResult;
    nResult = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));

    // 是否有设备列表
    if (nResult < 0)
    {
        // 清空内存
        delete[] pRawInputDeviceList;
        return Results;
    }

    // 循环枚举列表
    for (UINT index = 0; index < nDevices; index++)
    {
        // 获取设备名称的字节数
        UINT nBufferSize = 0;
        nResult = GetRawInputDeviceInfoW(pRawInputDeviceList[index].hDevice, // 磁盘
                                         RIDI_DEVICENAME,                    // 驱动名称
                                         NULL,                               // 没有缓存区  获取缓冲区大小
                                         &nBufferSize);                      // 文本大小预设!
        napi_value NextDeviceInfo;
        status = napi_create_object(env, &NextDeviceInfo);
        // 是否有设备名称
        if (nResult < 0)
            continue;

        // 为设备名称分配内存
        WCHAR *wcDeviceName = new WCHAR[nBufferSize + 1];

        // 是否有内存
        if (wcDeviceName == NULL)
            continue;

        // 设备名称
        nResult = GetRawInputDeviceInfoW(pRawInputDeviceList[index].hDevice, // 磁盘
                                         RIDI_DEVICENAME,                    // 驱动名称
                                         wcDeviceName,                       // 设备名称
                                         &nBufferSize);                      // 文本大小

        // 是否有驱动名称
        if (nResult < 0)
        {
            // 清空并执行下个
            delete[] wcDeviceName;
            continue;
        }

        // 设置设备信息和缓冲区大小
        RID_DEVICE_INFO rdiDeviceInfo;
        rdiDeviceInfo.cbSize = sizeof(RID_DEVICE_INFO);
        nBufferSize = rdiDeviceInfo.cbSize;

        // 获取磁盘参数
        nResult = GetRawInputDeviceInfoW(pRawInputDeviceList[index].hDevice,
                                         RIDI_DEVICEINFO,
                                         &rdiDeviceInfo,
                                         &nBufferSize);

        // 没有多个内存? 执行下个
        if (nResult < 0)
            continue;

        // 鼠标
        if (rdiDeviceInfo.dwType == RIM_TYPEMOUSE)
        {
            napi_set_property(env, NextDeviceInfo, as_String("type"), as_String(L"mouse"));
            napi_set_property(env, NextDeviceInfo, as_String("index"), as_Number(index));
            napi_set_property(env, NextDeviceInfo, as_String("name"), as_String( wcDeviceName));
            napi_set_property(env, NextDeviceInfo, as_String("dwId"), as_Number(rdiDeviceInfo.mouse.dwId));
            napi_set_property(env, NextDeviceInfo, as_String("dwNumberOfButtons"), as_Number(rdiDeviceInfo.mouse.dwNumberOfButtons));
            napi_set_property(env, NextDeviceInfo, as_String("dwSampleRate"), as_Number(rdiDeviceInfo.mouse.dwSampleRate));
            napi_set_property(env, NextDeviceInfo, as_String("fHasHorizontalWheel"),as_Boolean(rdiDeviceInfo.mouse.fHasHorizontalWheel));
        }

        // Keyboard
        else if (rdiDeviceInfo.dwType == RIM_TYPEKEYBOARD)
        {
            napi_set_property(env, NextDeviceInfo, as_String("type"), as_String(L"keyboard"));
            napi_set_property(env, NextDeviceInfo, as_String("index"), as_Number(index));
            napi_set_property(env, NextDeviceInfo, as_String("name"), as_String( wcDeviceName));
            napi_set_property(env, NextDeviceInfo, as_String("dwKeyboardMode"), as_Number(rdiDeviceInfo.keyboard.dwKeyboardMode));
            napi_set_property(env, NextDeviceInfo, as_String("dwNumberOfFunctionKeys"), as_Number(rdiDeviceInfo.keyboard.dwNumberOfFunctionKeys));
            napi_set_property(env, NextDeviceInfo, as_String("dwNumberOfIndicators"), as_Number(rdiDeviceInfo.keyboard.dwNumberOfIndicators));
            napi_set_property(env, NextDeviceInfo, as_String("dwNumberOfKeysTotal"), as_Number(rdiDeviceInfo.keyboard.dwNumberOfKeysTotal));
            napi_set_property(env, NextDeviceInfo, as_String("dwType"), as_Number(rdiDeviceInfo.keyboard.dwType));
            napi_set_property(env, NextDeviceInfo, as_String("dwSubType"), as_Number(rdiDeviceInfo.keyboard.dwSubType));
        }

        // Some HID
        else if (rdiDeviceInfo.dwType == RIM_TYPEHID)
        {
            napi_set_property(env, NextDeviceInfo, as_String("type"), as_String(L"hid"));
            napi_set_property(env, NextDeviceInfo, as_String("index"), as_Number(index));
            napi_set_property(env, NextDeviceInfo, as_String("name"), as_String( wcDeviceName));
            napi_set_property(env, NextDeviceInfo, as_String("dwVendorId"), as_Number(rdiDeviceInfo.hid.dwVendorId));
            napi_set_property(env, NextDeviceInfo, as_String("dwProductId"), as_Number(rdiDeviceInfo.hid.dwProductId));
            napi_set_property(env, NextDeviceInfo, as_String("dwVersionNumber"), as_Number(rdiDeviceInfo.hid.dwVersionNumber));
            napi_set_property(env, NextDeviceInfo, as_String("usUsage"), as_Number(rdiDeviceInfo.hid.usUsage));
            napi_set_property(env, NextDeviceInfo, as_String("usUsagePage"), as_Number(rdiDeviceInfo.hid.usUsagePage));
        }

        status = napi_set_element(env, Results, index, NextDeviceInfo);
        assert(status == napi_ok);
        // Delete Name Memory!
        delete[] wcDeviceName;
    }

    delete[] pRawInputDeviceList;
    return Results;
}

napi_value getUsbDevsInfo(napi_env env, napi_callback_info info)
{
    napi_value usbDevsInfoList, value;
    napi_status status;
    status = napi_create_array(env, &usbDevsInfoList);
    if (status != napi_ok)
        return nullptr;

    HDEVINFO hDevInfo;
    PSP_DEVICE_INTERFACE_DETAIL_DATA_W psp_device_details;
    SP_DEVICE_INTERFACE_DATA sp_device_data;
    BOOL bRes = TRUE;
    int nextCount = 0;
    hDevInfo = ::SetupDiGetClassDevsW((LPGUID)&UsbClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    if (hDevInfo != INVALID_HANDLE_VALUE)

    {

        psp_device_details = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)::GlobalAlloc(LMEM_ZEROINIT, 1024);
        psp_device_details->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        while (bRes)

        {

            sp_device_data.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

            bRes = ::SetupDiEnumDeviceInterfaces(hDevInfo, NULL, (LPGUID)&UsbClassGuid, nextCount, &sp_device_data);

            if (bRes)

            {
                bRes = ::SetupDiGetInterfaceDeviceDetailW(hDevInfo, &sp_device_data, psp_device_details, 1024, NULL, NULL);
                if (bRes)
                {
                    wstring str_device_path = psp_device_details->DevicePath;
                    for (int i = 3 - 1; i >= 0; i--)
                    {
                        str_device_path.replace(str_device_path.find(L"#"), 1, L"\\");
                    }

                    status = napi_set_element(env, usbDevsInfoList, nextCount,as_String( str_device_path));
                    if (status != napi_ok)
                        return nullptr;
                    nextCount++;
                }
            }
        }

        ::GlobalFree(psp_device_details);
        ::SetupDiDestroyDeviceInfoList(hDevInfo);
    }
    return usbDevsInfoList;
}

napi_value getHidUsbIdList(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    status = napi_create_array(env, &Results);
    assert(status == napi_ok);
    // 获取设备数量
    UINT nDevices = 0;
    GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST));

    // 没有设备
    if (nDevices < 1)
        return Results;

    // 为设备列表分配内存
    PRAWINPUTDEVICELIST pRawInputDeviceList;
    pRawInputDeviceList = new RAWINPUTDEVICELIST[sizeof(RAWINPUTDEVICELIST) * nDevices];

    // 没有内存变量
    if (pRawInputDeviceList == NULL)
        return Results;

    // 设备列表缓冲区
    int nResult;
    nResult = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));

    // 是否有设备列表
    if (nResult < 0)
    {
        // 清空内存
        delete[] pRawInputDeviceList;
        return Results;
    }

    // 循环枚举列表
    for (UINT index = 0; index < nDevices; index++)
    {
        // 获取设备名称的字节数
        UINT nBufferSize = 0;
        nResult = GetRawInputDeviceInfoW(pRawInputDeviceList[index].hDevice, // 磁盘
                                         RIDI_DEVICENAME,                    // 驱动名称
                                         NULL,                               // 没有缓存区  获取缓冲区大小
                                         &nBufferSize);                      // 文本大小预设!
        napi_value NextDeviceInfo;
        status = napi_create_object(env, &NextDeviceInfo);
        // 是否有设备名称
        if (nResult < 0)
            continue;

        // 为设备名称分配内存
        WCHAR *wcDeviceName = new WCHAR[nBufferSize + 1];

        // 是否有内存
        if (wcDeviceName == NULL)
            continue;

        // 设备名称
        nResult = GetRawInputDeviceInfoW(pRawInputDeviceList[index].hDevice, // 磁盘
                                         RIDI_DEVICENAME,                    // 驱动名称
                                         wcDeviceName,                       // 设备名称
                                         &nBufferSize);                      // 文本大小

        // 是否有驱动名称
        if (nResult < 0)
        {
            // 清空并执行下个
            delete[] wcDeviceName;
            continue;
        }

        wstring str_device_path =wcDeviceName;// hmc_string_util::utf16_to_utf8(wcDeviceName);
        delete[] wcDeviceName;

        for (int i = 3 - 1; i >= 0; i--)
        {
            str_device_path.replace(str_device_path.find(L"#"), 1, L"\\");
        }

        status = napi_set_element(env, Results, (int)index, as_String(str_device_path));
        if (status != napi_ok)
        {
            return Results;
        }
    }

    delete[] pRawInputDeviceList;
    return Results;
}

wstring FormatVolumePath(wstring VolumeName)
{
    DWORD VolumePathNamesLeng = MAX_PATH + 1;
    wstring VolumePathNames = L"";
    VolumePathNames.reserve(VolumePathNamesLeng);
    VolumePathNames.resize(VolumePathNamesLeng);

    if (GetVolumePathNamesForVolumeNameW(VolumeName.c_str(), &VolumePathNames[0], MAX_PATH, &VolumePathNamesLeng))
    {

        VolumePathNames.resize(VolumePathNamesLeng);
    }
    else
    {
        VolumePathNames.clear();
        VolumePathNames.resize(0);
    }
    return VolumePathNames;
}

vector<util_Volume> util_getVolumeList()
{
    vector<util_Volume> Results = {};
    DWORD CharCount = 0;
    WCHAR DeviceName[MAX_PATH] = L"";
    HANDLE FindHandle = INVALID_HANDLE_VALUE;
    BOOL Found = FALSE;
    size_t PrefixIndex = 0;
    BOOL Success = FALSE;
    WCHAR VolumeName[MAX_PATH] = L"";

    // gc
    std::shared_ptr<void> _shared_free_handle(nullptr, [&](void *)
                                              {
        if (FindHandle != INVALID_HANDLE_VALUE) {
            FindVolumeClose(FindHandle);
            FindHandle = INVALID_HANDLE_VALUE;
        } });

    //  枚举驱动器设备号
    FindHandle = FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));

    if (FindHandle == INVALID_HANDLE_VALUE)
        return Results;

    while (true)
    {
        PrefixIndex = wcslen(VolumeName) - 1;
        if (VolumeName[0] != L'\\' ||
            VolumeName[1] != L'\\' ||
            VolumeName[2] != L'?' ||
            VolumeName[3] != L'\\' ||
            VolumeName[PrefixIndex] != L'\\')
        {
            break;
        }

        VolumeName[PrefixIndex] = L'\0';

        CharCount = QueryDosDeviceW(&VolumeName[4], DeviceName, ARRAYSIZE(DeviceName));

        VolumeName[PrefixIndex] = L'\\';

        if (CharCount == 0)
            break;

        Results.push_back(util_Volume{
            FormatVolumePath(VolumeName),
            wstring(VolumeName),
            wstring(DeviceName),
        });

        Success = FindNextVolumeW(FindHandle, VolumeName, ARRAYSIZE(VolumeName));
        if (!Success)
            break;
    }

    return Results;
}

napi_value getVolumeList(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    status = napi_create_array(env, &Results);
    assert(status == napi_ok);
    vector<util_Volume> _getVolumeList = util_getVolumeList();
    for (size_t index = 0; index < _getVolumeList.size(); index++)
    {
        util_Volume volume = _getVolumeList[index];
        napi_value cur_item;
        status = napi_create_object(env, &cur_item);
        if (status != napi_ok)
        {
            break;
        }
        status = napi_set_property(env, cur_item, as_String("device"), as_String(volume.device.c_str()));
        if (status != napi_ok)
        {
            return Results;
        }
        status = napi_set_property(env, cur_item, as_String("name"), as_String(volume.name.c_str()));
        if (status != napi_ok)
        {
            return Results;
        }
        status = napi_set_property(env, cur_item, as_String("path"), as_String(volume.path.c_str()));
        if (status != napi_ok)
        {
            return Results;
        }
        status = napi_set_element(env, Results, (int)index, cur_item);
        if (status != napi_ok)
        {
            return Results;
        }
    }

    return Results;
}

napi_value formatVolumePath(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);
    hmc_is_argv_type(args, 0, 1, napi_string, NULL);
    wstring Paths = hmc_napi_get_value::string_utf16(env, args[0]);
    wstring VolumePaths = FormatVolumePath((PWCHAR)Paths.c_str());
    if (VolumePaths.empty())
    {
        VolumePaths.append(Paths.c_str());
    }
    return as_String(VolumePaths.c_str());
}
