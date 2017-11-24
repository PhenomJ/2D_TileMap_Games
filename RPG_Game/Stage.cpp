#include "Stage.h"
#include "Component.h"
#include "ComponentSystem.h"
#include "Map.h"
#include "RecoveryItem.h"
#include "PosionItem.h"
#include "Character.h"
#include "NPC.h"
#include "Monster.h"
#include "Player.h"

Stage::Stage()
{

}

Stage::~Stage()
{
	ComponentSystem::GetInstance()->RemoveAllComponents();
}

void Stage::Init(std::wstring mapName)
{
	_componentList.clear();

	_map = new Map(mapName.c_str());
	_componentList.push_back(_map);

	for (int i = 0; i < 10; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"Recovery_%d", i);
		RecoveryItem* item = new RecoveryItem(name, L"Recovery_Item", L"item");
		_componentList.push_back(item);
	}

	for (int i = 0; i < 10; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"Poision_%d", i);
		PosionItem* item = new PosionItem(name, L"Poision_item", L"item");
		_componentList.push_back(item);
	}

	Character* player = new Player(L"player", L"player", L"player");
	_componentList.push_back(player);

	for (int i = 0; i < 10; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"npc_%d", i);
		NPC* npc = new NPC(name, L"npc", L"npc");
		_componentList.push_back(npc);
	}

	for (int i = 0; i < 10; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"monster_%d", i);
		Monster* monster = new Monster(name, L"monster", L"monster");
		_componentList.push_back(monster);
	}

	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->Init();
	}

	_map->InitViewer(player);
}

void Stage::Release()
{
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->Release();
	}
}

void Stage::Update(float deltaTime)
{
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->Update(deltaTime);
	}
}

void Stage::Render()
{
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->Render();
	}
}

void Stage::Reset()
{
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->Reset();
	}
}
