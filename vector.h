#pragma once
#include "d3dx9.h"

D3DXVECTOR3 ClampAngles(D3DXVECTOR3 angle);
D3DXVECTOR3 CalcAngle(const D3DXVECTOR3& src, const D3DXVECTOR3& dst);
void VectorAngles(D3DXVECTOR3 forward, D3DXVECTOR3& angles);