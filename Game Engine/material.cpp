#include "material.h"
#include "Shader.h"
#include "texture.h"

Material::Material(Shader& shader, const vector<Texture>& textures) : m_shader(shader), m_textures(textures) {
}

Shader& Material::getShader() {
	return m_shader;
}


