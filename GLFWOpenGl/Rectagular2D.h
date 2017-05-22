#pragma once
#include "RawObject.h"
#include "MainWindow.h"
class Rectangular2D : public RawObject
{
public:
	Rectangular2D(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, const char* vert, const char* frag);
};

