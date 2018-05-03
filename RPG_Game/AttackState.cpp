#include "AttackState.h"
#include "ComponentMessage.h"
#include "ComponentSystem.h"
#include "Character.h"

AttackState::AttackState()
{

}

AttackState::~AttackState()
{

}

void AttackState::Init(Character* character)
{
	State::Init(character);
}

void AttackState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}

	_character->ResetTarget();
	_nextState = eStateType::ET_IDLE;
}

void AttackState::Start()
{
	State::Start();

	sComponentMsgParam msgParam;
	msgParam.sender = (Component*)this;
	msgParam.receiver = _character->GetTarget();
	msgParam.message = L"Attack";
	msgParam.attackPoint = _character->GetAttackPoint();
	ComponentSystem::GetInstance()->SendMsg(msgParam);
	TurnManager::GetInstance()->ChangeTurn();
}

void AttackState::Stop()
{
	State::Stop();
}

void AttackState::Release()
{
	State::Release();
}

void AttackState::Render()
{
	State::Render();
}

void AttackState::Reset()
{
	State::Reset();
}