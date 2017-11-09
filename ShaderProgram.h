#pragma once

#include <string>
#include "glm\glm.hpp"
#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram(Shader* vert, Shader* frag);
	~ShaderProgram();

	bool Create();
	bool Link();
	bool IsLinked() const;

	void SetVertexShader(Shader* shader);
	void SetFragmentShader(Shader* shader);
	Shader* GetVertexShader() const;
	Shader* GetFragmentShader() const;

	void Use();
	
	void SetUniform(std::string name, glm::vec2 value);
	void SetUniform(std::string name, glm::mat4 value);
	void SetUniform(std::string name, int value);
	void SetUniform(std::string name, float value);
	void SetSubroutine(unsigned int targetShader, std::string name);
private:
	int _handle;
	bool _isLinked;
	Shader *_vertShader, *_fragShader;

	unsigned int GetUniformLocation(std::string name);
};

