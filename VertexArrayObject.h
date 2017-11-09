#pragma once

#include "BufferObject.h"

class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();

	void Bind();
	void BindBufferToVertexAttrib(BufferObject* buffer, int index, int size, unsigned int type);
	void EnableVertexAttrib(int index);
	void DisableVertexAttrib(int index);
	void Release();

private:
	unsigned int _handle;
};

