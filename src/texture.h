#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h> 
using std::string;

class Texture {
public:
	Texture(const char* path, const char* name, bool hasAlpha);
	void Bind(GLenum target) const; // bind Texture to appropriate OpenGL var for drawing
	const char* getName() const;
private:
	unsigned int m_id;
	const char* m_name;
};

#endif // !TEXTURE_H
