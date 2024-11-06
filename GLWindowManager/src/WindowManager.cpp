#include "WindowManager.h"

#include <iostream>
#include <sstream>

#include "spdlog/spdlog.h"

GLFWwindow* WindowManager::CreateGLFWWindow()
{
	SPDLOG_INFO("Creating window");
	try
	{
		m_windowInstance = glfwCreateWindow(m_windowWidth,
											m_windowHeight,
											m_windowName, NULL, NULL);

		if (m_windowInstance == NULL)
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

void WindowManager::ProcessInput()
{
	if (glfwGetKey(m_windowInstance, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_windowInstance, true);
	}
	if (glfwGetKey(m_windowInstance, GLFW_KEY_1) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(m_windowInstance, GLFW_KEY_2) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (glfwGetKey(m_windowInstance, GLFW_KEY_3) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
}

void WindowManager::UpdateFpsCounter() {
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;

	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf(tmp, "%s FPS: %.f", m_windowName, fps);
		glfwSetWindowTitle(m_windowInstance, tmp);
		frame_count = 0;
	}
	frame_count++;
}

void WindowManager::ViewportResizeCb(GLFWwindow* /*window*/, int width, int height)
{
	glViewport(0, 0, width, height);
}

void WindowManager::SetResolution(int width, int height)
{
	SPDLOG_INFO("Setting resolution to {}x{}", width, height);
	m_windowHeight = height;
	m_windowWidth = width;

	if (m_windowInstance)
	{
		glfwSetWindowSize(m_windowInstance, m_windowWidth, m_windowHeight);
	}
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::Update()
{
	SPDLOG_TRACE("POLL EVENTS");
	glfwPollEvents();
	ProcessInput();
	UpdateFpsCounter();
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
	//glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	//Anti-Aliasing Hint
	glfwWindowHint(GLFW_SAMPLES, 16);

	m_windowName = name;
	SetResolution(800, 600);
}

WindowManager::~WindowManager()
{
	TerminateWindow();
	glfwTerminate();
	SPDLOG_DEBUG("OpenGL Terminated");

}
