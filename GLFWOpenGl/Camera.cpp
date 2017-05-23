#include "Camera.h"
#include "Application.h"

void Camera::do_movement()
{
	GLfloat cameraSpeed = 5.0f * Application::deltaTime;
	if (keys[GLFW_KEY_W])
		cameraPos += cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_S])
		cameraPos -= cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::Update()
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

Camera::Camera()
{
	// Note that we're translating the scene in the reverse direction of where we want to move
	model = glm::rotate(model, -50.f, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, (GLfloat)4 / (GLfloat)3, 0.1f, 100.0f);
}


Camera::~Camera()
{
}


Camera mainCamera;