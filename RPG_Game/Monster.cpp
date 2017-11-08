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
	

		//Ž�� ���� ����
		{
			// Ž�� ������ �� Ȯ��
			if (component->GetType() == eComponentType::CT_NPC || eComponentType::CT_PLAYER)
			{
				findEnemy = component;
			}
		}

		if (findEnemy != NULL)
		{
			// �߰� ���� ����
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