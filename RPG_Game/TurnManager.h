#pragma once
#include <Windows.h>

class TurnManager
{
private:
	TurnManager();
	static TurnManager* _instance;

public:
	~TurnManager();
	static TurnManager* GetInstance();

	// TurnManagement
private:
	bool _isPlayerTurn = false;

public:
	void ChangeTurn() { _isPlayerTurn = !_isPlayerTurn; }
	bool IsPlayerTurn() { return _isPlayerTurn; }
};