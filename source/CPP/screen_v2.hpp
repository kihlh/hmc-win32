#pragma once

#ifndef defined(HMC_IMPORT_SCREEN_H)
#define HMC_IMPORT_SCREEN_H

// 截屏的存储为文件
#include <fstream>
// 小写转换
#include <algorithm>
#include <string>
#include <vector>
#include "./Mian.hpp";

namespace hmc_screen
{
    struct chGetColorInfo
    {
        int r;
        int g;
        int b;
        std::string hex;
    };

    std::vector<RECT> GetDeviceCapsAll();
    chGetColorInfo GetColor(int x, int y);
    bool isInside(int x1, int y1, int x2, int y2, int x, int y);
    void CaptureBmpToBuff(std::vector<std::uint8_t> &buffer, int x, int y, int nScopeWidth, int nScopeHeight);
    void CaptureBmpToFile(std::string filename, int x, int y, int nScopeWidth, int nScopeHeight);

}

#endif