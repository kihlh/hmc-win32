
#ifndef defined(HMC_IMPORT_SCREEN_H)
#define HMC_IMPORT_SCREEN_H

// 截屏的存储为文件
#include <fstream>
// 小写转换
#include <algorithm>

namespace hmc_screen
{
     struct chGetColorInfo
    {
        int r;
        int g;
        int b;
        string hex;
    };

    vector<RECT> GetDeviceCapsAll();
    chGetColorInfo GetColor(int x, int y);
    bool isInside(int x1, int y1, int x2, int y2, int x, int y);
    void CaptureBmpToBuff(vector<unsigned char> &buffer, int x, int y, int nScopeWidth, int nScopeHeight);
    void CaptureBmpToFile(string filename, int x, int y, int nScopeWidth, int nScopeHeight);

    bool isInside(int x1, int y1, int x2, int y2, int x, int y)
    {
        if (x > x1 && x < x2 && y > y1 && y < y2)
            return true;
        return false;
    }

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

   
    // 获取屏幕上指定位置的颜色
    chGetColorInfo GetColor(int x, int y)
    {
        chGetColorInfo _ColorInfo;
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

    vector<RECT> GetDeviceCapsAll()
    {
        vector<RECT> CrectList;
        DISPLAY_DEVICE displayDevice;
        ZeroMemory(&displayDevice, sizeof(displayDevice));
        displayDevice.cb = sizeof(displayDevice);
        DEVMODE devMode;
        ZeroMemory(&devMode, sizeof(devMode));
        devMode.dmSize = sizeof(devMode);

        for (int i = 0; EnumDisplayDevices(NULL, i, &displayDevice, 0); ++i)
        {
            if (EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
            {
                int left = devMode.dmPosition.x;
                int top = devMode.dmPosition.y;
                int right = devMode.dmPosition.x + devMode.dmPelsWidth;
                int bottom = devMode.dmPosition.y + devMode.dmPelsHeight;
                RECT rect;
                rect.bottom = bottom;
                rect.left = left;
                rect.top = top;
                rect.right = right;
                CrectList.push_back(rect);
            }
        }
        return CrectList;
    }

}


#endif