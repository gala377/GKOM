#pragma once
#include "..\MainWindow.h"
#include "E:\Programowanie\OpenGLTEST\GLFWOpenGl\GLFWOpenGl\RawObject.h"
class Triangle2D : RawObject
{
public:
	Triangle2D();
	~Triangle2D();
	void defineVertertices(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3);
	void Draw(GLuint VBO);
private:
	GLfloat* vertices;
};
