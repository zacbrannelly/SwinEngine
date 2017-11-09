#include "Line.h"
#include <SDL_opengl.h>

using namespace std;
using namespace glm;

Line::Line(string name, vec2 start, vec2 end) : Shape(name, start, end.x - start.x, end.y - start.y, LineObject)
{
	SetPoints(start, end);
	SetColor(vec4(1.0f));
}

bool Line::Load(ResourceManager* mgr)
{
	Shape::Load(mgr);

	// Disable texture coords since we don't use them for lines
	GetVertexArrayObject()->DisableVertexAttrib(TEXTURE_COORDS_ID);

	return true;
}

void Line::Render(RenderingContext* context, double interpolation)
{
	Shape::Render(context, interpolation);

	glDrawArrays(GL_LINES, 0, 2);
}

void Line::SetColor(vec4 color)
{
	vec4 colors[2] = { color, color };
	SetColors(&colors[0], 8 * sizeof(float));
}

void Line::SetPoints(glm::vec2 start, glm::vec2 end)
{
	_start = start;
	_end = end;

	vec2 points[2] = { _start, _end };
	SetVertices(&points[0], 8 * sizeof(float));
}

void Line::SetStartPoint(glm::vec2 point)
{
	SetPoints(point, _end);
}

vec2 Line::GetStartPoint() const
{
	return _start;
}

void Line::SetEndPoint(vec2 point)
{
	SetPoints(_start, point);
}

vec2 Line::GetEndPoint() const
{
	return _end;
}

Line::~Line()
{
}
