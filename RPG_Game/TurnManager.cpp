#include "TurnManager.h"

TurnManager* TurnManager::_instance = NULL;

TurnManager::TurnManager()
{
	_isPlayerTurn = true;
}

TurnManager::~TurnManager()
{

}

TurnManager* TurnManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new TurnManager();
	}
	return _instance;
}