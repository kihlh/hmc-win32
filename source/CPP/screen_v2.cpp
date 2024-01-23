#include "./Mian.hpp";
#include "./screen_v2.hpp";
#include "./module/hmc_napi_value_util.h";

bool hmc_screen::isInside(int x1, int y1, int x2, int y2, int x, int y)
{
    if (x > x1 && x < x2 && y > y1 && y < y2)
        return true;
    return false;
}

// 截屏并且将其写入到文件系统
void hmc_screen::CaptureBmpToFile(string filename, int x, int y, int nScopeWidth, int nScopeHeight)
{
    vector<std::uint8_t> buffer;
    CaptureBmpToBuff(buffer, x, y, nScopeWidth, nScopeHeight);

    std::ofstream OutFile(filename.c_str(), std::ofstream::ios_base::trunc|std::ofstream::ios_base::binary );

    if (!OutFile.is_open())
    {
        return;
    }

    OutFile.write(reinterpret_cast<char *>(buffer.data()),buffer.size());

    if (OutFile.fail())
    {
        OutFile.close();
        return;
    }

    OutFile.close();
}

// 截屏bmp文件 并且返回为缓冲区
void hmc_screen::CaptureBmpToBuff(vector<unsigned char> &buffer, int x, int y, int nScopeWidth, int nScopeHeight)
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
    catch (...)
    {
    }
}

// 获取屏幕上指定位置的颜色
hmc_screen::chGetColorInfo hmc_screen::GetColor(int x, int y)
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

vector<RECT> hmc_screen::GetDeviceCapsAll()
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
    string FilePathA = hmc_napi_get_value::string_ansi(env, args[0]);
    napi_get_value_int32(env, args[1], &x);
    napi_get_value_int32(env, args[2], &y);
    napi_get_value_int32(env, args[3], &w);
    napi_get_value_int32(env, args[4], &h);
    hmc_screen::CaptureBmpToFile(FilePathA, x, y, w, h);
    return NULL;
}

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

    hmc_screen::chGetColorInfo InfoColor = hmc_screen::GetColor(x, y);
    napi_value _getColor;
    napi_create_object(env, &_getColor);
    napi_set_property(env, _getColor, as_String("r"), as_Number32(InfoColor.r));
    napi_set_property(env, _getColor, as_String("g"), as_Number32(InfoColor.g));
    napi_set_property(env, _getColor, as_String("b"), as_Number32(InfoColor.b));
    napi_set_property(env, _getColor, as_String("hex"), as_String(InfoColor.hex));

    return _getColor;
}
