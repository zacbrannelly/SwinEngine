#include "Sprite.h"
#include <vector>
#include <SDL_opengl.h>
#include "GLExtensions.h"

using namespace std;
using namespace glm;

Sprite::Sprite(string name, vec2 position, string path) : Rect(name, position, 0, 0, SpriteObject)
{
	_path = path;
	_texture = NULL;
}

Sprite::Sprite(string name, vec2 position, Texture* texture) : Rect(name, position, texture->GetWidth(), texture->GetHeight(), SpriteObject)
{
	_texture = texture;
	_path = "";
}

bool Sprite::Load(ResourceManager* mgr)
{
	Rect::Load(mgr);

	// Re-enable texture coords since it was disabled by Rect
	GetVertexArrayObject()->EnableVertexAttrib(TEXTURE_COORDS_ID);

	if (_path != "")
	{
		_texture = mgr->LoadTexture(_path);
	}

	if (_texture != NULL)
	{
		if (GetWidth() == 0 && GetHeight() == 0)
			SetSize(_texture->GetWidth(), _texture->GetHeight());

		if (_sourceRect.GetWidth() == 0 && _sourceRect.GetHeight() == 0)
			SetSourceRect(0, 0, _texture->GetWidth(), _texture->GetHeight());
	}
	
	return _texture != NULL;
}

void Sprite::Render(RenderingContext* context, double interpolation)
{
	auto shader = context->GetShaders();
	shader->Use();

	auto glActiveTexture = (PFNGLACTIVETEXTUREPROC)GLExtensions::GetExtensionFunction("glActiveTexture");
	glActiveTexture(GL_TEXTURE0);

	_texture->Bind();
	shader->SetUniform("Tex", 0);
	shader->SetUniform("usingTextures", true);

	Rect::Render(context, interpolation);

	shader->SetUniform("usingTextures", false);
}

void Sprite::SetSourceRect(float x, float y, float width, float height)
{
	_sourceRect.Calculate(vec2(x, y), width, height);

	vector<vec2> texData;
	texData.push_back(vec2(x / _texture->GetWidth(), (y + height) / _texture->GetHeight())); // bottom left
	texData.push_back(vec2(x / _texture->GetWidth(), y / _texture->GetHeight())); // top left
	texData.push_back(vec2((x + width) / _texture->GetWidth(), y / _texture->GetHeight())); // top right
	texData.push_back(vec2((x + width) / _texture->GetWidth(), (y + height) / _texture->GetHeight())); // bottom right

	SetTextureCoords(&texData[0], texData.size() * 2 * sizeof(float));
}

BoundingBox Sprite::GetSourceRect() const
{
	return _sourceRect;
}

void Sprite::SetTexture(Texture* texture)
{
	_texture = texture;
}

Texture* Sprite::GetTexture() const
{
	return _texture;
}

Sprite::~Sprite()
{
}
