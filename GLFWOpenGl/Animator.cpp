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
	
	glm::vec3 translation = frames[currentFrame].translation;
	glm::vec3 rotation = (frames[currentFrame].rotation.w)* glm::vec3(frames[currentFrame].rotation);
	
	GLfloat deltaTime = (currTime - lastFrameTime);
	
	GLfloat rotatedAngle = 0;
	GLfloat speed = frames[currentFrame].speed;

	std::cout << "Curr Time:\t" << currTime << "\n";
	std::cout << "Curr Frame:\t" << currentFrame << "\n";
	std::cout << "TranslationRemeaning:\t" << remeaningTranslation().x << ", " << remeaningTranslation().y << ", " << remeaningTranslation().z << "\n";
	std::cout << "RotationRemeaning:\t" << remeaningTranslation().x << ", " << remeaningTranslation().y << ", " << remeaningTranslation().z << "\n";

	translation *= speed * deltaTime;
	rotation *= speed * deltaTime;
	rotatedAngle = (frames[currentFrame].rotation.w - frames[currentFrame].rotatedBy)*frames[currentFrame].speed * deltaTime;;

	if (positionOverShoot(translation))
	{
		translation = remeaningTranslation();
		frameFinished = true;
		std::cout << "Traslation Overshoot happened\n";
	}
	if (rotationOverShoot(rotatedAngle))
	{
		frameFinished = true;
		rotation = remeaningRotation();
	}

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
	currentFrame++;
	
	if (currentFrame == frames.size())
		currentFrame = loop ? 0 : -1;
}
