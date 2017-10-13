#pragma once
#include <d3dx9.h>

class Texture;

class ResourceManager
{
private:
	static ResourceManager* _Instace;
	ResourceManager();

public:
	~ResourceManager();
	static ResourceManager* GetInstance();
	Texture* LoadTexture(LPCWSTR fileName);

private:
	Texture* _texture;
};