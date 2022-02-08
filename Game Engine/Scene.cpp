#include "Scene.h"
#include <cassert>
#include<string>
using std::string;
#include <camera.h>
#include "Shader.h"
#include "IDrawable.h"

const string VIEW_MATRIX = "view";
const string PROJECTION_MATRIX = "projection";

Scene::Scene(Camera& camera): m_camera(camera) {
	// Guarantee single instance at runtime (without use of singleton pattern)
	assert(!instantiated_);		
	instantiated_ = true;
}

void Scene::RegisterDrawable(IDrawable& drawable) {
	m_drawables.push_back(drawable);
}

void Scene::RegisterShader(Shader& shader) {
	m_shaders.push_back(shader);
}

void Scene::Draw() {
	const mat4& viewMatrix = m_camera.calcViewMatrix();
	const mat4& projectionMatrix = m_camera.calcProjectionMatrix();

	//m_shaders[0].get().setMatrix(VIEW_MATRIX, viewMatrix);
	//m_shaders[0].get().setMatrix(PROJECTION_MATRIX, projectionMatrix);
	for (auto& shader : m_shaders) {
		shader.get().setValue(VIEW_MATRIX, viewMatrix);
		shader.get().setValue(PROJECTION_MATRIX, projectionMatrix);
	}

	// Draw all drawables
	for (auto& drawable: m_drawables) {
		drawable.get().Draw(); 
	}
}

bool Scene::instantiated_{ false };
vector<reference_wrapper<IDrawable>> Scene::m_drawables{};
vector<reference_wrapper<Shader>> Scene::m_shaders{};