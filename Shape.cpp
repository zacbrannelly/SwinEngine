#include "Shape.h"
#include <SDL_opengl.h>

using namespace glm;
using namespace std;

Shape::Shape(string name, vec2 pos, float width, float height, ObjectType type) : MapObject(name, pos, width, height, type)
{
	_vertexBuffer = new BufferObject(GL_ARRAY_BUFFER);
	_colorBuffer = new BufferObject(GL_ARRAY_BUFFER);
	_texCoordBuffer = new BufferObject(GL_ARRAY_BUFFER);
	_indexBuffer = new BufferObject(GL_ELEMENT_ARRAY_BUFFER);
	_vertexArrayObj = new VertexArrayObject();
}

void Shape::SetVertices(void* data, int size)
{
	_vertexBuffer->Bind();
	_vertexBuffer->UploadData(data, size, GL_STATIC_DRAW);
}

void Shape::SetColors(void* data, int size)
{
	_colorBuffer->Bind();
	_colorBuffer->UploadData(data, size, GL_STATIC_DRAW);
}

void Shape::SetTextureCoords(void* data, int size)
{
	_texCoordBuffer->Bind();
	_texCoordBuffer->UploadData(data, size, GL_STATIC_DRAW);
}

void Shape::SetIndices(void* data, int size)
{
	_indexBuffer->Bind();
	_indexBuffer->UploadData(data, size, GL_STATIC_DRAW);
}

bool Shape::Load(ResourceManager* mgr)
{
	_vertexArrayObj->Bind();

	_vertexArrayObj->EnableVertexAttrib(VERTEX_ID);
	_vertexArrayObj->EnableVertexAttrib(COLOR_ID);
	_vertexArrayObj->EnableVertexAttrib(TEXTURE_COORDS_ID);

	_vertexArrayObj->BindBufferToVertexAttrib(_vertexBuffer, VERTEX_ID, 2, GL_FLOAT);
	_vertexArrayObj->BindBufferToVertexAttrib(_colorBuffer, COLOR_ID, 4, GL_FLOAT);
	_vertexArrayObj->BindBufferToVertexAttrib(_texCoordBuffer, TEXTURE_COORDS_ID, 2, GL_FLOAT);

	return true;
}

void Shape::Render(RenderingContext* context, double interpolation)
{
	MapObject::Render(context, interpolation);

	_vertexArrayObj->Bind();
}

BufferObject* Shape::GetVertexBuffer() const
{
	return _vertexBuffer;
}

BufferObject* Shape::GetColorBuffer() const
{
	return _colorBuffer;
}

BufferObject* Shape::GetTextureCoordsBuffer() const
{
	return _texCoordBuffer;
}

BufferObject* Shape::GetIndexBuffer() const
{
	return _indexBuffer;
}

VertexArrayObject* Shape::GetVertexArrayObject() const
{
	return _vertexArrayObj;
}

void Shape::Release()
{
	_vertexBuffer->Release();
	_colorBuffer->Release();
	_texCoordBuffer->Release();
	_indexBuffer->Release();
	_vertexArrayObj->Release();
}

Shape::~Shape()
{
	delete _vertexArrayObj;
	delete _vertexBuffer;
	delete _colorBuffer;
	delete _texCoordBuffer;
	delete _indexBuffer;
}
