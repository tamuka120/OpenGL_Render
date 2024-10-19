#include "GLShaderProgram.h"

#include <string>

#include "spdlog/spdlog.h"

namespace GLShader 
{
	void GLShaderProgram::compileErrors() const
	{
		GLint hasCompiled;
		char infoLog[1024];
		glGetProgramiv(ID, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(ID, 1024, NULL, infoLog);
			SPDLOG_ERROR("SHADER_PROGRAM_LINKING_ERROR:\n{}", infoLog);
		}
	}

	void GLShaderProgram::AttachShaders(const GLBaseShader& Vertex, const GLBaseShader& Fragment) const
	{
		SPDLOG_TRACE("ATTACH VERTEX SHADER {} TO SHADER_PROGRAM {}", Vertex.GetID(), ID);
		glAttachShader(ID, Vertex.GetID());

		SPDLOG_TRACE("ATTACH FRAGMENT SHADER {} TO SHADER_PROGRAM {}", Fragment.GetID(), ID);
		glAttachShader(ID, Fragment.GetID());

		// Wrap-up/Link all the shaders together into the Shader Program
		glLinkProgram(ID);
		compileErrors();
	}

	void GLShaderProgram::Activate() const
	{
		SPDLOG_TRACE("ACTIVATE SHADER PROGRAM {}", ID);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(ID);
	}

	void GLShaderProgram::Delete() const
	{
		SPDLOG_TRACE("DELETE SHADER PROGRAM {}", ID);
		glDeleteProgram(ID);
	}

	GLShaderProgram::GLShaderProgram()
	{
		SPDLOG_DEBUG("INITIALISE SHADER PROGRAM");
		ID = glCreateProgram();
	}

	GLShaderProgram::~GLShaderProgram()
	{
		SPDLOG_DEBUG("TERMINATE SHADER PROGRAM");
		Delete();
	}
}
