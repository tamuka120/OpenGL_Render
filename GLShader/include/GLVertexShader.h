#ifndef GLVERTEX_SHADER_H
#define GLVERTEX_SHADER_H

#include "GLBaseShader.h"

#include <filesystem>

#include <glad/glad.h>

namespace GLShader
{
class GLVertexShader : public GLBaseShader
{

public:
	GLVertexShader(const std::filesystem::path path) :
		GLBaseShader(path, GL_VERTEX_SHADER, "VERTEX")
	{};
};
}
#endif // !GLVERTEX_SHADER_H
