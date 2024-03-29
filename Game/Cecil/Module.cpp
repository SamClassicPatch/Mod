/* Copyright (c) 2023-2024 Dreamy Cecil
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

#include "StdAfx.h"

// Retrieve module information
MODULE_API void Module_GetInfo(CPluginInfo &info) {
  // Don't set utility flags, so it doesn't get freed by the plugin API
  info.SetUtility(PLF_MANUAL);

  // Metadata
  info.strAuthor = "Croteam, Dreamy Cecil";
  info.strName = "Game library";
  info.strDescription = "Main component that provides game logic.";
  info.ulVersion = CORE_PATCH_VERSION;
};
