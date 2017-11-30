#include "LifeTileObject.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "Map.h"
#include "Stage.h"

LifeTileObject::LifeTileObject(int tileX, int tileY, LPCWSTR componentName, Sprite* sprite) : TileObject(componentName, sprite)
{
	_tileX = tileX;
	_tileY = tileY;
}

LifeTileObject::~LifeTileObject()
{

}

void LifeTileObject::Update(float deltaTime)
{
	TileObject::Update(deltaTime);
	// FindComponentInRange를 통하여 캐릭터의 마리수를 가져 올것.
	// 주변 8칸 탐색 * 캐릭터가 몇?

	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	std::vector<eComponentType> typeList;
	typeList.push_back(eComponentType::CT_NPC);
	int range = 1;
	int count = 0;
	Component* tileCharacter = false;

	int minX = _tileX - range;
	int maxX = _tileX + range;
	int minY = _tileY - range;
	int maxY = _tileY + range;

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
			if (x != _tileX || y != _tileY)
			{
				std::list<Component*> componentList;
				if (map->GetTileCollisionList(x, y, componentList) == false)
				{
					for (std::list<Component*>::iterator itr = componentList.begin(); itr != componentList.end(); itr++)
					{
						Component* component = (*itr);
						switch (component->GetType())
						{
						case eComponentType::CT_NPC:
						case eComponentType::CT_PLAYER:
							count++;
							break;
						}
					}
				}
			}

			else
			{
				std::list<Component*> componentList;
				if (map->GetTileCollisionList(x, y, componentList) == false)
				{
					for (std::list<Component*>::iterator itr = componentList.begin(); itr != componentList.end(); itr++)
					{
						Component* component = (*itr);
						switch (component->GetType())
						{
						case eComponentType::CT_NPC:
						case eComponentType::CT_PLAYER:
							tileCharacter = component;
							break;
						}
					}
				}
			}
		}
	}

	if (count == 3)
	{
		if (tileCharacter == NULL)
		{
			//GameSystem::GetInstance()->GetStage()->CreateLifeNPC(_tileX, _tileY);
			GameSystem::GetInstance()->GetStage()->CreateLifeNPC(this);
		}
	}

	else if (count == 2)
	{

	}

	else
	{
		if (tileCharacter != NULL)
		{
			if (eComponentType::CT_PLAYER != tileCharacter->GetType())
			{
				GameSystem::GetInstance()->GetStage()->CheckDestoryNPC(tileCharacter);
				//GameSystem::GetInstance()->GetStage()->DestroyLifeNpc(_tileX, _tileY, tileCharacter);
				tileCharacter = NULL;
			}
		}
	}
}