#include "NPC.h"
#include "Map.h"
#include "ComponentSystem.h"
#include <list>

NPC::NPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName,spriteName)
{
	_type = eComponentType::CT_NPC;
	int speed = (rand() % 1500) + 400;
	_moveSpeed = (float)speed / 1000.0f;
}

NPC::~NPC()
{

}

void NPC::UpdateAI(float deltaTime)
{
	if (_isMoving == false)
	{
		// 타일 범위
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");

		int range = 1; // 시야같은거
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

		Component* findEnemy = NULL;

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
						if (component->GetType() == eComponentType::CT_MONSTER)
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
			for (int findDir = 0; findDir < 4; findDir++)
			{
				int newtileX = _tileX;
				int newtileY = _tileY;

				switch (findDir)
				{
				case eDirection::LEFT:
					newtileX--;
					break;
				case eDirection::RIGHT:
					newtileX++;
					break;

				case eDirection::DOWN:
					newtileY++;
					break;
				case eDirection::UP:
					newtileY--;
					break;

				default:
					break;
				}

				if (map->CanMoveTileMap(newtileX, newtileY))
				{
					_moveSpeed = 0.3f;
					direction = (eDirection)findDir;
					MoveStart(direction);
					break;
				}
			}
		}

		else
		{
			Character::UpdateAI(deltaTime);
		}
		//
	}
}