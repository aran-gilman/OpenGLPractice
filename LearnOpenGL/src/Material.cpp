#include "Material.h"

#include "Shader.h"
#include "Texture.h"

Material::Material(std::shared_ptr<Shader> shader) : Material(shader, nullptr) {}

Material::Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture) : shader(shader), texture(texture) {}

void Material::Use() const
{
	if (texture != nullptr)
	{
		texture->Use();
	}
	shader->Use();
}

void Material::Reset() const
{
	if (texture != nullptr)
	{
		texture->Reset();
	}
}

Shader* Material::GetShader()
{
	return shader.get();
}
