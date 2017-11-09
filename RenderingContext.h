#pragma once

#include "glm\glm.hpp"
#include "ShaderProgram.h"
#include "Camera.h"

class RenderingContext
{
public:
	RenderingContext(int width, int height, ShaderProgram* shaders);
	~RenderingContext();

	void SetModelMatrix(glm::mat4 matrix);

	int GetViewWidth() const;
	int GetViewHeight() const;

	void SetShaders(ShaderProgram* shaders);
	ShaderProgram* GetShaders() const;

	Camera* GetCamera() const;

	void ApplyProjectionViewMatrices();
private:
	glm::mat4 _projMatrix, _viewMatrix; 
	int _viewWidth, _viewHeight;
	ShaderProgram* _shaderProgram;
	Camera* _camera;
};

