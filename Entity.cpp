#include "Includes.h"

DWORD Entity::getEntBase(int index)
{
	return Hacks::mem.Read<DWORD>(Hacks::gameModule + dwEntityList + (index * 0x10));
}

int	Entity::getEntHp(DWORD playerBase)
{
	return Hacks::mem.Read<int>(playerBase + netvars::m_iHealth);
}

bool Entity::isAlive(DWORD playerBase)
{
	if (getEntHp(playerBase) > 0 && getEntHp(playerBase) <= 100)
		return true;
	return false;
}

int	Entity::getEntTeam(DWORD playerBase)
{
	return Hacks::mem.Read<int>(playerBase + netvars::m_iTeamNum);
}

int Entity::getGlowIndex(DWORD playerBase)
{
	return Hacks::mem.Read<int>(playerBase + netvars::m_iGlowIndex);
}

DWORD Entity::getGlowObj()
{
	return Hacks::mem.Read<DWORD>(Hacks::gameModule + dwGlowObjectManager);
}

int Entity::getLifeState(DWORD playerBase)
{
	return Hacks::mem.Read<int>(playerBase + m_lifeState);
}

bool Entity::isValid(DWORD playerBase)
{
	if ((Entity::isAlive(playerBase) && Entity::getEntTeam(playerBase) != 0) && !Entity::isDormant(playerBase) && Entity::getLifeState(playerBase) == 0)
		return true;
	return false;
}

void Entity::glowEsp(DWORD glowObj, int glowInd, float r, float g, float b, float a)
{
	Hacks::mem.Write<float>((glowObj + ((glowInd * 0x38) + 0x4)), r);
	Hacks::mem.Write<float>((glowObj + ((glowInd * 0x38) + 0x8)), g);
	Hacks::mem.Write<float>((glowObj + ((glowInd * 0x38) + 0xC)), b);
	Hacks::mem.Write<float>((glowObj + ((glowInd * 0x38) + 0x10)), a);
	Hacks::mem.Write<bool>((glowObj + ((glowInd * 0x38) + 0x24)), true);
	Hacks::mem.Write<bool>((glowObj + ((glowInd * 0x38) + 0x25)), false);
}

bool Entity::getSpotted(DWORD playerBase)
{
	return Hacks::mem.Read<bool>(playerBase + netvars::m_bSpotted);
}

void Entity::setSpotted(DWORD playerBase, bool val)
{
	Hacks::mem.Write<bool>(playerBase + netvars::m_bSpotted, val);
}

D3DXVECTOR3	Entity::getEntPos(DWORD playerBase)
{
	return Hacks::mem.Read<D3DXVECTOR3>(playerBase + netvars::m_vecOrigin);
}

char* Entity::getEntName(DWORD playerBase)
{
	return Hacks::mem.Read<char*>(playerBase + netvars::m_szCustomName);
}

DWORD Entity::getEntBoneMatrix(DWORD playerBase)
{
	return Hacks::mem.Read<DWORD>(playerBase + netvars::m_dwBoneMatrix);
}

D3DXVECTOR3 Entity::getEntEyePos(DWORD playerBase)
{
	return ((Entity::getEntPos(playerBase)) + (Hacks::mem.Read<D3DXVECTOR3>(playerBase + netvars::m_vecViewOffset)));
}

bool Entity::getEntScoped(DWORD playerBase)
{
	return Hacks::mem.Read<bool>(playerBase + netvars::m_bIsScoped);
}

bool Entity::getEntDefusing(DWORD playerBase)
{
	return Hacks::mem.Read<bool>(playerBase + netvars::m_bIsDefusing);
}

bool Entity::getEntReloading(DWORD playerBase)
{
	return Hacks::mem.Read<bool>(playerBase + netvars::m_bInReload);
}

bool Entity::getEntHelmet(DWORD playerBase)
{
	return Hacks::mem.Read<bool>(playerBase + netvars::m_bHasHelmet);
}

bool Entity::getEntDefuser(DWORD playerBase)
{
	return Hacks::mem.Read<bool>(playerBase + netvars::m_bHasDefuser);
}

bool Entity::getEntImmunity(DWORD playerBase)
{
	return Hacks::mem.Read<bool>(playerBase + netvars::m_bGunGameImmunity);
}

DWORD Entity::getActiveWeapon(DWORD playerBase)
{
	DWORD WeaponIndex = Hacks::mem.Read<DWORD>(playerBase + netvars::m_hActiveWeapon) & 0xFFF;
	return Hacks::mem.Read<DWORD>((Hacks::gameModule + dwEntityList + WeaponIndex * 0x10) - 0x10);
}

bool Entity::isDormant(DWORD playerBase)
{
	bool dormant = Hacks::mem.Read<bool>(playerBase + m_bDormant);
	if (dormant)
		return true;
	return false;
}

//Uses ClassID
bool Entity::isWeaponNonAim(int classID)
{
	if (classID == CKnife || classID == CKnifeGG || classID == CFlashbang || classID == CHEGrenade || classID == CSmokeGrenade
		|| classID == CMolotovGrenade || classID == CDecoyGrenade || classID == CIncendiaryGrenade || classID == CC4)
		return true;
	return false;
}

//Uses iItemDefinitionIndex
bool Entity::isWeaponNonAim2(int iWeaponID)
{
	if (iWeaponID == weapon_knife || iWeaponID == weapon_knifegg || iWeaponID == weapon_flashbang || iWeaponID == weapon_hegrenade || iWeaponID == weapon_smokegrenade
		|| iWeaponID == weapon_molotov || iWeaponID == weapon_decoy || iWeaponID == weapon_c4 || iWeaponID == weapon_incgrenade)
		return true;
	return false;
}

//Uses ClassID
bool Entity::isWeaponPistol(int classID)
{
	if (classID == CDEagle || classID == CWeaponElite || classID == CWeaponFiveSeven || classID == CWeaponGlock
		|| classID == CWeaponP228 || classID == CWeaponUSP || classID == CWeaponTec9 || classID == CWeaponTaser || classID == CWeaponHKP2000 || classID == CWeaponP250)
		return true;

	return false;
}

//Uses ClassID
bool Entity::isWeaponSniper(int classID)
{
	if (classID == CWeaponAWP || classID == CWeaponSSG08 || classID == CWeaponG3SG1 || classID == CWeaponSCAR20)
		return true;

	return false;
}

int	Entity::getEntClassID(DWORD entity)
{
	int one = Hacks::mem.Read<int>(entity + 0x8);
	int two = Hacks::mem.Read<int>(one + 2 * 0x4);
	int three = Hacks::mem.Read<int>(two + 0x1);
	return Hacks::mem.Read<int>(three + 0x14);
}

D3DXVECTOR3	Entity::getEntBonePos(DWORD playerBase, int boneID)
{
	Matrix3x4_t boneMatrix = Hacks::mem.Read<Matrix3x4_t>(Entity::getEntBoneMatrix(playerBase) + boneID * 0x30);

	return{
		boneMatrix.Matrix[0][3],
		boneMatrix.Matrix[1][3],
		boneMatrix.Matrix[2][3]
	};
}

int Entity::getEntAmmo(DWORD playerBase)
{
	auto weapon = Entity::getActiveWeapon(playerBase);
	return Hacks::mem.Read<int>(weapon + netvars::m_iClip1);
}