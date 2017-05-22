#include "RawObject.h"
#include "Application.h"



RawObject::RawObject()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	shader = nullptr;
	trans = glm::mat4(1.0);

}

RawObject::RawObject(std::vector<GLfloat> verts, std::vector<GLuint> indics) : RawObject()
{
	vertices = std::move(verts);
	indices = std::move(indics);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);

}

RawObject::~RawObject()
{
	delete shader;
}

void RawObject::Draw()
{	
	shader->Use();
	GLuint transformLoc = glGetUniformLocation(shader->get_programID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void RawObject::compileShaders(const char* frag, const char* vert)
{
	if (shader != nullptr)
		delete shader;
	shader = new ShaderProgram(frag, vert);
}

void RawObject::translate(GLfloat x, GLfloat y, GLfloat z)
{
	trans = glm::translate(trans, glm::vec3(x, y, z));
}

void RawObject::rotate(GLfloat arc, GLfloat x, GLfloat y, GLfloat z)
{
	trans = glm::rotate(trans, arc, glm::vec3(x, y, z));
}

void RawObject::scale(GLfloat x, GLfloat y, GLfloat z)
{
	trans = glm::scale(trans, glm::vec3(x, y, z));
}


