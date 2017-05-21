#pragma once
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "MainLayout.h"

class Application
{
public:
	Application();
	~Application();

	void Run();
	static int assignVAO();
private:
	static int VAOcount;
	MainWindow* screen;
	MainLayout* layout;

	void initGLFW();
	void initGLEW() throw( std::runtime_error );
	void renderAll();
	friend 	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);