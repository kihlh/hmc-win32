#include "../../window.hpp"
#include <iostream>



int main()
{
    bool ddf = false;
    HWND hwnd = (HWND)34014842;
    cout << "getClassName -> " << hmc_window::getClassName(hwnd) << endl;
    cout << "getStyle -> " << hmc_window::getStyle(hwnd) << endl;
    cout << "getWindowID -> " << hmc_window::getWindowID(hwnd) << endl;
    cout << "getWindowText -> " << hmc_window::getWindowText(hwnd, 1001) << endl;
    cout << "getSubWindow -> " << hmc_window::getSubWindow(hwnd).size() << endl;
    cout << "getWindowTitle -> " << hmc_window::getWindowTitle(hwnd) << endl;

    return 0;
}
