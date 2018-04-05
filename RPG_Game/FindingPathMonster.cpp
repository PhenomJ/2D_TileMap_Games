#include "FindingPathMonster.h"

FindingPathMonster::FindingPathMonster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Monster(name, scriptName, spriteName)
{

}

FindingPathMonster::~FindingPathMonster()
{

}

void FindingPathMonster::UpdateAI(float deltaTime)
{

}

Component* FindingPathMonster::Collision(std::list<Component*> &collisionList)
{
	return NULL;
}