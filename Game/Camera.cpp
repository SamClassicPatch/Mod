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

#include "StdAfx.h"
#include "Camera.h"

static BOOL _bCameraOn = FALSE;
static CTFileStream _strmScript;
static BOOL _bInitialized;
static FLOAT _fStartTime;
static SCameraPos _cp0, _cp1; // Two read positions for linear interpolation
static SCameraPos _cpCurrent; // Current camera position

// Camera control
static INDEX cam_bRecord           = FALSE;
static INDEX cam_bMoveForward      = FALSE;
static INDEX cam_bMoveBackward     = FALSE;
static INDEX cam_bMoveLeft         = FALSE;
static INDEX cam_bMoveRight        = FALSE;
static INDEX cam_bMoveUp           = FALSE;
static INDEX cam_bMoveDown         = FALSE;
static INDEX cam_bTurnBankingLeft  = FALSE;
static INDEX cam_bTurnBankingRight = FALSE;
static INDEX cam_bZoomIn           = FALSE;
static INDEX cam_bZoomOut          = FALSE;
static INDEX cam_bZoomDefault      = FALSE;
static INDEX cam_bResetToPlayer    = FALSE;
static INDEX cam_bSnapshot         = FALSE;
static FLOAT cam_fSpeed            = 1.0f;

// Camera functions
void ICamera::Init(void)
{
  _pShell->DeclareSymbol("user INDEX cam_bRecord;",           &cam_bRecord);
  _pShell->DeclareSymbol("user INDEX cam_bMoveForward;",      &cam_bMoveForward);
  _pShell->DeclareSymbol("user INDEX cam_bMoveBackward;",     &cam_bMoveBackward);
  _pShell->DeclareSymbol("user INDEX cam_bMoveLeft;",         &cam_bMoveLeft);
  _pShell->DeclareSymbol("user INDEX cam_bMoveRight;",        &cam_bMoveRight);
  _pShell->DeclareSymbol("user INDEX cam_bMoveUp;",           &cam_bMoveUp);
  _pShell->DeclareSymbol("user INDEX cam_bMoveDown;",         &cam_bMoveDown);
  _pShell->DeclareSymbol("user INDEX cam_bTurnBankingLeft;",  &cam_bTurnBankingLeft);
  _pShell->DeclareSymbol("user INDEX cam_bTurnBankingRight;", &cam_bTurnBankingRight);
  _pShell->DeclareSymbol("user INDEX cam_bZoomIn;",           &cam_bZoomIn);
  _pShell->DeclareSymbol("user INDEX cam_bZoomOut;",          &cam_bZoomOut);
  _pShell->DeclareSymbol("user INDEX cam_bZoomDefault;",      &cam_bZoomDefault);
  _pShell->DeclareSymbol("user INDEX cam_bSnapshot;",         &cam_bSnapshot);
  _pShell->DeclareSymbol("user INDEX cam_bResetToPlayer;",    &cam_bResetToPlayer);
  _pShell->DeclareSymbol("user FLOAT cam_fSpeed;",            &cam_fSpeed);
};

BOOL ICamera::IsOn(void) {
  return _bCameraOn;
};

void ICamera::ReadPos(SCameraPos &cp)
{
  // [Cecil] Finish reading positions
  if (_strmScript.AtEOF()) {
    Stop();
    return;
  }

  try {
    CTString strLine;
    _strmScript.GetLine_t(strLine);

    strLine.ScanF("%g: %g: %g %g %g:%g %g %g:%g",
      &cp.tmTick, &cp.fSpeed,
      &cp.vPos(1), &cp.vPos(2), &cp.vPos(3),
      &cp.aRot(1), &cp.aRot(2), &cp.aRot(3),
      &cp.fFOV);

  } catch (char *strError) {
    CPrintF("Camera: %s\n", strError);
  }
};

void ICamera::WritePos(SCameraPos &cp)
{
  try {
    CTString strLine(0, "%g: %g: %g %g %g:%g %g %g:%g",
      _pTimer->GetLerpedCurrentTick() - _fStartTime, 1.0f,
      cp.vPos(1), cp.vPos(2), cp.vPos(3),
      cp.aRot(1), cp.aRot(2), cp.aRot(3),
      cp.fFOV);

    _strmScript.PutLine_t(strLine);

  } catch (char *strError) {
    CPrintF("Camera: %s\n", strError);
  }
};

static inline void SetSpeed(FLOAT fSpeed) {
  _pShell->Execute(CTString(0, "dem_fRealTimeFactor = %g;", fSpeed));
};

void ICamera::Start(const CTFileName &fnmDemo) {
  _bCameraOn = FALSE;
  // [Cecil] Simple text file with a suffix
  CTFileName fnmScript = fnmDemo.NoExt() + "_CAM.txt";

  if (cam_bRecord) {
    try {
      _strmScript.Create_t(fnmScript);
    } catch (char *strError) {
      CPrintF("Camera: %s\n", strError);
      return;
    }

    _cpCurrent.vPos = FLOAT3D(0, 0, 0);
    _cpCurrent.aRot = ANGLE3D(0, 0, 0);
    _cpCurrent.fFOV = 90;
    _cpCurrent.fSpeed = 1;
    _cpCurrent.tmTick = 0;

  } else {
    try {
      _strmScript.Open_t(fnmScript);
    } catch (char *strError) {
      (void)strError;
      return;
    }
  }

  _bCameraOn = TRUE;
  _bInitialized = FALSE;
};

void ICamera::Stop(void) {
  if (_bCameraOn) {
    _strmScript.Close();
  }

  _bCameraOn = FALSE;
};

void ICamera::Render(CEntity *pen, CDrawPort *pdp) {
  SCameraPos &cp = _cpCurrent;

  if (cam_bRecord) {
    if (!_bInitialized) {
      _bInitialized = TRUE;
      SetSpeed(1.0f);
      _fStartTime = _pTimer->CurrentTick();
    }

    // [Cecil] Refactored camera movement
    FLOATmatrix3D m;
    MakeRotationMatrixFast(m, cp.aRot);

    FLOAT3D vMoveDir(
      cam_bMoveRight    - cam_bMoveLeft,
      cam_bMoveUp       - cam_bMoveDown,
      cam_bMoveBackward - cam_bMoveForward
    );

    cp.vPos += vMoveDir * cam_fSpeed * m;

    cp.aRot(1) -= _pInput->GetAxisValue(MOUSE_X_AXIS) * 0.5f;
    cp.aRot(2) += _pInput->GetAxisValue(MOUSE_Y_AXIS) * 0.5f;
    cp.aRot(3) += Sgn(cam_bTurnBankingLeft - cam_bTurnBankingRight) * 10.0f;

    if (cam_bZoomDefault) {
      cp.fFOV = 90.0f;
    } else {
      cp.fFOV = Clamp(cp.fFOV + FLOAT(cam_bZoomOut - cam_bZoomIn), 10.0f, 150.0f);
    }

    if (cam_bResetToPlayer) {
      cp.vPos = pen->GetPlacement().pl_PositionVector;
      cp.aRot = pen->GetPlacement().pl_OrientationAngle;
    }

    // Take position snapshot
    if (cam_bSnapshot) {
      cam_bSnapshot = FALSE;
      WritePos(cp);
    }

  } else {
    // Read first two positions in the beginning
    if (!_bInitialized) {
      _bInitialized = TRUE;

      ReadPos(_cp0);
      ReadPos(_cp1);
      SetSpeed(_cp0.fSpeed);
      _fStartTime = _pTimer->CurrentTick();
    }

    // Read next position when the destination expires
    TIME tmNow = _pTimer->GetLerpedCurrentTick() - _fStartTime;

    if (tmNow > _cp1.tmTick) {
      _cp0 = _cp1;
      ReadPos(_cp1);
      SetSpeed(_cp0.fSpeed);
    }

    // Interpolate between two positions
    FLOAT fRatio = (tmNow - _cp0.tmTick) / (_cp1.tmTick - _cp0.tmTick);

    cp.vPos = Lerp(_cp0.vPos, _cp1.vPos, fRatio);
    cp.aRot = Lerp(_cp0.aRot, _cp1.aRot, fRatio);
    cp.fFOV = Lerp(_cp0.fFOV, _cp1.fFOV, fRatio);
  }

  // Prepare view projection
  CPerspectiveProjection3D prProjection;
  prProjection.FOVL() = cp.fFOV;
  prProjection.ScreenBBoxL() = FLOATaabbox2D(FLOAT2D(0, 0), FLOAT2D(pdp->GetWidth(), pdp->GetHeight()));
  prProjection.AspectRatioL() = 1.0f;
  prProjection.FrontClipDistanceL() = 0.3f;

  // Render view from the camera
  CAnyProjection3D apr;
  apr = prProjection;
  apr->ViewerPlacementL() = CPlacement3D(cp.vPos, cp.aRot);

  RenderView(*pen->en_pwoWorld, *(CEntity *)NULL, apr, *pdp);
};
