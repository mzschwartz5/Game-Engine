#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "graphics/IDrawable.h"
#include <functional>
using std::reference_wrapper;
#include <vector>
using std::vector;
#include "graphics/Model.h"
#include "globals/Scene.h"
#include <glm/glm.hpp>
using glm::vec3;
using glm::dvec3;
#include <glm/gtc/matrix_transform.hpp>
using glm::mat4;
using glm::mat3;

// Forward declare Collider
class Collider;

class GameObject : public IDrawable {
public:
	GameObject(const Model& model);
	GameObject(const Model& model, const vec3& position);
	vec3 position() const;
	mat3 rotation() const;
	void translate(const vec3& translation);
	void setPosition(const vec3& position);
	Collider* collider();
	void setCollider(Collider* const collider);
	dvec3 pointToWorldSpace(const dvec3& point); // TODO - encapsulate this in a transform class along with transform itself

private:
	void Draw() override;
	void DrawModel(const mat4& parentTransform = mat4(1.0), bool hasParentMoved = false);

	// Game object data
	const Model& m_model;
	vector<reference_wrapper<GameObject>> m_children;
	mat4 transform{ mat4(1.0f) }; // aka Model-to-World matrix
	bool hasMoved{ false };	      // does the transform need to be recalculated?
	Collider* m_collider{ nullptr };
};

#endif