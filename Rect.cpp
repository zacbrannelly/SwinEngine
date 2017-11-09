#include "Rect.h"
#include <SDL_opengl.h>
#include <vector>

using namespace std;
using namespace glm;

Rect::Rect(string name, vec2 pos, float width, float height) : Rect(name, pos, width, height, RectangleObject)
{

}

Rect::Rect(string name, vec2 pos, float width, float height, ObjectType type) : Shape(name, pos, width, height, type)
{
	SetSize(GetWidth(), GetHeight());
	SetColor(vec4(1.0f));

	_isFilled = true;
}

bool Rect::Load(ResourceManager* mgr)
{
	Shape::Load(mgr);

	// Disable texture coords since we won't be using them
	GetVertexArrayObject()->DisableVertexAttrib(TEXTURE_COORDS_ID);

	unsigned short indices[6] = { 0, 1, 2, 0, 2, 3 };
	SetIndices(&indices, 6 * sizeof(unsigned short));

	return true;
}

void Rect::Render(RenderingContext* context, double interpolation)
{
	Shape::Render(context, interpolation);

	if (_isFilled)
	{
		GetIndexBuffer()->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
	}
	else
	{
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}
}

void Rect::SetColor(vec4 color)
{
	vector<vec4> colorData;
	for (int i = 0; i < 4; ++i)
		colorData.push_back(color);

	SetColors(&colorData[0], 16 * sizeof(float));
}

void Rect::SetSize(float width, float height)
{
	Shape::SetSize(width, height);

	vector<vec2> vertexData;
	vertexData.push_back(vec2(0, height)); // bottom left
	vertexData.push_back(vec2(0, 0)); // top left
	vertexData.push_back(vec2(width, 0)); // top right
	vertexData.push_back(vec2(width, height)); // bottom right

	SetVertices(&vertexData[0], vertexData.size() * 2 * sizeof(float));
}

void Rect::SetFilled(bool filled)
{
	_isFilled = filled;
}

bool Rect::IsFilled() const
{
	return _isFilled;
}

Rect::~Rect()
{
}
