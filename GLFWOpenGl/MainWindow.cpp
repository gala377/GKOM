#include "MainWindow.h"



MainWindow::MainWindow(int width = 800, int height = 600, std::string title = "")
{
	std::cout << "Creating new window\n";
	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	
} 


MainWindow::~MainWindow()
{
}
