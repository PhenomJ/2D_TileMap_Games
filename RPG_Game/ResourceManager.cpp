#include"ResourceManager.h"

ResourceManager* ResourceManager::_Instace = NULL;

ResourceManager::ResourceManager()
{
	
}

ResourceManager::~ResourceManager()
{

}

ResourceManager* ResourceManager::GetInstance()
{
	if (_Instace == NULL)
	{
		_Instace = new ResourceManager();
	}

	return _Instace;
}

Texture* ResourceManager::LoadTexture(LPCWSTR fileName)
{
	return _texture;
}