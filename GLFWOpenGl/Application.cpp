#include "Application.h"


Application::Application()
{
	try {
		initGLFW();
		screen = new MainWindow(1280, 720, "Test window");
		glfwMakeContextCurrent(screen->window);
		screen->setViewport();
		initGLEW();
		
		glfwSetKeyCallback(screen->window, key_callback);
	}
	catch (std::runtime_error e) {
		std::cout << "Runtime Exception in Application.Application " << e.what() << "\n";
		glfwTerminate();
	}
	catch (...) {
		std::cout << "Uknown exception cought: Application.Application\n";
		glfwTerminate();
	}
}

Application::~Application()
{
	glfwTerminate();
	delete screen;
}

void Application::initGLFW()
{
#ifdef DEBUG
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
#endif // DEBUG
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void Application::initGLEW()
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Could not initilaize Glew: Application.initGLEW");
}

void Application::Run()
{
	while (!glfwWindowShouldClose(screen->window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		// Swap the screen buffers
		glfwSwapBuffers(screen->window);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}