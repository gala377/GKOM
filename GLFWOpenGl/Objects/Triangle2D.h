#pragma once
#include "..\MainWindow.h"
#include "E:\Programowanie\OpenGLTEST\GLFWOpenGl\GLFWOpenGl\RawObject.h"
class Triangle2D : public RawObject
{
public:
	Triangle2D();
	Triangle2D(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, const char* vert, const char* frag, GLuint VBO);
	~Triangle2D();
	void defineVertertices(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3);
	void Draw(GLuint VBO);
	void Init();
private:
	GLfloat* vertices;
};

