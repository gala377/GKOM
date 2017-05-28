#include "Application.h"
#include "Objects\Triangle2D.h"
#include "Rectagular2D.h"
#include "Objects\ColorCube.h"
#include "Objects\Light.h"
#include "Objects\SolidColorCube.h"
#include "Camera.h"
#include "ModelFactory.h"

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

	setUpScene();

	while (!glfwWindowShouldClose(screen->window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		mainCamera.do_movement();
		mainCamera.Update();

		renderAll();

		glfwSwapBuffers(screen->window);
	}
}

void Application::renderAll()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	layout->Draw();
}
void Application::setUpScene()
{
	setUpLight();
	setUpBase();
	setUpDetails();
	setUpSaw();
	setUpHouse();
	setUpLogs();

}

void Application::setUpBase()
{
	RawObject* ground = ModelFactory::texturedCube(15, 0.1, 20, "textures/ground2.jpg", "textures/ground2.jpg", 16);
	layout->addObject(ground);

	RawObject* base1 = ModelFactory::texturedCube(1.5, 1.5, 7.9, "textures/planks.jpg", "textures/planks.jpg", 16);
	RawObject* base2 = ModelFactory::texturedCube(1.5, 1.5, 7.9, "textures/planks.jpg", "textures/planks.jpg", 16);
	RawObject* base3 = ModelFactory::texturedCube(5, 1, 8, "textures/planks.jpg", "textures/planks.jpg", 16);
	RawObject* base4 = ModelFactory::texturedCube(0.65, 1, 7.89, "textures/planks.jpg", "textures/planks.jpg", 16);
	RawObject* base5 = ModelFactory::texturedCube(0.65, 1, 7.89, "textures/planks.jpg", "textures/planks.jpg", 16);


	base3->translate(0, 0.1, 0);
	base1->translate(3.4, 0.1, 0);
	base2->translate(-3.4, 0.1, 0);
	base4->translate(2.4, 0.5, 0);
	base5->translate(-2.4, 0.5, 0);

	base4->rotate(45, 0, 0, 1);
	base5->rotate(-45, 0, 0, 1);

	layout->addObject(base1);
	layout->addObject(base2);
	layout->addObject(base3);
	layout->addObject(base4);
	layout->addObject(base5);
}

void Application::setUpLight()
{
	Light::addNewLight(glm::vec3(10, 8, 7), glm::vec3(0, 0, 0));
	Light::addNewLight(glm::vec3(1, 8, 4), glm::vec3(0, 0, 0));
	Light::addNewLight(glm::vec3(-7, 8, -4), glm::vec3(0, 0, 0));
	Light::addNewLight(glm::vec3(-8, 8, 9), glm::vec3(1, 1, 1));

	for (auto light : Light::lights)
		layout->addObject(light);
}

void Application::setUpDetails()
{
	RawObject* pole1 = ModelFactory::texturedCyllinder(0.5, 6, 32, "textures/metal2.jpg", "texture/metal2.jpg", 128);
	RawObject* pole2 = ModelFactory::texturedCyllinder(0.5, 6, 32, "textures/metal2.jpg", "texture/metal2.jpg", 128);
	
	pole1->translate(2.6, 3, 2);
	pole2->translate(-2.6, 3, 2);

	layout->addObject(pole1);
	layout->addObject(pole2);

}

void Application::setUpHouse()
{
	RawObject* wall1 = ModelFactory::texturedCube(15, 8, 0.4, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	RawObject* wall2 = ModelFactory::texturedCube(4, 8, 0.4, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	RawObject* wall3 = ModelFactory::texturedCube(4, 8, 0.4, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	RawObject* wall4 = ModelFactory::texturedCube(9, 4, 0.4, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	RawObject* wall5 = ModelFactory::texturedCube(0.4, 8, 20, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	RawObject* wall6 = ModelFactory::texturedCube(0.4, 8, 20, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);

	wall1->translate(0, 8, -20);
	
	wall2->translate(13, 8, 20);
	wall3->translate(-13, 8, 20);
	wall4->translate(0, 12, 20);
	
	wall5->translate(-15, 8, 0);
	wall6->translate(15, 8, 0);
	


	layout->addObject(wall1);
	layout->addObject(wall2);
	layout->addObject(wall3);
	layout->addObject(wall4);
	layout->addObject(wall5);
	layout->addObject(wall6);
}

void Application::setUpSaw()
{
	RawObject* saw = ModelFactory::gnCube(2.3, 0.3, 0.01, glm::vec3(0.8, 0.8, 0.8), glm::vec3(0.8, 0.8, 0.8), glm::vec3(0.8, 0.8, 0.8), glm::vec3(1, 1, 1), 256);

	saw->translate(0, 8.5, 2);
	layout->addObject(saw);

}

void Application::setUpLogs()
{
	RawObject* log1 = ModelFactory::texturedCyllinder(0.1, 4, 32, "textures/tree5.jpg", "textures/tree5.jpg", 16);
	//RawObject* log2 = ModelFactory::texturedCyllinder(0.1, 4, 32, "textures/tree4.jpg", "textures/tree4.jpg", 16);
	//RawObject* log3 = ModelFactory::texturedCyllinder(0.1, 4, 32, "textures/tree4.jpg", "textures/tree4.jpg", 16);
	//RawObject* log4 = ModelFactory::texturedCyllinder(0.1, 4, 32, "textures/tree4.jpg", "textures/tree4.jpg", 16);
	//RawObject* log5 = ModelFactory::texturedCyllinder(0.1, 4, 32, "textures/tree4.jpg", "textures/tree4.jpg", 16);
	//RawObject* log6 = ModelFactory::texturedCyllinder(0.1, 4, 32, "textures/tree4.jpg", "textures/tree4.jpg", 16);
	//RawObject* log7 = ModelFactory::texturedCyllinder(0.1, 4, 32, "textures/tree4.jpg", "textures/tree4.jpg", 16);

	log1->translate(0, 0.05, 10);
	//log2->translate(0.1, 0.05, 10);
	//log3->translate(-0.1, 0.05, 10);
	//log4->translate(0.05, 0.15, 10);
	//log5->translate(-0.05, 0.15, 10);
	//log6->translate(0,0.25,10);

	layout->addObject(log1);
	//layout->addObject(log2);
	//layout->addObject(log3);
	//layout->addObject(log4);
	//layout->addObject(log5);
	//layout->addObject(log6);
}

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