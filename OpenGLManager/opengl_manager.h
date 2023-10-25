#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class OpenGLManager
{
private:
	float m_windowWidth;
	float m_windowHeight;
	const char* m_windowName;
	GLFWwindow* m_windowInstance = nullptr;

	// OpenGL Callbacks

public:

	GLFWwindow* CreateGLFWWindow();
	void TerminateWindow();
	GLFWwindow* GetWindow();

	void SetResolution(int width, int height);
	void FillScreenColor(const GLfloat RGBA[]);
	void FillScreenColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A);

	// Callbacks
	static void ViewportResizeCb(GLFWwindow* window, float width, float height);

	OpenGLManager(const char* name);
	~OpenGLManager();
};

