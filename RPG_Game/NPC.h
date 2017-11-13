#pragma once
#include "Character.h"

class NPC : public Character
{
public:
	NPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName);
	~NPC();
	void UpdateAI(float deltaTime);
	//void receiveMessage(std::wstring msg, const sComponentMsgParam &msgParam);

private:
	
};