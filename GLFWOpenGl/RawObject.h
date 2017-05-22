#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shprogram.h"


class RawObject
{
public:
	RawObject();
	~RawObject();
	virtual void Draw() = 0;
	void compileShaders(const char* vert, const char* frag);
protected:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	ShaderProgram* shader;
};

