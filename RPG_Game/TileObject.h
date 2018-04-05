#pragma once
#include "Component.h"
#include <vector>

class Sprite;

class TileObject : public Component
{
public:
	TileObject(LPCWSTR componentName, Sprite* sprite, int tileX, int tileY);
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

	// °¡ÁßÄ¡

private:
	float _weight = 1.0f;

public:
	void SetDistanceWeight(float weight) { _weight = weight; }
	float GetDistanceWeight() { return _weight; }
};