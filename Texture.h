#pragma once

enum Quality
{
	Linear, NearestNeighbour
};

class Texture
{
public:
	Texture(unsigned int handle, int width, int height);
	~Texture();

	void Bind();
	void Unbind();
	void UploadData(void* data, int mode, unsigned int type);
	void Release();

	void SetQuality(Quality quality);
	Quality GetQuality() const;

	int GetWidth() const;
	int GetHeight() const;

	void ClampToEdge();

	static Texture* GenerateEmpty(int width, int height);
private:
	unsigned int _handle;
	int _width, _height;
	Quality _quality;
};

