#pragma once
#include <d3dx9.h>

class Frame
{
public:
	Frame();
	~Frame();

public:
	void Init(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite, IDirect3DTexture9* _texture, int x, int y, int width, int height);
	void Deinit();
	void Render();
	void Release();
	void Reset(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite);

private:
	IDirect3DTexture9* _texture;
	RECT _srcTextureRect;
	D3DCOLOR _textureColor;
	LPD3DXSPRITE _sprite;

	int _width;
	int _height;
};