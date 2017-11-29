#include "Stage.h"
#include "Component.h"
#include "ComponentSystem.h"
#include "Map.h"
#include "RecoveryItem.h"
#include "PosionItem.h"
#include "Character.h"
#include "NPC.h"
#include "LifeNPC.h"
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

	if (mapName != L"3")
	{
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
	}

	else if (mapName == L"3")
	{
		_lifeNpcCount = 0;
		for (int i = 0; i < 100; i++)
		{
			WCHAR name[256];
			wsprintf(name, L"lifenpc_%d", _lifeNpcCount);
			_lifeNpcCount++;

			LifeNPC* npc = new LifeNPC(name, L"npc", L"npc");
			_componentList.push_back(npc);
		}
	}

	Character* player = new Player(L"player", L"player", L"player");
	_componentList.push_back(player);

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

void Stage::CreateLifeNPC(int tileX, int tileY)
{
	WCHAR name[256];
	wsprintf(name, L"npc_%d", _lifeNpcCount);
	_lifeNpcCount++;
	LifeNPC* npc = new LifeNPC(name, L"npc", L"npc");
	npc->Init(tileX, tileY);
	_componentList.push_back(npc);
}

void Stage::DestroyLifeNpc(int tileX, int tileY, Component* tileCharacter)
{
	_map->ResetTileComponent(tileX, tileY, tileCharacter);
	tileCharacter->SetCanMove(true);
	tileCharacter->SetLive(false);

	_componentList.remove(tileCharacter);
	ComponentSystem::GetInstance()->RemoveComponent(tileCharacter);
}