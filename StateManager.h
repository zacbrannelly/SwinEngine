#pragma once

#include <string>
#include <map>
#include "Map.h"

class StateManager
{
public:
	StateManager();
	~StateManager();

	void RegisterMap(std::string state, Map* map);
	Map* GetMap(std::string state) const;

	void SetState(std::string state);
	std::string GetState() const;

	std::string GetPreviousState() const;
	Map* GetCurrentMap() const;
private:
	std::map<std::string, Map*> _maps;
	std::string _state;
	std::string _prevState;
	Map* _currentMap;
};

