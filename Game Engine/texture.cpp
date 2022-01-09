#include "texture.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>

Texture::Texture(const char* path, const char* name, bool hasAlpha): m_name(name) {

	// Generate texture ID and bind to GL_TEXTURE_2D
	glGenTextures(1, &m_id);
	Bind(GL_TEXTURE_2D);

	// Set texture wrapping / filtering options (on the currently bound object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load and generate the texture
	int width, height, nrChannels;

	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, (hasAlpha ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0); // unbind texture for now - rebind when using.
}

void Texture::Bind(GLenum target) const{
	glBindTexture(target, m_id);
}

const char* Texture::getName() const{
	return m_name;
}