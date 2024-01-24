#include "./hmc_usb_util.h"

std::wstring hmc_usb_util::formatVolumeName(std::wstring VolumeName)
{
    DWORD VolumePathNamesLeng = MAX_PATH + 1;
    std::wstring VolumePathNames = L"";

    VolumePathNames.resize(VolumePathNamesLeng);

    if (::GetVolumePathNamesForVolumeNameW(VolumeName.c_str(), &VolumePathNames[0], MAX_PATH, &VolumePathNamesLeng))
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

std::wstring hmc_usb_util::formatVolumeNtName(std::wstring VolumeName)
{
    DWORD VolumePathNamesLeng = MAX_PATH + 1;
    std::wstring VolumePathNames = L"";

    VolumePathNames.resize(VolumePathNamesLeng);

    if (::GetVolumePathNameW(VolumeName.c_str(), &VolumePathNames[0], VolumePathNamesLeng))
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

std::vector<hmc_usb_util::chVolume> hmc_usb_util::getVolumeList()
{
    std::vector<hmc_usb_util::chVolume> Results = {};

    DWORD CharCount = 0;
    WCHAR DeviceName[MAX_PATH] = L"";
    HANDLE FindHandle = INVALID_HANDLE_VALUE;
    BOOL Found = FALSE;
    size_t PrefixIndex = 0;
    BOOL Success = FALSE;
    WCHAR VolumeName[MAX_PATH] = L"";

    //  枚举驱动器设备号
    FindHandle = ::FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));

    if (FindHandle == INVALID_HANDLE_VALUE)
        return Results;

    // gc
    std::shared_ptr<void> _shared_free_handle(nullptr, [&](void *)
                                              {
        if (FindHandle != INVALID_HANDLE_VALUE) {
            ::FindVolumeClose(FindHandle);
            FindHandle = INVALID_HANDLE_VALUE;
        } });

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

        CharCount = ::QueryDosDeviceW(&VolumeName[4], DeviceName, ARRAYSIZE(DeviceName));

        VolumeName[PrefixIndex] = L'\\';

        if (CharCount == 0)
            break;

        Results.push_back(chVolume{
            formatVolumeName(VolumeName),
            std::wstring(VolumeName),
            std::wstring(DeviceName),
        });

        Success = ::FindNextVolumeW(FindHandle, VolumeName, ARRAYSIZE(VolumeName));
        if (!Success)
            break;
    }

    return Results;
}

std::vector<std::wstring> hmc_usb_util::getUsbDevsNameList()
{
    std::vector<std::wstring> result = {};

    HDEVINFO hDevInfo;
    PSP_DEVICE_INTERFACE_DETAIL_DATA_W psp_device_details;
    SP_DEVICE_INTERFACE_DATA sp_device_data;
    BOOL bRes = TRUE;
    int nextCount = 0;
    hDevInfo = ::SetupDiGetClassDevsW((LPGUID)&UsbClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

    if (hDevInfo != INVALID_HANDLE_VALUE)
    {
        std::shared_ptr<void> _shared_free_handle(nullptr, [&](void *)
                                                  {
        ::GlobalFree(psp_device_details);
        ::SetupDiDestroyDeviceInfoList(hDevInfo); });

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
                    std::wstring str_device_path = psp_device_details->DevicePath;

                    for (int i = 3 - 1; i >= 0; i--)
                    {
                        str_device_path.replace(str_device_path.find(L"#"), 1, L"\\");
                    }

                    result.push_back(str_device_path);

                    nextCount++;
                }
            }
        }
    }

    return result;
}

std::vector<hmc_usb_util::chUsbDevsInfo> hmc_usb_util::getUsbDevsInfoList()
{
    std::vector<chUsbDevsInfo> result = {};

    // 获取设备信息集合句柄
    HDEVINFO deviceInfoSet = ::SetupDiGetClassDevsW((LPGUID)&UsbClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if (deviceInfoSet == INVALID_HANDLE_VALUE)
    {
        return result;
    }

    DWORD deviceIndex = 0;
    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA); // 设备信息数据大小

    while (::SetupDiEnumDeviceInfo(deviceInfoSet, deviceIndex, &deviceInfoData))
    {
        deviceIndex++;

        DWORD dataType;
        wchar_t buffer[4096];
        DWORD bufferSize = 4096;

        // 获取设备ID
        wchar_t deviceID[4096];
        if (::CM_Get_Device_IDW(deviceInfoData.DevInst, deviceID, sizeof(deviceID), 0) != CR_SUCCESS)
        {
            continue;
        }

        // 获取设备描述信息
        if (!::SetupDiGetDeviceRegistryPropertyW(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC, &dataType, (PBYTE)buffer, bufferSize, NULL))
        {
            continue;
        }
        std::wstring description = buffer;

        // 获取供应商ID和产品ID
        std::wstring vidStr = L"VID_";
        std::wstring pidStr = L"PID_";

        std::wstring deviceIdStr = deviceID;
        std::size_t vidLocation = deviceIdStr.find(vidStr) + vidStr.size();
        std::size_t pidLocation = deviceIdStr.find(pidStr) + pidStr.size();

        std::wstring vendorId = deviceIdStr.substr(vidLocation, 4);
        std::wstring productId = deviceIdStr.substr(pidLocation, 4);

        chUsbDevsInfo item;
        item.name = deviceID;
        item.description = description;
        item.dwVendorId = vendorId.empty() ? 0 : std::stoi(vendorId, nullptr, 16);
        item.dwProductId = productId.empty() ? 0 : std::stoi(productId, nullptr, 16);

        result.push_back(item);
    }

    // 销毁设备信息集合
    ::SetupDiDestroyDeviceInfoList(deviceInfoSet);

    return result;
}

std::vector<std::wstring> hmc_usb_util::getUsbHidNameList()
{
    std::vector<std::wstring> result = {};

    // 获取设备数量
    UINT nDevices = 0;
    ::GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST));

    if (nDevices < 1)
        return result;

    // 为设备列表分配内存
    std::vector<RAWINPUTDEVICELIST> pRawInputDeviceList;
    pRawInputDeviceList.resize(nDevices);

    // 设备列表缓冲区
    int nResult;
    nResult = ::GetRawInputDeviceList(pRawInputDeviceList.data(), &nDevices, sizeof(RAWINPUTDEVICELIST));

    if (nResult < 0)
    {
        pRawInputDeviceList.clear();
        return result;
    }

    result.reserve(nResult);

    // 循环枚举列表
    for (UINT index = 0; index < nDevices; index++)
    {
        // 获取设备名称的字节数
        UINT nBufferSize = 0;
        nResult = ::GetRawInputDeviceInfoW(pRawInputDeviceList[index].hDevice, // 磁盘
                                           RIDI_DEVICENAME,                    // 驱动名称
                                           NULL,                               // 没有缓存区  获取缓冲区大小
                                           &nBufferSize);                      // 文本大小预设!

        if (nResult < 0)
            continue;

        // 为设备名称分配内存

        std::wstring deviceName = std::wstring();
        deviceName.resize(nBufferSize + 1);

        // 设备名称
        nResult = ::GetRawInputDeviceInfoW(pRawInputDeviceList[index].hDevice, // 磁盘
                                           RIDI_DEVICENAME,                    // 驱动名称
                                           &deviceName[0],                     // 设备名称
                                           &nBufferSize);                      // 文本大小

        // 是否有驱动名称
        if (nResult < 0)
        {
            deviceName.clear();
            continue;
        }

        std::wstring str_device_path = std::wstring(deviceName.c_str());

        for (int i = 3 - 1; i >= 0; i--)
        {
            str_device_path.replace(str_device_path.find(L"#"), 1, L"\\");
        }

        result.push_back(str_device_path);
    }

    return result;
}

std::vector<hmc_usb_util::thHidInfo> hmc_usb_util::getUsbHidList()
{
    std::vector<hmc_usb_util::thHidInfo> result = {};

    // 获取设备数量
    UINT nDevices = 0;
    ::GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST));

    // 没有设备
    if (nDevices < 1)
        return result;

    // 为设备列表分配内存

    std::vector<RAWINPUTDEVICELIST> pRawInputDeviceList;
    pRawInputDeviceList.resize(nDevices);

    // 设备列表缓冲区
    int nResult;
    nResult = ::GetRawInputDeviceList(pRawInputDeviceList.data(), &nDevices, sizeof(RAWINPUTDEVICELIST));

    // 是否有设备列表
    if (nResult < 0)
    {
        return result;
    }

    // 循环枚举列表
    for (UINT index = 0; index < nDevices; index++)
    {
        // 获取设备名称的字节数
        UINT nBufferSize = 0;
        nResult = ::GetRawInputDeviceInfoW(pRawInputDeviceList[index].hDevice, // 磁盘
                                           RIDI_DEVICENAME,                    // 驱动名称
                                           NULL,                               // 没有缓存区  获取缓冲区大小
                                           &nBufferSize);                      // 文本大小预设!
        // 是否有设备名称
        if (nResult < 0)
            continue;

        // 为设备名称分配内存

        std::wstring deviceName = std::wstring();
        deviceName.resize(nBufferSize + 1);

        // 设备名称
        nResult = ::GetRawInputDeviceInfoW(pRawInputDeviceList[index].hDevice, // 磁盘
                                           RIDI_DEVICENAME,                    // 驱动名称
                                           &deviceName[0],                     // 设备名称
                                           &nBufferSize);                      // 文本大小

        // 是否有驱动名称
        if (nResult < 0)
        {
            continue;
        }

        // 设置设备信息和缓冲区大小
        RID_DEVICE_INFO rdiDeviceInfo;
        rdiDeviceInfo.cbSize = sizeof(RID_DEVICE_INFO);
        nBufferSize = rdiDeviceInfo.cbSize;

        // 获取磁盘参数
        nResult = ::GetRawInputDeviceInfoW(pRawInputDeviceList[index].hDevice,
                                           RIDI_DEVICEINFO,
                                           &rdiDeviceInfo,
                                           &nBufferSize);

        // 没有多个内存? 执行下个
        if (nResult < 0)
            continue;

        // 鼠标
        if (rdiDeviceInfo.dwType == RIM_TYPEMOUSE)
        {
            chHidMouseInfo item = {L"", L"mouse", index, 0, 0, 0, 0};
            item.name = std::wstring(deviceName.c_str());
            item.dwId = rdiDeviceInfo.mouse.dwId;
            item.dwNumberOfButtons = rdiDeviceInfo.mouse.dwNumberOfButtons;
            item.dwSampleRate = rdiDeviceInfo.mouse.dwSampleRate;
            item.fHasHorizontalWheel = rdiDeviceInfo.mouse.fHasHorizontalWheel;
            result.push_back(item);
        }

        // Keyboard
        else if (rdiDeviceInfo.dwType == RIM_TYPEKEYBOARD)
        {
            chHidKeyboardInfo item = {L"", L"keyboard", index, 0, 0, 0, 0, 0};
            item.name = std::wstring(deviceName.c_str());

            item.dwKeyboardMode = rdiDeviceInfo.keyboard.dwKeyboardMode;
            item.dwNumberOfFunctionKeys = rdiDeviceInfo.keyboard.dwNumberOfFunctionKeys;
            item.dwNumberOfIndicators = rdiDeviceInfo.keyboard.dwNumberOfIndicators;
            item.dwNumberOfKeysTotal = rdiDeviceInfo.keyboard.dwNumberOfKeysTotal;
            item.dwType = rdiDeviceInfo.keyboard.dwType;
            item.dwSubType = rdiDeviceInfo.keyboard.dwSubType;
            result.push_back(item);
        }

        // Some HID
        else if (rdiDeviceInfo.dwType == RIM_TYPEHID)
        {
            chHidSomeInfo item = {L"", L"hid", index, 0, 0, 0, 0};
            item.name = std::wstring(deviceName.c_str());

            item.dwVendorId = rdiDeviceInfo.hid.dwVendorId;
            item.dwProductId = rdiDeviceInfo.hid.dwProductId;
            item.dwVersionNumber = rdiDeviceInfo.hid.dwVersionNumber;
            item.usUsage = rdiDeviceInfo.hid.usUsage;
            item.usUsagePage = rdiDeviceInfo.hid.usUsagePage;
            result.push_back(item);
        }
    }

    return result;
}

std::wstring hmc_usb_util::formatVolumePath(std::wstring VolumePath)
{
    std::wstring result(VolumePath.begin(), VolumePath.begin() + VolumePath.size());
    auto volumeList = getVolumeList();
    size_t length = volumeList.size();

    for (size_t i = 0; i < length; i++)
    {
        auto it = &volumeList.at(i);

        auto end_pos = it->path.size();

        // 移除所有尾部 \0
        while ((end_pos = it->path.find_last_not_of(L'\0')) != it->path.size() - 1)
        {
            it->path.erase(end_pos + 1);
        }

        end_pos = it->device.size();

        // 移除所有尾部 \0
        while ((end_pos = it->device.find_last_not_of(L'\0')) != it->device.size() - 1)
        {
            it->device.erase(end_pos + 1);
        }
    }

    for (size_t i = 0; i < length; i++)
    {
        auto &it = volumeList.at(i);

        size_t start_pos = 0;

        start_pos = result.find(it.name, start_pos);

        if ((start_pos = result.find(it.name, start_pos)) != std::wstring::npos)
        {
            result.replace(start_pos, it.name.size(), it.path);
            break;
        }

        start_pos = 0;

        start_pos = result.find(it.device, start_pos);

        if ((start_pos = result.find(it.device, start_pos)) != std::wstring::npos)
        {
            result.replace(start_pos, it.device.size(), it.path);
            break;
        }
    }

    // 没有变化 是nt路径？
    if (result.size() == VolumePath.size())
    {

        size_t start_pos = 0;

        std::wstring from = L"\\DosDevices\\";

        start_pos = result.find(from, start_pos);

        if ((start_pos = result.find(from, start_pos)) != std::wstring::npos)
        {
            result.replace(start_pos, from.size(), L"");
        }
    }

    // 移除所有尾部 \0
    auto end_pos = result.size();
    while ((end_pos = result.find_last_not_of(L'\0')) != result.size() - 1)
    {
        result.erase(end_pos + 1);
    }

    // 格式化路径

    for (size_t i = 0; i < result.size(); i++)
    {
        auto d = L'\\';

        if (result[i] == L'/') {
            result[i] = d;
        }
    }

    size_t start_pos = 0;

    std::wstring from = L"\\\\";

    start_pos = result.find(from, start_pos);

    while ((start_pos = result.find(from, start_pos)) != std::wstring::npos)
    {
        result.replace(start_pos, from.size(), L"\\");
    }

    return result;
}