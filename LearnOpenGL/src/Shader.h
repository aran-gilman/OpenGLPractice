#ifndef SHADER_H
#define SHADER_H

#include <string_view>

class Shader
{
public:
	Shader(std::string_view vertexShaderCode, std::string_view fragmentShaderCode);
	~Shader();

	void Use() const;

	void Set(std::string_view name, bool value) const;
	void Set(std::string_view name, int value) const;
	void Set(std::string_view name, float value) const;
	void Set(std::string_view name, float value0, float value1, float value2) const;
	void Set(std::string_view name, float value0, float value1, float value2, float value3) const;

	void SetMatrix4(std::string_view name, const float* value) const;

private:
	int id;
};

#endif