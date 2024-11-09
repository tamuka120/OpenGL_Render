#include "WindowManager.h"

#include <memory>

#include <spdlog/spdlog.h>

namespace
{
	std::shared_ptr<GLCamera> CurrentCamera;

	void ViewportResizeCallback(GLFWwindow* /*window*/, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void MouseScrollCallback(GLFWwindow* /*window*/, double xpos, double ypos)
	{
		CurrentCamera->MouseScroll(xpos, ypos);
	}

	void MouseLookCallback(GLFWwindow* /*window*/, double xpos, double ypos)
	{
		CurrentCamera->MouseLook(xpos, ypos);
	}

	void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;
			case GLFW_KEY_1:
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				break;
			case GLFW_KEY_2:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;
			case GLFW_KEY_3:
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				break;
			default:
				break;
			}
		}
	}

	void RegisterCallbacks(GLFWwindow* window)
	{
		glfwSetFramebufferSizeCallback(window, &ViewportResizeCallback);
		glfwSetCursorPosCallback(window, &MouseLookCallback);
		glfwSetScrollCallback(window, &MouseScrollCallback);
		glfwSetKeyCallback(window, &KeyInputCallback);
	}
}

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
		RegisterCallbacks(m_windowInstance);
		glfwMakeContextCurrent(m_windowInstance);

		gladLoadGL();

		GLint maxAttr;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttr);
		SPDLOG_INFO("Maximum number of vertex attributes supported is {}", maxAttr);

		// Tell OpenGL the area it can render in.
		glViewport(0, 0, m_windowWidth, m_windowHeight);
		glEnable(GL_DEPTH_TEST);
		// tell GLFW to capture our mouse
		glfwSetInputMode(m_windowInstance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;


	// There is a delay in callbacks from pressed to repeat so to ensure input is syncronous we
	// have to query it manually in the update function
	for (const int key : CameraKeyInputs)
	{
		if (int action = glfwGetKey(m_windowInstance, key); action & (GLFW_PRESS | GLFW_REPEAT))
		{
			CurrentCamera->KeyInput(key, action, deltaTime);
		}
	}
}

void WindowManager::SetCurrentCamera(std::shared_ptr<GLCamera> camera)
{
	CurrentCamera = camera;
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
