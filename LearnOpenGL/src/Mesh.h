#ifndef MESH_H
#define MESH_H

#include <vector>

class Mesh
{
public:
	Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
	~Mesh();

	void Use() const;

private:
	unsigned int vboID;
	unsigned int vaoID;
	unsigned int eboID;
};

#endif

