#pragma once
#include <list>

class Component;
class Sprite;

class TileCell
{
public:
	TileCell(int tileX, int tileY);
	~TileCell();

	void Deinit();
	void Update(float deltaTime);

	void Render();
	void Release();
	void Reset();

	//Position
	float GetPositionX();
	float GetPositionY();
	void SetPosition(float posX, float posY);
	void MoveDeltaPosition(float deltaX, float deltaY);

	//Component
	void AddComponent(Component* thisComponent, bool isRender);
	void RemoveComponent(Component* thisComponent);

	//Collision
	bool CanMove();
	bool GetCollisionList(std::list<Component*> &collisionList);

	std::list<Component*> GetComponentList();

private:
	std::list<Component*> _componentList;
	std::list<Component*> _renderList;
	float _posX;
	float _posY;

	//FindingPath algorythm
private:
	bool _isFindingPathMark;
	TileCell* _prevCell;

	float _distanceWeight; // 고정값, 맵 로딩시 셋팅
	float _distanceFromStart; // 계산된 값을 저장하기 위한 변수

	int _tileX;
	int _tileY;

public:
	void InitFindingPath();
	bool IsFindingPathMarked() { return _isFindingPathMark; }
	void FindingPathMarking() { _isFindingPathMark = true; }
	void FindingPathMark();

	int GetTileX() { return _tileX; }
	int GetTileY() { return _tileY; }

	TileCell* GetPrevCell() { return _prevCell; }
	void SetPrevCell(TileCell* tilecell) { _prevCell = tilecell; }

	float GetDistanceFromStart() { return _distanceFromStart; };
	float GetDistanceWeight() { return _distanceWeight; };
	void SetDistanceFromStart(float distance) { _distanceFromStart = distance; }

	//Heurisitc
private:
	float _heuristic;

public:
	void SetHeuristic(float heuristic) { _heuristic = heuristic; };
	float GetHeuristic();


private:
	bool _isClickable = false;

public:
	void ChangeClickable() { _isClickable = !_isClickable; }
	bool GetClickable() { return _isClickable; }

	//Attack judge
private:
	bool _isAttackable = false;

public:
	void ChangeAttackable() { _isAttackable = !_isAttackable; }
	bool GetAttackable() { return _isAttackable; }
};