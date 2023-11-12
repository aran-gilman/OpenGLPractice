#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
	static void Reset(unsigned int textureUnit);

	Texture(const std::string& path);
	~Texture();

	void Use(unsigned int textureUnit) const;

private:
	unsigned int id;
};

#endif

