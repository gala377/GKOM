#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "Application.h"
int main()
{
	Application* app = new Application();
	app->Run();
	return 0;
}