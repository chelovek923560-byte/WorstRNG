# DOOMedRNG

Doom with the worst possible luck.

DOOMedRNG is a modified version of the [Woof](https://github.com/fabiangreffrath/woof)
source port. It adds an **RNG** menu (Options → RNG) with settings that rig the game's
random number rolls: damage rolls (melee / bullets / projectiles), hitscan accuracy for
the player and for enemies, enemy refire and aggression, enemy pathing and focus,
Revenant homing missiles, pain chance, radiation suit damage, the Icon of Sin spawn,
monster respawn and invisibility aim wobble.

Each setting can be **Default** (identical to the stock game), **Best** or **Worst**.
Whenever a result is rigged, it is always a value that a real roll could have produced,
so the game stays as close to vanilla Doom as possible. The settings are disabled in
demos and netgames.

## Building

Build it with CMake, or push the source to a GitHub repository and let the included
GitHub Actions workflow build Windows binaries for you. The executable is `doomedrng`
(`doomedrng.exe` on Windows) and needs `doomedrng.pk3` next to it.

You also need an IWAD (for example `DOOM2.WAD`, or the free `freedoom2.wad`).

## Credits and license

DOOMedRNG is free software, licensed under the GNU General Public License, version 2
or (at your option) any later version. See `COPYING`.

It is built on top of **Woof** by Fabian Greffrath, Roman Fomin and contributors, which is
a continuation of Lee Killough's **MBF**, which is derived from the Doom source code
released by id Software. All of their copyright notices are kept in the source files.
This project is not affiliated with or endorsed by the Woof project.

The source code of this modified version is available in this repository.
