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


int main()
{
	// https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
	spdlog::set_pattern("%^[%l][%!: %#] [thread %t]%$: %v");
	spdlog::set_level(spdlog::level::debug);

	std::array<GLfloat,4> Background{ (51.f / 255), (76.f / 255), (76.f / 255),1 };
	std::array<GLfloat, 9> triangleRight{
		.25, 0, 0,     // bottom left
		.5, 0, 0,	   // bottom right
		.365, .365, 0, // top
	};

	std::array<GLfloat, 9> triangleLeft{
		-.25, 0, 0,     // bottom left
		-.5, 0, 0,	   // bottom right
		-.365, .365, 0  // top
	};

	WindowManager WindowManager("OpenGL Window");
	WindowManager.SetResolution(2560, 1440);
	GLFWwindow * Window = WindowManager.CreateGLFWWindow();

	GLShader::VertexArrayObject VAO1;
	//GLShader::VertexArrayObject VAO2;
	GLShader::ElementBufferObject EBO1;
	GLShader::VertexBufferObject VBO1(triangleLeft.data(), sizeof(triangleLeft));
	GLShader::VertexBufferObject VBO2(triangleRight.data(), sizeof(triangleRight));

	GLShader::GLShaderProgram ShaderProgram1;
	GLShader::GLShaderProgram ShaderProgram2;
	GLShader::GLVertexShader VertexShader("default.vert");
	GLShader::GLFragmentShader FragmentShader("default.frag");
	GLShader::GLFragmentShader FragmentShader2("default2.frag");

	ShaderProgram1.AttachShaders(VertexShader, FragmentShader);
	ShaderProgram2.AttachShaders(VertexShader, FragmentShader2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(Window))
	{
		WindowManager.ProcessInput(Window);
		WindowManager.FillScreenColor(Background.data());

		glUseProgram(ShaderProgram1.GetID());
		VAO1.LinkBufferObjects(0, EBO1, VBO1);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(triangleLeft) / 3);

		glUseProgram(ShaderProgram2.GetID());
		VAO1.LinkBufferObjects(0, EBO1, VBO2);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(triangleRight) / 3);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(Window);

		SPDLOG_TRACE("POLL EVENTS");

		// Listen for events on the window.
		glfwPollEvents();
	}


	return 0;
}
