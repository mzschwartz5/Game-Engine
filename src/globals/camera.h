#ifndef CAMERA_H
#define CAMERA_H

#include "constants.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using glm::vec3;
using glm::mat4;
#include "Scene.h"

class Camera {
public:
	Camera(const vec3& position, const vec3& front);
	vec3& getCameraPosition();
	void setCameraPosition(const vec3& pos);
	vec3& getCameraRight();
	vec3& getCameraUp();
	vec3& getCameraFront();
	float getFov();
	void setFov(float newFov);
	void setCameraFront(double xoffset, double yoffset);
	friend void Scene::Draw(); // so Scene::Draw can tell camera to update it's matrices

private:
	mat4 viewMatrix;
	mat4 projectionMatrix;
	vec3 cameraPos;
	vec3 cameraRight;
	vec3 cameraUp;
	vec3 cameraFront;
	double pitch;
	double yaw;
	float fov;
	void updateCameraVectors();
	const mat4& calcViewMatrix();
	const mat4& calcProjectionMatrix(const float width = Constants::SCR_WIDTH, const float height = Constants::SCR_HEIGHT);

};

#endif