#include "ResourceManager.h"
#include <iostream>
#include <SDL_opengl.h>
#include <SDL_image.h>

using namespace std;

ResourceManager::ResourceManager()
{
}

Texture* ResourceManager::GetTexture(string path)
{
	return _textures.find(path) != _textures.end() ? _textures[path] : NULL;
}

Texture* ResourceManager::LoadTexture(string path)
{
	auto texture = GetTexture(path);

	if (texture != NULL)
		return texture;

	auto surface = IMG_Load(path.c_str());

	if (surface == NULL)
	{
		cout << "Failed to load image file: " << path << endl;
		return NULL;
	}

	texture = ConvertSurfaceToTexture(surface);

	_textures[path] = texture;

	return texture;
}

Texture* ResourceManager::ConvertSurfaceToTexture(SDL_Surface* surface)
{
	Texture* newTexture = Texture::GenerateEmpty(surface->w, surface->h);

	int mode = GL_RGB;

	if (surface->format->BytesPerPixel == 4)
		mode = GL_RGBA;

	newTexture->UploadData(surface->pixels, mode, GL_UNSIGNED_BYTE);
	newTexture->SetQuality(Quality::Linear);
	newTexture->ClampToEdge();

	newTexture->Unbind();

	return newTexture;
}

void ResourceManager::ReleaseTexture(string path)
{
	auto texture = GetTexture(path);

	if (texture != NULL)
		texture->Release();
}

void ResourceManager::ReleaseAll()
{
	for (auto pair : _textures)
	{
		if (pair.second != NULL)
			pair.second->Release();
	}
}

ResourceManager::~ResourceManager()
{
}
