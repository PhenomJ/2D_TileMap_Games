#include "GameGen.h"
#include "Stage.h"

GameGen::GameGen(Stage* stage)
{
	_count = 0;
}

GameGen::~GameGen()
{

}

void GameGen::CreateComponents()
{

}

Component* GameGen::CreateLifeNpc(std::wstring scriptName, std::wstring textureName)
{
	return NULL;
}

void GameGen::SetName(std::wstring name)
{
	WCHAR wname[256];
	wsprintf(wname, L"%s_%d", name, _count);
	_name = wname;
}