#include "Triangle2D.h"
#include "..\shprogram.h"


Triangle2D::Triangle2D() : RawObject()
{
	vertices = new GLfloat[9];
	vertices[2] = 0.0f;
	vertices[5] = 0.0f;
	vertices[8] = 0.0f;
}

Triangle2D::Triangle2D(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, const char * vert, const char * frag) : 
	RawObject({ x1, y1, 0.0f, x2, y2, 0.0f, x3, y3, 0.0f }, {0, 1, 2})
{
	compileShaders(vert, frag);
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

void Triangle2D::Init()
{
	compileShaders("Text.vert", "basiccolor.frag");

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left  
		0.5f, -0.5f, 0.0f, // Right 
		0.0f,  0.5f, 0.0f  // Top   
	};
	GLuint VBO;
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);
}

