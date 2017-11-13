#include "NPC.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "ComponentMessage.h"
#include <list>

NPC::NPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName,spriteName)
{
	_type = eComponentType::CT_NPC;
	int speed = (rand() % 1500) + 400;
	_moveSpeed = (float)speed / 1000.0f;
}

NPC::~NPC()
{

}

void NPC::UpdateAI(float deltaTime)
{
	if (_isLive == false)
		return;

	if (_isMoving == false)
	{
		// 타일 범위
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");

		std::vector<eComponentType> typeList;
		typeList.push_back(eComponentType::CT_MONSTER);
		Component* findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(this, 2, typeList);


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
					_moveSpeed = 0.3f;
					direction = (eDirection)findDir;
					MoveStart(direction);
					break;
				}
			}
		}

		else
		{
			Character::UpdateAI(deltaTime);
		}
		//
	}
}
/*
void NPC::receiveMessage(std::wstring msg, const sComponentMsgParam &msgParam)
{
	if (msg == L"Attack")
	{
		int attackPoint = msgParam.attackPoint;
		_hp -= attackPoint;

		if (_hp < 0)
		{
			//dead
			_isLive = false;
			SetCanMove(true);

			//stop
			_moveDistanceperTimeX = 0;
			_moveDistanceperTimeY = 0;
		}
	}
}
*/