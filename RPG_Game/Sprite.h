#pragma once
#include <d3dx9.h>
#include <vector>

class Texture;
class Frame;

class Sprite
{
public:
	Sprite(LPCWSTR texturefileName, LPCWSTR scriptfileName, float rotate = 0.0f);
	~Sprite();

public:
	void Init();
	void Init(int srcX, int srcY, int x, int y, float frameDelay, D3DCOLOR color);
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
	std::vector<Frame*> _frameList;
	int _currnetFrame;
	float _frameTime;
	Texture* _srcTexture;

	LPCWSTR _texturefileName;
	LPCWSTR _scriptfileName;

	float _x;
	float _y;
	float _rotate;

	//Change Color
public:
	void ChangeColor(D3DCOLOR color);
	float GetPositionX() { return _x; }
	float GetPositionY() { return _y; }
};