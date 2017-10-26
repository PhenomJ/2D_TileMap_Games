#pragma once
#include <list>

class Sprite;
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
	
	void SetSprite(Sprite* sprite);

	//Position
	float GetPositionX();
	float GetPositionY();
	void SetPosition(float posX, float posY);
	void MoveDeltaPosition(float deltaX, float deltaY);

	//Component
	void AddComponent(Component* thisComponent, bool isRender);
	void RemoveComponent(Component* thisComponent);

private:
	Sprite* _sprite;
	std::list<Component*> _componentList;
	std::list<Component*> _renderList;
	float _posX;
	float _posY;

};