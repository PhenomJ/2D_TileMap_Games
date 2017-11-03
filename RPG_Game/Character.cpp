#include "Character.h"
#include "GameSystem.h"
#include "Sprite.h"
#include "Map.h"
#include "ComponentSystem.h"

Character::Character(LPCWSTR name, LPCWSTR spriteName) : Component(name), _spriteList(NULL), _x(0.0f), _y(0.0f)
{
	_map = 32;
	_targetX = 0;
	_targetY = 0;
	_moveDistanceperTimeX = 0;
	_moveDistanceperTimeY = 0;
	_moveSpeed = 0.5f;
	_spriteName = spriteName;

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
		wsprintf(scriptFilename, L"%s_01.json", _name);
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_02.json", _name);
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_03.json", _name);
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_04.json", _name);
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	
	InitMove();

	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		_tileX = 2;
		_tileY = 2;
		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);

		map->SetTileComponent(_tileX, _tileY, this, false);
	}
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
	case eDirection::LEFT: // left
		newTileX--;
		break;
	case eDirection::RIGHT: // right
		newTileX++;
		break;
	case eDirection::UP: // up
		newTileY--;
		break;
	case eDirection::DOWN: // down
		newTileY++;
		break;
	}

	if (map->CanMoveTileMap(newTileX, newTileY) == false)
		return;

	map->ResetTileComponent(_tileX, _tileY, this);
	_tileX = newTileX;
	_tileY = newTileY;

	// 이동을 위한 보간작업.
		{
			map->SetTileComponent(_tileX, _tileY, this,false);

			// 이동 거리를 구하기 위한 목적지.
			_targetX = map->GetPositionX(_tileX, _tileY);
			_targetY = map->GetPositionY(_tileX, _tileY);

			float distanceX = _targetX - _x;
			float distanceY = _targetY - _y;

			//최소 이동거리
			_moveDistanceperTimeX = distanceX / _moveSpeed;
			_moveDistanceperTimeY = distanceY / _moveSpeed;	
		}

		_isMoving = true;
}

void Character::UpdateMove(float deltaTime)
{
	if (_isMoving == false)
		return;

	if (_moveSpeed <= _movingDuration)
	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		_movingDuration = 0.0f;
		_isMoving = false;
		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);
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