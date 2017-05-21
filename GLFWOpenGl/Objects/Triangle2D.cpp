#include "Triangle2D.h"



Triangle2D::Triangle2D()
{
	vertices = new GLfloat[9];
	vertices[2] = 0.0f;
	vertices[5] = 0.0f;
	vertices[8] = 0.0f;
}


Triangle2D::~Triangle2D()
{
	delete[] vertices;
}

void Triangle2D::defineVertertices(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3)
{
	vertices[0] = x1;
	vertices[1] = y1;

	vertices[2] = x2;
	vertices[3] = y2;

	vertices[6] = x3;
	vertices[7] = y3;

}

void Triangle2D::Draw(GLuint VBO)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

