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

	//Component
	void AddComponent(Component* thisComponent);
	void RemoveComponent(Component* thisComponent);

private:
	Sprite* _sprite;
	std::list<Component*> _componentList;
	float _posX;
	float _posY;

};