#include "Camera.h"
#include "glm\gtc\matrix_transform.hpp"

using namespace glm;

Camera::Camera(vec2 pos, vec2 scale, float angle)
{
	_position = pos;
	_scale = scale;
	_rotation = angle;
}

mat4 Camera::CalculateViewMatrix()
{
	mat4 viewMatrix(1.0f);

	viewMatrix = rotate(viewMatrix, _rotation, vec3(0, 0, 1));
	viewMatrix = translate(viewMatrix, vec3(_position, 0) * vec3(-1));
	viewMatrix = scale(viewMatrix, vec3(_scale, 1.0f));

	return viewMatrix;
}

void Camera::Translate(vec2 pos)
{
	_position = pos;
}

vec2 Camera::GetPosition() const
{
	return _position;
}

void Camera::Scale(vec2 scale)
{
	_scale = scale;
}

vec2 Camera::GetScale() const
{
	return _scale;
}

void Camera::Rotate(float angle)
{
	_rotation = angle;
}

float Camera::GetRotation() const
{
	return _rotation;
}

Camera::~Camera()
{
}
