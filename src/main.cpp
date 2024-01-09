#include <glad/gl.h>
#include <GLFW/glfw3.h>	
#include <iostream>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "globals/camera.h"
#include <vector>
#include "globals/Scene.h"
#include "globals/Timer.h"
#include "constants.h"
#include "game_constructs/primitives/Cube.h"
#include "physics/CollisionDetection.h"
using std::vector;
using glm::vec3;
using glm::vec2;
using Primitive::Cube;

// Forward declarations
GLFWwindow* initializeGLFW();
void processKeyboardInput(GLFWwindow* window, Camera& camera);
void bindMouseInputsToWindow(GLFWwindow* window, Camera* camera);
void glfwErrorCallback(int error, const char* description);

int main()
{
	// Top level error handling
	try { 
	    glfwSetErrorCallback(glfwErrorCallback);

		// GLFW initialization and global settings
		GLFWwindow* window = initializeGLFW();
		stbi_set_flip_vertically_on_load(true); // global setting for STB image loader

		// Create camera with position and front vectors, control it via mouse input.
		Camera camera(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, -1.0f));
		bindMouseInputsToWindow(window, &camera);

		// Initialize scene
		Scene scene{ camera, window };

		// Initialize Time
		Timer timer;

		// Instantiate cube primitives for testing
		Cube cube1(vec3(0.0f, 0.0f, 0.0f));
		Cube cube2(vec3(2.0f, 5.0f, -15.0f));
		Cube cube3(vec3(-1.5f, -2.2, -2.5f));
		Cube cube4(vec3(-3.8, -2.0f, -12.3f));
		Cube cube5(vec3(2.4f, -0.4f, -3.5f));
		Cube cube6(vec3(-1.7f, 3.0f, -7.5f));
		Cube cube7(vec3(1.3f, -2.0f, -2.5f));
		Cube cube8(vec3(1.5f, 2.0f, -2.5f));
		Cube cube9(vec3(1.5f, 0.2f, -1.5f));
		Cube cube10(vec3(-1.3f, 1.0f, -1.5f));

		// Cube cube1(vec3(0.0, 0.0, 0.0));
		// Cube cube2(vec3(.95, .93, 0.0));
		bool collided = Physics::GJK(*cube1.collider(), *cube2.collider());
		std::cout << collided << std::endl;

		// Main render loop
		// Draw images until told to explicitly stop (e.g. x out of window)
		while (!glfwWindowShouldClose(window))
		{
			timer.calcDeltaTime();
			processKeyboardInput(window, camera);

			// Draw!
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			scene.Draw();

			glfwSwapBuffers(window);
			glfwPollEvents(); // updates window state upon events like keyboard or mouse inputs;
		}

		glfwTerminate(); // clean up GLFW resources
	}
	catch (const char* str) {
		std::cerr << str << std::endl;
	}

	return 0;
}

GLFWwindow* initializeGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	//glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(Constants::SCR_WIDTH, Constants::SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		std::exit(1);
	}
	glfwMakeContextCurrent(window);

	// GLFW dependent on GLAD - make sure glad is loaded
	if (!gladLoadGL(glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		std::exit(1);
	}

	// The reason we get the frame buffer here instead of using the width/height constants is because retina screens have a higher resolution than the window size.
	// After creating the window with our constants, we'll take what GLFW says the screen size is as the source of truth.
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);	

	// Register callback on window resize
	auto frameBufferReziseCallback = [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); };
	glfwSetFramebufferSizeCallback(window, frameBufferReziseCallback); 

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable mouse for FPS camera system

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	
	return window;
}

void processKeyboardInput(GLFWwindow* window, Camera& camera) {

	glm::vec3 cameraPos = camera.getCameraPosition();
	glm::vec3 cameraFront = camera.getCameraFront();
	glm::vec3 cameraUp = camera.getCameraUp();

	const float cameraSpeed = 2.5f * Timer::deltaTime; // adjust if necessary

	// Keyboard input
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwTerminate();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	camera.setCameraPosition(cameraPos);

}

void bindMouseInputsToWindow(GLFWwindow* window, Camera* camera) {
	/*
		NOTE: GLFW callbacks must be function pointers. This is annoying because the callbacks need access to camera. By passing in camera to the lambda's capture, the lambda
		no longer decays to a function pointer. Instead, we have to use GLFW functions to store off and retrieve the camera pointer. (Which causes other annoyances and oddities..)
	*/
	glfwSetWindowUserPointer(window, camera);
	// Lambda for mouse input callback
	auto mouseCallback = [](GLFWwindow* window, double xpos, double ypos) {
		static double lastX{ xpos };
		static double lastY{ ypos };
		
		double xoffset = xpos - lastX;
		double yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		// Retrieve pointer to camera from GLFW and call method to set the camera front vector
		static Camera* pCamera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
		pCamera->setCameraFront(xoffset, yoffset);
	};
	glfwSetCursorPosCallback(window, mouseCallback); // register callback 
	
	// Call the lambda once to initialize the static camera pointer, so we can unbind it at the end of this function.
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	mouseCallback(window, xpos, ypos); 

	// Lambda for scroll input callback
	auto scrollCallback = [](GLFWwindow* window, double xoffset, double yoffset) {
		float sensitivty = 1.5f;
		static Camera* pCamera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

		float fov = pCamera->getFov();
		fov -= (float)(yoffset * sensitivty);
		pCamera->setFov(fov);
	};
	glfwSetScrollCallback(window, scrollCallback); // register callback
	scrollCallback(window, 0.0, 0.0); // call once to initialize the static camera pointer, so we can then clear it.

	// Unbind GLFW user pointer
	glfwSetWindowUserPointer(window, nullptr);
}

void glfwErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}