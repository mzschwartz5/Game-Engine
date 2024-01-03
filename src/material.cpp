#include "material.h"
#include "Shader.h"
#include "texture.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

Material::Material(Shader& shader, const vector<Texture>& textures) : m_shader(shader), m_textures(textures) {
}

Shader& Material::getShader() {
	return m_shader;
}

void Material::activateTextures()
{	// Activate and bind all textures before drawing
	for (int i = 0; i < m_textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		m_shader.setValue(m_textures[i].getName(), i);
		m_textures[i].Bind(GL_TEXTURE_2D);
	}
	glActiveTexture(GL_TEXTURE0);
}


