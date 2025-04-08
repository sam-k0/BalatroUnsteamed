# BalatroUnsteamed 
[![MSBuild](https://github.com/sam-k0/BalatroUnsteamed/actions/workflows/msbuild.yml/badge.svg)](https://github.com/sam-k0/BalatroUnsteamed/actions/workflows/msbuild.yml)

*If you think this tool is helpful, please leave a ⭐️*

Enables you to play Balatro without Steam running.

**I do not condone pirating the game!**

(This should also work for other games using `lua51.dll` and `luasteam.dll`)
## Install
1) Go to the game install directory and rename "luasteam.dll" to "Original.dll", then place the newly compiled "luasteam.dll" in the game directory.
2) Run the game. The console will be hidden when everything worked correctly.
3) You can use `F2` to toggle the console.

# Uninstall

Delete "luasteam.dll" and rename "Original.dll" to "luasteam.dll"

## Compiling
- Balatro is an x64 executable, so please use the x64 Release config.
- Make sure you have Microsoft Detours setup correctly. I recommend using vcpkg for easy linking.
- 1 in 4 chance your Windows Installation gets wiped
