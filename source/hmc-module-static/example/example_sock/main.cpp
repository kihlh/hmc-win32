#include <iostream>


#ifdef _DEBUG
#ifdef _WIN64
#pragma comment(lib, "hmc-module-static_DEBUG_X64.lib")
#else
#pragma comment(lib, "hmc-module-static_DEBUG_X86.lib")
#endif
#else
#ifdef _WIN64
#pragma comment(lib, "hmc-module-static_RELEASE_X64.lib")
#else
#pragma comment(lib, "hmc-module-static_RELEASE_X86.lib")
#endif
#endif


void StartupExample();
int SelectFileExample();

int main()
{
    SelectFileExample();

    return 0;
}