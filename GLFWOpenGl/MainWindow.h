#pragma once
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MainWindow
{
public:
	GLFWwindow* window;

	MainWindow(int width = 800, int height = 600, const char* title = "");
	~MainWindow();
	void setViewport();
private:
	GLFWwindow* createWindow(int width, int height, const char* title) throw(std::runtime_error);
	void setViewport(GLFWwindow* w);
};

