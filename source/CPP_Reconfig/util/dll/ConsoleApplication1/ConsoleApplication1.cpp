
#include <windows.h>
#include <iostream>
#include "../../tray.hpp"

using namespace std;



int main() {
    auto trays = new hmc_tray::CTrayIcon();
    trays->Start();

    return 0;
}
