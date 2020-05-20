#include "Includes.h"


DWORD LocalPlayer::getLocalPlayer()
{
	return Hacks::mem.Read<DWORD>(Hacks::gameModule + dwLocalPlayer);
}

DWORD LocalPlayer::getClosestTarget(float fov)
{
	D3DXVECTOR3 viewAngles = LocalPlayer::getLocalViewAngles();
	D3DXVECTOR3 localEyePos = LocalPlayer::getLocalEyePos();

	DWORD bestEntity;

	for (int i = 0; i < 64; i++)
	{
		if (Entity::isValid(Entity::getEntBase(i)) && Entity::getEntTeam(Entity::getEntBase(i)) != LocalPlayer::getLocalTeam())
		{
			D3DXVECTOR3 angle = CalcAngle(localEyePos, Entity::getEntBonePos(Entity::getEntBase(i), Hacks::AimBone));
			D3DXVECTOR3 cAngles = ClampAngles(angle - viewAngles);
			float delta = sqrt(cAngles.x * cAngles.x + cAngles.y * cAngles.y);

			if (delta < fov)
			{
				fov = delta;
				bestEntity = Entity::getEntBase(i);
			}
		}
	}
	return bestEntity;
}

int LocalPlayer::getLocalFlags()
{
	return Hacks::mem.Read<int>(LocalPlayer::getLocalPlayer() + netvars::m_fFlags);
}

int LocalPlayer::getLocalHealth()
{
	return Hacks::mem.Read<int>(LocalPlayer::getLocalPlayer() + netvars::m_iHealth);
}

int LocalPlayer::getLocalTeam()
{
	return Hacks::mem.Read<int>(LocalPlayer::getLocalPlayer() + netvars::m_iTeamNum);
}

int LocalPlayer::getShotsFired()
{
	return Hacks::mem.Read<int>(LocalPlayer::getLocalPlayer() + m_iShotsFired);
}

void LocalPlayer::forceJump(int waitTime)
{
	Hacks::mem.Write<int>(Hacks::gameModule + dwForceJump, 1);
	Sleep(waitTime);
	Hacks::mem.Write<int>(Hacks::gameModule + dwForceJump, 0);
}

void LocalPlayer::forceAttack()
{
	Hacks::mem.Write<int>(Hacks::gameModule + dwForceAttack, 5);
	Sleep(50);
	Hacks::mem.Write<int>(Hacks::gameModule + dwForceAttack, 4);
}

void LocalPlayer::AimAtPlayer(DWORD player, int smooth, int bone)
{
	if (player != NULL)
	{
		D3DXVECTOR3 aimAngles = Entity::getEntBonePos(player, bone) - LocalPlayer::getLocalEyePos();
		VectorAngles(aimAngles, aimAngles);
		D3DXVECTOR3 delta = aimAngles - LocalPlayer::getLocalViewAngles();
		D3DXVECTOR3 sAngles = ClampAngles(LocalPlayer::getLocalViewAngles() + (delta / smooth));
		if (Entity::isValid(player))
			LocalPlayer::setLocalViewAngles(sAngles);
	}
}

int LocalPlayer::getLocalCrossID()
{
	return Hacks::mem.Read<int>(LocalPlayer::getLocalPlayer() + netvars::m_iCrosshairId);
}

D3DXVECTOR3 LocalPlayer::getLocalEyePos()
{
	D3DXVECTOR3 localPos = LocalPlayer::getLocalPos();
	localPos += Hacks::mem.Read<D3DXVECTOR3>(LocalPlayer::getLocalPlayer() + m_vecViewOffset);
	return localPos;
}

D3DXVECTOR3 LocalPlayer::getLocalPos()
{
	return Hacks::mem.Read<D3DXVECTOR3>(LocalPlayer::getLocalPlayer() + netvars::m_vecOrigin);
}

D3DXMATRIX	LocalPlayer::getLocalViewMatrix()
{
	return Hacks::mem.Read<D3DXMATRIX>(Hacks::gameModule + dwViewMatrix);
}

D3DXVECTOR3 LocalPlayer::getLocalViewAngles()
{
	return Hacks::mem.Read<D3DXVECTOR3>(Engine::GetEnginePointer() + dwClientState_ViewAngles);
}

void LocalPlayer::setLocalViewAngles(D3DXVECTOR3 angles)
{
	Hacks::mem.Write<D3DXVECTOR3>(Engine::GetEnginePointer() + dwClientState_ViewAngles, angles);
}

D3DXVECTOR3 LocalPlayer::getLocalPunchAngles()
{
	return Hacks::mem.Read<D3DXVECTOR3>(LocalPlayer::getLocalPlayer() + netvars::m_aimPunchAngle);
}

void LocalPlayer::setFlashMaxAlpha(float alpha)
{
	Hacks::mem.Write<float>(LocalPlayer::getLocalPlayer() + m_flFlashMaxAlpha, alpha);
}