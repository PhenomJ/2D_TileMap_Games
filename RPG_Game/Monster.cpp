#include "Monster.h"
#include "Map.h"
#include "ComponentSystem.h"

Monster::Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName ,spriteName)
{
	int speed = (rand() % 1500) + 200;
	_moveSpeed = (float)speed / 1000.0f;
}

Monster::~Monster()
{

}

void Monster::UpdateAI(float deltaTime)
{
	if (_isMoving == false)
	{
		Component* findEnemy = NULL;
		
		// 타일 범위
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");

		int range = 10; // 시야같은거
		int minX = _tileX - range;
		int maxX = _tileX + range;
		int minY = _tileY - range;
		int maxY = _tileY + range;

		if (minX < 0)
			minX = 0;
		if (maxX >= map->GetWidth())
			maxX = map->GetWidth() -1;
		if (minY < 0)
			minY = 0;
		if (maxY >= map->GetHeight())
			maxY = map->GetHeight() -1;
	
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
						if (component->GetType() == eComponentType::CT_NPC || component->GetType() == eComponentType::CT_PLAYER)
						{
							findEnemy = component;
							break;
						}
					}
				}
			}
		}

		// 탐색 범위에 적 확인

		
		if (findEnemy != NULL)
		{
			// 추격 방향 설정
			eDirection direction = eDirection::NONE;

			if (findEnemy->GetTileX() < _tileX)
			{
				direction = eDirection::LEFT;
			}

			else if (findEnemy->GetTileX() > _tileX)
			{
				direction = eDirection::RIGHT;
			}

			else if (findEnemy->GetTileY() < _tileY)
			{
				direction = eDirection::UP;
			}

			else if (findEnemy->GetTileY() > _tileY)
			{
				direction = eDirection::DOWN;
			}
			MoveStart(direction);
		}

		else
		{
			Character::UpdateAI(deltaTime);
		}
		//
	}
}