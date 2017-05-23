#pragma once 
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	//all objects
	glm::mat4 model;
	//camera
	glm::mat4 view;
	//perspective
	glm::mat4 projection;

	Camera();
	~Camera();
};

extern Camera mainCamera;

