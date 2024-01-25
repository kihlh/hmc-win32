/**
 * @file hmc_usb_util.h
 * @author kiic
 * @brief 本模块是USB相关功能的合集
 * @version 0.1
 * @date 2024-01-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_USB_UTIL_HPP
#define MODE_INTERNAL_INCLUDE_HMC_USB_UTIL_HPP

#include <windows.h>
#include <setupapi.h>
#include <Cfgmgr32.h>
#include <iostream>
#include <vector>
#include <string>
#include <initguid.h>
#include <Usbiodef.h>
#include <Usb100.h>
#include <Usbioctl.h>
#include <variant>

#include <variant>

#pragma comment(lib, "Setupapi.lib")

#define EPOCH_TIME UINT64_C(116444736000000000) // 1970.01.01 00:00:000 in MS Filetime

namespace hmc_usb_util
{
    DEFINE_GUID(UsbClassGuid, 0xa5dcbf10L, 0x6530, 0x11d2, 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed);

    namespace hmc_define_util
    {
        std::wstring hmc_usb_util_escapeJsonString(const std::wstring &input, bool is_to_value);
    }
    struct chVolume
    {
        // 路径 "D:\\"
        std::wstring path;
        // 驱动器GUID名称  "\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\"
        std::wstring name;
        // 驱动器 磁盘号    "\\Device\\HarddiskVolume6"
        std::wstring device;

        std::wstring to_json();
    };

    struct chUsbDevsInfo
    {
        // 设备名称  如 "\\\\?\\usb\\vid_0bda&pid_8812\\123456\\{a5abcd66-6530-66d2-666f-666666666}""
        std::wstring name;
        // 设备名称
        std::wstring description;
        //  产品ID，它是由设备制造商分配的一个标识符，可以用来区分同一制造商产生的不同产品
        DWORD dwProductId;
        //  供应商ID，它是由USB实现论坛 (USB-IF) 分配的一个标识符
        DWORD dwVendorId;

        std::wstring to_json();
    };

    struct chHidSomeInfo
    {
        // 设备名称  如 "\\\\?\\HID#VID_AAAA&PID_AAA2&MI_01&Col01#8&3a6fd666&0&0000#{6d66666f6-f66f-66cf-66cb-006666000060}"
        std::wstring name;
        // 设备类型(只会是hid) 如: hid keyboard mouse
        std::wstring type;
        //  设备索引号，当系统中有多个相同类型的设备的时候，可以用来区分它们
        DWORD index;
        //  产品ID，它是由设备制造商分配的一个标识符，可以用来区分同一制造商产生的不同产品
        DWORD dwProductId;
        //  供应商ID，它是由USB实现论坛 (USB-IF) 分配的一个标识符
        DWORD dwVendorId;
        // 设备的版本号，它由设备制造商分配
        DWORD dwVersionNumber;
        //  这是设备类别的用途ID, 它配合 usUsagePage 使用，确定设备的具体类型和用途。例如，usUsage = 1 且 usUsagePage = 12 表示设备是一个人机接口设备的消费者控制设备。
        DWORD usUsage;
        //  这是设备的用途页面ID，它配合 usUsage 使用，确定设备的具体类型和用途。例如，usUsagePage = 1 表示设备是一个通用桌面控制类的设备，例如键盘或鼠标等。null
        DWORD usUsagePage;

        std::wstring to_json();
    };

    struct chHidKeyboardInfo
    {
        // 设备名称  如 "\\\\?\\HID#VID_AAAA&PID_AAA2&MI_01&Col01#8&3a6fd666&0&0000#{6d66666f6-f66f-66cf-66cb-006666000060}"
        std::wstring name;
        // 设备类型(只会是"keyboard") 如: hid keyboard mouse
        std::wstring type;
        //  设备索引号，当系统中有多个相同类型的设备的时候，可以用来区分它们
        DWORD index;
        // 键盘模式。比如，1 代表“普通模式”。
        DWORD dwKeyboardMode;
        // 键盘上功能键的数目。这个例子中显示的是有 12 个功能键，即F1至F12
        DWORD dwNumberOfFunctionKeys;
        // 键盘上指示灯的数目，比如数码锁 (Num Lock)，大写锁定 (Caps Lock) 和滚动锁定 (Scroll Lock) 等
        DWORD dwNumberOfIndicators;
        // 键盘上总的按键数目
        DWORD dwNumberOfKeysTotal;
        // 设备子类型。对应的值因设备的类型和制造商会有所不同
        DWORD dwSubType;
        // 设备类型。例如 81 代表键盘设备。
        DWORD dwType;

        std::wstring to_json();
    };

    struct chHidMouseInfo
    {
        // 设备名称  如 "\\\\?\\HID#VID_AAAA&PID_AAA2&MI_01&Col01#8&3a6fd666&0&0000#{6d66666f6-f66f-66cf-66cb-006666000060}"
        std::wstring name;
        // 设备类型(只会是"mouse") 如: hid keyboard mouse
        std::wstring type;
        //  设备索引号，当系统中有多个相同类型的设备的时候，可以用来区分它们
        DWORD index;
        // 鼠标设备ID，这是鼠标硬件的唯一标识符
        DWORD dwId;
        // 鼠标上的按钮数。
        DWORD dwNumberOfButtons;
        // 鼠标报告其状态的速率，以每秒报告数(即 Hertz)表示。例如，值1000表示每秒鼠标报告1000次其状态。dwSampleRate为0可能表示未知或状态未报告。
        DWORD dwSampleRate;
        // 表示这个鼠标是否有横向滚轮。此例中其值为false，表示鼠标没有横向滚轮。
        bool fHasHorizontalWheel;

        std::wstring to_json();
    };

    typedef std::variant<hmc_usb_util::chHidSomeInfo, hmc_usb_util::chHidKeyboardInfo, hmc_usb_util::chHidMouseInfo> thHidInfo;

    namespace hmc_define_util
    {
    }

    /**
     * @brief 格式化 驱动器路径（GUID） '\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\'  -> H:\\
     *
     * @param VolumeName
     * @return std::wstring
     */
    std::wstring formatVolumeName(std::wstring VolumeName);

    /**
     * @brief 格式化 驱动器路径 '\Device\HarddiskVolume2' / \DosDevices\H:  -> H:\\
     *
     * @param VolumeName
     * @return std::wstring
     */
    std::wstring formatVolumeNtName(std::wstring VolumeName);

    /**
     * @brief 获取当前文件系统的驱动器名称及路径
     *
     * @return std::vector<chVolume>
     */
    std::vector<chVolume> getVolumeList();

    /**
     * @brief USB设备名称(id)列表 （如U盘，加密狗，可移动硬盘，等）
     *
     * @return std::vector<std::wstring>
     */
    std::vector<std::wstring> getUsbDevsNameList();

    /**
     * @brief USB设备信息列表 （如U盘，加密狗，可移动硬盘，等）
     *
     * @return std::vector<hmc_usb_util::chUsbDevsInfo>
     */
    std::vector<hmc_usb_util::chUsbDevsInfo> getUsbDevsInfoList();

    /**
     * @brief 获取当前接入的usb hid设备的名称(id)列表（如键盘，鼠标，触摸屏，等）
     *
     * @return std::vector<std::wstring>
     */
    std::vector<std::wstring> getUsbHidNameList();

    /**
     * @brief 获取当前接入的usb hid设备的信息列表（如键盘，鼠标，触摸屏，等）
     *
     * @return std::vector<std::wstring>
     */
    std::vector<thHidInfo> getUsbHidList();

    /**
     * @brief VolumePath 格式化 驱动器路径
     * @param '\\\\?\\Volume{68de5ae6-0000-0000-0000-100000000000}\\123'  -> H:\\
     * @param '\Device\HarddiskVolume2\\123'   \\DosDevices\\H:\\123  -> H:\\
     * @return std::wstring
     */
    std::wstring formatVolumePath(std::wstring VolumePath);

}

#endif // MODE_INTERNAL_INCLUDE_HMC_USB_UTIL_HPP