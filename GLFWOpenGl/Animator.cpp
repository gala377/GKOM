#include "Animator.h"



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
	if (currentFrameTime >= frames[currentFrame].time)
	{
		currentFrame++;
		currentFrameTime = 0;
		if (currentFrame == frames.size())
			currentFrame = -1;
	}

	if (currentFrame < 0)
		return;
	
	updateFrame();

	currentFrameTime += glfwGetTime() - lastFrameTime;
	lastFrameTime = glfwGetTime();
}

void Animator::updateFrame()
{
	for (RawObject* el : objects)
	{
		glm::vec3 postion = el->getPosition();
		glm::vec3 rotation = el->

	}
}
