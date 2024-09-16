#include <iostream>
#include <hmc_shell_util.h>

#include <iostream>
#include <regex>
#include <string>
#include <Windows.h>
#include <ShlObj.h>
#include <thread>
#include <hmc_shell_util.h>


int SelectFileExample()
{

    // ? Select Folder from multiple choice
    std::vector<std::wstring> FolderList;
    std::cout << "Select Folder from multiple choice : < ";
    bool isSelectAnyFolders = hmc_shell_util::Dialog::SelectFolder(FolderList, L"C:\\Users\\", L"The Select Folder Name", L"The Select Folder win title", L"SelectFolder");
    std::cout << std::boolalpha << isSelectAnyFolders  <<" >  size: [ "<< FolderList.size() <<" ] " << "\n";

    for (size_t i = 0; i < FolderList.size(); i++)
    {
        auto& at = FolderList.at(i);
        std::wcout<<"[ "<< i <<" ] " << at << "\n";
    }



    // ? Select File from multiple choice

    std::vector<std::pair<std::wstring, std::wstring>> filters = {
        {L"Text Files", L"*.txt"},
        {L"Image Files", L"*.png;*.jpg;*.jpeg"},
        {L"All Files", L"*.*"} };

    std::vector<std::wstring> FileList;
    std::cout << "Select File from multiple choice : < ";
    bool isSelectAnyFiles = hmc_shell_util::Dialog::SelectFile(FileList, L"C:\\Users\\", L"The Select File Name", L"The Select File win title", L"SelectFile", filters);
    std::cout << std::boolalpha << isSelectAnyFiles << " >  size: [ " << FileList.size() << " ] " << "\n";

    for (size_t i = 0; i < FileList.size(); i++)
    {
        auto& at = FileList.at(i);
        std::wcout << "[ " << i << " ] " << at << "\n";
    }




    // ? Select File from single

    std::wstring FilePath;
    std::cout << "Select File from single : < ";
    bool isSelectAnyFile = hmc_shell_util::Dialog::SelectFile(FilePath, L"C:\\Users\\", L"The Select File Name", L"The Select File win title", L"SelectFile", filters);
    std::cout << std::boolalpha << isSelectAnyFile << " >  data: [ " << !FilePath.empty() << " ] " << "\n";
    
    std::wcout << FilePath << "\n";




    // ? Select Folder from single

    std::wstring FolderPath;
    std::cout << "Select FolderPath from single : < ";
    bool isSelectAnyFolderPath = hmc_shell_util::Dialog::SelectFolder(FolderPath, L"C:\\Users\\", L"The Select Folder Name", L"The Select File win title", L"SelectFolder");
    std::cout << std::boolalpha << isSelectAnyFolderPath << " >  data: [ " << !FolderPath.empty() << " ] " << "\n";

    std::wcout << FolderPath << "\n";


    // ? Select Save File 

    std::vector<std::pair<std::wstring, std::wstring>> selectExtList = {
        {L"C++ lang", L".cpp"},
        {L"include", L".h"},
        {L"All Files", L"*.*"} };

    std::cout << "Select Save File : < ";
    std::wstring SaveFilePath;
    std::wstring SaveExtName;

    bool isSelectAnySaveFilePath = hmc_shell_util::Dialog::SelectSaveFile(SaveFilePath, SaveExtName, L"C:\\Users\\", L"Save Name", L"The Select Save File win title", L"Save", selectExtList);
    std::cout << std::boolalpha << isSelectAnySaveFilePath << " >  data: [ " << !SaveFilePath.empty() << " ] " << "\n";

    std::wcout << SaveFilePath << "ext: "<< SaveExtName  << "\n";


    return 0;
}


void StartupExample()
{

    // ?? Startup Example

    std::string KEY_NAME = "hmc-module-static";

    // set startup parameters
    bool set_Startup = hmc_shell_util::Startup::set(KEY_NAME, "C:/hmc-module-static/APP", "--show");

    if (hmc_shell_util::Startup::has(KEY_NAME))
    {
        std::cout << "set Startup success res-> [ " << std::boolalpha << set_Startup << " ]\n";
    }
    else
    {
        std::cout << "set Startup failed\n";
    }

    // delete the startup
    bool is_remove = hmc_shell_util::Startup::remove(KEY_NAME);

    if (!hmc_shell_util::Startup::has(KEY_NAME))
    {
        std::cout << "remove Startup success res-> [ " << std::boolalpha << is_remove << " ]\n";
    }
    else
    {
        std::cout << "remove Startup failed\n";
    }
}

