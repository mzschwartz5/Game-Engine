#include "mesh.h"
#include "Shader.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Mesh::Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<Texture>& textures)
	: m_vertices(vertices), m_indices(indices), m_textures(textures) {

	setupMesh();
}

void Mesh::Draw(const Shader& shader) const {
	
	// Activate and bind all textures before drawing
	for (unsigned int i = 0; i < m_textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		shader.setInt(m_textures[i].getName(), i);
		m_textures[i].Bind(GL_TEXTURE_2D);
	}
	glActiveTexture(GL_TEXTURE0);
	
	// Draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0); // DRAW
	glBindVertexArray(0); // unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind
}

void Mesh::setupMesh() {
	// Generate buffer object identifiers
	glGenVertexArrays(1, &VAO); // (VAO stores VBO and EBO along with metadata about each)
	glGenBuffers(1, &VBO);		// (VBO stores actual vertex positions in NDC space)
	glGenBuffers(1, &EBO);		// (EBO stores vertex indices)

	// Bind to OpenGL state so we can use them
	glBindVertexArray(VAO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Set data to now-bound arrays
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW); // sets to VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW); // sets to EBO

	// Dictate how to interpret vertex data (which attributes are where, in the array)
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// Vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_normal));
	// Vertex texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_texCoords));

	// Unbind VAO until use
	glBindVertexArray(0);
}	