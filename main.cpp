#include "memory"
#include <mutex>
#include <random>
#include <thread>
#include <array>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ElementBufferObject.h"
#include "GLCamera.h"
#include "GLFragmentShader.h"
#include "GLShaderProgram.h"
#include "GLTexture.h"
#include "GLVertexShader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "WindowManager.h"
#include "resources.h"

namespace
{
	std::array<GLfloat, 4> Background{ (51.f / 255), (76.f / 255), (76.f / 255),1 };

	std::array<GLfloat, 12> Rect{
		-0.5f,  0.5f, 0.0f,  // top left 0
		0.5f,  0.5f, 0.0f,  // top right 1
		-0.5f, -0.5f, 0.0f, // bottom left 2
		0.5f, -0.5f, 0.0f,  // bottom right 3
	};

	std::array<GLuint, 6> indices = {
		0, 2, 3,   // first triangle
		3, 1, 0    // second triangle
	};

	std::array<GLfloat, 8> texCoords = {
		0.0f, 1.0f, // top-right  
		1.0f, 1.0f, // top-left
		0.0f, 0.0f, // bottom-left
		1.0f, 0.0f, // bottom-right
	};


	std::array<GLfloat, 180> cube = {
	/*Vertex Position*/  -0.5f, -0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 0.0f,
	/*Vertex Position*/   0.5f, -0.5f, -0.5f,  /*Texture Coordinate*/ 1.0f, 0.0f,
	/*Vertex Position*/   0.5f,  0.5f, -0.5f,  /*Texture Coordinate*/ 1.0f, 1.0f,
	/*Vertex Position*/   0.5f,  0.5f, -0.5f,  /*Texture Coordinate*/ 1.0f, 1.0f,
	/*Vertex Position*/  -0.5f,  0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 1.0f,
	/*Vertex Position*/  -0.5f, -0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 0.0f,
	/*Vertex Position*/  -0.5f, -0.5f,  0.5f,  /*Texture Coordinate*/ 0.0f, 0.0f,
	/*Vertex Position*/   0.5f, -0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 0.0f,
	/*Vertex Position*/   0.5f,  0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 1.0f,
	/*Vertex Position*/   0.5f,  0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 1.0f,
	/*Vertex Position*/  -0.5f,  0.5f,  0.5f,  /*Texture Coordinate*/ 0.0f, 1.0f,
	/*Vertex Position*/  -0.5f, -0.5f,  0.5f,  /*Texture Coordinate*/ 0.0f, 0.0f,
	/*Vertex Position*/  -0.5f,  0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 0.0f,
	/*Vertex Position*/  -0.5f,  0.5f, -0.5f,  /*Texture Coordinate*/ 1.0f, 1.0f,
	/*Vertex Position*/  -0.5f, -0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 1.0f,
	/*Vertex Position*/  -0.5f, -0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 1.0f,
	/*Vertex Position*/  -0.5f, -0.5f,  0.5f,  /*Texture Coordinate*/ 0.0f, 0.0f,
	/*Vertex Position*/  -0.5f,  0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 0.0f,
	/*Vertex Position*/   0.5f,  0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 0.0f,
	/*Vertex Position*/   0.5f,  0.5f, -0.5f,  /*Texture Coordinate*/ 1.0f, 1.0f,
	/*Vertex Position*/   0.5f, -0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 1.0f,
	/*Vertex Position*/   0.5f, -0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 1.0f,
	/*Vertex Position*/   0.5f, -0.5f,  0.5f,  /*Texture Coordinate*/ 0.0f, 0.0f,
	/*Vertex Position*/   0.5f,  0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 0.0f,
	/*Vertex Position*/  -0.5f, -0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 1.0f,
	/*Vertex Position*/   0.5f, -0.5f, -0.5f,  /*Texture Coordinate*/ 1.0f, 1.0f,
	/*Vertex Position*/   0.5f, -0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 0.0f,
	/*Vertex Position*/   0.5f, -0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 0.0f,
	/*Vertex Position*/  -0.5f, -0.5f,  0.5f,  /*Texture Coordinate*/ 0.0f, 0.0f,
	/*Vertex Position*/  -0.5f, -0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 1.0f,
	/*Vertex Position*/  -0.5f,  0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 1.0f,
	/*Vertex Position*/   0.5f,  0.5f, -0.5f,  /*Texture Coordinate*/ 1.0f, 1.0f,
	/*Vertex Position*/   0.5f,  0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 0.0f,
	/*Vertex Position*/   0.5f,  0.5f,  0.5f,  /*Texture Coordinate*/ 1.0f, 0.0f,
	/*Vertex Position*/  -0.5f,  0.5f,  0.5f,  /*Texture Coordinate*/ 0.0f, 0.0f,
	/*Vertex Position*/  -0.5f,  0.5f, -0.5f,  /*Texture Coordinate*/ 0.0f, 1.0f
	};


	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
}



int main()
{
	// https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
	spdlog::set_pattern("%^[%l][%!: %#] [thread %t]%$: %v");
	spdlog::set_level(spdlog::level::info);

	WindowManager WindowManager("OpenGL Window");
	const std::shared_ptr Window = std::make_shared<GLFWwindow*>(WindowManager.CreateGLFWWindow());

	GLShader::GLShaderProgram ShaderProgram1;
	GLShader::GLVertexShader VertexShader("default.vert");
	GLShader::GLFragmentShader FragmentShader("default.frag");
	ShaderProgram1.AttachShaders(VertexShader, FragmentShader);

	// Buffers will bind and unbind during initialisation so other objects (such as the VAO)
	// can link them as needed.
	GLShader::VertexBufferObject VBO1(cube.data(), sizeof(cube));
	GLShader::ElementBufferObject EBO1(indices.data(), sizeof(indices));
	GLShader::VertexArrayObject VAO1(&EBO1, &VBO1);

	// Create and Set Texture Uniform
	std::filesystem::path path = IMAGES_DIR / std::filesystem::path("wall.jpg");
	GLShader::GLTexture Texture(path, 512, 512);
	Texture.SetTextureUnit(GL_TEXTURE0);
	Texture.Bind();
	Texture.CreateTexture();

	const GLuint ID = ShaderProgram1.GetID();
	const GLuint PositionAttributeIndex = 0;
	const GLuint TexCoordAttributeIndex = 1;

	// Set Vertex Position Attribute
	VAO1.Bind();
	EBO1.Bind();
	VBO1.Bind();
	glBindAttribLocation(ID, PositionAttributeIndex, "vertex_position");;
	glVertexAttribPointer(PositionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(PositionAttributeIndex);

	// Set Texture Coordinate Attribute
	glBindAttribLocation(ID, TexCoordAttributeIndex, "texture_coords");
	glVertexAttribPointer(TexCoordAttributeIndex, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(TexCoordAttributeIndex);

	glUseProgram(ID);
	const GLuint ModelLocation = glGetUniformLocation(ID, "model");
	const GLuint IntensityLocation = glGetUniformLocation(ID, "color_intensity");

	std::shared_ptr<GLCamera> Camera = std::make_shared<GLCamera>(Window, ID);
	WindowManager.SetCurrentCamera(Camera);

	while (!glfwWindowShouldClose(*Window.get()))
	{
		WindowManager.Update();
		WindowManager.FillScreenColor(Background.data());

		float time = glfwGetTime();
		//glUniform1f(IntensityLocation, 1.f);
		//const glm::mat4 perspective = glm::perspective(std::abs(sin(time)), 800.0f / 600.0f, 0.1f, 100.0f);
		//glUniformMatrix4fv(PerspLocation, 1, GL_FALSE, glm::value_ptr(perspective));


		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, cubePositions[1]);
		//glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//model = glm::mat4(1.0f);
		//model = glm::translate(model, Camera->GetTarget());
		//glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		for (int idx = 0; idx < 10; idx++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[idx]);
			if (idx % 3 == 0 && idx != 0)
			{
				// Rotate each cube independently and rotate from that position
				model = glm::rotate(model, glm::radians(20.0f * idx), glm::vec3(1.0f, 0.3f, 0.5f));
				model = glm::rotate(model, time, glm::vec3(0.5f, 1.0f, 0.0f));
			}

			// Pulse each cube independently
			//glUniform1f(IntensityLocation, (sin(time) + sin(idx)) / 2.0f + 0.5f);
			glUniform1f(IntensityLocation, 1.f);
			glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(*Window.get());
	}

	return 0;
}