#include "Frame.h"
#include "GameSystem.h"
#include "Texture.h"

Frame::Frame() : _frameDelay(0.0f)
{

}

Frame::~Frame()
{

}

void Frame::Init(Texture* texture, int x, int y, int width, int height, float rotate,float frameDelay, D3DCOLOR textureColor)
{
	_sprite = GameSystem::GetInstance()->GetSprite();
	_texture = texture;

	_width = width;
	_height = height;
	_rotate = rotate;
	_srcTextureRect.left = x;
	_srcTextureRect.top = y;
	_srcTextureRect.right = x + _width;
	_srcTextureRect.bottom = y + _height;
	_textureColor = textureColor;
	
	_frameDelay = frameDelay;
}

void Frame::Deinit()
{
	_texture = NULL;
}

void Frame::Render()
{
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)_width / 2.0f, (float)_height / 2.0f);
	_translate = D3DXVECTOR2(_x - _width / 2.0f, _y - _height / 2.0f);
	D3DXVECTOR2 scaling = D3DXVECTOR2(1.0f, 1.0f);
	
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,
		NULL,
		0.0f,
		&scaling,
		&spriteCenter,
		_rotate, // 회전각도
		&_translate
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

void Frame::SetPosition(float x, float y)
{
	_x = x;
	_y = y;
}

void Frame::ChangeColor(D3DCOLOR color)
{
	_textureColor = color;
}