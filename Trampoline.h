#pragma once
#include "detours/detours.h"
#include <vector>
#include <direct.h>
#include "Console.h"

HMODULE hOriginalDLL = NULL;
//Define export functions
#define EXPORT extern "C" __declspec(dllexport)
// define Lua function types
typedef int(*lua_CFunction) (void** L);
typedef void(__stdcall *lua_createtable_proto) (void** L, int narr, int nrec);

lua_createtable_proto original_lua_createtable = NULL;

void __stdcall lua_createtable_hook(void** L, int narr, int nrec) {
	std::cout << "lua_createtable called" << std::endl;
	original_lua_createtable(L, narr, nrec);
}


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

#pragma region Hooked Functions

EXPORT int luasteam_activateActionSet(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_activateActionSet");
    // Your implementation here
    Console::RedirectStdout();
    std::cout << "luasteam_activateActionSet called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_activateActionSetLayer(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_activateActionSetLayer");
    // Your implementation here
    Console::RedirectStdout();
    std::cout << "luasteam_activateActionSetLayer called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_activateGameOverlay(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_activateGameOverlay");

    // Your implementation here
    std::cout << "luasteam_activateGameOverlay called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_activateGameOverlayToWebPage(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_activateGameOverlayToWebPage");
    // Your implementation here
    std::cout << "luasteam_activateGameOverlayToWebPage called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_createItem(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_createItem");
    // Your implementation here
    std::cout << "luasteam_createItem called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_deactivateActionSetLayer(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_deactivateActionSetLayer");
    // Your implementation here
    std::cout << "luasteam_deactivateActionSetLayer called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_deactivateAllActionSetLayers(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_deactivateAllActionSetLayers");
    // Your implementation here
    std::cout << "luasteam_deactivateAllActionSetLayers called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_downloadLeaderboardEntries(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_downloadLeaderboardEntries");
    // Your implementation here
    std::cout << "luasteam_downloadLeaderboardEntries called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_equint64(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_equint64");
    // Your implementation here
    std::cout << "luasteam_equint64 called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_findLeaderboard(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_findLeaderboard");
    // Your implementation here
    std::cout << "luasteam_findLeaderboard called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_findOrCreateLeaderboard(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_findOrCreateLeaderboard");
    // Your implementation here
    std::cout << "luasteam_findOrCreateLeaderboard called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getAchievement(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getAchievement");
    // Your implementation here
    std::cout << "luasteam_getAchievement called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getActionOriginFromXboxOrigin(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getActionOriginFromXboxOrigin");
    // Your implementation here
    std::cout << "luasteam_getActionOriginFromXboxOrigin called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getActionSetHandle(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getActionSetHandle");
    // Your implementation here
    std::cout << "luasteam_getActionSetHandle called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getActiveActionSetLayers(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getActiveActionSetLayers");
    // Your implementation here
    std::cout << "luasteam_getActiveActionSetLayers called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getAnalogActionData(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getAnalogActionData");
    // Your implementation here
    std::cout << "luasteam_getAnalogActionData called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getAnalogActionHandle(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getAnalogActionHandle");
    // Your implementation here
    std::cout << "luasteam_getAnalogActionHandle called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getAnalogActionOrigins(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getAnalogActionOrigins");
    // Your implementation here
    std::cout << "luasteam_getAnalogActionOrigins called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getAppID(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getAppID");
    // Your implementation here
    std::cout << "luasteam_getAppID called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getConnectedControllers(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getConnectedControllers");
    // Your implementation here
    std::cout << "luasteam_getConnectedControllers called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getControllerForGamepadIndex(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getControllerForGamepadIndex");
    // Your implementation here
    std::cout << "luasteam_getControllerForGamepadIndex called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getCurrentActionSet(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getCurrentActionSet");
    // Your implementation here
    std::cout << "luasteam_getCurrentActionSet called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getCurrentGameLanguage(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getCurrentGameLanguage");
    // Your implementation here
    std::cout << "luasteam_getCurrentGameLanguage called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getDeviceBindingRevision(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getDeviceBindingRevision");
    // Your implementation here
    std::cout << "luasteam_getDeviceBindingRevision called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getDigitalActionData(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getDigitalActionData");
    // Your implementation here
    std::cout << "luasteam_getDigitalActionData called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getDigitalActionHandle(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getDigitalActionHandle");
    // Your implementation here
    std::cout << "luasteam_getDigitalActionHandle called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getDigitalActionOrigins(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getDigitalActionOrigins");
    // Your implementation here
    std::cout << "luasteam_getDigitalActionOrigins called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getFriendPersonaName(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getFriendPersonaName");
    // Your implementation here
    std::cout << "luasteam_getFriendPersonaName called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getGamepadIndexForController(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getGamepadIndexForController");
    // Your implementation here
    std::cout << "luasteam_getGamepadIndexForController called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getGlyphForActionOrigin(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getGlyphForActionOrigin");
    // Your implementation here
    std::cout << "luasteam_getGlyphForActionOrigin called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getInputTypeForHandle(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getInputTypeForHandle");
    // Your implementation here
    std::cout << "luasteam_getInputTypeForHandle called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getItemInstallInfo(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getItemInstallInfo");
    // Your implementation here
    std::cout << "luasteam_getItemInstallInfo called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getItemState(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getItemState");
    // Your implementation here
        std::cout << "luasteam_getItemState called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getItemUpdateProgress(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getItemUpdateProgress");
    // Your implementation here
    std::cout << "luasteam_getItemUpdateProgress called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getLeaderboardDisplayType(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getLeaderboardDisplayType");
    // Your implementation here
    std::cout << "luasteam_getLeaderboardDisplayType called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getLeaderboardEntryCount(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getLeaderboardEntryCount");
    // Your implementation here
    std::cout << "luasteam_getLeaderboardEntryCount called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getLeaderboardName(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getLeaderboardName");
    // Your implementation here
    std::cout << "luasteam_getLeaderboardName called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getLeaderboardSortMethod(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getLeaderboardSortMethod");
    // Your implementation here
    std::cout << "luasteam_getLeaderboardSortMethod called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getMotionData(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getMotionData");
    // Your implementation here
    std::cout << "luasteam_getMotionData called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getNumSubscribedItems(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getNumSubscribedItems");
    // Your implementation here
    std::cout << "luasteam_getNumSubscribedItems called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getPlayerSteamLevel(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getPlayerSteamLevel");
    // Your implementation here
    std::cout << "luasteam_getPlayerSteamLevel called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getRemotePlaySessionID(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getRemotePlaySessionID");
    // Your implementation here
    std::cout << "luasteam_getRemotePlaySessionID called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getStatFloat(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getStatFloat");
    // Your implementation here
    std::cout << "luasteam_getStatFloat called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getStatInt(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getStatInt");
    // Your implementation here
    std::cout << "luasteam_getStatInt called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getSteamID(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getSteamID");
    // Your implementation here
    std::cout << "luasteam_getSteamID called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getStringForActionOrigin(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getStringForActionOrigin");
    // Your implementation here
    std::cout << "luasteam_getStringForActionOrigin called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_getSubscribedItems(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_getSubscribedItems");
    // Your implementation here
    std::cout << "luasteam_getSubscribedItems called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_init(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_init");
    // Your implementation here
    std::cout << "luasteam_init called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_input_init(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_input_init");
    // Your implementation here
    std::cout << "luasteam_input_init called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_input_shutdown(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_input_shutdown");
    // Your implementation here
    std::cout << "luasteam_input_shutdown called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_parseUint64(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_parseUint64");
    // Your implementation here
    std::cout << "luasteam_parseUint64 called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_requestCurrentStats(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_requestCurrentStats");
    // Your implementation here
    std::cout << "luasteam_requestCurrentStats called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_resetAllStats(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_resetAllStats");
    // Your implementation here
    std::cout << "luasteam_resetAllStats called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_runCallbacks(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_runCallbacks");
    // Your implementation here
    std::cout << "luasteam_runCallbacks called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_runFrame(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_runFrame");
    // Your implementation here
    std::cout << "luasteam_runFrame called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_setAchievement(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_setAchievement");
    // Your implementation here
    std::cout << "luasteam_setAchievement called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_setItemContent(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_setItemContent");
    // Your implementation here
    std::cout << "luasteam_setItemContent called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_setItemDescription(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_setItemDescription");
    // Your implementation here
    std::cout << "luasteam_setItemDescription called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_setItemPreview(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_setItemPreview");
    // Your implementation here
    std::cout << "luasteam_setItemPreview called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_setItemTitle(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_setItemTitle");
    // Your implementation here
    std::cout << "luasteam_setItemTitle called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_setLEDColor(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_setLEDColor");
    // Your implementation here
    std::cout << "luasteam_setLEDColor called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_setRichPresence(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_setRichPresence");
    // Your implementation here
    std::cout << "luasteam_setRichPresence called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_setStatFloat(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_setStatFloat");
    // Your implementation here
    std::cout << "luasteam_setStatFloat called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_setStatInt(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_setStatInt");
    // Your implementation here
    std::cout << "luasteam_setStatInt called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_showBindingPanel(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_showBindingPanel");
    // Your implementation here
    std::cout << "luasteam_showBindingPanel called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_shutdown(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_shutdown");
    // Your implementation here
    std::cout << "luasteam_shutdown called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_startItemUpdate(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_startItemUpdate");
    // Your implementation here
    std::cout << "luasteam_startItemUpdate called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_startPlaytimeTracking(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_startPlaytimeTracking");
    // Your implementation here
    std::cout << "luasteam_startPlaytimeTracking called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_stopAnalogActionMomentum(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_stopAnalogActionMomentum");
    // Your implementation here
    std::cout << "luasteam_stopAnalogActionMomentum called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_stopPlaytimeTracking(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_stopPlaytimeTracking");
    // Your implementation here
    std::cout << "luasteam_stopPlaytimeTracking called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_stopPlaytimeTrackingForAllItems(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_stopPlaytimeTrackingForAllItems");
    // Your implementation here
    std::cout << "luasteam_stopPlaytimeTrackingForAllItems called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_storeStats(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_storeStats");
    // Your implementation here
    std::cout << "luasteam_storeStats called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_submitItemUpdate(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_submitItemUpdate");
    // Your implementation here
    std::cout << "luasteam_submitItemUpdate called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_translateActionOrigin(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_translateActionOrigin");
    // Your implementation here
    std::cout << "luasteam_translateActionOrigin called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_triggerHapticPulse(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_triggerHapticPulse");
    // Your implementation here
    std::cout << "luasteam_triggerHapticPulse called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_triggerRepeatedHapticPulse(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_triggerRepeatedHapticPulse");
    // Your implementation here
    std::cout << "luasteam_triggerRepeatedHapticPulse called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_triggerVibration(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_triggerVibration");
    // Your implementation here
    std::cout << "luasteam_triggerVibration called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_uint64ToString(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_uint64ToString");
    // Your implementation here
    std::cout << "luasteam_uint64ToString called" << std::endl;
    return pfnOriginal(L);
}

EXPORT int luasteam_uploadLeaderboardScore(void** L) {
    lua_CFunction pfnOriginal = (lua_CFunction)GetProcAddress(hOriginalDLL, "luasteam_uploadLeaderboardScore");
    // Your implementation here
    std::cout << "luasteam_uploadLeaderboardScore called" << std::endl;
    return pfnOriginal(L);
}

#pragma endregion Hooked Functions

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


        return TRUE;

	}
}