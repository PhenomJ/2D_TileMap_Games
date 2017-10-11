#include <Windows.h>
#include <D3D9.h>
#include "GameSystem.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow)
{
	GameSystem::GetInstance()->InitSystem(hInstance, nCmdShow);
	
	return GameSystem::GetInstance()->UpdateSystem();
}