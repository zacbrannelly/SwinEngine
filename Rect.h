#pragma once
#include "Shape.h"
class Rect : public Shape
{
protected:
	Rect(std::string name, glm::vec2 pos, float width, float height, ObjectType type);
public:
	Rect(std::string name, glm::vec2 pos, float width, float height);
	virtual ~Rect();

	virtual bool Load(ResourceManager* mgr) override;
	virtual void Render(RenderingContext* context, double interpolation) override;

	void SetColor(glm::vec4 color);
	void SetSize(float width, float height) override;

	void SetFilled(bool filled);
	bool IsFilled() const;

private:
	bool _isFilled;
};

