#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <json/json.h>


#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"
#include "camera.h"
#include "mesh.h"
#include "model.h"

const int width = 1600;
const int height = 900;
const char* title = "G3DEngine";

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW Window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	// OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_MULTISAMPLE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// ========== OPENGL OPTIONS

	glViewport(0, 0, width, height);



	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	glm::vec3 dirLightDirection = glm::vec3(-0.5f, 0.3f, 0.6f);

	shaderProgram.Activate();
	shaderProgram.SetMat4("model", pyramidModel);

	shaderProgram.SetVec3("directionalLight.direction", dirLightDirection);
	shaderProgram.SetVec4("directionalLight.diffuse", glm::vec4(1.0f));
	shaderProgram.SetFloat("directionalLight.ambient", 0.5f);
	shaderProgram.SetFloat("directionalLight.intensity", 1.0f);

	shaderProgram.SetVec4("pointLights[0].diffuse", lightColor);
	shaderProgram.SetVec3("pointLights[0].position", lightPos);
	shaderProgram.SetFloat("pointLights[0].ambient", 0.5f);
	shaderProgram.SetFloat("pointLights[0].constant", 0.1f);
	shaderProgram.SetFloat("pointLights[0].linear", .2f);
	shaderProgram.SetFloat("pointLights[0].quadratic", .2f * .2f);

	Camera camera(width, height, glm::vec3(0.0f, 0.4f, 1.5f));

	Model model("scene.gltf");

	float time = (float)glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		float deltaTime = (float)glfwGetTime() - time;
		time = (float)glfwGetTime();

		glfwPollEvents();

		camera.Inputs(window, deltaTime);
		camera.updateMatrix();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model.Draw(shaderProgram, camera);


		glfwSwapBuffers(window);
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}