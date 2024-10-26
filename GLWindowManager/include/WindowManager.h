#ifndef OPENGL_MANAGER_H
#define OPENGL_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager
{
private:
	int m_windowWidth;
	int m_windowHeight;
	const char* m_windowName;
	GLFWwindow* m_windowInstance = nullptr;

	// OpenGL Callbacks

	/// <summary>
	/// In the event that the window is resized the viewport to match the new viewport.
	/// </summary>
	/// <param name="window">The window instance. Unused.</param>
	/// <param name="width">The width of the viewport.</param>
	/// <param name="height">The height of the viewport.</param>
	static void ViewportResizeCb(GLFWwindow* window, int width, int height);

public:
	/// <summary>
	/// Creates a GLFWwindow instance and sets that window to be the current context.
	/// If the window doesnt initialise the library is terminated and the process exits.
	/// </summary>
	GLFWwindow* CreateGLFWWindow();

	/// <summary>
	/// Terminate the window and its context.
	/// </summary>
	void TerminateWindow();

	/// <returns>The window instance.</returns>
	GLFWwindow* GetWindow();

	/// <summary>
	/// Check if there is a key has been press in the current window instance and execute
	/// the function relate to the key.
	/// </summary>
	/// <param name="window">The window instance.</param>
	void ProcessInput(GLFWwindow* window);

	/// <summary>
	/// In the event that the window is resized the viewport to match the new viewport.
	/// </summary>
	/// <param name="window">The window instance. Unused.</param>
	/// <param name="width">The width of the viewport.</param>
	/// <param name="height">The height of the viewport.</param>
	void SetResolution(int width, int height);

	/// <summary>
	/// Clear back buffer then set the back buffer to the input colour.
	/// Finally swap buffers.
	/// </summary>
	/// <param name="RGBA">float array of color components.</param>
	void FillScreenColor(const GLfloat RGBA[]);

	/// <summary>
	/// Clear back buffer then set the back buffer to the input colour.
	/// Finally swap buffers.
	/// </summary>
	/// <param name="R">Red component.</param>
	/// <param name="G">Green component.</param>
	/// <param name="B">Blue component.</param>
	/// <param name="A">Alpha component.</param>
	void FillScreenColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A);

	/// <summary>
	/// Initialise OpenGLWindowManager
	/// </summary>
	/// <param name="name">Window name.</param>
	WindowManager(const char* name = "OpenGLWindow");
	~WindowManager();
};

#endif // !OPENGL_MANAGER_H




