#include "Cube.h"





Cube::Cube(GLfloat width, GLfloat height, GLfloat length) : Cube(width, height, length, "shaders/default.vert", "shaders/default.frag")
{
	
}

Cube::Cube(GLfloat width, GLfloat height, GLfloat length, const char * vert, const char * frag) : 
	RawObject({
			-1.0f*width, -1.0f*height, -1.0f*length, //0
			1.0f*width, -1.0f*height, -1.0f*length, //1
			1.0f*width, -1.0f*height, 1.0f*length, //2
			-1.0f*width, -1.0f*height, 1.0f*length, //3

			-1.0f*width, 1.0f*height, -1.0f*length, //4
			1.0f*width, 1.0f*height, -1.0f*length, //5
			1.0f*width, 1.0f*height, 1.0f*length, //6
			-1.0f*width, 1.0f*height, 1.0f*length, //7

			-1.0f*width, -1.0f*height, -1.0f*length, //8
			-1.0f*width, 1.0f*height, -1.0f*length, //9
			-1.0f*width, 1.0f*height, 1.0f*length, //10
			-1.0f*width, -1.0f*height, 1.0f*length, //11

			1.0f*width, -1.0f*height, -1.0f*length, //12
			1.0f*width, 1.0f*height, -1.0f*length, //13
			1.0f*width, 1.0f*height, 1.0f*length, //14
			1.0f*width, -1.0f*height, 1.0f*length, //15

			1.0f*width, -1.0f*height, -1.0f*length, //16
			1.0f*width, 1.0f*height, -1.0f*length, //17
			-1.0f*width, 1.0f*height, -1.0f*length, //18
			-1.0f*width, -1.0f*height, -1.0f*length, //19

			1.0f*width, -1.0f*height, 1.0f*length, //20
			1.0f*width, 1.0f*height, 1.0f*length, //21
			-1.0f*width, 1.0f*height, 1.0f*length, //22
			-1.0f*width, -1.0f*height, 1.0f*length, //23
		},{
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f
		},{
			0,1,2, 2,3,0,
			4,6,5, 6,4,7,
			8,10,9, 10,8,11,
			12,13,14, 14,15,12,
			16,18,17, 18,16,19,
			20,21,22, 20,22,23
		})
{
	compileShaders(vert, frag);
}

Cube::~Cube()
{
}
