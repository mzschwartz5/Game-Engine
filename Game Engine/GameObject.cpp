#include "GameObject.h"
#include "Scene.h"
#include <iostream>
#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;
#include <glm/gtc/matrix_transform.hpp>
using glm::mat4;

GameObject::GameObject(const Model& model): m_model(model) {
	Scene::RegisterDrawable(*this);
}

GameObject::GameObject(const Model& model, const vec3& position) : GameObject(model) {
	setPosition(position);
}

void GameObject::Draw() {
	DrawModel(); // has default param values in .h file.
}

void GameObject::DrawModel(const mat4& parentTransform, bool hasParentMoved) {

	// Dirty flag pattern to avoid unnecessary recalculations of transforms
	if (hasParentMoved) {
		transform = parentTransform * transform;
		hasMoved = true;
	}
	
	m_model.Draw(transform);

	for (const auto& child : m_children) {
		child.get().DrawModel(transform, hasMoved);
	}

	// Reset flags
	hasMoved = false;
}

// TODO - this is returning a local variable by reference
const vec3& GameObject::position() const {
	return vec3(transform[3].x, transform[3].y, transform[3].z); // read position off of transform matrix
}

// Translate and set -- is this the appropriate way to be doing these?
void GameObject::translate(const vec3& translation) {
	transform = glm::translate(transform, translation);
	hasMoved = true;
}

void GameObject::setPosition(const vec3& position) {
	transform[3] = vec4{ position, transform[3].w }; // should w component remain the same?
}