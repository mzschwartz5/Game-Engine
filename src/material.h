#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "texture.h"
#include <vector>
using std::vector;

class Material {
public:
	Material(Shader& shader, const vector<Texture>& textures);
	Shader& getShader();
	void activateTextures();
private:
	Shader& m_shader;
	const vector<Texture>& m_textures;
};

#endif