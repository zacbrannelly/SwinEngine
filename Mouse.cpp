#include "Mouse.h"
#include <iostream>

using namespace std;
using namespace glm;

map<Button, bool> Mouse::_states;
map<Button, bool> Mouse::_prevStates;
vec2 Mouse::_mousePosition;

void Mouse::GetStatesFromEvents(vector<SDL_Event>& events)
{
	_prevStates.clear();

	for (auto event : events)
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN: 
			_prevStates[(Button)event.button.button] = _states[(Button)event.button.button];
			_states[(Button)event.button.button] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			_prevStates[(Button)event.button.button] = _states[(Button)event.button.button];
			_states[(Button)event.button.button] = false;
			break;
		case SDL_MOUSEMOTION:
			_mousePosition.x = event.motion.x;
			_mousePosition.y = event.motion.y;
			break;
		}
	}
}

bool Mouse::IsButtonDown(Button btn)
{
	return _states[btn];
}

bool Mouse::IsButtonUp(Button btn)
{
	return !_states[btn];
}

bool Mouse::WasButtonDown(Button btn)
{
	return _prevStates[btn];
}

bool Mouse::WasButtonUp(Button btn)
{
	return !_prevStates[btn];
}

vec2 Mouse::GetMousePosition()
{
	return _mousePosition;
}

float Mouse::GetMouseX()
{
	return _mousePosition.x;
}

float Mouse::GetMouseY()
{
	return _mousePosition.y;
}