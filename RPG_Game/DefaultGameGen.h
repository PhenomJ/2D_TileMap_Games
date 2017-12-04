#pragma once
#include "GameGen.h"

class Stage;
class DefaultGameGen : public GameGen
{
public:
	DefaultGameGen(Stage* stage);
	~DefaultGameGen();

public:
	void CreateComponents();
	Component* CreateNpc(std::wstring scriptName, std::wstring textureName);
	Component* CreateMonster(std::wstring scriptName, std::wstring textureName);
	Component* CreateRecoveryItem(std::wstring scriptName, std::wstring textureName);
	Component* CreatePoisionItem(std::wstring scriptName, std::wstring textureName);
};