#pragma once
#include "Component.h"
#include <vector>

class Sprite;

class TileObject : public Component
{
public:
	TileObject(LPCWSTR componentName, Sprite* sprite);
	virtual ~TileObject();

	void Init();
	void Deinit();
	virtual void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void MoveDeltaPosition(float deltaX, float deltaY);
	void SetPosition(float posX, float posY);

private:
	Sprite* _sprite;

	float _posX;
	float _posY;
};