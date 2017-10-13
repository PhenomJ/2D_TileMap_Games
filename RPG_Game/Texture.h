#pragma once
#include <d3dx9.h>

class Texture
{
public:
	Texture();
	~Texture();

public:
	void Init(LPCWSTR fileName);
	void Deinit();
	void Release();
	IDirect3DTexture9* GetTextureDX();

private:
	IDirect3DTexture9* _texture;
	D3DXIMAGE_INFO _textureInfo;
};