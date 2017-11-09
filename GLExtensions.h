#pragma once

#include <SDL_opengl.h>
#include <map>

class GLExtensions
{
public:
	static PROC GetExtensionFunction(std::string name);
private:
	static std::map<std::string, PROC> _loadedExtensions;
};
