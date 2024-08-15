Proton work-around for "COTTON Reboot!"
=======================================
As of Proton ``9.0-2``, "COTTON Reboot!" is still unable to run in Proton without additional work-arounds. This work-around is needed to override the unimplemented functions.

Prerequisites
-------------
The game requires the Microsoft Visual C++ Runtime to be installed and will fail to run without it. You can install it with Protontricks:

1. Select the Game.
2. Choose "Select the default wineprefix".
3. Choose "Install a Windows Dll or component".
4. Choose "vcrun2019" (technically 2015 or later should work).

The underlying ``winetricks`` script is often out of date and you may get warnings related to a file not matching a hash.

If the Runtime installed correctly then the game should launch and display a warning about epilepsy (and piracy). It will then crash when it tries to load the video data.

Installation
------------
With the C++ Runtime correctly installed, you can now install the work-around:

1. Rename the ``steam_api64.dll`` file that comes with the game to ``steam_api64_orig.dll``.
2. Copy the replacement ``steam_api64.dll`` into the game folder.

When launched, the game should now continue past the warning. Unfortunately the video showing the publisher logo does not display (you only hear sound; probably a codec problem) but everything else works correctly including all the game cutscenes.

Inputs Not Working?
-------------------
Input via the keyboard or an Xbox 360 controller is recognised but the game ignores my Mayflash F101 Arcade Stick which is an XInput device. It's likely that the game is specifically looking for an actual Xbox Controller rather than just using XInput. I don't own a Steam Deck or a Steam Controller, but the game likely ignores input from those too.

If your controller inputs are not working, you will need to edit the Steam Input Configuration for the game to map the buttons to keyboard keys instead. The game uses the following keyboard inputs:

=========  ==========
Button     Key
=========  ==========
Menu       Esc
A          X
B          V
X          Z
Y          C
LT         A
RT         D
Direction  Arrow Keys
=========  ==========

Additional
----------
This software is provided without warranty of any kind (see ``LICENSE``) and is used at your own risk. I am unable to offer any support.
