#pragma once
#include "detours/detours.h"
#include <vector>
#include <direct.h>
#include "Console.h"

HMODULE hOriginalDLL = NULL;
//Define export functions
#define EXPORT extern "C" __declspec(dllexport)

// SteamAPI hooks
typedef bool(__stdcall *SteamAPI_Init_proto) ();
SteamAPI_Init_proto original_SteamAPI_Init = NULL;

// define Lua function types
typedef int(*lua_CFunction) (void** L);
typedef void(__stdcall *lua_createtable_proto) (void** L, int narr, int nrec);
typedef void(__stdcall *lua_setfield_proto) (void** L, int idx, const char* k);
typedef void(__stdcall *lua_pushcclosure_proto)(void** L, lua_CFunction fn, int n);
typedef void (__stdcall *lua_pushboolean_proto)(void** L, int b);
typedef void (__stdcall *lua_pushnumber_proto)(void** L, double n);

lua_createtable_proto original_lua_createtable = NULL;
lua_setfield_proto original_lua_setfield = NULL;
lua_pushcclosure_proto original_lua_pushcclosure = NULL;
lua_pushboolean_proto original_lua_pushboolean = NULL;
lua_pushnumber_proto original_lua_pushnumber = NULL;

//maybe
//- luaL_checkstring, luaL_checkint


// Luasteam functions
typedef int(__stdcall *luasteam_common_function_proto) (void** L);
luasteam_common_function_proto original_luasteam_init = NULL;
luasteam_common_function_proto original_luasteam_shutdown = NULL;
luasteam_common_function_proto original_luasteam_runCallbacks = NULL;
luasteam_common_function_proto original_luasteam_setAchievement = NULL;
luasteam_common_function_proto original_luasteam_storeStats = NULL;
luasteam_common_function_proto original_luasteam_getAchievement = NULL;
luasteam_common_function_proto original_luasteam_getStatInt = NULL;
luasteam_common_function_proto original_luasteam_setStatInt = NULL;
luasteam_common_function_proto original_luasteam_getSteamID = NULL;

// steam_api64.dll functions
bool __stdcall SteamAPI_Init_hook() {
    bool ret = original_SteamAPI_Init();
	std::cout << "SteamAPI_Init called: "<<ret << std::endl;
    return ret; // Hier einfach true zurückgeben
}


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
int __stdcall luasteam_init_hook(void** L) {// Pushes a luaboolean "true" to the stack
    int ret = original_luasteam_init(L); // Original callen
    std::cout << "luasteam_init called with return value "<<ret << std::endl;
	return (ret);
}

int __stdcall luasteam_shutdown_hook(void** L) { // return 0
	int ret = original_luasteam_shutdown(L);
	std::cout << "luasteam_shutdown called with return value " << ret << std::endl;
	return (ret);
}

int __stdcall luasteam_runCallbacks_hook(void** L) { // return 0
    std::cout << "luasteam_runCallbacks called" << std::endl;
    return original_luasteam_runCallbacks(L);
}
// setAchievements
int __stdcall luasteam_setAchievement_hook(void** L)
{
    // lua pushboolean(L, true);
    std::cout << "luasteam_setAchievement called" << std::endl;
	return  original_luasteam_setAchievement(L); // return 1
}

//storeStats
int __stdcall luasteam_storeStats_hook(void** L)
{
	std::cout << "luasteam_storeStats called" << std::endl;
	return original_luasteam_storeStats(L);
}

// getAchievement,
int __stdcall luasteam_getAchievement_hook(void** L)
{
    /**
    
    const char *ach_name = luaL_checkstring(L, 1);
    bool achieved = false;
    bool success = SteamUserStats()->GetAchievement(ach_name, &achieved);
    lua_pushboolean(L, success);
    if (success) {
        lua_pushboolean(L, achieved);
        return 2;
    } else {
        return 1;
    }
    
    
    */

    int ret = original_luasteam_getAchievement(L);
	std::cout << "luasteam_getAchievement called: "<<ret << std::endl;
    return ret;
}

// getStatInt
int __stdcall luasteam_getStatInt_hook(void** L)
{
	std::cout << "luasteam_getStatInt called" << std::endl;
	return original_luasteam_getStatInt(L);
}

//setStatInt
int __stdcall luasteam_setStatInt_hook(void** L)
{
	std::cout << "luasteam_setStatInt called" << std::endl;
	return original_luasteam_setStatInt(L);
}

//getSteamID
int __stdcall luasteam_getSteamID_hook(void** L)
{
	std::cout << "luasteam_getSteamID called" << std::endl;
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
		std::cout << "Failed to get address of luaopen_luasteam" << std::endl;
		return 0;
	}

    std::cout << "luaopen_luasteam called" << std::endl;

    return pfnOriginal(L);
}


int InstallDetourLuasteam(HMODULE SteamDLL, const char* fnName, luasteam_common_function_proto& functionOriginal, luasteam_common_function_proto functionHook)
{
    functionOriginal = (luasteam_common_function_proto)GetProcAddress(SteamDLL, fnName);
    if (!functionOriginal)
    {
        std::cout << "Failed to get address of" << fnName << GetLastError() << std::endl;
    }
    // Detour luasteam_init
    if (DetourTransactionBegin() != NO_ERROR ||
        DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
        DetourAttach(&(PVOID&)functionOriginal, functionHook) != NO_ERROR ||
        DetourTransactionCommit() != NO_ERROR) {
        std::cerr << "Detour failed" << std::endl;
        return 1;
    }
    return 0;
}

int InstallDetourSteamAPI(HMODULE SteamDLL, const char* fnName, SteamAPI_Init_proto& functionOriginal, SteamAPI_Init_proto functionHook)
{
    functionOriginal = (SteamAPI_Init_proto)GetProcAddress(SteamDLL, fnName);
    if (!functionOriginal)
    {
        std::cout << "Failed to get address of" << fnName << GetLastError() << std::endl;
    }
    // Detour luasteam_init
    if (DetourTransactionBegin() != NO_ERROR ||
        DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
        DetourAttach(&(PVOID&)functionOriginal, functionHook) != NO_ERROR ||
        DetourTransactionCommit() != NO_ERROR) {
        std::cerr << "Detour failed" << std::endl;
        return 1;
    }
    return 0;
}

namespace Trampoline {

	std::vector<std::string> g_vOriginalFunctions = {
        "luaopen_luasteam",
        "luasteam_activateActionSet",
        "luasteam_activateActionSetLayer",
        "luasteam_activateGameOverlay",
        "luasteam_activateGameOverlayToWebPage",
        "luasteam_createItem",
        "luasteam_deactivateActionSetLayer",
        "luasteam_deactivateAllActionSetLayers",
        "luasteam_downloadLeaderboardEntries",
        "luasteam_equint64",
        "luasteam_findLeaderboard",
        "luasteam_findOrCreateLeaderboard",
        "luasteam_getAchievement",
        "luasteam_getActionOriginFromXboxOrigin",
        "luasteam_getActionSetHandle",
        "luasteam_getActiveActionSetLayers",
        "luasteam_getAnalogActionData",
        "luasteam_getAnalogActionHandle",
        "luasteam_getAnalogActionOrigins",
        "luasteam_getAppID",
        "luasteam_getConnectedControllers",
        "luasteam_getControllerForGamepadIndex",
        "luasteam_getCurrentActionSet",
        "luasteam_getCurrentGameLanguage",
        "luasteam_getDeviceBindingRevision",
        "luasteam_getDigitalActionData",
        "luasteam_getDigitalActionHandle",
        "luasteam_getDigitalActionOrigins",
        "luasteam_getFriendPersonaName",
        "luasteam_getGamepadIndexForController",
        "luasteam_getGlyphForActionOrigin",
        "luasteam_getInputTypeForHandle",
        "luasteam_getItemInstallInfo",
        "luasteam_getItemState",
        "luasteam_getItemUpdateProgress",
        "luasteam_getLeaderboardDisplayType",
        "luasteam_getLeaderboardEntryCount",
        "luasteam_getLeaderboardName",
        "luasteam_getLeaderboardSortMethod",
        "luasteam_getMotionData",
        "luasteam_getNumSubscribedItems",
        "luasteam_getPlayerSteamLevel",
        "luasteam_getRemotePlaySessionID",
        "luasteam_getStatFloat",
        "luasteam_getStatInt",
        "luasteam_getSteamID",
        "luasteam_getStringForActionOrigin",
        "luasteam_getSubscribedItems",
        "luasteam_init",
        "luasteam_input_init",
        "luasteam_input_shutdown",
        "luasteam_parseUint64",
        "luasteam_requestCurrentStats",
        "luasteam_resetAllStats",
        "luasteam_runCallbacks",
        "luasteam_runFrame",
        "luasteam_setAchievement",
        "luasteam_setItemContent",
        "luasteam_setItemDescription",
        "luasteam_setItemPreview",
        "luasteam_setItemTitle",
        "luasteam_setLEDColor",
        "luasteam_setRichPresence",
        "luasteam_setStatFloat",
        "luasteam_setStatInt",
        "luasteam_showBindingPanel",
        "luasteam_shutdown",
        "luasteam_startItemUpdate",
        "luasteam_startPlaytimeTracking",
        "luasteam_stopAnalogActionMomentum",
        "luasteam_stopPlaytimeTracking",
        "luasteam_stopPlaytimeTrackingForAllItems",
        "luasteam_storeStats",
        "luasteam_submitItemUpdate",
        "luasteam_translateActionOrigin",
        "luasteam_triggerHapticPulse",
        "luasteam_triggerRepeatedHapticPulse",
        "luasteam_triggerVibration",
        "luasteam_uint64ToString",
        "luasteam_uploadLeaderboardScore"
    };
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

    

	BOOL LoadOriginalDLL()
	{
		// Find the original DLL in the current executable's directory
        std::string exedir = GetCurrentDir();
        std::cout << "Current directory: " << exedir << std::endl;

        // Load steam_api64.dll
        std::string steamapipath = (exedir + "\\steam_api64.dll");
        HMODULE hSteamDLL = LoadLibraryA(steamapipath.c_str());
        std::cout << "Expecting DLL in : " << steamapipath << std::endl;
        if(!hSteamDLL)
        {
			std::cout << "Failed to load the steam_api64.dll" << GetLastError() << std::endl;
			return FALSE;
		}
		else
		{
			std::cout << "Loaded the steam_api64.dll" << std::endl;
		}

        InstallDetourSteamAPI(hSteamDLL, "SteamAPI_Init", original_SteamAPI_Init, SteamAPI_Init_hook);

        // Load luasteam
        std::string szPath = exedir + "\\" + g_szOriginalDLL;
        std::cout << "Expecting DLL in : " << szPath << std::endl;

		hOriginalDLL = LoadLibraryA(szPath.c_str());
		if (!hOriginalDLL) {
			// Add some error handling here.
			//You can call GetLastError() to get more info about the error.
			std::cout << "Failed to load the original DLL" << GetLastError() << std::endl;
			return FALSE;
		}
        else
        {
			std::cout << "Loaded the original DLL" << std::endl;
		}

        // try to load lua functions
        std::string LUAdll = exedir + "\\lua51.dll";
        HMODULE hLuaDLL = GetModuleHandleA(LUAdll.c_str());
        if (!hLuaDLL) {
			std::cout << "Failed to load the lua DLL" << GetLastError() << std::endl;
			return FALSE;
		}
        else
        {
			std::cout << "Loaded the lua DLL" << std::endl;
		}

        HMODULE hOriginalLuaSteamDLL = GetModuleHandleA((exedir + "\\" + g_szOriginalDLL).c_str());
        if (!hOriginalLuaSteamDLL) {
            std::cout << "Failed to load the luasteam DLL for hooking" << GetLastError() << std::endl;
            return FALSE;
        }
        else
        {
            std::cout << "Loaded the luasteam DLL for hooking" << std::endl;
        }        



#pragma region Hooked lua_createtable
        original_lua_createtable = (lua_createtable_proto)GetProcAddress(hLuaDLL, "lua_createtable");
        if (!original_lua_createtable) {
            std::cout << "Failed to get address of lua_createtable" << GetLastError() << std::endl;
        }
        
        // Initialize Detours
        if (DetourTransactionBegin() != NO_ERROR ||
            DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
            DetourAttach(&(PVOID&)original_lua_createtable, lua_createtable_hook) != NO_ERROR ||
            DetourTransactionCommit() != NO_ERROR) {
            std::cerr << "Detour failed" << std::endl;
            return 1;
        }
#pragma endregion

#pragma region Hooked lua_setfield
        original_lua_setfield = (lua_setfield_proto)GetProcAddress(hLuaDLL, "lua_setfield");
        if (!original_lua_setfield)
        {
			std::cout << "Failed to get address of lua_setfield" << GetLastError() << std::endl;
		}

        // Detour lua_setfield
        if (DetourTransactionBegin() != NO_ERROR ||
            DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
            DetourAttach(&(PVOID&)original_lua_setfield, lua_setfield_hook) != NO_ERROR ||
            DetourTransactionCommit() != NO_ERROR) {
			std::cerr << "Detour failed" << std::endl;
			return 1;
		}
#pragma endregion

#pragma region Hooked lua_pushcclosure
        original_lua_pushcclosure = (lua_pushcclosure_proto)GetProcAddress(hLuaDLL, "lua_pushcclosure");
        if (!original_lua_pushcclosure)
        {
            std::cout<<"Failed to get address of lua_pushcclosure" << GetLastError() << std::endl;
        }
        // Detour lua_pushcclosure
        if (DetourTransactionBegin() != NO_ERROR ||
            DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
            DetourAttach(&(PVOID&)original_lua_pushcclosure, lua_pushcclosure_hook) != NO_ERROR ||
            DetourTransactionCommit() != NO_ERROR) {
            std::cerr << "Detour failed" << std::endl;
            return 1;
        }
#pragma endregion
    
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
        
        /// Hooked luasteam functions, getting called by the game

#pragma region Hooked luasteam_init
        original_luasteam_init = (luasteam_common_function_proto)GetProcAddress(hOriginalLuaSteamDLL, "luasteam_init");
        if (!original_luasteam_init)
        {
            std::cout << "Failed to get address of luasteam_init" << GetLastError() << std::endl;
        }
        // Detour luasteam_init
        if (DetourTransactionBegin() != NO_ERROR ||
            DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
            DetourAttach(&(PVOID&)original_luasteam_init, luasteam_init_hook) != NO_ERROR ||
            DetourTransactionCommit() != NO_ERROR) {
            std::cerr << "Detour failed" << std::endl;
            return 1;
        }
#pragma endregion
        
#pragma region Hooked luasteam_shutdown
        original_luasteam_shutdown = (luasteam_common_function_proto)GetProcAddress(hOriginalLuaSteamDLL, "luasteam_shutdown");
        if (!original_luasteam_shutdown)
        {
            std::cout << "Failed to get address of luasteam_shutdown" << GetLastError() << std::endl;
        }
        // Detour luasteam_init
        if (DetourTransactionBegin() != NO_ERROR ||
            DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
            DetourAttach(&(PVOID&)original_luasteam_shutdown, luasteam_shutdown_hook) != NO_ERROR ||
            DetourTransactionCommit() != NO_ERROR) {
            std::cerr << "Detour failed" << std::endl;
            return 1;
        }
#pragma endregion
        
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
        

        return TRUE;

	}
}