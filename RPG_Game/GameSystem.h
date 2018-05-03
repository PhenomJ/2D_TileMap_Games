#pragma once
#include <vector>
#include <d3dx9.h>
#include <Windows.h>
#include <list>

#define RELEASE_COM(x) {if (x != NULL) {x->Release(); x = NULL;}}
#define SAFE_DELETE(x) {if(x) {delete x; x = NULL;}}


class GameTimer;
class Map;
class Character;
class Component;
class Font;
class Stage;

class GameSystem
{
private:
	GameSystem();
	static GameSystem* _instance;

public:
	~GameSystem();
	static GameSystem* GetInstance();
	bool InitSystem(HINSTANCE hInstance, int nCmdShow);
	int UpdateSystem();
	
public:
	bool InitDirect3D();
	void CheckDeviceLost();

private:
	HWND _hMainWnd;
	GameTimer* _gameTimer;
	float _frameduration;

	LPDIRECT3DDEVICE9 _device3d;
	LPD3DXSPRITE _sprite;
	D3DPRESENT_PARAMETERS _d3dpp;

	bool _isFullScreen;

	int _clientWidth = 1920;
	int _clientHeight = 1080;	

public:
	int GetClientWidth();
	int GetClientHeight();
	LPD3DXSPRITE GetSprite();
	LPDIRECT3DDEVICE9 GetDevice3d();


private:

	// Input
public:
	void InitInput();
	void KeyDown(unsigned int KeyCode);
	void KeyUp(unsigned int KeyCode);
	bool IsKeyDown(unsigned int KeyCode);
	bool IsMouseDown() { return _isMouseDown; }
	void MouseDown(int mouseX, int mouseY);
	void MouseUp();
	int GetMouseX() { return _mouseX; }
	int GetMouseY() { return _mouseY; }

	enum eKeyState
	{
		KEY_DOWN,
		KEY_UP
	};

private:
	eKeyState _keyState[256];
	bool _isMouseDown;
	int _mouseX;
	int _mouseY;
	//Stage
private:
	Stage* _stage;

public:
	Stage* GetStage() { return _stage; }
};