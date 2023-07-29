// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

#ifndef HMC_LIBCP_H
#define HMC_LIBCP_H

#ifdef HMC_LIBCP_EXPORTS
#define HMC_LIBCP_API __declspec(dllexport)
#else
#define HMC_LIBCP_API __declspec(dllimport)
#endif



#endif // HMC_LIBCP_H



BOOL APIENTRY DllMain( HMODULE vhModule,DWORD  vul_reason_for_call,LPVOID vlpReserved)
{


    switch (vul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

