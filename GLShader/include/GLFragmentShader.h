#ifndef GLFRAGMENT_SHADER_H
#define GLFRAGMENT_SHADER_H

#include "GLBaseShader.h"

#include <filesystem>

#include <glad/glad.h>

namespace GLShader
{
class GLFragmentShader : public GLBaseShader
{

public:
	GLFragmentShader(const std::filesystem::path path) :
		GLBaseShader(path, GL_FRAGMENT_SHADER, "FRAGMENT")
	{};
};
}
#endif // !GLFRAGMENT_SHADER_H
