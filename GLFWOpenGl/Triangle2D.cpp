#include "Triangle2D.h"
#include <GLFW\glfw3.h>


Triangle2D::Triangle2D()
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

}


Triangle2D::~Triangle2D()
{
}
