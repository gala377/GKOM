#include "Light.h"



Light::Light(GLfloat r, GLfloat g, GLfloat b)
	: Cube(0.1, 0.1, 0.1, "shaders/lightVert.vert", "shaders/lightFrag.frag")
{
}

Light::~Light()
{
}
