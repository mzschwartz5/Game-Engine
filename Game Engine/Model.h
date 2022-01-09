#ifndef MODEL_H
#define MODEL_H
#include <vector>
using std::vector;
#include <functional>
using std::reference_wrapper;
#include "mesh.h"
#include "material.h"
#include <glm/gtc/matrix_transform.hpp>
using glm::mat4;

class Model {
public:
	Model(const Mesh& mesh, Material& material);
	void Draw(const mat4& transform) const; // (public, but the Model class is a private member of GameObject)
private:
	// References to "global" objects stored in Scene vectors
	const Mesh& m_mesh;
	Material& m_material;
	const vector<reference_wrapper<Model>> m_childModels;
};

#endif