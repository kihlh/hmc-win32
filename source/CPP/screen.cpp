#include "./Mian.hpp";
// #include "./include/napi.h";

// 截屏的存储为文件
#include <fstream>

// 获取指定坐标的颜色
// #include <gdiplus.h>
// using namespace Gdiplus;

// 小写转换
#include <algorithm>

// 截屏并且将其写入到文件系统
void CaptureBmpToFile(string filename, int x, int y, int nScopeWidth, int nScopeHeight)
{
    try
    {

        // 获取屏幕DC
        HDC hScreenDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
        // 获取屏幕分辨率
        if (nScopeWidth == 0 || nScopeWidth == NULL)
        {
            nScopeWidth = GetDeviceCaps(hScreenDC, HORZRES);
        }
        if (nScopeHeight == 0 || nScopeHeight == NULL)
        {
            nScopeHeight = GetDeviceCaps(hScreenDC, VERTRES);
        }
        // 创建与屏幕DC兼容的内存DC
        HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
        // 创建位图对象
        HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, nScopeWidth, nScopeHeight);
        // 将位图选入内存DC中
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
        // 将屏幕内容拷贝到内存DC中
        BitBlt(hMemoryDC, 0, 0, nScopeWidth, nScopeHeight, hScreenDC, 0, 0, SRCCOPY);
        // 将位图保存为文件
        PBITMAPINFO pBitmapInfo = (PBITMAPINFO) new char[sizeof(BITMAPINFOHEADER)];
        memset(pBitmapInfo, 0, sizeof(BITMAPINFOHEADER));
        pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        pBitmapInfo->bmiHeader.biWidth = nScopeWidth;
        pBitmapInfo->bmiHeader.biHeight = nScopeHeight;
        pBitmapInfo->bmiHeader.biPlanes = 1;
        pBitmapInfo->bmiHeader.biBitCount = 24;
        pBitmapInfo->bmiHeader.biCompression = BI_RGB;
        pBitmapInfo->bmiHeader.biSizeImage = nScopeWidth * nScopeHeight * 3;
        char *pData = NULL;
        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, pBitmapInfo->bmiHeader.biSizeImage);
        pData = (char *)GlobalLock(hGlobal);
        GetDIBits(hMemoryDC, hBitmap, 0, nScopeHeight, pData, pBitmapInfo, DIB_RGB_COLORS);
        DWORD dwBytesWritten = 0;
        BITMAPFILEHEADER bmfHeader;
        bmfHeader.bfType = 0x4d42;
        bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + pBitmapInfo->bmiHeader.biSize;
        bmfHeader.bfSize = bmfHeader.bfOffBits + pBitmapInfo->bmiHeader.biSizeImage;

        HANDLE hFile = CreateFileA(filename.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        WriteFile(hFile, &bmfHeader, sizeof(bmfHeader), &dwBytesWritten, NULL);
        WriteFile(hFile, pBitmapInfo, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
        WriteFile(hFile, pData, pBitmapInfo->bmiHeader.biSizeImage, &dwBytesWritten, NULL);
        CloseHandle(hFile);

        GlobalUnlock(hGlobal);
        GlobalFree(hGlobal);
        // 释放资源
        SelectObject(hMemoryDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hMemoryDC);
        DeleteDC(hScreenDC);
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
    }
}

// 截屏bmp文件 并且返回为缓冲区
void CaptureBmpToBuff(vector<unsigned char> &buffer, int x, int y, int nScopeWidth, int nScopeHeight)
{
    try
    {
        // 获取屏幕DC
        HDC hScreenDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
        // 获取屏幕分辨率
        if (nScopeWidth == 0 || nScopeWidth == NULL)
        {
            nScopeWidth = GetDeviceCaps(hScreenDC, HORZRES);
        }
        if (nScopeHeight == 0 || nScopeHeight == NULL)
        {
            nScopeHeight = GetDeviceCaps(hScreenDC, VERTRES);
        }
        // 创建与屏幕DC兼容的内存DC
        HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
        // 创建位图对象
        HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, nScopeWidth, nScopeHeight);
        // 将位图选入内存DC中
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
        // 将屏幕内容拷贝到内存DC中
        BitBlt(hMemoryDC, 0, 0, nScopeWidth, nScopeHeight, hScreenDC, 0, 0, SRCCOPY);
        // 将位图保存到缓冲区
        PBITMAPINFO pBitmapInfo = (PBITMAPINFO) new char[sizeof(BITMAPINFOHEADER)];
        memset(pBitmapInfo, 0, sizeof(BITMAPINFOHEADER));
        pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        pBitmapInfo->bmiHeader.biWidth = nScopeWidth;
        pBitmapInfo->bmiHeader.biHeight = nScopeHeight;
        pBitmapInfo->bmiHeader.biPlanes = 1;
        pBitmapInfo->bmiHeader.biBitCount = 24;
        pBitmapInfo->bmiHeader.biCompression = BI_RGB;
        pBitmapInfo->bmiHeader.biSizeImage = nScopeWidth * nScopeHeight * 3;
        char *pData = NULL;
        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, pBitmapInfo->bmiHeader.biSizeImage);
        pData = (char *)GlobalLock(hGlobal);
        GetDIBits(hMemoryDC, hBitmap, 0, nScopeHeight, pData, pBitmapInfo, DIB_RGB_COLORS);
        // 计算文件大小
        DWORD dwFileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + pBitmapInfo->bmiHeader.biSizeImage;
        // 分配缓冲区
        buffer.resize(dwFileSize);
        // 将位图数据拷贝到缓冲区中
        BITMAPFILEHEADER bmfHeader;
        bmfHeader.bfType = 0x4d42;
        bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        bmfHeader.bfSize = dwFileSize;
        memcpy(&buffer[0], &bmfHeader, sizeof(BITMAPFILEHEADER));
        memcpy(&buffer[sizeof(BITMAPFILEHEADER)], pBitmapInfo, sizeof(BITMAPINFOHEADER));
        memcpy(&buffer[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)], pData, pBitmapInfo->bmiHeader.biSizeImage);
        // 释放资源
        GlobalUnlock(hGlobal);
        GlobalFree(hGlobal);
        SelectObject(hMemoryDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hMemoryDC);
        DeleteDC(hScreenDC);
    }
    catch (const std::exception &e)
    {
    }
}

struct GetColorInfo
{
    int r;
    int g;
    int b;
    string hex;
};

// 获取屏幕上指定位置的颜色
GetColorInfo GetColor(int x, int y)
{
    GetColorInfo _ColorInfo;
    _ColorInfo.b = 0;
    _ColorInfo.g = 0;
    _ColorInfo.r = 0;
    _ColorInfo.hex = "#000000";
    // 获取屏幕DC
    HDC hScreenDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
    // 获取屏幕分辨率
    int nScopeWidth = GetDeviceCaps(hScreenDC, HORZRES);
    int nScopeHeight = GetDeviceCaps(hScreenDC, VERTRES);
    int nScopeX = 0;
    int nScopeY = 0;
    // nScopeWidth = 3840;
    //  坐标小于0肯定不对
    if (x < 0 || y < 0)
    {
        return _ColorInfo;
    }
    // 坐标超过了第一个屏幕  则应该开始判断是在第二个屏幕还是参数过界了
    if (nScopeHeight < y || nScopeWidth < x)
    {
        int is_ok = false;
        vector<RECT> deviceCapsAll = GetDeviceCapsAll();
        for (size_t i = 0; i < deviceCapsAll.size(); i++)
        {
            RECT deviceCaps = deviceCapsAll[i];
            if (isInside(deviceCaps.left, deviceCaps.top, deviceCaps.right, deviceCaps.bottom, x, y))
            {

                nScopeWidth = deviceCaps.right;
                nScopeHeight = deviceCaps.bottom;
                nScopeX = deviceCaps.left;
                nScopeY = deviceCaps.top;
                is_ok = true;
            }
        }
        if (!is_ok)
            return _ColorInfo;
    }
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, nScopeWidth, nScopeHeight);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
    BitBlt(hMemoryDC, 0, 0, nScopeWidth, nScopeHeight, hScreenDC, 0, 0, SRCCOPY);
    COLORREF color = GetPixel(hMemoryDC, x, y);
    SelectObject(hMemoryDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    DeleteDC(hScreenDC);

    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);
    char hex[8];
    sprintf_s(hex, "#%02X%02X%02X", r, g, b);
    _ColorInfo.b = b;
    _ColorInfo.g = g;
    _ColorInfo.r = r;
    _ColorInfo.hex = hex;
    transform(_ColorInfo.hex.begin(), _ColorInfo.hex.end(), _ColorInfo.hex.begin(), ::tolower);

    return _ColorInfo;
}

napi_value captureBmpToFile(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 5;
    napi_value args[5];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);

    hmc_is_argv_type(args, 0, 1, napi_string, NULL);
    hmc_is_argv_type(args, 1, 5, napi_number, NULL);
    int x, y, w, h;
    string FilePathA = call_String_NAPI_WINAPI_A(env, args[0]);
    napi_get_value_int32(env, args[1], &x);
    napi_get_value_int32(env, args[2], &y);
    napi_get_value_int32(env, args[3], &w);
    napi_get_value_int32(env, args[4], &h);
    CaptureBmpToFile(FilePathA, x, y, w, h);
    return NULL;
}

// napi_value captureBmpToBuff(napi_env env, napi_callback_info info)
// {
//     napi_status status;
//     size_t argc = 4;
//     napi_value args[4];
//     status = $napi_get_cb_info(argc, args);
//     assert(status == napi_ok);

//     hmc_is_argv_type(args, 0, 4, napi_number, NULL);
//     int x, y, w, h;
//     napi_get_value_int32(env, args[0], &x);
//     napi_get_value_int32(env, args[1], &y);
//     napi_get_value_int32(env, args[2], &w);
//     napi_get_value_int32(env, args[3], &h);

//     vector<unsigned char> buffer;
//     CaptureBmpToBuff(buffer, x, y, w, h);

//     napi_value result;
//     napi_value array_buffer_value;
//     void *array_buffer_data;
//     napi_status nstatus;
//     napi_create_arraybuffer(env, buffer.size(), &array_buffer_data, &array_buffer_value);
//     memcpy(array_buffer_data, buffer.data(), buffer.size());
//     napi_create_typedarray(env, napi_uint8_array, buffer.size(), array_buffer_value, 0, &result);
//     return array_buffer_value;
// }

napi_value getColor(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    status = $napi_get_cb_info(argc, args);
    assert(status == napi_ok);

    hmc_is_argv_type(args, 0, 2, napi_number, NULL);
    int x, y;
    napi_get_value_int32(env, args[0], &x);
    napi_get_value_int32(env, args[1], &y);

    GetColorInfo InfoColor = GetColor(x, y);
    napi_value _getColor;
    napi_create_object(env, &_getColor);
    napi_set_property(env, _getColor, _create_char_string(env, "r"), _create_int32_Number(env, InfoColor.r));
    napi_set_property(env, _getColor, _create_char_string(env, "g"), _create_int32_Number(env, InfoColor.g));
    napi_set_property(env, _getColor, _create_char_string(env, "b"), _create_int32_Number(env, InfoColor.b));
    napi_set_property(env, _getColor, _create_char_string(env, "hex"), _create_String(env, InfoColor.hex));

    return _getColor;
}
