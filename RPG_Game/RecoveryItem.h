#pragma once
#include "Component.h"
#include <string>

class Sprite;

class RecoveryItem : public Component
{
public:
	RecoveryItem(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFilename);
	~RecoveryItem();

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
	std::wstring _textureFilename;
	std::wstring _scripteFileName;
	float _posX;
	float _posY;
};