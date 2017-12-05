#include "LifeGameGen.h"
#include "LifeNPC.h"
#include "LifePlayer.h"
#include "Stage.h"
#include "Map.h"

LifeGameGen::LifeGameGen(Stage* stage) : GameGen(stage)
{
	_npcCount = 0;
	_lifeNpcCount = 100;
}

LifeGameGen::~LifeGameGen()
{

}

Component* LifeGameGen::CreateNpc(std::wstring scriptName, std::wstring textureName)
{
	SetName(L"lifeNpc_");
	_npcCount++;
	Component* component  = new LifeNPC(_name.c_str(), scriptName.c_str(), textureName.c_str());
	_stage->AddStageComponent(component);
	
	return component;
}

void LifeGameGen::CreateComponents(std::wstring mapName)
{
	GameGen::CreateComponents(mapName);

	for (int i = 0; i < _lifeNpcCount; i++)
	{
		Component* component = CreateNpc(L"npc", L"npc");
	}
	LifePlayer* player = new LifePlayer(L"player", L"player", L"player");

	_stage->AddStageComponent(player);
	_map->InitViewer(player);
}