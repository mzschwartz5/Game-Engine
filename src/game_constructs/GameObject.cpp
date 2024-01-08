#include "GameObject.h"
#include "globals/Scene.h"
#include <iostream>
#include <glm/glm.hpp>
using glm::vec3;
using glm::dvec3;
using glm::dvec4;
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
	// If this object has a parent, it will be drawn by the parent.
	if (hasParent()) return;
	DrawModel();
}

void GameObject::DrawModel() {

	// Dirty flag pattern to avoid unnecessary recalculations of transforms
	if (hasParent() && m_parent->hasMoved) {
		transform = m_parent->transform * transform;
		hasMoved = true;
	}
	
	m_model.Draw(transform);

	for (const auto& child : m_children) {
		child.get().DrawModel();
	}

	// Reset flags
	hasMoved = false;
}

vec3 GameObject::position() const {
	return vec3(transform[3].x, transform[3].y, transform[3].z); // read position off of transform matrix
}

// Translate and set -- is this the appropriate way to be doing these?
void GameObject::translate(const vec3& translation) {
	transform = glm::translate(transform, translation);
	hasMoved = true;
}

void GameObject::setPosition(const vec3& position) {
	transform[3] = vec4{ position, transform[3].w }; // should w component remain the same?
	hasMoved = true;
}

mat3 GameObject::rotation() const {
	return mat3(transform); // gets the rotation piece of the transform
}

Collider* GameObject::collider() {
	return m_collider;
}

void GameObject::setCollider(Collider* const collider) {
	m_collider = collider;
}

dvec3 GameObject::pointToWorldSpace(const dvec3& point)
{
	dvec4 transformedPoint = transform * dvec4(point, 1.0);
	return dvec3(transformedPoint);
}

void GameObject::setParent(GameObject& parent) {
	parent.m_children.push_back(*this);
	this->m_parent = &parent;
}

bool GameObject::hasParent() {
	return m_parent != nullptr;
}