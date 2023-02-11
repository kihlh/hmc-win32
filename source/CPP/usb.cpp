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

long GetPortFromLocationW(const wstring &location_information)
{
    size_t port_starting_index = location_information.find_first_of('#');
    size_t port_ending_index = location_information.find_first_of('.');

    wstring port = location_information.substr(port_starting_index + 1, (port_ending_index - port_starting_index) - 1);
    return stol(port.c_str());
}

long GetPortFromLocationA(const string &location_information)
{
    size_t port_starting_index = location_information.find_first_of('#');
    size_t port_ending_index = location_information.find_first_of('.');

    string port = location_information.substr(port_starting_index + 1, (port_ending_index - port_starting_index) - 1);
    return stol(port.c_str());
}

napi_value usbDevsInfo(napi_env env, napi_callback_info info)
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
                    GetPortFromLocationA(str_device_path);
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

//-----------------------------------
// 遍历当前USB设备信息 选用时有轻微改动
// https://blog.51cto.com/u_15127593/3620239

/**
 * @brief Device structure to represent a USB device
 *
 */
struct Device
{
    /**
     * @brief Device path
     *
     */
    std::string device_path;
    /**
     * @brief Device descriptor
     *
     */
    USB_DEVICE_DESCRIPTOR usb_device_descriptor;
    /**
     * @brief Manufacture name
     *
     */
    std::string manufacture;
    /**
     * @brief Serial number
     *
     */
    std::string serial;
    /**
     * @brief Product name
     *
     */
    std::string product;
};

/**
 * @brief Get the Hub Path object
 *
 * @param device_instance Device instance of the hub
 * @return std::wstring Device path of the hub associated with provided device instance
 */
std::wstring GetHubPath(DEVINST device_instance)
{
    std::wstring hub_path;
    HDEVINFO device_information = SetupDiGetClassDevs((LPGUID)&GUID_DEVINTERFACE_USB_HUB, NULL, NULL, (DIGCF_PRESENT | DIGCF_DEVICEINTERFACE));
    DWORD member_index = 0;
    DWORD last_error = NO_ERROR;
    SP_DEVINFO_DATA device_information_data;
    ;
    SP_DEVICE_INTERFACE_DATA device_interface_data;
    PSP_DEVICE_INTERFACE_DETAIL_DATA_W device_interface_detail_data;

    if (INVALID_HANDLE_VALUE != device_information)
    {
        while (ERROR_NO_MORE_ITEMS != GetLastError())
        {
            device_information_data.cbSize = sizeof(SP_DEVINFO_DATA);

            if (SetupDiEnumDeviceInfo(device_information, member_index, &device_information_data))
            {
                if (device_information_data.DevInst == device_instance)
                {
                    device_interface_data.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

                    if (SetupDiEnumDeviceInterfaces(device_information, NULL, (LPGUID)&GUID_DEVINTERFACE_USB_HUB, member_index, &device_interface_data))
                    {
                        DWORD required_size = 0;
                        SetupDiGetDeviceInterfaceDetailW(device_information, &device_interface_data, NULL, 0, &required_size, NULL);
                        device_interface_detail_data = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)malloc(required_size);
                        device_interface_detail_data->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W);
                        if (SetupDiGetDeviceInterfaceDetailW(device_information, &device_interface_data, device_interface_detail_data, required_size, NULL, NULL))
                        {
                            hub_path = device_interface_detail_data->DevicePath;
                        }

                        if (NULL != device_interface_detail_data)
                        {
                            free(device_interface_detail_data);
                        }
                    }
                }
            }
            member_index++;
        }
    }
    SetupDiDestroyDeviceInfoList(device_information);
    return hub_path;
}

/**
 * @brief Get the String Descriptor object
 *
 * @param hub_path Hub path
 * @param port Device port number
 * @param index String descriptor index
 * @return std::string Descriptor value
 */
std::string GetStringDescriptor(std::wstring hub_path, ULONG port, USHORT index)
{
    HANDLE hub_handle = CreateFileW(hub_path.c_str(),
                                    GENERIC_WRITE | GENERIC_READ,
                                    FILE_SHARE_WRITE | FILE_SHARE_READ,
                                    NULL,
                                    OPEN_EXISTING,
                                    NULL,
                                    NULL);
    if (INVALID_HANDLE_VALUE != hub_handle)
    {
        ULONG buffer_size = 0;
        ULONG returned_buffer_size = 0;

        UCHAR string_descriptor_buffer[sizeof(USB_DESCRIPTOR_REQUEST) + MAXIMUM_USB_STRING_LENGTH];

        PUSB_DESCRIPTOR_REQUEST usb_descriptor_request = NULL;

        buffer_size = sizeof(string_descriptor_buffer);

        usb_descriptor_request = (PUSB_DESCRIPTOR_REQUEST)string_descriptor_buffer;
        PUSB_STRING_DESCRIPTOR usb_string_descriptor = (PUSB_STRING_DESCRIPTOR)(usb_descriptor_request + 1);

        memset(usb_descriptor_request, 0, buffer_size);

        usb_descriptor_request->ConnectionIndex = port;

        usb_descriptor_request->SetupPacket.wValue = (USB_STRING_DESCRIPTOR_TYPE << 8) | index;

        usb_descriptor_request->SetupPacket.wIndex = 1033; // en-US

        usb_descriptor_request->SetupPacket.wLength = (USHORT)(buffer_size - sizeof(USB_DESCRIPTOR_REQUEST));

        if (DeviceIoControl(hub_handle,
                            IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
                            usb_descriptor_request,
                            buffer_size,
                            usb_descriptor_request,
                            buffer_size,
                            &returned_buffer_size,
                            NULL))
        {
            std::wstring wstring(usb_string_descriptor->bString);
            std::string usb_string_descriptor(wstring.begin(), wstring.end());
            CloseHandle(hub_handle);
            return usb_string_descriptor;
        }
        CloseHandle(hub_handle);
    }
    return "";
}

/**
 * @brief Get the Device Descriptor
 *
 * @param hub_path Device path of the hub
 * @param port Port number of the device
 * @return USB_DEVICE_DESCRIPTOR Device descriptor
 */
USB_DEVICE_DESCRIPTOR GetDeviceDescriptor(std::wstring hub_path, ULONG port)
{
    USB_DEVICE_DESCRIPTOR usb_device_descriptor = {};
    HANDLE hub_handle = CreateFileW(hub_path.c_str(),
                                    GENERIC_WRITE | GENERIC_READ,
                                    FILE_SHARE_WRITE | FILE_SHARE_READ,
                                    NULL,
                                    OPEN_EXISTING,
                                    NULL,
                                    NULL);
    if (INVALID_HANDLE_VALUE != hub_handle)
    {
        // There can be a maximum of 30 endpoints per device configuration.
        // So allocate space to hold info for 30 pipes.

        ULONG buffer_size = sizeof(USB_NODE_CONNECTION_INFORMATION_EX) + (sizeof(USB_PIPE_INFO) * 30);

        PUSB_NODE_CONNECTION_INFORMATION_EX usb_node_connection_information_ex = (PUSB_NODE_CONNECTION_INFORMATION_EX)malloc(buffer_size);
        usb_node_connection_information_ex->ConnectionIndex = port;

        if (DeviceIoControl(hub_handle,
                            IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX,
                            usb_node_connection_information_ex,
                            buffer_size,
                            usb_node_connection_information_ex,
                            buffer_size,
                            &buffer_size,
                            NULL))
        {
            usb_device_descriptor = usb_node_connection_information_ex->DeviceDescriptor;
        }
        if (NULL != usb_node_connection_information_ex)
        {
            free(usb_node_connection_information_ex);
        }
        CloseHandle(hub_handle);
    }
    return usb_device_descriptor;
}

/**
 * @brief Get the Devices connected to host
 *
 * @param guid GUID of the devices interested
 * @return std::vector<Device*> Vector of devices
 */
std::vector<Device *> GetDevices(GUID *guid)
{
    std::vector<Device *> devices;
    HDEVINFO device_information = SetupDiGetClassDevs(guid, NULL, NULL, (DIGCF_PRESENT | DIGCF_DEVICEINTERFACE));
    DWORD member_index = 0;
    DWORD last_error = NO_ERROR;
    SP_DEVINFO_DATA device_information_data;
    ;
    SP_DEVICE_INTERFACE_DATA device_interface_data;
    PSP_DEVICE_INTERFACE_DETAIL_DATA_W device_interface_detail_data;

    if (INVALID_HANDLE_VALUE != device_information)
    {
        while (ERROR_NO_MORE_ITEMS != GetLastError())
        {
            Device *device = new Device();
            device_information_data.cbSize = sizeof(SP_DEVINFO_DATA);

            if (SetupDiEnumDeviceInfo(device_information, member_index, &device_information_data))
            {
                device_interface_data.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

                if (SetupDiEnumDeviceInterfaces(device_information, NULL, guid, member_index, &device_interface_data))
                {
                    DWORD required_size = 0;
                    SetupDiGetDeviceInterfaceDetailW(device_information, &device_interface_data, NULL, 0, &required_size, NULL);
                    device_interface_detail_data = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)malloc(required_size);
                    device_interface_detail_data->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W);
                    if (SetupDiGetDeviceInterfaceDetailW(device_information, &device_interface_data, device_interface_detail_data, required_size, NULL, NULL))
                    {
                        std::wstring wstring(device_interface_detail_data->DevicePath);
                        std::string device_path(wstring.begin(), wstring.end());
                        device->device_path = device_path;

                        WCHAR location_information[MAX_PATH];
                        if (SetupDiGetDeviceRegistryProperty(device_information,
                                                             &device_information_data,
                                                             SPDRP_LOCATION_INFORMATION,
                                                             NULL,
                                                             (BYTE *)location_information,
                                                             MAX_PATH,
                                                             NULL))
                        {
                            DEVINST parent_device_instance = 0;
                            CONFIGRET config_return = CM_Get_Parent(&parent_device_instance, device_information_data.DevInst, 0);
                            if (CR_SUCCESS == config_return)
                            {
                                USB_DEVICE_DESCRIPTOR usb_device_descriptor = GetDeviceDescriptor(GetHubPath(parent_device_instance), GetPortFromLocationW(location_information));
                                device->manufacture = GetStringDescriptor(GetHubPath(parent_device_instance), GetPortFromLocationW(location_information), usb_device_descriptor.iManufacturer);
                                device->serial = GetStringDescriptor(GetHubPath(parent_device_instance), GetPortFromLocationW(location_information), usb_device_descriptor.iSerialNumber);
                                device->product = GetStringDescriptor(GetHubPath(parent_device_instance), GetPortFromLocationW(location_information), usb_device_descriptor.iProduct);
                                device->usb_device_descriptor = usb_device_descriptor;
                                devices.push_back(device);
                            }
                        }
                    }
                    else
                    {
                        last_error = GetLastError();
                    }
                    if (NULL != device_interface_detail_data)
                    {
                        free(device_interface_detail_data);
                    }
                }
                else
                {
                    last_error = GetLastError();
                }
            }
            else
            {
                last_error = GetLastError();
            }
            member_index++;
        }
    }
    else
    {
        last_error = GetLastError();
    }
    SetupDiDestroyDeviceInfoList(device_information);
    return devices;
}

//-------------end----------------------
napi_value getDeviceUsbList(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value Results;
    status = napi_create_array(env, &Results);
    assert(status == napi_ok);
    napi_value NextDeviceInfo;

    std::vector<Device *> devices = GetDevices((LPGUID)&GUID_DEVINTERFACE_USB_DEVICE);
    size_t nextCount = 0;
    for (auto device : devices)
    {
        status = napi_create_object(env, &NextDeviceInfo);
        assert(status == napi_ok);
        status = napi_set_property(env, NextDeviceInfo, _create_char_string(env, "path"), _create_String(env, device->device_path));
        assert(status == napi_ok);
        status = napi_set_property(env, NextDeviceInfo, _create_char_string(env, "vendor_id"), _create_int64_Number(env, device->usb_device_descriptor.idVendor));
        assert(status == napi_ok);
        status = napi_set_property(env, NextDeviceInfo, _create_char_string(env, "product_id"), _create_int64_Number(env, device->usb_device_descriptor.idProduct));
        assert(status == napi_ok);
        status = napi_set_property(env, NextDeviceInfo, _create_char_string(env, "product"), _create_String(env, device->product));
        assert(status == napi_ok);
        status = napi_set_property(env, NextDeviceInfo, _create_char_string(env, "manufacture"), _create_String(env, device->manufacture));
        assert(status == napi_ok);
        status = napi_set_property(env, NextDeviceInfo, _create_char_string(env, "serial"), _create_String(env, device->serial));
        assert(status == napi_ok);
        status = napi_set_property(env, NextDeviceInfo, _create_char_string(env, "product"), _create_String(env, device->product));
        assert(status == napi_ok);
        status = napi_set_element(env, Results, nextCount, NextDeviceInfo);
        if (status != napi_ok)
            continue;
        nextCount += 1;
    }
}
