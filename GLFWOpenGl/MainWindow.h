#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MainWindow
{
public:
	MainWindow(int width, int height, std::string title);
	~MainWindow();
private:
	GLFWwindow* window;


};

