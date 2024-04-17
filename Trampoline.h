#pragma once
#include "HookInstaller.h"
#include <vector>
#include <direct.h>


HMODULE hOriginalDLL = NULL;
//Define export functions
#define EXPORT extern "C" __declspec(dllexport)

// SteamAPI hooks
SteamAPI_Init_proto original_SteamAPI_Init = NULL;
// Lua function hooks
lua_createtable_proto original_lua_createtable = NULL;
lua_setfield_proto original_lua_setfield = NULL;
lua_pushcclosure_proto original_lua_pushcclosure = NULL;
lua_pushboolean_proto original_lua_pushboolean = NULL;
lua_pushnumber_proto original_lua_pushnumber = NULL;
luaL_checklstring_proto original_luaL_checklstring = NULL;
luaL_checkinteger_proto original_luaL_checkinteger = NULL;
// Luasteam functions
luasteam_common_function_proto original_luasteam_init = NULL;
luasteam_common_function_proto original_luasteam_shutdown = NULL;
luasteam_common_function_proto original_luasteam_runCallbacks = NULL;
luasteam_common_function_proto original_luasteam_setAchievement = NULL;
luasteam_common_function_proto original_luasteam_storeStats = NULL;
luasteam_common_function_proto original_luasteam_getAchievement = NULL;
luasteam_common_function_proto original_luasteam_getStatInt = NULL;
luasteam_common_function_proto original_luasteam_setStatInt = NULL;
luasteam_common_function_proto original_luasteam_getSteamID = NULL;

#pragma region steam_api64.dll functions
bool __stdcall SteamAPI_Init_hook() {
    Console::Print("SteamAPI_Init called");
    return true;
}
#pragma endregion

#pragma region lua function hooks
void __stdcall lua_createtable_hook(void** L, int narr, int nrec) {
	//std::cout << "lua_createtable called" << std::endl;
	original_lua_createtable(L, narr, nrec);
}

void __stdcall lua_setfield_hook(void** L, int idx, const char* k) {
	//std::cout << "lua_setfield called with idx " << idx << " value " << k << std::endl;
	original_lua_setfield(L, idx, k);
}

void __stdcall lua_pushcclosure_hook(void** L, lua_CFunction fn, int n) {
    if (n == 0)
    {
        //std::cout << "lua_pushcclosure called with " << reinterpret_cast<void*>(fn) << std::endl;
    }
	original_lua_pushcclosure(L, fn, n);
}
#pragma endregion

#pragma region luasteam function hook functions
int __stdcall luasteam_init_hook(void** L) {
    int ret = original_luasteam_init(L); // Original callen
	return (ret);
}

int __stdcall luasteam_shutdown_hook(void** L) { // return 0
    int ret = 0;//original_luasteam_shutdown(L);
	std::cout << "luasteam_shutdown called with return value " << ret << std::endl;
	return (ret);
}

int __stdcall luasteam_runCallbacks_hook(void** L) { // return 0
    std::cout << "luasteam_runCallbacks called" << std::endl;
    return 0;//original_luasteam_runCallbacks(L);
}
// setAchievements
int __stdcall luasteam_setAchievement_hook(void** L)
{
    original_luaL_checklstring(L, 1, NULL);
    original_lua_pushboolean(L, true); // Pushes a luaboolean "true" to the stack
    Console::Print("luasteam_setAchievement hook tripped!");
    return 1;
}

//storeStats
int __stdcall luasteam_storeStats_hook(void** L)// return 1
{
    Console::Print("luasteam_storeStats hook tripped!");
    original_lua_pushboolean(L, true); // Pushes a luaboolean "true" to the stack
    return 1;
}

// getAchievement,
int __stdcall luasteam_getAchievement_hook(void** L)
{
    original_luaL_checklstring(L, 1, NULL);
    Console::Print("luasteam_getAchievement hook tripped!");
    original_lua_pushboolean(L, true); // Pushes a luaboolean "true" to the stack
    original_lua_pushboolean(L, true); // Pushes a luaboolean "true" to the stack
    return 2;
}

// getStatInt
int __stdcall luasteam_getStatInt_hook(void** L)
{
    original_luaL_checklstring(L, 1, NULL);
    Console::Print("luasteam_getStatInt hook tripped!");
    original_lua_pushboolean(L, false);
    return 1;
}

//setStatInt
int __stdcall luasteam_setStatInt_hook(void** L)
{
    original_luaL_checklstring(L, 1, NULL);
    original_luaL_checkinteger(L, 2);
    original_lua_pushboolean(L, true);
    Console::Print("luasteam_setStatInt hook tripped");
    return 1;
}

//getSteamID
int __stdcall luasteam_getSteamID_hook(void** L)
{
    Console::Print("luasteam_getSteamID hook tripped");
	return original_luasteam_getSteamID(L);
}
#pragma endregion

// define the hooked functions
EXPORT int luaopen_luasteam(void** L) {

    if (hOriginalDLL == NULL)
    {
		std::cout << "hOriginalDLL is NULL!" << std::endl;
		return 0;
	}

    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luaopen_luasteam");
    
    if (pfnOriginal == NULL)
    {
		Console::Print("Failed to get address of luaopen_luasteam", 2);
        MessageBoxA(NULL, "Failed to get address of luaopen_luasteam", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

    Console::Print("luaopen_luasteam called");

    return pfnOriginal(L);
}



namespace Trampoline {

    const char* g_szOriginalDLL = "Original.dll";

    std::string GetCurrentDir() // Returns EXE directory
    {
        char cCurrentPath[FILENAME_MAX]; // get working directory into buffer
        if (!_getcwd(cCurrentPath, sizeof(cCurrentPath)))
            exit(-1);
        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; // not really required

        char* s = cCurrentPath; // save path from buffer into currentpath chararr
        std::string str(s);
        //free(s);
        return str;
    }

    HMODULE GetLoadedModuleHandle(std::string path)
    {
        HMODULE hMOD= GetModuleHandleA(path.c_str());
        Console::Print("Expecting lua51.dll in : " + path, 1);

        if (!hMOD) {
            Console::Print("Failed to load DLL from: " + path, 2);
            return NULL;
        }
        else
        {
            Console::Print("Loaded DLL from: " + path, 1);
        }
        return hMOD;
    }

	BOOL LoadOriginalDLL()
	{
		// Find the original DLL in the current executable's directory
        std::string exedir = GetCurrentDir();

        // Load steam_api64.dll
        std::string steamapipath = (exedir + "\\steam_api64.dll");
        HMODULE hSteamDLL = LoadLibraryA(steamapipath.c_str());
        Console::Print("Expecting steam_api64.dll in : " + steamapipath, 1);
        if(!hSteamDLL)
        {
            Console::Print("Failed to load the steam_api64.dll", 2);
			return FALSE;
		}
		else
		{
			Console::Print("Loaded steam_api64.dll", 1);
		}
        // try to install detour for SteamAPI_Init
        InstallDetourSteamAPI(hSteamDLL, "SteamAPI_Init", original_SteamAPI_Init, SteamAPI_Init_hook);

        // Load luasteam
        std::string originalLuasteamDLLpath = exedir + "\\" + g_szOriginalDLL;
        Console::Print("Expecting Original.dll in : " + originalLuasteamDLLpath, 1);

		hOriginalDLL = LoadLibraryA(originalLuasteamDLLpath.c_str());
		if (!hOriginalDLL) {
            Console::Print("Failed to load Original.dll, which is the renamed luasteam.dll", 2);
			return FALSE;
		}
        else
        {
			Console::Print("Loaded Original.dll, which is the renamed luasteam.dll", 1);
		}

        // try to load lua functions
        std::string lua51DLLpath = exedir + "\\lua51.dll";
        HMODULE hLuaDLL = GetLoadedModuleHandle(lua51DLLpath);
        if (hLuaDLL == NULL)
        {
			return FALSE;
		}


        HMODULE hOriginalLuaSteamDLL = GetLoadedModuleHandle(exedir + "\\" + g_szOriginalDLL);
        if (!hOriginalLuaSteamDLL) {
            return FALSE;
        }   


        InstallDetour<lua_createtable_proto>(hLuaDLL, "lua_createtable", original_lua_createtable, lua_createtable_hook);


        InstallDetour<lua_setfield_proto>(hLuaDLL, "lua_setfield", original_lua_setfield, lua_setfield_hook);


        InstallDetour<lua_pushcclosure_proto>(hLuaDLL, "lua_pushcclosure", original_lua_pushcclosure, lua_pushcclosure_hook);

    
        original_lua_pushboolean = (lua_pushboolean_proto)GetProcAddress(hLuaDLL, "lua_pushboolean");
        if (!original_lua_pushboolean)
        {
            std::cout << "Failed to get address of lua_pushboolean" << GetLastError() << std::endl;
        }


        original_lua_pushnumber = (lua_pushnumber_proto)GetProcAddress(hLuaDLL, "lua_pushnumber");       
        if (!original_lua_pushnumber)
        {
            std::cout << "Failed to get address of lua_pushnumber" << GetLastError() << std::endl;
        }

        original_luaL_checklstring = (luaL_checklstring_proto)GetProcAddress(hLuaDLL, "luaL_checklstring");
        if (!original_luaL_checklstring)
		{
			std::cout << "Failed to get address of luaL_checklstring" << GetLastError() << std::endl;
		}

        original_luaL_checkinteger = (luaL_checkinteger_proto)GetProcAddress(hLuaDLL, "luaL_checkinteger");
        if (!original_luaL_checkinteger)
		{
			std::cout << "Failed to get address of luaL_checkinteger" << GetLastError() << std::endl;
		}
        
        /// Hooked luasteam functions, getting called by the game
        InstallDetour<luasteam_common_function_proto>(hOriginalLuaSteamDLL, "luasteam_init", original_luasteam_init, luasteam_init_hook);

        InstallDetour<luasteam_common_function_proto>(hOriginalLuaSteamDLL, "luasteam_shutdown", original_luasteam_shutdown, luasteam_shutdown_hook);
        
        if (InstallDetourLuasteam(hOriginalLuaSteamDLL, "luasteam_runCallbacks", original_luasteam_runCallbacks, luasteam_runCallbacks_hook) == 1)
        {
            std::cout << "Failed to install detour luasteam_runCallbacks" << std::endl;
        }

        if (InstallDetourLuasteam(hOriginalLuaSteamDLL,"luasteam_setAchievement", original_luasteam_setAchievement, luasteam_setAchievement_hook) == 1)
        {
            std::cout << "Failed to install detour luasteam_setAchievement" << std::endl;
        }

        if (InstallDetourLuasteam(hOriginalLuaSteamDLL, "luasteam_storeStats", original_luasteam_storeStats, luasteam_storeStats_hook) == 1)
		{
			std::cout << "Failed to install detour luasteam_storeStats" << std::endl;
		}

        if (InstallDetourLuasteam(hOriginalLuaSteamDLL, "luasteam_getAchievement", original_luasteam_getAchievement, luasteam_getAchievement_hook) == 1)
        {
            std::cout << "Failed to install detour luasteam_getAchievement" << std::endl;
        }

        if (InstallDetourLuasteam(hOriginalLuaSteamDLL, "luasteam_getStatInt", original_luasteam_getStatInt, luasteam_getStatInt_hook) == 1)
		{
			std::cout << "Failed to install detour luasteam_getStatInt" << std::endl;
		}

        if (InstallDetourLuasteam(hOriginalLuaSteamDLL, "luasteam_setStatInt", original_luasteam_setStatInt, luasteam_setStatInt_hook) == 1)
        {
            std::cout << "Failed to install detour luasteam_setStatInt" << std::endl;
        }

        if (InstallDetourLuasteam(hOriginalLuaSteamDLL, "luasteam_getSteamID", original_luasteam_getSteamID, luasteam_getSteamID_hook) == 1)
		{
			std::cout << "Failed to install detour luasteam_getSteamID" << std::endl;
		}
        Console::Print("End of loading libraries and installing hooks. Hopefully everything works correctly now.", 69);
        return TRUE;

	}
}