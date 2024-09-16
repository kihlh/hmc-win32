#include "hmc_screen_util.h"

std::vector<RECT> hmc_screen_util::GetDeviceCapsAll()
{
    std::vector<RECT> CrectList;
    try
    {
        DISPLAY_DEVICE displayDevice;
        ::ZeroMemory(&displayDevice, sizeof(displayDevice));
        displayDevice.cb = sizeof(displayDevice);
        DEVMODE devMode;
        ::ZeroMemory(&devMode, sizeof(devMode));
        devMode.dmSize = sizeof(devMode);

        for (int i = 0; ::EnumDisplayDevices(NULL, i, &displayDevice, 0); ++i)
        {
            if (::EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
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
    }
    catch (...)
    {
    }

    return CrectList;
}

bool hmc_screen_util::captureBmpToFile(std::variant<std::string, std::wstring> output, int upperLeftX, int upperLeftY, int nScopeWidth, int nScopeHeight)
{
    try
    {

        // 处理矩形宽高过低
        HDC hScreenDC_g = ::CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
        // 获取屏幕分辨率
        if (nScopeWidth <= 0 || nScopeWidth == NULL)
        {
            nScopeWidth = ::GetDeviceCaps(hScreenDC_g, HORZRES);
        }
        if (nScopeHeight <= 0 || nScopeHeight == NULL)
        {
            nScopeHeight = ::GetDeviceCaps(hScreenDC_g, VERTRES);
        }

        // 获取屏幕设备上下文
        HDC hScreenDC = ::GetDC(NULL);
        // 创建兼容的内存设备上下文
        HDC hMemoryDC = ::CreateCompatibleDC(hScreenDC);

        // 创建兼容的位图
        HBITMAP hBitmap = ::CreateCompatibleBitmap(hScreenDC, nScopeWidth, nScopeHeight);
        HGDIOBJ hOldBitmap = ::SelectObject(hMemoryDC, hBitmap);

        // 将屏幕内容拷贝到内存设备上下文中
        BitBlt(hMemoryDC, 0, 0, nScopeWidth, nScopeHeight, hScreenDC, upperLeftX, upperLeftY, SRCCOPY);

        // 保存位图到文件
        BITMAPFILEHEADER fileHeader;
        BITMAPINFOHEADER infoHeader;
        BITMAP bitmap;

        // 获取位图信息
        GetObject(hBitmap, sizeof(BITMAP), &bitmap);

        DWORD dwBmpSize = ((bitmap.bmWidth * bitmap.bmBitsPixel + 31) / 32) * 4 * bitmap.bmHeight;
        HANDLE hDIB = ::GlobalAlloc(GHND, dwBmpSize + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER));
        char *lpbitmap = (char *)::GlobalLock(hDIB);

        // 设置文件头
        fileHeader.bfType = 0x4D42; // 'BM'
        fileHeader.bfSize = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        fileHeader.bfReserved1 = 0;
        fileHeader.bfReserved2 = 0;
        fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        // 设置信息头
        infoHeader.biSize = sizeof(BITMAPINFOHEADER);
        infoHeader.biWidth = bitmap.bmWidth;
        infoHeader.biHeight = bitmap.bmHeight;
        infoHeader.biPlanes = 1;
        infoHeader.biBitCount = bitmap.bmBitsPixel;
        infoHeader.biCompression = BI_RGB;
        infoHeader.biSizeImage = 0;
        infoHeader.biXPelsPerMeter = 0;
        infoHeader.biYPelsPerMeter = 0;
        infoHeader.biClrUsed = 0;
        infoHeader.biClrImportant = 0;

        // 拷贝位图数据
        ::memcpy(lpbitmap, &fileHeader, sizeof(BITMAPFILEHEADER));
        ::memcpy(lpbitmap + sizeof(BITMAPFILEHEADER), &infoHeader, sizeof(BITMAPINFOHEADER));
        ::GetDIBits(hMemoryDC, hBitmap, 0, (UINT)bitmap.bmHeight, lpbitmap + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), (BITMAPINFO *)&infoHeader, DIB_RGB_COLORS);

        // 写入文件
        if (std::holds_alternative<std::wstring>(output))
        {
            HANDLE hFile = CreateFileW(std::get<std::wstring>(output).c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            DWORD dwBytesWritten;
            WriteFile(hFile, lpbitmap, dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
            CloseHandle(hFile);
        }
        else if (std::holds_alternative<std::string>(output))
        {
            HANDLE hFile = CreateFileA(std::get<std::string>(output).c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            DWORD dwBytesWritten;
            WriteFile(hFile, lpbitmap, dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
            CloseHandle(hFile);
        }

        // 清理
        ::GlobalUnlock(hDIB);
        ::GlobalFree(hDIB);
        ::SelectObject(hMemoryDC, hOldBitmap);
        ::DeleteObject(hBitmap);
        ::DeleteDC(hMemoryDC);
        ::ReleaseDC(NULL, hScreenDC);
    }
    catch (...)
    {

        return false;
    }
    return true;
}

bool hmc_screen_util::captureBmpToFileA(std::string output, int upperLeftX, int upperLeftY, int nScopeWidth, int nScopeHeight){
    return captureBmpToFile(std::variant<std::string, std::wstring>(output), upperLeftX, upperLeftY, nScopeWidth, nScopeHeight);
}

bool hmc_screen_util::captureBmpToFileW(std::wstring output, int upperLeftX, int upperLeftY, int nScopeWidth, int nScopeHeight){
    return captureBmpToFile(std::variant<std::string, std::wstring>(output), upperLeftX, upperLeftY, nScopeWidth, nScopeHeight);
}

bool hmc_screen_util::captureBmpToBuffer(std::vector<std::uint8_t> &output, int upperLeftX, int upperLeftY, int nScopeWidth, int nScopeHeight)
{
    try
    {

        // 处理矩形宽高过低
        HDC hScreenDC_g = ::CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
        // 获取屏幕分辨率
        if (nScopeWidth <= 0 || nScopeWidth == NULL)
        {
            nScopeWidth = ::GetDeviceCaps(hScreenDC_g, HORZRES);
        }
        if (nScopeHeight <= 0 || nScopeHeight == NULL)
        {
            nScopeHeight = ::GetDeviceCaps(hScreenDC_g, VERTRES);
        }

        // 获取屏幕设备上下文
        HDC hScreenDC = ::GetDC(NULL);
        // 创建兼容的内存设备上下文
        HDC hMemoryDC = ::CreateCompatibleDC(hScreenDC);

        // 创建兼容的位图
        HBITMAP hBitmap = ::CreateCompatibleBitmap(hScreenDC, nScopeWidth, nScopeHeight);
        HGDIOBJ hOldBitmap = ::SelectObject(hMemoryDC, hBitmap);

        // 将屏幕内容拷贝到内存设备上下文中
        ::BitBlt(hMemoryDC, 0, 0, nScopeWidth, nScopeHeight, hScreenDC, upperLeftX, upperLeftY, SRCCOPY);

        // 保存位图到文件
        BITMAPFILEHEADER fileHeader;
        BITMAPINFOHEADER infoHeader;
        BITMAP bitmap;

        // 获取位图信息
        ::GetObjectW(hBitmap, sizeof(BITMAP), &bitmap);

        DWORD dwBmpSize = ((bitmap.bmWidth * bitmap.bmBitsPixel + 31) / 32) * 4 * bitmap.bmHeight;
        HANDLE hDIB = ::GlobalAlloc(GHND, dwBmpSize + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER));
        char *lpbitmap = (char *)::GlobalLock(hDIB);

        // 设置文件头
        fileHeader.bfType = 0x4D42; // 'BM'
        fileHeader.bfSize = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        fileHeader.bfReserved1 = 0;
        fileHeader.bfReserved2 = 0;
        fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        // 设置信息头
        infoHeader.biSize = sizeof(BITMAPINFOHEADER);
        infoHeader.biWidth = bitmap.bmWidth;
        infoHeader.biHeight = bitmap.bmHeight;
        infoHeader.biPlanes = 1;
        infoHeader.biBitCount = bitmap.bmBitsPixel;
        infoHeader.biCompression = BI_RGB;
        infoHeader.biSizeImage = 0;
        infoHeader.biXPelsPerMeter = 0;
        infoHeader.biYPelsPerMeter = 0;
        infoHeader.biClrUsed = 0;
        infoHeader.biClrImportant = 0;

        // 拷贝位图数据
        ::memcpy(lpbitmap, &fileHeader, sizeof(BITMAPFILEHEADER));
        ::memcpy(lpbitmap + sizeof(BITMAPFILEHEADER), &infoHeader, sizeof(BITMAPINFOHEADER));
        ::GetDIBits(hMemoryDC, hBitmap, 0, (UINT)bitmap.bmHeight, lpbitmap + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), (BITMAPINFO *)&infoHeader, DIB_RGB_COLORS);

        size_t bitmap_length = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        output.reserve(bitmap_length);
        for (size_t i = 0; i < bitmap_length; i++)
        {
            output.push_back(lpbitmap[i]);
        }

        // 清理
        ::GlobalUnlock(hDIB);
        ::GlobalFree(hDIB);
        ::SelectObject(hMemoryDC, hOldBitmap);
        ::DeleteObject(hBitmap);
        ::DeleteDC(hMemoryDC);
        ::ReleaseDC(NULL, hScreenDC);
    }
    catch (...)
    {
        output.clear();
        output.shrink_to_fit();
        output.resize(0);
        return false;
    }
    return true;
}

bool hmc_screen_util::isInside(int x1, int y1, int x2, int y2, int x, int y)
{
    if (x > x1 && x < x2 && y > y1 && y < y2)
        return true;
    return false;
}
