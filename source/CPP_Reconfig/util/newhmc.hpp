#include "./include/global.hpp"

long hmc_Object_Context_id = 0;


/**
 * @brief 系统时间转为时间戳
 *
 * @param st
 * @return long
 */

long SystemTimeToTimestamp(const SYSTEMTIME &st)
{
    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);

    // 将 FILETIME 转换为 64 位整数，表示 100 毫微秒为单位的时间数
    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;

    // 将时间数转换为毫秒
    return static_cast<long>(uli.QuadPart / 10000);
}

/**
 * @brief 获取一个内容id
 *
 * @return long
 */
long getContextNextID()
{
    hmc_Object_Context_id++;
    return hmc_Object_Context_id;
};
