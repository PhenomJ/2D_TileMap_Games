#include "TurnManager.h"

TurnManager* TurnManager::_instance = NULL;

TurnManager::TurnManager()
{

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