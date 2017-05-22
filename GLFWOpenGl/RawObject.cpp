#include "RawObject.h"
#include "Application.h"


RawObject::RawObject()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	shader = nullptr;

}

RawObject::~RawObject()
{
	delete shader;
}

void RawObject::compileShaders(const char* frag, const char* vert)
{
	if (shader != nullptr)
		delete shader;
	shader = new ShaderProgram(frag, vert);
}

