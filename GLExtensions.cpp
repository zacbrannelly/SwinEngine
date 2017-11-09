#include "GLExtensions.h"

std::map<std::string, PROC> GLExtensions::_loadedExtensions;

PROC GLExtensions::GetExtensionFunction(std::string name)
{
	if (_loadedExtensions.find(name) == _loadedExtensions.end())
		_loadedExtensions[name] = wglGetProcAddress(name.c_str());

	return _loadedExtensions[name];
}