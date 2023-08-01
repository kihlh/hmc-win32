#include "../../shell.hpp"
#include <Shellapi.h>
#include <Psapi.h>



int main(){
    cout<<"s->"<< hmc_shell::getShortcutLink(L"F:\\变量管理.lnk") .path <<endl;
    
    hmc_shell::WinRunApplication("node");
}

