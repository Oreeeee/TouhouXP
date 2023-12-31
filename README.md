# Patched TH17 and TH18 executables (trial and full) to run on unmodified Windows XP or Windows 2000 with Extended Kernel

## How?
This patch modifies the header values of the executables to require Windows 2000 instead of Windows Vista. Without this patch, you will get `thXX.exe is not a valid Win32 application` error. Touhou 17 and 18 uses only APIs availible in XP (and 2000 Extended Kernel), so this patch can just work. In total, only 2 bytes get patched.

## Installation

### Simple
Download both thXX.exe and custom.exe for your corresponding game and replace them in your game files. If you use THCRAP don't worry about the errors and warnings about an unrecognized game, it will work fine. Updating DirectX 9 to June 2010 can be nescesarry [link](https://dl.bobpony.com/software/dx/directx_Jun2010_redist.zip).

### Manual - if you don't trust my executables
`patcher.py` will generate patched executables for the games. The script isn't Touhou-specific, so it might work on other programs too, but they might require having different headers to be modifies, so it's better to use CFF Explorer or a hex editor for them.

## What about Touhou 19 and future games?
Quoting [this article](https://www.thpatch.net/wiki/How_to_patch_a_new_Touhou_game_in_a_couple_of_hours#Tangentially_related:_Will_ZUN_finally_drop_Windows_XP_support_this_time?):
`Unfinished Dream of All Living Ghost, starting with version 0.02a, doesn't even support Windows 7 anymore. This is due to to the networking library the game uses, Photon. The game also uses a newer version of XInput then what Windows 7 has. Running the game on Windows 7 requires a custom winhttp.dll and a custom XInput1_4.dll. Running the game on XP will at the very least require OneCore in addition to that`.

However, future games without networking might be patchable.

## Screenshots
![th17 on Windows XP](assets/th17.png)

![th18 on Windows XP](assets/th18.png)