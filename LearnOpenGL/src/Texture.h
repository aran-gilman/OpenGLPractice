#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void Use() const;

private:
	unsigned int id;
};

#endif

