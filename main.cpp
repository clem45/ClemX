#include "Includes.h"

int main()
{
	Hacks::Initialize();
	SetConsoleTitle("ClemExternal V3 Complete Recode");
	ClemX::UpdateMenu();
	while (true)
	{
		ClemX::KeyBinds();
		Hacks::HacksThread();
	}
}