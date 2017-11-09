#pragma once
#include "MapObject.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"

#define VERTEX_ID 0
#define COLOR_ID 1
#define TEXTURE_COORDS_ID 2

class Shape : public MapObject
{
public:
	Shape(std::string name, glm::vec2 pos, float width, float height, ObjectType type);
	virtual ~Shape();

	void SetVertices(void* data, int size);
	void SetColors(void* data, int size);
	void SetTextureCoords(void* data, int size);
	void SetIndices(void* data, int size);

	BufferObject* GetVertexBuffer() const;
	BufferObject* GetColorBuffer() const;
	BufferObject* GetTextureCoordsBuffer() const;
	BufferObject* GetIndexBuffer() const;
	VertexArrayObject* GetVertexArrayObject() const;

	virtual bool Load(ResourceManager* mgr) override;
	virtual void Render(RenderingContext* context, double interpolation) override;
	virtual void Release() override;
private:
	BufferObject* _vertexBuffer;
	BufferObject* _colorBuffer;
	BufferObject* _texCoordBuffer;
	BufferObject* _indexBuffer;
	VertexArrayObject* _vertexArrayObj;
};

