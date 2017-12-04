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
#include "LifePlayer.h"
#include "LifeGameGen.h"
#include "DefaultGameGen.h"
#include "Player.h"

Stage::Stage()
{
	_Game = NULL;
}

Stage::~Stage()
{
	ComponentSystem::GetInstance()->RemoveAllComponents();

	if (_Game != NULL)
	{
		delete _Game;
		_Game = NULL;
	}{}
}

void Stage::Init(std::wstring mapName)
{
	_componentList.clear();

	_map = new Map(mapName.c_str());
	
	_componentList.push_back(_map);

	Player* player = NULL;
	WCHAR name[256];

	if (mapName == L"3")
	{
		//GameGen »ó¼Ó LifeGameGen
		_Game = new LifeGameGen(this);
	}

	else
	{
	
		_Game = new DefaultGameGen(this);
		
	}
	

	_Game->CreateComponents();

	if (Find(mapName) == true)
		_GameGenMap[mapName]->CreateComponents();

	else
		_GameGenMap[L"default"]->CreateComponents();

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
	UpdateCreateComponentList();
	UpdateRemoveComponentList();
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

void Stage::CreateLifeNPC(Component* comp)
{
	comp->GetTileX();
	comp->GetTileY();
	_createBaseComponentList.push_back(comp);
}

void Stage::UpdateCreateComponentList()
{
	for (std::list<Component*>::iterator itr = _createBaseComponentList.begin(); itr != _createBaseComponentList.end(); itr++)
	{
		Component* baseComponent = (*itr);

		LifeNPC* npc = (LifeNPC*)(_Game->CreateLifeNpc(L"npc", L"npc"));
		npc->Init(baseComponent->GetTileX(), baseComponent->GetTileY());
	}

	_createBaseComponentList.clear();
}

void Stage::DestroyLifeNpc(int tileX, int tileY, Component* tileCharacter)
{
	_map->ResetTileComponent(tileX, tileY, tileCharacter);
	_componentList.remove(tileCharacter);
	ComponentSystem::GetInstance()->RemoveComponent(tileCharacter);
}

void Stage::CheckDestoryNPC(Component* tileCharacter)
{
	_removeComponentList.push_back(tileCharacter);
}

void Stage::UpdateRemoveComponentList()
{
	for (std::list<Component*>::iterator itr = _removeComponentList.begin(); itr != _removeComponentList.end(); itr++)
	{
		Component* component = (*itr);
		DestroyLifeNpc(component->GetTileX(), component->GetTileY(), component);
	}
	_removeComponentList.clear();
}

void Stage::AddStageComponent(Component* component)
{
	_componentList.push_back(component);
}

bool Stage::Find(std::wstring mapName)
{

	return true;
}