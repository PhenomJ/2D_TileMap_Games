#include "GameGen.h"
#include "Stage.h"
#include "Component.h"
#include "Map.h"

GameGen::GameGen(Stage* stage)
{
	_stage = stage;
}

GameGen::~GameGen()
{

}

void GameGen::SetName(std::wstring name)
{
	WCHAR wname[256];
	wsprintf(wname, L"%s_%d", name, _npcCount);
	_name = wname;
}

void GameGen::CreateComponents(std::wstring mapName)
{
	_map = new Map(mapName.c_str());
	_stage->SetMap(_map);
	_stage->AddStageComponent(_map);
};