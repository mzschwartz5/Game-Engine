#include "Collider.h"
#include <glm/glm.hpp>
using glm::dvec3;
using glm::mat4;
using glm::mat3;
#include <vector>
using std::vector;


Collider::Collider(GameObject* const gameObject, const vector<dvec3>& points): 
	m_gameObject(gameObject), m_points(points), m_inverseRotation(glm::transpose(gameObject->rotation())) 
{
	if (gameObject == nullptr) throw "Invalid game object: null pointer";
}

// Default algorithm for calculating a furthest point in given direction (may be overriden for easy shapes like spheres)
dvec3 Collider::furthestPoint(const dvec3& direction) const {
	// First transform direction vector into collider-space by counter-rotating it using the (inverse) gameObject transform 
	dvec3 directionTransformed = m_inverseRotation * direction;
	
	// Initialize max distance calc starting with the first point
	dvec3 furthestPoint = m_points[0];
	double maxDistance = glm::dot(furthestPoint, directionTransformed);
	
	// Iterate over each point and compare its projected distance along directionTransformed. 
	for (int pointIdx = 1; pointIdx < m_points.size(); ++pointIdx) {
		double distance = glm::dot(m_points.at(pointIdx), directionTransformed);
		if (distance > maxDistance) {
			maxDistance = distance;
			furthestPoint = m_points.at(pointIdx);
		}
	}

	// Transform furthest point from model space into world space using game object's transform
	furthestPoint = m_gameObject->pointToWorldSpace(furthestPoint);

	return furthestPoint;
}

const dvec3 Collider::center() const {
	return m_gameObject->pointToWorldSpace(dvec3(0.0, 0.0, 0.0));
}