#include "IdleState.h"
#include "Character.h"

IdleState::IdleState()
{

}

IdleState::~IdleState()
{

}

void IdleState::Init(Character* character)
{
	_character = character;
}

void IdleState::Update(float deltaTime)
{
	if (_character->IsLive() == false)
		return;

	if (_character->IsMoving() == false)
	{
		_character->UpdateAI(deltaTime);
	}
}

void IdleState::Start()
{

}

void IdleState::Stop()
{

}
