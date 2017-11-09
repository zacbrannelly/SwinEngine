#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
	Circle(std::string name, glm::vec2 pos, float radius);
	~Circle();

	bool Load(ResourceManager* mgr) override;
	void Render(RenderingContext* context, double interpolation) override;

	void SetColor(glm::vec4 color);

	void SetRadius(float radius);
	float GetRadius() const;

	void SetFilled(bool filled);
	bool IsFilled() const;

private:
	float _radius;
	bool _isFilled;
};

