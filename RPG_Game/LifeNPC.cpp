#include "LifeNPC.h"

LifeNPC::LifeNPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName, spriteName)
{
	_type = eComponentType::CT_NPC;
}

LifeNPC::~LifeNPC()
{

}

void LifeNPC::UpdateAI(float deltaTime)
{

}