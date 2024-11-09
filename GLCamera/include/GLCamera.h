#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/>

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


struct CameraProperties
{
	float CameraSensitivity = 0.1f;
	float CameraSpeed = 2.5f;
	float Pitch = 0.0f;
	float Yaw = -90;

	float AspectRatio;
	float FOV;
	float NearPlane = 0.1f;
	float FarPlane = 100.f;

	glm::vec3 CameraFront;
	glm::vec3 CameraRight;
	glm::vec3 CameraUp;
	glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);

	const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

class GLCamera
{


private:
	std::shared_ptr<GLFWwindow*> Window;
	GLuint ViewLocation;
	GLuint PerspLocation;

	bool FirstMouse = true;
	float LastX = 0.0f;
	float LastY = 0.0f;

	float MaxPitch = 89.f;
	float MinPitch = -89.f;
	float MaxFOV= 120.f;
	float MinFOV = 1.f;

	CameraProperties Properties{};
	
public:

	CameraProperties GetCameraProperties() const { return Properties; }

	void UpdateViewMatrix();
	void UpdatePerspectiveMatrix();

	void UpdateCameraVectors();
	void MouseScroll(double xpos, double ypos);
	void MouseLook(double xpos, double ypos);
	void KeyInput(int key, int action, float deltaTime);

	GLCamera(std::shared_ptr<GLFWwindow*> window, GLuint ShaderProgramID, float fov = 45.f, float aspectRatio = 800.0f / 600.0f);
	~GLCamera();

};


#endif // !GLCAMERA_H
