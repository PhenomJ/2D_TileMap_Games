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
#include "GameGen.h"
#include "LifeGameGen.h"
#include "DefaultGameGen.h"
#include "Player.h"

Stage::Stage()
{
	_game = NULL;
}

Stage::~Stage()
{
	ComponentSystem::GetInstance()->RemoveAllComponents();

	if (_game != NULL)
	{
		delete _game;
		_game = NULL;
	}
}

void Stage::Init(std::wstring mapName)
{
	_componentList.clear();

	
	_gameGenMap[L"Default"] = new DefaultGameGen(this);
	_gameGenMap[L"3"] = new LifeGameGen(this);
	
	
	GameSet(mapName);
	_game->CreateComponents(mapName);
	AllComponentInit();
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

		LifeNPC* npc = (LifeNPC*)(_game->CreateNpc(L"npc", L"npc"));
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

void Stage::GameSet(std::wstring mapName)
{
	std::map<std::wstring, GameGen*>::iterator itr = _gameGenMap.find(mapName);
	if (itr != _gameGenMap.end())
	{
	_game = itr->second;
	}

	else
	_game = _gameGenMap[L"Default"];
}

void Stage::AllComponentInit()
{
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->Init();
	}
}