#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shprogram.h"
#include <vector>


class RawObject
{
public:
	RawObject();
	RawObject(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
	~RawObject();
	virtual void Draw();
	void compileShaders(const char* vert, const char* frag);
protected:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	ShaderProgram* shader;
};

