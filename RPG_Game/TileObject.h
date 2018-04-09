#pragma once
#include "Component.h"
#include <d3d9types.h>
#include <vector>


class Sprite;

class TileObject : public Component
{
public:
	TileObject(Sprite* sprite, int tileX, int tileY);
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

	// 가중치

private:
	float _weight = 1.0f;

public:
	void SetDistanceWeight(float weight) { _weight = weight; }
	float GetDistanceWeight() { return _weight; }

	//색 변경
public:
	void ChangeColor(D3DCOLOR color);

private:
	D3DCOLOR _color;
};