#include "Animator.h"
#include <iostream>


Animator::Animator()
{
	lastFrameTime = glfwGetTime();
}

Animator::~Animator()
{
}

void Animator::addObject(RawObject * obj)
{
	objects.push_back(obj);
}

void Animator::removeObject(RawObject * obj)
{
	for (int i = 0; i < objects.size(); i++)
		if (objects[i] == obj)
			objects.erase(objects.begin()+i);
}

void Animator::addFrame(Frame f)
{
	frames.push_back(f);
}

void Animator::start()
{
	currentFrame = 0;
	lastFrameTime = glfwGetTime();
}

void Animator::update()
{
	if (currentFrame < 0)
		return;
	
	GLfloat time = updateFrame();

	currentFrameTime += time - lastFrameTime;
	lastFrameTime = time;
}

GLfloat Animator::updateFrame()
{
	bool nextFrame = true;
	const GLfloat epsilon = 0.001;

	GLfloat currTime = glfwGetTime();
	std::cout << "Curr Time:\t" << currTime << "\n";
	std::cout << "Curr Frame:\t" << currentFrame << "\n";

	glm::vec3 translation = frames[currentFrame].transaltion - frames[currentFrame].translatedBy;
	glm::vec3 rotation = (frames[currentFrame].rotation.w - frames[currentFrame].rotatedBy)* glm::vec3(frames[currentFrame].rotation);
	GLfloat deltaTime = (currTime - lastFrameTime);
	GLfloat rotatedAngle = 0;

	std::cout << "Translation:\t" << translation.x << ", " << translation.y << ", " << translation.z << "\n";
	std::cout << "Rotation:\t" << rotation.x << ", " << rotation.y << ", " << rotation.z << "\n";

	if (glm::length(translation) > epsilon || glm::length(rotation) > epsilon) 
	{
		nextFrame = false;
		translation *= frames[currentFrame].speed * deltaTime;
		rotation *= frames[currentFrame].speed * deltaTime;
	}

	rotatedAngle = (frames[currentFrame].rotation.w - frames[currentFrame].rotatedBy)*frames[currentFrame].speed * deltaTime;;

	std::cout << "Translaring By:\t" << translation.x << ", " << translation.y << ", " << translation.z << "\n";
	std::cout << "Rotating By:\t" << rotation.x << ", " << rotation.y << ", " << rotation.z << "\n\n";

	for (RawObject* el : objects) 
	{
		el->translate(translation.x, translation.y, translation.z);
		el->rotate(rotation.x, 1, 0, 0);
		el->rotate(rotation.y, 0, 1, 0);
		el->rotate(rotation.z, 0, 0, 1);
	}

	frames[currentFrame].translatedBy += translation;
	frames[currentFrame].rotatedBy += rotatedAngle;
	
	if (nextFrame)
	{
		frames[currentFrame].rotatedBy = 0;
		frames[currentFrame].translatedBy = glm::vec3(0.0);
		currentFrame++;
	}
	if (currentFrame == frames.size())
		currentFrame = loop ? 0 : -1;
			
	return currTime;
}
