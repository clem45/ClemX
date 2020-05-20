#pragma once
#include "windows.h"
#include <d3d9.h>
#include <d3dx9.h>
namespace Engine 
{
	extern DWORD GetEnginePointer();
	extern void ForceUpdate();
	extern bool IsInGame();
}