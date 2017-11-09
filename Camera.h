#pragma once

#include "glm\glm.hpp"

class Camera
{
public:
	Camera(glm::vec2 pos, glm::vec2 scale, float angle);
	~Camera();

	void Translate(glm::vec2 pos);
	glm::vec2 GetPosition() const;

	void Scale(glm::vec2 scale);
	glm::vec2 GetScale() const;

	void Rotate(float angle);
	float GetRotation() const;

	glm::mat4 CalculateViewMatrix();
private:
	glm::vec2 _position, _scale;
	float _rotation;
};

