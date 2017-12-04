#pragma once
#include <string>
#include <Windows.h>

class Component;

class Stage;

class GameGen
{
public:
	GameGen(Stage* stage);
	~GameGen();

public:
	virtual void CreateComponents();
	virtual Component* CreateLifeNpc(std::wstring scriptName, std::wstring textureName);
	virtual void SetName(std::wstring name);

protected:
	Stage* _stage;
	std::wstring _name;
	int _count;
};