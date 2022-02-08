#include "CollisionDetection.h"
#include "Collider.h"
#include <glm/glm.hpp>
using glm::vec3;
using glm::dvec3;
#include <vector>
using std::vector;
#include "constants.h"
using Constants::ORIGIN;
#include <glm/gtx/norm.hpp>
#include <math.h>

namespace Physics {

	const int MAX_ITERATIONS = 100;
	const double COLLISION_TOLERANCE = 0.00000001; // alter as needed
	enum class SimplexType {
		Line = 2,
		Triangle = 3,
		Tetrahedron = 4
	};

	bool GJK(const Collider& c1, const Collider& c2) {
		// Initialize seed for algorithm
		dvec3 direction = c1.center() - c2.center();
		vector<dvec3> simplex{ support(c1, c2, direction) };

		// Search towards origin
		direction = ORIGIN - simplex[0];
		for (int i = 0; i < MAX_ITERATIONS; ++i) {

			dvec3 A = support(c1, c2, direction);		     // Next point to try in minkowski difference
			if (!sameDirection(A, direction)) return false;  // Point A does not pass Origin in direction d; minkowski diff cannot contain origin.
			simplex.push_back(A);
			
			if (simplexContainsOrigin(simplex, direction)) return true; // Objects are in collision; otherwise try new point with updated direction.
		}

		throw "GJK Algorithm: Maximum iterations exceeded, did not converge to answer";
		return false;
	};

	dvec3 support(const Collider& c1, const Collider& c2, const dvec3& direction) {
		return c1.furthestPoint(direction) - c2.furthestPoint(-direction);
	}

	inline bool simplexContainsOrigin(vector<dvec3>& simplex, dvec3& direction) {
		switch (simplex.size()) {
			case static_cast<int>(SimplexType::Line):
				return lineContainsOrigin(simplex, direction);

			case static_cast<int>(SimplexType::Triangle):
				return triangleContainsOrigin(simplex, direction);

			case static_cast<int>(SimplexType::Tetrahedron):
				return tetrahedronContainsOrigin(simplex, direction);
		}
		return false;
	};

	inline bool lineContainsOrigin(vector<dvec3>& simplex_IO, dvec3& direction_out) {
		dvec3 AB = simplex_IO.front() - simplex_IO.back(); // B - A
		dvec3 AO = ORIGIN - simplex_IO.back();			   // O - A
		direction_out = tripleProduct(AB, AO, AB);         // AB-perpendicular (coplanar with O)
		
		return (glm::length2(direction_out) < COLLISION_TOLERANCE); // if line contains origin, squared magnitude of triple product will be 0 (within numerical precision) 
	}

	inline bool triangleContainsOrigin(vector<dvec3>& simplex_IO, dvec3& direction_out) {
		dvec3 AB = simplex_IO.at(1) - simplex_IO.back();    // B - A
		dvec3 AC = simplex_IO.front() - simplex_IO.back();  // C - A
		dvec3 AO = ORIGIN - simplex_IO.back();				// O - A 
		dvec3 ABCPerp = glm::cross(AB, AC);					// Perpedicular to plane of triangle ABC

		// Origin lies in region AB (covers cases where Origin is above or below plane)
		dvec3 ABPerp = tripleProduct(AC, AB, AB);	   // Perpendicular to AB and coplanar with triangle ABC
		if (sameDirection(ABPerp, AO)) {

			direction_out = tripleProduct(AB, AO, AB); // Perpendicular to AB and coplanar with triangle ABO
			// Origin is in region AB, but is coplanar with triangle - remove point C so we can try for a better triangle next iteration
			if (!sameDirection(direction_out, ABCPerp)) {
				simplex_IO.erase(simplex_IO.begin());
			}
			
			return false; // Origin is in region AB, and is NOT coplanar with triangle, so we move onto tetrahedral tests.
		}
		// Origin lies in region AC (works if above or below plane too)
		dvec3 ACPerp = tripleProduct(AB, AC, AC);	// Perpendicular to AC and coplanar with triangel ABC
		if (sameDirection(ACPerp, AO)) {			

			direction_out = tripleProduct(AC, AO, AC);
			// Origin is in region AC, but is coplanar with triangle - remove point B so we can try for a better triangle next iteration
			if (!sameDirection(direction_out, ABCPerp)) {
				simplex_IO.erase(simplex_IO.begin() + 1);
			}

			return false; // Origin is in region AC, and is NOT coplanar with triangle, so we move onto tetrahedral cases
		}
		
		// Origin lies in region ABC (but TBD if above or below plane of triangle)
		double ABCPerpDotAO = sameDirection(ABCPerp, AO);
		if (abs(ABCPerpDotAO) > COLLISION_TOLERANCE) { // if origin is above or below plane
			direction_out = glm::sign(ABCPerpDotAO) * ABCPerp; // TODO - should be O - centroid of ABC?
			return false;
		}

		return true; // Origin is within the triangle itself (or on an edge) - either way, a collision has occurred.
	}

	inline bool tetrahedronContainsOrigin(vector<dvec3>& simplex_IO, dvec3& direction_out) {
		dvec3 AB = simplex_IO.at(3) - simplex_IO.back();   // B - A
		dvec3 AC = simplex_IO.at(2) - simplex_IO.back();   // C - A
		dvec3 AD = simplex_IO.front() - simplex_IO.back(); // D - A
		dvec3 AO = ORIGIN - simplex_IO.back();			   // O - A
		
		// Origin lies in region ABC
		dvec3 ABCPerp = glm::cross(AB, AC);
		if (sameDirection(ABCPerp, AO)) {
			// Remove point D and try again for a better tetrahedron
			simplex_IO.erase(simplex_IO.begin());
			direction_out = ABCPerp;
			return false;
		}

		// Origin lies in region ABD
		dvec3 ABDPerp = glm::cross(AB, AD);
		if (sameDirection(ABDPerp, AO)) {
			// Remove point C and try again for a better tetrahedron
			simplex_IO.erase(simplex_IO.begin() + 1);
			direction_out = ABDPerp;
			return false;
		}

		// Origin lies in region ACD
		dvec3 ACDPerp = glm::cross(AC, AD);
		if (sameDirection(ACDPerp, AO)) {
			// Remove point B and try again for a better tetrahedron
			simplex_IO.erase(simplex_IO.begin() + 2);
			direction_out = ACDPerp;
			return false;
		}

		return true;  // Origin must be inside tetrahedron (or on edge / face) - collision occurred!
	}

	inline dvec3 tripleProduct(dvec3& v1, dvec3& v2, dvec3& v3) {
		return glm::cross(glm::cross(v1, v2), v3);
	}

	inline bool sameDirection(dvec3& v1, dvec3& v2) {
		return glm::dot(v1, v2) > COLLISION_TOLERANCE;
	}
}