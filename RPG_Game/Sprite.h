#pragma once
#include <d3dx9.h>
#include <vector>

class Frame;

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
	void Update(float deltaTime);
	//Direct X
private:
	IDirect3DTexture9* _texture;
	D3DXIMAGE_INFO _textureInfo;
	LPD3DXSPRITE _sprite;

private:
	// Frame* _frame;
	std::vector<Frame*> _frameList;
	int _currnetFrame;
};