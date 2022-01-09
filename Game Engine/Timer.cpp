#include "Timer.h"
#include <GLFW/glfw3.h>
#include <cassert>


double Timer::deltaTime{ 0.0 };
bool Timer::instantiated_{ false };
Timer::Timer() : m_lastFrameTimeStamp(0.0) {
	assert(!instantiated_);
	instantiated_ = true; // guarantees single instance
}

void Timer::calcDeltaTime()
{
	double currentFrame = glfwGetTime();
	deltaTime = currentFrame - m_lastFrameTimeStamp;
	m_lastFrameTimeStamp = currentFrame;
}

