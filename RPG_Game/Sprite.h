#pragma once
#include <d3dx9.h>
#include <vector>

class Texture;
class Frame;

class Sprite
{
public:
	Sprite(LPCWSTR texturefileName, LPCWSTR scriptfileName);
	~Sprite();

public:
	void Init();
	void Deinit();
	
	void Render();
	void Reset();
	void Release();

	void Update(float deltaTime);
	void SetPosition(float posX, float posY);
	//Direct X
private:
	LPD3DXSPRITE _sprite;
	LPDIRECT3DDEVICE9 _device3d;
private:
	// Frame* _frame;
	std::vector<Frame*> _frameList;
	int _currnetFrame;
	float _frameTime;
	Texture* _srcTexture;

	LPCWSTR _texturefileName;
	LPCWSTR _scriptfileName;

	float _x;
	float _y;
};