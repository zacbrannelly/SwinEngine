#include "StateManager.h"

using namespace std;

StateManager::StateManager()
{
	_currentMap = NULL;
}

void StateManager::RegisterMap(string state, Map* map)
{
	_maps[state] = map;
}

Map* StateManager::GetMap(string state) const
{
	return _maps.at(state);
}

void StateManager::SetState(string state)
{
	if (_maps.find(state) != _maps.end())
	{
		_prevState = _state;
		_state = state;

		_currentMap = _maps[state];
	}
}

string StateManager::GetState() const
{
	return _state;
}

string StateManager::GetPreviousState() const
{
	return _prevState;
}

Map* StateManager::GetCurrentMap() const
{
	return _currentMap;
}

StateManager::~StateManager()
{
}
