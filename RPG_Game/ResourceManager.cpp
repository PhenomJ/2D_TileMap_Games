#include "ResourceManager.h"

ResourceManager* ResourceManager::_Instance = 0;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager* ResourceManager::GetInstance()
{
	if (_Instance == 0)
	{
		_Instance = new ResourceManager();
	}

	return _Instance;
}

Texture* ResourceManager::LoadTexture(LPCWSTR fileName)
{
	std::map<LPCWSTR, Texture*>::iterator itr = _textureMap.find(fileName);
	if (itr != _textureMap.end())
	{
		return itr->second;
	}

	Texture* texture = new Texture();
	texture->Init(fileName);
	
	_textureMap[fileName] = texture;
	return texture;
}