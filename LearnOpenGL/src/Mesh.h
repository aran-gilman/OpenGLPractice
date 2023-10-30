#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};

class Mesh
{
public:
	static Mesh MakeCube();

	Mesh(const std::vector<Vertex>& vertices);
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	~Mesh();

	void Draw() const;

private:
	unsigned int vboID;
	unsigned int vaoID;
	unsigned int eboID;

	int drawCount;
};

#endif

