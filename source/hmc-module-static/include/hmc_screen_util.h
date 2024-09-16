#ifndef HMC_IMPORT_HMC_SCREEN_UTIL_V2_H
#define HMC_IMPORT_HMC_SCREEN_UTIL_V2_H

// 截屏的存储为文件
#include <fstream>
// 小写转换
#include <algorithm>
#include <string>
#include <vector>
#include <windows.h>

#if _HAS_CXX17
#include <variant>
#endif // _HAS_CXX17

namespace hmc_screen_util
{

    /**
     * @brief 坐标包含测试
     *
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @param x
     * @param y
     * @return true
     * @return false
     */
    extern bool isInside(int x1, int y1, int x2, int y2, int x, int y);

    struct chGetColorInfo
    {
        int r;
        int g;
        int b;
        std::string hex;
    };

    /**
     * @brief 获取所有屏幕的位置
     *
     * @return std::vector<RECT>
     */
    extern std::vector<RECT> GetDeviceCapsAll();

    /**
     * @brief 获取指定屏幕坐标的颜色
     *
     * @param x
     * @param y
     * @return chGetColorInfo
     */
    extern chGetColorInfo GetColor(int x, int y);
    /**
     * @brief 截屏到二进制并写入到文件
     *
     * @param filename
     * @param x
     * @param y
     * @param nScopeWidth
     * @param nScopeHeight
     */
    extern bool captureBmpToBuffer(std::vector<std::uint8_t> &output, int x, int y, int nScopeWidth, int nScopeHeight);

    /**
     * @brief 截屏到二进制并写入到文件
     *
     * @param filename
     * @param x
     * @param y
     * @param nScopeWidth
     * @param nScopeHeight
     */
    extern bool captureBmpToFileA(std::string output, int x, int y, int nScopeWidth, int nScopeHeight);
    /**
     * @brief 截屏到二进制并写入到文件
     *
     * @param filename
     * @param x
     * @param y
     * @param nScopeWidth
     * @param nScopeHeight
     */
    extern bool captureBmpToFileW(std::wstring output, int x, int y, int nScopeWidth, int nScopeHeight);

}


#if _HAS_CXX17
namespace hmc_screen_util
{
    /**
     * @brief 截屏到二进制并写入到文件
     *
     * @param filename
     * @param x
     * @param y
     * @param nScopeWidth
     * @param nScopeHeight
     */
    extern bool captureBmpToFile(std::variant<std::string, std::wstring> output, int x, int y, int nScopeWidth, int nScopeHeight);
}
#endif // _HAS_CXX17

#endif // HMC_IMPORT_HMC_SCREEN_UTIL_V2_H
