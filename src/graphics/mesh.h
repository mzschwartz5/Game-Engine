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
	Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices);
	void Draw() const;
private:
	// Mesh data
	vector<Vertex> m_vertices;
	vector<unsigned int> m_indices;

	// Render data (OpenGL objects)
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif 