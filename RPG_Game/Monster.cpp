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
	if (_isLive == false)
		return;

	if (_isMoving == false)
	{
		std::vector<eComponentType> typeList;
		typeList.push_back(eComponentType::CT_NPC);
		typeList.push_back(eComponentType::CT_PLAYER);
		Component* findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(this, 4, typeList);


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