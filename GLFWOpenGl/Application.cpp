#include "Application.h"
#include "Objects\Triangle2D.h"
#include "Rectagular2D.h"
#include "Objects\ColorCube.h"
#include "Objects\Light.h"
#include "Objects\SolidColorCube.h"
#include "Camera.h"

bool keys[1024];

GLfloat Application::deltaTime = 0.0f;
GLfloat Application::lastFrame = 0.0f;

int Application::VAOcount = 0;

Application::Application()
{
	try {
		initGLFW();
		screen = new MainWindow(WIDTH, HEIGHT, "Test window");
		glfwMakeContextCurrent(screen->window);
		screen->setViewport();
		initGLEW();
		
		glfwSetKeyCallback(screen->window, key_callback);
		glfwSetCursorPosCallback(screen->window, mouse_callback);
		glfwSetScrollCallback(screen->window, scroll_callback);

		layout = new MainLayout(screen);
		glEnable(GL_DEPTH_TEST);
		glfwSetInputMode(screen->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
	delete layout;
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
	Triangle2D* tra2D2 = new Triangle2D(-1, -1, -1, 0, 0, 0);
	//layout->addObject(tra2D2);
	Rectangular2D* rec2D = new Rectangular2D(1,1, 1,0, 0,0, 0, 1);
	//layout->addObject(rec2D);
	ColorCube* cube = new ColorCube(0.3, 1, 0.5);
	layout->addObject(cube);
	//rec2D->rotate(-10, 1, 0, 0);
	Light::addNewLight(glm::vec3(2, 0, 2), glm::vec3(1, 1, 1));
	//Light::addNewLight(glm::vec3(4, 0, 1), glm::vec3(0.5, 0.3, 0.2));

	for (auto light : Light::lights)
		layout->addObject(light);

	SolidColorCube* solid = new SolidColorCube(1, 1, 1, glm::vec3(1.0f, 0.3f, 0.5f));
	layout->addObject(solid);
	solid->translate(5, 2, 0);


	while (!glfwWindowShouldClose(screen->window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		mainCamera.do_movement();
		mainCamera.Update();

		renderAll();
		cube->rotate(0.001, 1, 1, 1);
		solid->rotate(0.001, 1, 0, 1);
		glfwSwapBuffers(screen->window);
	}
}

void Application::renderAll()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	layout->Draw();
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (mainCamera.firstMouse)
	{
		mainCamera.lastX = xpos;
		mainCamera.lastY = ypos;
		mainCamera.firstMouse = false;
	}

	GLfloat xoffset = xpos - mainCamera.lastX;
	GLfloat yoffset = mainCamera.lastY - ypos; // Reversed since y-coordinates go from bottom to left
	mainCamera.lastX = xpos;
	mainCamera.lastY = ypos;

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	mainCamera.yaw += xoffset;
	mainCamera.pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (mainCamera.pitch > 89.0f)
		mainCamera.pitch = 89.0f;
	if (mainCamera.pitch < -89.0f)
		mainCamera.pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(mainCamera.yaw)) * cos(glm::radians(mainCamera.pitch));
	front.y = sin(glm::radians(mainCamera.pitch));
	front.z = sin(glm::radians(mainCamera.yaw)) * cos(glm::radians(mainCamera.pitch));
	mainCamera.cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (mainCamera.fov >= 1.0f && mainCamera.fov <= 45.0f)
		mainCamera.fov -= yoffset;
	if (mainCamera.fov <= 1.0f)
		mainCamera.fov = 1.0f;
	if (mainCamera.fov >= 45.0f)
		mainCamera.fov = 45.0f;
}