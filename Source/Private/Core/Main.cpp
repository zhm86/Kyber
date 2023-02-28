// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <Base/Platform.h>
#include <Base/Version.h>
#include <Core/Program.h>
#include <windows.h>
#include <string>

extern "C" BOOL WINAPI DllMain(HINSTANCE hModule,DWORD dwReason,LPVOID lpReserved)
{
    static HINSTANCE hL;
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        hL = LoadLibrary(_T(".\\dinput8_org.dll"));
		if (!hL) return false;
        g_program = new Kyber::Program(hModule);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        delete g_program;
        FreeLibrary(hL);
    }

    return TRUE;
}

#pragma comment(linker, "/export:DirectInput8Create=dinput8_org.DirectInput8Create")

#pragma comment(linker, "/export:DllGetClassObject=dinput8_org.DllGetClassObject")

#pragma comment(linker, "/export:DllCanUnloadNow=dinput8_org.DllCanUnloadNow")

#pragma comment(linker, "/export:DllRegisterServer=dinput8_org.DllRegisterServer")

#pragma comment(linker, "/export:DllUnregisterServer=dinput8_org.DllUnregisterServer")
