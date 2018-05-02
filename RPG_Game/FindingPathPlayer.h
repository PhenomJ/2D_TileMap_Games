#pragma once
#include "Player.h"

class FindingPathPlayer : public Player
{
public:
	FindingPathPlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName);
	~FindingPathPlayer();

	//AI
public:
	void UpdateAI(float deltaTime);

	//State
public:
	void InitState();

private:
	int beforeMouseX;
	int beforeMouseY;

	//Test
private:
	TileCell* _tileCell;

public:
	TileCell* GetTileCell();

	void CallMovableRange(TileCell* targetTileCell, int movableCount);
};