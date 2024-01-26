#include "./util.h";
#include "hmc_string_util.h"
#include "hmc_napi_value_util.h"

bool util_diff_napi_type(napi_env env, napi_value value, napi_valuetype valuetype)
{
    napi_valuetype value_type;
    napi_typeof(env, value, &value_type);
    if (value_type == valuetype)
        return true;
    return false;
}

napi_valuetype util_get_napi_type(napi_env env, napi_value value)
{
    napi_valuetype value_type;
    napi_typeof(env, value, &value_type);
    return value_type;
}

string util_get_napi_type_name(napi_env env, napi_value value)
{
    napi_valuetype value_type;
    napi_typeof(env, value, &value_type);
    return hmc_napi_type::typeName(value_type);
}

struct hmcRect
{
    int x;
    int y;
    int height;
    int width;
};

//  https://blog.csdn.net/qq_32285693/article/details/126322110
//  授权 CC 4.0 BY-SA
/**
 * @brief 矩形相交判断
 *
 * @param inRect
 * @param mian
 * @return true
 * @return false
 */
bool rectInRect(hmcRect mian, hmcRect inRect)
{
    bool isInRet = true;
    // 得出对比传入的边界
    int in_x = inRect.x;
    int in_y = inRect.y;
    int in_xw = inRect.x + inRect.width;
    int in_hy = inRect.y + inRect.height;
    if (!inRect.x)
        in_x = 1;
    if (!inRect.y)
        in_y = 1;
    // 得出mian的边界
    int mian_x = mian.x;
    int mian_y = mian.y;
    int mian_xw = mian.x + mian.width;
    int mian_hy = mian.y + mian.height;

    isInRet = (((in_x >= mian_x && in_x < mian_xw) || (mian_x >= in_x && mian_x <= in_xw)) &&
               ((in_y >= mian_y && in_y < mian_hy) || (mian_y >= in_y && mian_y <= in_hy)))
                  ? false
                  : true;

    // 是否完全在另一个矩形内

    if (isInRet == false)
    {
        if (mian.x > inRect.x && mian.y > inRect.y &&
            mian.x + mian.width < inRect.x + inRect.width &&
            mian.y + mian.height < inRect.x + inRect.height)
        {
            return true;
        }

        return false;
    }
    return false;
}

//  https://blog.csdn.net/qq_32285693/article/details/126322110
//  授权 CC 4.0 BY-SA
/**
 * @brief 点在矩形中
 *
 * @param pt
 * @param rect
 * @return true
 * @return false
 */
bool pointInRect(POINT pt, hmcRect rect)
{
    if ((pt.x > rect.x) && (pt.y > rect.y) && (pt.x < (rect.x + rect.width)) && (pt.y < (rect.y + rect.height)))
    {
        return true;
    }
    return false;
}

hmcRect RECT2Rect(RECT inputRect)
{
    hmcRect out;
    out.height = inputRect.top - inputRect.bottom;
    out.width = inputRect.right - inputRect.left;
    out.x = inputRect.left;
    out.y = inputRect.top;
    return out;
}

/**
 * @brief 矩形相交判断
 *
 * @param inRect
 * @param mian
 * @return true
 * @return false
 */
bool RECTinRECT(RECT inRect, RECT mian)
{
    return rectInRect(RECT2Rect(inRect), RECT2Rect(mian));
}

/**
 * @brief 点在矩形中
 *
 * @param pt
 * @param rect
 * @return true
 * @return false
 */
bool pointInRECT(POINT pt, RECT inputRect)
{
    hmcRect rect = RECT2Rect(inputRect);
    if ((pt.x > rect.x) && (pt.y > rect.y) && (pt.x < (rect.x + rect.width)) && (pt.y < (rect.y + rect.height)))
    {
        return true;
    }
    return false;
}

bool isInside(int x1, int y1, int x2, int y2, int x, int y)
{
    if (x > x1 && x < x2 && y > y1 && y < y2)
        return true;
    return false;
}
