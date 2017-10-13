#include "Frame.h"
#include "GameSystem.h"
#include "Texture.h"

Frame::Frame() : _frameDelay(0.0f)
{

}

Frame::~Frame()
{

}

void Frame::Init(Texture* texture, int x, int y, int width, int height, float frameDelay)
{
	_sprite = GameSystem::GetInstance()->GetSprite();
	_texture = texture;
	_width = width;
	_height = height;

	_srcTextureRect.left = x;
	_srcTextureRect.top = y;
	_srcTextureRect.right = x + _width;
	_srcTextureRect.bottom = y + _height;
	_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	
	_frameDelay = frameDelay;
}

void Frame::Deinit()
{

}

void Frame::Render()
{
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)_width / 2.0f, (float)_height / 2.0f);
	D3DXVECTOR2 translate = D3DXVECTOR2((float)GameSystem::GetInstance()->GetClientWidth() / 2.0f - _width / 2.0f, (float)GameSystem::GetInstance()->GetClientHeight() / 2.0f - _height / 2.0f);
	D3DXVECTOR2 scaling = D3DXVECTOR2(1.0f, 1.0f);

	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,
		NULL,
		0.0f,
		&scaling,
		&spriteCenter,
		0.0f,
		&translate
	);

	_sprite->SetTransform(&matrix);
	_sprite->Draw(_texture->GetTextureDX(), &_srcTextureRect, NULL, NULL, _textureColor);
}

void Frame::Release()
{

}

void Frame::Reset()
{

}

float Frame::GetFrameDelay()
{
	return _frameDelay;
}