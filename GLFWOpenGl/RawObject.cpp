#include "RawObject.h"
#include "Application.h"


RawObject::RawObject()
{
	glGenVertexArrays(Application::assignVAO(), &VAO);
}

RawObject::~RawObject()
{
	delete shader;
}

void RawObject::compileShaders(const char* frag, const char* vert)
{
	shader = new ShaderProgram(frag, vert);
}

