#include "Stage.h"
#include "Component.h"
#include "ComponentSystem.h"
#include "GameSystem.h"
#include "Map.h"
#include "RecoveryItem.h"
#include "PosionItem.h"
#include "Character.h"
#include "NPC.h"
#include "Monster.h"
#include "GameGen.h"
#include "DefaultGameGen.h"
#include "FindingPathGen.h"
#include "Player.h"
#include "TileCell.h"

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
	
	_gameMapGen[L"Default"] = new DefaultGameGen(this);
	_gameMapGen[L"4"] = new FindingPathGen(this);
	
	GameSet(mapName);
	_game->CreateComponents(mapName);
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

void Stage::UpdateCreateComponentList()
{
	for (std::list<Component*>::iterator itr = _createBaseComponentList.begin(); itr != _createBaseComponentList.end(); itr++)
	{
		Component* baseComponent = (*itr);

		NPC* npc = (NPC*)(_game->CreateNpc(L"npc", L"npc"));
		npc->InitTilePosition(baseComponent->GetTileX(), baseComponent->GetTileY());
	}

	_createBaseComponentList.clear();
}

void Stage::UpdateRemoveComponentList()
{
	for (std::list<Component*>::iterator itr = _removeComponentList.begin(); itr != _removeComponentList.end(); itr++)
	{
		Component* component = (*itr);
	}
	_removeComponentList.clear();
}

void Stage::AddStageComponent(Component* component)
{
	component->Init();
	_componentList.push_back(component);
}

void Stage::GameSet(std::wstring mapName)
{
	std::map<std::wstring, GameGen*>::iterator itr = _gameMapGen.find(mapName);
	if (itr != _gameMapGen.end())
	{
		_game = itr->second;
	}

	else
	_game = _gameMapGen[L"Default"];
}

void Stage::AllComponentInit()
{
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->Init();
	}
}

void Stage::CreateMark(TileCell* tileCell)
{
	Character* mark = (Character*)(_game->CreateNpc(L"monster", L"monster"));
	mark->InitTilePosition(tileCell->GetTileX(), tileCell->GetTileY());
	mark->SetCanMove(true);

	if (!tileCell->CanMove())
		tileCell->ChangeAttackable();

	tileCell->ChangeClickable();
	_componentList.remove(mark);
	tileCell->AddComponent(mark, true);
}