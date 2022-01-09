#ifndef MESH_H
#define MESH_H

#include "mesh.h"
#include "vertex.h"
#include "texture.h"
#include "Shader.h"
#include <vector>
using std::vector;

class Mesh {
public:
	Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<Texture>& textures);
	void Draw(const Shader& shader) const;
private:
	// Mesh data
	vector<Vertex> m_vertices;
	vector<unsigned int> m_indices;
	vector<Texture>& m_textures;

	// Render data (OpenGL objects)
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif 