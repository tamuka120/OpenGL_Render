#include <iostream>
#include <sstream>

#include "opengl_manager.h"
#include "spdlog/spdlog.h"

/// <summary>
/// Creates a GLFWwindow instance and sets that window to be the current context.
/// If the window doesnt initialise the library is terminated and the process exits.
/// </summary>
GLFWwindow* OpenGLManager::CreateGLFWWindow()
{
	
	spdlog::info("Creating window.");
	try
	{
		this->m_windowInstance = glfwCreateWindow(this->m_windowWidth,
												  this->m_windowHeight,
												  this->m_windowName, NULL, NULL);

		if (this->m_windowInstance == NULL)
		{
			const char* error = "Failed to create window instance.";
			glfwTerminate();
			spdlog::error(error);
			throw std::exception(error);

		}
		glfwSetFramebufferSizeCallback(
			this->m_windowInstance, (GLFWframebuffersizefun)&OpenGLManager::ViewportResizeCb);

		glfwMakeContextCurrent(this->m_windowInstance);
		gladLoadGL();

		// Tell OpenGL the area it can render in.
		glViewport(0, 0, this->m_windowWidth, this->m_windowHeight);
	}
	catch (const std::exception& ex)
	{
		this->TerminateWindow();
		throw std::exception(ex);
	}
	return this->m_windowInstance;
}

/// <summary>
/// Terminate the window and its context.
/// </summary>
void OpenGLManager::TerminateWindow()
{
	if (this->m_windowInstance == nullptr)
	{
		return;
	}

	spdlog::info("Terminating Window.");
	glfwDestroyWindow(this->m_windowInstance);
}

/// <returns>The window instance.</returns>
GLFWwindow* OpenGLManager::GetWindow()
{
	return this->m_windowInstance;
}

/// <summary>
/// In the event that the window is resized the viewport to match the new viewport.
/// </summary>
/// <param name="window">The window instance. Unused.</param>
/// <param name="width">The width of the viewport.</param>
/// <param name="height">The height of the viewport.</param>
void OpenGLManager::ViewportResizeCb(GLFWwindow* /*window*/, float width, float height)
{
	glViewport(0, 0, width, height);
}

void OpenGLManager::SetResolution(int width, int height)
{

	spdlog::info("Setting resolution");
	this->m_windowHeight = height;
	this->m_windowWidth = width;
}

/// <summary>
/// Clear back buffer then set the back buffer to the input colour.
/// Finally swap buffers.
/// </summary>
/// <param name="RGBA">float array of color components.</param>
void OpenGLManager::FillScreenColor(const GLfloat RGBA[])
{
	const GLfloat R = RGBA[0];
	const GLfloat G = RGBA[1];
	const GLfloat B = RGBA[2];
	const GLfloat A = RGBA[3];
	this->FillScreenColor(R, G, B, A);
}

/// <summary>
/// Clear back buffer then set the back buffer to the input colour.
/// Finally swap buffers.
/// </summary>
/// <param name="R">Red component.</param>
/// <param name="G">Green component.</param>
/// <param name="B">Blue component.</param>
/// <param name="A">Alpha component.</param>
void OpenGLManager::FillScreenColor(const GLfloat R,
									const GLfloat G,
									const GLfloat B,
									const GLfloat A)
{
	// Prepare to clear back buffer and set color.
	glClearColor(R, G, B, A);

	// Clear the back buffer and set.
	glClear(GL_COLOR_BUFFER_BIT);
}

/// <summary>
/// Initialise OpenGLWindowManager
/// </summary>
/// <param name="name">Window name.</param>
OpenGLManager::OpenGLManager(const char* name = "OpenGLWindow")
{
	spdlog::info("Initialising OpenGL.");
	glfwInit();

	// Tell OpenGL we're using version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell OpenGL were using the CORE profile. This profile only contains
	// modern features. Legacy or backwards-compatible functions are not
	// included.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	this->m_windowName = name;
	this->SetResolution(800, 800);


}

OpenGLManager::~OpenGLManager()
{
	spdlog::info("Terminating OpenGL.");
	this->TerminateWindow();
	glfwTerminate();
	spdlog::info("OpenGL Terminated.");

}
