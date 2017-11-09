#include "BufferObject.h"
#include "GLExtensions.h"

using gle = GLExtensions;

BufferObject::BufferObject(unsigned int target) {
	_target = target;

	// Generate the buffer handle.
	auto glGenBuffers = (PFNGLGENBUFFERSPROC)gle::GetExtensionFunction("glGenBuffers");
	glGenBuffers(1, &_handle);
}

void BufferObject::UploadData(void* data, int size, unsigned int usage) {
	auto glBufferData = (PFNGLBUFFERDATAPROC)gle::GetExtensionFunction("glBufferData");
	glBufferData(_target, size, data, usage);
}

void BufferObject::UpdateData(const void* data, int offset, int size, unsigned int usage) {
	auto glBufferSubData = (PFNGLBUFFERSUBDATAPROC)gle::GetExtensionFunction("glBufferSubData");
	glBufferSubData(_target, offset, size, data);
}

void BufferObject::Bind() {
	auto glBindBuffer = (PFNGLBINDBUFFERPROC)gle::GetExtensionFunction("glBindBuffer");
	glBindBuffer(_target, _handle);
}

void BufferObject::Release()
{
	auto glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)gle::GetExtensionFunction("glDeleteBuffers");
	glDeleteBuffers(1, &_handle);
}

BufferObject::~BufferObject() {
	
}