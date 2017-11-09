#pragma once
#include "Rect.h"
class Sprite :
	public Rect
{
public:
	Sprite(std::string name, glm::vec2 position, std::string path);
	Sprite(std::string name, glm::vec2 position, Texture* texture);
	~Sprite();

	bool Load(ResourceManager* mgr) override;
	void Render(RenderingContext* context, double interpolation) override;

	void SetSourceRect(float x, float y, float width, float height);
	BoundingBox GetSourceRect() const;

	void SetTexture(Texture* texture);
	Texture* GetTexture() const;

private:
	Texture* _texture;
	BoundingBox _sourceRect;
	std::string _path;
};

