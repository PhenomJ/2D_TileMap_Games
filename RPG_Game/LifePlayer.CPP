#include "LifePlayer.h"
#include "GameSystem.h"
#include "ComponentSystem.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"
#include "AttackState.h"
#include "MoveState.h"
#include "DeadState.h"
#include "DefenseState.h"
#include "IdleState.h"

LifePlayer::LifePlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Player(name, scriptName, spriteName)
{
	_moveSpeed = 0.1f;
	_type = eComponentType::CT_PLAYER;
	_hp = 10;
	_attackPoint = 5;
	_attackCoolDown = 1.0f;
}

LifePlayer::~LifePlayer()
{

}

void LifePlayer::InitState()
{
	Player::InitState();
	ReplaceState(eStateType::ET_ATTACK, new IdleState());
}