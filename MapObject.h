#pragma once

#include <string>
#include "BoundingBox.h"
#include "glm\glm.hpp"
#include "ResourceManager.h"
#include "RenderingContext.h"

enum ObjectType
{
	RectangleObject, CircleObject, LineObject, SpriteObject, UnknownObject
};

class MapObject
{
public:
	MapObject(std::string name, glm::vec2 pos, float width, float height, ObjectType type);
	virtual ~MapObject();

	virtual bool Load(ResourceManager* mgr) = 0;
	void Update();
	virtual void Render(RenderingContext* context, double interpolation);

	void SetName(std::string name);
	std::string GetName() const;

	void SetPosition(glm::vec2 pos);
	glm::vec2 GetPosition() const;

	virtual void SetSize(float w, float h);
	float GetWidth() const;
	float GetHeight() const;

	void SetOrigin(glm::vec2 origin);
	glm::vec2 GetOrigin() const;

	void SetAngle(float angle);
	float GetAngle() const;

	void SetScale(glm::vec2 scale);
	glm::vec2 GetScale() const;

	void SetBoundingBox(BoundingBox bb);
	BoundingBox GetBoundingBox() const;

	void SetAcceleration(glm::vec2 accel);
	glm::vec2 GetAcceleration() const;

	void SetVelocity(glm::vec2 vel);
	glm::vec2 GetVelocity() const;

	void SetAngularAcceleration(float accel);
	float GetAngularAcceleration() const;

	void SetAngularVelocity(float vel);
	float GetAngularVelocity() const;

	glm::mat4 CalculateModelMatrix(glm::vec2 interpolatedPosition, float interpolatedRotation) const;

	template<typename T>
	T* CastTo() 
	{
		return static_cast<T*>(this);
	}

	virtual void Release() = 0;
private:
	std::string _name;
	glm::vec2 _position, _origin, _scale, _acceleration, _velocity;
	float _width, _height;
	float _angularAcceleration, _angularVelocity;
	float _rotation;
	BoundingBox _bb;
	ObjectType _type;
};

