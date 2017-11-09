#include "Texture.h"

#include <SDL_opengl.h>

Texture::Texture(unsigned int handle, int width, int height)
{
	_handle = handle;
	_width = width;
	_height = height;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _handle);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::UploadData(void* data, int mode, unsigned int type)
{
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, mode, _width, _height, 0, mode, type, data);
}

void Texture::SetQuality(Quality quality)
{
	int filter = 0;
	
	switch (quality)
	{
	case Linear:
		filter = GL_LINEAR;
		break;
	case NearestNeighbour:
		filter = GL_NEAREST;
		break;
	default:
		return;
	}

	_quality = quality;

	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::ClampToEdge() 
{
	Bind();

	// Fixes artifacts on edges of sprites.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

Quality Texture::GetQuality() const
{
	return _quality;
}

int Texture::GetWidth() const
{
	return _width;
}

int Texture::GetHeight() const
{
	return _height;
}

void Texture::Release()
{
	glDeleteTextures(1, &_handle);
}

Texture* Texture::GenerateEmpty(int width, int height)
{
	unsigned int newHandle = 0;
	glGenTextures(1, &newHandle);

	return new Texture(newHandle, width, height);
}

Texture::~Texture()
{
}
