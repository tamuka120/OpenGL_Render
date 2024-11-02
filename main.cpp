#include <mutex>
#include <random>
#include <thread>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ElementBufferObject.h"
#include "GLShaderProgram.h"
#include "GLFragmentShader.h"
#include "GLVertexShader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "WindowManager.h"

void drawArrays(
	GLShader::GLShaderProgram& ShaderProgram,
	GLShader::VertexArrayObject& VAO,
	float intensity)
{
	//float timeValue = glfwGetTime();
	GLuint id = ShaderProgram.GetID();
	glUseProgram(id);
	glUniform1f(
		glGetUniformLocation(id, "color_intensity"),
		intensity);

	VAO.BindAllBuffers();
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, VAO.GetVertexBufferSize() / 3);
}

void drawElements(
	GLShader::GLShaderProgram& ShaderProgram, 
	GLShader::VertexArrayObject& VAO,
	float intensity)
{
	GLuint id = ShaderProgram.GetID();
	glUseProgram(id);
	glUniform1f(
		glGetUniformLocation(id, "color_intensity"),
		intensity);

	VAO.BindAllBuffers();
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


int main()
{
	// https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
	spdlog::set_pattern("%^[%l][%!: %#] [thread %t]%$: %v");
	spdlog::set_level(spdlog::level::info);

	std::array<GLfloat,4> Background{ (51.f / 255), (76.f / 255), (76.f / 255),1 };
	std::array<GLfloat, 12> triangleLeft{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	std::array<GLuint, 6> indices = {  // note that we start from 0!
	   0, 1, 3,   // first triangle
	   1, 2, 3    // second triangle
	};

	std::array<GLfloat, 9> triangleRight{
		.25, 0, 0,     // bottom left
		.5, 0, 0,	   // bottom right
		.365, .365, 0, // top
	};



	WindowManager WindowManager("OpenGL Window");
	GLFWwindow * Window = WindowManager.CreateGLFWWindow();

	GLShader::GLShaderProgram ShaderProgram1;
	GLShader::GLShaderProgram ShaderProgram2;
	GLShader::GLVertexShader VertexShader("default.vert");
	GLShader::GLFragmentShader FragmentShader("default.frag");
	GLShader::GLFragmentShader FragmentShader2("default2.frag");
	ShaderProgram1.AttachShaders(VertexShader, FragmentShader);
	ShaderProgram2.AttachShaders(VertexShader, FragmentShader2);
	//glBindAttribLocation(ShaderProgram1.GetID(), 0, "vertex_position");
	//glBindAttribLocation(ShaderProgram2.GetID(), 0, "vertex_position");

	// Buffers will bind and unbind during initialisation so other objects can link them as needed.
	GLShader::VertexBufferObject VBO1(triangleLeft.data(), sizeof(triangleLeft));
	GLShader::ElementBufferObject EBO1(indices.data(), sizeof(indices));
	GLShader::VertexArrayObject VAO1(&EBO1, &VBO1);
	VAO1.BindAllBuffers();
	VAO1.LinkBuffers();

	GLShader::ElementBufferObject EBO2;
	GLShader::VertexBufferObject VBO2(triangleRight.data(), sizeof(triangleRight));
	GLShader::VertexArrayObject VAO2(&EBO2, &VBO2);
	VAO2.BindAllBuffers();
	VAO2.LinkBuffers();

	while (!glfwWindowShouldClose(Window))
	{
		SPDLOG_TRACE("POLL EVENTS");
		glfwPollEvents();

		WindowManager.Update();
		WindowManager.FillScreenColor(Background.data());

		float timeValue = glfwGetTime();
		drawElements(ShaderProgram1, VAO1, sin(timeValue) / 2.0f + 0.5f);
		drawArrays(ShaderProgram2, VAO2, cos(timeValue) / 2.0f + 0.5f);

		glfwSwapBuffers(Window);
	}


	return 0;
}
