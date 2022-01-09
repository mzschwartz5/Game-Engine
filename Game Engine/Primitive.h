#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "GameObject.h"
#include <glm/glm.hpp>
using glm::vec3;

namespace Primitive {

	class Cube : public GameObject {
	public:
		Cube();
		Cube(const vec3& position);
	};

}
#endif