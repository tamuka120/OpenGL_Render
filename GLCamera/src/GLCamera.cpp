#include "GLCamera.h"

#include <algorithm>

#include <spdlog/spdlog.h>

#include <glm/gtc/type_ptr.hpp>

void GLCamera::UpdateViewMatrix()
{
	const glm::mat4 view = glm::lookAt(
		Properties.CameraPosition,
		Properties.CameraPosition + Properties.CameraFront, 
		Properties.CameraUp);

	glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(view));
}

void GLCamera::UpdatePerspectiveMatrix()
{
	const glm::mat4 perspective = glm::perspective(
		glm::radians(Properties.FOV),
		Properties.AspectRatio, 
		Properties.NearPlane,
		Properties.FarPlane);
	glUniformMatrix4fv(PerspLocation, 1, GL_FALSE, glm::value_ptr(perspective));
}

void GLCamera::UpdateCameraVectors()
{
	spdlog::debug(
		"\nPosition: [{},{}, {}]"
		"\nTarget: [{},{}, {}]"
		"\nPitch:{}"
		"\nYaw:{}"
		"\n-------------------------",
		Properties.CameraPosition.x,
		Properties.CameraPosition.y,
		Properties.CameraPosition.z,
		Properties.CameraPosition.x + Properties.CameraFront.x,
		Properties.CameraPosition.y + Properties.CameraFront.y,
		Properties.CameraPosition.z + Properties.CameraFront.z,
		Properties.Pitch,
		Properties.Yaw);


	glm::vec3 front
	{
		cos(glm::radians(Properties.Yaw)) * cos(glm::radians(Properties.Pitch)),
		sin(glm::radians(Properties.Pitch)),
		sin(glm::radians(Properties.Yaw)) * cos(glm::radians(Properties.Pitch))
	};

	// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Properties.CameraFront = glm::normalize(front);
	Properties.CameraRight = glm::normalize(glm::cross(Properties.CameraFront, Properties.WorldUp));  
	Properties.CameraUp = glm::normalize(glm::cross(Properties.CameraRight, Properties.CameraFront));
}

void GLCamera::MouseScroll(double /*xpos*/, double ypos)
{
	Properties.FOV -= static_cast<float>(ypos);
	Properties.FOV = std::min(MaxFOV, std::max(MinFOV, Properties.FOV));
	UpdatePerspectiveMatrix();
}

void GLCamera::MouseLook(double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (FirstMouse)
	{
		LastX = xpos;
		LastY = ypos;
		FirstMouse = false;
	}

	float xoffset = xpos - LastX;
	float yoffset = LastY - ypos; // reversed since y-coordinates go from bottom to top
	LastX = xpos;
	LastY = ypos;

	Properties.Yaw += xoffset * Properties.CameraSensitivity;
	Properties.Pitch += yoffset * Properties.CameraSensitivity;

	// Keep pitch in bounds
	Properties.Pitch = std::min(MaxPitch, std::max(MinPitch, Properties.Pitch));
	UpdateCameraVectors();
	UpdateViewMatrix();
}

void GLCamera::KeyInput(int key, int action, float deltaTime)
{
	const glm::vec3 XPositionOffset = Properties.CameraRight * Properties.CameraSpeed * deltaTime;
	const glm::vec3 YPositionOffset = Properties.CameraUp * Properties.CameraSpeed * deltaTime;
	const glm::vec3 ZPositionOffset = Properties.CameraFront * Properties.CameraSpeed * deltaTime;

	switch (key)
	{
	case GLFW_KEY_W:
		Properties.CameraPosition += ZPositionOffset;
		break;
	case GLFW_KEY_A:
		Properties.CameraPosition -= XPositionOffset;
		break;
	case GLFW_KEY_S:
		Properties.CameraPosition -= ZPositionOffset;
		break;
	case GLFW_KEY_D:
		Properties.CameraPosition += XPositionOffset;
		break;
	case GLFW_KEY_Q:
		Properties.CameraPosition -= YPositionOffset;
		break;
	case GLFW_KEY_E:
		Properties.CameraPosition += YPositionOffset;
		break;
	default:
		break;

	}

	UpdateCameraVectors();
	UpdateViewMatrix();
}

GLCamera::GLCamera(std::shared_ptr<GLFWwindow*> window, GLuint ShaderProgramID, float fov, float aspectRatio) :
	Window(window)
{
	Properties.FOV = fov;
	Properties.AspectRatio = aspectRatio;
	ViewLocation = glGetUniformLocation(ShaderProgramID, "view");
	PerspLocation = glGetUniformLocation(ShaderProgramID, "perspective");

	UpdateCameraVectors();
	UpdateViewMatrix();
	UpdatePerspectiveMatrix();
}

GLCamera::~GLCamera()
{
}
