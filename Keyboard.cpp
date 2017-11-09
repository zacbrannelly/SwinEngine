#include "Keyboard.h"

using namespace std;

std::map<SDL_Keycode, bool> Keyboard::_states;
std::map <SDL_Keycode, bool> Keyboard::_prevStates;

void Keyboard::GetStatesFromEvents(vector<SDL_Event>& events)
{
	_prevStates.clear();

	for (auto event : events)
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			_prevStates[event.key.keysym.sym] = _states[event.key.keysym.sym];
			_states[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			_prevStates[event.key.keysym.sym] = _states[event.key.keysym.sym];
			_states[event.key.keysym.sym] = false;
			break;  
		}
	}
}

bool Keyboard::IsKeyDown(string name)
{
	auto keyCode = SDL_GetKeyFromName(name.c_str());
	
	if (keyCode == SDLK_UNKNOWN)
		return false;

	return _states[keyCode];
}

bool Keyboard::IsKeyUp(string name)
{
	return !IsKeyDown(name);
}

bool Keyboard::WasKeyDown(string name)
{
	auto keyCode = SDL_GetKeyFromName(name.c_str());

	if (keyCode == SDLK_UNKNOWN)
		return false;

	return _prevStates[keyCode];
}

bool Keyboard::WasKeyUp(string name)
{
	return !WasKeyDown(name);
}