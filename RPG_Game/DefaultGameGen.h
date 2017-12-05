#pragma once
#include "GameGen.h"

class DefaultGameGen : public GameGen
{
public:
	DefaultGameGen(Stage* stage);
	~DefaultGameGen();

public:
	void CreateComponents(std::wstring mapName);
};