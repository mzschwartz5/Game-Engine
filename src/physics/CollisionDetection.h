#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "Collider.h"
#include <glm/glm.hpp>
using glm::dvec3;
#include <vector>
using std::vector;

namespace Physics {

	// Collision detection algorithms
	bool GJK(const Collider& c1, const Collider& c2);
	bool simplexContainsOrigin(vector<dvec3>& simplex, dvec3& direction);
	bool lineContainsOrigin(vector<dvec3>& simplex, dvec3& direction);
	bool triangleContainsOrigin(vector<dvec3>& simplex, dvec3& direction);
	bool tetrahedronContainsOrigin(vector<dvec3>& simplex, dvec3& direction);
	dvec3 tripleProduct(dvec3& v1, dvec3& v2, dvec3& v3);
	bool sameDirection(dvec3& v1, dvec3& v2);
	dvec3 support(const Collider& c1, const Collider& c2, const dvec3& direction);
}

#endif