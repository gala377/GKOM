#include "ColorCube.h"






ColorCube::ColorCube(GLfloat width, GLfloat height, GLfloat length) : ColorCube(width, height, length, "shaders/defaultColor.vert", "shaders/defaultColor.frag")
{
}

ColorCube::ColorCube(GLfloat width, GLfloat height, GLfloat length, const char * vert, const char * frag) : RawObject()
{
	vertices = {
		-1.0f*width, -1.0f*height, -1.0f*length, 1.0f, 0.0f, 0.0f,//0
		1.0f*width, -1.0f*height, -1.0f*length, 0.0f, 1.0f, 0.0f,//1
		1.0f*width, -1.0f*height, 1.0f*length, 0.0f, 0.0f, 1.0f,//2
		-1.0f*width, -1.0f*height, 1.0f*length, 1.0f, 1.0f, 1.0f,//3

		-1.0f*width, 1.0f*height, -1.0f*length, 1.0f, 0.0f, 0.0f,//4
		1.0f*width, 1.0f*height, -1.0f*length, 0.0f, 1.0f, 0.0f,//5
		1.0f*width, 1.0f*height, 1.0f*length, 0.0f, 0.0f, 1.0f,//6
		-1.0f*width, 1.0f*height, 1.0f*length, 1.0f, 1.0f, 1.0f,//7

		-1.0f*width, -1.0f*height, -1.0f*length, 1.0f, 0.0f, 0.0f,//8
		-1.0f*width, 1.0f*height, -1.0f*length,	0.0f, 1.0f, 0.0f, //9
		-1.0f*width, 1.0f*height, 1.0f*length, 0.0f, 0.0f, 1.0f,//10
		-1.0f*width, -1.0f*height, 1.0f*length, 1.0f, 1.0f, 1.0f,//11

		1.0f*width, -1.0f*height, -1.0f*length, 1.0f, 0.0f, 0.0f,//12
		1.0f*width, 1.0f*height, -1.0f*length, 0.0f, 1.0f, 0.0f,//13
		1.0f*width, 1.0f*height, 1.0f*length, 0.0f, 0.0f, 1.0f,//14
		1.0f*width, -1.0f*height, 1.0f*length, 1.0f, 1.0f, 1.0f,//15

		1.0f*width, -1.0f*height, -1.0f*length, 1.0f, 0.0f, 0.0f,//16
		1.0f*width, 1.0f*height, -1.0f*length, 0.0f, 1.0f, 0.0f,//17
		-1.0f*width, 1.0f*height, -1.0f*length, 0.0f, 0.0f, 1.0f,//18
		-1.0f*width, -1.0f*height, -1.0f*length, 1.0f, 1.0f, 1.0f,//19

		1.0f*width, -1.0f*height, 1.0f*length, 1.0f, 0.0f, 0.0f,//20
		1.0f*width, 1.0f*height, 1.0f*length, 0.0f, 1.0f, 0.0f,//21
		-1.0f*width, 1.0f*height, 1.0f*length, 0.0f, 0.0f, 1.0f,//22
		-1.0f*width, -1.0f*height, 1.0f*length, 1.0f, 1.0f, 1.0f,//23
	};
	indices = {
		0,1,2, 2,3,0,
		4,6,5, 6,4,7,
		8,10,9, 10,8,11,
		12,13,14, 14,15,12,
		16,18,17, 18,16,19,
		20,21,22, 20,22,23
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);
	compileShaders(vert, frag);
}

ColorCube::~ColorCube()
{
}
