#pragma once
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MainWindow
{
public:
	GLFWwindow* window;

	MainWindow(GLuint width = 800, GLuint height = 600, const char* title = "");
	~MainWindow();

	void setViewport();
	void setVBO();
	GLuint getVBO() { return VBO; };
private:
	GLuint VBO;

	GLFWwindow* createWindow(GLuint width, GLuint height, const char* title) throw(std::runtime_error);
	void setViewport(GLFWwindow* w);
};

