#include "LifeTileObject.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "Map.h"
#include "Stage.h"

LifeTileObject::LifeTileObject(LPCWSTR componentName, Sprite* sprite) : TileObject(componentName, sprite)
{

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
	
	int minX = this->GetTileX() - range;
	int maxX = this->GetTileX() + range;
	int minY = this->GetTileY() - range;
	int maxY = this->GetTileY() + range;

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

							}
						}
					}
				}
			}
		}
	}
}