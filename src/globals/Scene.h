#ifndef SCENE_H
#define SCENE_H
#include <vector>
using std::vector;
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/Shader.h"
#include <functional>
using std::reference_wrapper;
#include "graphics/IDrawable.h"
#include <GLFW/glfw3.h>

class Camera;

class Scene {
public:	
	Scene(Camera& camera, GLFWwindow* window);
	static void RegisterDrawable(IDrawable& drawable);
	static void RegisterShader(Shader& shader);
	void Draw();
private:
	Camera& m_camera;
	GLFWwindow* m_window;

	// "Global" (restricted access) arrays of data in the scene, shared by all game objects in scene.
	static vector<reference_wrapper<IDrawable>> m_drawables;
	vector<Mesh> m_meshes;		// not implemented yet, make static too
	vector<Texture> m_textures; // not implmented yet, make static too
	static vector<reference_wrapper<Shader>> m_shaders;
	static bool instantiated_;
};

#endif