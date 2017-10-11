#pragma once
#include <d3dx9.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

public:
	void Init(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite);
	void Deinit();
	void Render();
	void Reset(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite);
	void Release();

private:
	IDirect3DTexture9* _texture;
	RECT _srcTextureRect;
	D3DCOLOR _textureColor;
	D3DXIMAGE_INFO _textureInfo;
	LPD3DXSPRITE _sprite;
};