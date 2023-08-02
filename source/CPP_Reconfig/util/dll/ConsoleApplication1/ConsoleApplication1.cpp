#include "../../shell.hpp"

#include <Shellapi.h>
#include <Psapi.h>
#include <fstream>

// 获取图标 PNG 数据的函数（同上，省略...）

// 将 PNG 数据写入文件的函数
bool WritePNGToFile(const std::wstring& filePath, const std::vector<BYTE>& pngData)
{
    std::ofstream file(filePath, std::ios::binary);
    if (!file)
    {
        std::cout << "Failed to open file for writing." << std::endl;
        return false;
    }

    file.write(reinterpret_cast<const char*>(pngData.data()), pngData.size());
    file.close();

    return true;
}



int main(){
    cout<<"s->"<< hmc_shell::getShortcutLink(L"F:\\变量管理.lnk") .path <<endl;
    //WritePNGToFile(L"F:\\12113.png" ,hmc_shell::getThumbnailPngBuffer(L"F:\\chrome.exe.lnk", 128));
    //hmc_shell::getThumbnailPngFile(L"F:\\Dawn Launcher.lnk", L"F:\\123.png",256);
    //hmc_shell::beep();
    //hmc_shell::WinRunApplication("node");
}

