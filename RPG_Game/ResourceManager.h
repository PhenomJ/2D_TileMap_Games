#pragma once
#include <d3dx9.h>
#include <map>
#include "Texture.h"



class ResourceManager
{
private:
	static ResourceManager* _Instance;
	ResourceManager();

public:
	~ResourceManager();
	static ResourceManager* GetInstance();
	

	Texture* LoadTexture(LPCWSTR fileName);

private:
	Texture* _texture;
	std::map<LPCWSTR, Texture*> _textureMap;

};