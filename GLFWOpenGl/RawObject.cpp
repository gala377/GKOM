#include "RawObject.h"
#include "Application.h"


RawObject::RawObject()
{
	glGenVertexArrays(Application::assignVAO(), &VAO);
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

