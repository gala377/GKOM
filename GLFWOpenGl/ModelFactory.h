#pragma once
#include "Objects\Objects.h"
#include <vector>
#include <iostream>
class ModelFactory
{
public:
	~ModelFactory();

	static RawObject* cube(GLfloat width, GLfloat height, GLfloat length);
	static RawObject* cube(GLfloat width, GLfloat height, GLfloat length, const char* vert, const char* frag);

	static RawObject* colorCube(GLfloat width, GLfloat height, GLfloat length);
	static RawObject* solidColorCube(GLfloat width, GLfloat height, GLfloat length, glm::vec3 color);
	static RawObject* triangle2D();
	static RawObject* cyllinder(GLfloat radius, GLfloat height, GLuint segments);
	static RawObject* cyllinder(GLfloat radius, GLfloat height, GLuint segments, const char* vert, const char* frag);
	static RawObject* solidColorCyllinder(GLfloat radius, GLfloat height, GLuint segments, glm::vec3 color);

	static RawObject* gnCube(GLfloat width, GLfloat height, GLfloat length, glm::vec3 color, glm::vec3 ambientColor, glm::vec3 diffColor, glm::vec3 specColor, GLfloat shiness);
	static RawObject* gnCyllinder(GLfloat radius, GLfloat height, GLuint segments, glm::vec3 ambientColor, glm::vec3 diffColor, glm::vec3 specColor, GLfloat shiness);
	static RawObject* texturedCube(GLfloat width, GLfloat height, GLfloat length, const char* diffTexture, const char* specTexture, GLfloat shiness);
	static RawObject* texturedCyllinder(GLfloat radius, GLfloat height, GLuint segments, const char* diffTexture, const char* specTexture, GLfloat shiness);
private:
	ModelFactory();

};

