/* Copyright (c) 2023 Dreamy Cecil
This program is free software; you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License as published by
the Free Software Foundation


This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#ifndef CECIL_INCL_GAMECOLORS_H
#define CECIL_INCL_GAMECOLORS_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

/* Usage reference table
 * SE_COL_ORANGE_LIGHT   - GameExecutable: LCDGetColor(<several>)
 * SE_COL_ORANGE_NEUTRAL - GameExecutable: LCDGetColor(<several>)
 * SE_COL_ORANGE_DARK    - GameExecutable: LCDGetColor("disabled unselected")
 * SE_COL_ORANGE_DARK_LT - GameExecutable: LCDGetColor("disabled selected")
 * SE_COL_BLUE_DARK_HV   - Game: Net graph background
 * SE_COL_BLUE_DARK      - Game: Several uses
 * SE_COL_BLUE_DARK_LT   - GameExecutable: LCDGetColor("edit fill")
 * SE_COL_BLUE_NEUTRAL   - Game: Main menu elements
 * SE_COL_BLUE_LIGHT     - Game: Loading bar with several levels of tint
 * SE_COL_BLUEGREEN_LT   - Game: Center message (e.g. "Paused")
 *
 * CECIL_COL_LIGHT      - GameExecutable: LCDGetColor(<several>); equal to C_WHITE in TFE
 * CECIL_COL_NEUTRAL    - GameExecutable: LCDGetColor(<several>); equal to C_WHITE in TFE
 * CECIL_COL_BORDER     - Game: Border boxes (player model, computer)
 * CECIL_COL_CONBORDER  - Game: Bottom line of the opened console
 * CECIL_COL_CONTEXT    - Game: Console text
 * CECIL_COL_COMPTEXT   - Game: Computer text
 * CECIL_COL_COMPCLOUDS - Game: Background clouds of the computer
 */

// Vanilla colors of the current theme
#define SE_COL_ORANGE_LIGHT   0xFFD70000
#define SE_COL_ORANGE_NEUTRAL 0xEE9C0000
#define SE_COL_ORANGE_DARK    0x9B4B0000
#define SE_COL_ORANGE_DARK_LT 0xBC6A0000
#define SE_COL_BLUE_DARK_HV   0x151C2300
#define SE_COL_BLUE_DARK      0x2A384600
#define SE_COL_BLUE_DARK_LT   0x43596F00
#define SE_COL_BLUE_NEUTRAL   0x5C7A9900
#define SE_COL_BLUE_LIGHT     0x64B4FF00
#define SE_COL_BLUEGREEN_LT   0x6CFF6C00

// New colors of the current theme
#define CECIL_COL_LIGHT      SE_COL_ORANGE_LIGHT
#define CECIL_COL_NEUTRAL    SE_COL_ORANGE_NEUTRAL
#define CECIL_COL_BORDER     SE_COL_BLUE_NEUTRAL
#define CECIL_COL_CONBORDER  SE_COL_BLUE_NEUTRAL
#define CECIL_COL_CONTEXT    SE_COL_BLUE_LIGHT
#define CECIL_COL_COMPTEXT   SE_COL_BLUE_LIGHT
#define CECIL_COL_COMPCLOUDS SE_COL_BLUE_NEUTRAL

#endif
