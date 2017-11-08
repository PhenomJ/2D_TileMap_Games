#include "Monster.h"

Monster::Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName ,spriteName)
{
	
}

Monster::~Monster()
{

}

void Monster::UpdateAI(float deltaTime)
{
	if (_isMoving == false)
	{
		Component* findEnemy = NULL;
	

		//탐색 범위 지정
		{
			// 탐색 범위에 적 확인
			if (component->GetType() == eComponentType::CT_NPC || eComponentType::CT_PLAYER)
			{
				findEnemy = component;
			}
		}

		if (findEnemy != NULL)
		{
			// 추격 방향 설정
			eDirection direction = eDirection::NONE;
			MoveStart(direction);
		}

		else
		{
			Character::UpdateAI(deltaTime);
		}
		//
	}
}