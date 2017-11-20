#include "DefenseState.h"
#include "ComponentMessage.h"
#include "ComponentSystem.h"
#include "Character.h"

DefenseState::DefenseState()
{

}

DefenseState::~DefenseState()
{

}

void DefenseState::Init(Character* character)
{
	State::Init(character);
}

void DefenseState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}
}

void DefenseState::Start()
{
	State::Start();

	int attackPoint = _character->GetAttackedPoint();
	_character->DecreaseHP(attackPoint);

	if (_character->IsLive() == false)
	{
		_character->SetCanMove(true);
		_character->MoveStop();
		//_character->ChangeState(eStateType::ET_DEAD);
		_nextState = eStateType::ET_DEAD;
	}

	else
	{
		//_character->ChangeState(eStateType::ET_IDLE);
		_nextState = eStateType::ET_MOVE;
	}
}

void DefenseState::Stop()
{
	State::Stop();
}

void DefenseState::Release()
{
	State::Release();
}

void DefenseState::Render()
{
	State::Render();
}

void DefenseState::Reset()
{
	State::Reset();
}