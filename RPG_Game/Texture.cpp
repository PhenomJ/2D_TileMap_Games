#include "Texture.h"
#include "GameSystem.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

void Texture::Init(LPCWSTR fileName)
{
	HRESULT hr = D3DXGetImageInfoFromFile(fileName, &_textureInfo);

	hr = D3DXCreateTextureFromFileEx
	(
		GameSystem::GetInstance()->GetDevice3d(),
		fileName,
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
}

void Texture::Deinit()
{
	if (_texture != NULL)
	{
		delete _texture;
		_texture->Release();
		_texture = NULL;
	}
}

void Texture::Release()
{
	RELEASE_COM(_texture);
}

IDirect3DTexture9* Texture::GetTextureDX()
{
	return _texture;
}