#include "RenderingContext.h"
#include "glm/gtc/matrix_transform.hpp"
#include <SDL_opengl.h>

using namespace glm;

RenderingContext::RenderingContext(int width, int height, ShaderProgram* shaders)
{
	_viewWidth = width;
	_viewHeight = height;
	_shaderProgram = shaders;

	_camera = new Camera(vec2(), vec2(1.0f), 0.0f);

	_projMatrix = ortho<float>(0, width, height, 0);
	_viewMatrix = _camera->CalculateViewMatrix();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderingContext::ApplyProjectionViewMatrices()
{
	_projMatrix = ortho<float>(0, _viewWidth, _viewHeight, 0);
	_viewMatrix = _camera->CalculateViewMatrix();

	_shaderProgram->Use();
	_shaderProgram->SetUniform("projMatrix", _projMatrix);
	_shaderProgram->SetUniform("viewMatrix", _viewMatrix);
}

void RenderingContext::SetModelMatrix(mat4 matrix)
{
	_shaderProgram->Use();
	_shaderProgram->SetUniform("modelMatrix", matrix);
}

int RenderingContext::GetViewWidth() const
{
	return _viewWidth;
}

int RenderingContext::GetViewHeight() const
{
	return _viewHeight;
}

void RenderingContext::SetShaders(ShaderProgram* shaders)
{
	_shaderProgram = shaders;
}

ShaderProgram* RenderingContext::GetShaders() const
{
	return _shaderProgram;
}

Camera* RenderingContext::GetCamera() const
{
	return _camera;
}

RenderingContext::~RenderingContext()
{
	delete _camera;
}
