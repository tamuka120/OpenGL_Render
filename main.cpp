#include <mutex>
#include <random>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLManager/opengl_manager.h"
#include "Util/helpers.h"

#include "spdlog/spdlog.h"

GLuint CreateShaders()
{
	const char* vertexShaderSource = R"V0G0N(
	#version 330 core

	layout (location = 0) in vec3 aPos;
	void main()
	{
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
	)V0G0N";

	const char* fragmentShaderSource = R"V0G0N(
	#version 330 core

	out vec4 FragColor;
	void main()
	{
		FragColor = vec4(0.31f, 0.878f, 0.922f, 1.0f);
	}
	)V0G0N";

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

GLuint* CreateVertexObjects()
{
	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	static GLuint VAO, VBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(NULL);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint result[2] = { VAO, VBO };
	return result;
}

void draw(GLfloat* color)
{

}


#ifdef _DEBUG
int main()
#else
int WinMain()
#endif // _DEBUG
{
	try
	{
		// Create window with 800x800 resolution.
		auto WindowManager = OpenGLManager("OpenGL Window");
		WindowManager.SetResolution(1366, 720);
		auto Window = WindowManager.CreateGLFWWindow();

		auto ShaderProgram = CreateShaders();
		auto VertexObjects = CreateVertexObjects();
		auto VAO = VertexObjects[0];
		auto VBO = VertexObjects[1];

		static std::default_random_engine rand(std::time(0));
		static std::uniform_real_distribution<> distributor(0, 1); // range [0, 1)
		auto r = distributor(rand);
		auto g = distributor(rand);
		auto b = distributor(rand);
		auto a = distributor(rand);
		GLfloat Background[4] = { r, g, b, a };

		// Tell OpenGL which Shader Program we want to use
		glUseProgram(ShaderProgram);

		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);

		while (!glfwWindowShouldClose(Window))
		{
			WindowManager.FillScreenColor(Background);

			// Draw the triangle using the GL_TRIANGLES primitive
			glDrawArrays(GL_TRIANGLES, 0, 3);

			// Swap the back buffer with the front buffer
			glfwSwapBuffers(Window);

			// Listen for events on the window.
			glfwPollEvents();
		}

		spdlog::info("Deleting Vertex Objects.");

		// Delete all the objects we've created
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(ShaderProgram);
	}
	catch (const std::exception& ex)
	{
		spdlog::error(std::string("Termination Reason: ") + ex.what());
		return -1;
	}


	return 0;
}


