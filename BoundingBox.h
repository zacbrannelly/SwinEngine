#pragma once

#include "glm\glm.hpp"

class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(glm::vec2 min, glm::vec2 max);
	BoundingBox(glm::vec2 pos, float w, float h);
	~BoundingBox();

	void SetMin(glm::vec2 min);
	glm::vec2 GetMin() const;

	void SetMax(glm::vec2 max);
	glm::vec2 GetMax() const;

	void Calculate(glm::vec2 pos, float width, float height);

	void SetWidth(float width);
	float GetWidth() const;

	void SetHeight(float height);
	float GetHeight() const;

	void SetPosition(glm::vec2 pos);
	glm::vec2 GetPosition() const;

	bool Intersects(BoundingBox& bb);
	bool Contains(glm::vec2& point);
private:
	glm::vec2 _min, _max;
};

