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
	bool frameFinished = false;
	GLfloat currTime = glfwGetTime();
	GLfloat deltaTime = (currTime - lastFrameTime);

	if (frames[currentFrame].caller)
	{
		frames[currentFrame].receiver->start();
		nextFrame();
		return currTime;
	}
	wait(deltaTime);

	glm::vec3 translation = frames[currentFrame].translation;
	glm::vec3 rotation = (frames[currentFrame].rotation.w)* glm::vec3(frames[currentFrame].rotation);
	
	GLfloat rotatedAngle = 0;
	GLfloat speed = frames[currentFrame].speed;

	translation *= speed * deltaTime;
	rotation *= speed * deltaTime;
	rotatedAngle = (frames[currentFrame].rotation.w - frames[currentFrame].rotatedBy)*frames[currentFrame].speed * deltaTime;;

	if (positionOverShoot(translation))
	{
		translation = remeaningTranslation();
		frameFinished = true;
	}
	if (rotationOverShoot(rotatedAngle))
	{
		frameFinished = true;
		rotation = remeaningRotation();
	}

	for (RawObject* el : objects) 
	{
		el->translate(translation.x, translation.y, translation.z);
		el->rotate(rotation.x, 1, 0, 0);
		el->rotate(rotation.y, 0, 1, 0);
		el->rotate(rotation.z, 0, 0, 1);
	}

	frames[currentFrame].translatedBy += translation;
	frames[currentFrame].rotatedBy += rotatedAngle;
	
	if (frameFinished)
		nextFrame();

	return currTime;
}

glm::vec3 Animator::remeaningTranslation()
{
	return frames[currentFrame].translation - frames[currentFrame].translatedBy;
}

glm::vec3 Animator::remeaningRotation()
{
	return (frames[currentFrame].rotation.w - frames[currentFrame].rotatedBy)* glm::vec3(frames[currentFrame].rotation);
}

bool Animator::positionOverShoot(glm::vec3 translation)
{
	glm::vec3 dst = frames[currentFrame].translation;
	glm::vec3 position = frames[currentFrame].translatedBy;

	GLfloat distToDest = glm::length(position - dst);
	GLfloat distAfterTrans = glm::length(position + translation - dst);
	
	if (distAfterTrans > distToDest)
		return true;
	return false;
}

bool Animator::rotationOverShoot(GLfloat angle)
{
	GLfloat dst = frames[currentFrame].rotation.w * glm::length(glm::vec3(frames[currentFrame].rotation));
	GLfloat position = frames[currentFrame].rotatedBy;

	GLfloat distToDest = position - dst;
	GLfloat distAfterTrans = position + angle - dst;
	if (distAfterTrans > distToDest)
		return true;
	return false;
}

void Animator::nextFrame()
{
	frames[currentFrame].rotatedBy = 0;
	frames[currentFrame].translatedBy = glm::vec3(0.0);
	frames[currentFrame].waiting = 0;
	currentFrame++;
	
	if (currentFrame == frames.size())
		currentFrame = loop ? 0 : -1;
}

void Animator::wait(GLfloat deltaTime)
{
	if (frames[currentFrame].waiting  < frames[currentFrame].wait)
	{
		std::cout << "Waiting: " << frames[currentFrame].waiting << " Wait: " << frames[currentFrame].wait << "\n";
		frames[currentFrame].waiting += deltaTime;
		if (frames[currentFrame].waiting >= frames[currentFrame].wait)
			nextFrame();
	}
}
