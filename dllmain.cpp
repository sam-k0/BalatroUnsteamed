// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include <Windows.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "Console.h"
#include "Trampoline.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		Console::RedirectStdout();
        Console::PrintRainbow("Balatro Unsteamed by sam-k0 - this is open source!");
        Console::Print("Press F1 to change log level", 69);
		Trampoline::LoadOriginalDLL();
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Trampoline::KeyboardMenu, 0, 0, 0);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

