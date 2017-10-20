#pragma once
#include <d3dx9.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
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


	std::vector<std::string> LoadScript(LPCWSTR scriptfileName);
private:
	Texture* _texture;
	std::map<LPCWSTR, Texture*> _textureMap;
	std::map<LPCWSTR, std::vector<std::string>> _scriptMap;
};