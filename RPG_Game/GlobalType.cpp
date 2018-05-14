#include "GlobalType.h"
#include "Map.h"
#include "GameSystem.h"
#include "Stage.h"

TilePosition GetNextTilePosition(TilePosition currentTilePos, eDirection direction)
{
	TilePosition tilePosition = currentTilePos;
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();

	switch (direction)
	{
	case eDirection::LEFT:
		tilePosition.x--;
		break;
	case eDirection::RIGHT:
		tilePosition.x++;
		break;
	case eDirection::UP:
		tilePosition.y--;
		break;
	case eDirection::DOWN:
		tilePosition.y++;
		break;
	}

	if (tilePosition.x < 0)
		tilePosition.x = 0;

	if (tilePosition.y < 0)
		tilePosition.y = 0;

	if (tilePosition.x >= map->GetWidth())
		tilePosition.x = map->GetWidth() -1;

	if (tilePosition.y >= map->GetHeight())
		tilePosition.y = map->GetHeight() -1;

	return tilePosition;
}

eDirection GetDirection(TilePosition to, TilePosition from)
{
	eDirection direction = eDirection::NONE;

	if (to.x < from.x)
		direction = eDirection::LEFT;
	else if (to.x > from.x)
		direction = eDirection::RIGHT;
	else if (to.y < from.y)
		direction = eDirection::UP;
	else if (to.y > from.y)
		direction = eDirection::DOWN;
	else
		direction = eDirection::NONE;

	return direction;
}