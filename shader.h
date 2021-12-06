#ifndef _shader_h
#define _shader_h

#include <glad/glad.h>
#include <iostream>
#include <cerrno>
#include "utils.h"

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:

	GLuint ID;

	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void Activate();
	void Delete();

    void UpdateEngineUniforms(float time) const;

    void SetBool(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }

    void SetInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }

    void SetFloat(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }

    void SetVec2(const std::string& name, glm::vec2 value) const { glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value)); }

    void SetVec2(const std::string& name, float x, float y) const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(glm::vec2(x, y))); }

    void SetVec3(const std::string& name, glm::vec3 value) const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value)); }

    void SetVec3(const std::string& name, float x, float y, float z) const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(glm::vec3(x, y, z))); }

    void SetVec4(const std::string& name, glm::vec4 value) const { glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value)); }

    void SetVec4(const std::string& name, float x, float y, float z, float w) const { glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(glm::vec4(x, y, z, w))); }

    void SetMat4(const std::string& name, glm::mat4 value) const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); }

    static void UseZero() { glUseProgram(0); }

};

#endif