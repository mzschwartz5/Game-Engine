#ifndef COLLIDER_H
#define COLLIDER_H
#include <glm/glm.hpp>
using glm::dvec3;
using glm::mat4;
using glm::mat3;
#include <vector>
using std::vector;
#include "game_constructs/GameObject.h"

class Collider {
public:
	virtual dvec3 furthestPoint(const dvec3& direction) const; // used by support function for GJK collision detection
	const dvec3 center() const;

protected:
	GameObject* m_gameObject{ nullptr };
	const vector<dvec3> m_points;
	Collider(GameObject* const gameObject, const vector<dvec3>& points);


private:
	mat3 m_inverseRotation; // the 3x3 rotation (inverted) of the parent game object
};

#endif