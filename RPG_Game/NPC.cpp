#include "NPC.h"

NPC::NPC(LPCWSTR name) : Character(name)
{
	
}

NPC::~NPC()
{

}

void NPC::UpdateAI(float deltaTime)
{
	if (_isMoving == false)
	{
		int direction = rand() % 4;
		MoveStart((eDirection)direction);
	}
}