/* Copyright (c) 2002-2012 Croteam Ltd. 
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

// [Cecil] Moved from Camera.cpp
struct SCameraPos {
  TIME tmTick;
  FLOAT fSpeed;
  FLOAT3D vPos;
  ANGLE3D aRot;
  FLOAT fFOV;
};

// [Cecil] Organized into an interface
class ICamera {
  public:
    static void Init(void);

    static void ReadPos(SCameraPos &cp);
    static void WritePos(SCameraPos &cp);

    static void Start(const CTFileName &fnmDemo);
    static void Stop(void);
    static BOOL IsOn(void);
    static void Render(CEntity *pen, CDrawPort *pdp);
};
