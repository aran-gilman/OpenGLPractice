#ifndef SHADER_BUFFER_MANAGER_H
#define SHADER_BUFFER_MANAGER_H

#include <string>
#include <string_view>

class ShaderBufferManager
{
public:
	ShaderBufferManager(std::string name, unsigned int bindingPoint, unsigned int size);
	~ShaderBufferManager();

	std::string_view GetName() { return name; }
	unsigned int GetBindingPoint() const { return bindingPoint; }
	unsigned int GetID() const { return ID; }

	ShaderBufferManager(const ShaderBufferManager&) = delete;
	ShaderBufferManager& operator=(const ShaderBufferManager&) = delete;

private:
	std::string name;
	unsigned int ID;
	unsigned int bindingPoint;
};

#endif

