#include "Application.h"
#include "Objects\Triangle2D.h"
#include "Rectagular2D.h"
#include "Camera.h"

int Application::VAOcount = 0;

Application::Application()
{
	try {
		initGLFW();
		screen = new MainWindow(1280, 720, "Test window");
		glfwMakeContextCurrent(screen->window);
		screen->setViewport();
		initGLEW();
		
		glfwSetKeyCallback(screen->window, key_callback);
		layout = new MainLayout(screen);
		glEnable(GL_DEPTH_TEST);
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
	Triangle2D* tra2D2 = new Triangle2D(-1, -1, -1, 0, 0, 0, "Text.vert", "basiccolor.frag");
	//layout->addObject(tra2D2);
	Rectangular2D* rec2D = new Rectangular2D(1,1, 1,0, 0,0, 0, 1, "Text.vert", "basiccolor.frag");
	//layout->addObject(rec2D);

	//rec2D->rotate(-10, 1, 0, 0);

	RawObject* cube = new RawObject(
	{
		-1.0f, -1.0f, -1.0f, //0
		1.0f, -1.0f, -1.0f, //1
		1.0f, -1.0f, 1.0f, //2
		-1.0f, -1.0f, 1.0f, //3

		-1.0f, 1.0f, -1.0f, //4
		1.0f, 1.0f, -1.0f, //5
		1.0f, 1.0f, 1.0f, //6
		-1.0f, 1.0f, 1.0f, //7

		-1.0f, -1.0f, -1.0f, //8
		-1.0f, 1.0f, -1.0f, //9
		-1.0f, 1.0f, 1.0f, //10
		-1.0f, -1.0f, 1.0f, //11

		1.0f, -1.0f, -1.0f, //12
		1.0f, 1.0f, -1.0f, //13
		1.0f, 1.0f, 1.0f, //14
		1.0f, -1.0f, 1.0f, //15

		1.0f, -1.0f, -1.0f, //16
		1.0f, 1.0f, -1.0f, //17
		-1.0f, 1.0f, -1.0f, //18
		-1.0f, -1.0f, -1.0f, //19

		1.0f, -1.0f, 1.0f, //20
		1.0f, 1.0f, 1.0f, //21
		-1.0f, 1.0f, 1.0f, //22
		-1.0f, -1.0f, 1.0f, //23
	}, {
		0,1,2, 2,3,0,
		4,6,5, 6,4,7,
		8,10,9, 10,8,11,
		12,13,14, 14,15,12,
		16,18,17, 18,16,19,
		20,21,22, 20,22,23
	});
	cube->compileShaders("Text.vert", "basiccolor.frag");
	layout->addObject(cube);

	while (!glfwWindowShouldClose(screen->window))
	{


		glfwPollEvents();
		renderAll();
		cube->rotate(0.001, 1, 0, 0);
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
}
