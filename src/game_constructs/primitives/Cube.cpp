#include "Cube.h"
using namespace Primitive;
#include "graphics/Model.h"
#include "graphics/material.h"
#include "graphics/Shader.h"
#include "graphics/mesh.h"
#include "graphics/vertex.h"
#include <glm/glm.hpp>
using glm::vec3;
using glm::dvec3;

vector<Vertex> cubeVertices = {
	// Top
	Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.0f,  0.0f, -1.0f), vec2(0.0f, 0.0f)),
	Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)),
	Vertex(vec3(0.5f,  0.5f, -0.5f), vec3(0.0f,  0.0f, -1.0f), vec2(1.0f, 1.0f)),
	Vertex(vec3(-0.5f,  0.5f, -0.5f), vec3(0.0f,  0.0f, -1.0f), vec2(0.0f, 1.0f)),

	// Bottom
	Vertex(vec3(-0.5f, -0.5f,  0.5f), vec3(0.0f,  0.0f,  1.0f), vec2(0.0f, 0.0f)),
	Vertex(vec3(0.5f, -0.5f,  0.5f), vec3(0.0f,  0.0f,  1.0f), vec2(1.0f, 0.0f)),
	Vertex(vec3(0.5f,  0.5f,  0.5f), vec3(0.0f,  0.0f,  1.0f), vec2(1.0f, 1.0f)),
	Vertex(vec3(-0.5f,  0.5f,  0.5f), vec3(0.0f,  0.0f,  1.0f), vec2(0.0f, 1.0f)),

	// Left
	Vertex(vec3(-0.5f,  0.5f,  0.5f), vec3(-1.0f,  0.0f,  0.0f), vec2(1.0f, 0.0f)),
	Vertex(vec3(-0.5f,  0.5f, -0.5f), vec3(-1.0f,  0.0f,  0.0f), vec2(1.0f, 1.0f)),
	Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f, 1.0f)),
	Vertex(vec3(-0.5f, -0.5f,  0.5f), vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f)),

	// Right
	Vertex(vec3(0.5f,  0.5f,  0.5f), vec3(1.0f,  0.0f,  0.0f), vec2(1.0f, 0.0f)),
	Vertex(vec3(0.5f,  0.5f, -0.5f), vec3(1.0f,  0.0f,  0.0f), vec2(1.0f, 1.0f)),
	Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(1.0f,  0.0f,  0.0f), vec2(0.0f, 1.0f)),
	Vertex(vec3(0.5f, -0.5f,  0.5f), vec3(1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f)),

	// Front
	Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.0f, -1.0f,  0.0f), vec2(0.0f, 1.0f)),
	Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0.0f, -1.0f,  0.0f), vec2(1.0f, 1.0f)),
	Vertex(vec3(0.5f, -0.5f,  0.5f), vec3(0.0f, -1.0f,  0.0f), vec2(1.0f, 0.0f)),
	Vertex(vec3(-0.5f, -0.5f,  0.5f), vec3(0.0f, -1.0f,  0.0f), vec2(0.0f, 0.0f)),

	// Back
	Vertex(vec3(-0.5f,  0.5f, -0.5f), vec3(0.0f,  1.0f,  0.0f), vec2(0.0f, 1.0f)),
	Vertex(vec3(0.5f,  0.5f, -0.5f), vec3(0.0f,  1.0f,  0.0f), vec2(1.0f, 1.0f)),
	Vertex(vec3(0.5f,  0.5f,  0.5f), vec3(0.0f,  1.0f,  0.0f), vec2(1.0f, 0.0f)),
	Vertex(vec3(-0.5f,  0.5f,  0.5f), vec3(0.0f,  1.0f,  0.0f), vec2(0.0f, 0.0f)),
};

vector<unsigned int> cubeIndices = {
	0,  1,  2,      0,  2,  3,    // front
	4,  5,  6,      4,  6,  7,    // back
	8,  9,  10,     8,  10, 11,   // top
	12, 13, 14,     12, 14, 15,   // bottom
	16, 17, 18,     16, 18, 19,   // right
	20, 21, 22,     20, 22, 23,   // left
};


const vector<dvec3> cubeColliderVertices = {
	dvec3(0.5, 0.5, 0.5),
	dvec3(0.5, 0.5, -0.5),
	dvec3(0.5, -0.5, 0.5),
	dvec3(0.5, -0.5, -0.5),
	dvec3(-0.5, 0.5, 0.5),
	dvec3(-0.5, 0.5, -0.5),
	dvec3(-0.5, -0.5, 0.5),
	dvec3(-0.5, -0.5, -0.5),
};

Model& CubeModel() {

	// Create textures
	// TODO - make file loading more robust. Right now file paths are relative to the build directory / location of executable.
	Texture* texture1 = new Texture("../src/dev_data/images/wall_tex.jpg", "texture1", false);
	Texture* texture2 = new Texture("../src/dev_data/images/awesomeface.png", "texture2", true);
	vector<Texture>* textures = new vector<Texture>{ *texture1, *texture2 };

	// Create mesh
	Mesh* mesh = new Mesh(cubeVertices, cubeIndices);

	// Create shader
	// TODO - make file loading more robust. Right now file paths are relative to the build directory / location of executable.
	Shader* shader = new Shader("../src/dev_data/shaders/vertShader.vs", "../src/dev_data/shaders/fragShader.fs");
	shader->use();

	// Create material
	Material* material = new Material(*shader, *textures);

	// Create model
	Model* model = new Model(*mesh, *material);

	return *model;
}

CubeCollider::CubeCollider(GameObject* const gameObject) : Collider(gameObject, cubeColliderVertices) {
}

// Constructors
// Default 
Cube::Cube() : GameObject(CubeModel()) {
	setCollider(new CubeCollider(this));
}

// With position
Cube::Cube(const vec3& position) : GameObject(CubeModel(), position) {
	setCollider(new CubeCollider(this));
}