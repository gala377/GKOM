#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MainWindow
{
public:
	GLFWwindow* window;

	MainWindow(int width, int height, std::string title);
	~MainWindow();
private:
	GLFWwindow* createWindow(int width, int height, std::string title) throw(std::runtime_error);
	void setViewport(GLFWwindow* w);
};

