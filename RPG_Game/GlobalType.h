#pragma once

typedef struct TilePosition
{
	int x;
	int y;
};

enum eDirection
{
	UP, DOWN, LEFT, RIGHT, NONE
};

enum ePathFindingType
{
	DISTANCE,
	SIMPLE,
	COMPLEX,
	ASTAR,
};

TilePosition GetNextTilePosition(TilePosition currentTilePos, eDirection direction);
eDirection GetDirection(TilePosition to, TilePosition from);