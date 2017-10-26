#pragma once
#include <d3dx9.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>
#include "Texture.h"

class ResourceManager
{
private:
	static ResourceManager* _Instance;
	ResourceManager();

public:
	~ResourceManager();
	static ResourceManager* GetInstance();
	
	Texture* LoadTexture(std::wstring fileName);


	
private:
	Texture* _texture;
	std::map<std::wstring, Texture*> _textureMap;

public:
	std::vector<std::string> LoadScript(std::wstring scriptfileName);
private:
	std::map<std::wstring, std::vector<std::string>> _scriptMap;
};