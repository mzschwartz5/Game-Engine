#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "IDrawable.h"
#include <functional>
using std::reference_wrapper;
#include <vector>
using std::vector;
#include "Model.h"
#include "Scene.h"
#include <glm/glm.hpp>
using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>
using glm::mat4;


class GameObject : public IDrawable {
public:
	GameObject(const Model& model);
	GameObject(const Model& model, const vec3& position);
	const vec3& position() const;
	void translate(const vec3& translation);
	void setPosition(const vec3& position);

private:
	void Draw() override;
	void DrawModel(const mat4& parentTransform = mat4(1.0), bool hasParentMoved = false);

	// Game object data
	const Model& m_model;
	vector<reference_wrapper<GameObject>> m_children;
	mat4 transform{ mat4(1.0f) }; // aka Model-to-World matrix
	bool hasMoved{ false };	// does the transform need to be recalculated?

};

#endif