#include "Character.h"
#include "GameSystem.h"
#include "Sprite.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "ComponentMessage.h"
#include <time.h>

Character::Character(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Component(name), _spriteList(NULL), _x(0.0f), _y(0.0f)
{
	_map = 32;
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
	WCHAR textureFilename[256];
	wsprintf(textureFilename, L"%s.png", _spriteName.c_str());

	WCHAR scriptFilename[256];
	{
		wsprintf(scriptFilename, L"%s_01.json", _scriptName.c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_02.json", _scriptName.c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_03.json", _scriptName.c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_04.json", _scriptName.c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	
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
}

void Character::Deinit()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Deinit();
		delete _spriteList[i];
	}
	_spriteList.clear();
}

void Character::Update(float deltaTime)
{
	_spriteList[(int)_currentDirection]->Update(deltaTime);
	UpdateAI(deltaTime);
	UpdateMove(deltaTime);
}

void Character::Render()
{
	_spriteList[(int)_currentDirection]->SetPosition(_x, _y);
	_spriteList[(int)_currentDirection]->Render();
}

void Character::Release()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Release();
	}
	_spriteList.clear();
}

void Character::Reset()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Reset();
	}
	_spriteList.clear();
}

void Character::SetPosition(float tileX, float tileY)
{
	_x = tileX;
	_y = tileY;
}

void Character::InitMove()
{
	_isMoving = false;
	
	_movingDuration = 0.0f;
	_currentDirection = eDirection::DOWN;
}

void Character::MoveStart(eDirection direction)
{
	if (_isMoving == true)
		return;

	_currentDirection = direction;

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
	
	int newTileX = _tileX;
	int newTileY = _tileY;
	switch (direction)
	{
	case eDirection::LEFT: 
		newTileX--;
		break;
	case eDirection::RIGHT: 
		newTileX++;
		break;
	case eDirection::UP: 
		newTileY--;
		break;
	case eDirection::DOWN: 
		newTileY++;
		break;
	}

	std::list<Component*> collisionList;
	bool canMove = map->GetTileCollisionList(newTileX, newTileY, collisionList);

	if (canMove == false)
	{
		Collision(collisionList);
		return;
	}

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

void Character::UpdateMove(float deltaTime)
{
	if (_isLive == false)
		return;

	if (_isMoving == false)
		return;

	if (_moveSpeed <= _movingDuration)
	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		_movingDuration = 0.0f;
		_isMoving = false;
		
		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);

		_moveDistanceperTimeX = 0.0f;
		_moveDistanceperTimeY = 0.0f;
	}

	else
	{
		_movingDuration += deltaTime;

		float moveDistanceX = _moveDistanceperTimeX * deltaTime;
		float moveDistanceY = _moveDistanceperTimeY * deltaTime;

		_x += moveDistanceX;
		_y += moveDistanceY;
	}
}

void Character::MoveDeltaPosition(float deltaX, float deltaY)
{
	_x += deltaX;
	_y += deltaY;
}

void Character::UpdateAI(float deltaTime)
{
	if (_isMoving == false)
	{
		int direction = rand() % 4;
		MoveStart((eDirection)direction);
	}
}

void Character::ReceiveMessage(const sComponentMsgParam &msgParam)
{
	if (msgParam.message == L"Attack")
	{
		int attackPoint = msgParam.attackPoint;
		_hp -= attackPoint;

		if (_hp < 0)
		{
			//dead
			_isLive = false;
			SetCanMove(false);

			//stop
			_moveDistanceperTimeX = 0;
			_moveDistanceperTimeY = 0;
		}
	}
}

void Character::Collision(std::list<Component*>& collisionList)
{
	for (std::list<Component*>::iterator itr = collisionList.begin(); itr != collisionList.end(); itr++)
	{
		sComponentMsgParam msgParam;
		msgParam.sender = this;
		msgParam.receiver = (*itr);
		msgParam.message = L"Collision";
		ComponentSystem::GetInstance()->SendMsg(msgParam);
	}
}