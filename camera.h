#ifndef _camera_h
#define _camera_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
		 
#include "shader.h"

class Camera
{
public:

	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	bool firstClick = true;

	int width;
	int height;

	float defaultSpeed = 0.8f * 10;
	float fastSpeed = 4.0f * 10;
	float speed = 0.01f;
	float sensitivity = 100.0f;

	float fov = 70.0f;
	float nearPlane = 0.03f;
	float farPlane = 100.0f;

	Camera(int width, int height, glm::vec3 position, float fov = 70.0f, float nearPlane = 0.03f, float farPlane = 100.0f);

	void updateMatrix();

	void Matrix(Shader& shader, const char* uniform);

	void Inputs(GLFWwindow* window, float deltaTime);
};

#endif