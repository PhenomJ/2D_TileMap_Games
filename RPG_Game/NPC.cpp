#include "NPC.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "ComponentMessage.h"
#include "MoveState.h"
#include <list>

NPC::NPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName,spriteName)
{
	_type = eComponentType::CT_NPC;
	int speed = (rand() % 1500) + 400;
	_moveSpeed = (float)speed / 1000.0f;
	_hp = 1;
}

NPC::~NPC()
{

}

void NPC::UpdateAI(float deltaTime)
{
	// 타일 범위
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");

	int _range = 2;
	int minTileX = _tileX - _range;
	int minTileY = _tileY - _range;
	int maxTileX = _tileX + _range;
	int maxTileY = _tileY + _range;

	if (minTileX < 0)
		minTileX = 0;
	if (map->GetWidth() <= maxTileX)
		maxTileX = map->GetWidth() - 1;
	if (minTileY < 0)
		minTileY = 0;
	if (map->GetHeight() <= maxTileY)
		maxTileY = map->GetHeight() - 1;

	Component* findEnemy = NULL;

	for (int y = minTileY; y <= maxTileY; y++)
	{
		for (int x = minTileX; x <= maxTileX; x++)
		{
			std::list<Component*>componentList;
			if (false == map->GetTileCollisionList(x, y, componentList))
			{
				for (std::list<Component*>::iterator it = componentList.begin(); it != componentList.end(); it++)
				{
					_component = (*it);
					if (_component->GetType() == eComponentType::CT_MONSTER)
					{
						findEnemy = _component;
						break;
					}
				}
			}
		}
	}

	// 탐색 범위에 적 확인


	if (findEnemy != NULL)
	{
		// 추격 방향 설정
		eDirection direction = eDirection::NONE;
		for (int findDir = 0; findDir < 4; findDir++)
		{
			int newtileX = _tileX;
			int newtileY = _tileY;

			switch (findDir)
			{
			case eDirection::LEFT:
				newtileX--;
				break;
			case eDirection::RIGHT:
				newtileX++;
				break;

			case eDirection::DOWN:
				newtileY++;
				break;
			case eDirection::UP:
				newtileY--;
				break;

			default:
				break;
			}

			if (map->CanMoveTileMap(newtileX, newtileY))
			{
				if (direction != eDirection::NONE)
				{
					_currentDirection = (eDirection)findDir;
					_state->NextState(eStateType::ET_MOVE);
				}
				break;
			}
		}
	}

	else
	{
		Character::UpdateAI(deltaTime);
	}
}
