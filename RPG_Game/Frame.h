#pragma once
#include <d3dx9.h>

class Texture;

class Frame
{
public:
	Frame();
	~Frame();

public:
	void Init(Texture* _texture, int x, int y, int width, int height, float frameDelay);
	void Deinit();
	void Render();
	void Release();
	void Reset();
	float GetFrameDelay();

private:
	Texture* _texture;
	RECT _srcTextureRect;
	D3DCOLOR _textureColor;
	LPD3DXSPRITE _sprite;

	int _width;
	int _height;

	float _frameDelay;
};