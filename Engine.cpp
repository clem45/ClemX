#include "Includes.h"

DWORD Engine::GetEnginePointer()
{
	return Hacks::mem.Read<DWORD>(Hacks::dwEngine + dwClientState);
}

void Engine::ForceUpdate()
{
	Hacks::mem.Write<int>(Engine::GetEnginePointer() + 0x16C, -1);
}

bool Engine::IsInGame()
{
	if (Hacks::mem.Read<int>(Engine::GetEnginePointer() + dwClientState_State) == 6)
	{
		return true;
	}
	return false;
}