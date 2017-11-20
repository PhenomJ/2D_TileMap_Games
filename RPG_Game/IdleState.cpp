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
	State::Init(character);
}

void IdleState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}

	if (_character->IsLive() == false)
		return;

	if (_character->IsMoving() == false)
	{
		_character->UpdateAI(deltaTime);
	}
}

void IdleState::Start()
{
	State::Start();
}

void IdleState::Stop()
{
	State::Stop();
}
