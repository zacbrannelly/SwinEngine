#include "ShaderProgram.h"
#include <iostream>
#include "GLExtensions.h"

using namespace std;

ShaderProgram::ShaderProgram(Shader* vert, Shader* frag)
{
	_vertShader = vert;
	_fragShader = frag;

	_isLinked = false;
	_handle = -1;
}

bool ShaderProgram::Create()
{
	auto glCreateProgram = (PFNGLCREATEPROGRAMPROC)GLExtensions::GetExtensionFunction("glCreateProgram");
	
	if (!glCreateProgram)
	{
		cout << "Failed to load OpenGL extensions!" << endl;
		return false;
	}

	_handle = glCreateProgram();

	if (!_handle)
	{
		cout << "Failed to create the shader program!" << endl;
		return false;
	}

	return true;
}

bool ShaderProgram::Link()
{
	if (!_vertShader || !_fragShader)
	{
		cout << "Can't link the program with no shaders!" << endl;
		return false;
	}

	auto glAttachShader = (PFNGLATTACHSHADERPROC)GLExtensions::GetExtensionFunction("glAttachShader");
	auto glLinkProgram = (PFNGLLINKPROGRAMPROC)GLExtensions::GetExtensionFunction("glLinkProgram");
	auto glGetProgramiv = (PFNGLGETPROGRAMIVPROC)GLExtensions::GetExtensionFunction("glGetProgramiv");

	if (!glAttachShader || !glLinkProgram || !glGetProgramiv)
	{
		cout << "Failed to load OpenGL extensions!" << endl;
		return false;
	}

	// if not both compiled, then try to compile, return false on failure
	if ((!_vertShader->IsCompiled() && !_fragShader->IsCompiled()) 
		&& (!_vertShader->Compile() || !_fragShader->Compile()))
		return false;

	glAttachShader(_handle, _vertShader->GetHandle());
	glAttachShader(_handle, _fragShader->GetHandle());

	glLinkProgram(_handle);

	int status = 0;
	glGetProgramiv(_handle, GL_LINK_STATUS, &status);

	_isLinked = status == GL_TRUE;

	return _isLinked;
}

bool ShaderProgram::IsLinked() const
{
	return _isLinked;
}

void ShaderProgram::Use()
{
	auto glUseProgram = (PFNGLUSEPROGRAMPROC)GLExtensions::GetExtensionFunction("glUseProgram");

	if (!glUseProgram)
	{
		cout << "Failed to load OpenGL extensions!" << endl;
		return;
	}

	glUseProgram(_handle);
}

unsigned int ShaderProgram::GetUniformLocation(std::string name)
{
	auto glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)GLExtensions::GetExtensionFunction("glGetUniformLocation");

	return glGetUniformLocation(_handle, name.c_str());
}

void ShaderProgram::SetUniform(std::string name, glm::vec2 value)
{
	auto glUniform2fv = (PFNGLUNIFORM2FVPROC)GLExtensions::GetExtensionFunction("glUniform2fv");
	auto location = GetUniformLocation(name);
	glUniform2fv(location, 1, &value[0]);
}

void ShaderProgram::SetUniform(std::string name, glm::mat4 value)
{
	auto glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)GLExtensions::GetExtensionFunction("glUniformMatrix4fv");
	auto location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetUniform(std::string name, int value)
{
	auto glUniform1i = (PFNGLUNIFORM1IPROC)GLExtensions::GetExtensionFunction("glUniform1i");
	auto location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void ShaderProgram::SetUniform(std::string name, float value)
{
	auto glUniform1f = (PFNGLUNIFORM1FPROC)GLExtensions::GetExtensionFunction("glUniform1f");
	auto location = GetUniformLocation(name);
	glUniform1f(location, value);
}

void ShaderProgram::SetSubroutine(unsigned int targetShader, std::string name)
{
	auto glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)GLExtensions::GetExtensionFunction("glGetSubroutineIndex");
	auto glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)GLExtensions::GetExtensionFunction("glUniformSubroutinesuiv");

	auto index = glGetSubroutineIndex(_handle, targetShader, name.c_str());
	glUniformSubroutinesuiv(targetShader, 1, &index);
}

void ShaderProgram::SetVertexShader(Shader* shader)
{
	_vertShader = shader;
}

void ShaderProgram::SetFragmentShader(Shader* shader)
{
	_fragShader = shader;
}

Shader* ShaderProgram::GetVertexShader() const
{
	return _vertShader;
}

Shader* ShaderProgram::GetFragmentShader() const
{
	return _fragShader;
}
ShaderProgram::~ShaderProgram()
{
}
