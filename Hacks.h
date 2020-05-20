#pragma once
#include <windows.h>

namespace Hacks
{
	extern bool RadarActive;
	extern bool GlowActive;
	extern bool BhopActive;
	extern bool TriggerBotActive;
	extern bool NoFlashActive;
	extern bool NoRecoilActive;
	extern bool AimBotActive;
	extern bool AimBotConfig;
	extern bool ChamsActive;
	extern bool NoHandsActive;

	extern int AimSmoothing;
	extern int AimBone;
	extern float AimFov;
	extern float ChamsBrightness;

	extern void Radar();
	extern void Glow();
	extern void Bhop();
	extern void TriggerBot();
	extern void NoFlash();
	extern void NoRecoil();
	extern void AimBot();
	extern void Chams();
	extern void NoHands();
	extern void Initialize();
	extern void HacksThread();

	extern ProcMem mem;
	extern DWORD gameModule;
	extern DWORD dwEngine;
}