#include "Sprite.h"
#include "GameSystem.h"
#include "Frame.h"

Sprite::Sprite() : _currnetFrame(0)
{

}

Sprite::~Sprite()
{

}

void Sprite::Init(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite)
{	
	_sprite = sprite;
	HRESULT hr = D3DXGetImageInfoFromFile(L"character_sprite.png", &_textureInfo);
	hr = D3DXCreateTextureFromFileEx
	(
		device3d,
		L"character_sprite.png",
		_textureInfo.Width,
		_textureInfo.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		&_textureInfo,
		NULL,
		&_texture
	);

	{
		Frame* frame = new Frame();
		frame->Init(device3d, sprite, _texture, 32*0, 0, 32, 32);
		_frameList.push_back(frame);
		
	}

	{
		Frame* frame = new Frame();
		frame->Init(device3d, sprite, _texture, 32*1, 0, 32, 32);
		_frameList.push_back(frame);
	}

	{
		Frame* frame = new Frame();
		frame->Init(device3d, sprite, _texture, 32*2, 0, 32, 32);
		_frameList.push_back(frame);
	}
	_currnetFrame = 2;
}

void Sprite::Deinit()
{
	RELEASE_COM(_texture);
	
	std::vector<Frame*>::iterator itr = _frameList.begin();
	for (itr = _frameList.begin(); itr != _frameList.end(); itr++)
	{
		Frame* frame = (*itr);
		frame->Deinit();
		delete frame;
	}
	_frameList.clear();
}

void Sprite::Render()
{
	if (_currnetFrame < _frameList.size())
	_frameList[_currnetFrame]->Render();
}

void Sprite::Reset(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite)
{
	Init(device3d, sprite);
	std::vector<Frame*>::iterator itr = _frameList.begin();
	for (itr = _frameList.begin(); itr != _frameList.end(); itr++)
	{
		Frame* frame = (*itr);
		frame->Reset(device3d, sprite);
	}

}

void Sprite::Release()
{
	std::vector<Frame*>::iterator itr = _frameList.begin();
	for (itr = _frameList.begin(); itr != _frameList.end(); itr++)
	{
		Frame* frame = (*itr);
		frame->Release();
	}
	RELEASE_COM(_texture);
}

void Sprite::Update(float deltaTime)
{

}