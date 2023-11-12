#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <string_view>
#include <vector>

class Shader;
class Texture;

class Material
{
public:
	Material(std::shared_ptr<Shader> shader);
	Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

	void Use() const;

	Shader* GetShader();
	void SetTexture(unsigned int textureUnit, std::shared_ptr<Texture> texture);

private:
	// We use shared_ptr in order to keep shader and texture alive for as long as any material exists that uses them
	// One thing to consider: in multi-threaded contexts, is it safe to share shaders like this? (e.g. would setting uniforms cause problems?)
	const std::shared_ptr<Shader> shader;
	std::vector<std::shared_ptr<Texture>> textures;
};

#endif

