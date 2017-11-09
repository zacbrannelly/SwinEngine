#pragma once

#include <SDL.h>
#include <map>
#include <vector>
#include <string>
#include "glm\glm.hpp"
	
enum Button
{
	Left = 1, Middle = 2, Right = 3
};

class Mouse
{
public:
	static void GetStatesFromEvents(std::vector<SDL_Event>& events);
	static bool IsButtonDown(Button btn);
	static bool IsButtonUp(Button btn);
	static bool WasButtonDown(Button btn);
	static bool WasButtonUp(Button btn);
	static glm::vec2 GetMousePosition();
	static float GetMouseX();
	static float GetMouseY();
private:
	static std::map<Button, bool> _states;
	static std::map<Button, bool> _prevStates;
	static glm::vec2 _mousePosition;
};