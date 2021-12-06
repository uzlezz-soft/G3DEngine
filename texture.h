#ifndef _texture_h
#define _texture_h

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shader.h"

class Texture
{
public:

	GLuint ID;
	const char* typeStr;
	GLenum type;
	GLuint unit;

	Texture(const char* image, const char* texType = "diffuse", GLuint slot = 0);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};
#endif