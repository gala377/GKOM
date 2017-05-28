#include "TexturedCube.h"
#include "Light.h"
#include <SOIL.h>

TexturedCube::TexturedCube(GLfloat width, GLfloat height, GLfloat length) :
	TexturedCube(width, height, length, "shaders/materialMapped.vert", "shaders/materialMapped.frag", "textures/wood.png", "textures/woodSpecular.png")
{
}

TexturedCube::TexturedCube(GLfloat width, GLfloat height, GLfloat length, const char* diffText, const char* specText) :
		TexturedCube(width, height, length, "shaders/materialMapped.vert", "shaders/materialMapped.frag", diffText, specText)
{
}

TexturedCube::TexturedCube(GLfloat width, GLfloat height, GLfloat length, const char* vert, const char* frag, const char* diffText, const char* specText) :
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
}, {
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
}, {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f


}, {
	0,1,2, 2,3,0,
	4,6,5, 6,4,7,
	8,10,9, 10,8,11,
	12,13,14, 14,15,12,
	16,18,17, 18,16,19,
	20,21,22, 20,22,23
})
{
	// Set texture units
	compileShaders(vert, frag);
	//Load Texture
	glGenTextures(1, &diffuseMap);
	int textWidth, textHeight;
	unsigned char* image;
	// Diffuse map
	image = SOIL_load_image(diffText, &textWidth, &textHeight, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw std::runtime_error("Could not find texture");
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textWidth, textHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	shader->Use();
	//set Texture location
	glUniform1i(glGetUniformLocation(shader->get_programID(), "material.diffuse"), 0);

}

TexturedCube::~TexturedCube()
{
}


void TexturedCube::setMaterial(glm::vec3 diffColor, glm::vec3 specColor, GLfloat shiness)
{
	diffuse = diffColor;
	specular = specColor;
	this->shiness = shiness;
}

void TexturedCube::setUniforms()
{
	RawObject::setUniforms();


	GLint viewPosLoc = glGetUniformLocation(shader->get_programID(), "viewPos");

	GLint matSpecularLoc = glGetUniformLocation(shader->get_programID(), "material.specular");
	GLint matShineLoc = glGetUniformLocation(shader->get_programID(), "material.shininess");

	GLint lightAmbientLoc = glGetUniformLocation(shader->get_programID(), "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(shader->get_programID(), "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(shader->get_programID(), "light.specular");
	GLint lightPosLoc = glGetUniformLocation(shader->get_programID(), "light.position");

	glUniform3f(matSpecularLoc, specular.x, specular.y, specular.z);
	glUniform1f(matShineLoc, shiness);

	glUniform3f(viewPosLoc, mainCamera.cameraPos.x, mainCamera.cameraPos.y, mainCamera.cameraPos.z);

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	for (auto light : Light::lights)
	{
		glUniform3f(lightPosLoc, light->getPosition().x, light->getPosition().y, light->getPosition().z);
		glUniform3f(lightAmbientLoc, light->ambient.x, light->ambient.y, light->ambient.z);
		glUniform3f(lightDiffuseLoc, light->diffuse.x, light->diffuse.y, light->diffuse.z);
		glUniform3f(lightSpecularLoc, light->specular.x, light->specular.y, light->specular.z);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
}
