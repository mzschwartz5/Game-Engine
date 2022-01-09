#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	void use() const;
	void setBool(const std::string&, bool) const;
	void setInt(const std::string&, int) const;
	void setFloat(const std::string&, float) const;
	void setMatrix(const std::string&, const glm::mat4&);

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif