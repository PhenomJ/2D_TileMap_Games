#pragma once
#include "Component.h"
#include <string>

class Sprite;

class PosionItem : public Component
{
public:
	PosionItem(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFilename);
	~PosionItem();

	void Init();
	void Deinit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void MoveDeltaPosition(float deltaX, float deltaY);
	void SetPosition(float posX, float posY);

	void ReceiveMessage(const sComponentMsgParam &msgParam);

private:
	Sprite* _sprite;
	std::wstring _textureFilename;
	std::wstring _scripteFileName;
	float _posX;
	float _posY;
};