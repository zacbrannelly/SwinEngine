#pragma once

#include <SDL.h>
#include <map>
#include <vector>
#include <string>

class Keyboard
{
public:
	static void GetStatesFromEvents(std::vector<SDL_Event>& events);
	static bool IsKeyDown(std::string name);
	static bool IsKeyUp(std::string name);
	static bool WasKeyDown(std::string name);
	static bool WasKeyUp(std::string name);
private:
	static std::map<SDL_Keycode, bool> _states;
	static std::map <SDL_Keycode, bool> _prevStates;
};