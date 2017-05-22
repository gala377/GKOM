#include "Rectagular2D.h"


Rectangular2D::Rectangular2D(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, const char * vert, const char * frag) 
	: RawObject({ x1, y1, 0.0f, x2, y2, 0.0f, x3, y3, 0.0f, x4, y4, 0.0f }, {0, 1, 3, 1, 2, 3})
{
	compileShaders(vert, frag);
}

void Rectangular2D::Draw()
{
	shader->Use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

