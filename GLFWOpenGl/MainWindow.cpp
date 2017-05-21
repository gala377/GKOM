#include "MainWindow.h"


MainWindow::MainWindow(int width, int height, const char* title)
{
#ifdef DEBUG
	std::cout << "Creating new window: MainWindow.MainWindow\n";
#endif // DEBUG

	window = createWindow(width, height, title);
	
#ifdef DEBUG
	std::cout << "Window Created\n";
#endif // DEBUG

} 

MainWindow::~MainWindow()
{
}

GLFWwindow* MainWindow::createWindow(int width, int height, const char* title)
{
	GLFWwindow* w = glfwCreateWindow(width, height, title, nullptr, nullptr);
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

void MainWindow::setViewport()
{
	setViewport(window);
}