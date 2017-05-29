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
	RawObject* ground = ModelFactory::texturedCube(15, 0.1, 20, "textures/ground3.jpg", "textures/ground3.jpg", 16);
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
	Light::addNewLight(glm::vec3(0, 5, 20), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	Light::addNewLight(glm::vec3(10, 16, 10), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	Light::addNewLight(glm::vec3(-10, 16, -10), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	Light::addNewLight(glm::vec3(0, 16, 0), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 0.02, 0.02, 0.02);

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
	//RawObject* wall4 = ModelFactory::texturedCube(9, 4, 0.4, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	RawObject* wall5 = ModelFactory::texturedCube(0.4, 8, 20, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	RawObject* wall6 = ModelFactory::texturedCube(0.4, 8, 20, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);

	RawObject* roof1 = ModelFactory::texturedTriangle(15, 0.4, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	RawObject* roof2 = ModelFactory::texturedTriangle(15,0.4, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	
	RawObject* roof3 = ModelFactory::texturedCube(11, 0.4, 20, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	RawObject* roof4 = ModelFactory::texturedCube(11, 0.4, 20, "textures/woodWall.jpg", "textures/woodWall.jpg", 16);
	
	roof1->translate(0, 16, -20);
	roof2->translate(0, 16, 20);
	roof3->translate(-7.5, 22,0);
	roof4->translate(7.5, 22, 0);

	wall1->translate(0, 8, -20);
	
	wall2->translate(13, 8, 20);
	wall3->translate(-13, 8, 20);
	//wall4->translate(0, 12, 20);
	
	wall5->translate(-15, 8, 0);
	wall6->translate(15, 8, 0);
	

	roof3->rotate(glm::radians(45.0f), 0, 0, 1);
	roof4->rotate(glm::radians(-45.0f), 0, 0, 1);


	layout->addObject(wall1);
	layout->addObject(wall2);
	layout->addObject(wall3);
	//layout->addObject(wall4);
	layout->addObject(wall5);
	layout->addObject(wall6);

	layout->addObject(roof1);
	layout->addObject(roof2);
	layout->addObject(roof3);
	layout->addObject(roof4);
}

void Application::setUpSaw()
{
	RawObject* saw = ModelFactory::gnCube(2.3, 0.3, 0.01, glm::vec3(0.8, 0.8, 0.8), glm::vec3(0.8, 0.8, 0.8), glm::vec3(0.8, 0.8, 0.8), glm::vec3(1, 1, 1), 256);

	for (GLint i = -2; i < 3; i++)
	{
		std::cout << "Iteration: " << i << "\n";
		RawObject* zab = ModelFactory::gnTriangle(0.5, 0.01, glm::vec3(0.8, 0.8, 0.8), glm::vec3(0.8, 0.8, 0.8), glm::vec3(1, 1, 1), 256);
		zab->translate(i, 8.25, 2);
		zab->rotate(glm::radians(180.0f), 0, 0, 1);
		layout->addObject(zab);
	}

	saw->translate(0, 8.5, 2);
	layout->addObject(saw);


}

void Application::setUpLogs()
{
	RawObject* log1 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log2 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log3 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log4 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log5 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log6 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log7 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log8 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log9 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log10 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log11 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log12 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log13 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log14 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log15 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);
	RawObject* log16 = ModelFactory::texturedCyllinder(0.5, 3, 12, "textures/tree5.jpg", "textures/tree5.jpg", 8);

	log1->translate(0, 0.7, -13);
	log2->translate(1.2, 0.7, -13);
	log3->translate(-1.2, 0.7, -13);
	log4->translate(0.6, 1.5, -13);
	log5->translate(-0.6, 1.5, -13);
	log6->translate(0, 2.3, -13);

	log8->translate(2.4, 0.7, -13);
	log9->translate(-2.4, 0.7, -13);
	log10->translate(1.8, 1.5, -13);
	log11->translate(-1.8, 1.5, -13);
	log12->translate(1.2, 2.3, -13);
	log13->translate(-1.2, 2.3, -13);
	log14->translate(0.6, 3.1, -13);
	
	log15->translate(-0.6, 3.1, -13);
	log16->translate(0, 3.9, -13);


	log1->rotate(glm::radians(-90.0), 1, 0, 0);
	log2->rotate(glm::radians(-90.0), 1, 0, 0);
	log3->rotate(glm::radians(-90.0), 1, 0, 0);
	log4->rotate(glm::radians(-90.0), 1, 0, 0);
	log5->rotate(glm::radians(-90.0), 1, 0, 0);
	log6->rotate(glm::radians(-90.0), 1, 0, 0);
	log8->rotate(glm::radians(-90.0), 1, 0, 0);
	log9->rotate(glm::radians(-90.0), 1, 0, 0);
	log10->rotate(glm::radians(-90.0), 1, 0, 0);
	log11->rotate(glm::radians(-90.0), 1, 0, 0);
	log12->rotate(glm::radians(-90.0), 1, 0, 0);
	log13->rotate(glm::radians(-90.0), 1, 0, 0);
	log14->rotate(glm::radians(-90.0), 1, 0, 0);
	log15->rotate(glm::radians(-90.0), 1, 0, 0);
	log16->rotate(glm::radians(-90.0), 1, 0, 0);

	layout->addObject(log1);
	layout->addObject(log2);
	layout->addObject(log3);
	layout->addObject(log4);
	layout->addObject(log5);
	layout->addObject(log6);

	layout->addObject(log8);
	layout->addObject(log9);
	layout->addObject(log10);
	layout->addObject(log11);
	layout->addObject(log12);
	layout->addObject(log13);
	layout->addObject(log14);
	layout->addObject(log15);
	layout->addObject(log16);
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