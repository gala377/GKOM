#include "Camera.h"

Camera::Camera()
{
	model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	// Note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, (GLfloat)1280 / (GLfloat)720, 0.1f, 100.0f);
}


Camera::~Camera()
{
}


Camera mainCamera;