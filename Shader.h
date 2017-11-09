#pragma once

#include <string>

class Shader
{
public:
	Shader(std::string source, unsigned int type);
	~Shader();

	bool Compile();

	void SetSource(std::string source);
	std::string GetSource() const;

	bool IsCompiled() const;
	int GetHandle() const;

	static Shader* FromFile(std::string path, unsigned int type);
private:
	std::string _source;
	unsigned int _type;
	int _handle;
	bool _compiled;
};

