#include "memory"
#include <mutex>
#include <random>
#include <thread>
#include <array>
#include <algorithm>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ElementBufferObject.h"
#include "GLFragmentShader.h"
#include "GLShaderProgram.h"
#include "GLTexture.h"
#include "GLVertexShader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "WindowManager.h"
#include "GLShader/include/resources.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
namespace
{
	std::array<GLfloat, 4> Background{ (51.f / 255), (76.f / 255), (76.f / 255),1 };

	std::array<GLfloat, 12> Rect{
		-0.5f,  0.5f, 0.0f,   // top left 0
		0.5f,  0.5f, 0.0f,  // top right 1
		-0.5f, -0.5f, 0.0f,  // bottom left 2
		0.5f, -0.5f, 0.0f,  // bottom right 3
	};

	std::array<GLuint, 6> indices = {  // note that we start from 0!
		0, 2, 3,   // first triangle
		3, 1, 0    // second triangle
	};

	std::array<GLfloat, 8> texCoords = {
		0.0f, 1.0f,  // top-right  
		1.0f, 1.0f,   // top-left
		0.0f, 0.0f,  // bottom-left
		1.0f, 0.0f,    // bottom-right
	};


	std::array<GLfloat, 180> cube = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
}



int main()
{
	// https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
	spdlog::set_pattern("%^[%l][%!: %#] [thread %t]%$: %v");
	spdlog::set_level(spdlog::level::info);

	WindowManager WindowManager("OpenGL Window");
	const auto Window = std::make_unique<GLFWwindow*>(WindowManager.CreateGLFWWindow());

	GLShader::GLShaderProgram ShaderProgram1;
	GLShader::GLVertexShader VertexShader("default.vert");
	GLShader::GLFragmentShader FragmentShader("default.frag");
	ShaderProgram1.AttachShaders(VertexShader, FragmentShader);

	// Buffers will bind and unbind during initialisation so other objects (such as the VAO)
	// can link them as needed.
	GLShader::VertexBufferObject VBO1(cube.data(), sizeof(cube));
	GLShader::VertexBufferObject VBO3(texCoords.data(), sizeof(texCoords));
	GLShader::ElementBufferObject EBO1(indices.data(), sizeof(indices));
	GLShader::VertexArrayObject VAO1(&EBO1, &VBO1);

	// Create and Set Texture Uniform
	std::filesystem::path path = IMAGES_DIR / std::filesystem::path("wall.jpg");
	GLShader::GLTexture Texture(path, 512, 512);
	Texture.SetTextureUnit(GL_TEXTURE0);
	Texture.Bind();
	Texture.CreateTexture();

	const GLuint ID = ShaderProgram1.GetID();
	const GLuint PositionAttributeIndex = 0;
	const GLuint TexCoordAttributeIndex = 1;
	// Set Vertex Position Attribute
	VAO1.Bind();
	EBO1.Bind();
	VBO1.Bind();
	glBindAttribLocation(ID, PositionAttributeIndex, "vertex_position");
	//glVertexAttribPointer(PositionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribPointer(PositionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(PositionAttributeIndex);

	// Set Texture Coordinate Attribute
	//VBO3.Bind();
	glBindAttribLocation(ID, TexCoordAttributeIndex, "texture_coords");
	//glVertexAttribPointer(TexCoordAttributeIndex, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glVertexAttribPointer(TexCoordAttributeIndex, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(TexCoordAttributeIndex);

	glUseProgram(ID);
	const GLuint ModelLocation = glGetUniformLocation(ID, "model");
	const GLuint ViewLocation = glGetUniformLocation(ID, "view");
	const GLuint PerspLocation = glGetUniformLocation(ID, "perspective");
	const GLuint IntensityLocation = glGetUniformLocation(ID, "color_intensity");

	// coordinate system conversion
	// local -> world (model matrix) 
	// world -> view  (view matrix)
	// view  -> clip  (projection matrix)
	// clip = projection * view * model * local
	// 
	// The projection matrix maps a given frustum range to clip space,
	// but also manipulates the w value of each vertex coordinate in
	// such a way that the further away a vertex coordinate is from the
	// viewer, the higher this w component becomes. 

	// In world space our object is current still location at the origin (0,0,0), in view space our camera becomes 
	// the origin so our object is currently inside the camera and not visibe. To make our object visible we want
	// to move the camera backwards. To move a camera backwards, is the same as moving the entire scene forward.
	const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(view));

	// glm::perspective(fov, aspect_ratio, near_plane, far_plane)
	const glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(PerspLocation, 1, GL_FALSE, glm::value_ptr(perspective));


	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(*Window))
	{
		WindowManager.Update();
		WindowManager.FillScreenColor(Background.data());

		float time = glfwGetTime();
		//const glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		//glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1f(IntensityLocation, sin(time) / 2.0f + 0.5f);

		//// Draw
		//VAO1.BindAllBuffers();
		////glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);


		for (int idx = 0; idx < 10; idx++)
		{
			glUniform1f(IntensityLocation, (sin(time) + sin(idx)) / 2.0f + 0.5f);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[idx]);
			float angle = 20.0f * idx;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			model = glm::rotate(model, time, glm::vec3(0.5f, 1.0f, 0.0f));

			glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(*Window);
	}

	return 0;
}

//std::array<GLfloat, 9> Triangle{
//	.25, 0, 0,     // bottom left
//	.5, 0, 0,	   // bottom right
//	.365, .365, 0, // top
//};

//void drawArrays(
//	GLShader::GLShaderProgram& ShaderProgram,
//	GLShader::VertexArrayObject& VAO,
//	float intensity)
//{
//	GLuint id = ShaderProgram.GetID();
//	glUseProgram(id);
//	glUniform1f(
//		glGetUniformLocation(id, "color_intensity"),
//		intensity);
//
//	VAO.BindAllBuffers();
//	glDrawArrays(GL_TRIANGLES, 0, VAO.GetVertexBufferSize() / 3);
//}

//GLShader::GLShaderProgram ShaderProgram2;
//GLShader::GLFragmentShader FragmentShader2("default2.frag");
//ShaderProgram2.AttachShaders(VertexShader, FragmentShader2);
//GLShader::VertexBufferObject VBO2(Triangle.data(), sizeof(Triangle));
//GLShader::ElementBufferObject EBO2;
//GLShader::VertexArrayObject VAO2(&EBO2, &VBO2);

//VAO2.Bind();
//VBO2.Bind();
//glVertexAttribPointer(PositionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//glEnableVertexAttribArray(PositionAttributeIndex);
//drawArrays(ShaderProgram2, VAO2, cos(time) / 2.0f + 0.5f);
