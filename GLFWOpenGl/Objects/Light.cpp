#include "Light.h"



void Light::addNewLight(glm::vec3 postion, glm::vec3 color)
{
	Light* light = new Light(color.x, color.y, color.z);
	light->translate(postion.x, postion.y, postion.z);
	lights.push_back(light);
}

Light::Light(GLfloat r, GLfloat g, GLfloat b)
	: Cube(0.1, 0.1, 0.1, "shaders/lightVert.vert", "shaders/lightFrag.frag")
{
}

Light::~Light()
{
}
