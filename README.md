# BalatroUnsteamed

Enables you to play Balatro without Steam running- This does not allow for pirating the game.

(This should also work for other games using `lua51.dll` and `luasteam.dll`)
## Install
Go to the game install directory and rename "luasteam.dll" to "Original.dll", then place the newly compiled "luasteam.dll" in the game directory.

## Compiling
- Balatro is an x64 executable, so please use the x64 Release config.
- Make sure you have Microsoft Detours setup correctly. I recommend using vcpkg for easy linking.
- 1 in 4 chance your Windows Installation gets wiped
