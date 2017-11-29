#pragma once
#include "TileObject.h"
#include "Component.h"
#include "list"

class Sprite;

class LifeTileObject : public TileObject
{
public:
	LifeTileObject(int tileX, int tileY, LPCWSTR componentName, Sprite* sprite);
	~LifeTileObject();
	void Update(float deltaTime);

private:
	int _tileX;
	int _tileY;
};