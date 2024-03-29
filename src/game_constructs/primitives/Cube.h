#ifndef CUBE_H
#define CUBE_H
#include "game_constructs/GameObject.h"
#include <glm/glm.hpp>
using glm::vec3;
using glm::dvec3;
#include "physics/Collider.h"

namespace Primitive {

	class Cube : public GameObject {
	public:
		Cube();
		Cube(const vec3& position);
	};

	class CubeCollider : public Collider {
	public:
		CubeCollider(GameObject* const gameObject);
	private:

	};

}
#endif