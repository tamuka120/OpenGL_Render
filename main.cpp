#pragma once

#include <mutex>
#include <random>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "spdlog/spdlog.h"

#include "ElementBufferObject.h"
#include "GLShaderProgram.h"
#include "GLFragmentShader.h"
#include "GLVertexShader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "WindowManager.h"

#ifdef _DEBUG
int main()
{
	// https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
	spdlog::set_pattern("%^[%l][%!: %#] [thread %t]%$: %v");
	spdlog::set_level(spdlog::level::debug);
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Setup to log to file instead
	spdlog::set_level(spdlog::level::off);
#endif // _DEBUG

	// Formatting Guide: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
	try
	{
		GLfloat Background[] = {(51.f/255), (76.f/255), (76.f/255),1};
		//GLfloat vertices[] =
		//{
		//	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		//	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		//	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner

		//	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		//	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		//	0.0f, -1.0f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
		//};

		//GLfloat vertices[] = {
		//	// first triangle
		//	 0.5f,  0.5f, 0.0f,  // top right
		//	 0.5f, -0.5f, 0.0f,  // bottom right
		//	-0.5f,  0.5f, 0.0f,  // top left 
		//	// second triangle
		//	 0.5f, -0.5f, 0.0f,  // bottom right
		//	-0.5f, -0.5f, 0.0f,  // bottom left
		//	-0.5f,  0.5f, 0.0f   // top left
		//};

		//GLuint indices[] = {  // note that we start from 0!
		//	//0, 1, 3,   // first triangle
		//	//1, 2, 3    // second triangle
		//	0, 1, 2
		//};

		GLfloat triangle1[] =
		{
			.25, 0, 0,     // bottom left
			.5, 0, 0,	   // bottom right
			.365, .365, 0, // top

			//-.25, 0, 0,     // bottom left
			//-.5, 0, 0,	   // bottom right
			//-.365, .365, 0  // top
		};

		GLfloat triangle2[] =
		{
			-.25, 0, 0,     // bottom left
			-.5, 0, 0,	   // bottom right
			-.365, .365, 0  // top
		};

		WindowManager WindowManager("OpenGL Window");
		GLFWwindow * Window = WindowManager.CreateGLFWWindow();

		GLShader::VertexArrayObject VAO1;
		GLShader::VertexArrayObject VAO2;
		GLShader::ElementBufferObject EBO1;
		GLShader::VertexBufferObject VBO1(triangle1, sizeof(triangle1));
		GLShader::VertexBufferObject VBO2(triangle2, sizeof(triangle2));

		GLShader::GLVertexShader VertexShader("default.vert");
		GLShader::GLFragmentShader FragmentShader("default.frag");
		GLShader::GLFragmentShader FragmentShader2("default2.frag");
		GLShader::GLShaderProgram ShaderProgram1;
		GLShader::GLShaderProgram ShaderProgram2;

		ShaderProgram1.AttachShaders(VertexShader, FragmentShader);
		ShaderProgram2.AttachShaders(VertexShader, FragmentShader2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		while (!glfwWindowShouldClose(Window))
		{
			WindowManager.ProcessInput(Window);
			WindowManager.FillScreenColor(Background);

			glUseProgram(ShaderProgram1.GetID());
			VAO1.LinkBufferObjects(0, EBO1, VBO1);
			glDrawArrays(GL_TRIANGLES, 0, sizeof(triangle1) / 3);

			glUseProgram(ShaderProgram2.GetID());
			VAO2.LinkBufferObjects(0, EBO1, VBO2);
			glDrawArrays(GL_TRIANGLES, 0, sizeof(triangle2) / 3);

			// Swap the back buffer with the front buffer
			glfwSwapBuffers(Window);

			SPDLOG_TRACE("POLL EVENTS");

			// Listen for events on the window.
			glfwPollEvents();
		}
	}
	catch (const std::exception& ex)
	{
		SPDLOG_CRITICAL("Termination Reason: {}", ex.what());
		return -1;
	}

	return 0;
}
