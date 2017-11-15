#include "Monster.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "MoveState.h"

Monster::Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName ,spriteName)
{
	int speed = (rand() % 1500) + 200;
	_moveSpeed = (float)speed / 1000.0f;
	_type = eComponentType::CT_MONSTER;
}

Monster::~Monster()
{

}

void Monster::UpdateAI(float deltaTime)
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

			if (eDirection::NONE != direction)
			{
				_currentDirection = direction;
				ChangeState(eStateType::ET_MOVE);
			}
		}

		else
		{
			Character::UpdateAI(deltaTime);
		}
}

void Monster::Collision(std::list<Component*> &collisionList)
{
	for (std::list<Component*>::iterator itr = collisionList.begin(); itr != collisionList.end(); itr++)
	{
		Component* component = (*itr);

		if (component->GetType() == eComponentType::CT_NPC || component->GetType() == eComponentType::CT_PLAYER)
		{
			sComponentMsgParam msgParam;
			msgParam.sender = this;
			msgParam.receiver = (*itr);
			msgParam.message = L"Attack";
			msgParam.attackPoint = _attackPoint;
			ComponentSystem::GetInstance()->SendMsg(msgParam);
		}
	}
}