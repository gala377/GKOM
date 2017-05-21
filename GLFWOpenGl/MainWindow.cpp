#include "MainWindow.h"



MainWindow::MainWindow(int width = 800, int height = 600, std::string title = "")
{
	std::cout << "Creating new window\n";
	window = createWindow(width, height, title);
	setViewport(window);
} 


MainWindow::~MainWindow()
{
}


GLFWwindow* MainWindow::createWindow(int width, int height, std::string title)
{
	GLFWwindow* w = glfwCreateWindow(width, height, title.c_str, nullptr, nullptr);
	if (w == nullptr)
		throw std::runtime_error("Could not initialize new Window MainWindow.CreateWindow");
	return w;
}

void MainWindow::setViewport(GLFWwindow* w)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}