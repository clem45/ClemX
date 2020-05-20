#include "Includes.h"
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void ClemX::UpdateMenu()
{
	system("CLS");
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << "Bienvenue sur l'interface de ClemExternal, version actuelle : 3.0 \n";
	if (Hacks::AimBotConfig)
	{
		std::cout << "Options aimbot actuelles : \n Smoothing (lenteur) : " << Hacks::AimSmoothing << "\n Os a viser : " << Hacks::AimBone << "\n FOV de l'aimbot : " << Hacks::AimFov;
		std::cout << "\nPour les os, mettre 8 pour viser la tete et 4 pour le milieu corps le reste bat la race \n Le fov determinera la distance au joueur pour qu'il s'active (recommendation legit : 4)";
		std::cout << "\nMerci d'entrer la valeur du smoothing (1 = aimlock) + c'est haut + ce sera legit (recommendation legit = 60) \n";
		cin >> Hacks::AimSmoothing;
		std::cout << "Vous avez desormais un smoothing de : " << Hacks::AimSmoothing << "\n";
		std::cout << "Merci d'entrer la valeur de l'os \n";
		cin >> Hacks::AimBone;
		std::cout << "Vous viserez desormais sur l'os : " << Hacks::AimBone << "\n";
		std::cout << "Merci d'entrer la valeur du fov souhaitee \n";
		cin >> Hacks::AimFov;
		std::cout << "Votre fov est desormais de : " << Hacks::AimFov << " degres \n";
		std::cout << "Validation des options et retour a l'accueil en cours... \n";
		Sleep(2500);
		Hacks::AimBotConfig = !Hacks::AimBotConfig;
		ClemX::UpdateMenu();
	}
	else
	{
		if (Hacks::RadarActive)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "[F1] Radar : Actif\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "[F1] Radar : Inactif\n";
		}
		if (Hacks::GlowActive)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "[F2] Glow Wallhack : Actif\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "[F2] Glow Wallhack : Inactif\n";
		}
		if (Hacks::BhopActive)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "[F3] Bhop : Actif\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "[F3] Bhop : Inactif\n";
		}
		if (Hacks::TriggerBotActive)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "[F4] TriggerBot : Actif\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "[F4] TriggerBot : Inactif\n";
		}
		if (Hacks::NoFlashActive)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "[F5] NoFlash : Actif\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "[F5] NoFlash : Inactif\n";
		}
		if (Hacks::NoRecoilActive)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "[F6] NoRecoil : Actif\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "[F6] NoRecoil : Inactif\n";
		}
		if (Hacks::AimBotActive)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "[F7] AimBot : Actif\n";
			SetConsoleTextAttribute(hConsole, 11);
			std::cout << "	[F8] Configurer l'aimbot\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "[F7] AimBot : Inactif\n";
		}
		if (Hacks::ChamsActive)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "[F9] Chams : Actif\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "[F9] Chams : Inactif\n";
		}
		if (Hacks::NoHandsActive)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "[F10] NoHands : Actif\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "[F10] NoHands : Inactif\n";
		}
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "Utilisation du TriggerBot : ";
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "ALT GAUCHE \n";
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "Utilisation de l'aimbot : ";
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "ALT GAUCHE \n";
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "Couleurs du WallHack Glow : \n";
		std::cout << "+ de 70 de vie : ";
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "VERT \n";
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "Entre 35 et 70 de vie : ";
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << "JAUNE \n";
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "Entre 0 et 35 de vie : ";
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "ROUGE \n";
	}
}

void ClemX::KeyBinds()
{
	if (GetAsyncKeyState(VK_F1) & 1)
	{
		Hacks::RadarActive = !Hacks::RadarActive;
		ClemX::UpdateMenu();
	}
	if (GetAsyncKeyState(VK_F2) & 1)
	{
		Hacks::GlowActive = !Hacks::GlowActive;
		ClemX::UpdateMenu();
	}
	if (GetAsyncKeyState(VK_F3) & 1)
	{
		Hacks::BhopActive = !Hacks::BhopActive;
		ClemX::UpdateMenu();
	}
	if (GetAsyncKeyState(VK_F4) & 1)
	{
		Hacks::TriggerBotActive = !Hacks::TriggerBotActive;
		ClemX::UpdateMenu();
	}
	if (GetAsyncKeyState(VK_F5) & 1)
	{
		Hacks::NoFlashActive = !Hacks::NoFlashActive;
		ClemX::UpdateMenu();
	}
	if (GetAsyncKeyState(VK_F6) & 1)
	{
		Hacks::NoRecoilActive = !Hacks::NoRecoilActive;
		ClemX::UpdateMenu();
	}
	if (GetAsyncKeyState(VK_F7) & 1)
	{
		Hacks::AimBotActive = !Hacks::AimBotActive;
		ClemX::UpdateMenu();
	}
	if (GetAsyncKeyState(VK_F8) & 1)
	{
		Hacks::AimBotConfig = !Hacks::AimBotConfig;
		ClemX::UpdateMenu();
	}
	if (GetAsyncKeyState(VK_F9) & 1)
	{
		Hacks::ChamsActive = !Hacks::ChamsActive;
		ClemX::UpdateMenu();
	}
	if (GetAsyncKeyState(VK_F10) & 1)
	{
		Hacks::NoHandsActive = !Hacks::NoHandsActive;
		ClemX::UpdateMenu();
	}
}