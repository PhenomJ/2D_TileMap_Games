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

Texture* ResourceManager::LoadTexture(std::wstring fileName)
{
	std::map<std::wstring, Texture*>::iterator itr = _textureMap.find(fileName);
	if (itr != _textureMap.end())
	{
		return itr->second;
	}

	Texture* texture = new Texture();
	texture->Init(fileName.c_str());
	
	_textureMap[fileName] = texture;
	return texture;
}

std::vector<std::string> ResourceManager::LoadScript(std::wstring scriptfileName)
{
	std::map<std::wstring, std::vector<std::string>>::iterator itr = _scriptMap.find(scriptfileName);
	if (itr != _scriptMap.end())
	{
		return itr->second;
	}

	std::vector<std::string> script;
	char record[1000];
	std::ifstream infile(scriptfileName);
	
	while (!infile.eof())
	{
		infile.getline(record, 100);
		script.push_back(record);
	}

	_scriptMap[scriptfileName] = script;
	return script;
}