#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader
{
public:
	Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
	~Shader();
	void Use();
	void Set(const std::string& name, bool value) const;
	void Set(const std::string& name, int value) const;
	void Set(const std::string& name, float value) const;
	void Set(const std::string& name, float value0, float value1, float value2) const;
	void Set(const std::string& name, float value0, float value1, float value2, float value3) const;

private:
	int id;
};

#endif