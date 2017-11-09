#pragma once

#include <map>
#include <string>
#include "Texture.h"
#include <SDL.h>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Texture* GetTexture(std::string path);
	Texture* LoadTexture(std::string path);

	void ReleaseTexture(std::string path);
	void ReleaseAll();
private:
	std::map<std::string, Texture*> _textures;

	Texture* ConvertSurfaceToTexture(SDL_Surface* surface);
};

