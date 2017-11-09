#include "Circle.h"
#include <vector>
#include <SDL_opengl.h>

using namespace std;
using namespace glm;

Circle::Circle(string name, vec2 pos, float radius) : Shape(name, pos, 2 * radius, 2 * radius, CircleObject)
{
	SetRadius(radius);
	SetColor(vec4(1.0f));
}

bool Circle::Load(ResourceManager* mgr)
{
	Shape::Load(mgr);

	// Disable texture coords since we don't use them here
	GetVertexArrayObject()->DisableVertexAttrib(TEXTURE_COORDS_ID);

	return true;
}

void Circle::Render(RenderingContext* context, double interpolation)
{
	Shape::Render(context, interpolation);

	if (_isFilled)
		glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
	else
		glDrawArrays(GL_LINE_LOOP, 0, 360);
}

void Circle::SetColor(vec4 color)
{
	vector<vec4> colorData;

	for (int i = 0; i < 360; i++)
		colorData.push_back(color);

	SetColors(&colorData[0], colorData.size() * 4 * sizeof(float));
}

void Circle::SetRadius(float radius)
{
	_radius = radius;

	SetSize(2 * radius, 2 * radius);

	vector<vec2> vertexData;

	for (int i = 0; i < 360; i++)
	{
		float x = radius * cos(i * (180.0f / M_PI));
		float y = radius * sin(i * (180.0f / M_PI));

		vertexData.push_back(vec2(x, y) + vec2(radius));
	}

	SetVertices(&vertexData[0], vertexData.size() * 2 * sizeof(float));
}

float Circle::GetRadius() const
{
	return _radius;
}

void Circle::SetFilled(bool filled)
{
	_isFilled = filled;
}

bool Circle::IsFilled() const
{
	return _isFilled;
}

Circle::~Circle()
{
}
