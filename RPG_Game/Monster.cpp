#include "Monster.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "GameSystem.h"
#include "Stage.h"
#include "MoveState.h"
#include "TileCell.h"

Monster::Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName ,spriteName)
{
	int speed = (rand() % 1500) + 200;
	_moveSpeed = (float)speed / 1000.0f;
	_type = eComponentType::CT_MONSTER;
	_hp = 10;
	_attackPoint = 5;
}

Monster::~Monster()
{

}

void Monster::UpdateAI(float deltaTime)
{
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	std::vector<eComponentType> typeList;
	typeList.push_back(eComponentType::CT_NPC);
	typeList.push_back(eComponentType::CT_PLAYER);
	Component* findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(map,this, 4, typeList);
	
	if (findEnemy != NULL)
	{
		// ±æÃ£±â
		TileCell* targetCell = GameSystem::GetInstance()->GetStage()->GetMap()->GetTileCell(findEnemy->GetTileX(), findEnemy->GetTileY());
		SetTargetCell(targetCell);
	}

	else
	{
		Character::UpdateAI(deltaTime);
	}
	
}

Component* Monster::Collision(std::list<Component*> &collisionList)
{
	for (std::list<Component*>::iterator itr = collisionList.begin(); itr != collisionList.end(); itr++)
	{
		Component* component = (*itr);

		if (component->GetType() == eComponentType::CT_NPC || component->GetType() == eComponentType::CT_PLAYER)
		{
			return (*itr);
		}
	}
	return NULL;
}