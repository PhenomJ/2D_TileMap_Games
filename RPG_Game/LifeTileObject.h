#pragma once
#include "TileObject.h"
#include "Component.h"
#include "list"

class Sprite;

class LifeTileObject : public TileObject
{
public:
	LifeTileObject(LPCWSTR componentName, Sprite* sprite);
	~LifeTileObject();
	void Update(float deltaTime);

public:

};