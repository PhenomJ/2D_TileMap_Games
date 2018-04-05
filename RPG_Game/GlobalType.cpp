#include "GlobalType.h"

TilePosition GetNextTilePosition(TilePosition currentTilePos, eDirection direction)
{
	TilePosition tilePosition = currentTilePos;

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