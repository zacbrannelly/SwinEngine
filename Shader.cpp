#include <iostream>
#include <fstream>
#include "Shader.h"
#include "GLExtensions.h"

using namespace std;

Shader::Shader(string source, unsigned int type)
{
	_source = source;
	_type = type;
	_compiled = false;
	_handle = -1;
}

bool Shader::Compile()
{
	auto glCreateShader = (PFNGLCREATESHADERPROC)GLExtensions::GetExtensionFunction("glCreateShader");
	auto glCompileShader = (PFNGLCOMPILESHADERPROC)GLExtensions::GetExtensionFunction("glCompileShader");
	auto glShaderSource = (PFNGLSHADERSOURCEPROC)GLExtensions::GetExtensionFunction("glShaderSource");
	auto glGetShaderiv = (PFNGLGETSHADERIVPROC)GLExtensions::GetExtensionFunction("glGetShaderiv");
	auto glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GLExtensions::GetExtensionFunction("glGetShaderInfoLog");

	if (!glCreateShader || !glCompileShader)
	{
		cout << "Failed to get OpenGL extensions!" << endl;
		return false;
	}

	_handle = glCreateShader(_type);

	// Upload the shader source code
	const char* source = _source.c_str();
	glShaderSource(_handle, 1, &source, NULL);

	glCompileShader(_handle);

	// Check if it compiled successfully
	int success = 0;
	glGetShaderiv(_handle, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		int maxSize = 0;
		glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &maxSize);

		char* log = new char[maxSize];
		glGetShaderInfoLog(_handle, maxSize, &maxSize, log);

		cout << "Shader Error: " << log << endl;

		delete[] log;
	}

	_compiled = success == GL_TRUE;

	return _compiled;
}

void Shader::SetSource(string source)
{
	_source = source;
}

string Shader::GetSource() const
{
	return _source;
}

bool Shader::IsCompiled() const
{
	return _compiled;
}

int Shader::GetHandle() const
{
	return _handle;
}

Shader* Shader::FromFile(string path, unsigned int type)
{
	ifstream in(path.c_str());
		
	if (in.is_open())
	{
		string contents;
		string line;
		while (!in.eof())
		{
			getline(in, line);
			contents.append(line + "\n");
		}

		in.close();

		return new Shader(contents, type);
	}

	return NULL;
}

Shader::~Shader()
{
	
}
