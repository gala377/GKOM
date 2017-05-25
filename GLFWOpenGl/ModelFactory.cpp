#include "ModelFactory.h"
#include "Camera.h"


ModelFactory::ModelFactory()
{
}


ModelFactory::~ModelFactory()
{
}

RawObject* ModelFactory::cube(GLfloat width, GLfloat height, GLfloat length)
{
	return new Cube(width, height, length);
}

RawObject * ModelFactory::cube(GLfloat width, GLfloat height, GLfloat length, const char * vert, const char * frag)
{
	return new Cube(width, height, length, vert, frag);
}

RawObject * ModelFactory::colorCube(GLfloat width, GLfloat height, GLfloat length)
{
	return new ColorCube(width, height, length);
}

RawObject * ModelFactory::solidColorCube(GLfloat width, GLfloat height, GLfloat length, glm::vec3 color)
{
	return new SolidColorCube(width, height, length, color);
}

RawObject * ModelFactory::triangle2D()
{
	return new Triangle2D();
}

RawObject * ModelFactory::cyllinder(GLfloat radius, GLfloat height, GLuint segments)
{
	glm::vec4 normal = glm::vec4(1, 0, 0, 1);
	glm::vec3 points[4];
	points[0] = glm::vec3(radius, height, 0);
	points[1] = glm::vec3(radius, -height, 0);
	GLfloat angle = 360.0f / (GLfloat)segments;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLuint> indices;

	glm::mat4 rotation = glm::mat4(1.0f);
	rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(0, 1, 0));

	{
		vertices.push_back(0);
		vertices.push_back(height);
		vertices.push_back(0);

		vertices.push_back(0);
		vertices.push_back(-height);
		vertices.push_back(0);

		normals.push_back(0);
		normals.push_back(1);
		normals.push_back(0);

		normals.push_back(0);
		normals.push_back(-1);
		normals.push_back(0);

	}

	for (int i = 0; i < segments; i++)
	{
		normal = rotation * normal;
		points[2] = glm::vec3(normal.x*radius, height, normal.z*radius);
		points[3] = glm::vec3(normal.x*radius, -height, normal.z*radius);

		for (int j = 0; j < 4; j++)
		{
			vertices.push_back(points[j].x);
			vertices.push_back(points[j].y);
			vertices.push_back(points[j].z);
			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);
		}

		for (int i = 0; i < 2; i++)
		{
			vertices.push_back(points[2 * i].x);
			vertices.push_back(points[2 * i].y);
			vertices.push_back(points[2 * i].z);

			vertices.push_back(points[2 * i + 1].x);
			vertices.push_back(points[2 * i + 1].y);
			vertices.push_back(points[2 * i + 1].z);

			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			normals.push_back(0);
			normals.push_back(-1);
			normals.push_back(0);

		}

		//wall
		indices.push_back(0 + (i * 8) + 2);
		indices.push_back(1 + (i * 8) + 2);
		indices.push_back(2 + (i * 8) + 2);
		indices.push_back(1 + (i * 8) + 2);
		indices.push_back(2 + (i * 8) + 2);
		indices.push_back(3 + (i * 8) + 2);

		//caps 
		indices.push_back(4 + (i * 8) + 2);
		indices.push_back(6 + (i * 8) + 2);
		indices.push_back(0);
		indices.push_back(5 + (i * 8) + 2);
		indices.push_back(7 + (i * 8) + 2);
		indices.push_back(1);


		points[0] = points[2];
		points[1] = points[3];
	}


	RawObject* mesh = new RawObject(vertices, normals, indices);
	return mesh;
}

RawObject * ModelFactory::cyllinder(GLfloat radius, GLfloat height, GLuint segments, const char * vert, const char * frag)
{
	RawObject* mesh = cyllinder(radius, height, segments);
	mesh->compileShaders(vert, frag);
	return mesh;
}

RawObject * ModelFactory::solidColorCyllinder(GLfloat radius, GLfloat height, GLuint segments, glm::vec3 color)
{
	glm::vec4 normal = glm::vec4(1, 0, 0, 1);
	glm::vec3 points[4];
	points[0] = glm::vec3(radius, height, 0);
	points[1] = glm::vec3(radius, -height, 0);
	GLfloat angle = 360.0f / (GLfloat)segments;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLuint> indices;

	glm::mat4 rotation = glm::mat4(1.0f);
	rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(0, 1, 0));
	
	{
		vertices.push_back(0);
		vertices.push_back(height);
		vertices.push_back(0);

		vertices.push_back(0);
		vertices.push_back(-height);
		vertices.push_back(0);

		normals.push_back(0);
		normals.push_back(1);
		normals.push_back(0);
		
		normals.push_back(0);
		normals.push_back(-1);
		normals.push_back(0);

	}

	for (int i = 0; i < segments; i++)
	{
		normal = rotation * normal;
		points[2] = glm::vec3(normal.x*radius, height, normal.z*radius);
		points[3] = glm::vec3(normal.x*radius, -height, normal.z*radius);

		for (int j = 0; j < 4; j++)
		{
			vertices.push_back(points[j].x);
			vertices.push_back(points[j].y);
			vertices.push_back(points[j].z);
			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);
		}

		for (int i = 0; i < 2; i++)
		{
			vertices.push_back(points[2*i].x);
			vertices.push_back(points[2*i].y);
			vertices.push_back(points[2*i].z);

			vertices.push_back(points[2*i + 1].x);
			vertices.push_back(points[2*i + 1].y);
			vertices.push_back(points[2*i + 1].z);

			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);

			normals.push_back(0);
			normals.push_back(-1);
			normals.push_back(0);

		}

		//wall
		indices.push_back(0 + (i * 8) + 2);
		indices.push_back(1 + (i * 8) + 2);
		indices.push_back(2 + (i * 8) + 2);
		indices.push_back(1 + (i * 8) + 2);
		indices.push_back(2 + (i * 8) + 2);
		indices.push_back(3 + (i * 8) + 2);

		//caps 
		indices.push_back(4 + (i * 8) + 2);
		indices.push_back(6 + (i * 8) + 2);
		indices.push_back(0);
		indices.push_back(5 + (i * 8) + 2);
		indices.push_back(7 + (i * 8) + 2);
		indices.push_back(1);


		points[0] = points[2];
		points[1] = points[3];
	}

	SolidColorCyllinder* cyllinder = new SolidColorCyllinder(vertices, normals, indices);
	cyllinder->setColor(glm::vec4(color, 1.0f));
	cyllinder->compileShaders("shaders/defaultLight.vert", "shaders/defaultLightSpecular.frag");

	return cyllinder;
}