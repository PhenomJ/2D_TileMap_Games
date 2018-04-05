#pragma once
#include "GameGen.h"

class Stage;
class FindingPathGen : public GameGen
{
public:
	FindingPathGen(Stage* stage);
	~FindingPathGen();

public:
	void CreateComponents(std::wstring mapName);
	Component* CreateNpc(std::wstring scriptName, std::wstring textureName);
};