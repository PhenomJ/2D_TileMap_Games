#include "DefaultGameGen.h"
#include "Player.h"
#include "Stage.h"
#include "Map.h"
#include "RecoveryItem.h"
#include "PosionItem.h"
#include "Monster.h"
#include "NPC.h"

DefaultGameGen::DefaultGameGen(Stage* stage) : GameGen(stage)
{

}

DefaultGameGen::~DefaultGameGen()
{

}

void DefaultGameGen::CreateComponents(std::wstring mapName)
{
	GameGen::CreateComponents(mapName);

	for (int i = 0; i < 10; i++)
	{
		SetName(L"Recovery_Item_");
		RecoveryItem* item = new RecoveryItem(_name.c_str(), L"Recovery_Item", L"item");
		_stage->AddStageComponent(item);
	}

	for (int i = 0; i < 10; i++)
	{
		SetName(L"Posion_Item_");
		PosionItem* item = new PosionItem(_name.c_str(), L"Posion_item", L"item");
		_stage->AddStageComponent(item);
	}

	for (int i = 0; i < 10; i++)
	{
		SetName(L"npc_");
		NPC* npc = new NPC(_name.c_str(), L"npc", L"npc");
		_stage->AddStageComponent(npc);
	}

	for (int i = 0; i < 10; i++)
	{
		SetName(L"monster_");
		Monster* monster = new Monster(_name.c_str(), L"monster", L"monster");
		_stage->AddStageComponent(monster);
	}

	Player* player = new Player(L"player", L"player", L"player");

	_stage->AddStageComponent(player);
	_map->InitViewer(player);
}