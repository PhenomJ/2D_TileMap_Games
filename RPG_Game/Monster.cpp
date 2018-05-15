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
	_movePoint = 10;
}

Monster::~Monster()
{

}

void Monster::UpdateAI(float deltaTime)
{
	if (TurnManager::GetInstance()->IsPlayerTurn() == false)
	{
		Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
		std::vector<eComponentType> typeList;
		typeList.push_back(eComponentType::CT_PLAYER);
		Component* findEnemy = ComponentSystem::GetInstance()->FindComponentInAllMap(map, this, typeList);

		if (findEnemy != NULL)
		{
			TileCell* targetCell = GameSystem::GetInstance()->GetStage()->GetMap()->GetTileCell(findEnemy->GetTileX(), findEnemy->GetTileY());
			// ±Ê√£±‚

			std::list<TileCell*> tileCellRange = ComponentSystem::GetInstance()->FindTileCellInRange(map, this, _movePoint, typeList);
			std::list<TileCell*>::iterator itr = tileCellRange.begin();
			for (itr ; itr != tileCellRange.end(); itr++)
			{
				if ((*itr)->GetTileX() == targetCell->GetTileX() && (*itr)->GetTileY() == targetCell->GetTileY())
				{
					Attack(targetCell);
					targetCell = NULL;
					return;
				}
			}

			if (targetCell != NULL)
				SetTargetCell(MinDistanceTileCell(targetCell, tileCellRange));
		}
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

TileCell* Monster::MinDistanceTileCell(TileCell* targetCell, std::list<TileCell*> tileCellList)
{
	TileCell* minDistanceTileCell = NULL;
	float minDistance = -1;

	for (std::list<TileCell*>::iterator itr = tileCellList.begin(); itr != tileCellList.end(); itr++)
	{
		float distanceX = (*itr)->GetTileX() - targetCell->GetTileX();
		float distanceY = (*itr)->GetTileY() - targetCell->GetTileY();

		float distance = distanceX * distanceX + distanceY * distanceY;

		if (minDistance == -1)
		{
			minDistance = distance;
		}

		else if (minDistance > distance && ((*itr)->CanMove() == true))
		{
			minDistance = distance;
			minDistanceTileCell = (*itr);
		}
	}

	return minDistanceTileCell;
}