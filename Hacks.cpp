#include "Includes.h"

ProcMem Hacks::mem;
DWORD Hacks::gameModule;
DWORD Hacks::dwEngine;
bool Hacks::RadarActive = false;
bool Hacks::GlowActive = false;
bool Hacks::BhopActive = false;
bool Hacks::TriggerBotActive = false;
bool Hacks::NoFlashActive = false;
bool Hacks::NoRecoilActive = false;
bool Hacks::AimBotActive = false;
bool Hacks::AimBotConfig = false;
bool Hacks::ChamsActive = false;
bool Hacks::NoHandsActive = false;

int Hacks::AimSmoothing = 60;
int Hacks::AimBone = 8;
float Hacks::AimFov = 4.f;
float Hacks::ChamsBrightness = 255.f;

void Hacks::Radar()
{
	if (Hacks::RadarActive)
	{
		for (int i = 0; i < 32; i++)
		{
			if (Entity::isValid(Entity::getEntBase(i)))
			{
				Entity::setSpotted(Entity::getEntBase(i), true);
			}
		}
	}
}
 
void Hacks::Glow()
{
	if (Hacks::GlowActive)
	{
		for (int i = 0; i < 32; i++)
		{
			if (Entity::isValid(Entity::getEntBase(i)) && Entity::getEntTeam(i) != LocalPlayer::getLocalTeam())
			{
				if (Entity::getEntHp(Entity::getEntBase(i)) >= 70)
				{
					Entity::glowEsp(Entity::getGlowObj(), Entity::getGlowIndex(Entity::getEntBase(i)), 0, 255, 0, 255);
				}
				else if (Entity::getEntHp(Entity::getEntBase(i)) > 35 && Entity::getEntHp(Entity::getEntBase(i)) < 70)
				{
					Entity::glowEsp(Entity::getGlowObj(), Entity::getGlowIndex(Entity::getEntBase(i)), 255, 255, 0, 255);
				}
				else
				{
					Entity::glowEsp(Entity::getGlowObj(), Entity::getGlowIndex(Entity::getEntBase(i)), 255, 0, 0, 255);
				}
			}
		}
	}
}

void Hacks::Bhop()
{
	if (Hacks::BhopActive)
	{
		if (GetAsyncKeyState(VK_SPACE) && LocalPlayer::getLocalFlags() == FL_ON_GROUND)
		{
			LocalPlayer::forceJump();
		}
	}
}

void Hacks::TriggerBot()
{
	if (Hacks::TriggerBotActive && GetAsyncKeyState(VK_MENU))
	{
		DWORD detectedEnemy = Hacks::mem.Read<DWORD>(gameModule + dwEntityList + ((LocalPlayer::getLocalCrossID() - 1) * 0x10));
		if (LocalPlayer::getLocalTeam() != Entity::getEntTeam(detectedEnemy) && Entity::isValid(detectedEnemy))
		{
			LocalPlayer::forceAttack();
		}
	}
}

void Hacks::NoFlash()
{
	if (Hacks::NoFlashActive)
		LocalPlayer::setFlashMaxAlpha(0.f);
	else
		LocalPlayer::setFlashMaxAlpha(255.f);
}

void Hacks::NoRecoil()
{
	if (Hacks::NoRecoilActive && Engine::IsInGame())
	{
		static D3DXVECTOR3 OldVectorPunch;
		if (LocalPlayer::getShotsFired() > 1) {
			D3DXVECTOR3 MyViewAngles = LocalPlayer::getLocalViewAngles();
			D3DXVECTOR3 ViewAngles;
			D3DXVECTOR3 LocalPlayerPunch = LocalPlayer::getLocalPunchAngles();
			ViewAngles.x = MyViewAngles.x + OldVectorPunch.x;
			ViewAngles.y = MyViewAngles.y + OldVectorPunch.y;

			D3DXVECTOR3 NewAngles;
			NewAngles.x = ViewAngles.x - LocalPlayerPunch.x * 2;
			NewAngles.y = ViewAngles.y - LocalPlayerPunch.y * 2;
			NewAngles.z = 0.0f;
			LocalPlayer::setLocalViewAngles(ClampAngles(NewAngles));

			OldVectorPunch.x = LocalPlayerPunch.x * 2;
			OldVectorPunch.y = LocalPlayerPunch.y * 2;
		}
		else
		{
			OldVectorPunch.x = 0.0f;
			OldVectorPunch.y = 0.0f;
			OldVectorPunch.z = 0.0f;
		}
	}
}

void Hacks::AimBot()
{
	if (GetAsyncKeyState(VK_MENU) && Hacks::AimBotActive)
	{
		LocalPlayer::AimAtPlayer(LocalPlayer::getClosestTarget(Hacks::AimFov), Hacks::AimSmoothing, Hacks::AimBone);
	}
}

void Hacks::Chams()
{
	if (Hacks::ChamsActive)
	{
		for (int i = 0; i < 32; i++)
		{
			if (LocalPlayer::getLocalTeam() == Entity::getEntTeam(Entity::getEntBase(i)))
			{
				Hacks::mem.Write<BYTE>(Entity::getEntBase(i) + 0x70, BYTE(0));
				Hacks::mem.Write<BYTE>(Entity::getEntBase(i) + 0x71, BYTE(255));
				Hacks::mem.Write<BYTE>(Entity::getEntBase(i) + 0x72, BYTE(0));
			}
			else
			{
				Hacks::mem.Write<BYTE>(Entity::getEntBase(i) + 0x70, BYTE(255));
				Hacks::mem.Write<BYTE>(Entity::getEntBase(i) + 0x71, BYTE(0));
				Hacks::mem.Write<BYTE>(Entity::getEntBase(i) + 0x72, BYTE(0));
			}
		}
		DWORD thisPtr = (int)(Hacks::dwEngine + model_ambient_min - 0x2c);
		DWORD xored = *(DWORD*)&Hacks::ChamsBrightness^ thisPtr;
		mem.Write<int>(Hacks::dwEngine + model_ambient_min, xored);
	}
}

void Hacks::NoHands()
{
	if(Hacks::NoHandsActive)
		Hacks::mem.Write<int>(LocalPlayer::getLocalPlayer() + 0x258, 0); //n_ModelIndex 0x258
	else
		Hacks::mem.Write<int>(LocalPlayer::getLocalPlayer() + 0x258, 339); //n_ModelIndex 0x258, 339 = CT MODEL INDEX
}

void Hacks::Initialize()
{
	char process[] = "csgo.exe";
	char client_dll[] = "client_panorama.dll";
	char engine_dll[] = "engine.dll";
	Hacks::mem.Process(process);
	Hacks::gameModule = Hacks::mem.Module(client_dll);
	Hacks::dwEngine = Hacks::mem.Module(engine_dll);
}

void Hacks::HacksThread()
{
	Hacks::Radar();
	Hacks::Glow();
	Hacks::Bhop();
	Hacks::TriggerBot();
	Hacks::NoFlash();
	Hacks::NoRecoil();
	Hacks::AimBot();
	Hacks::Chams();
	Hacks::NoHands();
}