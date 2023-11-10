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
	shader->Set("material.ambient", 1.0f, 0.5f, 0.31f);
	shader->Set("material.diffuse", 1.0f, 0.5f, 0.31f);
	shader->Set("material.specular", 0.5f, 0.5f, 0.5f);
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
