#include "MapObject.h"
#include "glm\gtc\matrix_transform.hpp"

using namespace std;
using namespace glm;

MapObject::MapObject(string name, vec2 pos, float width, float height, ObjectType type)
{
	_name = name;
	_position = pos;
	_width = width;
	_height = height;
	_type = type;

	_velocity = vec2(0, 0);
	_acceleration = vec2(0, 0);
	_angularAcceleration = 0.0f;
	_angularVelocity = 0.0f;
	_rotation = 0.0f;
	_origin = vec2(0 ,0);
	_scale = vec2(1.0f);

	_bb.Calculate(pos, width, height);
}

void MapObject::Update()
{
	// Update the objects motion
	_velocity += _acceleration;
	_position += _velocity;

	// Update the objects angular motion
	_angularVelocity += _angularAcceleration;
	_rotation += _angularVelocity;

	// Update the position for the bounding box
	_bb.SetPosition(_position);
}

void MapObject::Render(RenderingContext* context, double interpolation)
{
	// Interpolate angular motion
	float tempAngularVel = _angularVelocity + _angularAcceleration * interpolation;
	float tempRotation = _rotation + tempAngularVel * interpolation;

	// Interpolate motion
	auto tempVel = _velocity + _acceleration * vec2(interpolation);
	auto tempPosition = _position + tempVel * vec2(interpolation);

	// Calculate model matrix from interpolated position and rotation
	auto modelMatrix = CalculateModelMatrix(tempPosition, tempRotation);

	// apply the model matrix to the shader
	context->SetModelMatrix(modelMatrix);
}

mat4 MapObject::CalculateModelMatrix(glm::vec2 interpolatedPosition, float interpolatedRotation) const
{
	mat4 matrix(1.0f);
	matrix = translate(matrix, vec3(interpolatedPosition, 0.0f));
	matrix = scale(matrix, vec3(_scale, 1.0f));
	matrix = translate(matrix, vec3(_origin, 0.0f));
	matrix = rotate(matrix, interpolatedRotation, vec3(0, 0, 1.0f));
	matrix = translate(matrix, vec3(-_origin.x, -_origin.y, 0.0f));

	return matrix;
}

void MapObject::SetName(string name)
{
	_name = name;
}

string MapObject::GetName() const
{
	return _name;
}

void MapObject::SetPosition(vec2 position)
{
	_position = position;
	_bb.SetPosition(_position);
}

vec2 MapObject::GetPosition() const
{
	return _position;
}

void MapObject::SetSize(float w, float h)
{
	_width = w;
	_height = h;

	_bb.Calculate(_position, w, h);
}

float MapObject::GetWidth() const
{
	return _width;
}

float MapObject::GetHeight() const
{
	return _height;
}

void MapObject::SetOrigin(glm::vec2 origin)
{
	_origin = origin;
}

vec2 MapObject::GetOrigin() const
{
	return _origin;
}

void MapObject::SetAngle(float angle)
{
	_rotation = angle;
}

float MapObject::GetAngle() const
{
	return _rotation;
}

void MapObject::SetScale(glm::vec2 scale)
{
	_scale = scale;
}

vec2 MapObject::GetScale() const
{
	return _scale;
}

void MapObject::SetBoundingBox(BoundingBox bb)
{
	_bb = bb;
}

BoundingBox MapObject::GetBoundingBox() const
{
	return _bb;
}

void MapObject::SetAcceleration(glm::vec2 accel)
{
	_acceleration = accel;
}

vec2 MapObject::GetAcceleration() const
{
	return _acceleration;
}

void MapObject::SetVelocity(glm::vec2 vel)
{
	_velocity = vel;
}

vec2 MapObject::GetVelocity() const
{
	return _velocity;
}

void MapObject::SetAngularAcceleration(float accel)
{
	_angularAcceleration = accel;
}

float MapObject::GetAngularAcceleration() const
{
	return _angularAcceleration;
}


void MapObject::SetAngularVelocity(float vel)
{
	_angularVelocity = vel;
}

float MapObject::GetAngularVelocity() const
{
	return _angularVelocity;
}

MapObject::~MapObject()
{
}
