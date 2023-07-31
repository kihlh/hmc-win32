#include <windows.h>
#include <iostream>
#include "../console.hpp"
#include <vector>
#include <string>
#include <map>
#include <any>
#include <unordered_map>

using namespace std;

int main()
{
	hmc_console::setLevel(hmc_console::level::all);

	hmc_console::warn("example", "hmc_console -> ");
	hmc_console::error("example", "hmc_console -> ");
	hmc_console::info("example", "hmc_console -> ");

	hmc_console::debug("example", vector<int>({6566, 2314163, 136541313, 153541536, 442233}));

	hmc_console::debug("example", map<string, string>());

	hmc_console::debug("example", vector<string>({"sagdsh", "sagdfsh", "136541313", "sagdstgw4e"}));

	hmc_console::debug("HWND", GetConsoleWindow());

	return 0;
    
}