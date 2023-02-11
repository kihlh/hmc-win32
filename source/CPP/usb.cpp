#include "./Mian.hpp";
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
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "type"), _create_W2U8_string(env, L"mouse"));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "index"), _create_int64_Number(env, index));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "name"), _create_W2U8_string(env, wcDeviceName));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwId"), _create_int64_Number(env, rdiDeviceInfo.mouse.dwId));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwNumberOfButtons"), _create_int64_Number(env, rdiDeviceInfo.mouse.dwNumberOfButtons));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwSampleRate"), _create_int64_Number(env, rdiDeviceInfo.mouse.dwSampleRate));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "fHasHorizontalWheel"), _create_bool_Boolean(env, rdiDeviceInfo.mouse.fHasHorizontalWheel));
        }

        // Keyboard
        else if (rdiDeviceInfo.dwType == RIM_TYPEKEYBOARD)
        {
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "type"), _create_W2U8_string(env, L"keyboard"));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "index"), _create_int64_Number(env, index));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "name"), _create_W2U8_string(env, wcDeviceName));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwKeyboardMode"), _create_int64_Number(env, rdiDeviceInfo.keyboard.dwKeyboardMode));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwNumberOfFunctionKeys"), _create_int64_Number(env, rdiDeviceInfo.keyboard.dwNumberOfFunctionKeys));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwNumberOfIndicators"), _create_int64_Number(env, rdiDeviceInfo.keyboard.dwNumberOfIndicators));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwNumberOfKeysTotal"), _create_int64_Number(env, rdiDeviceInfo.keyboard.dwNumberOfKeysTotal));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwType"), _create_int64_Number(env, rdiDeviceInfo.keyboard.dwType));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwSubType"), _create_int64_Number(env, rdiDeviceInfo.keyboard.dwSubType));
        }

        // Some HID
        else if (rdiDeviceInfo.dwType == RIM_TYPEHID)
        {
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "type"), _create_W2U8_string(env, L"hid"));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "index"), _create_int64_Number(env, index));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "name"), _create_W2U8_string(env, wcDeviceName));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwVendorId"), _create_int64_Number(env, rdiDeviceInfo.hid.dwVendorId));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwProductId"), _create_int64_Number(env, rdiDeviceInfo.hid.dwProductId));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "dwVersionNumber"), _create_int64_Number(env, rdiDeviceInfo.hid.dwVersionNumber));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "usUsage"), _create_int64_Number(env, rdiDeviceInfo.hid.usUsage));
            napi_set_property(env, NextDeviceInfo, _create_char_string(env, "usUsagePage"), _create_int64_Number(env, rdiDeviceInfo.hid.usUsagePage));
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
    PSP_DEVICE_INTERFACE_DETAIL_DATA_A psp_device_details;
    SP_DEVICE_INTERFACE_DATA sp_device_data;
    BOOL bRes = TRUE;
    int nextCount = 0;
    hDevInfo = ::SetupDiGetClassDevs((LPGUID)&UsbClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    if (hDevInfo != INVALID_HANDLE_VALUE)

    {

        psp_device_details = (PSP_DEVICE_INTERFACE_DETAIL_DATA_A)::GlobalAlloc(LMEM_ZEROINIT, 1024);
        psp_device_details->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        while (bRes)

        {

            sp_device_data.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

            bRes = ::SetupDiEnumDeviceInterfaces(hDevInfo, NULL, (LPGUID)&UsbClassGuid, nextCount, &sp_device_data);

            if (bRes)

            {
                bRes = ::SetupDiGetInterfaceDeviceDetailA(hDevInfo, &sp_device_data, psp_device_details, 1024, NULL, NULL);
                if (bRes)
                {
                    string str_device_path = psp_device_details->DevicePath;
                    for (int i = 3 - 1; i >= 0; i--)
                    {
                        str_device_path.replace(str_device_path.find("#"), 1, "\\");
                    }
                    
                    status = napi_set_element(env, usbDevsInfoList, nextCount, _create_String(env, str_device_path));
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
