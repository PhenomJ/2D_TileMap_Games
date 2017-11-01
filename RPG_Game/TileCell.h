#pragma once
#include <list>

class Component;
class TileCell
{
public:
	TileCell();
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

	//Collision Check
	bool CanMove();

private:
	std::list<Component*> _componentList;
	std::list<Component*> _renderList;
	float _posX;
	float _posY;

};