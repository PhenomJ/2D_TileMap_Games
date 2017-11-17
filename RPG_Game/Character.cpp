#include "Character.h"
#include "GameSystem.h"
#include "Sprite.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "ComponentMessage.h"
#include "State.h"
#include "MoveState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "DefenseState.h"
#include "DeadState.h"
#include <time.h>

Character::Character(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Component(name), _x(0.0f), _y(0.0f)
{
	_state = NULL;
	_targetX = 0;
	_targetY = 0;
	_moveDistanceperTimeX = 0;
	_moveDistanceperTimeY = 0;
	_moveSpeed = 1.0f;
	_spriteName = spriteName;
	_scriptName = scriptName;
	_attackPoint = 1;
}

Character::~Character()
{
	
}

void Character::Init()
{
	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		
		while (true)
		{
			if (map->CanMoveTileMap(_tileX, _tileY) == false)
			{
				_tileX = rand() % (map->GetWidth() - 1) + 1;
				_tileY = rand() % (map->GetHeight() - 1) + 1;
			}

			else
			{
				_x = map->GetPositionX(_tileX, _tileY);
				_y = map->GetPositionY(_tileX, _tileY);
				break;
			}
		}

		map->SetTileComponent(_tileX, _tileY, this, false);
	}

	
	InitMove();
	{
		State* state = new IdleState();
		state->Init(this);
		_stateMap[eStateType::ET_IDLE] = state;
	}

	{
		State* state = new MoveState();
		state->Init(this);
		_stateMap[eStateType::ET_MOVE] = state;
	}

	{
		State* state = new AttackState();
		state->Init(this);
		_stateMap[eStateType::ET_ATTACK] = state;
	}

	{
		State* state = new DefenseState();
		state->Init(this);
		_stateMap[eStateType::ET_DEFENCE] = state;
	}

	{
		State* state = new DeadState();
		state->Init(this);
		_stateMap[eStateType::ET_DEAD] = state;
	}

	ChangeState(eStateType::ET_IDLE);
}

void Character::Deinit()
{
	std::map<eStateType, State*>::iterator itr = _stateMap.begin();

	while (_stateMap.end() != itr)
	{
		State* state = itr->second;
		delete state;
		itr++;
	}

	_stateMap.clear();
}

void Character::Update(float deltaTime)
{
	_state->Update(deltaTime);
}

void Character::Render()
{
	
	_state->Render();
}

void Character::Release()
{
	
	_state->Release();
}

void Character::Reset()
{
	
	_state->Reset();
}

void Character::SetPosition(float tileX, float tileY)
{
	_x = tileX;
	_y = tileY;
}

void Character::InitMove()
{
	_isMoving = false;
	_currentDirection = eDirection::DOWN;
}

void Character::MoveStart(int newTileX, int newTileY)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
	map->ResetTileComponent(_tileX, _tileY, this);
	_tileX = newTileX;
	_tileY = newTileY;

		{
			map->SetTileComponent(_tileX, _tileY, this,false);

			_targetX = map->GetPositionX(_tileX, _tileY);
			_targetY = map->GetPositionY(_tileX, _tileY);

			float distanceX = _targetX - _x;
			float distanceY = _targetY - _y;

			_moveDistanceperTimeX = distanceX / _moveSpeed;
			_moveDistanceperTimeY = distanceY / _moveSpeed;	
		}

	_isMoving = true;
}

void Character::MoveDeltaPosition(float deltaX, float deltaY)
{
	_x += deltaX;
	_y += deltaY;
}

void Character::UpdateAI(float deltaTime)
{
	_currentDirection = (eDirection)(rand() % 4);
	ChangeState(eStateType::ET_MOVE);
}

void Character::ChangeState(eStateType stateType)
{
	if (_state != NULL)
		_state->Stop();

	_state = _stateMap[stateType];
	_state->Start();
}

void Character::ReceiveMessage(const sComponentMsgParam &msgParam)
{
	if (msgParam.message == L"Attack")
	{
		_attackedPoint = msgParam.attackPoint;
		ChangeState(eStateType::ET_DEFENCE);
	}
}

Component* Character::Collision(std::list<Component*>& collisionList)
{
	return NULL;
}

void Character::MoveStop()
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
	
	_x = map->GetPositionX(_tileX, _tileY);
	_y = map->GetPositionY(_tileX, _tileY);

	_moveDistanceperTimeX = 0.0f;
	_moveDistanceperTimeY = 0.0f;

	_isMoving = false;
}

void Character::Moving(float deltaTime)
{
	float moveDistanceX = _moveDistanceperTimeX * deltaTime;
	float moveDistanceY = _moveDistanceperTimeY * deltaTime;

	_x += moveDistanceX;
	_y += moveDistanceY;
}
bool Character::IsMoving()
{
	return _isMoving;
}

std::wstring Character::GetTextureFileName()
{
	return _spriteName;
}

std::wstring Character::GetScriptFileName()
{
	return _scriptName;
}

void Character::DecreaseHP(int attackPoint)
{
	_hp -= attackPoint;

	if (_hp < 0)
		_isLive = false;
}

void Character::SetTarget(Component* target)
{
	_target = target;
}