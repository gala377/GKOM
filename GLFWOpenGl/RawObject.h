#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shprogram.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class RawObject
{
public:
	RawObject();
	RawObject(std::vector<GLfloat> verts, std::vector<GLuint> indics);
	~RawObject();
	virtual void Draw();
	void compileShaders(const char* vert, const char* frag);
	void translate(GLfloat x, GLfloat y, GLfloat z);
	void rotate(GLfloat arc, GLfloat x, GLfloat y, GLfloat z);
	void scale(GLfloat x, GLfloat y, GLfloat z);
protected:
	glm::mat4 trans;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	ShaderProgram* shader;
	
	virtual void setUniforms();
};

