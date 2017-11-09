#include "BoundingBox.h"

using namespace glm;

BoundingBox::BoundingBox() : BoundingBox(vec2(0, 0), vec2(0, 0))
{
	
}

BoundingBox::BoundingBox(vec2 min, vec2 max)
{
	_min = min;
	_max = max;
}

BoundingBox::BoundingBox(vec2 pos, float width, float height)
{
	Calculate(pos, width, height);
}

void BoundingBox::SetMin(glm::vec2 min)
{
	_min = min;
}

vec2 BoundingBox::GetMin() const
{
	return _min;
}

void BoundingBox::SetMax(glm::vec2 max)
{
	_max = max;
}

vec2 BoundingBox::GetMax() const
{
	return _max;
}

void BoundingBox::Calculate(vec2 pos, float width, float height)
{
	_min = pos;
	_max = _min + vec2(width, height);
}

void BoundingBox::SetWidth(float width)
{
	_max.x = _min.x + width;
}

float BoundingBox::GetWidth() const
{
	return _max.x - _min.x;
}

void BoundingBox::SetHeight(float height)
{
	_max.y = _min.y + height;
}

float BoundingBox::GetHeight() const
{
	return _max.y - _min.y;
}

void BoundingBox::SetPosition(vec2 pos)
{
	float w = GetWidth();
	float h = GetHeight();

	Calculate(pos, w, h);
}

vec2 BoundingBox::GetPosition() const
{
	return _min;
}

bool BoundingBox::Intersects(BoundingBox& bb) 
{
	auto bottomLeft = vec2(_min.x, _max.y);
	auto topRight = vec2(_max.x, _min.y);

	auto bbBottomLeft = vec2(bb.GetMin().x, bb.GetMax().y);
	auto bbTopRight = vec2(bb.GetMax().x, bb.GetMin().y);

	return Contains(bb.GetMin()) || Contains(bb.GetMax()) || Contains(bbBottomLeft) || Contains(bbTopRight)
		|| bb.Contains(_min) || bb.Contains(_max) || bb.Contains(bottomLeft) || bb.Contains(topRight);
}

bool BoundingBox::Contains(glm::vec2& point) 
{
	return point.x >= _min.x && point.x <= _max.x && point.y >= _min.y && point.y <= _max.y;
}

BoundingBox::~BoundingBox()
{
}
