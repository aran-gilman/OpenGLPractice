#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

class Shader;
class Texture;

class Material
{
public:
	Material(std::shared_ptr<Shader> shader);
	Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

	void Use() const;
	void Reset() const;

	Shader* GetShader();

private:
	// We use shared_ptr in order to keep shader and texture alive for as long as any material exists that uses them
	// One thing to consider: in multi-threaded contexts, is it safe to share shaders like this? (e.g. would setting uniforms cause problems?)
	const std::shared_ptr<Shader> shader;
	const std::shared_ptr<Texture> texture;
};

#endif

