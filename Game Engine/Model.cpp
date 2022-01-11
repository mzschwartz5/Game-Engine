#include "Model.h"
#include <vector>
using std::vector;
#include <functional>
using std::reference_wrapper;
#include "mesh.h"
#include "material.h"
#include "texture.h"
#include <glm/gtc/matrix_transform.hpp>
using glm::mat4;
#include <string>

const std::string TRANSFORM_UNIFORM = "model";

Model::Model(const Mesh& mesh, Material& material): m_mesh(mesh), m_material(material)
{
}

void Model::Draw(const mat4& transform) const{
	
	m_material.getShader().setMatrix(TRANSFORM_UNIFORM, transform); // update model-to-world matrix on shader
	m_material.activateTextures(); // done before drawing
	m_mesh.Draw();

	for (const auto& child : m_childModels) {
		child.get().Draw(transform);
	}
}

// Getters?