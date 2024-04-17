#pragma once
#include <detours/detours.h>
#include <Windows.h>
#include <string>
#include "Console.h"

// define Lua function types
typedef int(*lua_CFunction) (void** L);
typedef void(__stdcall* lua_createtable_proto) (void** L, int narr, int nrec);
typedef void(__stdcall* lua_setfield_proto) (void** L, int idx, const char* k);
typedef void(__stdcall* lua_pushcclosure_proto)(void** L, lua_CFunction fn, int n);
typedef void(__stdcall* lua_pushboolean_proto)(void** L, int b);
typedef void(__stdcall* lua_pushnumber_proto)(void** L, double n);
typedef const char* (__stdcall* luaL_checklstring_proto)(void** L, int n, size_t* l);
typedef double(__stdcall* luaL_checkinteger_proto)(void** L, int n);

typedef int(__stdcall* luasteam_common_function_proto) (void** L);

typedef bool(__stdcall* SteamAPI_Init_proto) ();

int InstallDetourLuasteam(HMODULE SteamDLL, const char* fnName, luasteam_common_function_proto& functionOriginal, luasteam_common_function_proto functionHook)
{
    functionOriginal = (luasteam_common_function_proto)GetProcAddress(SteamDLL, fnName);
    if (!functionOriginal)
    {
        Console::Print("Failed to get address of " + std::string(fnName), 2);
        MessageBoxA(NULL, (std::string("Failed to get address of ") + std::string(fnName)).c_str(), "Error", MB_OK | MB_ICONERROR);
    }
    if (DetourTransactionBegin() != NO_ERROR ||
        DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
        DetourAttach(&(PVOID&)functionOriginal, functionHook) != NO_ERROR ||
        DetourTransactionCommit() != NO_ERROR) {
        Console::Print("Detour " + std::string(fnName) + " failed!", 2);
        return 1;
    }
    return 0;
}

int InstallDetourSteamAPI(HMODULE SteamDLL, const char* fnName, SteamAPI_Init_proto& functionOriginal, SteamAPI_Init_proto functionHook)
{
    functionOriginal = (SteamAPI_Init_proto)GetProcAddress(SteamDLL, fnName);
    if (!functionOriginal)
    {
        Console::Print("Failed to get address of " + std::string(fnName), 2);
        MessageBoxA(NULL, (std::string("Failed to get address of ") + std::string(fnName)).c_str(), "Error", MB_OK | MB_ICONERROR);
    }
    // Detour luasteam_init
    if (DetourTransactionBegin() != NO_ERROR ||
        DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
        DetourAttach(&(PVOID&)functionOriginal, functionHook) != NO_ERROR ||
        DetourTransactionCommit() != NO_ERROR) {
        Console::Print("Detour " + std::string(fnName) + " failed!", 2);
        return 1;
    }
    return 0;
}

template<typename FunctionType>
int InstallDetour(HMODULE SteamDLL, const char* fnName, FunctionType& functionOriginal, FunctionType functionHook)
{
    functionOriginal = (FunctionType)GetProcAddress(SteamDLL, fnName);
    if (!functionOriginal)
    {
        std::string errorMessage = "Failed to get address of " + std::string(fnName);
        Console::Print(errorMessage, 2);
        MessageBoxA(NULL, errorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Detour the function
    if (DetourTransactionBegin() != NO_ERROR ||
        DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
        DetourAttach(&(PVOID&)functionOriginal, functionHook) != NO_ERROR ||
        DetourTransactionCommit() != NO_ERROR) {
        std::string errorMessage = "Detour " + std::string(fnName) + " failed!";
        Console::Print(errorMessage, 2);
        return 1;
    }
    return 0;
}