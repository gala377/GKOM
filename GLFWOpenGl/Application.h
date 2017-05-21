#pragma once
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "MainWindow.h"
class Application
{
public:
	Application();
	~Application();

	void Run();
private:
	MainWindow* screen;
	void initGLFW();
	void initGLEW() throw( std::runtime_error );
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

