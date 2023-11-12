#include "Material.h"

#include <iostream>

#include "Shader.h"
#include "Texture.h"

Material::Material(std::shared_ptr<Shader> shader) : Material(shader, nullptr) {}

Material::Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture) : 
	shader(shader),
	textures(16)
{
	textures[0] = texture;
}

void Material::Use() const
{
	for (size_t i = 0; i < textures.size(); i++)
	{
		if (textures[i] != nullptr)
		{
			textures[i]->Use(i);
		}
		else
		{
			Texture::Reset(i);
		}
	}
	shader->Use();
}

Shader* Material::GetShader()
{
	return shader.get();
}

void Material::SetTexture(unsigned int textureUnit, std::shared_ptr<Texture> texture)
{
	if (textureUnit >= textures.size())
	{
		std::cerr << "Failed to set material texture: textureUnit must be less than " << textures.size() << ", but it was " << textureUnit << std::endl;
	}
	else
	{
		textures[textureUnit] = texture;
	}
}
