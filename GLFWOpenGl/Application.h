#pragma once
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "MainLayout.h"
#include "Animator.h"

#define WIDTH 1280
#define HEIGHT 720

class Application
{
public:
	static GLfloat deltaTime;

	Application();
	~Application();

	void Run();
private:
	static int VAOcount;
	MainWindow* screen;
	MainLayout* layout;

	Animator sawAnimator;
	Animator sawAnimator2;
	Animator logAnimator1;
	Animator logAnimator2;
	Animator logAnimator3;

	void checkKeys();

	static GLfloat lastFrame;

	void initGLFW();
	void initGLEW() throw( std::runtime_error );
	void renderAll();
	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void setUpScene();

	void setUpBase();
	void setUpLight();
	void setUpDetails();
	void setUpHouse();
	void setUpSaw();
	void setUpLogs();
	void setUpAnimatedLog();


};

extern bool keys[1024];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);