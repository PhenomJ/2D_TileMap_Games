#include "ComponentSystem.h"
#include "GameSystem.h"
#include "Component.h"
#include "Map.h"
#include "TileCell.h"

ComponentSystem* ComponentSystem::_instance = NULL;

ComponentSystem::ComponentSystem()
{
	_componentMap.clear();
}

ComponentSystem::~ComponentSystem()
{

}

ComponentSystem* ComponentSystem::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new ComponentSystem();
	}
	return _instance;
}

void ComponentSystem::AddComponent(std::wstring name, Component* thisComponent)
{
	if (thisComponent != NULL)
	{
		std::map<std::wstring, Component*>::iterator itr = _componentMap.find(name);
	
		if (itr == _componentMap.end())
		{
			_componentMap[name] = thisComponent;
		}
	}
}

void ComponentSystem::RemoveAllComponents()
{
	for (std::map<std::wstring, Component*>::iterator itr = _componentMap.begin(); itr != _componentMap.end(); itr++)
	{
		delete itr->second;
	}
	_componentMap.clear();
}

Component* ComponentSystem::FindComponent(std::wstring name)
{
	std::map<std::wstring, Component*>::iterator itr = _componentMap.find(name);
	if (itr != _componentMap.end())
	{
		return itr->second;
	}

	return 0;
}

std::list<TileCell*> ComponentSystem::FindTileCellInRange(Component* mapComp ,Component* thisComponent, int range, std::vector<eComponentType> typeList)
{
	// 타일 범위
	Map* map = (Map*)mapComp;
	std::list<TileCell*> tileCellRange;
	int minX = thisComponent->GetTileX() - range;
	int maxX = thisComponent->GetTileX() + range;
	int minY = thisComponent->GetTileY() - range;
	int maxY = thisComponent->GetTileY() + range;

	if (minX < 0)
		minX = 0;
	if (maxX >= map->GetWidth())
		maxX = map->GetWidth() - 1;
	if (minY < 0)
		minY = 0;
	if (maxY >= map->GetHeight())
		maxY = map->GetHeight() - 1;
	
	for (int y = minY; y <= maxY; y++)
	{
		for (int x = minX; x <= maxX; x++)
		{
			tileCellRange.push_back(map->GetTileCell(x, y));
		}
	}
	return tileCellRange;
}

Component* ComponentSystem::FindComponentInAllMap(Component* mapComp, Component* thisComponent, std::vector<eComponentType> typeList)
{
	// 타일 범위
	Map* map = (Map*)mapComp;

	int minX = 0;
	int maxX = map->GetWidth();
	int minY = 0;
	int maxY = map->GetHeight();

	if (minX < 0)
		minX = 0;
	if (maxX >= map->GetWidth())
		maxX = map->GetWidth() - 1;
	if (minY < 0)
		minY = 0;
	if (maxY >= map->GetHeight())
		maxY = map->GetHeight() - 1;

	for (int y = minY; y <= maxY; y++)
	{
		for (int x = minX; x <= maxX; x++)
		{
			std::list<Component*> componentList;
			if (map->GetTileCollisionList(x, y, componentList) == false)
			{
				for (std::list<Component*>::iterator itr = componentList.begin(); itr != componentList.end(); itr++)
				{
					Component* component = (*itr);
					if (component->IsLive() == true)
					{
						for (int i = 0; i < typeList.size(); i++)
						{
							if (typeList[i] == component->GetType())
							{
								return component;
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}

void ComponentSystem::SendMsg(const sComponentMsgParam &msgParam)
{
	_msgQueue.push(msgParam);
}

void ComponentSystem::ProcessMessageQueue()
{
	while (_msgQueue.size() > 0)
	{
		sComponentMsgParam msgParam = _msgQueue.front();
		_msgQueue.pop();
		msgParam.receiver->ReceiveMessage(msgParam);
	}
}

void ComponentSystem::ClearMessageQueue()
{
	while (0 < _msgQueue.size())
	{
		_msgQueue.pop();
	}
}

void ComponentSystem::Update(float deltaTime)
{
	ProcessMessageQueue();
}

void ComponentSystem::RemoveComponent(Component* tileObject)
{
	_componentMap.erase(tileObject->GetName());
	delete tileObject;
}