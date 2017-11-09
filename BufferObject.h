#pragma once

class BufferObject {
public:
	BufferObject(unsigned int target);
	~BufferObject();

	void Bind();
	void UpdateData(const void* data, int offset, int size, unsigned int usage);
	void UploadData(void* data, int size, unsigned int usage);
	void Release();
private:
	unsigned int _handle;
	unsigned int _target;
};