#include "WindowManager.h"

#include <iostream>
#include <sstream>

#include "spdlog/spdlog.h"

GLFWwindow* WindowManager::CreateGLFWWindow()
{
	SPDLOG_INFO("Creating window");
	try
	{
		this->m_windowInstance = glfwCreateWindow(this->m_windowWidth,
												  this->m_windowHeight,
												  this->m_windowName, NULL, NULL);

		if (this->m_windowInstance == NULL)
		{
			const char* error = "Failed to create window instance. Window was NULL";
			glfwTerminate();
			SPDLOG_ERROR(error);
			throw std::exception(error);

		}
		glfwSetFramebufferSizeCallback(
			m_windowInstance, (GLFWframebuffersizefun)&WindowManager::ViewportResizeCb);

		glfwMakeContextCurrent(m_windowInstance);

		gladLoadGL();

		GLint maxAttr;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttr);
		SPDLOG_INFO("Maximum number of vertex attributes supported is {}", maxAttr);

		// Tell OpenGL the area it can render in.
		glViewport(0, 0, m_windowWidth, m_windowHeight);
	}
	catch (const std::exception& ex)
	{
		TerminateWindow();
		throw std::exception(ex);
	}
	return m_windowInstance;
}

void WindowManager::TerminateWindow()
{
	if (m_windowInstance == nullptr)
	{
		return;
	}

	SPDLOG_INFO("Terminating Window");
	glfwDestroyWindow(m_windowInstance);
}

GLFWwindow* WindowManager::GetWindow()
{
	return m_windowInstance;
}

void WindowManager::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void WindowManager::ViewportResizeCb(GLFWwindow* /*window*/, float width, float height)
{
	glViewport(0, 0, width, height);
}

void WindowManager::SetResolution(int width, int height)
{
	SPDLOG_INFO("Setting resolution to {}x{}", width, height);
	m_windowHeight = height;
	m_windowWidth = width;
}

void WindowManager::FillScreenColor(const GLfloat RGBA[])
{
	const GLfloat R = RGBA[0];
	const GLfloat G = RGBA[1];
	const GLfloat B = RGBA[2];
	const GLfloat A = RGBA[3];
	FillScreenColor(R, G, B, A);
}

void WindowManager::FillScreenColor(const GLfloat R,
									const GLfloat G,
									const GLfloat B,
									const GLfloat A)
{
	// Prepare to clear back buffer and set color.
	glClearColor(R, G, B, A);

	// Clear the back buffer and set.
	glClear(GL_COLOR_BUFFER_BIT);
}

WindowManager::WindowManager(const char* name)
{
	SPDLOG_DEBUG("Initialising OpenGL");
	glfwInit();

	// Tell OpenGL we're using version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell OpenGL were using the CORE profile. This profile only contains
	// modern features. Legacy or backwards-compatible functions are not
	// included.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	m_windowName = name;
	SetResolution(2560, 1440);
}

WindowManager::~WindowManager()
{
	TerminateWindow();
	glfwTerminate();
	SPDLOG_DEBUG("OpenGL Terminated");

}
