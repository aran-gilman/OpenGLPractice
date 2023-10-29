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
	shader->Set("frustumScale", 1.0f);
	shader->Set("zNear", 1.0f);
	shader->Set("zFar", 3.0f);
}

Shader* Material::GetShader()
{
	return shader.get();
}
