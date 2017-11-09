#pragma once
#include "Shape.h"
class Line : public Shape
{
public:
	Line(std::string name, glm::vec2 start, glm::vec2 end);
	~Line();

	bool Load(ResourceManager* mgr) override;
	void Render(RenderingContext* context, double interpolation) override;

	void SetColor(glm::vec4 color);

	void SetStartPoint(glm::vec2 point);
	glm::vec2 GetStartPoint() const;

	void SetEndPoint(glm::vec2 point);
	glm::vec2 GetEndPoint() const;

	void SetPoints(glm::vec2 start, glm::vec2 end);
private:
	glm::vec2 _start, _end;
};

