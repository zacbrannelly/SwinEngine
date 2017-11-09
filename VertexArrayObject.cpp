#include "VertexArrayObject.h"
#include "GLExtensions.h"

using gle = GLExtensions;

VertexArrayObject::VertexArrayObject()
{
	auto glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)gle::GetExtensionFunction("glGenVertexArrays");
	glGenVertexArrays(1, &_handle);
}

void VertexArrayObject::Bind()
{
	auto glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)gle::GetExtensionFunction("glBindVertexArray");
	glBindVertexArray(_handle);
}

void VertexArrayObject::BindBufferToVertexAttrib(BufferObject* buffer, int index, int size, unsigned int type)
{
	Bind();
	buffer->Bind();

	auto glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)gle::GetExtensionFunction("glVertexAttribPointer");
	glVertexAttribPointer(index, size, type, GL_FALSE, 0, NULL);
}

void VertexArrayObject::EnableVertexAttrib(int index)
{
	auto glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)gle::GetExtensionFunction("glEnableVertexAttribArray");
	glEnableVertexAttribArray(index);
}

void VertexArrayObject::DisableVertexAttrib(int index)
{
	auto glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)gle::GetExtensionFunction("glDisableVertexAttribArray");
	glDisableVertexAttribArray(index);
}

void VertexArrayObject::Release()
{
	auto glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)gle::GetExtensionFunction("glDeleteVertexArrays");
	glDeleteVertexArrays(1, &_handle);
}

VertexArrayObject::~VertexArrayObject()
{
}
