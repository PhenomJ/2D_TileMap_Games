#pragma once
#include "Component.h"
#include <vector>

class Sprite;

class TileObject : public Component
{
public:
	TileObject(LPCWSTR componentName, Sprite* sprite);
	~TileObject();

	void Init();
	void Deinit();
	void Update(float deltaTime);
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